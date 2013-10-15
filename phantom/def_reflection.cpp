#include "phantom/phantom.h"

o_namespace_begin(phantom, reflection)

typedef_registrer::typedef_registrer( const char* a_strNamespace, const char* a_strTypedef, Type* a_pType )
{
    Phantom::dynamic_initializer(); // ensure modules (and especially reflection here) are initialized and ready
    Namespace* pNamespace = phantom::rootNamespace()->findOrCreateNamespaceCascade(a_strNamespace);
    o_assert(pNamespace);
    pNamespace->addTypedef(a_strTypedef, a_pType);
}

typedef_registrer::typedef_registrer( const char* a_strTypedef, Type* a_pType )
{
    Phantom::dynamic_initializer(); // ensure modules (and especially reflection here) are initialized and ready
    phantom::rootNamespace()->addTypedef(a_strTypedef, a_pType);
}

void initializeSystem()
{
#define x_reflection_register_fundamental_type(type) \
    { phantom::typeOf<type>(); }

    x_reflection_register_fundamental_type(char);
#if o_BUILT_IN_WCHAR_T
    x_reflection_register_fundamental_type(wchar_t);
#endif
    x_reflection_register_fundamental_type(short);
    x_reflection_register_fundamental_type(int);
    x_reflection_register_fundamental_type(long);
    x_reflection_register_fundamental_type(float);
    x_reflection_register_fundamental_type(double);
    x_reflection_register_fundamental_type(bool);
    x_reflection_register_fundamental_type(void);
    x_reflection_register_fundamental_type(signed char);
    x_reflection_register_fundamental_type(unsigned char);
    x_reflection_register_fundamental_type(unsigned short);
    x_reflection_register_fundamental_type(unsigned int);
    x_reflection_register_fundamental_type(unsigned long);
    x_reflection_register_fundamental_type(long double);
    x_reflection_register_fundamental_type(long long);
    x_reflection_register_fundamental_type(unsigned long long);
    o_reflection_register_typedef(size_t);

    {phantom::typeOf<phantom::signal_t>();}

    o_reflection_register_typedef(phantom, uchar);
    o_reflection_register_typedef(phantom, schar);
    o_reflection_register_typedef(phantom, ushort);
    o_reflection_register_typedef(phantom, uint);
    o_reflection_register_typedef(phantom, ulong);
    o_reflection_register_typedef(phantom, longlong);
    o_reflection_register_typedef(phantom, ulonglong);
    o_reflection_register_typedef(phantom, longdouble);
    o_reflection_register_typedef(phantom, character);
    o_reflection_register_typedef(phantom, byte);
    o_reflection_register_typedef(phantom, boolean);
    o_reflection_register_typedef(phantom, int8);
    o_reflection_register_typedef(phantom, int16);
    o_reflection_register_typedef(phantom, int32);
    o_reflection_register_typedef(phantom, int64);
    o_reflection_register_typedef(phantom, uint8);
    o_reflection_register_typedef(phantom, uint16);
    o_reflection_register_typedef(phantom, uint32);
    o_reflection_register_typedef(phantom, uint64);
    o_reflection_register_typedef(phantom, sint8);
    o_reflection_register_typedef(phantom, sint16);
    o_reflection_register_typedef(phantom, sint32);
    o_reflection_register_typedef(phantom, sint64);
    o_reflection_register_typedef(phantom, real);
}

o_namespace_end(phantom, reflection)




