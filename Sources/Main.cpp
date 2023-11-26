#include "MainWindow.h"
#include "QStyleHints"

void setHighDPIScalePolicy()
{
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);
}

void setRandomSeed()
{
    srand((unsigned)time(NULL));
}

int main(int argc, char* argv[])
{
    setHighDPIScalePolicy();
    setRandomSeed();

    QApplication app(argc, argv);
    MainGame game;
    MainWindow window;

    app.setStyle("fusion");
    window.setGame(&game);
    window.initialize();
    window.show();

    return app.exec();
}