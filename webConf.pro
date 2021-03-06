#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T09:52:28
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_ICONS = earth.ico
VERSION = 1.0.0.1
QMAKE_TARGET_COMPANY = Kontel Co
QMAKE_TARGET_PRODUCT = Dispatcher Config
QMAKE_TARGET_DESCRIPTION = Web Server Configuration Utility
QMAKE_TARGET_COPYRIGHT = Kontel

TARGET = webConf
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    messagevar.cpp \
    discretevar.cpp \
    analogvar.cpp \
    controller.cpp \
    dispobject.cpp \
    objectgroup.cpp \
    disproot.cpp \
    dialoggroupadd.cpp \
    dialoggroupchangename.cpp \
    dialogcontrolleradd.cpp \
    dialogobjectadd.cpp \
    dialoganalogvaradd.cpp \
    dialogdiscretevaradd.cpp \
    dialogmessagevaradd.cpp

HEADERS  += mainwindow.h \
    messagevar.h \
    discretevar.h \
    analogvar.h \
    controller.h \
    dispobject.h \
    objectgroup.h \
    disproot.h \
    dialoggroupadd.h \
    dialoggroupchangename.h \
    dialogcontrolleradd.h \
    dialogobjectadd.h \
    dialoganalogvaradd.h \
    dialogdiscretevaradd.h \
    dialogmessagevaradd.h

FORMS    += mainwindow.ui \
    dialoggroupadd.ui \
    dialoggroupchangename.ui \
    dialogcontrolleradd.ui \
    dialogobjectadd.ui \
    dialoganalogvaradd.ui \
    dialogdiscretevaradd.ui \
    dialogmessagevaradd.ui
