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

#ifndef o_phantom_typedefs_h__
#define o_phantom_typedefs_h__

#include <phantom/def_export.h>


o_namespace_begin(phantom)

    enum { max_type_size = 1024 };

#if (o_COMPILER == o_COMPILER_GCC) || (o_COMPILER == o_COMPILER_CLANG)
typedef int8_t           int8;
typedef int16_t          int16;
typedef int32_t          int32;
typedef int64_t          int64;
typedef uint8_t          uint8;
typedef uint16_t         uint16;
typedef uint32_t         uint32;
typedef uint64_t         uint64;
typedef int8_t           sint8;
typedef int16_t          sint16;
typedef int32_t          sint32;
typedef int64_t          sint64;

#elif (o_COMPILER == o_COMPILER_VISUAL_STUDIO)
typedef __int8           int8;
typedef __int16          int16;
typedef __int32          int32;
typedef __int64          int64;
typedef unsigned __int8  uint8;
typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;
typedef signed __int8    sint8;
typedef signed __int16   sint16;
typedef signed __int32   sint32;
typedef signed __int64   sint64;

#else
#   error Int types must be defined for this compiler
#endif

typedef long long                      longlong;

typedef unsigned char              uchar;
typedef unsigned short          ushort;
typedef unsigned int              uint;
typedef unsigned long              ulong;
typedef unsigned long long    ulonglong;

typedef signed char                  schar;
typedef signed short              sshort;
typedef signed int                  sint;
typedef signed long                  slong;
typedef signed long long      slonglong;

#if defined(_M_IA64) || defined(_M_X64) || defined(_M_AMD64)
typedef __int128                    int128;
typedef unsigned __int128        uint128;
typedef signed  __int128        sint128;
#else

#endif

#if defined(_UNICODE)
typedef wchar_t                    character;
#else
typedef char                    character;

#endif


typedef long double             longdouble;

typedef bool                    boolean;
typedef size_t                  guid;
typedef size_t                  handle;
typedef void*                   voidptr;
typedef unsigned char           byte;

typedef float                   sreal;
typedef double                  dreal;

#if o__bool__use_double_precision_real == 1
typedef dreal                   real;
#else
typedef sreal                   real;
#endif

template<typename t_Ty>
struct make_float
{
    typedef float type;
};

template<>
struct make_float<double>
{
    typedef double type;
};

/**
 * \struct signal_t
 *
 * \brief Signal return type
 *        used to differenciate a classic member_function void return
 *        from a signal return type. Useful when passed as template argument to differentiate
 *        a member_function from a signal.
 *
 */

struct signal_t
{
public:
    o_forceinline signal_t(void) {}
    o_forceinline signal_t(const int& a_i) {}
};


#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
struct generic_member_func_ptr
{
    generic_member_func_ptr() 
        : pointer(NULL) {}

    void setClosurePointer(void* ptr)
    {
        pointer = ptr;
    }

    template<typename t_MemberPtr>
    generic_member_func_ptr(t_MemberPtr ptr)
    {
        o_static_assert_msg(boost::is_member_function_pointer<t_MemberPtr>::value, "must be a member function pointer");
        union
        {
            t_MemberPtr mptr;
            void* hacked;
        } un;
        un.mptr = ptr;
        pointer = un.hacked;
    }
    template<typename t_MemberPtr>
    generic_member_func_ptr& operator = (t_MemberPtr ptr)
    {
        o_static_assert_msg(boost::is_member_function_pointer<t_MemberPtr>::value, "must be a member function pointer");
        union
        {
            t_MemberPtr mptr;
            void* hacked;
        } un;
        un.mptr = ptr;
        pointer = un.hacked;
        return *this;
    }
    template<typename t_MemberPtr>
    operator t_MemberPtr() const
    {
        o_static_assert_msg(boost::is_member_function_pointer<t_MemberPtr>::value, "must be a member function pointer");
        union
        {
            t_MemberPtr mptr;
            void* hacked;
        } un;
        un.hacked = pointer;
        return un.mptr;
    }

