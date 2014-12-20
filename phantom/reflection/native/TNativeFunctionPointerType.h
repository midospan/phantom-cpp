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

#ifndef o_phantom_reflection_TNativeFunctionPointerType_h__
#define o_phantom_reflection_TNativeFunctionPointerType_h__



/* ****************** Includes ******************* */
/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)


template<int t_eConvention, typename t_ReturnType>
class TNativeFunctionPointerType0 : public FunctionPointerType
{
public:
    typedef TNativeFunctionPointerType0<t_eConvention, t_ReturnType> self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType()>::type function_pointer_t;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;

    TNativeFunctionPointerType0(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : FunctionPointerType(a_pSignature, (EABI)t_eConvention, a_Modifiers|o_native, (int)0){}

    void*                   getClosurePointer(void* a_pPointer) const { return (void*)(*static_cast<function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer) const
    {
        return FastDelegate0<t_ReturnType>(*static_cast<function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void** a_pParams) const
    {
        (**static_cast<function_pointer_t*>(a_pPointer))();
    }

    virtual void call(void* a_pPointer, void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((**static_cast<function_pointer_t*>(a_pPointer))());
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((**static_cast<function_pointer_t*>(a_pPointer))());
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    function_pointer_t        m_function_pointer;
};


template<int t_eConvention>
class TNativeFunctionPointerType0<t_eConvention, void> : public FunctionPointerType
{
public:
    typedef TNativeFunctionPointerType0<t_eConvention, void>    self_type;

    typedef typename native_function_pointer_type<t_eConvention, void()>::type function_pointer_t;

    TNativeFunctionPointerType0(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : FunctionPointerType(a_pSignature, (EABI)t_eConvention, a_Modifiers|o_native, (int)0)
    {

    }

    void*                   getClosurePointer(void* a_pPointer) const { return (void*)(*static_cast<function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer) const
    {
        return FastDelegate0<fastdelegate::detail::DefaultVoid>(*static_cast<function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void** a_pParams) const
    {
        (**static_cast<function_pointer_t*>(a_pPointer))();
    }
protected:
    

};


template<int t_eConvention, typename t_ReturnType, typename t_Param0>
class TNativeFunctionPointerType1 : public FunctionPointerType
{
public:
    typedef TNativeFunctionPointerType1<t_eConvention, t_ReturnType, t_Param0>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0)>::type function_pointer_t;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;


    TNativeFunctionPointerType1(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : FunctionPointerType(a_pSignature, (EABI)t_eConvention, a_Modifiers|o_native, (int)0)
    {

    }

    void*                   getClosurePointer(void* a_pPointer) const { return (void*)(*static_cast<function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer) const
    {
        return FastDelegate1<t_ReturnType, t_Param0>(*static_cast<function_pointer_t*>(a_pPointer)).GetMemento();
    }
    
    virtual void call(void* a_pPointer, void** a_pParams) const
    {
        (**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) );
    }
    virtual void call(void* a_pPointer, void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) ));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) ));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    
};


template<int t_eConvention, typename t_Param0>
class TNativeFunctionPointerType1<t_eConvention, void, t_Param0> : public FunctionPointerType
{
public:
    typedef TNativeFunctionPointerType1<t_eConvention, void, t_Param0>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, void(t_Param0)>::type function_pointer_t;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;

    TNativeFunctionPointerType1(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : FunctionPointerType(a_pSignature, (EABI)t_eConvention, a_Modifiers|o_native, (int)0)
    {

    }

    void*                   getClosurePointer(void* a_pPointer) const { return (void*)(*static_cast<function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer) const
    {
        return FastDelegate1<fastdelegate::detail::DefaultVoid, t_Param0>(*static_cast<function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void** a_pParams) const
    {
        (**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) );
    }

protected:
    
};


template<int t_eConvention, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeFunctionPointerType2 : public FunctionPointerType
{
public:
    typedef TNativeFunctionPointerType2<t_eConvention, t_ReturnType, t_Param0, t_Param1>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1)>::type function_pointer_t;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;

    TNativeFunctionPointerType2(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : FunctionPointerType(a_pSignature, (EABI)t_eConvention, a_Modifiers|o_native, (int)0)
    {

    }

    void*                   getClosurePointer(void* a_pPointer) const { return (void*)(*static_cast<function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer) const
    {
        return FastDelegate2<t_ReturnType, t_Param0, t_Param1>(*static_cast<function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void** a_pParams) const
    {
        (**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) );
    }

    virtual void call(void* a_pPointer, void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) ));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) ));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    

};

