/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "CallExpression.h"
#include "CallExpression.hxx"
#include "AddressExpression.h"
#include "ConstantExpression.h"
#include "ExpressionStatement.h"
#include "Block.h"
#include "Compiler.h"
/* *********************************************** */
o_registerN((phantom, reflection), CallExpression);

o_namespace_begin(phantom, reflection)

CallExpression::CallExpression( Subroutine* a_pSubroutine, const vector<Expression*>& a_Arguments, Type* a_pConstructedType ) 
    : Expression(a_pConstructedType ? a_pConstructedType : a_pSubroutine ? a_pSubroutine->getReturnType() : nullptr
                , 0)
    , m_pSubroutine(a_pSubroutine)
    , m_Arguments(a_Arguments)
    , m_pReturnStorage(nullptr)
{
    if(m_pSubroutine == nullptr) setInvalid();
    else addReferencedElement(m_pSubroutine);
    for(size_t i = 0; i<m_Arguments.size(); ++i)
    {
        if(m_Arguments[i] AND m_Arguments[i]->getOwner()) m_Arguments[i] = m_Arguments[i]->clone();
    }
    m_pConvertedArgumentTypes = m_Arguments.size() ? o_allocate_n(m_Arguments.size(), Type*) : nullptr;
}

CallExpression::CallExpression( Subroutine* a_pSubroutine, Expression* a_pArgument, Type* a_pConstructedType ) 
    : Expression(a_pConstructedType ? a_pConstructedType : a_pSubroutine ? a_pSubroutine->getReturnType() : nullptr
    , 0)
    , m_pSubroutine(a_pSubroutine)
    , m_pReturnStorage(nullptr)
{
    m_Arguments.push_back((a_pArgument AND a_pArgument->getOwner()) ? a_pArgument->clone() : a_pArgument);
    if(m_pSubroutine == nullptr) setInvalid();
    else addReferencedElement(m_pSubroutine);
    m_pConvertedArgumentTypes = o_allocate_n(1, Type*);
}

CallExpression::CallExpression( const vector<Expression*>& a_Arguments, Type* a_pConstructedType ) 
    : Expression(a_pConstructedType ? a_pConstructedType : nullptr, 0)
    , m_pSubroutine(nullptr)
    , m_Arguments(a_Arguments)
    , m_pReturnStorage(nullptr)
{
    for(size_t i = 0; i<m_Arguments.size(); ++i)
    {
        if(m_Arguments[i] AND m_Arguments[i]->getOwner()) m_Arguments[i] = m_Arguments[i]->clone();
    }
    m_pConvertedArgumentTypes = m_Arguments.size() ? o_allocate_n(m_Arguments.size(), Type*) : nullptr;
}

CallExpression::CallExpression( Expression* a_pArgument, Type* a_pConstructedType ) 
    : Expression(a_pConstructedType ? a_pConstructedType : nullptr, 0)
    , m_pSubroutine(nullptr)
    , m_pReturnStorage(nullptr)
{
    m_Arguments.push_back((a_pArgument AND a_pArgument->getOwner()) ? a_pArgument->clone() : a_pArgument);
    m_pConvertedArgumentTypes = o_allocate_n(1, Type*);
}

Type* CallExpression::returnStorageType() const 
{
    return storageType(m_pSubroutine->getReturnType());
}

o_initialize_cpp(CallExpression)
{
    Type* pStorageType = returnStorageType();
    if(pStorageType)
    {
        m_pReturnStorage = pStorageType->allocate();
    }
    bool isInstanceMemberFunction = m_pSubroutine ? (m_pSubroutine->asInstanceMemberFunction() != nullptr) : false;
    o_assert(m_pSubroutine == nullptr OR m_Arguments.size() == (m_pSubroutine->getParameterCount()+isInstanceMemberFunction));
    m_TempValues.resize(m_Arguments.size(), nullptr);
    m_ConvertedArguments.resize(m_Arguments.size(), nullptr);
    Type* pThisPointerType = nullptr;
    if(isInstanceMemberFunction AND m_pSubroutine)
    {
        pThisPointerType = m_pSubroutine->getOwner()->asClassType();
        if(m_pSubroutine->isConst())
        {
            pThisPointerType = pThisPointerType->constType()->referenceType();
        }
        else 
        {
            pThisPointerType = pThisPointerType->referenceType();
        }
    }

    size_t i = m_Arguments.size();
    while(i--)
    {
        Expression* pArgument = m_Arguments[i];
        if(pArgument == nullptr)
        {
            setInvalid();
            continue;
        }
        if(isInstanceMemberFunction AND (i == 0))
        {
            pArgument = m_ConvertedArguments[i] = o_new(AddressExpression)(m_Arguments[i]->implicitCast(pThisPointerType)); 
        }
        else 
        {
            pArgument = m_ConvertedArguments[i] = m_Arguments[i]->implicitCast(m_pSubroutine->getParameterType(i-isInstanceMemberFunction));
        }
        if(pArgument)
        {
            m_pConvertedArgumentTypes[i] = m_ConvertedArguments[i]->getValueType();
            addSubExpression(m_ConvertedArguments[i]); // add elements in evaluation order
        }
        else 
        {
            m_pConvertedArgumentTypes[i] = nullptr;
            setInvalid();
            continue;
        }
        if(NOT(pArgument->hasEffectiveAddress()))
        {
            addReferencedElement(pArgument->getValueType());
            pStorageType = storageType(pArgument->getValueType());
            void* pTempValue = pStorageType->allocate();
            pStorageType->construct(pTempValue);
            pStorageType->install(pTempValue);
            pStorageType->initialize(pTempValue);
            m_TempValues[i] = pTempValue;
        }
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
            pStorageType->terminate(m_pReturnStorage);
            pStorageType->uninstall(m_pReturnStorage);
            pStorageType->destroy(m_pReturnStorage);
            pStorageType->deallocate(m_pReturnStorage);
            m_pReturnStorage = nullptr;
        }
    }
    for(size_t i = 0; i<m_ConvertedArguments.size(); ++i)
    {
        Expression* pArgument = m_ConvertedArguments[i];
        if(pArgument)
        {
            if(m_TempValues[i])
            {
                void* pTempValue = m_TempValues[i];
                Type* pStorageType = storageType(pArgument->getValueType());
                pStorageType->terminate(pTempValue);
                pStorageType->uninstall(pTempValue);
                pStorageType->destroy(pTempValue);
                pStorageType->deallocate(pTempValue);
                m_TempValues[i] = nullptr;
            }
        }
    }
    if(m_pConvertedArgumentTypes)
    {
        o_deallocate_n(m_pConvertedArgumentTypes, m_Arguments.size(), Type*);
        m_pConvertedArgumentTypes = nullptr;
    }
}

