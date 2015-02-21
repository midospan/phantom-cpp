/* TODO LICENCE HERE */

#ifndef o_def_helpers_h__
#define o_def_helpers_h__

o_namespace_begin(phantom)

template<typename t_Ty, bool t_is_copyable>
struct value_getter_helper
{
    typedef o_NESTED_TYPE boost::remove_const<t_Ty>::type no_const;
    static void apply(void* dest, t_Ty& src)
    {
        *reinterpret_cast<no_const*>(dest) = src;
    }
};

template<typename t_Ty>
struct value_getter_helper<t_Ty, false>
{
    static void apply(void* dest, t_Ty& src)
    {
        o_exception(exception::reflection_runtime_exception, "Non copyable data member cannot be get");
    }
};

template<typename t_Ty>
struct value_getter : public value_getter_helper<t_Ty
    , NOT(has_copy_disabled<t_Ty>::value) AND (NOT(boost::is_class<t_Ty>::value) OR is_structure<t_Ty>::value OR boost::is_copy_constructible<t_Ty>::value)  >
{
};

template<typename t_Ty, size_t t_size>
struct value_getter<t_Ty[t_size]>
{
    typedef o_NESTED_TYPE boost::remove_const<t_Ty>::type no_const;
    static void apply(void* dest, t_Ty src[t_size])
    {
        size_t i = 0;
        for(;i<t_size;++i)
        {
            value_getter<t_Ty>::apply(&reinterpret_cast<no_const*>(dest)[i], src[i]);
        }
    }
};


template<typename t_Ty, bool t_is_copyable>
struct value_setter_helper
{
    typedef o_NESTED_TYPE boost::remove_const<t_Ty>::type no_const;
    static void apply(void const* src, t_Ty& dest)
    {
        dest = *const_cast<no_const*>(reinterpret_cast<t_Ty const*>(src));
    }
};

template<typename t_Ty>
struct value_setter_helper<t_Ty, false>
{
    static void apply(void const* src, t_Ty& dest)
    {
        o_exception(exception::reflection_runtime_exception, "Non copyable data member cannot be get");
    }
};

template<typename t_Ty>
struct value_setter : public value_setter_helper<t_Ty,
    NOT(has_copy_disabled<t_Ty>::value) AND (NOT(boost::is_class<t_Ty>::value) OR is_structure<t_Ty>::value OR boost::is_copy_constructible<t_Ty>::value)  >
{
};

template<typename t_Ty, size_t t_size>
struct value_setter<t_Ty[t_size]>
{
    typedef o_NESTED_TYPE boost::remove_const<t_Ty>::type no_const;
    static void apply(void const* src, t_Ty dest[t_size])
    {
        size_t i = 0;
        for(;i<t_size;++i)
        {
            value_setter<t_Ty>::apply(&(const_cast<no_const*>(reinterpret_cast<t_Ty const*>(src))[i]), dest[i]);
        }
    }
};


template<int e_eConvention, typename t_Signature>
struct native_function_pointer_type;

/// STDCALL

template<typename t_ReturnType>
struct native_function_pointer_type<e_stdcall, t_ReturnType()>
{
    typedef t_ReturnType (__stdcall * type)();
};

