#include "views/dialogs/success.h"

#include "ui_success.h"

SuccessDialog::SuccessDialog(QWidget* parent): QDialog(parent), ui(new Ui::SuccessDialog)
{
    ui->setupUi(this);
    connect(ui->pRestartButton, &QPushButton::clicked, this, &SuccessDialog::close);
}

SuccessDialog::~SuccessDialog()
{
    delete ui;
}

void SuccessDialog::setInfo(int elapseTime, bool tracked)
{
    ui->pTimeLabel->setText(QString("TIME: %1s %2").arg(elapseTime).arg((tracked) ? "(Tracked)" : ""));
}

void SuccessDialog::show()
{
    needRestart = false;
    QDialog::exec();
}

void SuccessDialog::close()
{
    needRestart = true;
    QDialog::close();
}

bool SuccessDialog::isNeedRestart()
{
    return needRestart;
}
