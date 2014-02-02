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
#include <phantom/reflection/ReferenceType.h>
#include <phantom/reflection/ReferenceType.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), ReferenceType);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(ReferenceType);

ReferenceType::ReferenceType( Type* a_pType ) : Type(a_pType->getName()+'&'
, sizeof(void*)
, boost::alignment_of<void*>::value
, 0xFFFFFFFF
, 0)    
, m_pReferencedType(a_pType)
{
    addReferencedElement(m_pReferencedType);
}

boolean ReferenceType::isConvertibleTo( Type* a_pType ) const
{
    return m_pReferencedType->isConvertibleTo(a_pType);
}

boolean ReferenceType::isImplicitlyConvertibleTo( Type* a_pType ) const
{
    return m_pReferencedType->isImplicitlyConvertibleTo(a_pType);
}

Type* ReferenceType::createConstType() const
{
    return o_new(ConstReferenceType)(const_cast<ReferenceType*>(this));
}

void ReferenceType::convertValueTo( Type* a_pDestType, void* a_pDestValue, const void* a_pSrcValue ) const
{
    m_pReferencedType->convertValueTo(a_pDestType, a_pDestValue, a_pSrcValue);
}

void ReferenceType::referencedElementRemoved( LanguageElement* a_pElement )
{
    Type::referencedElementRemoved(a_pElement);
    if(m_pReferencedType == a_pElement)
        m_pReferencedType = nullptr;
}

o_namespace_end(phantom, reflection)