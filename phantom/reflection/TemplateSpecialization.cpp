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

TemplateSpecialization::TemplateSpecialization( Template* a_pTemplate )
    : LanguageElement(o_CS("<>"), modifiers_t())
    , m_pTemplate(a_pTemplate)
    , m_DefaultArgumentsCount(0)
{
    m_pTemplate->registerSpecialization(this);
}

TemplateSpecialization::~TemplateSpecialization()
{
    m_pTemplate->unregisterSpecialization(this);
}

void TemplateSpecialization::_updateName()
{
    m_strName = o_CS("< ");
    uint i = 0;
    uint count = m_Arguments.size();
    for(;i<count;++i)
    {
        TemplateElement*  pElement = m_Arguments[i].element;
        if(i != 0) m_strName += o_CS(", ");
        m_strName += pElement->asLanguageElement()->getDecoratedName();
    }
    m_strName += o_CS(" >");
}

phantom::string TemplateSpecialization::getQualifiedName() const
{
    string strQualifiedName = o_CS("< ");
    uint i = 0;
    uint count = m_Arguments.size();
    for(;i<count;++i)
    {
        TemplateElement*  pElement = m_Arguments[i].element;
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
        TemplateElement*  pElement = m_Arguments[i].element;
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

TemplateElement* TemplateSpecialization::getArgumentElement( const string& a_strParameterName ) const
{
    for(auto it = m_Arguments.begin(); it != m_Arguments.end(); ++it)
    {
        if(it->name == a_strParameterName)
            return it->element;
    }
    return nullptr;
}

Type* TemplateSpecialization::getType(const string& a_strParameterName) const
{
    TemplateElement* pTemplateElement = getArgumentElement(a_strParameterName);
    if(pTemplateElement) return pTemplateElement->asLanguageElement()->asType();
    return NULL;
}

void TemplateSpecialization::setArgument( const string& a_strTemplateTypeName, TemplateElement* a_pElement )
{
    o_assert(a_pElement);
    o_assert(getArgumentElement(a_strTemplateTypeName) == nullptr);
    m_Arguments.push_back(Argument(a_strTemplateTypeName, a_pElement));
    LanguageElement* pElement = a_pElement->asLanguageElement();
    if(pElement->getOwner())
        addReferencedElement(pElement);
    else 
        addElement(pElement);
    _updateName();
}

void TemplateSpecialization::removeArgument( TemplateElement* a_pElement )
{
    LanguageElement* pElement = a_pElement->asLanguageElement();
    if(pElement->getOwner())
        removeReferencedElement(pElement);
    else 
        removeElement(pElement);
}

void TemplateSpecialization::referencedElementAdded(LanguageElement* a_pElement)
{
}

void TemplateSpecialization::referencedElementRemoved(LanguageElement* a_pElement)
{
    for(auto it = m_Arguments.begin(); it != m_Arguments.end(); )
    {
        if(it->defaultElement && it->defaultElement->asLanguageElement() == a_pElement)
            it->defaultElement = nullptr;
        if(it->element->asLanguageElement() == a_pElement)
        {
            it = m_Arguments.erase(it);
        }
        else ++it;
    }
}

boolean TemplateSpecialization::matches( const vector<TemplateElement*>* a_TemplateSpecialization ) const
{
    size_t s0 = a_TemplateSpecialization->size();
    if((s0 < m_Arguments.size()-m_DefaultArgumentsCount) || (s0 > m_Arguments.size())) 
        return false;
    size_t i = 0;
    for(;i<m_Arguments.size();++i)
    {
        if(i<s0)
        {
            if((*a_TemplateSpecialization)[i] == NULL) return false;
            if(NOT( (*a_TemplateSpecialization)[i]->asLanguageElement()->equals(m_Arguments[i].element->asLanguageElement()) )) return false;
        }
        else 
        {
            if(m_Arguments[i].element != m_Arguments[i].defaultElement) // default argument doesn't match current specialization argument
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

TemplateElement* TemplateSpecialization::getDefaultArgument(const string& a_strParameterName) const 
{
    for(auto it = m_Arguments.begin(); it != m_Arguments.end(); ++it)
    {
        if(it->name == a_strParameterName)
            return it->defaultElement;
    }
    return nullptr;
}

void TemplateSpecialization::setDefaultArgument( const string& a_strParameterName, TemplateElement* a_pElement )
{
    o_assert(a_pElement, "Argument type has not been registered");
    o_assert(getDefaultArgument(a_strParameterName) == nullptr);
    size_t index = getArgumentIndex(a_strParameterName);
    if(index != (m_Arguments.size() - m_DefaultArgumentsCount - 1))
    {
        o_exception(exception::invalid_argument_exception, "Default template arguments must be passed from right to left, contiguously");
    }
    m_Arguments[index].defaultElement = a_pElement;
    m_DefaultArgumentsCount++;
    LanguageElement* pElement = a_pElement->asLanguageElement();
    if(pElement->getOwner())
    {
        if (m_pReferencedElements == nullptr 
            OR std::find(m_pReferencedElements->begin(), m_pReferencedElements->end(), pElement) == m_pReferencedElements->end())
        {
            addReferencedElement(pElement);
        }
    }
    else 
    {
        addElement(pElement);
    }
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
        if(it->defaultElement && it->defaultElement->asLanguageElement() == a_pElement)
            it->defaultElement = nullptr;
        if(it->element->asLanguageElement() == a_pElement)
        {
            it = m_Arguments.erase(it);
        }
        else ++it;
    }
    LanguageElement::elementRemoved(a_pElement);
}

o_namespace_end(phantom, reflection)