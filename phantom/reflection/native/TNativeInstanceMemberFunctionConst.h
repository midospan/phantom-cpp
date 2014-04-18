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

#ifndef o_phantom_reflection_native_TNativeInstanceMemberFunctionConst_h__
#define o_phantom_reflection_native_TNativeInstanceMemberFunctionConst_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

#define TNativeInstanceMemberFunctionConstBase TNativeInstanceMemberFunctionBase

o_namespace_begin(phantom, reflection, native)

template<typename t_Ty, typename t_ReturnType>
class TNativeInstanceMemberFunctionConst0 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInstanceMemberFunctionConst0<t_Ty, t_ReturnType> self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(void) const;
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
  

    TNativeInstanceMemberFunctionConst0(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        :TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }

    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }

    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate0<t_ReturnType>(reinterpret_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    

    virtual void call(void* a_pObject, argument::list* a_pParams) const 
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)();
    }

    virtual void call(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    { 
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) 
            = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)();
    }

    virtual void call(void* a_pObject, void** a_pParams) const 
    {
        ((static_cast<t_Ty*>(a_pObject))->*m_member_function_pointer)();
    }

    virtual void call(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) 
            = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)();
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
class TNativeInstanceMemberFunctionConst0<t_Ty, void> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInstanceMemberFunctionConst0<t_Ty, void>    self_type;
    typedef void (t_Ty::*member_function_pointer)(void) const;
  

    TNativeInstanceMemberFunctionConst0(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        :TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate0<fastdelegate::detail::DefaultVoid>(reinterpret_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    

    virtual void call(void* a_pObject, argument::list* a_pParams) const 
    {
        ((static_cast<t_Ty*>(a_pObject))->*m_member_function_pointer)();
    }

    virtual void call(void* a_pObject, void** a_pParams) const 
    {
        ((static_cast<t_Ty*>(a_pObject))->*m_member_function_pointer)();
    }

protected:
    member_function_pointer m_member_function_pointer;

};


template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeInstanceMemberFunctionConst1 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInstanceMemberFunctionConst1<t_Ty, t_ReturnType, t_Param0>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0) const;
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;

    TNativeInstanceMemberFunctionConst1(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        :TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }

    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate1<t_ReturnType, t_Param0>(reinterpret_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, argument::list* a_pParams) const 
    {
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            (static_cast<argument::list_1<t_Param0>*>(a_pParams)->p0);
    }

    virtual void call(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    { 
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) 
            = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            (static_cast<argument::list_1<t_Param0>*>(a_pParams)->p0);
    }

    virtual void call(void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) );
    }

    virtual void call(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) );
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
class TNativeInstanceMemberFunctionConst1<t_Ty, void, t_Param0> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInstanceMemberFunctionConst1<t_Ty, void, t_Param0>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;

    TNativeInstanceMemberFunctionConst1(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        :TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }

    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate1<fastdelegate::detail::DefaultVoid, t_Param0>(reinterpret_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
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


protected:
    member_function_pointer m_member_function_pointer;
};


