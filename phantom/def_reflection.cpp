#include "phantom/phantom.h"

o_namespace_begin(phantom, reflection)

typedef_registrer::typedef_registrer( const char* a_strScope, const char* a_strTypedef, Type* a_pType )
{
    Phantom::dynamic_initializer(); // ensure modules (and especially reflection here) are initialized and ready
    phantom::reflection::Type* pType = phantom::typeByName(a_strScope);
    if(pType)
    {
        pType->addNestedTypedef(a_strTypedef, a_pType);
    }
    else
    {
        Namespace* pNamespace = phantom::rootNamespace()->findOrCreateNamespaceCascade(a_strScope);
        o_assert(pNamespace);
        pNamespace->addTypedef(a_strTypedef, a_pType);
    }
}

typedef_registrer::typedef_registrer( const char* a_strTypedef, Type* a_pType )
{
    Phantom::dynamic_initializer(); // ensure modules (and especially reflection here) are initialized and ready
    phantom::rootNamespace()->addTypedef(a_strTypedef, a_pType);
}

namespace_alias_registrer::namespace_alias_registrer( const char* a_strNamespace, const char* a_strAlias, const char* a_strAliasedNamespace )
{
    Phantom::dynamic_initializer(); // ensure modules (and especially reflection here) are initialized and ready
    Namespace* pNamespace = phantom::rootNamespace()->findOrCreateNamespaceCascade(a_strNamespace);
    Namespace* pAliasedNamespace = phantom::rootNamespace()->findOrCreateNamespaceCascade(a_strAliasedNamespace);
    pNamespace->addNamespaceAlias(a_strAlias, pAliasedNamespace);
}

namespace_alias_registrer::namespace_alias_registrer( const char* a_strAlias, const char* a_strAliasedNamespace )
{
    Phantom::dynamic_initializer(); // ensure modules (and especially reflection here) are initialized and ready
    phantom::rootNamespace()->addNamespaceAlias(a_strAlias, phantom::rootNamespace()->findOrCreateNamespaceCascade(a_strAliasedNamespace));
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
    o_register_typedef(size_t);

    {phantom::typeOf<phantom::signal_t>();}

    o_register_typedefN(phantom, uchar);
    o_register_typedefN(phantom, schar);
    o_register_typedefN(phantom, ushort);
    o_register_typedefN(phantom, uint);
    o_register_typedefN(phantom, ulong);
    o_register_typedefN(phantom, longlong);
    o_register_typedefN(phantom, ulonglong);
    o_register_typedefN(phantom, longdouble);
    o_register_typedefN(phantom, character);
    o_register_typedefN(phantom, byte);
    o_register_typedefN(phantom, boolean);
    o_register_typedefN(phantom, int8);
    o_register_typedefN(phantom, int16);
    o_register_typedefN(phantom, int32);
    o_register_typedefN(phantom, int64);
    o_register_typedefN(phantom, uint8);
    o_register_typedefN(phantom, uint16);
    o_register_typedefN(phantom, uint32);
    o_register_typedefN(phantom, uint64);
    o_register_typedefN(phantom, sint8);
    o_register_typedefN(phantom, sint16);
    o_register_typedefN(phantom, sint32);
    o_register_typedefN(phantom, sint64);
    o_register_typedefN(phantom, real);
}

o_namespace_end(phantom, reflection)




