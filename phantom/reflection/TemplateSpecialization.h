/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_TemplateSpecialization_h__
#define o_phantom_reflection_TemplateSpecialization_h__



/* ****************** Includes ******************* */


/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export TemplateSpecialization : public NamedElement
{
    o_language_element;

    friend class LanguageElement;
    friend class Template;

    o_declare_meta_type(TemplateSpecialization);

public:
    TemplateSpecialization(Template* a_pTemplate, TemplateSignature* a_pSignature, const vector<LanguageElement*>& arguments);
    TemplateSpecialization(Template* a_pTemplate, TemplateSignature* a_pSignature, const vector<LanguageElement*>& arguments, NamedElement* a_pBody);

    o_destructor ~TemplateSpecialization();

    virtual TemplateSpecialization* asTemplateSpecialization() const { return (TemplateSpecialization*)this; }

    virtual TemplateSpecialization* getAscendantTemplateSpecialization() const { return const_cast<TemplateSpecialization*>(this); }

    uint                getArgumentCount() const { return m_Arguments.size(); }
    Type*               getType(const string& a_strTypenameVariableName) const;
    LanguageElement*    getArgument(const string& a_strTypenameVariableName) const;
    LanguageElement*    getArgument(size_t i) const { return m_Arguments[i]; }
    size_t              getArgumentIndex(const string& a_strTemplateTypeName) const;
    LanguageElement*    getDefaultArgument(size_t i) const { return m_pDefaultArguments ? (*m_pDefaultArguments)[i] : nullptr; }
    LanguageElement*    getDefaultArgument(const string& a_strTemplateTypeName) const;
    const vector<LanguageElement*>& getArguments() const { return m_Arguments; }

    vector<LanguageElement*>::const_iterator beginArguments() const { return m_Arguments.begin(); }
    vector<LanguageElement*>::const_iterator endArguments() const { return m_Arguments.end(); }

    void                setArgument(size_t a_uiIndex, LanguageElement* a_pElement);
    void                setDefaultArgument( size_t i, LanguageElement* a_pElement );
    void                setDefaultArgument( const string& a_strParameterName, LanguageElement* a_pElement );
    void                removeArgument(LanguageElement* a_pElement);

    string              getDecoration() const;
    string              getQualifiedDecoratedName() const;
    string              getDecoratedName() const;
    string              getQualifiedName() const;
  
    Template*           getTemplate() const { return m_pTemplate; }
    TemplateSignature*  getTemplateSignature() const { return m_pTemplateSignature; }

    virtual void        checkCompleteness() const;
    virtual bool        canBeDestroyed() const;

    bool                isEmpty() const;

    bool                isPartial() const;

    bool                isFull() const;
    
    LanguageElement*    getSpecializedElement() const { return m_pOwner; }

    bool                isSpecializingParameter(TemplateParameter* a_pParameter) const;

    bool                matches(const vector<LanguageElement*>& a_TemplateSpecialization) const;
    bool                equals(TemplateSpecialization* a_pTemplateSpecialization) const;
    bool                partialAccepts( const vector<LanguageElement*>& a_Arguments, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_Deductions ) const;

    void                setBody(NamedElement* a_pBody);
    NamedElement*       getBody() const { return m_pBody; }

    void                finalize();

protected:
    void                _updateName();
    void                referencedElementAdded(LanguageElement* a_pElement);
    void                referencedElementRemoved(LanguageElement* a_pElement);
    void                elementRemoved(LanguageElement* a_pElement);

protected:
    typedef phantom::map<string, LanguageElement*>  template_element_map;
    typedef phantom::map<string, size_t>            template_element_index_map;
    Template*                   m_pTemplate;
    TemplateSignature*          m_pTemplateSignature;
    vector<LanguageElement*>    m_Arguments;
    NamedElement*               m_pBody;
    vector<LanguageElement*>*   m_pDefaultArguments;

};

o_namespace_end(phantom, reflection)



#endif
