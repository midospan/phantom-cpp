/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "phantom/reflection/Signature.h"
#include "phantom/reflection/Signature.hxx"
#include "phantom/reflection/Expression.h"
#include "phantom/reflection/Parameter.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <sstream>
/* *********************************************** */
o_registerN((phantom, reflection), Signature);

o_namespace_begin(phantom, reflection) 

o_invalid_def(Signature, Type::Invalid(), o_invalid|o_shared);

Signature* Signature::Create( modifiers_t modifiers )
{
    return o_new(Signature)(modifiers);
}

Signature* Signature::Create( Type* a_pReturnType, modifiers_t modifiers )
{
    return o_new(Signature)(a_pReturnType, modifiers);
}

Signature* Signature::Create( Type* a_pReturnType, Type* a_pSingleParameterType, modifiers_t modifiers )
{
    return o_new(Signature)(a_pReturnType, a_pSingleParameterType, modifiers);
}

Signature::Signature( modifiers_t modifiers ) 
: NamedElement("", modifiers)
, m_pReturnType(nullptr)
, m_uiArgumentStorageSize(0)
, m_pReturnTypeName(nullptr)
{

}

Signature::Signature( Type* a_pReturnType, modifiers_t modifiers )
    : NamedElement("", modifiers)
    , m_pReturnType(nullptr)
    , m_uiArgumentStorageSize(0)
    , m_pReturnTypeName(nullptr)
{
    setReturnType(a_pReturnType);
}

Signature::Signature( Type* a_pReturnType, Type* a_pSingleParameterType, modifiers_t modifiers )
    : NamedElement("", modifiers)
    , m_pReturnType(nullptr)
    , m_uiArgumentStorageSize(0)
    , m_pReturnTypeName(nullptr)
{
    setReturnType(a_pReturnType);
    addParameter(o_new(Parameter)(a_pSingleParameterType));
}

Signature::Signature( Type* a_pType, const vector<Parameter*>& a_Parameters, modifiers_t modifiers /*= 0 */ )
    : NamedElement("", modifiers)
    , m_pReturnType(nullptr)
    , m_uiArgumentStorageSize(0)
    , m_pReturnTypeName(nullptr)
{
    setReturnType(a_pType);
    for(auto it = a_Parameters.begin(); it != a_Parameters.end(); ++it)
    {
        addParameter(*it);
    }
}

Signature::Signature( Type* a_pType, const vector<Type*>& a_Types, modifiers_t modifiers /*= 0 */ )
    : NamedElement("", modifiers)
    , m_pReturnType(nullptr)
    , m_uiArgumentStorageSize(0)
    , m_pReturnTypeName(nullptr)
{
    setReturnType(a_pType);
    for(auto it = a_Types.begin(); it != a_Types.end(); ++it)
    {
        addParameter(o_new(Parameter)(*it));
    }
}

void Signature::parse( const string& a_strSignature, LanguageElement* a_pFutureScope )
{
    if(m_pOwner == nullptr)
    {
        o_exception(exception::reflection_runtime_exception, "cannot parse a signature without a scope context");
    }
    o_assert(a_pFutureScope == nullptr OR getOwnerSubroutine() == nullptr OR getOwnerSubroutine()->getOwner() == nullptr)
    if(a_pFutureScope AND getOwnerSubroutine())
    {
        a_pFutureScope->addScopedElement(getOwnerSubroutine());
    }
    size_t i = 0;
    size_t length = a_strSignature.length();
    string returnType;
    for(;i<length;++i)
    {
        character c = a_strSignature[i];
        if(c == '(')
        {
            if(returnType.empty()) 
            {
                o_exception(exception::invalid_parsing_exception, "No return type specified in the signature string");
            }
            Type* pReturnType = m_pReturnType;
            if(pReturnType == nullptr)
            {
                pReturnType = phantom::typeByName(returnType, this, isNative()*o_native);
            }
            if(pReturnType == nullptr) 
            {
                if(isNative())
                {
                    o_exception(exception::unknown_reflection_type_exception, returnType.c_str());
                }
                else setInvalid();
            }
            else
            {
                setReturnType(pReturnType);
                vector<Type*> parameterTypes;
                vector<string> parameterNames;
                vector<Expression*> parameterExps;
                if(NOT(parseParameterTypeList(a_strSignature.substr(i), parameterTypes, parameterNames, parameterExps)))
                {
                    o_exception(exception::invalid_parsing_exception, a_strSignature.substr(i).c_str());
                }
                else 
                {
                    o_assert(parameterTypes.size() == parameterNames.size() AND parameterTypes.size() == parameterExps.size());
                    for(size_t i = 0; i<parameterTypes.size(); ++i)
                    {
                        addParameter(parameterTypes[i], parameterNames[i], parameterExps[i]);
                    }
                }
            }
            goto end_parse;
        }
        else
        {
            returnType += c;
        }
    }
end_parse:
    if(a_pFutureScope AND getOwnerSubroutine())
    {
        a_pFutureScope->removeScopedElement(getOwnerSubroutine());
    }
}

