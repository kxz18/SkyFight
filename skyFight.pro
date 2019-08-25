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
        api/api.cpp \
        api/yourcontrol.cpp \
        flyer/abstractflyer.cpp \
        flyer/abstractplane.cpp \
        flyer/bossplane.cpp \
        flyer/enemybullet1.cpp \
        flyer/enemybullet2.cpp \
        flyer/menemyplane.cpp \
        flyer/playerbullet.cpp \
        flyer/playerplane.cpp \
        flyer/senemyplane.cpp \
        flyer/star.cpp \
        main.cpp \
        manager/bulletfactory.cpp \
        manager/planefactory.cpp \
        manager/space.cpp \
        manager/startmenu.cpp \
        manager/supplyfactory.cpp \ 
        others/avilib.cpp \
        widget.cpp

HEADERS += \
        api/api.h \
        api/if_ai.h \
        flyer/abstractbullet.h \
        flyer/abstractflyer.h \
        flyer/abstractplane.h \
        flyer/abstractsupply.h \
        flyer/bossplane.h \
        flyer/enemybullet1.h \
        flyer/enemybullet2.h \
        flyer/menemyplane.h \
        flyer/playerbullet.h \
        flyer/playerplane.h \
        flyer/senemyplane.h \
        flyer/star.h \
        manager/bulletfactory.h \
        manager/global.h \
        manager/planefactory.h \
        manager/space.h \
        manager/startmenu.h \
        manager/supplyfactory.h \
        others/avilib.h \
        others/randomer.h \
        others/randomer_copy.h \
        others/recorder.h \
        others/recorder_new.h \
        others/replayer.h \
        others/replayer_new.h \
        others/rollingbackgroud.h \
        widget.h

FORMS += \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

INCLUDEPATH += \
              api/\
              flyer/\
              manager/\
              others/
