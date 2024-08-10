#ifndef __VIEWS_MAINWINDOW_H__
#define __VIEWS_MAINWINDOW_H__

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>

#include "commons/resources.h"
#include "cores/controller.h"
#include "views/dialogs/successdialog.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::MainWindow* ui;

    private:
        QTimer* pFrameTimer;
        QTimer* pClockTimer;

    private:
        GameController* pGameController;
        GameResources* pGameResources;

    private:
        SuccessDialog* pSuccessDialog;

    private:
        bool keyInputs[DirectIndex::COUNT];
        int elapseTime;

    private:
        void restart();

    private:
        void keyPressEvent(QKeyEvent* pKeyEvent) override;
        void keyReleaseEvent(QKeyEvent* pKeyEvent) override;

    public:
        MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

    public:
        void init();
};
#endif
