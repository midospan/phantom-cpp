/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_native_NativeVTableSizeComputer_h__
#define o_phantom_reflection_native_NativeVTableSizeComputer_h__

/* ****************** Includes ******************* */
/* ************* t_Class Declarations ************** */
/* *********************************************** */

#include <phantom/def_export.h>

o_namespace_begin(phantom, reflection, native)

template<typename t_Ty>
class NativeVTableSizeComputer;

template<typename t_Ty>
struct NativeVTableSizeComputer<t_Ty()> : public t_Ty
{
    virtual void PHANTOM_RESERVED_VTableSizeComputer() {}
    static size_t apply() { return NativeVTableInspector::getIndexOf(&NativeVTableSizeComputer<t_Ty()>::PHANTOM_RESERVED_VTableSizeComputer); }
};

template<typename t_Ty
    , typename t_0
>
struct NativeVTableSizeComputer<t_Ty(t_0)> : public t_Ty
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value, "t_Ty must be polymorphic");
    typedef typename boost::remove_reference<typename boost::remove_cv<t_0>::type>::type t_0nocvr;
    static t_0nocvr* t0() { static t_0nocvr* dummy; return dummy; }
    NativeVTableSizeComputer() : t_Ty(*t0()) { }
    virtual void PHANTOM_RESERVED_VTableSizeComputer() {}
    static size_t apply() { return NativeVTableInspector::getIndexOf(&NativeVTableSizeComputer<t_Ty(t_0)>::PHANTOM_RESERVED_VTableSizeComputer); }
};

template<typename t_Ty
    , typename t_0
    , typename t_1
>
struct NativeVTableSizeComputer<t_Ty(t_0, t_1)> : public t_Ty
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value, "t_Ty must be polymorphic");
    typedef typename boost::remove_reference<typename boost::remove_cv<t_0>::type>::type t_0nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_1>::type>::type t_1nocvr;
    static t_0nocvr* t0() { static t_0nocvr* dummy; return dummy; }
    static t_1nocvr* t1() { static t_1nocvr* dummy; return dummy; }
    NativeVTableSizeComputer() : t_Ty(*t0(), *t1()) { }
    virtual void PHANTOM_RESERVED_VTableSizeComputer() {}
    static size_t apply() { return NativeVTableInspector::getIndexOf(&NativeVTableSizeComputer<t_Ty(t_0, t_1)>::PHANTOM_RESERVED_VTableSizeComputer); }
};

template<typename t_Ty
    , typename t_0
    , typename t_1
    , typename t_2
>
struct NativeVTableSizeComputer<t_Ty(t_0, t_1, t_2)> : public t_Ty
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value, "t_Ty must be polymorphic");
    typedef typename boost::remove_reference<typename boost::remove_cv<t_0>::type>::type t_0nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_1>::type>::type t_1nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_2>::type>::type t_2nocvr;
    static t_0nocvr* t0() { static t_0nocvr* dummy; return dummy; }
    static t_1nocvr* t1() { static t_1nocvr* dummy; return dummy; }
    static t_2nocvr* t2() { static t_2nocvr* dummy; return dummy; }
    NativeVTableSizeComputer() : t_Ty(*t0(), *t1(), *t2()) { } 
    virtual void PHANTOM_RESERVED_VTableSizeComputer() {} 
    static size_t apply() { return NativeVTableInspector::getIndexOf(&NativeVTableSizeComputer<t_Ty(t_0, t_1, t_2)>::PHANTOM_RESERVED_VTableSizeComputer); }
};

template<typename t_Ty
    , typename t_0
    , typename t_1
    , typename t_2
    , typename t_3
>
struct NativeVTableSizeComputer<t_Ty(t_0, t_1, t_2, t_3)> : public t_Ty
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value, "t_Ty must be polymorphic");
    typedef typename boost::remove_reference<typename boost::remove_cv<t_0>::type>::type t_0nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_1>::type>::type t_1nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_2>::type>::type t_2nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_3>::type>::type t_3nocvr;
    static t_0nocvr* t0() { static t_0nocvr* dummy; return dummy; }
    static t_1nocvr* t1() { static t_1nocvr* dummy; return dummy; }
    static t_2nocvr* t2() { static t_2nocvr* dummy; return dummy; }
    static t_3nocvr* t3() { static t_3nocvr* dummy; return dummy; }
    NativeVTableSizeComputer() : t_Ty(*t0(), *t1(), *t2(), *t3()) { }
    virtual void PHANTOM_RESERVED_VTableSizeComputer() {}
    static size_t apply() { return NativeVTableInspector::getIndexOf(&NativeVTableSizeComputer<t_Ty(t_0, t_1, t_2, t_3)>::PHANTOM_RESERVED_VTableSizeComputer); }
};

