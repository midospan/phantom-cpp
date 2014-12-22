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
#include <phantom/reflection/ArrayExpression.h>
#include <phantom/reflection/ArrayExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), ArrayExpression);

o_namespace_begin(phantom, reflection) 

ArrayType* extract_array_type(Expression* a_pLeftExpression)
{
    if(a_pLeftExpression == nullptr) return nullptr;
    if(a_pLeftExpression->getValueType() == nullptr) return nullptr;
    return (a_pLeftExpression->getValueType()->removeConstReference()->asArrayType());
}

Type* extract_array_element_type(ArrayType* a_pArrayType)
{
    return a_pArrayType ? a_pArrayType->getItemType() : nullptr;
}

Type* extract_array_element_type(Expression* a_pLeftExpression)
{
    return extract_array_element_type(extract_array_type(a_pLeftExpression));
}

ReferenceType* extract_array_element_reference_type(Expression* a_pLeftExpression)
{
    Type* pType = extract_array_element_type(a_pLeftExpression);
    return pType ? pType->referenceType() : nullptr;
}

ReferenceType* extract_array_element_reference_type(ArrayType* a_pArrayType, bool a_bConst = false)
{
    Type* pType = extract_array_element_type(a_pArrayType);
    return pType ? (a_bConst ? pType->constType()->referenceType() : pType->referenceType()) : nullptr;
}

ArrayExpression::ArrayExpression( Expression* a_pLeftExpression, Expression* a_pIndexExpression) 
    : Expression(extract_array_element_reference_type(a_pLeftExpression), (a_pLeftExpression ? a_pLeftExpression->getModifiers() : 0))
    , m_pArrayType(extract_array_type(a_pLeftExpression))
    , m_pLeftExpression(a_pLeftExpression)
    , m_pIndexExpression(a_pIndexExpression)
{
    if(m_pLeftExpression == nullptr 
        OR m_pIndexExpression == nullptr
        OR NOT(m_pLeftExpression->hasEffectiveAddress()))
        setInvalid();
    if(m_pLeftExpression)
        addSubExpression(m_pLeftExpression);
    if(m_pIndexExpression)
        addSubExpression(m_pIndexExpression);
    if(m_pArrayType)
        addReferencedElement(m_pArrayType);
}

ArrayExpression::ArrayExpression( ArrayType* a_pArrayType, Expression* a_pLeftExpression, Expression* a_pIndexExpression) 
    : Expression(extract_array_element_reference_type(a_pArrayType)
                , a_pLeftExpression ? a_pLeftExpression->getModifiers() : 0)
    , m_pArrayType(a_pArrayType)
    , m_pLeftExpression(a_pLeftExpression)
    , m_pIndexExpression(a_pIndexExpression)
{
    if(m_pLeftExpression == nullptr 
        OR m_pIndexExpression == nullptr
        OR NOT(m_pLeftExpression->hasEffectiveAddress()))
        setInvalid();
    addSubExpression(m_pLeftExpression);
    addSubExpression(m_pIndexExpression);
    addReferencedElement(m_pArrayType);
}

ArrayExpression::ArrayExpression(ConstType* a_pConstArrayType, Expression* a_pLeftExpression, Expression* a_pIndexExpression)
    : Expression(extract_array_element_reference_type(a_pConstArrayType ? a_pConstArrayType->getConstedType()->asArrayType() : nullptr, true), a_pLeftExpression->getModifiers())
    , m_pArrayType(a_pConstArrayType->getConstedType()->asArrayType())
    , m_pLeftExpression(a_pLeftExpression)
    , m_pIndexExpression(a_pIndexExpression)
{
    if(NOT(a_pLeftExpression->hasEffectiveAddress()))
        setInvalid();
    addSubExpression(m_pLeftExpression);
    addSubExpression(m_pIndexExpression);
    addReferencedElement(a_pConstArrayType);
}

void ArrayExpression::referencedElementRemoved( LanguageElement* a_pElement )
{
    Expression::referencedElementRemoved(a_pElement);
    if(m_pArrayType == a_pElement)
        m_pArrayType = nullptr;
}

ArrayExpression* ArrayExpression::clone() const
{
    return o_new(ArrayExpression)(m_pArrayType, m_pLeftExpression, m_pIndexExpression);
}

bool ArrayExpression::isPersistent() const
{
    return Expression::isPersistent() AND m_pArrayType->isNative();
}

void ArrayExpression::flush() const
{
    m_pIndexExpression->flush(); m_pLeftExpression->flush();
}

o_namespace_end(phantom, reflection)