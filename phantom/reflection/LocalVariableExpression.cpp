/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/LocalVariableExpression.h>
#include <phantom/reflection/LocalVariableExpression.hxx>
#include <phantom/reflection/LocalVariable.h>
#include <phantom/reflection/Interpreter.h>
/* *********************************************** */
o_registerN((phantom, reflection), LocalVariableExpression);
o_namespace_begin(phantom, reflection) 

LocalVariableExpression::LocalVariableExpression(LocalVariable* a_pLocalVariable)
    : LValueExpression(a_pLocalVariable->getValueType())
    , m_pLocalVariable(a_pLocalVariable)
{
    addReferencedElement(a_pLocalVariable);
}

void* LocalVariableExpression::internalEvalAddress() const
{
    return phantom::interpreter()->getBasePointer() + m_pLocalVariable->getFrameOffset();
}

LocalVariableExpression* LocalVariableExpression::clone() const
{
    return o_new(LocalVariableExpression)(m_pLocalVariable);
}

bool LocalVariableExpression::isPersistent() const
{
    return Expression::isPersistent() AND m_pLocalVariable->isNative();
}

o_namespace_end(phantom, reflection)
