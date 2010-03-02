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

#include "ProcessObserver.h"

#include <QtCore>

ProcessObserver::ProcessObserver(QObject *parent)
    : QObject(parent)
{
    setObjectName("PuppetTestLauncher");
}

ProcessObserver::~ProcessObserver()
{
    stopProgram();
}

bool ProcessObserver::startProgram(const QString& program)
{
    Q_ASSERT(!m_process);
	QProcess *process = new QProcess(this);
	m_process = process;
	connect(process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(onError(QProcess::ProcessError)));
	connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(onFinished(int,QProcess::ExitStatus)));
	connect(process, SIGNAL(stateChanged(QProcess::ProcessState)), this, SLOT(onStateChanged(QProcess::ProcessState)));
	connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(onReadyReadStandardOutput()));
	connect(process, SIGNAL(readyReadStandardError()), this, SLOT(onReadyReadStandardError()));

	process->start(program);
    for (int i=0; i<=puppetProcessTimeout_/puppetProcessTimeoutStep_; ++i) {
		if (process->waitForStarted(puppetProcessTimeoutStep_))
            return true;
        qApp->processEvents();
    }

    // if it didn't start, kill it
    stopProgram();
    qWarning("Can't start %s", qPrintable(program));
    return false;
}

void ProcessObserver::stopProgram()
{
    if (m_process) {
		QProcess *process = m_process.data();
		if (process->state() != QProcess::NotRunning) {
			process->terminate();
			process->waitForFinished(puppetProcessTimeout_);
        }
		process->deleteLater();
    }
}

bool ProcessObserver::isActive() const
{
    return m_process;
}

void ProcessObserver::onError(QProcess::ProcessError error)
{
    qDebug() << "Process error" << error;
}

void ProcessObserver::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    QString message(tr("Program %1 with code %2."));
    message = message.arg( exitStatus == QProcess::NormalExit ? tr("exited") : tr("crashed") ).arg(exitCode);
    qDebug() << message;
    stopProgram();
}

void ProcessObserver::onStateChanged(QProcess::ProcessState newState)
{
    qDebug() << "State changed to" << newState;
}

void ProcessObserver::onReadyReadStandardOutput()
{
	QByteArray data = m_process.data()->readAllStandardOutput();
    if (data.endsWith("\n"))
        data.chop(1);
    qDebug() << "Puppet stdout:" << data;
}

void ProcessObserver::onReadyReadStandardError()
{
	QByteArray data = m_process.data()->readAllStandardError();
    if (data.endsWith("\n"))
        data.chop(1);
    qDebug() << "Puppet stderr:" << data;
}
