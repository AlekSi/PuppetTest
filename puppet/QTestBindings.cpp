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

#include "QTestBindings.h"
using namespace PuppetTest;

QTestBindings::QTestBindings(QObject *parent)
    : QObject(parent)
{
    setObjectName("QTest");
}

QTestBindings::~QTestBindings()
{
}

void QTestBindings::mouseClick(QWidget *widget, int button, Qt::KeyboardModifiers modifier, QPoint pos, int delay) const
{
    QTest::mouseClick(widget, static_cast<Qt::MouseButton>(button), modifier, pos, delay);
}

void QTestBindings::mouseMove(QWidget *widget, QPoint pos, int delay) const
{
    QTest::mouseMove(widget, pos, delay);
}
