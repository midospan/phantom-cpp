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

#ifndef o_phantom_reflection_native_TNativeInstanceMethodConst_h__
#define o_phantom_reflection_native_TNativeInstanceMethodConst_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

#define TNativeInstanceMethodConstBase TNativeInstanceMethodBase

o_namespace_begin(phantom, reflection, native)

template<typename t_Ty, typename t_ReturnType>
class TNativeInstanceMethodConst0 : public TNativeInstanceMethodBase<t_Ty>
{
public:
    typedef TNativeInstanceMethodConst0<t_Ty, t_ReturnType> self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(void) const;
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
  

    TNativeInstanceMethodConst0(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMethodBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMethodIndexOf(a_pFunc));
    }

    virtual void            deleteNow() { o_delete(self_type) this; }

    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate0<t_ReturnType>(reinterpret_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)();
    }

    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    { 
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) 
            = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)();
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {
        ((static_cast<t_Ty*>(a_pObject))->*m_member_function_pointer)();
    }

    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) 
            = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)();
    }

protected:
    member_function_pointer m_member_function_pointer;
    
};


template<typename t_Ty>
class TNativeInstanceMethodConst0<t_Ty, void> : public TNativeInstanceMethodBase<t_Ty>
{
public:
    typedef TNativeInstanceMethodConst0<t_Ty, void>    self_type;
    typedef void (t_Ty::*member_function_pointer)(void) const;
  

    TNativeInstanceMethodConst0(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMethodBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMethodIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate0<fastdelegate::detail::DefaultVoid>(reinterpret_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        ((static_cast<t_Ty*>(a_pObject))->*m_member_function_pointer)();
    }

    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {
        ((static_cast<t_Ty*>(a_pObject))->*m_member_function_pointer)();
    }

    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;

};


template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeInstanceMethodConst1 : public TNativeInstanceMethodBase<t_Ty>
{
public:
    typedef TNativeInstanceMethodConst1<t_Ty, t_ReturnType, t_Param0>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0) const;
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;

    TNativeInstanceMethodConst1(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMethodBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMethodIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }

    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate1<t_ReturnType, t_Param0>(reinterpret_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            (static_cast<argument::list_1<t_Param0>*>(a_pParams)->p0);
    }

    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    { 
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) 
            = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            (static_cast<argument::list_1<t_Param0>*>(a_pParams)->p0);
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) );
    }

protected:
    member_function_pointer m_member_function_pointer;
};


template<typename t_Ty, typename t_Param0>
class TNativeInstanceMethodConst1<t_Ty, void, t_Param0> : public TNativeInstanceMethodBase<t_Ty>
{
public:
    typedef TNativeInstanceMethodConst1<t_Ty, void, t_Param0>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;

    TNativeInstanceMethodConst1(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMethodBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMethodIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }

    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate1<fastdelegate::detail::DefaultVoid, t_Param0>(reinterpret_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            (static_cast<argument::list_1<t_Param0>*>(a_pParams)->p0);
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }


protected:
    member_function_pointer m_member_function_pointer;
};


template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeInstanceMethodConst2 : public TNativeInstanceMethodBase<t_Ty>
{
public:
    typedef TNativeInstanceMethodConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1) const;
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    
    TNativeInstanceMethodConst2(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMethodBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMethodIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate2<t_ReturnType, t_Param0, t_Param1>(reinterpret_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p0
            , static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p1 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = 
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p0
            , static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p1 );
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) );
    }



protected:
    member_function_pointer m_member_function_pointer;
    
};

template<typename t_Ty, typename t_Param0, typename t_Param1>
class TNativeInstanceMethodConst2<t_Ty, void, t_Param0, t_Param1> : public TNativeInstanceMethodBase<t_Ty>
{
public:
    typedef TNativeInstanceMethodConst2<t_Ty, void, t_Param0, t_Param1>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;

    TNativeInstanceMethodConst2(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMethodBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMethodIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate2<fastdelegate::detail::DefaultVoid, t_Param0, t_Param1>(reinterpret_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    
    
    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p0
            , static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p1 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
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
class TNativeInstanceMethodConst3 : public TNativeInstanceMethodBase<t_Ty>
{
public:
    typedef TNativeInstanceMethodConst3<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2) const;
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;

    TNativeInstanceMethodConst3(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMethodBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMethodIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate3<t_ReturnType, t_Param0,t_Param1,t_Param2>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p0
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p1
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p2 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p0
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p1
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p2 );
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) );
    }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeInstanceMethodConst3<t_Ty, void, t_Param0, t_Param1, t_Param2> : public TNativeInstanceMethodBase<t_Ty>
{
public:
    typedef TNativeInstanceMethodConst3<t_Ty, void, t_Param0, t_Param1, t_Param2>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;

    TNativeInstanceMethodConst3(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMethodBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMethodIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate3<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p0
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p1
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p2 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
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
class TNativeInstanceMethodConst4 : public TNativeInstanceMethodBase<t_Ty>
{
public:
    typedef TNativeInstanceMethodConst4<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3) const;
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;

    TNativeInstanceMethodConst4(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMethodBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMethodIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate4<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p0
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p1
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p2
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p3 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p0
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p1
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p2
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p3 );
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) );
    }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeInstanceMethodConst4<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3> : public TNativeInstanceMethodBase<t_Ty>
{
public:
    typedef TNativeInstanceMethodConst4<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;

    TNativeInstanceMethodConst4(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMethodBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMethodIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate4<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p0
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p1
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p2
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p3 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) );
    }

    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
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
class TNativeInstanceMethodConst5 : public TNativeInstanceMethodBase<t_Ty>
{
public:
    typedef TNativeInstanceMethodConst5<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4) const;
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;

    TNativeInstanceMethodConst5(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMethodBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMethodIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate5<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p0
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p1
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p2
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p3
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p4 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p0
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p1
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p2
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p3
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p4 );
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
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
class TNativeInstanceMethodConst5<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4> : public TNativeInstanceMethodBase<t_Ty>
{
public:
    typedef TNativeInstanceMethodConst5<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;

