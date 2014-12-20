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
#include "InstanceDataMember.h"
#include "InstanceDataMember.hxx"
#include "InstanceDataMemberExpression.h"
#include <phantom/std/vector.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), InstanceDataMember);
o_registerNTI((phantom), vector, (phantom::reflection::InstanceDataMember*));

o_namespace_begin(phantom, reflection) 

Class* const InstanceDataMember::metaType = o_type_of(phantom::reflection::InstanceDataMember);

InstanceDataMember::InstanceDataMember() 
    : m_uiOffset(0xffffffff)
    , m_pAnonymousSection(nullptr)
{

}

InstanceDataMember::InstanceDataMember( Type* a_pValueType, const string& a_strName, size_t  a_uiOffset, Range* a_pRange, uint a_uiSerializationMask, modifiers_t a_Modifiers /*= 0*/ )
    : ValueMember(a_pValueType, a_strName, a_pRange, a_uiSerializationMask, a_Modifiers)
    , m_uiOffset(a_uiOffset)
    , m_pAnonymousSection(nullptr)
{
}

InstanceDataMember::InstanceDataMember( Type* a_pValueType, const string& a_strName, Range* a_pRange, uint a_uiSerializationMask /*= 0xffffffff*/, modifiers_t a_Modifiers /*= 0*/ )
    : ValueMember(a_pValueType, a_strName, a_pRange, a_uiSerializationMask, a_Modifiers)
    , m_uiOffset(~size_t(0))
    , m_pAnonymousSection(nullptr)
{

}

void InstanceDataMember::referencedElementRemoved( LanguageElement* a_pElement )
{
    ValueMember::referencedElementRemoved(a_pElement);
}

Expression* InstanceDataMember::createExpression( Expression* a_pLeftExpression ) const
{
    return o_new(InstanceDataMemberExpression)(a_pLeftExpression, const_cast<InstanceDataMember*>(this));
}

bool InstanceDataMember::referencesData( const void* a_pInstance, const phantom::data& a_Data ) const
{
    return m_pValueType->referencesData(getAddress(a_pInstance), a_Data);
}


o_namespace_end(phantom, reflection)