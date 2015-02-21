/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_TNativeFunction_h__
#define o_phantom_reflection_TNativeFunction_h__



/* ****************** Includes ******************* */
/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

o_namespace_begin(phantom, reflection, native)

class TNativeFunctionBase : public Function
{
protected:
    TNativeFunctionBase( const string& a_strName, const string& a_strSignature, EABI a_eABI, modifiers_t a_Modifiers /*= 0*/ )
        : Function(phantom::reflection::native::currentScope(), a_strName, a_strSignature, a_eABI, a_Modifiers|o_native)
    {
        phantom::reflection::native::currentScope()->asScope()->addFunction(this);    
    }
};

template<int e_eConvention, typename t_Signature>
struct native_function_pointer_type;

/// STDCALL

template<typename t_ReturnType>
struct native_function_pointer_type<e_stdcall, t_ReturnType()>
{
    typedef t_ReturnType (__stdcall * type)();
};

template<typename t_ReturnType, typename t_Param0>
struct native_function_pointer_type<e_stdcall, t_ReturnType(t_Param0)>
{
    typedef t_ReturnType (__stdcall * type)(t_Param0);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1>
struct native_function_pointer_type<e_stdcall, t_ReturnType(t_Param0, t_Param1)>
{
    typedef t_ReturnType (__stdcall * type)(t_Param0, t_Param1);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
struct native_function_pointer_type<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2)>
{
    typedef t_ReturnType (__stdcall * type)(t_Param0, t_Param1, t_Param2);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
struct native_function_pointer_type<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3)>
{
    typedef t_ReturnType (__stdcall * type)(t_Param0, t_Param1, t_Param2, t_Param3);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
struct native_function_pointer_type<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)>
{
    typedef t_ReturnType (__stdcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
struct native_function_pointer_type<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)>
{
    typedef t_ReturnType (__stdcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
struct native_function_pointer_type<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)>
{
    typedef t_ReturnType (__stdcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
struct native_function_pointer_type<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)>
{
    typedef t_ReturnType (__stdcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7, typename t_Param8>
struct native_function_pointer_type<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8)>
{
    typedef t_ReturnType (__stdcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7, typename t_Param8, typename t_Param9>
struct native_function_pointer_type<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8, t_Param9)>
{
    typedef t_ReturnType (__stdcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8, t_Param9);
};

/// FASTCALL

template<typename t_ReturnType>
struct native_function_pointer_type<e_fastcall, t_ReturnType()>
{
    typedef t_ReturnType (__fastcall * type)();
};

template<typename t_ReturnType, typename t_Param0>
struct native_function_pointer_type<e_fastcall, t_ReturnType(t_Param0)>
{
    typedef t_ReturnType (__fastcall * type)(t_Param0);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1>
struct native_function_pointer_type<e_fastcall, t_ReturnType(t_Param0, t_Param1)>
{
    typedef t_ReturnType (__fastcall * type)(t_Param0, t_Param1);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
struct native_function_pointer_type<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2)>
{
    typedef t_ReturnType (__fastcall * type)(t_Param0, t_Param1, t_Param2);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
struct native_function_pointer_type<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3)>
{
    typedef t_ReturnType (__fastcall * type)(t_Param0, t_Param1, t_Param2, t_Param3);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
struct native_function_pointer_type<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)>
{
    typedef t_ReturnType (__fastcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
struct native_function_pointer_type<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)>
{
    typedef t_ReturnType (__fastcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
struct native_function_pointer_type<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)>
{
    typedef t_ReturnType (__fastcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
struct native_function_pointer_type<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)>
{
    typedef t_ReturnType (__fastcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7, typename t_Param8>
struct native_function_pointer_type<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8)>
{
    typedef t_ReturnType (__fastcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7, typename t_Param8, typename t_Param9>
struct native_function_pointer_type<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8, t_Param9)>
{
    typedef t_ReturnType (__fastcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8, t_Param9);
};

/// CDECL

template<typename t_ReturnType>
struct native_function_pointer_type<e_cdecl, t_ReturnType()>
{
    typedef t_ReturnType (__cdecl * type)();
};

template<typename t_ReturnType, typename t_Param0>
struct native_function_pointer_type<e_cdecl, t_ReturnType(t_Param0)>
{
    typedef t_ReturnType (__cdecl * type)(t_Param0);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1>
struct native_function_pointer_type<e_cdecl, t_ReturnType(t_Param0, t_Param1)>
{
    typedef t_ReturnType (__cdecl * type)(t_Param0, t_Param1);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
struct native_function_pointer_type<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2)>
{
    typedef t_ReturnType (__cdecl * type)(t_Param0, t_Param1, t_Param2);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
struct native_function_pointer_type<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3)>
{
    typedef t_ReturnType (__cdecl * type)(t_Param0, t_Param1, t_Param2, t_Param3);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
struct native_function_pointer_type<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)>
{
    typedef t_ReturnType (__cdecl * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
struct native_function_pointer_type<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)>
{
    typedef t_ReturnType (__cdecl * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
struct native_function_pointer_type<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)>
{
    typedef t_ReturnType (__cdecl * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
struct native_function_pointer_type<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)>
{
    typedef t_ReturnType (__cdecl * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7, typename t_Param8>
struct native_function_pointer_type<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8)>
{
    typedef t_ReturnType (__cdecl * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7, typename t_Param8, typename t_Param9>
struct native_function_pointer_type<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8, t_Param9)>
{
    typedef t_ReturnType (__cdecl * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8, t_Param9);
};


template<int t_eConvention, typename t_ReturnType>
class TNativeFunction0 : public TNativeFunctionBase
{
public:
    typedef TNativeFunction0<t_eConvention, t_ReturnType> self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType()>::type function_pointer;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;

