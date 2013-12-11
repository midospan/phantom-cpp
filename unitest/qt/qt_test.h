#ifndef QT_TEST_H
#define QT_TEST_H

#include <QtGui/QMainWindow>
#include "ui_qt_test.h"

class qt_test : public QMainWindow
{
    Q_OBJECT

public:
    qt_test(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~qt_test();

private:
    Ui::qt_testClass ui;
};

#endif // QT_TEST_H
