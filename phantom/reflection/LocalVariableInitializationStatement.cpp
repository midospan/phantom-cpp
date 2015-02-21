/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/LocalVariableInitializationStatement.h>
#include <phantom/reflection/LocalVariableInitializationStatement.hxx>
#include <phantom/reflection/Interpreter.h>
#include <phantom/reflection/LocalVariable.h>
#include <phantom/reflection/Expression.h>
/* *********************************************** */
o_registerN((phantom, reflection), LocalVariableInitializationStatement);

o_namespace_begin(phantom, reflection) 

LocalVariableInitializationStatement::LocalVariableInitializationStatement( LocalVariable* a_pLocalVariable, Expression* a_pRightExpression /*= nullptr*/ ) 
    : LValueInitializationStatement(a_pLocalVariable->getValueType(), a_pRightExpression)
    , m_pLocalVariable(a_pLocalVariable)
{
    if(m_pLocalVariable)
    {
        addReferencedElement(m_pLocalVariable);
    }
    else setInvalid();
}

LocalVariableInitializationStatement::~LocalVariableInitializationStatement()
{
    
}

LocalVariableInitializationStatement* LocalVariableInitializationStatement::clone() const
{
    return o_new(LocalVariableInitializationStatement)(m_pLocalVariable, m_pRightExpression);
}

void LocalVariableInitializationStatement::internalEval() const
{
    if(m_pRightExpression)
    {
        void* _where = phantom::interpreter()->getBasePointer() + m_pLocalVariable->getFrameOffset();
        m_pRightExpression->internalEval(_where);
        LValueInitializationStatement::internalEval();
    }
}

Type* LocalVariableInitializationStatement::getValueType() const
{
    return m_pLocalVariable->getValueType();
}

o_namespace_end(phantom, reflection)
