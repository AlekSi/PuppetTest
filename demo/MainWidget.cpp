#include "MainWidget.h"
#include "ui_MainWidget.h"

#include <QtGui/QMessageBox>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWidget)
{
    ui->setupUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_createButton_clicked()
{
    if (ui->objectExists->isChecked()) {
        QMessageBox::warning(this, qApp->applicationName(), "Object already exists!");
        return;
    }
    ui->objectExists->setChecked(true);
}

void MainWidget::on_destroyButton_clicked()
{
    if (!ui->objectExists->isChecked()) {
        QMessageBox::warning(this, qApp->applicationName(), "Object doesn't exists!");
        return;
    }
    ui->objectExists->setChecked(false);
}
