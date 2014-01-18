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


Type::Type( const string& a_strName, bitfield a_Modifiers /*= 0*/ ) : TemplateElement(a_strName, a_Modifiers)
, m_uiSize(0)
, m_uiSerializedSize(0)
, m_uiResetSize(0)
, m_uiAlignment(0)
, m_pNestedTypes(nullptr)
, m_pNestedTypedefs(nullptr)
, m_pExtendedTypes(nullptr)
, m_pTypedefs(nullptr)
{
    m_uiBuildOrder = NextBuildOrderValue();
}

Type::Type( const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_Modifiers /*= 0*/ ) : TemplateElement(a_strName, a_Modifiers)
    , m_uiSize(a_uiSize)
    , m_uiAlignment(a_uiAlignment)
    , m_uiSerializedSize(a_uiSize)
    , m_uiResetSize(a_uiSize)
    , m_pNestedTypes(nullptr)
    , m_pNestedTypedefs(nullptr)
    , m_pExtendedTypes(nullptr)
    , m_pTypedefs(nullptr)
{
    m_uiBuildOrder = NextBuildOrderValue();
}

Type::Type( const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, uint a_uiGuid, bitfield a_Modifiers /*= 0*/ ) : TemplateElement(a_strName, a_uiGuid, a_Modifiers)
    , m_uiSize(a_uiSize)
    , m_uiAlignment(a_uiAlignment)
    , m_uiSerializedSize(a_uiSize)
    , m_uiResetSize(a_uiSize)
    , m_pNestedTypes(nullptr)
    , m_pNestedTypedefs(nullptr)
    , m_pExtendedTypes(nullptr)
    , m_pTypedefs(nullptr)
{
    m_uiBuildOrder = NextBuildOrderValue();
}

Type::~Type()
{

}

