
o_classN((phantom), signal_t)();


o_namespace_begin(phantom, reflection)

#define o_specialize_type_of_for_primitive_type(_type_) \
    template<>\
class type_of<_type_>\
{\
public:\
    inline static phantom::reflection::PrimitiveType* object() { return static_cast<phantom::reflection::PrimitiveType*>(phantom::reflection::Types::get<_type_>()); }\
};

//o_specialize_type_of_for_primitive_type(phantom::string);
o_specialize_type_of_for_primitive_type(char);
o_specialize_type_of_for_primitive_type(unsigned char);
o_specialize_type_of_for_primitive_type(signed char);
#if o_HAS_BUILT_IN_WCHAR_T
o_specialize_type_of_for_primitive_type(wchar_t);
#endif
o_specialize_type_of_for_primitive_type(short);
o_specialize_type_of_for_primitive_type(unsigned short);
o_specialize_type_of_for_primitive_type(int);
o_specialize_type_of_for_primitive_type(unsigned int);
o_specialize_type_of_for_primitive_type(long);
o_specialize_type_of_for_primitive_type(unsigned long);
o_specialize_type_of_for_primitive_type(long long);
o_specialize_type_of_for_primitive_type(unsigned long long);
o_specialize_type_of_for_primitive_type(float);
o_specialize_type_of_for_primitive_type(double);
o_specialize_type_of_for_primitive_type(long double);
o_specialize_type_of_for_primitive_type(bool);
o_specialize_type_of_for_primitive_type(void);

o_namespace_end(phantom, reflection)