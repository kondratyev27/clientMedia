#-------------------------------------------------
#
# Project created by QtCreator 2017-12-15T19:24:29
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kr_client
TEMPLATE = app

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS _LINUX _NPTL

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS +=  -lMCU -lSDP4_3 -lCommon -lBaseLogic -lva -lyami -lva-drm -lcrypto -lavcodec -lavformat -lavutil -lX11 -lvdpau -ldl -lavdevice -lswscale -lswresample -lm -lz -lx264

INCLUDEPATH += $$(LIBS_INCLUDES)/libMCU/install/include


SOURCES += \
        main.cpp \
    VideoTermiantion.cpp \
    VideoWidget.cpp \
    Singleton.cpp \
    Widget.cpp \
    SettingsDialog.cpp

HEADERS += \
    VideoTermiantion.h \
    VideoWidget.h \
    Singleton.h \
    Widget.h \
    SettingsDialog.h \
    ServerParams.h

target.path = /bin
INSTALLS += target

FORMS += \
    SettingsDialog.ui
