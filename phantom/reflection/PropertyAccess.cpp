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
#include <phantom/reflection/PropertyAccess.h>
#include <phantom/reflection/PropertyAccess.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), PropertyAccess);

o_namespace_begin(phantom, reflection) 

PropertyAccess::PropertyAccess( Expression* a_pLeftExpression, Property* a_pProperty ) 
    : Expression(a_pLeftExpression->isConstExpression() 
                                ? m_pProperty->getValueType()->constType() 
                                : m_pProperty->getValueType()
                , a_pLeftExpression->getName() + m_pProperty->getName())
    , m_pLeftExpression(a_pLeftExpression)
    , m_pProperty(a_pProperty)
{
    o_assert(a_pLeftExpression->isAddressable());
    addElement(a_pLeftExpression);
    addReferencedElement(a_pProperty);

    m_pBuffer = m_pValueType->allocate();
    m_pValueType->construct(m_pBuffer);
    m_pValueType->install(m_pBuffer);
    m_pValueType->initialize(m_pBuffer);
}

void PropertyAccess::referencedElementRemoved( LanguageElement* a_pElement )
{
    Expression::referencedElementRemoved(a_pElement);
    if(m_pProperty == a_pElement)
        m_pProperty = nullptr;
}

void PropertyAccess::setValue( void const* a_pSrc ) const
{
    void* pCaller = nullptr;
    m_pLeftExpression->getValue(&pCaller);
    if(m_pProperty->getSignal())
    {
        auto thisRtti = rttiDataOf(this);
        rtti_data callerRtti = rttiDataOf(pCaller, getProperty()->getOwnerClass());
        phantom::connect(callerRtti, m_pProperty->getSignal(), thisRtti, thisRtti.object_class->getSignalCascade("valueChanged()"));
        m_pProperty->setValue(pCaller, a_pSrc);
        phantom::disconnect(callerRtti, m_pProperty->getSignal(), thisRtti, thisRtti.object_class->getSignalCascade("valueChanged()"));
    }
    else 
    {
        m_pProperty->setValue(pCaller, a_pSrc);
    }

    m_pProperty->getValue(pCaller, m_pBuffer); // store the value back in the buffer
    m_pLeftExpression->flush();
}

void PropertyAccess::getValue( void* a_pDest ) const
{
    void* pCaller = nullptr;
    m_pLeftExpression->getValue(&pCaller);
    m_pProperty->getValue(m_pLeftExpression->getAddress(), a_pDest);
}

void PropertyAccess::flush()
{
    setValue(m_pBuffer);  
}

o_namespace_end(phantom, reflection)