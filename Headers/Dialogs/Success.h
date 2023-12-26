#ifndef __DIALOGS_SUCCESS_H__
#define __DIALOGS_SUCCESS_H__

#include <QDialog>

QT_BEGIN_NAMESPACE

namespace Ui
{
    class SuccessDialog;
}

QT_END_NAMESPACE

class SuccessDialog : public QDialog
{
    Q_OBJECT

    private:
        Ui::SuccessDialog *ui;

    private:
        bool isNeedRestart;

    private:
        void setDialogFlags();
        void connectButtons();

    public:
        SuccessDialog(QWidget* parent = nullptr);
        ~SuccessDialog();

    public:
        void setDialogInfo(int elapseTime, bool isHaveTracked);
        void showDialog();
        void closeDialog();

    public:
        bool getIsNeedRestart();
};
#endif