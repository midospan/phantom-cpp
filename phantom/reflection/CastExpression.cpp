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
#include <phantom/reflection/CastExpression.h>
#include <phantom/reflection/CastExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), CastExpression);

o_namespace_begin(phantom, reflection) 

CastExpression::CastExpression( Type* a_pCastType, Expression* a_pCastedExpression ) 
    : Expression(a_pCastType, "("+a_pCastType->getQualifiedDecoratedName()+")("+a_pCastedExpression->getName()+")", a_pCastedExpression->getModifiers())
    , m_pCastedExpression(a_pCastedExpression)
    , m_pTempValue(nullptr)
    , m_pIntermediateBuffer(nullptr)
{
    addElement(m_pCastedExpression);
    o_assert(a_pCastedExpression->getValueType()->isCopyable());
    if(NOT(a_pCastedExpression->hasValueStorage()))
    {
        m_pTempValue = a_pCastedExpression->getValueType()->allocate();
        m_pCastedExpression->getValueType()->construct(m_pTempValue);
        m_pCastedExpression->getValueType()->install(m_pTempValue);
        m_pCastedExpression->getValueType()->initialize(m_pTempValue);
    }
    reflection::ReferenceType* pRefCastType = a_pCastType->asReferenceType();
    if(pRefCastType AND m_pCastedExpression->getValueType()->asReferenceType() == nullptr AND pRefCastType->getReferencedType()->asConstType())
    {
        // Conversion from non-ref to const ref, need intermediate buffer
        Type* pType = pRefCastType->removeReference()->removeConst();
        m_pIntermediateBuffer = pType->allocate();
        pType->construct(m_pIntermediateBuffer);
        pType->install(m_pIntermediateBuffer);
        pType->initialize(m_pIntermediateBuffer);
    }
}

CastExpression::~CastExpression()
{
    
}

void CastExpression::getValue( void* a_pDest ) const
{
    if(m_pTempValue)
    {
        m_pCastedExpression->getValue(m_pTempValue);
    }
    if(m_pIntermediateBuffer)
    {
        m_pCastedExpression->getValueType()->convertValueTo(getValueType()->removeReference()->removeConst(), m_pIntermediateBuffer, 
            m_pTempValue 
                ? m_pTempValue 
                : m_pCastedExpression->getValueStorageAddress());
        *((void**)a_pDest) = m_pIntermediateBuffer;
    }
    else 
    {
        m_pCastedExpression->getValueType()->convertValueTo(getValueType(), a_pDest, m_pTempValue 
                                                                                    ? m_pTempValue 
                                                                                    : m_pCastedExpression->getValueStorageAddress());
    }
}

void CastExpression::terminate()
{
    if(m_pTempValue)
    {
        m_pCastedExpression->getValueType()->terminate(m_pTempValue);
        m_pCastedExpression->getValueType()->uninstall(m_pTempValue);
        m_pCastedExpression->getValueType()->destroy(m_pTempValue);
        m_pCastedExpression->getValueType()->deallocate(m_pTempValue);
    }
    Expression::terminate();
}

CastExpression* CastExpression::clone() const
{
    return o_new(CastExpression)(m_pValueType, m_pCastedExpression->clone());
}

o_namespace_end(phantom, reflection)
