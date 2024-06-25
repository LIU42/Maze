QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/Headers/

SOURCES += \
	Sources/Engines/MainGame.cpp \
	Sources/Engines/Map.cpp \
	Sources/Engines/Player.cpp \
	Sources/Engines/Point.cpp \
	Sources/Modules/Resources.cpp \
	Sources/Views/Dialogs/Success.cpp \
	Sources/Views/MainWindow.cpp \
	Sources/Main.cpp \
	Sources/Views/Widgets/Scene.cpp

HEADERS += \
	Headers/Engines/MainGame.h \
	Headers/Engines/Map.h \
	Headers/Engines/Player.h \
	Headers/Engines/Point.h \
	Headers/Modules/Resources.h \
	Headers/Views/Dialogs/Success.h \
	Headers/Views/MainWindow.h \
	Headers/Views/Widgets/Scene.h

FORMS += \
	Forms/Dialogs/Success.ui \
	Forms/MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/Resources.qrc

RC_ICONS = Resources/Images/icon.ico
