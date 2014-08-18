/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "VariableWidgetEditor.h"
#include "VariableWidgetEditor.hxx"
#include "VariableNode.h"
#include "phantom/reflection/Expression.h"
#include "phantom/std/string.h"
#include <QWidget>
/* *********************************************** */
o_registerN((phantom, qt), VariableWidgetEditor);

namespace phantom { namespace qt {

VariableWidgetEditor::VariableWidgetEditor( QWidget* a_pWidget, const char* signal, reflection::Type* a_pType) 
    : m_pWidget(a_pWidget)
    , m_pType(a_pType)
    , m_pVariableNode(nullptr)
{
    connect(m_pWidget, signal, this, SIGNAL(valueChanged()));
    connect(m_pWidget, SIGNAL(destroyed()), this, SLOT(slotDestroyed()));
}

void VariableWidgetEditor::setVariableNode( VariableNode* a_pVariableNode )
{
    if(m_pVariableNode == a_pVariableNode) 
        return; 
    m_pVariableNode = a_pVariableNode; 
    
    variableChanged(m_pVariableNode);
}

void VariableWidgetEditor::slotDestroyed()
{
    o_dynamic_delete this;
}

void VariableWidgetEditor::variableChanged( VariableNode* a_pVariable )
{

}

void VariableWidgetEditor::setValues( void const** a_ppMultipleSrc ) const
{
    for(size_t i = 0 ;i<m_pVariableNode->getExpressionCount(); ++i)
    {
        setValue(a_ppMultipleSrc[i]);
    }
}

void VariableWidgetEditor::getValues( void** a_ppMultipleDest ) const
{
    for(size_t i = 0 ;i<m_pVariableNode->getExpressionCount(); ++i)
    {
        getValue(a_ppMultipleDest[i]);
    }
}

}}