template<int t_eConvention, typename t_Param0, typename t_Param1>
class TNativeFunctionPointerType2<t_eConvention, void, t_Param0, t_Param1> : public FunctionPointerType
{
public:
    typedef TNativeFunctionPointerType2<t_eConvention, void, t_Param0, t_Param1>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, void(t_Param0, t_Param1)>::type function_pointer_t;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;

    TNativeFunctionPointerType2(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : FunctionPointerType(a_pSignature, (EABI)t_eConvention, a_Modifiers|o_native, (int)0)
    {

    }

    void*                   getClosurePointer(void* a_pPointer) const { return (void*)(*static_cast<function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer) const
    {
        return FastDelegate2<fastdelegate::detail::DefaultVoid, t_Param0, t_Param1>(*static_cast<function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void** a_pParams) const
    {
        (**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) );
    }

protected:
    
};


///  ==================================================================================================
///        3 PARAMETERS
///  ==================================================================================================

template<int t_eConvention, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeFunctionPointerType3 : public FunctionPointerType
{
public:
    typedef TNativeFunctionPointerType3<t_eConvention, t_ReturnType, t_Param0, t_Param1,t_Param2>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1,t_Param2)>::type function_pointer_t;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;


    TNativeFunctionPointerType3(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : FunctionPointerType(a_pSignature, (EABI)t_eConvention, a_Modifiers|o_native, (int)0)
    {

    }

    void*                   getClosurePointer(void* a_pPointer) const { return (void*)(*static_cast<function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer) const
    {
        return FastDelegate3<t_ReturnType, t_Param0,t_Param1,t_Param2>(*static_cast<function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void** a_pParams) const
    {
        (**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) );
    }

    virtual void call(void* a_pPointer, void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) ));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) 
            , *static_cast<t_Param2_noref*>(a_pParams[2])));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    

};

template<int t_eConvention, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeFunctionPointerType3<t_eConvention, void, t_Param0, t_Param1, t_Param2> : public FunctionPointerType
{
public:
    typedef TNativeFunctionPointerType3<t_eConvention, void, t_Param0, t_Param1, t_Param2>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, void(t_Param0, t_Param1,t_Param2)>::type function_pointer_t;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;

    TNativeFunctionPointerType3(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : FunctionPointerType(a_pSignature, (EABI)t_eConvention, a_Modifiers|o_native, (int)0)
    {

    }

    void*                   getClosurePointer(void* a_pPointer) const { return (void*)(*static_cast<function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer) const
    {
        return FastDelegate3<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2>(*static_cast<function_pointer_t*>(a_pPointer)).GetMemento();
    }
    
    virtual void call(void* a_pPointer, void** a_pParams) const
    {
        (**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) );
    }

protected:
    
};



///  ==================================================================================================
///        4 PARAMETERS
///  ==================================================================================================

template<
    int t_eConvention, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeFunctionPointerType4 : public FunctionPointerType
{
public:
    typedef TNativeFunctionPointerType4<t_eConvention, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1,t_Param2,t_Param3)>::type function_pointer_t;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;

    TNativeFunctionPointerType4(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : FunctionPointerType(a_pSignature, (EABI)t_eConvention, a_Modifiers|o_native, (int)0)
    {

    }

    void*                   getClosurePointer(void* a_pPointer) const { return (void*)(*static_cast<function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer) const
    {
        return FastDelegate4<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3>(*static_cast<function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void** a_pParams) const
    {
        (**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) );
    }
    virtual void call(void* a_pPointer, void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) ));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    

};

