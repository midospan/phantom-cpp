/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_LValueExpression_h__
#define o_phantom_reflection_LValueExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), LValueExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export LValueExpression : public Expression
{
    o_language_element;

public:
    LValueExpression(Type* a_pRValueType, modifiers_t modifiers = 0);
    LValueExpression(Type* a_pLValueType, Type* a_pRValueType, modifiers_t modifiers = 0);
    o_destructor ~LValueExpression(void)     {}

    virtual LValueExpression* asLValueExpression() const { return (LValueExpression*)this; }

    virtual void internalEval(void* a_pDest) const;

    virtual void*    internalEvalAddress() const = 0;

protected:
    Type* m_pRValueType;

};

o_namespace_end(phantom, reflection)



#endif
