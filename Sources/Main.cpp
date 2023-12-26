#include "MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);
    MainWindow window;

    application.setStyle("windows");
    window.init();
    window.show();

    return application.exec();
}