Signature::~Signature( void )
{
}

void Signature::addParameter( Type* a_pType, const string& a_strName, Expression* a_pExpression )
{
    addParameter(o_new(Parameter)(a_pType, a_strName, a_pExpression));
}

void Signature::addParameter( Parameter* a_pParameter )
{
    if(m_Parameters.size())
    {
        if(m_Parameters.back()->getInitializationExpression())
        {
            if(a_pParameter->getInitializationExpression() == nullptr)
            {
                if(isNative())
                {
                    o_error(false, "parameter must have a default argument as it's predecessor had one");
                }
                else 
                {
                    setInvalid();
                }
            }
        }
    }
    if(a_pParameter)
    {
        if(a_pParameter->m_strName.empty())
        {
            a_pParameter->m_strName = '$'+lexical_cast<string>(m_Parameters.size());
        }
        addElement(a_pParameter);
    }
    else 
    {
        setInvalid();
    }
    m_Parameters.push_back(a_pParameter);
}

void Signature::setReturnType( Type* a_pType )
{
    if(NOT(a_pType AND (a_pType == typeOf<void>() OR a_pType->isCopyable())))
        setInvalid();
    m_pReturnType = a_pType;
    if(m_pReturnType)
    {
        addReferencedElement(a_pType);
    }
    else setInvalid();
}

void Signature::referencedElementRemoved(LanguageElement* a_pElement)
{
    if(m_pReturnType == a_pElement)
    {
        m_pReturnType = nullptr;
    }
    LanguageElement::referencedElementRemoved(a_pElement);
}

void Signature::elementRemoved(LanguageElement* a_pElement)
{
    for(auto it = m_Parameters.begin(); it != m_Parameters.end(); ++it)
    {
        if((*it) == a_pElement)
        {
            m_Parameters.erase(std::find(m_Parameters.begin(), m_Parameters.end(), a_pElement));
            break;
        }
    }
    LanguageElement::elementRemoved(a_pElement);
}

size_t Signature::getParameterCount() const
{
    return m_Parameters.size();
}

Type* Signature::getParameterType( size_t a_uiParamIndex ) const
{
    o_assert(a_uiParamIndex < getParameterCount(), "Index too big");
    return m_Parameters[a_uiParamIndex]->getValueType();
}

Type* Signature::getReturnType() const
{
    return m_pReturnType;
}

bool Signature::separateParameters( const string& a_strText, vector<string>& a_OutParameters )
{
    string parameter;
    size_t length = a_strText.length();
    size_t i = 0;
    size_t template_level = 0;
    for(;i<length;++i)
    {
        character c = a_strText[i];
        if( c == ',' AND template_level == 0 )
        {
            a_OutParameters.push_back(parameter);
            parameter.clear();
        }
        else 
        {
            if( c == '<' )
            {
                ++template_level;
            }
            else if( c == '>')
            {
                if(template_level != 0) 
                    --template_level;
            }
            parameter += c;
        }
    }
    if(template_level == 0 AND NOT(parameter.empty()))
    {
        a_OutParameters.push_back(parameter);
        return true;
    }
    a_OutParameters.clear();
    return false;
}

