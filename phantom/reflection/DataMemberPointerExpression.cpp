/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "DataMemberPointerExpression.h"
#include "DataMemberPointerExpression.hxx"
#include "Compiler.h"
/* *********************************************** */
o_registerN((phantom, reflection), DataMemberPointerExpression);

o_namespace_begin(phantom, reflection)
    
DataMemberPointerExpression::DataMemberPointerExpression( DataMemberPointerType* a_pDataMemberPointerType, Expression* a_pObjectExpression, Expression* a_pMemberExpression ) 
    : Expression(a_pDataMemberPointerType->getValueType()->lvalueReferenceType())
    , m_pDataMemberPointerType(a_pDataMemberPointerType)
    , m_pObjectExpression(a_pObjectExpression)
    , m_pMemberExpression(a_pMemberExpression)
{        
    if(m_pObjectExpression)
    {
        addSubExpression(m_pObjectExpression);
        if(m_pObjectExpression->getValueType() == nullptr 
            OR NOT(m_pObjectExpression->hasEffectiveAddress()))
            setInvalid();
    }
    else setInvalid();
}

DataMemberPointerExpression::~DataMemberPointerExpression() 
{

}

o_terminate_cpp(DataMemberPointerExpression)
{

}

void DataMemberPointerExpression::internalEval( void* a_pDest ) const
{
    void* pMemberBuffer = m_pDataMemberPointerType->newInstance();
    m_pMemberExpression->load(pMemberBuffer);
    *(void**)a_pDest = m_pDataMemberPointerType->getAddress(pMemberBuffer, m_pObjectExpression->loadEffectiveAddress());
    m_pDataMemberPointerType->deleteInstance(pMemberBuffer);
}

DataMemberPointerExpression* DataMemberPointerExpression::clone() const
{
    return o_new(DataMemberPointerExpression)(m_pDataMemberPointerType, m_pObjectExpression, m_pMemberExpression);
}

o_namespace_end(phantom, reflection)
