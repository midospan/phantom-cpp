/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_native_TNativeSignalBase_h__
#define o_phantom_reflection_native_TNativeSignalBase_h__



/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)

template<typename t_Ty>
class TNativeSignalBase : public Signal
{
public:
    typedef connection::slot::list (t_Ty::*member_pointer);

    TNativeSignalBase(const string& a_strName, const string& a_strSignature, member_pointer a_MemberPointer, modifiers_t a_Modifiers = 0)
        : Signal(phantom::reflection::native::currentClassType(), o_dynamic_proxy_new(TNativeDataMember<t_Ty, connection::slot::list>)(connection::slot::list::metaType, string("PHANTOM_CODEGEN_m_slot_list_of_")+a_strName, a_MemberPointer, nullptr, 0, o_private_access) 
                , a_strName, a_strSignature, a_Modifiers|o_native)
                , m_member_pointer(a_MemberPointer) 
    {
        phantom::reflection::native::currentClass()->addSignal(this);
    }

    virtual void                        call( void* a_pCallerAddress, void** a_pArgs ) const = 0;
    virtual void                        call( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const { call( a_pCallerAddress, a_pArgs ); }
    virtual void                        call( void** a_pArgs ) const 
    {
        void* pCaller = *((void**)(*a_pArgs++));
        call(pCaller, a_pArgs);
    }
    virtual void                        call( void** a_pArgs, void* a_pReturnAddress ) const 
    { 
        void* pCaller = *((void**)(*a_pArgs++));
        call(pCaller, a_pArgs);
    }

protected:
    member_pointer            m_member_pointer;
};


o_namespace_end(phantom, reflection, native)

    /*o_traits_specialize_all_base_traitNTB(
    (phantom,reflection,native)
    , (typename)
    , (t_Ty)
    , TNativeSignalBase
    , (Signal)
    )*/

#endif // reflection_native_TNativeSignalBase_h__