#include "success.h"
#include "ui_success.h"

SuccessDialog::SuccessDialog(QWidget *parent): QDialog(parent), ui(new Ui::SuccessDialog)
{
    ui->setupUi(this);
    setDialogFlags();
    connectButtons();
}

SuccessDialog::~SuccessDialog()
{
    delete ui;
}

void SuccessDialog::setDialogFlags()
{
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}

void SuccessDialog::connectButtons()
{
    connect(ui->pRestartButton, &QPushButton::clicked, this, &SuccessDialog::closeDialog);
}

void SuccessDialog::setDialogInfo(int elapseTime, bool isHaveTracked)
{
    QString timeInfo = QString("TIME: %1s").arg(elapseTime);

    if (isHaveTracked)
    {
        timeInfo.append(" (Tracked)");
    }
    ui->pTimeLabel->setText(timeInfo);
}

void SuccessDialog::showDialog()
{
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