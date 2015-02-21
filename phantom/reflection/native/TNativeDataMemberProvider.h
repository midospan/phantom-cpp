/* TODO LICENCE HERE */

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
    static LanguageElement* CreateDataMember(    const string& a_strName,
        Type*    a_pContentType,
        t_ContentType* a_pDataMemberPtr,
        Range* a_pRange,
        uint a_uiSerializationMask, 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeVariable<t_ContentType>) (a_pContentType, a_strName, a_pDataMemberPtr, a_pRange, a_Modifiers|o_static);
    }
};

template<typename t_Ty, typename t_ContentType>
class TNativeDataMemberProviderTagged<t_Ty, TNativeDataMemberProviderTag<eNativeDataMemberProviderTagId_Auto>, t_ContentType>
{
public:
    static LanguageElement* CreateDataMember(    const string& a_strName,
        Type*    a_pContentType,
        t_ContentType (t_Ty::*a_pDataMemberPtr),
        Range* a_pRange,
        uint a_uiSerializationMask, 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeDataMember<t_Ty, t_ContentType>)(a_pContentType, a_strName, a_pDataMemberPtr, a_pRange, a_uiSerializationMask, a_Modifiers);
    }
    static LanguageElement* CreateDataMember(    const string& a_strName,
        Type*    a_pContentType,
        t_ContentType* a_pDataMemberPtr,
        Range* a_pRange,
        uint a_uiSerializationMask, 
        modifiers_t a_Modifiers = 0)
    {
        return o_dynamic_proxy_new(TNativeVariable<t_ContentType>) (a_pContentType, a_strName, a_pDataMemberPtr, a_pRange, a_Modifiers|o_static);
    }
};

template<typename t_Ty, uint t_Modifiers, typename t_ContentType>
class TNativeDataMemberProvider : public TNativeDataMemberProviderTagged<t_Ty, typename TNativeDataMemberModifierTagProvider<t_Modifiers>::tag, t_ContentType>
{

};

o_namespace_end(phantom, reflection, native)



#endif
