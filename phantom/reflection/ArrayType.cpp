/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/ArrayType.h>
#include <phantom/reflection/ArrayType.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), ArrayType);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(ArrayType);

ArrayType::ArrayType( Type* a_pItemType, size_t a_uiCount, modifiers_t modifiers /*= 0*/ ) 
    : Type(e_array, string("[")+phantom::lexical_cast<string>(a_uiCount)+']'
    , a_uiCount*a_pItemType->getSize(), a_pItemType->getAlignment(), a_pItemType->getModifiers()|modifiers)
    , m_pItemType(a_pItemType)
    , m_uiCount(a_uiCount) /// m_uiCount == 0 => unknown bound array
{
    if(m_pItemType)
        addReferencedElement(m_pItemType);
    else 
        setInvalid();
}

ArrayType::~ArrayType( void )
{

}

void ArrayType::serialize( void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    m_pItemType->serialize(a_pInstance, m_uiCount, m_uiSize/m_uiCount, a_OutBranch, a_uiSerializationMask, a_pDataBase);
}

void ArrayType::deserialize( void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    m_pItemType->deserialize(a_pInstance, m_uiCount, m_uiSize/m_uiCount, a_InBranch, a_uiSerializationMask, a_pDataBase);
}

void ArrayType::copy( void* a_pDest, void const* a_pSrc ) const
{
    size_t i = 0;
    size_t storedTypeSize = m_pItemType->getSize();
    for(;i<m_uiCount;++i)
    {
        m_pItemType->copy((byte*)a_pDest + i*storedTypeSize, (byte*)a_pSrc + i*storedTypeSize);
    }
}

void ArrayType::referencedElementRemoved( LanguageElement* a_pItem )
{
    Type::referencedElementRemoved(a_pItem);
    if(m_pItemType == a_pItem)
    {
        m_pItemType = nullptr;
    }
}

void ArrayType::valueFromString(const string& a_str, void* dest) const
{
    *reinterpret_cast<void**>(dest) = ::phantom::lexical_cast<void*>(a_str);
}

void ArrayType::valueToString(string& a_str, const void* src) const
{
    a_str += ::phantom::lexical_cast<string>(*((void**)src));
}

string ArrayType::getQualifiedName() const
{
    return m_pItemType->getQualifiedName()+'['+phantom::lexical_cast<string>(m_uiCount)+']';
}

string ArrayType::getDecoratedName() const
{
    return m_pItemType->getDecoratedName()+'['+phantom::lexical_cast<string>(m_uiCount)+']';
}

string ArrayType::getQualifiedDecoratedName() const
{
    return m_pItemType->getQualifiedDecoratedName()+'['+phantom::lexical_cast<string>(m_uiCount)+']';
}

bool ArrayType::partialAccepts( Type* a_pType, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_Deductions ) const
{
    if(a_pType->asArrayType())
    {
        if(a_pType->asArrayType()->getItemCount() == m_uiCount)
        {
            a_Score+=10;
            return m_pItemType->partialAccepts(a_pType->removeArray(), a_Score, a_Deductions);
        }
    }
    return false;
}

o_namespace_end(phantom, reflection)