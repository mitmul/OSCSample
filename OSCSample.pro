#-------------------------------------------------
#
# Project created by QtCreator 2012-02-22T02:07:52
#
#-------------------------------------------------

QT       += core gui

TARGET = OSCSample
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    OSCSender.cpp

HEADERS  += MainWindow.h \
    OSCSender.h

FORMS    += MainWindow.ui

mac {

# oscpack
INCLUDEPATH += /usr/local/include/oscpack \
    /usr/local/include/oscpack/osc \
    /usr/local/include/oscpack/ip
LIBS += -L/usr/local/lib \
    -loscpack

# liblo
INCLUDEPATH += /usr/local/include/lo
LIBS += -L/usr/local/lib \
    -llo

# boost
INCLUDEPATH += /opt/local/include
}
