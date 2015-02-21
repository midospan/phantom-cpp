/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_BranchStatement_h__
#define o_phantom_reflection_BranchStatement_h__



/* ****************** Includes ******************* */
#include "phantom/reflection/Statement.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), BranchStatement);
o_fwd(class, phantom, reflection, LabelStatement);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export BranchStatement : public Statement
{
    o_language_element;

public:
    BranchStatement();
    BranchStatement(LabelStatement* a_pLabelStatement);

    virtual void internalEval() const ;
    
    Expression* getExpression() const;

    void setLabelStatement(LabelStatement* a_pLabelStatement);

    LabelStatement* getLabelStatement() const { return m_pLabelStatement; }
    
protected:
    virtual void restore();
    virtual void elementRemoved( LanguageElement* a_pElement );
    virtual void ancestorChanged(LanguageElement* a_pOwner);

protected:
    LabelStatement* m_pLabelStatement;
    size_t m_uiLabelStatementIndex;
};

o_namespace_end(phantom, reflection)



#endif
