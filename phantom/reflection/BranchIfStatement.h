/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_BranchIfStatement_h__
#define o_phantom_reflection_BranchIfStatement_h__



/* ****************** Includes ******************* */
#include "phantom/reflection/BranchStatement.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), BranchIfStatement);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export BranchIfStatement : public BranchStatement
{
    o_language_element;

public:
    BranchIfStatement() : m_pExpression(nullptr), m_pConvertedExpression(nullptr), m_pExpressionString(nullptr) {}
    BranchIfStatement(Expression* a_pExpression);
    BranchIfStatement(Expression* a_pExpression, LabelStatement* a_pLabelStatement);

    virtual void internalEval() const ;
    
    virtual void flush() const;

    Expression* getExpression() const { return m_pExpression; } 

    Expression* getConvertedExpression() const { return m_pConvertedExpression; } 

protected:
    void setExpressionString(string a_Expression);
    string getExpressionString() const;
    virtual void restore();
    virtual void elementRemoved( LanguageElement* a_pElement );

protected:
    Expression* m_pExpression;
    Expression* m_pConvertedExpression;
    string*     m_pExpressionString;

};

o_namespace_end(phantom, reflection)



#endif
