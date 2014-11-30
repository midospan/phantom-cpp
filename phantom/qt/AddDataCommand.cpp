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

AddDataCommand::AddDataCommand(reflection::Type* a_pType, phantom::serialization::Node* a_pNode)
    : DataBaseCommand(a_pNode->getDataBase())
    , m_uiNodeGuid(a_pNode->getGuid())
    , m_uiGuid(0xffffffff)
    , m_strTypeName(a_pType->getQualifiedDecoratedName())
{
}

AddDataCommand::AddDataCommand( const string& a_strTypeName, phantom::serialization::Node* a_pNode )
    : DataBaseCommand(a_pNode->getDataBase())
    , m_uiNodeGuid(a_pNode->getGuid())
    , m_uiGuid(0xffffffff)
    , m_strTypeName(a_strTypeName)
{
}

AddDataCommand::~AddDataCommand()
{

}


//================================================
// Operations
//================================================

UndoCommand* AddDataCommand::clone() const
{
    return o_new(AddDataCommand)(m_strTypeName, m_pDataBase->getNode(m_uiNodeGuid));
}

void AddDataCommand::redoReplayed()
{
    serialization::Node* pParentNode = m_pDataBase->getNode(m_uiNodeGuid);
    o_assert(pParentNode);
    reflection::Type* pType = m_pDataBase->solveTypeByName(m_strTypeName);
    phantom::data d = pParentNode->newData(pType);
    o_assert(m_uiGuid == 0xffffffff OR m_pDataBase->getGuid(d) == m_uiGuid, "Guid should have been restored the same as the first give to the data");
    m_uiGuid = m_pDataBase->getGuid(d);
    m_pDataBase->setDataAttributeValue(d, "name", nameOf(pType));
}

void AddDataCommand::undoReplayed()
{
    serialization::Node* pParentNode = m_pDataBase->getNode(m_uiNodeGuid);
    o_assert(pParentNode);
    reflection::Type* pType = m_pDataBase->solveTypeByName(m_strTypeName);
    auto d = m_pDataBase->getData(m_uiGuid);
    pParentNode->removeData(d);
    d.destroy();

}

}}
