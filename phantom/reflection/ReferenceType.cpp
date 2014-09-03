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

ReferenceType::ReferenceType( Type* a_pType ) : Type(e_reference, a_pType->getName()+'&'
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
    return a_pType->asReferenceType()
        OR m_pReferencedType->isConvertibleTo(a_pType)
        OR isImplicitlyConvertibleTo(a_pType);
}

boolean ReferenceType::isImplicitlyConvertibleTo( Type* a_pType ) const
{
    if(a_pType == this) return true;
    return m_pReferencedType->isImplicitlyConvertibleTo(a_pType) 
        OR (a_pType->asReferenceType() 
            AND m_pReferencedType->pointerType()->isImplicitlyConvertibleTo(a_pType->removeReference()->pointerType()));
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
            void* pBuffer = m_pReferencedType->newInstance();
            m_pReferencedType->copy(pBuffer, *((void**)a_pSrcValue));
            m_pReferencedType->convertValueTo(a_pDestType, a_pDestValue, pBuffer);
        }
    }
}

void ReferenceType::referencedElementRemoved( LanguageElement* a_pElement )
{
    Type::referencedElementRemoved(a_pElement);
    if(m_pReferencedType == a_pElement)
        m_pReferencedType = nullptr;
}

Expression* ReferenceType::solveExpression( Expression* a_pLeftExpression , const string& a_strName , const vector<TemplateElement*>* a_pTemplateSignature, const vector<LanguageElement*>* a_pFunctionSignature, bitfield a_Modifiers /* = 0 */ ) const
{
    return m_pReferencedType->solveExpression(a_pLeftExpression, a_strName, a_pTemplateSignature, a_pFunctionSignature, a_Modifiers);
}

void*   ReferenceType::allocate() const
{
    return m_pReferencedType->pointerType()->allocate();
}

void ReferenceType::deallocate( void* a_pInstance ) const
{
    m_pReferencedType->pointerType()->deallocate(a_pInstance);
}

void*   ReferenceType::allocate(size_t a_uiCount) const
{
    return m_pReferencedType->pointerType()->allocate(a_uiCount);
}

void ReferenceType::deallocate( void* a_pChunk, size_t a_uiCount ) const
{
    m_pReferencedType->pointerType()->deallocate(a_pChunk, a_uiCount);
}

void ReferenceType::safeConstruct( void* a_pBuffer ) const
{
    m_pReferencedType->pointerType()->safeConstruct(a_pBuffer);
}

void ReferenceType::safeConstruct( void* a_pBuffer, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    m_pReferencedType->pointerType()->safeConstruct(a_pBuffer, a_uiCount, a_uiChunkSectionSize);
}

void ReferenceType::construct( void* a_pBuffer ) const
{
    m_pReferencedType->pointerType()->construct(a_pBuffer);
}

void ReferenceType::construct( void* a_pBuffer, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    m_pReferencedType->pointerType()->construct(a_pBuffer, a_uiCount, a_uiChunkSectionSize);
}

void ReferenceType::destroy( void* a_pBuffer ) const
{
    m_pReferencedType->pointerType()->destroy(a_pBuffer);
}

void ReferenceType::destroy( void* a_pBuffer, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    m_pReferencedType->pointerType()->destroy(a_pBuffer, a_uiCount, a_uiChunkSectionSize);
}

Expression* ReferenceType::solveOperator( const string& a_strOp, const vector<Expression*>& a_Expressions, bitfield a_Modifiers ) const
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