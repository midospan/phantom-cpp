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

#ifndef o_phantom_reflection_native_TNativeInterfaceMemberFunction_h__
#define o_phantom_reflection_native_TNativeInterfaceMemberFunction_h__



/* ****************** Includes ******************* */
/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)

template<typename t_Ty, typename _ReturnType>
class TNativeInterfaceMemberFunction0 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef _ReturnType (t_Ty::*member_function_pointer)(void);
    typedef TNativeInterfaceMemberFunction0<t_Ty, _ReturnType> self_type;

    TNativeInterfaceMemberFunction0(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_interface | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }

    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate<_ReturnType()>(phantom::polymorphic_cast<t_Ty>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void                    deleteNow() { o_delete(self_type) this; }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)();
    }

    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) 
            = (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)();
    }
    
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)();
    }

    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) 
            = (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)();
    }

protected:
    member_function_pointer m_member_function_pointer;

};


template<typename t_Ty>
class TNativeInterfaceMemberFunction0<t_Ty, void> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunction0<t_Ty, void>    self_type;
    typedef void (t_Ty::*member_function_pointer)(void);

    TNativeInterfaceMemberFunction0(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_interface | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate0<fastdelegate::detail::DefaultVoid>(phantom::polymorphic_cast<t_Ty>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)();
    }

    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)();
    }

    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;

};


template<typename t_Ty, typename _ReturnType, typename t_Param0>
class TNativeInterfaceMemberFunction1 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunction1<t_Ty, _ReturnType, t_Param0>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0);

    TNativeInterfaceMemberFunction1(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_interface | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }

    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate1<_ReturnType, t_Param0>(phantom::polymorphic_cast<t_Ty>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            (static_cast<argument::list_1<t_Param0>*>(a_pParams)->p0);
    }

    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    { 
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) 
            = (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            (static_cast<argument::list_1<t_Param0>*>(a_pParams)->p0);
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = 
            (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0]) );
    }

protected:
    member_function_pointer m_member_function_pointer;
};


template<typename t_Ty, typename t_Param0>
class TNativeInterfaceMemberFunction1<t_Ty, void, t_Param0> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunction1<t_Ty, void, t_Param0>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0);

    TNativeInterfaceMemberFunction1(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_interface | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }

    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate1<fastdelegate::detail::DefaultVoid, t_Param0>(phantom::polymorphic_cast<t_Ty>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            (static_cast<argument::list_1<t_Param0>*>(a_pParams)->p0);
    }

    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;
};


template<typename t_Ty, typename _ReturnType, typename t_Param0, typename t_Param1>
class TNativeInterfaceMemberFunction2 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunction2<t_Ty, _ReturnType, t_Param0, t_Param1>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1);

    TNativeInterfaceMemberFunction2(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_interface | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate2<_ReturnType, t_Param0, t_Param1>(phantom::polymorphic_cast<t_Ty>(a_pObject), m_member_function_pointer).GetMemento();
    }

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p0
            , static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p1 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p0
            , static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p1 );
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = 
            (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1]) );
    }



protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty, typename t_Param0, typename t_Param1>
class TNativeInterfaceMemberFunction2<t_Ty, void, t_Param0, t_Param1> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunction2<t_Ty, void, t_Param0, t_Param1>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1);

    TNativeInterfaceMemberFunction2(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_interface | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate2<fastdelegate::detail::DefaultVoid, t_Param0, t_Param1>(phantom::polymorphic_cast<t_Ty>(a_pObject), m_member_function_pointer).GetMemento();
    }
    
    
    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p0
            , static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p1 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;
};


///  ==================================================================================================
///        3 PARAMETERS
///  ==================================================================================================

template<typename t_Ty, typename _ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeInterfaceMemberFunction3 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunction3<t_Ty, _ReturnType, t_Param0, t_Param1,t_Param2>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2);

    TNativeInterfaceMemberFunction3(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate3<_ReturnType, t_Param0,t_Param1,t_Param2>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p0
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p1
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p2 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p0
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p1
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p2 );
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = 
            (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2]) );
    }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeInterfaceMemberFunction3<t_Ty, void, t_Param0, t_Param1, t_Param2> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunction3<t_Ty, void, t_Param0, t_Param1, t_Param2>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2);

    TNativeInterfaceMemberFunction3(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate3<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p0
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p1
            , static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p2 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;
};



///  ==================================================================================================
///        4 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeInterfaceMemberFunction4 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunction4<t_Ty, _ReturnType, t_Param0, t_Param1,t_Param2,t_Param3>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3);

    TNativeInterfaceMemberFunction4(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate4<_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p0
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p1
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p2
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p3 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p0
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p1
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p2
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p3 );
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = 
            (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3]) );
    }