void CallExpression::internalEval( void* a_pDest ) const
{
    vector<void*> addresses;
    evaluateArguments(addresses);
    if(m_pReturnStorage)
    {
        m_pSubroutine->call(addresses.data(), m_pReturnStorage); // first call
        getValueType()->copy(a_pDest, m_pReturnStorage); // then copy the return value to dest
    }
    else // void call
    {
        m_pSubroutine->call(addresses.data());
    }
}

void* CallExpression::getValueStorageAddress() const
{
    internalEval(m_pReturnStorage);
    return m_pReturnStorage;
}

void CallExpression::flush() const
{
    for(auto it = m_ConvertedArguments.begin(); it != m_ConvertedArguments.end(); ++it)
    {
        (*it)->flush();
    }
}

void CallExpression::internalEval() const
{
    vector<void*> addresses;
    evaluateArguments(addresses);
    if(m_pReturnStorage)
    {
        Type* pStorageType = storageType(m_pSubroutine->getReturnType());
        pStorageType->construct(m_pReturnStorage);
        pStorageType->install(m_pReturnStorage);
        pStorageType->initialize(m_pReturnStorage);
        m_pSubroutine->call(addresses.data(), m_pReturnStorage);
    }
    else
    {
        m_pSubroutine->call(addresses.data());
    }
    flush();
}

void CallExpression::ancestorChanged( LanguageElement* a_pLanguageElement )
{
    if(getBlock())
    {
        if(getValueType()->asClass())
        {
            o_assert(m_pReturnStorage);
            Expression* pThis = (o_new(ConstantExpression)(phantom::constant<void*>(m_pReturnStorage)))->cast(getValueType()->pointerType())->dereference();
            getBlock()->addRAIIDestructionExpressionStatement(
                    o_new(CallExpression)(getValueType()->asClass()->getDestructor(), pThis)
            );
        }
    }
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
    return o_new(CallExpression)(m_pSubroutine, clonedExpressions, (m_pSubroutine->getReturnType() != m_pValueType) ? m_pValueType : nullptr);
}

void CallExpression::referencedElementRemoved( LanguageElement* a_pElement )
{
    if(m_pConvertedArgumentTypes)
    {
        for(size_t i = 0; i<m_ConvertedArguments.size(); i++)
        {
            if(m_pConvertedArgumentTypes[i] == a_pElement)
            {
                if(m_TempValues[i])
                {
                    m_pConvertedArgumentTypes[i]->terminate(m_TempValues[i]);
                    m_pConvertedArgumentTypes[i]->uninstall(m_TempValues[i]);
                    m_pConvertedArgumentTypes[i]->destroy(m_TempValues[i]);
                    m_pConvertedArgumentTypes[i]->deallocate(m_TempValues[i]);
                    m_TempValues[i] = nullptr;
                }
            }
        }
    }
    if(m_pValueType == a_pElement)
    {
        if(m_pReturnStorage)
        {
            Type* pStorageType = storageType(m_pValueType);
            pStorageType->terminate(m_pReturnStorage);
            pStorageType->uninstall(m_pReturnStorage);
            pStorageType->destroy(m_pReturnStorage);
            pStorageType->deallocate(m_pReturnStorage);
            m_pReturnStorage = nullptr;
        }
    }
    else if(m_pSubroutine == a_pElement)
    {
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

void CallExpression::evaluateArguments( vector<void*> &addresses ) const
{
    addresses.resize(m_ConvertedArguments.size());
    size_t i = m_ConvertedArguments.size();
    while(i--) // evaluate arguments from right to left
    {
        Expression* pArgument = m_ConvertedArguments[i];

        if(pArgument->isAddressable())
        {
            pArgument->internalEval(&addresses[i]);
        }
        else if(pArgument->hasValueStorage())
        {
            addresses[i] = pArgument->getValueStorageAddress();
        }
        else 
        {
            pArgument->internalEval(m_TempValues[i]);
            addresses[i] = m_TempValues[i];
        }
    }
}

o_namespace_end(phantom, reflection)
