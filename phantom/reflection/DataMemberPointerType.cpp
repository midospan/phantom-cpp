/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "DataMemberPointerType.h"
#include "DataMemberPointerType.hxx"
/* *********************************************** */
o_registerN((phantom, reflection), DataMemberPointerType);

o_namespace_begin(phantom, reflection) 

o_invalid_def(DataMemberPointerType, ClassType::Invalid(), Type::Invalid(), o_invalid);

Class* const DataMemberPointerType::metaType = o_type_of(phantom::reflection::DataMemberPointerType);

DataMemberPointerType::DataMemberPointerType( ClassType* a_pObjectType, Type* a_pValueType, modifiers_t a_uiModifiers /*= 0*/ )
    : MemberPointerType(a_pObjectType, sizeof(DataMember*), boost::alignment_of<DataMember*>::value, a_uiModifiers)
    , m_pValueType(a_pValueType)
{
    if(m_pValueType) 
        addReferencedElement(m_pValueType);
}

DataMemberPointerType::DataMemberPointerType(ClassType* a_pObjectType, Type* a_pValueType, size_t a_uiSize, size_t a_uiAlignment, modifiers_t a_uiModifiers) 
    : MemberPointerType(a_pObjectType, a_uiSize, a_uiAlignment, a_uiModifiers)
    , m_pValueType(a_pValueType)
{
    if(m_pValueType) addReferencedElement(m_pValueType);
}

void DataMemberPointerType::referencedElementRemoved( LanguageElement* a_pElement )
{
    if(m_pValueType == a_pElement)
    {
        m_pValueType = nullptr;
    }
    MemberPointerType::referencedElementRemoved(a_pElement);
}

size_t DataMemberPointerType::getOffset( void* a_pPointer ) const
{
    return static_cast<DataMember*>(a_pPointer)->getOffset();
}

void DataMemberPointerType::setValue( void* a_pPointer, void* a_pObject, void const* src ) const
{
    static_cast<DataMember*>(a_pPointer)->setValue(a_pObject, src);
}

void DataMemberPointerType::getValue( void* a_pPointer, void const* a_pObject, void* dest ) const
{
    static_cast<DataMember*>(a_pPointer)->getValue(a_pObject, dest);
}

void* DataMemberPointerType::getAddress( void* a_pPointer, void const* a_pObject ) const
{
    return static_cast<DataMember*>(a_pPointer)->getAddress(a_pObject);
}                                                                           

o_namespace_end(phantom, reflection)