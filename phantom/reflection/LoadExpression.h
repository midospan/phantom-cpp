/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_LoadExpression_h__
#define o_phantom_reflection_LoadExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), LoadExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export LoadExpression : public Expression
{
    o_language_element;

public:
    LoadExpression(Expression* a_pLoadedExpression);

    virtual void               internalEval(void* a_pDest) const;

    virtual LoadExpression*    asLoadExpression() const  { return const_cast<LoadExpression*>(this); }

    virtual void flush() const { m_pLoadedExpression->flush(); }

    Expression* getLoadedExpression() const { return m_pLoadedExpression; }

    virtual LoadExpression*     clone() const;

    virtual bool hasValueStorage() const { return true; }

    virtual void* evalStorage() const { return m_pLoadedExpression->loadEffectiveAddress(); }

protected:
    Expression* m_pLoadedExpression;
};

o_namespace_end(phantom, reflection)



#endif
