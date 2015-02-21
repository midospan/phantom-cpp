/* TODO LICENCE HERE */

#ifndef o_phantom_typedefs_h__
#define o_phantom_typedefs_h__

#include <phantom/def_export.h>


o_namespace_begin(phantom)

    enum { max_type_size = 1024 };

typedef float            float32;
typedef double           float64;

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

typedef long long               longlong;

typedef unsigned char           uchar;
typedef unsigned short          ushort;
typedef unsigned int            uint;
typedef unsigned long           ulong;
typedef unsigned long long      ulonglong;

typedef signed char             schar;
typedef signed short            sshort;
typedef signed int              sint;
typedef signed long             slong;
typedef signed long long        slonglong;

#if defined(_M_IA64) || defined(_M_X64) || defined(_M_AMD64)
typedef __int128                int128;
typedef unsigned __int128       uint128;
typedef signed  __int128        sint128;
typedef unsigned __int128       double_size_t;
#else
typedef unsigned long long      double_size_t;
#endif



#if defined(_UNICODE)
typedef wchar_t                 character;
#else
typedef char                    character;

#endif


struct hex_t 
{ 
    hex_t() : val(0) {}
    explicit hex_t(unsigned long long x) : val(x) {} 
    operator unsigned long long() const { return val; } 
    unsigned long long val; 
} ;

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

#elif o_COMPILER == o_COMPILER_GCC || o_COMPILER == o_COMPILER_CLANG

struct generic_member_func_ptr
{
    generic_member_func_ptr()
    {
        funcaddress = 0;
        delta = 0;
    }

    void setClosurePointer(void* ptr)
    {
        funcaddress = ptr;
    }

    template<typename t_MemberPtr>
    generic_member_func_ptr(t_MemberPtr ptr)
    {
        o_static_assert_msg(boost::is_member_function_pointer<t_MemberPtr>::value, "must be a member function pointer");
        union
        {
            t_MemberPtr mptr;
            struct {
                union {
                    void* funcaddress; // always even
                    int vtable_index_2; //  = vindex*2+1, always odd
                };
                int delta;
            };
        } un;
//         adjustedthis = this + delta
//             if (funcadr & 1) CALL (* ( *delta + (vindex+1)/2) + 4)
//             else CALL funcadr
        un.mptr = ptr;
        funcaddress = un.funcaddress;
        vtable_index_2 = un.vtable_index_2;
        delta = un.delta;
    }
    template<typename t_MemberPtr>
    generic_member_func_ptr& operator = (t_MemberPtr ptr)
    {
        o_static_assert_msg(boost::is_member_function_pointer<t_MemberPtr>::value, "must be a member function pointer");
        union
        {
            t_MemberPtr mptr;
            struct {
                union {
                    void* funcaddress; // always even
                    int vtable_index_2; //  = vindex*2+1, always odd
                };
                int delta;
            };
        } un;
        //         adjustedthis = this + delta
        //             if (funcadr & 1) CALL (* ( *delta + (vindex+1)/2) + 4)
        //             else CALL funcadr
        un.mptr = ptr;
        funcaddress = un.funcaddress;
        vtable_index_2 = un.vtable_index_2;
        delta = un.delta;
        return *this;
    }
    template<typename t_MemberPtr>
    operator t_MemberPtr() const
    {
        o_static_assert_msg(boost::is_member_function_pointer<t_MemberPtr>::value, "must be a member function pointer");
        union
        {
            t_MemberPtr mptr;
            struct {
                union {
                    void* funcaddress; // always even
                    int vtable_index_2; //  = vindex*2+1, always odd
                };
                int delta;
            };
        } un;
        un.funcaddress = funcaddress;
        un.delta = delta;
        un.vtable_index_2 = vtable_index_2;
        return un.mptr;
    }

    operator void*() const { return funcaddress; }

protected:
    struct {
        union {
            void* funcaddress; // always even
            int vtable_index_2; //  = vindex*2+1, always odd
        };
        int delta;
    };
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
    typedef std::vector<t_Ty, o__t1_class__contiguous_memory_allocator(t_Ty)> base_type;
    typedef o_NESTED_TYPE base_type::size_type size_type;
    typedef phantom::vector<t_Ty> self_type;

