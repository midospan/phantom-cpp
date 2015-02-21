/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_NamedElement_h__
#define o_phantom_reflection_NamedElement_h__




/* ****************** Includes ******************* */
#include <phantom/reflection/LanguageElement.h>
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export NamedElement : public LanguageElement
{
    o_language_element;

    friend class phantom::reflection::ClassType;
    friend class phantom::reflection::Class;
    friend class phantom::reflection::Scope;
    friend class phantom::reflection::TemplateSpecialization;
    friend class phantom::reflection::Module;
    friend class phantom::reflection::Application;
    friend class phantom::reflection::Source;
    friend class phantom::reflection::Namespace;

public:
    NamedElement(modifiers_t a_Modifiers = 0);
protected:
    NamedElement(const string& a_strName, modifiers_t a_Modifiers = 0);

public:
    ~NamedElement();

    o_terminate();

public:
    virtual NamedElement*               asNamedElement() const { return (NamedElement*)this; }

    void                                setModifiers(modifiers_t a_Flags);
    o_forceinline modifiers_t           getModifiers() const { return m_Modifiers; }
    o_forceinline boolean               testModifiers(modifiers_t a_uiModifiers) const { return ((m_Modifiers & a_uiModifiers) == a_uiModifiers); }

    o_forceinline void                  setShared() { m_Modifiers |= o_shared; }
    o_forceinline boolean               isShared() const { return ((m_Modifiers & o_shared) == o_shared); }

    o_forceinline const string&         getName() const { return m_strName; }
    virtual string                      getQualifiedName() const;
    virtual string                      getDecoratedName() const;
    virtual string                      getQualifiedDecoratedName() const;

    bool                                hasElementWithName(const string& a_strName) const;

	o_forceinline size_t				getGuid() const { return m_uiGuid; }

    modifiers_t                         getAccess() const { return m_Modifiers & (o_public_access|o_protected_access|o_private_access); }
    
    virtual void                        setTemplateDependant();
    bool                                isPureDeclaration() const { return !testModifiers(o_finalized) AND !testModifiers(o_defined); }
    bool                                isDefined() const { return testModifiers(o_defined); }
    bool                                isFinalized() const { return testModifiers(o_finalized); }
    void                                setDefined() { if(isDefined()) return; m_Modifiers |= o_defined; if(m_pOwner) m_pOwner->elementDefined(this); }
    void                                setFinalized() { if(isFinalized()) return; o_assert(isDefined()); m_Modifiers |= o_finalized; finalize(); }
    virtual bool                        isPOD() const { return false; }
    virtual bool                        isAlwaysValid() const { return (m_Modifiers & o_always_valid) == o_always_valid; }
    virtual bool                        isTemplateInstance() const { return false; }
    virtual bool                        isTemplateDependant() const { return ((m_Modifiers & o_template_dependant) == o_template_dependant) OR LanguageElement::isTemplateDependant(); }
    o_forceinline bool                  isStatic() const  { return ((m_Modifiers & o_static) == o_static); }
    o_forceinline bool                  isProtected() const { return ((m_Modifiers & o_protected_access) == o_protected_access) ; }
    o_forceinline bool                  isPrivate() const { return (m_Modifiers & o_private_access) == o_private_access; }
    o_forceinline bool                  isPublic() const { return ((m_Modifiers & (o_protected_access|o_private_access)) == 0); }
    o_forceinline bool                  isOwner() const { return ((m_Modifiers & o_owner) == o_owner) ; }
    o_forceinline bool                  isAbstract() const { return ((m_Modifiers & o_abstract) == o_abstract); }
    o_forceinline bool                  isVirtual() const { return ((m_Modifiers & o_virtual) == o_virtual); }
    o_forceinline bool                  isConst() const { return ((m_Modifiers & o_const) == o_const); }
    o_forceinline bool                  isMutable() const { return ((m_Modifiers & o_mutable) == o_mutable); }
    o_forceinline bool                  isImportable() const { return ((m_Modifiers & o_importable) == o_importable); }

    virtual bool                        hasPublicMember(NamedElement* a_pNamedElement) const;
    virtual bool                        hasProtectedMember(NamedElement* a_pNamedElement) const;
    virtual bool                        hasPrivateMember(NamedElement* a_pNamedElement) const;

    virtual boolean                     isNative() const;

    void                                setMetaDataValue(size_t index, const string& value);
    const string&                       getMetaDataValue(size_t index) const;
    void                                teardownMetaDataCascade(size_t count);

    virtual string                      getUniqueName() const;
    virtual string                      getUniqueDecoratedName() const;
    void                                getDoubles(vector<NamedElement*>& out) const;
    virtual bool                        equals(LanguageElement* a_pOther) const;
    bool                                equals(NamedElement* a_pOther) const;
    virtual Scope*                      getNamingScope() const;
    Namespace*                          getNamespace() const;

    void                                dumpElementList(ostream& out) const;
    void                                dumpElementListCascade(ostream& out) const;

protected:
    void setGuid(uint a_uiGuid);
    void setName(const string& a_strName) { m_strName = a_strName; }
    o_forceinline void setImportable( bool a_bValue ) { if(a_bValue) m_Modifiers |= o_importable; else m_Modifiers &= ~o_importable; }
    virtual void                        finalize() {}

protected:
    void setupMetaData(size_t count);

protected:
    string                      m_strName;
    Namespace*                  m_pNamespace;   /// Namespace represents the abstract, qualifying container of the element, for example a global function is scoped inside the global namespace
    modifiers_t                 m_Modifiers;
    uint                        m_uiGuid;
    mutable string*             m_pMetaData;
};

