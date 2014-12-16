/*
    This file is part of PHANTOM
         P reprocessed 
         H igh-level 
         A llocator 
         N ested state-machines and 
         T emplate 
         O riented 
         M eta-programming

    For the latest infos and sources, see http://code.google.com/p/phantom-cpp

    Copyright (C) 2008-2011 by Vivien MILLET

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE
*/

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "phantom/reflection/Signature.h"
#include "phantom/reflection/Signature.hxx"
#include "phantom/reflection/Expression.h"
#include "phantom/reflection/LocalVariable.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <sstream>
/* *********************************************** */
o_registerN((phantom, reflection), Signature);

o_namespace_begin(phantom, reflection) 

Signature* Signature::Create( void )
{
    return o_new(Signature);
}

Signature* Signature::Create( const char* a_pText, phantom::reflection::TemplateSpecialization* a_pTemplateSpecialization, phantom::reflection::LanguageElement* a_pScope )
{
    return o_new(Signature)(a_pText, a_pTemplateSpecialization, a_pScope);
}

Signature* Signature::Create( Type* a_pType )
{
    return o_new(Signature)(a_pType);
}

Signature::Signature( void ) : m_pReturnType(NULL)
, m_uiArgumentStorageSize(0)
, m_pReturnTypeName(nullptr)
, m_pParameterTypeNames(nullptr)
{

}

Signature::Signature( Type* a_pType )
    : m_pReturnType(NULL)
    , m_uiArgumentStorageSize(0)
    , m_pReturnTypeName(nullptr)
    , m_pParameterTypeNames(nullptr)
{
    setReturnType(a_pType);
}

Signature::Signature( const string& a_strSignature, TemplateSpecialization* a_pTemplateSpecialization /*= NULL*/, LanguageElement* a_pScope /*= (LanguageElement*)phantom::rootNamespace() */ )
    : m_pReturnType(NULL)
    , m_uiArgumentStorageSize(0)
    , m_pReturnTypeName(nullptr)
    , m_pParameterTypeNames(nullptr)
{
    parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
}

void Signature::parse( const string& a_strSignature, TemplateSpecialization* a_pTemplateSpecialization, LanguageElement* a_pScope /*= NULL*/)
{
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
            if(pReturnType == NULL AND a_pTemplateSpecialization != NULL)
            {
                pReturnType = a_pTemplateSpecialization->getType(returnType);
            }
            if(pReturnType == nullptr)
            {
                pReturnType = phantom::typeByName(returnType, a_pScope);
            }
            if(pReturnType == NULL) 
            {
                o_exception(exception::unknown_reflection_type_exception, returnType.c_str());
            }
            else
            {
                setReturnType(pReturnType);
                vector<Type*> parameterTypes;
                vector<string> parameterNames;
                vector<Expression*> parameterExps;
                if(NOT(ParseParameterTypeList(a_strSignature.substr(i), a_pTemplateSpecialization, parameterTypes, parameterNames, parameterExps, a_pScope)))
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
            return;
        }
        else
        {
            returnType += c;
        }
    }
}

Signature::~Signature( void )
{
}

void Signature::addParameter( Type* a_pType, const string& a_strName, Expression* a_pExpression )
{
    o_assert(a_pType && a_pType->isCopyable() );
    m_ParametersTypes.push_back(a_pType);
    m_ParameterNames.push_back(a_strName);
    m_ParameterDefaultValues.push_back(a_pExpression);
    if(a_pExpression)
    {
        addElement(a_pExpression);
    }
    addReferencedElement(a_pType);
    updateName();
}

void Signature::setReturnType( Type* a_pType )
{
    o_assert(a_pType AND (a_pType == typeOf<void>() OR a_pType->isCopyable()));
    m_pReturnType = a_pType;
    addReferencedElement(a_pType);
    updateName();
}

void Signature::referencedElementRemoved(LanguageElement* a_pElement)
{
    if(a_pElement->asExpression())
    {
        auto found = std::find(m_ParameterDefaultValues.begin(), m_ParameterDefaultValues.end(), a_pElement->asExpression());
        if(found != m_ParameterDefaultValues.end())
        {
            m_ParameterDefaultValues.erase(found);
        }
    }
    else
    {
        bool bFound = true;
        while(bFound)
        {
            bFound = false;
            for(auto it = m_ParametersTypes.begin(); it != m_ParametersTypes.end(); ++it)
            {
                if((*it) == a_pElement)
                {
                    bFound = true;
                    m_ParametersTypes.erase(std::find(m_ParametersTypes.begin(), m_ParametersTypes.end(), a_pElement));
                    break;
                }
            }
            if(m_pReturnType == a_pElement)
            {
                m_pReturnType = nullptr;
            }
        }
    }
    LanguageElement::referencedElementRemoved(a_pElement);
}

