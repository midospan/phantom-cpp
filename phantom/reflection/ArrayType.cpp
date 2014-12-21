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
#include <phantom/reflection/ArrayType.h>
#include <phantom/reflection/ArrayType.hxx>
#include "phantom/reflection/ArrayExpression.h"
/* *********************************************** */
o_registerN((phantom, reflection), ArrayType);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(ArrayType);

ArrayType::ArrayType( Type* a_pItemType, size_t a_uiCount, modifiers_t modifiers = 0 ) 
    : Type(e_array, a_pItemType->getName()
    , a_uiCount*a_pItemType->getSize(), a_pItemType->getAlignment(), a_pItemType->getModifiers()|modifiers)
    , m_pItemType(a_pItemType)
    , m_uiCount(a_uiCount)
{
    o_assert(a_uiCount);
    addReferencedItem(m_pItemType);
}

ArrayType::~ArrayType( void )
{
    if(m_pItemType)
    {
        m_pItemType->removeExtendedType(this);
    }
}

boolean ArrayType::isConvertibleTo( Type* a_pType ) const
{
    return a_pType->asDataPointerType() OR a_pType->asArrayType() OR isImplicitlyConvertibleTo(a_pType);
}

boolean ArrayType::isImplicitlyConvertibleTo( Type* a_pType ) const
{
    if(a_pType == this OR m_pItemType->pointerType()->isImplicitlyConvertibleTo(a_pType)) return true;
    if(a_pType->asArrayType() == nullptr) return false;
    Type*    pItemType = static_cast<ArrayType*>(a_pType)->getItemType();
    if((pItemType->asClass() == nullptr) OR (m_pItemType->asClass() == nullptr)) return false;
    return static_cast<Class*>(pItemType)->isKindOf(static_cast<Class*>(m_pItemType));
}


void ArrayType::serialize( void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    m_pItemType->serialize(a_pInstance, m_uiCount, m_uiSize/m_uiCount, a_OutBranch, a_uiSerializationMask, a_pDataBase);
}

void ArrayType::deserialize( void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    m_pItemType->deserialize(a_pInstance, m_uiCount, m_uiSize/m_uiCount, a_InBranch, a_uiSerializationMask, a_pDataBase);
}

void ArrayType::copy( void* a_pDest, void const* a_pSrc ) const
{
    size_t i = 0;
    size_t storedTypeSize = m_pItemType->getSize();
    for(;i<m_uiCount;++i)
    {
        m_pItemType->copy((byte*)a_pDest + i*storedTypeSize, (byte*)a_pSrc + i*storedTypeSize);
    }
}

void ArrayType::referencedItemRemoved( LanguageElement* a_pItem )
{
    Type::referencedItemRemoved(a_pItem);
    if(m_pItemType == a_pItem)
    {
        m_pItemType->removeExtendedType(this);
        m_pItemType = nullptr;
    }
}

void ArrayType::convertValueTo( Type* a_pDestType, void* a_pDestValue, void const* a_pSrcValue ) const
{
    if(a_pDestType->asPointerType())
    {
        m_pItemType->pointerType()->convertValueTo(a_pDestType, a_pDestValue, &a_pSrcValue);
    }
    else 
    {

    }
}

void ArrayType::valueFromString(const string& a_str, void* dest) const
{
    *reinterpret_cast<void**>(dest) = ::phantom::lexical_cast<void*>(a_str);
}

void ArrayType::valueToString(string& a_str, const void* src) const
{
    a_str += ::phantom::lexical_cast<string>(*((void**)src));
}

string ArrayType::getDecoratedName() const
{
    return m_pItemType->getDecoratedName()+'['+phantom::lexical_cast<string>(m_uiCount)+']';
}

string ArrayType::getQualifiedDecoratedName() const
{
    return m_pItemType->getQualifiedDecoratedName()+'['+phantom::lexical_cast<string>(m_uiCount)+']';
}

bool ArrayType::templatePartialMatch( Type* a_pType, size_t& a_Score, map<TemplateParameter*, LanguageElement*>& a_Deductions ) const
{
    if(a_pType->asArrayType())
    {
        if(a_pType->asArrayType()->getItemCount() == m_uiCount)
        {
            a_Score+=10;
            m_pConstedType->templatePartialMatch(a_pType->removeArray());
        }
    }
    else 
    {
        a_Score = 0; 
        a_Deductions.clear();
    }
}

o_namespace_end(phantom, reflection)