QT -= core
QT -= gui

TARGET = system_stat
CONFIG += console c++11
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    client.cpp \
    dispatcher.cpp \
    reporter.cpp \
    server.cpp \
    network.cpp \
    node.cpp \
    protocoltypetcp.cpp \
    protocoltypeudp.cpp \
    protocoltype.cpp

HEADERS += \
    client.hpp \
    dispatcher.hpp \
    reporter.hpp \
    server.hpp \
    connection_types.hpp \
    network.hpp \
    node.hpp \
    protocoltypetcp.hpp \
    protocoltypeudp.hpp \
    protocoltype.hpp

