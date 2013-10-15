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
#include <phantom/reflection/Type.h>
/* *********************************************** */


o_enumNC((phantom,reflection),(Type),ERelation, (
          eRelation_None
        , eRelation_Equal
        , eRelation_Child
        , eRelation_Parent
        , eRelation_GenericContentChild
        , eRelation_GenericContentParent
    ))

o_registerNC((phantom,reflection),(Type),ERelation)

o_cpp_begin 

ReflectionCPP__________________________________________________________________________________
o_signal(kindCreated, (void*))
o_signal(kindDestroyed, (void*))
__________________________________________________________________________________ReflectionCPP


Type::Type( const string& a_strName, bitfield a_bfModifiers /*= bitfield()*/ ) : TemplateElement(a_strName, a_bfModifiers)
, m_uiSize(0)
, m_uiSerializedSize(0)
, m_uiResetSize(0)
, m_uiAlignment(0)
, m_pSubTypes(nullptr)
{

}

Type::Type( const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_bfModifiers /*= bitfield()*/ ) : TemplateElement(a_strName, a_bfModifiers)
    , m_uiSize(a_uiSize)
    , m_uiAlignment(a_uiAlignment)
    , m_uiSerializedSize(a_uiSize)
    , m_uiResetSize(a_uiSize)
    , m_pSubTypes(nullptr)
{

}

Type::Type( const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, uint a_uiGuid, bitfield a_bfModifiers /*= bitfield()*/ ) : TemplateElement(a_strName, a_uiGuid, a_bfModifiers)
    , m_uiSize(a_uiSize)
    , m_uiAlignment(a_uiAlignment)
    , m_uiSerializedSize(a_uiSize)
    , m_uiResetSize(a_uiSize)
    , m_pSubTypes(nullptr)
{

}

Type::~Type()
{
    if(getNamespace())
    {
        getNamespace()->removeType(this);
    }
    else if(getOwnerType())
    {
        getOwnerType()->removeSubType(this);
    }
    while(m_pSubTypes != nullptr)
    {
        o_dynamic_delete(m_pSubTypes->back());
    }
}


Type::ERelation Type::getRelationWith( Type* a_pType ) const
{
    if(a_pType == this) return eRelation_Equal;
    return eRelation_None;
}

boolean Type::areValueEqual( void const* a_pSrc0, void const* a_pSrc1 ) const
{
    return memcmp(a_pSrc0, a_pSrc1, m_uiSize) == 0;
}

void Type::removeFromNamespace()
{
    o_assert(m_pOwner);
    getNamespace()->removeType(this);
}

DataPointerType* Type::createDataPointerType() const
{
    return o_new(DataPointerType)(const_cast<Type*>(this));
}

ArrayType* Type::createArrayType(size_t a_uiCount) const
{
    return o_new(ArrayType)(const_cast<Type*>(this), a_uiCount);
}

ReferenceType* Type::createReferenceType() const 
{
    return o_new(ReferenceType)(const_cast<Type*>(this));
}

void* Type::newInstance() const
{
    void* pInstance = o_dynamic_pool_allocate(m_uiSize); 
    construct(pInstance);
    return pInstance;
}

void Type::deleteInstance(void* a_pInstance) const
{
    destroy(a_pInstance);
    o_dynamic_pool_deallocate(a_pInstance, m_uiSize); 
}

boolean Type::matches( const char* a_strName, template_specialization const* a_TemplateSpecialization, bitfield a_bfModifiers ) const
{
  return (m_strName == a_strName) 
      AND (a_TemplateSpecialization == NULL OR a_TemplateSpecialization->empty())
      AND m_bfModifiers.matchesMask(a_bfModifiers);
}

Namespace* Type::getNamespace() const
{
    return m_pOwner ? m_pOwner->asNamespace() : nullptr;
}

Type* Type::getOwnerType() const
{
    return m_pOwner ? m_pOwner->asType() : nullptr;
}

