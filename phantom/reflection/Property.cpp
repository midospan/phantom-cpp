/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/Property.h>
#include <phantom/reflection/Property.hxx>
#include <phantom/reflection/PropertyExpression.h>
#include <phantom/vector.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), Property);
o_registerNTI((phantom), vector, (phantom::reflection::Property*));

o_namespace_begin(phantom, reflection) 

Class* const Property::metaType = o_type_of(phantom::reflection::Property);

Property::Property()
    : m_pSetMemberFunction(nullptr)
    , m_pGetMemberFunction(nullptr)
    , m_pSignal(nullptr)
    , m_pCompilationData(new property_compilation_data)
    , m_pSignalString(nullptr)
    , m_pSetMemberFunctionString(nullptr)
    , m_pGetMemberFunctionString(nullptr)
{

}

Property::Property( Type* a_pValueType, const string& a_strName, MemberFunction* a_pSetMemberFunction, MemberFunction* a_pGetMemberFunction, Signal* a_pSignal, Range* a_pRange, uint a_uiSerializationMask, modifiers_t a_Modifiers /*= 0*/ ) 
    : ValueMember(a_pValueType, a_strName, a_pRange, a_uiSerializationMask, a_Modifiers) 
    , m_pSetMemberFunction(a_pSetMemberFunction)
    , m_pGetMemberFunction(a_pGetMemberFunction)
    , m_pSignal(a_pSignal)
    , m_pCompilationData(new property_compilation_data)
    , m_pSignalString(nullptr)
    , m_pSetMemberFunctionString(nullptr)
    , m_pGetMemberFunctionString(nullptr)
{
    o_assert(m_pGetMemberFunction == nullptr OR (m_pGetMemberFunction->getSignature()->getReturnType() == m_pValueType));
    o_assert(m_pSetMemberFunction == nullptr 
        OR (m_pSetMemberFunction->getSignature()->getParameterCount() == 1 
        AND m_pSetMemberFunction->getSignature()->getParameterType(0) == m_pValueType));
    o_assert(m_pSignal == nullptr 
        || m_pSignal->getSignature()->getParameterCount() == 0 
        || (m_pSignal->getSignature()->getParameterCount() == 1 && m_pSignal->getSignature()->getParameterType(0) == m_pValueType));
    if(m_pSetMemberFunction)
    {
        addReferencedElement(m_pSetMemberFunction);
    }
    if(m_pGetMemberFunction)
    {
        addReferencedElement(m_pGetMemberFunction);
    }
    if(m_pSignal)
    {
        addReferencedElement(m_pSignal);
        m_pSignal->m_pProperty = this;
    }
}

Property::Property( Type* a_pValueType, const string& a_strName, MemberFunction* a_pSetMemberFunction, MemberFunction* a_pGetMemberFunction, Signal* a_pSignal, Range* a_pRange, uint a_uiSerializationMask, modifiers_t a_Modifiers, int protectedTag ) 
    : ValueMember(a_pValueType, a_strName, a_pRange, a_uiSerializationMask, a_Modifiers) 
    , m_pSetMemberFunction(a_pSetMemberFunction)
    , m_pGetMemberFunction(a_pGetMemberFunction)
    , m_pSignal(a_pSignal)
    , m_pCompilationData(nullptr)
    , m_pSignalString(nullptr)
    , m_pSetMemberFunctionString(nullptr)
    , m_pGetMemberFunctionString(nullptr)
{
    o_assert(m_pGetMemberFunction == nullptr OR (m_pGetMemberFunction->getSignature()->getReturnType() == m_pValueType));
    o_assert(m_pSetMemberFunction == nullptr 
            OR (m_pSetMemberFunction->getSignature()->getParameterCount() == 1 
                AND m_pSetMemberFunction->getSignature()->getParameterType(0) == m_pValueType));
    o_assert(m_pSignal == nullptr 
        || m_pSignal->getSignature()->getParameterCount() == 0 
        || (m_pSignal->getSignature()->getParameterCount() == 1 && m_pSignal->getSignature()->getParameterType(0) == m_pValueType));
    if(m_pSetMemberFunction)
    {
        addReferencedElement(m_pSetMemberFunction);
    }
    if(m_pGetMemberFunction)
    {
        addReferencedElement(m_pGetMemberFunction);
    }
    if(m_pSignal)
    {
        addReferencedElement(m_pSignal);
        m_pSignal->m_pProperty = this;
    }
}

o_destructor Property::~Property( void )
{
    delete m_pCompilationData;
}

void Property::referencedElementRemoved( LanguageElement* a_pElement )
{
    ValueMember::referencedElementRemoved(a_pElement);
    if(m_pSignal == a_pElement)
        m_pSignal = nullptr;
    else if(m_pGetMemberFunction == a_pElement)
        m_pGetMemberFunction = nullptr;
    else if(m_pSetMemberFunction == a_pElement)
        m_pSetMemberFunction = nullptr;
}

