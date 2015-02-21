/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "ConstructorCallExpression.h"
#include "ConstructorCallExpression.hxx"
#include "Compiler.h"
/* *********************************************** */
o_registerN((phantom, reflection), ConstructorCallExpression);

o_namespace_begin(phantom, reflection)

ConstructorCallExpression::ConstructorCallExpression( Constructor* a_pConstructor )
    : CallExpression(a_pConstructor, a_pConstructor->getOwner()->asType())
{

}
    
ConstructorCallExpression::ConstructorCallExpression( Constructor* a_pConstructor, const vector<Expression*>& a_Expressions ) 
    : CallExpression(a_pConstructor, a_Expressions, a_pConstructor->getOwner()->asType())
{        
    o_assert(m_pValueType->isCopyable());
    m_pReturnStorage = m_pValueType->allocate();
}

ConstructorCallExpression::~ConstructorCallExpression() 
{
}

o_terminate_cpp(ConstructorCallExpression)
{
    m_pValueType->deallocate(m_pReturnStorage);
    m_pReturnStorage = nullptr;
}

void ConstructorCallExpression::internalEval( void* a_pDest ) const
{
    vector<void*> addresses;
    evaluateArguments(m_Arguments, addresses);
    m_pSubroutine->call(a_pDest, addresses.data());
}

void ConstructorCallExpression::internalEval() const
{
    vector<void*> addresses;
    evaluateArguments(m_Arguments, addresses);
    m_pSubroutine->call(m_pReturnStorage, addresses.data());
    flush();
    /// (destruction after the call is context dependant => if stored in a const ref or an r-value reference, life time is longer and goes to the end of the scope, else its destroyed after current statement
}

void ConstructorCallExpression::referencedElementRemoved( LanguageElement* a_pElement )
{
    if(m_pValueType == a_pElement)
    {
        m_pValueType->deallocate(m_pReturnStorage);
        m_pReturnStorage = nullptr;
    }
    CallExpression::referencedElementRemoved(a_pElement);
}

o_namespace_end(phantom, reflection)
