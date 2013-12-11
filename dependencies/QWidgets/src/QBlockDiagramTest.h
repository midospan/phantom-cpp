#ifndef QWIDGETSTEST_H
#define QWIDGETSTEST_H

#include "QWidgetsPrerequisites.h"
#include <QMainWindow>

class QWIDGETS_EXPORT QBlockDiagramTest : public QMainWindow
{
    Q_OBJECT

    QBlockDiagramTest(QWidget *parent = 0);
public:
    ~QBlockDiagramTest();
    static QBlockDiagramTest* Instance()
    {
      static QBlockDiagramTest s_Instance;
      return &s_Instance;
    }


private:
};

#endif // QWIDGETSTEST_H
