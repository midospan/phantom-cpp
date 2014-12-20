/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "PlacementConstructionExpression.h"
#include "PlacementConstructionExpression.hxx"
#include "Compiler.h"
/* *********************************************** */
o_registerN((phantom, reflection), PlacementConstructionExpression);

o_namespace_begin(phantom, reflection)
    
PlacementConstructionExpression::PlacementConstructionExpression( Constructor* a_pConstructor, Expression* a_pPlace, const vector<Expression*>& a_Arguments ) 
    : CallExpression(a_pConstructor, a_Arguments, a_pConstructor->getOwner()->asClassType()->pointerType())
    , m_pPlaceExpression(a_pPlace)
{        
    if(m_pPlaceExpression)
    {
        addSubExpression(m_pPlaceExpression);
        if(m_pPlaceExpression->getValueType() == nullptr OR m_pPlaceExpression->getValueType()->removeReference()->asDataPointerType() == nullptr)
            setInvalid();
    }
    else setInvalid();
}

PlacementConstructionExpression::PlacementConstructionExpression( Constructor* a_pConstructor, Expression* a_pPlace, Expression* a_pArgument )
    : CallExpression(a_pConstructor, a_pArgument, a_pConstructor->getOwner()->asClassType()->pointerType())
    , m_pPlaceExpression(a_pPlace)
{
    if(m_pPlaceExpression)
    {
        addSubExpression(m_pPlaceExpression);
        if(m_pPlaceExpression->getValueType() == nullptr OR m_pPlaceExpression->getValueType()->removeReference()->asDataPointerType() == nullptr)
            setInvalid();
    }
    else setInvalid();
}

PlacementConstructionExpression::~PlacementConstructionExpression() 
{

}

o_terminate_cpp(PlacementConstructionExpression)
{

}

void PlacementConstructionExpression::internalEval( void* a_pDest ) const
{
    void* pPlace;
    m_pPlaceExpression->load(&pPlace);
    vector<void*> addresses;
    evaluateArguments(addresses);
    m_pSubroutine->call(pPlace, addresses.data());
    *((void**)a_pDest) = pPlace;
}

void PlacementConstructionExpression::internalEval() const
{
    void* pPlace;
    m_pPlaceExpression->load(&pPlace);
    vector<void*> addresses;
    evaluateArguments(addresses);
    m_pSubroutine->call(pPlace, addresses.data());
    flush();
}

o_namespace_end(phantom, reflection)