template<typename t_Ty
    , typename t_0
    , typename t_1
    , typename t_2
    , typename t_3
    , typename t_4
>
struct NativeVTableSizeComputer<t_Ty(t_0, t_1, t_2, t_3, t_4)> : public t_Ty
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value, "t_Ty must be polymorphic");
    typedef typename boost::remove_reference<typename boost::remove_cv<t_0>::type>::type t_0nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_1>::type>::type t_1nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_2>::type>::type t_2nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_3>::type>::type t_3nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_4>::type>::type t_4nocvr;
    static t_0nocvr* t0() { static t_0nocvr* dummy; return dummy; }
    static t_1nocvr* t1() { static t_1nocvr* dummy; return dummy; }
    static t_2nocvr* t2() { static t_2nocvr* dummy; return dummy; }
    static t_3nocvr* t3() { static t_3nocvr* dummy; return dummy; }
    static t_4nocvr* t4() { static t_4nocvr* dummy; return dummy; }
    NativeVTableSizeComputer() : t_Ty(*t0(), *t1(), *t2(), *t3(), *t4()) { }  
    virtual void PHANTOM_RESERVED_VTableSizeComputer() {}
    static size_t apply() { return NativeVTableInspector::getIndexOf(&NativeVTableSizeComputer<t_Ty(t_0, t_1, t_2, t_3, t_4)>::PHANTOM_RESERVED_VTableSizeComputer); }
};

template<typename t_Ty
    , typename t_0
    , typename t_1
    , typename t_2
    , typename t_3
    , typename t_4
    , typename t_5
>
struct NativeVTableSizeComputer<t_Ty(t_0, t_1, t_2, t_3, t_4, t_5)> : public t_Ty
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value, "t_Ty must be polymorphic");
    typedef typename boost::remove_reference<typename boost::remove_cv<t_0>::type>::type t_0nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_1>::type>::type t_1nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_2>::type>::type t_2nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_3>::type>::type t_3nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_4>::type>::type t_4nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_5>::type>::type t_5nocvr;
    static t_0nocvr* t0() { static t_0nocvr* dummy; return dummy; }
    static t_1nocvr* t1() { static t_1nocvr* dummy; return dummy; }
    static t_2nocvr* t2() { static t_2nocvr* dummy; return dummy; }
    static t_3nocvr* t3() { static t_3nocvr* dummy; return dummy; }
    static t_4nocvr* t4() { static t_4nocvr* dummy; return dummy; }
    static t_5nocvr* t5() { static t_5nocvr* dummy; return dummy; }
    NativeVTableSizeComputer() : t_Ty(*t0(), *t1(), *t2(), *t3(), *t4(), *t5()) { } 
    virtual void PHANTOM_RESERVED_VTableSizeComputer() {}
    static size_t apply() { return NativeVTableInspector::getIndexOf(&NativeVTableSizeComputer<t_Ty(t_0, t_1, t_2, t_3, t_4, t_5)>::PHANTOM_RESERVED_VTableSizeComputer); }
};

template<typename t_Ty
    , typename t_0
    , typename t_1
    , typename t_2
    , typename t_3
    , typename t_4
    , typename t_5
    , typename t_6
>
struct NativeVTableSizeComputer<t_Ty(t_0, t_1, t_2, t_3, t_4, t_5, t_6)> : public t_Ty
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value, "t_Ty must be polymorphic");
    typedef typename boost::remove_reference<typename boost::remove_cv<t_0>::type>::type t_0nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_1>::type>::type t_1nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_2>::type>::type t_2nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_3>::type>::type t_3nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_4>::type>::type t_4nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_5>::type>::type t_5nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_6>::type>::type t_6nocvr;
    static t_0nocvr* t0() { static t_0nocvr* dummy; return dummy; }
    static t_1nocvr* t1() { static t_1nocvr* dummy; return dummy; }
    static t_2nocvr* t2() { static t_2nocvr* dummy; return dummy; }
    static t_3nocvr* t3() { static t_3nocvr* dummy; return dummy; }
    static t_4nocvr* t4() { static t_4nocvr* dummy; return dummy; }
    static t_5nocvr* t5() { static t_5nocvr* dummy; return dummy; }
    static t_6nocvr* t6() { static t_6nocvr* dummy; return dummy; }
    NativeVTableSizeComputer() : t_Ty(*t0(), *t1(), *t2(), *t3(), *t4(), *t5(), *t6()) { } 
    virtual void PHANTOM_RESERVED_VTableSizeComputer() {}
    static size_t apply() { return NativeVTableInspector::getIndexOf(&NativeVTableSizeComputer<t_Ty(t_0, t_1, t_2, t_3, t_4, t_5, t_6)>::PHANTOM_RESERVED_VTableSizeComputer); }
};

