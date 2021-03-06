/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_native_TNativeSignal_h__
#define o_phantom_reflection_native_TNativeSignal_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)

///  ==================================================================================================
///        0 PARAMETERS
///  ==================================================================================================

template<typename t_Ty>
class TNativeSignal0 : public TNativeSignalBase<t_Ty>
{
public:
    typedef signal_t (t_Ty::*member_function_pointer)(void);
    typedef TNativeSignal0<t_Ty> self_type;

    TNativeSignal0(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, o_NESTED_TYPE TNativeSignalBase<t_Ty>::member_pointer a_MemberPointer, modifiers_t a_Modifiers = 0)
        : TNativeSignalBase<t_Ty>(a_strName, a_strSignature, a_MemberPointer, a_Modifiers | o_native)
        , m_member_function_pointer(a_pFunc)
    {
    }

    virtual void*       getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento     getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate0<signal_t>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const 
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)();
    }

    virtual connection::slot::list*    getSlotList( void* a_pThis ) const 
    {
        return &(static_cast<t_Ty*>(a_pThis)->*TNativeSignalBase<t_Ty>::m_member_pointer);
    }

protected:
    member_function_pointer m_member_function_pointer;

};


///  ==================================================================================================
///        1 PARAMETER
///  ==================================================================================================

template<typename t_Ty, typename t_Param0>
class TNativeSignal1 : public TNativeSignalBase<t_Ty>
{
public:
    typedef TNativeSignal1<t_Ty, t_Param0>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;

    TNativeSignal1(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, o_NESTED_TYPE TNativeSignalBase<t_Ty>::member_pointer a_MemberPointer, modifiers_t a_Modifiers = 0)
        :TNativeSignalBase<t_Ty>(a_strName, a_strSignature, a_MemberPointer, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }

    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate1<signal_t, t_Param0>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) );
    }

    virtual connection::slot::list*    getSlotList( void* a_pThis ) const 
    {
        return &(static_cast<t_Ty*>(a_pThis)->*TNativeSignalBase<t_Ty>::m_member_pointer);
    }

protected:
    member_function_pointer m_member_function_pointer;
};


///  ==================================================================================================
///        2 PARAMETERS
///  ==================================================================================================

template<typename t_Ty, typename t_Param0, typename t_Param1>
class TNativeSignal2 : public TNativeSignalBase<t_Ty>
{
public:
    typedef TNativeSignal2<t_Ty, t_Param0, t_Param1>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;

    TNativeSignal2(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, o_NESTED_TYPE TNativeSignalBase<t_Ty>::member_pointer a_MemberPointer, modifiers_t a_Modifiers = 0)
        :TNativeSignalBase<t_Ty>(a_strName, a_strSignature, a_MemberPointer, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate2<signal_t, t_Param0,t_Param1>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) );
    }

    virtual connection::slot::list*    getSlotList( void* a_pThis ) const 
    {
        return &(static_cast<t_Ty*>(a_pThis)->*TNativeSignalBase<t_Ty>::m_member_pointer);
    }

protected:
    member_function_pointer m_member_function_pointer;
};

///  ==================================================================================================
///        3 PARAMETERS
///  ==================================================================================================

template<typename t_Ty, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeSignal3 : public TNativeSignalBase<t_Ty>
{
public:
    typedef TNativeSignal3<t_Ty, t_Param0, t_Param1,t_Param2>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;

    TNativeSignal3(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, o_NESTED_TYPE TNativeSignalBase<t_Ty>::member_pointer a_MemberPointer, modifiers_t a_Modifiers = 0)
        : TNativeSignalBase<t_Ty>(a_strName, a_strSignature, a_MemberPointer, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate3<signal_t, t_Param0,t_Param1,t_Param2>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) );
    }

    virtual connection::slot::list*    getSlotList( void* a_pThis ) const 
    {
        return &(static_cast<t_Ty*>(a_pThis)->*TNativeSignalBase<t_Ty>::m_member_pointer);
    }

protected:
    member_function_pointer m_member_function_pointer;
};


///  ==================================================================================================
///        4 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeSignal4 : public TNativeSignalBase<t_Ty>
{
public:
    typedef TNativeSignal4<t_Ty, t_Param0, t_Param1,t_Param2,t_Param3>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;

    TNativeSignal4(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, o_NESTED_TYPE TNativeSignalBase<t_Ty>::member_pointer a_MemberPointer, modifiers_t a_Modifiers = 0)
        : TNativeSignalBase<t_Ty>(a_strName, a_strSignature, a_MemberPointer, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate4<signal_t, t_Param0,t_Param1,t_Param2,t_Param3>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]));
    }

    virtual connection::slot::list*    getSlotList( void* a_pThis ) const 
    {
        return &(static_cast<t_Ty*>(a_pThis)->*TNativeSignalBase<t_Ty>::m_member_pointer);
    }

