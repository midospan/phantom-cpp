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

#ifndef o_def_installer_h__
#define o_def_installer_h__

o_namespace_begin(phantom)

namespace detail 
{
    template<typename t_Ty, uint t_baseclasscount>
    struct rtti_data_registrer_helper_base;

    template<typename t_Ty, size_t t_index, bool deferred> 
    struct rtti_data_registrer_helper_get_base_class_helper
    {
        o_forceinline static reflection::Class* apply(reflection::Class* a_pLayoutClass) 
        { 
            return typeOf<o_traits_t_Ty_base_class(t_index)>(); 
        }
    };

    template<typename t_Ty, size_t t_index> 
    struct rtti_data_registrer_helper_get_base_class_helper<t_Ty, t_index, false>
    {
        o_forceinline static reflection::Class* apply(reflection::Class* a_pLayoutClass) { return a_pLayoutClass->getBaseClass(t_index); }
    };

    template<typename t_Ty, size_t t_index> 
    struct rtti_data_registrer_helper_get_base_class : public rtti_data_registrer_helper_get_base_class_helper<t_Ty, t_index, ((phantom::meta_specifiers<t_Ty>::value & o_deferred) == o_deferred)>
    {
    };

    template<typename t_Ty>
    struct rtti_data_registrer_helper_base<t_Ty, 0>
    {
        template <typename> friend struct rtti_data_registrer;
        static void installRTTI(t_Ty* a_pThis, reflection::Class* a_pLayoutClass, void* a_pBase, reflection::Class* a_pBaseClass, connection::slot_pool* a_csac, dynamic_delete_func_t a_dynamic_delete_func, const rtti_data* a_pOwner, const rtti_data* a_pRTTI) {}
        static void uninstallRTTI(t_Ty* a_pThis, reflection::Class* a_pLayoutClass, size_t a_uiLevel) {}
    };

#define o_rtti_data_registrer_helper_base_register_0() 
#define o_rtti_data_registrer_helper_base_register_1()  o_rtti_data_registrer_helper_base_register_0() phantom::rtti_data_registrer<o_traits_t_Ty_base_class(0)>::installRTTI(a_pThis, rtti_data_registrer_helper_get_base_class<t_Ty, 0>::apply(a_pLayoutClass), a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_pOwner, (const rtti_data*)( ( ( ((size_t)static_cast<o_traits_t_Ty_base_class(0)*>(a_pThis)) - ((size_t)a_pThis) )==0 ) * (size_t)a_pRTTI));
#define o_rtti_data_registrer_helper_base_register_2()  o_rtti_data_registrer_helper_base_register_1() phantom::rtti_data_registrer<o_traits_t_Ty_base_class(1)>::installRTTI(a_pThis, rtti_data_registrer_helper_get_base_class<t_Ty, 1>::apply(a_pLayoutClass), a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_pOwner, (const rtti_data*)( ( ( ((size_t)static_cast<o_traits_t_Ty_base_class(1)*>(a_pThis)) - ((size_t)a_pThis) )==0 ) * (size_t)a_pRTTI));
#define o_rtti_data_registrer_helper_base_register_3()  o_rtti_data_registrer_helper_base_register_2() phantom::rtti_data_registrer<o_traits_t_Ty_base_class(2)>::installRTTI(a_pThis, rtti_data_registrer_helper_get_base_class<t_Ty, 2>::apply(a_pLayoutClass), a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_pOwner, (const rtti_data*)( ( ( ((size_t)static_cast<o_traits_t_Ty_base_class(2)*>(a_pThis)) - ((size_t)a_pThis) )==0 ) * (size_t)a_pRTTI));
#define o_rtti_data_registrer_helper_base_register_4()  o_rtti_data_registrer_helper_base_register_3() phantom::rtti_data_registrer<o_traits_t_Ty_base_class(3)>::installRTTI(a_pThis, rtti_data_registrer_helper_get_base_class<t_Ty, 3>::apply(a_pLayoutClass), a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_pOwner, (const rtti_data*)( ( ( ((size_t)static_cast<o_traits_t_Ty_base_class(3)*>(a_pThis)) - ((size_t)a_pThis) )==0 ) * (size_t)a_pRTTI));
#define o_rtti_data_registrer_helper_base_register_5()  o_rtti_data_registrer_helper_base_register_4() phantom::rtti_data_registrer<o_traits_t_Ty_base_class(4)>::installRTTI(a_pThis, rtti_data_registrer_helper_get_base_class<t_Ty, 4>::apply(a_pLayoutClass), a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_pOwner, (const rtti_data*)( ( ( ((size_t)static_cast<o_traits_t_Ty_base_class(4)*>(a_pThis)) - ((size_t)a_pThis) )==0 ) * (size_t)a_pRTTI));
#define o_rtti_data_registrer_helper_base_register_6()  o_rtti_data_registrer_helper_base_register_5() phantom::rtti_data_registrer<o_traits_t_Ty_base_class(5)>::installRTTI(a_pThis, rtti_data_registrer_helper_get_base_class<t_Ty, 5>::apply(a_pLayoutClass), a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_pOwner, (const rtti_data*)( ( ( ((size_t)static_cast<o_traits_t_Ty_base_class(5)*>(a_pThis)) - ((size_t)a_pThis) )==0 ) * (size_t)a_pRTTI));
#define o_rtti_data_registrer_helper_base_register_7()  o_rtti_data_registrer_helper_base_register_6() phantom::rtti_data_registrer<o_traits_t_Ty_base_class(6)>::installRTTI(a_pThis, rtti_data_registrer_helper_get_base_class<t_Ty, 6>::apply(a_pLayoutClass), a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_pOwner, (const rtti_data*)( ( ( ((size_t)static_cast<o_traits_t_Ty_base_class(6)*>(a_pThis)) - ((size_t)a_pThis) )==0 ) * (size_t)a_pRTTI));
#define o_rtti_data_registrer_helper_base_register_8()  o_rtti_data_registrer_helper_base_register_7() phantom::rtti_data_registrer<o_traits_t_Ty_base_class(7)>::installRTTI(a_pThis, rtti_data_registrer_helper_get_base_class<t_Ty, 7>::apply(a_pLayoutClass), a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_pOwner, (const rtti_data*)( ( ( ((size_t)static_cast<o_traits_t_Ty_base_class(7)*>(a_pThis)) - ((size_t)a_pThis) )==0 ) * (size_t)a_pRTTI));
#define o_rtti_data_registrer_helper_base_register_9()  o_rtti_data_registrer_helper_base_register_8() phantom::rtti_data_registrer<o_traits_t_Ty_base_class(8)>::installRTTI(a_pThis, rtti_data_registrer_helper_get_base_class<t_Ty, 8>::apply(a_pLayoutClass), a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_pOwner, (const rtti_data*)( ( ( ((size_t)static_cast<o_traits_t_Ty_base_class(8)*>(a_pThis)) - ((size_t)a_pThis) )==0 ) * (size_t)a_pRTTI));
#define o_rtti_data_registrer_helper_base_register_10() o_rtti_data_registrer_helper_base_register_9() phantom::rtti_data_registrer<o_traits_t_Ty_base_class(9)>::installRTTI(a_pThis, rtti_data_registrer_helper_get_base_class<t_Ty, 9>::apply(a_pLayoutClass), a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_pOwner, (const rtti_data*)( ( ( ((size_t)static_cast<o_traits_t_Ty_base_class(9)*>(a_pThis)) - ((size_t)a_pThis) )==0 ) * (size_t)a_pRTTI));

#define o_rtti_data_registrer_helper_base_unregister_0() 
#define o_rtti_data_registrer_helper_base_unregister_1()  o_rtti_data_registrer_helper_base_unregister_0() phantom::rtti_data_registrer<o_traits_t_Ty_base_class(0)>::uninstallRTTI(a_pThis, rtti_data_registrer_helper_get_base_class<t_Ty, 0>::apply(a_pLayoutClass), a_uiLevel, ( ( ((size_t)static_cast<o_traits_t_Ty_base_class(0)*>(a_pThis)) - ((size_t)a_pThis) )!=0 ));
#define o_rtti_data_registrer_helper_base_unregister_2()  o_rtti_data_registrer_helper_base_unregister_1() phantom::rtti_data_registrer<o_traits_t_Ty_base_class(1)>::uninstallRTTI(a_pThis, rtti_data_registrer_helper_get_base_class<t_Ty, 1>::apply(a_pLayoutClass), a_uiLevel, ( ( ((size_t)static_cast<o_traits_t_Ty_base_class(1)*>(a_pThis)) - ((size_t)a_pThis) )!=0 ));
#define o_rtti_data_registrer_helper_base_unregister_3()  o_rtti_data_registrer_helper_base_unregister_2() phantom::rtti_data_registrer<o_traits_t_Ty_base_class(2)>::uninstallRTTI(a_pThis, rtti_data_registrer_helper_get_base_class<t_Ty, 2>::apply(a_pLayoutClass), a_uiLevel, ( ( ((size_t)static_cast<o_traits_t_Ty_base_class(2)*>(a_pThis)) - ((size_t)a_pThis) )!=0 ));
#define o_rtti_data_registrer_helper_base_unregister_4()  o_rtti_data_registrer_helper_base_unregister_3() phantom::rtti_data_registrer<o_traits_t_Ty_base_class(3)>::uninstallRTTI(a_pThis, rtti_data_registrer_helper_get_base_class<t_Ty, 3>::apply(a_pLayoutClass), a_uiLevel, ( ( ((size_t)static_cast<o_traits_t_Ty_base_class(3)*>(a_pThis)) - ((size_t)a_pThis) )!=0 ));
#define o_rtti_data_registrer_helper_base_unregister_5()  o_rtti_data_registrer_helper_base_unregister_4() phantom::rtti_data_registrer<o_traits_t_Ty_base_class(4)>::uninstallRTTI(a_pThis, rtti_data_registrer_helper_get_base_class<t_Ty, 4>::apply(a_pLayoutClass), a_uiLevel, ( ( ((size_t)static_cast<o_traits_t_Ty_base_class(4)*>(a_pThis)) - ((size_t)a_pThis) )!=0 ));
#define o_rtti_data_registrer_helper_base_unregister_6()  o_rtti_data_registrer_helper_base_unregister_5() phantom::rtti_data_registrer<o_traits_t_Ty_base_class(5)>::uninstallRTTI(a_pThis, rtti_data_registrer_helper_get_base_class<t_Ty, 5>::apply(a_pLayoutClass), a_uiLevel, ( ( ((size_t)static_cast<o_traits_t_Ty_base_class(5)*>(a_pThis)) - ((size_t)a_pThis) )!=0 ));
#define o_rtti_data_registrer_helper_base_unregister_7()  o_rtti_data_registrer_helper_base_unregister_6() phantom::rtti_data_registrer<o_traits_t_Ty_base_class(6)>::uninstallRTTI(a_pThis, rtti_data_registrer_helper_get_base_class<t_Ty, 6>::apply(a_pLayoutClass), a_uiLevel, ( ( ((size_t)static_cast<o_traits_t_Ty_base_class(6)*>(a_pThis)) - ((size_t)a_pThis) )!=0 ));
#define o_rtti_data_registrer_helper_base_unregister_8()  o_rtti_data_registrer_helper_base_unregister_7() phantom::rtti_data_registrer<o_traits_t_Ty_base_class(7)>::uninstallRTTI(a_pThis, rtti_data_registrer_helper_get_base_class<t_Ty, 7>::apply(a_pLayoutClass), a_uiLevel, ( ( ((size_t)static_cast<o_traits_t_Ty_base_class(7)*>(a_pThis)) - ((size_t)a_pThis) )!=0 ));
#define o_rtti_data_registrer_helper_base_unregister_9()  o_rtti_data_registrer_helper_base_unregister_8() phantom::rtti_data_registrer<o_traits_t_Ty_base_class(8)>::uninstallRTTI(a_pThis, rtti_data_registrer_helper_get_base_class<t_Ty, 8>::apply(a_pLayoutClass), a_uiLevel, ( ( ((size_t)static_cast<o_traits_t_Ty_base_class(8)*>(a_pThis)) - ((size_t)a_pThis) )!=0 ));
#define o_rtti_data_registrer_helper_base_unregister_10() o_rtti_data_registrer_helper_base_unregister_9() phantom::rtti_data_registrer<o_traits_t_Ty_base_class(9)>::uninstallRTTI(a_pThis, rtti_data_registrer_helper_get_base_class<t_Ty, 9>::apply(a_pLayoutClass), a_uiLevel, ( ( ((size_t)static_cast<o_traits_t_Ty_base_class(9)*>(a_pThis)) - ((size_t)a_pThis) )!=0 ));

#define o_specialize_rtti_data_registrer_helper_base(_base_class_count_of_) \
    template<typename t_Ty>\
    struct rtti_data_registrer_helper_base<t_Ty, _base_class_count_of_>\
    {\
    static void installRTTI(t_Ty* a_pThis, reflection::Class* a_pLayoutClass, void* a_pBase, reflection::Class* a_pBaseClass, connection::slot_pool* a_csac, dynamic_delete_func_t a_dynamic_delete_func, const rtti_data* a_pOwner, const rtti_data* a_pRTTI) \
    {\
    o_rtti_data_registrer_helper_base_register_##_base_class_count_of_() \
    }\
    static void uninstallRTTI(t_Ty* a_pThis, reflection::Class* a_pLayoutClass, size_t a_uiLevel) \
    {\
    o_rtti_data_registrer_helper_base_unregister_##_base_class_count_of_() \
    }\
    };

