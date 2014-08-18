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
#include <phantom/reflection/ArrayElementAccess.h>
#include <phantom/reflection/ArrayElementAccess.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), ArrayElementAccess);

o_namespace_begin(phantom, reflection) 

ArrayElementAccess::ArrayElementAccess( ArrayType* a_pArrayType, Expression* a_pLeftExpression, Expression* a_pIndexExpression) 
    : Expression(a_pArrayType->getElementType()->referenceType(), "("+a_pLeftExpression->getName()+")["+a_pIndexExpression->getName()+']', a_pLeftExpression->getModifiers())
    , m_pArrayType(a_pArrayType)
    , m_pLeftExpression(a_pLeftExpression)
    , m_pIndexExpression(a_pIndexExpression)
{
    if(NOT(m_pLeftExpression->hasEffectiveAddress()))
        setInvalid();
    addElement(m_pLeftExpression);
    addReferencedElement(m_pArrayType);
}

ArrayElementAccess::ArrayElementAccess(ConstType* a_pConstArrayType, Expression* a_pLeftExpression, Expression* a_pIndexExpression)
    : Expression(a_pConstArrayType->getConstedType()->asArrayType()->getElementType()->constType()->referenceType(), "("+a_pLeftExpression->getName()+")["+a_pIndexExpression->getName()+']', a_pLeftExpression->getModifiers())
    , m_pArrayType(a_pConstArrayType->getConstedType()->asArrayType())
    , m_pLeftExpression(a_pLeftExpression)
    , m_pIndexExpression(a_pIndexExpression)
{
    if(NOT(a_pLeftExpression->hasEffectiveAddress()))
        setInvalid();
    addElement(m_pLeftExpression->asConstant());
    addReferencedElement(a_pConstArrayType);
}

void ArrayElementAccess::referencedElementRemoved( LanguageElement* a_pElement )
{
    Expression::referencedElementRemoved(a_pElement);
    if(m_pArrayType == a_pElement)
        m_pArrayType = nullptr;
}

ArrayElementAccess* ArrayElementAccess::clone() const
{
    return o_new(ArrayElementAccess)(m_pArrayType, m_pLeftExpression->clone(), m_pIndexExpression->clone());
}

o_namespace_end(phantom, reflection)