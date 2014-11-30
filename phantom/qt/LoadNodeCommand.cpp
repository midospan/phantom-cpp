/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "LoadNodeCommand.h"
#include "LoadNodeCommand.hxx"
#include <phantom/serialization/Node.h>
#include <phantom/serialization/DataStateBase.h>
/* *********************************************** */
o_registerN((phantom, qt), LoadNodeCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================

LoadNodeCommand::LoadNodeCommand(phantom::serialization::Node* a_pNode)
: DataBaseCommand(a_pNode->getDataBase())
, m_uiGuid(a_pNode->getGuid())
{
    o_assert(m_uiGuid != 0xffffffff);
    setName("Load node '" + m_pDataBase->getNodeAttributeValue(a_pNode, "name")+"'("+boost::lexical_cast<string>((void*)m_uiGuid)+")");
}

LoadNodeCommand::~LoadNodeCommand()
{

}


//================================================
// Operations
//================================================

void LoadNodeCommand::redoReplayed()
{
    serialization::Node* pNode = m_pDataBase->getNode(m_uiGuid);
    o_assert(pNode);
    o_assert(pNode->isUnloaded());
    o_assert(pNode->getParentNode() == nullptr OR pNode->getParentNode()->isLoaded());
    o_assert(pNode->canLoad());
    pNode->load();
}

void LoadNodeCommand::undoReplayed()
{
    serialization::Node* pNode = m_pDataBase->getNode(m_uiGuid);
    pNode->unload();
}

LoadNodeCommand* LoadNodeCommand::clone() const
{
    return o_new(LoadNodeCommand)(m_pDataBase->getNode(m_uiGuid));
}

}}
