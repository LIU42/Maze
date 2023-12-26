#include "Dialogs/Success.h"
#include "ui_Success.h"

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
    ui->pTimeLabel->setText(QString("TIME: %1s %2").arg(elapseTime).arg((isHaveTracked) ? "(Tracked)" : ""));
}

void SuccessDialog::showDialog()
{
    isNeedRestart = false;
    exec();
}

void SuccessDialog::closeDialog()
{
    isNeedRestart = true;
    close();
}

bool SuccessDialog::getIsNeedRestart()
{
    return isNeedRestart;
}