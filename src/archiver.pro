#-------------------------------------------------
#
# Project created by QtCreator 2010-09-14T23:59:07
#
#-------------------------------------------------

QT       += core\
            sql\
            network\
            xml\
            xmlpatterns\
            gui

TARGET = archiver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    qarchiver.cpp \
    configurations.cpp

HEADERS += \
    qarchiver.h \
    configurations.h
