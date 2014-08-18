/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "SaveNodeAttributeCommand.h"
#include "SaveNodeAttributeCommand.hxx"
#include <phantom/serialization/Node.h>
/* *********************************************** */
o_registerN((phantom, qt), SaveNodeAttributeCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================

SaveNodeAttributeCommand::SaveNodeAttributeCommand(phantom::serialization::Node* a_pNode)
: UndoCommand()
, m_pDataBase(a_pNode->getOwnerDataBase())
, m_uiGuid(a_pNode->getGuid())
{
    o_assert(m_pDataBase);
    setName("Save attributes of node '"+boost::lexical_cast<string>((void*)m_uiGuid)+"'");
}

SaveNodeAttributeCommand::~SaveNodeAttributeCommand()
{

}


//================================================
// Operations
//================================================


void SaveNodeAttributeCommand::redo()
{
    serialization::Node* pNode = m_pDataBase->getNode(m_uiGuid);
    o_assert(pNode);
    pNode->saveAttributes();
}

void SaveNodeAttributeCommand::undo()
{
    serialization::Node* pNode = m_pDataBase->getNode(m_uiGuid);
    o_assert(pNode);
    pNode->saveAttributes();
}

}}
