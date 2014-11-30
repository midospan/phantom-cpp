/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "AddNodeCommand.h"
#include "AddNodeCommand.hxx"
#include <phantom/serialization/Node.h>
/* *********************************************** */
o_registerN((phantom, qt), AddNodeCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================

AddNodeCommand::AddNodeCommand(phantom::serialization::Node* a_pParentNode)
: DataBaseCommand(a_pParentNode->getDataBase())
, m_uiParentGuid(a_pParentNode->getGuid())
, m_uiGuid(0xffffffff)
{
    o_assert(m_pDataBase);
    setName("Add node to '" + m_pDataBase->getNodeAttributeValue(a_pParentNode, "name")+"'("+boost::lexical_cast<string>((void*)m_uiParentGuid)+")");
}

AddNodeCommand::~AddNodeCommand()
{

}


//================================================
// Operations
//================================================

void AddNodeCommand::redoReplayed()
{
    serialization::Node* pParentNode = m_pDataBase->getNode(m_uiParentGuid);
    o_assert(pParentNode);
    serialization::Node* pNode = nullptr; 
    if(m_uiGuid != 0xffffffff)
    {
        pNode = pParentNode->newChildNode(m_uiGuid);
    }
    else
    {
        pNode = pParentNode->newChildNode();
    }
    m_uiGuid = pNode->getGuid();
    m_pDataBase->setNodeAttributeValue(pNode, "name", "Node");
    pNode->saveAttributes();
}

void AddNodeCommand::undoReplayed()
{
    serialization::Node* pParentNode = m_pDataBase->getNode(m_uiParentGuid);
    o_assert(pParentNode);
    o_assert(m_uiGuid != 0xffffffff);
    serialization::Node* pNode = m_pDataBase->getNode(m_uiGuid);
    pParentNode->removeChildNode(pNode);
}


UndoCommand* AddNodeCommand::clone() const
{
    return o_new(AddNodeCommand)(m_pDataBase->getNode(m_uiParentGuid));
}

}}
