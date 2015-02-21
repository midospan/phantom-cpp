/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/DataMemberInitializationStatement.h>
#include <phantom/reflection/DataMemberInitializationStatement.hxx>
#include <phantom/reflection/Expression.h>
/* *********************************************** */
o_registerN((phantom, reflection), DataMemberInitializationStatement);

o_namespace_begin(phantom, reflection) 

DataMemberInitializationStatement::DataMemberInitializationStatement( Expression* a_pThisExpression, DataMember* a_pDataMember, Expression* a_pRightExpression ) 
    : LValueInitializationStatement(a_pDataMember->getValueType(), a_pRightExpression)
    , m_pDataMember(a_pDataMember)
    , m_pThisExpression(a_pThisExpression)
{
    addElement(m_pThisExpression);
    if(m_pDataMember)
    {
        addReferencedElement(m_pDataMember);
    }
    else setInvalid();
}

DataMemberInitializationStatement::~DataMemberInitializationStatement()
{
    
}

DataMemberInitializationStatement* DataMemberInitializationStatement::clone() const
{
    return o_new(DataMemberInitializationStatement)(m_pThisExpression, m_pDataMember, m_pRightExpression);
}

void DataMemberInitializationStatement::internalEval() const
{
    byte* _this = nullptr;
    m_pThisExpression->internalEval(&_this);
    m_pRightExpression->internalEval(_this+m_pDataMember->getOffset());
    LValueInitializationStatement::internalEval();
}

Type* DataMemberInitializationStatement::getValueType() const
{
    return m_pDataMember->getValueType();
}

o_namespace_end(phantom, reflection)
