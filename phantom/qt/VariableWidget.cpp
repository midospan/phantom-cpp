/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "VariableWidget.h"
#include "VariableWidgetEditor.h"
#include "VariableAction.h"
#include "VariableManager.h"
/* *********************************************** */
namespace phantom { namespace qt {

VariableWidget::VariableWidget( VariableWidgetEditor* a_pVariableWidgetEditor, VariableEditor* a_pVariableEditor ) 
    : m_pVariableWidgetEditor(a_pVariableWidgetEditor)
    , m_pVariable(nullptr)
    , m_pVariableEditor(a_pVariableEditor)
{
    QLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));
    setAutoFillBackground(true);
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
    m_Actions.append(a_pAction);
    a_pAction->setParent(this);
    rebuildLayout();
}

void VariableWidget::rebuildLayout()
{
    delete layout();
    QLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_pVariableWidgetEditor->getWidget());
    for(auto it = m_Actions.begin(); it != m_Actions.end(); ++it)
    {
        QToolButton* pButton = new QToolButton(this);
        pButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
        pButton->setIconSize(QSize(16,16));
        pButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding));
        pButton->setDefaultAction(*it);
        layout->addWidget(pButton);
    }
    setFocusProxy(m_pVariableWidgetEditor->getWidget());
}

void VariableWidget::setVariable( reflection::Variable* a_pVariable )
{
    if(m_pVariable == a_pVariable) 
        return; 
    m_pVariable = a_pVariable;
    m_pVariableWidgetEditor->setVariable(a_pVariable);

    reflection::Variable* pUnproxiedVariable = a_pVariable;
    ProxyVariable* pProxy = nullptr;
    // Remove proxy levels
    while( (pProxy = as<ProxyVariable*>(pUnproxiedVariable)) )
    {
        pUnproxiedVariable = pProxy->getProxiedVariable();
    }

    CollectionElementVariable* pCollectionElementVariable = phantom::as<CollectionElementVariable*>(pUnproxiedVariable);
    phantom::reflection::IteratorVariable* pIteratorVariable = phantom::as<phantom::reflection::IteratorVariable*>(pUnproxiedVariable);
    if(pCollectionElementVariable)
    {
        addVariableAction(o_new(ContainerMoveUpAction)(pCollectionElementVariable, this));
        addVariableAction(o_new(ContainerMoveDownAction)(pCollectionElementVariable, this));
    }
    if(pIteratorVariable)
    {
        addVariableAction(o_new(EraseContainerIteratorAction)(pIteratorVariable, this));
    }
    else if (a_pVariable->getRange()) 
    {
        addVariableAction(o_new(ResetAction)(a_pVariable, this));
    }
}

}}
