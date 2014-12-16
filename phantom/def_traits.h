#ifndef o_phantom_traits_h__
#define o_phantom_traits_h__


o_namespace_begin(phantom)

template<typename t_Ty>
class constructor_protection_hacker : public t_Ty
{
public:
    o_forceinline static void apply(void* a_pInstance)
    {
        new (a_pInstance) constructor_protection_hacker();
    }
};

template<typename t_Ty>
class destructor_protection_hacker : public t_Ty
{
public:
    o_forceinline static void apply(void* a_pInstance)
    {
        static_cast<destructor_protection_hacker<t_Ty>*>(a_pInstance)->~destructor_protection_hacker<t_Ty>();
    }
};

template<typename t_Ty>
struct member_access_value_type;

template<typename t_Ty>
struct member_access_value_type<t_Ty*>
{
    typedef t_Ty type;
};

template<typename t_Owner, typename t_Ty>
struct member_access_value_type<t_Ty (t_Owner::*)>
{
    typedef t_Ty type;
};

template<typename t_Ty>
struct meta_specifiers;
template<typename t_Ty>
struct proxy_of;
template<typename t_Ty>
struct has_deferred_cpp_reflection;
template<typename t_Ty>
struct has_new_vtable;
template<typename t_Ty>
struct has_module;
template<typename t_Ty>
struct is_template;
template<typename t_Ty>
struct base_class_count_of;
template<typename t_Ty>
struct has_statechart;
template<typename t_Ty>
struct has_root_statechart;
template<typename t_Ty>
struct has_statechart_cascade;
template<typename t_Ty>
struct has_base_statechart_cascade;
template<typename t_Ty>
struct has_reflection;
template<typename t_Ty>
struct has_reflection_cascade;
template<typename t_Ty>
struct track_count_of;
template<typename t_Ty>
struct track_count_cascade_of;
template<typename t_Ty, int index>
struct base_class_of;
template<typename t_Ty, typename t_DTy = t_Ty>
struct statechart;
template<typename t_Ty, typename t_STy>
struct base_class_index_of;
template<typename t_Ty, typename t_STy>
struct base_statechart;
template<typename t_Ty>
struct first_base_statechart_class_of ;
template<typename t_Ty>
struct base_total_track_count_of;
template<typename t_Ty>
struct is_default_constructible_and_not_abstract;
template<typename t_Ty>
struct has_copy_disabled;
template<typename t_Ty>
struct has_copy_disabled_cascade;
template<typename t_Ty>
struct has_virtual_destructor_cascade;

#if defined(_MSC_VER)
template<class T, int discriminator>
struct is_complete {
    static T & getT();
    static char (& pass(T))[2];
    static char pass(...);
    static const bool value = sizeof(pass(getT()))==2;
};
#else
template <class T, int discriminator>
struct is_complete {
    typedef char false_type;
    typedef int true_type;
    template <class T1>
    static typename boost::enable_if_c<sizeof(T1), true_type>::type test(int);
    template <class T1>
    static false_type test(...);
    enum ENU { value = (
        sizeof(test<T>(0)) == sizeof(true_type)
        )};
};
#endif

template<typename t_Ty>
struct is_data_pointer;

template<typename t_Ty>
struct is_nullptr_t
{
    static const bool value = false;
};

template<>
struct is_nullptr_t<std::nullptr_t>
{
    static const bool value = true;
};

o_namespace_begin(reflection)

template<typename t_Ty>
struct type_of;

o_namespace_end(reflection)


o_namespace_end(phantom)

#if !o_STD_TYPE_TRAIT_DEFINED_IS_DEFAULT_CONSTRUCTIBLE

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

namespace std {

    namespace detail {

        template<typename _B1, typename _B2>
        struct __and_
            : public conditional<_B1::value, _B2, _B1>::type
        { };

        template<typename _Pp>
        struct __not_
            : public integral_constant<bool, !_Pp::value>
        { };


        template<typename _Tp>
        struct __is_array_known_bounds
            : public integral_constant<bool, (extent<_Tp>::value > 0)>
        { };

        template<typename _Tp>
        struct __is_array_unknown_bounds
            : public __and_<is_array<_Tp>, __not_<extent<_Tp> > >::type
        { };

        struct __do_is_default_constructible_impl
        {

            template<typename _Tp>
            static true_type __test(int,decltype(_Tp())* a = 0);

            template<typename>
            static false_type __test(...);
        };

        template<typename _Tp>
        struct __is_default_constructible_impl
            : public __do_is_default_constructible_impl
        {
            typedef decltype(__test<_Tp>(0)) type;
        };

        template<typename _Tp>
        struct __is_default_constructible_atom
            : public __and_<__not_<is_void<_Tp> >,
            __is_default_constructible_impl<_Tp> >::type
        { };

        template<typename _Tp, bool = is_array<_Tp>::value>
        struct __is_default_constructible_safe;

        // The following technique is a workaround for a current core language
        // restriction, which does not allow for array types to occur in
        // functional casts of the form T().  Complete arrays can be default-
        // constructed, if the element type is default-constructible, but
        // arrays with unknown bounds are not.
        template<typename _Tp>
        struct __is_default_constructible_safe<_Tp, true>
            : public __and_<__is_array_known_bounds<_Tp>,
            __is_default_constructible_atom<typename
            remove_all_extents<_Tp>::type> >::type
        { };

        template<typename _Tp>
        struct __is_default_constructible_safe<_Tp, false>
            : public __is_default_constructible_atom<_Tp>::type
        { };

    }

    /**
     * \struct is_default_constructible
     *
     * \brief Tells if the class has a default constructor or not (doesn't take into account the accessibility).
     *
     */

    template<typename _Tp>
    struct is_default_constructible
        : public integral_constant<bool, (detail::__is_default_constructible_safe<
        _Tp>::value)>
    { };

}

#elif o_COMPILER == o_COMPILER_GCC // o_COMPILER

namespace std {

    template<class T, bool t_is_class>
    struct ____is_default_constructible_protected_skipper_helper
    {
        class type : public T
        {
        };
    };

    template<class T>
    struct ____is_default_constructible_protected_skipper_helper<T, false>
    {
        typedef T type;
    };

    template<class T>
    struct ____is_default_constructible_protected_skipper
        : public ____is_default_constructible_protected_skipper_helper<T, boost::is_class<T>::value>
    {

    };

    template< class T >
    class is_default_constructible {

        template<int x>
        class receive_size{};

        template< class U >
        static int sfinae( receive_size< sizeof U() > * );

        template< class U >
        static char sfinae( ... );

    public:
        enum { value = sizeof( sfinae<typename ____is_default_constructible_protected_skipper<T>::type >(0) ) == sizeof(int) };
    };
}

#else
#error  std::is_default_constructible not available for the current compiler/version, you must implement your own here (or try activating your compiler CPP0X features)
#endif// o_COMPILER

#endif // o_STD_TYPE_TRAIT_DEFINED_IS_DEFAULT_CONSTRUCTIBLE

/* Forward declarations */
o_namespace_begin(phantom, reflection)
class Type;
class Class;
o_namespace_end(phantom, reflection)



o_namespace_begin(phantom)

template<typename t_Ty, int index>
struct base_class_of ;

template<typename t_Owner, typename t_ValueType>
struct member_pointer_type_maker
{
    typedef t_ValueType (t_Owner::*type);
};

template<typename t_Owner, typename t_ValueType, size_t t_size0>
struct member_pointer_type_maker<t_ValueType[t_size0], t_Owner>
{
    typedef t_ValueType (t_Owner::*type)[t_size0];
};

template<typename t_Owner, typename t_ValueType, size_t t_size0, size_t t_size1>
struct member_pointer_type_maker<t_ValueType[t_size0][t_size1], t_Owner>
{
    typedef t_ValueType (t_Owner::*type)[t_size0][t_size1];
};

template<typename t_Owner, typename t_ValueType, size_t t_size0, size_t t_size1, size_t t_size2>
struct member_pointer_type_maker<t_ValueType[t_size0][t_size1][t_size2], t_Owner>
{
    typedef t_ValueType (t_Owner::*type)[t_size0][t_size1][t_size2];
};

template<typename t_Owner, typename t_ValueType, size_t t_size0, size_t t_size1, size_t t_size2, size_t t_size3>
struct member_pointer_type_maker<t_ValueType[t_size0][t_size1][t_size2][t_size3], t_Owner>
{
    typedef t_ValueType (t_Owner::*type)[t_size0][t_size1][t_size2][t_size3];
};

template<typename t_Owner, typename t_ValueType, size_t t_size0, size_t t_size1, size_t t_size2, size_t t_size3, size_t t_size4>
struct member_pointer_type_maker<t_ValueType[t_size0][t_size1][t_size2][t_size3][t_size4], t_Owner>
{
    typedef t_ValueType (t_Owner::*type)[t_size0][t_size1][t_size2][t_size3][t_size4];
};

template<typename t_Owner, typename t_ValueType, size_t t_size0, size_t t_size1, size_t t_size2, size_t t_size3, size_t t_size4, size_t t_size5>
struct member_pointer_type_maker<t_ValueType[t_size0][t_size1][t_size2][t_size3][t_size4][t_size5], t_Owner>
{
    typedef t_ValueType (t_Owner::*type)[t_size0][t_size1][t_size2][t_size3][t_size4][t_size5];
};

template<typename t_Owner, typename t_ValueType, size_t t_size0, size_t t_size1, size_t t_size2, size_t t_size3, size_t t_size4, size_t t_size5, size_t t_size6>
struct member_pointer_type_maker<t_ValueType[t_size0][t_size1][t_size2][t_size3][t_size4][t_size5][t_size6], t_Owner>
{
    typedef t_ValueType (t_Owner::*type)[t_size0][t_size1][t_size2][t_size3][t_size4][t_size5][t_size6];
};

template<typename t_Owner, typename t_ValueType, size_t t_size0, size_t t_size1, size_t t_size2, size_t t_size3, size_t t_size4, size_t t_size5, size_t t_size6, size_t t_size7>
struct member_pointer_type_maker<t_ValueType[t_size0][t_size1][t_size2][t_size3][t_size4][t_size5][t_size6][t_size7], t_Owner>
{
    typedef t_ValueType (t_Owner::*type)[t_size0][t_size1][t_size2][t_size3][t_size4][t_size5][t_size6][t_size7];
};

template<typename t_Owner, typename t_ValueType, size_t t_size0, size_t t_size1, size_t t_size2, size_t t_size3, size_t t_size4, size_t t_size5, size_t t_size6, size_t t_size7, size_t t_size8>
struct member_pointer_type_maker<t_ValueType[t_size0][t_size1][t_size2][t_size3][t_size4][t_size5][t_size6][t_size7][t_size8], t_Owner>
{
    typedef t_ValueType (t_Owner::*type)[t_size0][t_size1][t_size2][t_size3][t_size4][t_size5][t_size6][t_size7][t_size8];
};

template<typename t_Owner, typename t_ValueType, size_t t_size0, size_t t_size1, size_t t_size2, size_t t_size3, size_t t_size4, size_t t_size5, size_t t_size6, size_t t_size7, size_t t_size8, size_t t_size9>
struct member_pointer_type_maker<t_ValueType[t_size0][t_size1][t_size2][t_size3][t_size4][t_size5][t_size6][t_size7][t_size8][t_size9], t_Owner>
{
    typedef t_ValueType (t_Owner::*type)[t_size0][t_size1][t_size2][t_size3][t_size4][t_size5][t_size6][t_size7][t_size8][t_size9];
};

namespace detail
{
    template<bool is_union, typename t_Then, typename t_Else>
    struct select_type_if_union_helper
    {
        typedef t_Then type;
    };
    template<typename t_Then, typename t_Else>
    struct select_type_if_union_helper<false, t_Then, t_Else>
    {
        typedef t_Else type;
    };

}

template<typename t_Tested, typename t_Then, typename t_Else>
struct select_type_if_union : public detail::select_type_if_union_helper<boost::is_union<t_Tested>::value, t_Then, t_Else> {};

o_namespace_end(phantom)



o_namespace_begin(phantom, detail)

template<typename t_Ty, int t_init_counter, int t_counter>
struct phantom_proxy_generator_track_counter_unit
{
    phantom_proxy_generator_track_counter_unit() {}
};

struct false_
{
    const static bool value = false;
};

struct true_
{
    const static bool value = true;
};

template<int i>
struct int_num_type
{
};

template<typename t_Ty
, typename t_S0 = void
, typename t_S1 = void
, typename t_S2 = void
, typename t_S3 = void
, typename t_S4 = void
, typename t_S5 = void
, typename t_S6 = void
, typename t_S7 = void
, typename t_S8 = void
, typename t_S9 = void>
struct base_total_track_count_of_helper;


template<typename t_Ty
    , typename t_S0 = void
    , typename t_S1 = void
    , typename t_S2 = void
    , typename t_S3 = void
    , typename t_S4 = void
    , typename t_S5 = void
    , typename t_S6 = void
    , typename t_S7 = void
    , typename t_S8 = void
    , typename t_S9 = void>
struct base_class_count_of_helper;

template<typename t_Ty
    , int t_index
    , typename t_S0 = void
    , typename t_S1 = void
    , typename t_S2 = void
    , typename t_S3 = void
    , typename t_S4 = void
    , typename t_S5 = void
    , typename t_S6 = void
    , typename t_S7 = void
    , typename t_S8 = void
    , typename t_S9 = void>
struct base_class_of_helper
{
    typedef void type;
};

template<typename t_Ty
    , typename t_STy
    , typename t_S0 = void
    , typename t_S1 = void
    , typename t_S2 = void
    , typename t_S3 = void
    , typename t_S4 = void
    , typename t_S5 = void
    , typename t_S6 = void
    , typename t_S7 = void
    , typename t_S8 = void
    , typename t_S9 = void>
