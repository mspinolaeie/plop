#include "MainWindow.h"

#include "PartDimensionWindow.h"
#include "PlotWindow.h"

#include <QAction>
#include <QCheckBox>
#include <QComboBox>
#include <QDesktopServices>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QSettings>
#include <QSpinBox>
#include <QStatusBar>
#include <QTabWidget>
#include <QTextEdit>
#include <QThread>
#include <QUrl>
#include <QVBoxLayout>

#include <memory>

#include "plop_parms.h"
#include "plot.h"

namespace {

constexpr int kMaxRecentFiles = 8;

class AutoCellDialog : public QDialog
{
public:
	AutoCellDialog(const QString &directory, QWidget *parent = nullptr)
		: QDialog(parent)
		, selector_(new QComboBox(this))
	{
		setWindowTitle(tr("AutoCell Template"));

		QVBoxLayout *layout = new QVBoxLayout(this);
		layout->addWidget(new QLabel(tr("Select a template from the app-relative autocell directory."), this));
		layout->addWidget(selector_);

		QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
		layout->addWidget(buttons);

		QDir dir(directory);
		for (const QFileInfo &fileInfo : dir.entryInfoList(QStringList() << QStringLiteral("*.gr"), QDir::Files | QDir::Readable)) {
			selector_->addItem(fileInfo.fileName(), fileInfo.absoluteFilePath());
		}

		connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
		connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
	}

	QString selectedPath() const
	{
		return selector_->currentData().toString();
	}

	bool hasTemplates() const
	{
		return selector_->count() > 0;
	}

private:
	QComboBox *selector_;
};

class GraphOptionsDialog : public QDialog
{
public:
	GraphOptionsDialog(QWidget *parent = nullptr)
		: QDialog(parent)
		, colorsSpin_(new QSpinBox(this))
		, contoursSpin_(new QSpinBox(this))
		, zRangeEdit_(new QLineEdit(this))
		, contourSpaceEdit_(new QLineEdit(this))
	{
		setWindowTitle(tr("Graph Options"));
		colorsSpin_->setRange(2, color_map_size);
		colorsSpin_->setValue(n_colors);
		contoursSpin_->setRange(2, max_contours);
		contoursSpin_->setValue(n_contours);
		zRangeEdit_->setText(pic_z_range == 0.0 ? QString() : QString::number(pic_z_range, 'g', 10));
		contourSpaceEdit_->setText(contour_space == 0.0 ? QString() : QString::number(contour_space, 'g', 10));

		QFormLayout *form = new QFormLayout;
		form->addRow(tr("Colors"), colorsSpin_);
		form->addRow(tr("Contours"), contoursSpin_);
		form->addRow(tr("Z range"), zRangeEdit_);
		form->addRow(tr("Contour spacing"), contourSpaceEdit_);

		QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
		connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
		connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

		QVBoxLayout *layout = new QVBoxLayout(this);
		layout->addLayout(form);
		layout->addWidget(buttons);
	}

	void apply() const
	{
		n_colors = colorsSpin_->value();
		n_contours = contoursSpin_->value();
		pic_z_range = zRangeEdit_->text().trimmed().isEmpty() ? 0.0 : zRangeEdit_->text().toDouble();
		contour_space = contourSpaceEdit_->text().trimmed().isEmpty() ? 0.0 : contourSpaceEdit_->text().toDouble();
	}

private:
	QSpinBox *colorsSpin_;
	QSpinBox *contoursSpin_;
	QLineEdit *zRangeEdit_;
	QLineEdit *contourSpaceEdit_;
};

class TextDialog : public QDialog
{
public:
	TextDialog(const QString &title, const QString &text, QWidget *parent = nullptr)
		: QDialog(parent)
	{
		setWindowTitle(title);
		QVBoxLayout *layout = new QVBoxLayout(this);
		QTextEdit *viewer = new QTextEdit(this);
		viewer->setReadOnly(true);
		viewer->setPlainText(text);
		layout->addWidget(viewer);
		QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Close, this);
		connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
		layout->addWidget(buttons);
		resize(700, 500);
	}
};

