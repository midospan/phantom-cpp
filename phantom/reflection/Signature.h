/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Signature_h__
#define o_phantom_reflection_Signature_h__



/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Signature : public NamedElement
{
    o_language_element;

    o_invalid_decl(Signature);

    friend class Subroutine;

public:
    static Signature* Create( modifiers_t modifiers = 0 );
    static Signature* Create( Type* a_pReturnType, modifiers_t modifiers = 0 );
    static Signature* Create( Type* a_pReturnType, Type* a_pSingleParameterType, modifiers_t modifiers = 0 );
    
    enum EState
    {
        eState_Virgin = 0,
        eState_UnderConstruction,
        eState_Final,
    };

    struct ElementParsingInfo
    {
        ElementParsingInfo()
            : m_pType(NULL)
            , m_uiPointingLevel(0)
        {

        }
        ElementParsingInfo(Type* a_pType)
            : m_pType(a_pType)
            , m_uiPointingLevel(0)
        {

        }
        enum EProperties
        {
            eConst = 0,
            eReference,
        };
        Type*                m_pType;
        uint                m_uiPointingLevel;
        flags<EProperties>    m_Properties;
    };

    typedef phantom::vector<Type*> parameter_type_list;

    Signature( modifiers_t modifiers = 0 );
    Signature( Type* a_pType, modifiers_t modifiers = 0 );
    Signature( Type* a_pReturnType, Type* a_pSingleParameterType, modifiers_t modifiers = 0);
    Signature( Type* a_pType, const vector<Parameter*>& a_Parameters, modifiers_t modifiers = 0 );
    Signature( Type* a_pType, const vector<Type*>& a_Types, modifiers_t modifiers = 0 );
    o_destructor ~Signature(void);

    virtual Signature* asSignature() const { return (Signature*)this; }

    virtual bool        equals(LanguageElement* a_pOther) const;

    bool                equals(Signature* a_pOther) const;

    bool                matches(const vector<Type*>& parameterTypes, modifiers_t a_Modifiers) const;

    bool                matches(const vector<Expression*>& arguments, modifiers_t a_Modifiers) const;

    bool                matches(Signature* a_pOther) const { return matches(a_pOther->getParameterTypes(), a_pOther->getModifiers()); }

    virtual Signature*  clone() const;

    void            parse( const string& a_strSignature, LanguageElement* a_pFutureScope = nullptr );

    size_t          getParameterCount() const;
    size_t          getMinimumNeededParameterCount() const;
    Parameter*      getParameter(size_t i) const { return m_Parameters[i]; }
    void            addParameter(Type* a_pParameterType, const string& a_strName = "", Expression* a_pDefaultValueExpression = nullptr);
    void            addParameter(Parameter* a_pParameter);
    Type*           getParameterType(size_t a_uiParamIndex) const;
    vector<Type*>   getParameterTypes() const;
    const string&   getParameterName(size_t a_uiParamIndex) const;
    Expression*     getParameterDefaultValue(size_t a_uiParamIndex) const;
    void            setReturnType(Type* a_pType);
    void            setParameterName(size_t i, const string& a_strName);
    Type*           getReturnType() const;

    virtual string  getQualifiedName() const;
    virtual string  getDecoratedName() const;
    virtual string  getQualifiedDecoratedName() const;

    size_t          getRequiredArgumentCount() const;

    void            implicitConversions(Language* a_pLanguage, const vector<Type*>& a_ArgumentTypes, LanguageElement* a_pContextScope, conversions& a_ImplicitConversions) const;
    void            implicitConversions(Language* a_pLanguage, const vector<Expression*>& a_Arguments, LanguageElement* a_pContextScope, conversions& a_ImplicitConversions) const;

    void            implicitConversions(const vector<Type*>& a_ArgumentTypes, LanguageElement* a_pContextScope, conversions& a_ImplicitConversions) const;
    void            implicitConversions(const vector<Expression*>& a_Arguments, LanguageElement* a_pContextScope, conversions& a_ImplicitConversions) const;

    bool            hasEllipsis() const;

    vector<Parameter*>::const_iterator beginParameters() const { return m_Parameters.begin(); }
    vector<Parameter*>::const_iterator endParameters() const { return m_Parameters.end(); }

    Subroutine*     getOwnerSubroutine() const { return m_pOwner ? m_pOwner->asSubroutine() : nullptr; }

protected:
    bool separateParameters(const string& a_strText, vector<string>& a_OutParameters);
    bool parseParameterTypeList(const string& a_strText, vector<Type*>& a_OutParameterTypes, vector<string>& a_OutParameterNames, vector<Expression*>& a_OutParameterExps);

    void referencedElementRemoved(LanguageElement* a_pElement);
    void elementRemoved(LanguageElement* a_pElement);

    void setReturnTypeName(string name);

    string getReturnTypeName() const;

    vector<Parameter*> getParameters() const { return m_Parameters; }

    void setParameters(vector<Parameter*> parameters) { m_Parameters = parameters; } 

protected:
    Type*               m_pReturnType;
    vector<Parameter*>  m_Parameters;
    string*             m_pReturnTypeName;
    size_t              m_uiArgumentStorageSize;
};

o_namespace_end(phantom, reflection)



#endif