struct base_class_index_of_helper;
template<typename t_Ty
    , typename t_DTy
    , typename t_S0 = void
    , typename t_S1 = void
    , typename t_S2 = void
    , typename t_S3 = void
    , typename t_S4 = void
    , typename t_S5 = void
    , typename t_S6 = void
    , typename t_S7 = void
    , typename t_S8 = void
    , typename t_S9 = void>
struct base_statechart_helper;

template<typename t_Ty, int t_base_class_count_of>
struct first_base_statechart_class_of_helper_base_;

template<typename t_Ty, int t_base_class_count_of, boolean t_base_has_statechart>
struct first_base_statechart_class_of_helper_cascade_;

// Convenient macro to access the base class of a template argument in a meta-function trait
#define o_traits_t_Ty_base_class(index) \
    o_NESTED_TYPE phantom::base_class_of<t_Ty,index>::type



template<typename t_Ty, bool t_is_abstract>
struct is_default_constructible_and_not_abstract_helper
    : public std::is_default_constructible<t_Ty>
{

};

template<typename t_Ty>
struct is_default_constructible_and_not_abstract_helper <t_Ty, true> : public false_
{

};


template<typename t_Ty, int t_base_class_count_of>
struct has_base_statechart_cascade_helper_
{
    const static bool value = has_statechart_cascade<typename base_class_of<t_Ty, t_base_class_count_of-1>::type>::value
        OR has_base_statechart_cascade_helper_<t_Ty, t_base_class_count_of-1>::value;
};

template<typename t_Ty>
struct has_base_statechart_cascade_helper_<t_Ty, 0>
{
    const static bool value = false;
};

template<typename t_Ty, int t_base_class_count_of>
struct has_statechart_cascade_helper_
{
    const static bool value = has_statechart<t_Ty>::value
        OR has_statechart_cascade<typename base_class_of<t_Ty, t_base_class_count_of-1>::type>::value
        OR has_statechart_cascade_helper_<t_Ty, t_base_class_count_of-1>::value;
};

template<typename t_Ty>
struct has_statechart_cascade_helper_<t_Ty,0>
{
    const static bool value = has_statechart<t_Ty>::value;
};

template<typename t_Ty>
struct has_base_statechart_cascade_
    : public has_base_statechart_cascade_helper_<t_Ty, base_class_count_of<t_Ty>::value>
{
};

template<typename t_Ty, boolean t_has_statechart, boolean t_has_base_statechart>
struct first_base_statechart_class_of_helper_
{

};

template<typename t_Ty>
struct first_base_statechart_class_of_helper_<t_Ty, false, false>
{
  o_static_assert(sizeof(t_Ty) == 0);
};

template<typename t_Ty>
struct first_base_statechart_class_of_helper_<t_Ty, true, false>
{
  typedef t_Ty type;
};


template<typename t_Ty, boolean t_has_statechart>
struct first_base_statechart_class_of_helper_<t_Ty, t_has_statechart, true>
  : public first_base_statechart_class_of_helper_base_<
  t_Ty
  , base_class_count_of<t_Ty>::value>
{
};


template<typename t_Ty, int t_base_class_count_of>
struct first_base_statechart_class_of_helper_base_
  : public first_base_statechart_class_of_helper_cascade_<
  t_Ty
  , t_base_class_count_of
  , has_statechart_cascade<
  o_NESTED_TYPE base_class_of<t_Ty, base_class_count_of<t_Ty>::value-t_base_class_count_of>::type
  >::value >
{

};

template<typename t_Ty>
struct first_base_statechart_class_of_helper_base_<t_Ty, 0>
{

};

template<typename t_Ty, int t_base_class_count_of, boolean t_base_has_statechart>
struct first_base_statechart_class_of_helper_cascade_
{

};


template<typename t_Ty, int t_base_class_count_of>
struct first_base_statechart_class_of_helper_cascade_<t_Ty, t_base_class_count_of, true>
  : public first_base_statechart_class_of<
      o_traits_t_Ty_base_class(base_class_count_of<t_Ty>::value - t_base_class_count_of)
    >
{};

template<typename t_Ty>
struct first_base_statechart_class_of_helper_cascade_<t_Ty, 0, true>
{

};

template<typename t_Ty, int t_base_class_count_of>
struct first_base_statechart_class_of_helper_cascade_<t_Ty, t_base_class_count_of, false>
  : public first_base_statechart_class_of_helper_cascade_<
     t_Ty
    , t_base_class_count_of - 1
    , has_statechart_cascade<o_traits_t_Ty_base_class(base_class_count_of<t_Ty>::value - (t_base_class_count_of - 1))>::value
  >
{};

template<typename t_Ty>
struct first_base_statechart_class_of_helper_cascade_<t_Ty, 0, false>
{

};


template<typename t_Ty>
struct is_signal_t_
{
  static const bool value = false;
};

template<>
struct is_signal_t_<phantom::signal_t>
{
  static const bool value = true;
};

template<typename t_Ty>
struct is_void_
{
  static const bool value = false;
};

template<>
struct is_void_<void>
{
  static const bool value = true;
};

template<typename t_Ty, bool t_abstract, bool t_class>
struct safe_alignment_of_helper_ ;

template<typename t_Ty>
struct safe_alignment_of_helper_<t_Ty, true, true>
{
    BOOST_STATIC_CONSTANT(size_t, value = 0);
};
template<typename t_Ty>
struct safe_alignment_of_helper_<t_Ty, false, true> : public boost::alignment_of<destructor_protection_hacker<t_Ty> >
{
};
template<typename t_Ty>
struct safe_alignment_of_helper_<t_Ty, false, false> : public boost::alignment_of<t_Ty>
{
};

template<typename t_Ty, boolean t_void>
struct safe_size_of_helper_
{
    BOOST_STATIC_CONSTANT(size_t, value = sizeof(t_Ty));
};

template<typename t_Ty>
struct safe_size_of_helper_<t_Ty, true>
{
    BOOST_STATIC_CONSTANT(size_t, value = 0);
};

template<typename t_Ty, size_t t_size_of>
struct enum_integral_type_helper;

template<typename t_Ty>
struct enum_integral_type_helper<t_Ty, sizeof(char)>
{
    typedef char type;
};
template<typename t_Ty>
struct enum_integral_type_helper<t_Ty, sizeof(short)>
{
    typedef short type;
};
template<typename t_Ty>
struct enum_integral_type_helper<t_Ty, sizeof(int)>
{
    typedef int type;
};
template<typename t_Ty>
struct enum_integral_type_helper<t_Ty, sizeof(long long)>
{
    typedef long long type;
};

template<typename t_Ty>
struct enum_integral_type_ : public enum_integral_type_helper<t_Ty, sizeof(t_Ty)>
{

};

template<typename t_Ty, int t_base_class_count_of>
struct has_virtual_destructor_cascade_helper_
{
    const static boolean value = boost::has_virtual_destructor<t_Ty>::value
        OR has_virtual_destructor_cascade<typename base_class_of<t_Ty, t_base_class_count_of-1>::type>::value
        OR has_virtual_destructor_cascade_helper_<t_Ty, t_base_class_count_of-1>::value;
};

template<typename t_Ty>
struct has_virtual_destructor_cascade_helper_<t_Ty, 0>
{
    const static boolean value = boost::has_virtual_destructor<t_Ty>::value;
};

BOOST_MPL_HAS_XXX_TRAIT_DEF(enclosed_statechart_declaration);
BOOST_MPL_HAS_XXX_TRAIT_DEF(enclosed_reflection_declaration);

template<typename t_Ty, bool t_has_enclosed_statechart_declaration>
struct has_enclosed_statechart_helper_has_enclosed_statechart_declaration
    : public boost::is_same<o_NESTED_TYPE proxy_of<t_Ty>::type::enclosed_reflection::enclosed_statechart_declaration, t_Ty>{};

template<typename t_Ty>
struct has_enclosed_statechart_helper_has_enclosed_statechart_declaration<t_Ty, false>
{
    static const bool value = false;
};

template<typename t_Ty, bool t_has_enclosed_reflection_declaration>
struct has_enclosed_statechart_helper_has_enclosed_reflection
    : has_enclosed_statechart_helper_has_enclosed_statechart_declaration<t_Ty, has_enclosed_statechart_declaration<o_NESTED_TYPE proxy_of<t_Ty>::type::enclosed_reflection>::value>
{

};

template<typename t_Ty>
struct has_enclosed_statechart_helper_has_enclosed_reflection<t_Ty, false>
{
    static const bool value = false;
};


template<typename t_Ty>
struct has_enclosed_statechart_cascade : public has_enclosed_statechart_declaration<t_Ty> {};

template<typename t_Ty>
struct has_enclosed_statechart
    : public has_enclosed_statechart_helper_has_enclosed_reflection<t_Ty, has_enclosed_reflection_declaration<o_NESTED_TYPE proxy_of<t_Ty>::type>::value>{};

template<typename t_Ty, bool t_has_enclosed_reflection_declaration>
struct has_enclosed_reflection_helper
{
    static const bool value = false;
};

template<typename t_Ty>
struct has_enclosed_reflection_helper<t_Ty, true>
    : public boost::is_same<o_NESTED_TYPE proxy_of<t_Ty>::type::enclosed_reflection_declaration, t_Ty>{};

template<typename t_Ty>
struct has_enclosed_reflection_cascade : public has_enclosed_reflection_declaration<t_Ty> {};

template<typename t_Ty>
struct has_enclosed_reflection
    : public has_enclosed_reflection_helper<t_Ty
    , has_enclosed_reflection_declaration<o_NESTED_TYPE proxy_of<t_Ty>::type>::value>{};



template<typename t_Ty, int t_base_class_count_of>
struct has_reflection_cascade_helper_
{
    const static bool value = has_reflection<t_Ty>::value
        OR has_reflection_cascade<typename base_class_of<t_Ty, t_base_class_count_of-1>::type>::value
        OR has_reflection_cascade_helper_<t_Ty, t_base_class_count_of-1>::value;
};

template<typename t_Ty>
struct has_reflection_cascade_helper_<t_Ty,0>
{
    const static bool value = has_reflection<t_Ty>::value;
};

template<typename t_Ty, typename t_DTy, bool t_has_statechart>
struct statechart_helper;


template<typename t_BaseTy, typename t_Ty, bool t_has_statechart>
struct statechart_helper
    : public base_statechart<t_BaseTy,t_Ty>
{

};

template<typename t_Ty, typename t_DTy>
struct statechart_helper<t_Ty, t_DTy, true>
    : public proxy_of<t_Ty>::type::enclosed_reflection::o_NESTED_TEMPLATE enclosed_statechart<t_DTy>
{

};

template<typename t_Ty, bool t_has_enclosed_statechart>
struct track_count_of_helper;


template<typename t_Ty, bool t_has_enclosed_statechart>
struct track_count_of_helper
{
    enum { value = 0 };
};


template<typename t_Ty, int t_base_class_count_of>
struct has_copy_disabled_cascade_helper_
{
    const static bool value = has_copy_disabled<t_Ty>::value
        OR has_copy_disabled_cascade<typename base_class_of<t_Ty, t_base_class_count_of-1>::type>::value
        OR has_copy_disabled_cascade_helper_<t_Ty, t_base_class_count_of-1>::value;
};

template<typename t_Ty>
struct has_copy_disabled_cascade_helper_<t_Ty, 0>
{
    const static bool value = has_copy_disabled<t_Ty>::value;
};








BOOST_MPL_HAS_XXX_TRAIT_DEF(phantom_proxy_generator_track_counter_marker);
BOOST_MPL_HAS_XXX_TRAIT_DEF(phantom_proxy_generator_track_counter_defined)

template<typename t_Ty, bool t_has_counter_marker, bool t_has_counter_marker_base >
struct phantom_proxy_generator_track_counter_solver_finder;

template<typename t_Ty, int t_count, bool t_must_continue>
struct phantom_proxy_generator_track_counter_solver_recursive_helper
{
    enum { value = t_count };
};

template<typename t_Ty, int t_count>
struct phantom_proxy_generator_track_counter_solver_recursive
    : public phantom_proxy_generator_track_counter_solver_recursive_helper<t_Ty
    , t_count
    , has_phantom_proxy_generator_track_counter_defined<o_DOUBLE_NESTED_TYPE proxy_of<t_Ty>::type::enclosed_reflection::o_NESTED_TEMPLATE
        enclosed_statechart<t_Ty>::
        o_NESTED_TEMPLATE phantom_proxy_generator_track_counter<t_Ty,t_count> >::value
    >
{
};

template<typename t_Ty>
struct phantom_proxy_generator_track_counter_solver
    : public phantom_proxy_generator_track_counter_solver_finder<t_Ty
                , has_phantom_proxy_generator_track_counter_marker<o_DOUBLE_NESTED_TYPE proxy_of<t_Ty>::type::enclosed_reflection::o_NESTED_TEMPLATE enclosed_statechart<t_Ty> >::value
                , has_phantom_proxy_generator_track_counter_marker<base_statechart<t_Ty,t_Ty> >::value>
{

};

template<typename t_Ty, bool t_has_same_marker>
struct phantom_proxy_generator_track_counter_solver_finder_test_same
{
    enum { value = 0 };
};

template<typename t_Ty>
struct phantom_proxy_generator_track_counter_solver_finder_test_same<t_Ty, false>
    : public phantom_proxy_generator_track_counter_solver_recursive<t_Ty
    , 0>
{
};