template<typename t_ReturnType, typename t_Param0>
struct native_function_pointer_type<e_stdcall, t_ReturnType(t_Param0)>
{
    typedef t_ReturnType (__stdcall * type)(t_Param0);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1>
struct native_function_pointer_type<e_stdcall, t_ReturnType(t_Param0, t_Param1)>
{
    typedef t_ReturnType (__stdcall * type)(t_Param0, t_Param1);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
struct native_function_pointer_type<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2)>
{
    typedef t_ReturnType (__stdcall * type)(t_Param0, t_Param1, t_Param2);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
struct native_function_pointer_type<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3)>
{
    typedef t_ReturnType (__stdcall * type)(t_Param0, t_Param1, t_Param2, t_Param3);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
struct native_function_pointer_type<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)>
{
    typedef t_ReturnType (__stdcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
struct native_function_pointer_type<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)>
{
    typedef t_ReturnType (__stdcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
struct native_function_pointer_type<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)>
{
    typedef t_ReturnType (__stdcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
struct native_function_pointer_type<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)>
{
    typedef t_ReturnType (__stdcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7, typename t_Param8>
struct native_function_pointer_type<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8)>
{
    typedef t_ReturnType (__stdcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7, typename t_Param8, typename t_Param9>
struct native_function_pointer_type<e_stdcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8, t_Param9)>
{
    typedef t_ReturnType (__stdcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8, t_Param9);
};

/// FASTCALL

template<typename t_ReturnType>
struct native_function_pointer_type<e_fastcall, t_ReturnType()>
{
    typedef t_ReturnType (__fastcall * type)();
};

template<typename t_ReturnType, typename t_Param0>
struct native_function_pointer_type<e_fastcall, t_ReturnType(t_Param0)>
{
    typedef t_ReturnType (__fastcall * type)(t_Param0);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1>
struct native_function_pointer_type<e_fastcall, t_ReturnType(t_Param0, t_Param1)>
{
    typedef t_ReturnType (__fastcall * type)(t_Param0, t_Param1);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
struct native_function_pointer_type<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2)>
{
    typedef t_ReturnType (__fastcall * type)(t_Param0, t_Param1, t_Param2);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
struct native_function_pointer_type<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3)>
{
    typedef t_ReturnType (__fastcall * type)(t_Param0, t_Param1, t_Param2, t_Param3);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
struct native_function_pointer_type<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)>
{
    typedef t_ReturnType (__fastcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
struct native_function_pointer_type<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)>
{
    typedef t_ReturnType (__fastcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
struct native_function_pointer_type<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)>
{
    typedef t_ReturnType (__fastcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
struct native_function_pointer_type<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)>
{
    typedef t_ReturnType (__fastcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7, typename t_Param8>
struct native_function_pointer_type<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8)>
{
    typedef t_ReturnType (__fastcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7, typename t_Param8, typename t_Param9>
struct native_function_pointer_type<e_fastcall, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8, t_Param9)>
{
    typedef t_ReturnType (__fastcall * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8, t_Param9);
};

/// CDECL

template<typename t_ReturnType>
struct native_function_pointer_type<e_cdecl, t_ReturnType()>
{
    typedef t_ReturnType (__cdecl * type)();
};

template<typename t_ReturnType, typename t_Param0>
struct native_function_pointer_type<e_cdecl, t_ReturnType(t_Param0)>
{
    typedef t_ReturnType (__cdecl * type)(t_Param0);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1>
struct native_function_pointer_type<e_cdecl, t_ReturnType(t_Param0, t_Param1)>
{
    typedef t_ReturnType (__cdecl * type)(t_Param0, t_Param1);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
struct native_function_pointer_type<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2)>
{
    typedef t_ReturnType (__cdecl * type)(t_Param0, t_Param1, t_Param2);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
struct native_function_pointer_type<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3)>
{
    typedef t_ReturnType (__cdecl * type)(t_Param0, t_Param1, t_Param2, t_Param3);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
struct native_function_pointer_type<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4)>
{
    typedef t_ReturnType (__cdecl * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
struct native_function_pointer_type<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5)>
{
    typedef t_ReturnType (__cdecl * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
struct native_function_pointer_type<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6)>
{
    typedef t_ReturnType (__cdecl * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
struct native_function_pointer_type<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7)>
{
    typedef t_ReturnType (__cdecl * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7, typename t_Param8>
struct native_function_pointer_type<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8)>
{
    typedef t_ReturnType (__cdecl * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8);
};

template<typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7, typename t_Param8, typename t_Param9>
struct native_function_pointer_type<e_cdecl, t_ReturnType(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8, t_Param9)>
{
    typedef t_ReturnType (__cdecl * type)(t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7, t_Param8, t_Param9);
};

template <typename t_Ty>
o_forceinline string                            decoratedTypeNameOf()
{
    return phantom::reflection::type_infos_of<t_Ty>::object().decorated_name();
}

template <typename t_Ty>
o_forceinline string                            typeNameOf()
{
    return phantom::reflection::type_infos_of<t_Ty>::object().name;
}

template <typename t_Ty>
o_forceinline string                            qualifiedTypeNameOf()
{
    return phantom::reflection::type_infos_of<t_Ty>::object().qualified_name();
}

template <typename t_Ty>
o_forceinline string                            qualifiedDecoratedTypeNameOf()
{
    return phantom::reflection::type_infos_of<t_Ty>::object().qualified_decorated_name();
}

template <typename t_Ty>
o_forceinline string                            scopeNameOf()
{
    return phantom::reflection::type_infos_of<t_Ty>::object().scope;
}

template<typename t_Target, typename t_Source>
inline t_Target lexical_cast(const t_Source &arg)
{
    return boost::lexical_cast<t_Target>(arg);
}

// float
template<>
inline float lexical_cast<float, phantom::string>(const phantom::string& arg)
{
    static float zero = 0.f;
    if(arg == "-1.#IND") return -zero/zero;
    else if(arg == "1.#IND") return zero/zero;
    else if(arg == "-1.#INF") return -1.f/zero;
    else if(arg == "1.#INF") return 1.f/zero;
    else return boost::lexical_cast<float>(arg);
}

// double
template<>
inline double lexical_cast<double, phantom::string>(const phantom::string& arg)
{
    static double zero = 0;
    if(arg == "-1.#IND") return -zero/zero;
    else if(arg == "1.#IND") return zero/zero;
    else if(arg == "-1.#INF") return -1./zero;
    else if(arg == "1.#INF") return 1./zero;
    else return boost::lexical_cast<double>(arg);
}

// long double
template<>
inline long double lexical_cast<long double, phantom::string>(const phantom::string& arg)
{
    static long double zero = 0;
    if(arg == "-1.#IND") return -zero/zero;
    else if(arg == "1.#IND") return zero/zero;
    else if(arg == "-1.#INF") return -1./zero;
    else if(arg == "1.#INF") return 1./zero;
    else return boost::lexical_cast<long double>(arg);
}

// long long
template<>
inline long long lexical_cast<long long, phantom::string>(const phantom::string& arg)
{
    return (long long)phantom::lexical_cast<long double>(arg);
}

template<>
inline unsigned long long lexical_cast<unsigned long long, phantom::string>(const phantom::string& arg)
{
    return (unsigned long long)phantom::lexical_cast<long double>(arg);
}

// long
template<>
inline long lexical_cast<long, phantom::string>(const phantom::string& arg)
{
    return (long)phantom::lexical_cast<float>(arg);
}

template<>
inline unsigned long lexical_cast<unsigned long, phantom::string>(const phantom::string& arg)
{
    return (unsigned long)phantom::lexical_cast<double>(arg);
}


// int
template<>
inline int lexical_cast<int, phantom::string>(const phantom::string& arg)
{
    return (int)phantom::lexical_cast<double>(arg);
}

template<>
inline unsigned int lexical_cast<unsigned int, phantom::string>(const phantom::string& arg)
{
    return (unsigned int)phantom::lexical_cast<double>(arg);
}


// short
template<>
inline short lexical_cast<short, phantom::string>(const phantom::string& arg)
{
    return (short)phantom::lexical_cast<float>(arg);
}

template<>
inline unsigned short lexical_cast<unsigned short, phantom::string>(const phantom::string& arg)
{
    return (unsigned short)phantom::lexical_cast<float>(arg);
}

// char
template<>
inline char lexical_cast<char, phantom::string>(const phantom::string &arg)
{
    return (char)phantom::lexical_cast<int>(arg);
}

template<>
inline phantom::string lexical_cast<phantom::string, char>(const char& arg)
{
    return phantom::lexical_cast<phantom::string>((int)arg);
}

// char
template<>
inline bool lexical_cast<bool, phantom::string>(const phantom::string &arg)
{
#pragma warning(disable:4800)
    return (bool)phantom::lexical_cast<int>(arg);
#pragma warning(default:4800)
}

template<>
inline phantom::string lexical_cast<phantom::string, bool>(const bool& arg)
{
    return phantom::lexical_cast<phantom::string>((int)arg);
}

template<>
inline unsigned char lexical_cast<unsigned char, phantom::string>(const phantom::string &arg)
{
    return (unsigned char)phantom::lexical_cast<unsigned int>(arg);
}

template<>
inline phantom::string lexical_cast<phantom::string, unsigned char>(const unsigned char& arg)
{
    return phantom::lexical_cast<phantom::string>((unsigned int)arg);
}

template<>
inline std::nullptr_t lexical_cast<std::nullptr_t, phantom::string>(const phantom::string &arg)
{
    if(arg != "nullptr")
    {
        o_exception(exception::base_exception, "parsing nullptr value failed");
    }
    return nullptr;
}

template<>
inline phantom::string lexical_cast<phantom::string, std::nullptr_t>(const std::nullptr_t& arg)
{
    if(arg != nullptr)
    {
        o_exception(exception::base_exception, "parsing nullptr value failed");
    }
    return "nullptr";
}

template<>
inline void* lexical_cast<void*, phantom::string>(const phantom::string &arg)
{
    void* ptr;
#pragma warning(disable:4996)
    sscanf(arg.c_str(), "%X", &ptr);
#pragma warning(default:4996)
    return ptr;
}

typedef void* msvc_bug_lexical_cast_void_ptr; // WTF ??? why do i need this typedef to make the specialization work ? o‘
template<>
inline phantom::string lexical_cast<phantom::string, msvc_bug_lexical_cast_void_ptr>(const msvc_bug_lexical_cast_void_ptr& arg)
{
    char buffer[32] = "";
#pragma warning(disable:4996)

#if o_ARCHITECTURE == o_ARCHITECTURE_X86
    sprintf(buffer, "%08X", (size_t)arg);
#elif o_ARCHITECTURE == o_ARCHITECTURE_X64
    sprintf(buffer, "%016X", (size_t)arg);
#else
    sprintf(buffer, "%016X", (size_t)arg);
#endif
#pragma warning(default:4996)
    return buffer;
}

template<typename t_Signature>
class constructor_caller;

template<typename t_Ty>
class constructor_caller<t_Ty()> : public t_Ty
{
public:
    o_forceinline static void apply(void* a_pAddress, void** a_pParams)
    {
        new (a_pAddress) constructor_caller();
    }

};

template<typename t_Ty, typename t_Param0>
class constructor_caller<t_Ty(t_Param0)> : public t_Ty
{
public:
    o_forceinline constructor_caller(t_Param0 p0)
        : t_Ty(p0) {}
    typedef constructor_caller<t_Ty(t_Param0)> self_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;

