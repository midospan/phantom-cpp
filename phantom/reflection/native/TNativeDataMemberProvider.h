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

#ifndef o_phantom_reflection_native_TNativeDataMemberProvider_h__
#define o_phantom_reflection_native_TNativeDataMemberProvider_h__



/* ****************** Includes ******************* */
/* *********************************************** */
/* The *.hxx file must be the last #include */
//#include "TNativeDataMemberProvider.hxx"
/* **************** Declarations ***************** */

/* *********************************************** */


o_namespace_begin(phantom, reflection, native)

enum ETNativeDataMemberProviderTagId
{
    eNativeDataMemberProviderTagId_Static,
    eNativeDataMemberProviderTagId_Instance,
    eNativeDataMemberProviderTagId_Auto,
    eNativeDataMemberProviderTagId_Invalid = 0xffffffff,
};

template<uint t_modifier>
class TNativeDataMemberProviderTag
{

};


template<uint t_modifiers>
class TNativeDataMemberModifierTagProvider
{
public:
    typedef TNativeDataMemberProviderTag<
        ((t_modifiers & o_static) == o_static)
            ? eNativeDataMemberProviderTagId_Static
            : eNativeDataMemberProviderTagId_Auto

    > tag;
};


template<typename t_Ty, typename t_Tag, typename t_ContentType>
class TNativeDataMemberProviderTagged;

template<typename t_Ty, typename t_ContentType>
class TNativeDataMemberProviderTagged<t_Ty, TNativeDataMemberProviderTag<eNativeDataMemberProviderTagId_Invalid>, t_ContentType>
{
    byte incompatible_reflection_modifiers[sizeof(t_Ty)?0:1];
};

template<typename t_Ty, typename t_ContentType>
class TNativeDataMemberProviderTagged<t_Ty, TNativeDataMemberProviderTag<eNativeDataMemberProviderTagId_Static>, t_ContentType>
{
public:
    static DataMember* CreateDataMember(    const string& a_strName,
        Type*    a_pContentType,
        t_ContentType* a_pDataMemberPtr,
        Range* a_pRange,
        uint a_uiSerializationMask, 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeStaticDataMember<t_Ty, t_ContentType>) (a_pContentType, a_strName, a_pDataMemberPtr, a_pRange, a_Modifiers|o_static);
    }
};

template<typename t_Ty, typename t_ContentType>
class TNativeDataMemberProviderTagged<t_Ty, TNativeDataMemberProviderTag<eNativeDataMemberProviderTagId_Auto>, t_ContentType>
{
public:
    static DataMember* CreateDataMember(    const string& a_strName,
        Type*    a_pContentType,
        t_ContentType (t_Ty::*a_pDataMemberPtr),
        Range* a_pRange,
        uint a_uiSerializationMask, 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeInstanceDataMember<t_Ty, t_ContentType>)(a_pContentType, a_strName, a_pDataMemberPtr, a_pRange, a_uiSerializationMask, a_Modifiers);
    }
    static DataMember* CreateDataMember(    const string& a_strName,
        Type*    a_pContentType,
        t_ContentType* a_pDataMemberPtr,
        Range* a_pRange,
        uint a_uiSerializationMask, 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeStaticDataMember<t_Ty, t_ContentType>) (a_pContentType, a_strName, a_pDataMemberPtr, a_pRange, a_Modifiers|o_static);
    }
};

template<typename t_Ty, uint t_Modifiers, typename t_ContentType>
class TNativeDataMemberProvider : public TNativeDataMemberProviderTagged<t_Ty, typename TNativeDataMemberModifierTagProvider<t_Modifiers>::tag, t_ContentType>
{

};

o_namespace_end(phantom, reflection, native)



#endif