    vector()
        : base_type()
    {	// construct empty vector
    }

    explicit vector(size_type _Count)
        : base_type(_Count)
    {	// construct from _Count * _Ty()
    }

    vector(size_type _Count, const t_Ty& _Val)
        : base_type(_Count, _Val)
    {	// construct from _Count * _Val
    }

    vector(const self_type& _Right)
        : base_type(_Right)
    {	// construct by copying _Right

    }

    template<class _Iter>
    vector(_Iter _First, _Iter _Last)
        : base_type(_First, _Last)
    {	// construct from [_First, _Last)
    }

};

template<typename t_Ty>
class list : public std::list<t_Ty, o__t1_class__partioned_memory_allocator(t_Ty)>
{
public:
    typedef std::list<t_Ty, o__t1_class__partioned_memory_allocator(t_Ty)> base_type;
    typedef o__t1_class__partioned_memory_allocator(t_Ty) allocator_type;
    typedef o_NESTED_TYPE base_type::size_type size_type;
    typedef phantom::list<t_Ty> self_type;
    list()
        : base_type()
    {
    }

    explicit list(const allocator_type& _Al)
        : base_type(_Al)
    {
    }

    explicit list(size_type _Count)
        : base_type(_Count)
    {
    }

    list(size_type _Count, const t_Ty& _Val)
        : base_type(_Count, _Val)
    {
    }

    list(size_type _Count, const t_Ty& _Val, const allocator_type& _Al)
        : base_type(_Count, _Val, _Al)
    {
    }

    list(const self_type& _Right)
        : base_type(_Right)
    {
    }

    template<class t_Iter>
    list(t_Iter _First, t_Iter _Last)
        : base_type(_First, _Last)
    {	// construct list from [_First, _Last)

    }

    template<class t_Iter>
    list(t_Iter _First, t_Iter _Last, const allocator_type& _Al)
        : base_type(_First, _Last, _Al)
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

    typedef deque<t_Ty> self_type;

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

