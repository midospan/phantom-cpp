#ifndef QT_TEST_H
#define QT_TEST_H

#include <QtGui/QMainWindow>
#include "ui_qt_test.h"
#include <phantom/phantom.h>

namespace phantom { namespace qt { class VariableModel; } }

class qt_test : public QMainWindow
{
    Q_OBJECT

public:
    qt_test(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~qt_test();

protected slots:
    void edit(const phantom::vector<phantom::data>& a_Data);

private:
    phantom::qt::VariableModel* m_pModel0;
    phantom::qt::VariableModel* m_pModel1;
    phantom::qt::VariableModel* m_pModel2;
    phantom::qt::VariableModel* m_pModel3;
    Ui::qt_testClass ui;
};

#endif // QT_TEST_H
