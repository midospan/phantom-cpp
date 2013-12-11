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
/* The *.classdef.h file must be the last #include */
//#include "TNativeMemberFunctionProvider.classdef.h"
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

template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunctionProviderTagged0<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(), 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeStaticMemberFunction0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionProviderTagged1<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType, t_Param0>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0), 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeStaticMemberFunction1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, o_static);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionProviderTagged2<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1), 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeStaticMemberFunction2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, o_static);
    }
};


template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunctionProviderTagged3<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2), 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeStaticMemberFunction3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, o_static);
    }
};




template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunctionProviderTagged0<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(), 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunction0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }

    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)() const, 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunctionConst0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionProviderTagged1<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType, t_Param0>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0), 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunction1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0) const, 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunctionConst1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionProviderTagged2<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1),
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunction2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1) const,
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunctionConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunctionProviderTagged3<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2),
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunction3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2) const,
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunctionConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunctionProviderTagged0<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType>
{
public:
    
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)() const, 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunctionConst0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionProviderTagged1<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType, t_Param0>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0) const, 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunctionConst1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionProviderTagged2<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1) const,
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunctionConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunctionProviderTagged3<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2) const,
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunctionConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunctionProviderTagged0<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType>
{
public:

    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)() const, 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunctionConst0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionProviderTagged1<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0), 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunctionConst1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionProviderTagged2<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1),
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunctionConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunctionProviderTagged3<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2),
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunctionConst2<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};


template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunctionProviderTagged0<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Interface>, t_ReturnType>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(), 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInterfaceMemberFunction0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }

    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)() const, 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInterfaceMemberFunctionConst0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionProviderTagged1<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Interface>, t_ReturnType, t_Param0>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0), 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInterfaceMemberFunction1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0) const, 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInterfaceMemberFunctionConst1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionProviderTagged2<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Interface>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1),
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInterfaceMemberFunction2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1) const,
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInterfaceMemberFunctionConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunctionProviderTagged3<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Interface>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2),
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInterfaceMemberFunction3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2) const,
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInterfaceMemberFunctionConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunctionProviderTagged0<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType>
{
public:

    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(), 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeStaticMemberFunction0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }

    static MemberFunction* CreateMemberFunction(const string& a_strName, 
                                    Signature* a_pSignature, 
                                    t_ReturnType (t_Ty::*a_pFunc)(), 
                                    bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunction0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }

    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)() const, 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunctionConst0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionProviderTagged1<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType, t_Param0>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0), 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeStaticMemberFunction1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0), 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunction1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0) const, 
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunctionConst1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionProviderTagged2<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1),
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeStaticMemberFunction2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1),
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunction2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1) const,
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunctionConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunctionProviderTagged3<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static MemberFunction* CreateMemberFunction(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2),
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeStaticMemberFunction3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_Modifiers|o_static);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2),
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunction3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
    static MemberFunction* CreateMemberFunction(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2) const,
        bitfield a_Modifiers = 0)
    {
        return o_new(TNativeInstanceMemberFunctionConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_Modifiers);
    }
};

#ifdef o_NO_FUNCTION_STYLE_TEMPLATE_SIGNATURE


template<typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0 = void
    , typename t_Param1 = void
    , typename t_Param2 = void
>
class TNativeMemberFunctionProvider 
    : public TNativeMemberFunctionProviderTagged3<t_Ty
    , typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag
    , t_ReturnType
    , t_Param0
    , t_Param1
    , t_Param2>
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
    , void>
    : public TNativeMemberFunctionProviderTagged1<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType>
class TNativeMemberFunctionProvider<t_Ty, t_modifiers, t_ReturnType, void, void, void> 
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

#ifdef o_NO_FUNCTION_STYLE_TEMPLATE_SIGNATURE

template<typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0 = void
    , typename t_Param1 = void>
class TNativeInterfaceMemberFunctionProvider 
    : public TNativeMemberFunctionProviderTagged2<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0>
class TNativeInterfaceMemberFunctionProvider<t_Ty, t_modifiers, t_ReturnType, t_Param0, void>
    : public TNativeMemberFunctionProviderTagged1<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType>
class TNativeInterfaceMemberFunctionProvider<t_Ty, t_modifiers, t_ReturnType, void, void> 
    : public TNativeMemberFunctionProviderTagged0<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType>
{

};

