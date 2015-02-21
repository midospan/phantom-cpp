/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Template_h__
#define o_phantom_reflection_Template_h__



/* ****************** Includes ******************* */


/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Template);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Template : public NamedElement
{
    o_language_element;

    friend class Namespace;
    friend class TemplateSpecialization;
    friend struct ::phantom::detail::dynamic_initializer_template_registrer;

    o_declare_meta_type(Template);

public:
    Template(modifiers_t a_Modifiers = 0);
    Template(TemplateSignature* a_pSignature, const string& a_strName, modifiers_t a_Modifiers = 0);
    o_destructor ~Template();

    Scope* getScope() const { return m_pOwner ? m_pOwner->asScope() : nullptr; }

    vector<TemplateSpecialization*>::const_iterator beginTemplateSpecializations() const { return m_TemplateSpecializations.begin(); }
    vector<TemplateSpecialization*>::const_iterator endTemplateSpecializations() const { return m_TemplateSpecializations.end(); }

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

    void                setTemplateSignature(TemplateSignature* a_pSignature);

    TemplateSignature*  getTemplateSignature() const { return m_pTemplateSignature; }

    TemplateSpecialization* createTemplateSpecialization(const vector<LanguageElement*>& arguments, ClassType* a_pTemplated = nullptr, TemplateSignature* a_pTemplateSignature = nullptr);
    
    void                addTemplateParameterAliasName(size_t a_uiIndex, const string& a_strAlias);

    TemplateSpecialization* getTemplateSpecialization(const vector<LanguageElement*>& arguments ) const;
    TemplateSpecialization* getTemplateSpecialization( const map<Placeholder*, LanguageElement*>& arguments ) const;

    TemplateSpecialization* getTemplateSpecialization(TemplateSpecialization* a_pTemplateSpecialization ) const;

    void                addSpecialization(TemplateSpecialization* a_pSpecialization);

    TemplateSpecialization* getEmptyTemplateSpecialization() const { return m_TemplateSpecializations[0]; }

    TemplateSpecialization* createEmptyTemplateSpecialization(NamedElement* a_pBody);

    bool acceptsArguments(const vector<LanguageElement*>& a_Arguments) const;

    bool mapArguments(const vector<LanguageElement*>& a_Arguments, map<Placeholder*, LanguageElement*>& a_Out) const;

protected:// native constructor
    Template(const string& a_strTemplateTypes, const string& a_strTemplateParam, const string& a_strName, modifiers_t a_Modifiers = 0);

protected:
    void createEmptyTemplateSpecialization();
    virtual bool canBeDestroyed() const { return m_TemplateSpecializations.empty(); }
    virtual void ancestorChanged(LanguageElement* a_pOwner);

protected:
    TemplateSignature*              m_pTemplateSignature;
    vector<TemplateSpecialization*> m_TemplateSpecializations;
};

o_namespace_end(phantom, reflection)



#endif