    operator void*() const { return pointer; }

protected:
    void* pointer;
};

#else
#   error define generic_member_func_ptr for your compiler
#endif





typedef std::basic_string<
  character
  , std::char_traits<character>
  , o__t1_class__contiguous_memory_allocator(character) >    astring;

typedef std::basic_string<
  char
  , std::char_traits<char>
  , o__t1_class__contiguous_memory_allocator(char) >    string;

typedef std::basic_string<
  wchar_t
  , std::char_traits<wchar_t>
  , o__t1_class__contiguous_memory_allocator(wchar_t) >    wstring;

typedef std::basic_stringstream<character, std::char_traits<character>,
    o__t1_class__contiguous_memory_allocator(character) > astringstream;

typedef std::basic_stringstream<char, std::char_traits<char>,
    o__t1_class__contiguous_memory_allocator(char) > stringstream;

typedef std::basic_stringstream<wchar_t, std::char_traits<wchar_t>,
    o__t1_class__contiguous_memory_allocator(wchar_t) > wstringstream;

typedef std::basic_istringstream<character, std::char_traits<character>,
    o__t1_class__contiguous_memory_allocator(character) > aistringstream;

typedef std::basic_istringstream<char, std::char_traits<char>,
    o__t1_class__contiguous_memory_allocator(char) > istringstream;

typedef std::basic_istringstream<wchar_t, std::char_traits<wchar_t>,
    o__t1_class__contiguous_memory_allocator(wchar_t) > wistringstream;

typedef std::basic_ostringstream<character, std::char_traits<character>,
    o__t1_class__contiguous_memory_allocator(character) > aostringstream;

typedef std::basic_ostringstream<char, std::char_traits<char>,
    o__t1_class__contiguous_memory_allocator(char) > ostringstream;

typedef std::basic_ostringstream<wchar_t, std::char_traits<wchar_t>,
    o__t1_class__contiguous_memory_allocator(wchar_t) > wostringstream;


typedef std::basic_ostream<character, std::char_traits<character> > ostream;

typedef std::basic_ostream<char, std::char_traits<char> > aostream;

typedef std::basic_ostream<wchar_t, std::char_traits<wchar_t> > wostream;

typedef std::basic_istream<character, std::char_traits<character> > istream;

typedef std::basic_istream<char, std::char_traits<char> > aistream;

typedef std::basic_istream<wchar_t, std::char_traits<wchar_t> > wistream;


#include <phantom/def_export.h>

template<typename t_Ty>
class vector : public std::vector<t_Ty, o__t1_class__contiguous_memory_allocator(t_Ty)>    
{
public:
    typedef std::vector<t_Ty, o__t1_class__contiguous_memory_allocator(t_Ty)> _Mybase;
    typedef phantom::vector<t_Ty> _Myt;

    vector()
        : _Mybase()
    {	// construct empty vector
    }

    explicit vector(size_type _Count)
        : _Mybase(_Count)
    {	// construct from _Count * _Ty()
    }

    vector(size_type _Count, const t_Ty& _Val)
        : _Mybase(_Count, _Val)
    {	// construct from _Count * _Val
    }

    vector(const _Myt& _Right)
        : _Mybase(_Right)
    {	// construct by copying _Right
     
    }

    template<class _Iter>
    vector(_Iter _First, _Iter _Last)
        : _Mybase(_First, _Last)
    {	// construct from [_First, _Last)
    }

};

template<typename t_Ty>
class list : public std::list<t_Ty, o__t1_class__partioned_memory_allocator(t_Ty)> 
{
public:
    typedef std::list<t_Ty, o__t1_class__partioned_memory_allocator(t_Ty)> _Mybase;
    typedef o__t1_class__partioned_memory_allocator(t_Ty) allocator_type;
    typedef typename _Mybase::size_type size_type;
    typedef phantom::list<t_Ty> _Myt;
    list()        
        : _Mybase()
    {	
    }

