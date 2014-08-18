/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "NodeAttributeChangeCommand.h"
#include "NodeAttributeChangeCommand.hxx"
#include <phantom/serialization/Node.h>
/* *********************************************** */
o_registerN((phantom, qt), NodeAttributeChangeCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================

NodeAttributeChangeCommand::NodeAttributeChangeCommand(serialization::Node* a_pNode, size_t a_uiAttributeIndex, const string& a_NewValue)
: UndoCommand()
, m_pDataBase(a_pNode->getOwnerDataBase())
, m_uiGuid(a_pNode->getGuid())
, m_uiAttributeIndex(a_uiAttributeIndex)
, m_strNewValue(a_NewValue)
, m_strOldValue(m_pDataBase->getNodeAttributeValue(a_pNode, a_uiAttributeIndex))
{
    o_assert(m_pDataBase);
    setName("Attribute '"+m_pDataBase->getAttributeName(m_uiAttributeIndex)+"' "+ "changed on node '"+boost::lexical_cast<string>((void*)m_uiGuid)+"' from '"+m_strOldValue+"' to '"+m_strNewValue+"'");
}

NodeAttributeChangeCommand::~NodeAttributeChangeCommand()
{

}


//================================================
// Operations
//================================================


void NodeAttributeChangeCommand::redo()
{
    serialization::Node* pNode = m_pDataBase->getNode(m_uiGuid);
    o_assert(pNode);
    m_pDataBase->setNodeAttributeValue(pNode, m_uiAttributeIndex, m_strNewValue);
}

void NodeAttributeChangeCommand::undo()
{
    serialization::Node* pNode = m_pDataBase->getNode(m_uiGuid);
    o_assert(pNode);
    m_pDataBase->setNodeAttributeValue(pNode, m_uiAttributeIndex, m_strOldValue);
}

}}
