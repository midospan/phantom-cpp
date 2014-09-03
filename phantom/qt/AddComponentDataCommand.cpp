/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "AddComponentDataCommand.h"
#include "AddComponentDataCommand.hxx"
#include "UpdateComponentDataCommand.h"
#include <phantom/serialization/Node.h>
#include <phantom/reflection/Expression.h>
/* *********************************************** */
o_registerN((phantom, qt), AddComponentDataCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================
    
AddComponentDataCommand::AddComponentDataCommand( serialization::DataBase* a_pDataBase, reflection::Type* a_pType, const phantom::data& a_OwnerData, reflection::Expression* a_pReferenceExpression )
    : UndoCommand()
    , m_pDataBase(a_pDataBase)
    , m_uiGuid(0xffffffff)
    , m_uiOwnerGuid(a_pDataBase->getGuid(a_OwnerData))
    , m_strTypeName(a_pType->getQualifiedDecoratedName())
    , m_Modifiers(0)
    , m_strReferenceExpression(a_pReferenceExpression->getName())
{
    o_assert(m_pDataBase);
    setName("Add new component data to '" + m_pDataBase->getDataAttributeValue(a_OwnerData, "name")+"'("+boost::lexical_cast<string>((void*)m_uiOwnerGuid)+")");
    pushCommand(o_new(UpdateComponentDataCommand)(m_pDataBase, a_OwnerData));
}

AddComponentDataCommand::AddComponentDataCommand( serialization::DataBase* a_pDataBase, const string& a_strTypeName, uint a_uiOwnerGuid, const string& a_strReferenceExpression )
    : UndoCommand()
    , m_pDataBase(a_pDataBase)
    , m_uiGuid(0xffffffff)
    , m_uiOwnerGuid(a_uiOwnerGuid)
    , m_strTypeName(a_strTypeName)
    , m_Modifiers(0)
    , m_strReferenceExpression(a_strReferenceExpression)
{
    o_assert(m_pDataBase);
    auto d = m_pDataBase->getData(m_uiOwnerGuid);
    setName("Add new component data to '" + m_pDataBase->getDataAttributeValue(d, "name")+"'("+boost::lexical_cast<string>((void*)m_uiOwnerGuid)+")");
    pushCommand(o_new(UpdateComponentDataCommand)(m_pDataBase, d));
    setRedoChildExecutionPolicy(e_ChildExecutionPolicy_ForwardAfterParent);
    setUndoChildExecutionPolicy(e_ChildExecutionPolicy_ForwardAfterParent);
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
    void* pAddress = pType->newInstance();
    phantom::data d(pAddress, pType);
    reflection::Expression* pExpression = phantom::expressionByName(m_strReferenceExpression);
    o_assert(pExpression);
    pAddress = pType->cast(pExpression->getValueType()->removeReference()->removeConst(), pAddress);
    pExpression->store(&pAddress);
    phantom::deleteElement(pExpression);
}

void AddComponentDataCommand::undo()
{
    phantom::data ownerData = m_pDataBase->getData(m_uiOwnerGuid);
    o_assert(!ownerData.isNull());
    serialization::Node* pNode = m_pDataBase->getNode(ownerData);
    o_assert(pNode);
    reflection::Type* pType = m_pDataBase->solveTypeByName(m_strTypeName);
    o_assert(pType);
    void* pAddress = nullptr;
    reflection::Expression* pExpression = phantom::expressionByName(m_strReferenceExpression);
    o_assert(pExpression);
    pExpression->store(&pAddress);
    phantom::deleteElement(pExpression);
}

AddComponentDataCommand* AddComponentDataCommand::clone() const
{
    return o_new(AddComponentDataCommand)(m_pDataBase, m_strTypeName, m_uiOwnerGuid, m_strReferenceExpression);
}

}}
