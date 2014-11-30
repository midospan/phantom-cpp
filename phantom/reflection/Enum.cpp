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
#include <phantom/reflection/ConstantExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), Enum);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(Enum);

Enum::Enum() 
    : PrimitiveType(e_enum, "", 4, 4, 0)
    , m_pIntType(typeOf<int>())
{
    addReferencedElement(m_pIntType);
}

Enum::Enum( const string& a_strName, PrimitiveType* a_pIntType, modifiers_t a_Modifiers /*= 0*/ )
    : PrimitiveType(e_enum, a_strName, a_pIntType->getSize(), a_pIntType->getAlignment(), a_Modifiers)
    , m_pIntType(a_pIntType)
{
    addReferencedElement(m_pIntType);
}

Enum::Enum( const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers /*= 0*/ ) 
    : PrimitiveType(e_enum, a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
    , m_pIntType(nullptr)
{

}

Enum::~Enum()
{

}

LanguageElement* Enum::solveElement( const string& a_strName , const vector<TemplateElement*>* ts , const vector<LanguageElement*>* fs , modifiers_t a_Modifiers /*= 0*/ ) const
{
    if(ts AND !ts->empty()) return NULL;
    if(fs AND !fs->empty()) return NULL;
    Constant* pConstant = getConstant(a_strName);
    return pConstant ? o_new(ConstantExpression)(pConstant) : nullptr;
}

boolean Enum::isConvertibleTo( Type* a_pType ) const
{
    return (a_pType->getTypeId() >= e_char AND a_pType->getTypeId() <= e_enum);
}

boolean Enum::isImplicitlyConvertibleTo( Type* a_pType ) const
{
    return a_pType == this OR (a_pType->getTypeId() >= e_char AND a_pType->getTypeId() <= e_wchar_t);
}

void Enum::convertValueTo( Type* a_pDestType, void* a_pDestValue, void const* a_pSrcValue ) const
{
    m_pIntType->convertValueTo(a_pDestType, a_pDestValue, a_pSrcValue);
}

void Enum::addConstant( NumericConstant* a_pConstant )
{
    o_assert(getConstant(a_pConstant->getName()) == nullptr);
    o_assert(a_pConstant->getValueType() == this);
    addElement(a_pConstant);
}

void Enum::removeConstant( NumericConstant* a_pConstant )
{
    o_assert(getConstant(a_pConstant->getName()) != nullptr);
    o_assert(a_pConstant->getValueType() == this);
    removeElement(a_pConstant);
}

NumericConstant* Enum::getConstant( const string& a_strKey ) const
{
    value_vector::const_iterator it = m_Constants.begin();
    value_vector::const_iterator end = m_Constants.end();
    for(;it!=end;++it)
    {
        if((*it)->getName() == a_strKey) return *it;
    }
    return nullptr;
}

void Enum::valueFromString( const string& a_strIn, void* a_pDest ) const
{
    size_t i = 0;
    size_t count = getConstantCount();
    for(;i<count;++i)
    {
        size_t constantValue = 0;
        reflection::NumericConstant* pConstant = getConstant(i);
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
        reflection::NumericConstant* pConstant = getConstant(i);
        pConstant->getValue(&constantValue);
        if(constantValue == *((size_t*)a_pSrc))
        {
            a_strOut = m_pOwner ? m_pOwner->getQualifiedName() + "::" + pConstant->getName() : pConstant->getName();
            return;
        }
    }
}

void Enum::elementAdded( LanguageElement* a_pElement )
{
    NumericConstant* pConstant = a_pElement->asNumericConstant();
    o_assert(pConstant);
    m_Constants.push_back(pConstant);
}

void Enum::elementRemoved( LanguageElement* a_pElement )
{
    NumericConstant* pConstant = a_pElement->asNumericConstant();
    o_assert(pConstant);
    m_Constants.erase(std::find(m_Constants.begin(), m_Constants.end(), pConstant));
}

void Enum::findConstantsWithValue( void* a_pSrc, vector<Constant*>& out ) const
{
    for(auto it = m_Constants.begin(); it != m_Constants.end(); ++it)
    {
        if((*it)->hasValue(a_pSrc)) out.push_back(*it);
    }
}

o_namespace_end(phantom, reflection)