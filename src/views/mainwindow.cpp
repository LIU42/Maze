#include "views/mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ResourceManager::load();

    pFrameTimer = new QTimer(parent);
    pFrameTimer->setInterval(FRAME_INTERVAL);
    pFrameTimer->start();

    pClockTimer = new QTimer(parent);
    pClockTimer->setInterval(CLOCK_INTERVAL);
    pClockTimer->start();

    pGameController = new GameController(keyPress);
    pSuccessDialog = new SuccessDialog(this);

    ui->setupUi(this);
    ui->pSceneWidget->setGameController(pGameController);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pGameController;
    delete pSuccessDialog;
    delete pFrameTimer;
    delete pClockTimer;

    ResourceManager::release();
}

void MainWindow::init()
{
    connectTimers();
    connectButtons();
    restart();
}

void MainWindow::mainInterval()
{
    if (pGameController->isInMainLoop())
    {
        updateElapseTime();
        playerMove();
        gameover();
    }
    ui->pSceneWidget->update();
}

void MainWindow::clockCallBack()
{
    if (pGameController->isInMainLoop())
    {
        elapseTime += 1;
    }
}

void MainWindow::connectTimers()
{
    connect(pFrameTimer, &QTimer::timeout, this, &MainWindow::mainInterval);
    connect(pClockTimer, &QTimer::timeout, this, &MainWindow::clockCallBack);
}

void MainWindow::connectButtons()
{
    connect(ui->pRestartButton, &QPushButton::clicked, this, &MainWindow::restart);
    connect(ui->pFindWayButton, &QPushButton::clicked, this, &MainWindow::findWay);
}

void MainWindow::restart()
{
    pGameController->restart();
    ui->pSceneWidget->clearWay();

    for (int index = 0; index < MapUnit::DIRECT_COUNT; index++)
    {
        keyPress[index] = false;
    }
    elapseTime = 0;
}

void MainWindow::updateElapseTime()
{
    ui->pTimeLabel->setText(QString("TIME: %1").arg(elapseTime));
}

void MainWindow::findWay()
{
    ui->pSceneWidget->updateWay();
}

void MainWindow::playerMove()
{
    pGameController->playerMove();
}

void MainWindow::gameover()
{
    if (pGameController->isGameover())
    {
        pSuccessDialog->setInfo(elapseTime, pGameController->hasTracked());
        pSuccessDialog->show();

        if (pSuccessDialog->isNeedRestart())
        {
            restart();
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent* pKeyEvent)
{
    switch (pKeyEvent->key())
    {
        case Qt::Key_W: keyPress[(int)Direct::UP] = true; break;
        case Qt::Key_S: keyPress[(int)Direct::DOWN] = true; break;
        case Qt::Key_A: keyPress[(int)Direct::LEFT] = true; break;
        case Qt::Key_D: keyPress[(int)Direct::RIGHT] = true; break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* pKeyEvent)
{
    switch (pKeyEvent->key())
    {
        case Qt::Key_W: keyPress[(int)Direct::UP] = false; break;
        case Qt::Key_S: keyPress[(int)Direct::DOWN] = false; break;
        case Qt::Key_A: keyPress[(int)Direct::LEFT] = false; break;
        case Qt::Key_D: keyPress[(int)Direct::RIGHT] = false; break;
    }
}
