#include "phantom/phantom.h"

#include "phantom/reflection/Expression.h"
#include "phantom/reflection/Application.h"

// Fundamental expressions
#include "phantom/reflection/DataExpression.h"

o_enumN((phantom), EABI)(e_stdcall,
    e_fastcall,
    e_cdecl,
    e_thiscall);

o_registerN((phantom), EABI);

#include "native/TFundamentals.h"

/// META META TYPES
#include "phantom/reflection/VirtualMemberFunctionTable.hxx"
#include "phantom/reflection/Class.hxx"
#include "phantom/reflection/Enum.hxx"
#include "phantom/reflection/Type.hxx"
#include "phantom/reflection/PrimitiveType.hxx"
#include "phantom/reflection/PointerType.hxx"
#include "phantom/reflection/DataPointerType.hxx"
#include "phantom/reflection/LValueReferenceType.hxx"
#include "phantom/reflection/RValueReferenceType.hxx"
#include "phantom/reflection/ArrayType.hxx"
#include "phantom/reflection/ClassType.hxx"
#include "phantom/reflection/Union.hxx"
#include "phantom/reflection/Structure.hxx"
#include "phantom/reflection/ContainerClass.hxx"
#include "phantom/reflection/ConstType.hxx"
#include "phantom/reflection/ConstVolatileType.hxx"
#include "phantom/reflection/VolatileType.hxx"
#include "phantom/reflection/MapContainerClass.hxx"
#include "phantom/reflection/SequentialContainerClass.hxx"
#include "phantom/reflection/SetContainerClass.hxx"
#include "phantom/reflection/LocalVariable.h"
#include "phantom/reflection/LocalVariable.hxx"
#include "phantom/reflection/Parameter.h"
#include "phantom/reflection/Parameter.hxx"
#include "phantom/reflection/Alias.h"
#include "phantom/reflection/Alias.hxx"
#include "phantom/reflection/Template.h"
#include "phantom/reflection/Template.hxx"
#include "phantom/reflection/TemplateParameter.h"
#include "phantom/reflection/TemplateParameter.hxx"
#include "phantom/reflection/TemplateSignature.h"
#include "phantom/reflection/TemplateSignature.hxx"
#include "phantom/reflection/TemplateSpecialization.h"
#include "phantom/reflection/TemplateSpecialization.hxx"
#include "phantom/reflection/Placeholder.h"
#include "phantom/reflection/Placeholder.hxx"
#include "phantom/string.h"
#include "phantom/string.hxx"

o_static_assert((boost::is_same<phantom::reflection::ClassType, phantom::base_class_of<phantom::reflection::Class, 0>::type>::value));
o_static_assert(boost::is_polymorphic<phantom::reflection::ClassType>::value);
o_static_assert(!phantom::has_new_vtable<phantom::reflection::Class>::value);


o_namespace_begin(phantom, reflection)

template<typename t_Ty>
void fundamental_type_installer(Type* a_pType, uint step /*(not used)*/)
{
    o_assert(step == 0);
}

