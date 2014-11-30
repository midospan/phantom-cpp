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

#ifndef o_phantom_reflection_native_TNativeMemberFunctionProvider_h__
#define o_phantom_reflection_native_TNativeMemberFunctionProvider_h__



/* ****************** Includes ******************* */
/* *********************************************** */
/* The *.hxx file must be the last #include */
//#include "TNativeMemberFunctionProvider.hxx"
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection, native)

enum ETNativeMemberFunctionProviderTagId 
{
    eNativeMemberFunctionProviderTagId_Static,
    eNativeMemberFunctionProviderTagId_Instance,
    eNativeMemberFunctionProviderTagId_InstanceConst,
    eNativeMemberFunctionProviderTagId_InstanceNoConst,
    eNativeMemberFunctionProviderTagId_Interface,
    eNativeMemberFunctionProviderTagId_Auto,
    eNativeMemberFunctionProviderTagId_Invalid = 0xffffffff,
};

template<uint t_modifier>
class TNativeMemberFunctionProviderTag;


template<uint t_modifiers>
class TNativeMemberFunctionModifierTagProvider 
{
public:
    o_static_assert(((t_modifiers & o_const) != o_const) OR ((t_modifiers & o_noconst) != o_noconst));
    typedef TNativeMemberFunctionProviderTag<
        ((t_modifiers&o_static)==o_static)
            ? ((t_modifiers & o_virtual) == o_virtual) 
                ? eNativeMemberFunctionProviderTagId_Invalid
                : eNativeMemberFunctionProviderTagId_Static
            : /*((t_modifiers & o_interface) == o_interface)
                ? eNativeMemberFunctionProviderTagId_Interface
                :*/ (((t_modifiers & o_virtual) == o_virtual) 
                    || ((t_modifiers & o_abstract) == o_abstract)
                    || ((t_modifiers & o_const) == o_const)
                    || ((t_modifiers & o_noconst) == o_noconst))
                    ? ((t_modifiers & o_const) == o_const) 
                        ? eNativeMemberFunctionProviderTagId_InstanceConst
                        : ((t_modifiers & o_noconst) == o_noconst) 
                            ? eNativeMemberFunctionProviderTagId_InstanceNoConst
                            : eNativeMemberFunctionProviderTagId_Instance
                    : eNativeMemberFunctionProviderTagId_Auto
    > tag;
};


template<typename t_Ty, typename t_Tag, typename t_ReturnType>
class TNativeMemberFunctionProviderTagged0;

template<typename t_Ty, typename t_Tag, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionProviderTagged1;

template<typename t_Ty, typename t_Tag, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionProviderTagged2;

template<typename t_Ty, typename t_Tag, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunctionProviderTagged3;

template<typename t_Ty, typename t_Tag, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
class TNativeMemberFunctionProviderTagged4;

template<typename t_Ty, typename t_Tag, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
class TNativeMemberFunctionProviderTagged5;

template<typename t_Ty, typename t_Tag, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
class TNativeMemberFunctionProviderTagged6;

template<typename t_Ty, typename t_Tag, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
class TNativeMemberFunctionProviderTagged7;

template<typename t_Ty, typename t_Tag, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
class TNativeMemberFunctionProviderTagged8;


template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunctionProviderTagged0<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Invalid>, t_ReturnType>
{
    byte incompatible_reflection_modifiers_you_probably_used_static_with_virtual_or_abstract[sizeof(t_Ty)?0:1];
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionProviderTagged1<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Invalid>, t_ReturnType, t_Param0>
{
    byte incompatible_reflection_modifiers_you_probably_used_static_with_virtual_or_abstract[sizeof(t_Ty)?0:1];
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionProviderTagged2<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Invalid>, t_ReturnType, t_Param0, t_Param1>
{
    byte incompatible_reflection_modifiers_you_probably_used_static_with_virtual_or_abstract[sizeof(t_Ty)?0:1];
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunctionProviderTagged3<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Invalid>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
    byte incompatible_reflection_modifiers_you_probably_used_static_with_virtual_or_abstract[sizeof(t_Ty)?0:1];
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
class TNativeMemberFunctionProviderTagged4<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Invalid>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
    byte incompatible_reflection_modifiers_you_probably_used_static_with_virtual_or_abstract[sizeof(t_Ty)?0:1];
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
class TNativeMemberFunctionProviderTagged5<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Invalid>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>
{
    byte incompatible_reflection_modifiers_you_probably_used_static_with_virtual_or_abstract[sizeof(t_Ty)?0:1];
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
class TNativeMemberFunctionProviderTagged6<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Invalid>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>
{
    byte incompatible_reflection_modifiers_you_probably_used_static_with_virtual_or_abstract[sizeof(t_Ty)?0:1];
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
class TNativeMemberFunctionProviderTagged7<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Invalid>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>
{
    byte incompatible_reflection_modifiers_you_probably_used_static_with_virtual_or_abstract[sizeof(t_Ty)?0:1];
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
class TNativeMemberFunctionProviderTagged8<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Invalid>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>
{
    byte incompatible_reflection_modifiers_you_probably_used_static_with_virtual_or_abstract[sizeof(t_Ty)?0:1];
};

template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunctionProviderTagged0<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeStaticMemberFunction0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionProviderTagged1<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType, t_Param0>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeStaticMemberFunction1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, o_static);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionProviderTagged2<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeStaticMemberFunction2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, o_static);
    }
};


template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunctionProviderTagged3<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeStaticMemberFunction3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, o_static);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
class TNativeMemberFunctionProviderTagged4<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeStaticMemberFunction4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>)(a_strName, a_pSignature, a_pFunc, o_static);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
class TNativeMemberFunctionProviderTagged5<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeStaticMemberFunction5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>)(a_strName, a_pSignature, a_pFunc, o_static);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
class TNativeMemberFunctionProviderTagged6<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeStaticMemberFunction6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>)(a_strName, a_pSignature, a_pFunc, o_static);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
class TNativeMemberFunctionProviderTagged7<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeStaticMemberFunction7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>)(a_strName, a_pSignature, a_pFunc, o_static);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
class TNativeMemberFunctionProviderTagged8<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeStaticMemberFunction8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>)(a_strName, a_pSignature, a_pFunc, o_static);
    }
};

