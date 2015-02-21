/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_TemplateSignature_h__
#define o_phantom_reflection_TemplateSignature_h__



/* ****************** Includes ******************* */


/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), TemplateSignature);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export TemplateSignature : public NamedElement
{
    o_language_element;

    o_declare_meta_type(TemplateSignature);

public:
    TemplateSignature();
    TemplateSignature(size_t a_uiParameterCount);
    TemplateSignature(const vector<TemplateParameter*>& a_Parameters);
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
    LanguageElement*    getDefaultArgument(size_t i) const;

    size_t              getDefaultArgumentCount() const;

    void                addParameter(TemplateParameter* a_pTemplateSignatureParameter);
    void                addParameterAliasName(size_t a_uiIndex, const string& a_strAlias);

    const vector<LanguageElement*>& getPlaceholders() const { return m_Placeholders; }

    TemplateParameter*  getParameter(size_t i) const {return m_Parameters[i]; }

    TemplateParameter*  getParameter(const string& a_strName) const 
    {
        size_t i = getParameterIndex(a_strName);
        return (i == ~size_t(0)) ? nullptr : m_Parameters[i];
    }

    bool                acceptsArguments(const vector<LanguageElement*>& a_Arguments) const;

    virtual bool        equals(LanguageElement* a_pLanguageElement) const 
    {
        TemplateSignature* pTS = a_pLanguageElement->asTemplateSignature();
        return pTS AND equals(pTS);
    }

    bool                equals(TemplateSignature* a_pOther) const;

protected:
    vector<TemplateParameter*>  m_Parameters;
    vector<LanguageElement*>    m_Placeholders;
    map<string, size_t>         m_ParameterAliasNames;
};

o_namespace_end(phantom, reflection)



#endif
