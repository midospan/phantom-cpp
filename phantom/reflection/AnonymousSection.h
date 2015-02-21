/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_AnonymousSection_h__
#define o_phantom_reflection_AnonymousSection_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export AnonymousSection : public NamedElement
{
    o_declare_meta_type(AnonymousSection);

public:
    AnonymousSection(modifiers_t modifiers = 0);

    virtual AnonymousSection* asAnonymousSection() const { return (AnonymousSection*)this; }

    void addVariable( Variable* a_pVariable );

    LanguageElement* getVariable(size_t a_uiIndex) const { return m_Variables[a_uiIndex]; }

    size_t getVariableCount() const { return m_Variables.size(); }

    vector<Variable*>::const_iterator beginVariables() const { return m_Variables.begin(); }

    vector<Variable*>::const_iterator endVariables() const { return m_Variables.end(); }

    ClassType* getRootOwner() const { return getOwnerSection() ? getOwnerSection()->getRootOwner() : m_pOwner ? m_pOwner->asClassType() : nullptr; }

    AnonymousSection* getOwnerSection() const { return m_pOwner ? m_pOwner->asAnonymousSection() : nullptr; }

    AnonymousSection* getRootSection() const { return getOwnerSection() ? getOwnerSection()->getRootSection() : (AnonymousSection*)this; }

    void                addAnonymousSection(AnonymousSection* a_pAnonymousSection)
    {
        o_assert(std::find(m_AnonymousSections.begin(), m_AnonymousSections.end(), a_pAnonymousSection) == m_AnonymousSections.end());
        m_AnonymousSections.push_back(a_pAnonymousSection);
        addElement(a_pAnonymousSection);
    }
    void                removeAnonymousSection( AnonymousSection* a_pAnonymousSection )
    {
        m_AnonymousSections.erase(std::find(m_AnonymousSections.begin(), m_AnonymousSections.end(), a_pAnonymousSection));
        removeElement(a_pAnonymousSection);
    }
    AnonymousSection*   getAnonymousSection(size_t a_uiIndex) const {return m_AnonymousSections[a_uiIndex]; }
    size_t              getAnonymousSectionCount() const { return m_AnonymousSections.size(); }

protected:
    void referencedElementRemoved(LanguageElement* a_pElement);

protected:
    vector<Variable*> m_Variables;
    vector<AnonymousSection*> m_AnonymousSections;

};

o_namespace_end(phantom, reflection)



#endif