bool Signature::parseParameterTypeList( const string& a_strText, vector<Type*>& a_OutParameterTypes, vector<string>& a_OutParameterNames, vector<Expression*>& a_OutParameterExps )
{
    if(a_strText.empty()) return false;
    list<string> words;
    split( words, a_strText, boost::is_any_of("()"), boost::token_compress_on ); // SplitVec == { "hello abc","ABC","aBc goodbye" }
    // Remove empty tokens
    words.erase( std::remove_if( words.begin(), words.end(), 
        boost::bind( &string::empty, _1 ) ), words.end() );
    if(words.empty()) return true;
   if(a_strText[0] != o_CC('('))
    {
        words.pop_front();
    }
    if(words.size() != 1) return false;
    
    vector<string> parameters;
    if(NOT(separateParameters(words.front(), parameters)))
        return false;
    for(auto it = parameters.begin(); it != parameters.end(); ++it)
    {
        Type* pType = nullptr;
        string name;
        Expression* pExpression = nullptr;
        LanguageElement* pParamElement = elementByName(*it, this, isNative()*o_native);
        if(pParamElement == nullptr)
        {
            if(isNative())
            {
                o_exception(exception::unknown_reflection_type_exception, (*it).c_str());
            }
            else 
            {
                addParameter((Parameter*)nullptr);
            }
        }
        else 
        {
            if(pParamElement->asParameter())
            {
                addParameter(static_cast<Parameter*>(pParamElement));
            }
            else if(pParamElement->asType())
            {
                addParameter(o_new(Parameter)(static_cast<Type*>(pParamElement)));
            }
            else 
            {
                o_assert(pParamElement->getOwner() == nullptr);
                setInvalid();
                o_dynamic_delete pParamElement;
                addParameter((Parameter*)nullptr);
            }
        }
    }
    return true;
}

void Signature::implicitConversions( const vector<Type*>& a_Arguments, LanguageElement* a_pContextScope, conversions& a_ImplicitConversions ) const
{
    o_assert(getLanguage());
    implicitConversions(getLanguage(), a_Arguments, a_pContextScope, a_ImplicitConversions);
}

void Signature::implicitConversions( const vector<Expression*>& a_Arguments, LanguageElement* a_pContextScope , conversions& a_ImplicitConversions /*= nullptr*/) const
{
    vector<Type*> types;
    for(auto it = a_Arguments.begin(); it != a_Arguments.end(); ++it)
    {
        if(*it == nullptr OR (*it)->getValueType() == nullptr) return;
        types.push_back((*it)->getValueType());
    }
    implicitConversions(types, a_pContextScope, a_ImplicitConversions);
}

void Signature::implicitConversions( Language* a_pLanguage, const vector<Type*>& a_Arguments, LanguageElement* a_pContextScope, conversions& a_ImplicitConversions ) const
{
    size_t paramCount = m_Parameters.size();
    size_t argCount = a_Arguments.size();
    if((argCount < getRequiredArgumentCount())
        OR (argCount > paramCount AND NOT(hasEllipsis()))) return;
    size_t i = 0;
    bool result = true;
    for(;i<argCount;++i)
    {
        Type* pParamType = m_Parameters[i]->getValueType();
        Type* pInputType = (i<a_Arguments.size()) ? a_Arguments[i] : getParameterDefaultValue(i)->getValueType();
        a_ImplicitConversions.push_back(a_pLanguage->typeConversion(pInputType, pParamType, e_implicit_conversion, a_pContextScope));
    }
}

void Signature::implicitConversions( Language* a_pLanguage, const vector<Expression*>& a_Arguments, LanguageElement* a_pContextScope, conversions& a_ImplicitConversions /*= nullptr*/) const
{
    vector<Type*> types;
    for(auto it = a_Arguments.begin(); it != a_Arguments.end(); ++it)
    {
        if(*it == nullptr OR (*it)->getValueType() == nullptr) return;
        types.push_back((*it)->getValueType());
    }
    implicitConversions(a_pLanguage, types, a_pContextScope, a_ImplicitConversions);
}

bool Signature::equals( Signature* a_pOther ) const
{
    if(m_Modifiers != a_pOther->m_Modifiers) 
        return false;
    vector<Type*> types;
    for(size_t i = 0; i<m_Parameters.size(); ++i)
    {
       if(NOT(m_Parameters[i]->getValueType()->equals(a_pOther->m_Parameters[i]->getValueType())))
           return false;
    }
    return m_pReturnType->equals(a_pOther->m_pReturnType);
}

string Signature::getQualifiedDecoratedName() const
{
    string result = "(";
    auto it = m_Parameters.begin();
    auto end = m_Parameters.end();
    for(;it!=end;++it)
    {
        if(it != m_Parameters.begin())
        {
            result += ", ";
        }
        result += (*it)->getQualifiedDecoratedName();
    }
    result += ")";
    if(isConst())
    {
        result += " const";
    }
    //result += m_pReturnType->getQualifiedDecoratedName();
    return result;
}

