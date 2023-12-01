#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QApplication>
#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>

#include "Dialogs/Success.h"
#include "Models/Maze.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class GameTimers
{
    public:
        static const int CLOCK_INTERVAL = 1000;
        static const int GAME_FPS = 60;

    public:
        QTimer interval;
        QTimer clock;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::MainWindow* ui;
        MainGame* pGame;
        SuccessDialog* pSuccessDialog;

    private:
        GameTimers timers;

    private:
        bool isKeyPress[MazeBlockUnit::DIRECT_COUNT];
        int elapseTime;

    private:
        void setInterval();
        void connectTimers();
        void connectButtons();
        void startTimers();

    private:
        void mainInterval();
        void clockCallBack();
        void updateElapseTime();
        void gameFindWay();
        void gamePlayerMove();
        void gameover();
        void restartGame();

    private:
        void keyPressEvent(QKeyEvent* pKeyEvent);
        void keyReleaseEvent(QKeyEvent* pKeyEvent);

    public:
        MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

    public:
        void setGame(MainGame* pGame);
        void initialize();
};
#endif