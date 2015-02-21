/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_ReturnStatement_h__
#define o_phantom_reflection_ReturnStatement_h__



/* ****************** Includes ******************* */
#include "phantom/reflection/Statement.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), ReturnStatement);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export ReturnStatement : public Statement
{
    o_language_element;

    friend class Block;
public:
    ReturnStatement();
    ReturnStatement(Expression* a_pReturnExpression);

    virtual void internalEval() const ;

    void setExpression(Expression* a_pReturnExpression);

    Expression* getExpression() const { return m_pReturnExpression; }

protected:
    void setExpressionString(string a_Expression);
    string getExpressionString() const;
    virtual void restore();
    void checkValidity();
    void ancestorChanged(LanguageElement* a_pOwner);

protected:
    Expression* m_pReturnExpression;
    Expression* m_pConvertedReturnExpression;
    string*     m_pExpressionString;
    vector<Statement*> m_RAIIDestructionStatements;

};

o_namespace_end(phantom, reflection)



#endif
