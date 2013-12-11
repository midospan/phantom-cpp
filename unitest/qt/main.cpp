#include "qt_test.h"
#include <QtGui/QApplication>
#include <phantom/qt/qt.h>

int main(int argc, char *argv[])
{
    phantom::Phantom p(argc,argv);
    QApplication a(argc, argv);
    qt_test w;
    w.show();
    return a.exec();
}
