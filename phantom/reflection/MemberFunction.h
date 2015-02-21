/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_MemberFunction_h__
#define o_phantom_reflection_MemberFunction_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Subroutine.h>
/* *********************************************** */

o_namespace_begin(phantom, reflection)
    
class o_export MemberFunction : public Subroutine
{
    o_language_element;

    friend class Class;
    friend class ClassType;
    friend class Structure;
    friend class VirtualMemberFunctionTable;

public:
    static Class* const metaType;

public:
    MemberFunction(modifiers_t a_Modifiers = 0);
    MemberFunction(const string& a_strName, Signature* a_pSignature, modifiers_t a_Modifiers = 0);
    ~MemberFunction();

    reflection::ClassType*              getOwnerClassType() const { return static_cast<reflection::ClassType*>(m_pOwner); }
    reflection::Class*                  getOwnerClass() const { return static_cast<reflection::ClassType*>(m_pOwner)->asClass(); }

    virtual void                        call( void* a_pCallerAddress, void** a_pArgs ) const { Subroutine::call(a_pCallerAddress, a_pArgs); }
    virtual void                        call( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const { Subroutine::call(a_pCallerAddress, a_pArgs, a_pReturnAddress); }
    virtual void                        placementCall( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const { Subroutine::placementCall(a_pCallerAddress, a_pArgs, a_pReturnAddress); }
    virtual void                        call( void** a_pArgs ) const { Subroutine::call(a_pArgs); }
    virtual void                        call( void** a_pArgs, void* a_pReturnAddress ) const { Subroutine::call(a_pArgs, a_pReturnAddress); }
    virtual void                        placementCall( void** a_pArgs, void* a_pReturnAddress ) const { Subroutine::placementCall(a_pArgs, a_pReturnAddress); }
    void                                safeCall( void* a_pCallerAddress, void** a_pArgs ) const;
    void                                safeCall( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const;
    void                                safePlacementCall( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const;
    /*void                                virtualCall( void** a_pArgs ) const
    {
        void* pThis = *a_pArgs++;
        virtualCall(pThis, a_pArgs);
    }

    void                                virtualCall( void** a_pArgs, void* a_pReturnAddress ) const
    {
        void* pThis = *a_pArgs++;
        virtualCall(pThis, a_pArgs, a_pReturnAddress);
    }

    void                                virtualCall( void* a_pThis, void** a_pArgs ) const 
    {
        if(!isVirtual())
        {
            o_exception(exception::reflection_runtime_exception, "virtual call on non-virtual member function");
        }
        if(isNative()) 
        {
            call(a_pThis, a_pArgs);
            return;
        }
        o_assert(m_uiVirtualTableIndex != ~size_t(0));
        void** vtable = *(void***)a_pThis;
        void* pClosure = vtable[m_uiVirtualTableIndex];
        if(pClosure == nullptr)
        {
            o_exception(exception::reflection_runtime_exception, "pure virtual member function call");
        }
        /// on interpretation
        ((MemberFunction*)pClosure)->call()
    }

    void                                virtualCall( void* a_pThis, void** a_pArgs, void* a_pReturnAddress ) const 
    {
        if(!isVirtual())
        {
            o_exception(exception::reflection_runtime_exception, "virtual call on non-virtual member function");
        }
        if(isNative()) 
        {
            call(a_pThis, a_pArgs, a_pReturnAddress);
            return;
        }
        o_assert(m_uiVirtualTableIndex != ~size_t(0));
    }*/

    bool                                canOverride(MemberFunction* a_pMemberFunction) const;
    bool                                canOverride(const string& a_strName, Signature* a_pSignature, modifiers_t a_Modifiers) const;

    virtual MemberFunction*             asSlot() const { return (((m_Modifiers & o_slot_member_function) == o_slot_member_function)) ? const_cast<MemberFunction*>(this) : nullptr; }
    virtual LanguageElement*            asLanguageElement() const { return const_cast<MemberFunction*>(this); }
    virtual Subroutine*                 asSubroutine() const { return const_cast<MemberFunction*>(this); }
    virtual MemberFunction*             asMemberFunction() const { return const_cast<MemberFunction*>(this); }

    size_t                              getVirtualTableIndex() const { return m_uiVirtualTableIndex; }
    
    void                                setVirtual();

    virtual void*                       getVTableClosure(size_t a_uiOffset) const;

    void                                setVTableClosure(size_t a_uiOffset, void* a_pClosure);

    void                                getOriginalOverriddenMemberFunctions(vector<MemberFunction*>& a_Out) const;

    virtual Block*                      createBlock();

    virtual bool                        hasAccessTo(NamedElement* a_pOther, NamedElement* a_pAccessContext = nullptr) const
    {
        return Subroutine::hasAccessTo(a_pOther, a_pAccessContext) OR (m_pOwner AND m_pOwner->hasAccessTo(a_pOther));
    }

    bool                                acceptsObjectExpressionType(Type* a_pType) const;

    bool                                acceptsObjectExpressionQualifiers(modifiers_t a_CallerQualifiers) const ;

    Type*                               getImplicitObjectParameterType() const;

protected:
    MemberFunction(ClassType* a_pClassType, const string& a_strName, const string& a_strSignature, modifiers_t a_Modifiers = 0);
    virtual void                        setVirtualTableIndex(int index)
    { 
        o_assert(m_uiVirtualTableIndex == ~size_t(0)); 
        m_uiVirtualTableIndex = index; 
    }

protected:
    size_t              m_uiVirtualTableIndex;
    map<size_t, void*>* m_pVTableClosures;

/// -----------------------
};

o_namespace_end(phantom, reflection)



#endif
