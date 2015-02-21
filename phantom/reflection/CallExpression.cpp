/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "CallExpression.h"
#include "CallExpression.hxx"
#include "ConstantExpression.h"
#include "ExpressionStatement.h"
#include "Block.h"
#include "Compiler.h"
/* *********************************************** */
o_registerN((phantom, reflection), CallExpression);

o_namespace_begin(phantom, reflection)

Type* CallExpressionTypeDeducer(Type* a_pInput)
{
    if(a_pInput == nullptr) return nullptr;
    LValueReferenceType* pReferenceType = a_pInput->asLValueReferenceType();
    if(pReferenceType) return pReferenceType;
    RValueReferenceType* pRValueReferenceType = a_pInput->asRValueReferenceType();
    if(pRValueReferenceType) return pRValueReferenceType;
    ClassType* pClassType = a_pInput->asClassType();
    if(pClassType) return pClassType->rvalueReferenceType();
    return a_pInput;
}

CallExpression::CallExpression( Subroutine* a_pSubroutine, const vector<Expression*>& a_Arguments, Type* a_pConstructedType ) 
    : Expression(CallExpressionTypeDeducer(a_pConstructedType ? a_pConstructedType : a_pSubroutine ? a_pSubroutine->getReturnType() : nullptr))
    , m_pSubroutine(a_pSubroutine)
    , m_Arguments(a_Arguments)
    , m_pReturnStorage(nullptr)
    , m_bSkipFirstArgument(false)
{
    if(m_pSubroutine == nullptr) setInvalid();
    else addReferencedElement(m_pSubroutine);
    for(size_t i = 0; i<m_Arguments.size(); ++i)
    {
        if(m_Arguments[i] AND m_Arguments[i]->getOwner()) m_Arguments[i] = m_Arguments[i]->clone();
    }
}

CallExpression::CallExpression( Subroutine* a_pSubroutine, Expression* a_pArgument, Type* a_pConstructedType ) 
    : Expression(CallExpressionTypeDeducer(a_pConstructedType ? a_pConstructedType : a_pSubroutine ? a_pSubroutine->getReturnType() : nullptr))
    , m_pSubroutine(a_pSubroutine)
    , m_pReturnStorage(nullptr)
    , m_bSkipFirstArgument(false)
{
    m_Arguments.push_back((a_pArgument AND a_pArgument->getOwner()) ? a_pArgument->clone() : a_pArgument);
    if(m_pSubroutine == nullptr) setInvalid();
    else addReferencedElement(m_pSubroutine);
}

CallExpression::CallExpression( const vector<Expression*>& a_Arguments, Type* a_pConstructedType ) 
    : Expression(a_pConstructedType ? a_pConstructedType : nullptr)
    , m_pSubroutine(nullptr)
    , m_Arguments(a_Arguments)
    , m_pReturnStorage(nullptr)
    , m_bSkipFirstArgument(false)
{
    for(size_t i = 0; i<m_Arguments.size(); ++i)
    {
        if(m_Arguments[i] AND m_Arguments[i]->getOwner()) m_Arguments[i] = m_Arguments[i]->clone();
    }
}

CallExpression::CallExpression( Expression* a_pArgument, Type* a_pConstructedType /*= nullptr*/ ) 
    : Expression(CallExpressionTypeDeducer(a_pConstructedType ? a_pConstructedType : nullptr))
    , m_pSubroutine(nullptr)
    , m_pReturnStorage(nullptr)
    , m_bSkipFirstArgument(false)
{
    m_Arguments.push_back((a_pArgument AND a_pArgument->getOwner()) ? a_pArgument->clone() : a_pArgument);
}

CallExpression::CallExpression( Subroutine* a_pFunction, Type* a_pConstructedType /*= nullptr*/ )
    : Expression(CallExpressionTypeDeducer(a_pConstructedType ? a_pConstructedType : nullptr))
    , m_pSubroutine(nullptr)
    , m_pReturnStorage(nullptr)
    , m_bSkipFirstArgument(false)
{
}

Type* CallExpression::returnStorageType() const 
{
    return m_pSubroutine ? storageType(m_pSubroutine->getReturnType()) : nullptr;
}