    TNativeFunction0(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeFunctionBase(a_strName, a_strSignature, (EABI)t_eConvention, a_Modifiers|o_native), m_function_pointer(a_pFunc){}

    void*                   getClosurePointer() const { return (void*)m_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate0<t_ReturnType>(m_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_function_pointer)();
    }

    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((*m_function_pointer)());
    }

    virtual void placementCall(void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((*m_function_pointer)
            ( )));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((*m_function_pointer)());
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    function_pointer        m_function_pointer;
};


template<int t_eConvention>
class TNativeFunction0<t_eConvention, void> : public TNativeFunctionBase
{
public:
    typedef TNativeFunction0<t_eConvention, void>    self_type;

    typedef typename native_function_pointer_type<t_eConvention, void()>::type function_pointer;

    TNativeFunction0(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeFunctionBase(a_strName, a_strSignature, (EABI)t_eConvention, a_Modifiers|o_native), m_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate0<fastdelegate::detail::DefaultVoid>(m_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_function_pointer)();
    }
protected:
    function_pointer m_function_pointer;

};


template<int t_eConvention, typename t_ReturnType, typename t_Param0>
class TNativeFunction1 : public TNativeFunctionBase
{
public:
    typedef TNativeFunction1<t_eConvention, t_ReturnType, t_Param0>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0)>::type function_pointer;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;


    TNativeFunction1(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeFunctionBase(a_strName, a_strSignature, (EABI)t_eConvention, a_Modifiers|o_native), m_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate1<t_ReturnType, t_Param0>(m_function_pointer).GetMemento();
    }
    
    virtual void call(void** a_pParams) const
    {
        (*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) ));
    }
    virtual void placementCall(void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]))));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) ));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    function_pointer m_function_pointer;
};


template<int t_eConvention, typename t_Param0>
class TNativeFunction1<t_eConvention, void, t_Param0> : public TNativeFunctionBase
{
public:
    typedef TNativeFunction1<t_eConvention, void, t_Param0>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, void(t_Param0)>::type function_pointer;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;

    TNativeFunction1(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeFunctionBase(a_strName, a_strSignature, (EABI)t_eConvention, a_Modifiers|o_native), m_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate1<fastdelegate::detail::DefaultVoid, t_Param0>(m_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0]) );
    }

protected:
    function_pointer m_function_pointer;
};


template<int t_eConvention, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeFunction2 : public TNativeFunctionBase
{
public:
    typedef TNativeFunction2<t_eConvention, t_ReturnType, t_Param0, t_Param1>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1)>::type function_pointer;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;

    TNativeFunction2(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeFunctionBase(a_strName, a_strSignature, (EABI)t_eConvention, a_Modifiers|o_native), m_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate2<t_ReturnType, t_Param0, t_Param1>(m_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) );
    }

    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) ));
    }
    virtual void placementCall(void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) )));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) ));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    function_pointer m_function_pointer;

};

template<int t_eConvention, typename t_Param0, typename t_Param1>
class TNativeFunction2<t_eConvention, void, t_Param0, t_Param1> : public TNativeFunctionBase
{
public:
    typedef TNativeFunction2<t_eConvention, void, t_Param0, t_Param1>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, void(t_Param0, t_Param1)>::type function_pointer;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;

