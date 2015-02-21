/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/BuiltInConversionExpression.h>
#include <phantom/reflection/BuiltInConversionExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), BuiltInConversionExpression);

o_namespace_begin(phantom, reflection) 

BuiltInConversionExpression::BuiltInConversionExpression( Expression* a_pInputExpression, conversion* a_pConversion, int a_iConversionType ) 
    : Expression(a_pConversion ? a_pConversion->output : Type::Invalid())
    , m_pInputExpression(a_pInputExpression)
    , m_pTempValue(nullptr)
    , m_pConversion(a_pConversion)
    , m_pStorage(nullptr)
    , m_iConversionType(a_iConversionType)
{
    // o_assert(a_pInputExpression->getValueType()->removeQualifiers()->equals(a_pConversion->input->removeQualifiers()));
    if(m_pInputExpression->getValueType()->asPrimitiveType() == nullptr)
        setInvalid();
    if(m_pInputExpression)
    {
        addSubExpression(m_pInputExpression);
        if(NOT(m_pInputExpression->hasValueStorage()))
        {
            m_pTempValue = m_pInputExpression->getValueType()->allocate();
            addReferencedElement(m_pInputExpression->getValueType());
        }
    }
    else setInvalid();
    if(NOT(getValueType()->asReferenceType()))
    {
        m_pStorage = getValueType()->allocate();
    }
}

BuiltInConversionExpression::~BuiltInConversionExpression()
{
    delete m_pConversion;
}

void BuiltInConversionExpression::internalEval( void* a_pDest ) const
{
    if(m_pTempValue)
    {
        m_pInputExpression->internalEval(m_pTempValue);
    }
    m_pConversion->apply(m_pTempValue ? m_pTempValue : m_pInputExpression->evalStorage(), a_pDest);
}

o_terminate_cpp(BuiltInConversionExpression)
{
    if(m_pTempValue)
    {
        m_pInputExpression->getValueType()->deallocate(m_pTempValue);
        m_pTempValue = nullptr;
    }
    if(m_pStorage)
    {
        getValueType()->deallocate(m_pStorage);
        m_pStorage = nullptr;
    }
}

BuiltInConversionExpression* BuiltInConversionExpression::clone() const
{
    return o_new(BuiltInConversionExpression)(m_pInputExpression, m_pConversion ? m_pConversion->clone() : nullptr, m_iConversionType);
}

void BuiltInConversionExpression::elementRemoved( LanguageElement* a_pElement )
{
    Expression::elementRemoved(a_pElement);
    if(m_pInputExpression == a_pElement)
    {
        setInvalid();
        if(m_pTempValue)
        {
            m_pInputExpression->getValueType()->deallocate(m_pTempValue);
            m_pTempValue = nullptr;
        }
        m_pInputExpression = nullptr;
    }
}

void BuiltInConversionExpression::referencedElementRemoved( LanguageElement* a_pElement )
{
    // Release m_pTempValue if its value type is destroyed
    if(m_pTempValue AND a_pElement == m_pInputExpression->getValueType())
    {
        m_pInputExpression->getValueType()->deallocate(m_pTempValue);
        m_pTempValue = nullptr;
    }
    if(m_pStorage AND a_pElement == getValueType())
    {
        getValueType()->deallocate(m_pStorage);
        m_pStorage = nullptr;
    }
}

void* BuiltInConversionExpression::evalStorage() const
{
    if(m_pTempValue)
    {
        m_pInputExpression->internalEval(m_pTempValue);
    }
    m_pConversion->apply(m_pTempValue ? m_pTempValue : m_pInputExpression->evalStorage(), m_pStorage);
    return m_pStorage;
}

o_namespace_end(phantom, reflection)
