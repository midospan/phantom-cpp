/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_FunctionPointerType_h__
#define o_phantom_reflection_FunctionPointerType_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export FunctionPointerType : public PointerType
{
    o_type;

    o_declare_meta_type(FunctionPointerType);

public:
    friend class Type;
    typedef void(*minimal_function_pointer_t)();

public:
    FunctionPointerType(Signature* a_pSignature, EABI a_eABI, modifiers_t a_Modifiers);

public:
    o_destructor ~FunctionPointerType(void);

    virtual void*           getClosure(void* a_pPointer) const;

    virtual 
    FunctionPointerType*    asFunctionPointerType() const { return const_cast<FunctionPointerType*>(this); }

    virtual void        copy(void* a_pDest, void const* a_pSrc) const;
    
    virtual void        valueFromString(const string& a_str, void* dest) const;

    virtual void        valueToString(string& a_str, const void* src) const;

    virtual void        valueToLiteral(string& a_str, const void* src) const;

    virtual string      getDecoratedName() const { return getQualifiedDecoratedName(); }
    virtual string      getQualifiedName() const { return getQualifiedDecoratedName(); }
    virtual string      getQualifiedDecoratedName() const { return m_pSignature->getReturnType()->getQualifiedDecoratedName()+"(*)"+m_pSignature->getQualifiedDecoratedName(); }

    virtual bool        isCopyable() const { return true; }

    Signature*          getSignature() const { return m_pSignature; }

    EABI                getABI() const { return m_eABI; }

    virtual void        call( void* a_pPointer, void** a_pArgs ) const;
    virtual void        call( void* a_pPointer, void** a_pArgs, void* a_pReturnAddress ) const;

protected:
    virtual void        referencedElementRemoved(LanguageElement* a_pElement);

protected:
    EABI        m_eABI;
    Signature*  m_pSignature;
};

o_namespace_end(phantom, reflection)



#endif