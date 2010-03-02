TEMPLATE = app
TARGET = demo

MOC_DIR = _build
UI_DIR = _build
OBJECTS_DIR = _build/obj

HEADERS += MainWidget.h
SOURCES += MainWidget.cpp
FORMS += MainWidget.ui

SOURCES += main.cpp

CONFIG += be_puppet
include($$PWD/../puppet/puppet.pri)