    TNativeFunction2(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeFunctionBase(a_strName, a_strSignature, (EABI)t_eConvention, a_Modifiers|o_native), m_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate2<fastdelegate::detail::DefaultVoid, t_Param0, t_Param1>(m_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) );
    }

protected:
    function_pointer m_function_pointer;
};


///  ==================================================================================================
///        3 PARAMETERS
///  ==================================================================================================

template<int t_eConvention, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeFunction3 : public TNativeFunctionBase
{
public:
    typedef TNativeFunction3<t_eConvention, t_ReturnType, t_Param0, t_Param1,t_Param2>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1,t_Param2)>::type function_pointer;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;


    TNativeFunction3(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeFunctionBase(a_strName, a_strSignature, (EABI)t_eConvention, a_Modifiers|o_native), m_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate3<t_ReturnType, t_Param0,t_Param1,t_Param2>(m_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) );
    }

    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) ));
    }
    virtual void placementCall(void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) )));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]) 
            , *static_cast<t_Param2_noref*>(a_pParams[2])));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    function_pointer m_function_pointer;

};

template<int t_eConvention, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeFunction3<t_eConvention, void, t_Param0, t_Param1, t_Param2> : public TNativeFunctionBase
{
public:
    typedef TNativeFunction3<t_eConvention, void, t_Param0, t_Param1, t_Param2>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, void(t_Param0, t_Param1,t_Param2)>::type function_pointer;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;

    TNativeFunction3(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeFunctionBase(a_strName, a_strSignature, (EABI)t_eConvention, a_Modifiers|o_native), m_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate3<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2>(m_function_pointer).GetMemento();
    }
    
    virtual void call(void** a_pParams) const
    {
        (*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2]) );
    }

protected:
    function_pointer m_function_pointer;
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
class TNativeFunction4 : public TNativeFunctionBase
{
public:
    typedef TNativeFunction4<t_eConvention, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1,t_Param2,t_Param3)>::type function_pointer;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;

    TNativeFunction4(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeFunctionBase(a_strName, a_strSignature, (EABI)t_eConvention, a_Modifiers|o_native), m_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate4<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3>(m_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])));
    }
    virtual void placementCall(void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) )));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) ));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    function_pointer m_function_pointer;

};

template<int t_eConvention
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeFunction4<t_eConvention, void, t_Param0, t_Param1, t_Param2, t_Param3> : public TNativeFunctionBase
{
public:
    typedef TNativeFunction4<t_eConvention, void, t_Param0, t_Param1, t_Param2, t_Param3>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, void(t_Param0, t_Param1,t_Param2,t_Param3)>::type function_pointer;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;

    TNativeFunction4(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeFunctionBase(a_strName, a_strSignature, (EABI)t_eConvention, a_Modifiers|o_native), m_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate4<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3>(m_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) );
    }

protected:
    function_pointer m_function_pointer;
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
class TNativeFunction5 : public TNativeFunctionBase
{
public:
    typedef TNativeFunction5<t_eConvention, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4)>::type function_pointer;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;

    TNativeFunction5(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeFunctionBase(a_strName, a_strSignature, (EABI)t_eConvention, a_Modifiers|o_native), m_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate5<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(m_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4]) ));
    }
    virtual void placementCall(void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4]) )));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) 
            , *static_cast<t_Param4_noref*>(a_pParams[4])));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    function_pointer m_function_pointer;

};

template<
    int t_eConvention
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeFunction5<t_eConvention, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4> : public TNativeFunctionBase
{
public:
    typedef TNativeFunction5<t_eConvention, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, void(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4)>::type function_pointer;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;

    TNativeFunction5(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeFunctionBase(a_strName, a_strSignature, (EABI)t_eConvention, a_Modifiers|o_native), m_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate5<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(m_function_pointer).GetMemento();
    }
    
    virtual void call(void** a_pParams) const
    {
        (*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4]) );
    }

protected:
    function_pointer m_function_pointer;
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
class TNativeFunction6 : public TNativeFunctionBase
{
public:
    typedef TNativeFunction6<t_eConvention, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)>::type function_pointer;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;

    TNativeFunction6(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeFunctionBase(a_strName, a_strSignature, (EABI)t_eConvention, a_Modifiers|o_native), m_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate6<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(m_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) );
    }
    virtual void call(void** a_pParams, void* a_pReturnAddress) const
    {
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) ));
    }
    virtual void placementCall(void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) )));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3]) 
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])));
    }

    virtual bool        isAddressable() const { return addressable_wrapper<t_ReturnType>::value; }

