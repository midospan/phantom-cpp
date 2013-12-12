#include "qt_test.h"
#include <QtGui/QApplication>
#include <phantom/qt/qt.h>

int main(int argc, char *argv[])
{
    phantom::Phantom p(argc,argv);
    phantom::installReflection("main", "", 0);
    QApplication a(argc, argv);
    qt_test w;
    w.show();
    int result = a.exec();
    phantom::uninstallReflection("main");
    return result;
}