    o_forceinline static void apply(void* a_pAddress, void** a_pParams)
    {
        new (a_pAddress) self_type(*static_cast<t_Param0_noref*>(a_pParams[0]));
    }
};


template<typename t_Ty, typename t_Param0, typename t_Param1>
class constructor_caller<t_Ty(t_Param0,t_Param1)> : public t_Ty
{
public:
    o_forceinline constructor_caller(t_Param0 p0,t_Param1 p1)
        : t_Ty(p0,p1) {}
    typedef constructor_caller<t_Ty(t_Param0,t_Param1)> self_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;

    o_forceinline static void apply(void* a_pAddress, void** a_pParams)
    {
        new (a_pAddress) self_type(*static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1]));
    }
};


template<typename t_Ty, typename t_Param0, typename t_Param1, typename t_Param2>
class constructor_caller<t_Ty(t_Param0,t_Param1,t_Param2)> : public t_Ty
{
public:
    o_forceinline constructor_caller(t_Param0 p0,t_Param1 p1,t_Param2 p2)
        : t_Ty(p0,p1,p2) {}
    typedef constructor_caller<t_Ty(t_Param0,t_Param1,t_Param2)> self_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;

    o_forceinline static void apply(void* a_pAddress, void** a_pParams)
    {
        new (a_pAddress) self_type(*static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            );
    }
};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
>
class constructor_caller<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3)> : public t_Ty
{
public:
    o_forceinline constructor_caller(t_Param0 p0,t_Param1 p1,t_Param2 p2,t_Param3 p3)
        : t_Ty(p0,p1,p2,p3) {}
    typedef constructor_caller<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3)> self_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;

