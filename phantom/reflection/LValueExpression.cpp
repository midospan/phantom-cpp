/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/LValueExpression.h>
#include <phantom/reflection/LValueExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), LValueExpression);

o_namespace_begin(phantom, reflection) 

Type* LValueExpressionTypeDeducer(Type* a_pInput)
{
    if(!a_pInput) return Type::Invalid();
    LValueReferenceType* pReferenceType = a_pInput->asLValueReferenceType();
    if(pReferenceType) return pReferenceType;
    RValueReferenceType* pRValueReferenceType = a_pInput->asRValueReferenceType();
    Type* pType = nullptr;
    if(pRValueReferenceType) 
    {
        pType = pRValueReferenceType->removeRValueReference()->lvalueReferenceType(); /// Named r-value references are l-values
    }
    else pType = a_pInput->lvalueReferenceType();
    return pType ? pType : Type::Invalid();
}

LValueExpression::LValueExpression(Type* a_pRValueType, modifiers_t modifiers)
    : Expression(LValueExpressionTypeDeducer(a_pRValueType))
    , m_pRValueType(a_pRValueType)
{
}

LValueExpression::LValueExpression(Type* a_pLValueType, Type* a_pRValueType, modifiers_t modifiers)
    : Expression(a_pLValueType)
    , m_pRValueType(a_pRValueType)
{
}

void LValueExpression::internalEval( void* a_pDest ) const
{
    void* pPhysicalAddress = internalEvalAddress();
    if(m_pRValueType->asLValueReferenceType()
        OR m_pRValueType->asRValueReferenceType())
    {
        /// ex: a local variable with a reference type : 
        /// int& variable = v;
        /// have an effectiveAddress of &variable, and not its address on the stack
        /// when you do variable = 5; it goes to *(&variable) 
        *(void**)a_pDest = *(void**)pPhysicalAddress;
    }
    else 
    {
        *(void**)a_pDest = pPhysicalAddress;
    }
}

o_namespace_end(phantom, reflection)
