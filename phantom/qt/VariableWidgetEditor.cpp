/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "VariableWidgetEditor.h"
#include "VariableWidgetEditor.hxx"
#include "VariableNode.h"
#include "phantom/reflection/Expression.h"
#include <QWidget>
/* *********************************************** */
o_registerN((phantom, qt), VariableWidgetEditor);

namespace phantom { namespace qt {

VariableWidgetEditor::VariableWidgetEditor( QWidget* a_pWidget, const char* valueChangedSignal, reflection::Type* a_pValueType) 
    : m_pWidget(a_pWidget)
    , m_pValueType(a_pValueType)
    , m_pVariableNode(nullptr)
{
    connect(m_pWidget, valueChangedSignal, this, SIGNAL(valueChanged()));
    connect(m_pWidget, SIGNAL(destroyed()), this, SLOT(slotDestroyed()));
    connect(&m_OpenTimer, SIGNAL(timeout()), this, SLOT(opened()));
    m_OpenTimer.setSingleShot(true);
    m_OpenTimer.start(0);
}


void VariableWidgetEditor::slotDestroyed()
{
    o_dynamic_delete this;
}

}}