    o_forceinline static void apply(void* a_pAddress, void** a_pParams)
    {
        new (a_pAddress) self_type(*static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            );
    }
};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
>
class constructor_caller<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4)> : public t_Ty
{
public:
    o_forceinline constructor_caller(t_Param0 p0,t_Param1 p1,t_Param2 p2,t_Param3 p3,t_Param4 p4)
        : t_Ty(p0,p1,p2,p3,p4) {}
    typedef constructor_caller<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4)> self_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;

    o_forceinline static void apply(void* a_pAddress, void** a_pParams)
    {
        new (a_pAddress) self_type(*static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            );
    }
};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
>
class constructor_caller<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)> : public t_Ty
{
public:
    o_forceinline constructor_caller(t_Param0 p0,t_Param1 p1,t_Param2 p2,t_Param3 p3,t_Param4 p4,t_Param5 p5)
        : t_Ty(p0,p1,p2,p3,p4,p5) {}
    typedef constructor_caller<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)> self_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;


    o_forceinline static void apply(void* a_pAddress, void** a_pParams)
    {
        new (a_pAddress) self_type(*static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            );
    }
};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
>
class constructor_caller<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)> : public t_Ty
{
public:
    o_forceinline constructor_caller(t_Param0 p0,t_Param1 p1,t_Param2 p2,t_Param3 p3,t_Param4 p4,t_Param5 p5,t_Param6 p6)
        : t_Ty(p0,p1,p2,p3,p4,p5,p6) {}
    typedef constructor_caller<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)> self_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;

    o_forceinline static void apply(void* a_pAddress, void** a_pParams)
    {
        new (a_pAddress) self_type(*static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            );
    }
};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7
>
class constructor_caller<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)> : public t_Ty
{
public:
    o_forceinline constructor_caller(t_Param0 p0,t_Param1 p1,t_Param2 p2,t_Param3 p3,t_Param4 p4,t_Param5 p5,t_Param6 p6,t_Param7 p7)
        : t_Ty(p0,p1,p2,p3,p4,p5,p6,p7) {}
    typedef constructor_caller<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)> self_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;

    o_forceinline static void apply(void* a_pAddress, void** a_pParams)
    {
        new (a_pAddress) self_type(*static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7])
            );
    }
};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7
    , typename t_Param8
>
class constructor_caller<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7,t_Param8)> : public t_Ty
{
public:
    o_forceinline constructor_caller(t_Param0 p0,t_Param1 p1,t_Param2 p2,t_Param3 p3,t_Param4 p4,t_Param5 p5,t_Param6 p6,t_Param7 p7,t_Param8 p8)
        : t_Ty(p0,p1,p2,p3,p4,p5,p6,p7,p8) {}
    typedef constructor_caller<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7,t_Param8)> self_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param8>::type t_Param8_noref;

    o_forceinline static void apply(void* a_pAddress, void** a_pParams)
    {
        new (a_pAddress) self_type(*static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7])
            , *static_cast<t_Param8_noref*>(a_pParams[8])
            );
    }
};

template<typename t_Ty
    , typename t_Param0
    , typename t_Param1
    , typename t_Param2
    , typename t_Param3
    , typename t_Param4
    , typename t_Param5
    , typename t_Param6
    , typename t_Param7
    , typename t_Param8
    , typename t_Param9
>
class constructor_caller<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7,t_Param8,t_Param9)> : public t_Ty
{
public:
    o_forceinline constructor_caller(t_Param0 p0,t_Param1 p1,t_Param2 p2,t_Param3 p3,t_Param4 p4,t_Param5 p5,t_Param6 p6,t_Param7 p7,t_Param8 p8,t_Param9 p9)
        : t_Ty(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9) {}
    typedef constructor_caller<t_Ty(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7,t_Param8,t_Param9)> self_type;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param0>::type t_Param0_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param1>::type t_Param1_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param2>::type t_Param2_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param3>::type t_Param3_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param4>::type t_Param4_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param5>::type t_Param5_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param6>::type t_Param6_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param7>::type t_Param7_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param8>::type t_Param8_noref;
    typedef o_NESTED_TYPE boost::remove_reference<t_Param9>::type t_Param9_noref;

    o_forceinline static void apply(void* a_pAddress, void** a_pParams)
    {
        new (a_pAddress) self_type(*static_cast<t_Param0_noref*>(a_pParams[0])
            , *static_cast<t_Param1_noref*>(a_pParams[1])
            , *static_cast<t_Param2_noref*>(a_pParams[2])
            , *static_cast<t_Param3_noref*>(a_pParams[3])
            , *static_cast<t_Param4_noref*>(a_pParams[4])
            , *static_cast<t_Param5_noref*>(a_pParams[5])
            , *static_cast<t_Param6_noref*>(a_pParams[6])
            , *static_cast<t_Param7_noref*>(a_pParams[7])
            , *static_cast<t_Param8_noref*>(a_pParams[8])
            , *static_cast<t_Param9_noref*>(a_pParams[9])
            );
    }
};

