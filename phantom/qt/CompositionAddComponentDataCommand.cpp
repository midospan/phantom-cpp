/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "CompositionAddComponentDataCommand.h"
#include "CompositionAddComponentDataCommand.hxx"
#include "UpdateComponentDataCommand.h"
#include <phantom/serialization/Node.h>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/CompositionClass.h>
#include <phantom/reflection/CompositionClass.hxx>
#include <phantom/reflection/ConstantExpression.h>
/* *********************************************** */
o_registerN((phantom, qt), CompositionAddComponentDataCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================
    
CompositionAddComponentDataCommand::CompositionAddComponentDataCommand( serialization::DataBase* a_pDataBase
    , reflection::Type* a_pType
    , uint a_uiGuid
    , const phantom::data& a_OwnerData
    , reflection::Expression* a_pCompositionExpression )
    : UndoCommand()
    , m_pDataBase(a_pDataBase)
    , m_uiGuid(a_uiGuid)
    , m_uiOwnerGuid(a_pDataBase->getGuid(a_OwnerData))
    , m_strTypeName(a_pType->getQualifiedDecoratedName())
    , m_Modifiers(0)
    , m_strCompositionExpression(a_pCompositionExpression->getName())
{
    o_assert(m_pDataBase);
    setName("Add new component data to '" + m_pDataBase->getDataAttributeValue(a_OwnerData, "name")+"'("+boost::lexical_cast<string>((void*)m_uiOwnerGuid)+")");
    UpdateComponentDataCommand* pUpdateComponentDataCommand = o_new(UpdateComponentDataCommand)(m_pDataBase, a_OwnerData);
    pUpdateComponentDataCommand->setNamerDelegate(UpdateComponentDataCommand::namer_delegate(this, &CompositionAddComponentDataCommand::generateComponentName));
    pushCommand(pUpdateComponentDataCommand);
    setRedoChildExecutionPolicy(e_ChildExecutionPolicy_ForwardAfterParent);
    setUndoChildExecutionPolicy(e_ChildExecutionPolicy_ForwardAfterParent);
}

CompositionAddComponentDataCommand::CompositionAddComponentDataCommand( serialization::DataBase* a_pDataBase
    , const string& a_strTypeName
    , uint a_uiGuid
    , uint a_uiOwnerGuid
    , const string& a_strCompositionExpression )
    : UndoCommand()
    , m_pDataBase(a_pDataBase)
    , m_uiGuid(a_uiGuid)
    , m_uiOwnerGuid(a_uiOwnerGuid)
    , m_strTypeName(a_strTypeName)
    , m_Modifiers(0)
    , m_strCompositionExpression(a_strCompositionExpression)
{
    o_assert(m_pDataBase);
    auto d = m_pDataBase->getData(m_uiOwnerGuid);
    setName("Add new component data to '" + m_pDataBase->getDataAttributeValue(d, "name")+"'("+boost::lexical_cast<string>((void*)m_uiOwnerGuid)+")");
    UpdateComponentDataCommand* pUpdateComponentDataCommand = o_new(UpdateComponentDataCommand)(m_pDataBase, d);
    pUpdateComponentDataCommand->setNamerDelegate(UpdateComponentDataCommand::namer_delegate(this, &CompositionAddComponentDataCommand::generateComponentName));
    pushCommand(pUpdateComponentDataCommand);
    setRedoChildExecutionPolicy(e_ChildExecutionPolicy_ForwardAfterParent);
    setUndoChildExecutionPolicy(e_ChildExecutionPolicy_ForwardAfterParent);
}

CompositionAddComponentDataCommand::~CompositionAddComponentDataCommand()
{

}


//================================================
// Operations
//================================================


void CompositionAddComponentDataCommand::redo()
{
    reflection::Type* pType = m_pDataBase->solveTypeByName(m_strTypeName);
    o_assert(pType);
    phantom::data owner = m_pDataBase->getData(m_uiOwnerGuid);
    o_assert(!owner.isNull());
    serialization::Node* pNode = m_pDataBase->getNode(owner);
    void* pAddress = pType->newInstance();
    phantom::data d(pAddress, pType);
    reflection::Expression* pCompositionExpression = phantom::expressionByName(m_strCompositionExpression);
    reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(pCompositionExpression->getValueType()->removeReference()->removeConst());
    pAddress = pType->cast(pCompositionClass->getComponentClass(), pAddress);
    void* pComposition = pCompositionExpression->loadEffectiveAddress();
    size_t count = pCompositionClass->count(pComposition);
    pCompositionClass->add(pCompositionExpression->loadEffectiveAddress(), &pAddress);
    reflection::CompositionClass::InsertRemoveExpression* pInsertRemoveExpression = o_new(reflection::CompositionClass::InsertRemoveExpression)(pCompositionExpression, o_new(reflection::ConstantExpression)(phantom::constant<size_t>(count), nullptr, true), pCompositionClass);
    pNode->addComponentData(d, m_uiGuid, owner, pInsertRemoveExpression->getName(), 0);
    phantom::deleteElement(pInsertRemoveExpression);
}

void CompositionAddComponentDataCommand::undo()
{
    phantom::data owner = m_pDataBase->getData(m_uiOwnerGuid);
    o_assert(!owner.isNull());
    reflection::Expression* pCompositionExpression = phantom::expressionByName(m_strCompositionExpression);
    reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(pCompositionExpression->getValueType()->removeReference()->removeConst());
    void* pAddress = nullptr;
    pCompositionClass->removeLast(pCompositionExpression->loadEffectiveAddress(), &pAddress);
    serialization::Node* pNode = m_pDataBase->getNode(owner);
    pNode->removeComponentData(pAddress, owner);
    phantom::deleteElement(pCompositionExpression);
}

CompositionAddComponentDataCommand* CompositionAddComponentDataCommand::clone() const
{
    return o_new(CompositionAddComponentDataCommand)(m_pDataBase, m_strTypeName, m_uiGuid, m_uiOwnerGuid, m_strCompositionExpression);
}

string CompositionAddComponentDataCommand::generateComponentName( serialization::DataBase* a_pDataBase, phantom::data a_Component )
{
    void* pAddress = a_Component.address();
    reflection::Expression* pCompositionExpression = phantom::expressionByName(m_strCompositionExpression);
    reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(pCompositionExpression->getValueType()->removeReference()->removeConst());
    return nameOf(pCompositionExpression->getHatchedElement())+" - "+lexical_cast<string>(pCompositionClass->indexOf(pCompositionExpression->loadEffectiveAddress(), &pAddress));
}

}}
