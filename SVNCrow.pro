#-------------------------------------------------
#
# Project created by QtCreator 2012-03-29T20:06:44
#
#-------------------------------------------------

QT       += core xml widgets

TARGET = SVNCrow
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
    settings.cpp \
    application.cpp \
    crowmon.cpp \
    toast.cpp

HEADERS  += \
    output.h \
    settings.h \
    application.h \
    crowmon.h \
    toast.h

FORMS    += \
    settings.ui \
    settingsnew.ui \
    toast.ui

RESOURCES += \
    svncrow.qrc
