/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Alias_h__
#define o_phantom_reflection_Alias_h__

/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Alias : public NamedElement
{
    o_language_element;

public:
    o_declare_meta_type(Alias);

public:
    Alias(modifiers_t a_Modifiers = 0);
    Alias(const string& a_strName, modifiers_t a_Modifiers = 0);
    Alias(NamedElement* a_pNamedElement, const string& a_strName = "", modifiers_t a_Modifiers = 0);

    virtual Alias* asAlias() const { return (Alias*)this; }

    NamedElement* getAliasedElement() const { return m_pElement; }

    void setAliasedElement(NamedElement* a_pElement) 
    { 
        o_assert(m_pElement == nullptr)
        m_pElement = a_pElement; 
    }

    void addAlias(Alias* a_pAlias) 
    {
        if(m_pAliases == nullptr) m_pAliases = new vector<Alias*>;
        m_pAliases->push_back(a_pAlias);
        addElement(a_pAlias);
    }

    Alias* getAlias(const string& a_strName) const;

protected:
    virtual void referencedElementRemoved(LanguageElement* a_pElement);

protected:
    NamedElement* m_pElement;
    vector<Alias*>* m_pAliases;
};

o_namespace_end(phantom, reflection)



#endif
