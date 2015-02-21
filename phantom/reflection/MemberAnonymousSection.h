/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_MemberAnonymousSection_h__
#define o_phantom_reflection_MemberAnonymousSection_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export MemberAnonymousSection : public NamedElement
{
    o_declare_meta_type(MemberAnonymousSection);

public:
    MemberAnonymousSection(modifiers_t modifiers = 0);

    virtual MemberAnonymousSection* asMemberAnonymousSection() const { return (MemberAnonymousSection*)this; }

    void addDataMember( DataMember* a_pDataMember );

    LanguageElement* getDataMember(size_t a_uiIndex) const { return m_DataMembers[a_uiIndex]; }

    size_t getDataMemberCount() const { return m_DataMembers.size(); }

    vector<DataMember*>::const_iterator beginDataMembers() const { return m_DataMembers.begin(); }

    vector<DataMember*>::const_iterator endDataMembers() const { return m_DataMembers.end(); }

    ClassType* getRootOwner() const { return getOwnerSection() ? getOwnerSection()->getRootOwner() : m_pOwner ? m_pOwner->asClassType() : nullptr; }

    MemberAnonymousSection* getOwnerSection() const { return m_pOwner ? m_pOwner->asMemberAnonymousSection() : nullptr; }

    MemberAnonymousSection* getRootSection() const { return getOwnerSection() ? getOwnerSection()->getRootSection() : (MemberAnonymousSection*)this; }

    ClassType* getClassType() const { return m_pOwner ? m_pOwner->asClassType() : nullptr; }

    void                addMemberAnonymousSection(MemberAnonymousSection* a_pMemberAnonymousSection)
    {
        o_assert(std::find(m_MemberAnonymousSections.begin(), m_MemberAnonymousSections.end(), a_pMemberAnonymousSection) == m_MemberAnonymousSections.end());
        m_MemberAnonymousSections.push_back(a_pMemberAnonymousSection);
        addElement(a_pMemberAnonymousSection);
    }
    void                removeMemberAnonymousSection( MemberAnonymousSection* a_pMemberAnonymousSection )
    {
        m_MemberAnonymousSections.erase(std::find(m_MemberAnonymousSections.begin(), m_MemberAnonymousSections.end(), a_pMemberAnonymousSection));
        removeElement(a_pMemberAnonymousSection);
    }
    MemberAnonymousSection*   getMemberAnonymousSection(size_t a_uiIndex) const {return m_MemberAnonymousSections[a_uiIndex]; }
    size_t              getMemberAnonymousSectionCount() const { return m_MemberAnonymousSections.size(); }

protected:
    void referencedElementRemoved(LanguageElement* a_pElement);

protected:
    vector<DataMember*> m_DataMembers;
    vector<MemberAnonymousSection*> m_MemberAnonymousSections;

};

o_namespace_end(phantom, reflection)



#endif
