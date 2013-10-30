#ifndef o_phantom_container_h__
#define o_phantom_container_h__

// use the spirit helpers for now
//#include <boost/spirit/home/support/container.hpp>

o_namespace_begin(phantom)

///////////////////////////////////////////////////////////////////////////
// Taken from boost::spirit
/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2001-2011 Hartmut Kaiser
    Copyright (c)      2010 Bryce Lelbach

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
================================================_==============================*/
///////////////////////////////////////////////////////////////////////////
template<typename t_Ty>
struct is_container
{
    const static bool value = detail::has_value_type<t_Ty>::value AND
        detail::has_iterator<t_Ty>::value AND
        detail::has_size_type<t_Ty>::value AND
        detail::has_reference<t_Ty>::value;
};

template<typename t_Ty, bool t_has_key_type>
struct is_set_container_helper 
    : public boost::is_same<o_NESTED_TYPE t_Ty::key_type, o_NESTED_TYPE t_Ty::value_type>
{
};

template<typename t_Ty>
struct is_set_container_helper<t_Ty, false>
{
    enum {value = false};
};

template<typename t_Ty>
struct is_set_container 
    : public is_set_container_helper<t_Ty, is_container<t_Ty>::value AND detail::has_key_type<t_Ty>::value>
{
};

template<typename t_Ty>
struct is_map_container
{
    const static bool value = is_container<t_Ty>::value 
        AND detail::has_key_type<t_Ty>::value
        AND detail::has_mapped_type<t_Ty>::value
        AND NOT(is_set_container<t_Ty>::value);
};

template<typename t_Ty>
struct is_sequential_container
{
    const static bool value = is_container<t_Ty>::value 
        AND NOT(detail::has_key_type<t_Ty>::value);
};


template <typename T>
struct is_string : boost::mpl::false_ {};

template <typename T>
struct is_string<T const> : is_string<T> {};

template <>
struct is_string<char const*> : boost::mpl::true_ {};

template <>
struct is_string<wchar_t const*> : boost::mpl::true_ {};

template <>
struct is_string<char*> : boost::mpl::true_ {};

template <>
struct is_string<wchar_t*> : boost::mpl::true_ {};

template <std::size_t N>
struct is_string<char[N]> : boost::mpl::true_ {};

template <std::size_t N>
struct is_string<wchar_t[N]> : boost::mpl::true_ {};

template <std::size_t N>
struct is_string<char const[N]> : boost::mpl::true_ {};

template <std::size_t N>
struct is_string<wchar_t const[N]> : boost::mpl::true_ {};

template <std::size_t N>
struct is_string<char(&)[N]> : boost::mpl::true_ {};

template <std::size_t N>
struct is_string<wchar_t(&)[N]> : boost::mpl::true_ {};

template <std::size_t N>
struct is_string<char const(&)[N]> : boost::mpl::true_ {};

template <std::size_t N>
struct is_string<wchar_t const(&)[N]> : boost::mpl::true_ {};

template <typename T, typename Traits, typename Allocator>
struct is_string<std::basic_string<T, Traits, Allocator> > : boost::mpl::true_ {};

template<typename t_Ty>
struct is_basic_string : boost::mpl::false_ {};

template <typename T, typename Traits, typename Allocator>
struct is_basic_string<std::basic_string<T, Traits, Allocator> > : boost::mpl::true_ {};

template<typename t_Ty>
struct is_basic_string_char : boost::mpl::false_ {};

template <typename Traits, typename Allocator>
struct is_basic_string_char<std::basic_string<char, Traits, Allocator> > : boost::mpl::true_ {};

template<typename t_Ty>
struct is_basic_string_wchar_t : boost::mpl::false_ {};

template <typename Traits, typename Allocator>
struct is_basic_string_wchar_t<std::basic_string<wchar_t, Traits, Allocator> > : boost::mpl::true_ {};

o_namespace_end(phantom)

o_namespace_begin(phantom, container)


#define o_define_trait_is_std_container(_container_)                                                    \
    \
    template<typename t_Ty>                                                                                 \
struct is_##_container_;                                                                                \
    \
    template<typename t_Ty>                                                                                 \
struct is_std_##_container_                                                                             \
{                                                                                                       \
    enum { value = false };                                                                             \
};                                                                                                      \
    \
    template<typename t_Ty, int t_super_class_count_of>                                                     \
