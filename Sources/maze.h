#ifndef __MAZE_H__
#define __MAZE_H__

#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>

#include <dwmapi.h>
#include <time.h>

#include "map.h"
#include "player.h"
#include "success.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainGame;
}

QT_END_NAMESPACE

enum Status { PLAYING, OVER };

struct Image
{
	QPixmap background;
	QPixmap way;
	QPixmap finish;
	QPixmap player;
	QPixmap wall[4];
};

struct Timer
{
	QTimer interval;
	QTimer clock;
};

class MainGame : public QMainWindow
{
    Q_OBJECT

	private:
		static const int SCREEN_WIDTH = 940;
		static const int SCREEN_HEIGHT = 700;
		static const int GAME_FPS = 60;
		static const int CLOCK_INTERVAL = 1000;

	private:
		static const int IS_DARK_MODE = 1;
		static const int DARK_MODE_CODE = 20;

	private:
		static const int MENU_HEIGHT = 60;
		static const int BORDER = 20;
		static const int WALL_WIDTH = 3;

    private:
        Ui::MainGame* ui;
		SuccessDialog* success;

	private:
		Image image;
		Timer timer;

	private:
		Map map;
		Player player;

	private:
		Status status;
		WayData wayData;
		bool isKeyPress[4];
		bool isHaveTracked;
		int timeDuring;
		int wayDataIndex;

	private:
		void setDarkMode();
		void setInterval();
		void loadImage();
		void connectTimer();
		void connectButton();
		void startTimer();
		void resetKeyStatus();

	private:
		void mainInterval();
		void clockCallBack();
		void restart();
		void getWayData();
		void playerMove();
		void gameover();

	private:
		void displayBackground(QPainter&);
		void displayMap(QPainter&);
		void displayWay(QPainter&);
		void displayPlayer(QPainter&);
		void displayInfo();

	private:
		void keyPressEvent(QKeyEvent*);
		void keyReleaseEvent(QKeyEvent*);
		void paintEvent(QPaintEvent*);

    public:
        MainGame(QWidget* parent = nullptr);
        ~MainGame();

	public:
		void init();
};
#endif