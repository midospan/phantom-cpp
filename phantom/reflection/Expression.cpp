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

Expression::Expression( Type* a_pType, modifiers_t a_Modifiers /*= 0*/) 
    : Evaluable("", a_Modifiers)
    , m_pValueType(a_pType)
    , m_pSubExpressions(nullptr)
    , m_bSignalsBlocked(false)
{
    if(m_pValueType)
    {
        addReferencedElement(m_pValueType);
    }
    else setInvalid();
}

Expression::Expression( Type* a_pType, const string& a_strName, modifiers_t a_Modifiers /*= 0*/ ) 
    : Evaluable(a_strName, a_Modifiers)
    , m_pValueType(a_pType)
    , m_pSubExpressions(nullptr)
    , m_bSignalsBlocked(false)
{
    if(m_pValueType)
    {
        addReferencedElement(m_pValueType);
    }
    else setInvalid();
}

Expression* Expression::solveOperator(const string& a_strOp, const vector<Expression*>& a_Expressions, modifiers_t a_Modifiers) const 
{
    vector<Expression*> newExpressions;
    newExpressions.push_back(const_cast<Expression*>(this));
    if(a_Expressions.size() > 0)
    {
        newExpressions.insert(newExpressions.end(), a_Expressions.begin(), a_Expressions.end());

        // Use 'strongest' type to solve operation
        if((m_pValueType->removeReference()->getTypeId() >= e_struct) OR (m_pValueType->removeReference()->getTypeId() >= a_Expressions.back()->getValueType()->removeReference()->getTypeId()))
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

LanguageElement* Expression::solveElement( const string& a_strName, const vector<TemplateElement*>* a_pTemplateSignature, const vector<LanguageElement*>* a_pFunctionSignature, modifiers_t a_Modifiers /*= 0*/ ) const
{
    if(m_pValueType == nullptr)
    {
        return nullptr;
    }
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
        return o_new(CastExpression)(a_pTargetType, const_cast<Expression*>(this), true);
    }
    return nullptr;
}

Expression* Expression::cast( Type* a_pTargetType ) const
{
    if(m_pValueType == a_pTargetType) 
        return const_cast<Expression*>(this);
    if(m_pValueType->isConvertibleTo(a_pTargetType) && m_pValueType->isCopyable())
        return o_new(CastExpression)(a_pTargetType, const_cast<Expression*>(this), false);
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
    vector<LanguageElement*> empty;
    return getValueType()->solveExpression(const_cast<Expression*>(this), "operator&", nullptr, &empty, 0);
}

Expression* Expression::dereference() const
{
    if(isDereferenceable())
    {
        return o_new(DereferenceExpression)(const_cast<Expression*>(this));
    }
    vector<LanguageElement*> empty;
    return getValueType()->solveExpression(const_cast<Expression*>(this), "operator*", nullptr, &empty, 0);
}

Type* Expression::storageType(Type* a_pType) const
{
    Type* pStorageType = a_pType;
    if(pStorageType == typeOf<void>()) return nullptr;
    if(pStorageType == typeOf<signal_t>()) return nullptr;
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

void Expression::referencedElementRemoved( LanguageElement* a_pElement )
{
    if(a_pElement == m_pValueType) // Type destroyed => expression cannot exist anymore
    {
        m_pValueType = nullptr;
    }
    Evaluable::referencedElementRemoved(a_pElement);
}

void Expression::addSubExpression( Expression*& a_prExpression )
{
    if(a_prExpression->isInvalid())
        setInvalid();
    if(a_prExpression->getOwner())
    {
        addElement(a_prExpression = a_prExpression->clone());
    }
    else 
    {
        addElement(a_prExpression);
    }
    if(m_pSubExpressions == nullptr)
    {
        m_pSubExpressions = new vector<Expression*>;
    }
    m_pSubExpressions->push_back(a_prExpression);
}

void Expression::elementRemoved( LanguageElement* a_pElement )
{
    if(m_pSubExpressions)
    {
        auto found = std::find(m_pSubExpressions->begin(), m_pSubExpressions->end(), a_pElement);
        if(found != m_pSubExpressions->end())
        {
            m_pSubExpressions->erase(found);
        }
        if(m_pSubExpressions->empty())
        {
            delete m_pSubExpressions;
            m_pSubExpressions = nullptr;
        }
    }
}

bool Expression::isPersistent() const
{
    if(isInvalid()) return false;

    if(m_pSubExpressions)
    {
        for(auto it = m_pSubExpressions->begin(); it != m_pSubExpressions->end(); ++it)
        {
            if(NOT((*it)->isPersistent()))
                return false;
        }
    }
    return m_pValueType->isNative();
}

void Expression::setSignalBlockedCascade( bool a_bSignalsBlocked )
{
    setSignalBlocked(a_bSignalsBlocked);
    if(m_pSubExpressions)
    {
        for(auto it = m_pSubExpressions->begin(); it != m_pSubExpressions->end(); ++it)
        {
            (*it)->setSignalBlockedCascade(a_bSignalsBlocked);
        }
    }
}

void Expression::setSignalBlocked( bool a_bSignalsBlocked )
{
    m_bSignalsBlocked = a_bSignalsBlocked;
}

bool Expression::hasValueStorageCascade() const
{
    if(hasValueStorage())
        return true;
    if(m_pSubExpressions)
    {
        for(auto it = m_pSubExpressions->begin(); it != m_pSubExpressions->end(); ++it)
        {
            if((*it)->hasValueStorageCascade()) return true;
        }
    }
    return false;
}

void Expression::removeSubExpression( Expression* a_pExpression )
{
    o_assert(m_pSubExpressions);
    removeElement(a_pExpression);
}

void Expression::detach()
{
    if(m_pOwner)
    {
        static_cast<Expression*>(m_pOwner)->removeElement(this);
    }
}

o_namespace_end(phantom, reflection)
