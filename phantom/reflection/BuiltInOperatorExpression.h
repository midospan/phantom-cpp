/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_BuiltInOperatorExpression_h__
#define o_phantom_reflection_BuiltInOperatorExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), BuiltInOperatorExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export BuiltInOperatorExpression : public Expression
{
    o_language_element;

public:
    BuiltInOperatorExpression( BuiltInOperator* a_pOperator, Type* a_pResultType, Expression** a_Arguments, operation_delegate_t a_Delegate );
    ~BuiltInOperatorExpression();

    virtual BuiltInOperatorExpression* asBuiltInOperatorExpression() const { return (BuiltInOperatorExpression*)this; }

    virtual void    internalEval(void* a_pDest) const;

    virtual void    internalEval() const;

    virtual void    flush() const;

    virtual BuiltInOperatorExpression* clone() const;

    BuiltInOperator* getOperator() const { return m_pOperator; }

    Expression* getArgument(size_t i) const {return m_Arguments[i]; }

    virtual bool hasValueStorage() const { return true; }

    virtual void*   evalStorage() const { internalEval(m_Buffer); return m_Buffer; }
 
protected:
    BuiltInOperator* m_pOperator;
    Expression* m_Arguments[3];
    operation_delegate_t m_Delegate;
    mutable byte m_Buffer[sizeof(double_size_t)]; /// big enough to receive any fundamental type

};

o_namespace_end(phantom, reflection)



#endif