template<int t_eConvention
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeFunctionPointerType4<t_eConvention, void, t_Param0, t_Param1, t_Param2, t_Param3> : public FunctionPointerType
{
public:
    typedef TNativeFunctionPointerType4<t_eConvention, void, t_Param0, t_Param1, t_Param2, t_Param3>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, void(t_Param0, t_Param1,t_Param2,t_Param3)>::type function_pointer_t;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;

    TNativeFunctionPointerType4(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : FunctionPointerType(a_pSignature, (EABI)t_eConvention, a_Modifiers|o_native, (int)0)
    {

    }

    void*                   getClosurePointer(void* a_pPointer) const { return (void*)(*static_cast<function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer) const
    {
        return FastDelegate4<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3>(*static_cast<function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void** a_pParams) const
    {
        (**static_cast<function_pointer_t*>(a_pPointer))
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

template<
    int t_eConvention, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeFunctionPointerType5 : public FunctionPointerType
{
public:
    typedef TNativeFunctionPointerType5<t_eConvention, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4)>::type function_pointer_t;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;

    TNativeFunctionPointerType5(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : FunctionPointerType(a_pSignature, (EABI)t_eConvention, a_Modifiers|o_native, (int)0)
    {

    }

    void*                   getClosurePointer(void* a_pPointer) const { return (void*)(*static_cast<function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer) const
    {
        return FastDelegate5<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(*static_cast<function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void** a_pParams) const
    {
        (**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4]) );
    }
    virtual void call(void* a_pPointer, void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4]) ));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) 
            , *static_cast<t_Param4_noref*>(a_pParams[4])));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    

};

template<
    int t_eConvention
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeFunctionPointerType5<t_eConvention, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4> : public FunctionPointerType
{
public:
    typedef TNativeFunctionPointerType5<t_eConvention, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, void(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4)>::type function_pointer_t;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;

    TNativeFunctionPointerType5(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : FunctionPointerType(a_pSignature, (EABI)t_eConvention, a_Modifiers|o_native, (int)0)
    {

    }

    void*                   getClosurePointer(void* a_pPointer) const { return (void*)(*static_cast<function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer) const
    {
        return FastDelegate5<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(*static_cast<function_pointer_t*>(a_pPointer)).GetMemento();
    }
    
    virtual void call(void* a_pPointer, void** a_pParams) const
    {
        (**static_cast<function_pointer_t*>(a_pPointer))
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

template<
    int t_eConvention, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeFunctionPointerType6 : public FunctionPointerType
{
public:
    typedef TNativeFunctionPointerType6<t_eConvention, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)>::type function_pointer_t;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;

    TNativeFunctionPointerType6(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : FunctionPointerType(a_pSignature, (EABI)t_eConvention, a_Modifiers|o_native, (int)0)
    {

    }

    void*                   getClosurePointer(void* a_pPointer) const { return (void*)(*static_cast<function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer) const
    {
        return FastDelegate6<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(*static_cast<function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void** a_pParams) const
    {
        (**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) );
    }
    virtual void call(void* a_pPointer, void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) ));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) 
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    

};

template<
    int t_eConvention
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeFunctionPointerType6<t_eConvention, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5> : public FunctionPointerType
{
public:
    typedef TNativeFunctionPointerType6<t_eConvention, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, void(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)>::type function_pointer_t;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;

    TNativeFunctionPointerType6(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : FunctionPointerType(a_pSignature, (EABI)t_eConvention, a_Modifiers|o_native, (int)0)
    {

    }

    void*                   getClosurePointer(void* a_pPointer) const { return (void*)(*static_cast<function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer) const
    {
        return FastDelegate6<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(*static_cast<function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void** a_pParams) const
    {
        (**static_cast<function_pointer_t*>(a_pPointer))
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

template<
    int t_eConvention, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6>
class TNativeFunctionPointerType7 : public FunctionPointerType
{
public:
    typedef TNativeFunctionPointerType7<t_eConvention, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)>::type function_pointer_t;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;

    TNativeFunctionPointerType7(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : FunctionPointerType(a_pSignature, (EABI)t_eConvention, a_Modifiers|o_native, (int)0)
    {

    }

    void*                   getClosurePointer(void* a_pPointer) const { return (void*)(*static_cast<function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer) const
    {
        return FastDelegate7<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(*static_cast<function_pointer_t*>(a_pPointer)).GetMemento();
    }
    
    virtual void call(void* a_pPointer, void** a_pParams) const
    {
        (**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6]) );
    }
    virtual void call(void* a_pPointer, void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6]) ));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) 
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }


protected:
    

};

template<
    int t_eConvention
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6>
class TNativeFunctionPointerType7<t_eConvention, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6> : public FunctionPointerType
{
public:
    typedef TNativeFunctionPointerType7<t_eConvention, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, void(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)>::type function_pointer_t;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;

    TNativeFunctionPointerType7(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : FunctionPointerType(a_pSignature, (EABI)t_eConvention, a_Modifiers|o_native, (int)0)
    {

    }

    void*                   getClosurePointer(void* a_pPointer) const { return (void*)(*static_cast<function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer) const
    {
        return FastDelegate7<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(*static_cast<function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void** a_pParams) const
    {
        (**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6]));
    }

protected:
    
};



///  ==================================================================================================
///        8 PARAMETERS
///  ==================================================================================================

template<
    int t_eConvention, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7>
class TNativeFunctionPointerType8 : public FunctionPointerType
{
public:
    typedef TNativeFunctionPointerType8<t_eConvention, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)>::type function_pointer_t;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;

    TNativeFunctionPointerType8(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : FunctionPointerType(a_pSignature, (EABI)t_eConvention, a_Modifiers|o_native, (int)0)
    {

    }

    void*                   getClosurePointer(void* a_pPointer) const { return (void*)(*static_cast<function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer) const
    {
        return FastDelegate8<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(*static_cast<function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void** a_pParams) const
    {
        (**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7]) );
    }
    virtual void call(void* a_pPointer, void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((**static_cast<function_pointer_t*>(a_pPointer))
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7]) ));
    }
    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((**static_cast<function_pointer_t*>(a_pPointer))
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
    

};

