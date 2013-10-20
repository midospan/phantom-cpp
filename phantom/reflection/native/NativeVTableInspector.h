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

#ifndef o_phantom_reflection_native_NativeVTableInspector_h__
#define o_phantom_reflection_native_NativeVTableInspector_h__

/* ****************** Includes ******************* */
/* ************* t_Class Declarations ************** */
/* *********************************************** */

#include <phantom/_kernel.noclassdef.h>


#define NativeVTableInspector_hack_member_function(_index_) \
    int NativeVTableInspector_hack_member_function_##_index_() { return _index_; }


o_namespace_begin(phantom, reflection, native)

class o_export NativeVTableInspector
{
public:
    typedef int (NativeVTableInspector::*member_function_pointer)();

public:
    NativeVTableInspector_hack_member_function(0)
    NativeVTableInspector_hack_member_function(1)
    NativeVTableInspector_hack_member_function(2)
    NativeVTableInspector_hack_member_function(3)
    NativeVTableInspector_hack_member_function(4)
    NativeVTableInspector_hack_member_function(5)
    NativeVTableInspector_hack_member_function(6)
    NativeVTableInspector_hack_member_function(7)
    NativeVTableInspector_hack_member_function(8)
    NativeVTableInspector_hack_member_function(9)
    NativeVTableInspector_hack_member_function(10)
    NativeVTableInspector_hack_member_function(11)
    NativeVTableInspector_hack_member_function(12)
    NativeVTableInspector_hack_member_function(13)
    NativeVTableInspector_hack_member_function(14)
    NativeVTableInspector_hack_member_function(15)
    NativeVTableInspector_hack_member_function(16)
    NativeVTableInspector_hack_member_function(17)
    NativeVTableInspector_hack_member_function(18)
    NativeVTableInspector_hack_member_function(19)
    NativeVTableInspector_hack_member_function(20)
    NativeVTableInspector_hack_member_function(21)
    NativeVTableInspector_hack_member_function(22)
    NativeVTableInspector_hack_member_function(23)
    NativeVTableInspector_hack_member_function(24)
    NativeVTableInspector_hack_member_function(25)
    NativeVTableInspector_hack_member_function(26)
    NativeVTableInspector_hack_member_function(27)
    NativeVTableInspector_hack_member_function(28)
    NativeVTableInspector_hack_member_function(29)
    NativeVTableInspector_hack_member_function(30)
    NativeVTableInspector_hack_member_function(31)
    NativeVTableInspector_hack_member_function(32)
    NativeVTableInspector_hack_member_function(33)
    NativeVTableInspector_hack_member_function(34)
    NativeVTableInspector_hack_member_function(35)
    NativeVTableInspector_hack_member_function(36)
    NativeVTableInspector_hack_member_function(37)
    NativeVTableInspector_hack_member_function(38)
    NativeVTableInspector_hack_member_function(39)
    NativeVTableInspector_hack_member_function(40)
    NativeVTableInspector_hack_member_function(41)
    NativeVTableInspector_hack_member_function(42)
    NativeVTableInspector_hack_member_function(43)
    NativeVTableInspector_hack_member_function(44)
    NativeVTableInspector_hack_member_function(45)
    NativeVTableInspector_hack_member_function(46)
    NativeVTableInspector_hack_member_function(47)
    NativeVTableInspector_hack_member_function(48)
    NativeVTableInspector_hack_member_function(49)
    NativeVTableInspector_hack_member_function(50)
    NativeVTableInspector_hack_member_function(51)
    NativeVTableInspector_hack_member_function(52)
    NativeVTableInspector_hack_member_function(53)
    NativeVTableInspector_hack_member_function(54)
    NativeVTableInspector_hack_member_function(55)
    NativeVTableInspector_hack_member_function(56)
    NativeVTableInspector_hack_member_function(57)
    NativeVTableInspector_hack_member_function(58)
    NativeVTableInspector_hack_member_function(59)
    NativeVTableInspector_hack_member_function(60)
    NativeVTableInspector_hack_member_function(61)
    NativeVTableInspector_hack_member_function(62)
    NativeVTableInspector_hack_member_function(63)
    NativeVTableInspector_hack_member_function(64)
    NativeVTableInspector_hack_member_function(65)
    NativeVTableInspector_hack_member_function(66)
    NativeVTableInspector_hack_member_function(67)
    NativeVTableInspector_hack_member_function(68)
    NativeVTableInspector_hack_member_function(69)
    NativeVTableInspector_hack_member_function(70)
    NativeVTableInspector_hack_member_function(71)
    NativeVTableInspector_hack_member_function(72)
    NativeVTableInspector_hack_member_function(73)
    NativeVTableInspector_hack_member_function(74)
    NativeVTableInspector_hack_member_function(75)
    NativeVTableInspector_hack_member_function(76)
    NativeVTableInspector_hack_member_function(77)
    NativeVTableInspector_hack_member_function(78)
    NativeVTableInspector_hack_member_function(79)
    NativeVTableInspector_hack_member_function(80)
    NativeVTableInspector_hack_member_function(81)
    NativeVTableInspector_hack_member_function(82)
    NativeVTableInspector_hack_member_function(83)
    NativeVTableInspector_hack_member_function(84)
    NativeVTableInspector_hack_member_function(85)
    NativeVTableInspector_hack_member_function(86)
    NativeVTableInspector_hack_member_function(87)
    NativeVTableInspector_hack_member_function(88)
    NativeVTableInspector_hack_member_function(89)
    NativeVTableInspector_hack_member_function(90)
    NativeVTableInspector_hack_member_function(91)
    NativeVTableInspector_hack_member_function(92)
    NativeVTableInspector_hack_member_function(93)
    NativeVTableInspector_hack_member_function(94)
    NativeVTableInspector_hack_member_function(95)
    NativeVTableInspector_hack_member_function(96)
    NativeVTableInspector_hack_member_function(97)
    NativeVTableInspector_hack_member_function(98)
    NativeVTableInspector_hack_member_function(99)

protected:


    typedef member_function_pointer            vptr_imspostor_t [100]; 

    static vptr_imspostor_t            sm_vtable_impostor;
    static int                        sm_inspection_result;
    static void*                    sm_vptr_impostor;

public:
    template<typename _FuncPtr>
    static int                        getIndexOf(_FuncPtr ptr)
    {
#if o_COMPILER == o_COMPILER_GCC
        union
        {
            struct {
                union {
                    void (*fn)();
                    ptrdiff_t vtable_index;
                };
                ptrdiff_t delta;
            } wrap_fp;

            _FuncPtr fp;
        } u;
        u.fp = ptr;
        std::cout<<u.wrap_fp.delta<<std::endl;
        return (u.wrap_fp.vtable_index-1)/sizeof(u.wrap_fp.fn);
#else
        NativeVTableInspector::member_function_pointer mp = *reinterpret_cast<NativeVTableInspector::member_function_pointer*>(&ptr);
        return (reinterpret_cast<NativeVTableInspector*>(&sm_vptr_impostor)->*mp)();
#endif
    }

private:
    template<typename t_ClassPtr>
    class VirtualMemberFunctionCountHacker : public t_ClassPtr
    {
    public:
        virtual void PHANTOM_RESERVED_VirtualMemberFunctionCounter() { }

    };

public:
    template<typename t_ClassPtr>
    static int                        getVirtualMemberFunctionCount()
    {
        return getIndexOf(&VirtualMemberFunctionCountHacker<t_ClassPtr>::PHANTOM_RESERVED_VirtualMemberFunctionCounter);
    }
};


o_namespace_end(phantom, reflection, native)

#undef NativeVTableInspector_hack_member_function

// Create easy access traits
namespace phantom
{
    template<typename t_Ty>
    struct vtable_count_of;
    template<typename t_Ty, int index>
    struct vtable_offset_of;
    template<typename t_Ty, int index>
    struct vtable_base_class_of;
    template<typename t_Ty, int index>
    struct vtable_top_class_of;

    namespace detail 
    {

        template<typename t_Ty, int t_super_class_count>
        struct vtable_count_of_helper_cascade
        {
            enum { value = 
                + vtable_count_of<super_class_of<t_Ty, t_super_class_count-1>::type>::value 
                + vtable_count_of_helper_cascade<t_Ty, t_super_class_count-1>::value};
        };

        template<typename t_Ty>
        struct vtable_count_of_helper_cascade<t_Ty, 0>
        {
            enum { value = 1 };
        };

        template<typename t_Ty>
        struct vtable_count_of_helper_cascade<t_Ty, 1>
        {
            enum { value = vtable_count_of<super_class_of<t_Ty, 0>::type>::value };
        };

        template<typename t_Ty, bool t_is_polymorphic>
        struct vtable_count_of_helper : public vtable_count_of_helper_cascade<t_Ty, super_class_count_of<t_Ty>::value>
        {
        };

        template<typename t_Ty>
        struct vtable_count_of_helper<t_Ty, false>
        {
            enum { value = 0 };
        };

