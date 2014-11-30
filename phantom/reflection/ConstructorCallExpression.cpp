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
}

o_terminate_cpp(ConstructorCallExpression)
{
    m_pValueType->deallocate(m_pReturnStorage);
    m_pReturnStorage = nullptr;
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

void ConstructorCallExpression::eval() const
{
    vector<void*> addresses;
    addresses.resize(m_ConvertedArguments.size());
    size_t i = m_ConvertedArguments.size();
    while(i--) // evaluate arguments from right to left
    {
        Expression* pArgument = m_ConvertedArguments[i];
        o_assert(as<Expression*>(pArgument));

        if(pArgument->isAddressable())
        {
            pArgument->getValue(&addresses[i]);
        }
        else if(pArgument->hasValueStorage())
        {
            addresses[i] = pArgument->getValueStorageAddress();
        }
        else 
        {
            pArgument->getValue(m_TempValues[i]);
            addresses[i] = m_TempValues[i];
        }
    }
    m_pSubroutine->call(m_pReturnStorage, addresses.data());
    flush();
    // Directly destroy the return storage after the call
    m_pValueType->terminate(m_pReturnStorage);
    m_pValueType->uninstall(m_pReturnStorage);
    m_pValueType->destroy(m_pReturnStorage);
}

variant ConstructorCallExpression::compile( Compiler* a_pCompiler )
{
    return a_pCompiler->compile(this);
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
