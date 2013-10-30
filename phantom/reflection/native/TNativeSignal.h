/*
    This file is part of PHANTOM
         P reprocessed 
         H igh-level 
         A llocator 
         N ested state-machines and 
         T emplate 
         O riented 
         M eta-programming

    For the latest infos and sources, see http://code.google.com/p/phantom-cpp

    Copyright (C) 2008-2011 by Vivien MILLET

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE
*/

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
    typedef signal_t (t_Ty::*member_function_pointer)(void) const;
    typedef TNativeSignal0<t_Ty> self_type;
    typedef connection::slot::list (t_Ty::*member_pointer);

    TNativeSignal0(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, member_pointer a_pMember, bitfield a_bfModifiers = bitfield())
        : TNativeSignalBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc), m_member_pointer(a_pMember) {}

    virtual void            deleteNow() { o_delete(self_type) this; }

    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate0<signal_t>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, argument::list* a_pParams) const 
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)();
    }

    virtual void call(void* a_pObject, void** a_pParams) const 
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)();
    }

    virtual connection::slot::list*    getSlotList( void* a_pCaller ) const 
    {
        return &(static_cast<t_Ty*>(a_pCaller)->*m_member_pointer);
    }

protected:
    member_function_pointer m_member_function_pointer;
    member_pointer            m_member_pointer;

};


///  ==================================================================================================
///        1 PARAMETER
///  ==================================================================================================

template<typename t_Ty, typename t_Param0>
class TNativeSignal1 : public TNativeSignalBase<t_Ty>
{
public:
    typedef TNativeSignal1<t_Ty, t_Param0>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0)  const;
    typedef connection::slot::list (t_Ty::*member_pointer);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;

    TNativeSignal1(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, member_pointer a_pMember, bitfield a_bfModifiers = bitfield())
        :TNativeSignalBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc), m_member_pointer(a_pMember)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate1<signal_t, t_Param0>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    

    virtual void call(void* a_pObject, argument::list* a_pParams) const 
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            (static_cast<argument::list_1<t_Param0>*>(a_pParams)->p0);
    }

    virtual void call(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) );
    }

    virtual connection::slot::list*    getSlotList( void* a_pCaller ) const 
    {
        return &(static_cast<t_Ty*>(a_pCaller)->*m_member_pointer);
    }

protected:
    member_function_pointer m_member_function_pointer;
    member_pointer            m_member_pointer;
};


///  ==================================================================================================
///        2 PARAMETERS
///  ==================================================================================================

template<typename t_Ty, typename t_Param0, typename t_Param1>
class TNativeSignal2 : public TNativeSignalBase<t_Ty>
{
public:
    typedef TNativeSignal2<t_Ty, t_Param0, t_Param1>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1)  const;
    typedef connection::slot::list (t_Ty::*member_pointer);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;

    TNativeSignal2(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, member_pointer a_pMember, bitfield a_bfModifiers = bitfield())
        :TNativeSignalBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc), m_member_pointer(a_pMember)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate2<signal_t, t_Param0,t_Param1>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    

    virtual void call(void* a_pObject, argument::list* a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p0
            , static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p1 );
    }
    virtual void call(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) );
    }

    virtual connection::slot::list*    getSlotList( void* a_pCaller ) const 
    {
        return &(static_cast<t_Ty*>(a_pCaller)->*m_member_pointer);
    }

protected:
    member_function_pointer m_member_function_pointer;
    member_pointer            m_member_pointer;
};

///  ==================================================================================================
///        3 PARAMETERS
///  ==================================================================================================

template<typename t_Ty, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeSignal3 : public TNativeSignalBase<t_Ty>
{
public:
    typedef TNativeSignal3<t_Ty, t_Param0, t_Param1,t_Param2>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2) const;
    typedef connection::slot::list (t_Ty::*member_pointer);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;

    TNativeSignal3(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, member_pointer a_pMember, bitfield a_bfModifiers = bitfield())
        : TNativeSignalBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc), m_member_pointer(a_pMember)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate3<signal_t, t_Param0,t_Param1,t_Param2>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, argument::list* a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p0
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p1
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p2 );
    }
    virtual void call(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) );
    }

    virtual connection::slot::list*    getSlotList( void* a_pCaller ) const 
    {
        return &(static_cast<t_Ty*>(a_pCaller)->*m_member_pointer);
    }