    explicit list(const allocator_type& _Al)
        : _Mybase(_Al)
    {	
    }

    explicit list(size_type _Count)
        : _Mybase(_Count)
    {	
    }

    list(size_type _Count, const t_Ty& _Val)
        : _Mybase(_Count, _Val)
    {	
    }

    list(size_type _Count, const t_Ty& _Val, const allocator_type& _Al)
        : _Mybase(_Count, _Val, _Al)
    {	
    }

    list(const _Myt& _Right)
        : _Mybase(_Right)
    {	
    }

    template<class _Iter>
    list(_Iter _First, _Iter _Last)
        : _Mybase(_First, _Last)
    {	// construct list from [_First, _Last)
        
    }

    template<class _Iter>
    list(_Iter _First, _Iter _Last, const allocator_type& _Al)
        : _Mybase(_First, _Last, _Al)
    {	
    }

};

template<typename t_Ty>
class deque : public std::deque<t_Ty, o__t1_class__contiguous_memory_allocator(t_Ty)>
{
public:
    typedef o__t1_class__contiguous_memory_allocator(t_Ty) allocator_type;
    typedef std::deque<t_Ty, allocator_type> base_type;
    typedef typename std::deque<t_Ty, o__t1_class__contiguous_memory_allocator(t_Ty)>::size_type size_type;

    typedef deque<t_Ty> _Myt;

public:
    o_forceinline deque()
        : base_type()
    {	// construct empty deque
    }

    o_forceinline explicit deque(const allocator_type& a_Al)
        : base_type(a_Al)
    {	// construct empty deque with allocator
    }

    o_forceinline explicit deque(size_type a_Count)
        : base_type(a_Count)
    {	// construct from _Count * _Ty()
    }

    o_forceinline deque(size_type a_Count, const t_Ty& _Val)
        : base_type(a_Count, _Val)
    {	// construct from _Count * _Val
    }

    o_forceinline deque(size_type a_Count, const t_Ty& a_Val, const allocator_type& a_Al)
        : base_type(a_Count, a_Val, a_Al)
    {	// construct from _Count * _Val with allocator
    }

    o_forceinline deque(const _Myt& a_Right)
        : base_type(a_Right)
    {	// construct by copying _Right
    }

    template<class t_It>
    o_forceinline deque(t_It a_First, t_It a_Last)
        : base_type(a_First, a_Last)
    {	// construct from [_First, _Last)
    }

    template<class t_It>
    o_forceinline deque(t_It a_First, t_It a_Last, const allocator_type& a_Al)
        : base_type(a_First, a_Last, a_Al)
    {	// construct from [_First, _Last) with allocator
    }

};

template<typename _KeyTy, typename _ValueTy, typename _Pr = std::less<_KeyTy> >
class map : public std::map<_KeyTy
    , _ValueTy
    , _Pr
    , o__t1_class__partioned_memory_allocator(o_TT(std::pair, const _KeyTy, _ValueTy))>

{
public:
    typedef std::map<_KeyTy
        , _ValueTy
        , _Pr
        , o__t1_class__partioned_memory_allocator(o_TT(std::pair, const _KeyTy, _ValueTy))> _Mybase;

    map() : _Mybase() {}
    map(const _Myt& _Right)
        : _Mybase(_Right)
    {	// construct map by copying _Right
    }

    explicit map(const key_compare& _Pred)
        : _Mybase(_Pred)
    {	// construct empty map from comparator
    }

    map(const key_compare& _Pred, const allocator_type& _Al)
        : _Mybase(_Pred, _Al)
    {	// construct empty map from comparator and allocator
    }

    template<class _Iter>
    map(_Iter _First, _Iter _Last)
        : _Mybase(_First, _Last)
    {	// construct map from [_First, _Last), defaults
    }

    template<class _Iter>
    map(_Iter _First, _Iter _Last,
        const key_compare& _Pred)
        : _Mybase(_First, _Last, _Pred)
    {	// construct map from [_First, _Last), comparator
    }

    template<class _Iter>
    map(_Iter _First, _Iter _Last,
        const key_compare& _Pred, const allocator_type& _Al)
        : _Mybase(_First, _Last, _Pred, _Al)
    {	// construct map from [_First, _Last), comparator, and allocator
    }

    _Myt& operator=(const _Myt& _Right)
    {	// assign by copying _Right
        _Mybase::operator=(_Right);
        return (*this);
    }

    map(_Myt&& _Right)
        : _Mybase(_Right)
    {	// construct map by moving _Right
    }
};