struct AsyncRunState
{
	bool ok = false;
	QString errorMessage;
	plopqt::RunResults results;
};

}

MainWindow::MainWindow()
	: controlEditor_(new QPlainTextEdit(this))
	, runOutput_(new QTextEdit(this))
	, mirrorSummary_(new QTextEdit(this))
	, supportsSummary_(new QTextEdit(this))
	, variablesSummary_(new QTextEdit(this))
	, partsSummary_(new QTextEdit(this))
	, z88Summary_(new QTextEdit(this))
	, runProgress_(new QProgressBar(this))
	, usePvCheckBox_(new QCheckBox(tr("Use peak-valley error"), this))
	, refocusCheckBox_(new QCheckBox(tr("Refocus"), this))
	, refocusXyrCheckBox_(new QCheckBox(tr("Refocus XYR"), this))
	, useBasisCheckBox_(new QCheckBox(tr("Use basis"), this))
	, generateZ88CheckBox_(new QCheckBox(tr("Generate Z88 input"), this))
	, traceOptCheckBox_(new QCheckBox(tr("Trace optimization"), this))
	, zernikeCheckBox_(new QCheckBox(tr("Calculate Zernike"), this))
	, zernikeOrderSpin_(new QSpinBox(this))
	, monteTestsSpin_(new QSpinBox(this))
	, resultsView_(new QTextEdit(this))
	, recentFilesMenu_(menuBar()->addMenu(tr("Recent Files")))
	, meshWindow_(new PlotWindow(tr("Mesh Plot"), this))
	, supportsWindow_(new PlotWindow(tr("Support Plot"), this))
	, colorWindow_(new PlotWindow(tr("Color Plot"), this))
	, contourWindow_(new PlotWindow(tr("Contour Plot"), this))
	, partsWindow_(new PlotWindow(tr("Cell Parts Plot"), this))
	, quadsWindow_(new PlotWindow(tr("Quad Plot"), this))
	, z88Window_(new PlotWindow(tr("Z88 Color Plot"), this))
	, partDimensionWindow_(new PartDimensionWindow(&facade_, this))
{
	setWindowTitle(tr("PLOP Qt"));
	resize(1200, 900);

	QMenu *fileMenu = menuBar()->addMenu(tr("File"));
	fileMenu->addAction(tr("New"), this, &MainWindow::newControlFile);
	fileMenu->addAction(tr("Open..."), this, qOverload<>(&MainWindow::openControlFile));
	fileMenu->addAction(tr("Save"), this, &MainWindow::saveControlFile);
	fileMenu->addAction(tr("Save As..."), this, &MainWindow::saveControlFileAs);
	fileMenu->addMenu(recentFilesMenu_);

	QMenu *toolsMenu = menuBar()->addMenu(tr("Tools"));
	toolsMenu->addAction(tr("AutoCell Template..."), this, &MainWindow::chooseAutoCellTemplate);
	toolsMenu->addAction(tr("Graph Options..."), this, &MainWindow::showGraphOptions);
	toolsMenu->addAction(tr("Run Z88"), this, &MainWindow::runZ88);

	QMenu *windowsMenu = menuBar()->addMenu(tr("Windows"));
	windowsMenu->addAction(tr("Mesh"), this, &MainWindow::openPlotMesh);
	windowsMenu->addAction(tr("Supports"), this, &MainWindow::openPlotSupports);
	windowsMenu->addAction(tr("Color"), this, &MainWindow::openPlotColor);
	windowsMenu->addAction(tr("Contour"), this, &MainWindow::openPlotContour);
	windowsMenu->addAction(tr("Parts"), this, &MainWindow::openPlotParts);
	windowsMenu->addAction(tr("Quads"), this, &MainWindow::openPlotQuads);
	windowsMenu->addAction(tr("Z88 Color"), this, &MainWindow::openPlotZ88);
	windowsMenu->addAction(tr("Part Dimensions"), this, &MainWindow::openPartDimensions);

	QMenu *helpMenu = menuBar()->addMenu(tr("Help"));
	helpMenu->addAction(tr("Open Manual"), this, &MainWindow::openManual);
	helpMenu->addAction(tr("What's New"), this, &MainWindow::showWhatsNew);
	helpMenu->addAction(tr("About"), this, &MainWindow::showAbout);

	QWidget *central = new QWidget(this);
	setCentralWidget(central);

	QTabWidget *tabs = new QTabWidget(central);
	controlEditor_->setPlainText(QStringLiteral("; Paste or open a .gr file here.\n"));
	tabs->addTab(controlEditor_, tr("Text"));

	QWidget *runTab = new QWidget(tabs);
	QVBoxLayout *runLayout = new QVBoxLayout(runTab);
	QHBoxLayout *topControls = new QHBoxLayout;
	topControls->addWidget(usePvCheckBox_);
	topControls->addWidget(refocusCheckBox_);
	topControls->addWidget(refocusXyrCheckBox_);
	topControls->addWidget(useBasisCheckBox_);
	topControls->addWidget(generateZ88CheckBox_);
	topControls->addWidget(traceOptCheckBox_);
	runLayout->addLayout(topControls);

	QHBoxLayout *secondControls = new QHBoxLayout;
	zernikeOrderSpin_->setRange(1, max_refocus_distortion_order);
	zernikeOrderSpin_->setValue(12);
	monteTestsSpin_->setRange(0, 100000);
	secondControls->addWidget(zernikeCheckBox_);
	secondControls->addWidget(new QLabel(tr("Zernike order"), runTab));
	secondControls->addWidget(zernikeOrderSpin_);
	secondControls->addSpacing(16);
	secondControls->addWidget(new QLabel(tr("Monte tests"), runTab));
	secondControls->addWidget(monteTestsSpin_);
	secondControls->addStretch(1);
	runLayout->addLayout(secondControls);

	QHBoxLayout *buttonRow = new QHBoxLayout;
	QPushButton *runButton = new QPushButton(tr("Run PLOP"), runTab);
	QPushButton *runZ88Button = new QPushButton(tr("Run Z88"), runTab);
	QPushButton *refreshButton = new QPushButton(tr("Refresh Summaries"), runTab);
	buttonRow->addWidget(runButton);
	buttonRow->addWidget(runZ88Button);
	buttonRow->addWidget(refreshButton);
	buttonRow->addStretch(1);
	runLayout->addLayout(buttonRow);

	runProgress_->setRange(0, 1);
	runProgress_->setValue(0);
	runLayout->addWidget(runProgress_);

	resultsView_->setReadOnly(true);
	runOutput_->setReadOnly(true);
	runLayout->addWidget(new QLabel(tr("Results"), runTab));
	runLayout->addWidget(resultsView_, 0);
	runLayout->addWidget(new QLabel(tr("Run Output"), runTab));
	runLayout->addWidget(runOutput_, 1);
	tabs->addTab(runTab, tr("Run"));

	mirrorSummary_->setReadOnly(true);
	supportsSummary_->setReadOnly(true);
	variablesSummary_->setReadOnly(true);
	partsSummary_->setReadOnly(true);
	z88Summary_->setReadOnly(true);
	tabs->addTab(mirrorSummary_, tr("Mirror"));
	tabs->addTab(supportsSummary_, tr("Supports"));
	tabs->addTab(variablesSummary_, tr("Variables"));
	tabs->addTab(partsSummary_, tr("Parts"));
	tabs->addTab(z88Summary_, tr("Z88"));

	QVBoxLayout *layout = new QVBoxLayout(central);
	layout->addWidget(tabs);

	connect(runButton, &QPushButton::clicked, this, &MainWindow::runPlop);
	connect(runZ88Button, &QPushButton::clicked, this, &MainWindow::runZ88);
	connect(refreshButton, &QPushButton::clicked, this, &MainWindow::refreshSummaries);

	QSettings settings;
	recentFiles_ = settings.value(QStringLiteral("recentFiles")).toStringList();
	updateRecentFilesMenu();

	refocusCheckBox_->setChecked(true);
	useBasisCheckBox_->setChecked(true);

	statusBar()->showMessage(tr("Ready"));
	refreshSummaries();
}

