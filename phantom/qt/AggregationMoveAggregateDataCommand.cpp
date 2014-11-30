/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "AggregationMoveAggregateDataCommand.h"
#include "AggregationMoveAggregateDataCommand.hxx"
#include <phantom/serialization/Node.h>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/AggregationClass.h>
/* *********************************************** */
o_registerN((phantom, qt), AggregationMoveAggregateDataCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================
    
AggregationMoveAggregateDataCommand::AggregationMoveAggregateDataCommand( serialization::DataBase* a_pDataBase
    , const phantom::data& a_OwnerData
    , reflection::Expression* a_pAggregationExpression
    , size_t oldIndex
    , size_t newIndex)
    : DataBaseCommand(a_pDataBase)
    , m_uiOwnerGuid(a_pDataBase->getGuid(a_OwnerData))
    , m_strAggregationExpression(a_pAggregationExpression->getName())
    , m_uiNewIndex(newIndex)
    , m_uiOldIndex(oldIndex)
{
    o_assert(m_pDataBase);
    setName("Move reference from index '"+lexical_cast<string>(oldIndex)+"' to '"+lexical_cast<string>(newIndex)+"' in "+ m_pDataBase->getDataAttributeValue(a_OwnerData, "name")+"'("+lexical_cast<string>((void*)m_uiOwnerGuid)+")");
}

AggregationMoveAggregateDataCommand::AggregationMoveAggregateDataCommand( serialization::DataBase* a_pDataBase
    , uint a_uiOwnerGuid
    , const string& a_strAggregationExpression
    , size_t oldIndex
    , size_t newIndex )
    : DataBaseCommand(a_pDataBase)
    , m_uiOwnerGuid(a_uiOwnerGuid)
    , m_strAggregationExpression(a_strAggregationExpression)
    , m_uiNewIndex(newIndex)
    , m_uiOldIndex(oldIndex)
{
    o_assert(m_pDataBase);
    auto d = m_pDataBase->getData(m_uiOwnerGuid);
    setName("Move reference from index '"+lexical_cast<string>(oldIndex)+"' to '"+lexical_cast<string>(newIndex)+"' in "+ m_pDataBase->getDataAttributeValue(m_pDataBase->getData(m_uiOwnerGuid), "name")+"'("+boost::lexical_cast<string>((void*)m_uiOwnerGuid)+")");
    
}

AggregationMoveAggregateDataCommand::~AggregationMoveAggregateDataCommand()
{

}

//================================================
// Operations
//================================================


void AggregationMoveAggregateDataCommand::record()
{
    reflection::Expression* pAggregationExpression = phantom::expressionByName(m_strAggregationExpression);
    reflection::AggregationClass* pAggregationClass = as<reflection::AggregationClass*>(pAggregationExpression->getValueType()->removeReference()->removeConst());
    pAggregationClass->move(pAggregationExpression->loadEffectiveAddress(), m_uiOldIndex, m_uiNewIndex);
    m_pDataBase->saveData(m_pDataBase->getData(m_uiOwnerGuid));
    phantom::deleteElement(pAggregationExpression);
}

AggregationMoveAggregateDataCommand* AggregationMoveAggregateDataCommand::clone() const
{
    return o_new(AggregationMoveAggregateDataCommand)(m_pDataBase, m_uiOwnerGuid, m_strAggregationExpression, m_uiOldIndex, m_uiNewIndex);
}

}}