bool Property::referencesData( const void* a_pInstance, const phantom::data& a_Data ) const
{
    Type* pType = m_pValueType->removeReference()->removeQualifiers();
    void* pBuffer = pType->allocate();
    pType->construct(pBuffer);
    pType->initialize(pBuffer);
    getValue(a_pInstance, pBuffer);
    if(pType->referencesData(pBuffer, a_Data))
    {
        pType->terminate(pBuffer);
        pType->destroy(pBuffer);
        pType->deallocate(pBuffer);
        return true;
    }
    pType->terminate(pBuffer);
    pType->destroy(pBuffer);
    pType->deallocate(pBuffer);
    return false;
}

void Property::getValue( void const* a_pObject, void* a_pDest ) const
{
    o_assert(m_pCompilationData);
    void* args[1] = {&a_pObject};
    if(m_pCompilationData->m_ClosureCallDelegate.empty())
    {
        if(m_pGetMemberFunction == nullptr)
        {
            o_exception(exception::reflection_runtime_exception, "No get member function defined for this property");
        }
        m_pGetMemberFunction->call(args, a_pDest);
    }
    else
    {
        m_pCompilationData->m_ClosureCallDelegate(m_pCompilationData->m_pGetClosure, args, 1, a_pDest);
    }
}

void Property::setValue( void* a_pObject, void const* a_pSrc ) const
{
    o_assert(m_pCompilationData);
    void* args[2] = {&a_pObject, (void*)a_pSrc};
    if(m_pCompilationData->m_ClosureCallDelegate.empty())
    {
        if(m_pSetMemberFunction == nullptr)
        {
            o_exception(exception::reflection_runtime_exception, "No set member function defined for this property");
        }
        m_pSetMemberFunction->call(args);
    }
    else
    {
        m_pCompilationData->m_ClosureCallDelegate(m_pCompilationData->m_pSetClosure, args, 2, nullptr);
    }
}

void Property::finalize()
{
    ValueMember::finalize();
    if(m_pSignalString)
    {
        o_assert(m_pSignal == nullptr);
        LanguageElement* pElem = phantom::elementByName(*m_pSignalString);
        m_pSignal = pElem ? pElem->asSignal() : nullptr;
        if(m_pSignal)
        {
            addReferencedElement(m_pSignal);
            m_pSignal->m_pProperty = this;
        }
        delete m_pSignalString;
        m_pSignalString = nullptr;
    }
    if(m_pSetMemberFunctionString)
    {
        o_assert(m_pSetMemberFunction == nullptr);
        LanguageElement* pElem = phantom::elementByName(*m_pSetMemberFunctionString);
        m_pSetMemberFunction = pElem ? pElem->asMemberFunction() : nullptr;
        if(m_pSetMemberFunction)
        {
            addReferencedElement(m_pSetMemberFunction);
        }
        delete m_pSetMemberFunctionString;
        m_pSetMemberFunctionString = nullptr;
    }
    if(m_pGetMemberFunctionString)
    {
        o_assert(m_pGetMemberFunction == nullptr);
        LanguageElement* pElem = phantom::elementByName(*m_pGetMemberFunctionString);
        m_pGetMemberFunction = pElem ? pElem->asMemberFunction() : nullptr;
        if(m_pGetMemberFunction)
        {
            addReferencedElement(m_pGetMemberFunction);
        }
        delete m_pGetMemberFunctionString;
        m_pGetMemberFunctionString = nullptr;
    }
}

void Property::setSignalString( string str )
{
    if(str.size())
    {
        o_assert(m_pSignalString == nullptr);
        m_pSignalString = new string(str);
    }
}

string Property::getSignalString() const
{
    return m_pSignal ? m_pSignal->getQualifiedDecoratedName() : "";
}

void Property::setSetMemberFunctionString( string str )
{
    if(str.size())
    {
        o_assert(m_pSetMemberFunctionString == nullptr);
        m_pSetMemberFunctionString = new string(str);
    }
}

string Property::getSetMemberFunctionString() const
{
    return m_pSetMemberFunction ? m_pSetMemberFunction->getQualifiedDecoratedName() : "";
}

void Property::setGetMemberFunctionString( string str )
{
    if(str.size())
    {
        o_assert(m_pGetMemberFunctionString == nullptr);
        m_pGetMemberFunctionString = new string(str);
    }
}

string Property::getGetMemberFunctionString() const
{
    return m_pGetMemberFunction ? m_pGetMemberFunction->getQualifiedDecoratedName() : "";
}

void Property::addDataMember( DataMember* a_pDataMember )
{
    if(a_pDataMember)
    {
        o_assert(std::find(beginDataMembers(), endDataMembers(), a_pDataMember) == endDataMembers());
        m_DataMembers.push_back(a_pDataMember);
        addReferencedElement(a_pDataMember);
    }
}

o_namespace_end(phantom, reflection)