plopqt::RunSettings MainWindow::gatherRunSettings() const
{
	plopqt::RunSettings settings;
	settings.usePeakValley = usePvCheckBox_->isChecked();
	settings.refocus = refocusCheckBox_->isChecked();
	settings.refocusXyr = refocusXyrCheckBox_->isChecked();
	settings.useBasis = useBasisCheckBox_->isChecked();
	settings.generateZ88Input = generateZ88CheckBox_->isChecked();
	settings.traceOptimization = traceOptCheckBox_->isChecked();
	settings.calculateZernike = zernikeCheckBox_->isChecked();
	settings.zernikeOrder = zernikeOrderSpin_->value();
	settings.monteTests = monteTestsSpin_->value();
	return settings;
}

void MainWindow::newControlFile()
{
	currentFilePath_.clear();
	controlEditor_->setPlainText(QString());
	refreshSummaries();
}

void MainWindow::openControlFile(const QString &filePath)
{
	QString errorMessage;
	const QString text = facade_.loadControlFile(filePath, &errorMessage);
	if (!errorMessage.isEmpty()) {
		QMessageBox::critical(this, tr("Open Control File"), errorMessage);
		return;
	}

	controlEditor_->setPlainText(text);
	setCurrentFile(filePath);
	refreshSummaries();
	appendStatusMessage(tr("Loaded %1").arg(QDir::toNativeSeparators(filePath)));
}

