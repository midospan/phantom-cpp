/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "AddDataCommand.h"
#include "AddDataCommand.hxx"
#include "UpdateComponentDataCommand.h"
#include <phantom/serialization/Node.h>
#include <phantom/serialization/TrashBin.h>
/* *********************************************** */
o_registerN((phantom, qt), AddDataCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================

AddDataCommand::AddDataCommand(reflection::Type* a_pType
    , uint guid
    , phantom::serialization::Node* a_pNode)
: UndoCommand()
, m_pDataBase(a_pNode->getOwnerDataBase())
, m_uiNodeGuid(a_pNode->getGuid())
, m_uiGuid(guid)
, m_strTypeName(a_pType->getQualifiedDecoratedName())
, m_bInitialized(false)
{
    o_assert(m_pDataBase);
}

AddDataCommand::AddDataCommand( const string& a_strTypeName
    , uint guid
    , phantom::serialization::Node* a_pNode )
    : UndoCommand()
    , m_pDataBase(a_pNode->getOwnerDataBase())
    , m_uiNodeGuid(a_pNode->getGuid())
    , m_uiGuid(guid)
    , m_strTypeName(a_strTypeName)
    , m_bInitialized(false)
{
    o_assert(m_pDataBase);
}

AddDataCommand::~AddDataCommand()
{

}


//================================================
// Operations
//================================================


void AddDataCommand::redo()
{
    if(!m_bInitialized)
    {
        serialization::Node* pParentNode = m_pDataBase->getNode(m_uiNodeGuid);
        o_assert(pParentNode);
        reflection::Type* pType = m_pDataBase->solveTypeByName(m_strTypeName);
        phantom::data d;
        o_assert(m_uiGuid != 0xffffffff);
        d = pParentNode->newData(pType, m_uiGuid);
        m_pDataBase->setDataAttributeValue(d, "name", nameOf(pType));
        pParentNode->saveData(d);
        pParentNode->saveIndex();
        m_bInitialized = true;
    }
    else 
    {
        vector<uint> guids;
        guids.push_back(m_uiGuid);
        m_pDataBase->getTrashbin()->restore(guids);
    }
}

void AddDataCommand::undo()
{
    vector<uint> guids;
    guids.push_back(m_uiGuid);
    m_pDataBase->getTrashbin()->add(guids);
}

UndoCommand* AddDataCommand::clone() const
{
    return o_new(AddDataCommand)(m_strTypeName, m_uiGuid, m_pDataBase->getNode(m_uiNodeGuid));
}

}}