template<typename t_Ty
    , typename t_0
    , typename t_1
    , typename t_2
    , typename t_3
    , typename t_4
    , typename t_5
    , typename t_6
    , typename t_7
>
struct NativeVTableSizeComputer<t_Ty(t_0, t_1, t_2, t_3, t_4, t_5, t_6, t_7)> : public t_Ty
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value, "t_Ty must be polymorphic");
    typedef typename boost::remove_reference<typename boost::remove_cv<t_0>::type>::type t_0nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_1>::type>::type t_1nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_2>::type>::type t_2nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_3>::type>::type t_3nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_4>::type>::type t_4nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_5>::type>::type t_5nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_6>::type>::type t_6nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_7>::type>::type t_7nocvr;
    static t_0nocvr* t0() { static t_0nocvr* dummy; return dummy; }
    static t_1nocvr* t1() { static t_1nocvr* dummy; return dummy; }
    static t_2nocvr* t2() { static t_2nocvr* dummy; return dummy; }
    static t_3nocvr* t3() { static t_3nocvr* dummy; return dummy; }
    static t_4nocvr* t4() { static t_4nocvr* dummy; return dummy; }
    static t_5nocvr* t5() { static t_5nocvr* dummy; return dummy; }
    static t_6nocvr* t6() { static t_6nocvr* dummy; return dummy; }
    static t_7nocvr* t7() { static t_7nocvr* dummy; return dummy; }
    NativeVTableSizeComputer() : t_Ty(*t0(), *t1(), *t2(), *t3(), *t4(), *t5(), *t6(), *t7()) { } 
    virtual void PHANTOM_RESERVED_VTableSizeComputer() {}
    static size_t apply() { return NativeVTableInspector::getIndexOf(&NativeVTableSizeComputer<t_Ty(t_0, t_1, t_2, t_3, t_4, t_5, t_6, t_7)>::PHANTOM_RESERVED_VTableSizeComputer); }
};

template<typename t_Ty
    , typename t_0
    , typename t_1
    , typename t_2
    , typename t_3
    , typename t_4
    , typename t_5
    , typename t_6
    , typename t_7
    , typename t_8
>
struct NativeVTableSizeComputer<t_Ty(t_0, t_1, t_2, t_3, t_4, t_5, t_6, t_7, t_8)> : public t_Ty
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value, "t_Ty must be polymorphic");
    typedef typename boost::remove_reference<typename boost::remove_cv<t_0>::type>::type t_0nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_1>::type>::type t_1nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_2>::type>::type t_2nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_3>::type>::type t_3nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_4>::type>::type t_4nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_5>::type>::type t_5nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_6>::type>::type t_6nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_7>::type>::type t_7nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_8>::type>::type t_8nocvr;
    static t_0nocvr* t0() { static t_0nocvr* dummy; return dummy; }
    static t_1nocvr* t1() { static t_1nocvr* dummy; return dummy; }
    static t_2nocvr* t2() { static t_2nocvr* dummy; return dummy; }
    static t_3nocvr* t3() { static t_3nocvr* dummy; return dummy; }
    static t_4nocvr* t4() { static t_4nocvr* dummy; return dummy; }
    static t_5nocvr* t5() { static t_5nocvr* dummy; return dummy; }
    static t_6nocvr* t6() { static t_6nocvr* dummy; return dummy; }
    static t_7nocvr* t7() { static t_7nocvr* dummy; return dummy; }
    static t_8nocvr* t8() { static t_8nocvr* dummy; return dummy; }
    NativeVTableSizeComputer() : t_Ty(*t0(), *t1(), *t2(), *t3(), *t4(), *t5(), *t6(), *t7(), *t8()) { }  
    virtual void PHANTOM_RESERVED_VTableSizeComputer() {}
    static size_t apply() { return NativeVTableInspector::getIndexOf(&NativeVTableSizeComputer<t_Ty(t_0, t_1, t_2, t_3, t_4, t_5, t_6, t_7, t_8)>::PHANTOM_RESERVED_VTableSizeComputer); }
};

