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

#ifndef o_phantom_reflection_TemplateSignature_h__
#define o_phantom_reflection_TemplateSignature_h__



/* ****************** Includes ******************* */


/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), TemplateSignature);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export TemplateSignature : public LanguageElement
{
    o_language_element;

public:
    TemplateSignature(size_t a_uiParameterCount);
    TemplateSignature(const string& a_strTemplateSignatureTypes, const string& a_strTemplateSignatureParams);
    o_destructor ~TemplateSignature();

    vector<TemplateParameter*>::const_iterator beginParameters() const { return m_Parameters.begin(); }
    vector<TemplateParameter*>::const_iterator endParameters() const { return m_Parameters.end(); }

    virtual TemplateSignature* asTemplateSignature() const { return const_cast<TemplateSignature*>(this); }

    size_t              getParameterCount() const { return m_Parameters.size(); }
    size_t              getParameterIndex(const string& a_strName) const;
    size_t              getParameterIndex(TemplateParameter* a_pParameter) const;

    void                setDefaultArgument(const string& a_strParameterName, LanguageElement* a_pElement);
    LanguageElement*    getDefaultArgument(const string& a_strParameterName) const;

    size_t              getDefaultArgumentCount() const;

    void                addParameter(TemplateParameter* a_pTemplateSignatureParameter);
    void                addParameterAliasName(size_t a_uiIndex, const string& a_strAlias);

    const vector<LanguageElement*>& getPlaceholders() const { return m_Placeholders; }

protected:
    vector<TemplateParameter*> m_Parameters;
    vector<LanguageElement*> m_Placeholders;
    map<string, size_t>        m_ParameterAliasNames;
};

o_namespace_end(phantom, reflection)



#endif
