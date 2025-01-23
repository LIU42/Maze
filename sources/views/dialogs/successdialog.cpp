#include "views/dialogs/successdialog.h"

#include "ui_successdialog.h"

SuccessDialog::SuccessDialog(QWidget* parent): QDialog(parent), ui(new Ui::SuccessDialog)
{
    ui->setupUi(this);
}

SuccessDialog::~SuccessDialog()
{
    delete ui;
}

void SuccessDialog::setInfo(int elapseTime, bool tracked)
{
    ui->timeValueLabel->setNum(elapseTime);

    if (tracked)
    {
        ui->trackedLabel->show();
    }
    else
    {
        ui->trackedLabel->hide();
    }
}
