#-------------------------------------------------
#
# Project created by QtCreator 2018-02-08T13:23:45
#
#-------------------------------------------------

QT       += xml
QT       -= gui

CONFIG(debug, debug|release) {
    TARGET = QtUSBd
}
else {
    TARGET = QtUSB
}

TEMPLATE = lib

CONFIG += c++11

DEFINES += QTUSB_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    QUSBPort.cpp \
    QUSBPortInfo.cpp

win32 {
SOURCES += \
    QUSBPortInfo_Win.cpp
}

HEADERS += \
    QtUSB_global.h \
    QUSBPortInfo.h \
    QUSBPort.h \
    QtUSB_global.h \
    QUSBPort.h \
    QUSBPortInfo.h

win32 {
    LIBS += setupapi.lib
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