template<typename t_Ty, int t_count>
struct phantom_proxy_generator_track_counter_solver_recursive_helper<t_Ty, t_count, true>
    : public phantom_proxy_generator_track_counter_solver_recursive<t_Ty, t_count+1>
{

};

template<typename t_Ty>
struct phantom_proxy_generator_track_counter_solver_finder<t_Ty,true,true>
    : public phantom_proxy_generator_track_counter_solver_finder_test_same<t_Ty
    , boost::is_same<o_DOUBLE_NESTED_TYPE proxy_of<t_Ty>::type::enclosed_reflection::o_NESTED_TEMPLATE enclosed_statechart<t_Ty>::phantom_proxy_generator_track_counter_marker, o_NESTED_TYPE base_statechart<t_Ty,t_Ty>::phantom_proxy_generator_track_counter_marker>::value
    >
{
};

template<typename t_Ty>
struct phantom_proxy_generator_track_counter_solver_finder<t_Ty,true,false>
    : public phantom_proxy_generator_track_counter_solver_finder_test_same<t_Ty, false>
{
};

template<typename t_Ty>
struct phantom_proxy_generator_track_counter_solver_finder<t_Ty,false,true>
{
    enum { value = 0 };
};

template<typename t_Ty>
struct phantom_proxy_generator_track_counter_solver_finder<t_Ty,false,false>
{
    enum { value = 0 };
};

template<typename t_Ty>
struct track_count_of_helper<t_Ty, true>
{
    enum { value = (has_root_statechart<t_Ty>::value ? 1 : 0) // +/- Root Track
        + phantom_proxy_generator_track_counter_solver<t_Ty>::value // + User defined tracks
    };
};

template<typename t_Ty, bool t_has_enclosed_statechart>
struct track_count_cascade_of_helper;


template<typename t_Ty, bool t_has_statechart_cascade>
struct track_count_cascade_of_helper
{
    enum { value = 0 };
};

template<typename t_Ty>
struct track_count_cascade_of_helper<t_Ty, true>
{

};

// to detect containers
BOOST_MPL_HAS_XXX_TRAIT_DEF(key_type)
BOOST_MPL_HAS_XXX_TRAIT_DEF(value_type)
BOOST_MPL_HAS_XXX_TRAIT_DEF(mapped_type)
BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator)
BOOST_MPL_HAS_XXX_TRAIT_DEF(size_type)
BOOST_MPL_HAS_XXX_TRAIT_DEF(reference)

BOOST_MPL_HAS_XXX_TRAIT_DEF(recursive_meta_type_stop_type)


#define o_traits_base_helper_typename_base_class_list_0()
#define o_traits_base_helper_typename_base_class_list_1() o_traits_base_helper_typename_base_class_list_0(), typename t_S0
#define o_traits_base_helper_typename_base_class_list_2() o_traits_base_helper_typename_base_class_list_1(), typename t_S1
#define o_traits_base_helper_typename_base_class_list_3() o_traits_base_helper_typename_base_class_list_2(), typename t_S2
#define o_traits_base_helper_typename_base_class_list_4() o_traits_base_helper_typename_base_class_list_3(), typename t_S3
#define o_traits_base_helper_typename_base_class_list_5() o_traits_base_helper_typename_base_class_list_4(), typename t_S4
#define o_traits_base_helper_typename_base_class_list_6() o_traits_base_helper_typename_base_class_list_5(), typename t_S5
#define o_traits_base_helper_typename_base_class_list_7() o_traits_base_helper_typename_base_class_list_6(), typename t_S6
#define o_traits_base_helper_typename_base_class_list_8() o_traits_base_helper_typename_base_class_list_7(), typename t_S7
#define o_traits_base_helper_typename_base_class_list_9() o_traits_base_helper_typename_base_class_list_8(), typename t_S8
#define o_traits_base_helper_typename_base_class_list_10()o_traits_base_helper_typename_base_class_list_9(), typename t_S9

#define o_traits_base_helper_base_class_list_0()
#define o_traits_base_helper_base_class_list_1() o_traits_base_helper_base_class_list_0(), t_S0
#define o_traits_base_helper_base_class_list_2() o_traits_base_helper_base_class_list_1(), t_S1
#define o_traits_base_helper_base_class_list_3() o_traits_base_helper_base_class_list_2(), t_S2
#define o_traits_base_helper_base_class_list_4() o_traits_base_helper_base_class_list_3(), t_S3
#define o_traits_base_helper_base_class_list_5() o_traits_base_helper_base_class_list_4(), t_S4
#define o_traits_base_helper_base_class_list_6() o_traits_base_helper_base_class_list_5(), t_S5
#define o_traits_base_helper_base_class_list_7() o_traits_base_helper_base_class_list_6(), t_S6
#define o_traits_base_helper_base_class_list_8() o_traits_base_helper_base_class_list_7(), t_S7
#define o_traits_base_helper_base_class_list_9() o_traits_base_helper_base_class_list_8(), t_S8
#define o_traits_base_helper_base_class_list_10()o_traits_base_helper_base_class_list_9(), t_S9

#define o_traits_base_helper_base_class_void_list_0() o_traits_base_helper_base_class_void_list_1() , void
#define o_traits_base_helper_base_class_void_list_1() o_traits_base_helper_base_class_void_list_2() , void
#define o_traits_base_helper_base_class_void_list_2() o_traits_base_helper_base_class_void_list_3() , void
#define o_traits_base_helper_base_class_void_list_3() o_traits_base_helper_base_class_void_list_4() , void
#define o_traits_base_helper_base_class_void_list_4() o_traits_base_helper_base_class_void_list_5() , void
#define o_traits_base_helper_base_class_void_list_5() o_traits_base_helper_base_class_void_list_6() , void
#define o_traits_base_helper_base_class_void_list_6() o_traits_base_helper_base_class_void_list_7() , void
#define o_traits_base_helper_base_class_void_list_7() o_traits_base_helper_base_class_void_list_8() , void
#define o_traits_base_helper_base_class_void_list_8() o_traits_base_helper_base_class_void_list_9() , void
#define o_traits_base_helper_base_class_void_list_9() o_traits_base_helper_base_class_void_list_10(), void
#define o_traits_base_helper_base_class_void_list_10()

