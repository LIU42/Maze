QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/include/

SOURCES += \
	src/engines/controller.cpp \
	src/engines/map.cpp \
	src/engines/player.cpp \
	src/engines/point.cpp \
	src/modules/resources.cpp \
	src/views/dialogs/successdialog.cpp \
	src/views/mainwindow.cpp \
	src/main.cpp \
	src/views/widgets/scenewidget.cpp

HEADERS += \
	include/engines/controller.h \
	include/engines/map.h \
	include/engines/player.h \
	include/engines/point.h \
	include/modules/resources.h \
	include/views/dialogs/successdialog.h \
	include/views/mainwindow.h \
	include/views/widgets/scenewidget.h

FORMS += \
	ui/dialogs/successdialog.ui \
	ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	res/resources.qrc

RC_ICONS = res/images/icon.ico
