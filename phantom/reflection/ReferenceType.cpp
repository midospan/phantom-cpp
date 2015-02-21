/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/ReferenceType.h>
#include <phantom/reflection/ReferenceType.hxx>
#include <phantom/reflection/Expression.h>
/* *********************************************** */
o_registerN((phantom, reflection), ReferenceType);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(ReferenceType);

ReferenceType::ReferenceType( Type* a_pReferencedType, const string& a_strName ) 
    : Type(e_reference, a_strName
    , sizeof(void*)
    , boost::alignment_of<void*>::value
    , a_pReferencedType->isNative() ? modifiers_t(o_native) : 0)    
    , m_pReferencedType(a_pReferencedType)
{
    addReferencedElement(m_pReferencedType);
}

ReferenceType::~ReferenceType()
{
}

void ReferenceType::referencedElementRemoved( LanguageElement* a_pElement )
{
    Type::referencedElementRemoved(a_pElement);
    if(m_pReferencedType == a_pElement)
    {
        m_pReferencedType = nullptr;
    }
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

o_namespace_end(phantom, reflection)