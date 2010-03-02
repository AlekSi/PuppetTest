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

#ifndef PROCESS_OBSERVER_H
#define PROCESS_OBSERVER_H

#include <QtCore/QObject>
#include <QtCore/QWeakPointer>
#include <QtCore/QProcess>

class ProcessObserver : public QObject
{
    Q_OBJECT

public:
	ProcessObserver(QObject *parent = 0);
	virtual ~ProcessObserver();

    /*! Starts program and wait for it start.
     *  \returns true if program was started, false otherwise.
     */
    bool startProgram(const QString &program);

    /*! Stops program and wait for it stop. */
    void stopProgram();

    /*! \returns true if process is active, false otherwise. */
    bool isActive() const;

private slots:
    void onError(QProcess::ProcessError error);
    void onFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onStateChanged(QProcess::ProcessState newState);
    void onReadyReadStandardOutput();
    void onReadyReadStandardError();

private:
    static const int puppetProcessTimeout_ = 10000;
    static const int puppetProcessTimeoutStep_ = 100;

private:
	QWeakPointer<QProcess> m_process;
};

#endif // PROCESS_OBSERVER_H
