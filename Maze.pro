QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

LIBS += Dwmapi.lib

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sources/graphics.cpp \
    Sources/main.cpp \
    Sources/mainwindow.cpp \
	Sources/Models/map.cpp \
	Sources/Models/maze.cpp \
	Sources/Models/player.cpp \
	Sources/Dialogs/success.cpp

HEADERS += \
    Sources/graphics.h \
    Sources/mainwindow.h \
	Sources/Models/map.h \
	Sources/Models/maze.h \
	Sources/Models/player.h \
	Sources/Dialogs/success.h

FORMS += \
	Forms/mainwindow.ui \
	Forms/Dialogs/success.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/resource.qrc

RC_ICONS = Resources/Images/icon.ico