#if (o_COMPILER == o_COMPILER_GCC) || (o_COMPILER == o_COMPILER_CLANG)
#define o_traits_specialize_base_class_of_code(i)\
    o_static_assert_msg((phantom::has_reflection<t_S##i>::value), "base class ('t_S"#i"' below) : undeclared reflection (ensure you included the corresponding .hxx)");\
    typedef t_S##i type;

#else

#define o_traits_specialize_base_class_of_code(i)\
    o_static_assert_msg((phantom::has_reflection<t_S##i>::value), "base class ('t_S"#i"' below) : undeclared reflection (ensure you included the corresponding .hxx)");\
    o_static_assert_msg((!boost::is_virtual_base_of<t_S##i, t_Ty>::value), "base class ('t_S"#i"' below) : virtual inheritance not supported");\
    typedef t_S##i type;
#endif

#define o_traits_specialize_base_class_of_helper_0(_count_)
#define o_traits_specialize_base_class_of_helper_1(_count_) o_traits_specialize_base_class_of_helper_0(_count_) \
    template<typename t_Ty o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_of_helper<t_Ty, 0 o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()> { o_traits_specialize_base_class_of_code(0) };

#define o_traits_specialize_base_class_of_helper_2(_count_) o_traits_specialize_base_class_of_helper_1(_count_) \
    template<typename t_Ty o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_of_helper<t_Ty, 1 o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()> { o_traits_specialize_base_class_of_code(1) };

#define o_traits_specialize_base_class_of_helper_3(_count_) o_traits_specialize_base_class_of_helper_2(_count_) \
    template<typename t_Ty o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_of_helper<t_Ty, 2 o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()> { o_traits_specialize_base_class_of_code(2) };

#define o_traits_specialize_base_class_of_helper_4(_count_) o_traits_specialize_base_class_of_helper_3(_count_) \
    template<typename t_Ty o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_of_helper<t_Ty, 3 o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()> { o_traits_specialize_base_class_of_code(3) };

#define o_traits_specialize_base_class_of_helper_5(_count_) o_traits_specialize_base_class_of_helper_4(_count_) \
    template<typename t_Ty o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_of_helper<t_Ty, 4 o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()> { o_traits_specialize_base_class_of_code(4) };

#define o_traits_specialize_base_class_of_helper_6(_count_) o_traits_specialize_base_class_of_helper_5(_count_) \
    template<typename t_Ty  o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_of_helper<t_Ty, 5 o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()> { o_traits_specialize_base_class_of_code(5) };

#define o_traits_specialize_base_class_of_helper_7(_count_) o_traits_specialize_base_class_of_helper_6(_count_) \
    template<typename t_Ty o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_of_helper<t_Ty, 6 o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()> { o_traits_specialize_base_class_of_code(6) };

#define o_traits_specialize_base_class_of_helper_8(_count_) o_traits_specialize_base_class_of_helper_7(_count_) \
    template<typename t_Ty o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_of_helper<t_Ty, 7 o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()> { o_traits_specialize_base_class_of_code(7) };

#define o_traits_specialize_base_class_of_helper_9(_count_) o_traits_specialize_base_class_of_helper_8(_count_) \
    template<typename t_Ty o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_of_helper<t_Ty, 8 o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()>{ o_traits_specialize_base_class_of_code(8) };

#define o_traits_specialize_base_class_of_helper_10(_count_)o_traits_specialize_base_class_of_helper_9(_count_) \
    template<typename t_Ty o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_of_helper<t_Ty, 9 o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_(_count_)> { o_traits_specialize_base_class_of_code(9) };




#define o_traits_specialize_base_class_index_of_helper_0(_count_)
#define o_traits_specialize_base_class_index_of_helper_1(_count_) o_traits_specialize_base_class_index_of_helper_0(_count_) \
    template<typename t_Ty o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_index_of_helper<t_Ty, t_S0 o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()> { enum { value = 0 }; };

#define o_traits_specialize_base_class_index_of_helper_2(_count_) o_traits_specialize_base_class_index_of_helper_1(_count_) \
    template<typename t_Ty o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_index_of_helper<t_Ty, t_S1 o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()> { enum { value = 1 }; };

#define o_traits_specialize_base_class_index_of_helper_3(_count_) o_traits_specialize_base_class_index_of_helper_2(_count_) \
    template<typename t_Ty o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_index_of_helper<t_Ty, t_S2 o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()> { enum { value = 2 }; };

#define o_traits_specialize_base_class_index_of_helper_4(_count_) o_traits_specialize_base_class_index_of_helper_3(_count_) \
    template<typename t_Ty o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_index_of_helper<t_Ty, t_S3 o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()> { enum { value = 3 }; };

#define o_traits_specialize_base_class_index_of_helper_5(_count_) o_traits_specialize_base_class_index_of_helper_4(_count_) \
    template<typename t_Ty o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_index_of_helper<t_Ty, t_S4 o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()> { enum { value = 4 }; };

#define o_traits_specialize_base_class_index_of_helper_6(_count_) o_traits_specialize_base_class_index_of_helper_5(_count_) \
    template<typename t_Ty  o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_index_of_helper<t_Ty, t_S5 o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()> { enum { value = 5 }; };

#define o_traits_specialize_base_class_index_of_helper_7(_count_) o_traits_specialize_base_class_index_of_helper_6(_count_) \
    template<typename t_Ty o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_index_of_helper<t_Ty, t_S6 o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()> { enum { value = 6 }; };

#define o_traits_specialize_base_class_index_of_helper_8(_count_) o_traits_specialize_base_class_index_of_helper_7(_count_) \
    template<typename t_Ty o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_index_of_helper<t_Ty, t_S7 o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()> { enum { value = 7 }; };

#define o_traits_specialize_base_class_index_of_helper_9(_count_) o_traits_specialize_base_class_index_of_helper_8(_count_) \
    template<typename t_Ty o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_index_of_helper<t_Ty, t_S8 o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()>{ enum { value = 8 }; };

#define o_traits_specialize_base_class_index_of_helper_10(_count_)o_traits_specialize_base_class_index_of_helper_9(_count_) \
    template<typename t_Ty o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_index_of_helper<t_Ty, t_S9 o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_(_count_)> { enum { value = 9 }; };



#define o_traits_specialize_base_total_track_count_of_helper_0() 0
#define o_traits_specialize_base_total_track_count_of_helper_1() o_traits_specialize_base_total_track_count_of_helper_0() +  phantom::track_count_cascade_of<t_S0>::value
#define o_traits_specialize_base_total_track_count_of_helper_2() o_traits_specialize_base_total_track_count_of_helper_1() +  ((phantom::track_count_cascade_of<t_S1>::value > 0)?phantom::track_count_cascade_of<t_S1>::value-1:0)
#define o_traits_specialize_base_total_track_count_of_helper_3() o_traits_specialize_base_total_track_count_of_helper_2() +  ((phantom::track_count_cascade_of<t_S2>::value > 0)?phantom::track_count_cascade_of<t_S2>::value-1:0)
#define o_traits_specialize_base_total_track_count_of_helper_4() o_traits_specialize_base_total_track_count_of_helper_3() +  ((phantom::track_count_cascade_of<t_S3>::value > 0)?phantom::track_count_cascade_of<t_S3>::value-1:0)
#define o_traits_specialize_base_total_track_count_of_helper_5() o_traits_specialize_base_total_track_count_of_helper_4() +  ((phantom::track_count_cascade_of<t_S4>::value > 0)?phantom::track_count_cascade_of<t_S4>::value-1:0)
#define o_traits_specialize_base_total_track_count_of_helper_6() o_traits_specialize_base_total_track_count_of_helper_5() +  ((phantom::track_count_cascade_of<t_S5>::value > 0)?phantom::track_count_cascade_of<t_S5>::value-1:0)
#define o_traits_specialize_base_total_track_count_of_helper_7() o_traits_specialize_base_total_track_count_of_helper_6() +  ((phantom::track_count_cascade_of<t_S6>::value > 0)?phantom::track_count_cascade_of<t_S6>::value-1:0)
#define o_traits_specialize_base_total_track_count_of_helper_8() o_traits_specialize_base_total_track_count_of_helper_7() +  ((phantom::track_count_cascade_of<t_S7>::value > 0)?phantom::track_count_cascade_of<t_S7>::value-1:0)
#define o_traits_specialize_base_total_track_count_of_helper_9() o_traits_specialize_base_total_track_count_of_helper_8() +  ((phantom::track_count_cascade_of<t_S8>::value > 0)?phantom::track_count_cascade_of<t_S8>::value-1:0)
#define o_traits_specialize_base_total_track_count_of_helper_10() o_traits_specialize_base_total_track_count_of_helper_9() + ((phantom::track_count_cascade_of<t_S9>::value > 0)?phantom::track_count_cascade_of<t_S9>::value-1:0)

#define o_traits_specialize_base_total_track_count_of_helper(_count_) \
    template<typename t_Ty o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_total_track_count_of_helper<t_Ty o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()>\
{\
    enum { value = o_traits_specialize_base_total_track_count_of_helper_##_count_()};\
};

#define o_traits_specialize_base_class_of_helper(_count_) \
    o_traits_specialize_base_class_of_helper_##_count_(_count_)

/*

#define o_traits_specialize_base_class_index_of_helper_0()
#define o_traits_specialize_base_class_index_of_helper_1()        o_traits_specialize_base_class_index_of_helper_0()  template<> struct index_of< t_S0 > { const static int code = 0; };
#define o_traits_specialize_base_class_index_of_helper_2()        o_traits_specialize_base_class_index_of_helper_1()  template<> struct index_of< t_S1 > { const static int code = 1;};
#define o_traits_specialize_base_class_index_of_helper_3()        o_traits_specialize_base_class_index_of_helper_2()  template<> struct index_of< t_S2 > { const static int code = 2;};
#define o_traits_specialize_base_class_index_of_helper_4()        o_traits_specialize_base_class_index_of_helper_3()  template<> struct index_of< t_S3 > { const static int code = 3;};
#define o_traits_specialize_base_class_index_of_helper_5()        o_traits_specialize_base_class_index_of_helper_4()  template<> struct index_of< t_S4 > { const static int code = 4;};
#define o_traits_specialize_base_class_index_of_helper_6()        o_traits_specialize_base_class_index_of_helper_5()  template<> struct index_of< t_S5 > { const static int code = 5;};
#define o_traits_specialize_base_class_index_of_helper_7()        o_traits_specialize_base_class_index_of_helper_6()  template<> struct index_of< t_S6 > { const static int code = 6;};
#define o_traits_specialize_base_class_index_of_helper_8()        o_traits_specialize_base_class_index_of_helper_7()  template<> struct index_of< t_S7 > { const static int code = 7;};
#define o_traits_specialize_base_class_index_of_helper_9()        o_traits_specialize_base_class_index_of_helper_8()  template<> struct index_of< t_S8 > { const static int code = 8;};
#define o_traits_specialize_base_class_index_of_helper_10()       o_traits_specialize_base_class_index_of_helper_9()  template<> struct index_of< t_S9 > { const static int code = 9;};
*/

#define o_traits_specialize_base_class_index_of_helper(_count_) \
    o_traits_specialize_base_class_index_of_helper_##_count_(_count_)


#define o_traits_specialize_base_class_count_of_helper(_count_) \
    template<typename t_Ty o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_class_count_of_helper<t_Ty o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()>\
{\
    enum { value = _count_ }; \
};

#define o_traits_specialize_base_statechart_helper_0() public virtual phantom::state::native::root_statechart<t_DTy>
#define o_traits_specialize_base_statechart_helper_1()                                             public virtual phantom::statechart<t_S0, t_DTy>
#define o_traits_specialize_base_statechart_helper_2() o_traits_specialize_base_statechart_helper_1() , public virtual phantom::statechart<t_S1, t_DTy>
#define o_traits_specialize_base_statechart_helper_3() o_traits_specialize_base_statechart_helper_2() , public virtual phantom::statechart<t_S2, t_DTy>
#define o_traits_specialize_base_statechart_helper_4() o_traits_specialize_base_statechart_helper_3() , public virtual phantom::statechart<t_S3, t_DTy>
#define o_traits_specialize_base_statechart_helper_5() o_traits_specialize_base_statechart_helper_4() , public virtual phantom::statechart<t_S4, t_DTy>
#define o_traits_specialize_base_statechart_helper_6() o_traits_specialize_base_statechart_helper_5() , public virtual phantom::statechart<t_S5, t_DTy>
#define o_traits_specialize_base_statechart_helper_7() o_traits_specialize_base_statechart_helper_6() , public virtual phantom::statechart<t_S6, t_DTy>
#define o_traits_specialize_base_statechart_helper_8() o_traits_specialize_base_statechart_helper_7() , public virtual phantom::statechart<t_S7, t_DTy>
#define o_traits_specialize_base_statechart_helper_9() o_traits_specialize_base_statechart_helper_8() , public virtual phantom::statechart<t_S8, t_DTy>
#define o_traits_specialize_base_statechart_helper_10() o_traits_specialize_base_statechart_helper_9() ,public virtual phantom::statechart<t_S9, t_DTy>

#define o_traits_specialize_base_statechart_helper(_count_) \
    template<typename t_Ty, typename t_DTy o_traits_base_helper_typename_base_class_list_##_count_() >\
struct base_statechart_helper<t_Ty, t_DTy o_traits_base_helper_base_class_list_##_count_() \
    o_traits_base_helper_base_class_void_list_##_count_()> : o_traits_specialize_base_statechart_helper_##_count_()\
{\
};

#define o_traits_begin_base_namespace_solverN(_namespaces_,_name_)\
    o_namespace_begin _namespaces_ \
    struct _name_##_base_namespace_solver {\
    typedef _name_ reflected_type;


#define o_traits_begin_base_namespace_solverNC(_namespaces_,_classes_,_name_)\
    o_namespace_begin _namespaces_ \
struct o_PP_CREATE_QUALIFIED_IDENTIFIER_NAME(_classes_, _name_##_base_namespace_solver) {\
    typedef o_PP_CREATE_QUALIFIED_NAME_RELATIVE( _classes_, _name_) reflected_type;

#define o_traits_begin_base_namespace_solverNT(_namespaces_,_template_types_ , _template_params_, _name_)\
    o_namespace_begin _namespaces_ \
    template<o_PP_MIX(_template_types_,_template_params_)>\
    struct _name_##_base_namespace_solver {\
    typedef _name_<o_PP_IDENTITY _template_params_> reflected_type;

#define o_traits_begin_base_namespace_solverC(_classes_,_name_)\
struct _name_##_base_namespace_solver {\
    typedef o_PP_CREATE_QUALIFIED_NAME_RELATIVE(_classes_, _name_) reflected_type;

#define o_traits_add_base_trait_to_base_namespace_solver(_trait_,_bases_)\
    typedef phantom::detail::_trait_##_helper< reflected_type, o_PP_IDENTITY _bases_ > _trait_##_____;

#define o_traits_add_base_trait_to_base_namespace_solverex(_trait_,_exT_,_exP_,_bases_)\
        template<_exT_ _exP_> struct _trait_##_____ : public ::phantom::detail::_trait_##_helper< reflected_type, _exP_, o_PP_IDENTITY _bases_ > {};

#define o_traits_end_base_namespace_solverN(_namespaces_)\
};\
o_namespace_end _namespaces_

#define o_traits_end_base_namespace_solverC()\
    };\


#define o_traits_specialize_base_traitB(_trait_,_name_, _bases_)\
    namespace phantom {\
    template<>\
    struct _trait_< ::_name_> \
    : public detail::_trait_##_helper< ::_name_, o_PP_IDENTITY _bases_> {};\
    }

#define o_traits_specialize_base_traitTB(_trait_, _template_types_ , _template_params_, _name_, _bases_)\
    namespace phantom {\
    template<o_PP_MIX(_template_types_,_template_params_)>\
    struct _trait_ < ::_name_ < o_PP_IDENTITY _template_params_ > >\
    : public detail::_trait_##_helper< ::_name_ < o_PP_IDENTITY _template_params_ >, o_PP_IDENTITY _bases_> {};\
    }

#define o_traits_specialize_base_traitCTB(_trait_, _classes_, _template_types_ , _template_params_, _name_, _bases_)\
    namespace phantom {\
    template<o_PP_MIX(_template_types_,_template_params_)>\
struct _trait_ < o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_) < o_PP_IDENTITY _template_params_ > >\
    : public detail::_trait_##_helper< o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_) < o_PP_IDENTITY _template_params_ >, o_PP_IDENTITY _bases_> {};\
    }

#define o_traits_specialize_base_traitN(_trait_,_namespaces_,_name_)\
    namespace phantom {\
    template<>\
    struct _trait_< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_)> \
    : public :: o_PP_CREATE_SCOPE _namespaces_ :: _name_##_base_namespace_solver::_trait_##_____{};\
    }

#define o_traits_specialize_base_traitNC(_trait_,_namespaces_,_classes_,_name_)\
    namespace phantom {\
    template<>\
struct _trait_< o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_)> \
    : public :: o_PP_CREATE_SCOPE _namespaces_ :: o_PP_CREATE_QUALIFIED_IDENTIFIER_NAME(_classes_, _name_##_base_namespace_solver)::_trait_##_____{};\
    }

#define o_traits_specialize_base_traitC(_trait_,_classes_,_name_)\
    namespace phantom {\
    template<>\
struct _trait_< o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)> \
    : public :: o_PP_CREATE_SCOPE _classes_ :: _name_##_base_namespace_solver::_trait_##_____{};\
    }

#define o_traits_specialize_base_traitNT(_trait_,_namespaces_, _template_types_ , _template_params_, _name_)\
    namespace phantom {\
    template<o_PP_MIX(_template_types_,_template_params_)>\
    struct _trait_ < o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_params_ > >\
    : public :: o_PP_CREATE_SCOPE _namespaces_ :: _name_##_base_namespace_solver< o_PP_IDENTITY _template_params_ >::_trait_##_____{};\
    }

#define o_traits_specialize_base_traitNCT(_trait_,_namespaces_, _classes_, _template_types_ , _template_params_, _name_)\
    namespace phantom {\
    template<o_PP_MIX(_template_types_,_template_params_)>\
struct _trait_ < o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) < o_PP_IDENTITY _template_params_ > >\
    : public :: o_PP_CREATE_SCOPE _namespaces_ :: o_PP_CREATE_QUALIFIED_IDENTIFIER_NAME(_classes_, _name_##_base_namespace_solver)< o_PP_IDENTITY _template_params_ >::_trait_##_____{};\
    }

#define o_traits_specialize_base_traitexS(_trait_,_exT_,_exP_,_name_, _bases_)\
    namespace phantom {\
    template<_exT_ _exP_>\
struct _trait_< ::_name_,_exP_> \
    : public detail::_trait_##_helper< ::_name_, _exP_, o_PP_IDENTITY _bases_> {};\
    }

#define o_traits_specialize_base_traitexTB(_trait_,_exT_,_exP_, _template_types_ , _template_params_, _name_, _bases_)\
    namespace phantom {\
    template<o_PP_MIX(_template_types_,_template_params_), _exT_ _exP_>\
struct _trait_ < ::_name_ < o_PP_IDENTITY _template_params_ >, _exP_ > \
    : public detail::_trait_##_helper< ::_name_< o_PP_IDENTITY _template_params_ >, _exP_, o_PP_IDENTITY _bases_> {};\
    }

#define o_traits_specialize_base_traitexCTB(_trait_,_exT_,_exP_, _classes_, _template_types_ , _template_params_, _name_, _bases_)\
    namespace phantom {\
    template<o_PP_MIX(_template_types_,_template_params_), _exT_ _exP_>\
struct _trait_ < o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_) < o_PP_IDENTITY _template_params_ >, _exP_ > \
    : public detail::_trait_##_helper< o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_)< o_PP_IDENTITY _template_params_ >, _exP_, o_PP_IDENTITY _bases_> {};\
    }

#define o_traits_specialize_base_traitexN(_trait_,_exT_,_exP_,_namespaces_,_name_)\
    namespace phantom {\
    template<_exT_ _exP_>\
struct _trait_< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_), _exP_ > \
    : public :: o_PP_CREATE_SCOPE _namespaces_ :: _name_##_base_namespace_solver:: o_NESTED_TEMPLATE _trait_##_____< _exP_ > {};\
    }

#define o_traits_specialize_base_traitexNC(_trait_,_exT_,_exP_,_namespaces_,_classes_,_name_)\
    namespace phantom {\
    template<_exT_ _exP_>\
struct _trait_< o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_), _exP_ > \
    : public :: o_PP_CREATE_SCOPE _namespaces_ :: o_PP_CREATE_QUALIFIED_IDENTIFIER_NAME(_classes_, _name_##_base_namespace_solver):: o_NESTED_TEMPLATE _trait_##_____< _exP_ > {};\
    }


#define o_traits_specialize_base_traitexNT(_trait_,_exT_,_exP_,_namespaces_, _template_types_ , _template_params_, _name_)\
    namespace phantom {\
    template<o_PP_MIX(_template_types_,_template_params_), _exT_ _exP_>\
struct _trait_ < o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_params_ >, _exP_ > \
    : public :: o_PP_CREATE_SCOPE _namespaces_ :: _name_##_base_namespace_solver< o_PP_IDENTITY _template_params_ >::o_NESTED_TEMPLATE _trait_##_____<_exP_> {};\
    }

#define o_traits_specialize_base_traitexC(_trait_,_exT_,_exP_,_classes_,_name_)\
    namespace phantom {\
    template<_exT_ _exP_>\
struct _trait_< o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_), _exP_ > \
    : public :: o_PP_CREATE_SCOPE _classes_ :: _name_##_base_namespace_solver:: o_NESTED_TEMPLATE _trait_##_____< _exP_ > {};\
    }