template<
    int t_eConvention
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7>
class TNativeFunctionPointerType8<t_eConvention, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7> : public FunctionPointerType
{
public:
    typedef TNativeFunctionPointerType8<t_eConvention, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>    self_type;
  typedef typename native_function_pointer_type<t_eConvention, void(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)>::type function_pointer_t;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;



    TNativeFunctionPointerType8(Signature* a_pSignature, modifiers_t a_Modifiers = 0)
        : FunctionPointerType(a_pSignature, (EABI)t_eConvention, a_Modifiers|o_native, (int)0)
    {

    }

    void*                   getClosurePointer(void* a_pPointer) const { return (void*)(*static_cast<function_pointer_t*>(a_pPointer)); }
    DelegateMemento        getDelegateMemento(void* a_pPointer) const
    {
        return FastDelegate8<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(*static_cast<function_pointer_t*>(a_pPointer)).GetMemento();
    }

    virtual void call(void* a_pPointer, void** a_pParams) const
    {
        (**static_cast<function_pointer_t*>(a_pPointer))
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


/// STDCALL

#if defined (stdcall)
#define o_stdcall_was_defined
#pragma push_macro("stdcall")
#undef stdcall
#endif

#define o_convention_base stdcall
#include "TNativeFunctionPointerTypeCustomConvention.h"
#undef o_convention_base

#if defined (o_stdcall_was_defined)
#undef o_stdcall_was_defined
#pragma pop_macro("stdcall")
#endif

/// CDECL

#if defined (cdecl)
#define o_cdecl_was_defined
#pragma push_macro("cdecl")
#undef cdecl
#endif

#define o_convention_base cdecl
#include "TNativeFunctionPointerTypeCustomConvention.h"
#undef o_convention_base

#if defined (o_cdecl_was_defined)
#undef o_cdecl_was_defined
#pragma pop_macro("cdecl")
#endif


/// FASTCALL

#if defined (fastcall)
#define o_fastcall_was_defined
#pragma push_macro("fastcall")
#undef fastcall
#endif

#define o_convention_base fastcall
#include "TNativeFunctionPointerTypeCustomConvention.h"
#undef o_convention_base

#if defined (o_fastcall_was_defined)
#undef o_fastcall_was_defined
#pragma pop_macro("fastcall")
#endif

o_namespace_end(phantom, reflection, native)
// 
// o_namespace_begin(phantom)
// template<typename t_Signature> 
// struct dynamic_deleter<phantom::reflection::native::TNativeFunctionPointerType<t_Signature>> 
// {
//     o_forceinline static void dynamicDelete(void* a_pBase o_memory_stat_append_parameters)
//     {
//         o_dynamic_proxy_delete(phantom::reflection::native::TNativeFunctionPointerType<t_Signature>) a_pBase;
//     }
// };
// o_namespace_end(phantom)

#endif // TNativeFunctionPointerType_h__
