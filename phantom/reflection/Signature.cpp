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
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include "phantom/reflection/Signature.h"
#include "phantom/reflection/Signature.hxx"
/* *********************************************** */
o_namespace_begin(phantom, reflection) 

Signature* Signature::Create( void )
{
    return o_new(Signature);
}

Signature* Signature::Create( const char* a_pText, phantom::reflection::TemplateSpecialization* a_pTemplateSpecialization, phantom::reflection::LanguageElement* a_pScope )
{
    return o_new(Signature)(a_pText, a_pTemplateSpecialization, a_pScope);
}

Signature::Signature( void ) : m_pReturnType(NULL)
, m_uiArgumentStorageSize(0)
{

}

Signature::Signature( const string& a_strSignature, TemplateSpecialization* a_pTemplateSpecialization /*= NULL*/, LanguageElement* a_pScope /*= (LanguageElement*)phantom::rootNamespace() */ )
    : m_pReturnType(NULL)
    , m_uiArgumentStorageSize(0)
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
                if(NOT(ParseParameterTypeList(a_strSignature.substr(i), a_pTemplateSpecialization, parameterTypes, a_pScope)))
                {
                    o_exception(exception::invalid_parsing_exception, a_strSignature.substr(i).c_str());
                }
                else 
                {
                    for(auto it = parameterTypes.begin(); it != parameterTypes.end(); ++it)
                    {
                        addParameterType(*it);
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

void Signature::addParameterType( Type* a_pType )
{
    o_assert(a_pType && a_pType->isCopyable() );
    m_ParametersTypes.push_back(a_pType);
    addReferencedElement(a_pType);
    updateName();
}

void Signature::setReturnType( Type* a_pType )
{
    o_assert(a_pType && a_pType->isCopyable());
    m_pReturnType = a_pType;
    addReferencedElement(a_pType);
    updateName();
}

void Signature::referencedElementRemoved(LanguageElement* a_pElement)
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
}

boolean Signature::SeparateParameterTypes( const string& a_strText, TemplateSpecialization* a_pTemplateSpecialization, vector<Type*>& a_OutParameterTypes, LanguageElement* a_pScope )
{
    string parameterType;
    size_t length = a_strText.length();
    size_t i = 0;
    size_t template_level = 0;
    for(;i<length;++i)
    {
        character c = a_strText[i];
        if( c == ',' AND template_level == 0 )
        {
            Type* pType = phantom::typeByName(parameterType, a_pScope);
            if(pType == NULL)
            {
                a_OutParameterTypes.clear();
                return false;
            }
            a_OutParameterTypes.push_back(pType);
            parameterType.clear();
        }
        else 
        {
            if( c == '<' )
            {
                ++template_level;
            }
            else if( c == '>')
            {
                if(template_level == 0) 
                {
                    a_OutParameterTypes.clear();
                    return false;
                }
                --template_level;
            }
            parameterType += c;
        }
    }
    if(template_level == 0 AND NOT(parameterType.empty()))
    {
        Type* pType = phantom::typeByName(parameterType, a_pScope);
        if(pType == NULL) 
        {
            a_OutParameterTypes.clear();
            return false;
        }
        a_OutParameterTypes.push_back(pType);
        return true;
    }
    a_OutParameterTypes.clear();
    return false;
}

boolean Signature::ParseParameterTypeList( const string& a_strText, TemplateSpecialization* a_pTemplateSpecialization, vector<Type*>& a_OutParameterTypes, LanguageElement* a_pScope )
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
    return SeparateParameterTypes(words.front(), a_pTemplateSpecialization, a_OutParameterTypes, a_pScope);
}

bool Signature::matches( const vector<Type*>& a_FunctionSignature, vector<size_t>* a_pPartialMatchesIndexes ) const
{
    size_t count = a_FunctionSignature.size();
    if(count != m_ParametersTypes.size()) return false;
    size_t i = 0;
    bool result = true;
    for(;i<count;++i)
    {
        if(NOT(a_FunctionSignature[i]->isImplicitlyConvertibleTo(m_ParametersTypes[i]))) 
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
        pSignature->addParameterType(pParameterType);
    }
    pSignature->setReturnType(m_pReturnType);
    return pSignature;
}

bool Signature::equals( LanguageElement* a_pOther ) const
{
    if(NOT(phantom::is<Signature>(a_pOther))) return false;
    Signature*    pOther = static_cast<Signature*>(a_pOther);
    if(NOT(compareParameterList(pOther))) return false;
    return m_pReturnType == pOther->m_pReturnType;
}

o_namespace_end(phantom, reflection)