namespace reflection
{
    struct type_infos
    {
        type_infos() {}
        type_infos(const char* s, const char* n, const string& d) : scope(s), name(n), decoration(d) {}
        string scope;
        string name;
        string decoration;
        string decorated_name() const { return name+decoration; }
        string qualified_name() const { return (scope.empty() ? name : scope+"::"+name); }
        string qualified_decorated_name() const { return qualified_name()+decoration; }
    };

    namespace detail 
    {
#if o_HAS_COMPILE_TIME_TYPEID == 0
        template <typename t_Ty>
        const type_infos&  typeInfosOf();
#endif

        o_export void cpp_typeid_name_to_phantom_qualifiedDecoratedName(string& a_typeid_name);
        o_export void qualifiedDecoratedName_to_type_infos(string& a_typeid_name, type_infos& a_type_infos);

    }

    template<typename t_Ty>
    struct type_infos_of
    {
#if o_HAS_COMPILE_TIME_TYPEID
        static const type_infos& object() 
        { 
            static type_infos ti;
            if(ti.name.empty())
            {
                string qualifiedDecoratedName = typeid(t_Ty).name();
                detail::cpp_typeid_name_to_phantom_qualifiedDecoratedName(qualifiedDecoratedName);
                detail::qualifiedDecoratedName_to_type_infos(qualifiedDecoratedName, ti);
            }
            return ti;
#else // if typeid not available and type_infos_of not specialized for the current type => use home made typeInfosOf defined on registration (o_register)
        o_forceinline static const type_infos& object() 
        { 
            o_static_warning(!(is_template<t_Ty>::value), "template class used in reflection without C++ RTTI 'typeid' enabled or corresponding .hxx included : be sure that every underlying template instance generated is registered explicitely somewhere then (in this module or another linked dll) or you will face a link error");
            return detail::typeInfosOf<t_Ty>(); 
#endif
        }
    };

    template<typename t_Ty>
    struct type_infos_of<t_Ty*>
    {
        inline static const phantom::reflection::type_infos& object() 
        { 
            static type_infos ti;
            if(ti.name.empty())
            {
                const type_infos& base = type_infos_of<t_Ty>::object();
                ti.scope = base.scope;
                ti.name = base.name;
                ti.decoration = base.decoration+"*";
            }
            return ti;
        }
    };

    template<typename t_Ty>
    struct type_infos_of<t_Ty&>
    {
        inline static const phantom::reflection::type_infos& object() 
        { 
            static type_infos ti;
            if(ti.name.empty())
            {
                const type_infos& base = type_infos_of<t_Ty>::object();
                ti.scope = base.scope;
                ti.name = base.name;
                ti.decoration = base.decoration+"&";
            }
            return ti;
        }
    };

#if o_HAS_RVALUE_REFERENCES
    template<typename t_Ty>
    struct type_infos_of<t_Ty&&>
    {
        inline static const phantom::reflection::type_infos& object() 
        { 
            static type_infos ti;
            if(ti.name.empty())
            {
                const type_infos& base = type_infos_of<t_Ty>::object();
                ti.scope = base.scope;
                ti.name = base.name;
                ti.decoration = base.decoration+"&&";
            }
            return ti;
        }
    };
#endif

    template<typename t_Ty>
    struct type_infos_of<t_Ty const>
    {
        inline static const phantom::reflection::type_infos& object() 
        { 
            static type_infos ti;
            if(ti.name.empty())
            {
                const type_infos& base = type_infos_of<t_Ty>::object();
                ti.scope = base.scope;
                ti.name = base.name;
                ti.decoration = base.decoration + (base.decoration.empty()?"const":" const");
            }
            return ti;
        }
    };

