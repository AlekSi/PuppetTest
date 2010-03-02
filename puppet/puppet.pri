be_puppet { 

    DEFINES += BE_PUPPET

	QT *= network script testlib

    HEADERS += $$PWD/Puppet.h

    SOURCES += $$PWD/Engine.cpp \
        $$PWD/Binder.cpp \
        $$PWD/Puppet.cpp

    HEADERS += $$PWD/QTestBindings.h
    SOURCES += $$PWD/QTestBindings.cpp

	QMOF_DIR = $$PWD/../third-party/QtMetaObjectFramework/src/
	INCLUDEPATH += $$QMOF_DIR
	HEADERS += $$QMOF_DIR/QtMetaObjectFramework.h
	LIBS += -L$$QMOF_DIR -lQtMetaObjectFramework
}

HEADERS += $$PWD/macros.h
