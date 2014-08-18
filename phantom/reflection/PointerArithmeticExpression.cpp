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
#include <phantom/reflection/PointerArithmeticExpression.h>
#include <phantom/reflection/PointerArithmeticExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), PointerArithmeticExpression);

o_namespace_begin(phantom, reflection) 

PointerArithmeticExpression::PointerArithmeticExpression( const string& a_strOperator, Expression* a_pPointerExpression, Expression* a_pOffsetExpression ) 
    : Expression(a_pPointerExpression->getValueType(), "("+a_pPointerExpression->getName()+')'+a_strOperator+'('+a_pOffsetExpression->getName()+')', a_pPointerExpression->getModifiers())
    , m_strOperator(a_strOperator)
    , m_pPointerExpression(a_pPointerExpression)
    , m_pOffsetExpression(a_pOffsetExpression)
    , m_pOffsetConvertedExpression(a_pOffsetExpression->implicitCast(typeOf<ptrdiff_t>()))
    , m_uiPointedSize(a_pPointerExpression->getValueType()->asDataPointerType()->getPointedType()->getSize())
{
    addElement(m_pPointerExpression);
    addElement(m_pOffsetConvertedExpression);
    o_assert(m_pPointerExpression->getValueType()->removeReference()->asDataPointerType());
    o_assert(a_pOffsetExpression->getValueType()->removeReference()->isConvertibleTo(typeOf<ptrdiff_t>()));
}

PointerArithmeticExpression::~PointerArithmeticExpression()
{
    
}

void PointerArithmeticExpression::getValue( void* a_pDest ) const
{
    byte** ppDest = (byte**)a_pDest;
    m_pPointerExpression->load(ppDest);
    ptrdiff_t offset;
    m_pOffsetConvertedExpression->getValue(&offset);
    *ppDest+=offset*m_uiPointedSize;
}

PointerArithmeticExpression* PointerArithmeticExpression::clone() const
{
    return o_new(PointerArithmeticExpression)(m_strOperator, m_pPointerExpression->clone(), m_pOffsetExpression->clone());
}


o_namespace_end(phantom, reflection)
