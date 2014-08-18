/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "CallExpression.h"
#include "CallExpression.hxx"
#include "AddressExpression.h"
#include "ExpressionStatement.h"
#include "Block.h"
#include "Compiler.h"
/* *********************************************** */
o_registerN((phantom, reflection), CallExpression);

o_namespace_begin(phantom, reflection)

string CallExpression::evaluateName( Subroutine* a_pSubroutine, Expression* a_pArgument )
{
    vector<Expression*> expressions;
    expressions.push_back(a_pArgument);
    return evaluateName(a_pSubroutine, expressions);
}

string CallExpression::evaluateName( Subroutine* a_pSubroutine, const vector<Expression*>& a_Arguments )
{
    string name;
    if(a_pSubroutine->asInstanceMemberFunction())
    {
        name += '(';
        name += a_Arguments[0]->getName();
        name += ')';
        name += '.';
        name += a_pSubroutine->getName();
        name += '(';
        if(a_Arguments.size() > 1)
        {
            for(size_t i = 1; i<a_Arguments.size(); ++i)
            {
                if(i != 1)
                    name += ',';
                name += a_Arguments[i]->getName();
            }
        }
        name += ')';
    }
    else 
    {
        name += a_pSubroutine->getName();
        name += '(';
        if(a_Arguments.size())
        {
            for(size_t i = 0; i<a_Arguments.size(); ++i)
            {
                if(i != 1)
                    name += ',';
                name += a_Arguments[i]->getName();
            }
        }
        name += ')';
    }
    return name;
}


CallExpression::CallExpression( Subroutine* a_pSubroutine, const vector<Expression*>& a_Arguments, Type* a_pConstructedType ) 
    : Expression(a_pConstructedType ? a_pConstructedType : a_pSubroutine->getReturnType()
                , evaluateName(a_pSubroutine, a_Arguments)
                , 0)
    , m_pSubroutine(a_pSubroutine)
    , m_Arguments(a_Arguments)
    , m_pReturnStorage(nullptr)
{
    
}

CallExpression::CallExpression( Subroutine* a_pSubroutine, Expression* a_pArgument, Type* a_pConstructedType ) 
    : Expression(a_pConstructedType ? a_pConstructedType : a_pSubroutine->getReturnType()
    , evaluateName(a_pSubroutine, a_pArgument)
    , 0)
    , m_pSubroutine(a_pSubroutine)
    , m_pReturnStorage(nullptr)
{
    m_Arguments.push_back(a_pArgument);
}

o_initialize_cpp(CallExpression)
{
    addReferencedElement(m_pSubroutine);
    Type* pStorageType = storageType(m_pSubroutine->getReturnType());
    if(pStorageType)
    {
        m_pReturnStorage = pStorageType->allocate();
    }
    bool isInstanceMemberFunction = (m_pSubroutine->asInstanceMemberFunction() != nullptr);
    o_assert(m_Arguments.size() == (m_pSubroutine->getParameterCount()+isInstanceMemberFunction));
    m_TempValues.resize(m_Arguments.size(), nullptr);
    m_ConvertedArguments.resize(m_Arguments.size(), nullptr);
    Type* pThisPointerType = nullptr;
    if(isInstanceMemberFunction)
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
        Expression* pArgument = m_ConvertedArguments[i] = m_Arguments[i]->implicitCast( (isInstanceMemberFunction AND (i == 0)) 
            ? pThisPointerType
            : m_pSubroutine->getParameterType(i-isInstanceMemberFunction) );
        o_assert(pArgument);
        addElement(pArgument); // add elements in evaluation order
        if(NOT(pArgument->hasValueStorage()))
        {
            pStorageType = storageType(pArgument->getValueType());
            void* pTempValue = pStorageType->allocate();
            pStorageType->construct(pTempValue);
            pStorageType->install(pTempValue);
            pStorageType->initialize(pTempValue);
            m_TempValues[i] = pTempValue;
        }
    }
}