protected:
    member_function_pointer m_member_function_pointer;
};

///  ==================================================================================================
///        5 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeSignal5 : public TNativeSignalBase<t_Ty>
{
public:
    typedef TNativeSignal5<t_Ty, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;

    TNativeSignal5(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, o_NESTED_TYPE TNativeSignalBase<t_Ty>::member_pointer a_MemberPointer, modifiers_t a_Modifiers = 0)
        : TNativeSignalBase<t_Ty>(a_strName, a_strSignature, a_MemberPointer, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate5<signal_t, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
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

    virtual connection::slot::list*    getSlotList( void* a_pThis ) const 
    {
        return &(static_cast<t_Ty*>(a_pThis)->*TNativeSignalBase<t_Ty>::m_member_pointer);
    }

protected:
    member_function_pointer m_member_function_pointer;
};

///  ==================================================================================================
///        6 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeSignal6 : public TNativeSignalBase<t_Ty>
{
public:
    typedef TNativeSignal6<t_Ty, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;

    TNativeSignal6(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, o_NESTED_TYPE TNativeSignalBase<t_Ty>::member_pointer a_MemberPointer, modifiers_t a_Modifiers = 0)
        : TNativeSignalBase<t_Ty>(a_strName, a_strSignature, a_MemberPointer, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate6<signal_t, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
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

    virtual connection::slot::list*    getSlotList( void* a_pThis ) const 
    {
        return &(static_cast<t_Ty*>(a_pThis)->*TNativeSignalBase<t_Ty>::m_member_pointer);
    }

protected:
    member_function_pointer m_member_function_pointer;
};


///  ==================================================================================================
///        7 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6>
class TNativeSignal7 : public TNativeSignalBase<t_Ty>
{
public:
    typedef TNativeSignal7<t_Ty, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;

    TNativeSignal7(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, o_NESTED_TYPE TNativeSignalBase<t_Ty>::member_pointer a_MemberPointer, modifiers_t a_Modifiers = 0)
        : TNativeSignalBase<t_Ty>(a_strName, a_strSignature, a_MemberPointer, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate7<signal_t, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
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

    virtual connection::slot::list*    getSlotList( void* a_pThis ) const 
    {
        return &(static_cast<t_Ty*>(a_pThis)->*TNativeSignalBase<t_Ty>::m_member_pointer);
    }

protected:
    member_function_pointer m_member_function_pointer;
};


///  ==================================================================================================
///        8 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7>
class TNativeSignal8 : public TNativeSignalBase<t_Ty>
{
public:
    typedef TNativeSignal8<t_Ty, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param7_noref;

    TNativeSignal8(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, o_NESTED_TYPE TNativeSignalBase<t_Ty>::member_pointer a_MemberPointer, modifiers_t a_Modifiers = 0)
        : TNativeSignalBase<t_Ty>(a_strName, a_strSignature, a_MemberPointer, a_Modifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void*           getClosure() const { return generic_member_func_ptr(m_member_function_pointer); }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate8<signal_t, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
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

    virtual connection::slot::list*    getSlotList( void* a_pThis ) const 
    {
        return &(static_cast<t_Ty*>(a_pThis)->*TNativeSignalBase<t_Ty>::m_member_pointer);
    }

protected:
    member_function_pointer m_member_function_pointer;
};



template<typename t_Ty, typename Signature>
class TNativeSignal;

template<typename t_Ty>
class TNativeSignal<t_Ty, signal_t()> : public TNativeSignal0< t_Ty>
{
public:
    typedef TNativeSignal<t_Ty, signal_t()>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(void);
    TNativeSignal(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, typename TNativeSignal0< t_Ty>::member_pointer a_MemberPointer, modifiers_t a_Modifiers = 0)
        :TNativeSignal0< t_Ty>(a_strName,a_strSignature, a_pFunc, a_MemberPointer, a_Modifiers | o_native)
    {

    }
};

template<typename t_Ty, typename t_Param0>
class TNativeSignal<t_Ty, signal_t(t_Param0)> : public TNativeSignal1<t_Ty, t_Param0>
{
public:
    typedef TNativeSignal<t_Ty, signal_t(t_Param0)>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0);
    TNativeSignal(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, typename TNativeSignal1< t_Ty, t_Param0>::member_pointer a_MemberPointer, modifiers_t a_Modifiers = 0)
        :TNativeSignal1<t_Ty, t_Param0>(a_strName,a_strSignature, a_pFunc ,a_MemberPointer,  a_Modifiers | o_native)
    {

    }
};

template<typename t_Ty, typename t_Param0, typename t_Param1>
class TNativeSignal<t_Ty, signal_t(t_Param0,t_Param1)> : public TNativeSignal2<t_Ty, t_Param0, t_Param1>
{
public:
    typedef TNativeSignal<t_Ty, signal_t(t_Param0, t_Param1)>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1);
    TNativeSignal(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, typename TNativeSignal2< t_Ty, t_Param0, t_Param1>::member_pointer a_MemberPointer, modifiers_t a_Modifiers = 0)
        :TNativeSignal2<t_Ty, t_Param0, t_Param1>(a_strName,a_strSignature, a_pFunc , a_MemberPointer, a_Modifiers | o_native)
    {

    }

};

template<typename t_Ty
    
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2>
class TNativeSignal<t_Ty, signal_t(t_Param0,t_Param1,t_Param2)> : public TNativeSignal3<t_Ty, t_Param0, t_Param1, t_Param2>
{
public:
    typedef TNativeSignal<t_Ty, signal_t(t_Param0, t_Param1, t_Param2)>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2);
    TNativeSignal(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, typename TNativeSignal3< t_Ty, t_Param0, t_Param1, t_Param2>::member_pointer a_MemberPointer, modifiers_t a_Modifiers = 0)
        :TNativeSignal3<t_Ty, t_Param0, t_Param1, t_Param2>(a_strName,a_strSignature, a_pFunc , a_MemberPointer, a_Modifiers | o_native)
    {

    }
};


template<typename t_Ty
    
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeSignal<t_Ty, signal_t(t_Param0,t_Param1,t_Param2,t_Param3)> : public TNativeSignal4<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    typedef TNativeSignal<t_Ty, signal_t(t_Param0, t_Param1, t_Param2,t_Param3)>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3);
    TNativeSignal(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, typename TNativeSignal4<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3>::member_pointer a_MemberPointer, modifiers_t a_Modifiers = 0)
        :TNativeSignal4<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3>(a_strName,a_strSignature, a_pFunc , a_MemberPointer, a_Modifiers | o_native)
    {

    }
};

