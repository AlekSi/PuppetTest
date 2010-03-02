#include <QtGui/QApplication>
#include "MainWidget.h"

#include "../puppet/macros.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BECOME_PUPPET
    MainWidget w;
    w.show();
    return a.exec();
}
