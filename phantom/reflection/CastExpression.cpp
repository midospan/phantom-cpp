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

CastExpression::CastExpression( Type* a_pCastType, Expression* a_pCastedExpression, ECastType a_eCastType ) 
    : Expression(a_pCastType, a_pCastedExpression->getModifiers())
    , m_pCastedExpression(a_pCastedExpression)
    , m_pTempValue(nullptr)
    , m_pIntermediateBuffer(nullptr)
    , m_pIntermediateBufferType(nullptr)
    , m_eCastType(a_eCastType)
{
    if(((m_eCastType == e_implicit_cast) AND NOT(m_pCastedExpression->getValueType()->isImplicitlyConvertibleTo(getValueType())))
        OR ((m_eCastType != e_implicit_cast) AND NOT(m_pCastedExpression->getValueType()->isConvertibleTo(getValueType()))))
    {
        setInvalid();
    }
    construct();
}

CastExpression::~CastExpression()
{
    
}

void CastExpression::internalEval( void* a_pDest ) const
{
    if(m_pTempValue)
    {
        m_pCastedExpression->internalEval(m_pTempValue);
    }
    if(m_pIntermediateBuffer)
    {
        m_pCastedExpression->getValueType()->convertValueTo(m_pIntermediateBufferType, m_pIntermediateBuffer, 
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

o_terminate_cpp(CastExpression)
{
    if(m_pTempValue)
    {
        m_pCastedExpression->getValueType()->terminate(m_pTempValue);
        m_pCastedExpression->getValueType()->uninstall(m_pTempValue);
        m_pCastedExpression->getValueType()->destroy(m_pTempValue);
        m_pCastedExpression->getValueType()->deallocate(m_pTempValue);
        m_pTempValue = nullptr;
    }
    if(m_pIntermediateBuffer)
    {
        m_pIntermediateBufferType->terminate(m_pIntermediateBuffer);
        m_pIntermediateBufferType->uninstall(m_pIntermediateBuffer);
        m_pIntermediateBufferType->destroy(m_pIntermediateBuffer);
        m_pIntermediateBufferType->deallocate(m_pIntermediateBuffer);
        m_pIntermediateBuffer = nullptr;
    }
}

CastExpression* CastExpression::clone() const
{
    return o_new(CastExpression)(m_pValueType, m_pCastedExpression, m_eCastType);
}

void CastExpression::elementRemoved( LanguageElement* a_pElement )
{
    Expression::elementRemoved(a_pElement);
    if(m_pCastedExpression == a_pElement)
    {
        setInvalid();
        if(m_pTempValue)
        {
            m_pCastedExpression->getValueType()->terminate(m_pTempValue);
            m_pCastedExpression->getValueType()->uninstall(m_pTempValue);
            m_pCastedExpression->getValueType()->destroy(m_pTempValue);
            m_pCastedExpression->getValueType()->deallocate(m_pTempValue);
            m_pTempValue = nullptr;
        }
        m_pCastedExpression = nullptr;
    }
}

void CastExpression::referencedElementRemoved( LanguageElement* a_pElement )
{
    // Release m_pTempValue if its value type is destroyed
    if(m_pTempValue AND a_pElement == m_pCastedExpression->getValueType())
    {
        m_pCastedExpression->getValueType()->terminate(m_pTempValue);
        m_pCastedExpression->getValueType()->uninstall(m_pTempValue);
        m_pCastedExpression->getValueType()->destroy(m_pTempValue);
        m_pCastedExpression->getValueType()->deallocate(m_pTempValue);
        m_pTempValue = nullptr;
    }
    if(m_pIntermediateBuffer AND m_pIntermediateBufferType == a_pElement)
    {
        m_pIntermediateBufferType->terminate(m_pIntermediateBuffer);
        m_pIntermediateBufferType->uninstall(m_pIntermediateBuffer);
        m_pIntermediateBufferType->destroy(m_pIntermediateBuffer);
        m_pIntermediateBufferType->deallocate(m_pIntermediateBuffer);
        m_pIntermediateBuffer = nullptr;
    }
}

void CastExpression::construct()
{
    if(m_pCastedExpression)
    {
        addSubExpression(m_pCastedExpression);
        o_assert(m_pCastedExpression->getValueType()->isCopyable());
        if(NOT(m_pCastedExpression->hasValueStorage()))
        {
            m_pTempValue = m_pCastedExpression->getValueType()->allocate();
            m_pCastedExpression->getValueType()->construct(m_pTempValue);
            m_pCastedExpression->getValueType()->install(m_pTempValue);
            m_pCastedExpression->getValueType()->initialize(m_pTempValue);
            addReferencedElement(m_pCastedExpression->getValueType());
        }
        reflection::ReferenceType* pRefCastType = getValueType()->asReferenceType();
        if(pRefCastType AND m_pCastedExpression->getValueType()->asReferenceType() == nullptr AND pRefCastType->getReferencedType()->asConstType())
        {
            // Conversion from non-ref to const ref, need intermediate buffer
            m_pIntermediateBufferType = pRefCastType->removeReference()->removeConst();
            addReferencedElement(m_pIntermediateBufferType);
            m_pIntermediateBuffer = m_pIntermediateBufferType->allocate();
            m_pIntermediateBufferType->construct(m_pIntermediateBuffer);
            m_pIntermediateBufferType->install(m_pIntermediateBuffer);
            m_pIntermediateBufferType->initialize(m_pIntermediateBuffer);
        }
    }
    else setInvalid();
}

o_namespace_end(phantom, reflection)
