#include "qt_test.h"
#include <QtGui/QApplication>
#include <phantom/qt/qt.h>

int main(int argc, char *argv[])
{
    o_main("unitest.qt", argc, argv);
    QApplication a(argc, argv);
    qt_test w;
    w.show();
    int result = a.exec();
    return result;
}
