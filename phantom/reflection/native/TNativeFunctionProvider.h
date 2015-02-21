/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_native_TNativeFunctionProvider_h__
#define o_phantom_reflection_native_TNativeFunctionProvider_h__



/* ****************** Includes ******************* */
/* *********************************************** */
/* The *.hxx file must be the last #include */
//#include "TNativeFunctionProvider.hxx"
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection, native)

template<typename t_Signature>
class TNativeFunctionProvider;

template<typename t_ReturnType>
class TNativeFunctionProvider<t_ReturnType()>
{
public:

    static Function* CreateFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__stdcall*a_pFunc)(), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_stdcall, t_ReturnType()>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }

    static Function* CreateFunction(const string& a_strName, 
                                    const string& a_strSignature, 
                                    t_ReturnType (__cdecl*a_pFunc)(), 
                                    modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_cdecl, t_ReturnType()>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }

    static Function* CreateFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__fastcall*a_pFunc)(), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_fastcall, t_ReturnType()>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_ReturnType, typename t_Param0>
class TNativeFunctionProvider<t_ReturnType(t_Param0)>
{
public:
    static Function* CreateFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__stdcall*a_pFunc)(t_Param0), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_stdcall, t_ReturnType(t_Param0)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers|o_static);
    }
    static Function* CreateFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__cdecl*a_pFunc)(t_Param0), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_cdecl, t_ReturnType(t_Param0)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Function* CreateFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__fastcall*a_pFunc)(t_Param0), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_fastcall, t_ReturnType(t_Param0)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeFunctionProvider<t_ReturnType(t_Param0, t_Param1)>
{
public:
    static Function* CreateFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__stdcall*a_pFunc)(t_Param0, t_Param1),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_stdcall, t_ReturnType(t_Param0, t_Param1)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers|o_static);
    }
    static Function* CreateFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__cdecl*a_pFunc)(t_Param0, t_Param1),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_cdecl, t_ReturnType(t_Param0, t_Param1)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Function* CreateFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__fastcall*a_pFunc)(t_Param0, t_Param1),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_fastcall, t_ReturnType(t_Param0, t_Param1)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeFunctionProvider<t_ReturnType(t_Param0, t_Param1, t_Param2)>
{
public:
    static Function* CreateFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__stdcall*a_pFunc)(t_Param0, t_Param1, t_Param2),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers|o_static);
    }
    static Function* CreateFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__cdecl*a_pFunc)(t_Param0, t_Param1, t_Param2),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Function* CreateFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__fastcall*a_pFunc)(t_Param0, t_Param1, t_Param2),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
class TNativeFunctionProvider<t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3)>
{
public:
    static Function* CreateFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__stdcall*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers|o_static);
    }
    static Function* CreateFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__cdecl*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Function* CreateFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__fastcall*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
class TNativeFunctionProvider<t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)>
{
public:
    static Function* CreateFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__stdcall*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers|o_static);
    }
    static Function* CreateFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__cdecl*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Function* CreateFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__fastcall*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
class TNativeFunctionProvider<t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)>
{
public:
    static Function* CreateFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__stdcall*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers|o_static);
    }
    static Function* CreateFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__cdecl*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Function* CreateFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__fastcall*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
class TNativeFunctionProvider<t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)>
{
public:
    static Function* CreateFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__stdcall*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers|o_static);
    }
    static Function* CreateFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__cdecl*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Function* CreateFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__fastcall*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
class TNativeFunctionProvider<t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)>
{
public:
    static Function* CreateFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__stdcall*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers|o_static);
    }
    static Function* CreateFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__cdecl*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Function* CreateFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (__fastcall*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

o_namespace_end(phantom, reflection, native)


#endif