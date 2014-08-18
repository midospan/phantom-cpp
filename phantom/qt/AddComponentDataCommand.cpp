/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "AddComponentDataCommand.h"
#include "AddComponentDataCommand.hxx"
#include <phantom/serialization/Node.h>
/* *********************************************** */
o_registerN((phantom, qt), AddComponentDataCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================
    
AddComponentDataCommand::AddComponentDataCommand( serialization::DataBase* a_pDataBase, reflection::Type* a_pType, uint a_uiGuid, const phantom::data& a_OwnerData )
    : UndoCommand()
    , m_pDataBase(a_pDataBase)
    , m_uiGuid(a_uiGuid)
    , m_uiOwnerGuid(a_pDataBase->getGuid(a_OwnerData))
    , m_strTypeName(a_pType->getQualifiedDecoratedName())
{
    o_assert(m_pDataBase);
    setName("Add new component data to '" + m_pDataBase->getDataAttributeValue(a_OwnerData, "name")+"'("+boost::lexical_cast<string>((void*)m_uiOwnerGuid)+")");
}

AddComponentDataCommand::~AddComponentDataCommand()
{

}


//================================================
// Operations
//================================================


void AddComponentDataCommand::redo()
{
    phantom::data ownerData = m_pDataBase->getData(m_uiOwnerGuid);
    o_assert(!ownerData.isNull());
    serialization::Node* pNode = m_pDataBase->getNode(ownerData);
    o_assert(pNode);
    reflection::Type* pType = m_pDataBase->solveTypeByName(m_strTypeName);
    o_assert(pType);
    pNode->addComponentData(phantom::data(pType->newInstance(), pType), m_uiGuid, ownerData, "");
}

void AddComponentDataCommand::undo()
{
    phantom::data ownerData = m_pDataBase->getData(m_uiOwnerGuid);
    o_assert(!ownerData.isNull());
    serialization::Node* pNode = m_pDataBase->getNode(ownerData);
    o_assert(pNode);
    pNode->removeComponentData(m_pDataBase->getData(m_uiGuid), ownerData);
}

}}
