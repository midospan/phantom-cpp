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


#define NativeVTableInspector_hackmethod(_index_) \
    int NativeVTableInspector_hackmethod_##_index_() { return _index_; }


o_namespace_begin(phantom, reflection, native)

class o_export NativeVTableInspector
{
public:
    typedef int (NativeVTableInspector::*method_pointer)();

public:
    NativeVTableInspector_hackmethod(0)
    NativeVTableInspector_hackmethod(1)
    NativeVTableInspector_hackmethod(2)
    NativeVTableInspector_hackmethod(3)
    NativeVTableInspector_hackmethod(4)
    NativeVTableInspector_hackmethod(5)
    NativeVTableInspector_hackmethod(6)
    NativeVTableInspector_hackmethod(7)
    NativeVTableInspector_hackmethod(8)
    NativeVTableInspector_hackmethod(9)
    NativeVTableInspector_hackmethod(10)
    NativeVTableInspector_hackmethod(11)
    NativeVTableInspector_hackmethod(12)
    NativeVTableInspector_hackmethod(13)
    NativeVTableInspector_hackmethod(14)
    NativeVTableInspector_hackmethod(15)
    NativeVTableInspector_hackmethod(16)
    NativeVTableInspector_hackmethod(17)
    NativeVTableInspector_hackmethod(18)
    NativeVTableInspector_hackmethod(19)
    NativeVTableInspector_hackmethod(20)
    NativeVTableInspector_hackmethod(21)
    NativeVTableInspector_hackmethod(22)
    NativeVTableInspector_hackmethod(23)
    NativeVTableInspector_hackmethod(24)
    NativeVTableInspector_hackmethod(25)
    NativeVTableInspector_hackmethod(26)
    NativeVTableInspector_hackmethod(27)
    NativeVTableInspector_hackmethod(28)
    NativeVTableInspector_hackmethod(29)
    NativeVTableInspector_hackmethod(30)
    NativeVTableInspector_hackmethod(31)
    NativeVTableInspector_hackmethod(32)
    NativeVTableInspector_hackmethod(33)
    NativeVTableInspector_hackmethod(34)
    NativeVTableInspector_hackmethod(35)
    NativeVTableInspector_hackmethod(36)
    NativeVTableInspector_hackmethod(37)
    NativeVTableInspector_hackmethod(38)
    NativeVTableInspector_hackmethod(39)
    NativeVTableInspector_hackmethod(40)
    NativeVTableInspector_hackmethod(41)
    NativeVTableInspector_hackmethod(42)
    NativeVTableInspector_hackmethod(43)
    NativeVTableInspector_hackmethod(44)
    NativeVTableInspector_hackmethod(45)
    NativeVTableInspector_hackmethod(46)
    NativeVTableInspector_hackmethod(47)
    NativeVTableInspector_hackmethod(48)
    NativeVTableInspector_hackmethod(49)
    NativeVTableInspector_hackmethod(50)
    NativeVTableInspector_hackmethod(51)
    NativeVTableInspector_hackmethod(52)
    NativeVTableInspector_hackmethod(53)
    NativeVTableInspector_hackmethod(54)
    NativeVTableInspector_hackmethod(55)
    NativeVTableInspector_hackmethod(56)
    NativeVTableInspector_hackmethod(57)
    NativeVTableInspector_hackmethod(58)
    NativeVTableInspector_hackmethod(59)
    NativeVTableInspector_hackmethod(60)
    NativeVTableInspector_hackmethod(61)
    NativeVTableInspector_hackmethod(62)
    NativeVTableInspector_hackmethod(63)
    NativeVTableInspector_hackmethod(64)
    NativeVTableInspector_hackmethod(65)
    NativeVTableInspector_hackmethod(66)
    NativeVTableInspector_hackmethod(67)
    NativeVTableInspector_hackmethod(68)
    NativeVTableInspector_hackmethod(69)
    NativeVTableInspector_hackmethod(70)
    NativeVTableInspector_hackmethod(71)
    NativeVTableInspector_hackmethod(72)
    NativeVTableInspector_hackmethod(73)
    NativeVTableInspector_hackmethod(74)
    NativeVTableInspector_hackmethod(75)
    NativeVTableInspector_hackmethod(76)
    NativeVTableInspector_hackmethod(77)
    NativeVTableInspector_hackmethod(78)
    NativeVTableInspector_hackmethod(79)
    NativeVTableInspector_hackmethod(80)
    NativeVTableInspector_hackmethod(81)
    NativeVTableInspector_hackmethod(82)
    NativeVTableInspector_hackmethod(83)
    NativeVTableInspector_hackmethod(84)
    NativeVTableInspector_hackmethod(85)
    NativeVTableInspector_hackmethod(86)
    NativeVTableInspector_hackmethod(87)
    NativeVTableInspector_hackmethod(88)
    NativeVTableInspector_hackmethod(89)
    NativeVTableInspector_hackmethod(90)
    NativeVTableInspector_hackmethod(91)
    NativeVTableInspector_hackmethod(92)
    NativeVTableInspector_hackmethod(93)
    NativeVTableInspector_hackmethod(94)
    NativeVTableInspector_hackmethod(95)
    NativeVTableInspector_hackmethod(96)
    NativeVTableInspector_hackmethod(97)
    NativeVTableInspector_hackmethod(98)
    NativeVTableInspector_hackmethod(99)

protected:


    typedef method_pointer            vptr_imspostor_t [100]; 

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
        NativeVTableInspector::method_pointer mp = *reinterpret_cast<NativeVTableInspector::method_pointer*>(&ptr);
        return (reinterpret_cast<NativeVTableInspector*>(&sm_vptr_impostor)->*mp)();
#endif
    }

private:
    template<typename t_ClassPtr>
    class VirtualMethodCountHacker : public t_ClassPtr
    {
    public:
        virtual void PHANTOM_RESERVED_VirtualMethodCounter() { }

    };

public:
    template<typename t_ClassPtr>
    static int                        getVirtualMethodCount()
    {
        return getIndexOf(&VirtualMethodCountHacker<t_ClassPtr>::PHANTOM_RESERVED_VirtualMethodCounter);
    }
};


o_namespace_end(phantom, reflection, native)

#undef NativeVTableInspector_hackmethod

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
        struct virtual_method_count_of_helper
        {
            static size_t value()
            {
                return (size_t)phantom::reflection::native::NativeVTableInspector::getVirtualMethodCount<t_Ty>();
            }
        };
        template<typename t_Ty, int vtable_id>
        struct virtual_method_count_of_helper<t_Ty, vtable_id, false>
        {
            static size_t value()
            {
                return 0;
            }
        };
        template<typename t_Ty, int vtable_id = 0>
        struct virtual_method_count_of : public virtual_method_count_of_helper<t_Ty, vtable_id, boost::is_class<t_Ty>::value>
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
                size_t instanceVirtualMethodCount = virtualMethodCountOf<top_class>();
                vtable_info vtable;
                vtable.count = instanceVirtualMethodCount;
                vtable.offset = vtable_offset;
                vtable.methods = *((void***)((byte*)a_pInstance + vtable_offset));
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
    size_t     virtualMethodCountOf()
    {
        return detail::virtual_method_count_of<t_Ty>::value();
    }

    /// returns the vtable index of the given method or -1 if it's not a virtual method
    /// throw static assert if the tested argument is not a member function pointer 
    template<typename t_Ty>
    int         virtualMethodIndexOf(t_Ty method)
    {
        o_static_assert_msg(boost::is_member_function_pointer<t_Ty>::value, "Given argument is not a member function pointer");
        return phantom::reflection::native::NativeVTableInspector::getIndexOf(method);
    }
}


#endif