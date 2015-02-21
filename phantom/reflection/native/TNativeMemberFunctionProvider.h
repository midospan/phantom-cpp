/* TODO LICENCE HERE */

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
    static Subroutine* CreateMemberFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (*a_pFunc)(), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction0<e_defaultcall, t_ReturnType>)(a_strName, a_strSignature, a_pFunc, a_Modifiers|o_static);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionProviderTagged1<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType, t_Param0>
{
public:
    static Subroutine* CreateMemberFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (*a_pFunc)(t_Param0), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction1<e_defaultcall, t_ReturnType, t_Param0>)(a_strName, a_strSignature, a_pFunc, o_static);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionProviderTagged2<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static Subroutine* CreateMemberFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction2<e_defaultcall, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_strSignature, a_pFunc, o_static);
    }
};


template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunctionProviderTagged3<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static Subroutine* CreateMemberFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction3<e_defaultcall, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_strSignature, a_pFunc, o_static);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
class TNativeMemberFunctionProviderTagged4<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    static Subroutine* CreateMemberFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction4<e_defaultcall, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>)(a_strName, a_strSignature, a_pFunc, o_static);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
class TNativeMemberFunctionProviderTagged5<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>
{
public:
    static Subroutine* CreateMemberFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction5<e_defaultcall, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>)(a_strName, a_strSignature, a_pFunc, o_static);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
class TNativeMemberFunctionProviderTagged6<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>
{
public:
    static Subroutine* CreateMemberFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction6<e_defaultcall, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>)(a_strName, a_strSignature, a_pFunc, o_static);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
class TNativeMemberFunctionProviderTagged7<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>
{
public:
    static Subroutine* CreateMemberFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction7<e_defaultcall, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>)(a_strName, a_strSignature, a_pFunc, o_static);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
class TNativeMemberFunctionProviderTagged8<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Static>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>
{
public:
    static Subroutine* CreateMemberFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction8<e_defaultcall, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>)(a_strName, a_strSignature, a_pFunc, o_static);
    }
};

template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunctionProviderTagged0<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction0<t_Ty, t_ReturnType>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }

    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)() const, 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst0<t_Ty, t_ReturnType>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionProviderTagged1<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType, t_Param0>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0) const, 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionProviderTagged2<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunctionProviderTagged3<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
class TNativeMemberFunctionProviderTagged4<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
class TNativeMemberFunctionProviderTagged5<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
class TNativeMemberFunctionProviderTagged6<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
class TNativeMemberFunctionProviderTagged7<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
class TNativeMemberFunctionProviderTagged8<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Instance>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunctionProviderTagged0<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType>
{
public:
    
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)() const, 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst0<t_Ty, t_ReturnType>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionProviderTagged1<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType, t_Param0>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0) const, 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionProviderTagged2<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunctionProviderTagged3<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
class TNativeMemberFunctionProviderTagged4<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
class TNativeMemberFunctionProviderTagged5<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
class TNativeMemberFunctionProviderTagged6<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
class TNativeMemberFunctionProviderTagged7<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
class TNativeMemberFunctionProviderTagged8<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceConst>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunctionProviderTagged0<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType>
{
public:

    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction0<t_Ty, t_ReturnType>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionProviderTagged1<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionProviderTagged2<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunctionProviderTagged3<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
class TNativeMemberFunctionProviderTagged4<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
class TNativeMemberFunctionProviderTagged5<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
class TNativeMemberFunctionProviderTagged6<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
class TNativeMemberFunctionProviderTagged7<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
class TNativeMemberFunctionProviderTagged8<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_InstanceNoConst>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>
{
public:
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType>
class TNativeMemberFunctionProviderTagged0<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType>
{
public:

    static Subroutine* CreateMemberFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (*a_pFunc)(), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction0<e_defaultcall, t_ReturnType>)(a_strName, a_strSignature, a_pFunc, a_Modifiers|o_static);
    }

    static Subroutine* CreateMemberFunction(const string& a_strName, 
                                    const string& a_strSignature, 
                                    t_ReturnType (t_Ty::*a_pFunc)(), 
                                    modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction0<t_Ty, t_ReturnType>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }

    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)() const, 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst0<t_Ty, t_ReturnType>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0>
class TNativeMemberFunctionProviderTagged1<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType, t_Param0>
{
public:
    static Subroutine* CreateMemberFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (*a_pFunc)(t_Param0), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction1<e_defaultcall, t_ReturnType, t_Param0>)(a_strName, a_strSignature, a_pFunc, a_Modifiers|o_static);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0), 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0) const, 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst1<t_Ty, t_ReturnType, t_Param0>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1>
class TNativeMemberFunctionProviderTagged2<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType, t_Param0, t_Param1>
{
public:
    static Subroutine* CreateMemberFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction2<e_defaultcall, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_strSignature, a_pFunc, a_Modifiers|o_static);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst2<t_Ty, t_ReturnType, t_Param0, t_Param1>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeMemberFunctionProviderTagged3<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
    static Subroutine* CreateMemberFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction3<e_defaultcall, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_strSignature, a_pFunc, a_Modifiers|o_static);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst3<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
class TNativeMemberFunctionProviderTagged4<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
    static Subroutine* CreateMemberFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction4<e_defaultcall, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>)(a_strName, a_strSignature, a_pFunc, a_Modifiers|o_static);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst4<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
class TNativeMemberFunctionProviderTagged5<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>
{
public:
    static Subroutine* CreateMemberFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction5<e_defaultcall, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>)(a_strName, a_strSignature, a_pFunc, a_Modifiers|o_static);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst5<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
class TNativeMemberFunctionProviderTagged6<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>
{
public:
    static Subroutine* CreateMemberFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction6<e_defaultcall, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>)(a_strName, a_strSignature, a_pFunc, a_Modifiers|o_static);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst6<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
class TNativeMemberFunctionProviderTagged7<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>
{
public:
    static Subroutine* CreateMemberFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction7<e_defaultcall, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>)(a_strName, a_strSignature, a_pFunc, a_Modifiers|o_static);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst7<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
};

template<typename t_Ty, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
class TNativeMemberFunctionProviderTagged8<t_Ty, TNativeMemberFunctionProviderTag<eNativeMemberFunctionProviderTagId_Auto>, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>
{
public:
    static Subroutine* CreateMemberFunction(    const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeFunction8<e_defaultcall, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>)(a_strName, a_strSignature, a_pFunc, a_Modifiers|o_static);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7),
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunction8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
    }
    static Subroutine* CreateMemberFunction(const string& a_strName, 
        const string& a_strSignature, 
        t_ReturnType (t_Ty::*a_pFunc)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7) const,
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeMemberFunctionConst8<t_Ty, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>)(a_strName, a_strSignature, a_pFunc, a_Modifiers);
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