#ifndef __SUCCESS_H__
#define __SUCCESS_H__

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
		bool isNeedRestart;

	private:
		void setDialogFlags();
		void connectSignals();

	public:
		SuccessDialog(QWidget* parent = nullptr);
		~SuccessDialog();

	public:
		void openDialog(int, bool);
		void closeDialog();

	public:
		bool getIsNeedRestart();
};
#endif