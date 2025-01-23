#ifndef __VIEWS_MAINWINDOW_H__
#define __VIEWS_MAINWINDOW_H__

#include <QMainWindow>
#include <QTimer>
#include <QList>
#include <QKeyEvent>

#include "cores/framework.h"
#include "utils/resources.h"
#include "views/dialogs/successdialog.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::MainWindow* ui;

    private:
        GameFramework* gameFramework;
        GameResources* gameResources;

    private:
        SuccessDialog* successDialog;

    private:
        QTimer* frameTimer;
        QTimer* clockTimer;

    private:
        QList<int> directPriority;

    private:
        int elapseTime;

    private:
        void updateGame();
        void restartGame();

    private:
        void keyPressEvent(QKeyEvent* event) override;
        void keyReleaseEvent(QKeyEvent* event) override;

    public:
        MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

    public:
        void initialize();
};
#endif
