#pragma once

#include <QDialog>

class QComboBox;
class QLabel;
class QPushButton;

namespace plopqt {
class PlopCoreFacade;
}

class PartDimensionWindow : public QDialog
{
	Q_OBJECT

public:
	explicit PartDimensionWindow(plopqt::PlopCoreFacade *facade, QWidget *parent = nullptr);

	void refresh();

private slots:
	void updateView();
	void rotateCurrentPart();

private:
	plopqt::PlopCoreFacade *facade_;
	QComboBox *partSelector_;
	QComboBox *unitsSelector_;
	QLabel *imageLabel_;
	QLabel *detailsLabel_;
	QPushButton *rotateButton_;
};
