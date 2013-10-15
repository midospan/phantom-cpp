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

#ifndef o_phantom_reflection_TNativeStaticMethod_h__
#define o_phantom_reflection_TNativeStaticMethod_h__



/* ****************** Includes ******************* */
/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)

template<typename t_Ty, typename t_ReturnType>
class TNativeStaticMethod0 : public TNativeStaticMethodBase<t_Ty>
{
public:
    typedef TNativeStaticMethod0<t_Ty, t_ReturnType> self_type;
    typedef t_ReturnType (*member_function_pointer)(void);
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;


    TNativeStaticMethod0(){}
    TNativeStaticMethod0(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeStaticMethodBase<t_Ty>(a_strName, a_pSignature, a_bfModifiers|o_native|o_static), m_member_function_pointer(a_pFunc){}

    virtual void            deleteNow() { o_delete(self_type) this; }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate0<t_ReturnType>(m_member_function_pointer).GetMemento();
    }

    virtual void call(argument::list* a_pParams) const
    {
        (*m_member_function_pointer)();
    }

    virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
    {
        *reinterpret_cast<t_ReturnType*>(a_pReturnAddress)
            = (*m_member_function_pointer)();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)();
    }

    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *reinterpret_cast<t_ReturnType*>(a_pReturnAddress)
            = (*m_member_function_pointer)();
    }

protected:
    member_function_pointer        m_member_function_pointer;
};


template<typename t_Ty>
class TNativeStaticMethod0<t_Ty, void> : public TNativeStaticMethodBase<t_Ty>
{
public:
    typedef TNativeStaticMethod0<t_Ty, void>    self_type;
  typedef void (*member_function_pointer)(void);


    TNativeStaticMethod0()
    {

    }
    TNativeStaticMethod0(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeStaticMethodBase<t_Ty>(a_strName, a_pSignature, a_bfModifiers|o_native|o_static), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate0<fastdelegate::detail::DefaultVoid>(m_member_function_pointer).GetMemento();
    }

    virtual void call(argument::list* a_pParams) const
    {
        (*m_member_function_pointer)();
    }

    virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)();
    }

    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }
protected:
    member_function_pointer m_member_function_pointer;

};


template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeStaticMethod1 : public TNativeStaticMethodBase<t_Ty>
{
public:
    typedef TNativeStaticMethod1<t_Ty, t_ReturnType, t_Param0>    self_type;
    typedef t_ReturnType (*member_function_pointer)(t_Param0);
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;


    TNativeStaticMethod1()
    {

    }
    TNativeStaticMethod1(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeStaticMethodBase<t_Ty>(a_strName, a_pSignature, a_bfModifiers|o_native|o_static), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }


    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate1<t_ReturnType, t_Param0>(m_member_function_pointer).GetMemento();
    }



    virtual void call(argument::list* a_pParams) const
    {
        (*m_member_function_pointer)
            (static_cast<argument::list_1<t_Param0>*>(a_pParams)->p0);
    }

    virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
    {
        *reinterpret_cast<t_ReturnType*>(a_pReturnAddress)
            = (*m_member_function_pointer)
            (static_cast<argument::list_1<t_Param0>*>(a_pParams)->p0);
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *reinterpret_cast<t_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) );
    }

protected:
    member_function_pointer m_member_function_pointer;
};


template<typename t_Ty, typename t_Param0>
class TNativeStaticMethod1<t_Ty, void, t_Param0> : public TNativeStaticMethodBase<t_Ty>
{
public:
    typedef TNativeStaticMethod1<t_Ty, void, t_Param0>    self_type;
    typedef void (*member_function_pointer)(t_Param0);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;


    TNativeStaticMethod1()
    {

    }
    TNativeStaticMethod1(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeStaticMethodBase<t_Ty>(a_strName, a_pSignature, a_bfModifiers|o_native|o_static), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }


    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate1<fastdelegate::detail::DefaultVoid, t_Param0>(m_member_function_pointer).GetMemento();
    }

    virtual void call(argument::list* a_pParams) const
    {
        (*m_member_function_pointer)
            (static_cast<argument::list_1<t_Param0>*>(a_pParams)->p0);
    }

    virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }


    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;
};