#define o_traits_specialize_base_traitexNCT(_trait_,_exT_,_exP_,_namespaces_, _classes_, _template_types_ , _template_params_, _name_)\
    namespace phantom {\
    template<o_PP_MIX(_template_types_,_template_params_), _exT_ _exP_>\
struct _trait_ < o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) < o_PP_IDENTITY _template_params_ >, _exP_ > \
    : public :: o_PP_CREATE_SCOPE _namespaces_ :: o_PP_CREATE_QUALIFIED_IDENTIFIER_NAME(_classes_, _name_##_base_namespace_solver)< o_PP_IDENTITY _template_params_ >::o_NESTED_TEMPLATE _trait_##_____<_exP_> {};\
    }

#define o_traits_specialize_all_base_traitB(_name_, _bases_) \
    o_traits_specialize_base_traitexS(base_statechart,typename, t_S,_name_, _bases_)\
    o_traits_specialize_base_traitB(base_class_count_of,_name_, _bases_)\
    o_traits_specialize_base_traitexS(base_class_index_of,typename, t_S,_name_, _bases_)\
    o_traits_specialize_base_traitexS(base_class_of, int, t_index,_name_, _bases_)\
    o_traits_specialize_base_traitB(base_total_track_count_of, _name_, _bases_)

#define o_traits_specialize_all_base_traitTB(_template_types_ , _template_params_, _name_, _bases_) \
    o_traits_specialize_base_traitexTB(base_statechart, typename, t_S, _template_types_ , _template_params_, _name_, _bases_)\
    o_traits_specialize_base_traitTB(base_class_count_of, _template_types_ , _template_params_, _name_, _bases_)\
    o_traits_specialize_base_traitexTB(base_class_index_of,typename, t_S, _template_types_ , _template_params_, _name_, _bases_)\
    o_traits_specialize_base_traitexTB(base_class_of, int, t_index,_template_types_ , _template_params_, _name_, _bases_)\
    o_traits_specialize_base_traitTB(base_total_track_count_of, _template_types_ , _template_params_, _name_, _bases_)

#define o_traits_specialize_all_base_traitNB(_namespaces_, _name_, _bases_) \
    o_traits_begin_base_namespace_solverN(_namespaces_,_name_)\
    o_traits_add_base_trait_to_base_namespace_solver(base_class_count_of,_bases_)\
    o_traits_add_base_trait_to_base_namespace_solverex(base_statechart,typename, t_S,_bases_)\
    o_traits_add_base_trait_to_base_namespace_solverex(base_class_index_of,typename, t_S,_bases_)\
    o_traits_add_base_trait_to_base_namespace_solverex(base_class_of, int, t_index,_bases_)\
    o_traits_add_base_trait_to_base_namespace_solver(base_total_track_count_of,_bases_)\
    o_traits_end_base_namespace_solverN(_namespaces_)\
    o_traits_specialize_base_traitN(base_class_count_of,_namespaces_, _name_)\
    o_traits_specialize_base_traitexN(base_statechart,typename, t_S,_namespaces_, _name_)\
    o_traits_specialize_base_traitexN(base_class_index_of,typename, t_S,_namespaces_, _name_)\
    o_traits_specialize_base_traitexN(base_class_of, int, t_index,_namespaces_, _name_)\
    o_traits_specialize_base_traitN(base_total_track_count_of, _namespaces_, _name_)\

#define o_traits_specialize_all_base_traitNCB(_namespaces_, _classes_,_name_, _bases_) \
    o_traits_begin_base_namespace_solverNC(_namespaces_,_classes_,_name_)\
    o_traits_add_base_trait_to_base_namespace_solver(base_class_count_of,_bases_)\
    o_traits_add_base_trait_to_base_namespace_solverex(base_statechart,typename, t_S,_bases_)\
    o_traits_add_base_trait_to_base_namespace_solverex(base_class_index_of,typename, t_S,_bases_)\
    o_traits_add_base_trait_to_base_namespace_solverex(base_class_of, int, t_index,_bases_)\
    o_traits_add_base_trait_to_base_namespace_solver(base_total_track_count_of,_bases_)\
    o_traits_end_base_namespace_solverN(_namespaces_)\
    o_traits_specialize_base_traitNC(base_class_count_of,_namespaces_,_classes_, _name_)\
    o_traits_specialize_base_traitexNC(base_statechart,typename, t_S,_namespaces_,_classes_, _name_)\
    o_traits_specialize_base_traitexNC(base_class_index_of,typename, t_S,_namespaces_,_classes_, _name_)\
    o_traits_specialize_base_traitexNC(base_class_of, int, t_index,_namespaces_,_classes_, _name_)\
    o_traits_specialize_base_traitNC(base_total_track_count_of, _namespaces_,_classes_, _name_)\

#define o_traits_specialize_all_base_traitCB(_classes_, _name_, _bases_) \
    o_traits_begin_base_namespace_solverC(_classes_,_name_)\
    o_traits_add_base_trait_to_base_namespace_solver(base_class_count_of,_bases_)\
    o_traits_add_base_trait_to_base_namespace_solverex(base_statechart,typename, t_S,_bases_)\
    o_traits_add_base_trait_to_base_namespace_solverex(base_class_index_of,typename, t_S,_bases_)\
    o_traits_add_base_trait_to_base_namespace_solverex(base_class_of, int, t_index,_bases_)\
    o_traits_add_base_trait_to_base_namespace_solver(base_total_track_count_of,_bases_)\
    o_traits_end_base_namespace_solverC(_classes_)\
    o_traits_specialize_base_traitC(base_class_count_of,_classes_, _name_)\
    o_traits_specialize_base_traitexC(base_statechart,typename, t_S,_classes_, _name_)\
    o_traits_specialize_base_traitexC(base_class_index_of,typename, t_S,_classes_, _name_)\
    o_traits_specialize_base_traitexC(base_class_of, int, t_index,_classes_, _name_)\
    o_traits_specialize_base_traitC(base_total_track_count_of, _classes_, _name_)\


#define o_traits_specialize_all_base_traitNTB(_namespaces_, _template_types_ , _template_params_, _name_, _bases_) \
    o_traits_begin_base_namespace_solverNT(_namespaces_,_template_types_ , _template_params_, _name_)\
    o_traits_add_base_trait_to_base_namespace_solverex(base_statechart,typename, t_S,_bases_)\
    o_traits_add_base_trait_to_base_namespace_solver(base_class_count_of,_bases_)\
    o_traits_add_base_trait_to_base_namespace_solverex(base_class_index_of,typename, t_S,_bases_)\
    o_traits_add_base_trait_to_base_namespace_solverex(base_class_of, int, t_index,_bases_)\
    o_traits_add_base_trait_to_base_namespace_solver(base_total_track_count_of,_bases_)\
    o_traits_end_base_namespace_solverN(_namespaces_)\
    o_traits_specialize_base_traitexNT(base_statechart,typename, t_S,_namespaces_, _template_types_ , _template_params_,_name_)\
    o_traits_specialize_base_traitNT(base_class_count_of,_namespaces_, _template_types_ , _template_params_,_name_)\
    o_traits_specialize_base_traitexNT(base_class_index_of,typename, t_S,_namespaces_, _template_types_ , _template_params_,_name_)\
    o_traits_specialize_base_traitexNT(base_class_of, int, t_index,_namespaces_, _template_types_ , _template_params_,_name_)\
    o_traits_specialize_base_traitNT(base_total_track_count_of, _namespaces_, _template_types_ , _template_params_,_name_)\

#define o_traits_specialize_all_base_traitCTB(_classes_, _template_types_ , _template_params_, _name_, _bases_) \
    o_traits_specialize_base_traitexCTB(base_statechart,typename, t_S,_classes_, _template_types_ , _template_params_,_name_)\
    o_traits_specialize_base_traitCTB(base_class_count_of,_classes_, _template_types_ , _template_params_,_name_)\
    o_traits_specialize_base_traitexCTB(base_class_index_of,typename, t_S,_classes_, _template_types_ , _template_params_,_name_)\
    o_traits_specialize_base_traitexCTB(base_class_of, int, t_index,_classes_, _template_types_ , _template_params_,_name_)\
    o_traits_specialize_base_traitCTB(base_total_track_count_of, _classes_, _template_types_ , _template_params_,_name_)\

#define o_traits_specialize_all_base_traitNCTB(_namespaces_, _classes_, _template_types_ , _template_params_, _name_, _bases_) \
    o_traits_begin_base_namespace_solverNT(_namespaces_,_template_types_ , _template_params_, _name_)\
    o_traits_add_base_trait_to_base_namespace_solverex(base_statechart,typename, t_S,_bases_)\
    o_traits_add_base_trait_to_base_namespace_solver(base_class_count_of,_bases_)\
    o_traits_add_base_trait_to_base_namespace_solverex(base_class_index_of,typename, t_S,_bases_)\
    o_traits_add_base_trait_to_base_namespace_solverex(base_class_of, int, t_index,_bases_)\
    o_traits_add_base_trait_to_base_namespace_solver(base_total_track_count_of,_bases_)\
    o_traits_end_base_namespace_solverN(_namespaces_)\
    o_traits_specialize_base_traitexNCT(base_statechart,typename, t_S,_namespaces_, _classes_,_template_types_ , _template_params_,_name_)\
    o_traits_specialize_base_traitNCT(base_class_count_of,_namespaces_, _classes_,_template_types_ , _template_params_,_name_)\
    o_traits_specialize_base_traitexNCT(base_class_index_of,typename, t_S,_namespaces_, _classes_,_template_types_ , _template_params_,_name_)\
    o_traits_specialize_base_traitexNCT(base_class_of, int, t_index,_namespaces_, _classes_,_template_types_ , _template_params_,_name_)\
    o_traits_specialize_base_traitNCT(base_total_track_count_of, _namespaces_, _classes_, _template_types_ , _template_params_,_name_)\


#define o_traits_specialize_base_helpers(_count_) \
    o_traits_specialize_base_class_of_helper(_count_) \
    o_traits_specialize_base_class_index_of_helper(_count_) \
    o_traits_specialize_base_statechart_helper(_count_) \
    o_traits_specialize_base_class_count_of_helper(_count_) \
    o_traits_specialize_base_total_track_count_of_helper(_count_)

#define o_traits_opT(_trait_, l0, op)\
    o_PP_CAT o_PP_LEFT_PAREN o_traits_opT_,o_PP_NARG_FUNC()l0 o_PP_RIGHT_PAREN (_trait_, l0, op)

#define o_traits_opT_1(_trait_, l0, op) _trait_<o_PP_CAT(o_PP_ARG_0,l0)>::value
#define o_traits_opT_2(_trait_, l0, op) o_traits_opT_1(_trait_, l0, op) op _trait_<o_PP_CAT(o_PP_ARG_1,l0)>::value
#define o_traits_opT_3(_trait_, l0, op) o_traits_opT_2(_trait_, l0, op) op _trait_<o_PP_CAT(o_PP_ARG_2,l0)>::value
#define o_traits_opT_4(_trait_, l0, op) o_traits_opT_3(_trait_, l0, op) op _trait_<o_PP_CAT(o_PP_ARG_3,l0)>::value
#define o_traits_opT_5(_trait_, l0, op) o_traits_opT_4(_trait_, l0, op) op _trait_<o_PP_CAT(o_PP_ARG_4,l0)>::value
#define o_traits_opT_6(_trait_, l0, op) o_traits_opT_5(_trait_, l0, op) op _trait_<o_PP_CAT(o_PP_ARG_5,l0)>::value
#define o_traits_opT_7(_trait_, l0, op) o_traits_opT_6(_trait_, l0, op) op _trait_<o_PP_CAT(o_PP_ARG_6,l0)>::value
#define o_traits_opT_8(_trait_, l0, op) o_traits_opT_7(_trait_, l0, op) op _trait_<o_PP_CAT(o_PP_ARG_7,l0)>::value
#define o_traits_opT_9(_trait_, l0, op) o_traits_opT_8(_trait_, l0, op) op _trait_<o_PP_CAT(o_PP_ARG_8,l0)>::value


#define o_traits_specializeNT(_trait_,_value_,_namespaces_,_template_types_,_template_params_,_name_)\
    namespace phantom { \
    template<o_PP_MIX(_template_types_,_template_params_)>\
struct _trait_< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_params_ > >\
{\
    o_PP_IDENTITY _value_;\
};\
    }

// #define o_traits_specializeNTC(_trait_,_value_,_namespaces_,_template_types_,_template_params_,_class_,_name_)\
//     namespace phantom { \
//     template<o_PP_MIX(_template_types_,_template_params_)>\
// struct _trait_< o_NESTED_TYPE o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_class_) < o_PP_IDENTITY _template_params_ >::_name_ >\
// {\
//     o_PP_IDENTITY _value_;\
// };\
//     }

#define o_traits_specializeNPT(_trait_,_value_,_namespaces_,_template_types_,_template_params_,_template_spec_,_name_)\
    namespace phantom { \
    template<o_PP_MIX(_template_types_,_template_params_)>\
struct _trait_< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) < o_PP_IDENTITY _template_spec_ > >\
{\
    o_PP_IDENTITY _value_;\
};\
    }