    template<typename t_Ty, size_t i>
    struct type_infos_of<t_Ty[i]>
    {
        inline static const phantom::reflection::type_infos& object() 
        { 
            static type_infos ti;
            if(ti.name.empty())
            {
                const type_infos& base = type_infos_of<t_Ty>::object();
                ti.scope = base.scope;
                ti.name = base.name;
                ti.decoration = base.decoration+"["+lexical_cast<string>(i)+"]";
            }
            return ti;
        }
    };

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_create_type_decoration_extractor(types) o_PP_CAT(o_PP_CAT(o_create_type_decoration_extractor_,o_PP_NARG types),(types))


#define o_create_type_decoration_extractor_1(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST1))>\
    struct type_decoration_extractor\
    {\
        static phantom::string decoration() { return "< "\
            + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types o_PP_RIGHT_PAREN < t_0 > ::qualifiedDecoratedName()\
            +" >"; }\
    };

#define o_create_type_decoration_extractor_2(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST2))>\
    struct type_decoration_extractor\
    {\
    static string decoration() { return "< "\
    +       o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types o_PP_RIGHT_PAREN < t_0 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_1 types o_PP_RIGHT_PAREN < t_1 > ::qualifiedDecoratedName()\
    +" >"; }\
    };

#define o_create_type_decoration_extractor_3(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST3))>\
    struct type_decoration_extractor\
    {\
    static string decoration() { return "< "\
    +       o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types o_PP_RIGHT_PAREN < t_0 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_1 types o_PP_RIGHT_PAREN < t_1 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_2 types o_PP_RIGHT_PAREN < t_2 > ::qualifiedDecoratedName()\
    +" >"; }\
    };

#define o_create_type_decoration_extractor_4(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST4))>\
    struct type_decoration_extractor\
    {\
    static string decoration() { return "< "\
    +       o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types o_PP_RIGHT_PAREN < t_0 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_1 types o_PP_RIGHT_PAREN < t_1 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_2 types o_PP_RIGHT_PAREN < t_2 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_3 types o_PP_RIGHT_PAREN < t_3 > ::qualifiedDecoratedName()\
    +" >"; }\
    };

#define o_create_type_decoration_extractor_5(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST5))>\
    struct type_decoration_extractor\
    {\
    static string decoration() { return "< "\
    +       o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types o_PP_RIGHT_PAREN < t_0 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_1 types o_PP_RIGHT_PAREN < t_1 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_2 types o_PP_RIGHT_PAREN < t_2 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_3 types o_PP_RIGHT_PAREN < t_3 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_4 types o_PP_RIGHT_PAREN < t_4 > ::qualifiedDecoratedName()\
    +" >"; }\
    };

#define o_create_type_decoration_extractor_6(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST6))>\
    struct type_decoration_extractor\
    {\
    static string decoration() { return "< "\
    +       o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types o_PP_RIGHT_PAREN < t_0 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_1 types o_PP_RIGHT_PAREN < t_1 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_2 types o_PP_RIGHT_PAREN < t_2 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_3 types o_PP_RIGHT_PAREN < t_3 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_4 types o_PP_RIGHT_PAREN < t_4 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_5 types o_PP_RIGHT_PAREN < t_5 > ::qualifiedDecoratedName()\
    +" >"; }\
    };

#define o_create_type_decoration_extractor_6(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST6))>\
    struct type_decoration_extractor\
    {\
    static string decoration() { return "< "\
    +       o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types o_PP_RIGHT_PAREN < t_0 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_1 types o_PP_RIGHT_PAREN < t_1 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_2 types o_PP_RIGHT_PAREN < t_2 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_3 types o_PP_RIGHT_PAREN < t_3 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_4 types o_PP_RIGHT_PAREN < t_4 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_5 types o_PP_RIGHT_PAREN < t_5 > ::qualifiedDecoratedName()\
    +" >"; }\
    };

#define o_create_type_decoration_extractor_7(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST7))>\
    struct type_decoration_extractor\
    {\
    static string decoration() { return "< "\
    +       o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types o_PP_RIGHT_PAREN < t_0 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_1 types o_PP_RIGHT_PAREN < t_1 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_2 types o_PP_RIGHT_PAREN < t_2 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_3 types o_PP_RIGHT_PAREN < t_3 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_4 types o_PP_RIGHT_PAREN < t_4 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_5 types o_PP_RIGHT_PAREN < t_5 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_6 types o_PP_RIGHT_PAREN < t_6 > ::qualifiedDecoratedName()\
    +" >"; }\
    };

#define o_create_type_decoration_extractor_8(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST8))>\
    struct type_decoration_extractor\
    {\
    static string decoration() { return "< "\
    +       o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types o_PP_RIGHT_PAREN < t_0 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_1 types o_PP_RIGHT_PAREN < t_1 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_2 types o_PP_RIGHT_PAREN < t_2 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_3 types o_PP_RIGHT_PAREN < t_3 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_4 types o_PP_RIGHT_PAREN < t_4 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_5 types o_PP_RIGHT_PAREN < t_5 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_6 types o_PP_RIGHT_PAREN < t_6 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_7 types o_PP_RIGHT_PAREN < t_7 > ::qualifiedDecoratedName()\
    +" >"; }\
    };

#define o_create_type_decoration_extractor_9(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST9))>\
    struct type_decoration_extractor\
    {\
    static string decoration() { return "< "\
    +       o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types o_PP_RIGHT_PAREN < t_0 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_1 types o_PP_RIGHT_PAREN < t_1 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_2 types o_PP_RIGHT_PAREN < t_2 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_3 types o_PP_RIGHT_PAREN < t_3 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_4 types o_PP_RIGHT_PAREN < t_4 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_5 types o_PP_RIGHT_PAREN < t_5 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_6 types o_PP_RIGHT_PAREN < t_6 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_7 types o_PP_RIGHT_PAREN < t_7 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_8 types o_PP_RIGHT_PAREN < t_8 > ::qualifiedDecoratedName()\
    +" >"; }\
    };

#define o_create_type_decoration_extractor_10(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST10))>\
    struct type_decoration_extractor\
    {\
    static string decoration() { return "< "\
    +       o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types o_PP_RIGHT_PAREN < t_0 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_1 types o_PP_RIGHT_PAREN < t_1 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_2 types o_PP_RIGHT_PAREN < t_2 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_3 types o_PP_RIGHT_PAREN < t_3 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_4 types o_PP_RIGHT_PAREN < t_4 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_5 types o_PP_RIGHT_PAREN < t_5 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_6 types o_PP_RIGHT_PAREN < t_6 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_7 types o_PP_RIGHT_PAREN < t_7 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_8 types o_PP_RIGHT_PAREN < t_8 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT o_PP_LEFT_PAREN ::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_9 types o_PP_RIGHT_PAREN < t_9 > ::qualifiedDecoratedName()\
    +" >"; }\
    };


#else /// NOT VISUAL STUDIO


#define o_create_type_decoration_extractor(types) o_PP_CAT(o_create_type_decoration_extractor_,o_PP_NARG types) (types)

#define o_create_type_decoration_extractor_1(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST1))>\
struct type_decoration_extractor\
    {\
    static phantom::string decoration() { return "< "\
    + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types) < t_0 > ::qualifiedDecoratedName()\
    +" >"; }\
    };

#define o_create_type_decoration_extractor_2(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST2))>\
struct type_decoration_extractor\
    {\
    static string decoration() { return "< "\
    +       o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types) < t_0 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_1 types) < t_1 > ::qualifiedDecoratedName()\
    +" >"; }\
    };

