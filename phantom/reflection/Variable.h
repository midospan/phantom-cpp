/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Variable_h__
#define o_phantom_reflection_Variable_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Variable : public NamedElement
{
    o_language_element;

    o_declare_meta_type(Variable);

    friend class AnonymousSection;

public:
    Variable();
    Variable(Type* a_pValueType, const string& a_strName, modifiers_t a_Modifiers = 0);
    Variable(Type* a_pValueType, const string& a_strName, Range* a_pRange = nullptr, modifiers_t a_Modifiers = 0);
    Variable(void* a_pAddress, Range* a_pRange = nullptr, modifiers_t a_Modifiers = 0);
    Variable(void* a_pAddress, Type* a_pValueType, Range* a_pRange = nullptr, modifiers_t a_Modifiers = 0);
    Variable(void* a_pAddress, Type* a_pValueType, const string& a_strName, Range* a_pRange = nullptr, modifiers_t a_Modifiers = 0);

public:
    o_destructor ~Variable(void);
    
    virtual Variable*           asVariable() const  { return (Variable*)this; }
    virtual StaticDataMember*   asStaticDataMember() const  { return (m_pOwner == nullptr OR m_pOwner->asClassType()) ? (StaticDataMember*)this : nullptr; }

    void*           getAddress() const { return m_pAddress; }
    Type*           getValueType() const { return m_pValueType; }
    Range*          getRange() const { return m_pRange; }
    void            setRange(Range* a_pRange);

    void            setValue(void const* a_pSrc) const 
    {
        m_pValueType->copy(m_pAddress, a_pSrc);
    }

    void            getValue(void* a_pDest) const 
    {
        m_pValueType->copy(a_pDest, m_pAddress);
    }

    virtual Expression* toExpression(Expression* a_pLeftExpression) const;

protected:
    void            setAddress(void* a_pAddress) { m_pAddress = a_pAddress; }

protected:
    virtual void    referencedElementRemoved(LanguageElement* a_pElement);
    void            setValueTypeName(string str);
    string          getValueTypeName() const;
    virtual void    finalize();

protected:
    Type*       m_pValueType;
    Range*      m_pRange;
    void*       m_pAddress;
    string*     m_pValueTypeName;
    AnonymousSection* m_pAnonymousSection;
};

o_namespace_end(phantom, reflection)



#endif