LanguageElement* Type::getElement( const char* a_strName, template_specialization const* a_pTemplateSpecialization, function_signature const* a_pFunctionSignature, bitfield a_bfModifiers /*= bitfield()*/ ) const
{
    if(m_pSubTypes == NULL)  return NULL;
    vector<Type*>::const_iterator it = m_pSubTypes->begin();
    vector<Type*>::const_iterator end = m_pSubTypes->end();
    for(;it != end; ++it)
    {
        if((*it)->matches(a_strName, a_pTemplateSpecialization, a_bfModifiers))
        {
            return *it;
        }
        else if((*it)->isEnum())
        {
            LanguageElement* pConstant = (*it)->getElement(a_strName, a_pTemplateSpecialization, a_pFunctionSignature, a_bfModifiers);
            if(pConstant) return pConstant;
        }
    }
    return NULL;
}

void Type::addSubType( Type* a_pType )
{
    if(m_pSubTypes == NULL)
    {
        m_pSubTypes = o_default_new(vector<Type*>);
    }
    o_assert(a_pType->m_pOwner == NULL, "Type has already been attached to a Namespace or Type");
    o_assert(std::find(m_pSubTypes->begin(), m_pSubTypes->end(), a_pType) == m_pSubTypes->end(), "Type already added");
    m_pSubTypes->push_back(a_pType);
    addElement(a_pType);
}

void Type::removeSubType( Type* a_pType )
{
    o_assert(m_pSubTypes);
    o_assert(a_pType->m_pOwner == this, "Type doesn't belong to this type");
    o_assert(std::find(m_pSubTypes->begin(), m_pSubTypes->end(), a_pType) != m_pSubTypes->end(), "Type not fount");
    m_pSubTypes->erase(std::find(m_pSubTypes->begin(), m_pSubTypes->end(), a_pType));
    removeElement(a_pType);
    if(m_pSubTypes->size() == 0)
    {
        o_default_delete(vector<Type*>) m_pSubTypes;
        m_pSubTypes = nullptr;
    }
}

#if o__bool__use_kind_creation_signal
void                Type::fireKindCreated(void* a_pObject) const
{
    o_emit kindCreated(a_pObject);
}
#endif

#if o__bool__use_kind_destruction_signal
void                Type::fireKindDestroyed(void* a_pObject) const
{
    o_emit kindDestroyed(a_pObject);
}

#endif


#if o__bool__use_kind_creation_signal
    o_signal_data_definition(kindCreated, void*)
#endif

#if o__bool__use_kind_destruction_signal
    o_signal_data_definition(kindDestroyed, void*)
