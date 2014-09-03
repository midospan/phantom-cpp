/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "ComponentReferenceExpressionChangeCommand.h"
#include "ComponentReferenceExpressionChangeCommand.hxx"
#include <phantom/serialization/Node.h>
/* *********************************************** */
o_registerN((phantom, qt), ComponentReferenceExpressionChangeCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================

ComponentReferenceExpressionChangeCommand::ComponentReferenceExpressionChangeCommand(phantom::serialization::DataBase* a_pDataBase, const phantom::data& a_Data, const string& a_NewValue)
: UndoCommand()
, m_pDataBase(a_pDataBase)
, m_uiGuid(a_pDataBase->getGuid(a_Data))
, m_strNewValue(a_NewValue)
, m_strOldValue(m_pDataBase->getComponentDataReferenceExpression(a_Data))
{
    o_assert(m_pDataBase);
    setName("Component data '"+phantom::lexical_cast<string>((void*)m_uiGuid)+"' reference updated");
}

ComponentReferenceExpressionChangeCommand::ComponentReferenceExpressionChangeCommand( serialization::DataBase* a_pDataBase, uint a_uiGuid, const string& a_NewValue, const string& a_OldValue )
    : UndoCommand()
    , m_pDataBase(a_pDataBase)
    , m_uiGuid(a_uiGuid)
    , m_strNewValue(a_NewValue)
    , m_strOldValue(a_OldValue)
{
    o_assert(m_pDataBase);
    setName("Component data '"+phantom::lexical_cast<string>((void*)m_uiGuid)+"' reference updated");
}

ComponentReferenceExpressionChangeCommand::~ComponentReferenceExpressionChangeCommand()
{

}


//================================================
// Operations
//================================================


void ComponentReferenceExpressionChangeCommand::redo()
{
    phantom::data d = m_pDataBase->getData(m_uiGuid);
    o_assert(!d.isNull());
    m_pDataBase->setComponentDataReferenceExpression(d, m_strNewValue);
}

void ComponentReferenceExpressionChangeCommand::undo()
{
    phantom::data d = m_pDataBase->getData(m_uiGuid);
    o_assert(!d.isNull());
    m_pDataBase->setComponentDataReferenceExpression(d, m_strOldValue);
}

UndoCommand* ComponentReferenceExpressionChangeCommand::clone() const
{
    return o_new(ComponentReferenceExpressionChangeCommand)(m_pDataBase, m_uiGuid, m_strNewValue, m_strOldValue);
}

}}
