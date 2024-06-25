#include <QApplication>

#include "Views/MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow window;

    window.init();
    window.show();

    return app.exec();
}
