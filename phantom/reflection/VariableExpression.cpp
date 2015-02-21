/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/VariableExpression.h>
#include <phantom/reflection/VariableExpression.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), VariableExpression);
o_namespace_begin(phantom, reflection) 

VariableExpression::VariableExpression(Variable* a_pVariable, Expression* a_pChildExpression /*= nullptr*/)
    : LValueExpression(a_pVariable->getValueType())
    , m_pVariable(a_pVariable)
{
    addReferencedElement(a_pVariable);
    if(a_pChildExpression)
        addSubExpression(a_pChildExpression);
}

void*    VariableExpression::internalEvalAddress() const
{
    return m_pVariable->getAddress();
}

VariableExpression* VariableExpression::clone() const
{
    return o_new(VariableExpression)(m_pVariable, getElementCount() ? getElement(0)->asExpression() : nullptr);
}

o_namespace_end(phantom, reflection)
