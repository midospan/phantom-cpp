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
#include <phantom/reflection/Expression.h>
/* *********************************************** */
o_registerN((phantom, reflection), ReferenceType);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(ReferenceType);

ReferenceType::ReferenceType( Type* a_pReferencedType ) 
    : Type(e_reference, a_pReferencedType->getName()
    , sizeof(void*)
    , boost::alignment_of<void*>::value
    , a_pReferencedType->isNative() ? modifiers_t(o_native) : modifiers_t())    
    , m_pReferencedType(a_pReferencedType)
{
    addReferencedElement(m_pReferencedType);
}

ReferenceType::~ReferenceType()
{
    if(m_pReferencedType)
    {
        m_pReferencedType->removeExtendedType(this);
    }
}

boolean ReferenceType::isConvertibleTo( Type* a_pType ) const
{
    return a_pType->asReferenceType()
        OR isImplicitlyConvertibleTo(a_pType)
        OR m_pReferencedType->isConvertibleTo(a_pType);
}

boolean ReferenceType::isImplicitlyConvertibleTo( Type* a_pType ) const
{
    if(a_pType == this) return true;
    return (a_pType->asReferenceType() 
        AND m_pReferencedType->pointerType()->isImplicitlyConvertibleTo(a_pType->removeReference()->pointerType()))
        OR m_pReferencedType->isImplicitlyConvertibleTo(a_pType) ;
}

void ReferenceType::convertValueTo( Type* a_pDestType, void* a_pDestValue, const void* a_pSrcValue ) const
{
    if(a_pDestType == this)
    {
        *((void**)a_pDestValue) = *((void**)a_pSrcValue);
        return;
    }
    if(a_pDestType->asReferenceType())
    {
        // Reference to reference convertion is same as pointer to pointer convertion
        m_pReferencedType->pointerType()->convertValueTo(a_pDestType->removeReference()->pointerType(), a_pDestValue, a_pSrcValue);
    }
    else 
    {
        // First convert from dest type reference type, 
        if(isImplicitlyConvertibleTo(a_pDestType->referenceType()))
        {
            void* pConvertedReference;
            convertValueTo(a_pDestType->referenceType(), &pConvertedReference, a_pSrcValue);
            // then dereference the content from the reference value
            a_pDestType->copy(a_pDestValue, pConvertedReference);
        }
        else 
        {
            m_pReferencedType->convertValueTo(a_pDestType, a_pDestValue, *((void**)a_pSrcValue));
        }
    }
}

void ReferenceType::referencedElementRemoved( LanguageElement* a_pElement )
{
    Type::referencedElementRemoved(a_pElement);
    if(m_pReferencedType == a_pElement)
    {
        m_pReferencedType->removeExtendedType(this);
        m_pReferencedType = nullptr;
    }
}

Expression* ReferenceType::solveExpression( Expression* a_pLeftExpression , const string& a_strName , const vector<TemplateElement*>* a_pTemplateSignature, const vector<LanguageElement*>* a_pFunctionSignature, modifiers_t a_Modifiers /* = 0 */ ) const
{
    return m_pReferencedType->solveExpression(a_pLeftExpression, a_strName, a_pTemplateSignature, a_pFunctionSignature, a_Modifiers);
}

void*   ReferenceType::allocate() const
{
     return o_allocate(void*);
}

void ReferenceType::deallocate( void* a_pInstance ) const
{
    o_deallocate(static_cast<void**>(a_pInstance), void*);
}

void*   ReferenceType::allocate(size_t a_uiCount) const
{
    return o_allocate_n(a_uiCount, void*);
}

void ReferenceType::deallocate( void* a_pChunk, size_t a_uiCount ) const
{
    o_deallocate_n(static_cast<void**>(a_pChunk), a_uiCount, void*);
}

void ReferenceType::safeConstruct( void* a_pBuffer ) const
{
    *reinterpret_cast<void**>(a_pBuffer) = NULL;
}

void ReferenceType::safeConstruct( void* a_pBuffer, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    memset(a_pBuffer, 0, a_uiCount*a_uiChunkSectionSize*m_uiSize);
}

void ReferenceType::construct( void* a_pBuffer ) const
{
    o_unused(a_pBuffer);
}

void ReferenceType::construct( void* a_pBuffer, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    o_unused(a_pBuffer);
    o_unused(a_uiCount);
    o_unused(a_uiChunkSectionSize);
}

void ReferenceType::destroy( void* a_pBuffer ) const
{
    o_unused(a_pBuffer);
}

void ReferenceType::destroy( void* a_pBuffer, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    o_unused(a_pBuffer);
    o_unused(a_uiCount);
    o_unused(a_uiChunkSectionSize);
}

Expression* ReferenceType::solveOperator( const string& a_strOp, const vector<Expression*>& a_Expressions, modifiers_t a_Modifiers ) const
{
    if(a_strOp == "&" && a_Expressions.size() == 1)
    {
        return a_Expressions.back()->address();
    }
    else 
    {
        return m_pReferencedType->solveOperator(a_strOp, a_Expressions, a_Modifiers);
    }
}

o_namespace_end(phantom, reflection)