    TNativeInstanceMethodConst5(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMethodBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMethodIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate5<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p0
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p1
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p2
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p3
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p4 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
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
class TNativeInstanceMethodConst6 : public TNativeInstanceMethodBase<t_Ty>
{
public:
    typedef TNativeInstanceMethodConst6<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5) const;
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;

    TNativeInstanceMethodConst6(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMethodBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMethodIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate6<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p0
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p1
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p2
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p3
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p4
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p5 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p0
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p1
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p2
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p3
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p4
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p5 );
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
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
class TNativeInstanceMethodConst6<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5> : public TNativeInstanceMethodBase<t_Ty>
{
public:
    typedef TNativeInstanceMethodConst6<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;

    TNativeInstanceMethodConst6(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMethodBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMethodIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate6<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p0
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p1
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p2
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p3
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p4
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p5 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const
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
class TNativeInstanceMethodConst7 : public TNativeInstanceMethodBase<t_Ty>
{
public:
    typedef TNativeInstanceMethodConst7<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)const;
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;

    TNativeInstanceMethodConst7(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMethodBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMethodIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate7<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
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
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p0
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p1
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p2
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p3
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p4
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p5
            , static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p6 );
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
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
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
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
class TNativeInstanceMethodConst7<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6> : public TNativeInstanceMethodBase<t_Ty>
{
public:
    typedef TNativeInstanceMethodConst7<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;



    TNativeInstanceMethodConst7(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMethodBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMethodIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate7<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
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
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
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
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
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
class TNativeInstanceMethodConst8 : public TNativeInstanceMethodBase<t_Ty>
{
public:
    typedef TNativeInstanceMethodConst8<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7) const;
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;



    TNativeInstanceMethodConst8(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMethodBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMethodIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate8<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
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
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p0
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p1
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p2
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p3
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p4
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p5
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p6
            , static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p7 );
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
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
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
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
class TNativeInstanceMethodConst8<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7> : public TNativeInstanceMethodBase<t_Ty>
{
public:
    typedef TNativeInstanceMethodConst8<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;



    TNativeInstanceMethodConst8(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMethodBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMethodIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate8<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
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
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
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
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void method called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;
};


#ifndef o_NO_FUNCTION_STYLE_TEMPLATE_SIGNATURE

template<typename t_Ty, typename Signature>
class TNativeInstanceMethodConst;

template<typename t_Ty, typename t_ReturnType>
class TNativeInstanceMethodConst<t_Ty, t_ReturnType()> 
    : public TNativeInstanceMethodConst0<t_ReturnType, t_Ty>
{
public:
    typedef TNativeInstanceMethodConst<t_Ty, t_ReturnType()>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(void) const;
  

    TNativeInstanceMethodConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMethodConst0<t_ReturnType, t_Ty>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native | o_const)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeInstanceMethodConst<t_Ty, t_ReturnType(t_Param0)> 
    : public TNativeInstanceMethodConst1<t_ReturnType, t_Param0, t_Ty>
{
public:
    typedef TNativeInstanceMethodConst<t_Ty, t_ReturnType(t_Param0)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0) const;
    TNativeInstanceMethodConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMethodConst1<t_ReturnType, t_Param0, t_Ty>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native | o_const)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeInstanceMethodConst<t_Ty, t_ReturnType(t_Param0,t_Param1)> 
    : public TNativeInstanceMethodConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>
{
public:
    typedef TNativeInstanceMethodConst<t_Ty, t_ReturnType(t_Param0, t_Param1)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1) const;
  

    TNativeInstanceMethodConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMethodConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native | o_const)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};


template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2>
class TNativeInstanceMethodConst<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2)> 
    : public TNativeInstanceMethodConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    typedef TNativeInstanceMethodConst<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2) const;
  

    TNativeInstanceMethodConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMethodConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native | o_const)
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
class TNativeInstanceMethodConst<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3)> 
    : public TNativeInstanceMethodConst4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    typedef TNativeInstanceMethodConst<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3) const;
  

    TNativeInstanceMethodConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMethodConst4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native | o_const)
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
class TNativeInstanceMethodConst<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4)> 
    : public TNativeInstanceMethodConst5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>
{
public:
    typedef TNativeInstanceMethodConst<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4) const;
  

    TNativeInstanceMethodConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMethodConst5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native | o_const)
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
class TNativeInstanceMethodConst<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)> : public TNativeInstanceMethodConst6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>
{
public:
    typedef TNativeInstanceMethodConst<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5) const;
  

    TNativeInstanceMethodConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMethodConst6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native | o_const)
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
class TNativeInstanceMethodConst<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)> : public TNativeInstanceMethodConst7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>
{
public:
    typedef TNativeInstanceMethodConst<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6) const;
  

    TNativeInstanceMethodConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMethodConst7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native | o_const)
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
class TNativeInstanceMethodConst<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)> : public TNativeInstanceMethodConst8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>
{
public:
    typedef TNativeInstanceMethodConst<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7) const;
  

    TNativeInstanceMethodConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMethodConst8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native | o_const)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};

#endif

o_namespace_end(phantom, reflection, native)

    o_traits_specialize_all_super_traitNTTS_TNativeMethodRTXXX(TNativeInstanceMethodConst)

#endif // reflection_native_TNativeInstanceMethodConst_h__