protected:
    function_pointer m_function_pointer;

};

template<
    int t_eConvention
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeFunction6<t_eConvention, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5> : public TNativeFunctionBase
{
public:
    typedef TNativeFunction6<t_eConvention, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, void(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)>::type function_pointer;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;

    TNativeFunction6(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeFunctionBase(a_strName, a_strSignature, (EABI)t_eConvention, a_Modifiers|o_native), m_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate6<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(m_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5]) );
    }

protected:
    function_pointer m_function_pointer;
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
class TNativeFunction7 : public TNativeFunctionBase
{
public:
    typedef TNativeFunction7<t_eConvention, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)>::type function_pointer;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;

    TNativeFunction7(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeFunctionBase(a_strName, a_strSignature, (EABI)t_eConvention, a_Modifiers|o_native), m_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate7<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(m_function_pointer).GetMemento();
    }
    
    virtual void call(void** a_pParams) const
    {
        (*m_function_pointer)
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
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6]) ));
    }
    virtual void placementCall(void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6]) )));
    }

    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((*m_function_pointer)
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
    function_pointer m_function_pointer;

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
class TNativeFunction7<t_eConvention, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6> : public TNativeFunctionBase
{
public:
    typedef TNativeFunction7<t_eConvention, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, void(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)>::type function_pointer;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;

    TNativeFunction7(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeFunctionBase(a_strName, a_strSignature, (EABI)t_eConvention, a_Modifiers|o_native), m_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate7<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(m_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6]));
    }

protected:
    function_pointer m_function_pointer;
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
class TNativeFunction8 : public TNativeFunctionBase
{
public:
    typedef TNativeFunction8<t_eConvention, t_ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)>::type function_pointer;
    typedef o_NESTED_TYPE return_storage_type_helper<t_ReturnType>::type return_storage_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;

    TNativeFunction8(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeFunctionBase(a_strName, a_strSignature, (EABI)t_eConvention, a_Modifiers|o_native), m_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate8<t_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(m_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_function_pointer)
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
        *static_cast<return_storage_type*>(a_pReturnAddress) = return_storage_wrapper<t_ReturnType>::apply((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7]) ));
    }
    virtual void placementCall(void** a_pParams, void* a_pReturnAddress) const
    {
        new (a_pReturnAddress) return_storage_type(return_storage_wrapper<t_ReturnType>::apply((*m_function_pointer)
            ( *static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7]) )));
    }
    virtual void* getAddress(void** a_pParams) const
    {
        return addressable_wrapper<t_ReturnType>::address((*m_function_pointer)
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
    function_pointer m_function_pointer;

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
class TNativeFunction8<t_eConvention, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7> : public TNativeFunctionBase
{
public:
    typedef TNativeFunction8<t_eConvention, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>    self_type;
  typedef typename native_function_pointer_type<t_eConvention, void(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)>::type function_pointer;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
  typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;



    TNativeFunction8(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeFunctionBase(a_strName, a_strSignature, (EABI)t_eConvention, a_Modifiers|o_native), m_function_pointer(a_pFunc)
    {

    }

    void*                   getClosurePointer() const { return (void*)m_function_pointer; }
    DelegateMemento        getDelegateMemento(void* a_pObject) const
    {
        return FastDelegate8<fastdelegate::detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(m_function_pointer).GetMemento();
    }

    virtual void call(void** a_pParams) const
    {
        (*m_function_pointer)
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
    function_pointer m_function_pointer;
};

template<int callConvention, typename Signature>
class TNativeFunction;

template<int t_eConvention, typename t_ReturnType>
class TNativeFunction<t_eConvention, t_ReturnType()>
    : public TNativeFunction0<t_eConvention, t_ReturnType>
{
public:
    typedef TNativeFunction<t_eConvention, t_ReturnType()>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType()>::type function_pointer;

    TNativeFunction(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        : TNativeFunction0<t_eConvention, t_ReturnType>(a_strName, a_strSignature, a_pFunc , a_Modifiers|o_native)
    {

    }
};

template<int t_eConvention, typename t_ReturnType, typename t_Param0>
class TNativeFunction<t_eConvention, t_ReturnType(t_Param0)> 
    : public TNativeFunction1<t_eConvention, t_ReturnType, t_Param0>
{
public:
    typedef TNativeFunction<t_eConvention, t_ReturnType(t_Param0)>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0)>::type function_pointer;

    TNativeFunction(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeFunction1<t_eConvention, t_ReturnType,t_Param0>(a_strName, a_strSignature, a_pFunc , a_Modifiers|o_native)
    {

    }
};

template<int t_eConvention, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeFunction<t_eConvention, t_ReturnType(t_Param0,t_Param1)> 
    : public TNativeFunction2<t_eConvention, t_ReturnType, t_Param0, t_Param1>
{
public:
    typedef TNativeFunction<t_eConvention, t_ReturnType(t_Param0, t_Param1)>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1)>::type function_pointer;

    TNativeFunction(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeFunction2<t_eConvention, t_ReturnType,t_Param0,t_Param1>(a_strName, a_strSignature, a_pFunc , a_Modifiers|o_native)
    {

    }

};

template<
    int t_eConvention, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2>
class TNativeFunction<t_eConvention, t_ReturnType(t_Param0,t_Param1,t_Param2)> 
    : public TNativeFunction3<t_eConvention, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    typedef TNativeFunction<t_eConvention, t_ReturnType(t_Param0, t_Param1, t_Param2)>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1,t_Param2)>::type function_pointer;

    TNativeFunction(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeFunction3<t_eConvention, t_ReturnType, t_Param0, t_Param1, t_Param2>(a_strName, a_strSignature, a_pFunc , a_Modifiers|o_native)
    {

    }

};


template<
    int t_eConvention, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeFunction<t_eConvention, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3)> 
    : public TNativeFunction4<t_eConvention, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    typedef TNativeFunction<t_eConvention, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3)>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1,t_Param2,t_Param3)>::type function_pointer;

    TNativeFunction(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeFunction4<t_eConvention, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>(a_strName, a_strSignature, a_pFunc , a_Modifiers|o_native)
    {

    }

};

template<
    int t_eConvention, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeFunction<t_eConvention, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4)> 
    : public TNativeFunction5<t_eConvention, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>
{
public:
    typedef TNativeFunction<t_eConvention, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4)>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4)>::type function_pointer;

    TNativeFunction(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeFunction5<t_eConvention, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>(a_strName, a_strSignature, a_pFunc , a_Modifiers|o_native)
    {

    }

};

