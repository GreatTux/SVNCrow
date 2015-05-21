#-------------------------------------------------
#
# Project created by QtCreator 2012-03-29T20:06:44
#
#-------------------------------------------------

QT       += core xml widgets

TARGET = SVNCrow
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    settings.cpp \
    application.cpp \
    crowmon.cpp

HEADERS  += widget.h \
    output.h \
    settings.h \
    application.h \
    crowmon.h

FORMS    += widget.ui \
    settings.ui \
    settingsnew.ui

RESOURCES += \
    svncrow.qrc
