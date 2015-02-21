/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_native_TNativeMemberFunctionConst_h__
#define o_phantom_reflection_native_TNativeMemberFunctionConst_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

#define TNativeMemberFunctionConstBase TNativeMemberFunctionBase

o_namespace_begin(phantom, reflection, native)

template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunctionConst0 : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionConst0<t_Ty, t_ReturnType> self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(void) const;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
  

    TNativeMemberFunctionConst0(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        
    }

    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate0<t_ReturnType>(reinterpret_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const 
    {
        ((static_cast<t_Ty*>(a_pObject))->*m_member_function_pointer)();
    }

    virtual void call(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<return_storage_type*>(a_pReturnAddress) 
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
class TNativeMemberFunctionConst0<t_Ty, void> : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionConst0<t_Ty, void>    self_type;
    typedef void (t_Ty::*member_function_pointer)(void) const;
  

    TNativeMemberFunctionConst0(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        
    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate0<fastdelegate::detail::DefaultVoid>(reinterpret_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const 
    {
        ((static_cast<t_Ty*>(a_pObject))->*m_member_function_pointer)();
    }

protected:
    member_function_pointer m_member_function_pointer;

};


template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionConst1 : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionConst1<t_Ty, t_ReturnType, t_Param0>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0) const;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;

    TNativeMemberFunctionConst1(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        
    }

    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate1<t_ReturnType, t_Param0>(reinterpret_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) );
    }

    virtual void call(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) ));
    }
    virtual void placementCall(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]))));
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
class TNativeMemberFunctionConst1<t_Ty, void, t_Param0> : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionConst1<t_Ty, void, t_Param0>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;

    TNativeMemberFunctionConst1(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        
    }

    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate1<fastdelegate::detail::DefaultVoid, t_Param0>(reinterpret_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) );
    }


protected:
    member_function_pointer m_member_function_pointer;
};


