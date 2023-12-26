QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/Headers/

SOURCES += \
    Sources/Graphics.cpp \
    Sources/Main.cpp \
    Sources/MainWindow.cpp \
	Sources/Games/MainGame.cpp \
	Sources/Games/MazeMap.cpp \
	Sources/Games/Player.cpp \
	Sources/Dialogs/Success.cpp

HEADERS += \
    Headers/Graphics.h \
    Headers/MainWindow.h \
	Headers/Games/MainGame.h \
	Headers/Games/MazeMap.h \
	Headers/Games/Player.h \
	Headers/Dialogs/Success.h

FORMS += \
	Forms/MainWindow.ui \
	Forms/Dialogs/Success.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/Resources.qrc

RC_ICONS = Resources/Images/icon.ico