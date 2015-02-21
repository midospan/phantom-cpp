/* TODO LICENCE HERE */

#ifndef o_def_copier_h__
#define o_def_copier_h__

o_namespace_begin(phantom)


// Copier

template<typename t_Ty>
struct default_copier;

enum default_copier_id
{
    default_copier_default,
    default_copier_forbidden,
};

namespace detail
{
    template<typename t_Ty, int t_id>
    struct default_copier_helper;

    template<typename t_Ty, bool t_Success>
    struct default_copier_helper_decltype_check
    {
        typedef o_NESTED_TYPE boost::remove_const<t_Ty>::type t_Ty_no_const;
        static void copy(t_Ty* a_pDest, t_Ty const* a_pSrc)
        {
            //o_static_assert(!(boost::is_same<t_Ty, t_Ty>::value));
            *((t_Ty_no_const*)a_pDest) = *((t_Ty_no_const const*)a_pSrc);
        }
    };

    template<typename t_Ty>
    struct default_copier_helper_decltype_check<t_Ty, false>
    {
        static void copy(t_Ty* a_pDest, t_Ty const* a_pSrc)
        {
            o_exception(exception::unsupported_member_function_exception, "copy forbidden for the given type, remove an eventual 'o_no_copy' meta specifier to enable this member_function for your class");
        }
    };

    template<typename t_Ty>
    struct default_copier_helper <t_Ty, default_copier_default>
    {
        typedef o_NESTED_TYPE boost::remove_const<t_Ty>::type t_Ty_no_const;

        //     static t_Ty_no_const& a0();
        //     static t_Ty_no_const a1();

        //o_static_assert((boost::is_same<decltype(a0() = a1()), t_Ty_no_const&>::value));
        //     typedef int true_type;
        //     typedef char false_type;
        // 
        //     static true_type __test(t_Ty_no_const& a, t_Ty_no_const b = (a0() = a1()));
        // 
        //     static false_type __test(...);

        static void copy(t_Ty* a_pDest, t_Ty const* a_pSrc)
        {
            *((t_Ty_no_const*)a_pDest) = *((t_Ty_no_const const*)a_pSrc);
            //default_copier_helper_decltype_check<t_Ty, sizeof(__test(*((t_Ty_no_const*)a_pDest))) == sizeof(int)>::copy(a_pDest, a_pSrc);
        }
    };

    template<typename t_Ty>
    struct default_copier_helper <t_Ty, default_copier_forbidden>
    {
        static void copy(t_Ty* a_pDest, t_Ty const* a_pSrc)
        {
            o_exception(exception::unsupported_member_function_exception, "copy forbidden for the given type, remove an eventual 'o_no_copy' meta specifier to enable this member_function for your class");
        }
    };
}

template<typename t_Ty>
struct default_copier : public detail::default_copier_helper<t_Ty,
    (NOT(is_copyable<t_Ty>::value)/* OR NOT(std::is_default_constructible<t_Ty>::value)*/)
    ? default_copier_forbidden
    : default_copier_default
>
{
    o_rebind(default_copier)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct copier
///
/// \brief  copier.
/// 		Provides copy of type instances
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct copier : public default_copier<t_Ty>
{
};

o_namespace_end(phantom)

#endif // o_def_copier_h__