class persistent_element;
class persistent_element
{
    friend class phantom::reflection::Application;

public:
    NamedElement* element() const { return m_pElement; }
    persistent_element();
    persistent_element(const persistent_element& a_Other);
    ~persistent_element();
    persistent_element& operator=(NamedElement* a_pElement) 
    {
        m_pElement = a_pElement;
        return *this;
    }
    persistent_element& operator=(const persistent_element& a_Other);
    bool operator==(const persistent_element& a_Other) const { return m_pElement->equals(a_Other.m_pElement); }
    bool operator!=(const persistent_element& a_Other) const { return !m_pElement->equals(a_Other.m_pElement); }
    bool operator<(const persistent_element& a_Other) const { return m_pElement < a_Other.m_pElement; }

    NamedElement* operator->() const { return m_pElement; }

    bool isSingle() const 
    {
        if(m_pElement == nullptr) return false;
        vector<NamedElement*> doubles;
        m_pElement->getDoubles(doubles);
        return doubles.empty(); /// no doubles => single 
    }

    void moduleAboutToBeDestroyed() 
    {
        vector<NamedElement*> doubles;
        m_pElement->getDoubles(doubles);
        if(doubles.size())
        {
            o_assert(doubles.front()->getModule() != m_pElement->getModule());
            /// Element has a double somewhere in another module => replace current by the double
            m_pElement = doubles.front();
        }
        else m_pElement = nullptr;
    }
    NamedElement* m_pElement;
};

template<typename t_NamedElement>
class persistent : protected persistent_element
{
    static char asserter(...);
    static int asserter(NamedElement* a_pElement);
    friend class PersistentConnector;

public:
    persistent()
    {
        o_static_assert_msg(sizeof(asserter((t_NamedElement*)nullptr)) == sizeof(int), "t_NamedElement must derive from NamedElement");
    }
    persistent(const persistent<t_NamedElement>& a_Other) : persistent_element(a_Other) 
    { 
    }
    ~persistent()
    {
    }
    persistent<t_NamedElement>& operator=(t_NamedElement* a_pElement)
    {
        return (persistent<t_NamedElement>&)persistent_element::operator=(a_pElement);
    }
    persistent<t_NamedElement>& operator=(const persistent<t_NamedElement>& a_Other)
    {
        return (persistent<t_NamedElement>&)persistent_element::operator=((const persistent_element&)a_Other);
    }

    t_NamedElement* operator->() const { return static_cast<t_NamedElement*>(m_pElement); }
    bool operator==(const persistent<t_NamedElement>& a_Other) const { return m_pElement ? m_pElement->equals(a_Other.m_pElement) : (a_Other.m_pElement == nullptr); }
    bool operator!=(const persistent<t_NamedElement>& a_Other) const { return !operator==(a_Other); }
    bool operator<(const persistent<t_NamedElement>& a_Other) const { return m_pElement < a_Other.m_pElement; }

    t_NamedElement* element() const { return static_cast<t_NamedElement*>(m_pElement); }

};

o_namespace_end(phantom, reflection)

//#include "NamedElement.hxx"

#endif
