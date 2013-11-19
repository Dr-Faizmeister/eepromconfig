#-------------------------------------------------
#
# Project created by QtCreator 2013-09-19T11:55:02
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eepromconf
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CFirstAreaTable.cpp \
    CTreeWidgetItem.cpp \
    CTreeWidget.cpp \
    DomParser.cpp

HEADERS  += mainwindow.h \
    CFirstAreaTable.h \
    CTreeWidgetItem.h \
    CTreeWidget.h \
    DomParser.h \
    TLV.h

FORMS    += mainwindow.ui
CONFIG += staticlib

RESOURCES += \
    config.qrc
