/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Evaluable_h__
#define o_phantom_reflection_Evaluable_h__

/* ****************** Includes ******************* */
#include "phantom/reflection/LanguageElement.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Evaluable);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Evaluable : public LanguageElement
{
    o_language_element;

public:
    Evaluable() : m_pSubExpressions(nullptr) {}

    virtual Evaluable*      asEvaluable() const { return (Evaluable*)this; }

    void                    eval() const 
    {
        if(isInvalid())
        {
            o_exception(exception::reflection_runtime_exception, "Invalid expression cannot be evaluated");
        }
        internalEval();
    }

    virtual Statement*      evaluateExpressionLifeTime(Expression* a_pExpression) const
    {
        return getEnclosingStatement();
    }

protected:
    virtual void            flush() const {}
    virtual void            internalEval() const = 0;
    void                    addSubExpression( Expression*& a_prExpression );
    void                    removeSubExpression( Expression* a_pExpression );
    void                    elementRemoved( LanguageElement* a_pElement );
protected:
    vector<Expression*>*    m_pSubExpressions;
};

o_namespace_end(phantom, reflection)

#endif
