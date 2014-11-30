#include "phantom/phantom.h"

#include "phantom/reflection/Expression.h"

// Fundamental expressions
#include "phantom/reflection/AssignmentExpression.h"
#include "phantom/reflection/UnaryLogicalExpression.h"
#include "phantom/reflection/BinaryLogicalExpression.h"
#include "phantom/reflection/TUnaryBitExpression.h"
#include "phantom/reflection/TBinaryBitExpression.h"
#include "phantom/reflection/TBinaryIntegralExpression.h"
#include "phantom/reflection/TUnaryArithmeticExpression.h"
#include "phantom/reflection/TBinaryArithmeticExpression.h"
#include "phantom/reflection/TEqualityExpression.h"
#include "phantom/reflection/TBinaryBooleanExpression.h"
#include "phantom/reflection/TPreIncrementExpression.h"
#include "phantom/reflection/TPostIncrementExpression.h"
#include "phantom/reflection/TShiftExpression.h"
#include "phantom/reflection/DataExpression.h"

o_enumN((phantom, reflection), EABI)(e_ABI_stdcall,
    e_ABI_fastcall,
    e_ABI_cdecl,
    e_ABI_thiscall);

o_registerN((phantom, reflection), EABI);

o_namespace_begin(phantom, reflection, native)

template<typename t_Ty>
class TFundamentalType : public TPrimitiveType<t_Ty>
{
public:
    TFundamentalType(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0)
        : TPrimitiveType<t_Ty>(a_strName, a_uiSize, a_uiAlignment, a_Modifiers) {}

    virtual PrimitiveType* asFundamentalType() const { return (PrimitiveType*)this; }

};

template<typename t_Ty>
class TArithmeticType : public TFundamentalType<t_Ty>
{
public:
    TArithmeticType(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0)
        : TFundamentalType<t_Ty>(a_strName, a_uiSize, a_uiAlignment, a_Modifiers) {}

    virtual PrimitiveType* asArithmeticType() const { return (PrimitiveType*)this; }

    virtual Expression* solveOperator(const string& a_strOp, const vector<Expression*>& a_Expressions, modifiers_t a_Modifiers) const
    {
        o_assert(a_Expressions.size());
        o_assert(a_Expressions[0]->getValueType()->isImplicitlyConvertibleTo(const_cast<TArithmeticType<t_Ty>*>(this)));
        if(a_Expressions.size() == 2)
        {
            if(a_strOp.size() == 2)
            {
                if(a_strOp == "==" OR a_strOp == "!=")
                {
                    return o_new(TEqualityExpression<t_Ty>)(a_strOp, a_Expressions[0], a_Expressions[1]);
                }
                else if(a_strOp[1] == '=') // Assignment operation or equality test
                {
                    Expression* pSubExpression = nullptr;
                    switch(a_strOp[0])
                    {
                    case '+':
                    case '-':
                    case '*':
                    case '/':
                        pSubExpression = o_new(TBinaryArithmeticExpression<t_Ty>)(a_strOp.substr(0, 1), a_Expressions[0], a_Expressions[1]);
                        break;

                    case '=':
                    case '!':
                    case '<':
                    case '>':
                        return o_new(TBinaryBooleanExpression<t_Ty>)(a_strOp, a_Expressions[0], a_Expressions[1]);

                    }
                    if(pSubExpression)
                    {
                        return o_new(AssignmentExpression)(a_Expressions[0], pSubExpression);
                    }
                }
            }
            else if(a_strOp.size() == 1)
            {
                switch(a_strOp[0])
                {
                case '=':
                    {
                        return o_new(AssignmentExpression)(a_Expressions[0], a_Expressions[1]);
                    }
                case '+':
                case '-':
                case '*':
                case '/':
                    {
                        return o_new(TBinaryArithmeticExpression<t_Ty>)(a_strOp, a_Expressions[0], a_Expressions[1]);
                    }
                case '<':
                case '>':
                    {
                        return o_new(TBinaryBooleanExpression<t_Ty>)(a_strOp, a_Expressions[0], a_Expressions[1]);
                    }
                }
            }
        }
        else if(a_Expressions.size() == 1)
        {
            if(a_strOp.size() == 1)
            {
                if(a_strOp[0] == '+' OR a_strOp[0] == '-')
                {
                    return o_new(TUnaryArithmeticExpression<t_Ty>)(a_strOp, a_Expressions[0]);
                }
            }
        }
        return TFundamentalType<t_Ty>::solveOperator(a_strOp, a_Expressions, a_Modifiers);
    }
};

