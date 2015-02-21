/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_native_TNativeDestructor_h__
#define o_phantom_reflection_native_TNativeDestructor_h__



/* ****************** Includes ******************* */
/* **************** Declarations ***************** */

/* *********************************************** */
o_namespace_begin(phantom, reflection, native)

template<typename t_Ty>
class TNativeDestructor : public MemberFunction
{
    typedef TNativeDestructor<t_Ty> self_type;

public:
    void closure_wrapper() { destructor_protection_hacker<t_Ty>::apply(this); }
    TNativeDestructor(const string& a_strName)
        : MemberFunction(a_strName, Signature::Create(typeOf<void>()), (has_virtual_destructor_cascade<t_Ty>::value ? o_virtual : 0) | o_native | o_public_access)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualDestructorIndex<t_Ty>());
    }

    virtual void*           getClosure() const { return generic_member_func_ptr(&self_type::closure_wrapper); }

    DelegateMemento         getDelegateMemento(void* a_pObject) const
    {
        return DelegateMemento();
    }

    virtual void call(void* a_pInstance, void** a_pParams) const
    {
        destructor_protection_hacker<t_Ty>::apply(a_pInstance);
    }

    virtual void call(void* a_pInstance, void** a_pParams, void* a_pReturnAddress) const
    {
        destructor_protection_hacker<t_Ty>::apply(a_pInstance);
    }

    virtual void call(void** a_pParams) const
    {
        destructor_protection_hacker<t_Ty>::apply(a_pParams[0]);
    }

    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        destructor_protection_hacker<t_Ty>::apply(a_pParams[0]);
    }

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return nullptr;
    }

    virtual bool        isAddressable() const { return false; }

};


o_namespace_end(phantom, reflection, native)

#endif // TNativeDestructor_h__
