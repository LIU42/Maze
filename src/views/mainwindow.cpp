#include "views/mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    pFrameTimer = new QTimer(parent);
    pFrameTimer->setInterval(Interval::FRAME);
    pFrameTimer->start();

    pClockTimer = new QTimer(parent);
    pClockTimer->setInterval(Interval::CLOCK);
    pClockTimer->start();

    pGameEnvironment = new GameEnvironment(keyInputs);
    pGameResources = new GameResources();
    pSuccessDialog = new SuccessDialog(this);

    ui->setupUi(this);
    ui->pSceneWidget->setGameEnvironment(pGameEnvironment);
    ui->pSceneWidget->setGameResources(pGameResources);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pSuccessDialog;
    delete pFrameTimer;
    delete pClockTimer;
    delete pGameEnvironment;
    delete pGameResources;
}

void MainWindow::init()
{
    connect(pFrameTimer, &QTimer::timeout, this, [=]
    {
        if (pGameEnvironment->isPlaying())
        {
            pGameEnvironment->playerMove();

            if (pGameEnvironment->isGameover())
            {
                pSuccessDialog->setInfo(elapseTime, pGameEnvironment->hasTracked());
                pSuccessDialog->show();

                if (pSuccessDialog->isNeedRestart())
                {
                    restart();
                }
            }
            ui->pTimeLabel->setText(QString("TIME: %1").arg(elapseTime));
        }
        ui->pSceneWidget->update();
    });

    connect(pClockTimer, &QTimer::timeout, this, [=]
    {
        if (pGameEnvironment->isPlaying())
        {
            elapseTime += 1;
        }
    });

    connect(ui->pRestartButton, &QPushButton::clicked, this, [=]
    {
        restart();
    });

    connect(ui->pFogButton, &QPushButton::clicked, this, [=]
    {
        pGameEnvironment->switchFogMode();
    });

    connect(ui->pTrackButton, &QPushButton::clicked, this, [=]
    {
        ui->pSceneWidget->updateWayBlocks();
    });
    restart();
}

void MainWindow::restart()
{  
    pGameEnvironment->restart();
    elapseTime = 0;

    for (int index = 0; index < DirectIndex::COUNT; index++)
    {
        keyInputs[index] = false;
    }
    ui->pSceneWidget->clearWayBlocks();
}

void MainWindow::keyPressEvent(QKeyEvent* pKeyEvent)
{
    switch (pKeyEvent->key())
    {
        case Qt::Key_W: keyInputs[DirectIndex::UP] = true; break;
        case Qt::Key_S: keyInputs[DirectIndex::DOWN] = true; break;
        case Qt::Key_A: keyInputs[DirectIndex::LEFT] = true; break;
        case Qt::Key_D: keyInputs[DirectIndex::RIGHT] = true; break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* pKeyEvent)
{
    switch (pKeyEvent->key())
    {
        case Qt::Key_W: keyInputs[DirectIndex::UP] = false; break;
        case Qt::Key_S: keyInputs[DirectIndex::DOWN] = false; break;
        case Qt::Key_A: keyInputs[DirectIndex::LEFT] = false; break;
        case Qt::Key_D: keyInputs[DirectIndex::RIGHT] = false; break;
    }
}
