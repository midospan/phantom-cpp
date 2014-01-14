#include "phantom/phantom.h"

#define o_register_fundamental(_type_)\
static phantom::detail::dynamic_initializer_module_installer_registrer< _type_ > o_PP_CAT(g_register_module_, __COUNTER__) ;


o_register_fundamental(char);
#if o_BUILT_IN_WCHAR_T
o_register_fundamental(wchar_t);
#endif
o_register_fundamental(short);
o_register_fundamental(int);
o_register_fundamental(long);
o_register_fundamental(float);
o_register_fundamental(double);
o_register_fundamental(bool);
o_register_fundamental(void);
o_register_fundamental(signed char);
o_register_fundamental(unsigned char);
o_register_fundamental(unsigned short);
o_register_fundamental(unsigned int);
o_register_fundamental(unsigned long);
o_register_fundamental(long double);
o_register_fundamental(long long);
o_register_fundamental(unsigned long long);
o_register(phantom::signal_t);

o_register_typedef(size_t);

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

o_namespace_begin(phantom, reflection)
    
namespace_alias_registrer::namespace_alias_registrer( const char* a_strNamespace, const char* a_strAlias, const char* a_strAliasedNamespace )
{
    Phantom::dynamic_initializer()->setActive(true);
    Namespace* pNamespace = phantom::rootNamespace()->findOrCreateNamespaceCascade(a_strNamespace);
    Namespace* pAliasedNamespace = phantom::rootNamespace()->findOrCreateNamespaceCascade(a_strAliasedNamespace);
    pNamespace->addNamespaceAlias(a_strAlias, pAliasedNamespace);
    Phantom::dynamic_initializer()->setActive(false);
}

namespace_alias_registrer::namespace_alias_registrer( const char* a_strAlias, const char* a_strAliasedNamespace )
{
    Phantom::dynamic_initializer()->setActive(true);
    phantom::rootNamespace()->addNamespaceAlias(a_strAlias, phantom::rootNamespace()->findOrCreateNamespaceCascade(a_strAliasedNamespace));
    Phantom::dynamic_initializer()->setActive(false);
}

void initializeSystem()
{
}

o_namespace_end(phantom, reflection)