#endif

    void Type::convertValueTo( Type* a_pDestType, void* a_pDestValue, void const* a_pSrcValue ) const
    {
        ReferenceType* pRefType = a_pDestType->asReferenceType();
        if(pRefType)
        {
            pRefType->getReferencedType()->copy(a_pDestValue, a_pSrcValue); // for references, copy address to dest
        }
        // By default just copy
        else copy(a_pDestValue, a_pSrcValue);
    }

    boolean Type::isConvertibleTo( Type* a_pType ) const
    {
        if(a_pType->removeConst() == removeConst()) return true;
        ReferenceType* pRefType = a_pType->asReferenceType();
        if(pRefType->getReferencedType()->asReferenceType()) return false;
        return pRefType AND isConvertibleTo(pRefType->getReferencedType());
    }

    boolean Type::isImplicitlyConvertibleTo( Type* a_pType ) const
    {
        if(a_pType->removeConst() == removeConst()) return true;
        ReferenceType* pRefType = a_pType->asReferenceType();
        if(pRefType->getReferencedType()->asReferenceType()) return false;
        return pRefType AND isImplicitlyConvertibleTo(pRefType->getReferencedType());
    }

    void Type::aligner::construct( Type* a_pType )
    {
        a_pType->construct(m_pStartAddress+m_WrittenBytes);
        size_t alignment = a_pType->m_uiAlignment;
        if(alignment > m_MaxAlignment)
        {
            m_MaxAlignment = alignment;
        }
    
        size_t modulo = m_WrittenBytes % alignment;
        if(modulo)
            m_WrittenBytes += (alignment - modulo);
    
        m_WrittenBytes += a_pType->m_uiSize;
    }

    void Type::aligner::safeConstruct( Type* a_pType )
    {
        a_pType->safeConstruct(m_pStartAddress+m_WrittenBytes);
        size_t alignment = a_pType->m_uiAlignment;
        if(alignment > m_MaxAlignment)
        {
            m_MaxAlignment = alignment;
        }

        size_t modulo = m_WrittenBytes % alignment;
        if(modulo)
            m_WrittenBytes += (alignment - modulo);

        m_WrittenBytes += a_pType->m_uiSize;
    }

    void Type::aligner::destroy( Type* a_pType )
    {
        a_pType->destroy(m_pStartAddress+m_WrittenBytes);
        size_t alignment = a_pType->m_uiAlignment;
        if(alignment > m_MaxAlignment)
        {
            m_MaxAlignment = alignment;
        }
    
        size_t modulo = m_WrittenBytes % alignment;
        if(modulo)
            m_WrittenBytes += (alignment - modulo);
    
        m_WrittenBytes += a_pType->m_uiSize;
    }

    void Type::aligner::push( Type* a_pType, byte* a_pValueBytes )
    {
        memcpy(m_pStartAddress+m_WrittenBytes, a_pValueBytes, a_pType->m_uiSize);
        size_t alignment = a_pType->m_uiAlignment;
        if(alignment > m_MaxAlignment)
        {
            m_MaxAlignment = alignment;
        }
    
        size_t modulo = m_WrittenBytes % alignment;
        if(modulo)
            m_WrittenBytes += (alignment - modulo);
    
        m_WrittenBytes += a_pType->m_uiSize;
    }

    void Type::aligner::skip( Type* a_pType )
    {
        size_t alignment = a_pType->m_uiAlignment;
        if(alignment > m_MaxAlignment)
        {
            m_MaxAlignment = alignment;
        }


        size_t modulo = m_WrittenBytes % alignment;
        if(modulo)
            m_WrittenBytes += (alignment - modulo);

        m_WrittenBytes += a_pType->m_uiSize;
    }

    byte* Type::aligner::terminate()
    {
        size_t modulo = m_WrittenBytes % m_MaxAlignment;
        if(modulo)
            return m_pStartAddress + (m_MaxAlignment - modulo);

        return m_pStartAddress+m_WrittenBytes;
    }


    size_t Type::alignment::computer::push( Type* a_pType )
    {
        size_t alignment = a_pType->m_uiAlignment;
        if(alignment > m_MaxAlignment)
        {
            m_MaxAlignment = alignment;
        }
        
        size_t modulo = m_Result % alignment;
        if(modulo)
            m_Result += (alignment - modulo);
        
        size_t offset = m_Result;
        m_Result += a_pType->m_uiSize;
        return offset;
    }


    size_t Type::alignment::computer::compute()
    {
        if(m_Result == 0 OR m_MaxAlignment == 0) return 0;
        size_t modulo = m_Result % m_MaxAlignment;
        if(modulo)
            m_Result += (m_MaxAlignment - modulo);
        
        return m_Result;
    }

    void Type::getElements( vector<LanguageElement*>& out, Class* a_pClass ) const
    {
        TemplateElement::getElements(out, a_pClass);
        if(m_pSubTypes AND (a_pClass == nullptr OR classOf<Type>()->isKindOf(a_pClass)))
        {
            for(auto it = m_pSubTypes->begin(); it != m_pSubTypes->end(); ++it)
            {
                out.push_back(*it);
            }
        }
    }

o_cpp_end


