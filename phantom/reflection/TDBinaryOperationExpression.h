/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_TDBinaryOperationExpression_h__
#define o_phantom_reflection_TDBinaryOperationExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), TDBinaryOperationExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export TDBinaryOperationExpression : public Expression
{
    o_language_element;

public:
    TDBinaryOperationExpression( Type* a_pValueType, const string& a_strOperator, Expression* a_pLeftExpression, Expression* a_pRightExpression );
    ~TDBinaryOperationExpression();

    const string&   getOperator() const { return m_strOperator; }

    virtual TDBinaryOperationExpression*  asTDBinaryOperationExpression() const { return (TDBinaryOperationExpression*)this; }

    virtual void    internalEval(void* a_pDest) const { o_exception(exception::reflection_runtime_exception, "Invalid binary operation evaluation"); }

    virtual void    flush() const { m_pLeftExpression->flush(); m_pRightExpression->flush(); }

    virtual bool    hasValueStorage() const { return false; }

    Expression*     getLeftExpression() const { return m_pLeftExpression; }
    Expression*     getRightExpression() const { return m_pRightExpression; }

    virtual TDBinaryOperationExpression* clone() const { return nullptr; }

protected:
    string          m_strOperator;
    Expression*     m_pLeftExpression;
    Expression*     m_pRightExpression;

};

o_namespace_end(phantom, reflection)



#endif
