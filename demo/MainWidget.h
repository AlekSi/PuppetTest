#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtGui/QWidget>

namespace Ui
{
    class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void on_createButton_clicked();
    void on_destroyButton_clicked();

private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
