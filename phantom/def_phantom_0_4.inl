

o_namespace_begin(phantom)


// type_name_of specializations for primitive types
o_namespace_begin(reflection)

#define o_specialize_type_name_of_for_primitive_type(_type_) \
    template<>\
class type_name_of<_type_>\
{\
public:\
    static const char*  decoratedName() { return o_PP_QUOTE(_type_); }\
    static const char*  qualifiedDecoratedName() { return o_PP_QUOTE(_type_); }\
    static const char*  name() { return o_PP_QUOTE(_type_); }\
    static const char*  qualifiedName() { return o_PP_QUOTE(_type_); }\
    static const char*  namespaceName() { return ""; }\
    static const char*  classScopeName() { return ""; }\
};\
    namespace detail {\
template<int t_init_counter, int t_counter>\
class type_name_of_counter<_type_,t_init_counter,t_counter> : public type_name_of<_type_>\
{\
};\
}



o_specialize_type_name_of_for_primitive_type(char);
o_specialize_type_name_of_for_primitive_type(unsigned char);
o_specialize_type_name_of_for_primitive_type(signed char);
#if o_BUILT_IN_WCHAR_T
o_specialize_type_name_of_for_primitive_type(wchar_t);
#endif
o_specialize_type_name_of_for_primitive_type(short);
o_specialize_type_name_of_for_primitive_type(unsigned short);
o_specialize_type_name_of_for_primitive_type(int);
o_specialize_type_name_of_for_primitive_type(unsigned int);
o_specialize_type_name_of_for_primitive_type(long);
o_specialize_type_name_of_for_primitive_type(unsigned long);
o_specialize_type_name_of_for_primitive_type(long long);
o_specialize_type_name_of_for_primitive_type(unsigned long long);
o_specialize_type_name_of_for_primitive_type(float);
o_specialize_type_name_of_for_primitive_type(double);
o_specialize_type_name_of_for_primitive_type(long double);
o_specialize_type_name_of_for_primitive_type(bool);
o_specialize_type_name_of_for_primitive_type(void);

template<>
class type_name_of<std::nullptr_t>
{
public:
    static const char*  decoratedName() { return "nullptr_t"; }
    static const char*  qualifiedDecoratedName() { return "::std::nullptr_t"; }
    static const char*  name() { return "nullptr_t"; }
    static const char*  qualifiedName() { return "::std::nullptr_t"; }
    static const char*  namespaceName() { return "::std"; }
    static const char*  classScopeName() { return ""; }
};
namespace detail {
    template<int t_init_counter, int t_counter>
    class type_name_of_counter<std::nullptr_t,t_init_counter,t_counter> : public type_name_of<std::nullptr_t>
    {
    };
}
o_namespace_end(reflection)