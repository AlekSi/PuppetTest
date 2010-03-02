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

#ifndef QTESTBINDINGS_H
#define QTESTBINDINGS_H

#include <QtCore/QObject>
#include <QtTest>

namespace PuppetTest
{

/*! Bindings for QTest namespace. */
class QTestBindings : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QTestBindings)

public:
	QTestBindings(QObject *parent);
    virtual ~QTestBindings();

public slots:

    // TODO How to make Qt::MouseButton works?
    // I played a little with Q_DECLARE_METATYPE / qRegisterMetaType - it breaks script code.

    void mouseClick(QWidget *widget, int button, Qt::KeyboardModifiers modifier = 0,
                           QPoint pos = QPoint(), int delay = -1) const;
    void mouseMove(QWidget *widget, QPoint pos = QPoint(), int delay = -1) const;
};

}	// namespace PuppetTest

#endif // QTESTBINDINGS_H
