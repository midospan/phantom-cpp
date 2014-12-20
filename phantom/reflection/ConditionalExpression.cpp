/*
    This file is part of PHANTOM
         P reprocessed 
         H igh-level 
         A llocator 
         N ested state-machines and 
         T emplate 
         O riented 
         M eta-programming

    For the latest infos and sources, see http://code.google.com/p/phantom-cpp

    Copyright (C) 2008-2011 by Vivien MILLET

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE
*/

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/ConditionalExpression.h>
#include <phantom/reflection/ConditionalExpression.hxx>
#include <phantom/reflection/ConstantExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), ConditionalExpression);

o_namespace_begin(phantom, reflection) 

static Type* deduceValueType(Expression* a_pThenExpression, Expression* a_pElseExpression)
{
    Type* pThenType = a_pThenExpression->getValueType();
    Type* pElseType = a_pElseExpression->getValueType();
    // If both expressions are of the same type, the result is of that type.
    if(pThenType == pElseType)
    {
        return pThenType;
    }
    // If both expressions are of arithmetic or enumeration types, the usual arithmetic conversions (covered in Arithmetic Conversions) are performed to convert them to a common type.
    if(pThenType->asArithmeticType() AND pElseType->asArithmeticType())
    {
        return pThenType->getTypeId() > pElseType->getTypeId() ? pThenType : pElseType;
    }
    // If both expressions are of pointer types or if one is a pointer type and the other is a constant expression that evaluates to 0, pointer conversions are performed to convert them to a common type.
    if(pThenType->asDataPointerType() 
        AND a_pElseExpression->asConstantExpression() 
        AND a_pElseExpression->asConstantExpression()->getConstant()->isIntegralZero())
    {
        return pThenType;
    }
    if(pElseType->asDataPointerType() 
        AND a_pThenExpression->asConstantExpression() 
        AND a_pThenExpression->asConstantExpression()->getConstant()->isIntegralZero())
    {
        return pElseType;
    }
    if(pThenType->asDataPointerType() AND pElseType->asDataPointerType())
    {
        Type* pCommon = pThenType->asDataPointerType()->getPointedType()->getCommonAncestor(pElseType->asDataPointerType()->getPointedType());
        if(pCommon == nullptr) return typeOf<void*>();
        return pCommon->pointerType();
    }
    // If both expressions are of reference types, reference conversions are performed to convert them to a common type.
    if(pThenType->asReferenceType() AND pElseType->asReferenceType())
    {
        Type* pCommon = pThenType->asReferenceType()->getReferencedType()->getCommonAncestor(pElseType->asReferenceType()->getReferencedType());
        if(pCommon == nullptr) return nullptr;
        return pCommon->referenceType();
    }
    return nullptr;
    // If both expressions are of type void, the common type is type void.
    // If both expressions are of a given class type, the common type is that class type.
}

ConditionalExpression::ConditionalExpression(Expression* a_pTestExpression, Expression* a_pThenExpression, Expression* a_pElseExpression)
    : Expression(deduceValueType(a_pThenExpression, a_pElseExpression), 0)
    , m_pTestExpression(a_pTestExpression)
    , m_pThenExpression(a_pThenExpression)
    , m_pElseExpression(a_pElseExpression)
{
    if(m_pTestExpression)
    {
        m_pConvertedTestExpression = m_pTestExpression->implicitCast(typeOf<bool>());
        if(m_pConvertedTestExpression)
        {
            addSubExpression(m_pConvertedTestExpression);
        }
        else 
        {
            addSubExpression(m_pTestExpression);
            setInvalid();
        }
    }
    else setInvalid();

    if(m_pThenExpression)
    {
        m_pConvertedThenExpression = m_pThenExpression->implicitCast(m_pValueType);
        if(m_pConvertedThenExpression)
        {
            addSubExpression(m_pConvertedThenExpression);
        }
        else 
        {
            addSubExpression(m_pThenExpression);
            setInvalid();
        }
    }
    else setInvalid();

    if(m_pElseExpression)
    {
        m_pConvertedElseExpression = m_pElseExpression->implicitCast(m_pValueType);
        if(m_pConvertedElseExpression)
        {
            addSubExpression(m_pConvertedElseExpression);
        }
        else 
        {
            addSubExpression(m_pElseExpression);
            setInvalid();
        }
    }
    else setInvalid();
}

void ConditionalExpression::internalEval( void* a_pDest ) const
{
    bool result = false;
    m_pConvertedTestExpression->load(&result);
    if(result)
    {
        m_pConvertedThenExpression->internalEval(a_pDest);
    }
    else 
    {
        m_pConvertedElseExpression->internalEval(a_pDest);
    }
}

ConditionalExpression* ConditionalExpression::clone() const
{
    return o_new(ConditionalExpression)(m_pTestExpression, m_pThenExpression, m_pElseExpression);
}


o_namespace_end(phantom, reflection)
