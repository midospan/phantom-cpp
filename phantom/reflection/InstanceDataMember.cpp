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
#include "InstanceDataMemberAccess.h"
/* *********************************************** */
o_registerN((phantom, reflection), InstanceDataMember);

o_namespace_begin(phantom, reflection) 

Class* const InstanceDataMember::metaType = o_type_of(phantom::reflection::InstanceDataMember);

InstanceDataMember::InstanceDataMember( const string& a_strName, Type* a_pValueType, size_t  a_uiOffset, Range* a_pRange, uint a_uiSerializationMask, bitfield a_Modifiers /*= 0*/ )
    : ValueMember(a_strName, a_pValueType, a_pRange, a_uiSerializationMask, a_Modifiers)
    , m_uiOffset(a_uiOffset)
{
}

void InstanceDataMember::referencedElementRemoved( LanguageElement* a_pElement )
{
    ValueMember::referencedElementRemoved(a_pElement);
}

Expression* InstanceDataMember::createAccessExpression( Expression* a_pLeftExpression ) const
{
    return o_new(InstanceDataMemberAccess)(a_pLeftExpression->implicitCast(getOwnerClassType()), const_cast<InstanceDataMember*>(this));
}

bool InstanceDataMember::referencesData( const void* a_pInstance, const phantom::data& a_Data ) const
{
    return m_pValueType->referencesData(getAddress(a_pInstance), a_Data);
}

void InstanceDataMember::fetchReferencedData( const void* a_pInstance, vector<phantom::data>& out, uint a_uiSerializationMask ) const
{
    if((m_uiSerializationMask & a_uiSerializationMask) != 0)
    {
        m_pValueType->fetchReferencedData(getAddress(a_pInstance), out, a_uiSerializationMask);
    }
}


o_namespace_end(phantom, reflection)