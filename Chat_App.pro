TEMPLATE = app

QT += qml quick
QT += dbus
QT += sql
QT += core
QT +=multimedia
QT += dbus widgets
CONFIG += c++11

SOURCES += \
    chat.cpp \
    chat_adaptor.cpp \
    chat_interface.cpp

RESOURCES += qml.qrc


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    chat.h \
    chat_adaptor.h \
    chat_interface.h

DISTFILES += \
    LG.gif
