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
#include <phantom/reflection/Enum.h>
#include <phantom/reflection/Enum.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), Enum);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(Enum);

Enum::Enum() 
    : PrimitiveType("", 4, 4, 0)
{

}

Enum::Enum( const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_Modifiers /*= 0*/ ) 
    : PrimitiveType(a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
{

}

Enum::Enum( const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, uint a_uiGuid, bitfield a_Modifiers /*= 0*/ ) 
    : PrimitiveType(a_strName, a_uiSize, a_uiAlignment, a_uiGuid, a_Modifiers)
{

}

Enum::~Enum()
{
    while(m_Constants.size())
    {
        m_Constants.back()->deleteNow();
    }
}

LanguageElement* Enum::getElement( const char* a_strName , template_specialization const* ts , function_signature const* fs , bitfield a_Modifiers /*= 0*/ ) const
{
    if(ts AND !ts->empty()) return NULL;
    if(fs AND !fs->empty()) return NULL;
    return getConstant(a_strName);
}

boolean Enum::isConvertibleTo( Type* a_pType ) const
{
    return a_pType == this OR (a_pType->asIntegralType() != nullptr) OR (a_pType->asArithmeticType() != nullptr);
}

boolean Enum::isImplicitlyConvertibleTo( Type* a_pType ) const
{
    return a_pType == this 
        OR ((a_pType->asEnum() == nullptr) AND (a_pType->asIntegralType() != nullptr) OR (a_pType->asArithmeticType() != nullptr));
}

void Enum::convertValueTo( Type* a_pDestType, void* a_pDestValue, void const* a_pSrcValue ) const
{
    o_assert(isConvertibleTo(a_pDestType));
    if(a_pDestType->asIntegralType())
    {
        if(a_pDestType->getSize() == getSize())
        {
            memcpy(a_pDestValue, a_pSrcValue, getSize());
        }
        else 
        {
            memcpy(a_pDestValue, a_pSrcValue, std::min(getSize(), a_pDestType->getSize()));
        }
    }
    else if(a_pDestType->asArithmeticType())
    {
        switch(getSize())
        {
        case 1:
            extension::converter<byte>::convert(a_pDestType, a_pDestValue, (byte const*)a_pSrcValue);
            break;
        case 2:
            extension::converter<ushort>::convert(a_pDestType, a_pDestValue, (ushort const*)a_pSrcValue);
            break;
        case 4:
            extension::converter<uint>::convert(a_pDestType, a_pDestValue, (uint const*)a_pSrcValue);
            break;
        case 8:
            extension::converter<ulonglong>::convert(a_pDestType, a_pDestValue, (ulonglong const*)a_pSrcValue);
            break;
        default:
            o_assert(false, "invalid size for enum type");
        }
    }
}

void Enum::addConstant( Constant* a_pConstant )
{
    o_assert(getConstant(a_pConstant->getName()) == nullptr);
    addElement(a_pConstant);
}

void Enum::removeConstant( Constant* a_pConstant )
{
    o_assert(getConstant(a_pConstant->getName()) != nullptr);
    removeElement(a_pConstant);
}

Constant* Enum::getConstant( const string& a_strKey ) const
{
    value_vector::const_iterator it = m_Constants.begin();
    value_vector::const_iterator end = m_Constants.end();
    for(;it!=end;++it)
    {
        if((*it)->getName() == a_strKey) return *it;
    }
    return NULL;
}

void Enum::valueFromString( const string& a_strIn, void* a_pDest ) const
{
    size_t i = 0;
    size_t count = getConstantCount();
    for(;i<count;++i)
    {
        size_t constantValue = 0;
        reflection::Constant* pConstant = getConstant(i);
        if(pConstant->getName() == a_strIn)
        {
            pConstant->getValue(a_pDest);
            return;
        }
    }
}

void Enum::valueToString( string& a_strOut, const void* a_pSrc ) const
{
    size_t i = 0;
    size_t count = getConstantCount();
    for(;i<count;++i)
    {
        size_t constantValue = 0;
        reflection::Constant* pConstant = getConstant(i);
        pConstant->getValue(&constantValue);
        if(constantValue == *((size_t*)a_pSrc))
        {
            a_strOut = pConstant->getName();
            return;
        }
    }
}

void Enum::elementAdded( LanguageElement* a_pElement )
{
    Constant* pConstant = a_pElement->asConstant();
    o_assert(pConstant);
    m_Constants.push_back(pConstant);
}

void Enum::elementRemoved( LanguageElement* a_pElement )
{
    Constant* pConstant = a_pElement->asConstant();
    o_assert(pConstant);
    m_Constants.erase(std::find(m_Constants.begin(), m_Constants.end(), pConstant));
}

o_namespace_end(phantom, reflection)