template<class t_Kty,
class t_Ty,
#if o_HAS_CPP0X
class t_Hasher = std::hash<t_Kty>,
#else
class t_Hasher = std::tr1::hash<t_Kty>,
#endif
class t_Keyeq = std::equal_to<t_Kty>,
class t_Alloc = o__t1_class__partioned_memory_allocator(o_TT(std::pair, const t_Kty, t_Ty)) >
class unordered_map 

#if o_HAS_CPP0X
    : public std::unordered_map<t_Kty,t_Ty,t_Hasher,t_Keyeq,t_Alloc>
#else
    : public std::tr1::unordered_map<t_Kty,t_Ty,t_Hasher,t_Keyeq,t_Alloc>
#endif
{

};

template<typename _KeyTy, typename _ValueTy, typename _Pr = std::less<_KeyTy> >
class multimap : public std::multimap<_KeyTy
    , _ValueTy
    , _Pr
    , o__t1_class__partioned_memory_allocator(o_TT(std::pair, _KeyTy, _ValueTy))>
{};



/**
 * \brief Customized version of boost::property_tree::ptree (handles custom allocations)
 *
 */
typedef boost::property_tree_custom::basic_ptree<
    string
    , string
    , o__t1_class__partioned_memory_allocator(character)


    , o__t1_class__contiguous_memory_allocator(character)> property_tree;


/**
 * \brief Association of a path with a valueMember tree object
 *
 */
class property_branch
{
public:
    property_branch(void) : m_pTree(NULL) {}
    property_branch(const string& a_strTreePath, property_tree*    a_pTree) :
    m_strTreePath(a_strTreePath), m_pTree(a_pTree) {}

    inline void setValue(const string& a_strValue) const
    {
        m_pTree->put(m_strTreePath, a_strValue);
    }

    inline string getValue() const
    {
        return m_pTree->get<string>(m_strTreePath);
    }

    inline boost::optional<string> getOptionalValue() const
    {
        return m_pTree->get_optional<string>(m_strTreePath);
    }

    inline property_branch   subBranch(const string& a_strSubPath) const
    {
        return property_branch(m_strTreePath+'.'+a_strSubPath, m_pTree);
    }

protected:
    string            m_strTreePath;
    property_tree*    m_pTree;
};

template<typename _Type>
class o_export Delegates
{
public:
    typedef fastdelegate::FastDelegate<void(_Type&)>        Filler;
    typedef fastdelegate::FastDelegate<const _Type&()>        Getter;
    typedef fastdelegate::FastDelegate<void(const _Type&)>    Setter;
    typedef fastdelegate::FastDelegate<boolean(_Type)>            Selector;
};

namespace reflection { class Type; }

class argument
{
public:
    class list
    {
    public:

    };

    template<size_t t_size>
    class list_n : public list
    {
        byte data[t_size];
    };

