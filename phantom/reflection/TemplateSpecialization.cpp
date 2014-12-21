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
#include <phantom/reflection/TemplateSpecialization.h>
#include <phantom/reflection/TemplateSpecialization.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), TemplateSpecialization);


o_namespace_begin(phantom, reflection) 

TemplateSpecialization::TemplateSpecialization( Template* a_pTemplate, const vector<LanguageElement*>& arguments, TemplateSignature* a_pSignature = nullptr )
    : m_pTemplate(a_pTemplate)
    , m_pTemplateSignature(a_pSignature)
{
    o_assert(m_pTemplate->getTemplateParameterCount() == arguments.size());
    m_pTemplate->registerSpecialization(this);
    m_Arguments.resize(a_pTemplate->getTemplateParameterCount());
}

TemplateSpecialization::~TemplateSpecialization()
{
    m_pTemplate->unregisterSpecialization(this);
}

phantom::string TemplateSpecialization::getQualifiedName() const
{
    string strQualifiedName = o_CS("< ");
    uint i = 0;
    uint count = m_Arguments.size();
    for(;i<count;++i)
    {
        LanguageElement*  pElement = m_Arguments[i].element;
        LanguageElement*  pLanguageElement = pElement->asLanguageElement();
        if(i != 0) strQualifiedName += o_CS(", ");
        if(pLanguageElement->asNumericConstant())
        {
            strQualifiedName += pLanguageElement->getQualifiedName();
        }
        else strQualifiedName += pLanguageElement->getQualifiedName();
    }
    strQualifiedName += o_CS(" >");
    return strQualifiedName;
}

phantom::string TemplateSpecialization::getQualifiedDecoratedName() const
{
    string strQualifiedName = o_CS("< ");
    uint i = 0;
    uint count = m_Arguments.size();
    for(;i<count;++i)
    {
        LanguageElement*  pElement = m_Arguments[i].element;
        LanguageElement*  pLanguageElement = pElement->asLanguageElement();
        if(i != 0) strQualifiedName += o_CS(", ");
        if(pLanguageElement->asNumericConstant())
        {
            strQualifiedName += pLanguageElement->getQualifiedDecoratedName();
        }
        else strQualifiedName += pLanguageElement->getQualifiedDecoratedName();
    }
    strQualifiedName += o_CS(" >");
    return strQualifiedName;
}

LanguageElement* TemplateSpecialization::getArgument( const string& a_strParameterName ) const
{
    size_t index = m_pTemplate->getTemplateParameterIndex(a_strParameterName);
    o_assert(index != ~size_t(0));
    return m_Arguments[index];
}

Type* TemplateSpecialization::getType(const string& a_strParameterName) const
{
    LanguageElement* pTemplateElement = getArgument(a_strParameterName);
    if(pTemplateElement) return pTemplateElement->asType();
    return nullptr;
}

void TemplateSpecialization::setArgument( size_t a_uiIndex, const string& a_strParameterAlias, LanguageElement* a_pElement )
{
    size_t index = a_uiIndex;
    o_assert(index != ~size_t(0));
    if(a_pElement == nullptr) setInvalid();
    o_assert(getArgument(a_strParameterAlias) == nullptr);
    m_Arguments[index] = a_pElement;
    if(a_pElement)
    {
        if(a_pElement->getOwner())
            addReferencedElement(a_pElement);
        else 
            addElement(a_pElement);
    }
    size_t paramIndex = m_pTemplate->getTemplateParameterIndex(a_strParameterAlias);
    if(paramIndex != ~size_t(0))
    {
        if(paramIndex != a_uiIndex)
        {
            o_exception(exception::base_exception, "template parameter name reused for different template parameter");
        }
    }
    else m_pTemplate->addTemplateParameterAliasName(a_uiIndex, a_strParameterAlias);
}

void TemplateSpecialization::setArgument( size_t a_uiIndex, LanguageElement* a_pElement )
{
    size_t index = a_uiIndex;
    o_assert(index != ~size_t(0));
    o_assert(m_Arguments[index] == nullptr);
    if(a_pElement == nullptr) setInvalid();
    m_Arguments[index] = a_pElement;
    if(a_pElement)
    {
        if(a_pElement->getOwner())
            addReferencedElement(a_pElement);
        else 
            addElement(a_pElement);
    }
}

void TemplateSpecialization::removeArgument( LanguageElement* a_pElement )
{
    if(a_pElement->getOwner())
        removeReferencedElement(a_pElement);
    else 
        removeElement(a_pElement);
}

