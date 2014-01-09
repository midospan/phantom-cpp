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

#ifndef o_phantom_reflection_TemplateSpecialization_h__
#define o_phantom_reflection_TemplateSpecialization_h__



/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "TemplateSpecialization.classdef.h"
/* **************** Declarations ***************** */
o_declare(class, phantom, reflection, Type)
/* *********************************************** */

o_h_begin

class o_export TemplateSpecialization : public LanguageElement
{
    friend class TemplateElement;
    friend class LanguageElement;
public:

    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection
public:

    TemplateSpecialization(Template* a_pTemplate);
    o_destructor ~TemplateSpecialization();

    uint                getElementCount() const { return m_Elements.size(); }
    Type*               getType(const string& a_strTypenameVariableName) const;
    TemplateElement*    getElement(const string& a_strTypenameVariableName) const;

    void                add(const string& a_strTemplateTypeName, TemplateElement* a_pElement);

    string              getQualifiedName() const;

    
    boolean             matches(template_specialization const* a_TemplateSpecialization) const;
  
    Template*           getTemplate() const { return m_pTemplate; }

protected:
    void            _updateName();

protected:
    typedef phantom::map<string, TemplateElement*>    template_element_map;
    template_element_map        m_TemplateNameMap;
    template_specialization     m_Elements;
    Template*                   m_pTemplate;

};

o_h_end


#else // o_phantom_reflection_InstanciableClass_h__ 
#include "TemplateSpecialization.classdef.h"
#endif
