/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "LoadNodeCommand.h"
#include "LoadNodeCommand.hxx"
#include <phantom/serialization/Node.h>
/* *********************************************** */
o_registerN((phantom, qt), LoadNodeCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================

LoadNodeCommand::LoadNodeCommand(phantom::serialization::Node* a_pNode)
: UndoCommand()
, m_pDataBase(a_pNode->getOwnerDataBase())
, m_uiGuid(a_pNode->getGuid())
{
    o_assert(m_pDataBase);
    o_assert(m_uiGuid != 0xffffffff);
    setName("Load node '" + m_pDataBase->getNodeAttributeValue(a_pNode, "name")+"'("+boost::lexical_cast<string>((void*)m_uiGuid)+")");
}

LoadNodeCommand::~LoadNodeCommand()
{

}


//================================================
// Operations
//================================================

void LoadNodeCommand::undo()
{
    serialization::Node* pNode = m_pDataBase->getNode(m_uiGuid);
#if !defined(_NDEBUG)
    o_assert(pNode);
    o_assert(pNode->isLoaded());
    o_assert(pNode->getParentNode() == nullptr OR pNode->getParentNode()->isLoaded());
    for(auto it = pNode->beginChildNodes(); it != pNode->endChildNodes(); ++it)
    {
        o_assert((*it)->isUnloaded());
    }
#endif
    pNode->unload();
}

void LoadNodeCommand::redo()
{
    serialization::Node* pNode = m_pDataBase->getNode(m_uiGuid);
    o_assert(pNode);
    o_assert(pNode->isUnloaded());
    o_assert(pNode->getParentNode() == nullptr OR pNode->getParentNode()->isLoaded());
    o_assert(pNode->canLoad());
    pNode->load();
}

}}
