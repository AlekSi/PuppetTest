TEMPLATE = app
TARGET = PuppetMaster
VERSION = 0.1
QT = core gui network

MOC_DIR = _build
UI_DIR = _build
OBJECTS_DIR = _build/obj

INCLUDEPATH += $$PWD
include($$PWD/backend/backend.pri)
include($$PWD/gui/gui.pri)

SOURCES += main.cpp
