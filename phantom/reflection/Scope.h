/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Scope_h__
#define o_phantom_reflection_Scope_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */


o_namespace_begin(phantom, reflection)

class o_export Scope 
{
protected:
    Scope(LanguageElement* a_pThisElement);

public:
    virtual Scope*      asScope() const = 0;

    virtual void        addScopeElement(NamedElement* a_pElement) = 0;
    virtual void        removeScopeElement(NamedElement* a_pElement) = 0;

    o_forceinline LanguageElement* asLanguageElement() const { return m_pThisElement; }

    o_forceinline NamedElement* asNamedElement() const { return m_pThisElement->asNamedElement(); }

    virtual Scope*      getNamedScope() const { return (Scope*)this; }

    void                addType(Type* a_pType);
    void                replaceType(Type* a_pOldType, Type* a_pNewType);
    void                removeType(Type* a_pType);
    
    Type*               getType( size_t index ) const {return m_pTypes ? (*m_pTypes)[index] : nullptr; }
    Type*               getType( const string& a_strName ) const;
    size_t              getTypeCount() const {return m_pTypes ? m_pTypes->size() : 0; }
    PrimitiveType*      getPrimitiveType( const string& a_strName ) const;
    Type*               getTypeByGuid( uint a_uiGuid ) const;

    Class*              getClass(const string& a_strName) const;
    Class*              getClass(size_t index) const;
    size_t              getClassCount() const;

    void                addTemplate(Template* a_pTemplate);
    void                removeTemplate( Template* a_pTemplate );
    Template*           getTemplate( const string& a_strName ) const ;
    Template*           getTemplate( size_t a_uiIndex ) const ;
    size_t              getTemplateCount() const {return m_pTemplates ? m_pTemplates->size() : 0; }

    void                addTemplateSpecialization(TemplateSpecialization* a_pTemplateSpecialization);
    void                removeTemplateSpecialization( TemplateSpecialization* a_pTemplateSpecialization );
    TemplateSpecialization* getTemplateSpecialization( size_t a_uiIndex ) const ;
    size_t              getTemplateSpecializationCount() const {return m_pTemplateSpecializations ? m_pTemplateSpecializations->size() : 0; }

    void                addVariable(Variable* a_pVariable);
    void                removeVariable(Variable* a_pVariable);
    Variable*           getVariable( size_t a_uiIndex ) const;
    size_t              getVariableCount() const;
    Variable*           getVariable( const string& a_strName ) const;

    Alias*              addAlias( NamedElement* a_pElement, const string& a_strAlias, modifiers_t a_Modifiers = 0 );
    void                addAlias( Alias* a_pAlias );
    void                addUsing( NamedElement* a_pElement );
    void                removeAlias( Alias* a_pAlias );
    Alias*              getAlias(const string& a_strAlias) const;
    LanguageElement*    getAliased(const string& a_strAlias) const;
    Alias*              getAlias(size_t a_uiIndex) const;
    size_t              getAliasCount() const;
    Alias*              getTypedef(const string& a_strTypedef) const;

    void                addFunction(Function* a_pFunction);
    void                removeFunction(Function* a_pFunction);
    Function*           getFunction(size_t a_uiIndex) const;
    Function*           getFunction( const string& a_strName, const vector<Type*>& a_Types ) const;
    size_t              getFunctionCount() const;

    virtual Subroutine* getSubroutine(const string& a_strName, const vector<Type*>& a_ParameterTypes, modifiers_t a_Modifiers) const;
    Subroutine*         getSubroutine(Type* a_pReturnType, const string& a_strName, const vector<Type*>& a_ParameterTypes, modifiers_t a_Modifiers) const;
    virtual void        addSubroutine(Subroutine* a_pSubroutine);
    virtual bool        acceptsSubroutine(Type* a_pReturnType, const string& a_strName, const vector<Type*>& a_ParameterTypes, modifiers_t a_Modifiers, vector<Subroutine*>* a_pOutConflictingSubroutines = nullptr) const;
    bool                acceptsSubroutine(Subroutine* a_pSubroutine) const;

    vector<Type*>::const_iterator       beginTypes() const;
    vector<Type*>::const_iterator       endTypes() const;
    vector<Template*>::const_iterator   beginTemplates() const;
    vector<Template*>::const_iterator   endTemplates() const;
    vector<TemplateSpecialization*>::const_iterator   beginTemplateSpecializations() const;
    vector<TemplateSpecialization*>::const_iterator   endTemplateSpecializations() const;
    vector<Function*>::const_iterator   beginFunctions() const ;
    vector<Function*>::const_iterator   endFunctions() const;
    vector<Variable*>::const_iterator   beginVariables() const;
    vector<Variable*>::const_iterator   endVariables() const;
    vector<Alias*>::const_iterator    beginAliases() const;
    vector<Alias*>::const_iterator    endAliases() const;

    virtual void getElementDoubles(NamedElement* a_pElement, vector<NamedElement*>& out) const;

protected:
    void                scopedElementRemoved(LanguageElement* a_pElement);
    void                release(vector<Type*>& out_types);
    void                finalize();

protected:
    o_signal_data(typeAdded, Type*)
    o_signal_data(typeRemoved, Type*)
    o_signal_data(aliasAdded, Alias*)
    o_signal_data(aliasRemoved, Alias*)
    o_signal_data(templateAdded, Template*)
    o_signal_data(templateRemoved, Template*)
    o_signal_data(templateSpecializationAdded, TemplateSpecialization*)
    o_signal_data(templateSpecializationRemoved, TemplateSpecialization*)
    o_signal_data(functionAdded, Function*)
    o_signal_data(functionRemoved, Function*)
    o_signal_data(variableAdded, Variable*)
    o_signal_data(variableRemoved, Variable*)

protected:
    LanguageElement*                    m_pThisElement;
    vector<Function*>*                  m_pFunctions;
    vector<Variable*>*                  m_pVariables;
    vector<Type*>*                      m_pTypes;
    vector<Template*>*                  m_pTemplates;
    vector<TemplateSpecialization*>*    m_pTemplateSpecializations;
    vector<Alias*>*                     m_pAliases;
};

o_namespace_end(phantom, reflection)



#endif
