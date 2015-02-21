/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Namespace_h__
#define o_phantom_reflection_Namespace_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */


o_namespace_begin(phantom, reflection)

class o_export Namespace : public NamedElement, public Scope
{
    o_language_element;

public:
    typedef map<string, Type*>  typedef_map;
    typedef map<string, Namespace*> namespace_alias_map;
    typedef vector<Namespace*>  namespace_container;
    typedef vector<Function*>   function_container;
    typedef vector<Variable*> variable_container;
    typedef vector<Type*>       type_container;
    typedef vector<Template*>   template_container;

    friend class phantom::Phantom;
    friend class Type;

    o_invalid_decl(Namespace);

public:
    Namespace(modifiers_t a_Modifiers = 0);
    Namespace(const string& a_strName, modifiers_t a_Modifiers = 0);
    o_destructor ~Namespace(void);

    virtual Scope*      asScope() const { return (Namespace*)this; }
    virtual Namespace*  asNamespace() const { return (Namespace*)this; }

    virtual void        addScopeElement(NamedElement* a_pElement);
    virtual void        removeScopeElement(NamedElement* a_pElement);

    void                addNamespace(Namespace* a_pNamespace);
    void                removeNamespace(Namespace* a_pNamespace);

    Namespace*          getRootNamespace() const;
    Namespace*          getNamespace(const string& a_strName) const;
    Namespace*          getNamespace(size_t i) const { return m_Namespaces[i]; }
    size_t              getNamespaceCount() const { return m_Namespaces.size(); }
    Namespace*          getNamespaceCascade(list<string>* a_HierarchyWords) const;
    Namespace*          getNamespaceCascade(const string& qualifiedName, const char* a_SeparatorList = ":") const;
    o_forceinline
    Namespace*          getParentNamespace() const { return static_cast<Namespace*>(m_pOwner); }
    Namespace*          findOrCreateNamespaceCascade(const string& a_strNamespaceName, const char* separatorPattern = ":");
    Namespace*          findOrCreateNamespaceCascade(list<string>* a_HierarchyWords);


    Alias*              addNamespaceAlias( const string& a_strAlias, Namespace* a_pNamespace );
    void                removeNamespaceAlias( const string& a_strAlias );
    Alias*              getNamespaceAlias(const string& a_strAlias) const;
    Namespace*          getNamespaceAliased(const string& a_strAlias) const;

    vector<Namespace*>::const_iterator beginNamespaces() const { return m_Namespaces.begin(); }
    vector<Namespace*>::const_iterator endNamespaces() const { return m_Namespaces.end(); }
    vector<Alias*>::const_iterator beginNamespaceAliases() const;
    vector<Alias*>::const_iterator endNamespaceAliases() const;

    virtual void        addAnonymousSection(AnonymousSection* a_pAnonymousSection);
    virtual AnonymousSection* addAnonymousSection(const string& a_strCode, modifiers_t a_Modifiers = 0);
    virtual void        removeAnonymousSection( AnonymousSection* a_pAnonymousSection );
    AnonymousSection*   getAnonymousSection(size_t a_uiIndex) const;
    size_t              getAnonymousSectionCount() const;
    vector<AnonymousSection*>::const_iterator beginAnonymousSections() const;
    vector<AnonymousSection*>::const_iterator endAnonymousSections() const;
    vector<AnonymousSection*> getAnonymousSections() const { return m_pAnonymousSections ? *m_pAnonymousSections : vector<AnonymousSection*>(); }
    
    FunctionPointerType*functionPointerType(Type* a_pReturnType, EABI a_eABI, const vector<Type*>& a_ParameterTypes);

    string              asPath(char separator = '/') const;

    virtual void        getElementDoubles(NamedElement* a_pElement, vector<NamedElement*>& out) const override;

    virtual bool        equals(LanguageElement* a_pOther) const { return a_pOther == this; }

protected:
    void                setParentNamespace(Namespace* a_pNamespace) { m_pOwner = a_pNamespace; }
    virtual void        referencedElementRemoved(LanguageElement* a_pElement);
    virtual void        elementRemoved(LanguageElement* a_pElement);
    
protected:
    o_signal_data(namespaceAdded, Namespace*)
    o_signal_data(namespaceRemoved, Namespace*)
    o_signal_data(namespaceAliasAdded, Alias*)
    o_signal_data(namespaceAliasRemoved, Alias*)
    o_signal_data(anonymousSectionAdded, AnonymousSection*)
    o_signal_data(anonymousSectionRemoved, AnonymousSection*)

protected:
    vector<Namespace*>              m_Namespaces;
    vector<Alias*>                  m_NamespaceAliases;
    vector<AnonymousSection*>*      m_pAnonymousSections;
    vector<FunctionPointerType*>*   m_pFunctionPointerTypes;

private:
    void release(vector<Type*>& out_types);
};

o_namespace_end(phantom, reflection)



#endif
