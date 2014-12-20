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
#include <phantom/reflection/ConstType.h>
#include <phantom/reflection/ConstType.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), ConstType);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(ConstType);

ConstType::ConstType( Type* a_pType ) 
    : Type(a_pType->getTypeId()
            , a_pType->getName()
            , a_pType->getSize()
            , a_pType->getAlignment()
            , a_pType->getModifiers()|o_const)
    , m_pConstedType(a_pType)
{
    addReferencedElement(a_pType);
}

ConstType::~ConstType()
{
    if(m_pConstedType)
    {
        m_pConstedType->removeExtendedType(this);
    }
}

bool ConstType::isConvertibleTo( Type* a_pType ) const
{
    return m_pConstedType->isConvertibleTo(a_pType);
}

bool ConstType::isImplicitlyConvertibleTo( Type* a_pType ) const
{
    return m_pConstedType->isImplicitlyConvertibleTo(a_pType->removeConst());
}

string ConstType::getQualifiedName() const
{
    return m_pConstedType->getQualifiedName()+" const";
}

string ConstType::getDecoratedName() const
{
    return m_pConstedType->getDecoratedName()+" const";
}

string ConstType::getQualifiedDecoratedName() const
{
    return m_pConstedType->getQualifiedDecoratedName()+" const";
}

void ConstType::referencedElementRemoved( LanguageElement* a_pElement )
{
    if(m_pConstedType == a_pElement)
    {
        m_pConstedType->removeExtendedType(this);
        m_pConstedType = nullptr;
    }
}

void ConstType::getElements( vector<LanguageElement*>& out, Class* a_pClass /*= nullptr */ ) const
{
    m_pConstedType->getElements(out, a_pClass);
}

bool ConstType::referencesData( const void* a_pInstance, const phantom::data& a_Data ) const
{
    return m_pConstedType->referencesData(a_pInstance, a_Data);
}

void ConstType::fetchExpressions( Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter, uint a_uiSerializationMask ) const
{
    m_pConstedType->fetchExpressions(a_pInstanceExpression, out, a_Filter, a_uiSerializationMask);
}

o_namespace_end(phantom, reflection)