void MainWindow::openControlFile()
{
	const QString filePath = QFileDialog::getOpenFileName(this, tr("Open Control File"), QString(), tr("PLOP Control Files (*.gr);;All Files (*)"));
	if (!filePath.isEmpty()) {
		openControlFile(filePath);
	}
}

void MainWindow::saveControlFile()
{
	if (currentFilePath_.isEmpty()) {
		saveControlFileAs();
		return;
	}

	QString errorMessage;
	if (!facade_.saveControlFile(currentFilePath_, controlEditor_->toPlainText(), &errorMessage)) {
		QMessageBox::critical(this, tr("Save Control File"), errorMessage);
		return;
	}

	appendStatusMessage(tr("Saved %1").arg(QDir::toNativeSeparators(currentFilePath_)));
}

void MainWindow::saveControlFileAs()
{
	const QString filePath = QFileDialog::getSaveFileName(this, tr("Save Control File"), currentFilePath_, tr("PLOP Control Files (*.gr);;All Files (*)"));
	if (filePath.isEmpty()) {
		return;
	}

	QString errorMessage;
	if (!facade_.saveControlFile(filePath, controlEditor_->toPlainText(), &errorMessage)) {
		QMessageBox::critical(this, tr("Save Control File"), errorMessage);
		return;
	}

	setCurrentFile(filePath);
	appendStatusMessage(tr("Saved %1").arg(QDir::toNativeSeparators(filePath)));
}

void MainWindow::chooseAutoCellTemplate()
{
	AutoCellDialog dialog(facade_.autoCellDirectory(), this);
	if (!dialog.hasTemplates()) {
		QMessageBox::information(this, tr("AutoCell Template"), tr("No .gr templates were found in the app-relative autocell directory."));
		return;
	}

	if (dialog.exec() != QDialog::Accepted) {
		return;
	}

	openControlFile(dialog.selectedPath());
}