protected:
    member_function_pointer m_member_function_pointer;

};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeInterfaceMemberFunction4<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunction4<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3);

    TNativeInterfaceMemberFunction4(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate4<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p0
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p1
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p2
            , static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p3 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;
};


///  ==================================================================================================
///        5 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeInterfaceMemberFunction5 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunction5<t_Ty, _ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4);

    TNativeInterfaceMemberFunction5(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate5<_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p0
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p1
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p2
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p3
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p4 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p0
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p1
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p2
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p3
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p4 );
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3])
            , *static_cast<t_Param4*>(a_pParams[4]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = 
            (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3]) 
            , *static_cast<t_Param4*>(a_pParams[4]) );
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
class TNativeInterfaceMemberFunction5<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunction5<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4);

    TNativeInterfaceMemberFunction5(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate5<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p0
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p1
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p2
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p3
            , static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p4 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }
    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3])
            , *static_cast<t_Param4*>(a_pParams[4]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;
};





///  ==================================================================================================
///        6 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeInterfaceMemberFunction6 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunction6<t_Ty, _ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5);

    TNativeInterfaceMemberFunction6(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate6<_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p0
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p1
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p2
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p3
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p4
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p5 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p0
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p1
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p2
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p3
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p4
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p5 );
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3])
            , *static_cast<t_Param4*>(a_pParams[4])
            , *static_cast<t_Param5*>(a_pParams[5]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = 
            (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3]) 
            , *static_cast<t_Param4*>(a_pParams[4])
            , *static_cast<t_Param5*>(a_pParams[5]) );
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
class TNativeInterfaceMemberFunction6<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunction6<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5);

    TNativeInterfaceMemberFunction6(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate6<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p0
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p1
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p2
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p3
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p4
            , static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p5 );
    }
    virtual void invoke(void* a_pObject, argument::list* a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3])
            , *static_cast<t_Param4*>(a_pParams[4])
            , *static_cast<t_Param5*>(a_pParams[5]));
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;
};





///  ==================================================================================================
///        7 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6>
class TNativeInterfaceMemberFunction7 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunction7<t_Ty, _ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6);

    TNativeInterfaceMemberFunction7(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate7<_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
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
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
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
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3])
            , *static_cast<t_Param4*>(a_pParams[4])
            , *static_cast<t_Param5*>(a_pParams[5])
            , *static_cast<t_Param6*>(a_pParams[6]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = 
            (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3]) 
            , *static_cast<t_Param4*>(a_pParams[4])
            , *static_cast<t_Param5*>(a_pParams[5])
            , *static_cast<t_Param6*>(a_pParams[6]) );
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
class TNativeInterfaceMemberFunction7<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunction7<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6);

    TNativeInterfaceMemberFunction7(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate7<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
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
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3])
            , *static_cast<t_Param4*>(a_pParams[4])
            , *static_cast<t_Param5*>(a_pParams[5])
            , *static_cast<t_Param6*>(a_pParams[6]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;
};



///  ==================================================================================================
///        8 PARAMETERS
///  ==================================================================================================

template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7>
class TNativeInterfaceMemberFunction8 : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunction8<t_Ty, _ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7);

    TNativeInterfaceMemberFunction8(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate8<_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
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
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
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
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3])
            , *static_cast<t_Param4*>(a_pParams[4])
            , *static_cast<t_Param5*>(a_pParams[5])
            , *static_cast<t_Param6*>(a_pParams[6])
            , *static_cast<t_Param7*>(a_pParams[7]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<_ReturnType*>(a_pReturnAddress) = 
            (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3]) 
            , *static_cast<t_Param4*>(a_pParams[4])
            , *static_cast<t_Param5*>(a_pParams[5])
            , *static_cast<t_Param6*>(a_pParams[6])
            , *static_cast<t_Param7*>(a_pParams[7]) );
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
class TNativeInterfaceMemberFunction8<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7> : public TNativeInstanceMemberFunctionBase<t_Ty>
{
public:
    typedef TNativeInterfaceMemberFunction8<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>    self_type;
    typedef void (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7);

