/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_PlacementConstructionExpression_h__
#define o_phantom_reflection_PlacementConstructionExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/CallExpression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), PlacementConstructionExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export PlacementConstructionExpression : public CallExpression
{
    o_language_element;

public:
    PlacementConstructionExpression(Constructor* a_pConstructor, Expression* a_pPlace, const vector<Expression*>& a_Arguments);
    PlacementConstructionExpression(Constructor* a_pConstructor, Expression* a_pPlace, Expression* a_pArgument);
    ~PlacementConstructionExpression();

    o_terminate();

    virtual PlacementConstructionExpression* asPlacementConstructionExpression() const { return (PlacementConstructionExpression*)this; }

    virtual void internalEval(void* a_pDest) const ;

    virtual void internalEval() const ;

    Expression* getPlaceExpression() const { return m_pPlaceExpression; }

protected:
    virtual Type* returnStorageType() const { return nullptr; }

protected:
    Expression*         m_pPlaceExpression;
    
};

o_namespace_end(phantom, reflection)



#endif