template<typename t_Ty>
class TFloatingPointType : public TArithmeticType<t_Ty>
{
public:
    TFloatingPointType(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0)
        : TArithmeticType<t_Ty>(a_strName, a_uiSize, a_uiAlignment, a_Modifiers) {}

    virtual PrimitiveType* asFloatingPointType() const { return (PrimitiveType*)this; }
};

template<typename t_Ty>
class TIntegralType : public TArithmeticType<t_Ty>
{
public:
    TIntegralType(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0)
        : TArithmeticType<t_Ty>(a_strName, a_uiSize, a_uiAlignment, a_Modifiers) {}

    virtual PrimitiveType* asIntegralType() const { return (PrimitiveType*)this; }

    virtual Expression* solveOperator(const string& a_strOp, const vector<Expression*>& a_Expressions, modifiers_t a_Modifiers) const
    {
        o_assert(a_Expressions.size());
        o_assert(a_Expressions[0]->getValueType()->isImplicitlyConvertibleTo((Type*)this));
        if(a_strOp.size() == 3)
        {
            if((a_strOp == ">>=" OR a_strOp == "<<=") AND a_Expressions.size() == 2)
            {
                return o_new(AssignmentExpression)(a_Expressions[0], o_new(TShiftExpression<t_Ty>)(a_strOp, a_Expressions[0], a_Expressions[1]));
            }
        }
        else if(a_strOp.size() == 2)
        {
            if(a_Expressions.size() == 2)
            {
                if(a_strOp == "&&" OR a_strOp == "||")
                {
                    return o_new(BinaryLogicalExpression)(a_strOp, a_Expressions[0], a_Expressions[1]);
                }
                else if(a_strOp == "++" OR a_strOp == "--")
                {
                    if(a_Expressions[0]->getValueType() == referenceType())
                    {
                        return o_new(TPostIncrementExpression<t_Ty>)(a_strOp, a_Expressions[0]);
                    }
                }
                else if(a_strOp == ">>" OR a_strOp == "<<")
                {
                    return o_new(TShiftExpression<t_Ty>)(a_strOp, a_Expressions[0], a_Expressions[1]);
                }
                else if(a_strOp[1] == '=') // Assignment operation
                {
                    Expression* pSubExpression = nullptr;
                    switch(a_strOp[0])
                    {
                    case '|':
                    case '&':
                    case '^':
                        pSubExpression = o_new(TBinaryBitExpression<t_Ty>)(a_strOp.substr(0, 1), a_Expressions[0], a_Expressions[1]);
                        break;

                    case '%':
                        pSubExpression = o_new(TBinaryIntegralExpression<t_Ty>)(a_strOp.substr(0, 1), a_Expressions[0], a_Expressions[1]);
                        break;
                    }
                    if(pSubExpression)
                    {
                        return o_new(AssignmentExpression)(a_Expressions[0], pSubExpression);
                    }
                }
            }
            else
            {
                if(a_strOp == "++" OR a_strOp == "--")
                {
                    if(a_Expressions[0]->getValueType() == referenceType())
                    {
                        return o_new(TPreIncrementExpression<t_Ty>)(a_strOp, a_Expressions[0]);
                    }
                }
            }
        }
        else if(a_strOp.size() == 1)
        {
            if(a_Expressions.size() == 2)
            {
                if(a_strOp[0] == '&' OR a_strOp[0] == '|' OR a_strOp[0] == '^')
                {
                    return o_new(TBinaryBitExpression<t_Ty>)(a_strOp, a_Expressions[0], a_Expressions[1]);
                }
                else if(a_strOp[0] == '%')
                {
                    return o_new(TBinaryIntegralExpression<t_Ty>)(a_strOp, a_Expressions[0], a_Expressions[1]);
                }
            }
            else if(a_Expressions.size() == 1)
            {
                if(a_strOp[0] == '!' )
                {
                    return o_new(UnaryLogicalExpression)(a_strOp, a_Expressions[0]);
                }
                else if(a_strOp[0] == '~')
                {
                    return o_new(TUnaryBitExpression<t_Ty>)(a_strOp, a_Expressions[0]);
                }
                else if(a_strOp[0] == '@')
                {
                    if(phantom::getCurrentDataBase())
                    {
                        return o_new(DataExpression)(phantom::getCurrentDataBase(), a_Expressions.back());
                    }
                }
            }
        }
        return TArithmeticType<t_Ty>::solveOperator(a_strOp, a_Expressions, a_Modifiers);
    }

};
o_namespace_end(phantom, reflection, native)

