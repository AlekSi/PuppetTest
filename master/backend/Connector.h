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

#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QtCore/QObject>
#include <QtCore/QWeakPointer>
class QTcpSocket;

/*! Manages a connection with puppet. */
class Connector : public QObject
{
    Q_OBJECT

public:
    Connector(QObject *parent = 0);
    virtual ~Connector();

    /*! \returns true if connected, false otherwise. */
    bool connectToPuppet(const QString &host, quint16 port);

    /*! \returns connection. */
    QTcpSocket *connection() const;

private:
    static const int connectTimeout_ = 5000;
	QWeakPointer<QTcpSocket> m_connection;
};

#endif // CONNECTOR_H