        template<typename t_Ty, int vtable_id, bool is_class>
        struct virtual_member_function_count_of_helper
        {
            static size_t value()
            {
                return (size_t)phantom::reflection::native::NativeVTableInspector::getVirtualMemberFunctionCount<t_Ty>();
            }
        };
        template<typename t_Ty, int vtable_id>
        struct virtual_member_function_count_of_helper<t_Ty, vtable_id, false>
        {
            static size_t value()
            {
                return 0;
            }
        };
        template<typename t_Ty, int vtable_id = 0>
        struct virtual_member_function_count_of : public virtual_member_function_count_of_helper<t_Ty, vtable_id, boost::is_class<t_Ty>::value>
        {
        };
        

        template<typename t_Ty, int id, int t_super_class_count, size_t offset>
        struct vtable_offset_of_cascade
        {
            const static size_t super_index = super_class_count_of<t_Ty>::value - t_super_class_count ;
            const static size_t temp_value = vtable_offset_of<super_class_of<t_Ty, super_index>::type, id>::value ;
            const static size_t value = 
                (temp_value == 0xffffff) // Not matching
                ? vtable_offset_of_cascade<t_Ty, id - vtable_count_of<super_class_of<t_Ty, super_index>::type>::value, t_super_class_count-1, offset + sizeof(super_class_of<t_Ty, super_index>::type)>::value
                : (offset + temp_value);
        };

        template<typename t_Ty, int id, size_t offset>
        struct vtable_offset_of_cascade<t_Ty, id, 0, offset>
        {
            const static size_t value = (id == 0) ? offset : 0xffffff;
        };


        template<typename t_Ty, int id, size_t offset>
        struct vtable_offset_of_cascade<t_Ty, id, 1, offset>
        {
            const static size_t super_index = super_class_count_of<t_Ty>::value - 1;
            const static size_t temp_value = vtable_offset_of<super_class_of<t_Ty, super_index>::type, id>::value;
            const static size_t value = (temp_value == 0xffffff) // Not matching
                ? (size_t)0xffffff
                : (offset + temp_value);
        };

        template<typename t_Ty, int id, bool t_is_polymorphic>
        struct vtable_offset_of_helper : public vtable_offset_of_cascade<t_Ty, id, super_class_count_of<t_Ty>::value, 0>
        {

        };

        template<typename t_Ty, int id>
        struct vtable_offset_of_helper<t_Ty, id, false>
        {
            const static size_t value = 0xffffffff;
        };


        template<bool t_cond, typename t_True, typename t_False>
        struct vtable_class_type_selector
        {
            typedef t_True type;
        };

        template<typename t_True, typename t_False>
        struct vtable_class_type_selector<false, t_True, t_False>
        {
            typedef t_False type;
        };

        template<typename t_Ty, int id, int t_super_class_count>
        struct vtable_base_class_of_cascade
        {
            const static size_t super_index = super_class_count_of<t_Ty>::value - t_super_class_count ;
            typedef typename vtable_base_class_of<typename super_class_of<t_Ty, super_index>::type, id>::type temp_type;
            typedef typename vtable_class_type_selector<boost::is_void<temp_type>::value  // Not matching
                , typename vtable_base_class_of_cascade<t_Ty, id - vtable_count_of<typename super_class_of<t_Ty, super_index>::type>::value, t_super_class_count-1>::type
                , temp_type>::type type;
        };

        template<typename t_Ty, int id>
        struct vtable_base_class_of_cascade<t_Ty, id, 0>
        {
            typedef typename vtable_class_type_selector<(id == 0), t_Ty, void>::type type;
        };


        template<typename t_Ty, int id>
        struct vtable_base_class_of_cascade<t_Ty, id, 1>
        {
            const static size_t super_index = super_class_count_of<t_Ty>::value - 1;
            typedef typename vtable_base_class_of<typename super_class_of<t_Ty, super_index>::type, id>::type temp_type;
            typedef typename vtable_class_type_selector<boost::is_void<temp_type>::value // Not matching
                , void
                , temp_type>::type type;
        };

        template<typename t_Ty, int id, bool t_is_polymorphic>
        struct vtable_base_class_of_helper 
            : public vtable_base_class_of_cascade<t_Ty, id, super_class_count_of<t_Ty>::value>
        {

        };

        template<typename t_Ty, int id>
        struct vtable_base_class_of_helper<t_Ty, id, false>
        {
            typedef void type;
        };





        template<typename t_Ty, int id, int t_super_class_count>
        struct vtable_top_class_of_cascade
        {
            const static size_t super_index = super_class_count_of<t_Ty>::value - t_super_class_count ;
            typedef typename vtable_top_class_of<typename super_class_of<t_Ty, super_index>::type, id>::type temp_type;
            typedef typename vtable_class_type_selector<boost::is_void<temp_type>::value  // Not matching
                , typename vtable_top_class_of_cascade<t_Ty, id - vtable_count_of<typename super_class_of<t_Ty, super_index>::type>::value, t_super_class_count-1>::type
                , temp_type>::type type;
        };

