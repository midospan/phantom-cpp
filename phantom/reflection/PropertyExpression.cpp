/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/PropertyExpression.h>
#include <phantom/reflection/PropertyExpression.hxx>
#include <phantom/reflection/CallExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), PropertyExpression);

o_namespace_begin(phantom, reflection) 

PropertyExpression::PropertyExpression( Expression* a_pLeftExpression, Property* a_pProperty ) 
    : LValueExpression(a_pLeftExpression->getValueType()->replicate(a_pProperty->getValueType()->removeConstReference()), a_pProperty->getValueType()->removeConstReference())
    , m_pLeftExpression(a_pLeftExpression)
    , m_pProperty(a_pProperty)
{
    if(NOT(a_pLeftExpression->getValueType()->asReferenceType()))
    {
        setInvalid();
    }
    else if(a_pLeftExpression->getValueType()->removeReference()->removeConst() != a_pProperty->getOwner())
    {
        Class* pLeftClass = a_pLeftExpression->getValueType()->removeReference()->removeConst()->asClass();
        if(pLeftClass)
        {
            Class* pOwnerClass = a_pProperty->getOwner()->asClass();
            if(pOwnerClass)
            {
                if(pLeftClass->getBaseClassOffsetCascade(pOwnerClass) != 0)
                    setInvalid();
            }
            else setInvalid();
        }
        else setInvalid();
    }
    addSubExpression(m_pLeftExpression);
    addReferencedElement(a_pProperty);

    m_pBuffer = m_pValueType->removeReference()->allocate();
    m_pValueType->removeReference()->construct(m_pBuffer);
    m_pValueType->removeReference()->install(m_pBuffer);
    m_pValueType->removeReference()->initialize(m_pBuffer);
}

o_terminate_cpp(PropertyExpression)
{
    m_pValueType->removeReference()->terminate(m_pBuffer);
    m_pValueType->removeReference()->uninstall(m_pBuffer);
    m_pValueType->removeReference()->destroy(m_pBuffer);
    m_pValueType->removeReference()->deallocate(m_pBuffer);
}

void PropertyExpression::referencedElementRemoved( LanguageElement* a_pElement )
{
    Expression::referencedElementRemoved(a_pElement);
    if(m_pProperty == a_pElement)
        m_pProperty = nullptr;
}

void* PropertyExpression::internalEvalAddress() const
{
    m_pProperty->getValue(m_pLeftExpression->loadEffectiveAddress(), m_pBuffer);
    return (void*)m_pBuffer;
}

void PropertyExpression::flush() const
{
    void* pAddress = m_pLeftExpression->loadEffectiveAddress();
    bool bBlockSignal = areSignalsBlocked() AND m_pProperty->getSignal();
    if(bBlockSignal)
    {
        m_pProperty->getSignal()->block(pAddress);
    }
    m_pProperty->setValue(m_pLeftExpression->loadEffectiveAddress(), m_pBuffer);
    if(bBlockSignal)
    {
        m_pProperty->getSignal()->unblock(pAddress);
    }
    m_pLeftExpression->flush();
}

PropertyExpression* PropertyExpression::clone() const
{
    return o_new(PropertyExpression)(m_pLeftExpression, m_pProperty);
}

LanguageElement* PropertyExpression::getHatchedElement() const
{
    return m_pProperty;
}

bool PropertyExpression::isPersistent() const
{
    return Expression::isPersistent() AND m_pProperty->isNative();
}

o_namespace_end(phantom, reflection)