#else

template <typename t_Ty, uint t_modifiers, typename _Signature>
class TNativeInterfaceMemberFunctionProvider;

template<typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0 
    , typename t_Param1
    , typename t_Param2>
class TNativeInterfaceMemberFunctionProvider<t_Ty, t_modifiers, t_ReturnType(t_Param0,t_Param1,t_Param2)> 
    : public TNativeMemberFunctionProviderTagged3<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1, t_Param2>
{

};

template <typename t_Ty, uint t_modifiers, typename _Signature>
class TNativeInterfaceMemberFunctionProvider;

template<typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0 
    , typename t_Param1>
class TNativeInterfaceMemberFunctionProvider<t_Ty, t_modifiers, t_ReturnType(t_Param0,t_Param1)> 
    : public TNativeMemberFunctionProviderTagged2<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0>
class TNativeInterfaceMemberFunctionProvider<t_Ty, t_modifiers, t_ReturnType(t_Param0)>
    : public TNativeMemberFunctionProviderTagged1<t_Ty
    , typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag
    , t_ReturnType
    , t_Param0>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType>
class TNativeInterfaceMemberFunctionProvider<t_Ty, t_modifiers, t_ReturnType()> 
    : public TNativeMemberFunctionProviderTagged0<t_Ty, typename TNativeMemberFunctionModifierTagProvider<t_modifiers>::tag, t_ReturnType>
{

};


#endif


template <int t_counter, typename t_ReturnType>
class TNativeSignatureProvider0
{
public:
    static Signature*    CreateSignature(const char* a_strSignature, TemplateSpecialization* a_pTemplateSpecialization, LanguageElement* a_pScope)
    {
        /// Check first by static resolving
        Signature* pSignature = o_new(Signature);
        phantom::reflection::Type* pReturnType = phantom::reflection::detail::type_of_counter_<t_ReturnType, t_counter>::object();
        if(!pReturnType) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        pSignature->setReturnType(pReturnType);
        return pSignature;
    }
};


    template <int t_counter, typename t_ReturnType
    , typename t_Param0>
class TNativeSignatureProvider1
{
public:
    static Signature*    CreateSignature(const char* a_strSignature, TemplateSpecialization* a_pTemplateSpecialization, LanguageElement* a_pScope)
    {
        /// Resolve first by static type resolving.
        /// If one fails, resolve via signature parsing (probably a pointer on an uncomplete class).
        Signature* pSignature = o_new(Signature);
        Type* pReturnType = phantom::reflection::detail::type_of_counter_<t_ReturnType, t_counter>::object();
        if(!pReturnType) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        Type* pParam0 = phantom::reflection::detail::type_of_counter_<t_Param0, t_counter>::object();
        if(!pParam0) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        pSignature->setReturnType(pReturnType);
        pSignature->addParameterType(pParam0);
        return pSignature;
    }
};


template <int t_counter, typename t_ReturnType
        , typename t_Param0
        , typename t_Param1>
class TNativeSignatureProvider2
{
public:
    static Signature*    CreateSignature(const char* a_strSignature, TemplateSpecialization* a_pTemplateSpecialization, LanguageElement* a_pScope)
    {
        /// Resolve first by static type resolving.
        /// If one fails, resolve via signature parsing (probably a pointer on an uncomplete class).
        Signature* pSignature = o_new(Signature);
        Type* pReturnType = phantom::reflection::detail::type_of_counter_<t_ReturnType, t_counter>::object();
        if(!pReturnType) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        Type* pParam0 = phantom::reflection::detail::type_of_counter_<t_Param0, t_counter>::object();
        if(!pParam0) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        Type* pParam1 = phantom::reflection::detail::type_of_counter_<t_Param1, t_counter>::object();
        if(!pParam1) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        pSignature->setReturnType(pReturnType);
        pSignature->addParameterType(pParam0);
        pSignature->addParameterType(pParam1);
        return pSignature;
    }
};

