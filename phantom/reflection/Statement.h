/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Statement_h__
#define o_phantom_reflection_Statement_h__



/* ****************** Includes ******************* */
#include "phantom/reflection/Evaluable.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Statement);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Statement : public Evaluable
{
    friend class Block;
    friend class Subroutine;

public:
    Statement();

    virtual void            internalEval() const = 0;

    virtual Statement*      asStatement() const { return (Statement*)this; }
    
    virtual void            flush() const {}

    Block*		            getRootBlock() const;

    Subroutine*             getSubroutine() const;

    Statement*              getNextStatement() const;

    void                    addTemporaryObjectDestruction(CallExpression* a_pExpression);

    virtual Statement*      evaluateExpressionLifeTime(Expression* a_pExpression) const
    {
        return const_cast<Statement*>(this);
    }

protected:
    void evalTemporaryObjectDestructions() const;
    virtual void restore() {}

protected:
    size_t                  m_uiIndexInBlock;
    list<CallExpression*>* m_pTemporaryObjectExpressions;
};

o_namespace_end(phantom, reflection)



#endif
