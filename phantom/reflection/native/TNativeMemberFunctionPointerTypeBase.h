/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_native_TNativeMemberFunctionPointerTypeBase_h__
#define o_phantom_reflection_native_TNativeMemberFunctionPointerTypeBase_h__



/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)

template<typename t_Class>
class TNativeMemberFunctionPointerTypeBase : public MemberFunctionPointerType
{
public:
    typedef void (t_Class::*simplest_member_function_ptr)();
    TNativeMemberFunctionPointerTypeBase(Signature* a_pSignature, size_t a_Size, size_t a_Alignment, modifiers_t a_Modifiers = 0)
        : MemberFunctionPointerType(typeOf<t_Class>(), a_pSignature, a_Size, a_Alignment, a_Modifiers|o_native)
    {
    }

    virtual void call( void* a_pPointer, void* a_pThis, void** a_pArgs ) const = 0;
    virtual void call( void* a_pPointer, void* a_pThis, void** a_pArgs, void* a_pReturnAddress ) const 
    { 
        if(a_pReturnAddress) 
        {
            o_exception(exception::base_exception, "Expecting return address from a void function call, use call(void*, void**) instead"); 
        }
        else call(a_pPointer, a_pThis, a_pArgs); 
    }
    
};


o_namespace_end(phantom, reflection, native)

#endif // reflection_native_TNativeMemberFunctionPointerTypeBase_h__