void MainWindow::runPlop()
{
	const plopqt::RunSettings settings = gatherRunSettings();
	const QString controlText = controlEditor_->toPlainText();
	std::shared_ptr<AsyncRunState> state = std::make_shared<AsyncRunState>();
	QThread *thread = QThread::create([this, controlText, settings, state]() {
		state->ok = facade_.runControlText(controlText, settings, &state->results, &state->errorMessage);
	});
	thread->setParent(this);

	runProgress_->setRange(0, 0);
	statusBar()->showMessage(tr("Running PLOP..."));

	connect(thread, &QThread::finished, this, [this, thread, state]() {
		runProgress_->setRange(0, 1);
		runProgress_->setValue(1);
		thread->deleteLater();

		if (!state->ok) {
			QMessageBox::critical(this, tr("Run PLOP"), state->errorMessage);
			statusBar()->showMessage(tr("Run failed"), 5000);
			return;
		}

		updateRunResults(state->results);
		refreshSummaries();
		statusBar()->showMessage(tr("Run completed"), 5000);
	});
	thread->start();
}

void MainWindow::runZ88()
{
	plopqt::RunResults results;
	QString errorMessage;
	if (!facade_.runZ88(&results, &errorMessage)) {
		QMessageBox::critical(this, tr("Run Z88"), errorMessage);
		return;
	}

	updateRunResults(results);
	refreshSummaries();
	openPlot(plopqt::PlotKind::Z88Color, tr("Z88 Color Plot"));
	statusBar()->showMessage(tr("Z88 completed"), 5000);
}

void MainWindow::openManual()
{
	const QString manual = facade_.manualPath();
	if (!QFileInfo::exists(manual)) {
		QMessageBox::information(this, tr("Open Manual"), tr("The user manual was not found next to the application."));
		return;
	}

	QDesktopServices::openUrl(QUrl::fromLocalFile(manual));
}

void MainWindow::showAbout()
{
	TextDialog dialog(tr("About PLOP Qt"),
		tr("PLOP Qt\n\nModern local build and Qt Widgets frontend for the legacy PLOP numerical core."),
		this);
	dialog.exec();
}

void MainWindow::showWhatsNew()
{
	TextDialog dialog(tr("What's New"),
		tr("This local build replaces the legacy VCL-only entrypoint with:\n"
		   "- MinGW build targets for the legacy core and Z88 tools\n"
		   "- a Qt Widgets shell around the existing .gr workflow\n"
		   "- app-relative runtime assets instead of registry-based configuration"),
		this);
	dialog.exec();
}

void MainWindow::showGraphOptions()
{
	GraphOptionsDialog dialog(this);
	if (dialog.exec() != QDialog::Accepted) {
		return;
	}
	dialog.apply();
	statusBar()->showMessage(tr("Graph options updated"), 3000);
}

void MainWindow::refreshSummaries()
{
	QString errorMessage;
	if (!controlEditor_->toPlainText().trimmed().isEmpty()) {
		facade_.parseControlText(controlEditor_->toPlainText(), &errorMessage);
		if (!errorMessage.isEmpty()) {
			appendStatusMessage(errorMessage);
		}
	}
	const plopqt::SummaryData summaries = facade_.summaries();
	updateSummaryTabs(summaries);
	partDimensionWindow_->refresh();
}

void MainWindow::openPlotMesh()
{
	openPlot(plopqt::PlotKind::Mesh, tr("Mesh Plot"));
}

void MainWindow::openPlotSupports()
{
	openPlot(plopqt::PlotKind::Supports, tr("Support Plot"));
}

void MainWindow::openPlotColor()
{
	openPlot(plopqt::PlotKind::Color, tr("Color Plot"));
}

void MainWindow::openPlotContour()
{
	openPlot(plopqt::PlotKind::Contour, tr("Contour Plot"));
}

void MainWindow::openPlotParts()
{
	openPlot(plopqt::PlotKind::Parts, tr("Cell Parts Plot"));
}