    template<typename t_Param0>
    class list_1 : public list
    {
    public:
        list_1(void) {}
        list_1(const t_Param0& a_p0) : p0(a_p0) {}
        t_Param0 p0;
    };
    template<typename t_Param0, typename t_Param1>
    class list_2: public list
    {
    public:
        list_2(void) {}
        list_2(const t_Param0& a_p0, const t_Param1& a_p1) : p0(a_p0), p1(a_p1) {}
        t_Param0 p0;
        t_Param1 p1;
    };
    template<typename t_Param0, typename t_Param1, typename t_Param2>
    class list_3: public list
    {
    public:
        list_3(void) {}
        list_3(const t_Param0& a_p0, const t_Param1& a_p1, const t_Param2& a_p2)
            : p0(a_p0), p1(a_p1), p2(a_p2) {}
        t_Param0 p0;
        t_Param1 p1;
        t_Param2 p2;
    };
    template<typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
    class list_4: public list
    {
    public:
        list_4(void) {}
        list_4(const t_Param0& a_p0, const t_Param1& a_p1, const t_Param2& a_p2, const t_Param3& a_p3)
            : p0(a_p0), p1(a_p1), p2(a_p2), p3(a_p3) {}
        t_Param0 p0;
        t_Param1 p1;
        t_Param2 p2;
        t_Param3 p3;
    };
    template<typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
    class list_5: public list
    {
    public:
        list_5(void) {}
        list_5(const t_Param0& a_p0, const t_Param1& a_p1, const t_Param2& a_p2, const t_Param3& a_p3, const t_Param4& a_p4)
            : p0(a_p0), p1(a_p1), p2(a_p2), p3(a_p3), p4(a_p4) {}
        t_Param0 p0;
        t_Param1 p1;
        t_Param2 p2;
        t_Param3 p3;
        t_Param4 p4;
    };
    template<typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
    class list_6: public list
    {
    public:
        list_6(void) {}
        list_6(const t_Param0& a_p0, const t_Param1& a_p1, const t_Param2& a_p2, const t_Param3& a_p3, const t_Param4& a_p4, const t_Param5& a_p5)
            : p0(a_p0), p1(a_p1), p2(a_p2), p3(a_p3), p4(a_p4), p5(a_p5) {}
        t_Param0 p0;
        t_Param1 p1;
        t_Param2 p2;
        t_Param3 p3;
        t_Param4 p4;
        t_Param5 p5;
    };
    template<typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
    class list_7: public list
    {
    public:
        list_7(void) {}
        list_7(const t_Param0& a_p0, const t_Param1& a_p1, const t_Param2& a_p2, const t_Param3& a_p3, const t_Param4& a_p4, const t_Param5& a_p5, const t_Param6& a_p6)
            : p0(a_p0), p1(a_p1), p2(a_p2), p3(a_p3), p4(a_p4), p5(a_p5), p6(a_p6) {}
        t_Param0 p0;
        t_Param1 p1;
        t_Param2 p2;
        t_Param3 p3;
        t_Param4 p4;
        t_Param5 p5;
        t_Param6 p6;
    };
    template<typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
    class list_8: public list
    {
    public:
        list_8(void) {}
        list_8(const t_Param0& a_p0, const t_Param1& a_p1, const t_Param2& a_p2, const t_Param3& a_p3, const t_Param4& a_p4, const t_Param5& a_p5, const t_Param6& a_p6, const t_Param7& a_p7)
            : p0(a_p0), p1(a_p1), p2(a_p2), p3(a_p3), p4(a_p4), p5(a_p5), p6(a_p6), p7(a_p7) {}
        t_Param0 p0;
        t_Param1 p1;
        t_Param2 p2;
        t_Param3 p3;
        t_Param4 p4;
        t_Param5 p5;
        t_Param6 p6;
        t_Param7 p7;
    };
    template<typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7, typename t_Param8>
    class list_9: public list
    {
    public:
        list_9(void) {}
        list_9(const t_Param0& a_p0, const t_Param1& a_p1, const t_Param2& a_p2, const t_Param3& a_p3, const t_Param4& a_p4, const t_Param5& a_p5, const t_Param6& a_p6, const t_Param7& a_p7, const t_Param8& a_p8)
            : p0(a_p0), p1(a_p1), p2(a_p2), p3(a_p3), p4(a_p4), p5(a_p5), p6(a_p6), p7(a_p7), p8(a_p8) {}
        t_Param0 p0;
        t_Param1 p1;
        t_Param2 p2;
        t_Param3 p3;
        t_Param4 p4;
        t_Param5 p5;
        t_Param6 p6;
        t_Param7 p7;
        t_Param8 p8;
    };
    template<typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7, typename t_Param8, typename t_Param9>
    class list_10: public list
    {
    public:
        list_10(void) {}
        list_10(const t_Param0& a_p0, const t_Param1& a_p1, const t_Param2& a_p2, const t_Param3& a_p3, const t_Param4& a_p4, const t_Param5& a_p5, const t_Param6& a_p6, const t_Param7& a_p7, const t_Param8& a_p8, const t_Param9& a_p9)
            : p0(a_p0), p1(a_p1), p2(a_p2), p3(a_p3), p4(a_p4), p5(a_p5), p6(a_p6), p7(a_p7), p8(a_p8), p9(a_p9) {}
        t_Param0 p0;
        t_Param1 p1;
        t_Param2 p2;
        t_Param3 p3;
        t_Param4 p4;
        t_Param5 p5;
        t_Param6 p6;
        t_Param7 p7;
        t_Param8 p8;
        t_Param9 p9;
    };
};

