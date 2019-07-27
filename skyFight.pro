#-------------------------------------------------
#
# Project created by QtCreator 2019-07-18T22:27:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = skyFight
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        abstractflyer.cpp \
        abstractplane.cpp \
        api.cpp \
        avilib.cpp \
        bossplane.cpp \
        bulletfactory.cpp \
        enemybullet1.cpp \
        enemybullet2.cpp \
        main.cpp \
        menemyplane.cpp \
        planefactory.cpp \
        playerbullet.cpp \
        playerplane.cpp \
        senemyplane.cpp \
        space.cpp \
        star.cpp \
        startmenu.cpp \
        supplyfactory.cpp \
        widget.cpp \
        yourcontrol.cpp

HEADERS += \
        abstractbullet.h \
        abstractflyer.h \
        abstractplane.h \
        abstractsupply.h \
        api.h \
        avilib.h \
        bossplane.h \
        bulletfactory.h \
        enemybullet1.h \
        enemybullet2.h \
        global.h \
        if_ai.h \
        menemyplane.h \
        planefactory.h \
        playerbullet.h \
        playerplane.h \
        randomer.h \
        recorder.h \
        replayer.h \
        rollingbackgroud.h \
        senemyplane.h \
        space.h \
        star.h \
        startmenu.h \
        supplyfactory.h \
        widget.h

FORMS += \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
