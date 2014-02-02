#include "phantom/phantom.h"
/// META META TYPES
#include "phantom/reflection/Class.hxx"
#include "phantom/reflection/Enum.hxx"
#include "phantom/reflection/Type.hxx"
#include "phantom/reflection/PrimitiveType.hxx"
#include "phantom/reflection/PointerType.hxx"
#include "phantom/reflection/DataPointerType.hxx"
#include "phantom/reflection/ReferenceType.hxx"
#include "phantom/reflection/ArrayType.hxx"
#include "phantom/reflection/ClassType.hxx"
#include "phantom/reflection/Union.hxx"
#include "phantom/reflection/PODUnion.hxx"
#include "phantom/reflection/PODStruct.hxx"
#include "phantom/reflection/ConstDataPointerType.hxx"
#include "phantom/reflection/ConstArrayType.hxx"
#include "phantom/reflection/ConstReferenceType.hxx"
#include "phantom/reflection/ContainerClass.hxx"
#include "phantom/reflection/MapContainerClass.hxx"
#include "phantom/reflection/SequentialContainerClass.hxx"
#include "phantom/reflection/SetContainerClass.hxx"
#include "phantom/std/string.h"
#include "phantom/std/string.hxx"



o_namespace_begin(phantom, reflection)

template<typename t_Ty>
void fundamental_type_installer(Type* a_pType, uint step /*(not used)*/)
{
    o_assert(step == 0);
    currentModule()->addLanguageElement(a_pType);
}

void Types::Install()
{
    /// META-META-... TYPES :) (or type representation of the type representation of the type representation ... to INFINITY !
/*

#define o_create_meta_meta_type(_type_)\
    {_type_::metaType = new (o__t1_class__default_class_allocator(native::TType<_type_>)::allocate()) native::TType<_type_>;\
    native::TType<_type_>::metaType->install(_type_::metaType);\
    native::TType<_type_>::metaType->initialize(_type_::metaType);\
    Phantom::dynamic_initializer()->registerType("phantom::reflection::"#_type_, _type_::metaType); \
    phantom::detail::dynamic_initializer_module_installer_registrer< _type_, o_read_compilation_counter > register_meta_meta_type;}
*/

#define o_register_fundamental(type) \
    Phantom::dynamic_initializer()->registerType(#type, get<type>()); \
    Phantom::dynamic_initializer()->registerModule( get<type>(), fundamental_type_installer<type>, 0x1 );

    static bool installed = false;
    if(installed) return;
    installed = true;
    
    Class::metaType = nullptr;
    type_of<Class>::object();
    Enum::metaType = type_of<Enum>::object();
    Type::metaType = type_of<Type>::object();
    PrimitiveType::metaType = type_of<PrimitiveType>::object();
    PointerType::metaType = type_of<PointerType>::object();
    DataPointerType::metaType = type_of<DataPointerType>::object();
    ReferenceType::metaType = type_of<ReferenceType>::object();
    ArrayType::metaType = type_of<ArrayType>::object();
    ClassType::metaType = type_of<ClassType>::object();
    Union::metaType = type_of<Union>::object();
    PODUnion::metaType = type_of<PODUnion>::object();
    PODStruct::metaType = type_of<PODStruct>::object();
    ConstDataPointerType::metaType = type_of<ConstDataPointerType>::object();
    ConstArrayType::metaType = type_of<ConstArrayType>::object();
    ConstReferenceType::metaType = type_of<ConstReferenceType>::object();
    ContainerClass::metaType = type_of<ContainerClass>::object();
    MapContainerClass::metaType = type_of<MapContainerClass>::object();
    SequentialContainerClass::metaType = type_of<SequentialContainerClass>::object();
    SetContainerClass::metaType = type_of<SetContainerClass>::object();

#define o_build_fundamental_meta_type(_var_, _type_)\
    _var_ = new (o__t1_class__default_class_allocator(meta_class_type_of<_type_>::type)::allocate()) meta_class_type_of<_type_>::type;\
    meta_class_type_of<_type_>::type::metaType->install(_var_);\
    meta_class_type_of<_type_>::type::metaType->initialize(_var_);\

    Phantom::dynamic_initializer()->setActive(true);
    o_build_fundamental_meta_type(VOID, void);
    o_build_fundamental_meta_type(CHAR, char);
    o_build_fundamental_meta_type(UNSIGNED_CHAR, unsigned char);
    o_build_fundamental_meta_type(SIGNED_CHAR, signed char);
    o_build_fundamental_meta_type(SHORT, short);
    o_build_fundamental_meta_type(UNSIGNED_SHORT, unsigned short);
    o_build_fundamental_meta_type(INT, int);
    o_build_fundamental_meta_type(UNSIGNED_INT, unsigned int);
    o_build_fundamental_meta_type(LONG, long);
    o_build_fundamental_meta_type(UNSIGNED_LONG, unsigned long);
    o_build_fundamental_meta_type(LONG_LONG, long long);
    o_build_fundamental_meta_type(UNSIGNED_LONG_LONG, unsigned long long);
    o_build_fundamental_meta_type(FLOAT, float);
    o_build_fundamental_meta_type(DOUBLE, double);
    o_build_fundamental_meta_type(LONG_DOUBLE, long double);
    o_build_fundamental_meta_type(BOOL, bool);
    STRING = type_of<string>::object();
    SIGNAL_T = type_of<phantom::signal_t>::object();
#if o_BUILT_IN_WCHAR_T == 1
    o_build_fundamental_meta_type(WCHAR_T, wchar_t);
#else
        WCHAR_T = Types::UNSIGNED_SHORT;
#endif
    VOID_PTR = VOID->pointerType();


    Phantom::dynamic_initializer()->setActive(false);
}

void Types::Register()
{
    Phantom::dynamic_initializer()->setActive(true);
    currentInstalledTemplateSpecialization = 0;
    currentInstalledNamespace = 0;
    currentInstalledClass = 0;

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
    Phantom::dynamic_initializer()->setActive(false);
    
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
}

phantom::reflection::TemplateSpecialization* Types::currentInstalledTemplateSpecialization;

phantom::reflection::Namespace* Types::currentInstalledNamespace;

phantom::reflection::Class* Types::currentInstalledClass;

Type* Types::VOID = nullptr;
Type* Types::CHAR = nullptr;
Type* Types::UNSIGNED_CHAR = nullptr;
Type* Types::SIGNED_CHAR = nullptr;
Type* Types::SHORT = nullptr;
Type* Types::UNSIGNED_SHORT = nullptr;
Type* Types::INT = nullptr;
Type* Types::UNSIGNED_INT = nullptr;
Type* Types::LONG = nullptr;
Type* Types::UNSIGNED_LONG = nullptr;
Type* Types::LONG_LONG = nullptr;
Type* Types::UNSIGNED_LONG_LONG = nullptr;
Type* Types::FLOAT = nullptr;
Type* Types::DOUBLE = nullptr;
Type* Types::LONG_DOUBLE = nullptr;
Type* Types::BOOL = nullptr;
Type* Types::STRING = nullptr;
Type* Types::SIGNAL_T = nullptr;
Type* Types::WCHAR_T = 
#if o_BUILT_IN_WCHAR_T == 1
    nullptr;
#else
    Types::UNSIGNED_SHORT;
#endif
Type* Types::VOID_PTR = nullptr;
    
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

o_export void initializeSystem()
{
    /// Install pre defined and convenient types
    phantom::reflection::Types::Install();
    phantom::reflection::Types::Register();
}

o_namespace_end(phantom, reflection)




