/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_native_TNativeMemberFunction_h__
#define o_phantom_reflection_native_TNativeMemberFunction_h__



/* ****************** Includes ******************* */
/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)

///  ==================================================================================================
///        0 PARAMETERS
///  ==================================================================================================

template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunction0 : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(void);
    typedef TNativeMemberFunction0<t_Ty, t_ReturnType> self_type;

    TNativeMemberFunction0(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        
    }

    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate0<t_ReturnType>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)();
    }

    virtual void call(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress)
            = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)());
    }

    virtual void placementCall(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( )));
    }  

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)());
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    member_function_pointer m_member_function_pointer;

};


template<typename t_Ty>
class TNativeMemberFunction0<t_Ty, void> : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunction0<t_Ty, void>    self_type;
    typedef void (t_Ty::*member_function_pointer)(void);



    TNativeMemberFunction0(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        
    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate0<fastdelegate::detail::DefaultVoid>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void        call(void* a_pObject, void** a_pParams) const
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)();
    }

protected:
    member_function_pointer m_member_function_pointer;

};


///  ==================================================================================================
///        1 PARAMETER
///  ==================================================================================================

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunction1 : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunction1<t_Ty, t_ReturnType, t_Param0>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0);
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;


    TNativeMemberFunction1(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        
    }

    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate1<t_ReturnType, t_Param0>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void        call(void* a_pObject, void** a_pParams) const
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            (*static_cast<t_Param0_noref*>(a_pParams[0]));
    }

    virtual void        call(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress)
            = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            (*static_cast<t_Param0_noref*>(a_pParams[0])));
    }
    virtual void placementCall(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) )));
    }

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            (*static_cast<t_Param0_noref*>(a_pParams[0])));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    member_function_pointer m_member_function_pointer;
};


template<typename t_Ty, typename t_Param0>
class TNativeMemberFunction1<t_Ty, void, t_Param0> : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunction1<t_Ty, void, t_Param0>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;


    TNativeMemberFunction1(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        
    }

    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate1<fastdelegate::detail::DefaultVoid, t_Param0>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void        call(void* a_pObject, void** a_pParams) const
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            (*static_cast<t_Param0_noref*>(a_pParams[0]));
    }

protected:
    member_function_pointer m_member_function_pointer;
};


///  ==================================================================================================
///        2 PARAMETERS
///  ==================================================================================================

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunction2 : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunction2<t_Ty, t_ReturnType, t_Param0, t_Param1>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1);
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;


    TNativeMemberFunction2(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        
    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate2<t_ReturnType, t_Param0,t_Param1>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) );
    }
    virtual void call(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param0_noref*>(a_pParams[1]) ));
    }
    virtual void placementCall(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param0_noref*>(a_pParams[1]) )));
    }

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) ));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty, typename t_Param0, typename t_Param1>
class TNativeMemberFunction2<t_Ty, void, t_Param0, t_Param1> : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunction2<t_Ty, void, t_Param0, t_Param1>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;


    TNativeMemberFunction2(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        
    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate2<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) );
    }

protected:
    member_function_pointer m_member_function_pointer;
};


///  ==================================================================================================
///        3 PARAMETERS
///  ==================================================================================================

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunction3 : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunction3<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2);
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;


    TNativeMemberFunction3(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        
    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate3<t_ReturnType, t_Param0,t_Param1,t_Param2>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) );
    }
    virtual void call(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) ));
    }

    virtual void placementCall(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            )));
    }  

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) ));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunction3<t_Ty, void, t_Param0, t_Param1, t_Param2> : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunction3<t_Ty, void, t_Param0, t_Param1, t_Param2>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;


    TNativeMemberFunction3(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        
    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate3<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) );
    }

protected:
    member_function_pointer m_member_function_pointer;
};



///  ==================================================================================================
///        4 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeMemberFunction4 : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunction4<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3);
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;


    TNativeMemberFunction4(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        
    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate4<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) );
    }
    virtual void call(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) ));
    }

    virtual void placementCall(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            )));
    }  

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) ));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeMemberFunction4<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3> : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunction4<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;


    TNativeMemberFunction4(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        
    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate4<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }


    virtual void call(void* a_pObject, void** a_pParams) const
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) );
    }

protected:
    member_function_pointer m_member_function_pointer;
};


///  ==================================================================================================
///        5 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeMemberFunction5 : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunction5<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4);
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;


    TNativeMemberFunction5(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        
    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate5<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4]) );
    }
    virtual void call(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4]) ));
    }

    virtual void placementCall(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            )));
    }    

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4]) ));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeMemberFunction5<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4> : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunction5<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;



    TNativeMemberFunction5(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        
    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate5<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4]) );
    }

protected:
    member_function_pointer m_member_function_pointer;
};

