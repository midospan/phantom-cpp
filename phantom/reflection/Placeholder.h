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
    Placeholder(TemplateParameter* a_pTemplateParameter)
         { m_TemplateParameters.push_back(a_pTemplateParameter); }
    Placeholder(const vector<TemplateParameter*>& a_TemplateParameters)
        : m_TemplateParameters(a_TemplateParameters) {}

    virtual LanguageElement*    asLanguageElement() const = 0;

    virtual Placeholder*    asPlaceholder() const = 0;

    virtual PlaceholderType*    asPlaceholderType() const { return nullptr; }

    virtual PlaceholderConstant*    asPlaceholderConstant() const { return nullptr; }

    virtual PlaceholderClass*    asPlaceholderClass() const { return nullptr; }

    virtual PlaceholderInstanceDataMember*    asPlaceholderInstanceDataMember() const { return nullptr; }

    virtual PlaceholderSubroutine*    asPlaceholderSubroutine() const { return nullptr; }

protected:
    vector<TemplateParameter*> m_TemplateParameters;
};

class o_export PlaceholderType : public Type, public Placeholder
{
    o_type;

    o_declare_meta_type(PlaceholderType);

public:
    PlaceholderType(const string& a_strName, TemplateParameter* a_pParameterDependency, modifiers_t a_Modifiers = 0)
        : Type(e_placeholder, a_strName, 0, 0, a_Modifiers|o_placeholder) 
    {
        addTemplateParameterDependency(a_pParameterDependency);
    }

    virtual LanguageElement*    asLanguageElement() const { return (PlaceholderType*)this; }
    virtual Placeholder*        asPlaceholder() const { return (PlaceholderType*)this; }
    virtual PlaceholderType*    asPlaceholderType() const { return (PlaceholderType*)this; }

    TemplateParameter* getTemplateParameterDependency() const { return m_pTemplateParameterDependencies ? m_pTemplateParameterDependencies->front() : nullptr; }

    virtual bool templatePartialMatch(Type* a_pType, size_t& a_Score, map<TemplateParameter*, LanguageElement*>& a_Deductions ) const;
};

class o_export PlaceholderArrayType : public ArrayType, public Placeholder
{
    o_type;

    o_declare_meta_type(PlaceholderArrayType);

public:
    PlaceholderArrayType(Type* a_pType, PlaceholderConstantExpression* a_pSize)
        : ArrayType(a_pType, a_Modifiers|o_placeholder) 
        , m_pPlaceholderConstant(a_pSize)
    {
    }

    virtual LanguageElement*        asLanguageElement() const { return (PlaceholderArrayType*)this; }
    virtual Placeholder*            asPlaceholder() const { return (PlaceholderArrayType*)this; }
    virtual PlaceholderArrayType*   asPlaceholderArrayType() const { return (PlaceholderArrayType*)this; }
    PlaceholderConstant*            getPlaceholderConstant() const { return m_pPlaceholderConstant; }
    TemplateParameter*              getTemplateParameterDependency() const { return m_pTemplateParameterDependencies ? m_pTemplateParameterDependencies->front() : nullptr; }

    virtual bool templatePartialMatch(Type* a_pType, size_t& a_Score, map<TemplateParameter*, LanguageElement*>& a_Deductions ) const;

protected:
    PlaceholderConstant* m_pPlaceholderConstant;
};

class o_export PlaceholderTemplate : public Type, public Placeholder
{
    o_type;

    o_declare_meta_type(PlaceholderTemplate);

public:
    PlaceholderTemplate(Template* a_pTemplate, const vector<LanguageElement*>& a_Arguments)
        : Type(a_pTemplate->getName(), a_Modifiers|o_placeholder) 
        , m_Arguments(a_Arguments)
    {
    }

    virtual LanguageElement*    asLanguageElement() const { return (PlaceholderTemplate*)this; }
    virtual Placeholder*        asPlaceholder() const { return (PlaceholderTemplate*)this; }
    virtual PlaceholderTemplate* asPlaceholderTemplate() const { return (PlaceholderTemplate*)this; }

