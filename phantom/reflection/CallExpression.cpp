/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "CallExpression.h"
#include "CallExpression.hxx"
/* *********************************************** */
o_registerN((phantom, reflection), CallExpression);

o_namespace_begin(phantom, reflection)

string CallExpression::evaluateName( Subroutine* a_pSubroutine, const vector<Expression*>& a_Arguments )
{
    string name;
    if(a_pSubroutine->asInstanceMemberFunction())
    {
        name += a_Arguments[0]->getName();
        name += '.';
        name += a_pSubroutine->getName();
        if(a_Arguments.size() > 1)
        {
            name += '(';
            for(size_t i = 1; i<a_Arguments.size(); ++i)
            {
                name += a_Arguments[i]->getName();
            }
            name += ')';
        }
    }
    else 
    {
        name += a_pSubroutine->getName();
        if(a_Arguments.size())
        {
            name += '(';
            for(size_t i = 0; i<a_Arguments.size(); ++i)
            {
                name += a_Arguments[i]->getName();
            }
            name += ')';
        }
    }
    return name;
}


CallExpression::CallExpression( Subroutine* a_pSubroutine, const vector<Expression*>& a_Arguments ) 
    : Expression(a_pSubroutine->getReturnType(), evaluateName(a_pSubroutine, a_Arguments), 0)
    , m_pSubroutine(a_pSubroutine)
    , m_Arguments(a_Arguments)
    , m_pReturnStorage(nullptr)
{

    Type* pStorageType = storageType(m_pValueType);
    if(pStorageType)
    {
        m_pReturnStorage = pStorageType->allocate();
        pStorageType->construct(m_pReturnStorage);
        pStorageType->install(m_pReturnStorage);
        pStorageType->initialize(m_pReturnStorage);
    }

    m_TempValues.resize(m_Arguments.size(), nullptr);
    for(size_t i = 0; i<m_Arguments.size(); ++i)
    {
        Expression* pArgument = m_Arguments[i];
        addElement(pArgument);
        if(NOT(pArgument->isAddressable()))
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

CallExpression::~CallExpression() 
{
    // Release temp buffers
    Type* pStorageType = storageType(m_pValueType);
    if(pStorageType)
    {
        pStorageType->terminate(m_pReturnStorage);
        pStorageType->uninstall(m_pReturnStorage);
        pStorageType->destroy(m_pReturnStorage);
        pStorageType->deallocate(m_pReturnStorage);
    }
    for(size_t i = 0; i<m_Arguments.size(); ++i)
    {
        Expression* pArgument = m_Arguments[i];
        addElement(pArgument);
        if(NOT(pArgument->isAddressable()))
        {
            void* pTempValue = m_TempValues[i];
            pStorageType = storageType(pArgument->getValueType());
            pStorageType->terminate(pTempValue);
            pStorageType->uninstall(pTempValue);
            pStorageType->destroy(pTempValue);
            pStorageType->deallocate(pTempValue);
        }
    }
}

void CallExpression::getValue( void* a_pDest ) const
{
    vector<void*> addresses;
    addresses.resize(m_Arguments.size());
    size_t i = m_Arguments.size();
    while(i--) // evaluate arguments from right to left
    {
        Expression* pArgument = m_Arguments[i];
        if(pArgument->isAddressable())
        {
            addresses[i] = pArgument->getAddress();
        }
        else 
        {
            pArgument->getValue(m_TempValues[i]);
            addresses[i] = m_TempValues[i];
        }
    }
    if(m_pReturnStorage)
        m_pSubroutine->call(addresses.data(), a_pDest);
    else // void call
        m_pSubroutine->call(addresses.data());
}

void CallExpression::setValue( void const* a_pSrc ) const
{
    m_pValueType->copy(getAddress(), a_pSrc);
    for(auto it = m_Arguments.begin(); it != m_Arguments.end(); ++it)
    {
        (*it)->flush();
    }
}

void* CallExpression::getAddress() const
{
    getValue(m_pReturnStorage);
    return m_pReturnStorage;
}

void CallExpression::flush()
{
    for(auto it = m_Arguments.begin(); it != m_Arguments.end(); ++it)
    {
        (*it)->flush();
    }
}

Type* CallExpression::storageType(Type* a_pType)
{
    Type* pStorageType = a_pType;
    if(pStorageType == typeOf<void>()) return nullptr;
    if(pStorageType->asReferenceType())
    {
        pStorageType = pStorageType->asReferenceType()->getReferencedType()->pointerType();
    }
    return pStorageType;
}

o_namespace_end(phantom, reflection)
