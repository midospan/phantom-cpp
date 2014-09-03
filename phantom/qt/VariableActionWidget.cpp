/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "VariableActionWidget.h"
#include "VariableActionWidget.hxx"
#include "VariableNode.h"
#include "phantom/reflection/Expression.h"
#include "phantom/std/string.h"
#include <QWidget>
/* *********************************************** */
o_registerN((phantom, qt), VariableActionWidget);

namespace phantom { namespace qt {

VariableActionWidget::VariableActionWidget( QWidget* a_pWidget, const char* a_pReeditSignal ) 
    : m_pWidget(a_pWidget)
    , m_pVariableNode(nullptr)
{
    connect(m_pWidget, a_pReeditSignal, this, SIGNAL(reeditRequested()));
    connect(m_pWidget, SIGNAL(destroyed()), this, SLOT(slotDestroyed()));
}

void VariableActionWidget::setVariableNode( VariableNode* a_pVariableNode )
{
    if(m_pVariableNode == a_pVariableNode) 
        return; 
    m_pVariableNode = a_pVariableNode; 
    
    variableNodeChanged(m_pVariableNode);
}

void VariableActionWidget::slotDestroyed()
{
    o_dynamic_delete this;
}

void VariableActionWidget::variableNodeChanged( VariableNode* a_pVariable )
{

}

void VariableActionWidget::setValues( void const** a_ppMultipleSrc ) const
{
    for(size_t i = 0 ;i<m_pVariableNode->getExpressionCount(); ++i)
    {
        setValue(a_ppMultipleSrc[i]);
    }
}

void VariableActionWidget::getValues( void** a_ppMultipleDest ) const
{
    for(size_t i = 0 ;i<m_pVariableNode->getExpressionCount(); ++i)
    {
        getValue(a_ppMultipleDest[i]);
    }
}

}}