#define o_create_type_decoration_extractor_3(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST3))>\
struct type_decoration_extractor\
    {\
    static string decoration() { return "< "\
    +       o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types) < t_0 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_1 types) < t_1 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_2 types) < t_2 > ::qualifiedDecoratedName()\
    +" >"; }\
    };

#define o_create_type_decoration_extractor_4(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST4))>\
struct type_decoration_extractor\
    {\
    static string decoration() { return "< "\
    +       o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types) < t_0 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_1 types) < t_1 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_2 types) < t_2 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_3 types) < t_3 > ::qualifiedDecoratedName()\
    +" >"; }\
    };

#define o_create_type_decoration_extractor_5(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST5))>\
struct type_decoration_extractor\
    {\
    static string decoration() { return "< "\
    +       o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types) < t_0 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_1 types) < t_1 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_2 types) < t_2 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_3 types) < t_3 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_4 types) < t_4 > ::qualifiedDecoratedName()\
    +" >"; }\
    };

#define o_create_type_decoration_extractor_6(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST6))>\
struct type_decoration_extractor\
    {\
    static string decoration() { return "< "\
    +       o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types) < t_0 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_1 types) < t_1 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_2 types) < t_2 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_3 types) < t_3 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_4 types) < t_4 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_5 types) < t_5 > ::qualifiedDecoratedName()\
    +" >"; }\
    };

#define o_create_type_decoration_extractor_6(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST6))>\
struct type_decoration_extractor\
    {\
    static string decoration() { return "< "\
    +       o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types) < t_0 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_1 types) < t_1 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_2 types) < t_2 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_3 types) < t_3 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_4 types) < t_4 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_5 types) < t_5 > ::qualifiedDecoratedName()\
    +" >"; }\
    };

#define o_create_type_decoration_extractor_7(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST7))>\
struct type_decoration_extractor\
    {\
    static string decoration() { return "< "\
    +       o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types) < t_0 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_1 types) < t_1 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_2 types) < t_2 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_3 types) < t_3 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_4 types) < t_4 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_5 types) < t_5 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_6 types) < t_6 > ::qualifiedDecoratedName()\
    +" >"; }\
    };

#define o_create_type_decoration_extractor_8(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST8))>\
struct type_decoration_extractor\
    {\
    static string decoration() { return "< "\
    +       o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types) < t_0 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_1 types) < t_1 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_2 types) < t_2 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_3 types) < t_3 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_4 types) < t_4 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_5 types) < t_5 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_6 types) < t_6 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_7 types) < t_7 > ::qualifiedDecoratedName()\
    +" >"; }\
    };

#define o_create_type_decoration_extractor_9(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST9))>\
struct type_decoration_extractor\
    {\
    static string decoration() { return "< "\
    +       o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types) < t_0 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_1 types) < t_1 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_2 types) < t_2 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_3 types) < t_3 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_4 types) < t_4 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_5 types) < t_5 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_6 types) < t_6 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_7 types) < t_7 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_8 types) < t_8 > ::qualifiedDecoratedName()\
    +" >"; }\
    };

#define o_create_type_decoration_extractor_10(types)\
    template<o_PP_MIX(types, (o_PP_CREATE_TEMPLATE_ARGUMENT_LIST10))>\
struct type_decoration_extractor\
    {\
    static string decoration() { return "< "\
    +       o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_0 types) < t_0 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_1 types) < t_1 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_2 types) < t_2 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_3 types) < t_3 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_4 types) < t_4 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_5 types) < t_5 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_6 types) < t_6 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_7 types) < t_7 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_8 types) < t_8 > ::qualifiedDecoratedName()\
    + "," + o_PP_CAT(::phantom::reflection::detail::template_signature_parameter_name_, o_PP_ARG_9 types) < t_9 > ::qualifiedDecoratedName()\
    +" >"; }\
    };

#endif

template <typename t_Signature>
struct type_decoration_extractor;

template<typename a0>
struct type_decoration_extractor<void(a0)>
{
    static string decoration() { return "< "
        +       qualifiedDecoratedTypeNameOf<a0>()
        +" >"; }
};

template<typename a0, typename a1>
struct type_decoration_extractor<void(a0,a1)>
{
    static string decoration() { return "< "
        +       qualifiedDecoratedTypeNameOf<a0>()
        + "," + qualifiedDecoratedTypeNameOf<a1>()
        +" >"; }
};

template<typename a0, typename a1, typename a2>
struct type_decoration_extractor<void(a0,a1,a2)>
{
    static string decoration() { return "< "
        +       qualifiedDecoratedTypeNameOf<a0>()
        + "," + qualifiedDecoratedTypeNameOf<a1>()
        + "," + qualifiedDecoratedTypeNameOf<a2>()
        +" >"; }
};

