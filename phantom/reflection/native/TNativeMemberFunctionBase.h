/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_native_TNativeMemberFunctionBase_h__
#define o_phantom_reflection_native_TNativeMemberFunctionBase_h__



/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)

template<typename t_Class>
class TNativeMemberFunctionBase : public MemberFunction
{
public:
    typedef void (t_Class::*simplest_member_function_ptr)();
    template<typename t_Func>
    TNativeMemberFunctionBase(const string& a_strName, const string& a_strSignature, t_Func a_pFunc, modifiers_t a_Modifiers = 0)
        : MemberFunction(phantom::reflection::native::currentClassType(), a_strName, a_strSignature, a_Modifiers|o_native)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
        m_strName = conversionOperatorNameNormalizer(a_strName, this);
        phantom::reflection::native::currentClassType()->addMemberFunction(this);
    }
    virtual void call( void* a_pThis, void** a_pArgs ) const = 0;
    virtual void call( void* a_pThis, void** a_pArgs, void* a_pReturnAddress ) const 
    { 
        if(a_pReturnAddress) 
        {
            o_exception(exception::base_exception, "Expecting return address from a void function call, use call(void*, void**) instead"); 
        }
        else call(a_pThis, a_pArgs); 
    }
    virtual void placementCall( void* a_pThis, void** a_pArgs, void* a_pReturnAddress ) const 
    { 
        if(a_pReturnAddress) 
        {
            o_exception(exception::base_exception, "Expecting return address from a void function call, use placementCall(void*, void**) instead"); 
        }
        else call(a_pThis, a_pArgs); 
    }
    virtual void call( void** a_pArgs ) const
    {
        void* pThis = *a_pArgs++; /// 'this' pointer is stored as '*this', a reference, so getting address of argument is getting address of *this (&*this) which is in fact 'this'
        call( pThis, a_pArgs);
    }
    virtual void call( void** a_pArgs, void* a_pReturnAddress ) const
    {
        void* pThis = *a_pArgs++; /// 'this' pointer is stored as '*this', a reference, so getting address of argument is getting address of *this (&*this) which is in fact 'this'
        call( pThis, a_pArgs, a_pReturnAddress);
    }
    virtual void placementCall( void** a_pArgs, void* a_pReturnAddress ) const
    {
        void* pThis = *a_pArgs++; /// 'this' pointer is stored as '*this', a reference, so getting address of argument is getting address of *this (&*this) which is in fact 'this'
        placementCall( pThis, a_pArgs, a_pReturnAddress);
    }
};


o_namespace_end(phantom, reflection, native)

#endif // reflection_native_TNativeMemberFunctionBase_h__