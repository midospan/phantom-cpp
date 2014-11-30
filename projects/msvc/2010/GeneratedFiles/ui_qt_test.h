/********************************************************************************
** Form generated from reading UI file 'qt_test.ui'
**
** Created: Wed 29. Oct 19:58:10 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_TEST_H
#define UI_QT_TEST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qt_testClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qt_testClass)
    {
        if (qt_testClass->objectName().isEmpty())
            qt_testClass->setObjectName(QString::fromUtf8("qt_testClass"));
        qt_testClass->resize(600, 400);
        menuBar = new QMenuBar(qt_testClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        qt_testClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(qt_testClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        qt_testClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(qt_testClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        qt_testClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(qt_testClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        qt_testClass->setStatusBar(statusBar);

        retranslateUi(qt_testClass);

        QMetaObject::connectSlotsByName(qt_testClass);
    } // setupUi

    void retranslateUi(QMainWindow *qt_testClass)
    {
        qt_testClass->setWindowTitle(QApplication::translate("qt_testClass", "qt_test", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class qt_testClass: public Ui_qt_testClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_TEST_H
