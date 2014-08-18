/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "DataAttributeChangeCommand.h"
#include "DataAttributeChangeCommand.hxx"
#include <phantom/serialization/Node.h>
/* *********************************************** */
o_registerN((phantom, qt), DataAttributeChangeCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================

DataAttributeChangeCommand::DataAttributeChangeCommand(phantom::serialization::DataBase* a_pDataBase, const phantom::data& a_Data, size_t a_uiAttributeIndex, const string& a_NewValue)
: UndoCommand()
, m_pDataBase(a_pDataBase)
, m_uiGuid(a_pDataBase->getGuid(a_Data))
, m_uiAttributeIndex(a_uiAttributeIndex)
, m_strNewValue(a_NewValue)
, m_strOldValue(m_pDataBase->getDataAttributeValue(a_Data, a_uiAttributeIndex))
{
    o_assert(m_pDataBase);
    setName("Attribute '"+m_pDataBase->getAttributeName(m_uiAttributeIndex)+"' "+ "changed on data '"+boost::lexical_cast<string>((void*)m_uiGuid)+"' from '"+m_strOldValue+"' to '"+m_strNewValue+"'");
}

DataAttributeChangeCommand::~DataAttributeChangeCommand()
{

}


//================================================
// Operations
//================================================


void DataAttributeChangeCommand::redo()
{
    phantom::data d = m_pDataBase->getData(m_uiGuid);
    o_assert(!d.isNull());
    m_pDataBase->setDataAttributeValue(d, m_uiAttributeIndex, m_strNewValue);
}

void DataAttributeChangeCommand::undo()
{
    phantom::data d = m_pDataBase->getData(m_uiGuid);
    o_assert(!d.isNull());
    m_pDataBase->setDataAttributeValue(d, m_uiAttributeIndex, m_strOldValue);
}

}}
