#include "PartDimensionWindow.h"

#include "PlopCoreFacade.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>

PartDimensionWindow::PartDimensionWindow(plopqt::PlopCoreFacade *facade, QWidget *parent)
	: QDialog(parent)
	, facade_(facade)
	, partSelector_(new QComboBox(this))
	, unitsSelector_(new QComboBox(this))
	, imageLabel_(new QLabel(this))
	, detailsLabel_(new QLabel(this))
	, rotateButton_(new QPushButton(tr("Rotate"), this))
{
	setWindowTitle(tr("Part Dimensions"));
	unitsSelector_->addItem(tr("Millimeters"));
	unitsSelector_->addItem(tr("Inches"));
	imageLabel_->setMinimumSize(700, 700);
	imageLabel_->setAlignment(Qt::AlignCenter);
	detailsLabel_->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	detailsLabel_->setTextInteractionFlags(Qt::TextSelectableByMouse);

	QHBoxLayout *controls = new QHBoxLayout;
	controls->addWidget(new QLabel(tr("Part:"), this));
	controls->addWidget(partSelector_);
	controls->addWidget(new QLabel(tr("Units:"), this));
	controls->addWidget(unitsSelector_);
	controls->addWidget(rotateButton_);
	controls->addStretch(1);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addLayout(controls);
	layout->addWidget(imageLabel_, 1);
	layout->addWidget(detailsLabel_);

	connect(partSelector_, qOverload<int>(&QComboBox::currentIndexChanged), this, &PartDimensionWindow::updateView);
	connect(unitsSelector_, qOverload<int>(&QComboBox::currentIndexChanged), this, &PartDimensionWindow::updateView);
	connect(rotateButton_, &QPushButton::clicked, this, &PartDimensionWindow::rotateCurrentPart);
}

void PartDimensionWindow::refresh()
{
	partSelector_->blockSignals(true);
	partSelector_->clear();
	const int count = facade_->partCount();
	for (int i = 0; i < count; ++i) {
		partSelector_->addItem(tr("Part %1").arg(i + 1), i);
	}
	partSelector_->blockSignals(false);
	updateView();
}

void PartDimensionWindow::updateView()
{
	if (partSelector_->count() == 0) {
		imageLabel_->clear();
		detailsLabel_->setText(tr("No part data is available."));
		return;
	}

	const int partIndex = partSelector_->currentData().toInt();
	const bool inches = unitsSelector_->currentIndex() == 1;
	imageLabel_->setPixmap(QPixmap::fromImage(facade_->renderPartDimension(partIndex, inches)));
	detailsLabel_->setText(facade_->partDetails(partIndex, inches));
}

void PartDimensionWindow::rotateCurrentPart()
{
	if (partSelector_->count() == 0) {
		return;
	}

	facade_->rotatePart(partSelector_->currentData().toInt());
	updateView();
}
