#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pSuccessDialog = new SuccessDialog(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pSuccessDialog;
}

void MainWindow::setGame(MainGame* pGame)
{
    this->pGame = pGame;
    ui->pGraphics->setGame(pGame);
}

void MainWindow::initialize()
{
    setDarkMode();
    setInterval();
    connectTimers();
    connectButtons();
    startTimers();
    restartGame();
}

void MainWindow::setDarkMode()
{
    DwmSetWindowAttribute((HWND)this->winId(), DARK_MODE_CODE, &DARK_MODE_FLAG, sizeof(DARK_MODE_FLAG));
    DwmSetWindowAttribute((HWND)pSuccessDialog->winId(), DARK_MODE_CODE, &DARK_MODE_FLAG, sizeof(DARK_MODE_FLAG));
}

void MainWindow::mainInterval()
{
    if (pGame->isInMainLoop())
    {
        updateElapseTime();
        gamePlayerMove();
        gameover();
    }
    ui->pGraphics->update();
}

void MainWindow::clockCallBack()
{
    if (pGame->isInMainLoop())
    {
        elapseTime += 1;
    }
}

void MainWindow::setInterval()
{
    timers.interval.setInterval(1000 / GameTimers::GAME_FPS);
    timers.clock.setInterval(GameTimers::CLOCK_INTERVAL);
}

void MainWindow::connectTimers()
{
    connect(&timers.interval, &QTimer::timeout, this, &MainWindow::mainInterval);
    connect(&timers.clock, &QTimer::timeout, this, &MainWindow::clockCallBack);
}

void MainWindow::connectButtons()
{
    connect(ui->pRestartButton, &QPushButton::clicked, this, &MainWindow::restartGame);
    connect(ui->pFindButton, &QPushButton::clicked, this, &MainWindow::gameFindWay);
}

void MainWindow::startTimers()
{
    timers.interval.start();
    timers.clock.start();
}

void MainWindow::restartGame()
{
    pGame->restart();
    ui->pGraphics->clearWayData();

    for (int direct = DIRECT_UP; direct <= DIRECT_RIGHT; direct++)
    {
        isKeyPress[direct] = false;
    }
    elapseTime = 0;
}

void MainWindow::updateElapseTime()
{
    ui->pTimeLabel->setText(QString("TIME: %1").arg(elapseTime));
}

void MainWindow::gameFindWay()
{
    ui->pGraphics->updateWayData();
}

void MainWindow::gamePlayerMove()
{
    pGame->setKeyStatus(isKeyPress);
    pGame->playerMove();
}

void MainWindow::gameover()
{
    if (pGame->isGameover())
    {
        pSuccessDialog->setDialogInfo(elapseTime, pGame->getIsHaveTracked());
        pSuccessDialog->showDialog();

        if (pSuccessDialog->getIsNeedRestart())
        {
            restartGame();
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent* pKeyEvent)
{
    switch (pKeyEvent->key())
    {
        case Qt::Key_W: isKeyPress[DIRECT_UP] = true; break;
        case Qt::Key_S: isKeyPress[DIRECT_DOWN] = true; break;
        case Qt::Key_A: isKeyPress[DIRECT_LEFT] = true; break;
        case Qt::Key_D: isKeyPress[DIRECT_RIGHT] = true; break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* pKeyEvent)
{
    switch (pKeyEvent->key())
    {
        case Qt::Key_W: isKeyPress[DIRECT_UP] = false; break;
        case Qt::Key_S: isKeyPress[DIRECT_DOWN] = false; break;
        case Qt::Key_A: isKeyPress[DIRECT_LEFT] = false; break;
        case Qt::Key_D: isKeyPress[DIRECT_RIGHT] = false; break;
    }
}