///  ==================================================================================================
///        6 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeMemberFunction6 : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunction6<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5);
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;



    TNativeMemberFunction6(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        
    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate6<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) );
    }
    virtual void call(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) ));
    }
    virtual void placementCall(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            )));
    }

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])  ));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeMemberFunction6<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5> : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunction6<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;


    TNativeMemberFunction6(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        
    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate6<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) );
    }

protected:
    member_function_pointer m_member_function_pointer;
};





///  ==================================================================================================
///        7 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6>
class TNativeMemberFunction7 : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunction7<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6);
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;


    TNativeMemberFunction7(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        
    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate7<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6]) );
    }
    virtual void call(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6]) ));
    }
    virtual void placementCall(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            )));
    }

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])  ));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6>
class TNativeMemberFunction7<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6> : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunction7<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;


    TNativeMemberFunction7(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        
    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate7<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6]) );
    }

protected:
    member_function_pointer m_member_function_pointer;
};



///  ==================================================================================================
///        8 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7>
class TNativeMemberFunction8 : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunction8<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7);
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;


    TNativeMemberFunction8(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        
    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate8<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7]) );
    }
    virtual void call(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7]) ));
    }
    virtual void placementCall(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7]) )));
    }

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) 
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7])));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7>
class TNativeMemberFunction8<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7> : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunction8<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;



    TNativeMemberFunction8(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        
    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate8<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    
    virtual void call(void* a_pObject, void** a_pParams) const
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7]) );
    }

protected:
    member_function_pointer m_member_function_pointer;
};




template<typename t_Ty, typename Signature>
class TNativeMemberFunction;

template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunction<t_Ty, t_ReturnType()> : public TNativeMemberFunction0< t_Ty, t_ReturnType>
{
public:
    typedef TNativeMemberFunction<t_Ty, t_ReturnType()>    self_type;
  typedef t_ReturnType (t_Ty::*member_function_pointer)(void);

    TNativeMemberFunction(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunction0< t_Ty, t_ReturnType>(a_strName,a_strSignature, a_pFunc , a_Modifiers | o_native)
    {

    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunction<t_Ty, t_ReturnType(t_Param0)> : public TNativeMemberFunction1<t_Ty, t_ReturnType, t_Param0>
{
public:
    typedef TNativeMemberFunction<t_Ty, t_ReturnType(t_Param0)>    self_type;
  typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0);

    TNativeMemberFunction(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunction1<t_Ty, t_ReturnType, t_Param0>(a_strName,a_strSignature, a_pFunc , a_Modifiers | o_native)
    {

    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunction<t_Ty, t_ReturnType(t_Param0,t_Param1)> : public TNativeMemberFunction2<t_Ty, t_ReturnType, t_Param0, t_Param1>
{
public:
    typedef TNativeMemberFunction<t_Ty, t_ReturnType(t_Param0, t_Param1)>    self_type;
  typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1);

    TNativeMemberFunction(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunction2<t_Ty, t_ReturnType, t_Param0, t_Param1>(a_strName,a_strSignature, a_pFunc , a_Modifiers | o_native)
    {

    }

};

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2>
class TNativeMemberFunction<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2)> : public TNativeMemberFunction3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    typedef TNativeMemberFunction<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2)>    self_type;
  typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2);

    TNativeMemberFunction(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunction3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>(a_strName,a_strSignature, a_pFunc , a_Modifiers | o_native)
    {

    }

};


template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeMemberFunction<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3)> : public TNativeMemberFunction4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    typedef TNativeMemberFunction<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3)>    self_type;
  typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3);

    TNativeMemberFunction(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunction4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>(a_strName,a_strSignature, a_pFunc , a_Modifiers | o_native)
    {

    }

};

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeMemberFunction<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4)> : public TNativeMemberFunction5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>
{
public:
    typedef TNativeMemberFunction<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4)>    self_type;
  typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4);

    TNativeMemberFunction(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunction5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>(a_strName,a_strSignature, a_pFunc , a_Modifiers | o_native)
    {

    }

};

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeMemberFunction<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)>
    : public TNativeMemberFunction6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>
{
public:
    typedef TNativeMemberFunction<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5)>    self_type;
  typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5);

    TNativeMemberFunction(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunction6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>(a_strName,a_strSignature, a_pFunc , a_Modifiers | o_native)
    {

    }

};

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6>
class TNativeMemberFunction<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)> : public TNativeMemberFunction7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>
{
public:
    typedef TNativeMemberFunction<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)>    self_type;
  typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6);

    TNativeMemberFunction(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunction7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>(a_strName,a_strSignature, a_pFunc , a_Modifiers | o_native)
    {

    }

};


template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7>
class TNativeMemberFunction<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)>
    : public TNativeMemberFunction8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>
{
public:
    typedef TNativeMemberFunction<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)>    self_type;
  typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7);

    TNativeMemberFunction(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunction8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(a_strName,a_strSignature, a_pFunc , a_Modifiers | o_native)
    {

    }

};

o_namespace_end(phantom, reflection, native)

#endif // TNativeMemberFunction_h__
