#pragma once

#include <QMainWindow>

#include "PlopCoreFacade.h"

class QAction;
class QCheckBox;
class QComboBox;
class QMenu;
class QPlainTextEdit;
class QProgressBar;
class QSpinBox;
class QTabWidget;
class QTextEdit;

class PartDimensionWindow;
class PlotWindow;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

	void openControlFile(const QString &filePath);

private slots:
	void newControlFile();
	void openControlFile();
	void saveControlFile();
	void saveControlFileAs();
	void chooseAutoCellTemplate();
	void runPlop();
	void runZ88();
	void openManual();
	void showAbout();
	void showWhatsNew();
	void showGraphOptions();
	void refreshSummaries();
	void openPlotMesh();
	void openPlotSupports();
	void openPlotColor();
	void openPlotContour();
	void openPlotParts();
	void openPlotQuads();
	void openPlotZ88();
	void openPartDimensions();

private:
	plopqt::RunSettings gatherRunSettings() const;
	void updateRunResults(const plopqt::RunResults &results);
	void updateSummaryTabs(const plopqt::SummaryData &summaries);
	void setCurrentFile(const QString &filePath);
	void updateRecentFilesMenu();
	void openPlot(plopqt::PlotKind kind, const QString &title);
	QTextEdit *createReadOnlySummaryTab(const QString &title);
	void appendStatusMessage(const QString &message);

	plopqt::PlopCoreFacade facade_;
	QString currentFilePath_;
	QStringList recentFiles_;

	QPlainTextEdit *controlEditor_;
	QTextEdit *runOutput_;
	QTextEdit *mirrorSummary_;
	QTextEdit *supportsSummary_;
	QTextEdit *variablesSummary_;
	QTextEdit *partsSummary_;
	QTextEdit *z88Summary_;
	QProgressBar *runProgress_;
	QCheckBox *usePvCheckBox_;
	QCheckBox *refocusCheckBox_;
	QCheckBox *refocusXyrCheckBox_;
	QCheckBox *useBasisCheckBox_;
	QCheckBox *generateZ88CheckBox_;
	QCheckBox *traceOptCheckBox_;
	QCheckBox *zernikeCheckBox_;
	QSpinBox *zernikeOrderSpin_;
	QSpinBox *monteTestsSpin_;
	QTextEdit *resultsView_;

	QMenu *recentFilesMenu_;
	PlotWindow *meshWindow_;
	PlotWindow *supportsWindow_;
	PlotWindow *colorWindow_;
	PlotWindow *contourWindow_;
	PlotWindow *partsWindow_;
	PlotWindow *quadsWindow_;
	PlotWindow *z88Window_;
	PartDimensionWindow *partDimensionWindow_;
};
