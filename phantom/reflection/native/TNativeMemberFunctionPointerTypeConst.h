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

#ifndef o_phantom_reflection_native_TNativeMemberFunctionPointerTypeConst_h__
#define o_phantom_reflection_native_TNativeMemberFunctionPointerTypeConst_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

#define TNativeMemberFunctionPointerTypeConstBase TNativeMemberFunctionPointerTypeBase

o_namespace_begin(phantom, reflection, native)

template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunctionPointerTypeConst0 : public TNativeMemberFunctionPointerTypeBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionPointerTypeConst0<t_Ty, t_ReturnType> self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer_t)(void) const;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
  

    TNativeMemberFunctionPointerTypeConst0(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionPointerTypeBase<t_Ty>( a_pSignature, sizeof(member_function_pointer_t), boost::alignment_of<member_function_pointer_t>::value,a_Modifiers | o_native | o_const)
    {
        
    }

    virtual void*           getClosure(void* a_pPointer) const { return generic_member_func_ptr(*static_cast<member_function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer, void* a_pObject) const
    {
        return FastDelegate0<t_ReturnType>(reinterpret_cast<t_Ty*>(a_pObject), *static_cast<member_function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams) const 
    {
        ((static_cast<t_Ty*>(a_pObject))->*(*static_cast<member_function_pointer_t*>(a_pPointer)))();
    }

    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<return_storage_type*>(a_pReturnAddress) 
            = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))());
    }

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))());
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    
    
};


template<typename t_Ty>
class TNativeMemberFunctionPointerTypeConst0<t_Ty, void> : public TNativeMemberFunctionPointerTypeBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionPointerTypeConst0<t_Ty, void>    self_type;
    typedef void (t_Ty::*member_function_pointer_t)(void) const;
  

    TNativeMemberFunctionPointerTypeConst0(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionPointerTypeBase<t_Ty>( a_pSignature, sizeof(member_function_pointer_t), boost::alignment_of<member_function_pointer_t>::value,a_Modifiers | o_native | o_const)
    {
        
    }
    virtual void*           getClosure(void* a_pPointer) const { return generic_member_func_ptr(*static_cast<member_function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer, void* a_pObject) const
    {
        return FastDelegate0<fastdelegate::detail::DefaultVoid>(reinterpret_cast<t_Ty*>(a_pObject), *static_cast<member_function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams) const 
    {
        ((static_cast<t_Ty*>(a_pObject))->*(*static_cast<member_function_pointer_t*>(a_pPointer)))();
    }

protected:
    

};


template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionPointerTypeConst1 : public TNativeMemberFunctionPointerTypeBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionPointerTypeConst1<t_Ty, t_ReturnType, t_Param0>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer_t)(t_Param0) const;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;

    TNativeMemberFunctionPointerTypeConst1(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionPointerTypeBase<t_Ty>( a_pSignature, sizeof(member_function_pointer_t), boost::alignment_of<member_function_pointer_t>::value,a_Modifiers | o_native | o_const)
    {
        
    }

    virtual void*           getClosure(void* a_pPointer) const { return generic_member_func_ptr(*static_cast<member_function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer, void* a_pObject) const
    {
        return FastDelegate1<t_ReturnType, t_Param0>(reinterpret_cast<t_Ty*>(a_pObject), *static_cast<member_function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) );
    }

    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) ));
    }

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            (*static_cast<t_Param0_noref*>(a_pParams[0])));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    
};


template<typename t_Ty, typename t_Param0>
class TNativeMemberFunctionPointerTypeConst1<t_Ty, void, t_Param0> : public TNativeMemberFunctionPointerTypeBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionPointerTypeConst1<t_Ty, void, t_Param0>    self_type;
    typedef void (t_Ty::*member_function_pointer_t)(t_Param0) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;

    TNativeMemberFunctionPointerTypeConst1(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionPointerTypeBase<t_Ty>(TNativeSignatureProvider1<void,t_Param1>::CreateSignature(o_const), sizeof(member_function_pointer_t), boost::alignment_of<member_function_pointer_t>::value,a_Modifiers | o_native | o_const)
    {
        
    }

    virtual void*           getClosure(void* a_pPointer) const { return generic_member_func_ptr(*static_cast<member_function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer, void* a_pObject) const
    {
        return FastDelegate1<fastdelegate::detail::DefaultVoid, t_Param0>(reinterpret_cast<t_Ty*>(a_pObject), *static_cast<member_function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) );
    }


protected:
    
};