    o_specialize_rtti_data_registrer_helper_base(1)
        o_specialize_rtti_data_registrer_helper_base(2)
        o_specialize_rtti_data_registrer_helper_base(3)
        o_specialize_rtti_data_registrer_helper_base(4)
        o_specialize_rtti_data_registrer_helper_base(5)
        o_specialize_rtti_data_registrer_helper_base(6)
        o_specialize_rtti_data_registrer_helper_base(7)
        o_specialize_rtti_data_registrer_helper_base(8)
        o_specialize_rtti_data_registrer_helper_base(9)

}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class rtti_data_registrer
///
/// \brief This helper registers/unregisters RTTI info of any class instance to the phantom system.
/// 	   You shouldn't use this unless you decide to customize installation from scratch.
/// 	   Remark : It's recommanded to make your installer inherits/call the default_installer member_functions
/// 	   instead of making a new one from scratch
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct rtti_data_registrer
{
    template<typename, int> friend struct detail::default_installer_helper;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn static void rtti_data_registrer::installRTTI(t_Ty* a_pThis, void* a_pBase,
    ///     phantom::reflection::Class* a_pBaseClass, connection::slot::allocator* a_csac)
    ///
    /// \brief Registers RTTI instance info of a_pThis.
    ///
    /// \author Vivien MILLET
    /// \date 26/11/2011
    ///
    /// \param [in,out] a_pThis      If non-null, instance pointer.
    /// \param [in,out] a_pBase      If non-null, base address (for multiple inheritance).
    /// \param [in,out] a_pBaseClass If non-null, the base class.
    /// \param [in,out] a_csac       If non-null, the slot allocator.
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    inline static void installRTTI(t_Ty* a_pThis, reflection::Class* a_pLayoutClass, void* a_pBase, phantom::reflection::Class* a_pBaseClass, connection::slot_pool* a_csac, dynamic_delete_func_t a_dynamic_delete_func, const rtti_data* a_pOwner, const rtti_data* a_pRTTI)
    {
        const rtti_data* pThisRtti = a_pRTTI ? a_pRTTI : addRttiData(a_pThis, rtti_data(a_pBaseClass, a_pLayoutClass, a_pBase, a_pThis, a_csac, a_dynamic_delete_func, a_pOwner));
        a_pLayoutClass->installInstanceDataMembers(a_pThis, pThisRtti);
        detail::rtti_data_registrer_helper_base<t_Ty, base_class_count_of<t_Ty>::value>::installRTTI(a_pThis, a_pLayoutClass, a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_pOwner, pThisRtti);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn static void rtti_data_registrer::uninstallRTTI(t_Ty* a_pThis)
    ///
    /// \brief Unregisters RTTI instance info of a_pThis.
    ///
    /// \author Vivien MILLET
    /// \date 26/11/2011
    ///
    /// \param [in,out] a_pThis If non-null, instance pointer.
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    inline static void uninstallRTTI(t_Ty* a_pThis, reflection::Class* a_pLayoutClass, size_t a_uiLevel, bool a_bRemoveRTTI)
    {
        detail::rtti_data_registrer_helper_base<t_Ty, base_class_count_of<t_Ty>::value>::uninstallRTTI(a_pThis, a_pLayoutClass, a_uiLevel);
        a_pLayoutClass->uninstallInstanceDataMembers(a_pThis, a_uiLevel+1);
        if(a_bRemoveRTTI)
        {
            removeRttiData(a_pThis, a_uiLevel);
        }
    }
};

/* installation */

enum default_installer_id
{
    default_installer_none,
    default_installer_static_rtti_registration,
    default_installer_static_rtti_registration_and_statechart,
    no_installer,
};

namespace detail 
{
    
    template<typename t_Ty>
    struct default_installer_helper<t_Ty, default_installer_static_rtti_registration>
    {
    public:
        o_forceinline static void install(reflection::Class* a_pClass, t_Ty* a_pInstance, const rtti_data* a_pOwner)
        {
            o_assert(!connection::slot_pool::hasAllocationController(a_pInstance, a_pClass));
            connection::slot_pool& ac = connection::slot_pool::allocationController(a_pInstance, a_pClass);
            phantom::rtti_data_registrer<t_Ty>::installRTTI(a_pInstance, a_pClass, a_pInstance, a_pClass, &ac, &phantom::dynamic_deleter<t_Ty>::dynamicDelete, a_pOwner, nullptr);
            a_pClass->registerInstance(a_pInstance);
        }
        o_forceinline static void uninstall(reflection::Class* a_pClass, t_Ty* a_pInstance, size_t a_uiLevel)
        {
            a_pClass->unregisterInstance(a_pInstance);
            phantom::rtti_data_registrer<t_Ty>::uninstallRTTI(a_pInstance, a_pClass, a_uiLevel, true);
            connection::slot_pool::eraseAllocationController(a_pInstance, a_pClass);
        }
        o_forceinline static void install(reflection::Class* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const rtti_data* a_pOwner)
        {
            byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
            for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
            {
                o_assert(!connection::slot_pool::hasAllocationController(pChunk, a_pClass));
                connection::slot_pool& ac = connection::slot_pool::allocationController(pChunk, a_pClass);
                phantom::rtti_data_registrer<t_Ty>::installRTTI(reinterpret_cast<t_Ty*>(pChunk), a_pClass, pChunk, a_pClass, &ac, &phantom::dynamic_deleter<t_Ty>::dynamicDelete, a_pOwner, nullptr) ;
                a_pClass->registerInstance(pChunk);
            }
        }
        o_forceinline static void uninstall(reflection::Class* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, size_t a_uiLevel)
        {
            byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
            for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
            {
                a_pClass->unregisterInstance(pChunk);
                phantom::rtti_data_registrer<t_Ty>::uninstallRTTI(reinterpret_cast<t_Ty*>(pChunk), a_pClass, a_uiLevel, true) ;
                connection::slot_pool::eraseAllocationController(pChunk, a_pClass);
            }
        }
    };

    template<typename t_Ty, uint t_base_class_count_of, boolean t_has_smdataptr>
    struct smdata_installer_of_helper ;

    template<typename t_Ty, uint t_baseclasscount>
    struct smdata_installer_of_helper_base;

    template<typename t_Ty>
    struct smdata_installer_of
        : public smdata_installer_of_helper<t_Ty
        , phantom::base_class_count_of<t_Ty>::value
        , has_smdataptr<t_Ty>::value>
    {
        template<typename t_Ty2, uint t_baseclasscount>
        friend struct smdata_installer_of_helper_base;
    };

    template<typename t_Ty, uint t_base_class_count_of, boolean t_has_smdataptr>
    struct smdata_installer_of_helper
        : public smdata_installer_of_helper_base<t_Ty, t_base_class_count_of>
    {
        template<typename t_Ty2, uint t_baseclasscount>
        friend struct smdata_installer_of_helper_base;
    };

    template<typename t_Ty, uint t_baseclasscount>
    struct smdata_installer_of_helper_base
    {
        template<typename t_Ty2, uint t_baseclasscount2>
        friend struct smdata_installer_of_helper_base;

        template<typename,int> friend struct default_installer_helper;
        o_forceinline static void install(t_Ty* a_pThis, phantom::state::base_state_machine_data* a_pSmdataptr)
        {
            smdata_installer_of<o_NESTED_TYPE base_class_of<t_Ty,t_baseclasscount-1>::type>::install(a_pThis, a_pSmdataptr);
            smdata_installer_of_helper_base<t_Ty, t_baseclasscount-1>::install(a_pThis, a_pSmdataptr);
        }
        o_forceinline static void uninstall(t_Ty* a_pThis)
        {
            smdata_installer_of<o_NESTED_TYPE base_class_of<t_Ty,t_baseclasscount-1>::type>::uninstall(a_pThis);
            smdata_installer_of_helper_base<t_Ty, t_baseclasscount-1>::uninstall(a_pThis);
        }
    };

    template<typename t_Ty>
    struct smdata_installer_of_helper_base<t_Ty, 0>
    {
        template<typename t_Ty2, uint t_baseclasscount>
        friend struct smdata_installer_of_helper_base;
        template<typename,int>
        friend struct default_installer_helper;
        o_forceinline static void install(t_Ty* a_pThis, phantom::state::base_state_machine_data* a_pSmdataptr) {}
        o_forceinline static void uninstall(t_Ty* a_pThis) {}
    };

    template<typename t_Ty, uint t_baseclasscount>
    struct smdata_installer_of_helper<t_Ty, t_baseclasscount, true>
    {
        template<typename,int> friend struct default_installer_helper;
        template<typename t_Ty2, uint t_baseclasscount2>
        friend struct smdata_installer_of_helper_base;
        o_forceinline static void install(t_Ty* a_pThis, phantom::state::base_state_machine_data* a_pSmdataptr)
        {
            *((phantom::state::base_state_machine_data**)(&(a_pThis->PHANTOM_CODEGEN_m_smdataptr))) = a_pSmdataptr;
        }
        o_forceinline static void uninstall(t_Ty* a_pThis)
        {
            *((phantom::state::base_state_machine_data**)(&(a_pThis->PHANTOM_CODEGEN_m_smdataptr))) = NULL;
        }
    };

    template<typename t_Ty>
    struct default_installer_helper<t_Ty, default_installer_static_rtti_registration_and_statechart>
    {
        typedef phantom::state::native::state_machine_data<t_Ty> state_machine_data;
    public:
        inline static void        install(reflection::Class* a_pClass,  t_Ty* a_pInstance, const rtti_data* a_pOwner )
        {
            default_installer_helper<t_Ty, default_installer_static_rtti_registration>::install(a_pClass, a_pInstance, a_pOwner);
            phantom::state::base_state_machine_data* smdataptr = new (phantom::allocator<state_machine_data>::allocate(o_memory_stat_insert_arguments)) state_machine_data(a_pInstance);
            smdata_installer_of<t_Ty>::install(a_pInstance, smdataptr);
        }
        inline static void        uninstall(reflection::Class* a_pClass,  t_Ty* a_pInstance, size_t a_uiLevel )
        {
            phantom::allocator<state_machine_data>::deallocate(
                (state_machine_data*)(
                static_cast<o_NESTED_TYPE first_base_statechart_class_of<t_Ty>::type*>(a_pInstance)->PHANTOM_CODEGEN_m_smdataptr
                ) o_memory_stat_append_arguments
                );
            default_installer_helper<t_Ty, default_installer_static_rtti_registration>::uninstall(a_pClass, a_pInstance, a_uiLevel);

        }
        inline static void        install(reflection::Class* a_pClass,  t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const rtti_data* a_pOwner )
        {
            default_installer_helper<t_Ty, default_installer_static_rtti_registration>::install(a_pClass, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOwner);
            // new (phantom::allocate<state_machine_data>(a_uiCount)) state_machine_data[a_uiCount];
            o_assert(false, "TODO : implement smdataptr installation for chunks");
        }
        inline static void        uninstall(reflection::Class* a_pClass,  t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, size_t a_uiLevel )
        {
            phantom::allocator<state_machine_data>::deallocate(
                (state_machine_data*)(
                static_cast<o_NESTED_TYPE first_base_statechart_class_of<t_Ty>::type*>(a_pChunk)->PHANTOM_CODEGEN_m_smdataptr
                )
                , a_uiCount o_memory_stat_append_arguments
                );
            default_installer_helper<t_Ty, default_installer_static_rtti_registration>::uninstall(a_pClass, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_uiLevel);
        }
    };

    template<typename t_Ty>
    struct default_installer_helper<t_Ty, default_installer_none>
    {
    public:
        o_forceinline static void install(reflection::Type* , t_Ty* a_pInstance, const rtti_data* a_pOwner) {  }
        o_forceinline static void uninstall(reflection::Type* , t_Ty* a_pInstance, size_t a_uiLevel) {  }
        o_forceinline static void install(reflection::Type* , t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const rtti_data* a_pOwner) {  }
        o_forceinline static void uninstall(reflection::Type* , t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, size_t a_uiLevel) {  }
    };
}

template<typename t_Ty>
struct default_installer : public detail::default_installer_helper<t_Ty,
    (boost::is_fundamental<t_Ty>::value
    OR phantom::is_signal_t<t_Ty>::value
    OR phantom::is_nullptr_t<t_Ty>::value
    OR (boost::is_pod<t_Ty>::value AND NOT(boost::is_class<t_Ty>::value))
    OR is_structure<t_Ty>::value)
    ? default_installer_none
    : (has_reflection_cascade<t_Ty>::value || is_meta_type<t_Ty>::value)
    ? has_statechart_cascade<t_Ty>::value
    ? default_installer_static_rtti_registration_and_statechart
    : default_installer_static_rtti_registration
    :  default_installer_none

>
{
    o_rebind(default_installer)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct installer
///
/// \brief  Installer. (see instance creation process)
/// 		Installation is applied just after construction
/// 		Uninstallation is applied just before destruction
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct installer : public default_installer<t_Ty>
{
};

o_namespace_end(phantom)

#endif // o_def_installer_h__