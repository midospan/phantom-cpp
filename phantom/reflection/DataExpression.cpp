/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/DataExpression.h>
#include <phantom/reflection/DataExpression.hxx>
#include <phantom/reflection/ConstantExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), DataExpression);

o_namespace_begin(phantom, reflection) 

static Type* deduce_data_type(serialization::DataBase* a_pDataBase, ConstantExpression* a_pGuidExpression)
{
    if(a_pDataBase == nullptr) return nullptr;
    phantom::data d = a_pDataBase->getData(a_pGuidExpression->get().as<uint>());
    return d.isNull() ? nullptr : d.type()->lvalueReferenceType();
}

DataExpression::DataExpression(serialization::DataBase* a_pDataBase, ConstantExpression* a_pGuidExpression)
    : Expression(deduce_data_type(a_pDataBase, a_pGuidExpression))
                , m_pGuidExpression((a_pGuidExpression AND a_pGuidExpression->getOwner()) 
                        ? a_pGuidExpression->clone() 
                        : a_pGuidExpression)
    , m_pDataBase(a_pDataBase)
{
    if(m_pDataBase == nullptr)
        setInvalid();
    if(m_pGuidExpression->getValueType() != typeOf<size_t>())
    {
        setInvalid();
    }
    addSubExpression((Expression*&)m_pGuidExpression);
}

void DataExpression::internalEval( void* a_pDest ) const
{
    uint value = 0;
    m_pGuidExpression->load(&value);
    *((void**)a_pDest) = m_pDataBase->getData(value).address(); 
}

DataExpression* DataExpression::clone() const
{
    return o_new(DataExpression)(m_pDataBase, m_pGuidExpression);
}

void* DataExpression::evalStorage() const
{
    internalEval((void*)&m_Buffer);
    return (void*)&m_Buffer;
}

o_namespace_end(phantom, reflection)