template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionPointerTypeConst2 : public TNativeMemberFunctionPointerTypeBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionPointerTypeConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1) const;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    
    TNativeMemberFunctionPointerTypeConst2(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        :TNativeMemberFunctionPointerTypeBase<t_Ty>( a_pSignature, sizeof(member_function_pointer_t), boost::alignment_of<member_function_pointer_t>::value,a_Modifiers | o_native | o_const)
    {
        
    }
    virtual void*           getClosure(void* a_pPointer) const { return generic_member_func_ptr(*static_cast<member_function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer, void* a_pObject) const
    {
        return FastDelegate2<t_ReturnType, t_Param0, t_Param1>(reinterpret_cast<t_Ty*>(a_pObject), *static_cast<member_function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) );
    }
    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) ));
    }

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) ));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    
    
};

template<typename t_Ty, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionPointerTypeConst2<t_Ty, void, t_Param0, t_Param1> : public TNativeMemberFunctionPointerTypeBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionPointerTypeConst2<t_Ty, void, t_Param0, t_Param1>    self_type;
    typedef void (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;

    TNativeMemberFunctionPointerTypeConst2(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionPointerTypeBase<t_Ty>( a_pSignature, sizeof(member_function_pointer_t), boost::alignment_of<member_function_pointer_t>::value,a_Modifiers | o_native | o_const)
    {
        
    }
    virtual void*           getClosure(void* a_pPointer) const { return generic_member_func_ptr(*static_cast<member_function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer, void* a_pObject) const
    {
        return FastDelegate2<fastdelegate::detail::DefaultVoid, t_Param0, t_Param1>(reinterpret_cast<t_Ty*>(a_pObject), *static_cast<member_function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) );
    }


protected:
    
};




///  ==================================================================================================
///        3 PARAMETERS
///  ==================================================================================================

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunctionPointerTypeConst3 : public TNativeMemberFunctionPointerTypeBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionPointerTypeConst3<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1,t_Param2) const;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;

    TNativeMemberFunctionPointerTypeConst3(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionPointerTypeBase<t_Ty>( a_pSignature, sizeof(member_function_pointer_t), boost::alignment_of<member_function_pointer_t>::value,a_Modifiers | o_native | o_const)
    {
        
    }
    virtual void*           getClosure(void* a_pPointer) const { return generic_member_func_ptr(*static_cast<member_function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer, void* a_pObject) const
    {
        return FastDelegate3<t_ReturnType, t_Param0,t_Param1,t_Param2>(static_cast<t_Ty*>(a_pObject), *static_cast<member_function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) );
    }
    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) ));
    }

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) ));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    

};

template<typename t_Ty, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunctionPointerTypeConst3<t_Ty, void, t_Param0, t_Param1, t_Param2> : public TNativeMemberFunctionPointerTypeBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionPointerTypeConst3<t_Ty, void, t_Param0, t_Param1, t_Param2>    self_type;
    typedef void (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1,t_Param2) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;

    TNativeMemberFunctionPointerTypeConst3(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionPointerTypeBase<t_Ty>( a_pSignature, sizeof(member_function_pointer_t), boost::alignment_of<member_function_pointer_t>::value,a_Modifiers | o_native | o_const)
    {
        
    }
    virtual void*           getClosure(void* a_pPointer) const { return generic_member_func_ptr(*static_cast<member_function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer, void* a_pObject) const
    {
        return FastDelegate3<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2>(static_cast<t_Ty*>(a_pObject), *static_cast<member_function_pointer_t*>(a_pPointer)).GetMemento();
    }
    
    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) );
    }

