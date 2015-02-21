/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/DataMemberExpression.h>
#include <phantom/reflection/DataMemberExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), DataMemberExpression);

o_namespace_begin(phantom, reflection) 

DataMemberExpression::DataMemberExpression( Expression* a_pLeftExpression, DataMember* a_pDataMember ) 
    : LValueExpression(a_pLeftExpression->getValueType()->replicate(a_pDataMember->getValueType()), a_pDataMember->getValueType())
    , m_pLeftExpression(a_pLeftExpression)
    , m_pDataMember(a_pDataMember)
{
    if(m_pLeftExpression)
    {
        addSubExpression(m_pLeftExpression);
        if(NOT(m_pLeftExpression->hasEffectiveAddress()))
            setInvalid();
    }
    else setInvalid();
    if(m_pDataMember)
    {
        addReferencedElement(m_pDataMember);
    } 
    else setInvalid();
}

void DataMemberExpression::referencedElementRemoved( LanguageElement* a_pElement )
{
    Expression::referencedElementRemoved(a_pElement);
    if(m_pDataMember == a_pElement)
        m_pDataMember = nullptr;
}

void*    DataMemberExpression::internalEvalAddress() const
{
    return m_pDataMember->getAddress(m_pLeftExpression->loadEffectiveAddress());
}

DataMemberExpression* DataMemberExpression::clone() const
{
    return o_new(DataMemberExpression)(m_pLeftExpression, m_pDataMember);
}

LanguageElement* DataMemberExpression::getHatchedElement() const
{
    return m_pDataMember;
}

bool DataMemberExpression::isPersistent() const
{
    return Expression::isPersistent() AND m_pDataMember->isNative();
}

o_namespace_end(phantom, reflection)