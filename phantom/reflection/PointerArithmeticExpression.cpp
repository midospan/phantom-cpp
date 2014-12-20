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
    : BinaryOperationExpression(a_pPointerExpression->getValueType(), a_pPointerExpression->getValueType(), typeOf<ptrdiff_t>(), a_strOperator, a_pPointerExpression, a_pOffsetExpression)
    , m_uiPointedSize((a_pPointerExpression AND a_pPointerExpression->getValueType() AND a_pPointerExpression->getValueType()->asDataPointerType()) ? a_pPointerExpression->getValueType()->asDataPointerType()->getPointedType()->getSize() : 0)
{
    if(m_pLeftExpression AND m_pLeftExpression->getValueType()->removeReference()->asDataPointerType() == nullptr)
    {
        setInvalid();
    }
    if(m_uiPointedSize == 0)
    {
        setInvalid();
    }
}

PointerArithmeticExpression::~PointerArithmeticExpression()
{
    
}

void PointerArithmeticExpression::internalEval( void* a_pDest ) const
{
    byte** ppDest = (byte**)a_pDest;
    m_pPointerExpression->load(ppDest);
    ptrdiff_t offset;
    m_pOffsetConvertedExpression->internalEval(&offset);
    *ppDest+=offset*m_uiPointedSize;
}

PointerArithmeticExpression* PointerArithmeticExpression::clone() const
{
    return o_new(PointerArithmeticExpression)(m_strOperator, m_pPointerExpression, m_pOffsetExpression);
}


o_namespace_end(phantom, reflection)