template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeInstanceMemberFunctionConst2 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInstanceMemberFunctionConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1) const;
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    
    TNativeInstanceMemberFunctionConst2(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        :TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate2<t_ReturnType, t_Param0, t_Param1>(reinterpret_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void call(void* a_pObject, argument::list* a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p0
            , static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p1 );
    }
    virtual void call(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = 
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
    virtual void call(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) );
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
class TNativeInstanceMemberFunctionConst2<t_Ty, void, t_Param0, t_Param1> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInstanceMemberFunctionConst2<t_Ty, void, t_Param0, t_Param1>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;

    TNativeInstanceMemberFunctionConst2(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate2<fastdelegate::detail::DefaultVoid, t_Param0, t_Param1>(reinterpret_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
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


protected:
    member_function_pointer m_member_function_pointer;
};




///  ==================================================================================================
///        3 PARAMETERS
///  ==================================================================================================

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeInstanceMemberFunctionConst3 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInstanceMemberFunctionConst3<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2) const;
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;

    TNativeInstanceMemberFunctionConst3(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate3<t_ReturnType, t_Param0,t_Param1,t_Param2>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void call(void* a_pObject, argument::list* a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p0
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p1
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p2 );
    }
    virtual void call(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
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
    virtual void call(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) );
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
class TNativeInstanceMemberFunctionConst3<t_Ty, void, t_Param0, t_Param1, t_Param2> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInstanceMemberFunctionConst3<t_Ty, void, t_Param0, t_Param1, t_Param2>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;

    TNativeInstanceMemberFunctionConst3(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate3<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
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
class TNativeInstanceMemberFunctionConst4 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInstanceMemberFunctionConst4<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3) const;
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;

    TNativeInstanceMemberFunctionConst4(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate4<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void call(void* a_pObject, argument::list* a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p0
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p1
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p2
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p3 );
    }
    virtual void call(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
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
            , *static_cast<t_Param3_noref*>(a_pParams[3]) );
    }
    virtual void call(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) );
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
class TNativeInstanceMemberFunctionConst4<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInstanceMemberFunctionConst4<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;

    TNativeInstanceMemberFunctionConst4(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate4<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
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
class TNativeInstanceMemberFunctionConst5 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInstanceMemberFunctionConst5<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4) const;
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;

    TNativeInstanceMemberFunctionConst5(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate5<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
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
    virtual void call(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
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
    virtual void call(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) 
            , *static_cast<t_Param4_noref*>(a_pParams[4]) );
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
class TNativeInstanceMemberFunctionConst5<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInstanceMemberFunctionConst5<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;

    TNativeInstanceMemberFunctionConst5(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate5<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
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
class TNativeInstanceMemberFunctionConst6 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInstanceMemberFunctionConst6<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5) const;
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;

    TNativeInstanceMemberFunctionConst6(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate6<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
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
    virtual void call(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
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
    virtual void call(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) 
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) );
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
class TNativeInstanceMemberFunctionConst6<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInstanceMemberFunctionConst6<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;

    TNativeInstanceMemberFunctionConst6(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate6<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
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
class TNativeInstanceMemberFunctionConst7 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInstanceMemberFunctionConst7<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)const;
    typedef o_NESTED_TYPE boost::remove_cv<o_NESTED_TYPE boost::remove_reference<t_ReturnType>::type>::type t_ReturnType_no_cvr;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;

    TNativeInstanceMemberFunctionConst7(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate7<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
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
    virtual void call(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
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
        *reinterpret_cast<t_ReturnType_no_cvr*>(a_pReturnAddress) = (static_cast<t_Ty*>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) 
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6]) );
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
class TNativeInstanceMemberFunctionConst7<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInstanceMemberFunctionConst7<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;



    TNativeInstanceMemberFunctionConst7(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate7<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
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
class TNativeInstanceMemberFunctionConst8 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInstanceMemberFunctionConst8<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>    self_type;
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



    TNativeInstanceMemberFunctionConst8(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate8<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
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
    virtual void call(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
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
class TNativeInstanceMemberFunctionConst8<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInstanceMemberFunctionConst8<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;



    TNativeInstanceMemberFunctionConst8(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_Modifiers | o_native | o_const), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate8<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
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

protected:
    member_function_pointer m_member_function_pointer;
};


#ifndef o_NO_FUNCTION_STYLE_TEMPLATE_SIGNATURE

template<typename t_Ty, typename Signature>
class TNativeInstanceMemberFunctionConst;

template<typename t_Ty, typename t_ReturnType>
class TNativeInstanceMemberFunctionConst<t_Ty, t_ReturnType()> 
    : public TNativeInstanceMemberFunctionConst0<t_ReturnType, t_Ty>
{
public:
    typedef TNativeInstanceMemberFunctionConst<t_Ty, t_ReturnType()>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(void) const;
  

    TNativeInstanceMemberFunctionConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        :TNativeInstanceMemberFunctionConst0<t_ReturnType, t_Ty>(a_strName,a_pSignature, a_pFunc , a_Modifiers | o_native | o_const)
    {

    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeInstanceMemberFunctionConst<t_Ty, t_ReturnType(t_Param0)> 
    : public TNativeInstanceMemberFunctionConst1<t_ReturnType, t_Param0, t_Ty>
{
public:
    typedef TNativeInstanceMemberFunctionConst<t_Ty, t_ReturnType(t_Param0)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0) const;
    TNativeInstanceMemberFunctionConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        :TNativeInstanceMemberFunctionConst1<t_ReturnType, t_Param0, t_Ty>(a_strName,a_pSignature, a_pFunc , a_Modifiers | o_native | o_const)
    {

    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeInstanceMemberFunctionConst<t_Ty, t_ReturnType(t_Param0,t_Param1)> 
    : public TNativeInstanceMemberFunctionConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>
{
public:
    typedef TNativeInstanceMemberFunctionConst<t_Ty, t_ReturnType(t_Param0, t_Param1)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1) const;
  

    TNativeInstanceMemberFunctionConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        :TNativeInstanceMemberFunctionConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>(a_strName,a_pSignature, a_pFunc , a_Modifiers | o_native | o_const)
    {

    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }

};


template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2>
class TNativeInstanceMemberFunctionConst<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2)> 
    : public TNativeInstanceMemberFunctionConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    typedef TNativeInstanceMemberFunctionConst<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2) const;
  

    TNativeInstanceMemberFunctionConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        :TNativeInstanceMemberFunctionConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>(a_strName,a_pSignature, a_pFunc , a_Modifiers | o_native | o_const)
    {

    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }

};


template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeInstanceMemberFunctionConst<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3)> 
    : public TNativeInstanceMemberFunctionConst4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    typedef TNativeInstanceMemberFunctionConst<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3) const;
  

    TNativeInstanceMemberFunctionConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        :TNativeInstanceMemberFunctionConst4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>(a_strName,a_pSignature, a_pFunc , a_Modifiers | o_native | o_const)
    {

    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }

};

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeInstanceMemberFunctionConst<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4)> 
    : public TNativeInstanceMemberFunctionConst5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>
{
public:
    typedef TNativeInstanceMemberFunctionConst<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4) const;
  

    TNativeInstanceMemberFunctionConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        :TNativeInstanceMemberFunctionConst5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>(a_strName,a_pSignature, a_pFunc , a_Modifiers | o_native | o_const)
    {

    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }

};

