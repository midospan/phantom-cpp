/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_NamespaceAlias_h__
#define o_phantom_reflection_NamespaceAlias_h__

/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export NamespaceAlias : public NamedElement
{
    o_language_element;

public:
    static Class* const metaType;

public:
    NamespaceAlias()
        : m_pNamespace(nullptr)
    {

    }
    NamespaceAlias(const string& a_strName, Namespace* a_pNamespace, modifiers_t a_Modifiers = 0);

    virtual NamespaceAlias* asNamespaceAlias() const { return (NamespaceAlias*)this; }

    Namespace* getAliasedNamespace() const {return m_pNamespace; }

protected:
    virtual void referencedElementRemoved(LanguageElement* a_pElement);

protected:
    Namespace* m_pNamespace;
};

o_namespace_end(phantom, reflection)



#endif
