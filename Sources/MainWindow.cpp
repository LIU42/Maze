#include "MainWindow.h"
#include "ui_MainWindow.h"

GameTimers::GameTimers(QWidget* parent)
{
    pFrameTimer = new QTimer(parent);
    pFrameTimer->setInterval(FRAME_INTERVAL);
    pFrameTimer->start();

    pClockTimer = new QTimer(parent);
    pClockTimer->setInterval(CLOCK_INTERVAL);
    pClockTimer->start();
}

GameTimers::~GameTimers()
{
    delete pFrameTimer;
    delete pClockTimer;
}

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    pSuccessDialog = new SuccessDialog(this);
    pMainGame = new MainGame();
    pGameTimers = new GameTimers(this);

    ui->setupUi(this);
    ui->pGraphicsWidget->setMainGame(pMainGame);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pSuccessDialog;
    delete pMainGame;
    delete pGameTimers;
}

void MainWindow::init()
{
    connectTimers();
    connectButtons();
    restartGame();
}

void MainWindow::mainInterval()
{
    if (pMainGame->isInMainLoop())
    {
        updateElapseTime();
        gamePlayerMove();
        gameoverHandler();
    }
    ui->pGraphicsWidget->update();
}

void MainWindow::clockCallBack()
{
    if (pMainGame->isInMainLoop())
    {
        elapseTime += 1;
    }
}

void MainWindow::connectTimers()
{
    connect(pGameTimers->pFrameTimer, &QTimer::timeout, this, &MainWindow::mainInterval);
    connect(pGameTimers->pClockTimer, &QTimer::timeout, this, &MainWindow::clockCallBack);
}

void MainWindow::connectButtons()
{
    connect(ui->pRestartButton, &QPushButton::clicked, this, &MainWindow::restartGame);
    connect(ui->pFindButton, &QPushButton::clicked, this, &MainWindow::gameFindWay);
}

void MainWindow::restartGame()
{
    pMainGame->restart();
    ui->pGraphicsWidget->clearWayBlockList();

    for (int index = 0; index < MazeBlockUnit::DIRECT_COUNT; index++)
    {
        isKeyPress[index] = false;
    }
    elapseTime = 0;
}

void MainWindow::updateElapseTime()
{
    ui->pTimeLabel->setText(QString("TIME: %1").arg(elapseTime));
}

void MainWindow::gameFindWay()
{
    ui->pGraphicsWidget->updateWayBlockList();
}

void MainWindow::gamePlayerMove()
{
    pMainGame->setKeyStatus(isKeyPress);
    pMainGame->playerMove();
}

void MainWindow::gameoverHandler()
{
    if (pMainGame->isGameover())
    {
        pSuccessDialog->setDialogInfo(elapseTime, pMainGame->getIsHaveTracked());
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
        case Qt::Key_W: isKeyPress[(int)Direct::DIRECT_UP] = true; break;
        case Qt::Key_S: isKeyPress[(int)Direct::DIRECT_DOWN] = true; break;
        case Qt::Key_A: isKeyPress[(int)Direct::DIRECT_LEFT] = true; break;
        case Qt::Key_D: isKeyPress[(int)Direct::DIRECT_RIGHT] = true; break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* pKeyEvent)
{
    switch (pKeyEvent->key())
    {
        case Qt::Key_W: isKeyPress[(int)Direct::DIRECT_UP] = false; break;
        case Qt::Key_S: isKeyPress[(int)Direct::DIRECT_DOWN] = false; break;
        case Qt::Key_A: isKeyPress[(int)Direct::DIRECT_LEFT] = false; break;
        case Qt::Key_D: isKeyPress[(int)Direct::DIRECT_RIGHT] = false; break;
    }
}