void MainWindow::openPlotQuads()
{
	openPlot(plopqt::PlotKind::Quads, tr("Quad Plot"));
}

void MainWindow::openPlotZ88()
{
	openPlot(plopqt::PlotKind::Z88Color, tr("Z88 Color Plot"));
}

void MainWindow::openPartDimensions()
{
	partDimensionWindow_->refresh();
	partDimensionWindow_->show();
	partDimensionWindow_->raise();
	partDimensionWindow_->activateWindow();
}

void MainWindow::updateRunResults(const plopqt::RunResults &results)
{
	resultsView_->setPlainText(
		tr("Visible RMS: %1\nVisible P-V: %2\nRefocus focal length: %3\nZ88 RMS: %4\nZ88 P-V: %5")
			.arg(results.visibleRms, 0, 'g', 10)
			.arg(results.visiblePv, 0, 'g', 10)
			.arg(results.refocusFocalLength, 0, 'g', 10)
			.arg(results.z88VisibleRms, 0, 'g', 10)
			.arg(results.z88VisiblePv, 0, 'g', 10));
	runOutput_->setPlainText(results.outputLog + QLatin1String("\n") + results.warnings + QLatin1String("\n") + results.debugLog);
}

void MainWindow::updateSummaryTabs(const plopqt::SummaryData &summaries)
{
	mirrorSummary_->setPlainText(summaries.mirror);
	supportsSummary_->setPlainText(summaries.supports);
	variablesSummary_->setPlainText(summaries.variables);
	partsSummary_->setPlainText(summaries.parts);
	z88Summary_->setPlainText(summaries.z88);
}

void MainWindow::setCurrentFile(const QString &filePath)
{
	currentFilePath_ = filePath;
	setWindowTitle(tr("PLOP Qt - %1").arg(QDir::toNativeSeparators(filePath)));
	recentFiles_.removeAll(filePath);
	recentFiles_.prepend(filePath);
	while (recentFiles_.size() > kMaxRecentFiles) {
		recentFiles_.removeLast();
	}

	QSettings settings;
	settings.setValue(QStringLiteral("recentFiles"), recentFiles_);
	updateRecentFilesMenu();
}

void MainWindow::updateRecentFilesMenu()
{
	recentFilesMenu_->clear();
	for (const QString &filePath : recentFiles_) {
		QAction *action = recentFilesMenu_->addAction(QDir::toNativeSeparators(filePath));
		connect(action, &QAction::triggered, this, [this, filePath]() { openControlFile(filePath); });
	}
	if (recentFiles_.isEmpty()) {
		recentFilesMenu_->addAction(tr("No recent files"))->setEnabled(false);
	}
}

void MainWindow::openPlot(plopqt::PlotKind kind, const QString &title)
{
	PlotWindow *window = nullptr;
	switch (kind) {
	case plopqt::PlotKind::Mesh:
		window = meshWindow_;
		break;
	case plopqt::PlotKind::Supports:
		window = supportsWindow_;
		break;
	case plopqt::PlotKind::Color:
		window = colorWindow_;
		break;
	case plopqt::PlotKind::Contour:
		window = contourWindow_;
		break;
	case plopqt::PlotKind::Parts:
		window = partsWindow_;
		break;
	case plopqt::PlotKind::Quads:
		window = quadsWindow_;
		break;
	case plopqt::PlotKind::Z88Color:
		window = z88Window_;
		break;
	}

	window->setWindowTitle(title);
	window->setImage(facade_.renderPlot(kind));
	window->show();
	window->raise();
	window->activateWindow();
}

QTextEdit *MainWindow::createReadOnlySummaryTab(const QString &title)
{
	Q_UNUSED(title);
	QTextEdit *view = new QTextEdit(this);
	view->setReadOnly(true);
	return view;
}

void MainWindow::appendStatusMessage(const QString &message)
{
	statusBar()->showMessage(message, 5000);
}
