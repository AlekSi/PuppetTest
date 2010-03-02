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

#ifndef PUPPET_H
#define PUPPET_H

#include <QtCore/QObject>
#include <QtCore/QWeakPointer>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
class QScriptEngine;

namespace PuppetTest
{

QScriptEngine *engine();

/*! Binds object and it's parents recursively. */
void bindQObject(QObject *object);

void bindQObjectToName(QObject *object, const QString& name);
void bindQMetaObjectToName(const QMetaObject *metaObject, const QString& name);

/*! Main puppet's class. Installs event filter, binds objects, opens port,
 *	reads and evaluates commands, sends responce. */
class Puppet : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Puppet)

public:
	/*! Installs puppet. Called by BECOME_PUPPET macro. */
	static void install();

protected:
    /*! Records events. */
    virtual bool eventFilter(QObject *object, QEvent *event);

private slots:
    void onNewConnection();
    void onReadyRead();

	void bindQt();
	void bindWidgets();

private:
    Puppet();
    virtual ~Puppet();

private:
    static Puppet *instance_;

    QTcpServer m_server;
	QWeakPointer<QTcpSocket> m_connection;
};

}   // namespace PuppetTest

#endif // PUPPET_H
