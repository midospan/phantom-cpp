/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_BranchIfNotStatement_h__
#define o_phantom_reflection_BranchIfNotStatement_h__



/* ****************** Includes ******************* */
#include "phantom/reflection/BranchStatement.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), BranchIfNotStatement);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export BranchIfNotStatement : public BranchStatement
{
    o_language_element;

public:
    BranchIfNotStatement() : m_pExpression(nullptr), m_pConvertedExpression(nullptr), m_pExpressionString(nullptr) {}
    BranchIfNotStatement(Expression* a_pExpression);
    BranchIfNotStatement( Expression* a_pExpression, LabelStatement* a_pLabelStatement );

    virtual void internalEval() const ;
    
    virtual void flush() const;

    Expression* getExpression() const { return m_pExpression; } 

    Expression* getConvertedExpression() const { return m_pConvertedExpression; } 

protected:
    void setExpressionString(string a_Expression);
    string getExpressionString() const;
    virtual void restore();
    virtual void elementRemoved(LanguageElement* a_pElement);

protected:
    Expression* m_pExpression;
    Expression* m_pConvertedExpression;
    string* m_pExpressionString;
};

o_namespace_end(phantom, reflection)



#endif