/// META META TYPES
#include "phantom/reflection/VirtualMemberFunctionTable.hxx"
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
#include "phantom/reflection/Structure.hxx"
#include "phantom/reflection/ContainerClass.hxx"
#include "phantom/reflection/ConstType.hxx"
#include "phantom/reflection/MapContainerClass.hxx"
#include "phantom/reflection/SequentialContainerClass.hxx"
#include "phantom/reflection/SetContainerClass.hxx"
#include "phantom/std/string.h"
#include "phantom/std/string.hxx"

o_static_assert((boost::is_same<phantom::reflection::ClassType, phantom::base_class_of<phantom::reflection::Class, 0>::type>::value));
o_static_assert(boost::is_polymorphic<phantom::reflection::ClassType>::value);
o_static_assert(!phantom::has_new_vtable<phantom::reflection::Class>::value);


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


#define o_register_fundamental(type) \
    dynamic_initializer()->registerType(#type, get<type>()); \
    dynamic_initializer()->registerModule( get<type>(), fundamental_type_installer<type>, 0x1 );

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
    ReferenceType::metaType = type_of<ReferenceType>::object();
    ArrayType::metaType = type_of<ArrayType>::object();
    ClassType::metaType = type_of<ClassType>::object();
    Union::metaType = type_of<Union>::object();
    PODUnion::metaType = type_of<PODUnion>::object();
    Structure::metaType = type_of<Structure>::object();
    ConstType::metaType = type_of<ConstType>::object();
    ContainerClass::metaType = type_of<ContainerClass>::object();
    MapContainerClass::metaType = type_of<MapContainerClass>::object();
    SequentialContainerClass::metaType = type_of<SequentialContainerClass>::object();
    SetContainerClass::metaType = type_of<SetContainerClass>::object();

#define o_build_fundamental_meta_type(_var_, _type_)\
    _var_ = o_dynamic_proxy_new(meta_class_type_of<_type_>::type)(typeNameOf<_type_>());\

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
#if o_HAS_BUILT_IN_WCHAR_T == 1
    o_build_fundamental_meta_type(TYPE_WCHAR_T, wchar_t);
#else
        TYPE_WCHAR_T = Types::TYPE_UNSIGNED_SHORT;
#endif
    TYPE_VOID_PTR = TYPE_VOID->pointerType();


    dynamic_initializer()->setActive(false);
}