template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeInstanceMemberFunctionConst<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)> : public TNativeInstanceMemberFunctionConst6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>
{
public:
    typedef TNativeInstanceMemberFunctionConst<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5) const;
  

    TNativeInstanceMemberFunctionConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        :TNativeInstanceMemberFunctionConst6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>(a_strName,a_pSignature, a_pFunc , a_Modifiers | o_native | o_const)
    {

    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }

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
class TNativeInstanceMemberFunctionConst<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)> : public TNativeInstanceMemberFunctionConst7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>
{
public:
    typedef TNativeInstanceMemberFunctionConst<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6) const;
  

    TNativeInstanceMemberFunctionConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        :TNativeInstanceMemberFunctionConst7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>(a_strName,a_pSignature, a_pFunc , a_Modifiers | o_native | o_const)
    {

    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }

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
class TNativeInstanceMemberFunctionConst<t_Ty, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)> : public TNativeInstanceMemberFunctionConst8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>
{
public:
    typedef TNativeInstanceMemberFunctionConst<t_Ty, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7) const;
  

    TNativeInstanceMemberFunctionConst(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_Modifiers = 0)
        :TNativeInstanceMemberFunctionConst8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(a_strName,a_pSignature, a_pFunc , a_Modifiers | o_native | o_const)
    {

    }
    virtual void            deleteNow() { o_dynamic_proxy_delete(phantom::reflection::InstanceMemberFunction, phantom::reflection::InstanceMemberFunction::metaType, self_type) this; }

};

#endif

o_namespace_end(phantom, reflection, native)

    //o_traits_specialize_all_super_traitNTS_TNativeMemberFunctionRTXXX(TNativeInstanceMemberFunctionConst)

#endif // reflection_native_TNativeInstanceMemberFunctionConst_h__