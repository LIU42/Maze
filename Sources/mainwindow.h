#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>

#include <dwmapi.h>
#include <time.h>

#include "maze.h"
#include "success.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class GameTimers
{
    friend class MainWindow;

    private:
        static const int CLOCK_INTERVAL = 1000;
        static const int GAME_FPS = 60;

    private:
        QTimer interval;
        QTimer clock;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        static const int DARK_MODE_FLAG = 1;
		static const int DARK_MODE_CODE = 20;

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
		void setDarkMode();
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
		void keyPressEvent(QKeyEvent*);
		void keyReleaseEvent(QKeyEvent*);

    public:
        MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

	public:
        void setGame(MainGame*);
		void init();
};
#endif