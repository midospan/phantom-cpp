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

#ifndef o_phantom_reflection_Placeholder_h__
#define o_phantom_reflection_Placeholder_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Placeholder 
{
    o_declare_meta_type(Placeholder);

public:
    Placeholder(const string& a_strName, modifiers_t a_Modifiers = 0)
        : Type(e_placeholder, a_strName, 0, 0, a_Modifiers) 
    {}
    
    virtual Placeholder*    asPlaceholder() const = 0;

    virtual PlaceholderType*    asPlaceholderType() const = 0;

    virtual PlaceholderConstant*    asPlaceholderConstant() const = 0;

};

class o_export PlaceholderType : public Type, public Placeholder
{
    o_type;

    o_declare_meta_type(PlaceholderType);

public:
    PlaceholderType(const string& a_strName, TemplateParameter* a_pParameterDependency = nullptr, modifiers_t a_Modifiers = 0)
        : Type(e_placeholder, a_strName, 0, 0, a_Modifiers) 
    {
        if(a_pParameterDependency)
        {
            addTemplateParameterDependency(a_pParameterDependency);
        }
    }

    virtual Placeholder*        asPlaceholder() const { return (PlaceholderType*)this; }
    virtual PlaceholderType*    asPlaceholderType() const { return (PlaceholderType*)this; }

    virtual LanguageElement*    internalInstanciateTemplate(TemplateSpecialization* a_pSpecialization) 
    {
        LanguageElement* pElement = a_pSpecialization->getArgument(getName());
        return pElement AND pElement->asType() ? pElement : this;
    }
};

class o_export PlaceholderClass : public Class, public Placeholder
{
    o_type;

    o_declare_meta_type(PlaceholderClass);

public:
    PlaceholderClass(PlaceholderType* a_pPlaceholderType)
        : Class(a_pPlaceholderType->getName(), 0, 0, a_pPlaceholderType->getModifiers()) 
    {
        addTemplateParameterDependency(a_pPlaceholderType->getTemplateParameterDependency());
    }

    virtual Placeholder*        asPlaceholder() const { return (PlaceholderClass*)this; }
    virtual PlaceholderClass*   asPlaceholderClass() const { return (PlaceholderClass*)this; }

    virtual LanguageElement*    internalInstanciateTemplate(TemplateSpecialization* a_pSpecialization) 
    {
        LanguageElement* pElement = a_pSpecialization->getArgument(getName());
        if(pElement AND pElement->asClass()) 
        {
            return pElement;
        }
        return this;
    }
};

o_namespace_end(phantom, reflection)



#endif
