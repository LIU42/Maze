#include "maze.h"
#include "ui_maze.h"

MainGame::MainGame(QWidget* parent): QMainWindow(parent), ui(new Ui::MainGame)
{
    ui->setupUi(this);
	pSuccess = new SuccessDialog(this);
}

MainGame::~MainGame()
{
    delete ui;
	delete pSuccess;
}

void MainGame::init()
{
	srand((unsigned)time(NULL));
	setDarkMode();
	setInterval();
	loadImage();
	connectTimer();
	connectButton();
	startTimer();
	restart();
}

void MainGame::setDarkMode()
{
	DwmSetWindowAttribute((HWND)this->winId(), DARK_MODE_CODE, &IS_DARK_MODE, sizeof(IS_DARK_MODE));
	DwmSetWindowAttribute((HWND)pSuccess->winId(), DARK_MODE_CODE, &IS_DARK_MODE, sizeof(IS_DARK_MODE));
}

void MainGame::loadImage()
{
	images.background.load(":/Images/background.png");
	images.way.load(":/Images/way.png");
	images.finish.load(":/Images/finish.png");
	images.player.load(":/Images/player.png");

	for (int direct = UP; direct <= RIGHT; direct++)
	{
		images.wall[direct].load(QString(":/Images/wall_%1.png").arg(direct));
	}
}

void MainGame::mainInterval()
{
	if (status == PLAYING)
	{
		playerMove();
		gameover();
	}
	QWidget::update();
}

void MainGame::clockCallBack()
{
	if (status == PLAYING) { timeDuring += 1; }
}

void MainGame::setInterval()
{
	timers.interval.setInterval(1000 / GAME_FPS);
	timers.clock.setInterval(CLOCK_INTERVAL);
}

void MainGame::connectTimer()
{
	connect(&timers.interval, &QTimer::timeout, this, &MainGame::mainInterval);
	connect(&timers.clock, &QTimer::timeout, this, &MainGame::clockCallBack);
}

void MainGame::connectButton()
{
	connect(ui->restartButton, &QPushButton::clicked, this, &MainGame::restart);
	connect(ui->findButton, &QPushButton::clicked, this, &MainGame::getWayData);
}

void MainGame::startTimer()
{
	timers.interval.start();
	timers.clock.start();
}

void MainGame::resetKeyStatus()
{
	for (int key = UP; key <= RIGHT; key++)
	{
		isKeyPress[key] = false;
	}
}

void MainGame::restart()
{
	map.init();
	map.generate();
	player.init(BORDER, BORDER + MENU_HEIGHT, &map);
	wayData.clear();
	resetKeyStatus();
	status = PLAYING;
	timeDuring = 0;
	isHaveTracked = false;
}

void MainGame::getWayData()
{
	if (status == PLAYING)
	{
		int playerX = qRound(player.getRelativeX());
		int playerY = qRound(player.getRelativeY());

		wayData = map.getWayData(playerX, playerY);
		wayDataIndex = wayData.length() - 1;
		isHaveTracked = true;
	}
}

void MainGame::playerMove()
{
	player.setIsOnMove(false);

	for (int direct = UP; direct <= RIGHT; direct++)
	{
		if (isKeyPress[direct])
		{
			player.setIsOnMove(true);
			player.setDirect((Direct)direct);
		}
	}
	player.move();
}

void MainGame::gameover()
{
	double playerX = player.getRelativeX();
	double playerY = player.getRelativeY();

	if (playerX == Map::ROWS - 1 && playerY == Map::COLS - 1)
	{
		status = OVER;
		pSuccess->openDialog(timeDuring, isHaveTracked);

		if (pSuccess->getIsNeedRestart())
		{
			restart();
		}
	}
}

void MainGame::keyPressEvent(QKeyEvent* event)
{
	switch (event->key())
	{
		case Qt::Key_W: isKeyPress[UP] = true; break;
		case Qt::Key_S: isKeyPress[DOWN] = true; break;
		case Qt::Key_A: isKeyPress[LEFT] = true; break;
		case Qt::Key_D: isKeyPress[RIGHT] = true; break;
	}
}

void MainGame::keyReleaseEvent(QKeyEvent* event)
{
	switch (event->key())
	{
		case Qt::Key_W: isKeyPress[UP] = false; break;
		case Qt::Key_S: isKeyPress[DOWN] = false; break;
		case Qt::Key_A: isKeyPress[LEFT] = false; break;
		case Qt::Key_D: isKeyPress[RIGHT] = false; break;
	}
}

void MainGame::displayBackground(QPainter& painter)
{
	painter.drawPixmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, images.background);
}

void MainGame::displayMap(QPainter& painter)
{
	static QRect wallRect;

	for (int x = 0; x < Map::ROWS; x++)
	{
		for (int y = 0; y < Map::COLS; y++)
		{
			for (int direct = UP; direct <= RIGHT; direct++)
			{
				if (map.isHaveWall(x, y, (Direct)direct))
				{
					wallRect.setX(Map::UNIT_SIZE * x + BORDER - WALL_WIDTH);
					wallRect.setY(Map::UNIT_SIZE * y + BORDER + MENU_HEIGHT - WALL_WIDTH);
					wallRect.setWidth(Map::UNIT_SIZE + WALL_WIDTH * 2);
					wallRect.setHeight(Map::UNIT_SIZE + WALL_WIDTH * 2);

					painter.drawPixmap(wallRect, images.wall[direct]);
				}
			}
		}
	}
	int x = Map::UNIT_SIZE * (Map::ROWS - 1) + BORDER;
	int y = Map::UNIT_SIZE * (Map::COLS - 1) + BORDER + MENU_HEIGHT;

	painter.drawPixmap(x, y, Map::UNIT_SIZE, Map::UNIT_SIZE, images.finish);
}

void MainGame::displayWay(QPainter& painter)
{
	if (!wayData.isEmpty())
	{
		for (int i = wayData.length() - 1; i >= wayDataIndex; i--)
		{
			int x = wayData[i].x() * Map::UNIT_SIZE + BORDER;
			int y = wayData[i].y() * Map::UNIT_SIZE + BORDER + MENU_HEIGHT;

			painter.drawPixmap(x, y, Map::UNIT_SIZE, Map::UNIT_SIZE, images.way);
		}
		if (wayDataIndex > 0) { wayDataIndex -= 1; }
	}
}

void MainGame::displayPlayer(QPainter& painter)
{
	painter.drawPixmap(player.x(), player.y(), Map::UNIT_SIZE, Map::UNIT_SIZE, images.player);
}

void MainGame::displayInfo()
{
	ui->timeLabel->setText(QString("TIME: %1").arg(timeDuring));
}

void MainGame::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	displayBackground(painter);
	displayWay(painter);
	displayMap(painter);
	displayPlayer(painter);
	displayInfo();
}