/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "UnloadNodeCommand.h"
#include "UnloadNodeCommand.hxx"
#include <phantom/serialization/Node.h>
#include <phantom/serialization/DataStateBase.h>
/* *********************************************** */
o_registerN((phantom, qt), UnloadNodeCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================

UnloadNodeCommand::UnloadNodeCommand(phantom::serialization::Node* a_pNode)
: DataBaseCommand(a_pNode->getDataBase())
, m_uiGuid(a_pNode->getGuid())
{
    o_assert(m_pDataBase);
    o_assert(m_uiGuid != 0xffffffff);
    setName("Unload node '" + m_pDataBase->getNodeAttributeValue(a_pNode, "name")+"'("+boost::lexical_cast<string>((void*)m_uiGuid)+")");
}

UnloadNodeCommand::~UnloadNodeCommand()
{

}


//================================================
// Operations
//================================================

void UnloadNodeCommand::redoReplayed()
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

void UnloadNodeCommand::undoReplayed()
{
    serialization::Node* pNode = m_pDataBase->getNode(m_uiGuid);
    pNode->load();
}

UnloadNodeCommand* UnloadNodeCommand::clone() const
{
    return o_new(UnloadNodeCommand)(m_pDataBase->getNode(m_uiGuid));
}

}}
