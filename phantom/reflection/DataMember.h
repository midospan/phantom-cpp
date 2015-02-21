/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_DataMember_h__
#define o_phantom_reflection_DataMember_h__


/* ****************** Includes ******************* */

/* ************* Class Declarations ************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)


class o_export DataMember : public ValueMember
{
    o_language_element;

    friend class Class;
    friend class ClassType;
    friend class MemberAnonymousSection;

    o_invalid_decl(DataMember);

public:
    static Class* const metaType;

    DataMember();
    DataMember(Type* a_pValueType, const string& a_strName, Range* a_pRange = nullptr, uint a_uiSerializationMask = o_save_data, modifiers_t a_uiModifiers = 0);
    DataMember(Type* a_pValueType, const string& a_strName, size_t a_uiOffset, Range* a_pRange = nullptr, uint a_uiSerializationMask = o_save_data, modifiers_t a_uiModifiers = 0);
    o_destructor ~DataMember()
    {

    }

    Range*                  getRange() const { return ValueMember::getRange(); }
    inline size_t           getOffset() const { return m_uiOffset; }
    virtual void*           getAddress( void const* a_pObject ) const { return (byte*)a_pObject + m_uiOffset; }

    // fast content type access
    Type*                   getValueType() const { return ValueMember::getValueType(); }

    // overloadings
    virtual    void         getValue(void const* a_pObject, void* a_pDest) const 
    {
        m_pValueType->copy(a_pDest, getAddress(a_pObject));
    }

    virtual    void         setValue(void* a_pObject, void const* a_pSrc) const 
    {
        m_pValueType->copy(getAddress(a_pObject), a_pSrc);
    }

    virtual LanguageElement*    asLanguageElement() const  { return const_cast<DataMember*>(this); }
    virtual DataMember*         asDataMember() const { return const_cast<DataMember*>(this); }

    virtual bool                referencesData(const void* a_pInstance, const phantom::data& a_Data) const;

    o_forceinline bool          hasPlacementExtension() const 
    { 
        return NOT(testModifiers(o_no_placement_extension)) 
                AND ((m_pValueType->getTypeId() >= e_array AND m_pValueType->hasPlacementExtension()));
    }

    MemberAnonymousSection*           getMemberAnonymousSection() const { return m_pMemberAnonymousSection; }
    
protected:
    virtual void referencedElementRemoved(LanguageElement* a_pElement);
    void setOffset(size_t a_uiOffset) { m_uiOffset = a_uiOffset; }

protected:
    size_t  m_uiOffset;
    MemberAnonymousSection* m_pMemberAnonymousSection;

};
o_namespace_end(phantom, reflection)



#endif
