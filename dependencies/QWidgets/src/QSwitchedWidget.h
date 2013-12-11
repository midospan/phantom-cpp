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
	QSwitchedWidget(void) 
    {
        m_pStackedWidget  = new QStackedWidget();
        m_pSwitch3D = new QSwitch3D;
        addWidget(m_pStackedWidget);
        addWidget(m_pSwitch3D);

        connect(m_pSwitch3D, SIGNAL(selected(int)), this, SLOT(setCurrentIndex(int)));
        connect(m_pSwitch3D, SIGNAL(openingStarted()), this, SLOT(showSwitch3D()));
        connect(m_pSwitch3D, SIGNAL(closingEnded()), this, SLOT(hideSwitch3D()));

        connect(&m_SwitchTriggerTimer, SIGNAL(timeout()), this, SLOT(openSwitch()));

        QPalette p = m_pSwitch3D->palette();
        p.setColor(QPalette::Window, QColor(0,0,0));
        m_pSwitch3D->setPalette(p);

        m_pSwitch3D->setAutoFillBackground(true);
    }
	~QSwitchedWidget(void) {}

    void addSwitchableWidget(QWidget* pWidget)
    {
        pWidget->hide();
        m_pStackedWidget->addWidget(pWidget);
        m_pSwitch3D->addSwitchable3D(new QStaticWidgetSwitchable3D(pWidget));
    }

    void removeSwitchableWidget(QWidget* pWidget)
    {
        m_pStackedWidget->removeWidget(pWidget);
        int i = 0;
        int count = m_pSwitch3D->getSwitchable3DCount();
        for(;i<count;++i)
        {
            if( static_cast<QStaticWidgetSwitchable3D*>(m_pSwitch3D->getSwitchable3D(i))->getWidget() == pWidget)
            {
                m_pSwitch3D->removeSwitchable3D(i);
                break;
            }
        }
        Q_ASSERT(i<count);
    }
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

    void    keyPressEvent(QKeyEvent * event)
    {
        Qt::KeyboardModifiers modifiers = QApplication::keyboardModifiers();
        if(event->isAutoRepeat()) return;
        if((QApplication::keyboardModifiers() & Qt::ControlModifier) != 0)
        {
            if(event->key() == Qt::Key_Tab)
            {
                if(m_pSwitch3D->getState() == QSwitch3D::e_State_Closed)
                {
                    if(!m_SwitchTriggerTimer.isActive())
                    {
                        m_SwitchTriggerTimer.setSingleShot(true);
                        m_SwitchTriggerTimer.start(0);
                    }
                    //m_pSwitch3D->open(m_pStackedWidget->currentIndex());
                }                    
                else
                {
                    if(m_pSwitch3D->getState() == QSwitch3D::e_State_Opened 
                        || m_pSwitch3D->getState() == QSwitch3D::e_State_AnimatingSelect) 
                    {
                        m_pSwitch3D->selectNext();
                    }
                }
            } 
            else if(event->key() == Qt::Key_Backtab)
            {
                if(m_pSwitch3D->getState() == QSwitch3D::e_State_Closed)
                {
                    if(!m_SwitchTriggerTimer.isActive())
                    {
                        m_SwitchTriggerTimer.setSingleShot(true);
                        m_SwitchTriggerTimer.start(0);
                    }
                }                    
                else
                {
                    if(m_pSwitch3D->getState() == QSwitch3D::e_State_Opened 
                        || m_pSwitch3D->getState() == QSwitch3D::e_State_AnimatingSelect) 
                    {
                        m_pSwitch3D->selectPrevious();
                    }
                }
            }
        }
    }

    void    keyReleaseEvent(QKeyEvent * event)
    {
        if((!event->isAutoRepeat()) && m_SwitchTriggerTimer.isActive() && (event->key() == Qt::Key_Tab || event->key() == Qt::Key_Backtab))
        {
            m_SwitchTriggerTimer.stop();
            int nextIndex = m_pStackedWidget->currentIndex() + ((event->key() == Qt::Key_Tab)?1:-1);
            nextIndex = (nextIndex + m_pStackedWidget->count())%m_pStackedWidget->count();
            m_pStackedWidget->setCurrentIndex(nextIndex);
        }
        if(m_pSwitch3D->getState() != QSwitch3D::e_State_Closed)
        {
            if(event->key() == Qt::Key_Control)
            {
                m_pSwitch3D->requestClose();
                m_pStackedWidget->currentWidget()->setFocus();
            }
        }
    }

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
