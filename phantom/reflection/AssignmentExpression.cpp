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
#include <phantom/reflection/AssignmentExpression.h>
#include <phantom/reflection/AssignmentExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), AssignmentExpression);

o_namespace_begin(phantom, reflection) 

AssignmentExpression::AssignmentExpression( Expression* a_pLHSExpression, Expression* a_pRHSExpression ) 
    : Expression(a_pLHSExpression->getValueType(), "("+a_pLHSExpression->getName()+'='+a_pRHSExpression->getName()+')'
                , a_pLHSExpression->getModifiers())
    , m_pLHSExpression(a_pLHSExpression)
    , m_pRHSExpression(a_pRHSExpression)
    , m_pRHSConvertedExpression(a_pRHSExpression->implicitCast(a_pLHSExpression->getValueType()->removeReference()))
{
    o_assert(a_pLHSExpression->isAddressable());
    o_assert(m_pRHSConvertedExpression);
    if(m_pLHSExpression->getOwner() == nullptr) // In case of assigment operation of kind '+=' which uses LHS two times
    {
        addElement(m_pLHSExpression);
    }
    addElement(m_pRHSConvertedExpression);
}

AssignmentExpression::~AssignmentExpression()
{
    
}

AssignmentExpression* AssignmentExpression::clone() const
{
    return o_new(AssignmentExpression)(m_pLHSExpression->clone(), m_pRHSExpression->clone());
}


o_namespace_end(phantom, reflection)
