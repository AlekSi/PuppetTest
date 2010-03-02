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

#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>

#include <QtMetaObjectFramework.h>

void PuppetTest::bindQObject(QObject *object)
{
    Q_ASSERT(object);
	const QMap<QString, QObject *> hier = QtMetaObjectFramework::hierarchy(object);
	const QList<QString> names = hier.keys();
	foreach(const QString& name, names) {
		bindQObjectToName(hier[name], name);
	}
}

void PuppetTest::bindQObjectToName(QObject *object, const QString& name)
{
	Q_ASSERT(object);
	Q_ASSERT(!name.isEmpty());

	if(!engine()->globalObject().property(name).isValid()) {
		const QString className = object->metaObject()->className();
		QScriptValue o = engine()->newQObject(object);
		engine()->globalObject().setProperty(name, o);
		qDebug("Object %p (%s) binded as %s.", object, qPrintable(className), qPrintable(name));
	}
}

void PuppetTest::bindQMetaObjectToName(const QMetaObject *metaObject, const QString& name)
{
    Q_ASSERT(metaObject);
    Q_ASSERT(!name.isEmpty());

	if(!engine()->globalObject().property(name).isValid()) {
		const QString className = metaObject->className();
		QScriptValue mo = engine()->newQMetaObject(metaObject);
		engine()->globalObject().setProperty(name, mo);
		qDebug("Meta object %p (%s) binded as %s.", metaObject, qPrintable(className), qPrintable(name));
	}
}
