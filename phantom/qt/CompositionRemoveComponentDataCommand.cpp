/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "CompositionRemoveComponentDataCommand.h"
#include "CompositionRemoveComponentDataCommand.hxx"
#include <phantom/serialization/Node.h>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/CompositionClass.h>
#include <phantom/reflection/CompositionClass.hxx>
#include <phantom/reflection/ConstantExpression.h>
/* *********************************************** */
o_registerN((phantom, qt), CompositionRemoveComponentDataCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================
    
CompositionRemoveComponentDataCommand::CompositionRemoveComponentDataCommand( serialization::DataBase* a_pDataBase
    , size_t a_uiIndex
    , const phantom::data& a_OwnerData
    , reflection::Expression* a_pCompositionExpression )
    : DataBaseCommand(a_pDataBase)
    , m_uiOwnerGuid(a_pDataBase->getGuid(a_OwnerData))
    , m_strCompositionExpression(a_pCompositionExpression->getName())
    , m_uiIndex(a_uiIndex)
{
    setName("Remove component data from '" + m_pDataBase->getDataAttributeValue(a_OwnerData, "name")+"'("+boost::lexical_cast<string>((void*)m_uiOwnerGuid)+")");
}

CompositionRemoveComponentDataCommand::CompositionRemoveComponentDataCommand( serialization::DataBase* a_pDataBase
    , size_t a_uiIndex
    , uint a_uiOwnerGuid
    , const string& a_strCompositionExpression )
    : DataBaseCommand(a_pDataBase)
    , m_uiOwnerGuid(a_uiOwnerGuid)
    , m_strCompositionExpression(a_strCompositionExpression)
    , m_uiIndex(a_uiIndex)
{
    auto d = m_pDataBase->getData(m_uiOwnerGuid);
    setName("Remove component data from '" + m_pDataBase->getDataAttributeValue(d, "name")+"'("+boost::lexical_cast<string>((void*)m_uiOwnerGuid)+")");
}

CompositionRemoveComponentDataCommand::~CompositionRemoveComponentDataCommand()
{

}


//================================================
// Operations
//================================================


void CompositionRemoveComponentDataCommand::redoReplayed()
{
    reflection::Expression* pCompositionExpression = phantom::expressionByName(m_strCompositionExpression);
    reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(pCompositionExpression->getValueType()->removeReference()->removeConst());
    void* pComposition = pCompositionExpression->loadEffectiveAddress();
    void* pComponent = nullptr;
    pCompositionClass->get(pComposition, m_uiIndex, &pComponent);
    o_assert(pComponent);
    m_strTypeName = classOf(pComponent)->getQualifiedDecoratedName();
    pCompositionClass->remove(pComposition, m_uiIndex);
    phantom::deleteElement(pCompositionExpression);
}

void CompositionRemoveComponentDataCommand::undoReplayed()
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
    pCompositionClass->insert(pComposition, m_uiIndex, &pAddress);
    phantom::deleteElement(pCompositionExpression);
}

CompositionRemoveComponentDataCommand* CompositionRemoveComponentDataCommand::clone() const
{
    return o_new(CompositionRemoveComponentDataCommand)(m_pDataBase, m_uiIndex, m_uiOwnerGuid, m_strCompositionExpression);
}

string CompositionRemoveComponentDataCommand::generateComponentName( serialization::DataBase* a_pDataBase, phantom::data a_Component )
{
    void* pAddress = a_Component.address();
    reflection::Expression* pCompositionExpression = phantom::expressionByName(m_strCompositionExpression);
    reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(pCompositionExpression->getValueType()->removeReference()->removeConst());
    return nameOf(pCompositionExpression->getHatchedElement())+" - "+lexical_cast<string>(pCompositionClass->indexOf(pCompositionExpression->loadEffectiveAddress(), &pAddress));
}

}}
