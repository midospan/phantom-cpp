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
#include <phantom/reflection/SingleParameterFunctionExpression.h>
#include <phantom/reflection/SingleParameterFunctionExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), SingleParameterFunctionExpression);
o_namespace_begin(phantom, reflection) 

SingleParameterFunctionExpression::SingleParameterFunctionExpression(Subroutine* a_pSubroutine, Expression* a_pLeftExpression /*= nullptr*/)
    : Expression(a_pSubroutine->getParameterType(0), a_pLeftExpression ? "("+a_pLeftExpression->getName()+ ")." + a_pSubroutine->getName() : a_pSubroutine->getName())
    , m_pLeftExpression(a_pLeftExpression)
    , m_pSubroutine(a_pSubroutine)
{
    addReferencedElement(a_pSubroutine->getParameterType(0));
    addReferencedElement(a_pSubroutine);
    if(a_pLeftExpression)
        addSubExpression(m_pLeftExpression);
}

void SingleParameterFunctionExpression::setValue( void const* a_pSrc ) const
{
    if(m_pLeftExpression)
    {
        m_pSubroutine->call(m_pLeftExpression->loadEffectiveAddress(), (void**)&a_pSrc);
    }
    else 
    {
        m_pSubroutine->call((void**)&a_pSrc);
    }
}

SingleParameterFunctionExpression* SingleParameterFunctionExpression::clone() const
{
    return o_new(SingleParameterFunctionExpression)(m_pSubroutine, m_pLeftExpression ? m_pLeftExpression : nullptr);
}

o_namespace_end(phantom, reflection)