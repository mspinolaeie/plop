#pragma once

#include <QMainWindow>

class QLabel;

class PlotWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit PlotWindow(const QString &title, QWidget *parent = nullptr);

	void setImage(const QImage &image);

private slots:
	void saveImage();

private:
	QLabel *imageLabel_;
	QImage image_;
};
