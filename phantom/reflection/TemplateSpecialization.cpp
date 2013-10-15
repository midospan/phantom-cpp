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
/* ** The Class Header must be the last #include * */
#include <phantom/reflection/TemplateSpecialization.h>
/* *********************************************** */


o_cpp_begin 

ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP

TemplateSpecialization::TemplateSpecialization( )
: LanguageElement(o_CS("<>"),bitfield())
{
}


TemplateSpecialization::~TemplateSpecialization()
{
}

void            TemplateSpecialization::_updateName()
{
    m_strName = o_CS("<");
    uint i = 0;
    uint count = m_Elements.size();
    for(;i<count;++i)
    {
        TemplateElement*  pElement = m_Elements[i];
        if(i != 0) m_strName += o_CC(',');
        m_strName += pElement->getDecoratedName();
    }
    m_strName += o_CC('>');
}

phantom::string TemplateSpecialization::getQualifiedName() const
{
    string strQualifiedName = o_CS("<");
    uint i = 0;
    uint count = m_Elements.size();
    for(;i<count;++i)
    {
        TemplateElement*  pElement = m_Elements[i];
        if(i != 0) strQualifiedName += o_CC(',');
        strQualifiedName += pElement->getQualifiedDecoratedName();
    }
    strQualifiedName += o_CC('>');
    return strQualifiedName;
}

TemplateElement* TemplateSpecialization::getElement( const string& a_strTemplateElementName ) const
{
    template_element_map::const_iterator found = m_TemplateNameMap.find(a_strTemplateElementName);
    if(found == m_TemplateNameMap.end()) return NULL;
    return found->second;
}

Type*            TemplateSpecialization::getType(const string& a_strTemplateElementName) const
{
    TemplateElement* pTemplateElement = getElement(a_strTemplateElementName);
    if(pTemplateElement) return pTemplateElement->asType();
    return NULL;
}


void TemplateSpecialization::add( const string& a_strTemplateTypeName, TemplateElement* a_pElement )
{
    o_assert(m_TemplateNameMap.find(a_strTemplateTypeName) == m_TemplateNameMap.end());
    m_TemplateNameMap[a_strTemplateTypeName] = a_pElement;
    m_Elements.push_back(a_pElement);
    _updateName();
}

boolean TemplateSpecialization::matches( template_specialization const* a_TemplateSpecialization ) const
{
    size_t s0 = a_TemplateSpecialization->size();
    if(s0 != m_Elements.size()) return false;
    size_t i = 0;
    for(;i<s0;++i)
    {
        if((*a_TemplateSpecialization)[i] == NULL) return false;
        if(NOT( (*a_TemplateSpecialization)[i]->equals(m_Elements[i]) )) return false;
    }
    return true;
}

o_cpp_end