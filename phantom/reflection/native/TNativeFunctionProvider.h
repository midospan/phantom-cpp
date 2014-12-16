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
        Signature* a_pSignature, 
        t_ReturnType (__stdcall*a_pFunc)(), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_stdcall, t_ReturnType()>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }

#ifdef WIN32
    static Function* CreateFunction(const string& a_strName,
                                    Signature* a_pSignature, 
                                    t_ReturnType (__cdecl*a_pFunc)(), 
                                    modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_cdecl, t_ReturnType()>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }

    static Function* CreateFunction(const string& a_strName,
        Signature* a_pSignature, 
        t_ReturnType (__fastcall*a_pFunc)(), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_fastcall, t_ReturnType()>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
#endif //WIN32
};

template<typename t_ReturnType, typename t_Param0>
class TNativeFunctionProvider<t_ReturnType(t_Param0)>
{
public:
    static Function* CreateFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (__stdcall*a_pFunc)(t_Param0), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_stdcall, t_ReturnType(t_Param0)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
#ifdef WIN32
    static Function* CreateFunction(const string& a_strName,
        Signature* a_pSignature, 
        t_ReturnType (__cdecl*a_pFunc)(t_Param0), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_cdecl, t_ReturnType(t_Param0)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static Function* CreateFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (__fastcall*a_pFunc)(t_Param0), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_fastcall, t_ReturnType(t_Param0)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
#endif //WIN32
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeFunctionProvider<t_ReturnType(t_Param0, t_Param1)>
{
public:
    static Function* CreateFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (__stdcall*a_pFunc)(t_Param0, t_Param1),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_stdcall, t_ReturnType(t_Param0, t_Param1)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
#ifdef WIN32
    static Function* CreateFunction(const string& a_strName,
        Signature* a_pSignature, 
        t_ReturnType (__cdecl*a_pFunc)(t_Param0, t_Param1),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_cdecl, t_ReturnType(t_Param0, t_Param1)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static Function* CreateFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (__fastcall*a_pFunc)(t_Param0, t_Param1),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_fastcall, t_ReturnType(t_Param0, t_Param1)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
#endif //WIN32
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeFunctionProvider<t_ReturnType(t_Param0, t_Param1, t_Param2)>
{
public:
    static Function* CreateFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (__stdcall*a_pFunc)(t_Param0, t_Param1, t_Param2),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
#ifdef WIN32
    static Function* CreateFunction(const string& a_strName,
        Signature* a_pSignature, 
        t_ReturnType (__cdecl*a_pFunc)(t_Param0, t_Param1, t_Param2),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static Function* CreateFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (__fastcall*a_pFunc)(t_Param0, t_Param1, t_Param2),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
#endif //WIN32
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
class TNativeFunctionProvider<t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3)>
{
public:
    static Function* CreateFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (__stdcall*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
#ifdef WIN32
    static Function* CreateFunction(const string& a_strName,
        Signature* a_pSignature, 
        t_ReturnType (__cdecl*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static Function* CreateFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (__fastcall*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
#endif //WIN32
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
class TNativeFunctionProvider<t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)>
{
public:
    static Function* CreateFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (__stdcall*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
#ifdef WIN32
    static Function* CreateFunction(const string& a_strName,
        Signature* a_pSignature, 
        t_ReturnType (__cdecl*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static Function* CreateFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (__fastcall*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
#endif //WIN32
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
class TNativeFunctionProvider<t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)>
{
public:
    static Function* CreateFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (__stdcall*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
#ifdef WIN32
    static Function* CreateFunction(const string& a_strName,
        Signature* a_pSignature, 
        t_ReturnType (__cdecl*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static Function* CreateFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (__fastcall*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
#endif //WIN32
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
class TNativeFunctionProvider<t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)>
{
public:
    static Function* CreateFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (__stdcall*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
#ifdef WIN32
    static Function* CreateFunction(const string& a_strName,
        Signature* a_pSignature, 
        t_ReturnType (__cdecl*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static Function* CreateFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (__fastcall*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
#endif //WIN32
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
class TNativeFunctionProvider<t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)>
{
public:
    static Function* CreateFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (__stdcall*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
#ifdef WIN32
    static Function* CreateFunction(const string& a_strName,
        Signature* a_pSignature, 
        t_ReturnType (__cdecl*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static Function* CreateFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (__fastcall*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction<e_ABI_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
#endif //WIN32
};

o_namespace_end(phantom, reflection, native)


#endif