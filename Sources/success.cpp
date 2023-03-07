#include "success.h"
#include "ui_success.h"

SuccessDialog::SuccessDialog(QWidget *parent): QDialog(parent), ui(new Ui::SuccessDialog)
{
	ui->setupUi(this);
	setDialogFlags();
	connectSignals();
}

SuccessDialog::~SuccessDialog()
{
	delete ui;
}

void SuccessDialog::setDialogFlags()
{
	setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}

void SuccessDialog::connectSignals()
{
	connect(ui->restartButton, &QPushButton::clicked, this, &SuccessDialog::closeDialog);
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
	QDialog::exec();
}

void SuccessDialog::closeDialog()
{
	isNeedRestart = true;
	QDialog::close();
}

bool SuccessDialog::getIsNeedRestart()
{
	return isNeedRestart;
}