template<typename a0, typename a1, typename a2, typename a3>
struct type_decoration_extractor<void(a0,a1,a2,a3)>
{
    static string decoration() { return "< "
        +       qualifiedDecoratedTypeNameOf<a0>()
        + "," + qualifiedDecoratedTypeNameOf<a1>()
        + "," + qualifiedDecoratedTypeNameOf<a2>()
        + "," + qualifiedDecoratedTypeNameOf<a3>()
        +" >"; }
};

template<typename a0, typename a1, typename a2, typename a3, typename a4>
struct type_decoration_extractor<void(a0,a1,a2,a3,a4)>
{
    static string decoration() { return "< "
        +       qualifiedDecoratedTypeNameOf<a0>()
        + "," + qualifiedDecoratedTypeNameOf<a1>()
        + "," + qualifiedDecoratedTypeNameOf<a2>()
        + "," + qualifiedDecoratedTypeNameOf<a3>()
        + "," + qualifiedDecoratedTypeNameOf<a4>()
        +" >"; }
};

template<typename a0, typename a1, typename a2, typename a3, typename a4, typename a5>
struct type_decoration_extractor<void(a0,a1,a2,a3,a4,a5)>
{
    static string decoration() { return "< "
        +       qualifiedDecoratedTypeNameOf<a0>()
        + "," + qualifiedDecoratedTypeNameOf<a1>()
        + "," + qualifiedDecoratedTypeNameOf<a2>()
        + "," + qualifiedDecoratedTypeNameOf<a3>()
        + "," + qualifiedDecoratedTypeNameOf<a4>()
        + "," + qualifiedDecoratedTypeNameOf<a5>()
        +" >"; }
};

template<typename a0, typename a1, typename a2, typename a3, typename a4, typename a5, typename a6>
struct type_decoration_extractor<void(a0,a1,a2,a3,a4,a5,a6)>
{
    static string decoration() { return "< "
        +       qualifiedDecoratedTypeNameOf<a0>()
        + "," + qualifiedDecoratedTypeNameOf<a1>()
        + "," + qualifiedDecoratedTypeNameOf<a2>()
        + "," + qualifiedDecoratedTypeNameOf<a3>()
        + "," + qualifiedDecoratedTypeNameOf<a4>()
        + "," + qualifiedDecoratedTypeNameOf<a5>()
        + "," + qualifiedDecoratedTypeNameOf<a6>()
        +" >"; }
};

template<typename a0, typename a1, typename a2, typename a3, typename a4, typename a5, typename a6, typename a7>
struct type_decoration_extractor<void(a0,a1,a2,a3,a4,a5,a6,a7)>
{
    static string decoration() { return "< "
        +       qualifiedDecoratedTypeNameOf<a0>()
        + "," + qualifiedDecoratedTypeNameOf<a1>()
        + "," + qualifiedDecoratedTypeNameOf<a2>()
        + "," + qualifiedDecoratedTypeNameOf<a3>()
        + "," + qualifiedDecoratedTypeNameOf<a4>()
        + "," + qualifiedDecoratedTypeNameOf<a5>()
        + "," + qualifiedDecoratedTypeNameOf<a6>()
        + "," + qualifiedDecoratedTypeNameOf<a7>()
        +" >"; }
};

template<typename a0, typename a1, typename a2, typename a3, typename a4, typename a5, typename a6, typename a7, typename a8>
struct type_decoration_extractor<void(a0,a1,a2,a3,a4,a5,a6,a7,a8)>
{
    static string decoration() { return "< "
        +       qualifiedDecoratedTypeNameOf<a0>()
        + "," + qualifiedDecoratedTypeNameOf<a1>()
        + "," + qualifiedDecoratedTypeNameOf<a2>()
        + "," + qualifiedDecoratedTypeNameOf<a3>()
        + "," + qualifiedDecoratedTypeNameOf<a4>()
        + "," + qualifiedDecoratedTypeNameOf<a5>()
        + "," + qualifiedDecoratedTypeNameOf<a6>()
        + "," + qualifiedDecoratedTypeNameOf<a7>()
        + "," + qualifiedDecoratedTypeNameOf<a8>()
        +" >"; }
};

template<typename a0, typename a1, typename a2, typename a3, typename a4, typename a5, typename a6, typename a7, typename a8, typename a9>
struct type_decoration_extractor<void(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9)>
{
    static string decoration() { return "< "
        +       qualifiedDecoratedTypeNameOf<a0>()
        + "," + qualifiedDecoratedTypeNameOf<a1>()
        + "," + qualifiedDecoratedTypeNameOf<a2>()
        + "," + qualifiedDecoratedTypeNameOf<a3>()
        + "," + qualifiedDecoratedTypeNameOf<a4>()
        + "," + qualifiedDecoratedTypeNameOf<a5>()
        + "," + qualifiedDecoratedTypeNameOf<a6>()
        + "," + qualifiedDecoratedTypeNameOf<a7>()
        + "," + qualifiedDecoratedTypeNameOf<a8>()
        + "," + qualifiedDecoratedTypeNameOf<a9>()
        +" >"; }
};



}

o_export string conversionOperatorNameNormalizer(const string& a_strName, reflection::LanguageElement* a_pScope);

o_namespace_end(phantom)

#endif // o_def_helpers_h__