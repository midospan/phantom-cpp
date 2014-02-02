
// Copier

template<typename t_Ty>
struct default_copier;

enum default_copier_id
{
    default_copier_default,
    default_copier_forbidden,
};

template<typename t_Ty, default_copier_id t_id>
struct default_copier_helper;

template<typename t_Ty>
struct default_copier_helper <t_Ty, default_copier_default>
{
    static void copy(t_Ty* a_pDest, t_Ty const* a_pSrc)
    {
        *a_pDest = *a_pSrc;
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

template<typename t_Ty>
struct default_copier : public default_copier_helper<t_Ty,
    has_copy_disabled_cascade<t_Ty>::value
    ? detail::default_copier_forbidden
    : detail::default_copier_default
>
{
    o_rebind(default_copier)
};

template<typename t_Ty>
struct copier_ : public default_copier<t_Ty>
{
};