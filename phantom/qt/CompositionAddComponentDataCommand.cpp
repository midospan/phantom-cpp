/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "CompositionAddComponentDataCommand.h"
#include "CompositionAddComponentDataCommand.hxx"
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
    , const phantom::data& a_OwnerData
    , reflection::Expression* a_pCompositionExpression )
    : DataBaseCommand(a_pDataBase)
    , m_uiOwnerGuid(a_pDataBase->getGuid(a_OwnerData))
    , m_strTypeName(a_pType->getQualifiedDecoratedName())
    , m_strCompositionExpression(a_pCompositionExpression->getName())
{
    setName("Add new component data to '" + m_pDataBase->getDataAttributeValue(a_OwnerData, "name")+"'("+boost::lexical_cast<string>((void*)m_uiOwnerGuid)+")");
}

CompositionAddComponentDataCommand::CompositionAddComponentDataCommand( serialization::DataBase* a_pDataBase
    , const string& a_strTypeName
    , uint a_uiOwnerGuid
    , const string& a_strCompositionExpression )
    : DataBaseCommand(a_pDataBase)
    , m_uiOwnerGuid(a_uiOwnerGuid)
    , m_strTypeName(a_strTypeName)
    , m_strCompositionExpression(a_strCompositionExpression)
{
    auto d = m_pDataBase->getData(m_uiOwnerGuid);
    setName("Add new component data to '" + m_pDataBase->getDataAttributeValue(d, "name")+"'("+boost::lexical_cast<string>((void*)m_uiOwnerGuid)+")");
    setRedoChildExecutionPolicy(e_ChildExecutionPolicy_ForwardAfterParent);
    setUndoChildExecutionPolicy(e_ChildExecutionPolicy_ForwardAfterParent);
}

CompositionAddComponentDataCommand::~CompositionAddComponentDataCommand()
{

}


//================================================
// Operations
//================================================


void CompositionAddComponentDataCommand::redoReplayed()
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
    pCompositionClass->add(pComposition, &pAddress);
    phantom::deleteElement(pCompositionExpression);
}

void CompositionAddComponentDataCommand::undoReplayed()
{
    reflection::Expression* pCompositionExpression = phantom::expressionByName(m_strCompositionExpression);
    reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(pCompositionExpression->getValueType()->removeReference()->removeConst());
    void* pComposition = pCompositionExpression->loadEffectiveAddress();
    void* pComponent = nullptr;
    pCompositionClass->removeLast(pComposition, &pComponent);
    o_assert(pComponent);
    o_dynamic_delete pComponent;
    phantom::deleteElement(pCompositionExpression);
}

CompositionAddComponentDataCommand* CompositionAddComponentDataCommand::clone() const
{
    return o_new(CompositionAddComponentDataCommand)(m_pDataBase, m_strTypeName, m_uiOwnerGuid, m_strCompositionExpression);
}

string CompositionAddComponentDataCommand::generateComponentName( serialization::DataBase* a_pDataBase, phantom::data a_Component )
{
    void* pAddress = a_Component.address();
    reflection::Expression* pCompositionExpression = phantom::expressionByName(m_strCompositionExpression);
    reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(pCompositionExpression->getValueType()->removeReference()->removeConst());
    return nameOf(pCompositionExpression->getHatchedElement())+" - "+lexical_cast<string>(pCompositionClass->indexOf(pCompositionExpression->loadEffectiveAddress(), &pAddress));
}

}}
