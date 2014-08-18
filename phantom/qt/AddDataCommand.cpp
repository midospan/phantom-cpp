/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "AddDataCommand.h"
#include "AddDataCommand.hxx"
#include <phantom/serialization/Node.h>
/* *********************************************** */
o_registerN((phantom, qt), AddDataCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================

AddDataCommand::AddDataCommand(reflection::Type* a_pType, phantom::serialization::Node* a_pParentNode)
: UndoCommand()
, m_pDataBase(a_pParentNode->getOwnerDataBase())
, m_uiParentGuid(a_pParentNode->getGuid())
, m_uiGuid(0xffffffff)
, m_strTypeName(a_pType->getQualifiedDecoratedName())
{
    o_assert(m_pDataBase);
    setName("Add '"+nameOf(a_pType)+"' data to '" + m_pDataBase->getNodeAttributeValue(a_pParentNode, "name")+"'("+boost::lexical_cast<string>((void*)m_uiParentGuid)+")");
}

AddDataCommand::~AddDataCommand()
{

}


//================================================
// Operations
//================================================


void AddDataCommand::redo()
{
    serialization::Node* pParentNode = m_pDataBase->getNode(m_uiParentGuid);
    o_assert(pParentNode);
    reflection::Type* pType = m_pDataBase->solveTypeByName(m_strTypeName);
    phantom::data d;
    if(m_uiGuid != 0xffffffff)
    {
        d = pParentNode->newData(pType, m_uiGuid);
    }
    else
    {
        d = pParentNode->newData(pType);
        m_uiGuid = m_pDataBase->getGuid(d);
        o_assert(m_uiGuid != 0xffffffff);
    }
    m_pDataBase->setDataAttributeValue(d, "name", nameOf(pType));
    pParentNode->saveDataAttributes();
}

void AddDataCommand::undo()
{
    serialization::Node* pParentNode = m_pDataBase->getNode(m_uiParentGuid);
    o_assert(pParentNode);
    phantom::data d = m_pDataBase->getData(m_uiGuid);
    pParentNode->removeData(d);
    d.destroy();
}

}}
