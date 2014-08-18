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
#include <phantom/reflection/BinaryOperationExpression.h>
#include <phantom/reflection/BinaryOperationExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), BinaryOperationExpression);

o_namespace_begin(phantom, reflection) 
    
BinaryOperationExpression::BinaryOperationExpression( Type* a_pType, const string& a_strOperator, Expression* a_pLHSExpression, Expression* a_pRHSExpression ) 
    : Expression(a_pType
    , "("+a_pLHSExpression->getName()+a_strOperator+a_pRHSExpression->getName()+')'
                , a_pLHSExpression->getModifiers())
    , m_strOperator(a_strOperator)
    , m_pLHSExpression(a_pLHSExpression)
    , m_pRHSExpression(a_pRHSExpression)
    , m_pLHSConvertedExpression(a_pLHSExpression->implicitCast(a_pType))
    , m_pRHSConvertedExpression(a_pRHSExpression->implicitCast(a_pType))
{
    o_assert(m_pLHSExpression);
    o_assert(m_pRHSExpression);
    o_assert(m_pLHSConvertedExpression);
    o_assert(m_pRHSConvertedExpression);
    o_assert(m_strOperator.size());
    addElement(m_pLHSConvertedExpression);
    addElement(m_pRHSConvertedExpression);
}

BinaryOperationExpression::BinaryOperationExpression( Type* a_pLHSType, Type* a_pRHSType, const string& a_strOperator, Expression* a_pLHSExpression, Expression* a_pRHSExpression ) 
    : Expression(a_pLHSType
    , "("+a_pLHSExpression->getName()+a_strOperator+a_pRHSExpression->getName()+')'
    , a_pLHSExpression->getModifiers())
    , m_strOperator(a_strOperator)
    , m_pLHSExpression(a_pLHSExpression)
    , m_pRHSExpression(a_pRHSExpression)
    , m_pLHSConvertedExpression(a_pLHSExpression->implicitCast(a_pLHSType))
    , m_pRHSConvertedExpression(a_pRHSExpression->implicitCast(a_pRHSType))
{
    o_assert(m_pLHSExpression);
    o_assert(m_pRHSExpression);
    o_assert(m_pLHSConvertedExpression);
    o_assert(m_pRHSConvertedExpression);
    o_assert(m_strOperator.size());
    addElement(m_pLHSConvertedExpression);
    addElement(m_pRHSConvertedExpression);
}

BinaryOperationExpression::BinaryOperationExpression( Type* a_pValueType, Type* a_pLHSType, Type* a_pRHSType, const string& a_strOperator, Expression* a_pLHSExpression, Expression* a_pRHSExpression ) 
    : Expression(a_pValueType
    , "("+a_pLHSExpression->getName()+a_strOperator+a_pRHSExpression->getName()+')'
    , a_pLHSExpression->getModifiers())
    , m_strOperator(a_strOperator)
    , m_pLHSExpression(a_pLHSExpression)
    , m_pRHSExpression(a_pRHSExpression)
    , m_pLHSConvertedExpression(a_pLHSExpression->implicitCast(a_pLHSType))
    , m_pRHSConvertedExpression(a_pRHSExpression->implicitCast(a_pRHSType))
{
    o_assert(m_pLHSExpression);
    o_assert(m_pRHSExpression);
    o_assert(m_pLHSConvertedExpression);
    o_assert(m_pRHSConvertedExpression);
    o_assert(m_strOperator.size());
    addElement(m_pLHSConvertedExpression);
    addElement(m_pRHSConvertedExpression);
}

BinaryOperationExpression::~BinaryOperationExpression()
{
    
}


o_namespace_end(phantom, reflection)
