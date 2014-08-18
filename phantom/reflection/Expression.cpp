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
#include <phantom/reflection/AddressExpression.h>
#include <phantom/reflection/ReferenceExpression.h>
#include <phantom/reflection/CastExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), Expression);

o_namespace_begin(phantom, reflection) 

Expression::Expression( Type* a_pType, bitfield a_Modifiers /*= 0*/) 
    : Evaluable("", a_Modifiers)
    , m_pValueType(a_pType)
{
    addReferencedElement(a_pType);
}

Expression::Expression( Type* a_pType, const string& a_strName, bitfield a_Modifiers /*= 0*/ ) 
    : Evaluable(a_strName, a_Modifiers)
    , m_pValueType(a_pType)
{
    addReferencedElement(a_pType);
}

Expression* Expression::solveOperator(const string& a_strOp, const vector<Expression*>& a_Expressions, bitfield a_Modifiers) const 
{
    vector<Expression*> newExpressions;
    newExpressions.push_back(const_cast<Expression*>(this));
    if(a_Expressions.size() > 0)
    {
        newExpressions.insert(newExpressions.end(), a_Expressions.begin(), a_Expressions.end());

        // Use 'strongest' type to solve operation
        if(m_pValueType->getTypeId() == e_struct OR (m_pValueType->removeReference()->getTypeId() >= a_Expressions.back()->getValueType()->removeReference()->getTypeId()))
        {
            return m_pValueType->solveOperator(a_strOp, newExpressions, a_Modifiers);
        }
        else 
        {
            return a_Expressions.back()->getValueType()->solveOperator(a_strOp, newExpressions, a_Modifiers);
        }
    }
    else 
    {
        o_assert(a_Expressions.size() == 0);
        return m_pValueType->solveOperator(a_strOp, newExpressions, a_Modifiers);
    }
}

void Expression::setValue( void const* a_pSrc ) const
{
    o_exception(exception::reflection_runtime_exception, "Expression is not an l-value");
}

void Expression::load( void* a_pDest ) const
{
    if(m_pValueType->asReferenceType())
    {
        void* pBuffer;
        getValue(&pBuffer);
        m_pValueType->asReferenceType()->getReferencedType()->copy(a_pDest, pBuffer);
    }
    else getValue(a_pDest);
}

void Expression::store( void const* a_pSrc ) const
{
    if(isConstExpression())
    {
        o_exception(exception::reflection_runtime_exception, "Expression is const and cannot be modified");
    }
    if(m_pValueType->asReferenceType())
    {
        void* pBuffer;
        getValue(&pBuffer);
        m_pValueType->asReferenceType()->getReferencedType()->copy(pBuffer, a_pSrc);
    }
    else setValue(a_pSrc);
    flush();
}

LanguageElement* Expression::solveElement( const string& a_strName, const vector<TemplateElement*>* a_pTemplateSignature, const vector<LanguageElement*>* a_pFunctionSignature, bitfield a_Modifiers /*= 0*/ ) const
{
    if(hasEffectiveAddress())
    {
        Type* pType = m_pValueType;
        return pType->solveExpression(reference(), a_strName, a_pTemplateSignature, a_pFunctionSignature, a_Modifiers);
    }
    return nullptr;
}

void* Expression::loadEffectiveAddress() const
{
    if(m_pValueType->asReferenceType())
    {
        void* pAddress;
        getValue(&pAddress);
        return pAddress;
    }
    else if(hasValueStorage())
    {
        return getValueStorageAddress();
    }
    else
    {
        o_exception(exception::reflection_runtime_exception, "Expression value does not have memory storage"); return nullptr;
    }
}

Expression* Expression::implicitCast( Type* a_pTargetType ) const
{
    if(m_pValueType == a_pTargetType->removeConst()) 
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
    if(m_pValueType->asReferenceType())
    {
        return const_cast<Expression*>(this);
    }
    if(hasEffectiveAddress())
    {
        return o_new(ReferenceExpression)(const_cast<Expression*>(this));
    }
    return nullptr;
}

Expression* Expression::address() const
{
    if(isAddressable())
    {
        return o_new(AddressExpression)(const_cast<Expression*>(this));
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

Type* Expression::storageType(Type* a_pType) const
{
    Type* pStorageType = a_pType;
    if(pStorageType == typeOf<void>()) return nullptr;
    if(pStorageType->asReferenceType())
    {
        pStorageType = pStorageType->asReferenceType()->getReferencedType()->pointerType();
    }
    return pStorageType;
}

variant Expression::get() const
{
    variant v;
    v.setType(m_pValueType->removeReference()->removeConst());
    load((void*)v.buffer());
    return v;
}

void Expression::set( const variant& v )
{
    if(v.type() == m_pValueType->removeReference())
    {
        store(v.buffer());
    }
    else 
    {
        variant casted = v.as(m_pValueType->removeReference());
        if(casted.isNull())
        {
            o_exception(exception::reflection_runtime_exception, "Cannot convert variant to expression value type");
        }
        store(casted.buffer());
    }
}

bool Expression::isConstExpression() const
{
    return m_pValueType->removeReference()->asConstType() != nullptr;
}

bool Expression::isDereferenceable() const
{
    return m_pValueType->removeReference()->removeConst()->asDataPointerType() != nullptr;
}


o_namespace_end(phantom, reflection)
