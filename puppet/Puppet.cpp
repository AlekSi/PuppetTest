/********************************************************************
Copyright (C) 2010 Aleksey Palazhchenko

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
********************************************************************/

#include "Puppet.h"
#include "QTestBindings.h"
using namespace PuppetTest;

#include <QtCore>
#include <QtGui>
#include <QtScript>

// black magic explained: http://lists.trolltech.com/qt-interest/2007-07/thread00345-0.html
struct QtMetaObject : private QObject
{
public:
	static const QMetaObject *get() { return &static_cast<QtMetaObject *>(0)->staticQtMetaObject; }
};


Puppet *Puppet::instance_ = 0;

Puppet::Puppet()
	: QObject(qApp)
{
    Q_ASSERT(qApp);

    setObjectName("Puppet");

    bindQt();
	QTimer::singleShot(0, this, SLOT(bindWidgets()));

    qApp->installEventFilter(this);

    m_server.listen(QHostAddress::Any, 56789);
    m_server.setMaxPendingConnections(1);
    connect(&m_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

Puppet::~Puppet()
{
}

void Puppet::install()
{
    if (!instance_)
        instance_ = new Puppet();
}

bool Puppet::eventFilter(QObject *object, QEvent *event)
{
    const QString objectName = object->objectName();
    if (!objectName.isEmpty()) {
        const QString message = QString("Event %1 for %2 (%3): ").arg(event->type()).arg(objectName, object->metaObject()->className());

        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent *>(event);
		if (mouseEvent && mouseEvent->buttons()) {
			qDebug() << message << mouseEvent->pos() << "\t Global:" << mouseEvent->globalPos()
				<< "\t Buttons:" << mouseEvent->buttons();
        }

        QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);
        if (keyEvent) {
			qDebug() << message << keyEvent->text() << keyEvent->modifiers();
        }
    }

    // fly away
    return false;
}

void Puppet::onNewConnection()
{
	if(m_connection)
		m_connection.data()->deleteLater();
	m_connection = QWeakPointer<QTcpSocket>(m_server.nextPendingConnection());
	connect(m_connection.data(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void Puppet::onReadyRead()
{
	QTcpSocket *connection = m_connection.data();
	QScriptValue res = engine()->evaluate(connection->readAll());
    Q_ASSERT(res.isValid());
	connection->write(res.toString().toUtf8());
	connection->flush();
}

void Puppet::bindQt()
{
	bindQMetaObjectToName(QtMetaObject::get(), "Qt");
	bindQObjectToName(new QTestBindings(this), "QTest");
}

void Puppet::bindWidgets()
{
	QWidgetList widgets = QApplication::allWidgets();
	foreach(QWidget* widget, widgets) {
		widget->parent();
		bindQObject(widget);
	}
}
