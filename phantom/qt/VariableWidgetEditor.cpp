/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "VariableWidgetEditor.h"
#include "VariableManager.h"
/* *********************************************** */
o_registerN((phantom, qt), VariableWidgetEditor);

namespace phantom { namespace qt {

VariableWidgetEditor::VariableWidgetEditor( QWidget* a_pWidget, const char* signal, reflection::Type* a_pType) 
    : m_pWidget(a_pWidget)
    , m_pType(a_pType)
    , m_pVariable(nullptr)
{
    connect(m_pWidget, signal, this, SIGNAL(valueChanged()));
    connect(m_pWidget, SIGNAL(destroyed()), this, SLOT(slotDestroyed()));
}

void VariableWidgetEditor::setVariable( reflection::Variable* a_pVariable )
{
    if(m_pVariable == a_pVariable) 
        return; 
    m_pVariable = a_pVariable; 
    
    variableChanged(m_pVariable);
}

void VariableWidgetEditor::slotDestroyed()
{
    o_dynamic_delete this;
}

void VariableWidgetEditor::variableChanged( reflection::Variable* a_pVariable )
{

}

}}
