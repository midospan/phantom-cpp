/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_native_TNativeConstructorBase_h__
#define o_phantom_reflection_native_TNativeConstructorBase_h__



/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)

template<typename t_Class>
class TNativeConstructorBase : public Constructor
{
public:
    typedef void (t_Class::*simplest_member_function_ptr)();
    TNativeConstructorBase(const string& a_strName, Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : Constructor(a_strName, a_pSignature, a_Modifiers)
    {

    }
    virtual bool isNative() const { return true; }
    virtual void call( void* a_pThis, void** a_pArgs ) const = 0;
    virtual void call( void* a_pThis, void** a_pArgs, void* a_pReturnAddress ) const { call(a_pThis, a_pArgs); }
    virtual void call( void** a_pArgs ) const
    {
        void* pThis = *a_pArgs++; /// 'this' pointer is stored as '*this', a reference, so getting address of argument is getting address of *this (&*this) which is in fact 'this'
        call( caller, a_pArgs);
    }
    virtual void call( void** a_pArgs, void* a_pReturnAddress ) const
    {
        void* pThis = *a_pArgs++; /// 'this' pointer is stored as '*this', a reference, so getting address of argument is getting address of *this (&*this) which is in fact 'this'
        call( caller, a_pArgs, a_pReturnAddress);
    }
};


o_namespace_end(phantom, reflection, native)


    /*o_traits_specialize_all_base_traitNTB(
    (phantom,reflection,native)
    , (typename)
    , (t_Ty)
    , TNativeConstructorBase
    , (Constructor)
    )*/

#endif // reflection_native_TNativeConstructorBase_h__