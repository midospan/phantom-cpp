/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/DataMemberPointerAdjustmentExpression.h>
#include <phantom/reflection/DataMemberPointerAdjustmentExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), DataMemberPointerAdjustmentExpression);

o_namespace_begin(phantom, reflection) 

DataMemberPointerAdjustmentExpression::DataMemberPointerAdjustmentExpression( Type* a_pOutputPointerType, Expression* a_pPointerExpression, ptrdiff_t a_iOffset ) 
    : Expression(a_pOutputPointerType)
    , m_pPointerExpression(a_pPointerExpression)
    , m_iOffset(a_iOffset)
{
    o_assert(m_iOffset != 0, "adjustment is not identity and offset must have non zero value");
    if(m_pPointerExpression == nullptr)
    {
        setInvalid();
    }
}

DataMemberPointerAdjustmentExpression::~DataMemberPointerAdjustmentExpression()
{
    
}

void DataMemberPointerAdjustmentExpression::internalEval( void* a_pDest ) const
{
    ptrdiff_t* ppDest = (ptrdiff_t*)a_pDest;
    m_pPointerExpression->internalEval(ppDest);
    *ppDest+=m_iOffset;
}

DataMemberPointerAdjustmentExpression* DataMemberPointerAdjustmentExpression::clone() const
{
    return o_new(DataMemberPointerAdjustmentExpression)(static_cast<DataMemberPointerType*>(m_pValueType), m_pPointerExpression, m_iOffset);
}

o_namespace_end(phantom, reflection)
