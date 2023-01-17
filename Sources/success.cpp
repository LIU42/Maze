#include "success.h"
#include "ui_success.h"

SuccessDialog::SuccessDialog(QWidget *parent): QDialog(parent), ui(new Ui::SuccessDialog)
{
	ui->setupUi(this);
	setWindowFlag(Qt::WindowContextHelpButtonHint, false);
	connect(ui->restartButton, &QPushButton::clicked, this, &SuccessDialog::closeDialog);
}

SuccessDialog::~SuccessDialog()
{
	delete ui;
}

void SuccessDialog::openDialog(int timeDuring, bool isHaveTracked)
{
	QString timeInfo = QString("TIME: %1s").arg(timeDuring);

	if (isHaveTracked)
	{
		timeInfo.append(" (Tracked)");
	}
	ui->timeLabel->setText(timeInfo);
	isNeedRestart = false;
	this->exec();
}

void SuccessDialog::closeDialog()
{
	isNeedRestart = true;
	this->close();
}

bool SuccessDialog::getIsNeedRestart()
{
	return isNeedRestart;
}