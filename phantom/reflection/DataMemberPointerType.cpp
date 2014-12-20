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
#include "DataMemberPointerType.h"
#include "DataMemberPointerType.hxx"
/* *********************************************** */
o_registerN((phantom, reflection), DataMemberPointerType);

o_namespace_begin(phantom, reflection) 

Class* const DataMemberPointerType::metaType = o_type_of(phantom::reflection::DataMemberPointerType);

DataMemberPointerType::DataMemberPointerType(Type* a_pObjectType, Type* a_pValueType, size_t a_uiSize, size_t a_uiAlignment, modifiers_t modifiers) 
    : MemberPointerType(a_pObjectType, a_uiSize, a_uiAlignment, modifiers)
    , m_pValueType(a_pValueType)
{
    if(m_pValueType) addReferencedElement(m_pValueType);
}

void DataMemberPointerType::referencedElementRemoved( LanguageElement* a_pElement )
{
    if(m_pValueType == a_pElement)
    {
        m_pValueType = nullptr;
    }
    MemberPointerType::referencedElementRemoved(a_pElement);
}



o_namespace_end(phantom, reflection)