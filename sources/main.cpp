#include <QApplication>

#include "views/mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow window;

    window.initialize();
    window.show();

    return app.exec();
}
