/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_ExpressionStatement_h__
#define o_phantom_reflection_ExpressionStatement_h__



/* ****************** Includes ******************* */
#include "phantom/reflection/Statement.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), ExpressionStatement);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export ExpressionStatement : public Statement
{
    o_language_element;

public:
    ExpressionStatement();
    ExpressionStatement(Expression* a_pExpression);

    virtual void internalEval() const ;
    
    virtual void flush() const;

    Expression* getExpression() const { return m_pExpression; }

protected:
    void elementRemoved( LanguageElement* a_pElement );

protected:
    Expression* m_pExpression;

};

o_namespace_end(phantom, reflection)



#endif