struct rtti_data;

typedef void (*dynamic_delete_func_t)(void* o_memory_stat_append_parameters);

enum restore_state
{
    restore_complete = 0,
    restore_incomplete,
    restore_failed
};

struct vtable_info
{
    vtable_info()
        : offset(0xffffffff) , count(0xffffffff), member_functions(NULL) {}

    vtable_info(size_t a_offset, void** a_member_functions, size_t a_count)
        : offset(a_offset), member_functions(a_member_functions), count(a_count) {}

    bool operator<(const vtable_info& other) const
    {
        return offset < other.offset;
    }

    size_t offset;
    void** member_functions;
    size_t count;
};

o_namespace_end(phantom)


//#if defined(o_USE_POOL_ALLOCATORS)

_STD_BEGIN
    template<>
class hash<phantom::string>
    : public unary_function<phantom::string, size_t>
{	// hash functor
public:
    typedef phantom::string _Kty;

    size_t operator()(const _Kty& _Keyval) const
    {	// hash _Keyval to size_t value by pseudorandomizing transform
        size_t _Val = 2166136261U;
        size_t _First = 0;
        size_t _Last = _Keyval.size();
        size_t _Stride = 1 + _Last / 10;

        for(; _First < _Last; _First += _Stride)
            _Val = 16777619U * _Val ^ (size_t)_Keyval[_First];
        return (_Val);
    }
};

template<>
class hash<phantom::wstring>
    : public unary_function<phantom::wstring, size_t>
{	// hash functor
public:
    typedef phantom::wstring _Kty;

    size_t operator()(const _Kty& _Keyval) const
    {	// hash _Keyval to size_t value by pseudorandomizing transform
        size_t _Val = 2166136261U;
        size_t _First = 0;
        size_t _Last = _Keyval.size();
        size_t _Stride = 1 + _Last / 10;

        for(; _First < _Last; _First += _Stride)
            _Val = 16777619U * _Val ^ (size_t)_Keyval[_First];
        return (_Val);
    }
};

_STD_END


o_namespace_begin(phantom)

inline astring to_astring(const string& str) 
{
#if defined(_UNICODE) 
    phantom::wstringstream ws;
    ws << str.c_str();
    return ws.str();
#else
    return str;
#endif
}

inline astring to_astring(const wstring& wstr) 
{
#if defined(_UNICODE) 
    return wstr;
#else
    astring str;
    str.resize(wstr.size());
    for(size_t i = 0; i<wstr.size(); ++i)
        str = (character)wstr[i];
    return str;
#endif
}

inline string to_string(const string& astr)
{
    return astr;
}

inline string to_string(const wstring& astr)
{
    assert(false);
    return "";
}

o_namespace_end(phantom)

#include <phantom/bitfield.h>
#include <phantom/flags.h>

//#endif // defined(o_USE_POOL_ALLOCATORS)


#endif // o_phantom_typedefs_h__