#define o_traits_specializeT(_trait_,_value_,_template_types_,_template_params_,_name_)\
    namespace phantom { \
    template<o_PP_MIX(_template_types_,_template_params_)>\
struct _trait_< ::_name_ < o_PP_IDENTITY _template_params_ > >\
{\
    o_PP_IDENTITY _value_;\
};\
    }

#define o_traits_specializeCT(_trait_,_value_,_classes_,_template_types_,_template_params_,_name_)\
    namespace phantom { \
    template<o_PP_MIX(_template_types_,_template_params_)>\
struct _trait_< o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_) < o_PP_IDENTITY _template_params_ > >\
{\
    o_PP_IDENTITY _value_;\
};\
    }


#define o_traits_specializeN(_trait_,_value_,_namespaces_,_name_)\
    namespace phantom { \
    template<>\
struct _trait_< o_PP_CREATE_QUALIFIED_NAME(_namespaces_,_name_) >\
{\
    o_PP_IDENTITY _value_;\
};\
    }


#define o_traits_specializeC(_trait_,_value_,_classes_,_name_)\
    namespace phantom { \
    template<>\
struct _trait_< o_PP_CREATE_QUALIFIED_NAME(_classes_,_name_) >\
{\
    o_PP_IDENTITY _value_;\
};\
    }


#define o_traits_specializeNC(_trait_,_value_,_namespaces_,_classes_,_name_)\
    namespace phantom { \
    template<>\
struct _trait_< o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) >\
{\
    o_PP_IDENTITY _value_;\
};\
    }


#define o_traits_specializeNCT(_trait_,_value_,_namespaces_,_classes_,_template_types_,_template_params_,_name_)\
    namespace phantom { \
    template<o_PP_MIX(_template_types_,_template_params_)>\
struct _trait_< o_PP_CREATE_QUALIFIED_NAME_2(_namespaces_,_classes_,_name_) < o_PP_IDENTITY _template_params_ > >\
{\
    o_PP_IDENTITY _value_;\
};\
    }

#define o_traits_specialize(_trait_,_value_,_name_)\
    namespace phantom { \
    template<>\
struct _trait_< ::_name_ >\
{\
    o_PP_IDENTITY _value_;\
};\
    }

#define o_traits_specialize_primitive(_trait_,_name_,_value_)\
    namespace phantom { \
    template<>\
struct _trait_< _name_ >\
{\
    o_PP_IDENTITY _value_;\
};\
    }



o_traits_specialize_base_helpers(0)
o_traits_specialize_base_helpers(1)
o_traits_specialize_base_helpers(2)
o_traits_specialize_base_helpers(3)
o_traits_specialize_base_helpers(4)
o_traits_specialize_base_helpers(5)
o_traits_specialize_base_helpers(6)
o_traits_specialize_base_helpers(7)
o_traits_specialize_base_helpers(8)
o_traits_specialize_base_helpers(9)

template<typename t_Ty, typename t_DTy>
struct enclosed_statechart_base_____
{
    template<typename U>
    static boost::type_traits::no_type phantom_proxy_generator_track_counter_filter(...);
};


template <class t_Ty>
class template_arg_friend_helper
{
public:
    typedef t_Ty    type;
};
template < typename t_Ty >
struct fake_array_helper
{
public:
    t_Ty        operator[](size_t i) { return t_Ty();}
};
template< typename t_Ty, size_t t_size >
class inline_array_type_helper
{
public:
    typedef t_Ty type[t_size];
};
template < typename t_Ty >
class inline_array_type_helper<t_Ty, 0>
{
public:
    typedef fake_array_helper<t_Ty> type;
};


#if o_COMPILER == o_COMPILER_GCC
template < typename t_Ty >
class    allocator_template_disambiguator_compiler_GCC_specific
{
public:
    typedef typename t_Ty::template allocator<t_Ty>::instance allocator;
};
#endif
template <size_t t_modifiers = 0>
class int_embedder
{
public:
    enum { value = t_modifiers };
};

o_namespace_end(phantom, detail)

o_namespace_begin(phantom)

template<typename t_Ty>
struct is_void : public detail::is_void_<t_Ty> {};

template<typename t_Ty>
struct is_signal_t : public detail::is_signal_t_<t_Ty> {};

template<typename t_Ty>
struct has_reflection
    : public detail::has_enclosed_reflection<t_Ty>
{

};

template<typename t_Ty>
struct has_reflection<t_Ty*>
{
    BOOST_STATIC_CONSTANT(bool, value = has_reflection<t_Ty>::value);
};
template<typename t_Ty>
struct has_reflection<t_Ty&>
{
    BOOST_STATIC_CONSTANT(bool, value = has_reflection<t_Ty>::value);
};
template<typename t_Ty>
struct has_reflection<t_Ty const>
{
    BOOST_STATIC_CONSTANT(bool, value = has_reflection<t_Ty>::value);
};

template<typename t_Ty>
struct has_statechart : public detail::has_enclosed_statechart<t_Ty> {};

template<typename t_Ty>
struct has_statechart_cascade : detail::has_statechart_cascade_helper_<t_Ty, base_class_count_of<t_Ty>::value> {};

template<typename t_Ty>
struct has_base_statechart_cascade : public detail::has_base_statechart_cascade_<t_Ty> {};

/// has_module specialized in o_classX
template<typename t_Ty>
struct has_module : public has_reflection<t_Ty>
{

};

template<typename t_Ty>
struct has_full_module
{
    const static bool value = has_module<t_Ty>::value;
};

template<typename t_Ty>
struct proxy_of
{
    typedef t_Ty type;
};

template<typename t_Ty>
struct is_root_class
{
    static const boolean value = boost::is_class<t_Ty>::value
        AND base_class_count_of<t_Ty>::value == 0 ;
};

template<typename t_Ty>
struct is_root_type
{
    static const boolean value = base_class_count_of<t_Ty>::value == 0;
};

template<typename t_Ty>
struct has_root_statechart {
    const static boolean value = has_statechart<t_Ty>::value
        AND NOT(has_base_statechart_cascade<t_Ty>::value);
};

template<typename t_Ty>
struct first_base_statechart_class_of : public detail::first_base_statechart_class_of_helper_
    <
    t_Ty
    , has_statechart<t_Ty>::value
    , has_base_statechart_cascade<t_Ty>::value
    > {};

template<typename t_Ty>
struct meta_specifiers
{
    const static int value = 0;
};

template<typename t_Ty, int t_spec>
struct has_meta_specifier
{
    const static bool value = (meta_specifiers<t_Ty>::value & t_spec) == t_spec;
};

template<typename t_Ty>
struct is_meta_type
{
    BOOST_STATIC_CONSTANT(bool, value = false);
};

template<typename t_Ty, typename Sig>
struct has_destroyed_member_function;

template<typename t_Ty>
struct enum_integral_type : public detail::enum_integral_type_<t_Ty> {};


    template <typename type>
    class has_member_function_void_exp_result
    {};
    template <typename type, typename U>
    U const& operator,(U const&, has_member_function_void_exp_result<type>);
    template <typename type, typename U>
    U& operator,(U&, has_member_function_void_exp_result<type>);
    template <typename src_type, typename dest_type>
    struct has_member_function_clone_constness
    {
        typedef dest_type type;
    };
    template <typename src_type, typename dest_type>
    struct has_member_function_clone_constness<const src_type, dest_type>
    {
        typedef const dest_type type;
    };


#define o_create_has_member_function_0(foo)\
template <typename Type>                                                          \
class _____has_member_##foo                                                                  \
{                                                                                 \
    class yes { char m;};                                                         \
    class no { yes m[2];};                                                        \
    struct BaseMixin                                                              \
    {                                                                             \
        void foo(){}                                                              \
    };                                                                            \
    struct Base : public Type, public BaseMixin {};                               \
    template <typename T, T t>  class Helper{};                                   \
    template <typename U>                                                         \
    static no deduce(U*, Helper<void (BaseMixin::*)(), &U::foo>*                  \
        = 0);                                                                     \
    static yes deduce(...);                                                       \
public:                                                                           \
    static const bool result = sizeof(yes) == sizeof(deduce((Base*)               \
        (0)));                                                                    \
};                                                                                \
                                                                                  \
template <typename type, typename call_details>                                   \
    struct has_member_function_##foo                                                       \
{                                                                                 \
private:                                                                          \
    class yes {};                                                                 \
    class no { yes m[2]; };                                                       \
    struct derived : public type                                                  \
    {                                                                             \
        using type::foo;                                                          \
        no foo(...) const;                                                        \
    };                                                                            \
    typedef typename has_member_function_clone_constness<type, derived>::type              \
        derived_type;                                                             \
    template <typename T, typename due_type>                                      \
    struct return_value_check                                                     \
    {                                                                             \
        static yes deduce(due_type);                                              \
        static no deduce(...);                                                    \
        static no deduce(no);                                                     \
        static no deduce(has_member_function_void_exp_result<type>);                       \
    };                                                                            \
    template <typename T>                                                         \
    struct return_value_check<T, void>                                            \
    {                                                                             \
        static yes deduce(...);                                                   \
        static no deduce(no);                                                     \
    };                                                                            \
    template <bool has, typename F>                                               \
    struct impl                                                                   \
    {                                                                             \
        static const bool value = false;                                          \
    };                                                                            \
    template <typename r>                                                         \
    struct impl<true, r()>                                                        \
    {                                                                             \
        static const bool value =                                                 \
            sizeof(                                                               \
            return_value_check<type, r>::deduce(                                  \
            (((derived_type*)0)->foo(),                                           \
            has_member_function_void_exp_result<type>())                                   \
            )                                                                     \
            ) == sizeof(yes);                                                     \
    };                                                                            \
public:                                                                           \
    static const bool value = impl<_____has_member_##foo<type>::result,           \
        call_details>::value;                                                     \
};




#define o_create_has_member_function_const_0(foo)\
    template <typename Type>                                                          \
    class _____has_member_##foo                                                                  \
    {                                                                                 \
    class yes { char m;};                                                         \
    class no { yes m[2];};                                                        \
    struct BaseMixin                                                              \
    {                                                                             \
    phantom::signal_t foo() {}                                                              \
    };                                                                            \
    struct Base : public Type, public BaseMixin {};                               \
    template <typename T, T t>  class Helper{};                                   \
    template <typename U>                                                         \
    static no deduce(U*, Helper<phantom::signal_t (BaseMixin::*)(), &U::foo>*                  \
    = 0);                                                                     \
    static yes deduce(...);                                                       \
    public:                                                                           \
    static const bool result = sizeof(yes) == sizeof(deduce((Base*)               \
    (0)));                                                                    \
    };                                                                                \
    \
    template <typename type, typename call_details>                                   \
    struct has_member_function_##foo                                                       \
    {                                                                                 \
    private:                                                                          \
    class yes {};                                                                 \
    class no { yes m[2]; };                                                       \
    struct derived : public type                                                  \
    {                                                                             \
    using type::foo;                                                          \
    no foo(...) const;                                                        \
    };                                                                            \
    typedef typename has_member_function_clone_constness<type, derived>::type              \
    derived_type;                                                             \
    template <typename T, typename due_type>                                      \
    struct return_value_check                                                     \
    {                                                                             \
    static yes deduce(due_type);                                              \
    static no deduce(...);                                                    \
    static no deduce(no);                                                     \
    static no deduce(has_member_function_void_exp_result<type>);                       \
    };                                                                            \
    template <typename T>                                                         \
    struct return_value_check<T, signal_t>                                            \
    {                                                                             \
    static yes deduce(...);                                                   \
    static no deduce(no);                                                     \
    };                                                                            \
    template <bool has, typename F>                                               \
    struct impl                                                                   \
    {                                                                             \
    static const bool value = false;                                          \
    };                                                                            \
    template <typename r>                                                         \
    struct impl<true, r()>                                                        \
    {                                                                             \
    static const bool value =                                                 \
    sizeof(                                                               \
    return_value_check<type, r>::deduce(                                  \
    (((derived_type*)0)->foo(),                                           \
    has_member_function_void_exp_result<type>())                                   \
    )                                                                     \
    ) == sizeof(yes);                                                     \
    };                                                                            \
    public:                                                                           \
    static const bool value = impl<_____has_member_##foo<type>::result,           \
    call_details>::value;                                                     \
    };








#define o_create_has_member_function_1(foo)                                                      \
    template <typename Type>                                                            \
    class ____has_member_##foo                                                          \
    {                                                                                   \
        class yes { char m;};                                                           \
        class no { yes m[2];};                                                          \
        struct BaseMixin                                                                \
        {                                                                               \
            void foo(){}                                                                \
        };                                                                              \
        struct Base : public Type, public BaseMixin {};                                 \
        template <typename T, T t>  class Helper{};                                     \
        template <typename U>                                                           \
        static no deduce(U*, Helper<void (BaseMixin::*)(), &U::foo>*                    \
            = 0);                                                                       \
        static yes deduce(...);                                                         \
    public:                                                                             \
        static const bool result = sizeof(yes) == sizeof(deduce((Base*)                 \
            (0)));                                                                      \
    };                                                                                  \
                                                                                        \
    template <typename type, typename call_details>                                     \
    struct has_member_function_##foo                                                             \
    {                                                                                   \
    private:                                                                            \
        class yes {};                                                                   \
        class no { yes m[2]; };                                                         \
        struct derived : public type                                                    \
        {                                                                               \
            using type::foo;                                                            \
            no foo(...) const;                                                          \
        };                                                                              \
        typedef typename has_member_function_clone_constness<type, derived>::type                \
            derived_type;                                                               \
        template <typename T, typename due_type>                                        \
        struct return_value_check                                                       \
        {                                                                               \
            static yes deduce(due_type);                                                \
            static no deduce(...);                                                      \
            static no deduce(no);                                                       \
            static no deduce(has_member_function_void_exp_result<type>);                         \
        };                                                                              \
        template <typename T>                                                           \
        struct return_value_check<T, void>                                              \
        {                                                                               \
            static yes deduce(...);                                                     \
            static no deduce(no);                                                       \
        };                                                                              \
        template <bool has, typename F>                                                 \
        struct impl                                                                     \
        {                                                                               \
            static const bool value = false;                                            \
        };                                                                              \
        template <typename arg1, typename r>                                            \
        struct impl<true, r(arg1)>                                                      \
        {                                                                               \
            static const bool value =                                                   \
                sizeof(                                                                 \
                return_value_check<type, r>::deduce(                                    \
                (((derived_type*)0)->foo(*(arg1*)0),                                    \
                has_member_function_void_exp_result<type>())                            \
                )                                                                       \
                ) == sizeof(yes);                                                       \
        };                                                                              \
    public:                                                                             \
        static const bool value = impl<____has_member_##foo<type>::result,              \
            call_details>::value;                                                       \
    };