o_initialize_cpp(CallExpression)
{
    Type* pStorageType = returnStorageType();
    if(pStorageType)
    {
        m_pReturnStorage = pStorageType->allocate();
    }
    bool thisCall = m_pSubroutine ? (m_pSubroutine->getABI() == e_thiscall) : false;
    if(thisCall)
    {
        m_bSkipFirstArgument = 0;
    }
    else if(m_pSubroutine)
    {
        m_bSkipFirstArgument = m_Arguments.size() > m_pSubroutine->getParameterCount();
    }
    //m_TempValues.resize(m_Arguments.size(), nullptr);
    Type* pThisPointerType = nullptr;

    size_t i = m_Arguments.size();
    while(i--)
    {
        Expression* pArgument = m_Arguments[i];
        o_assert(pArgument);
        addSubExpression(m_Arguments[i]); // add elements in evaluation order
    }
}

o_terminate_cpp(CallExpression) 
{
    // Release temp buffers
    if(m_pSubroutine)
    {
        if(m_pReturnStorage AND m_pSubroutine->getReturnType() == m_pValueType)
        {
            Type* pStorageType = storageType(m_pSubroutine->getReturnType());
            pStorageType->deallocate(m_pReturnStorage);
            m_pReturnStorage = nullptr;
        }
    }
}

void CallExpression::internalEval( void* a_pDest ) const
{
    vector<void*> addresses;
    evaluateArguments(m_Arguments, addresses);
    if(m_pReturnStorage)
    {
        m_pSubroutine->placementCall(addresses.data()+ptrdiff_t(m_bSkipFirstArgument), m_pReturnStorage); // first call
        // then copy the return value to dest
        Type* pStorageType = returnStorageType();
        if(m_pValueType->asRValueReferenceType() AND NOT(pStorageType->asRValueReferenceType()))
            *(void**)a_pDest = m_pReturnStorage; 
        else 
            m_pValueType->copy(a_pDest, m_pReturnStorage);

        if(!getEnclosingStatement()) /// do not have a statement enclosing the expression => return storage must be destroyed just after the call                                    
        {
            pushDestruction(pStorageType, m_pReturnStorage);
        }
    }
    else // void call
    {
        m_pSubroutine->call(addresses.data()+ptrdiff_t(m_bSkipFirstArgument));
    }
}

void* CallExpression::evalStorage() const
{
    internalEval();
    return m_pReturnStorage;
}

void CallExpression::flush() const
{
    for(auto it = m_Arguments.begin(); it != m_Arguments.end(); ++it)
    {
        (*it)->flush();
    }
}

void CallExpression::internalEval() const
{
    vector<void*> addresses;
    evaluateArguments(m_Arguments, addresses);
    if(m_pReturnStorage)
    {
        m_pSubroutine->placementCall(addresses.data()+ptrdiff_t(m_bSkipFirstArgument), m_pReturnStorage);

        if(!getEnclosingStatement()) /// do not have a statement enclosing the expression => return storage must be destroyed just after the call                                    
        {
            pushDestruction(returnStorageType(), m_pReturnStorage);
        }
    }
    else
    {
        m_pSubroutine->call(addresses.data()+ptrdiff_t(m_bSkipFirstArgument));
    }
    flush();
}

LanguageElement* CallExpression::hatch()
{
    Subroutine* pSubroutine = m_pSubroutine;
    o_dynamic_delete (this);
    return pSubroutine;
}

Expression* CallExpression::clone() const
{
    vector<Expression*> clonedExpressions;
    for(auto it = m_Arguments.begin(); it != m_Arguments.end(); ++it)
    {
        clonedExpressions.push_back((*it)->clone());
    }
    return o_new(CallExpression)(m_pSubroutine, clonedExpressions, (m_pSubroutine->getReturnType() != m_pValueType) 
                                                                        ? m_pValueType 
                                                                        : nullptr);
}

void CallExpression::referencedElementRemoved( LanguageElement* a_pElement )
{
    if(m_pValueType == a_pElement)
    {
        if(m_pReturnStorage)
        {
            Type* pStorageType = returnStorageType();
            pStorageType->deallocate(m_pReturnStorage);
            m_pReturnStorage = nullptr;
        }
    }
    else if(m_pSubroutine == a_pElement)
    {
        if(m_pReturnStorage)
        {
            Type* pStorageType = returnStorageType();
            pStorageType->deallocate(m_pReturnStorage);
            m_pReturnStorage = nullptr;
        }
        m_pSubroutine = nullptr;
    }
    Expression::referencedElementRemoved(a_pElement);
}

void CallExpression::elementRemoved( LanguageElement* a_pElement )
{
    for(auto it = m_Arguments.begin(); it != m_Arguments.end(); ++it)
    {
        if((*it) == a_pElement)
        {
            *it = nullptr;
            break;
        }
    }
}

bool CallExpression::isPersistent() const
{
    return Expression::isPersistent() AND m_pSubroutine->isNative();
}

o_namespace_end(phantom, reflection)
