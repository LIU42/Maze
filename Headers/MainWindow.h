#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QApplication>
#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>

#include "Dialogs/Success.h"
#include "Games/MainGame.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class GameTimers
{  
    private:
        static constexpr int CLOCK_INTERVAL = 1000;
        static constexpr int FRAME_INTERVAL = 16;

    public:
        QTimer* pFrameTimer;
        QTimer* pClockTimer;

    public:
        GameTimers(QWidget* parent = nullptr);
        ~GameTimers();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::MainWindow* ui;

    private:
        SuccessDialog* pSuccessDialog;
        MainGame* pMainGame;
        GameTimers* pGameTimers;

    private:
        bool isKeyPress[MazeBlockUnit::DIRECT_COUNT];
        int elapseTime;

    private:
        void connectTimers();
        void connectButtons();

    private:
        void mainInterval();
        void clockCallBack();
        void updateElapseTime();
        void gameFindWay();
        void gamePlayerMove();
        void gameoverHandler();
        void restartGame();

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