void Types::Install()
{
    /// META-META-... TYPES :) (or type representation of the type representation of the type representation ... to INFINITY !


#define o_register_fundamental(type) \
    dynamic_initializer()->registerType(#type, get<type>()); \
    dynamic_initializer()->registerModule( get<type>(), fundamental_type_installer<type>, 0x1 );\
    application()->addBuiltInType(get<type>());

    static bool installed = false;
    if(installed) return;
    installed = true;

    Class::metaType = nullptr;
    type_of<Class>::object();
    VirtualMemberFunctionTable::metaType = nullptr;
    VirtualMemberFunctionTable::metaType = type_of<VirtualMemberFunctionTable>::object();
    Enum::metaType = type_of<Enum>::object();
    Type::metaType = type_of<Type>::object();
    PrimitiveType::metaType = type_of<PrimitiveType>::object();
    PointerType::metaType = type_of<PointerType>::object();
    DataPointerType::metaType = type_of<DataPointerType>::object();
    LValueReferenceType::metaType = type_of<LValueReferenceType>::object();
    RValueReferenceType::metaType = type_of<RValueReferenceType>::object();
    ArrayType::metaType = type_of<ArrayType>::object();
    ClassType::metaType = type_of<ClassType>::object();
    Union::metaType = type_of<Union>::object();
    Structure::metaType = type_of<Structure>::object();
    ConstType::metaType = type_of<ConstType>::object();
    VolatileType::metaType = type_of<VolatileType>::object();
    ConstVolatileType::metaType = type_of<ConstVolatileType>::object();
    ContainerClass::metaType = type_of<ContainerClass>::object();
    MapContainerClass::metaType = type_of<MapContainerClass>::object();
    SequentialContainerClass::metaType = type_of<SequentialContainerClass>::object();
    SetContainerClass::metaType = type_of<SetContainerClass>::object();
    LocalVariable::metaType = type_of<LocalVariable>::object();
    Parameter::metaType = type_of<Parameter>::object();
    Alias::metaType = type_of<Alias>::object();
    Template::metaType = type_of<Template>::object();
    TemplateSignature::metaType = type_of<TemplateSignature>::object();
    TemplateParameter::metaType = type_of<TemplateParameter>::object();
    TemplateSpecialization::metaType = type_of<TemplateSpecialization>::object();
    PlaceholderType::metaType = type_of<PlaceholderType>::object();
    PlaceholderConstant::metaType = type_of<PlaceholderConstant>::object();

#define o_build_fundamental_meta_type(_var_, _type_)\
    _var_ = o_dynamic_proxy_new(meta_class_type_of<_type_>::type)(typeNameOf<_type_>());\

    {o_namespace(std);}
    dynamic_initializer()->setActive(true);
    o_build_fundamental_meta_type(TYPE_VOID, void);
    o_build_fundamental_meta_type(TYPE_CHAR, char);
    o_build_fundamental_meta_type(TYPE_UNSIGNED_CHAR, unsigned char);
    o_build_fundamental_meta_type(TYPE_SIGNED_CHAR, signed char);
    o_build_fundamental_meta_type(TYPE_SHORT, short);
    o_build_fundamental_meta_type(TYPE_UNSIGNED_SHORT, unsigned short);
    o_build_fundamental_meta_type(TYPE_INT, int);
    o_build_fundamental_meta_type(TYPE_UNSIGNED_INT, unsigned int);
    o_build_fundamental_meta_type(TYPE_LONG, long);
    o_build_fundamental_meta_type(TYPE_UNSIGNED_LONG, unsigned long);
    o_build_fundamental_meta_type(TYPE_LONG_LONG, long long);
    o_build_fundamental_meta_type(TYPE_UNSIGNED_LONG_LONG, unsigned long long);
    o_build_fundamental_meta_type(TYPE_FLOAT, float);
    o_build_fundamental_meta_type(TYPE_DOUBLE, double);
    o_build_fundamental_meta_type(TYPE_LONG_DOUBLE, long double);
    o_build_fundamental_meta_type(TYPE_BOOL, bool);
    o_build_fundamental_meta_type(TYPE_NULLPTR_T, std::nullptr_t);
    TYPE_STRING = type_of<string>::object();
    TYPE_SIGNAL_T = type_of<phantom::signal_t>::object();
#if o_HAS_BUILT_IN_WCHAR_T
    o_build_fundamental_meta_type(TYPE_WCHAR_T, wchar_t);
#else
        TYPE_WCHAR_T = Types::TYPE_UNSIGNED_SHORT;
#endif
#if o_HAS_BUILT_IN_CHAR16_T
        o_build_fundamental_meta_type(TYPE_WCHAR_T, char16_t);
#else
        TYPE_CHAR16_T = Types::TYPE_UNSIGNED_SHORT;
#endif
#if o_HAS_BUILT_IN_CHAR32_T
        o_build_fundamental_meta_type(TYPE_WCHAR_T, char32_t);
#else
        TYPE_CHAR32_T = Types::TYPE_UNSIGNED_INT;
#endif
    TYPE_VOID_PTR = TYPE_VOID->pointerType();


    dynamic_initializer()->setActive(false);
}

void Types::Register()
{
    dynamic_initializer()->setActive(true);

    o_register_fundamental(char);
#if o_HAS_BUILT_IN_WCHAR_T
    o_register_fundamental(wchar_t);
#endif
#if o_HAS_BUILT_IN_CHAR16_T
    o_register_fundamental(char16_t);
#endif
#if o_HAS_BUILT_IN_CHAR32_T
    o_register_fundamental(char32_t);
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
    dynamic_initializer()->registerType("std::nullptr_t", "std", get<std::nullptr_t>());
    dynamic_initializer()->registerModule( get<std::nullptr_t>(), fundamental_type_installer<std::nullptr_t>, 0x1 );
    dynamic_initializer()->setActive(false);
    
    Namespace* pGlobal = globalNamespace();
    Namespace* pPhantom = pGlobal->findOrCreateNamespaceCascade("phantom");

#define o_fundamental_typedef(t)\
    pGlobal->addAlias(typeOf<t>(), #t, o_native)

#define o_fundamental_phantom_typedef(t)\
    pPhantom->addAlias(typeOf<t>(), #t, o_native)


#if defined(_M_IA64) || defined(_M_X64) || defined(_M_AMD64)
    o_fundamental_typedef(int128);
    o_fundamental_typedef(uint128);
    o_fundamental_typedef(sint128);
#endif

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
    o_fundamental_typedef(__int8);
    o_fundamental_typedef(__int16);
    o_fundamental_typedef(__int32);
    o_fundamental_typedef(__int64);
#else
    o_fundamental_typedef(int8_t);
    o_fundamental_typedef(int16_t);
    o_fundamental_typedef(int32_t);
    o_fundamental_typedef(int64_t);
#endif


#if o_HAS_BUILT_IN_WCHAR_T == 0
    o_fundamental_typedef(wchar_t);
#endif
#if o_HAS_BUILT_IN_CHAR16_T == 0
    o_fundamental_typedef(char16_t);
#endif
#if o_HAS_BUILT_IN_CHAR32_T == 0
    o_fundamental_typedef(char32_t);
#endif

    o_fundamental_typedef(size_t);
    o_fundamental_typedef(double_size_t);

    o_fundamental_phantom_typedef(uchar);
    o_fundamental_phantom_typedef(schar);
    o_fundamental_phantom_typedef(ushort);
    o_fundamental_phantom_typedef(uint);
    o_fundamental_phantom_typedef(ulong);
    o_fundamental_phantom_typedef(longlong);
    o_fundamental_phantom_typedef(ulonglong);
    o_fundamental_phantom_typedef(longdouble);
    o_fundamental_phantom_typedef(character);
    o_fundamental_phantom_typedef(byte);
    o_fundamental_phantom_typedef(boolean);
    o_fundamental_phantom_typedef(int8);
    o_fundamental_phantom_typedef(int16);
    o_fundamental_phantom_typedef(int32);
    o_fundamental_phantom_typedef(int64);
    o_fundamental_phantom_typedef(uint8);
    o_fundamental_phantom_typedef(uint16);
    o_fundamental_phantom_typedef(uint32);
    o_fundamental_phantom_typedef(uint64);
    o_fundamental_phantom_typedef(sint8);
    o_fundamental_phantom_typedef(sint16);
    o_fundamental_phantom_typedef(sint32);
    o_fundamental_phantom_typedef(sint64);
    o_fundamental_phantom_typedef(real);

#undef o_fundamental_typedef
}

Type* Types::TYPE_VOID = nullptr;
Type* Types::TYPE_CHAR = nullptr;
Type* Types::TYPE_UNSIGNED_CHAR = nullptr;
Type* Types::TYPE_SIGNED_CHAR = nullptr;
Type* Types::TYPE_SHORT = nullptr;
Type* Types::TYPE_UNSIGNED_SHORT = nullptr;
Type* Types::TYPE_INT = nullptr;
Type* Types::TYPE_UNSIGNED_INT = nullptr;
Type* Types::TYPE_LONG = nullptr;
Type* Types::TYPE_UNSIGNED_LONG = nullptr;
Type* Types::TYPE_LONG_LONG = nullptr;
Type* Types::TYPE_UNSIGNED_LONG_LONG = nullptr;
Type* Types::TYPE_FLOAT = nullptr;
Type* Types::TYPE_DOUBLE = nullptr;
Type* Types::TYPE_LONG_DOUBLE = nullptr;
Type* Types::TYPE_BOOL = nullptr;
Type* Types::TYPE_STRING = nullptr;
Type* Types::TYPE_SIGNAL_T = nullptr;
Type* Types::TYPE_NULLPTR_T = nullptr;

Type* Types::TYPE_WCHAR_T =
#if o_HAS_BUILT_IN_WCHAR_T == 1
    nullptr;
#else
    Types::TYPE_UNSIGNED_SHORT;
#endif

Type* Types::TYPE_CHAR16_T =
#if o_HAS_BUILT_IN_CHAR16_T == 1
nullptr;
#else
Types::TYPE_UNSIGNED_SHORT;
#endif

Type* Types::TYPE_CHAR32_T =
#if o_HAS_BUILT_IN_CHAR32_T== 1
nullptr;
#else
Types::TYPE_UNSIGNED_SHORT;
#endif

Type* Types::TYPE_VOID_PTR = nullptr;

namespace_alias_registrer::namespace_alias_registrer( const char* a_strNamespace, const char* a_strAlias, const char* a_strAliasedNamespace )
{
    dynamic_initializer()->setActive(true);
    Namespace* pNamespace = phantom::globalNamespace()->findOrCreateNamespaceCascade(a_strNamespace);
    Namespace* pAliasedNamespace = phantom::globalNamespace()->findOrCreateNamespaceCascade(a_strAliasedNamespace);
    pNamespace->addNamespaceAlias(a_strAlias, pAliasedNamespace);
    dynamic_initializer()->setActive(false);
}

namespace_alias_registrer::namespace_alias_registrer( const char* a_strAlias, const char* a_strAliasedNamespace )
{
    dynamic_initializer()->setActive(true);
    phantom::globalNamespace()->addNamespaceAlias(a_strAlias, phantom::globalNamespace()->findOrCreateNamespaceCascade(a_strAliasedNamespace));
    dynamic_initializer()->setActive(false);
}

namespace_registrer::namespace_registrer( const char* a_strNamespace, const char* a_strFile )
{
    dynamic_initializer()->setActive(true);
    Namespace* pNamespace = phantom::globalNamespace()->findOrCreateNamespaceCascade(a_strNamespace);
    dynamic_initializer()->registerNamespace(pNamespace, a_strFile);
    dynamic_initializer()->setActive(false);
}

o_export void initializeSystem()
{
    /// Install pre defined and convenient types
    phantom::reflection::Types::Install();
    phantom::reflection::Types::Register();
}

using_registrer::using_registrer( const char* a_strWhere, const char* a_strElement )
{
    LanguageElement* pWhere = elementByName(a_strWhere);
    o_assert(pWhere AND pWhere->asScope());
    LanguageElement* pElement = elementByName(a_strElement, pWhere);
    o_assert(pElement);
    NamedElement* pNamedElement = pElement->asNamedElement();
    o_assert(pNamedElement);
    pWhere->asScope()->addAlias(o_new(Alias)(pNamedElement, pNamedElement->getName()));
}

friend_registrer::friend_registrer( const char* a_strWhere, const char* a_strFriend )
{
    LanguageElement* pWhere = elementByName(a_strWhere);
    if(pWhere == nullptr OR pWhere->asClassType() == nullptr)
    {
        o_exception(exception::reflection_runtime_exception, "'%s' is not a class type and cannot have friends", a_strWhere);
    }
    LanguageElement* pElement = elementByName(a_strFriend, pWhere);
    if(pElement == nullptr)
    {
        o_exception(exception::reflection_runtime_exception, "'%s' is undefined or unregistered", a_strFriend);
    }
    static_cast<ClassType*>(pWhere)->addFriend(pElement);
}

o_namespace_end(phantom, reflection)