    o_forceinline deque(const self_type& a_Right)
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
    , o__t1_class__partioned_memory_allocator(std::pair<const _KeyTy, _ValueTy>)>

{
public:
    typedef std::map<_KeyTy
        , _ValueTy
        , _Pr
        , o__t1_class__partioned_memory_allocator(std::pair<const _KeyTy, _ValueTy>)> base_type;

    typedef map<_KeyTy, _ValueTy, _Pr> self_type;
    typedef o_NESTED_TYPE base_type::key_compare key_compare;
    typedef o_NESTED_TYPE base_type::allocator_type allocator_type;

    map() : base_type() {}
    map(const self_type& _Right)
        : base_type(_Right)
    {	// construct map by copying _Right
    }

    explicit map(const key_compare& _Pred)
        : base_type(_Pred)
    {	// construct empty map from comparator
    }

    map(const key_compare& _Pred, const allocator_type& _Al)
        : base_type(_Pred, _Al)
    {	// construct empty map from comparator and allocator
    }

    template<class _Iter>
    map(_Iter _First, _Iter _Last)
        : base_type(_First, _Last)
    {	// construct map from [_First, _Last), defaults
    }

    template<class _Iter>
    map(_Iter _First, _Iter _Last,
        const key_compare& _Pred)
        : base_type(_First, _Last, _Pred)
    {	// construct map from [_First, _Last), comparator
    }

    template<class _Iter>
    map(_Iter _First, _Iter _Last,
        const key_compare& _Pred, const allocator_type& _Al)
        : base_type(_First, _Last, _Pred, _Al)
    {	// construct map from [_First, _Last), comparator, and allocator
    }

    self_type& operator=(const self_type& _Right)
    {	// assign by copying _Right
        base_type::operator=(_Right);
        return (*this);
    }

    map(self_type&& _Right)
        : base_type(_Right)
    {	// construct map by moving _Right
    }
};

template<typename _KeyTy, typename _Pr = std::less<_KeyTy> >
class set : public std::set<_KeyTy
    , _Pr
    , o__t1_class__partioned_memory_allocator(_KeyTy)>

{
public:
    typedef std::set<_KeyTy
        , _Pr
        , o__t1_class__partioned_memory_allocator(_KeyTy)> base_type;

    typedef o_NESTED_TYPE base_type::key_compare key_compare;
    typedef o_NESTED_TYPE base_type::allocator_type allocator_type;

    typedef set<_KeyTy, _Pr> self_type;

    set() : base_type() {}
    set(const self_type& _Right)
        : base_type(_Right)
    {	// construct map by copying _Right
    }

    explicit set(const key_compare& _Pred)
        : base_type(_Pred)
    {	// construct empty map from comparator
    }

    set(const key_compare& _Pred, const allocator_type& _Al)
        : base_type(_Pred, _Al)
    {	// construct empty map from comparator and allocator
    }

    template<class _Iter>
    set(_Iter _First, _Iter _Last)
        : base_type(_First, _Last)
    {	// construct map from [_First, _Last), defaults
    }

    template<class _Iter>
    set(_Iter _First, _Iter _Last,
        const key_compare& _Pred)
        : base_type(_First, _Last, _Pred)
    {	// construct map from [_First, _Last), comparator
    }

    template<class _Iter>
    set(_Iter _First, _Iter _Last,
        const key_compare& _Pred, const allocator_type& _Al)
        : base_type(_First, _Last, _Pred, _Al)
    {	// construct map from [_First, _Last), comparator, and allocator
    }

    self_type& operator=(const self_type& _Right)
    {	// assign by copying _Right
        base_type::operator=(_Right);
        return (*this);
    }

    set(self_type&& _Right)
        : base_type(_Right)
    {	// construct set by moving _Right
    }
};

template<class t_Kty,
class t_Ty,
#if o_HAS_CPP0X
class t_Hasher = std::hash<t_Kty>,
#else
class t_Hasher = std::tr1::hash<t_Kty>,
#endif
class t_Keyeq = std::equal_to<t_Kty> >
class unordered_map

#if o_HAS_CPP0X
    : public std::unordered_map<t_Kty,t_Ty,t_Hasher,t_Keyeq,o__t1_class__partioned_memory_allocator(o_TT(std::pair, const t_Kty, t_Ty))>
#else
    : public std::tr1::unordered_map<t_Kty,t_Ty,t_Hasher,t_Keyeq,o__t1_class__partioned_memory_allocator(o_TT(std::pair, const t_Kty, t_Ty))>
#endif
{

};

template<class t_Kty,
#if o_HAS_CPP0X
class t_Hasher = std::hash<t_Kty>,
#else
class t_Hasher = std::tr1::hash<t_Kty>,
#endif
class t_Keyeq = std::equal_to<t_Kty>,
class t_Alloc = o__t1_class__partioned_memory_allocator(t_Kty) >
class unordered_set

#if o_HAS_CPP0X
    : public std::unordered_set<t_Kty,t_Hasher,t_Keyeq,o__t1_class__partioned_memory_allocator(t_Kty)>
#else
    : public std::tr1::unordered_set<t_Kty,t_Hasher,t_Keyeq,o__t1_class__partioned_memory_allocator(t_Kty)>
#endif
{

};

template<typename _KeyTy, typename _ValueTy, typename _Pr = std::less<_KeyTy> >
class multimap : public std::multimap<_KeyTy
    , _ValueTy
    , _Pr
    , o__t1_class__partioned_memory_allocator(std::pair<_KeyTy, _ValueTy>)>
{};

template<typename t_KeyTy, typename t_Pr = std::less<t_KeyTy> >
class multiset : public std::multiset<t_KeyTy
    , t_Pr
    , o__t1_class__partioned_memory_allocator(t_KeyTy)>
{};


/**
 * \brief Customized version of boost::property_tree::ptree (handles custom allocations)
 *
 */

#if o__bool__use_custom_stl_partioned_allocator OR o__bool__use_custom_stl_contiguous_allocator

typedef boost::property_tree_custom::basic_ptree<
    string
    , string
    , o__t1_class__partioned_memory_allocator(character)
    , o__t1_class__contiguous_memory_allocator(character)> property_tree;

namespace property_tree_namespace = boost::property_tree_custom;

#else 

typedef boost::property_tree::basic_ptree<string, string> property_tree;

namespace property_tree_namespace = boost::property_tree;

#endif

typedef std::pair<string, string>               string_string;
typedef std::pair<string, string_string>        string_string_string;

namespace reflection { class Type; }

struct rtti_data;

typedef void (*dynamic_delete_func_t)(void* o_memory_stat_append_parameters);

enum restore_state
{
    restore_complete ,
    restore_incomplete,
    restore_failed
};

enum restore_pass
{
    restore_pass_local,
    restore_pass_global_1,
    restore_pass_global_2,
    restore_pass_global_3,
    restore_pass_global_4,
    restore_pass_global_5,
};

#define o_restore_pass_local    phantom::restore_pass_local
#define o_restore_pass_global_1 phantom::restore_pass_global_1
#define o_restore_pass_global_2 phantom::restore_pass_global_2
#define o_restore_pass_global_3 phantom::restore_pass_global_3
#define o_restore_pass_global_4 phantom::restore_pass_global_4
#define o_restore_pass_global_5 phantom::restore_pass_global_5

#define o_restore_complete      phantom::restore_complete
#define o_restore_incomplete    phantom::restore_incomplete
#define o_restore_failed        phantom::restore_failed

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
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
_STD_BEGIN
#else
namespace std {
#endif

#if o__bool__use_custom_stl_contiguous_allocator
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
#endif // #if o__bool__use_custom_stl_contiguous_allocator

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
_STD_END
#else
}
#endif

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

typedef ulonglong modifiers_t;

enum EABI
{
    e_stdcall,
    e_fastcall,
    e_cdecl,
    e_thiscall,
    e_placeholdercall,
    e_unknowncall,
    e_defaultcall = e_cdecl,
};

typedef fastdelegate::DelegateMemento DelegateMemento;

typedef fastdelegate::FastDelegate<void(void** a_pArgs, void* a_pOutput)> operation_delegate_t;

#if !o__bool__disable_runtime_compilation

/// ASSERTION ON TYPE SIZES (PHANTOM IS VERY STRICT ON THAT AND RUNTIME COMPILATION CANNOT BE USED ON PLATFORMS NOT SATISFYING THIS)

o_static_assert(sizeof(bool) == 1);
o_static_assert(sizeof(char) == 1);
o_static_assert(sizeof(signed char) == 1);
o_static_assert(sizeof(unsigned char) == 1);
o_static_assert(sizeof(short) == 2);
o_static_assert(sizeof(ushort) == 2);
o_static_assert(sizeof(int) == 4);
o_static_assert(sizeof(uint) == 4);
o_static_assert(sizeof(long) == 4);
o_static_assert(sizeof(ulong) == 4);
o_static_assert(sizeof(longlong) == 8);
o_static_assert(sizeof(ulonglong) == 8);
o_static_assert(sizeof(float) == 4);
o_static_assert(sizeof(double) == 8);
#if o_ARCHITECTURE == o_ARCHITECTURE_X64
o_static_assert(sizeof(long double) == 16);
#else 
o_static_assert(sizeof(long double) == 8);
#endif

#endif // !o__bool__disable_runtime_compilation

o_namespace_end(phantom)

namespace boost
{
    template<typename t_Key, typename t_Value>
    struct is_copy_constructible<std::pair<const t_Key, t_Value> >
    {
        const static bool value = false;
    };
}


#if o_HAS_BUILT_IN_CHAR16_T
#   define o_if_char16_t(...) __VA_ARGS__
#else 
#   define o_if_char16_t(...)
#endif

#if o_HAS_BUILT_IN_CHAR32_T
#   define o_if_char32_t(...) __VA_ARGS__
#else 
#   define o_if_char32_t(...)
#endif

#if o_HAS_BUILT_IN_WCHAR_T
#   define o_if_wchar_t(...) __VA_ARGS__
#else 
#   define o_if_wchar_t(...)
#endif

#include <phantom/flags.h>

//#endif // defined(o_USE_POOL_ALLOCATORS)


#endif // o_phantom_typedefs_h__