void Type::terminate()
{
    TemplateElement::terminate();
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

Namespace* Type::getNamespace() const
{
    return m_pOwner ? m_pOwner->asNamespace() : nullptr;
}

Type* Type::getOwnerType() const
{
    return m_pOwner ? m_pOwner->asType() : nullptr;
}

void Type::addNestedTypedef( const string& a_strTypedef, Type* a_pType )
{
    if(m_pNestedTypedefs == nullptr)
    {
        m_pNestedTypedefs = o_default_new(nested_typedef_map);
    }
    o_assert(m_pNestedTypedefs->find(a_strTypedef) == m_pNestedTypedefs->end(), "Typedef already registered");
    (*m_pNestedTypedefs)[a_strTypedef] = a_pType;
}

void Type::removeNestedTypedef( const string& a_strTypedef, Type* a_pType )
{
    o_assert(m_pNestedTypedefs);
    auto found = m_pNestedTypedefs->find(a_strTypedef);
    o_assert( found != m_pNestedTypedefs->end(), "Typedef not found");
    m_pNestedTypedefs->erase(found);
    if(m_pNestedTypedefs->empty()) 
    {
        o_default_delete(nested_typedef_map) m_pNestedTypedefs;
        m_pNestedTypedefs = nullptr;
    }
}

inline Type* Type::getNestedTypedef( const string& a_strTypedef ) const
{
    if(m_pNestedTypedefs == nullptr) return nullptr;
    auto found = m_pNestedTypedefs->find(a_strTypedef);
    if( found != m_pNestedTypedefs->end() ) return found->second;
    return nullptr;
}

LanguageElement* Type::getElement( const char* a_strName, template_specialization const* a_pTemplateSpecialization, function_signature const* a_pFunctionSignature, bitfield a_Modifiers /*= 0*/ ) const
{
    LanguageElement* pElement = TemplateElement::getElement(a_strName, a_pTemplateSpecialization, a_pFunctionSignature, a_Modifiers);
    if(pElement) return pElement;
    if(m_pNestedTypedefs)  
    {
        auto found = m_pNestedTypedefs->find(a_strName);
        if(found != m_pNestedTypedefs->end()) return found->second;
    }
    if(m_pNestedTypes)  
    {
        vector<Type*>::const_iterator it = m_pNestedTypes->begin();
        vector<Type*>::const_iterator end = m_pNestedTypes->end();
        for(;it != end; ++it)
        {
            if((*it)->matches(a_strName, a_pTemplateSpecialization, a_Modifiers))
            {
                return *it;
            }
            else if((*it)->asEnum())
            {
                LanguageElement* pConstant = (*it)->getElement(a_strName, a_pTemplateSpecialization, a_pFunctionSignature, a_Modifiers);
                if(pConstant) return pConstant;
            }
        }
    }
    return NULL;
}

void Type::addNestedType( Type* a_pType )
{
    addElement(a_pType);
}

void Type::removeNestedType( Type* a_pType )
{
    removeElement(a_pType);
}

void Type::elementAdded(LanguageElement* a_pElement)
{
    TemplateElement::elementAdded(a_pElement);
    Type* pType = a_pElement->asType();
    if(pType)
    {
        if(m_pNestedTypes == NULL)
        {
            m_pNestedTypes = o_default_new(vector<Type*>);
        }
        o_assert(std::find(m_pNestedTypes->begin(), m_pNestedTypes->end(), pType) == m_pNestedTypes->end(), "Type already added");
        m_pNestedTypes->push_back(pType);
    }
}

void Type::elementRemoved(LanguageElement* a_pElement)
{
    TemplateElement::elementRemoved(a_pElement);
    Type* pType = a_pElement->asType();
    if(pType)
    {
        o_assert(m_pNestedTypes);
        o_assert(pType->m_pOwner == this, "Type doesn't belong to this type");
        if(std::find(m_pNestedTypes->begin(), m_pNestedTypes->end(), pType) != m_pNestedTypes->end())
        {
            m_pNestedTypes->erase(std::find(m_pNestedTypes->begin(), m_pNestedTypes->end(), pType));
            if(m_pNestedTypes->size() == 0)
            {
                o_default_delete(vector<Type*>) m_pNestedTypes;
                m_pNestedTypes = nullptr;
            }
        }
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
        if(m_pNestedTypes AND (a_pClass == nullptr OR classOf<Type>()->isKindOf(a_pClass)))
        {
            for(auto it = m_pNestedTypes->begin(); it != m_pNestedTypes->end(); ++it)
            {
                out.push_back(*it);
            }
        }
    }

    void Type::smartCopy( void* a_pDest, void const* a_pSource, reflection::Type* a_pSourceType ) const
    {
        if(a_pSourceType == this)
            copy(a_pDest, a_pSource);
    }

    Type* Type::getCommonAncestor( Type* a_pType ) const
    {
        o_assert(a_pType);
        Type* pCommonType = const_cast<Type*>(this);
        Class::ERelation relationType = this->getRelationWith(a_pType);
        switch(relationType)
        {
        case Class::eRelation_Equal:
        case Class::eRelation_Parent:
            {
                // Keep same type
            }
            break;
        case Class::eRelation_Compatible:
        case Class::eRelation_GenericContentChild:
        case Class::eRelation_GenericContentParent:
            {
                // Not used
            }
            break;
        case Class::eRelation_Child:
            {
                pCommonType = a_pType;
            }
            break;
        default:
            {
                pCommonType = NULL;

                Class* class1 = this->asClass();
                Class* class2 = a_pType->asClass();
                if (class1 AND class2)
                {
                    uint uiSuperClassCount = class1->getSuperClassCount();
                    if (uiSuperClassCount > 0)
                    {
                        for (uint i = 0; i < uiSuperClassCount AND pCommonType == NULL; i++)
                        {
                            pCommonType = class1->getSuperClass(i)->getCommonAncestor(a_pType);						
                        }
                    }

                    uiSuperClassCount = class2->getSuperClassCount();
                    if (uiSuperClassCount > 0)
                    {
                        for (uint i = 0; i < uiSuperClassCount AND pCommonType == NULL; i++)
                        {
                            pCommonType = this->getCommonAncestor(class2->getSuperClass(i));						
                        }
                    }
                }
            }
            break;
        }

        return pCommonType;
    }

    void Type::moduleChanged( Module* a_pModule )
    {
        if(m_pExtendedTypes && a_pModule) 
        {
            for(auto it = m_pExtendedTypes->begin(); it != m_pExtendedTypes->end(); ++it)
            {
                a_pModule->addLanguageElement(*it);
            }
        }
    }

    DataPointerType* Type::getDataPointerType() const
    {
        if(m_pExtendedTypes == nullptr) return nullptr;
        for(auto it = m_pExtendedTypes->begin(); it != m_pExtendedTypes->end(); ++it)
        {
            DataPointerType* pDataPointerType = (*it)->asDataPointerType();
            if(pDataPointerType) return pDataPointerType;
        }
        return nullptr;
    }

    ReferenceType* Type::getReferenceType() const
    {
        if(m_pExtendedTypes == nullptr) return nullptr;
        for(auto it = m_pExtendedTypes->begin(); it != m_pExtendedTypes->end(); ++it)
        {
            ReferenceType* pDataPointerType = (*it)->asReferenceType();
            if(pDataPointerType) return pDataPointerType;
        }
        return nullptr;
    }

    ArrayType* Type::getArrayType( size_t a_uiCount ) const
    {
        if(m_pExtendedTypes == nullptr) return nullptr;
        for(auto it = m_pExtendedTypes->begin(); it != m_pExtendedTypes->end(); ++it)
        {
            ArrayType* pArrayType = (*it)->asArrayType();
            if(pArrayType && pArrayType->getCount() == a_uiCount) return pArrayType;
        }
        return nullptr;
    }

    Type* Type::getConstType() const
    {
        if(m_pExtendedTypes == nullptr) return nullptr;
        for(auto it = m_pExtendedTypes->begin(); it != m_pExtendedTypes->end(); ++it)
        {
            Type* pConstType = (*it)->asConstType();
            if(pConstType) return pConstType;
        }
        return nullptr;
    }

    DataPointerType* Type::pointerType() const
    {
        if(this == nullptr) return nullptr;
        if(m_pExtendedTypes == nullptr)
        {
            m_pExtendedTypes = new type_container;
        }
        DataPointerType* pType = getDataPointerType();
        if(pType == nullptr)
        {
            pType = createDataPointerType();
            m_pExtendedTypes->push_back(pType);
            if(m_pModule)
            {
                m_pModule->addLanguageElement(pType);
            }
            if(getNamespace())
            {
                getNamespace()->addType(pType);
            }
            else if(m_pOwner && m_pOwner->asType())
            {
                m_pOwner->asType()->addNestedType(pType);
            }
        }
        return pType;
    }

    ReferenceType* Type::referenceType() const
    {
        if(this == nullptr) return nullptr;
        if(m_pExtendedTypes == nullptr)
        {
            m_pExtendedTypes = new type_container;
        }
        ReferenceType* pType = getReferenceType();
        if(pType == nullptr)
        {
            pType = createReferenceType();
            m_pExtendedTypes->push_back(pType);
            if(m_pModule)
            {
                m_pModule->addLanguageElement(pType);
            }
            if(getNamespace())
            {
                getNamespace()->addType(pType);
            }
            else if(m_pOwner && m_pOwner->asType())
            {
                m_pOwner->asType()->addNestedType(pType);
            }
        }
        return pType;
    }

    ArrayType* Type::arrayType( size_t a_uiCount ) const
    {
        if(this == nullptr) return nullptr;
        if(m_pExtendedTypes == nullptr)
        {
            m_pExtendedTypes = new type_container;
        }
        ArrayType* pType = getArrayType(a_uiCount);
        if(pType == nullptr)
        {
            pType = createArrayType(a_uiCount);
            m_pExtendedTypes->push_back(pType);
            if(m_pModule)
            {
                m_pModule->addLanguageElement(pType);
            }
            if(getNamespace())
            {
                getNamespace()->addType(pType);
            }
            else if(m_pOwner && m_pOwner->asType())
            {
                m_pOwner->asType()->addNestedType(pType);
            }
        }
        return pType;
    }

    Type* Type::constType() const
    {
        if(this == nullptr) return nullptr;
        if(m_pExtendedTypes == nullptr)
        {
            m_pExtendedTypes = new type_container;
        }
        Type* pType = getConstType();
        if(pType == nullptr)
        {
            pType = createConstType();
            if(pType == this) return (Type*)this;
            m_pExtendedTypes->push_back(pType);
            if(m_pModule)
            {
                m_pModule->addLanguageElement(pType);
            }
            if(getNamespace())
            {
                getNamespace()->addType(pType);
            }
            else if(m_pOwner && m_pOwner->asType())
            {
                m_pOwner->asType()->addNestedType(pType);
            }
        }
        return pType;
    }

    void Type::teardownMetaDataCascade( size_t count )
    {
        if(m_pNestedTypes)
        {
            type_container::const_iterator it = m_pNestedTypes->begin();
            type_container::const_iterator end = m_pNestedTypes->end();
            for(;it != end; ++it)
            {
                (*it)->teardownMetaDataCascade(count);
            }
        }
        TemplateElement::teardownMetaDataCascade(count);
    }

    Type* Type::pointerType( size_t a_uiPointerLevel ) const
    {
        if(a_uiPointerLevel == 0) return (Type*)this;
        return pointerType()->pointerType(a_uiPointerLevel-1);
    }

    void Type::registerTypedef( Namespace* a_pNamespace, const string& a_strTypedefName )
    {
        if(m_pTypedefs == nullptr)
        {
            m_pTypedefs = new typedef_namespace_map;
        }
        (*m_pTypedefs)[a_pNamespace].push_back(a_strTypedefName);
    }

    void Type::unregisterTypedef( Namespace* a_pNamespace, const string& a_strTypedefName )
    {
        auto& vec = (*m_pTypedefs)[a_pNamespace];
        vec.erase(std::find(vec.begin(), vec.end(), a_strTypedefName));
        if(vec.empty())
            m_pTypedefs->erase(a_pNamespace);
        if(m_pTypedefs->empty())
        {
            delete m_pTypedefs;
            m_pTypedefs = nullptr;
        }
    }

    void Type::referencedElementRemoved( LanguageElement* a_pElement )
    {
        TemplateElement::referencedElementRemoved(a_pElement);
    }

o_cpp_end