template <int t_counter, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2>
class TNativeSignatureProvider3
{
public:
    static Signature*    CreateSignature(const char* a_strSignature, TemplateSpecialization* a_pTemplateSpecialization, LanguageElement* a_pScope)
    {
        /// Resolve first by static type resolving.
        /// If one fails, resolve via signature parsing (probably due to the presence of a pointer on an uncomplete class).
        Signature* pSignature = o_new(Signature);
        Type* pReturnType = phantom::reflection::detail::type_of_counter_<t_ReturnType, t_counter>::object();
        if(!pReturnType) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        Type* pParam0 = phantom::reflection::detail::type_of_counter_<t_Param0, t_counter>::object();
        if(!pParam0) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        Type* pParam1 = phantom::reflection::detail::type_of_counter_<t_Param1, t_counter>::object();
        if(!pParam1) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        Type* pParam2 = phantom::reflection::detail::type_of_counter_<t_Param2, t_counter>::object();
        if(!pParam2) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        pSignature->setReturnType(pReturnType);
        pSignature->addParameterType(pParam0);
        pSignature->addParameterType(pParam1);
        pSignature->addParameterType(pParam2);
        return pSignature;
    }
};

template <int t_counter, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3>
class TNativeSignatureProvider4
{
public:
    static Signature*    CreateSignature(const char* a_strSignature, TemplateSpecialization* a_pTemplateSpecialization, LanguageElement* a_pScope)
    {
        /// Resolve first by static type resolving.
        /// If one fails, resolve via signature parsing (probably due to the presence of a pointer on an uncomplete class).
        Signature* pSignature = o_new(Signature);
        Type* pReturnType = phantom::reflection::detail::type_of_counter_<t_ReturnType, t_counter>::object();
        if(!pReturnType) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        Type* pParam0 = phantom::reflection::detail::type_of_counter_<t_Param0, t_counter>::object();
        if(!pParam0) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        Type* pParam1 = phantom::reflection::detail::type_of_counter_<t_Param1, t_counter>::object();
        if(!pParam1) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        Type* pParam2 = phantom::reflection::detail::type_of_counter_<t_Param2, t_counter>::object();
        if(!pParam2) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        Type* pParam3 = phantom::reflection::detail::type_of_counter_<t_Param3, t_counter>::object();
        if(!pParam3) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        pSignature->setReturnType(pReturnType);
        pSignature->addParameterType(pParam0);
        pSignature->addParameterType(pParam1);
        pSignature->addParameterType(pParam2);
        pSignature->addParameterType(pParam3);
        return pSignature;
    }
};

template <int t_counter, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4>
class TNativeSignatureProvider5
{
public:
    static Signature*    CreateSignature(const char* a_strSignature, TemplateSpecialization* a_pTemplateSpecialization, LanguageElement* a_pScope)
    {
        /// Resolve first by static type resolving.
        /// If one fails, resolve via signature parsing (probably due to the presence of a pointer on an uncomplete class).
        Signature* pSignature = o_new(Signature);
        Type* pReturnType = phantom::reflection::detail::type_of_counter_<t_ReturnType, t_counter>::object();
        if(!pReturnType) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        Type* pParam0 = phantom::reflection::detail::type_of_counter_<t_Param0, t_counter>::object();
        if(!pParam0) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        Type* pParam1 = phantom::reflection::detail::type_of_counter_<t_Param1, t_counter>::object();
        if(!pParam1) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        Type* pParam2 = phantom::reflection::detail::type_of_counter_<t_Param2, t_counter>::object();
        if(!pParam2) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        Type* pParam3 = phantom::reflection::detail::type_of_counter_<t_Param3, t_counter>::object();
        if(!pParam3) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        Type* pParam4 = phantom::reflection::detail::type_of_counter_<t_Param4, t_counter>::object();
        if(!pParam4) 
        {
            pSignature->parse(a_strSignature, a_pTemplateSpecialization, a_pScope);
            return pSignature;
        }
        pSignature->setReturnType(pReturnType);
        pSignature->addParameterType(pParam0);
        pSignature->addParameterType(pParam1);
        pSignature->addParameterType(pParam2);
        pSignature->addParameterType(pParam3);
        pSignature->addParameterType(pParam4);
        return pSignature;
    }
};

#ifdef o_NO_FUNCTION_STYLE_TEMPLATE_SIGNATURE

template <int t_counter, typename t_ReturnType
    , typename t_Param0 = void
    , typename t_Param1 = void
    , typename t_Param2 = void
    , typename t_Param3 = void
    , typename t_Param4 = void>
class TNativeSignatureProvider 
    : public TNativeSignatureProvider5<t_counter, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>
{
};

