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

string CallExpression::evaluateName( Subroutine* a_pSubroutine, Expression* a_pArgument )
{
    vector<Expression*> expressions;
    expressions.push_back(a_pArgument);
    return evaluateName(a_pSubroutine, expressions);
}

string CallExpression::evaluateName( Subroutine* a_pSubroutine, const vector<Expression*>& a_Arguments )
{
    string name;
    const string& subroutineName = a_pSubroutine->getName();
    if(a_pSubroutine->asInstanceMemberFunction())
    {
        if(subroutineName.compare(0, 8, "operator") == 0)
        {
            char c = subroutineName[8];
            if( NOT((c >= 'a' AND c <= 'z' )
                OR (c >= 'A' AND c <= 'Z' )
                OR (c >= '0' AND c <= '9')
                OR  c == '_'))
            {
                string op = subroutineName.substr(8);
                if(op == "[]")
                {
                    name += '(';
                    name += a_Arguments[0]->getName();
                    name += ")[";
                    name += a_Arguments[1]->getName();
                    name += ']';
                }
                else if(op == "()")
                {
                    name += '(';
                    name += a_Arguments[0]->getName();
                    name += ")(";
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
                    // Create operator expression
                    name += '(';
                    name += a_Arguments[0]->getName();
                    name += ')';
                    name += op;
                    if(a_Arguments.size() == 2)
                    {
                        name += '(';
                        name += a_Arguments[1]->getName();
                        name += ')';
                    }
                }
                return name;
            }
        }
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
        name += a_pSubroutine->getQualifiedName();
        name += '(';
        if(a_Arguments.size())
        {
            for(size_t i = 0; i<a_Arguments.size(); ++i)
            {
                if(i != 0)
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
    if(m_pSubroutine == nullptr) setInvalid();
    for(size_t i = 0; i<m_Arguments.size(); ++i)
    {
        if(m_Arguments[i] AND m_Arguments[i]->getOwner()) m_Arguments[i] = m_Arguments[i]->clone();
    }
    m_pConvertedArgumentTypes = m_Arguments.size() ? o_allocate_n(m_Arguments.size(), Type*) : nullptr;
}

CallExpression::CallExpression( Subroutine* a_pSubroutine, Expression* a_pArgument, Type* a_pConstructedType ) 
    : Expression(a_pConstructedType ? a_pConstructedType : a_pSubroutine->getReturnType()
    , evaluateName(a_pSubroutine, a_pArgument)
    , 0)
    , m_pSubroutine(a_pSubroutine)
    , m_pReturnStorage(nullptr)
{
    m_Arguments.push_back((a_pArgument AND a_pArgument->getOwner()) ? a_pArgument->clone() : a_pArgument);
    if(m_pSubroutine == nullptr) setInvalid();
    m_pConvertedArgumentTypes = o_allocate_n(1, Type*);
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
            o_assert(as<Expression*>(pArgument));
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

void CallExpression::getValue( void* a_pDest ) const
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
    for(auto it = m_ConvertedArguments.begin(); it != m_ConvertedArguments.end(); ++it)
    {
        (*it)->flush();
    }
}

void CallExpression::eval() const
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

variant CallExpression::compile( Compiler* a_pCompiler )
{
    return a_pCompiler->compile(this);
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

o_namespace_end(phantom, reflection)
