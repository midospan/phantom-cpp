/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/ConstantExpression.h>
#include <phantom/reflection/DataExpression.h>
#include <phantom/reflection/ConstantExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), ConstantExpression);
o_namespace_begin(phantom, reflection) 

ConstantExpression::ConstantExpression(Constant* a_pConstant, Expression* a_pChildExpression /*= nullptr*/)
    : Expression(a_pConstant->getValueType())
    , m_pConstant(a_pConstant)
{
    if(a_pChildExpression)
        addSubExpression(a_pChildExpression);
    if(m_pConstant)
    {
        if(m_pConstant->getOwner() == nullptr) 
            addElement(m_pConstant);
        else 
            addReferencedElement(m_pConstant);
    }
    else 
    {
        setInvalid();
    }
    m_pTempValue = m_pValueType->allocate();
    m_pConstant->getValue(m_pTempValue);
}

ConstantExpression::~ConstantExpression( void )
{
    if(m_pValueType) m_pValueType->deallocate(m_pTempValue);
}

void ConstantExpression::setValue( void const* a_pSrc ) const
{
    o_exception(exception::reflection_runtime_exception, "Constant cannot be assigned");
}

void ConstantExpression::internalEval( void* a_pDest ) const
{
    m_pConstant->getValue(a_pDest);
}

LanguageElement* ConstantExpression::hatch()
{
    Constant* pConstant = m_pConstant;
    if(pConstant->getOwner() == this)
    {
        removeElement(pConstant);
    }
    o_dynamic_delete (this);
    return pConstant;
}

ConstantExpression* ConstantExpression::clone() const
{
    // TODO : add clone function to Constant
    Constant* pConstant = m_pConstant;
    bool bOwnsConstant = pConstant AND pConstant->getOwner() == this;
    if(bOwnsConstant)
    {
        pConstant = pConstant->clone();
    }
    return o_new(ConstantExpression)(pConstant, (getElementCount() == 2) ? getElement(0)->asExpression() : nullptr);
}

void ConstantExpression::elementRemoved( LanguageElement* a_pElement )
{
    Expression::elementRemoved(a_pElement);
    if(a_pElement == m_pConstant) 
    {
        m_pConstant = nullptr;
    }
}

void ConstantExpression::referencedElementRemoved( LanguageElement* a_pElement )
{
    if(a_pElement == m_pConstant)
    {
        m_pConstant = nullptr;
    }
    else if(a_pElement == m_pValueType)
    {
        if(m_pTempValue)
        {
            m_pValueType->deallocate(m_pTempValue);
            m_pTempValue = nullptr;
        }
    }
    Expression::referencedElementRemoved(a_pElement);
}

bool ConstantExpression::isPersistent() const
{
    return Expression::isPersistent() AND (m_pConstant->getOwner() == this OR m_pConstant->isNative());
}

o_namespace_end(phantom, reflection)