#define o_create_has_member_function_2(foo)                                                      \
    template <typename Type>                                                            \
class ____has_member_##foo                                                          \
    {                                                                                   \
class yes { char m;};                                                           \
class no { yes m[2];};                                                          \
struct BaseMixin                                                                \
        {                                                                               \
        void foo(){}                                                                \
        };                                                                              \
struct Base : public Type, public BaseMixin {};                                 \
    template <typename T, T t>  class Helper{};                                     \
    template <typename U>                                                           \
    static no deduce(U*, Helper<void (BaseMixin::*)(), &U::foo>*                    \
    = 0);                                                                       \
    static yes deduce(...);                                                         \
    public:                                                                             \
    static const bool result = sizeof(yes) == sizeof(deduce((Base*)                 \
    (0)));                                                                      \
    };                                                                                  \
    \
    template <typename type, typename call_details>                                     \
struct has_member_function_##foo                                                             \
    {                                                                                   \
    private:                                                                            \
class yes {};                                                                   \
class no { yes m[2]; };                                                         \
struct derived : public type                                                    \
        {                                                                               \
        using type::foo;                                                            \
        no foo(...) const;                                                          \
        };                                                                              \
        typedef typename has_member_function_clone_constness<type, derived>::type                \
        derived_type;                                                               \
        template <typename T, typename due_type>                                        \
struct return_value_check                                                       \
        {                                                                               \
        static yes deduce(due_type);                                                \
        static no deduce(...);                                                      \
        static no deduce(no);                                                       \
        static no deduce(has_member_function_void_exp_result<type>);                         \
        };                                                                              \
        template <typename T>                                                           \
struct return_value_check<T, void>                                              \
        {                                                                               \
        static yes deduce(...);                                                     \
        static no deduce(no);                                                       \
        };                                                                              \
        template <bool has, typename F>                                                 \
struct impl                                                                     \
        {                                                                               \
        static const bool value = false;                                            \
        };                                                                              \
        template <typename arg1, typename arg2, typename r>                                            \
struct impl<true, r(arg1,arg2)>                                                      \
        {                                                                               \
        static const bool value =                                                   \
        sizeof(                                                                 \
        return_value_check<type, r>::deduce(                                    \
        (((derived_type*)0)->foo(*(arg1*)0,*(arg2*)0),                                    \
        has_member_function_void_exp_result<type>())                            \
        )                                                                       \
        ) == sizeof(yes);                                                       \
        };                                                                              \
    public:                                                                             \
    static const bool value = impl<____has_member_##foo<type>::result,              \
    call_details>::value;                                                       \
    };

o_create_has_member_function_0(PHANTOM_CODEGEN_initialize)
o_create_has_member_function_0(PHANTOM_CODEGEN_terminate)
o_create_has_member_function_2(PHANTOM_CODEGEN_restore)

BOOST_MPL_HAS_XXX_TRAIT_DEF(PHANTOM_CODEGEN_smdataptr_marker);
BOOST_MPL_HAS_XXX_TRAIT_DEF(PHANTOM_CODEGEN_destroyed_marker)

template<typename t_Ty>
struct has_smdataptr
    : public has_PHANTOM_CODEGEN_smdataptr_marker<t_Ty>
{

};

template<typename t_Ty>
struct has_destroyed_signal
    : public has_PHANTOM_CODEGEN_destroyed_marker<t_Ty>
{

};

template<typename t_Ty, bool t_has_member_function, int t_base_class_count>
struct has_destroyed_signal_declared_helper
{
    typedef char yes;
    typedef long no;

    typedef typename base_class_of<t_Ty,t_base_class_count-1>::type base_class;

    static yes deduce(phantom::signal_t (t_Ty::*)());
    static no deduce(phantom::signal_t (base_class ::*)());

    enum { value = sizeof(deduce(&t_Ty::PHANTOM_CODEGEN_destroyed)) == sizeof(yes)
        AND has_destroyed_signal_declared_helper<t_Ty, t_has_member_function, t_base_class_count-1>::value };
};

template<typename t_Ty, int t_base_class_count>
struct has_destroyed_signal_declared_helper<t_Ty, false, t_base_class_count>
{
    enum {value = false };
};

template<typename t_Ty, bool t_has_member_function>
struct has_destroyed_signal_declared_helper<t_Ty, t_has_member_function, 0>
{
    enum {value = t_has_member_function };
};

template<typename t_Ty>
struct has_destroyed_signal_declared_helper<t_Ty, false, 0>
{
    enum {value = false };
};

template<typename t_Ty>
struct has_destroyed_signal_declared
    : public has_destroyed_signal_declared_helper<t_Ty
    , has_destroyed_signal<t_Ty>::value
    , base_class_count_of<t_Ty>::value>
{

};

template<typename t_Ty>
struct has_initializer_member_function_restore
    : public has_member_function_PHANTOM_CODEGEN_restore<t_Ty, phantom::restore_state (phantom::uint, phantom::restore_pass)>
{

};

// RESTORE METHOD DECLARATION EXISTENCE

template<typename t_Ty, bool t_has_member_function, int t_base_class_count>
struct has_initializer_member_function_restore_declared_helper
{
    typedef char yes;
    typedef long no;

    typedef typename base_class_of<t_Ty,t_base_class_count-1>::type base_class;

    static yes deduce(phantom::restore_state (t_Ty::*)(phantom::uint,phantom::restore_pass));
    static no deduce(phantom::restore_state (base_class ::*)(phantom::uint,phantom::restore_pass));

    enum { value = sizeof(deduce(&t_Ty::PHANTOM_CODEGEN_restore)) == sizeof(yes)
        AND has_initializer_member_function_restore_declared_helper<t_Ty, t_has_member_function, t_base_class_count-1>::value };
};


template<typename t_Ty>
struct has_initializer_member_function_restore_declared_helper<t_Ty, false, 0>
{
    enum {value = false };
};

template<typename t_Ty, int t_base_class_count>
struct has_initializer_member_function_restore_declared_helper<t_Ty, false, t_base_class_count>
{
    enum {value = false };
};

template<typename t_Ty, bool t_has_member_function>
struct has_initializer_member_function_restore_declared_helper<t_Ty, t_has_member_function, 0>
{
    enum {value = t_has_member_function };
};

template<typename t_Ty>
struct has_initializer_member_function_restore_declared
    : public has_initializer_member_function_restore_declared_helper<t_Ty
    , has_initializer_member_function_restore<t_Ty>::value
    , base_class_count_of<t_Ty>::value>
{

};


// INITIALIZE METHOD EXISTENCE

template<typename t_Ty>
struct has_initializer_member_function_initialize
    : public has_member_function_PHANTOM_CODEGEN_initialize<t_Ty, void()>
{

};

// INITIALIZE METHOD DECLARATION EXISTENCE

template<typename t_Ty, bool t_has_member_function, int t_base_class_count>
struct has_initializer_member_function_initialize_declared_helper
{
    typedef char yes;
    typedef long no;

    typedef typename base_class_of<t_Ty,t_base_class_count-1>::type base_class;

    static yes deduce(void (t_Ty::*)());
    static no deduce(void (base_class ::*)());

    enum { value = sizeof(deduce(&t_Ty::PHANTOM_CODEGEN_initialize)) == sizeof(yes)
            AND has_initializer_member_function_initialize_declared_helper<t_Ty, t_has_member_function, t_base_class_count-1>::value };
};

template<typename t_Ty, int t_base_class_count>
struct has_initializer_member_function_initialize_declared_helper<t_Ty, false, t_base_class_count>
{
    enum {value = false };
};

template<typename t_Ty, bool t_has_member_function>
struct has_initializer_member_function_initialize_declared_helper<t_Ty, t_has_member_function, 0>
{
    enum {value = t_has_member_function };
};

template<typename t_Ty>
struct has_initializer_member_function_initialize_declared_helper<t_Ty, false, 0>
{
    enum {value = false };
};

template<typename t_Ty>
struct has_initializer_member_function_initialize_declared
    : public has_initializer_member_function_initialize_declared_helper<t_Ty
    , has_initializer_member_function_initialize<t_Ty>::value
    , base_class_count_of<t_Ty>::value>
{

};

// EXISTENCE TRAIT

template<typename t_Ty>
struct has_initializer_member_function_terminate
    : public has_member_function_PHANTOM_CODEGEN_terminate<t_Ty, void()>
{

};

// DECLARATION EXISTENCE TRAIT

template<typename t_Ty, bool t_has_member_function, int t_base_class_count>
struct has_initializer_member_function_terminate_declared_helper
{
    typedef char yes;
    typedef long no;

    typedef typename base_class_of<t_Ty,t_base_class_count-1>::type base_class;

    static yes deduce(void (t_Ty::*)());
    static no deduce(void (base_class ::*)());

    enum { value = sizeof(deduce(&t_Ty::PHANTOM_CODEGEN_terminate)) == sizeof(yes)
        AND has_initializer_member_function_terminate_declared_helper<t_Ty, t_has_member_function, t_base_class_count-1>::value };
};


template<typename t_Ty>
struct has_initializer_member_function_terminate_declared_helper<t_Ty, false, 0>
{
    enum {value = false };
};

template<typename t_Ty, int t_base_class_count>
struct has_initializer_member_function_terminate_declared_helper<t_Ty, false, t_base_class_count>
{
    enum {value = false };
};

template<typename t_Ty, bool t_has_member_function>
struct has_initializer_member_function_terminate_declared_helper<t_Ty, t_has_member_function, 0>
{
    enum {value = t_has_member_function };
};

template<typename t_Ty>
struct has_initializer_member_function_terminate_declared
    : public has_initializer_member_function_terminate_declared_helper<t_Ty, has_initializer_member_function_terminate<t_Ty>::value, base_class_count_of<t_Ty>::value>
{

};

template<typename t_Ty, bool t_is_class>
struct has_initializer_member_functions_helper
{
    static const bool value =
            has_initializer_member_function_initialize<t_Ty>::value
            AND
            has_initializer_member_function_terminate<t_Ty>::value
            AND
            has_initializer_member_function_restore<t_Ty>::value;

};

template<typename t_Ty>
struct has_initializer_member_functions_helper<t_Ty, false> : public detail::false_
{
};

template<typename t_Ty>
struct has_initializer_member_functions
    : public has_initializer_member_functions_helper<t_Ty, boost::is_class<t_Ty>::value>
{

};


template<typename t_Ty>
struct has_initializer_member_functions_cascade;

namespace detail
{
    template<typename t_Ty, int t_base_class_count>
    struct has_initializer_member_functions_cascade_helper
    {
        const static bool value =
            has_initializer_member_functions_cascade_helper<t_Ty, t_base_class_count-1>::value
            OR has_initializer_member_functions_cascade<o_NESTED_TYPE base_class_of<t_Ty, t_base_class_count-1>::type>::value
            ;
    };
    template<typename t_Ty>
    struct has_initializer_member_functions_cascade_helper<t_Ty,0>
    {
        const static bool value = has_initializer_member_functions<t_Ty>::value;
    };
}

template<typename t_Ty>
struct has_initializer_member_functions_cascade
    : public detail::has_initializer_member_functions_cascade_helper<t_Ty, base_class_count_of<t_Ty>::value>
{
};

template<typename t_Ty>
struct is_reflected_class
{
    BOOST_STATIC_CONSTANT(bool, value = boost::is_class<t_Ty>::value
        AND has_reflection<t_Ty>::value
        AND !is_signal_t<t_Ty>::value);
};
template<typename t_Ty>
struct has_deferred_cpp_reflection
{
    const static bool value = false;
};

#if o_HAS_VARIADIC_TEMPLATE

template < typename t_Ty > 
struct is_template : std::false_type {} ;

template < template <typename...> class t_Ty, typename... t_Params >
struct is_template< t_Ty<t_Params...> > : std::true_type {} ;

#else

template<typename t_Ty>
struct is_template
{
    const static bool value = false;
};

#endif

template<typename t_Ty, int index>
struct base_class_of : public detail::base_class_of_helper<t_Ty,index>{};

template<typename t_Ty>
struct safe_alignment_of : public detail::safe_alignment_of_helper_<t_Ty, boost::is_abstract<t_Ty>::value, boost::is_class<t_Ty>::value> {};

template<typename t_Ty>
struct safe_size_of : public detail::safe_size_of_helper_<t_Ty, boost::is_void<t_Ty>::value> {};

