#include "PlotWindow.h"

#include <QFileDialog>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QPixmap>
#include <QScrollArea>

PlotWindow::PlotWindow(const QString &title, QWidget *parent)
	: QMainWindow(parent)
	, imageLabel_(new QLabel(this))
{
	setWindowTitle(title);
	imageLabel_->setAlignment(Qt::AlignCenter);
	QScrollArea *scrollArea = new QScrollArea(this);
	scrollArea->setWidget(imageLabel_);
	scrollArea->setWidgetResizable(true);
	setCentralWidget(scrollArea);

	QAction *saveAction = menuBar()->addAction(tr("Save Image"));
	connect(saveAction, &QAction::triggered, this, &PlotWindow::saveImage);
	resize(900, 900);
}

void PlotWindow::setImage(const QImage &image)
{
	image_ = image;
	imageLabel_->setPixmap(QPixmap::fromImage(image_));
	imageLabel_->adjustSize();
}

void PlotWindow::saveImage()
{
	if (image_.isNull()) {
		QMessageBox::information(this, windowTitle(), tr("No image is available to save."));
		return;
	}

	const QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), QString(), tr("PNG Image (*.png);;BMP Image (*.bmp)"));
	if (fileName.isEmpty()) {
		return;
	}

	image_.save(fileName);
}
