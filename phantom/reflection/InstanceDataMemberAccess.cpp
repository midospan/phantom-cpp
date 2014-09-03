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
#include <phantom/reflection/InstanceDataMemberAccess.h>
#include <phantom/reflection/InstanceDataMemberAccess.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), InstanceDataMemberAccess);

o_namespace_begin(phantom, reflection) 

InstanceDataMemberAccess::InstanceDataMemberAccess( Expression* a_pLeftExpression, InstanceDataMember* a_pInstanceDataMember ) 
    : Expression(a_pLeftExpression->isConstExpression() 
                    ? a_pInstanceDataMember->getValueType()->constType()->referenceType()
                    : a_pInstanceDataMember->getValueType()->referenceType()
                , "("+a_pLeftExpression->getName() + ")." + a_pInstanceDataMember->getName()
                        , a_pInstanceDataMember->getModifiers())
    , m_pLeftExpression(a_pLeftExpression)
    , m_pInstanceDataMember(a_pInstanceDataMember)
{
    o_assert(a_pLeftExpression->hasEffectiveAddress());
    addElement(a_pLeftExpression);
    addReferencedElement(m_pInstanceDataMember);
}

void InstanceDataMemberAccess::referencedElementRemoved( LanguageElement* a_pElement )
{
    Expression::referencedElementRemoved(a_pElement);
    if(m_pInstanceDataMember == a_pElement)
        m_pInstanceDataMember = nullptr;
}

void InstanceDataMemberAccess::getValue( void* a_pDest ) const
{
    *((void**)a_pDest) = m_pInstanceDataMember->getAddress(m_pLeftExpression->loadEffectiveAddress());
}

void InstanceDataMemberAccess::setValue( void const* src ) const
{
    m_pInstanceDataMember->setValue(m_pLeftExpression->loadEffectiveAddress(), src);
}

InstanceDataMemberAccess* InstanceDataMemberAccess::clone() const
{
    return o_new(InstanceDataMemberAccess)(m_pLeftExpression->clone(), m_pInstanceDataMember);
}

LanguageElement* InstanceDataMemberAccess::getHatchedElement() const
{
    return m_pInstanceDataMember;
}

o_namespace_end(phantom, reflection)