template<
    int t_eConvention, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeFunction<t_eConvention, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)> 
    : public TNativeFunction6<t_eConvention, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>
{
public:
    typedef TNativeFunction<t_eConvention, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5)>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)>::type function_pointer;

    TNativeFunction(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeFunction6<t_eConvention, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>(a_strName, a_strSignature, a_pFunc , a_Modifiers|o_native)
    {

    }

};

template<
    int t_eConvention, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6>
class TNativeFunction<t_eConvention, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)> 
    : public TNativeFunction7<t_eConvention, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>
{
public:
    typedef TNativeFunction<t_eConvention, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)>::type function_pointer;

    TNativeFunction(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeFunction7<t_eConvention, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>(a_strName, a_strSignature, a_pFunc , a_Modifiers|o_native)
    {

    }

};


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
class TNativeFunction<t_eConvention, t_ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)> 
    : public TNativeFunction8<t_eConvention, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>
{
public:
    typedef TNativeFunction<t_eConvention, t_ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)>    self_type;
    typedef typename native_function_pointer_type<t_eConvention, t_ReturnType(t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)>::type function_pointer;

    TNativeFunction(const string& a_strName, const string& a_strSignature, function_pointer a_pFunc, modifiers_t a_Modifiers = 0)
        :TNativeFunction8<t_eConvention, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(a_strName, a_strSignature, a_pFunc , a_Modifiers|o_native)
    {

    }
};

o_namespace_end(phantom, reflection, native)
// 
// o_namespace_begin(phantom)
// template<int t_eConvention, typename t_Signature> 
// struct dynamic_deleter<phantom::reflection::native::TNativeFunction<t_eConvention, t_Signature>> 
// {
//     o_forceinline static void dynamicDelete(void* a_pBase o_memory_stat_append_parameters)
//     {
//         o_dynamic_proxy_delete(phantom::reflection::native::TNativeFunction<t_eConvention, t_Signature>) a_pBase;
//     }
// };
// o_namespace_end(phantom)

#endif // TNativeFunction_h__