template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunctionProviderTagged0<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }

    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)() const, 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionProviderTagged1<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType, t_Param0>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0) const, 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionProviderTagged2<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunctionProviderTagged3<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
class TNativeMemberFunctionProviderTagged4<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
class TNativeMemberFunctionProviderTagged5<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
class TNativeMemberFunctionProviderTagged6<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
class TNativeMemberFunctionProviderTagged7<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
class TNativeMemberFunctionProviderTagged8<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunctionProviderTagged0<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType>
{
public:
    
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)() const, 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionProviderTagged1<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType, t_Param0>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0) const, 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionProviderTagged2<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunctionProviderTagged3<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
class TNativeMemberFunctionProviderTagged4<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
class TNativeMemberFunctionProviderTagged5<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
class TNativeMemberFunctionProviderTagged6<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
class TNativeMemberFunctionProviderTagged7<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
class TNativeMemberFunctionProviderTagged8<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunctionProviderTagged0<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType>
{
public:

    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionProviderTagged1<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionProviderTagged2<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunctionProviderTagged3<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
class TNativeMemberFunctionProviderTagged4<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
class TNativeMemberFunctionProviderTagged5<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
class TNativeMemberFunctionProviderTagged6<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
class TNativeMemberFunctionProviderTagged7<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
class TNativeMemberFunctionProviderTagged8<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunctionProviderTagged0<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType>
{
public:

    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeStaticMemberFunction0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }

    static MemberFunction* CreateMemberFunction(const string& a_strName, 
                                    Signature* a_pSignature, 
                                    t_ReturnType (t_Ty::*a_pFunc)(), 
                                    modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }

    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)() const, 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionProviderTagged1<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType, t_Param0>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeStaticMemberFunction1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0) const, 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionProviderTagged2<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeStaticMemberFunction2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunctionProviderTagged3<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeStaticMemberFunction3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
class TNativeMemberFunctionProviderTagged4<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeStaticMemberFunction4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
class TNativeMemberFunctionProviderTagged5<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeStaticMemberFunction5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
class TNativeMemberFunctionProviderTagged6<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeStaticMemberFunction6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
class TNativeMemberFunctionProviderTagged7<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeStaticMemberFunction7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
class TNativeMemberFunctionProviderTagged8<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeStaticMemberFunction8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunction8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceMemberFunctionConst8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

#ifdef o_NO_FUNCTION_STYLE_TEMPLATE_SIGNATURE


template<typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0 = void
    , typename t_Param1 = void
    , typename t_Param2 = void
    , typename t_Param3 = void
    , typename t_Param4 = void
    , typename t_Param5 = void
    , typename t_Param6 = void
    , typename t_Param7 = void
>
class TNativeMemberFunctionProvider 
    : public TNativeMemberFunctionProviderTagged8<t_Ty
    , typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag
    , t_ReturnType
    , t_Param0
    , t_Param1
    , t_Param2
    , t_Param3
    , t_Param4
    , t_Param5
    , t_Param6
    , t_Param7>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6>
class TNativeMemberFunctionProvider<t_Ty
    , t_modifiers
    , t_ReturnType
    , t_Param0
    , t_Param1
    , t_Param2
    , t_Param3
    , t_Param4
    , t_Param5
    , t_Param6
    , void>
    : public TNativeMemberFunctionProviderTagged7<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5>
