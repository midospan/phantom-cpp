/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "AggregationRemoveAggregateDataCommand.h"
#include "AggregationRemoveAggregateDataCommand.hxx"
#include <phantom/serialization/Node.h>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/AggregationClass.h>
#include <phantom/reflection/AggregationClass.hxx>
#include <phantom/reflection/ConstantExpression.h>
/* *********************************************** */
o_registerN((phantom, qt), AggregationRemoveAggregateDataCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================
    
AggregationRemoveAggregateDataCommand::AggregationRemoveAggregateDataCommand( serialization::DataBase* a_pDataBase
    , size_t a_uiIndex
    , reflection::Expression* a_pAggregationExpression )
    : DataBaseCommand(a_pDataBase)
    , m_uiGuid(0xffffffff)
    , m_uiIndex(a_uiIndex)
    , m_Modifiers(0)
    , m_strAggregationExpression(a_pAggregationExpression->getName())
{
}

AggregationRemoveAggregateDataCommand::AggregationRemoveAggregateDataCommand( serialization::DataBase* a_pDataBase
    , size_t a_uiIndex
    , const string& a_strAggregationExpression )
    : DataBaseCommand(a_pDataBase)
    , m_uiGuid(0xffffffff)
    , m_uiIndex(a_uiIndex)
    , m_Modifiers(0)
    , m_strAggregationExpression(a_strAggregationExpression)
{
}

AggregationRemoveAggregateDataCommand::~AggregationRemoveAggregateDataCommand()
{

}


//================================================
// Operations
//================================================


void AggregationRemoveAggregateDataCommand::record()
{
    reflection::Expression* pAggregationExpression = phantom::expressionByName(m_strAggregationExpression);
    reflection::AggregationClass* pAggregationClass = as<reflection::AggregationClass*>(pAggregationExpression->getValueType()->removeReference()->removeConst());
    void* pAddress = nullptr;
    void* pAggregation = pAggregationExpression->loadEffectiveAddress();
    pAggregationClass->get(pAggregation, m_uiIndex, &pAddress);
    pAggregationClass->remove(pAggregationExpression->loadEffectiveAddress(), m_uiIndex);
    m_uiGuid = m_pDataBase->getGuid(pAddress);
    o_assert(m_uiGuid != 0xffffffff);
    phantom::deleteElement(pAggregationExpression);
}

AggregationRemoveAggregateDataCommand* AggregationRemoveAggregateDataCommand::clone() const
{
    return o_new(AggregationRemoveAggregateDataCommand)(m_pDataBase, m_uiIndex, m_strAggregationExpression);
}

// string AggregationRemoveAggregateDataCommand::generateAggregateName( serialization::DataBase* a_pDataBase, phantom::data a_Aggregate )
// {
//     void* pAddress = a_Aggregate.address();
//     reflection::Expression* pAggregationExpression = phantom::expressionByName(m_strAggregationExpression);
//     reflection::AggregationClass* pAggregationClass = as<reflection::AggregationClass*>(pAggregationExpression->getValueType()->removeReference()->removeConst());
//     return nameOf(pAggregationExpression->getHatchedElement())+" - "+lexical_cast<string>(pAggregationClass->indexOf(pAggregationExpression->loadEffectiveAddress(), &pAddress));
// }

}}
