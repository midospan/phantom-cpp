/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_LValueInitializationStatement_h__
#define o_phantom_reflection_LValueInitializationStatement_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Statement.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), LValueInitializationStatement);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export LValueInitializationStatement : public Statement
{
    o_language_element;

public:
    LValueInitializationStatement( Type* a_pValueType, Expression* a_pRightExpression );
    ~LValueInitializationStatement();

    virtual LValueInitializationStatement* asLValueInitializationStatement() const { return (LValueInitializationStatement*)this; }

    Expression*     getRightExpression() const { return m_pRightExpression; }


    virtual void internalEval() const = 0
    {
        evalTemporaryObjectDestructions();
    }

    virtual Statement* evaluateExpressionLifeTime(Expression* a_pExpression) const;

    Type* getValueType() const {return m_pValueType; }

protected:
    Type* m_pValueType; 
    Expression* m_pRightExpression;
};

o_namespace_end(phantom, reflection)



#endif