template <int t_counter, typename t_ReturnType>
class TNativeSignatureProvider<t_ReturnType,t_Param0, t_Param1, t_Param2, t_Param3, void> 
    : public TNativeSignatureProvider4<t_counter, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
};
template <int t_counter, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2>
class TNativeSignatureProvider<t_ReturnType,t_Param0, t_Param1, t_Param2, void, void> 
    : public TNativeSignatureProvider3<t_counter, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
};

template <int t_counter, typename t_ReturnType
    , typename t_Param0
    , typename t_Param1>
class TNativeSignatureProvider<t_ReturnType,t_Param0, t_Param1, void, void, void> 
    : public TNativeSignatureProvider2<t_counter, t_ReturnType, t_Param0, t_Param1>
{
};

template <int t_counter, typename t_ReturnType
    , typename t_Param0>
class TNativeSignatureProvider<t_ReturnType,t_Param0, void, void, void, void> 
    : public TNativeSignatureProvider1<t_counter, t_ReturnType, t_Param0>
{
};


template <int t_counter, typename t_ReturnType>
class TNativeSignatureProvider<t_ReturnType,void, void, void, void, void> : public TNativeSignatureProvider0<t_counter, t_ReturnType>
{
};

#else

template <int t_counter, typename Signature>
class TNativeSignatureProvider;


template <int t_counter, typename t_ReturnType>
class TNativeSignatureProvider<t_counter, t_ReturnType()> : public TNativeSignatureProvider0<t_counter, t_ReturnType>
{

};

template <int t_counter, typename t_ReturnType, typename t_Param0>
class TNativeSignatureProvider<t_counter, t_ReturnType(t_Param0)> : public TNativeSignatureProvider1<t_counter, t_ReturnType, t_Param0>
{

};

template <int t_counter, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeSignatureProvider<t_counter, t_ReturnType(t_Param0, t_Param1)> : public TNativeSignatureProvider2<t_counter, t_ReturnType, t_Param0, t_Param1>
{

};

template <int t_counter, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeSignatureProvider<t_counter, t_ReturnType(t_Param0, t_Param1, t_Param2)> : public TNativeSignatureProvider3<t_counter, t_ReturnType, t_Param0, t_Param1, t_Param2>
{

};

template <int t_counter, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
class TNativeSignatureProvider<t_counter, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3)> 
    : public TNativeSignatureProvider4<t_counter, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{

};

#endif

template<int t_counter, typename t_Ty, typename t_PropertyValueType>
class TNativePropertySignalProvider
{
    typedef typename proxy_of<t_Ty>::type proxy_type;
public:
    static Signal* CreateSignal(const char* a_strName, const char* a_strPropertyValueTypeName, signal_t (t_Ty::*signal_pointer)(t_PropertyValueType) const, connection::slot::list (t_Ty::*signal_slot_list_pointer))
    {
        return o_new(TNativeSignal<t_Ty, signal_t(t_PropertyValueType)>)( a_strName
            , TNativeSignatureProvider<t_counter, phantom::signal_t(t_PropertyValueType) >::CreateSignature(
                (string("phantom::signal_t(") + a_strPropertyValueTypeName + ")").c_str()
                , phantom::templateSpecializationOf<t_Ty>()
                , phantom::typeOf<t_Ty>()
            )
            , signal_pointer
            , signal_slot_list_pointer
            , o_protected);
    }
    static Signal* CreateSignal(const char* a_strName, const char* a_strPropertyValueTypeName, signal_t (t_Ty::*signal_pointer)() const, connection::slot::list (t_Ty::*signal_slot_list_pointer))
    {
        return o_new(TNativeSignal<t_Ty, signal_t()>)( a_strName
            , TNativeSignatureProvider<t_counter, phantom::signal_t() >::CreateSignature(
            "phantom::signal_t()"
            , phantom::templateSpecializationOf<t_Ty>()
            , phantom::typeOf<t_Ty>()
            )
            , signal_pointer
            , signal_slot_list_pointer
            , o_protected);
    }
    static Signal* CreateSignal(const char* a_strPropertyValueTypeName, const char* a_strName, int (proxy_type::*a_iNoSignal), int (proxy_type::*a_iNoSlotList))
    {
        return nullptr;
    }
};

o_namespace_end(phantom, reflection, native)


#else // TNativeMemberFunctionProvider_h__
#include "TNativeMemberFunctionProvider.classdef.h"
#endif