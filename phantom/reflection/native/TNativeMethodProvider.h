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

#ifndef o_phantom_reflection_native_TNativeMethodProvider_h__
#define o_phantom_reflection_native_TNativeMethodProvider_h__



/* ****************** Includes ******************* */
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
//#include "TNativeMethodProvider.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */


o_namespace_begin(phantom, reflection, native)

enum ETNativeMethodProviderTagId 
{
    eNativeMethodProviderTagId_Static,
    eNativeMethodProviderTagId_Instance,
    eNativeMethodProviderTagId_InstanceConst,
    eNativeMethodProviderTagId_InstanceNoConst,
    eNativeMethodProviderTagId_Interface,
    eNativeMethodProviderTagId_Auto,
    eNativeMethodProviderTagId_Invalid = 0xffffffff,
};

template<uint t_modifier>
class TNativeMethodProviderTag;


template<uint t_modifiers>
class TNativeMethodModifierTagProvider 
{
public:
    o_static_assert(((t_modifiers & o_const) != o_const) OR ((t_modifiers & o_noconst) != o_noconst));
    typedef TNativeMethodProviderTag<
        ((t_modifiers&o_static)==o_static)
            ? ((t_modifiers & o_virtual) == o_virtual) 
                ? eNativeMethodProviderTagId_Invalid
                : eNativeMethodProviderTagId_Static
            : /*((t_modifiers & o_interface) == o_interface)
                ? eNativeMethodProviderTagId_Interface
                :*/ (((t_modifiers & o_virtual) == o_virtual) 
                    || ((t_modifiers & o_abstract) == o_abstract)
                    || ((t_modifiers & o_const) == o_const)
                    || ((t_modifiers & o_noconst) == o_noconst))
                    ? ((t_modifiers & o_const) == o_const) 
                        ? eNativeMethodProviderTagId_InstanceConst
                        : ((t_modifiers & o_noconst) == o_noconst) 
                            ? eNativeMethodProviderTagId_InstanceNoConst
                            : eNativeMethodProviderTagId_Instance
                    : eNativeMethodProviderTagId_Auto
    > tag;
};


template<typename t_Ty, typename t_Tag, typename t_ReturnType>
class TNativeMethodProviderTagged0;

template<typename t_Ty, typename t_Tag, typename t_ReturnType, typename t_Param0>
class TNativeMethodProviderTagged1;

template<typename t_Ty, typename t_Tag, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMethodProviderTagged2;

template<typename t_Ty, typename t_Tag, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMethodProviderTagged3;

template<typename t_Ty, typename t_ReturnType>
class TNativeMethodProviderTagged0<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_Invalid>, t_ReturnType>
{
    byte incompatible_reflection_modifiers_you_probably_used_static_with_virtual_or_abstract[sizeof(t_Ty)?0:1];
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMethodProviderTagged1<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_Invalid>, t_ReturnType, t_Param0>
{
    byte incompatible_reflection_modifiers_you_probably_used_static_with_virtual_or_abstract[sizeof(t_Ty)?0:1];
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMethodProviderTagged2<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_Invalid>, t_ReturnType, t_Param0, t_Param1>
{
    byte incompatible_reflection_modifiers_you_probably_used_static_with_virtual_or_abstract[sizeof(t_Ty)?0:1];
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMethodProviderTagged3<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_Invalid>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
    byte incompatible_reflection_modifiers_you_probably_used_static_with_virtual_or_abstract[sizeof(t_Ty)?0:1];
};

template<typename t_Ty, typename t_ReturnType>
class TNativeMethodProviderTagged0<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_Static>, t_ReturnType>
{
public:
    static Method* CreateMethod(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(), 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeStaticMethod0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers|o_static);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMethodProviderTagged1<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_Static>, t_ReturnType, t_Param0>
{
public:
    static Method* CreateMethod(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0), 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeStaticMethod1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, o_static);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMethodProviderTagged2<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_Static>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static Method* CreateMethod(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1), 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeStaticMethod2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, o_static);
    }
};


template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMethodProviderTagged3<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_Static>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static Method* CreateMethod(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2), 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeStaticMethod3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, o_static);
    }
};




template<typename t_Ty, typename t_ReturnType>
class TNativeMethodProviderTagged0<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_Instance>, t_ReturnType>
{
public:
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(), 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethod0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }

    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)() const, 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethodConst0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMethodProviderTagged1<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_Instance>, t_ReturnType, t_Param0>
{
public:
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0), 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethod1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0) const, 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethodConst1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMethodProviderTagged2<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_Instance>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1),
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethod2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1) const,
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethodConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMethodProviderTagged3<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_Instance>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2),
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethod3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2) const,
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethodConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
};