protected:
    
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
class TNativeMemberFunctionPointerTypeConst4 : public TNativeMemberFunctionPointerTypeBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionPointerTypeConst4<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1,t_Param2,t_Param3) const;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;

    TNativeMemberFunctionPointerTypeConst4(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionPointerTypeBase<t_Ty>( a_pSignature, sizeof(member_function_pointer_t), boost::alignment_of<member_function_pointer_t>::value,a_Modifiers | o_native | o_const)
    {
        
    }
    virtual void*           getClosure(void* a_pPointer) const { return generic_member_func_ptr(*static_cast<member_function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer, void* a_pObject) const
    {
        return FastDelegate4<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3>(static_cast<t_Ty*>(a_pObject), *static_cast<member_function_pointer_t*>(a_pPointer)).GetMemento();
    }
    
    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) );
    }
    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) ));
    }

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) ));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    

};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeMemberFunctionPointerTypeConst4<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3> : public TNativeMemberFunctionPointerTypeBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionPointerTypeConst4<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3>    self_type;
    typedef void (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1,t_Param2,t_Param3) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;

    TNativeMemberFunctionPointerTypeConst4(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionPointerTypeBase<t_Ty>( a_pSignature, sizeof(member_function_pointer_t), boost::alignment_of<member_function_pointer_t>::value,a_Modifiers | o_native | o_const)
    {
        
    }
    virtual void*           getClosure(void* a_pPointer) const { return generic_member_func_ptr(*static_cast<member_function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer, void* a_pObject) const
    {
        return FastDelegate4<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3>(static_cast<t_Ty*>(a_pObject), *static_cast<member_function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) );
    }


protected:
    
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
class TNativeMemberFunctionPointerTypeConst5 : public TNativeMemberFunctionPointerTypeBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionPointerTypeConst5<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4) const;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;

    TNativeMemberFunctionPointerTypeConst5(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionPointerTypeBase<t_Ty>( a_pSignature, sizeof(member_function_pointer_t), boost::alignment_of<member_function_pointer_t>::value,a_Modifiers | o_native | o_const)
    {
        
    }
    virtual void*           getClosure(void* a_pPointer) const { return generic_member_func_ptr(*static_cast<member_function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer, void* a_pObject) const
    {
        return FastDelegate5<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(static_cast<t_Ty*>(a_pObject), *static_cast<member_function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4]) );
    }
    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) 
            , *static_cast<t_Param4_noref*>(a_pParams[4]) ));
    }

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) 
            , *static_cast<t_Param4_noref*>(a_pParams[4]) ));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    

};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeMemberFunctionPointerTypeConst5<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4> : public TNativeMemberFunctionPointerTypeBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionPointerTypeConst5<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>    self_type;
    typedef void (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;

    TNativeMemberFunctionPointerTypeConst5(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionPointerTypeBase<t_Ty>( a_pSignature, sizeof(member_function_pointer_t), boost::alignment_of<member_function_pointer_t>::value,a_Modifiers | o_native | o_const)
    {
        
    }
    virtual void*           getClosure(void* a_pPointer) const { return generic_member_func_ptr(*static_cast<member_function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer, void* a_pObject) const
    {
        return FastDelegate5<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(static_cast<t_Ty*>(a_pObject), *static_cast<member_function_pointer_t*>(a_pPointer)).GetMemento();
    }
    
    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4]) );
    }


protected:
    
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
class TNativeMemberFunctionPointerTypeConst6 : public TNativeMemberFunctionPointerTypeBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionPointerTypeConst6<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5) const;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;

    TNativeMemberFunctionPointerTypeConst6(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionPointerTypeBase<t_Ty>( a_pSignature, sizeof(member_function_pointer_t), boost::alignment_of<member_function_pointer_t>::value,a_Modifiers | o_native | o_const)
    {
        
    }
    virtual void*           getClosure(void* a_pPointer) const { return generic_member_func_ptr(*static_cast<member_function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer, void* a_pObject) const
    {
        return FastDelegate6<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(static_cast<t_Ty*>(a_pObject), *static_cast<member_function_pointer_t*>(a_pPointer)).GetMemento();
    }
    
    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) );
    }
    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) 
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) ));
    }

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) 
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) ));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    

};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeMemberFunctionPointerTypeConst6<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5> : public TNativeMemberFunctionPointerTypeBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionPointerTypeConst6<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>    self_type;
    typedef void (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;

    TNativeMemberFunctionPointerTypeConst6(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionPointerTypeBase<t_Ty>( a_pSignature, sizeof(member_function_pointer_t), boost::alignment_of<member_function_pointer_t>::value,a_Modifiers | o_native | o_const)
    {
        
    }
    virtual void*           getClosure(void* a_pPointer) const { return generic_member_func_ptr(*static_cast<member_function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer, void* a_pObject) const
    {
        return FastDelegate6<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(static_cast<t_Ty*>(a_pObject), *static_cast<member_function_pointer_t*>(a_pPointer)).GetMemento();
    }
    
    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) );
    }

