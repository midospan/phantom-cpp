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

#ifndef o_phantom_reflection_Template_h__
#define o_phantom_reflection_Template_h__



/* ****************** Includes ******************* */


/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Template);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Template : public LanguageElement
{
    o_language_element;

    friend class Namespace;
    friend class TemplateSpecialization;

public:
    Template(const string& a_strName, TemplateSignature* a_pSignature, modifiers_t a_Modifiers = 0);
    Template(const string& a_strName, const string& a_strTemplateTypes, const string& a_strTemplateParam, modifiers_t a_Modifiers = 0);
    o_destructor ~Template();

    Namespace* getNamespace() const { return m_pOwner ? m_pOwner->asNamespace() : nullptr; }

    vector<TemplateSpecialization*>::const_iterator beginSpecializations() const { return m_Specializations.begin(); }
    vector<TemplateSpecialization*>::const_iterator endSpecializations() const { return m_Specializations.end(); }

    vector<TemplateParameter*>::const_iterator beginTemplateParameters() const;
    vector<TemplateParameter*>::const_iterator endTemplateParameters() const;

    void parseParameters(const string& a_strTemplateTypes, const string& a_strTemplateParams);

    virtual Template* asTemplate() const { return const_cast<Template*>(this); }

    size_t              getTemplateParameterCount() const;
    size_t              getTemplateParameterIndex(const string& a_strName) const;
    size_t              getTemplateParameterIndex(TemplateParameter* a_pTemplateParameter) const;

    void                setDefaultArgument(const string& a_strParameterName, LanguageElement* a_pElement);
    LanguageElement*    getDefaultArgument(const string& a_strParameterName) const;
    LanguageElement*    getDefaultArgument(size_t i) const;

    size_t              getDefaultArgumentCount() const;

    void                addTemplateParameter(TemplateParameter* a_pTemplateParameter);

    TemplateSignature*  getTemplateSignature() const { return m_pTemplateSignature; }

    TemplateSpecialization* createSpecialization(const vector<LanguageElement*>& arguments, TemplateSignature* a_pTemplateSignature = nullptr);
    
    void                addTemplateParameterAliasName(size_t a_uiIndex, const string& a_strAlias);

    ClassType*          instanciate(const vector<LanguageElement*>& arguments);

protected:
    void                createEmptySpecialization();
    virtual bool canBeDestroyed() const { return m_Specializations.empty(); }

protected:
    void registerSpecialization(TemplateSpecialization* a_pTemplateSpecialization);
    
protected:
    TemplateSignature*              m_pTemplateSignature;
    vector<TemplateSpecialization*> m_Specializations;
};

o_namespace_end(phantom, reflection)



#endif