template<typename t_Ty, typename t_ReturnType>
class TNativeMethodProviderTagged0<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_InstanceConst>, t_ReturnType>
{
public:
    
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)() const, 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethodConst0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMethodProviderTagged1<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_InstanceConst>, t_ReturnType, t_Param0>
{
public:
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0) const, 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethodConst1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMethodProviderTagged2<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_InstanceConst>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1) const,
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethodConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMethodProviderTagged3<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_InstanceConst>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2) const,
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethodConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
};

template<typename t_Ty, typename t_ReturnType>
class TNativeMethodProviderTagged0<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_InstanceNoConst>, t_ReturnType>
{
public:

    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)() const, 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethodConst0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMethodProviderTagged1<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0>
{
public:
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0), 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethodConst1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMethodProviderTagged2<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1),
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethodConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMethodProviderTagged3<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2),
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethodConst2<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
};


template<typename t_Ty, typename t_ReturnType>
class TNativeMethodProviderTagged0<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_Interface>, t_ReturnType>
{
public:
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(), 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInterfaceMethod0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }

    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)() const, 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInterfaceMethodConst0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMethodProviderTagged1<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_Interface>, t_ReturnType, t_Param0>
{
public:
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0), 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInterfaceMethod1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0) const, 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInterfaceMethodConst1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMethodProviderTagged2<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_Interface>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1),
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInterfaceMethod2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1) const,
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInterfaceMethodConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMethodProviderTagged3<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_Interface>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2),
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInterfaceMethod3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2) const,
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInterfaceMethodConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
};

template<typename t_Ty, typename t_ReturnType>
class TNativeMethodProviderTagged0<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_Auto>, t_ReturnType>
{
public:

    static Method* CreateMethod(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(), 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeStaticMethod0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }

