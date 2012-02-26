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
    OSCSender.cpp \
    OSCReceiver.cpp

HEADERS  += MainWindow.h \
    OSCSender.h \
    OSCReceiver.h

FORMS    += MainWindow.ui

mac {

# liblo
INCLUDEPATH += /usr/local/include/lo
LIBS += -L/usr/local/lib \
    -llo

# boost
INCLUDEPATH += /opt/local/include
LIBS += -L/opt/local/lib \
    -lboost_thread-mt
}
