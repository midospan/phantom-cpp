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
#include <phantom/reflection/InstanceDataMemberExpression.h>
#include <phantom/reflection/InstanceDataMemberExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), InstanceDataMemberExpression);

o_namespace_begin(phantom, reflection) 

InstanceDataMemberExpression::InstanceDataMemberExpression( Expression* a_pLeftExpression, InstanceDataMember* a_pInstanceDataMember ) 
    : Expression(a_pLeftExpression 
                    ? a_pLeftExpression->isConstExpression() 
                        ? a_pInstanceDataMember->getValueType()->constType()->referenceType()
                        : a_pInstanceDataMember->getValueType()->referenceType()
                    : nullptr
                , (a_pInstanceDataMember ? a_pInstanceDataMember->getModifiers() : 0) & ~o_native)
    , m_pLeftExpression(a_pLeftExpression)
    , m_pInstanceDataMember(a_pInstanceDataMember)
{
    if(m_pLeftExpression)
    {
        addSubExpression(m_pLeftExpression);
        if(NOT(m_pLeftExpression->hasEffectiveAddress()))
            setInvalid();
    }
    else setInvalid();
    if(m_pInstanceDataMember)
    {
        addReferencedElement(m_pInstanceDataMember);
    } 
    else setInvalid();
}

void InstanceDataMemberExpression::referencedElementRemoved( LanguageElement* a_pElement )
{
    Expression::referencedElementRemoved(a_pElement);
    if(m_pInstanceDataMember == a_pElement)
        m_pInstanceDataMember = nullptr;
}

void InstanceDataMemberExpression::internalEval( void* a_pDest ) const
{
    *((void**)a_pDest) = m_pInstanceDataMember->getAddress(m_pLeftExpression->loadEffectiveAddress());
}

InstanceDataMemberExpression* InstanceDataMemberExpression::clone() const
{
    return o_new(InstanceDataMemberExpression)(m_pLeftExpression, m_pInstanceDataMember);
}

LanguageElement* InstanceDataMemberExpression::getHatchedElement() const
{
    return m_pInstanceDataMember;
}

bool InstanceDataMemberExpression::isPersistent() const
{
    return Expression::isPersistent() AND m_pInstanceDataMember->isNative();
}

o_namespace_end(phantom, reflection)