struct is_##_container_##_helper                                                                        \
{                                                                                                       \
    enum { value = is_std_##_container_<t_Ty>::value                                                    \
    OR is_##_container_<typename super_class_of<t_Ty, t_super_class_count_of-1>::type>::value       \
    OR is_##_container_##_helper<t_Ty, t_super_class_count_of-1>::value };                          \
};                                                                                                      \
    \
    template<typename t_Ty>                                                                                 \
struct is_##_container_##_helper<t_Ty, 0>                                                               \
{                                                                                                       \
    enum { value = is_std_##_container_<t_Ty>::value };                                                                             \
};                                                                                                      \
    \
    template<typename t_Ty>                                                                                 \
struct is_##_container_ : public is_##_container_##_helper<t_Ty, super_class_count_of<t_Ty>::value>     \
{                                                                                                       \
};                           
                                                                           \

o_define_trait_is_std_container(queue)
template<class T
, class Container
>
struct is_std_queue<std::queue<T,Container>>
{
     enum { value = true };
};


o_define_trait_is_std_container(unordered_map)
template<class Key,
class T,
class Hash,
class KeyEqual,
class Allocator >
struct is_std_unordered_map<std::unordered_map<Key,T,Hash,KeyEqual,Allocator>>
{
    enum { value = true };
};

o_define_trait_is_std_container(map)
    template<class Key,
class T,
class KeyEqual,
class Allocator >
struct is_std_map<std::map<Key,T,KeyEqual,Allocator>>
{
    enum { value = true };
};

o_define_trait_is_std_container(unordered_multimap)
    template<class Key,
class T,
class Hash,
class KeyEqual,
class Allocator >
struct is_std_unordered_multimap<std::unordered_multimap<Key,T,Hash,KeyEqual,Allocator>>
{
    enum { value = true };
};

o_define_trait_is_std_container(multimap)
    template<class Key,
class T,
class KeyEqual,
class Allocator >
struct is_std_multimap<std::multimap<Key,T,KeyEqual,Allocator>>
{
    enum { value = true };
};

o_define_trait_is_std_container(set)
    template < 
        class Key, 
        class Compare,
        class Allocator >
struct is_std_set<std::set<Key,Compare,Allocator>>
{
    enum { value = true };
};

o_define_trait_is_std_container(unordered_set)
    template < class Key,                                    // unordered_set::key_type/value_type
class Hash ,                       // unordered_set::hasher
class Pred ,                   // unordered_set::key_equal
class Alloc   // unordered_set::allocator_type
    > 
struct is_std_unordered_set<std::unordered_set<Key, Hash, Pred, Alloc>>
{
    enum { value = true };
};

o_define_trait_is_std_container(multiset)
    template < 
        class Key, 
        class Compare,
        class Allocator >
struct is_std_multiset<std::multiset<Key,Compare,Allocator>>
{
    enum { value = true };
};

o_define_trait_is_std_container(unordered_multiset)
    template < class Key,                                    // unordered_set::key_type/value_type
class Hash ,                       // unordered_set::hasher
class Pred ,                   // unordered_set::key_equal
class Alloc   // unordered_set::allocator_type
    > 
struct is_std_unordered_multiset<std::unordered_multiset<Key, Hash, Pred, Alloc>>
{
    enum { value = true };
};

o_define_trait_is_std_container(vector)
    template < class T,
class Alloc
    > 
struct is_std_vector<std::vector<T, Alloc>>
{
    enum { value = true };
};

o_define_trait_is_std_container(list)
    template < class T,
class Alloc
    > 
struct is_std_list<std::list<T, Alloc>>
{
    enum { value = true };
};

o_define_trait_is_std_container(stack)
    template<class T,
class Container>
struct is_std_stack<std::stack<T,Container>>
{
    enum { value = true };
};

o_define_trait_is_std_container(deque)
    template<class T,
class Alloc>
struct is_std_deque<std::deque<T,Alloc>>
{
    enum { value = true };
};

template<typename t_Ty>
struct has_reserve_member_function;

namespace detail {

template<typename t_Ty>
struct has_reserve_member_function_
{
    const static bool value = false;
};

template<typename t_Ty, bool t_has_reserve>
struct reserver_helper
{
    o_forceinline static void apply(t_Ty* a_pContainer, o_NESTED_TYPE t_Ty::size_type a_uiSize)
    {

    }
};

template<typename t_Ty>
struct reserver_helper<t_Ty, true>
{
    inline static void apply(t_Ty* a_pContainer, o_NESTED_TYPE t_Ty::size_type a_uiSize)
    {
        a_pContainer->reserve(a_uiSize);
    }
};

template<typename t_Ty>
struct reserver_ :public reserver_helper<t_Ty,
    phantom::is_container<t_Ty>::value
    AND has_reserve_member_function<t_Ty>::value>
{
    o_forceinline static void apply(t_Ty* a_pContainer, o_NESTED_TYPE t_Ty::size_type a_uiSize)
    {

    }
};


template<typename t_Ty, typename t_Alloc>
struct has_reserve_member_function_<std::vector<t_Ty, t_Alloc> >
{
    static const bool value = true;
};

template<typename t_Ty>
struct has_reserve_member_function_<phantom::vector<t_Ty> >
{
    static const bool value = true;
};

enum container_add_member_function
{
    e_add_by_push_back,
    e_add_by_push,
    e_add_by_insert,
};

template<typename t_Ty, container_add_member_function t_add_member_function>
struct adder_helper_;

template<typename t_Ty>
struct adder_helper_<t_Ty, e_add_by_insert>
{
    o_forceinline static void apply(t_Ty* a_pContainer, const o_NESTED_TYPE t_Ty::value_type& a_Value)
    {
        a_pContainer->insert(a_Value);
    }
};

template<typename t_Ty>
struct adder_helper_<t_Ty, e_add_by_push_back>
{
    o_forceinline static void apply(t_Ty* a_pContainer, const o_NESTED_TYPE t_Ty::value_type& a_Value)
    {
        a_pContainer->push_back(a_Value);
    }
};

template<typename t_Ty>
struct adder_helper_<t_Ty, e_add_by_push>
{
    o_forceinline static void apply(t_Ty* a_pContainer, const o_NESTED_TYPE t_Ty::value_type& a_Value)
    {
        a_pContainer->push(a_Value);
    }
};

template<typename t_Ty>
struct adder_ : public adder_helper_<t_Ty, 
    (is_vector<t_Ty>::value 
    OR is_list<t_Ty>::value
    OR is_deque<t_Ty>::value
    OR is_basic_string<t_Ty>::value) 
    ? e_add_by_push_back
    : (is_stack<t_Ty>::value 
    OR is_queue<t_Ty>::value)
    ? e_add_by_push
    : e_add_by_insert
    > 
{
};

}

template<typename t_Ty>
struct reserver : public detail::reserver_<t_Ty> {};

template<typename t_Ty>
struct adder : public detail::adder_<t_Ty> {};

template<typename t_Ty>
struct has_reserve_member_function : public detail::has_reserve_member_function_<t_Ty> {};

template<typename T>
struct str_len
{
    static std::size_t apply(const T* a_str)
    {
        return 0;
    }
};

template<>
struct str_len<char>
{
    static std::size_t apply(const char* a_str)
    {
        return strlen(a_str);
    }
};

template<>
struct str_len<wchar_t>
{
    static std::size_t apply(const wchar_t* a_str)
    {
        return wcslen(a_str);
    }
};




template <typename T>
struct char_type_of_string
{
    typedef o_NESTED_TYPE boost::remove_const<
        o_NESTED_TYPE boost::remove_pointer<
        o_NESTED_TYPE boost::remove_all_extents<T>::type
        >::type>::type type;
};

template <typename T, typename Traits, typename Allocator>
struct char_type_of_string<std::basic_string<T, Traits, Allocator> >
{
    typedef T type;
};

template<typename T>
struct string_size
{
    static std::size_t apply(const T& a_str)
    {
        return str_len<typename char_type_of_string<T>::type>::apply(a_str);
    }
};

template <typename T, typename Traits, typename Allocator>
struct string_size<std::basic_string<T, Traits, Allocator> >
{
    static std::size_t apply(const T& a_str)
    {
        return a_str.size();
    }
};

template<typename T>
struct string_c_str
{
    typedef o_NESTED_TYPE char_type_of_string<T>::type char_t;
    static const char_t* apply(const T& a_str)
    {
        return a_str;
    }
};

template <typename T, typename Traits, typename Allocator>
struct string_c_str<std::basic_string<T, Traits, Allocator> >
{
    typedef o_NESTED_TYPE char_type_of_string<T>::type char_t;
    static const char_t* apply(const T& a_str)
    {
        return a_str.c_str();
    }
};



template<typename T>
struct str_byte_count
{
    typedef o_NESTED_TYPE boost::remove_const<
        o_NESTED_TYPE boost::remove_pointer<T>::type
    >::type ch;
    static std::size_t apply(const T& a_str)
    {
        return std::basic_string<ch, std::char_traits<ch>, phantom::string::allocator_type>(a_str).size()
            *sizeof(ch);
    }
};

template <typename T, typename Traits, typename Allocator>
struct str_byte_count<std::basic_string<T, Traits, Allocator> >
{
    static std::size_t apply(const T& a_str)
    {
        return a_str.size()*sizeof(T);
    }
};

template<typename t_Ty, typename t_ValueType>
struct variable_value_type_helper
{
    typedef t_ValueType type;
};

// Map helper specialization
template<typename t_Ty, typename t_Key, typename t_Value>
struct variable_value_type_helper<t_Ty, std::pair<const t_Key, t_Value>>
{
    typedef t_Value type;
};

template<typename t_Ty>
struct variable_value_type : public variable_value_type_helper<t_Ty, typename t_Ty::value_type>
{
};

template<typename t_ContainerTy>
void move_unique(t_ContainerTy& c, typename t_ContainerTy::value_type v, size_t index)
{
    o_assert(index< c.size());
    auto it = std::find(c.begin(), c.end(), v);
    auto to = c.begin();
    std::advance(to, index);
    if(it == to) return;
    if(it < to)
    {
        std::rotate(it, it+1, to+1);
    }
    else
    {
        auto rit = std::find(c.rbegin(),
            c.rend(), v);
        auto rto = c.rbegin() + c.size()-index;
        std::rotate(rit, rit+1, rto);
    }
}

o_namespace_end(phantom, container)


#endif // o_phantom_container_h__