template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeStaticMethod2 : public TNativeStaticMethodBase<t_Ty>
{
public:
    typedef TNativeStaticMethod2<t_Ty, t_ReturnType, t_Param0, t_Param1>    self_type;
    typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1);
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;


    TNativeStaticMethod2()
    {

    }
    TNativeStaticMethod2(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeStaticMethodBase<t_Ty>(a_strName, a_pSignature, a_bfModifiers|o_native|o_static), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate2<t_ReturnType, t_Param0, t_Param1>(m_member_function_pointer).GetMemento();
    }



    virtual void call(argument::list* a_pParams) const
    {
        (*m_member_function_pointer)
            ( static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p0
            , static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p1 );
    }
    virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
    {
        *reinterpret_cast<t_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
            ( static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p0
            , static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p1 );
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *reinterpret_cast<t_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) );
    }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty, typename t_Param0, typename t_Param1>
class TNativeStaticMethod2<t_Ty, void, t_Param0, t_Param1> : public TNativeStaticMethodBase<t_Ty>
{
public:
    typedef TNativeStaticMethod2<t_Ty, void, t_Param0, t_Param1>    self_type;
    typedef void (*member_function_pointer)(t_Param0,t_Param1);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;


    TNativeStaticMethod2()
    {

    }
    TNativeStaticMethod2(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeStaticMethodBase<t_Ty>(a_strName, a_pSignature, a_bfModifiers|o_native|o_static), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate2<fastdelegate::detail::DefaultVoid, t_Param0, t_Param1>(m_member_function_pointer).GetMemento();
    }

    virtual void call(argument::list* a_pParams) const
    {
        (*m_member_function_pointer)
            ( static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p0
            , static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p1 );
    }
    virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;
};


