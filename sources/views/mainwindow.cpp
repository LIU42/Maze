#include "views/mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    frameTimer = new QTimer(this);
    clockTimer = new QTimer(this);

    gameFramework = new GameFramework();
    gameResources = new GameResources();
    successDialog = new SuccessDialog(this);

    ui->setupUi(this);
    ui->sceneWidget->setGameFramework(gameFramework);
    ui->sceneWidget->setGameResources(gameResources);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete successDialog;
    delete frameTimer;
    delete clockTimer;
    delete gameFramework;
    delete gameResources;
}

void MainWindow::initialize()
{
    connect(frameTimer, &QTimer::timeout, this, [=]
    {
        updateGame();
    });

    connect(clockTimer, &QTimer::timeout, this, [=]
    {
        if (gameFramework->isPlaying())
        {
            elapseTime += 1;
        }
    });

    connect(ui->restartButton, &QPushButton::clicked, this, [=]
    {
        restartGame();
    });

    connect(ui->fogButton, &QPushButton::clicked, this, [=]
    {
        gameFramework->switchFogMode();
    });

    connect(ui->trackButton, &QPushButton::clicked, this, [=]
    {
        ui->sceneWidget->updateWayBlocks();
    });

    restartGame();

    frameTimer->setInterval(TimerInterval::FRAME);
    frameTimer->start();

    clockTimer->setInterval(TimerInterval::CLOCK);
    clockTimer->start();
}

void MainWindow::updateGame()
{
    if (gameFramework->isPlaying())
    {
        gameFramework->playerMove(directPriority);

        if (gameFramework->isGameover())
        {
            successDialog->setInfo(elapseTime, gameFramework->hasTracked());

            if (successDialog->exec() == 0)
            {
                restartGame();
            }
        }
        ui->timeValueLabel->setNum(elapseTime);
    }
    ui->sceneWidget->update();
}

void MainWindow::restartGame()
{
    gameFramework->restart();
    directPriority.clear();
    elapseTime = 0;
    ui->sceneWidget->clearWayBlocks();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    int pressedKey = event->key();

    if (pressedKey == Qt::Key_W)
    {
        directPriority.append(Directs::UP);
    }
    else if (pressedKey == Qt::Key_S)
    {
        directPriority.append(Directs::DOWN);
    }
    else if (pressedKey == Qt::Key_A)
    {
        directPriority.append(Directs::LEFT);
    }
    else if (pressedKey == Qt::Key_D)
    {
        directPriority.append(Directs::RIGHT);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    int pressedKey = event->key();

    if (pressedKey == Qt::Key_W)
    {
        directPriority.removeAll(Directs::UP);
    }
    else if (pressedKey == Qt::Key_S)
    {
        directPriority.removeAll(Directs::DOWN);
    }
    else if (pressedKey == Qt::Key_A)
    {
        directPriority.removeAll(Directs::LEFT);
    }
    else if (pressedKey == Qt::Key_D)
    {
        directPriority.removeAll(Directs::RIGHT);
    }
}
