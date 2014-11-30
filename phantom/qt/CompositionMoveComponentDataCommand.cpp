/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "CompositionMoveComponentDataCommand.h"
#include "CompositionMoveComponentDataCommand.hxx"
#include <phantom/serialization/Node.h>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/CompositionClass.h>
#include "ComponentReferenceExpressionChangeCommand.h"
/* *********************************************** */
o_registerN((phantom, qt), CompositionMoveComponentDataCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================
    
CompositionMoveComponentDataCommand::CompositionMoveComponentDataCommand( serialization::DataBase* a_pDataBase
    , const phantom::data& a_OwnerData
    , reflection::Expression* a_pCompositionExpression
    , size_t oldIndex
    , size_t newIndex)
    : DataBaseCommand(a_pDataBase)
    , m_uiOwnerGuid(a_pDataBase->getGuid(a_OwnerData))
    , m_strCompositionExpression(a_pCompositionExpression->getName())
    , m_uiNewIndex(newIndex)
    , m_uiOldIndex(oldIndex)
{
    setName("Move component data from index '"+lexical_cast<string>(oldIndex)+"' to '"+lexical_cast<string>(newIndex)+"' in "+ m_pDataBase->getDataAttributeValue(a_OwnerData, "name")+"'("+lexical_cast<string>((void*)m_uiOwnerGuid)+")");
}

CompositionMoveComponentDataCommand::CompositionMoveComponentDataCommand( serialization::DataBase* a_pDataBase
    , uint a_uiOwnerGuid
    , const string& a_strCompositionExpression
    , size_t oldIndex
    , size_t newIndex )
    : DataBaseCommand(a_pDataBase)
    , m_uiOwnerGuid(a_uiOwnerGuid)
    , m_strCompositionExpression(a_strCompositionExpression)
    , m_uiNewIndex(newIndex)
    , m_uiOldIndex(oldIndex)
{
    auto d = m_pDataBase->getData(m_uiOwnerGuid);
    setName("Move component data from index '"+lexical_cast<string>(oldIndex)+"' to '"+lexical_cast<string>(newIndex)+"' in "+ m_pDataBase->getDataAttributeValue(m_pDataBase->getData(m_uiOwnerGuid), "name")+"'("+boost::lexical_cast<string>((void*)m_uiOwnerGuid)+")");
}

CompositionMoveComponentDataCommand::~CompositionMoveComponentDataCommand()
{

}

void CompositionMoveComponentDataCommand::record()
{
    reflection::Expression* pCompositionExpression = phantom::expressionByName(m_strCompositionExpression);
    reflection::CompositionClass* pCompositionClass = as<reflection::CompositionClass*>(pCompositionExpression->getValueType()->removeReference()->removeConst());
    void* pComposition = pCompositionExpression->loadEffectiveAddress();
    pCompositionClass->move(pComposition, m_uiOldIndex, m_uiNewIndex);
    phantom::deleteElement(pCompositionExpression);
}

CompositionMoveComponentDataCommand* CompositionMoveComponentDataCommand::clone() const
{
    return o_new(CompositionMoveComponentDataCommand)(m_pDataBase, m_uiOwnerGuid, m_strCompositionExpression, m_uiOldIndex, m_uiNewIndex);
}

}}