protected:
    member_function_pointer m_member_function_pointer;
    member_pointer            m_member_pointer;
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
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3) const;
    typedef connection::slot::list (t_Ty::*member_pointer);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;

    TNativeSignal4(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, member_pointer a_pMember, bitfield a_bfModifiers = bitfield())
        : TNativeSignalBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc), m_member_pointer(a_pMember)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate4<signal_t, t_Param0,t_Param1,t_Param2,t_Param3>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, argument::list* a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p0
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p1
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p2
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p3 );
    }
    virtual void call(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]));
    }

    virtual connection::slot::list*    getSlotList( void* a_pCaller ) const 
    {
        return &(static_cast<t_Ty*>(a_pCaller)->*m_member_pointer);
    }

protected:
    member_function_pointer m_member_function_pointer;
    member_pointer            m_member_pointer;
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
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4) const;
    typedef connection::slot::list (t_Ty::*member_pointer);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;

    TNativeSignal5(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, member_pointer a_pMember, bitfield a_bfModifiers = bitfield())
        : TNativeSignalBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc), m_member_pointer(a_pMember)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate5<signal_t, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, argument::list* a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p0
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p1
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p2
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p3
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p4 );
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

    virtual connection::slot::list*    getSlotList( void* a_pCaller ) const 
    {
        return &(static_cast<t_Ty*>(a_pCaller)->*m_member_pointer);
    }

protected:
    member_function_pointer m_member_function_pointer;
    member_pointer            m_member_pointer;
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
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5) const;
    typedef connection::slot::list (t_Ty::*member_pointer);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;

    TNativeSignal6(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, member_pointer a_pMember, bitfield a_bfModifiers = bitfield())
        : TNativeSignalBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc), m_member_pointer(a_pMember)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate6<signal_t, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, argument::list* a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p0
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p1
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p2
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p3
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p4
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p5 );
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

    virtual connection::slot::list*    getSlotList( void* a_pCaller ) const 
    {
        return &(static_cast<t_Ty*>(a_pCaller)->*m_member_pointer);
    }

protected:
    member_function_pointer m_member_function_pointer;
    member_pointer            m_member_pointer;
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
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6) const;
    typedef connection::slot::list (t_Ty::*member_pointer);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;

    TNativeSignal7(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, member_pointer a_pMember, bitfield a_bfModifiers = bitfield())
        : TNativeSignalBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc), m_member_pointer(a_pMember)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate7<signal_t, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, argument::list* a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p0
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p1
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p2
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p3
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p4
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p5
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p6 );
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

    virtual connection::slot::list*    getSlotList( void* a_pCaller ) const 
    {
        return &(static_cast<t_Ty*>(a_pCaller)->*m_member_pointer);
    }

protected:
    member_function_pointer m_member_function_pointer;
    member_pointer            m_member_pointer;
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
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7) const;
    typedef connection::slot::list (t_Ty::*member_pointer);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param7_noref;

    TNativeSignal8(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, member_pointer a_pMember, bitfield a_bfModifiers = bitfield())
        : TNativeSignalBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc), m_member_pointer(a_pMember)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate8<signal_t, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, argument::list* a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p0
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p1
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p2
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p3
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p4
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p5
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p6
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p7 );
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

    virtual connection::slot::list*    getSlotList( void* a_pCaller ) const 
    {
        return &(static_cast<t_Ty*>(a_pCaller)->*m_member_pointer);
    }

protected:
    member_function_pointer m_member_function_pointer;
    member_pointer            m_member_pointer;
};

#ifndef o_NO_FUNCTION_STYLE_TEMPLATE_SIGNATURE

template<typename t_Ty, typename Signature>
class TNativeSignal;

