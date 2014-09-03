
o_namespace_begin(phantom, extension)

#define o_phantom_extension_fundamental_converter_case(d) \
    if(a_pDestType == phantom::reflection::Types::get<d>())\
{\
    *((d*)dest) = (d)*src;\
}

#define o_phantom_extension_fundamental_converter_can_case(d) \
    if(a_pDestType == phantom::reflection::Types::get<d>())\
{\
    return true;\
}

#define o_phantom_extension_fundamental_converter(s) \
    template<>\
struct converter<s>\
{\
    static void convert(reflection::Type* a_pType, reflection::Type* a_pDestType, void* dest, const s* src)\
{\
    o_phantom_extension_fundamental_converter_case(bool)\
            else o_phantom_extension_fundamental_converter_case(char)\
            else o_phantom_extension_fundamental_converter_case(unsigned char)\
            else o_phantom_extension_fundamental_converter_case(short)\
            else o_phantom_extension_fundamental_converter_case(unsigned short)\
            else o_phantom_extension_fundamental_converter_case(int)\
            else o_phantom_extension_fundamental_converter_case(unsigned int)\
            else o_phantom_extension_fundamental_converter_case(long)\
            else o_phantom_extension_fundamental_converter_case(unsigned long)\
            else o_phantom_extension_fundamental_converter_case(long long)\
            else o_phantom_extension_fundamental_converter_case(unsigned long long)\
            else o_phantom_extension_fundamental_converter_case(long double)\
            else o_phantom_extension_fundamental_converter_case(float)\
            else o_phantom_extension_fundamental_converter_case(double)\
            else if(a_pDestType->asEnum()) \
{ \
    switch(a_pDestType->getSize())\
{\
    case 1:\
    convert(a_pType, phantom::reflection::Types::get<unsigned char>(), dest, src);\
    break;\
    case 2:\
    convert(a_pType, phantom::reflection::Types::get<unsigned short>(), dest, src);\
    break;\
    case 4:\
    convert(a_pType, phantom::reflection::Types::get<unsigned int>(), dest, src);\
    break;\
    case 8:\
    convert(a_pType, phantom::reflection::Types::get<unsigned long long>(), dest, src);\
    break;\
    default:\
    o_assert(false, "invalid size for enum type");\
}\
}\
            else detail::default_converter<s>::convert(a_pType, a_pDestType, dest, src);\
}\
    static bool isConvertibleTo(reflection::Type* a_pType, reflection::Type* a_pDestType)\
{\
    if(a_pDestType == a_pType) return true;\
    reflection::ReferenceType* pRefDestType = a_pDestType->asReferenceType();\
    if(pRefDestType AND pRefDestType->getReferencedType()->asConstType())\
        return isConvertibleTo(a_pType, a_pDestType->removeReference()->removeConst());\
            else o_phantom_extension_fundamental_converter_can_case(bool)\
            else o_phantom_extension_fundamental_converter_can_case(char)\
            else o_phantom_extension_fundamental_converter_can_case(unsigned char)\
            else o_phantom_extension_fundamental_converter_can_case(short)\
            else o_phantom_extension_fundamental_converter_can_case(unsigned short)\
            else o_phantom_extension_fundamental_converter_can_case(int)\
            else o_phantom_extension_fundamental_converter_can_case(unsigned int)\
            else o_phantom_extension_fundamental_converter_can_case(long)\
            else o_phantom_extension_fundamental_converter_can_case(unsigned long)\
            else o_phantom_extension_fundamental_converter_can_case(long long)\
            else o_phantom_extension_fundamental_converter_can_case(unsigned long long)\
            else o_phantom_extension_fundamental_converter_can_case(long double)\
            else o_phantom_extension_fundamental_converter_can_case(float)\
            else o_phantom_extension_fundamental_converter_can_case(double)\
            else if(a_pDestType->asEnum()) { return true; }\
            return detail::default_converter<s>::isConvertibleTo(a_pType, a_pDestType);\
}\
    static bool isImplicitlyConvertibleTo(reflection::Type* a_pType, reflection::Type* a_pDestType)\
{\
    if(a_pDestType == a_pType) return true;\
    reflection::ReferenceType* pRefDestType = a_pDestType->asReferenceType();\
    if(pRefDestType AND pRefDestType->getReferencedType()->asConstType())\
    return isImplicitlyConvertibleTo(a_pType, a_pDestType->removeReference()->removeConst());\
            else o_phantom_extension_fundamental_converter_can_case(bool)\
            else o_phantom_extension_fundamental_converter_can_case(char)\
            else o_phantom_extension_fundamental_converter_can_case(unsigned char)\
            else o_phantom_extension_fundamental_converter_can_case(short)\
            else o_phantom_extension_fundamental_converter_can_case(unsigned short)\
            else o_phantom_extension_fundamental_converter_can_case(int)\
            else o_phantom_extension_fundamental_converter_can_case(unsigned int)\
            else o_phantom_extension_fundamental_converter_can_case(long)\
            else o_phantom_extension_fundamental_converter_can_case(unsigned long)\
            else o_phantom_extension_fundamental_converter_can_case(long long)\
            else o_phantom_extension_fundamental_converter_can_case(unsigned long long)\
            else o_phantom_extension_fundamental_converter_can_case(long double)\
            else o_phantom_extension_fundamental_converter_can_case(float)\
            else o_phantom_extension_fundamental_converter_can_case(double)\
            return detail::default_converter<s>::isImplicitlyConvertibleTo(a_pType, a_pDestType);\
}\
};

