/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "MemberFunctionPointerCallExpression.h"
#include "MemberFunctionPointerCallExpression.hxx"
#include "Compiler.h"
/* *********************************************** */
o_registerN((phantom, reflection), MemberFunctionPointerCallExpression);

o_namespace_begin(phantom, reflection)
    
MemberFunctionPointerCallExpression::MemberFunctionPointerCallExpression( MemberFunctionPointerType* a_pMemberFunctionPointerType, Expression* a_pObjectExpression, Expression* a_pMemberExpression, const vector<Expression*>& a_Arguments ) 
    : CallExpression(a_Arguments, a_pMemberFunctionPointerType->getReturnType())
    , m_pMemberFunctionPointerType(a_pMemberFunctionPointerType)
    , m_pObjectExpression(a_pObjectExpression)
    , m_pMemberExpression(a_pMemberExpression)
{        
    if(m_pObjectExpression)
    {
        addSubExpression(m_pObjectExpression);
        if(m_pObjectExpression->getValueType() == nullptr 
            OR NOT(m_pObjectExpression->hasEffectiveAddress()))
            setInvalid();
    }
    else setInvalid();
}

MemberFunctionPointerCallExpression::~MemberFunctionPointerCallExpression() 
{

}

o_terminate_cpp(MemberFunctionPointerCallExpression)
{

}

void MemberFunctionPointerCallExpression::internalEval( void* a_pDest ) const
{
    vector<void*> addresses;
    evaluateArguments(addresses);
    void* pMemberBuffer = m_pMemberFunctionPointerType->newInstance();
    m_pMemberExpression->load(pMemberBuffer);
    if(m_pReturnStorage)
    {
        m_pMemberFunctionPointerType->call( pMemberBuffer, m_pObjectExpression->loadEffectiveAddress(), addresses.data(), m_pReturnStorage);
        getValueType()->copy(a_pDest, m_pReturnStorage); // then copy the return value to dest
    }
    else // void call
    {
        m_pMemberFunctionPointerType->call(pMemberBuffer, m_pObjectExpression->loadEffectiveAddress(), addresses.data());
    }
    m_pMemberFunctionPointerType->deleteInstance(pMemberBuffer);
}

void MemberFunctionPointerCallExpression::internalEval() const
{
    vector<void*> addresses;
    evaluateArguments(addresses);
    void* pMemberBuffer = m_pMemberFunctionPointerType->newInstance();
    m_pMemberExpression->load(pMemberBuffer);
    m_pMemberFunctionPointerType->call(pMemberBuffer, m_pObjectExpression->loadEffectiveAddress(), addresses.data());
    flush();
    m_pMemberFunctionPointerType->deleteInstance(pMemberBuffer);
}

o_namespace_end(phantom, reflection)