    static Method* CreateMethod(const string& a_strName, 
                                    Signature* a_pSignature, 
                                    t_ReturnType (t_Ty::*a_pFunc)(), 
                                    bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethod0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }

    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)() const, 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethodConst0<t_Ty, t_ReturnType>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMethodProviderTagged1<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_Auto>, t_ReturnType, t_Param0>
{
public:
    static Method* CreateMethod(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0), 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeStaticMethod1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers|o_static);
    }
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0), 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethod1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0) const, 
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethodConst1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMethodProviderTagged2<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_Auto>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static Method* CreateMethod(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1),
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeStaticMethod2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers|o_static);
    }
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1),
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethod2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1) const,
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethodConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMethodProviderTagged3<t_Ty, TNativeMethodProviderTag<eNativeMethodProviderTagId_Auto>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static Method* CreateMethod(    const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2),
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeStaticMethod3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers|o_static);
    }
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2),
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethod3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
    }
    static Method* CreateMethod(const string& a_strName, 
        Signature* a_pSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2) const,
        bitfield a_bfModifiers = bitfield())
    {
        return o_new(TNativeInstanceMethodConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_pSignature, a_pFunc, a_bfModifiers);
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
class TNativeMethodProvider 
    : public TNativeMethodProviderTagged3<t_Ty
    , typename TNativeMethodModifierTagProvider<t_modifiers>::tag
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
class TNativeMethodProvider<t_Ty
    , t_modifiers
    , t_ReturnType
    , t_Param0
    , t_Param1
    , void>
    : public TNativeMethodProviderTagged2<t_Ty, typename TNativeMethodModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0>
class TNativeMethodProvider<t_Ty
    , t_modifiers
    , t_ReturnType
    , t_Param0
    , void
    , void>
    : public TNativeMethodProviderTagged1<t_Ty, typename TNativeMethodModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType>
class TNativeMethodProvider<t_Ty, t_modifiers, t_ReturnType, void, void, void> 
    : public TNativeMethodProviderTagged0<t_Ty, typename TNativeMethodModifierTagProvider<t_modifiers>::tag, t_ReturnType>
{

};

#else

template <typename t_Ty, uint t_modifiers, typename _Signature>
class TNativeMethodProvider;

template<typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0 
    , typename t_Param1 
    , typename t_Param2>
class TNativeMethodProvider<t_Ty, t_modifiers, t_ReturnType(t_Param0,t_Param1,t_Param2)> 
    : public TNativeMethodProviderTagged3<t_Ty, typename TNativeMethodModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1, t_Param2>
{

};

template<typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0 
    , typename t_Param1>
class TNativeMethodProvider<t_Ty, t_modifiers, t_ReturnType(t_Param0,t_Param1)> 
    : public TNativeMethodProviderTagged2<t_Ty, typename TNativeMethodModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0>
class TNativeMethodProvider<t_Ty, t_modifiers, t_ReturnType(t_Param0)>
    : public TNativeMethodProviderTagged1<t_Ty
    , typename TNativeMethodModifierTagProvider<t_modifiers>::tag
    , t_ReturnType
    , t_Param0>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType>
class TNativeMethodProvider<t_Ty, t_modifiers, t_ReturnType()> 
    : public TNativeMethodProviderTagged0<t_Ty, typename TNativeMethodModifierTagProvider<t_modifiers>::tag, t_ReturnType>
{

};



#endif

#ifdef o_NO_FUNCTION_STYLE_TEMPLATE_SIGNATURE

template<typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0 = void
    , typename t_Param1 = void>
class TNativeInterfaceMethodProvider 
    : public TNativeMethodProviderTagged2<t_Ty, typename TNativeMethodModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0>
class TNativeInterfaceMethodProvider<t_Ty, t_modifiers, t_ReturnType, t_Param0, void>
    : public TNativeMethodProviderTagged1<t_Ty, typename TNativeMethodModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType>
class TNativeInterfaceMethodProvider<t_Ty, t_modifiers, t_ReturnType, void, void> 
    : public TNativeMethodProviderTagged0<t_Ty, typename TNativeMethodModifierTagProvider<t_modifiers>::tag, t_ReturnType>
{

};

#else

template <typename t_Ty, uint t_modifiers, typename _Signature>
class TNativeInterfaceMethodProvider;

template<typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0 
    , typename t_Param1
    , typename t_Param2>
class TNativeInterfaceMethodProvider<t_Ty, t_modifiers, t_ReturnType(t_Param0,t_Param1,t_Param2)> 
    : public TNativeMethodProviderTagged3<t_Ty, typename TNativeMethodModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1, t_Param2>
{

};

template <typename t_Ty, uint t_modifiers, typename _Signature>
class TNativeInterfaceMethodProvider;

template<typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0 
    , typename t_Param1>
class TNativeInterfaceMethodProvider<t_Ty, t_modifiers, t_ReturnType(t_Param0,t_Param1)> 
    : public TNativeMethodProviderTagged2<t_Ty, typename TNativeMethodModifierTagProvider<t_modifiers>::tag, t_ReturnType, t_Param0, t_Param1>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType
    , typename t_Param0>
class TNativeInterfaceMethodProvider<t_Ty, t_modifiers, t_ReturnType(t_Param0)>
    : public TNativeMethodProviderTagged1<t_Ty
    , typename TNativeMethodModifierTagProvider<t_modifiers>::tag
    , t_ReturnType
    , t_Param0>
{

};

template <typename t_Ty
    , uint t_modifiers
    , typename t_ReturnType>
class TNativeInterfaceMethodProvider<t_Ty, t_modifiers, t_ReturnType()> 
    : public TNativeMethodProviderTagged0<t_Ty, typename TNativeMethodModifierTagProvider<t_modifiers>::tag, t_ReturnType>
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
        pSignature->beginConstruction();
        pSignature->setReturnType(pReturnType);
        pSignature->endConstruction();
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
        pSignature->beginConstruction();
        pSignature->setReturnType(pReturnType);
        pSignature->addParameterType(pParam0);
        pSignature->endConstruction();
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
        pSignature->beginConstruction();
        pSignature->setReturnType(pReturnType);
        pSignature->addParameterType(pParam0);
        pSignature->addParameterType(pParam1);
        pSignature->endConstruction();
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
        pSignature->beginConstruction();
        pSignature->setReturnType(pReturnType);
        pSignature->addParameterType(pParam0);
        pSignature->addParameterType(pParam1);
        pSignature->addParameterType(pParam2);
        pSignature->endConstruction();
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
        pSignature->beginConstruction();
        pSignature->setReturnType(pReturnType);
        pSignature->addParameterType(pParam0);
        pSignature->addParameterType(pParam1);
        pSignature->addParameterType(pParam2);
        pSignature->addParameterType(pParam3);
        pSignature->endConstruction();
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
        pSignature->beginConstruction();
        pSignature->setReturnType(pReturnType);
        pSignature->addParameterType(pParam0);
        pSignature->addParameterType(pParam1);
        pSignature->addParameterType(pParam2);
        pSignature->addParameterType(pParam3);
        pSignature->addParameterType(pParam4);
        pSignature->endConstruction();
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

o_namespace_end(phantom, reflection, native)


#else // TNativeMethodProvider_h__
#include "TNativeMethodProvider.classdef.h"
#endif