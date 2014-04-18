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
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/Expression.hxx>
#include <phantom/reflection/DereferenceExpression.h>
#include <phantom/reflection/ReferenceExpression.h>
#include <phantom/reflection/CastExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), Expression);

o_namespace_begin(phantom, reflection) 

Expression::Expression( Type* a_pType, bitfield a_Modifiers /*= 0*/) 
: LanguageElement("", a_Modifiers)
, m_pValueType(a_pType)
{
    addReferencedElement(a_pType);
}

Expression::Expression( Type* a_pType, const string& a_strName, bitfield a_Modifiers /*= 0*/ ) 
    : LanguageElement(a_strName, a_Modifiers)
    , m_pValueType(a_pType)
{
    addReferencedElement(a_pType);
}

LanguageElement* Expression::solveBracketOperator( Expression* a_pExpression ) const
{
    vector<LanguageElement*> signature;
    signature.push_back(a_pExpression);
    return solveElement("operator[]", nullptr, &signature, 0);
}

LanguageElement* Expression::solveParenthesisOperator( const vector<LanguageElement*>& a_FunctionSignature ) const
{
    return solveElement("operator()", nullptr, &a_FunctionSignature, 0);
}

void Expression::setValue( void const* a_pSrc ) const
{
    o_exception(exception::reflection_runtime_exception, "Expression is not an l-value");
}

void Expression::load( void* a_pDest ) const
{
    getValue(a_pDest);
}

void Expression::store( void const* a_pSrc ) const
{
    if(m_pValueType->asConstType())
    {
        o_exception(exception::reflection_runtime_exception, "Expression is const and cannot be modified");
    }
    else if(!isAddressable())
    {
        o_exception(exception::reflection_runtime_exception, "Expression is not an l-value");
    }
    setValue(a_pSrc);
}

void* Expression::getAddress() const
{
    o_exception(exception::reflection_runtime_exception, "Expression is not an l-value"); return nullptr;
}

LanguageElement* Expression::solveElement( const string& a_strName, const vector<TemplateElement*>* a_pTemplateSignature, const vector<LanguageElement*>* a_pFunctionSignature, bitfield a_Modifiers /*= 0*/ ) const
{
    return m_pValueType->solveExpression(const_cast<Expression*>(this), a_strName, a_pTemplateSignature, a_pFunctionSignature, a_Modifiers);
}

Expression* Expression::implicitCast( Type* a_pTargetType ) const
{
    if(m_pValueType == a_pTargetType) 
        return const_cast<Expression*>(this);
    if(m_pValueType->isImplicitlyConvertibleTo(a_pTargetType) && m_pValueType->isCopyable())
    {
        return o_new(CastExpression)(a_pTargetType, const_cast<Expression*>(this));
    }
    return nullptr;
}

Expression* Expression::cast( Type* a_pTargetType ) const
{
    if(m_pValueType == a_pTargetType) 
        return const_cast<Expression*>(this);
    if(m_pValueType->isConvertibleTo(a_pTargetType))
        return o_new(CastExpression)(a_pTargetType, const_cast<Expression*>(this));
    return nullptr;
}

Expression* Expression::reference() const
{
    if(isReferenceable())
    {
        return o_new(ReferenceExpression)(const_cast<Expression*>(this));
    }
    return nullptr;
}

Expression* Expression::dereference() const
{
    if(isDereferenceable())
    {
        return o_new(DereferenceExpression)(const_cast<Expression*>(this));
    }
    return nullptr;
}


o_namespace_end(phantom, reflection)