size_t Signature::getParameterCount() const
{
    return m_ParametersTypes.size();
}

Type* Signature::getParameterType( size_t a_uiParamIndex ) const
{
    o_assert(a_uiParamIndex < getParameterCount(), "Index too big");
    return m_ParametersTypes[a_uiParamIndex];
}

Type* Signature::getReturnType() const
{
    return m_pReturnType;
}/*

bool Signature::ParseParameter(const string& parameter, Type*& a_OutType, string& a_OutName, Expression*& a_OutExpression, LanguageElement* a_pScope)
{
    size_t j = parameter.size();
    string word;
    string parameterDecl;
    while(j--)
    {
        char c = parameter[j];
        if(o_char_is_blank(c))
        {
            if(!word.empty())
            {
                Type* pType = phantom::typeByName(parameter.substr(0, j), a_pScope);
                if(pType != nullptr)
                {
                    parameterDecl = string(word.rbegin(), word.rend());
                    size_t equalPos = parameterDecl.find_first_of("=");
                    if(equalPos != string::npos)
                    {
                        Expression* pExpression = expressionByName(parameterDecl.substr(equalPos+1));
                        if(pExpression == nullptr OR NOT(pExpression->getValueType()->isImplicitlyConvertibleTo(pType)))
                        {
                            return false;
                        }
                        a_OutExpression = pExpression;
                        a_OutName = parameterDecl.substr(0, equalPos);
                    }
                    else 
                    {
                        a_OutParameterExps.push_back(nullptr);
                    }
                    a_OutType = pType;
                    return true;
                }
            }
        }
        word += c;
    }
    if(!word.empty())
    {
        Type* pType = phantom::typeByName(string(word.rbegin(), word.rend()), a_pScope);
        if(pType != nullptr)
        {
            a_OutType = pType;
            a_OutName = "";
            a_OutExpression = nullptr;
            return true;
        }
    }
    return false;
}*/

bool Signature::SeparateParameters( const string& a_strText, TemplateSpecialization* a_pTemplateSpecialization, vector<string>& a_OutParameters, LanguageElement* a_pScope )
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

bool Signature::ParseParameterTypeList( const string& a_strText, TemplateSpecialization* a_pTemplateSpecialization, vector<Type*>& a_OutParameterTypes, vector<string>& a_OutParameterNames, vector<Expression*>& a_OutParameterExps, LanguageElement* a_pScope )
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
    SeparateParameters(words.front(), a_pTemplateSpecialization, parameters, a_pScope);
    for(auto it = parameters.begin(); it != parameters.end(); ++it)
    {
        Type* pType = nullptr;
        string name;
        Expression* pExpression = nullptr;
        if(NOT(LocalVariable::Parse(*it, pType, name, pExpression, a_pScope)))
        {
            goto end_false;
        }
        else 
        {
            // remove name blanks
            name.erase(std::remove(name.begin(), name.end(), ' '), name.end());
            name.erase(std::remove(name.begin(), name.end(), '\t'), name.end());
            name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
            name.erase(std::remove(name.begin(), name.end(), '\r'), name.end());
            a_OutParameterTypes.push_back(pType);
            a_OutParameterNames.push_back(name);
            a_OutParameterExps.push_back(pExpression);
        }
    }
    return true;

end_false:
    a_OutParameterTypes.clear();
    a_OutParameterNames.clear();
    for(auto it = a_OutParameterExps.begin(); it != a_OutParameterExps.end(); ++it){o_dynamic_delete *it;}
    a_OutParameterExps.clear();
    return false;
}

