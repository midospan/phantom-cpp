/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_ConstructorCallExpression_h__
#define o_phantom_reflection_ConstructorCallExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/CallExpression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), ConstructorCallExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export ConstructorCallExpression : public CallExpression
{
    o_language_element;

public:
    ConstructorCallExpression(Constructor* a_pConstructor);
    ConstructorCallExpression(Constructor* a_pConstructor, const vector<Expression*>& a_Expressions);
    ~ConstructorCallExpression();

    o_terminate();

    virtual ConstructorCallExpression* asConstructorCallExpression() const { return (ConstructorCallExpression*)this; }

    virtual void internalEval(void* a_pDest) const ;

    virtual void internalEval() const ;

    virtual bool hasValueStorage() const { return true; }

    virtual void referencedElementRemoved( LanguageElement* a_pElement );
    
};

o_namespace_end(phantom, reflection)



#endif