template<typename t_Ty>
class TNativeSignal<t_Ty, signal_t()> : public TNativeSignal0< t_Ty>
{
public:
    typedef TNativeSignal<t_Ty, signal_t()>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(void) const;
    TNativeSignal(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, typename TNativeSignal0< t_Ty>::member_pointer a_pMember, bitfield a_bfModifiers = bitfield())
        :TNativeSignal0< t_Ty>(a_strName,a_pSignature, a_pFunc, a_pMember, a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }
};

template<typename t_Ty, typename t_Param0>
class TNativeSignal<t_Ty, signal_t(t_Param0)> : public TNativeSignal1<t_Ty, t_Param0>
{
public:
    typedef TNativeSignal<t_Ty, signal_t(t_Param0)>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0) const;
    TNativeSignal(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, typename TNativeSignal1< t_Ty, t_Param0>::member_pointer a_pMember, bitfield a_bfModifiers = bitfield())
        :TNativeSignal1<t_Ty, t_Param0>(a_strName,a_pSignature, a_pFunc ,a_pMember,  a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }
};

template<typename t_Ty, typename t_Param0, typename t_Param1>
class TNativeSignal<t_Ty, signal_t(t_Param0,t_Param1)> : public TNativeSignal2<t_Ty, t_Param0, t_Param1>
{
public:
    typedef TNativeSignal<t_Ty, signal_t(t_Param0, t_Param1)>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1) const;
    TNativeSignal(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, typename TNativeSignal2< t_Ty, t_Param0, t_Param1>::member_pointer a_pMember, bitfield a_bfModifiers = bitfield())
        :TNativeSignal2<t_Ty, t_Param0, t_Param1>(a_strName,a_pSignature, a_pFunc , a_pMember, a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};

template<typename t_Ty
    
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2>
class TNativeSignal<t_Ty, signal_t(t_Param0,t_Param1,t_Param2)> : public TNativeSignal3<t_Ty, t_Param0, t_Param1, t_Param2>
{
public:
    typedef TNativeSignal<t_Ty, signal_t(t_Param0, t_Param1, t_Param2)>    self_type;
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2) const;
    TNativeSignal(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, typename TNativeSignal3< t_Ty, t_Param0, t_Param1, t_Param2>::member_pointer a_pMember, bitfield a_bfModifiers = bitfield())
        :TNativeSignal3<t_Ty, t_Param0, t_Param1, t_Param2>(a_strName,a_pSignature, a_pFunc , a_pMember, a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

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
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3) const;
    TNativeSignal(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, typename TNativeSignal4<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3>::member_pointer a_pMember, bitfield a_bfModifiers = bitfield())
        :TNativeSignal4<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3>(a_strName,a_pSignature, a_pFunc , a_pMember, a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

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
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4) const;
    TNativeSignal(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, typename TNativeSignal5<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>::member_pointer a_pMember, bitfield a_bfModifiers = bitfield())
        :TNativeSignal5<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>(a_strName,a_pSignature, a_pFunc , a_pMember, a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

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
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5) const;
    TNativeSignal(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, typename TNativeSignal6<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>::member_pointer a_pMember, bitfield a_bfModifiers = bitfield())
        :TNativeSignal6<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>(a_strName,a_pSignature, a_pFunc , a_pMember, a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

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
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6) const;
    TNativeSignal(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, typename TNativeSignal7<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>::member_pointer a_pMember,  bitfield a_bfModifiers = bitfield())
        :TNativeSignal7<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>(a_strName,a_pSignature, a_pFunc , a_pMember, a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

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
    typedef signal_t (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7) const;
    TNativeSignal(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, typename TNativeSignal8<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>::member_pointer a_pMember,  bitfield a_bfModifiers = bitfield())
        :TNativeSignal8<t_Ty, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(a_strName,a_pSignature, a_pFunc , a_pMember, a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};

#endif

o_namespace_end(phantom, reflection, native)

o_traits_specialize_all_super_traitNTTS_TNativeMemberFunctionXXX(TNativeSignal)
                                                                                                                                                                                          
#endif // TNativeSignal