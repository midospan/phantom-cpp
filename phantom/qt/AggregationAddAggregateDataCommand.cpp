/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "AggregationAddAggregateDataCommand.h"
#include "AggregationAddAggregateDataCommand.hxx"
#include <phantom/serialization/Node.h>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/AggregationClass.h>
#include <phantom/reflection/AggregationClass.hxx>
#include <phantom/reflection/ConstantExpression.h>
/* *********************************************** */
o_registerN((phantom, qt), AggregationAddAggregateDataCommand);

namespace phantom { namespace qt {


//================================================
// Constructors / Destructor
//================================================
    
AggregationAddAggregateDataCommand::AggregationAddAggregateDataCommand( serialization::DataBase* a_pDataBase
    , uint a_uiGuid
    , reflection::Expression* a_pAggregationExpression )
    : DataBaseCommand(m_pDataBase)
    , m_uiGuid(a_uiGuid)
    , m_Modifiers(0)
    , m_strAggregationExpression(a_pAggregationExpression->getName())
{

}

AggregationAddAggregateDataCommand::AggregationAddAggregateDataCommand( serialization::DataBase* a_pDataBase
    , uint a_uiGuid
    , const string& a_strAggregationExpression )
    : DataBaseCommand(m_pDataBase)
    , m_uiGuid(a_uiGuid)
    , m_Modifiers(0)
    , m_strAggregationExpression(a_strAggregationExpression)
{

}

AggregationAddAggregateDataCommand::~AggregationAddAggregateDataCommand()
{

}


//================================================
// Operations
//================================================

void AggregationAddAggregateDataCommand::record()
{
    phantom::data d = m_pDataBase->getData(m_uiGuid);
    reflection::Expression* pAggregationExpression = phantom::expressionByName(m_strAggregationExpression);
    reflection::AggregationClass* pAggregationClass = as<reflection::AggregationClass*>(pAggregationExpression->getValueType()->removeReference()->removeConst());
    void* pAddress = d.type()->cast(pAggregationClass->getAggregateClass(), d.address());
    void* pAggregation = pAggregationExpression->loadEffectiveAddress();
    size_t count = pAggregationClass->count(pAggregation);
    pAggregationClass->add(pAggregationExpression->loadEffectiveAddress(), &pAddress);
    phantom::deleteElement(pAggregationExpression);
}

AggregationAddAggregateDataCommand* AggregationAddAggregateDataCommand::clone() const
{
    return o_new(AggregationAddAggregateDataCommand)(m_pDataBase, m_uiGuid, m_strAggregationExpression);
}

}}