string Signature::getQualifiedName() const
{
    string result = "(";
    auto it = m_Parameters.begin();
    auto end = m_Parameters.end();
    for(;it!=end;++it)
    {
        if(it != m_Parameters.begin())
        {
            result += ", ";
        }
        result += (*it)->getQualifiedName();
    }
    result += ")";
    //result += m_pReturnType->getQualifiedName();
    return result;
}

string Signature::getDecoratedName() const
{
    string result = "(";
    auto it = m_Parameters.begin();
    auto end = m_Parameters.end();
    for(;it!=end;++it)
    {
        if(it != m_Parameters.begin())
        {
            result += ", ";
        }
        result += (*it)->getDecoratedName();
    }
    result += ")";
    if(isConst())
    {
        result += " const";
    }
    return result;
}

Signature* Signature::clone() const
{
    Signature* pSignature = o_new(Signature);
    o_foreach(Parameter* pParameter, m_Parameters)
    {
        pSignature->addParameter(pParameter->clone());
    }
    pSignature->setReturnType(m_pReturnType);
    return pSignature;
}

bool Signature::equals( LanguageElement* a_pOther ) const
{
    if(NOT(a_pOther->asSignature())) return false;
    return equals(static_cast<Signature*>(a_pOther));
}

void Signature::setReturnTypeName( string name )
{
    if(name.size())
    {
        m_pReturnTypeName = new string(name);
    }
}

string Signature::getReturnTypeName() const
{
    return m_pReturnType ? m_pReturnType->getQualifiedDecoratedName() : "";
}

const string& Signature::getParameterName( size_t a_uiParamIndex ) const
{
    return m_Parameters[a_uiParamIndex]->getName();
}

Expression* Signature::getParameterDefaultValue( size_t a_uiParamIndex ) const
{
    return m_Parameters[a_uiParamIndex]->getInitializationExpression();
}

void Signature::setParameterName( size_t i, const string& a_strName )
{
    if(isNative())
    {
        o_exception(exception::base_exception, "Attempt to modify a native language element");
    }
    m_Parameters[i]->setName(a_strName);
}

vector<Type*> Signature::getParameterTypes() const
{
    vector<Type*> types;
    for(auto it = m_Parameters.begin(); it != m_Parameters.end(); ++it)
    {
        types.push_back((*it) ? (*it)->getValueType() : nullptr);
    }
    return types;
}

size_t Signature::getRequiredArgumentCount() const
{
    size_t defaultParameterCount = 0;
    for(auto it = m_Parameters.rbegin(); it != m_Parameters.rend(); ++it)
    {
        if((*it)->getInitializationExpression())
            defaultParameterCount++;
        else break;
    }
    return m_Parameters.size()-defaultParameterCount;
}

bool Signature::hasEllipsis() const
{
    return m_Parameters.size() AND m_Parameters.back()->getValueType()->asEllipsis();
}

size_t Signature::getMinimumNeededParameterCount() const
{
    size_t minimum = m_Parameters.size();
    for(auto it = m_Parameters.rbegin(); it != m_Parameters.rend(); ++it)
    {
        if((*it)->getInitializationExpression())
            minimum--;
        else 
            break;
    }
    return minimum;
}

bool Signature::matches( const vector<Type*>& a_ParameterTypes, modifiers_t a_Qualifiers ) const
{
    if(a_ParameterTypes.size() != getParameterCount() OR NOT(testModifiers(a_Qualifiers)))
    {
        return false;
    }
    for(size_t i = 0; i<m_Parameters.size(); ++i)
    {
        if(NOT(m_Parameters[i]->getValueType()->equals(a_ParameterTypes[i])))
            return false;
    }
    return true;
}

bool Signature::matches( const vector<Expression*>& arguments, modifiers_t a_Qualifiers ) const
{
    if(arguments.size() != getParameterCount() OR NOT(testModifiers(a_Qualifiers)))
    {
        return false;
    }
    for(size_t i = 0; i<m_Parameters.size(); ++i)
    {
        if(NOT(m_Parameters[i]->getValueType()->equals(arguments[i]->getValueType())))
            return false;
    }
    return true;
}

o_namespace_end(phantom, reflection)