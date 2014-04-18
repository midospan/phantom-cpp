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
#include <phantom/reflection/Property.h>
#include <phantom/reflection/Property.hxx>
#include <phantom/reflection/PropertyAccess.h>
/* *********************************************** */
o_registerN((phantom, reflection), Property);

o_namespace_begin(phantom, reflection) 

Class* const Property::metaType = o_type_of(phantom::reflection::Property);

Property::Property( const string& a_strName, Type* a_pValueType, InstanceMemberFunction* a_pSetMemberFunction, InstanceMemberFunction* a_pGetMemberFunction, Signal* a_pSignal, Range* a_pRange, uint a_uiSerializationMask, bitfield a_Modifiers /*= 0*/ ) 
    : ValueMember(a_strName, a_pValueType, a_pRange, a_uiSerializationMask, a_Modifiers) 
    , m_pSetMemberFunction(a_pSetMemberFunction)
    , m_pGetMemberFunction(a_pGetMemberFunction)
    , m_pSignal(a_pSignal)
{
    o_assert(m_pGetMemberFunction->getSignature()->getReturnType() == m_pValueType);
    o_assert(m_pSetMemberFunction->getSignature()->getParameterCount() == 1 && m_pSetMemberFunction->getSignature()->getParameterType(0) == m_pValueType);
    o_assert(m_pSignal == nullptr 
        || m_pSignal->getSignature()->getParameterCount() == 0 
        || (m_pSignal->getSignature()->getParameterCount() == 1 && m_pSignal->getSignature()->getParameterType(0) == m_pValueType));
    // TODO : fix this, put it in o_property ...
    if(m_pSignal && m_pSignal->getOwner() == nullptr)
        a_pSetMemberFunction->getOwnerClass()->addSignal(m_pSignal);
    addReferencedElement(a_pSetMemberFunction);
    addReferencedElement(a_pGetMemberFunction);
    if(m_pSignal)
        addReferencedElement(m_pSignal);
}

void Property::referencedElementRemoved( LanguageElement* a_pElement )
{
    ValueMember::referencedElementRemoved(a_pElement);
    if(m_pSignal == a_pElement)
        m_pSignal = nullptr;
    else if(m_pGetMemberFunction == a_pElement)
        m_pGetMemberFunction = nullptr;
    else if(m_pSetMemberFunction == a_pElement)
        m_pSetMemberFunction = nullptr;
}

Expression* Property::createAccessExpression( Expression* a_pLeftExpression ) const
{
    return o_new(PropertyAccess)(a_pLeftExpression->implicitCast(getOwnerClassType()), const_cast<Property*>(this));
}

bool Property::referencesData( const void* a_pInstance, const phantom::data& a_Data ) const
{
    Type* pType = m_pValueType;
    void* pBuffer = pType->allocate();
    pType->construct(pBuffer);
    pType->initialize(pBuffer);
    getValue(a_pInstance, pBuffer);
    if(pType->referencesData(pBuffer, a_Data))
    {
        pType->terminate(pBuffer);
        pType->destroy(pBuffer);
        pType->deallocate(pBuffer);
        return true;
    }
    pType->terminate(pBuffer);
    pType->destroy(pBuffer);
    pType->deallocate(pBuffer);
    return false;
}

void Property::fetchReferencedData( const void* a_pInstance, vector<phantom::data>& out, uint a_uiSerializationMask ) const
{
    if((m_uiSerializationMask & a_uiSerializationMask) != 0)
    {
        Type* pType = m_pValueType;
        void* pBuffer = pType->allocate();
        pType->construct(pBuffer);
        pType->initialize(pBuffer);
        getValue(a_pInstance, pBuffer);
        pType->fetchReferencedData(pBuffer, out, a_uiSerializationMask);
        pType->terminate(pBuffer);
        pType->destroy(pBuffer);
        pType->deallocate(pBuffer);
    }
}

o_namespace_end(phantom, reflection)