void TemplateSpecialization::referencedElementAdded(LanguageElement* a_pElement)
{
}

void TemplateSpecialization::referencedElementRemoved(LanguageElement* a_pElement)
{
    for(auto it = m_Arguments.begin(); it != m_Arguments.end(); )
    {
        if(*it == a_pElement)
        {
            it = m_Arguments.erase(it);
        }
        else ++it;
    }
}

boolean TemplateSpecialization::matches( const vector<LanguageElement*>& a_TemplateSpecialization ) const
{
    size_t s0 = a_TemplateSpecialization->size();
    if((s0 < m_Arguments.size()-m_pTemplate->getDefaultArgumentCount()) || (s0 > m_Arguments.size())) 
        return false;
    size_t i = 0;
    for(;i<m_Arguments.size();++i)
    {
        if(i<s0)
        {
            if((*a_TemplateSpecialization)[i] == nullptr) return false;
            if(NOT( (*a_TemplateSpecialization)[i]->equals(m_Arguments[i]) )) return false;
        }
        else 
        {
            if(m_Arguments[i] != m_pTemplate->getDefaultArgument(i)) // default argument doesn't match current specialization argument
                return false;
        }
    }
    return true;
}

void TemplateSpecialization::checkCompleteness() const
{
    o_assert(m_pTemplate);
    if(m_pTemplate->getModule() == nullptr)
    {
        o_exception(exception::reflection_runtime_exception, "Template not registered for this template specialization");
    }
}

bool TemplateSpecialization::canBeDestroyed() const
{
    return LanguageElement::canBeDestroyed();
}

size_t TemplateSpecialization::getArgumentIndex( const string& a_strParameterName ) const
{
    for(size_t i = 0; i<m_Arguments.size(); ++i)
    {
        if(m_Arguments[i].name == a_strParameterName)
            return i;
    }
    o_assert(false);
    return 0xffffffff;
}

void TemplateSpecialization::elementAdded( LanguageElement* a_pElement )
{
    LanguageElement::elementAdded(a_pElement);
}

void TemplateSpecialization::elementRemoved( LanguageElement* a_pElement )
{
    for(auto it = m_Arguments.begin(); it != m_Arguments.end(); )
    {
        if(*it == a_pElement)
        {
            it = m_Arguments.erase(it);
        }
        else ++it;
    }
    LanguageElement::elementRemoved(a_pElement);
}

bool TemplateSpecialization::isEmpty() const
{
    for(auto it = m_Arguments.begin(); it != m_Arguments.end(); ++it)
    {
        if((*it)->asPlaceholder() != nullptr) return false; // we found a placeholder => still template dependant
    }
    return true;
}

bool TemplateSpecialization::isPartial() const
{
    return m_pTemplateSignature != nullptr;
}

bool TemplateSpecialization::isSpecializingParameter( TemplateParameter* a_pParameter ) const
{
    size_t i = m_pTemplate->getTemplateParameterIndex(a_pParameter);
    return (i != ~size_t(0)) AND (m_Arguments[i] != nullptr);
}

bool TemplateSpecialization::isSpecializing( LanguageElement* a_pLanguageElement )
{
    if(a_pLanguageElement->m_pTemplateParameterDependencies == nullptr) return false;
    for(auto it = a_pLanguageElement->m_pTemplateParameterDependencies->begin(); it != a_pLanguageElement->m_pTemplateParameterDependencies->end(); ++it)
    {
        TemplateParameter* pDependency = *it;
        if(isSpecializingParameter(pDependency)) return true;
        for(auto it = a_pLanguageElement->beginElements(); it != a_pLanguageElement->endElements(); ++it)
        {
            if(isSpecializing(*it)) return true;
        }
        for(auto it = a_pLanguageElement->beginReferencedElements(); it != a_pLanguageElement->endReferencedElements(); ++it)
        {
            if(isSpecializing(*it)) return true;
        }
    }
    return false;
}

bool TemplateSpecialization::equals( TemplateSpecialization* a_pTemplateSpecialization ) const
{
    return a_pTemplateSpecialization->getTemplate() == m_pTemplate 
        AND matches(a_pTemplateSpecialization->getArguments());
}

int TemplateSpecialization::score( const vector<LanguageElement*>& a_TemplateSpecialization ) const
{

}

o_namespace_end(phantom, reflection)