/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_MemberFunctionPointerType_h__
#define o_phantom_reflection_MemberFunctionPointerType_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export MemberFunctionPointerType : public MemberPointerType
{
    o_type;

    o_invalid_decl(MemberFunctionPointerType);

    o_declare_meta_type(MemberFunctionPointerType);

    friend class Type;

public:
    MemberFunctionPointerType(ClassType* a_pObjectType, Signature* a_pSignature, modifiers_t a_Modifiers);

protected: // Native constructor
    MemberFunctionPointerType(ClassType* a_pObjectType, Signature* a_pSignature, size_t a_Size, size_t a_Alignment, modifiers_t a_Modifiers);

public:
    o_destructor ~MemberFunctionPointerType(void);

    bool matches(const vector<Type*>& parameters, modifiers_t a_Qualifiers) const;

    bool matches(const vector<Expression*>& args, modifiers_t a_Qualifiers) const;

    virtual void*           getClosure(void* a_pPointer) const;

    virtual 
    MemberFunctionPointerType* asMemberFunctionPointerType() const { return const_cast<MemberFunctionPointerType*>(this); }

    virtual void        copy(void* a_pDest, void const* a_pSrc) const;
    
    virtual void        valueFromString(const string& a_str, void* dest) const;

    virtual void        valueToString(string& a_str, const void* src) const;

    virtual void        valueToLiteral(string& a_str, const void* src) const;

    virtual string      getDecoratedName() const { return getQualifiedDecoratedName(); }
    virtual string      getQualifiedName() const { return getQualifiedDecoratedName(); }
    virtual string      getQualifiedDecoratedName() const { return m_pSignature->getReturnType()->getQualifiedDecoratedName()+'('+m_pObjectType->getQualifiedDecoratedName()+"::*)"+m_pSignature->getQualifiedDecoratedName(); }

    virtual bool        isCopyable() const { return true; }

    Signature*          getSignature() const { return m_pSignature; }

    Type*               getReturnType() const { return m_pSignature->getReturnType(); }

    Type*               getParameterType(size_t i) const { return m_pSignature->getParameterType(i); }

    inline void         call( void* a_pPointer, void** a_pArgs ) const
    {
        void* pThis = *a_pArgs++; /// 'this' pointer is stored as '*this', a reference, so getting address of argument is getting address of *this (&*this) which is in fact 'this'
        call( a_pPointer, pThis, a_pArgs);
    }
    inline void         call( void* a_pPointer, void** a_pArgs, void* a_pReturnAddress ) const
    {
        void* pThis = *a_pArgs++; /// 'this' pointer is stored as '*this', a reference, so getting address of argument is getting address of *this (&*this) which is in fact 'this'
        call( a_pPointer, pThis, a_pArgs, a_pReturnAddress);
    }

    /// Non native member function pointers contains the meta member function they point to 

    virtual void call( void* a_pPointer, void* a_pThis, void** a_pArgs ) const;

    virtual void call( void* a_pPointer, void* a_pThis, void** a_pArgs, void* a_pReturnAddress ) const;

    void implicitConversions(const vector<Type*>& a_FunctionSignature, LanguageElement* a_pContextScope, conversions& a_ImplicitConversions) const;

    void implicitConversions(const vector<Expression*>& a_Arguments, LanguageElement* a_pContextScope, conversions& a_ImplicitConversions) const;

    void implicitConversions(Language* a_pLanguage, const vector<Type*>& a_FunctionSignature, LanguageElement* a_pContextScope, conversions& a_ImplicitConversions) const;

    void implicitConversions(Language* a_pLanguage, const vector<Expression*>& a_Arguments, LanguageElement* a_pContextScope, conversions& a_ImplicitConversions) const;

protected:
    virtual void        referencedElementRemoved(LanguageElement* a_pElement);

protected:
    Signature*   m_pSignature;
};

o_namespace_end(phantom, reflection)



#endif