void CallExpression::terminate() 
{
    // Release temp buffers
    Type* pStorageType = storageType(m_pSubroutine->getReturnType());
    if(pStorageType)
    {
        pStorageType->terminate(m_pReturnStorage);
        pStorageType->uninstall(m_pReturnStorage);
        pStorageType->destroy(m_pReturnStorage);
        pStorageType->deallocate(m_pReturnStorage);
    }
    for(size_t i = 0; i<m_ConvertedArguments.size(); ++i)
    {
        Expression* pArgument = m_ConvertedArguments[i];
        if(NOT(pArgument->hasValueStorage()))
        {
            void* pTempValue = m_TempValues[i];
            pStorageType = storageType(pArgument->getValueType());
            pStorageType->terminate(pTempValue);
            pStorageType->uninstall(pTempValue);
            pStorageType->destroy(pTempValue);
            pStorageType->deallocate(pTempValue);
        }
    }
    Expression::terminate();
}

void CallExpression::getValue( void* a_pDest ) const
{
    vector<void*> addresses;
    addresses.resize(m_ConvertedArguments.size());
    size_t i = m_ConvertedArguments.size();
    while(i--) // evaluate arguments from right to left
    {
        Expression* pArgument = m_ConvertedArguments[i];
        if(pArgument->hasValueStorage())
        {
            addresses[i] = pArgument->getValueStorageAddress();
        }
        else 
        {
            pArgument->getValue(m_TempValues[i]);
            addresses[i] = m_TempValues[i];
        }
    }

    if(m_pReturnStorage AND m_pSubroutine->getReturnType() == m_pValueType)
    {
        Type* pStorageType = storageType(m_pSubroutine->getReturnType());
        // Default construct the return storage
        pStorageType->construct(m_pReturnStorage);
        pStorageType->install(m_pReturnStorage);
        pStorageType->initialize(m_pReturnStorage);
        m_pSubroutine->call(addresses.data(), a_pDest);
    }
    else // void call
    {
        m_pSubroutine->call(addresses.data());
    }

}

void CallExpression::setValue( void const* a_pSrc ) const
{
    m_pValueType->copy(getValueStorageAddress(), a_pSrc);
    for(auto it = m_ConvertedArguments.begin(); it != m_ConvertedArguments.end(); ++it)
    {
        (*it)->flush();
    }
}

void* CallExpression::getValueStorageAddress() const
{
    getValue(m_pReturnStorage);
    return m_pReturnStorage;
}

void CallExpression::flush() const
{
    for(auto it = m_Arguments.begin(); it != m_Arguments.end(); ++it)
    {
        (*it)->flush();
    }
}

void CallExpression::call() const
{
    vector<void*> addresses;
    addresses.resize(m_ConvertedArguments.size());
    size_t i = m_ConvertedArguments.size();
    while(i--) // evaluate arguments from right to left
    {
        Expression* pArgument = m_ConvertedArguments[i];
        if(pArgument->hasValueStorage())
        {
            addresses[i] = pArgument->getValueStorageAddress();
        }
        else 
        {
            pArgument->getValue(m_TempValues[i]);
            addresses[i] = m_TempValues[i];
        }
    }
    m_pSubroutine->call(addresses.data(), m_pReturnStorage);
    flush();
}

variant CallExpression::compile( Compiler* a_pCompiler )
{
    return a_pCompiler->compile(this);
}

void CallExpression::ancestorChanged( LanguageElement* a_pLanguageElement )
{
    if(m_pBlock == nullptr)
    {
        m_pBlock = getBlock();
        if(m_pBlock)
        {
            if(NOT(getValueType()->asPOD()) AND getValueType()->asClassType())
            {
                vector<Expression*> arguments;
                arguments.push_back(o_new(AddressExpression)(const_cast<CallExpression*>(this)));
                m_pBlock->addRAIIDestructionStatement(
                    o_new(ExpressionStatement)(
                        o_new(CallExpression)(getValueType()->asClassType()->getDestructor(), arguments)
                    )
                );
            }
        }
    }
}

LanguageElement* CallExpression::hatch()
{
    Subroutine* pSubroutine = m_pSubroutine;
    phantom::deleteElement(this);
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

o_namespace_end(phantom, reflection)
