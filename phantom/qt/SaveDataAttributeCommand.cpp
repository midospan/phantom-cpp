/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "SaveDataAttributeCommand.h"
#include "SaveDataAttributeCommand.hxx"
#include <phantom/serialization/Node.h>
/* *********************************************** */
o_registerN((phantom, qt), SaveDataAttributeCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================

SaveDataAttributeCommand::SaveDataAttributeCommand(phantom::serialization::Node* a_pNode, const phantom::data& a_Data)
: UndoCommand()
, m_pDataBase(a_pNode->getDataBase())
, m_uiParentGuid(a_pNode->getGuid())
, m_uiGuid(a_pNode->getDataBase()->getGuid(a_Data))
{
    o_assert(m_pDataBase);
    setName("Save attributes of data '"+boost::lexical_cast<string>((void*)m_uiGuid)+"'");
}

SaveDataAttributeCommand::~SaveDataAttributeCommand()
{

}


//================================================
// Operations
//================================================


void SaveDataAttributeCommand::redo()
{
    serialization::Node* pParentNode = m_pDataBase->getNode(m_uiParentGuid);
    o_assert(pParentNode);
    pParentNode->saveDataAttributes(m_pDataBase->getData(m_uiGuid));
}

void SaveDataAttributeCommand::undo()
{
    serialization::Node* pParentNode = m_pDataBase->getNode(m_uiParentGuid);
    o_assert(pParentNode);
    pParentNode->saveDataAttributes(m_pDataBase->getData(m_uiGuid));
}

SaveDataAttributeCommand* SaveDataAttributeCommand::clone() const
{
    return o_new(SaveDataAttributeCommand)(m_pDataBase->getNode(m_uiParentGuid), m_pDataBase->getData(m_uiGuid));
}

}}
