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

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <backend/Connector.h>

#include <QtCore>
#include <QtGui>
#include <QtNetwork>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::on_attachButton_clicked()
{
    Q_ASSERT(!m_connector);
	Connector *connector = new Connector(this);
	m_connector = connector;
	if (!connector->connectToPuppet(m_ui->hostEdit->text(), 56789)) {
		connector->deleteLater();
        return;
    }
	m_ui->hostEdit->setEnabled(false);
	m_ui->attachButton->setEnabled(false);
	m_ui->sendButton->setEnabled(true);
}

void MainWindow::on_sendButton_clicked()
{
	if(!m_connector) return;
	m_ui->sendButton->setEnabled(false);
	Connector *connector = m_connector.data();
	QTextStream stream(connector->connection());
    stream << m_ui->scriptEdit->toPlainText();
	stream.flush();
	bool hasData = connector->connection()->waitForReadyRead();
	Q_ASSERT(hasData);
	m_ui->outputEdit->setPlainText(QString::fromUtf8(connector->connection()->readAll()));
	m_ui->sendButton->setEnabled(true);
}
