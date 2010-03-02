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

#include "Connector.h"

#include <QtCore>
#include <QtNetwork>

Connector::Connector(QObject *parent)
	: QObject(parent)
{
    setObjectName("PuppetTestConnector");
}

Connector::~Connector()
{
}

bool Connector::connectToPuppet(const QString &host, quint16 port)
{
    Q_ASSERT(!m_connection);
	QTcpSocket *connection = new QTcpSocket(this);
	m_connection = connection;
	connection->connectToHost(host, port);
	if (connection->waitForConnected(connectTimeout_)) {
        qDebug("Connected to %s:%d.", qPrintable(host), port);
        return true;
    } else {
        qDebug("Can't connect to %s:%d.", qPrintable(host), port);
		qDebug() << "Error:" << connection->error() << connection->errorString();
		delete connection;
        return false;
    }
}

QTcpSocket * Connector::connection() const
{
	return m_connection.data();
}