template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionConst2 : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1) const;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    
    TNativeMemberFunctionConst2(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        
    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate2<t_ReturnType, t_Param0, t_Param1>(reinterpret_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) );
    }
    virtual void call(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) ));
    }
    virtual void placementCall(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]))));
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
class TNativeMemberFunctionConst2<t_Ty, void, t_Param0, t_Param1> : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionConst2<t_Ty, void, t_Param0, t_Param1>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;

    TNativeMemberFunctionConst2(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        
    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate2<fastdelegate::detail::DefaultVoid, t_Param0, t_Param1>(reinterpret_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
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
class TNativeMemberFunctionConst3 : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionConst3<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2) const;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;

    TNativeMemberFunctionConst3(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
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
        *reinterpret_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) ));
    }
    virtual void placementCall(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]))));
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
class TNativeMemberFunctionConst3<t_Ty, void, t_Param0, t_Param1, t_Param2> : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionConst3<t_Ty, void, t_Param0, t_Param1, t_Param2>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;

    TNativeMemberFunctionConst3(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
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
class TNativeMemberFunctionConst4 : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionConst4<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3) const;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;

    TNativeMemberFunctionConst4(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
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
        *reinterpret_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
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
            , *static_cast<t_Param3_noref*>(a_pParams[3]))));
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
class TNativeMemberFunctionConst4<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3> : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionConst4<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;

    TNativeMemberFunctionConst4(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
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
class TNativeMemberFunctionConst5 : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionConst5<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4) const;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;

    TNativeMemberFunctionConst5(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
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
        *reinterpret_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
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
            , *static_cast<t_Param4_noref*>(a_pParams[4]))));
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
class TNativeMemberFunctionConst5<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4> : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionConst5<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;

    TNativeMemberFunctionConst5(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
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
class TNativeMemberFunctionConst6 : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionConst6<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5) const;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;

    TNativeMemberFunctionConst6(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
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
        *reinterpret_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
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
            , *static_cast<t_Param5_noref*>(a_pParams[5]))));
    }

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) 
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) ));
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
class TNativeMemberFunctionConst6<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5> : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionConst6<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;

    TNativeMemberFunctionConst6(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
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
class TNativeMemberFunctionConst7 : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionConst7<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)const;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;

    TNativeMemberFunctionConst7(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
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
        *reinterpret_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
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
            , *static_cast<t_Param6_noref*>(a_pParams[6]) )));
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
            , *static_cast<t_Param6_noref*>(a_pParams[6]) ));
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
class TNativeMemberFunctionConst7<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6> : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionConst7<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;



    TNativeMemberFunctionConst7(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
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
class TNativeMemberFunctionConst8 : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionConst8<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7) const;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;



    TNativeMemberFunctionConst8(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
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
        *reinterpret_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
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
            , *static_cast<t_Param7_noref*>(a_pParams[7]) ));
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
class TNativeMemberFunctionConst8<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7> : public TNativeMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionConst8<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;



    TNativeMemberFunctionConst8(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionBase<t_Ty>(a_strName,a_strSignature, a_pFunc, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
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
class TNativeMemberFunctionConst;

template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunctionConst<t_Ty, t_ReturnType()> 
    : public TNativeMemberFunctionConst0<t_ReturnType, t_Ty>
{
public:
    typedef TNativeMemberFunctionConst<t_Ty, t_ReturnType()>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(void) const;
  

    TNativeMemberFunctionConst(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionConst0<t_ReturnType, t_Ty>(a_strName,a_strSignature, a_pFunc , a_Modifiers | o_native | o_const)
    {

    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionConst<t_Ty, t_ReturnType(t_Param0)> 
    : public TNativeMemberFunctionConst1<t_ReturnType, t_Param0, t_Ty>
{
public:
    typedef TNativeMemberFunctionConst<t_Ty, t_ReturnType(t_Param0)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0) const;
    TNativeMemberFunctionConst(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionConst1<t_ReturnType, t_Param0, t_Ty>(a_strName,a_strSignature, a_pFunc , a_Modifiers | o_native | o_const)
    {

    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionConst<t_Ty, t_ReturnType(t_Param0,t_Param1)> 
    : public TNativeMemberFunctionConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>
{
public:
    typedef TNativeMemberFunctionConst<t_Ty, t_ReturnType(t_Param0, t_Param1)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1) const;
  

    TNativeMemberFunctionConst(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>(a_strName,a_strSignature, a_pFunc , a_Modifiers | o_native | o_const)
    {

    }

};


template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2>
class TNativeMemberFunctionConst<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2)> 
    : public TNativeMemberFunctionConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    typedef TNativeMemberFunctionConst<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2) const;
  

    TNativeMemberFunctionConst(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>(a_strName,a_strSignature, a_pFunc , a_Modifiers | o_native | o_const)
    {

    }

};


template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeMemberFunctionConst<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3)> 
    : public TNativeMemberFunctionConst4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    typedef TNativeMemberFunctionConst<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3) const;
  

    TNativeMemberFunctionConst(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionConst4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>(a_strName,a_strSignature, a_pFunc , a_Modifiers | o_native | o_const)
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
class TNativeMemberFunctionConst<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4)> 
    : public TNativeMemberFunctionConst5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>
{
public:
    typedef TNativeMemberFunctionConst<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4) const;
  

    TNativeMemberFunctionConst(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionConst5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>(a_strName,a_strSignature, a_pFunc , a_Modifiers | o_native | o_const)
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
class TNativeMemberFunctionConst<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)> : public TNativeMemberFunctionConst6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>
{
public:
    typedef TNativeMemberFunctionConst<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5) const;
  

    TNativeMemberFunctionConst(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionConst6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>(a_strName,a_strSignature, a_pFunc , a_Modifiers | o_native | o_const)
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
class TNativeMemberFunctionConst<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)> : public TNativeMemberFunctionConst7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>
{
public:
    typedef TNativeMemberFunctionConst<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6) const;
  

    TNativeMemberFunctionConst(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionConst7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>(a_strName,a_strSignature, a_pFunc , a_Modifiers | o_native | o_const)
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
class TNativeMemberFunctionConst<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)> : public TNativeMemberFunctionConst8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>
{
public:
    typedef TNativeMemberFunctionConst<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7) const;
  

    TNativeMemberFunctionConst(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionConst8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(a_strName,a_strSignature, a_pFunc , a_Modifiers | o_native | o_const)
    {

    }

};

o_namespace_end(phantom, reflection, native)

#endif // reflection_native_TNativeMemberFunctionConst_h__