/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "ConstructorCallExpression.h"
#include "ConstructorCallExpression.hxx"
#include "Compiler.h"
/* *********************************************** */
o_registerN((phantom, reflection), ConstructorCallExpression);

o_namespace_begin(phantom, reflection)
    
ConstructorCallExpression::ConstructorCallExpression( Constructor* a_pConstructor, const vector<Expression*>& a_Expressions ) 
    : CallExpression(a_pConstructor, a_Expressions, a_pConstructor->getOwner()->asType())
{        
    o_assert(m_pValueType->isCopyable());
    m_pReturnStorage = m_pValueType->allocate();
}

ConstructorCallExpression::~ConstructorCallExpression() 
{
    // Release temp buffers
    m_pValueType->deallocate(m_pReturnStorage);
}

void ConstructorCallExpression::getValue( void* a_pDest ) const
{
    vector<void*> addresses;
    addresses.resize(m_Arguments.size());
    size_t i = m_Arguments.size();
    while(i--) // evaluate arguments from right to left
    {
        Expression* pArgument = m_Arguments[i];
        if(pArgument->hasEffectiveAddress())
        {
            addresses[i] = pArgument->loadEffectiveAddress();
        }
        else 
        {
            pArgument->getValue(m_TempValues[i]);
            addresses[i] = m_TempValues[i];
        }
    }
    m_pSubroutine->call(a_pDest, addresses.data());
}

variant ConstructorCallExpression::compile( Compiler* a_pCompiler )
{
    return a_pCompiler->compile(this);
}

o_namespace_end(phantom, reflection)
