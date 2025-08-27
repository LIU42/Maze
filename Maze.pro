QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/sources/

SOURCES += \
	sources/cores/framework.cpp \
	sources/main.cpp \
	sources/cores/map.cpp \
	sources/cores/player.cpp \
	sources/cores/points.cpp \
	sources/utils/resources.cpp \
	sources/views/successdialog.cpp \
	sources/views/mainwindow.cpp \
	sources/views/scenewidget.cpp

HEADERS += \
	sources/cores/framework.h \
	sources/cores/map.h \
	sources/cores/player.h \
	sources/cores/points.h \
	sources/utils/constants.h \
	sources/utils/resources.h \
	sources/views/successdialog.h \
	sources/views/mainwindow.h \
	sources/views/scenewidget.h

FORMS += \
	forms/successdialog.ui \
	forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	resources/resources.qrc

RC_ICONS = resources/images/icon.ico
