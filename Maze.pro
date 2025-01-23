QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/headers/

SOURCES += \
	sources/cores/framework.cpp \
	sources/main.cpp \
	sources/cores/map.cpp \
	sources/cores/player.cpp \
	sources/cores/points.cpp \
	sources/utils/resources.cpp \
	sources/views/dialogs/successdialog.cpp \
	sources/views/mainwindow.cpp \
	sources/views/widgets/scenewidget.cpp

HEADERS += \
	headers/cores/framework.h \
	headers/cores/map.h \
	headers/cores/player.h \
	headers/cores/points.h \
	headers/utils/constants.h \
	headers/utils/resources.h \
	headers/views/dialogs/successdialog.h \
	headers/views/mainwindow.h \
	headers/views/widgets/scenewidget.h

FORMS += \
	forms/dialogs/successdialog.ui \
	forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	resources/resources.qrc

RC_ICONS = resources/images/icon.ico