void Types::Register()
{
    dynamic_initializer()->setActive(true);
    currentInstalledTemplateSpecialization = 0;
    currentInstalledNamespace = 0;
    currentInstalledClass = 0;
    currentModifiers = 0;

    o_register_fundamental(char);
#if o_HAS_BUILT_IN_WCHAR_T
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
    dynamic_initializer()->registerType("std::nullptr_t", "std", get<std::nullptr_t>());
    dynamic_initializer()->registerModule( get<std::nullptr_t>(), fundamental_type_installer<std::nullptr_t>, 0x1 );
    dynamic_initializer()->setActive(false);

    o_typedef(size_t);

    o_typedefN((phantom), uchar);
    o_typedefN((phantom), schar);
    o_typedefN((phantom), ushort);
    o_typedefN((phantom), uint);
    o_typedefN((phantom), ulong);
    o_typedefN((phantom), longlong);
    o_typedefN((phantom), ulonglong);
    o_typedefN((phantom), longdouble);
    o_typedefN((phantom), character);
    o_typedefN((phantom), byte);
    o_typedefN((phantom), boolean);
    o_typedefN((phantom), int8);
    o_typedefN((phantom), int16);
    o_typedefN((phantom), int32);
    o_typedefN((phantom), int64);
    o_typedefN((phantom), uint8);
    o_typedefN((phantom), uint16);
    o_typedefN((phantom), uint32);
    o_typedefN((phantom), uint64);
    o_typedefN((phantom), sint8);
    o_typedefN((phantom), sint16);
    o_typedefN((phantom), sint32);
    o_typedefN((phantom), sint64);
    o_typedefN((phantom), real);
}

phantom::modifiers_t Types::currentModifiers;

phantom::reflection::TemplateSpecialization* Types::currentInstalledTemplateSpecialization;

phantom::reflection::ClassType* Types::currentInstalledClass;

phantom::reflection::AnonymousSection* Types::currentInstalledAnonymousSection;

phantom::reflection::Namespace* Types::currentInstalledNamespace;

phantom::reflection::TemplateSpecialization* Types::savedInstalledTemplateSpecialization;

phantom::reflection::ClassType* Types::savedInstalledClass;

phantom::modifiers_t Types::savedModifiers;

phantom::reflection::Namespace* Types::savedInstalledNamespace;

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
Type* Types::TYPE_VOID_PTR = nullptr;

namespace_alias_registrer::namespace_alias_registrer( const char* a_strNamespace, const char* a_strAlias, const char* a_strAliasedNamespace )
{
    dynamic_initializer()->setActive(true);
    Namespace* pNamespace = phantom::rootNamespace()->findOrCreateNamespaceCascade(a_strNamespace);
    Namespace* pAliasedNamespace = phantom::rootNamespace()->findOrCreateNamespaceCascade(a_strAliasedNamespace);
    pNamespace->addNamespaceAlias(a_strAlias, pAliasedNamespace);
    dynamic_initializer()->setActive(false);
}

namespace_alias_registrer::namespace_alias_registrer( const char* a_strAlias, const char* a_strAliasedNamespace )
{
    dynamic_initializer()->setActive(true);
    phantom::rootNamespace()->addNamespaceAlias(a_strAlias, phantom::rootNamespace()->findOrCreateNamespaceCascade(a_strAliasedNamespace));
    dynamic_initializer()->setActive(false);
}

namespace_registrer::namespace_registrer( const char* a_strNamespace )
{
    dynamic_initializer()->setActive(true);
    phantom::rootNamespace()->findOrCreateNamespaceCascade(a_strNamespace);
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
    o_assert(pWhere);
    LanguageElement* pElement = elementByName(a_strElement, pWhere);
    o_assert(pElement);
    pWhere->addUsing(pElement);
}

friend_registrer::friend_registrer( const char* a_strWhere, const char* a_strFriend )
{
    LanguageElement* pWhere = elementByName(a_strWhere);
    o_assert(pWhere);
    LanguageElement* pElement = elementByName(a_strFriend, pWhere);
    o_assert(pElement);
    pWhere->addFriend(pElement);
}

o_namespace_end(phantom, reflection)





