/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Property_h__
#define o_phantom_reflection_Property_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

struct property_compilation_data
{
    property_compilation_data() : m_pSetClosure(nullptr), m_pGetClosure(nullptr) {}
    void* m_pSetClosure;
    void* m_pGetClosure;
    closure_call_delegate m_ClosureCallDelegate;
};

class o_export Property : public ValueMember
{
    o_language_element;

public:
    static Class* const metaType;

public:
    Property();
    Property(Type* a_pValueType
        , const string& a_strName
        , MemberFunction* a_pSetMemberFunction
        , MemberFunction* a_pGetMemberFunction
        , Signal* a_pSignal
        , Range* a_pRange
    , uint a_uiSerializationMask
    , modifiers_t a_Modifiers = 0);

protected:
    Property(Type* a_pValueType
        , const string& a_strName
        , MemberFunction* a_pSetMemberFunction
        , MemberFunction* a_pGetMemberFunction
        , Signal* a_pSignal
        , Range* a_pRange
        , uint a_uiSerializationMask
        , modifiers_t a_Modifiers
        , int protectedCtorTag);

public:
    o_destructor ~Property(void);

    virtual void            getValue(void const* a_pObject, void* a_pDest) const;
    virtual void            setValue(void* a_pObject, void const* a_pSrc) const;
    Type*                   getValueType() const { return m_pValueType; }
    Type*                   getEffectiveValueType() const { return m_pValueType ? m_pValueType->removeConstReference() : nullptr; }
    virtual Property*       asProperty() const { return const_cast<Property*>(this); }
        
    MemberFunction*         getSetMemberFunction() const { return m_pSetMemberFunction; }
    MemberFunction*         getGetMemberFunction() const { return m_pGetMemberFunction; }
    Signal*                 getSignal() const { return m_pSignal; }

    virtual bool            referencesData(const void* a_pInstance, const phantom::data& a_Data) const;

    void                    addDataMember(DataMember* a_pDataMember);

    vector<DataMember*>::const_iterator beginDataMembers() const { return m_DataMembers.begin(); }
    vector<DataMember*>::const_iterator endDataMembers() const { return m_DataMembers.end(); }

    size_t                  getDataMemberCount() const { return m_DataMembers.size(); }

protected:
    virtual void            referencedElementRemoved(LanguageElement* a_pElement);

    void    setSignalString(string str);
    string  getSignalString() const;
    void    setSetMemberFunctionString(string str);
    string  getSetMemberFunctionString() const;
    void    setGetMemberFunctionString(string str);
    string  getGetMemberFunctionString() const;

    virtual void finalize();

protected:
    vector<DataMember*> m_DataMembers;
    Signal* m_pSignal;
    MemberFunction* m_pSetMemberFunction;
    MemberFunction* m_pGetMemberFunction;
    string* m_pSignalString;
    string* m_pSetMemberFunctionString;
    string* m_pGetMemberFunctionString;
    property_compilation_data* m_pCompilationData;
};

o_namespace_end(phantom, reflection)



#endif
