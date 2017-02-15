QT += core
QT -= gui

TARGET = cpu_stat
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    client.cpp \
    dispatcher.cpp \
    reporter.cpp \
    server.cpp \
    network.cpp \
    node.cpp

HEADERS += \
    client.hpp \
    dispatcher.hpp \
    reporter.hpp \
    server.hpp \
    connection_types.hpp \
    network.hpp \
    node.hpp