    virtual bool templatePartialMatch(Type* a_pType, size_t& a_Score, map<TemplateParameter*, LanguageElement*>& a_Deductions ) const;

protected:
    PlaceholderConstant* m_pPlaceholderConstant;
};

class o_export PlaceholderClass : public Class, public Placeholder
{
    o_type;

    o_declare_meta_type(PlaceholderClass);

public:
    PlaceholderClass(PlaceholderType* a_pPlaceholderType)
        : Class(a_pPlaceholderType->getName(), 0, 0, a_pPlaceholderType->getModifiers()|o_placeholder) 
    {
        addTemplateParameterDependency(a_pPlaceholderType->getTemplateParameterDependency());
    }

    virtual LanguageElement*    asLanguageElement() const { return (PlaceholderClass*)this; }
    virtual Placeholder*        asPlaceholder() const { return (PlaceholderClass*)this; }
    virtual PlaceholderClass*   asPlaceholderClass() const { return (PlaceholderClass*)this; }

    virtual bool templatePartialMatch(Type* a_pType, size_t& a_Score, map<TemplateParameter*, LanguageElement*>& a_Deductions ) const;

};

class PlaceholderConstantExpression : public ConstantExpression, public Placeholder
{
    o_language_element;

    o_declare_meta_type(PlaceholderConstantExpression);

public:
    PlaceholderConstantExpression(Type* a_pType, const string& a_strName, TemplateParameter* a_pTemplateParameter, modifiers_t modifiers = 0)
        : ConstantExpression(a_strName, modifiers|o_placeholder)
        , m_pType(a_pType)
    {
        addTemplateParameterDependency(a_pTemplateParameter);
    }
    virtual LanguageElement*        asLanguageElement() const { return (PlaceholderConstantExpression*)this; }
    virtual Placeholder*            asPlaceholder() const { return (PlaceholderConstantExpression*)this; }
    virtual PlaceholderConstantExpression*    asPlaceholderConstantExpression() const { return (PlaceholderConstantExpression*)this; }
    virtual void                    getValue(void* dest) const { o_exception_no_implementation(); }
    virtual Type*                   getValueType() const { return m_pType; }
    virtual bool                    hasValue(void* a_pSrc) const { o_exception_no_implementation(); return false; }
    virtual Constant*               clone() const;
    virtual bool                    isZero() const { o_exception_no_implementation(); return false; }
    virtual void                    toString(string& out) const { o_exception_no_implementation(); }
    virtual void                    toLiteral(string& out) const { o_exception_no_implementation(); }

protected:
    Type* m_pType;
};

class PlaceholderInstanceDataMember : public InstanceDataMember, public Placeholder
{
    o_language_element;

    o_declare_meta_type(PlaceholderInstanceDataMember);

    PlaceholderInstanceDataMember(const string& a_strName, uint a_uiSerializationMask = o_save_data, modifiers_t modifiers = 0)
        : InstanceDataMember(nullptr, a_strName, nullptr, a_uiSerializationMask, modifiers|o_placeholder)
    {

    }
    virtual LanguageElement*                asLanguageElement() const { return (PlaceholderInstanceDataMember*)this; }
    virtual Placeholder*                    asPlaceholder() const { return (PlaceholderInstanceDataMember*)this; }    
    virtual PlaceholderInstanceDataMember*  asPlaceholderInstanceDataMember() const { return (PlaceholderInstanceDataMember*)this; }
};

class PlaceholderSubroutine : public Subroutine, public Placeholder
{
    o_language_element;

    o_declare_meta_type(PlaceholderSubroutine);

public:
    PlaceholderSubroutine(const string& a_strName, modifiers_t modifiers = 0)
        : Subroutine(a_strName, nullptr, e_placeholdercall, modifiers|o_placeholder)
    {

    }
    virtual LanguageElement*        asLanguageElement() const { return (PlaceholderSubroutine*)this; }
    virtual Placeholder*            asPlaceholder() const { return (PlaceholderSubroutine*)this; }
    virtual PlaceholderSubroutine*  asPlaceholderSubroutine() const { return (PlaceholderSubroutine*)this; }
};   


o_namespace_end(phantom, reflection)



#endif