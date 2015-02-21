/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_VariableExpression_h__
#define o_phantom_reflection_VariableExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/LValueExpression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), VariableExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export VariableExpression : public LValueExpression
{
    o_language_element;

public:
    VariableExpression(Variable* a_pVariable, Expression* a_pChildExpression = nullptr);
    o_destructor ~VariableExpression(void)     {}

    virtual VariableExpression*asVariableExpression() const { return (VariableExpression*)this; }


    virtual void*    internalEvalAddress() const;

    virtual VariableExpression*     clone() const;

    Variable* getVariable() const { return m_pVariable; }

protected:
    Variable*     m_pVariable;

};

o_namespace_end(phantom, reflection)



#endif