protected:
    
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
class TNativeMemberFunctionPointerTypeConst7 : public TNativeMemberFunctionPointerTypeBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionPointerTypeConst7<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)const;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;

    TNativeMemberFunctionPointerTypeConst7(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionPointerTypeBase<t_Ty>( a_pSignature, sizeof(member_function_pointer_t), boost::alignment_of<member_function_pointer_t>::value,a_Modifiers | o_native | o_const)
    {
        
    }
    virtual void*           getClosure(void* a_pPointer) const { return generic_member_func_ptr(*static_cast<member_function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer, void* a_pObject) const
    {
        return FastDelegate7<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(static_cast<t_Ty*>(a_pObject), *static_cast<member_function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6]) );
    }
    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) 
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6]) ));
    }

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
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
    

};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6>
class TNativeMemberFunctionPointerTypeConst7<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6> : public TNativeMemberFunctionPointerTypeBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionPointerTypeConst7<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>    self_type;
    typedef void (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;



    TNativeMemberFunctionPointerTypeConst7(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionPointerTypeBase<t_Ty>( a_pSignature, sizeof(member_function_pointer_t), boost::alignment_of<member_function_pointer_t>::value,a_Modifiers | o_native | o_const)
    {
        
    }
    virtual void*           getClosure(void* a_pPointer) const { return generic_member_func_ptr(*static_cast<member_function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer, void* a_pObject) const
    {
        return FastDelegate7<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(static_cast<t_Ty*>(a_pObject), *static_cast<member_function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6]) );
    }

protected:
    
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
class TNativeMemberFunctionPointerTypeConst8 : public TNativeMemberFunctionPointerTypeBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionPointerTypeConst8<t_Ty, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7) const;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;



    TNativeMemberFunctionPointerTypeConst8(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionPointerTypeBase<t_Ty>( a_pSignature, sizeof(member_function_pointer_t), boost::alignment_of<member_function_pointer_t>::value,a_Modifiers | o_native | o_const)
    {
        
    }
    virtual void*           getClosure(void* a_pPointer) const { return generic_member_func_ptr(*static_cast<member_function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer, void* a_pObject) const
    {
        return FastDelegate8<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(static_cast<t_Ty*>(a_pObject), *static_cast<member_function_pointer_t*>(a_pPointer)).GetMemento();
    }
    
    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7]) );
    }
    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams, void* a_pReturnAddress) const 
    {
        *reinterpret_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) 
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7]) ));
    }

    virtual void* getAddress(void* a_pObject, void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
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
class TNativeMemberFunctionPointerTypeConst8<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7> : public TNativeMemberFunctionPointerTypeBase<t_Ty>
{
public:
    typedef TNativeMemberFunctionPointerTypeConst8<t_Ty, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>    self_type;
    typedef void (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7) const;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;



    TNativeMemberFunctionPointerTypeConst8(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : TNativeMemberFunctionPointerTypeBase<t_Ty>( a_pSignature, sizeof(member_function_pointer_t), boost::alignment_of<member_function_pointer_t>::value,a_Modifiers | o_native | o_const)
    {
        
    }
    virtual void*           getClosure(void* a_pPointer) const { return generic_member_func_ptr(*static_cast<member_function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer, void* a_pObject) const
    {
        return FastDelegate8<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(static_cast<t_Ty*>(a_pObject), *static_cast<member_function_pointer_t*>(a_pPointer)).GetMemento();
    }
    
    virtual void call(void* a_pPointer, void* a_pObject, void** a_pParams) const 
    {        
        (static_cast<t_Ty*>(a_pObject)->*(*static_cast<member_function_pointer_t*>(a_pPointer)))
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
    
};


template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunctionPointerType<t_ReturnType(t_Ty::*)() const> 
    : public TNativeMemberFunctionPointerTypeConst0<t_ReturnType, t_Ty>
{
public:
    typedef TNativeMemberFunctionPointerType<t_ReturnType(t_Ty::*)() const>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer_t)(void) const;
  

    TNativeMemberFunctionPointerType()
        :TNativeMemberFunctionPointerTypeConst0<t_ReturnType, t_Ty>(TNativeSignatureProvider<t_ReturnType()>::CreateSignature(o_const), o_native | o_const)
    {

    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionPointerType<t_ReturnType (t_Ty::*)(t_Param0) const> 
    : public TNativeMemberFunctionPointerTypeConst1<t_ReturnType, t_Param0, t_Ty>
{
public:
    typedef TNativeMemberFunctionPointerType<t_ReturnType (t_Ty::*)(t_Param0) const>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer_t)(t_Param0) const;
    TNativeMemberFunctionPointerType()
        :TNativeMemberFunctionPointerTypeConst1<t_ReturnType, t_Param0, t_Ty>(TNativeSignatureProvider<t_ReturnType (t_Param0)>::CreateSignature(o_const), o_native | o_const)
    {

    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionPointerType<t_ReturnType (t_Ty::*)(t_Param0,t_Param1) const> 
    : public TNativeMemberFunctionPointerTypeConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>
{
public:
    typedef TNativeMemberFunctionPointerType<t_ReturnType (t_Ty::*)(t_Param0, t_Param1) const>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1) const;
  

    TNativeMemberFunctionPointerType()
        :TNativeMemberFunctionPointerTypeConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>(TNativeSignatureProvider<t_ReturnType (t_Param0, t_Param1)>::CreateSignature(o_const), o_native | o_const)
    {

    }

};


template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2>
class TNativeMemberFunctionPointerType<t_ReturnType (t_Ty::*)(t_Param0,t_Param1,t_Param2) const> 
    : public TNativeMemberFunctionPointerTypeConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    typedef TNativeMemberFunctionPointerType<t_ReturnType (t_Ty::*)(t_Param0, t_Param1, t_Param2) const>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1,t_Param2) const;
  

    TNativeMemberFunctionPointerType()
        :TNativeMemberFunctionPointerTypeConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>(TNativeSignatureProvider<t_ReturnType (t_Param0, t_Param1, t_Param2)>::CreateSignature(o_const), o_native | o_const)
    {

    }

};


template<typename t_Ty
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeMemberFunctionPointerType<t_ReturnType (t_Ty::*)(t_Param0,t_Param1,t_Param2,t_Param3) const> 
    : public TNativeMemberFunctionPointerTypeConst4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    typedef TNativeMemberFunctionPointerType<t_ReturnType (t_Ty::*)(t_Param0, t_Param1, t_Param2,t_Param3) const>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1,t_Param2,t_Param3) const;
  

    TNativeMemberFunctionPointerType()
        :TNativeMemberFunctionPointerTypeConst4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>(TNativeSignatureProvider<t_ReturnType (t_Param0, t_Param1, t_Param2, t_Param3)>::CreateSignature(o_const), o_native | o_const)
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
class TNativeMemberFunctionPointerType<t_ReturnType (t_Ty::*)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4) const> 
    : public TNativeMemberFunctionPointerTypeConst5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>
{
public:
    typedef TNativeMemberFunctionPointerType<t_ReturnType (t_Ty::*)(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4) const>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4) const;
  

    TNativeMemberFunctionPointerType()
        :TNativeMemberFunctionPointerTypeConst5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>(TNativeSignatureProvider<t_ReturnType (t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)>::CreateSignature(o_const), o_native | o_const)
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
class TNativeMemberFunctionPointerType<t_ReturnType (t_Ty::*)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5) const> : public TNativeMemberFunctionPointerTypeConst6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>
{
public:
    typedef TNativeMemberFunctionPointerType<t_ReturnType (t_Ty::*)(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5) const>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5) const;
  

    TNativeMemberFunctionPointerType()
        :TNativeMemberFunctionPointerTypeConst6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>(TNativeSignatureProvider<t_ReturnType (t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)>::CreateSignature(o_const), o_native | o_const)
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
class TNativeMemberFunctionPointerType<t_ReturnType (t_Ty::*)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6) const> : public TNativeMemberFunctionPointerTypeConst7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>
{
public:
    typedef TNativeMemberFunctionPointerType<t_ReturnType (t_Ty::*)(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6) const>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6) const;
  

    TNativeMemberFunctionPointerType()
        :TNativeMemberFunctionPointerTypeConst7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>(TNativeSignatureProvider<t_ReturnType (t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)>::CreateSignature(o_const), o_native | o_const)
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
class TNativeMemberFunctionPointerType<t_ReturnType (t_Ty::*)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7) const> : public TNativeMemberFunctionPointerTypeConst8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>
{
public:
    typedef TNativeMemberFunctionPointerType<t_ReturnType (t_Ty::*)(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7) const>    self_type;
    typedef t_ReturnType (t_Ty::*member_function_pointer_t)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7) const;
  

    TNativeMemberFunctionPointerType()
        :TNativeMemberFunctionPointerTypeConst8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(TNativeSignatureProvider<t_ReturnType (t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)>::CreateSignature(o_const), o_native | o_const)
    {

    }

};

o_namespace_end(phantom, reflection, native)

#endif // reflection_native_TNativeMemberFunctionPointerTypeConst_h__