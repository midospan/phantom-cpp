/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/Variable.h>
#include <phantom/reflection/Variable.hxx>
#include <phantom/reflection/VariableExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), Variable);
o_namespace_begin(phantom, reflection)

o_define_meta_type(Variable) = o_type_of(Variable);

Variable::Variable()
    : NamedElement()
    , m_pRange(nullptr)
    , m_pValueType(nullptr)
    , m_pAddress(nullptr)
{

}

Variable::Variable(void* a_pAddress, Range* a_pRange, modifiers_t a_Modifiers /*= 0*/)
    : NamedElement(phantom::lexical_cast<string>(a_pAddress), a_Modifiers)
    , m_pRange(a_pRange)
    , m_pValueType(classOf(a_pAddress))
    , m_pAddress(a_pAddress)
{
    o_assert(testModifiers(o_native));
    if(m_pValueType)
    {
        addReferencedElement(m_pValueType);
    }
    else
    {
        o_exception(exception::reflection_runtime_exception, "No rtti at given static variable address");
    }
}

Variable::Variable(void* a_pAddress, Type* a_pValueType, Range* a_pRange, modifiers_t a_Modifiers /*= 0*/)
    : NamedElement(phantom::lexical_cast<string>(a_pAddress), a_Modifiers)
    , m_pRange(a_pRange)
    , m_pValueType(a_pValueType)
    , m_pAddress(a_pAddress)
    , m_pValueTypeName(nullptr)
{
    o_assert(testModifiers(o_native));
    o_assert(m_pValueType);
    addReferencedElement(m_pValueType);
}

Variable::Variable( void* a_pAddress, Type* a_pValueType, const string& a_strName, Range* a_pRange, modifiers_t a_Modifiers /*= 0*/ )
    : NamedElement(a_strName, a_Modifiers)
    , m_pRange(a_pRange)
    , m_pValueType(a_pValueType)
    , m_pAddress(a_pAddress)
    , m_pValueTypeName(nullptr)
{
    o_assert(isNative());
    o_assert(m_pValueType);
    addReferencedElement(m_pValueType);
}

Variable::Variable( Type* a_pValueType, const string& a_strName, modifiers_t a_Modifiers /*= 0*/ )
    : NamedElement(a_strName, a_Modifiers)
    , m_pRange(nullptr)
    , m_pValueType(a_pValueType)
    , m_pAddress(a_pValueType ? a_pValueType->newInstance() : nullptr)
    , m_pValueTypeName(nullptr)
{
    o_assert(!isNative());
    if(m_pValueType)
    {
        addReferencedElement(m_pValueType);
    }
}

Variable::Variable( Type* a_pValueType, const string& a_strName, Range* a_pRange /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
    : NamedElement(a_strName, a_Modifiers)
    , m_pRange(a_pRange)
    , m_pValueType(a_pValueType)
    , m_pAddress(a_pValueType ? a_pValueType->newInstance() : nullptr)
    , m_pValueTypeName(nullptr)
{
    o_assert(!isNative());
    if(m_pValueType)
    {
        addReferencedElement(m_pValueType);
    }
}

Variable::~Variable( void )
{
    if(!isNative() AND m_pValueType)
    {
        m_pValueType->deleteInstance(m_pAddress);
    }
}

void Variable::referencedElementRemoved( LanguageElement* a_pElement )
{
    LanguageElement::referencedElementRemoved(a_pElement);
    if(m_pValueType == a_pElement)
        m_pValueType = nullptr;
}

void Variable::setRange( Range* a_pRange )
{
    if(testModifiers(o_native))
    {
        o_exception(exception::base_exception, "Native elements cannot be modified");
    }
    m_pRange = a_pRange;
    if(m_pRange)
    {
        addElement(m_pRange);
    }
}

void Variable::setValueTypeName( string str )
{
    if(str.size())
    {
        m_pValueTypeName = new string(str);
    }
}

string Variable::getValueTypeName() const
{
    return m_pValueType ? m_pValueType->getQualifiedDecoratedName() : "";
}

void Variable::finalize()
{
    if(m_pValueTypeName)
    {
        o_assert(m_pValueType == nullptr);
        m_pValueType = phantom::typeByName(*m_pValueTypeName);
        if(m_pValueType)
        {
            addReferencedElement(m_pValueType);
            m_pAddress = m_pValueType->newInstance();
        }
        delete m_pValueTypeName;
        m_pValueTypeName = nullptr;
    }
}

Expression* Variable::toExpression( Expression* a_pLeftExpression ) const
{
    return o_new(VariableExpression)(const_cast<Variable*>(this), a_pLeftExpression);
}

o_namespace_end(phantom, reflection)
