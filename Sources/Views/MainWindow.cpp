#include "Views/MainWindow.h"

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ResourceManager::load();

    pFrameTimer = new QTimer(parent);
    pFrameTimer->setInterval(FRAME_INTERVAL);
    pFrameTimer->start();

    pClockTimer = new QTimer(parent);
    pClockTimer->setInterval(CLOCK_INTERVAL);
    pClockTimer->start();

    pMainGame = new MainGame(keyPress);
    pSuccessDialog = new SuccessDialog(this);

    ui->setupUi(this);
    ui->pSceneWidget->setMainGame(pMainGame);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pSuccessDialog;
    delete pMainGame;
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
    if (pMainGame->isInMainLoop())
    {
        updateElapseTime();
        playerMove();
        gameover();
    }
    ui->pSceneWidget->update();
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
    connect(pFrameTimer, &QTimer::timeout, this, &MainWindow::mainInterval);
    connect(pClockTimer, &QTimer::timeout, this, &MainWindow::clockCallBack);
}

void MainWindow::connectButtons()
{
    connect(ui->pRestartButton, &QPushButton::clicked, this, &MainWindow::restart);
    connect(ui->pFindButton, &QPushButton::clicked, this, &MainWindow::findWay);
}

void MainWindow::restart()
{
    pMainGame->restart();
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
    pMainGame->playerMove();
}

void MainWindow::gameover()
{
    if (pMainGame->isGameover())
    {
        pSuccessDialog->setInfo(elapseTime, pMainGame->hasTracked());
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
        case Qt::Key_W: keyPress[(int)Direct::DIRECT_UP] = true; break;
        case Qt::Key_S: keyPress[(int)Direct::DIRECT_DOWN] = true; break;
        case Qt::Key_A: keyPress[(int)Direct::DIRECT_LEFT] = true; break;
        case Qt::Key_D: keyPress[(int)Direct::DIRECT_RIGHT] = true; break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* pKeyEvent)
{
    switch (pKeyEvent->key())
    {
        case Qt::Key_W: keyPress[(int)Direct::DIRECT_UP] = false; break;
        case Qt::Key_S: keyPress[(int)Direct::DIRECT_DOWN] = false; break;
        case Qt::Key_A: keyPress[(int)Direct::DIRECT_LEFT] = false; break;
        case Qt::Key_D: keyPress[(int)Direct::DIRECT_RIGHT] = false; break;
    }
}
