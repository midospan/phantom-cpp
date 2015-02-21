/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "DataMember.h"
#include "DataMember.hxx"
#include "DataMemberExpression.h"
#include <phantom/vector.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), DataMember);
o_registerNTI((phantom), vector, (phantom::reflection::DataMember*));

o_namespace_begin(phantom, reflection) 

o_invalid_def(DataMember, Type::Invalid(), "<unknown-member>");

Class* const DataMember::metaType = o_type_of(phantom::reflection::DataMember);

DataMember::DataMember() 
    : m_uiOffset(0xffffffff)
    , m_pMemberAnonymousSection(nullptr)
{

}

DataMember::DataMember( Type* a_pValueType, const string& a_strName, size_t  a_uiOffset, Range* a_pRange, uint a_uiSerializationMask, modifiers_t a_Modifiers /*= 0*/ )
    : ValueMember(a_pValueType, a_strName, a_pRange, a_uiSerializationMask, a_Modifiers)
    , m_uiOffset(a_uiOffset)
    , m_pMemberAnonymousSection(nullptr)
{
}

DataMember::DataMember( Type* a_pValueType, const string& a_strName, Range* a_pRange, uint a_uiSerializationMask /*= 0xffffffff*/, modifiers_t a_Modifiers /*= 0*/ )
    : ValueMember(a_pValueType, a_strName, a_pRange, a_uiSerializationMask, a_Modifiers)
    , m_uiOffset(~size_t(0))
    , m_pMemberAnonymousSection(nullptr)
{

}

void DataMember::referencedElementRemoved( LanguageElement* a_pElement )
{
    ValueMember::referencedElementRemoved(a_pElement);
}

bool DataMember::referencesData( const void* a_pInstance, const phantom::data& a_Data ) const
{
    return m_pValueType->referencesData(getAddress(a_pInstance), a_Data);
}

o_namespace_end(phantom, reflection)