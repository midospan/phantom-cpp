/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_LabelStatement_h__
#define o_phantom_reflection_LabelStatement_h__



/* ****************** Includes ******************* */
#include "phantom/reflection/Statement.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), LabelStatement);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export LabelStatement : public Statement
{
    o_language_element;

    friend class Subroutine;
    friend class BranchStatement;

public:
    LabelStatement();
    LabelStatement(const string& a_strLabelName);

    virtual LabelStatement* asLabelStatement() const { return (LabelStatement*)this; }

    virtual void    internalEval() const { /*bypass*/ }

    virtual void    flush() const {}

    const string&   getLabelName() const { return m_strLabelName; }

    size_t          getIndex() const { return m_uiIndex; }

protected:
    void            ancestorChanged(LanguageElement* a_pLanguageElement);

protected:
    string  m_strLabelName;
    size_t  m_uiIndex;
    size_t  m_uiBranchCount;
};

o_namespace_end(phantom, reflection)



#endif
