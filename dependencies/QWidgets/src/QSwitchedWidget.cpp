/* ******************* Includes ****************** */
#include "QSwitchedWidget.h"
/* *********************************************** */

QSwitchedWidget::QSwitchedWidget( void )
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

void QSwitchedWidget::resizeEvent( QResizeEvent *event )
{
    m_pSwitch3D->resizeEvent(event);
}

bool QSwitchedWidget::hasSwitchableWidget( QWidget* a_pWidget ) const
{
    for(int i = 0; i<m_pStackedWidget->count(); ++i)
    {
        if(m_pStackedWidget->widget(i) == a_pWidget) return true; 
    }
    return false;
}

void QSwitchedWidget::addSwitchableWidget( QWidget* pWidget )
{
    pWidget->hide();
    m_pStackedWidget->addWidget(pWidget);
    m_pSwitch3D->addSwitchable3D(new QStaticWidgetSwitchable3D(pWidget));
}

void QSwitchedWidget::removeSwitchableWidget( QWidget* pWidget )
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

void QSwitchedWidget::keyPressEvent( QKeyEvent * event )
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

void QSwitchedWidget::keyReleaseEvent( QKeyEvent * event )
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


