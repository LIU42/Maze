#ifndef __VIEWS_MAINWINDOW_H__
#define __VIEWS_MAINWINDOW_H__

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>

#include "Engines/MainGame.h"

#include "Views/Dialogs/Success.h"

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
        static constexpr int CLOCK_INTERVAL = 1000;
        static constexpr int FRAME_INTERVAL = 16;

    private:
        Ui::MainWindow* ui;

    private:
        QTimer* pFrameTimer;
        QTimer* pClockTimer;

    private:
        MainGame* pMainGame;
        SuccessDialog* pSuccessDialog;

    private:
        bool keyPress[MapUnit::DIRECT_COUNT];
        int elapseTime;

    private:
        void connectTimers();
        void connectButtons();

    private:
        void mainInterval();
        void clockCallBack();
        void updateElapseTime();

    private:
        void findWay();
        void playerMove();
        void gameover();
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