template<typename t_Ty
    
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeSignal<t_Ty, signal_t(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4)> : public TNativeSignal5<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>
{
public:
    typedef TNativeSignal<t_Ty, signal_t(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4)>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4);
    TNativeSignal(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, typename TNativeSignal5<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>::member_pointer a_MemberPointer, modifiers_t a_Modifiers = 0)
        :TNativeSignal5<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>(a_strName,a_strSignature, a_pFunc , a_MemberPointer, a_Modifiers | o_native)
    {

    }
};

template<typename t_Ty
    
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeSignal<t_Ty, signal_t(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)> 
    : public TNativeSignal6<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>
{
public:
    typedef TNativeSignal<t_Ty, signal_t(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5)>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5);
    TNativeSignal(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, typename TNativeSignal6<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>::member_pointer a_MemberPointer, modifiers_t a_Modifiers = 0)
        :TNativeSignal6<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>(a_strName,a_strSignature, a_pFunc , a_MemberPointer, a_Modifiers | o_native)
    {

    }
};

template<typename t_Ty
    
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6>
class TNativeSignal<t_Ty, signal_t(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)> : public TNativeSignal7<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>
{
public:
    typedef TNativeSignal<t_Ty, signal_t(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6);
    TNativeSignal(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, typename TNativeSignal7<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>::member_pointer a_MemberPointer,  modifiers_t a_Modifiers = 0)
        :TNativeSignal7<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>(a_strName,a_strSignature, a_pFunc , a_MemberPointer, a_Modifiers | o_native)
    {

    }
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
class TNativeSignal<t_Ty, signal_t(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)> 
    : public TNativeSignal8<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>
{
public:
    typedef TNativeSignal<t_Ty, signal_t(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7);
    TNativeSignal(const string& a_strName, const string& a_strSignature, member_function_pointer a_pFunc, typename TNativeSignal8<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>::member_pointer a_MemberPointer,  modifiers_t a_Modifiers = 0)
        :TNativeSignal8<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(a_strName,a_strSignature, a_pFunc , a_MemberPointer, a_Modifiers | o_native)
    {

    }
};


o_namespace_end(phantom, reflection, native)

#endif // TNativeSignal