bool Signature::matches( const vector<Type*>& a_FunctionSignature, vector<size_t>* a_pPartialMatchesIndexes ) const
{
    size_t count = a_FunctionSignature.size();
    if(count != m_ParametersTypes.size()) return false;
    size_t i = 0;
    bool result = true;
    for(;i<count;++i)
    {
        Type* pParamType = m_ParametersTypes[i];
        ReferenceType* pRefType = m_ParametersTypes[i]->asReferenceType();
        if(pRefType AND pRefType->getReferencedType()->asConstType())
            pParamType = pParamType->removeReference()->removeConst();
        if(NOT(a_FunctionSignature[i]->isImplicitlyConvertibleTo(pParamType))) 
        {
            if(a_pPartialMatchesIndexes) 
            {
                result = false;
            } 
            else return false;
        }
        else if((a_FunctionSignature[i] != m_ParametersTypes[i]))
        {
            if(a_pPartialMatchesIndexes)
            {
                a_pPartialMatchesIndexes->push_back(i);
            }
            else return false;
        }
    }
    return result;
}

void Signature::updateName()
{
    m_strName = "(";
    auto it = m_ParametersTypes.begin();
    auto end = m_ParametersTypes.end();
    for(;it!=end;++it)
    {
        if(it != m_ParametersTypes.begin())
        {
            m_strName += ", ";
        }
        m_strName += (*it)->getName();
    }
    m_strName += ")";
    //m_strName += m_pReturnType->getName();
}

string Signature::getQualifiedDecoratedName() const
{
    string result = "(";
    auto it = m_ParametersTypes.begin();
    auto end = m_ParametersTypes.end();
    for(;it!=end;++it)
    {
        if(it != m_ParametersTypes.begin())
        {
            result += ", ";
        }
        result += (*it)->getQualifiedDecoratedName();
    }
    result += ")";
    //result += m_pReturnType->getQualifiedDecoratedName();
    return result;
}

string Signature::getQualifiedName() const
{
    string result = "(";
    auto it = m_ParametersTypes.begin();
    auto end = m_ParametersTypes.end();
    for(;it!=end;++it)
    {
        if(it != m_ParametersTypes.begin())
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
    auto it = m_ParametersTypes.begin();
    auto end = m_ParametersTypes.end();
    for(;it!=end;++it)
    {
        if(it != m_ParametersTypes.begin())
        {
            result += ", ";
        }
        result += (*it)->getDecoratedName();
    }
    result += ")";
    //result += m_pReturnType->getDecoratedName();
    return result;
}

Signature* Signature::clone() const
{
    Signature* pSignature = o_new(Signature);
    o_foreach(Type* pParameterType, m_ParametersTypes)
    {
        pSignature->addParameter(pParameterType);
    }
    pSignature->setReturnType(m_pReturnType);
    return pSignature;
}

bool Signature::equals( LanguageElement* a_pOther ) const
{
    if(NOT(phantom::as<Signature*>(a_pOther))) return false;
    Signature*    pOther = static_cast<Signature*>(a_pOther);
    if(NOT(compareParameterList(pOther))) return false;
    return m_pReturnType == pOther->m_pReturnType;
}

void Signature::setParameterTypeNames( vector<string> names )
{
    if(names.size())
    {
        m_pParameterTypeNames = new vector<string>(names);
    }
}

vector<string> Signature::getParameterTypeNames() const
{
    vector<string> names;
    for(auto it = m_ParametersTypes.begin(); it != m_ParametersTypes.end(); ++it)
    {
        if(*it)
        {
            names.push_back((*it)->getQualifiedDecoratedName());
        }
    }
    return names;
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

void Signature::finalize()
{
    if(m_pReturnTypeName)
    {
        m_pReturnType = typeByName(*m_pReturnTypeName);
        delete m_pReturnTypeName;
        m_pReturnTypeName = nullptr;
    }
    if(m_pParameterTypeNames)
    {
        for(auto it = m_pParameterTypeNames->begin(); it != m_pParameterTypeNames->end(); ++it)
        {
            addParameter(typeByName(*it));
        }
        delete m_pParameterTypeNames;
        m_pParameterTypeNames = nullptr;
    }
}

const string& Signature::getParameterName( size_t a_uiParamIndex ) const
{
    return m_ParameterNames[a_uiParamIndex];
}

Expression* Signature::getParameterDefaultValue( size_t a_uiParamIndex ) const
{
    return m_ParameterDefaultValues[a_uiParamIndex];
}

void Signature::setParameterName( size_t i, const string& a_strName )
{
    if(isNative())
    {
        o_exception(exception::base_exception, "Attempt to modify a native language element");
    }
    m_ParameterNames[i] = a_strName;
}

o_namespace_end(phantom, reflection)