#pragma warning(disable:4800)

    o_phantom_extension_fundamental_converter(bool)
    o_phantom_extension_fundamental_converter(char)
    o_phantom_extension_fundamental_converter(unsigned char)
    o_phantom_extension_fundamental_converter(short)
    o_phantom_extension_fundamental_converter(unsigned short)
    o_phantom_extension_fundamental_converter(int)
    o_phantom_extension_fundamental_converter(unsigned int)
    o_phantom_extension_fundamental_converter(long)
    o_phantom_extension_fundamental_converter(unsigned long)
    o_phantom_extension_fundamental_converter(long long)
    o_phantom_extension_fundamental_converter(unsigned long long)
    o_phantom_extension_fundamental_converter(long double)
    o_phantom_extension_fundamental_converter(float)
    o_phantom_extension_fundamental_converter(double)

    namespace detail {

    template<> struct safe_constructor_<bool>                  {    static void safeConstruct(void* a_pInstance) { *((bool*)a_pInstance) = 0; } };
template<> struct safe_constructor_<char>                  {    static void safeConstruct(void* a_pInstance) { *((char*)a_pInstance) = 0; } };
template<> struct safe_constructor_<unsigned char>         {    static void safeConstruct(void* a_pInstance) { *((unsigned char*)a_pInstance) = 0; } };
template<> struct safe_constructor_<short>                 {    static void safeConstruct(void* a_pInstance) { *((short*)a_pInstance) = 0; } };
template<> struct safe_constructor_<unsigned short>        {    static void safeConstruct(void* a_pInstance) { *((unsigned short*)a_pInstance) = 0; } };
template<> struct safe_constructor_<int>                   {    static void safeConstruct(void* a_pInstance) { *((int*)a_pInstance) = 0; } };
template<> struct safe_constructor_<unsigned int>          {    static void safeConstruct(void* a_pInstance) { *((unsigned int*)a_pInstance) = 0; } };
template<> struct safe_constructor_<long>                  {    static void safeConstruct(void* a_pInstance) { *((long*)a_pInstance) = 0; } };
template<> struct safe_constructor_<unsigned long>         {    static void safeConstruct(void* a_pInstance) { *((unsigned long*)a_pInstance) = 0; } };
template<> struct safe_constructor_<long long>             {    static void safeConstruct(void* a_pInstance) { *((long long*)a_pInstance) = 0; } };
template<> struct safe_constructor_<unsigned long long>    {    static void safeConstruct(void* a_pInstance) { *((unsigned long long*)a_pInstance) = 0; } };
template<> struct safe_constructor_<long double>           {    static void safeConstruct(void* a_pInstance) { *((long double*)a_pInstance) = 0; } };
template<> struct safe_constructor_<float>                 {    static void safeConstruct(void* a_pInstance) { *((float*)a_pInstance) = 0; } };
template<> struct safe_constructor_<double>                {    static void safeConstruct(void* a_pInstance) { *((double*)a_pInstance) = 0; } };

    }


#pragma warning(default:4800)

o_namespace_end(phantom, extension)