class TNativeMemberFunctionProvider<t_Ty
    , t_modifiers
    , t_ReturnType
    , t_Param0
    , t_Param1
    , t_Param2
    , t_Param3
    , t_Param4
    , t_Param5
    , void
    , void>
    : public TNativeMemberFunctionProviderTagged6<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeMemberFunctionProvider<t_Ty
    , t_modifiers
    , t_ReturnType
    , t_Param0
    , t_Param1
    , t_Param2
    , t_Param3
    , t_Param4
    , void
    , void
    , void>
    : public TNativeMemberFunctionProviderTagged5<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeMemberFunctionProvider<t_Ty
    , t_modifiers
    , t_ReturnType
    , t_Param0
    , t_Param1
    , t_Param2
    , t_Param3
    , void
    , void
    , void
    , void>
    : public TNativeMemberFunctionProviderTagged4<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2>
class TNativeMemberFunctionProvider<t_Ty
    , t_modifiers
    , t_ReturnType
    , t_Param0
    , t_Param1
    , t_Param2
    , void
    , void
    , void
    , void
    , void>
    : public TNativeMemberFunctionProviderTagged3<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1, t_Param2>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0
    , typename t_Param1>
class TNativeMemberFunctionProvider<t_Ty
    , t_modifiers
    , t_ReturnType
    , t_Param0
    , t_Param1
    , void
    , void
    , void
    , void
    , void
    , void>
    : public TNativeMemberFunctionProviderTagged2<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0>
class TNativeMemberFunctionProvider<t_Ty
    , t_modifiers
    , t_ReturnType
    , t_Param0
    , void
    , void
    , void
    , void
    , void
    , void
    , void>
    : public TNativeMemberFunctionProviderTagged1<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType>
class TNativeMemberFunctionProvider<t_Ty
    , t_modifiers
    , t_ReturnType
    , void
    , void
    , void
    , void
    , void
    , void
    , void
    , void> 
    : public TNativeMemberFunctionProviderTagged0<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType>
{

};

#else

template <typename t_Ty, uint t_modifiers, typename _Signature>
class TNativeMemberFunctionProvider;

template<typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0 
    , typename t_Param1 
    , typename t_Param2
    , typename t_Param3 
    , typename t_Param4 
    , typename t_Param5 
    , typename t_Param6 
    , typename t_Param7>
class TNativeMemberFunctionProvider<t_Ty, t_modifiers, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)> 
    : public TNativeMemberFunctionProviderTagged8<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>
{

};

template<typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0 
    , typename t_Param1 
    , typename t_Param2
    , typename t_Param3 
    , typename t_Param4 
    , typename t_Param5 
    , typename t_Param6>
class TNativeMemberFunctionProvider<t_Ty, t_modifiers, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)> 
    : public TNativeMemberFunctionProviderTagged7<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>
{

};

template<typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0 
    , typename t_Param1 
    , typename t_Param2
    , typename t_Param3 
    , typename t_Param4 
    , typename t_Param5>
class TNativeMemberFunctionProvider<t_Ty, t_modifiers, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)> 
    : public TNativeMemberFunctionProviderTagged6<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>
{

};

template<typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0 
    , typename t_Param1 
    , typename t_Param2
    , typename t_Param3 
    , typename t_Param4>
class TNativeMemberFunctionProvider<t_Ty, t_modifiers, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)> 
    : public TNativeMemberFunctionProviderTagged5<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>
{

};

template<typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0 
    , typename t_Param1 
    , typename t_Param2
    , typename t_Param3 >
class TNativeMemberFunctionProvider<t_Ty, t_modifiers, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3)> 
    : public TNativeMemberFunctionProviderTagged4<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{

};

template<typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0 
    , typename t_Param1 
    , typename t_Param2>
class TNativeMemberFunctionProvider<t_Ty, t_modifiers, t_ReturnType(t_Param0,t_Param1,t_Param2)> 
    : public TNativeMemberFunctionProviderTagged3<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1, t_Param2>
{

};

template<typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0 
    , typename t_Param1>
class TNativeMemberFunctionProvider<t_Ty, t_modifiers, t_ReturnType(t_Param0,t_Param1)> 
    : public TNativeMemberFunctionProviderTagged2<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0>
class TNativeMemberFunctionProvider<t_Ty, t_modifiers, t_ReturnType(t_Param0)>
    : public TNativeMemberFunctionProviderTagged1<t_Ty
    , typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag
    , t_ReturnType
    , t_Param0>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType>
class TNativeMemberFunctionProvider<t_Ty, t_modifiers, t_ReturnType()> 
    : public TNativeMemberFunctionProviderTagged0<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType>
{

};



#endif

o_namespace_end(phantom, reflection, native)


#endif