        template<typename t_Ty, int id>
        struct vtable_top_class_of_cascade<t_Ty, id, 0>
        {
            typedef typename vtable_class_type_selector<(id == 0), t_Ty, void>::type type;
        };


        template<typename t_Ty, int id>
        struct vtable_top_class_of_cascade<t_Ty, id, 1>
        {
            const static size_t super_index = super_class_count_of<t_Ty>::value - 1;
            typedef typename vtable_top_class_of<typename super_class_of<t_Ty, super_index>::type, id>::type temp_type;
            typedef typename vtable_class_type_selector<boost::is_void<temp_type>::value // Not matching
                , void
                , temp_type>::type type;
        };

        template<typename t_Ty, int id, bool t_is_polymorphic>
        struct vtable_top_class_of_helper 
            : public vtable_top_class_of_cascade<t_Ty, id, super_class_count_of<t_Ty>::value>
        {

        };

        template<typename t_Ty, int id>
        struct vtable_top_class_of_helper<t_Ty, id, false>
        {
            typedef void type;
        };


        template<typename t_Ty>
        struct vtable_top_class_of_helper<t_Ty, 0, true>
        {
            typedef t_Ty type;
        };
        
        template<typename t_Ty, int t_vtable_count>
        struct vtable_info_extractor_cascade
        {
            const static size_t vtable_offset = vtable_offset_of<t_Ty, t_vtable_count-1>::value;
            typedef typename vtable_top_class_of<t_Ty, t_vtable_count-1>::type top_class;
            static void apply(const void* a_pInstance, vector<vtable_info>& vtables) 
            {
                size_t instanceVirtualMemberFunctionCount = virtualMemberFunctionCountOf<top_class>();
                vtable_info vtable;
                vtable.count = instanceVirtualMemberFunctionCount;
                vtable.offset = vtable_offset;
                vtable.member_functions = *((void***)((byte*)a_pInstance + vtable_offset));
                vtable_info_extractor_cascade<t_Ty, t_vtable_count-1>::apply(a_pInstance, vtables);
                vtables.push_back(vtable);
            }            
        };

        template<typename t_Ty>
        struct vtable_info_extractor_cascade<t_Ty, 0>
        {
            static void apply(const void* a_pInstance, vector<vtable_info>& vtables) 
            {
            }
        };

        template<typename t_Ty, bool t_is_polymorphic>
        struct vtable_info_extractor_helper : public vtable_info_extractor_cascade<t_Ty, vtable_count_of<t_Ty>::value>
        {
        };

        template<typename t_Ty>
        struct vtable_info_extractor_helper<t_Ty, false>
        {
            static void apply(const void* a_pInstance, vector<vtable_info>& vtables) { o_assert("Non-polymorphic type doesn't have vtables so they cannot be copied"); }
        };

    }

    template<typename t_Ty>
    struct vtable_count_of : public detail::vtable_count_of_helper<t_Ty, boost::is_polymorphic<t_Ty>::value>
    {

    };

    template<typename t_Ty, int id>
    struct vtable_offset_of : public detail::vtable_offset_of_helper<t_Ty, id, boost::is_polymorphic<t_Ty>::value>
    {

    };

    template<typename t_Ty, int id>
    struct vtable_base_class_of : public detail::vtable_base_class_of_helper<t_Ty, id, boost::is_polymorphic<t_Ty>::value>
    {

    };
    template<typename t_Ty, int id>
    struct vtable_top_class_of : public detail::vtable_top_class_of_helper<t_Ty, id, boost::is_polymorphic<t_Ty>::value>
    {

    };

    template<typename t_Ty>
    struct vtable_info_extractor : public detail::vtable_info_extractor_helper<t_Ty, boost::is_polymorphic<t_Ty>::value>
    {

    };

    template<typename t_Ty>
    size_t     virtualMemberFunctionCountOf()
    {
        return detail::virtual_member_function_count_of<t_Ty>::value();
    }

    /// returns the vtable index of the given member_function or -1 if it's not a virtual member_function
    /// throw static assert if the tested argument is not a member function pointer 
    template<typename t_Ty>
    int         virtualMemberFunctionIndexOf(t_Ty member_function)
    {
        o_static_assert_msg(boost::is_member_function_pointer<t_Ty>::value, "Given argument is not a member function pointer");
        return phantom::reflection::native::NativeVTableInspector::getIndexOf(member_function);
    }
}


#endif