template<typename t_Ty>
struct has_virtual_destructor_cascade : public detail::has_virtual_destructor_cascade_helper_<t_Ty, base_class_count_of<t_Ty>::value>{};

template<typename t_Ty>
struct base_class_count_of : public detail::base_class_count_of_helper<t_Ty>{ };

template<typename t_Ty, size_t t_baseclasscount>
struct has_polymorphic_base_class_helper
{
    static const bool value = boost::is_polymorphic<o_NESTED_TYPE base_class_of<t_Ty, t_baseclasscount-1>::type>::value
        OR has_polymorphic_base_class_helper<t_Ty, t_baseclasscount-1>::value;
};

template<typename t_Ty>
struct has_polymorphic_base_class_helper<t_Ty, 0>
{
    static const bool value = false;
};

template<typename t_Ty>
struct has_polymorphic_base_class : public has_polymorphic_base_class_helper<t_Ty, base_class_count_of<t_Ty>::value>
{

};

template<typename t_Ty, size_t t_index>
struct base_class_offset_of_helper_size_before
{
    static const size_t value = sizeof(base_class_of<t_Ty, t_index-1>::type)
        + base_class_offset_of_helper_size_before<t_Ty, t_index-1>::value;
};

template<typename t_Ty>
struct base_class_offset_of_helper_size_before<t_Ty, 0>
{
    static const size_t value = sizeof(void*)*has_new_vtable<t_Ty>::value;
};

template<typename t_Ty, typename t_Sy>
struct base_class_offset_of
{
    static const size_t value = base_class_offset_of_helper_size_before<t_Ty, base_class_index_of<t_Ty, t_Sy>::value>::value;
};

template<typename t_Ty, int t_index>
struct has_base_class
{
    static const bool value = !boost::is_same<o_NESTED_TYPE base_class_of<t_Ty, t_index>::type, void>::value;
};

template<typename t_Ty>
struct has_new_vtable
{
    static const bool value = boost::is_polymorphic<t_Ty>::value AND !boost::is_polymorphic<o_NESTED_TYPE base_class_of<t_Ty, 0>::type>::value;
};

template<typename t_Ty, typename t_Base>
struct base_class_index_of  : public detail::base_class_index_of_helper<t_Ty,t_Base>{};

template<typename t_Ty>
struct has_reflection_cascade : public detail::has_reflection_cascade_helper_<t_Ty, base_class_count_of<t_Ty>::value> {};

template<typename t_Ty, typename t_STy = t_Ty>
struct base_statechart : public detail::base_statechart_helper<t_Ty,t_STy> {};

template<typename t_Ty>
struct base_total_track_count_of : detail::base_total_track_count_of_helper<t_Ty> {};

template<typename t_BaseTy, typename t_Ty>
struct statechart : public detail::statechart_helper<t_BaseTy, t_Ty, has_statechart<t_BaseTy>::value> {};

template<typename t_Ty>
struct track_count_of : public detail::track_count_of_helper<t_Ty, has_statechart<t_Ty>::value> {};

template<typename t_Ty>
struct track_count_cascade_of
{
    enum { value = track_count_of<t_Ty>::value + base_total_track_count_of<t_Ty>::value };
};

template<typename t_Ty, bool no_copy_meta_specifier_defined>
struct has_copy_disabled_helper
{
    static const bool value = true;
};
template<typename t_Ty>
struct has_copy_disabled_helper <t_Ty, false>
{
    static const bool value = (boost::is_void<t_Ty>::value)
        OR (boost::is_class<t_Ty>::value AND NOT(boost::is_copy_constructible<t_Ty>::value));
};

template<typename t_Ty>
struct has_copy_disabled : public has_copy_disabled_helper<t_Ty, (phantom::meta_specifiers<t_Ty>::value & o_no_copy) == o_no_copy>
{
};

template<typename t_Ty>
struct has_copy_disabled_cascade : public detail::has_copy_disabled_cascade_helper_<t_Ty, base_class_count_of<t_Ty>::value> {};

template<typename t_Ty>
struct is_serializable : public is_default_constructible_and_not_abstract<t_Ty> {};

template<typename t_Ty>
struct is_data_pointer : public detail::false_ {};

template<typename t_Ty>
struct is_structure : public detail::false_ {};

template<typename t_Ty>
struct is_data_pointer <t_Ty*> : public detail::true_ {};

template<typename t_Ty>
struct is_data_pointer <t_Ty const*> : public detail::true_ {};

template<typename t_Ty>
struct is_data_pointer <t_Ty* const> : public detail::true_ {};

template<typename t_Ty>
struct is_data_pointer <t_Ty const* const> : public detail::true_ {};

template<typename t_Ty>
struct is_default_constructible_and_not_abstract
    : public detail::is_default_constructible_and_not_abstract_helper<t_Ty, boost::is_abstract<t_Ty>::value> {};


/// has_xxx

template<typename t_Ty>
struct has_has_something : public detail::true_ {};

template<>
struct has_has_something<std::nullptr_t> : public detail::false_ {};

#define o_disable_has_something(...) namespace phantom { template<> struct has_has_something<__VA_ARGS__> : public detail::false_ {}; }

o_namespace_begin(detail)

template<typename t_Ty, bool has_has_something>
struct has_bit_and_helper : public boost::has_bit_and<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_bit_and_assign_helper : public boost::has_bit_and_assign<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_bit_or_helper : public boost::has_bit_or<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_bit_or_assign_helper : public boost::has_bit_or_assign<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_bit_xor_helper : public boost::has_bit_xor<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_bit_xor_assign_helper : public boost::has_bit_xor_assign<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_complement_helper : public boost::has_complement<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_dereference_helper : public boost::has_dereference<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_divides_helper : public boost::has_divides<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_divides_assign_helper : public boost::has_divides_assign<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_equal_to_helper : public boost::has_equal_to<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_greater_helper : public boost::has_greater<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_greater_equal_helper : public boost::has_greater_equal<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_left_shift_helper : public boost::has_left_shift<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_left_shift_assign_helper : public boost::has_left_shift_assign<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_less_helper : public boost::has_less<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_less_equal_helper : public boost::has_less_equal<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_logical_and_helper : public boost::has_logical_and<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_logical_not_helper : public boost::has_logical_not<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_logical_or_helper : public boost::has_logical_or<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_minus_helper : public boost::has_minus<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_minus_assign_helper : public boost::has_minus_assign<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_modulus_helper : public boost::has_modulus<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_modulus_assign_helper : public boost::has_modulus_assign<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_multiplies_helper : public boost::has_multiplies<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_multiplies_assign_helper : public boost::has_multiplies_assign<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_negate_helper : public boost::has_negate<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_new_operator_helper : public boost::has_new_operator<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_not_equal_to_helper : public boost::has_not_equal_to<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_nothrow_assign_helper : public boost::has_nothrow_assign<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_nothrow_constructor_helper : public boost::has_nothrow_constructor<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_nothrow_copy_helper : public boost::has_nothrow_copy<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_nothrow_copy_constructor_helper : public boost::has_nothrow_copy_constructor<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_nothrow_default_constructor_helper : public boost::has_nothrow_default_constructor<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_plus_helper : public boost::has_plus<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_plus_assign_helper : public boost::has_plus_assign<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_post_decrement_helper : public boost::has_post_decrement<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_post_increment_helper : public boost::has_post_increment<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_pre_decrement_helper : public boost::has_pre_decrement<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_pre_increment_helper : public boost::has_pre_increment<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_right_shift_helper : public boost::has_right_shift<t_Ty> {};
template<typename t_Ty, bool has_has_something>
struct has_right_shift_assign_helper : public boost::has_right_shift_assign<t_Ty> {};


template<typename t_Ty>
struct has_bit_and_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_bit_and_assign_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_bit_or_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_bit_or_assign_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_bit_xor_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_bit_xor_assign_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_complement_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_dereference_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_divides_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_divides_assign_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_equal_to_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_greater_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_greater_equal_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_left_shift_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_left_shift_assign_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_less_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_less_equal_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_logical_and_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_logical_not_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_logical_or_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_minus_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_minus_assign_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_modulus_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_modulus_assign_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_multiplies_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_multiplies_assign_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_negate_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_new_operator_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_not_equal_to_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_nothrow_assign_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_nothrow_constructor_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_nothrow_copy_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_nothrow_copy_constructor_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_nothrow_default_constructor_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_plus_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_plus_assign_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_post_decrement_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_post_increment_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_pre_decrement_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_pre_increment_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_right_shift_helper<t_Ty, false> : public false_ {};
template<typename t_Ty>
struct has_right_shift_assign_helper<t_Ty, false> : public false_ {};

o_namespace_end(detail)

template<typename t_Ty>
struct setup_steps_mask_of
{
    enum { value = (o_global_value_SetupStepBit_Reflection * has_reflection<t_Ty>::value)
        | (o_global_value_SetupStepBit_StateChart * has_statechart<t_Ty>::value )
        | (o_global_value_SetupStepBit_TemplateSignature * is_template<t_Ty>::value )
        | (o_global_value_SetupStepBit_VTable * has_new_vtable<t_Ty>::value)
        | (o_global_value_SetupStepBit_Inheritance * (base_class_count_of<t_Ty>::value != 0))
    };
};


template<typename t_Ty>
struct has_bit_and : public detail::has_bit_and_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_bit_and_assign : public detail::has_bit_and_assign_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_bit_or : public detail::has_bit_or_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_bit_or_assign : public detail::has_bit_or_assign_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_bit_xor : public detail::has_bit_xor_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_bit_xor_assign : public detail::has_bit_xor_assign_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_complement : public detail::has_complement_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_dereference : public detail::has_dereference_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_divides : public detail::has_divides_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_divides_assign : public detail::has_divides_assign_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_equal_to : public detail::has_equal_to_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_greater : public detail::has_greater_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_greater_equal : public detail::has_greater_equal_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_left_shift : public detail::has_left_shift_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_left_shift_assign : public detail::has_left_shift_assign_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_less : public detail::has_less_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_less_equal : public detail::has_less_equal_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_logical_and : public detail::has_logical_and_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_logical_not : public detail::has_logical_not_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_logical_or : public detail::has_logical_or_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_minus : public detail::has_minus_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_minus_assign : public detail::has_minus_assign_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_modulus : public detail::has_modulus_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_modulus_assign : public detail::has_modulus_assign_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_multiplies : public detail::has_multiplies_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_multiplies_assign : public detail::has_multiplies_assign_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_negate : public detail::has_negate_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_new_operator : public detail::has_new_operator_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_not_equal_to : public detail::has_not_equal_to_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_nothrow_assign : public detail::has_nothrow_assign_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_nothrow_constructor : public detail::has_nothrow_constructor_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_nothrow_copy : public detail::has_nothrow_copy_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_nothrow_copy_constructor : public detail::has_nothrow_copy_constructor_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_nothrow_default_constructor : public detail::has_nothrow_default_constructor_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_plus : public detail::has_plus_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_plus_assign : public detail::has_plus_assign_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_post_decrement : public detail::has_post_decrement_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_post_increment : public detail::has_post_increment_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_pre_decrement : public detail::has_pre_decrement_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_pre_increment : public detail::has_pre_increment_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_right_shift : public detail::has_right_shift_helper<t_Ty, has_has_something<t_Ty>::value> {};
template<typename t_Ty>
struct has_right_shift_assign : public detail::has_right_shift_assign_helper<t_Ty, has_has_something<t_Ty>::value> {};


namespace detail
{
    template<typename t_Ty, bool t_no_copy>
    struct is_copyable_helper
    {
        static const bool value = false;
    };

    template<typename t_Ty>
    struct is_copyable_helper<t_Ty, false>
    {
        static const bool value = boost::is_copy_constructible<t_Ty>::value
            AND NOT(has_statechart_cascade<t_Ty>::value) AND NOT(boost::is_abstract<t_Ty>::value);
    };
}

template<typename t_Ty>
struct is_copyable : public detail::is_copyable_helper<t_Ty, has_copy_disabled_cascade<t_Ty>::value>
{

};

o_namespace_end(phantom)

#if o_HAS_BUILT_IN_WCHAR_T

#define o_traits_specialize_primitive_if_wchar_t(_trait_, _name_, _value_) \
    o_traits_specialize_primitive(_trait_, _name_, _value_)

#else

#define o_traits_specialize_primitive_if_wchar_t(_trait_, _name_, _value_)

#endif

# define o_traits_specialize_for_primitives(_trait_, _value_) \
    o_traits_specialize_primitive(_trait_,char,_value_)\
    o_traits_specialize_primitive(_trait_,uchar,_value_)\
    o_traits_specialize_primitive(_trait_,schar,_value_)\
    o_traits_specialize_primitive_if_wchar_t(_trait_,wchar_t, _value_)\
    o_traits_specialize_primitive(_trait_,short, _value_)\
    o_traits_specialize_primitive(_trait_,ushort, _value_)\
    o_traits_specialize_primitive(_trait_,int, _value_)\
    o_traits_specialize_primitive(_trait_,uint, _value_)\
    o_traits_specialize_primitive(_trait_,long, _value_)\
    o_traits_specialize_primitive(_trait_,ulong, _value_)\
    o_traits_specialize_primitive(_trait_,longlong, _value_)\
    o_traits_specialize_primitive(_trait_,ulonglong, _value_)\
    o_traits_specialize_primitive(_trait_,float, _value_)\
    o_traits_specialize_primitive(_trait_,double, _value_)\
    o_traits_specialize_primitive(_trait_,longdouble, _value_)\
    o_traits_specialize_primitive(_trait_,bool, _value_)\
    o_traits_specialize_primitive(_trait_,void, _value_)\


o_traits_specialize_for_primitives(has_reflection, (const static bool value = true))

#endif // traits_h__
