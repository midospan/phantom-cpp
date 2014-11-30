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
#include <phantom/reflection/PropertyAccess.h>
#include <phantom/reflection/PropertyAccess.hxx>
#include <phantom/reflection/CallExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), PropertyAccess);

o_namespace_begin(phantom, reflection) 

PropertyAccess::PropertyAccess( Expression* a_pLeftExpression, Property* a_pProperty ) 
    : Expression(a_pLeftExpression->isConstExpression() 
                                ? a_pProperty->getValueType()->removeReference()->removeConst()->constType()->referenceType()
                                : a_pProperty->getValueType()->removeReference()->removeConst()->referenceType()
                , "("+a_pLeftExpression->getName() + ")." + a_pProperty->getName()
                , a_pProperty->getModifiers() & ~o_native)
    , m_pLeftExpression(a_pLeftExpression)
    , m_pProperty(a_pProperty)
{
    o_assert(a_pLeftExpression->hasEffectiveAddress());
    o_assert(a_pLeftExpression->getValueType()->removeReference()->removeConst() == a_pProperty->getOwner());
    addSubExpression(m_pLeftExpression);
    addReferencedElement(a_pProperty);

    m_pBuffer = m_pValueType->removeReference()->allocate();
    m_pValueType->removeReference()->construct(m_pBuffer);
    m_pValueType->removeReference()->install(m_pBuffer);
    m_pValueType->removeReference()->initialize(m_pBuffer);
}

o_terminate_cpp(PropertyAccess)
{
    m_pValueType->removeReference()->terminate(m_pBuffer);
    m_pValueType->removeReference()->uninstall(m_pBuffer);
    m_pValueType->removeReference()->destroy(m_pBuffer);
    m_pValueType->removeReference()->deallocate(m_pBuffer);
}

void PropertyAccess::referencedElementRemoved( LanguageElement* a_pElement )
{
    Expression::referencedElementRemoved(a_pElement);
    if(m_pProperty == a_pElement)
        m_pProperty = nullptr;
}

void PropertyAccess::setValue( void const* a_pSrc ) const
{
    void* pCaller = m_pLeftExpression->loadEffectiveAddress();
    m_pProperty->setValue(pCaller, a_pSrc);
    m_pProperty->getValue(pCaller, m_pBuffer); // store the value back in the buffer
}

void PropertyAccess::getValue( void* a_pDest ) const
{
    m_pProperty->getValue(m_pLeftExpression->loadEffectiveAddress(), m_pBuffer);
    *((void**)a_pDest) = (void*)m_pBuffer;
}

void PropertyAccess::flush() const
{
    void* pAddress = m_pLeftExpression->loadEffectiveAddress();
    bool bBlockSignal = areSignalsBlocked() AND m_pProperty->getSignal();
    if(bBlockSignal)
    {
        m_pProperty->getSignal()->block(pAddress);
    }
    m_pProperty->setValue(m_pLeftExpression->loadEffectiveAddress(), m_pBuffer);
    if(bBlockSignal)
    {
        m_pProperty->getSignal()->unblock(pAddress);
    }
    m_pLeftExpression->flush();
}

Expression* PropertyAccess::solveOperator( const string& a_strOp, const vector<Expression*>& a_Expressions, modifiers_t a_Modifiers /* = 0 */ ) const
{
//     if(a_Expressions.size() == 1)
//     {
//         if(a_strOp == "=")
//         {
//             if(a_Expressions[0]->getValueType()->isImplicitlyConvertibleTo(m_pProperty->getSetMemberFunction()->getParameterType(0)))
//             {
//                 const_cast<PropertyAccess*>(this)->removeElement(m_pLeftExpression);
//                 vector<Expression*> arguments;
//                 arguments.push_back(m_pLeftExpression->reference());
//                 InstanceMemberFunction* pSet = m_pProperty->getSetMemberFunction();
//                 arguments.push_back(a_Expressions[0]->implicitCast(pSet->getParameterType(0)));
//                 o_dynamic_delete (const_cast<PropertyAccess*>(this));
//                 return o_new(CallExpression)(pSet, arguments);
//             }
//         }
//         else if(a_strOp.size() == 2 && a_strOp[1] == '=' && a_strOp[0] != '=') 
//         {
//             vector<Expression*> arguments;
//             arguments.push_back(asExpression());
//             arguments.push_back(a_Expressions[0]);
//             Expression* pOperation = getValueType()->solveOperator(a_strOp.substr(0, 1), arguments, 0);
//             if(pOperation != nullptr)
//             {
//                 const_cast<PropertyAccess*>(this)->removeElement(m_pLeftExpression); // abandon left expression to give it to the call expression
//                 InstanceMemberFunction* pSet = m_pProperty->getSetMemberFunction();
//                 arguments[0] = m_pLeftExpression;
//                 arguments[1] = pOperation->implicitCast(pSet->getParameterType(0));
//                 return o_new(CallExpression)(pSet, arguments);
//             }
//         }
//     }
    return Expression::solveOperator(a_strOp, a_Expressions, a_Modifiers);
}

PropertyAccess* PropertyAccess::clone() const
{
    return o_new(PropertyAccess)(m_pLeftExpression, m_pProperty);
}

LanguageElement* PropertyAccess::getHatchedElement() const
{
    return m_pProperty;
}

bool PropertyAccess::isPersistent() const
{
    return Expression::isPersistent() AND m_pProperty->isNative();
}

o_namespace_end(phantom, reflection)