///  ==================================================================================================
///        3 PARAMETERS
///  ==================================================================================================

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeStaticMethod3 : public InstanceMethod
{
public:
    typedef TNativeStaticMethod3<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2>    self_type;
    typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2);
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;


    TNativeStaticMethod3(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate3<t_ReturnType, t_Param0,t_Param1,t_Param2>(m_member_function_pointer).GetMemento();
    }

    virtual void call(argument::list* a_pParams) const
    {
        (*m_member_function_pointer)
            ( static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p0
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p1
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p2 );
    }
    virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
    {
        *reinterpret_cast<t_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
            ( static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p0
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p1
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p2 );
    }


    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *reinterpret_cast<t_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) );
    }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeStaticMethod3<t_Ty, void, t_Param0, t_Param1, t_Param2> : public InstanceMethod
{
public:
    typedef TNativeStaticMethod3<t_Ty, void, t_Param0, t_Param1, t_Param2>    self_type;
    typedef void (*member_function_pointer)(t_Param0,t_Param1,t_Param2);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;

    TNativeStaticMethod3(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate3<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2>(m_member_function_pointer).GetMemento();
    }

    virtual void call(argument::list* a_pParams) const
    {
        (*m_member_function_pointer)
            ( static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p0
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p1
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p2 );
    }
    virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }


    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
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
class TNativeStaticMethod4 : public InstanceMethod
{
public:
    typedef TNativeStaticMethod4<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3>    self_type;
    typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3);
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;

    TNativeStaticMethod4(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate4<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3>(m_member_function_pointer).GetMemento();
    }

    virtual void call(argument::list* a_pParams) const
    {
        (*m_member_function_pointer)
            ( static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p0
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p1
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p2
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p3 );
    }
    virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
    {
        *reinterpret_cast<t_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
            ( static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p0
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p1
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p2
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p3 );
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *reinterpret_cast<t_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]));
    }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeStaticMethod4<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3> : public InstanceMethod
{
public:
    typedef TNativeStaticMethod4<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3>    self_type;
    typedef void (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;

    TNativeStaticMethod4(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate4<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3>(m_member_function_pointer).GetMemento();
    }

    virtual void call(argument::list* a_pParams) const
    {
        (*m_member_function_pointer)
            ( static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p0
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p1
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p2
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p3 );
    }
    virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }


    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
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
class TNativeStaticMethod5 : public InstanceMethod
{
public:
    typedef TNativeStaticMethod5<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4>    self_type;
    typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4);
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;

    TNativeStaticMethod5(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate5<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(m_member_function_pointer).GetMemento();
    }

    virtual void call(argument::list* a_pParams) const
    {
        (*m_member_function_pointer)
            ( static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p0
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p1
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p2
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p3
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p4 );
    }
    virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
    {
        *reinterpret_cast<t_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
            ( static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p0
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p1
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p2
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p3
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p4 );
    }


    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *reinterpret_cast<t_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4]) );
    }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeStaticMethod5<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4> : public InstanceMethod
{
public:
    typedef TNativeStaticMethod5<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>    self_type;
    typedef void (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;

    TNativeStaticMethod5(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate5<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(m_member_function_pointer).GetMemento();
    }

    virtual void call(argument::list* a_pParams) const
    {
        (*m_member_function_pointer)
            ( static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p0
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p1
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p2
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p3
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p4 );
    }
    virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }


    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
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
class TNativeStaticMethod6 : public InstanceMethod
{
public:
    typedef TNativeStaticMethod6<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>    self_type;
    typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5);
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;

    TNativeStaticMethod6(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate6<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(m_member_function_pointer).GetMemento();
    }

    virtual void call(argument::list* a_pParams) const
    {
        (*m_member_function_pointer)
            ( static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p0
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p1
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p2
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p3
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p4
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p5 );
    }
    virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
    {
        *reinterpret_cast<t_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
            ( static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p0
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p1
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p2
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p3
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p4
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p5 );
    }


    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *reinterpret_cast<t_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
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

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeStaticMethod6<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5> : public InstanceMethod
{
public:
    typedef TNativeStaticMethod6<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>    self_type;
    typedef void (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;

    TNativeStaticMethod6(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate6<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(m_member_function_pointer).GetMemento();
    }

    virtual void call(argument::list* a_pParams) const
    {
        (*m_member_function_pointer)
            ( static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p0
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p1
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p2
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p3
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p4
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p5 );
    }
    virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }


    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
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
class TNativeStaticMethod7 : public InstanceMethod
{
public:
    typedef TNativeStaticMethod7<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>    self_type;
    typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6);
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;

    TNativeStaticMethod7(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate7<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(m_member_function_pointer).GetMemento();
    }

    virtual void call(argument::list* a_pParams) const
    {
        (*m_member_function_pointer)
            ( static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p0
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p1
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p2
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p3
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p4
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p5
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p6 );
    }
    virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
    {
        *reinterpret_cast<t_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
            ( static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p0
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p1
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p2
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p3
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p4
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p5
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p6 );
    }


    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *reinterpret_cast<t_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
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

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6>
class TNativeStaticMethod7<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6> : public InstanceMethod
{
public:
    typedef TNativeStaticMethod7<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>    self_type;
    typedef void (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6);
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;

    TNativeStaticMethod7(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate7<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(m_member_function_pointer).GetMemento();
    }

    virtual void call(argument::list* a_pParams) const
    {
        (*m_member_function_pointer)
            ( static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p0
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p1
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p2
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p3
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p4
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p5
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p6 );
    }
    virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6]));
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
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
class TNativeStaticMethod8 : public InstanceMethod
{
public:
    typedef TNativeStaticMethod8<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>    self_type;
    typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7);
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;

    TNativeStaticMethod8(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate8<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(m_member_function_pointer).GetMemento();
    }

    virtual void call(argument::list* a_pParams) const
    {
        (*m_member_function_pointer)
            ( static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p0
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p1
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p2
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p3
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p4
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p5
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p6
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p7 );
    }
    virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
    {
        *reinterpret_cast<t_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
            ( static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p0
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p1
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p2
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p3
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p4
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p5
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p6
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p7 );
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *reinterpret_cast<t_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
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

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7>
class TNativeStaticMethod8<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7> : public InstanceMethod
{
public:
    typedef TNativeStaticMethod8<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>    self_type;
  typedef void (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7);
  typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;



    TNativeStaticMethod8(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

    void*                   getClosurePointer() const { return (void*)m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate8<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(m_member_function_pointer).GetMemento();
    }

    virtual void call(argument::list* a_pParams) const
    {
        (*m_member_function_pointer)
            ( static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p0
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p1
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p2
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p3
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p4
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p5
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p6
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p7 );
    }
    virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }

    virtual void call(void** a_pParams) const
    {
        (*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;
};

#ifndef o_NO_FUNCTION_STYLE_TEMPLATE_SIGNATURE

template<typename t_Ty, typename Signature>
class TNativeStaticMethod;

template<typename t_Ty, typename t_ReturnType>
class TNativeStaticMethod<t_Ty, t_ReturnType()>
    : public TNativeStaticMethod0< t_Ty, t_ReturnType>
{
public:
    typedef TNativeStaticMethod<t_Ty, t_ReturnType()>    self_type;
    typedef t_ReturnType (*member_function_pointer)(void);

    TNativeStaticMethod(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeStaticMethod0<t_Ty,t_ReturnType>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeStaticMethod<t_Ty, t_ReturnType(t_Param0)> : public TNativeStaticMethod1<t_Ty, t_ReturnType, t_Param0>
{
public:
    typedef TNativeStaticMethod<t_Ty, t_ReturnType(t_Param0)>    self_type;
    typedef t_ReturnType (*member_function_pointer)(t_Param0);

    TNativeStaticMethod(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeStaticMethod1<t_Ty,t_ReturnType,t_Param0>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeStaticMethod<t_Ty, t_ReturnType(t_Param0,t_Param1)> : public TNativeStaticMethod2<t_Ty, t_ReturnType, t_Param0, t_Param1>
{
public:
    typedef TNativeStaticMethod<t_Ty, t_ReturnType(t_Param0, t_Param1)>    self_type;
  typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1);

    TNativeStaticMethod(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeStaticMethod2<t_Ty,t_ReturnType,t_Param0,t_Param1>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2>
class TNativeStaticMethod<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2)> : public TNativeStaticMethod3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    typedef TNativeStaticMethod<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2)>    self_type;
  typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2);

    TNativeStaticMethod(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeStaticMethod3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};


template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeStaticMethod<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3)> : public TNativeStaticMethod4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    typedef TNativeStaticMethod<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3)>    self_type;
  typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3);

    TNativeStaticMethod(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeStaticMethod4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeStaticMethod<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4)> : public TNativeStaticMethod5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>
{
public:
    typedef TNativeStaticMethod<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4)>    self_type;
  typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4);

    TNativeStaticMethod(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeStaticMethod5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeStaticMethod<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)> : public TNativeStaticMethod6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>
{
public:
    typedef TNativeStaticMethod<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5)>    self_type;
  typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5);

    TNativeStaticMethod(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeStaticMethod6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

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
class TNativeStaticMethod<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)> : public TNativeStaticMethod7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>
{
public:
    typedef TNativeStaticMethod<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)>    self_type;
  typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6);

    TNativeStaticMethod(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeStaticMethod7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

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
class TNativeStaticMethod<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)> : public TNativeStaticMethod8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>
{
public:
    typedef TNativeStaticMethod<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)>    self_type;
  typedef t_ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7);

    TNativeStaticMethod(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeStaticMethod8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};

#endif

o_namespace_end(phantom, reflection, native)


    o_traits_specialize_all_super_traitNTTS_TNativeMethodRTXXX(TNativeStaticMethod)

#endif // TNativeStaticMethod_h__