template<typename t_Ty
    , typename t_0
    , typename t_1
    , typename t_2
    , typename t_3
    , typename t_4
    , typename t_5
    , typename t_6
    , typename t_7
    , typename t_8
    , typename t_9>
struct NativeVTableSizeComputer<t_Ty(t_0, t_1, t_2, t_3, t_4, t_5, t_6, t_7, t_8, t_9)> : public t_Ty
{
    o_static_assert_msg(boost::is_polymorphic<t_Ty>::value, "t_Ty must be polymorphic");
    typedef typename boost::remove_reference<typename boost::remove_cv<t_0>::type>::type t_0nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_1>::type>::type t_1nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_2>::type>::type t_2nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_3>::type>::type t_3nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_4>::type>::type t_4nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_5>::type>::type t_5nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_6>::type>::type t_6nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_7>::type>::type t_7nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_8>::type>::type t_8nocvr;
    typedef typename boost::remove_reference<typename boost::remove_cv<t_9>::type>::type t_9nocvr;
    static t_0nocvr* t0() { static t_0nocvr* dummy; return dummy; }
    static t_1nocvr* t1() { static t_1nocvr* dummy; return dummy; }
    static t_2nocvr* t2() { static t_2nocvr* dummy; return dummy; }
    static t_3nocvr* t3() { static t_3nocvr* dummy; return dummy; }
    static t_4nocvr* t4() { static t_4nocvr* dummy; return dummy; }
    static t_5nocvr* t5() { static t_5nocvr* dummy; return dummy; }
    static t_6nocvr* t6() { static t_6nocvr* dummy; return dummy; }
    static t_7nocvr* t7() { static t_7nocvr* dummy; return dummy; }
    static t_8nocvr* t8() { static t_8nocvr* dummy; return dummy; }
    static t_9nocvr* t9() { static t_9nocvr* dummy; return dummy; }
    NativeVTableSizeComputer() : t_Ty(*t0(), *t1(), *t2(), *t3(), *t4(), *t5(), *t6(), *t7(), *t8(), *t9()) { } 
    virtual void PHANTOM_RESERVED_VTableSizeComputer() {} 
    static size_t apply() { return NativeVTableInspector::getIndexOf(&NativeVTableSizeComputer<t_Ty(t_0, t_1, t_2, t_3, t_4, t_5, t_6, t_7, t_8, t_9)>::PHANTOM_RESERVED_VTableSizeComputer); }
};

    
namespace detail 
{
    template<typename t_Ty, bool t_is_default_constructible>
    struct vtable_size_of_helper_default_constructible
    {
        static size_t apply(const void*) { return NativeVTableSizeComputer<t_Ty()>::apply(); }
    };

    template<typename t_Ty>
    struct vtable_size_of_helper_default_constructible<t_Ty, false>
    {
        static size_t apply(const Class* a_pClass) 
        {
            auto it = a_pClass->beginConstructors();
            if(it != a_pClass->endConstructors())
                return (*it)->getNativeVTableSize();
            o_warning(false, "No constructor declared in reflection of %s, cannot extract vtable information", a_pClass->getQualifiedDecoratedName().c_str());
            return 0;
        }
    };

    template<typename t_Ty, bool t_is_polymorphic>
    struct vtable_size_of_helper : public vtable_size_of_helper_default_constructible<t_Ty, std::is_default_constructible<t_Ty>::value AND !boost::is_abstract<t_Ty>::value>
    {

    };

    template<typename t_Ty>
    struct vtable_size_of_helper<t_Ty, false>
    {
        static size_t apply(const void*) { return 0; }
    };
};

template<typename t_Ty>
struct vtable_size_of : detail::vtable_size_of_helper<t_Ty, boost::is_polymorphic<t_Ty>::value>
{

};

o_namespace_end(phantom, reflection, native)

namespace phantom 
{
    template<typename t_Ty>
    size_t     virtualMemberFunctionCountOf()
    {
        return phantom::reflection::native::vtable_size_of<t_Ty>::apply(phantom::typeOf<t_Ty>());
    }
}

#endif
