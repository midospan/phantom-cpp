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
#include <phantom/reflection/TemplateSignature.h>
#include <phantom/reflection/TemplateSignature.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), TemplateSignature);

o_namespace_begin(phantom, reflection) 

TemplateSignature::TemplateSignature(size_t a_uiParameterCount)
{
    m_Parameters.resize(a_uiParameterCount);
}

TemplateSignature::TemplateSignature( const string& a_strTemplateTypes, const string& a_strTemplateParams )
{
    vector<Type*> templateTypes;
    vector<string> types;
    split( types, a_strTemplateTypes, boost::is_any_of(","), boost::token_compress_on );
    vector<string> names;
    split( names, a_strTemplateParams, boost::is_any_of(","), boost::token_compress_on );
    o_assert(types.size() == names.size());
}

TemplateSignature::~TemplateSignature()
{

}

size_t TemplateSignature::getParameterIndex( const string& a_strName ) const
{
    for(size_t i = 0; i<m_Parameters.size(); ++i)
    {
        if(m_Parameters[i]->getName() == a_strName) return i;
    }
    auto found = m_ParameterAliasNames.find(a_strName);
    return found != m_ParameterAliasNames.end() ? found->second : ~size_t(0);
}

size_t TemplateSignature::getParameterIndex( TemplateParameter* a_pParameter ) const
{
    for(size_t i = 0; i<m_Parameters.size(); ++i)
    {
        if(m_Parameters[i] == a_pParameter) return i;
    }
    return ~size_t(0);
}

LanguageElement* TemplateSignature::getDefaultArgument(const string& a_strParameterName) const 
{
    size_t index = getParameterIndex(a_strParameterName);
    o_assert(index != ~size_t(0));
    return m_Parameters[i]->getDefaultArgument();
}

void TemplateSignature::setDefaultArgument( const string& a_strParameterName, LanguageElement* a_pElement )
{
    size_t index = getParameterIndex(a_strParameterName);
    o_assert(index != ~size_t(0));
    m_Parameters[i]->setDefaultArgument(a_pElement);
}

size_t TemplateSignature::getDefaultArgumentCount() const
{
    size_t i = 0;
    for(; i<m_Parameters.size(); ++i)
    {
        if(m_Parameters[i]->getDefaultArgument() == nullptr) return i;
    }
    return i;
}

void TemplateSignature::addParameter( TemplateParameter* a_pTemplateParameter )
{
    if(getParameterIndex(a_pTemplateParameter->getName()) != ~size_t(0))
    {
        setInvalid();
    }
    m_Parameters.push_back(a_pTemplateParameter);
    LanguageElement* pPH = a_pTemplateParameter->getPlaceholder() ? a_pTemplateParameter->getPlaceholder()->asLanguageElement() : nullptr;
    m_Placeholders.push_back(pPH);
    if(pPH)
    {
        addReferencedElement(pPH);
    }
}

void TemplateSignature::addParameterAliasName( size_t a_uiIndex, const string& a_strAlias )
{
    o_assert(getParameterIndex(a_strAlias) == ~size_t(0));
    m_ParameterAliasNames[a_strAlias] = a_uiIndex;
}

o_namespace_end(phantom, reflection)