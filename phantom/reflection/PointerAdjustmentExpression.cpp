/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/PointerAdjustmentExpression.h>
#include <phantom/reflection/PointerAdjustmentExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), PointerAdjustmentExpression);

o_namespace_begin(phantom, reflection) 

PointerAdjustmentExpression::PointerAdjustmentExpression( Type* a_pOutputPointerType, Expression* a_pPointerExpression, ptrdiff_t a_iOffset ) 
    : Expression(a_pOutputPointerType)
    , m_pPointerExpression(a_pPointerExpression)
    , m_iOffset(a_iOffset)
{
    o_assert(m_iOffset != 0, "adjustment is not identity and offset must have non zero value");
    if(m_pPointerExpression->getValueType()->asDataPointerType() == nullptr)
    {
        setInvalid();
    }
}

PointerAdjustmentExpression::~PointerAdjustmentExpression()
{
    
}

void PointerAdjustmentExpression::internalEval( void* a_pDest ) const
{
    byte** ppDest = (byte**)a_pDest;
    m_pPointerExpression->internalEval(ppDest);
    *ppDest+=m_iOffset;
}

PointerAdjustmentExpression* PointerAdjustmentExpression::clone() const
{
    return o_new(PointerAdjustmentExpression)(m_pValueType, m_pPointerExpression, m_iOffset);
}

o_namespace_end(phantom, reflection)
