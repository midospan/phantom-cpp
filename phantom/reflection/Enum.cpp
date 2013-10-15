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
/* ** The Class Header must be the last #include * */
#include <phantom/reflection/Enum.h>
/* *********************************************** */

o_cpp_begin 

ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP

Enum::Enum() : Type("", 4, 4, 0)
{

}

Enum::Enum( const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_bfModifiers /*= bitfield()*/ ) : Type(a_strName, a_uiSize, a_uiAlignment, a_bfModifiers)
{

}

Enum::Enum( const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, uint a_uiGuid, bitfield a_bfModifiers /*= bitfield()*/ ) : Type(a_strName, a_uiSize, a_uiAlignment, a_uiGuid, a_bfModifiers)
{

}

Enum::~Enum()
{
    for(auto it = m_Constants.begin(); it != m_Constants.end(); ++it)
    {
        o_dynamic_delete (*it);
    }
}

LanguageElement* Enum::getElement( const char* a_strName , template_specialization const* ts , function_signature const* fs , bitfield a_bfModifiers /*= bitfield()*/ ) const
{
    if(ts AND !ts->empty()) return NULL;
    if(fs AND !fs->empty()) return NULL;
    return getConstant(a_strName);
}

boolean Enum::isConvertibleTo( Type* a_pType ) const
{
    return a_pType == this OR a_pType->isIntegralType() OR a_pType->isArithmeticType();
}

boolean Enum::isImplicitlyConvertibleTo( Type* a_pType ) const
{
    return a_pType == this 
        OR (NOT(a_pType->isEnum()) AND a_pType->isIntegralType() OR a_pType->isArithmeticType());
}

void Enum::convertValueTo( Type* a_pDestType, void* a_pDestValue, void const* a_pSrcValue ) const
{
    o_assert(isConvertibleTo(a_pDestType));
    if(a_pDestType->isIntegralType())
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
    else if(a_pDestType->isArithmeticType())
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
    o_assert(getConstant(a_pConstant->getName()) == NULL);
    m_Constants.push_back(a_pConstant);
    addElement(a_pConstant);
}

void Enum::removeConstant( Constant* a_pConstant )
{
    m_Constants.erase(std::find(m_Constants.begin(), m_Constants.end(), a_pConstant));
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

o_cpp_end