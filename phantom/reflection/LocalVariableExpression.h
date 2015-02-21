/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_LocalVariableExpression_h__
#define o_phantom_reflection_LocalVariableExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/LValueExpression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), LocalVariableExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export LocalVariableExpression : public LValueExpression
{
    o_language_element;

public:
    LocalVariableExpression(LocalVariable* a_pLocalVariable);
    o_destructor ~LocalVariableExpression(void)     {}

    virtual void*    internalEvalAddress() const;

    LocalVariable* getLocalVariable() const { return m_pLocalVariable; }

    virtual LocalVariableExpression*     clone() const;

    virtual bool            isPersistent() const;

protected:
    LocalVariable* m_pLocalVariable;

};

o_namespace_end(phantom, reflection)



#endif