    TNativeInterfaceMemberFunction8(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        : TNativeInstanceMemberFunctionBase<t_Ty>(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
    {
        if(this->isVirtual()) this->setVirtualTableIndex(phantom::virtualMemberFunctionIndexOf(a_pFunc));
    }
    virtual void            deleteNow() { o_delete(self_type) this; }
    virtual generic_member_func_ptr           getGenericMemberFunctionPointer() const { return m_member_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate8<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(static_cast<t_Ty*>(a_pObject), m_member_function_pointer).GetMemento();
    }
    

    virtual void invoke(void* a_pObject, argument::list* a_pParams) const 
    {
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
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
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

    virtual void invoke(void* a_pObject, void** a_pParams) const 
    {        
        (phantom::polymorphic_cast<t_Ty>(a_pObject)->*m_member_function_pointer)
            ( *static_cast<t_Param0*>(a_pParams[0])
            , *static_cast<t_Param1*>(a_pParams[1])
            , *static_cast<t_Param2*>(a_pParams[2])
            , *static_cast<t_Param3*>(a_pParams[3])
            , *static_cast<t_Param4*>(a_pParams[4])
            , *static_cast<t_Param5*>(a_pParams[5])
            , *static_cast<t_Param6*>(a_pParams[6])
            , *static_cast<t_Param7*>(a_pParams[7]) );
    }
    virtual void invoke(void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        throw exception::reflection_runtime_exception("void member_function called with expected return result");
    }

protected:
    member_function_pointer m_member_function_pointer;
};

#ifndef o_NO_FUNCTION_STYLE_TEMPLATE_SIGNATURE

template<typename t_Ty, typename Signature>
class TNativeInterfaceMemberFunction;

template<typename t_Ty, typename _ReturnType>
class TNativeInterfaceMemberFunction<t_Ty, _ReturnType()> : public TNativeInterfaceMemberFunction0< t_Ty, _ReturnType>
{
public:
    typedef TNativeInterfaceMemberFunction<t_Ty, _ReturnType()>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(void);
    TNativeInterfaceMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInterfaceMemberFunction0< t_Ty, _ReturnType>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }
};

template<typename t_Ty, typename _ReturnType, typename t_Param0>
class TNativeInterfaceMemberFunction<t_Ty, _ReturnType(t_Param0)> : public TNativeInterfaceMemberFunction1<t_Ty, _ReturnType, t_Param0>
{
public:
    typedef TNativeInterfaceMemberFunction<t_Ty, _ReturnType(t_Param0)>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0);
    TNativeInterfaceMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInterfaceMemberFunction1<t_Ty, _ReturnType, t_Param0>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }
};

template<typename t_Ty, typename _ReturnType, typename t_Param0, typename t_Param1>
class TNativeInterfaceMemberFunction<t_Ty, _ReturnType(t_Param0,t_Param1)> : public TNativeInterfaceMemberFunction2<t_Ty, _ReturnType, t_Param0, t_Param1>
{
public:
    typedef TNativeInterfaceMemberFunction<t_Ty, _ReturnType(t_Param0, t_Param1)>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1);
    TNativeInterfaceMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInterfaceMemberFunction2<t_Ty, _ReturnType, t_Param0, t_Param1>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};

template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2>
class TNativeInterfaceMemberFunction<t_Ty, _ReturnType(t_Param0,t_Param1,t_Param2)> 
    : public TNativeInterfaceMemberFunction3<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    typedef TNativeInterfaceMemberFunction<t_Ty, _ReturnType(t_Param0, t_Param1, t_Param2)>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2);
    TNativeInterfaceMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInterfaceMemberFunction3<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};


template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeInterfaceMemberFunction<t_Ty, _ReturnType(t_Param0,t_Param1,t_Param2,t_Param3)> 
    : public TNativeInterfaceMemberFunction4<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    typedef TNativeInterfaceMemberFunction<t_Ty, _ReturnType(t_Param0, t_Param1, t_Param2,t_Param3)>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3);
    TNativeInterfaceMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInterfaceMemberFunction4<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};

template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeInterfaceMemberFunction<t_Ty, _ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4)> 
    : public TNativeInterfaceMemberFunction5<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>
{
public:
    typedef TNativeInterfaceMemberFunction<t_Ty, _ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4)>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4);
    TNativeInterfaceMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInterfaceMemberFunction5<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};

template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeInterfaceMemberFunction<t_Ty, _ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)> 
    : public TNativeInterfaceMemberFunction6<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>
{
public:
    typedef TNativeInterfaceMemberFunction<t_Ty, _ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5)>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5);
    TNativeInterfaceMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInterfaceMemberFunction6<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};

template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6>
class TNativeInterfaceMemberFunction<t_Ty, _ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)> 
    : public TNativeInterfaceMemberFunction7<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>
{
public:
    typedef TNativeInterfaceMemberFunction<t_Ty, _ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6);
    TNativeInterfaceMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInterfaceMemberFunction7<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};


template<typename t_Ty
    , typename _ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7>
class TNativeInterfaceMemberFunction<t_Ty, _ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)> : public TNativeInterfaceMemberFunction8<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>
{
public:
    typedef TNativeInterfaceMemberFunction<t_Ty, _ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)>    self_type;
    typedef _ReturnType (t_Ty::*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7);
    TNativeInterfaceMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
        :TNativeInterfaceMemberFunction8<t_Ty, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
    {

    }
    virtual void            deleteNow() { o_delete(self_type) this; }

};

#endif

o_namespace_end(phantom, reflection, native)


#endif // TNativeInterfaceMemberFunction_h__