#ifndef QSwitchedWidget_h__
#define QSwitchedWidget_h__

/* ****************** Includes ******************* */
#include "QWidgetsPrerequisites.h"
#include <QPainter>
#include <QDockWidget>
#include <QStackedWidget>
#include <QMouseEvent>
#include "QSwitch3D.h"
#include <QTreeView>
#include <QKeyEvent>
#include <QApplication>
/* **************** Declarations ***************** */

/* *********************************************** */

class QWIDGETS_EXPORT ColorWidget : public QWidget
{
public:
    ColorWidget(int r, int g, int b)
        : m_Color(r,g,b)
    {

    }

    void paintEvent(QPaintEvent* event)
    {
        QPainter p(this);
        p.fillRect(rect(), m_Color);
    }

    QColor  m_Color;
};

class QWIDGETS_EXPORT QSwitchedWidget : public QStackedWidget
{
    Q_OBJECT
    //o_gui_object

public:
	QSwitchedWidget(void);
	~QSwitchedWidget(void) {}

    void addSwitchableWidget(QWidget* pWidget);

    void removeSwitchableWidget(QWidget* pWidget);

    bool hasSwitchableWidget(QWidget* a_pWidget) const;
/*

    void wheelEvent(QWheelEvent * event)
    {
        if(m_pSwitch3D->getState() != QSwitch3D::e_State_Opened 
            && m_pSwitch3D->getState() != QSwitch3D::e_State_AnimatingSelect) return;
        int numDegrees = event->delta() / 8;
        int numSteps = numDegrees / 15;
        
        printf("%d\n",numSteps);
        if(event->delta() > 0)
        {
            m_pSwitch3D->selectNext();
        }
        else 
        {
            m_pSwitch3D->selectPrevious();
        }

    }*/

    void    keyPressEvent(QKeyEvent * event);

    void    keyReleaseEvent(QKeyEvent * event);

protected slots:
    void                        setCurrentIndex(int index)
    {
        m_pStackedWidget->setCurrentIndex(index);
    }
    void                        setCurrentWidget(QWidget* a_pWidget)
    {
        m_pStackedWidget->setCurrentWidget(a_pWidget);
    }
    void                        showSwitch3D()
    {
        QStackedWidget::setCurrentIndex(1);
    }
    void                        hideSwitch3D()
    {
        QStackedWidget::setCurrentIndex(0);
    }
    void                    openSwitch()
    {
        m_pSwitch3D->open(m_pStackedWidget->currentIndex());
    }

    void resizeEvent(QResizeEvent *event);

protected:
    QSwitch3D*                  m_pSwitch3D;
    QStackedWidget*             m_pStackedWidget;
    QTimer                      m_SwitchTriggerTimer;

};

#endif // Gui_QSwitchedWidget_h__
