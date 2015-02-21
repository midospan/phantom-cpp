/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "VariableWidget.h"
#include "VariableWidgetEditor.h"
#include "VariableNode.h"
#include "VariableModel.h"
/* *********************************************** */
namespace phantom { namespace qt {

VariableWidget::VariableWidget( VariableWidgetEditor* a_pVariableWidgetEditor, VariableEditor* a_pVariableEditor ) 
    : m_pVariableWidgetEditor(a_pVariableWidgetEditor)
    , m_pVariableNode(nullptr)
    , m_pVariableEditor(a_pVariableEditor)
{
    QLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));
    setAutoFillBackground(false);
    setAttribute(Qt::WA_NoBackground);
    rebuildLayout();
}

VariableWidget::~VariableWidget()
{
    for(auto it = m_Actions.begin(); it != m_Actions.end(); ++it)
    {
        o_dynamic_delete *it;
    }
}

void VariableWidget::addVariableAction( VariableAction* a_pAction )
{
//     m_Actions.append(a_pAction);
//     a_pAction->setParent(this);
//     rebuildLayout();
}

void VariableWidget::rebuildLayout()
{
    delete layout();
    QLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_pVariableWidgetEditor->getWidget());
//     for(auto it = m_Actions.begin(); it != m_Actions.end(); ++it)
//     {
//         QToolButton* pButton = new QToolButton(this);
//         pButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
//         pButton->setIconSize(QSize(16,16));
//         pButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding));
//         pButton->setDefaultAction(*it);
//         layout->addWidget(pButton);
//     }
    setFocusProxy(m_pVariableWidgetEditor->getWidget());
}

QSize VariableWidget::sizeHint() const
{
    return m_pVariableWidgetEditor->getWidget()->sizeHint();
}

}}
