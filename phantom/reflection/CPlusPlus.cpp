/* ******************* Includes ****************** */
#include "phantom/phantom.h"
// #define o_USE_BOOST_SPIRIT_CPLUSPLUS_PARSER // uncomment to disable parser
#include "phantom/reflection/Expression.h"
#include "CPlusPlus.h"
#include "CPlusPlus.hxx"
// 
// #include "detail/CxxLexer.h"
// #include "detail/CxxParser.h"
// #include "detail/CxxDriver.h"
// #include "detail/CxxTokenizer.h"

#include <phantom/reflection/native/TFundamentals.h>
#include <phantom/reflection/Application.h>
#include <phantom/reflection/Source.h>
#include <phantom/reflection/Import.h>
#include <phantom/reflection/Package.h>
#include <phantom/reflection/Placeholder.h>
#include <phantom/reflection/BuiltInOperator.h>
#include <phantom/reflection/ConstructorCallExpression.h>
#include <phantom/reflection/LocalVariableExpression.h>
#include <phantom/reflection/VariableExpression.h>
#include <phantom/reflection/PointerAdjustmentExpression.h>
#include <phantom/reflection/BuiltInOperatorExpression.h>
#include <phantom/reflection/DataMemberPointerAdjustmentExpression.h>
#include <phantom/reflection/MemberFunctionPointerAdjustmentExpression.h>
#include <phantom/reflection/RValueExpression.h>
#include <phantom/reflection/LoadExpression.h>
#include <phantom/reflection/PropertyExpression.h>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/ConstantExpression.h>
#include <phantom/reflection/Block.h>
#include <phantom/reflection/LocalVariable.h>
#include <phantom/reflection/DataExpression.h>
#include <phantom/reflection/StringLiteralExpression.h>
#include <phantom/reflection/ConditionalExpression.h>
#include <phantom/reflection/PlacementConstructionExpression.h>
#include <phantom/reflection/DataMemberExpression.h>
#include <phantom/reflection/CallExpression.h>
#include <phantom/reflection/BuiltInConversionExpression.h>
#include <phantom/reflection/MemberFunctionPointerCallExpression.h>
#include <phantom/reflection/DataMemberPointerExpression.h>
#include <phantom/reflection/MemberFunctionPointerType.h>
#include <phantom/reflection/DataMemberPointerType.h>
#include <phantom/reflection/Enum.h>
#include <phantom/reflection/NumericConstant.h>
#include <phantom/reflection/LabelStatement.h>
#include <phantom/reflection/BranchIfStatement.h>
#include <phantom/reflection/BranchIfNotStatement.h>
#include <phantom/reflection/BranchStatement.h>
#include <phantom/reflection/Constant.h>
#include <phantom/reflection/Statement.h>
#include <phantom/reflection/ExpressionStatement.h>
#include <phantom/reflection/LocalVariableInitializationStatement.h>
#include <phantom/reflection/ReturnStatement.h>
#include <phantom/reflection/TDBinaryOperationExpression.h>
#include <phantom/reflection/TDUnaryPreOperationExpression.h>
#include <phantom/reflection/TDunaryPostOperationExpression.h>
#include <phantom/reflection/Parameter.h>
#include <phantom/reflection/AggregationClass.h>
#include <phantom/reflection/CompositionClass.h>
#include <phantom/reflection/CommaExpression.h>
#include <boost/algorithm/string.hpp>
/* *********************************************** */

#include <stdio.h>

#pragma warning(disable:4800)
#pragma warning(disable:4244)

o_registerN((phantom, reflection), CPlusPlus);

o_namespace_begin(phantom, reflection)


static const char* _canBe = "can be";
static const char* _or = "or";

#define o_semantic_error(a)  do { if(a_Data.flags & 0x1) std::cout << "error : semantic : " << a << std::endl; } while (0)
#define o_semantic_suberror(a)  do { if(a_Data.flags & 0x1) std::cout << "    " << a << std::endl; } while (0)


string formatIndexString(string a_Input, size_t a_CharCount = 10)
{
    long long value_t = 0;
    if(sscanf(a_Input.c_str(), "%d", &value_t))
    {
        while(a_Input.size() < a_CharCount)
        {
            a_Input = ' ' + a_Input;
        }
    }
    return a_Input;
}

CPlusPlus::CPlusPlus( const char* a_ScopeDelimiter )
    : m_ScopeDelimiter(a_ScopeDelimiter)
{
}

CPlusPlus::~CPlusPlus( void )
{
}
// 
// void CPlusPlus::translate( NamedElement* a_pElement, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pElement, translation);
// }
// 
// void CPlusPlus::translate( Namespace* a_pNamespace, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pNamespace, translation);
// }
// 
// void CPlusPlus::translate( Type* a_pType, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pType, translation);
// }
// 
// void CPlusPlus::translate( PrimitiveType* a_pType, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pType, translation);
// }
// 
// void CPlusPlus::translate(FunctionPointerType* a_pType, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pType, translation);
// }
// 
// void CPlusPlus::translate(MemberFunctionPointerType* a_pType, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pType, translation);
// }
// 
// void CPlusPlus::translate(DataMemberPointerType* a_pType, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pType, translation);
// }
// 
// void CPlusPlus::translate(DataPointerType* a_pType, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pType, translation);
// }
// 
// void CPlusPlus::translate(LValueReferenceType* a_pType, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pType, translation);
// }
// 
// void CPlusPlus::translate(ConstType* a_pType, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pType, translation);
// }
// 
// void CPlusPlus::translate(ArrayType* a_pType, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pType, translation);
// }
// 
// void CPlusPlus::translate( Enum* a_pEnum, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pEnum, translation);
// }
// 
// void CPlusPlus::translate( ClassType* a_pClassType, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pClassType, translation);
// }
// 
// void CPlusPlus::translate( Class* a_pClass, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pClass, translation);
// }
// 
// void CPlusPlus::translate( Structure* a_pStructure, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pStructure, translation);
// }
// 
// void CPlusPlus::translate( Union* a_pUnion, string& translation, int options /*= 0*/ )
// {
//     qualifiedDecoratedName(a_pUnion, translation);
// }
// 
// void CPlusPlus::translate( AnonymousSection* a_pAnonymousSection, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pAnonymousSection, translation);
// }
// 
// void CPlusPlus::translate( AnonymousStruct* a_pAnonymousStruct, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pAnonymousStruct, translation);
// }
// 
// void CPlusPlus::translate( AnonymousUnion* a_pAnonymousUnion, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pAnonymousUnion, translation);
// }
// 
// void CPlusPlus::translate( Template* a_pTemplate, string& translation, int options /*= 0*/ )
// {
//     qualifiedDecoratedName(a_pTemplate, translation);
// }
// 
// void CPlusPlus::translate( TemplateSpecialization* a_pTemplateSpecialization, string& translation, int options /*= 0*/ )
// {
//     qualifiedDecoratedName(a_pTemplateSpecialization, translation);
// }
// 
// void CPlusPlus::translate( Subroutine* a_pSubroutine, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pSubroutine, translation);
// }
// 
// void CPlusPlus::translate( Constructor* a_pConstructor, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pConstructor, translation);
// }
// 
// void CPlusPlus::translate( Function* a_pFunction, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pFunction, translation);
// }
// 
// void CPlusPlus::translate( MemberFunction* a_pMemberFunction, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pMemberFunction, translation);
// }
// 
// void CPlusPlus::translate( Signal* a_pSignal, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pSignal, translation);
// }
// 
// void CPlusPlus::translate( Variable* a_pVariable, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pVariable, translation);
// }
// 
// void CPlusPlus::translate( DataMember* a_pDataMember, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pDataMember, translation);
// }
// 
// void CPlusPlus::translate( Property* a_pProperty, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pProperty, translation);
// }
// 
// void CPlusPlus::translate( StateMachine* a_pStateMachine, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pStateMachine, translation);
// }
// 
// void CPlusPlus::translate( State* a_pState, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pState, translation);
// }
// 
// void CPlusPlus::translate( Track* a_pTrack, string& translation, int options )
// {
//     qualifiedDecoratedName(a_pTrack, translation);
// }
// 
// void CPlusPlus::translate( Block* a_pBlock, string& translation, int options )
// {
// 
// }
// 
// 
// void CPlusPlus::translate( BranchStatement* a_pBranchStatement, string& translation, int options )
// {
// }
// 
// void CPlusPlus::translate( BranchIfStatement* a_pBranchIfStatement, string& translation, int options )
// {
// }
// 
// void CPlusPlus::translate( BranchIfNotStatement* a_pBranchIfNotStatement, string& translation, int options )
// {
// }
// 
// void CPlusPlus::translate( ExpressionStatement* a_pExpressionStatement, string& translation, int options )
// {
// }
// 
// void CPlusPlus::translate( ReturnStatement* a_pReturnStatement, string& translation, int options )
// {
// }
// 
// void CPlusPlus::translate( LabelStatement* a_pLabelStatement, string& translation, int options )
// {
// }
// 
// // Expressions
// 
// 
// void CPlusPlus::translate( VariableExpression* a_pVariableExpression, string& translation, int options )
// {
//     qualifiedDecoratedName(, translation);
// }
// 
void CPlusPlus::translateLiteral(const string& a_Value, string& translation, int options)
{
    translation += "\"";
    for(auto it = a_Value.begin(); it != a_Value.end(); ++it)
    {
        switch(*it)
        {
        case '"':  translation += "\\\""; break;
        case '\\': translation += "\\\\"; break;
        case '\n': translation += "\\n" ; break;
        case '\r': translation += "\\r" ; break;
        case '\t': translation += "\\t" ; break;
        case '\0': translation += "\\0" ; break;
        default:
            translation += *it;
        }
    }
    translation += "\"";
}
// 
// void CPlusPlus::translate( CompositionGetSetExpression* a_pCompositionGetSetExpression, string& translation, int options /*= 0*/ )
// {
//     translation += '(';
//     translateTo(a_pCompositionGetSetExpression->getLeftExpression(), translation, options);
//     translation += ")[";
//     string index;
//     translateTo(a_pCompositionGetSetExpression->getIndexExpression(), index);
//     translation += (options & e_TranslationOption_FixedSizeIndexes) ? formatIndexString(index) : index;
//     translation += ']';
// }
// 
// void CPlusPlus::translate( AggregationGetSetExpression* a_pAggregationGetSetExpression, string& translation, int options /*= 0*/ )
// {
//     translation += '(';
//     translateTo(a_pAggregationGetSetExpression->getLeftExpression(), translation, options);
//     translation += ")[";
//     string index;
//     translateTo(a_pAggregationGetSetExpression->getIndexExpression(), index);
//     translation += (options & e_TranslationOption_FixedSizeIndexes) ? formatIndexString(index) : index;
//     translation += ']';
// }
// 
// void CPlusPlus::translate( CompositionInsertRemoveExpression* a_pCompositionInsertRemoveExpression, string& translation, int options /*= 0*/ )
// {
//     translation += '(';
//     translateTo(a_pCompositionInsertRemoveExpression->getLeftExpression(), translation, options);
//     translation += ")(";
//     string index;
//     translateTo(a_pCompositionInsertRemoveExpression->getIndexExpression(), index);
//     translation += (options & e_TranslationOption_FixedSizeIndexes) ? formatIndexString(index) : index;
//     translation += ')';
// }
// 
// void CPlusPlus::translate( AggregationInsertRemoveExpression* a_pAggregationInsertRemoveExpression, string& translation, int options /*= 0*/ )
// {
//     translation += '(';
//     translateTo(a_pAggregationInsertRemoveExpression->getLeftExpression(), translation, options);
//     translation += ")(";
//     string index;
//     translateTo(a_pAggregationInsertRemoveExpression->getIndexExpression(), index);
//     translation += (options & e_TranslationOption_FixedSizeIndexes) ? formatIndexString(index) : index; 
//     translation += ')';
// }
// 
// void CPlusPlus::translate( Constant* a_pConstant, string& translation, int options )
// {
//     a_pConstant->toString(translation);
// }

LanguageElement* CPlusPlus::elementByName( const string& a_strName, LanguageElement* a_pScope /*= globalNamespace()*/, modifiers_t a_Modifiers /*= 0*/ ) const
{
    string elementByNameScopeToDots = a_strName;
    boost::replace_all(elementByNameScopeToDots, "::", "."); /// we replace every "::" by a '.' as shaman works with '.' scopes
    return shaman()->internalElementByName(true, elementByNameScopeToDots, a_pScope, a_Modifiers);
}


/// CONVERSION



struct constref_conversion;
struct lvalue_transformation;
struct qualification_adjustment;
struct standard_conversion;
struct standard_conversion_sequence;
struct numeric_conversion;
struct user_defined_conversion;

struct default_conversion_sequence : public conversion
{
    /// STANDARD CONVERSION ONLY
    default_conversion_sequence(value_t io, bool a_bEllipsis = false);  /// identity or ellipsis

    default_conversion_sequence(value_t i, value_t o, int a_iPlaceholding = 0); /// reinterpret_cast or placeholding

    default_conversion_sequence(constref_conversion* cr);

    default_conversion_sequence(lvalue_transformation* lvt);

    default_conversion_sequence(lvalue_transformation* lvt, qualification_adjustment* qa, constref_conversion* cr = 0);

    default_conversion_sequence(lvalue_transformation* lvt, numeric_conversion* nc, constref_conversion* cr = 0);

    default_conversion_sequence(lvalue_transformation* lvt, numeric_conversion* nc, qualification_adjustment* qa, constref_conversion* cr = 0);

    default_conversion_sequence(numeric_conversion* nc, qualification_adjustment* qa, constref_conversion* cr = 0);

    default_conversion_sequence(numeric_conversion* nc, constref_conversion* cr = 0);

    default_conversion_sequence(qualification_adjustment* qa, constref_conversion* cr = 0);

    default_conversion_sequence(standard_conversion_sequence* s1);

    /// + opt[USER DEFINED] + opt[STANDARD CONVERSION]
    default_conversion_sequence(standard_conversion_sequence* s1, user_defined_conversion* ud);
    default_conversion_sequence(user_defined_conversion* ud);
    standard_conversion_sequence*   m_standard;
    user_defined_conversion*        m_user_defined;
    bool m_ellipsis;
    int m_placeholding;

    virtual void apply(const void* a_pInput, void* a_pOutput) const;

    void addConstRef();
    void addLValueTransform();
    void addUserDefinedByConstruction(Constructor* a_pConstructor);
    void addUserDefinedByConversionFunction(MemberFunction* a_pConversionFunction);

    int compare(const default_conversion_sequence& other) const;

    virtual int compare(const conversion& other) const { return compare((const default_conversion_sequence&)other); }

    virtual default_conversion_sequence* clone() const;

    virtual Expression* convert(Expression* a_pExpression) const;

};

struct standard_conversion_sequence : public conversion
{
    /// int -> int const ?
    standard_conversion_sequence( value_t i, value_t o );

    /// int -> int
    standard_conversion_sequence(value_t io);

    /// int -> int const&
    standard_conversion_sequence(constref_conversion* cr);

    /// int& -> int 
    standard_conversion_sequence(lvalue_transformation* lt);

    /// int*& -> int* -> int const* (-> int const* const&)
    standard_conversion_sequence(lvalue_transformation* lt, qualification_adjustment* qa, constref_conversion* cr = 0);

    /// int& -> int -> float (-> float const&) || Derived*& -> Derived* -> Base* (-> Base* const&)
    standard_conversion_sequence(lvalue_transformation* lt, numeric_conversion* nc, constref_conversion* cr = 0);

    /// Derived*& -> Derived* -> Base* -> Base const* (-> Base const* const&)
    standard_conversion_sequence(lvalue_transformation* lt, numeric_conversion* nc, qualification_adjustment* qa, constref_conversion* cr = 0);

    /// Derived* -> Base* -> Base const* (-> Base const* const&)
    standard_conversion_sequence(numeric_conversion* nc, qualification_adjustment* qa, constref_conversion* cr = 0);

    /// int -> float -> const float& || Derived* -> Base* -> Base* const&
    standard_conversion_sequence(numeric_conversion* nc, constref_conversion* cr = 0);

    /// Class* -> Class const* -> Class const* const&
    standard_conversion_sequence(qualification_adjustment* qa, constref_conversion* cr = 0);

    lvalue_transformation*      m_lvalue_transformation;
    numeric_conversion* m_numeric_conversion;
    qualification_adjustment*   m_qualification_adjustment;
    constref_conversion*   m_const_ref;

    void addLValueTransform();

    void addConstRef();

    void apply(const void* a_pInput, void* a_pOutput) const;

    int compare(const standard_conversion_sequence& other) const;

    virtual standard_conversion_sequence* clone() const;

    virtual Expression* convert(Expression* a_pExpression) const;

};

struct standard_conversion : public conversion
{
    enum EType 
    {
        e_trivial_conversion,
        e_numeric_conversion,
        e_qualification_adjustment,
    };

    standard_conversion(value_t i, value_t o, EType t)
        : conversion(i, o)
        , type(t)
    {

    }
    EType type;
};

struct trivial_conversion : public standard_conversion
{
    trivial_conversion(value_t i, value_t o) : standard_conversion(i, o, e_trivial_conversion) {}

};

struct lvalue_transformation : public trivial_conversion
{
    lvalue_transformation(value_t ref) : trivial_conversion(ref, ref->removeReference()) {}

    virtual lvalue_transformation* clone() const;

    virtual void apply(const void* a_pInput, void* a_pOutput) const
    {
        output->copy(*(void**)a_pInput, a_pOutput);
    }
    virtual Expression* convert(Expression* a_pExpression) const 
    {
        return o_new(LoadExpression)(a_pExpression);
    }
};

struct constref_conversion : public trivial_conversion
{
    constref_conversion(value_t io)
        : trivial_conversion(io, io->constType()->lvalueReferenceType()) 
    {
        o_assert(input->isCopyable());
    }

    virtual void apply(const void* a_pInput, void* a_pOutput) const
    {
        *(void**)a_pOutput = (void*)a_pInput;
    }

    virtual Expression* convert(Expression* a_pExpression) const 
    {
        if(a_pExpression->getValueType()->asReferenceType()) 
            return a_pExpression;
        return o_new(RValueExpression)(a_pExpression);
    }

    virtual constref_conversion* clone() const;
};

struct numeric_conversion : public standard_conversion
{
    numeric_conversion(value_t i, value_t o, bool promotion = false, size_t pointerToPointerInheritanceLevel = 0) 
        : standard_conversion(i, o, e_numeric_conversion) {}

    int compare(const numeric_conversion& other) const 
    {
        if(promotion && !other.promotion) return 1;
        if(!promotion && other.promotion) return -1;

        ///  Conversion that involves pointer-to-bool, pointer-to-member to bool, or std::nullptr_t to bool conversion is worse than the one that doesn't
        bool ptobool = (output == Types::TYPE_BOOL) AND (input == Types::TYPE_NULLPTR_T OR input->getTypeId() == e_member_pointer OR input->getTypeId() == e_pointer);
        if(other.output == Types::TYPE_BOOL AND (other.input == Types::TYPE_NULLPTR_T OR other.input->getTypeId() == e_member_pointer OR other.input->getTypeId() == e_pointer))
        {
            if(!ptobool) return 1;
        }
        else 
        {
            if(ptobool) return -1;
        }
        if(pointerToPointerInheritanceLevel != ~size_t(0))
        {
            if(other.pointerToPointerInheritanceLevel != ~size_t(0))
            {
                return (pointerToPointerInheritanceLevel<other.pointerToPointerInheritanceLevel) - (pointerToPointerInheritanceLevel>other.pointerToPointerInheritanceLevel);
            }
            /// Conversion that converts pointer-to-derived to pointer-to-base is better than the conversion of pointer-to-derived to pointer-to-void, and conversion of pointer-to-base to void is better than pointer-to-derived to void.
            return 1;
        }
        else 
        {
            /// Conversion that converts pointer-to-derived to pointer-to-base is better than the conversion of pointer-to-derived to pointer-to-void, and conversion of pointer-to-base to void is better than pointer-to-derived to void.
            if(other.pointerToPointerInheritanceLevel != ~size_t(0))
            {
                return -1;
            }
        }
        return 0;
    }

    virtual numeric_conversion* clone() const;

    void apply(const void* a_pInput, void* a_pOutput) const 
    {
        memcpy(a_pOutput, a_pInput, std::min(input->getSize(), output->getSize()));
    }

    virtual Expression* convert(Expression* a_pExpression) const
    {
        return a_pExpression;
    }

    bool promotion;
    size_t pointerToPointerInheritanceLevel;
};

template<typename t_Input, typename t_Output, int t_iConversionType>
struct tnumeric_conversion;

template<typename t_Input, typename t_Output>
struct tnumeric_conversion<t_Input, t_Output, e_implicit_conversion> : public numeric_conversion
{
    tnumeric_conversion(bool promotion = false) : numeric_conversion(typeOf<t_Input>(), typeOf<t_Output>(), promotion) {}
    tnumeric_conversion(Type* a_pInput, Type* a_pOutput, bool promotion = false) : numeric_conversion(a_pInput, a_pOutput, promotion) {}
    virtual void apply(const void* a_pInput, void* a_pOutput) const 
    {
        *(t_Output*)a_pOutput = *(const t_Input*)a_pInput;
    }

    virtual Expression* convert(Expression* a_pExpression) const
    {
        return o_new(BuiltInConversionExpression)(a_pExpression, clone(), e_implicit_conversion);
    }

    virtual tnumeric_conversion<t_Input, t_Output, e_implicit_conversion>* clone() const { return new tnumeric_conversion<t_Input, t_Output, e_implicit_conversion>(input, output, promotion); }
};

template<typename t_Input, typename t_Output>
struct tnumeric_conversion<t_Input, t_Output, e_reinterpret_cast> : public numeric_conversion
{
    tnumeric_conversion(bool promotion = false) : numeric_conversion(typeOf<t_Input>(), typeOf<t_Output>(), promotion) {}
    tnumeric_conversion(Type* a_pInput, Type* a_pOutput, bool promotion = false) : numeric_conversion(a_pInput, a_pOutput, promotion) {}
    virtual void apply(const void* a_pInput, void* a_pOutput) const 
    {
        *(t_Output*)a_pOutput = reinterpret_cast<t_Output>(*(t_Input*)a_pInput);
    }

    virtual Expression* convert(Expression* a_pExpression) const
    {
        return o_new(BuiltInConversionExpression)(a_pExpression, clone(), e_reinterpret_cast);
    }

    virtual tnumeric_conversion<t_Input, t_Output, e_reinterpret_cast>* clone() const { return new tnumeric_conversion<t_Input, t_Output, e_reinterpret_cast>(input, output, promotion); }
};

/// C++11 allow identity reinterpret_cast, but every compiler is not c++11 compliant so we create a wrapper for those cases
#if !o_HAS_CPP11
template<typename t_Ty>
struct tnumeric_conversion<t_Ty, t_Ty, e_reinterpret_cast> : public numeric_conversion
{
    tnumeric_conversion(bool promotion = false) : numeric_conversion(typeOf<t_Ty>(), typeOf<t_Ty>(), promotion) {}
    tnumeric_conversion(Type* a_pInput, Type* a_pOutput, bool promotion = false) : numeric_conversion(a_pInput, a_pOutput, promotion) {}
    virtual void apply(const void* a_pInput, void* a_pOutput) const 
    {
        *(t_Ty*)a_pOutput = *(t_Ty*)a_pInput;
    }

    virtual Expression* convert(Expression* a_pExpression) const
    {
        return o_new(BuiltInConversionExpression)(a_pExpression, clone(), e_reinterpret_cast);
    }

    virtual tnumeric_conversion<t_Ty, t_Ty, e_reinterpret_cast>* clone() const { return new tnumeric_conversion<t_Ty, t_Ty, e_reinterpret_cast>(input, output, promotion); }
};
#endif

template<typename t_Input, typename t_Output>
struct tnumeric_conversion<t_Input, t_Output, e_static_cast> : public numeric_conversion
{
    tnumeric_conversion(bool promotion = false) : numeric_conversion(typeOf<t_Input>(), typeOf<t_Output>(), promotion) {}
    tnumeric_conversion(Type* a_pInput, Type* a_pOutput, bool promotion = false) : numeric_conversion(a_pInput, a_pOutput, promotion) {}
    virtual void apply(const void* a_pInput, void* a_pOutput) const 
    {
        *(t_Output*)a_pOutput = static_cast<t_Output>(*(t_Input*)a_pInput);
    }

    virtual Expression* convert(Expression* a_pExpression) const
    {
        return o_new(BuiltInConversionExpression)(a_pExpression, clone(), e_static_cast);
    }

    virtual tnumeric_conversion<t_Input, t_Output, e_static_cast>* clone() const { return new tnumeric_conversion<t_Input, t_Output, e_static_cast>(input, output, promotion); }
};


template<typename t_Input, typename t_Output>
struct tnumeric_conversion<t_Input, t_Output, e_explicit_cast> : public numeric_conversion
{
    tnumeric_conversion(bool promotion = false) : numeric_conversion(typeOf<t_Input>(), typeOf<t_Output>(), promotion) {}
    tnumeric_conversion(Type* a_pInput, Type* a_pOutput, bool promotion = false) : numeric_conversion(a_pInput, a_pOutput, promotion) {}
    virtual void apply(const void* a_pInput, void* a_pOutput) const 
    {
        *(t_Output*)a_pOutput = (t_Output)(*(t_Input*)a_pInput);
    }

    virtual Expression* convert(Expression* a_pExpression) const
    {
        return o_new(BuiltInConversionExpression)(a_pExpression, clone(), e_explicit_cast);
    }

    virtual tnumeric_conversion<t_Input, t_Output, e_explicit_cast>* clone() const { return new tnumeric_conversion<t_Input, t_Output, e_explicit_cast>(input, output, promotion); }
};

template<typename t_Output>
struct tnumeric_conversion<std::nullptr_t, t_Output, e_implicit_conversion> : public numeric_conversion
{
    tnumeric_conversion(bool promotion = false) : numeric_conversion(typeOf<std::nullptr_t>(), typeOf<t_Output>(), promotion) {}
    tnumeric_conversion(Type* a_pOutput, bool promotion = false) : numeric_conversion(typeOf<std::nullptr_t>(), a_pOutput, promotion) {}
    virtual void apply(const void* a_pInput, void* a_pOutput) const 
    {
        *(t_Output*)a_pOutput = nullptr;
    }

    virtual tnumeric_conversion<std::nullptr_t, t_Output, e_implicit_conversion>* clone() const { return new tnumeric_conversion<std::nullptr_t, t_Output, e_implicit_conversion>(output, promotion); }
};

template<typename t_Output>
struct tnumeric_conversion<std::nullptr_t, t_Output, e_static_cast> : public numeric_conversion
{
    tnumeric_conversion(bool promotion = false) : numeric_conversion(typeOf<std::nullptr_t>(), typeOf<t_Output>(), promotion) {}
    tnumeric_conversion(Type* a_pOutput, bool promotion = false) : numeric_conversion(typeOf<std::nullptr_t>(), a_pOutput, promotion) {}
    virtual void apply(const void* a_pInput, void* a_pOutput) const 
    {
        *(t_Output*)a_pOutput = static_cast<t_Output>(nullptr);
    }

    virtual tnumeric_conversion<std::nullptr_t, t_Output, e_static_cast>* clone() const { return new tnumeric_conversion<std::nullptr_t, t_Output, e_static_cast>(output, promotion); }
};

template<typename t_Output>
struct tnumeric_conversion<std::nullptr_t, t_Output, e_explicit_cast> : public numeric_conversion
{
    tnumeric_conversion(bool promotion = false) : numeric_conversion(typeOf<std::nullptr_t>(), typeOf<t_Output>(), promotion) {}
    tnumeric_conversion(Type* a_pOutput, bool promotion = false) : numeric_conversion(typeOf<std::nullptr_t>(), a_pOutput, promotion) {}
    virtual void apply(const void* a_pInput, void* a_pOutput) const 
    {
        *(t_Output*)a_pOutput = (t_Output)(nullptr);
    }

    virtual tnumeric_conversion<std::nullptr_t, t_Output, e_explicit_cast>* clone() const { return new tnumeric_conversion<std::nullptr_t, t_Output, e_explicit_cast>(output, promotion); }
};

template<typename t_Output>
struct tnumeric_conversion<std::nullptr_t, t_Output, e_reinterpret_cast> : public numeric_conversion
{
    tnumeric_conversion(bool promotion = false) : numeric_conversion(typeOf<std::nullptr_t>(), typeOf<t_Output>(), promotion) {}
    tnumeric_conversion(Type* a_pOutput, bool promotion = false) : numeric_conversion(typeOf<std::nullptr_t>(), a_pOutput, promotion) {}
    virtual void apply(const void* a_pInput, void* a_pOutput) const 
    {
        *(t_Output*)a_pOutput = reinterpret_cast<t_Output>(nullptr);
    }

    virtual tnumeric_conversion<std::nullptr_t, t_Output, e_reinterpret_cast>* clone() const { return new tnumeric_conversion<std::nullptr_t, t_Output, e_reinterpret_cast>(output, promotion); }
};

struct pointer_conversion : public numeric_conversion
{
    pointer_conversion(value_t i, value_t o, size_t inheritanceLevel = ~size_t(0), ptrdiff_t offset = 0) 
        : numeric_conversion(i, o, false, inheritanceLevel) 
        , offsetToBase(offset) {}
    virtual void apply(const void* a_pInput, void* a_pOutput) const
    {
        byte* inputValue = *(byte*const*)a_pInput;
        if(inputValue == 0) *(byte**)a_pOutput = 0;
        *(byte**)a_pOutput = *(byte*const*)a_pInput + offsetToBase;
    }

    virtual Expression* convert(Expression* a_pExpression) const;

    virtual pointer_conversion* clone() const { return new pointer_conversion(input, output, pointerToPointerInheritanceLevel, offsetToBase); }

    ptrdiff_t offsetToBase;
};

struct data_member_pointer_conversion : public numeric_conversion
{
    data_member_pointer_conversion(value_t i, value_t o, size_t inheritanceLevel = ~size_t(0), ptrdiff_t offset = 0) 
        : numeric_conversion(i, o, false, inheritanceLevel) 
        , offsetToBase(offset) {}

    virtual void apply(const void* a_pInput, void* a_pOutput) const
    {
        size_t inputValue = *(const size_t*)a_pInput;
        if(inputValue == ~size_t(0)) *(size_t*)a_pOutput = ~size_t(0);
        *(size_t*)a_pOutput = *(const size_t*)a_pInput + offsetToBase;
    }

    virtual Expression* convert(Expression* a_pExpression) const;

    virtual data_member_pointer_conversion* clone() const { return new data_member_pointer_conversion(input, output, pointerToPointerInheritanceLevel, offsetToBase); }

    ptrdiff_t offsetToBase;
};

struct member_function_pointer_conversion : public numeric_conversion
{
    member_function_pointer_conversion(value_t i, value_t o, size_t inheritanceLevel = ~size_t(0), ptrdiff_t offset = 0) 
        : numeric_conversion(i, o, false, inheritanceLevel) 
        , offsetToBase(offset) {}
    virtual void apply(const void* a_pInput, void* a_pOutput) const;
    ptrdiff_t offsetToBase;

    virtual Expression* convert(Expression* a_pExpression) const;

    virtual member_function_pointer_conversion* clone() const { return new member_function_pointer_conversion(input, output, pointerToPointerInheritanceLevel, offsetToBase); }
};

struct qualification_adjustment : public standard_conversion
{
    qualification_adjustment(value_t src, value_t dest, int count) 
        : standard_conversion(src, dest, e_qualification_adjustment), adjustmentCount(count) {}
    int adjustmentCount;
    virtual void apply(const void* a_pInput, void* a_pOutput) const {}
    virtual qualification_adjustment* clone() const { return new qualification_adjustment(input, output, adjustmentCount); }
    virtual Expression* convert(Expression* a_pExpression) const { return a_pExpression; }
};

struct user_defined_conversion : public conversion
{
    user_defined_conversion(Constructor* a_pConstructor) 
        : conversion(a_pConstructor->getParameterType(0), a_pConstructor->getOwnerClassType())
        , m_member_function(a_pConstructor)
        , m_standard(0) {}
    user_defined_conversion(MemberFunction* memberFunction) 
        : conversion(memberFunction->getOwnerClassType(), memberFunction->getReturnType())
        , m_member_function(memberFunction)
        , m_standard(0) {}


    MemberFunction* m_member_function;
    standard_conversion_sequence* m_standard;

    void apply(const void* a_pInput, void* a_pOutput) const 
    {
        if(m_member_function->asConstructor())
        {
            void* args[1] = {(void*)a_pInput};
            m_member_function->call(a_pOutput, args);
        }
        else 
        {
            m_member_function->call((void*)a_pInput, nullptr, a_pOutput);
        }
    }

    virtual Expression* convert(Expression* a_pExpression) const;

    int compare(const user_defined_conversion& other) const 
    {
        /// 13.3.3.2 (3.3)
        /// User-defined conversion sequence U1 is a better conversion sequence than another user-defined conversion
        /// sequence U2 if they contain the same user-defined conversion function or constructor or they
        /// initialize the same class in an aggregate initialization and in either case the second standard conversion
        /// sequence of U1 is better than the second standard conversion sequence of U2. [Example:
        if(m_member_function->equals(other.m_member_function))
        {
            if(!m_standard)
            {
                if(!other.m_standard) return 0;
                else return 1;
            }
            else if(!other.m_standard)
            {
                return -1;
            }
            return m_standard->compare(*other.m_standard);
        }
        return 0;
    }
    virtual user_defined_conversion* clone() const { return new user_defined_conversion(input, output, m_member_function, m_standard); }

private:
    user_defined_conversion(value_t i, value_t o, MemberFunction* memberFunction, standard_conversion_sequence* a_standard) 
        : conversion(i, o)
        , m_member_function(memberFunction)
        , m_standard(a_standard) {}
};


Expression* standard_conversion_sequence::convert(Expression* a_pExpression) const
{
    if(m_lvalue_transformation)
    {
        a_pExpression = m_lvalue_transformation->convert(a_pExpression);
    }
    if(m_numeric_conversion)
    {
        a_pExpression = m_numeric_conversion->convert(a_pExpression);
    }
    if(m_const_ref)
    {
        a_pExpression = m_const_ref->convert(a_pExpression);
    }
    return a_pExpression;
}

void default_conversion_sequence::addUserDefinedByConstruction(Constructor* a_pConstructor)
{
    m_user_defined = new user_defined_conversion(a_pConstructor);
    output = m_user_defined->output;
}
void default_conversion_sequence::addUserDefinedByConversionFunction(MemberFunction* a_pConversionFunction)
{
    m_user_defined = new user_defined_conversion(a_pConversionFunction);
    output = m_user_defined->output;
}

void member_function_pointer_conversion::apply( const void* a_pInput, void* a_pOutput ) const
{
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO /// /vmg + /vmv must be defined
    struct __MicrosoftUnknownMFP{
        void* m_func_address; // 64 bits for Itanium.
        ptrdiff_t m_delta;
        int m_vtordisp;
        int m_vtable_index; // or 0 if no virtual inheritance
    };
    __MicrosoftUnknownMFP& output = *(__MicrosoftUnknownMFP*)a_pOutput; 
    __MicrosoftUnknownMFP& input  = *(__MicrosoftUnknownMFP*)a_pInput;
    output.m_delta = input.m_delta + offsetToBase;
    o_assert(input.m_vtable_index == 0 AND output.m_vtable_index == 0, "phantom does not support virtual inheritance");


    //         if (vindex=0) adjustedthis = this + delta
    //         else adjustedthis = this + delta + vtordisp + *(*(this + vtordisp) + vindex)
    //         CALL funcadr
#elif o_COMPILER == o_COMPILER_GCC || o_COMPILER == o_COMPILER_CLANG
    // GNU g++ uses a tricky space optimisation, also adopted by IBM's VisualAge and XLC.
    struct __GnuClangMFP {
        union {
            void* m_func_address_even; // always even
            ptrdiff_t m_vtable_index_odd; //  = vindex*2+1, always odd
        };
        ptrdiff_t m_delta;
    };
    //         adjustedthis = this + delta
    //             if (funcadr & 1) CALL (* ( *delta + (vindex+1)/2) + 4)
    //             else CALL funcadr
    __GnuClangMFP& output = *(__GnuClangMFP*)a_pOutput; 
    __GnuClangMFP& input  = *(__GnuClangMFP*)a_pInput;
    output.m_delta = input.m_delta + offsetToBase;
#else
#   error define Member Function Pointer struct for the current compiler
#endif
}

Expression* member_function_pointer_conversion::convert( Expression* a_pExpression ) const
{
    o_assert(output->asMemberFunctionPointerType());
    return o_new(MemberFunctionPointerAdjustmentExpression)(output->asMemberFunctionPointerType(), a_pExpression, offsetToBase);
}

default_conversion_sequence::default_conversion_sequence( value_t io, bool a_bEllipsis /*= false*/ ) 
    : conversion(io, a_bEllipsis ? nullptr : io)
    , m_standard(a_bEllipsis ? 0 : new standard_conversion_sequence(io)), m_user_defined(0), m_ellipsis(a_bEllipsis)
{

}

default_conversion_sequence::default_conversion_sequence( value_t i, value_t o, int a_iPlaceholding /*= 0*/ ) 
    : conversion(i, o)
    , m_ellipsis(false)
    , m_placeholding(a_iPlaceholding)
{

}

default_conversion_sequence::default_conversion_sequence( constref_conversion* cr ) 
    : conversion(cr->input, cr->output), m_standard( new standard_conversion_sequence(cr)), m_user_defined(nullptr), m_ellipsis(false), m_placeholding(0)
{

}

default_conversion_sequence::default_conversion_sequence( lvalue_transformation* lvt ) 
    : conversion(lvt->input, lvt->output), m_standard( new standard_conversion_sequence(lvt)), m_user_defined(nullptr), m_ellipsis(false), m_placeholding(0)
{

}

default_conversion_sequence::default_conversion_sequence( lvalue_transformation* lvt, qualification_adjustment* qa, constref_conversion* cr /*= 0*/ ) 
    : conversion(lvt->input, cr ? cr->output : qa->output), m_standard( new standard_conversion_sequence(lvt, qa, cr)), m_user_defined(nullptr), m_ellipsis(false), m_placeholding(0)
{

}

default_conversion_sequence::default_conversion_sequence( lvalue_transformation* lvt, numeric_conversion* nc, constref_conversion* cr /*= 0*/ ) 
    : conversion(lvt->input, cr ? cr->output : nc->output), m_standard( new standard_conversion_sequence(lvt, nc, cr)), m_user_defined(nullptr), m_ellipsis(false), m_placeholding(0)
{

}

default_conversion_sequence::default_conversion_sequence( lvalue_transformation* lvt, numeric_conversion* nc, qualification_adjustment* qa, constref_conversion* cr /*= 0*/ ) 
    : conversion(lvt->input, cr ? cr->output : qa->output), m_standard( new standard_conversion_sequence(lvt, nc, qa, cr)), m_user_defined(nullptr), m_ellipsis(false), m_placeholding(0)
{

}

default_conversion_sequence::default_conversion_sequence( numeric_conversion* nc, qualification_adjustment* qa, constref_conversion* cr /*= 0*/ ) 
    : conversion(nc->input, cr ? cr->output : qa->output), m_standard( new standard_conversion_sequence(nc, qa, cr)), m_user_defined(nullptr), m_ellipsis(false), m_placeholding(0)
{

}

default_conversion_sequence::default_conversion_sequence( numeric_conversion* nc, constref_conversion* cr /*= 0*/ ) 
    : conversion(nc->input, cr ? cr->output : nc->output), m_standard( new standard_conversion_sequence(nc, cr)), m_user_defined(nullptr), m_ellipsis(false), m_placeholding(0)
{

}

default_conversion_sequence::default_conversion_sequence( qualification_adjustment* qa, constref_conversion* cr /*= 0*/ ) 
    : conversion(qa->input, cr ? cr->output : qa->output), m_standard( new standard_conversion_sequence(qa, cr)), m_user_defined(nullptr), m_ellipsis(false), m_placeholding(0)
{

}

default_conversion_sequence::default_conversion_sequence( standard_conversion_sequence* s1 ) 
    : conversion(s1->input, s1->output), m_standard(s1), m_user_defined(nullptr), m_ellipsis(false), m_placeholding(0)
{

}

default_conversion_sequence::default_conversion_sequence( standard_conversion_sequence* s1, user_defined_conversion* ud ) 
    : conversion(s1->input, ud->output), m_standard(s1), m_user_defined(ud), m_ellipsis(false), m_placeholding(0)
{

}

default_conversion_sequence::default_conversion_sequence( user_defined_conversion* ud ) 
    : conversion(ud->input, ud->output), m_standard(0), m_user_defined(ud), m_ellipsis(false), m_placeholding(0)
{

}

void default_conversion_sequence::apply( const void* a_pInput, void* a_pOutput ) const
{
    if((m_standard AND !m_standard->isIdentity()) OR m_user_defined)
    {
        if(m_standard)
        {
            m_standard->apply(a_pInput, a_pOutput);
            a_pInput = a_pOutput;
        }
        if(m_user_defined)
        {
            m_user_defined->apply(a_pInput, a_pOutput);
        }
    }
    else 
    {
        // raw copy
        memcpy(a_pOutput, a_pInput, std::min(input->getSize(), output->getSize()));
    }
}

void default_conversion_sequence::addConstRef()
{
    if(m_user_defined)
    {
        if(m_user_defined->m_standard == nullptr)
        {
            m_user_defined->m_standard = new standard_conversion_sequence(new constref_conversion(output));
        }
        else 
        {
            m_user_defined->m_standard->addConstRef();
        }
    }
    else if(m_standard == nullptr)
    {
        m_standard = new standard_conversion_sequence(new constref_conversion(output));
    }
    output = output->lvalueReferenceType()->constType();
}

void default_conversion_sequence::addLValueTransform()
{
    if(m_user_defined)
    {
        if(m_user_defined->m_standard == nullptr)
        {
            m_user_defined->m_standard = new standard_conversion_sequence(new lvalue_transformation(output));
        }
        else 
        {
            m_user_defined->m_standard->addLValueTransform();
        }
    }
    else if(m_standard == nullptr)
    {
        m_standard = new standard_conversion_sequence(new lvalue_transformation(output));
    }
    else 
    {
        o_assert(m_standard->m_lvalue_transformation == nullptr);
        m_standard->m_lvalue_transformation = new lvalue_transformation(output);
    }
    output = output->removeReference();
}

int default_conversion_sequence::compare( const default_conversion_sequence& other ) const
{
    /// 1) A standard conversion sequence or user-defined conversion sequence is always better than an ellipsis conversion sequence.
    if(m_ellipsis && !other.m_ellipsis) return -1;
    else if(!m_ellipsis && other.m_ellipsis) return 1;
    if(!m_standard)
    {
        if(!m_user_defined)
            // equals conversion (canonical copy)
        {
            if(!other.m_standard && !other.m_user_defined)
                return 0;
            return 1;
        }
        else if(other.m_standard)
        {
            if(other.m_user_defined) return 1; /// only u > other.s+other.u
            else if(!other.m_user_defined) return -1; /// only u < other.s 
        }
        else 
        {
            if(!other.m_user_defined) return -1; /// other is canonical conversion
            else return m_user_defined->compare(*other.m_user_defined);
        }
    }
    else // m_standard
    {
        if(!m_user_defined) // s + !u
        {
            if(other.m_standard) 
            {
                if(!other.m_user_defined) // o.s + !o.u
                    return m_standard->compare(*other.m_standard); 
                else // o.s + o.u 
                    return 1;
            }
            else 
            {
                if(!other.m_user_defined) // !o.s + !o.u
                    return -1; 
                else // !o.s + o.u 
                    return 1;
            }
        }
        else // s + u
        {
            if(other.m_standard)  
            {
                if(!other.m_user_defined) // o.s + !o.u
                    return -1; 
                else // o.s + o.u 
                {
                    int scompare = m_standard->compare(*other.m_standard);
                    if(scompare == 0) return m_user_defined->compare(*other.m_user_defined);
                    return scompare;
                }
            }
            else 
            {
                return -1;
            }
        }
    }
    /// 2) A standard conversion sequence is always better than an user-defined conversion
    if(m_standard && !other.m_standard) 
        return 1;
    else if(other.m_standard && !m_standard)
        return -1;
    if(m_standard)
    {
        /// standard conversion sequences comparison
        o_assert(other.m_standard);
        return m_standard->compare(*other.m_standard);
    }
    else 
    {
        /// user defined conversions comparison
        o_assert(m_user_defined);
        return m_user_defined->compare(*other.m_user_defined);
    }
}

default_conversion_sequence* default_conversion_sequence::clone() const
{
    default_conversion_sequence* pClone = new default_conversion_sequence(input, output);
    pClone->m_standard = m_standard ? m_standard->clone() : nullptr;
    pClone->m_user_defined = m_user_defined ? m_user_defined->clone() : nullptr;
    pClone->m_ellipsis = m_ellipsis;
    return pClone;
}

Expression* default_conversion_sequence::convert( Expression* a_pExpression ) const
{
    if(m_standard)
    {
        a_pExpression = m_standard->convert(a_pExpression);
    }
    if(m_user_defined)
    {
        a_pExpression = m_user_defined->convert(a_pExpression);
    }
    return a_pExpression;
}

standard_conversion_sequence::standard_conversion_sequence( value_t io ) : conversion(io, io), m_lvalue_transformation(0), m_numeric_conversion(0), m_qualification_adjustment(0), m_const_ref(0)
{

}

standard_conversion_sequence::standard_conversion_sequence( value_t i, value_t o ) : conversion(i, o), m_lvalue_transformation(0), m_numeric_conversion(0), m_qualification_adjustment(0), m_const_ref(0)
{

}
standard_conversion_sequence::standard_conversion_sequence( constref_conversion* cr ) 
    : conversion(cr->input, cr->output), m_lvalue_transformation(0), m_numeric_conversion(0), m_qualification_adjustment(0), m_const_ref(cr)
{

}

standard_conversion_sequence::standard_conversion_sequence( lvalue_transformation* lt ) : conversion(lt->input, lt->output), m_lvalue_transformation(lt), m_numeric_conversion(0), m_qualification_adjustment(0), m_const_ref(0)
{

}

standard_conversion_sequence::standard_conversion_sequence( lvalue_transformation* lt, qualification_adjustment* qa, constref_conversion* cr /*= 0*/ ) : conversion(lt->input, qa->output), m_lvalue_transformation(lt), m_numeric_conversion(0), m_qualification_adjustment(qa), m_const_ref(0)
{

}

standard_conversion_sequence::standard_conversion_sequence( lvalue_transformation* lt, numeric_conversion* nc, constref_conversion* cr /*= 0*/ ) : conversion(lt->input, cr ? cr->output : nc->output), m_lvalue_transformation(lt), m_numeric_conversion(nc), m_qualification_adjustment(0), m_const_ref(cr)
{

}

standard_conversion_sequence::standard_conversion_sequence( lvalue_transformation* lt, numeric_conversion* nc, qualification_adjustment* qa, constref_conversion* cr /*= 0*/ ) : conversion(lt->input, cr ? cr->output : qa->output), m_lvalue_transformation(lt), m_numeric_conversion(nc), m_qualification_adjustment(qa), m_const_ref(cr)
{

}

standard_conversion_sequence::standard_conversion_sequence( numeric_conversion* nc, qualification_adjustment* qa, constref_conversion* cr /*= 0*/ ) : conversion(nc->input, cr ? cr->output : qa->output), m_lvalue_transformation(0), m_numeric_conversion(nc), m_qualification_adjustment(qa), m_const_ref(cr)
{

}

standard_conversion_sequence::standard_conversion_sequence( numeric_conversion* nc, constref_conversion* cr /*= 0*/ ) : conversion(nc->input, cr ? cr->output : nc->output), m_lvalue_transformation(0), m_numeric_conversion(nc), m_qualification_adjustment(0), m_const_ref(cr)
{

}

standard_conversion_sequence::standard_conversion_sequence( qualification_adjustment* qa, constref_conversion* cr /*= 0*/ ) : conversion(qa->input, cr ? cr->output : qa->output), m_lvalue_transformation(0), m_numeric_conversion(0), m_qualification_adjustment(qa), m_const_ref(cr)
{

}

void standard_conversion_sequence::apply( const void* a_pInput, void* a_pOutput ) const
{
    if(m_lvalue_transformation)
    {
        a_pInput = *(void**)a_pInput;
        if(m_numeric_conversion == nullptr)
        {
            o_assert(m_const_ref == nullptr);
            memcpy(a_pOutput, a_pInput, output->getSize());
            return;
        }
    }
    if(m_numeric_conversion)
    {
        m_numeric_conversion->apply(a_pInput, a_pOutput);
        a_pInput = a_pOutput;
    }
    if(m_const_ref)
    {
        m_const_ref->apply(a_pInput, a_pOutput);
    }
}

int standard_conversion_sequence::compare( const standard_conversion_sequence& other ) const
{
    if(m_numeric_conversion)
    {
        if(!other.m_numeric_conversion) return -1;
        else return m_numeric_conversion->compare(*other.m_numeric_conversion);
    }
    else 
    {
        if(other.m_numeric_conversion) return 1;
        else 
        {
            if(m_qualification_adjustment)
            {
                if(!other.m_qualification_adjustment) return -1;
                else return m_qualification_adjustment->compare(*other.m_qualification_adjustment);
            }
            else 
                if(other.m_qualification_adjustment) return 1;
        }
    }
    return 0;
}

void standard_conversion_sequence::addConstRef()
{
    m_const_ref = new constref_conversion(output);
    output = output->lvalueReferenceType()->constType();
}

void standard_conversion_sequence::addLValueTransform()
{
    m_lvalue_transformation = new lvalue_transformation(output);
    output = output->removeReference();
}

standard_conversion_sequence* standard_conversion_sequence::clone() const
{
    standard_conversion_sequence* pClone = new standard_conversion_sequence(input, output);
    pClone->m_lvalue_transformation = m_lvalue_transformation ? m_lvalue_transformation->clone() : nullptr;
    pClone->m_numeric_conversion = m_numeric_conversion ? m_numeric_conversion->clone() : nullptr;
    pClone->m_qualification_adjustment = m_qualification_adjustment ? m_qualification_adjustment->clone() : nullptr;
    pClone->m_const_ref = m_const_ref ? m_const_ref->clone() : nullptr;
    return pClone;
}

lvalue_transformation* lvalue_transformation::clone() const
{
    return new lvalue_transformation(input);
}

constref_conversion* constref_conversion::clone() const
{
    return new constref_conversion(input);
}

numeric_conversion* numeric_conversion::clone() const
{
    return new numeric_conversion(input, output, promotion, pointerToPointerInheritanceLevel);
}

Expression* pointer_conversion::convert( Expression* a_pExpression ) const
{
    return offsetToBase ? o_new(PointerAdjustmentExpression)(output, a_pExpression, offsetToBase) : a_pExpression;
}

Expression* data_member_pointer_conversion::convert( Expression* a_pExpression ) const
{
    return offsetToBase ? o_new(DataMemberPointerAdjustmentExpression)(output, a_pExpression, offsetToBase) : a_pExpression;
}

Expression* user_defined_conversion::convert( Expression* a_pExpression ) const
{
    if(m_member_function)
    {
        Constructor* pCtor = m_member_function->asConstructor();
        if(pCtor)
        {
            /// Constructor
            vector<Expression*> arguments;
            arguments.push_back(a_pExpression);
            a_pExpression = o_new(ConstructorCallExpression)(pCtor, arguments);
        }
        else 
        {
            /// Conversion function
            vector<Expression*> arguments;
            arguments.push_back(a_pExpression);
            a_pExpression = o_new(CallExpression)(m_member_function, arguments);
        }
        static_cast<CallExpression*>(a_pExpression)->setImplicit(); /// ensure call is marked as implicit to avoid it to be translated to text when retro generating code
    }
    if(m_standard)
    {
        a_pExpression = m_standard->convert(a_pExpression);
    }
    return a_pExpression;
}

/// TEMPLATE INSTANCIATION


#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   define o_instanciateT(...) o_PP_CAT(o_PP_CAT(o_instanciateT_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#   define o_resolveT(...) o_PP_CAT(o_PP_CAT(o_resolveT_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
//#   define o_findT(...) o_PP_CAT(o_PP_CAT(o_findT_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#else
#   define o_instanciateT(...) o_PP_CAT(o_instanciateT_, o_PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#   define o_resolveT(...) o_PP_CAT(o_resolveT_, o_PP_NARG(__VA_ARGS__))(__VA_ARGS__)
//#   define o_findT(...) o_PP_CAT(o_findT_, o_PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#endif 

#define o_instanciateT_2(type, element)\
    (((element) == nullptr) ? nullptr : ((this->instanciateTemplate((element), pTemplateSignature, arguments, pScope, a_Data.flags))->as##type()))\

#define o_instanciateT_3(type, element, scope)\
    (((element) == nullptr) ? nullptr : ((this->instanciateTemplate((element), pTemplateSignature, arguments, scope, a_Data.flags))->as##type()))\

#define o_resolveT_2(type, element)\
    (((element) == nullptr) ? nullptr : this->resolveTemplateDependency((element), pTemplateSignature, arguments, pScope, a_Data.flags)->as##type())\

#define o_resolveT_3(type, element, scope)\
    (((element) == nullptr) ? nullptr : this->resolveTemplateDependency((element), pTemplateSignature, arguments, scope, a_Data.flags))->as##type())\
// 
// #define o_findT_2(type, element)\
//     (((element) == nullptr) ? nullptr : (*(ppTempElement = &m_Templated[&arguments][element])) ? (*ppTempElement)->as##type() : nullptr)\
// 
// #define o_findT_3(type, element, scope)\
//     (((element) == nullptr) ? nullptr : (*(ppTempElement = &m_Templated[&arguments][element])) ? (*ppTempElement)->as##type() : nullptr)\



#if o_HAS_BUILT_IN_WCHAR_T
#define case_e_wchar_t case e_wchar_t:
#else
#define case_e_wchar_t 
#endif

#if o_HAS_BUILT_IN_CHAR16_T
#define case_e_char16_t case e_char16_t:
#else
#define case_e_char16_t 
#endif

#if o_HAS_BUILT_IN_CHAR32_T
#define case_e_char32_t case e_char32_t:
#else
#define case_e_char32_t 
#endif

#define o_instanciate_template_clone \
    case e_Function_InstanciateTemplate:                                                                    \
        {                                                                                                   \
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];                     \
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];     \
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];                                     \
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];                            \
            pInstanciated = a_pInput->clone();                                                              \
        }                                                                                                   \
        return;                                                                                             

struct no_numeric_conversion { static numeric_conversion* apply(bool a_bPromotion) { return nullptr; } };

template<typename t_Input, typename t_Output, int a_iConversionType>
struct makeNumericConversion
{
    static numeric_conversion* apply(bool a_bPromotion)
    {
        return new tnumeric_conversion<t_Input, t_Output, a_iConversionType>(a_bPromotion);
    }
    static numeric_conversion* apply(Type* a_pInput, Type* a_pOutput, bool a_bPromotion)
    {
        return new tnumeric_conversion<t_Input, t_Output, a_iConversionType>(a_pInput, a_pOutput, a_bPromotion);
    }
};

template<typename t_Input, typename t_Output>
struct makeNumericConversion<t_Input, t_Output, e_reinterpret_cast> : public no_numeric_conversion {};

template<typename t_Ty>
struct makeNumericConversion<t_Ty, t_Ty, e_reinterpret_cast> 
{
    static numeric_conversion* apply(bool a_bPromotion)
    {
        return new tnumeric_conversion<t_Ty, t_Ty, e_reinterpret_cast>(a_bPromotion);
    }
    static numeric_conversion* apply(Type* a_pInput, Type* a_pOutput, bool a_bPromotion)
    {
        return new tnumeric_conversion<t_Ty, t_Ty, e_reinterpret_cast>(a_pInput, a_pOutput, a_bPromotion);
    }
};

template<typename t_Ty, int a_iConversionType>
numeric_conversion* CPlusPlus::arithmeticConversion(native::TArithmeticType<t_Ty>* a_pInput, Type* pOutput, bool a_bPromotion /*= false*/)
{
    ETypeId outputTypeId = pOutput->getTypeId();
    switch(outputTypeId)
    {
    case reflection::e_bool: return makeNumericConversion<t_Ty, bool, a_iConversionType>::apply(a_bPromotion);
    case reflection::e_char: return makeNumericConversion<t_Ty, char, a_iConversionType>::apply(a_bPromotion);
    case reflection::e_uchar: return makeNumericConversion<t_Ty, uchar, a_iConversionType>::apply(a_bPromotion);
    case reflection::e_schar: return makeNumericConversion<t_Ty, schar, a_iConversionType>::apply(a_bPromotion);
    case reflection::e_short: return makeNumericConversion<t_Ty, short, a_iConversionType>::apply(a_bPromotion);
    case reflection::e_ushort: return makeNumericConversion<t_Ty, ushort, a_iConversionType>::apply(a_bPromotion);
    case reflection::e_int: return makeNumericConversion<t_Ty, int, a_iConversionType>::apply(a_bPromotion);
    case reflection::e_uint: return makeNumericConversion<t_Ty, uint, a_iConversionType>::apply(a_bPromotion);
    case reflection::e_long: return makeNumericConversion<t_Ty, long, a_iConversionType>::apply(a_bPromotion);
    case reflection::e_ulong: return makeNumericConversion<t_Ty, ulong, a_iConversionType>::apply(a_bPromotion);
    case reflection::e_longlong: return makeNumericConversion<t_Ty, longlong, a_iConversionType>::apply(a_bPromotion);
    case reflection::e_ulonglong: return makeNumericConversion<t_Ty, ulonglong, a_iConversionType>::apply(a_bPromotion);
    case reflection::e_float: return makeNumericConversion<t_Ty, float, a_iConversionType>::apply(a_bPromotion);
    case reflection::e_double: return makeNumericConversion<t_Ty, double, a_iConversionType>::apply(a_bPromotion);
    case reflection::e_longdouble: return makeNumericConversion<t_Ty, longdouble, a_iConversionType>::apply(a_bPromotion);
#if o_HAS_BUILT_IN_WCHAR_T
    case reflection::e_wchar_t: return makeNumericConversion<t_Ty, wchar_t, a_iConversionType>::apply(a_bPromotion);
#endif
#if o_HAS_BUILT_IN_CHAR16_T
    case reflection::e_char16_t: return makeNumericConversion<t_Ty, char16_t, a_iConversionType>::apply(a_bPromotion);
#endif
#if o_HAS_BUILT_IN_CHAR32_T
    case reflection::e_char32_t: return makeNumericConversion<t_Ty, char32_t, a_iConversionType>::apply(a_bPromotion);
#endif
    case reflection::e_enum: 
        {
            return arithmeticConversion<t_Ty, a_iConversionType>(a_pInput, pOutput->asEnum()->getIntType(), a_bPromotion);
        }
    default:
        break;
    }
    return nullptr;
}

template<typename t_Ty, int a_iConversionType>
numeric_conversion* CPlusPlus::floatingPointConversion(native::TFloatingPointType<t_Ty>* a_pInput, Type* pOutput, bool a_bPromotion /*= false*/)
{
    return arithmeticConversion<t_Ty, a_iConversionType>(a_pInput, pOutput, a_bPromotion);
}

template<typename t_Ty, int a_iConversionType>
conversion* CPlusPlus::floatingPointConversion(native::TFloatingPointType<t_Ty>* a_pInput, Type* pOutput, bool a_bPromotion, bool a_bConstRef)
{
    numeric_conversion* pConversion = floatingPointConversion<t_Ty, a_iConversionType>(a_pInput, pOutput, a_bPromotion);
    if(pConversion) 
    {
        if(a_bConstRef)
            return new default_conversion_sequence(pConversion, new constref_conversion(pOutput));
        return new default_conversion_sequence(pConversion); // canonical conversion
    }
    return nullptr;
}

template<typename t_Ty, int a_iConversionType>
struct any_to_ptr_conversion
{
    static numeric_conversion* apply(Type* a_pOutput, bool a_bPromotion)
    {
        return new tnumeric_conversion<t_Ty, void*, a_iConversionType>(typeOf<t_Ty>(), a_pOutput, a_bPromotion);
    }
};

template<typename t_Ty>
struct any_to_ptr_conversion<t_Ty, e_static_cast>
{
    static numeric_conversion* apply(Type* a_pOutput, bool a_bPromotion)
    {
        return nullptr;
    }
};

template<typename t_Ty>
struct any_to_ptr_conversion<t_Ty, e_implicit_conversion>
{
    static numeric_conversion* apply(Type* a_pOutput, bool a_bPromotion)
    {
        return nullptr;
    }
};

template<typename t_Ty, int a_iConversionType>
numeric_conversion* CPlusPlus::integralConversion(native::TIntegralType<t_Ty>* a_pInput, Type* pOutput, bool a_bPromotion)
{    
    numeric_conversion* pConversion = arithmeticConversion<t_Ty, a_iConversionType>(a_pInput, pOutput, a_bPromotion);
    if(pConversion) return pConversion;
    ETypeId outputTypeId = pOutput->getTypeId();
    switch(outputTypeId)
    {
    case reflection::e_pointer: 
        {
            if(!boost::is_same<bool, t_Ty>::value)
            {
                return any_to_ptr_conversion<t_Ty, a_iConversionType>::apply(pOutput, a_bPromotion);
            }
        }
    case reflection::e_enum: 
        {
            return integralConversion<t_Ty, a_iConversionType>(a_pInput, pOutput->asEnum()->getIntType(), a_bPromotion);
        }
    default:
        break;
    }
    return nullptr;
}

template<typename t_Ty, int a_iConversionType>
conversion* CPlusPlus::integralConversion(native::TIntegralType<t_Ty>* a_pInput, Type* pOutput, bool a_bPromotion, bool a_bConstRef)
{
    numeric_conversion* pConversion = integralConversion<t_Ty, a_iConversionType>(a_pInput, pOutput, a_bPromotion);
    if(pConversion) 
    {
        if(a_bConstRef)
            return new default_conversion_sequence(pConversion, new constref_conversion(pOutput));
        return new default_conversion_sequence(pConversion); // canonical conversion
    }
    return nullptr;
}

bool CPlusPlus::baseConversion(Type* a_pInput, Type*& pOutput, int iConversionType)
{
    /// X => X const
    pOutput = pOutput->removeQualifiers();
    Type* pOutputConstRef = pOutput->asConstReferenceType();
    if(pOutputConstRef)
    {
        /// X -> const X& => temporary object (only for implicit conversions)
        if(iConversionType != e_implicit_conversion) 
            return false;
        pOutput = pOutputConstRef->removeConstReference();
        return true;
    }
    return false;
}

conversion* CPlusPlus::baseStandardConversion(Type* a_pInput, Type* pOutput, int iConversionType, bool& a_bConstRef)
{
    a_bConstRef = baseConversion(a_pInput, pOutput, iConversionType);
    if(a_pInput->equals(pOutput))
    {
        if(iConversionType == e_const_cast)
        {
            return nullptr; /// const_cast is forbidden for identity conversion
        } 
        return a_bConstRef 
            ? new default_conversion_sequence(new constref_conversion(pOutput)) 
            : new default_conversion_sequence(a_pInput);
    }
    return nullptr;
}

void CPlusPlus::visit( AggregationClass*            a_pInput, visitor_data a_Data) { visit(static_cast<Class*>(a_pInput), a_Data); }
void CPlusPlus::visit( Alias*                       a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void CPlusPlus::visit( AnonymousSection*            a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void CPlusPlus::visit( AnonymousStruct*             a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            AnonymousStruct* pAnonymousStruct = o_new(AnonymousStruct);
            for(auto it = a_pInput->beginVariables(); it != a_pInput->endVariables(); ++it)
            {
                pAnonymousStruct->addVariable(o_resolveT(Variable, *it));
            }
            pInstanciated = pAnonymousStruct;
        }
        return;
    }
    visit(static_cast<AnonymousSection*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( AnonymousUnion*              a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            AnonymousUnion* pAnonymousUnion = o_new(AnonymousUnion);
            for(auto it = a_pInput->beginVariables(); it != a_pInput->endVariables(); ++it)
            {
                pAnonymousUnion->addVariable(o_resolveT(Variable, *it));
            }
            pInstanciated = pAnonymousUnion;
        }
        return;
    }
    visit(static_cast<AnonymousSection*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( Application*                 a_pInput, visitor_data a_Data )
{
    switch(a_Data.id)
    {
    case e_Function_QualifiedLookup:
    case e_Function_UnqualifiedLookup:
        visit(static_cast<NamedElement*>(a_pInput), a_Data);
        return;
    case e_Function_QualifiedNameLookup:
        {
            const string& in_name = *(const string*)a_Data.in[0];
            vector<LanguageElement*>& out_candidates = *(vector<LanguageElement*>*)a_Data.out[0];
            LanguageElement* pElement = a_pInput->getBuiltInType(in_name);
            if(pElement)
            {
                out_candidates.push_back(pElement);
                return;
            }
        }
        break;
    case e_Function_BinaryOperator:
    case e_Function_UnaryPreOperator:
    case e_Function_UnaryPostOperator:
        {
            const string& in_op = *(const string*)a_Data.in[0];
            Expression** in_ppArguments = (Expression**)a_Data.in[1];
            LanguageElement* in_pContextScope = *(LanguageElement**)a_Data.in[2];
            Expression*& out_pExpression = *(Expression**)a_Data.out[0];
            if(in_op == ",")
            {
                out_pExpression = o_new(CommaExpression)(in_ppArguments[0], in_ppArguments[1]);
                return;
            }
            BuiltInOperator* pOperator = a_Data.id == e_Function_BinaryOperator 
                                            ? a_pInput->getBuiltInBinaryOperator(in_op)
                                            : a_Data.id == e_Function_UnaryPreOperator 
                                                ? a_pInput->getBuiltInPreUnaryOperator(in_op) 
                                                : a_pInput->getBuiltInPostUnaryOperator(in_op) 
                                                ;
            if(!pOperator) 
            {
                BuiltInOperatorExpression* pInvalidOperation = o_new(BuiltInOperatorExpression)(BuiltInOperator::Invalid(), Type::Invalid(), in_ppArguments, operation_delegate_t());
                pInvalidOperation->error("no built-in operator %s found", in_op.c_str());
                out_pExpression = pInvalidOperation;
                break;
            }
            size_t operandCount = pOperator->getOperandCount();
            vector<BuiltInOperator::overload> overloads;
            vector<conversions> overloadConversions;
            vector<BuiltInOperator::overload> viableOverloads;
            if(pOperator)
            {
                vector<conversions*> viableImplicitConversions;
                pOperator->implicitConversions(in_ppArguments, overloadConversions, overloads);
                for(size_t i = 0; i<overloadConversions.size(); ++i)
                {
                    if(overloadConversions[i].hasNull()) continue;
                    viableImplicitConversions.push_back(&overloadConversions[i]);
                    viableOverloads.push_back(overloads[i]);
                }

                if(viableImplicitConversions.size())
                {
                    /// Find best viable operator or display ambiguity error
                    conversions* pBest = nullptr;
                    BuiltInOperator::overload* pBestOverload = nullptr;
                    if(viableImplicitConversions.size() == 1)
                    {
                        pBest = viableImplicitConversions.back();
                        pBestOverload = &viableOverloads.back();
                    }
                    else
                    {
                        size_t bestIndex = 0;
                        for(size_t i = 0; i<viableImplicitConversions.size(); ++i)
                        {
                            int bestResult = -1;
                            size_t j = 0;
                            for(; j<viableImplicitConversions.size(); ++j)
                            {
                                int result = viableImplicitConversions[i]->compare(*viableImplicitConversions[j]);
                                o_assert(viableImplicitConversions[j]->compare(*viableImplicitConversions[i]) == -result); /// compare() coherence test
                                if(result >= 0)
                                    bestResult = std::max(bestResult, result);
                                else 
                                    break;
                            }
                            if(j == viableImplicitConversions.size()) /// superior or equal to every one (not worst to any)
                            {
                                if(bestResult == 1)
                                {
                                    /// found a best match (superior to at least one other signature and equal to the others)
                                    pBest = viableImplicitConversions[i];
                                    pBestOverload = &viableOverloads[i];
                                    goto end_of_selection;
                                }
                            }
                        }
                    }
                end_of_selection:
                    if(pBest)
                    {
                        o_assert(pBestOverload);
                        o_assert(pBest->size() == operandCount);
                        Expression* arguments[3];
                        for(size_t k = 0; k<operandCount; ++k)
                        {
                            arguments[k] = (*pBest)[k]->convert(in_ppArguments[k]); /// convert arguments 
                        }
                        out_pExpression = o_new(BuiltInOperatorExpression)(pOperator, pBestOverload->result, arguments, pBestOverload->delegate);
                    }
                    else
                    {
                        BuiltInOperatorExpression* pInvalidOperation = o_new(BuiltInOperatorExpression)(pOperator, Type::Invalid(), in_ppArguments, operation_delegate_t());
                        string operandTypesText = (a_Data.id == e_Function_BinaryOperator) 
                                                        ? string("taking left operand '")+in_ppArguments[0]->getValueType()->getQualifiedDecoratedName()+"' and right operand '"+in_ppArguments[1]->getValueType()->getQualifiedDecoratedName()+"'"
                                                        : (a_Data.id == e_Function_UnaryPreOperator)
                                                            ? string("taking suffix operand '")+in_ppArguments[0]->getValueType()->getQualifiedDecoratedName()+"'"
                                                            : (a_Data.id == e_Function_UnaryPostOperator)
                                                                ? string("taking prefix operand '")+in_ppArguments[0]->getValueType()->getQualifiedDecoratedName()+"'"
                                                                : "";
                        pInvalidOperation->error("ambiguous call to multiple built-in operator '%s' overloads %s", in_op.c_str(), operandTypesText.c_str());
                        for(auto it = viableOverloads.begin(); it != viableOverloads.end(); ++it)
                        {
                            pInvalidOperation->subError("%s '%s'", ((it == viableOverloads.begin()) ? _canBe : _or), it->toString(pOperator->getName()).c_str());
                        }
                    }
                }
                else 
                {
                    if(in_op == "?:")
                    {
                        Expression* pTest = convert(in_ppArguments[0], typeOf<bool>(), e_implicit_conversion, in_pContextScope);
                        Expression* pThenExpression = in_ppArguments[1];
                        Expression* pElseExpression = in_ppArguments[2];

                        Type* pThenType = pThenExpression->getValueType();
                        Type* pElseType = pElseExpression->getValueType();
                        Type* pResultType = pThenType;
                        // If both expressions are of the same type, the result is of that type.
                        if(pThenType->equals(pElseType))
                        {
                            pResultType = pThenType;
                        }
                        else if(pThenType->asArithmeticType() AND pElseType->asArithmeticType())
                        {
                            pResultType = pThenType->getTypeId() > pElseType->getTypeId() ? pThenType : pElseType;
                        }
                        // If both expressions are of pointer types or if one is a pointer type and the other is a constant expression that evaluates to 0, pointer conversions are performed to convert them to a common type.
                        else if(pThenType->asDataPointerType() 
                            AND pElseExpression->asConstantExpression() 
                            AND pElseExpression->asConstantExpression()->getConstant()->isIntegralZero())
                        {
                            pResultType = pThenType;
                        }
                        else if(pElseType->asDataPointerType() 
                                AND pThenExpression->asConstantExpression() 
                                AND pThenExpression->asConstantExpression()->getConstant()->isIntegralZero())
                        {
                            pResultType = pElseType;
                        }
                        else if(pThenType->asDataPointerType() AND pElseType->asDataPointerType())
                        {
                            Type* pCommon = pThenType->asDataPointerType()->getPointedType()->getCommonAncestor(pElseType->asDataPointerType()->getPointedType());
                            pResultType = (pCommon == nullptr) ? typeOf<void*>() : pCommon->pointerType();
                        }
                        // If both expressions are of reference types, reference conversions are performed to convert them to a common type.
                        else if(pThenType->asLValueReferenceType() AND pElseType->asLValueReferenceType())
                        {
                            Type* pCommon = pThenType->asLValueReferenceType()->getReferencedType()->getCommonAncestor(pElseType->asLValueReferenceType()->getReferencedType());
                            pResultType = (pCommon == nullptr) ? pThenType : pCommon->lvalueReferenceType();
                        }
                        else if(pThenType->asRValueReferenceType() AND pElseType->asRValueReferenceType())
                        {
                            Type* pCommon = pThenType->asRValueReferenceType()->getReferencedType()->getCommonAncestor(pElseType->asRValueReferenceType()->getReferencedType());
                            pResultType = (pCommon == nullptr) ? pThenType : pCommon->rvalueReferenceType();
                        }
                         
                        Expression* pConvertedThen = convert(pThenExpression, pResultType, e_implicit_conversion, in_pContextScope);
                        Expression* pConvertedElse = convert(pElseExpression, pResultType, e_implicit_conversion, in_pContextScope);
                        out_pExpression = o_new(ConditionalExpression)(pTest, pConvertedThen, pConvertedElse);
                        return;
                    }
                    else
                    {
                        BuiltInOperatorExpression* pInvalidOperation = o_new(BuiltInOperatorExpression)(pOperator, Type::Invalid(), in_ppArguments, operation_delegate_t());
                        string operandTypesText = (a_Data.id == e_Function_BinaryOperator) 
                            ? string("taking left operand '")+in_ppArguments[0]->getValueType()->getQualifiedDecoratedName()+"' and right operand '"+in_ppArguments[1]->getValueType()->getQualifiedDecoratedName()+"'"
                            : (a_Data.id == e_Function_UnaryPreOperator)
                                ? string("taking suffix operand '")+in_ppArguments[0]->getValueType()->getQualifiedDecoratedName()+"'"
                                : (a_Data.id == e_Function_UnaryPostOperator)
                                ? string("taking prefix operand '")+in_ppArguments[0]->getValueType()->getQualifiedDecoratedName()+"'"
                                : "";
                        pInvalidOperation->error("no built-in operator '%s' overload found %s", in_op.c_str(), operandTypesText.c_str());
                    }
                }
            }
        }
        break;
    }
}
void CPlusPlus::visit( ArrayType*                   a_pInput, visitor_data a_Data)
{
    switch(a_Data.id)
    {
    case e_Function_TemplateArgumentDeduction:
        {
            LanguageElement* pArgument = *(LanguageElement* const *)a_Data.in[0];
            LanguageElement*& pDeducedArgument = *(LanguageElement**)a_Data.out[0];
            map<Placeholder*, LanguageElement*>& deductions = *(map<Placeholder*, LanguageElement*>*)a_Data.out[1];
            ArrayType* pArrayType = pArgument->asArrayType();
            if(pArrayType)
            {
                if(pArrayType->getTypeId() == e_template_dependant)
                {
                    return;
                }
                if(pArrayType->getItemCount() == a_pInput->getItemCount())
                {
                    Type* pItemDeducedType = templateArgumentDeduction(a_pInput->getItemType(), pArrayType->getItemType(), deductions);
                    if(pItemDeducedType)
                    {
                        pDeducedArgument = pItemDeducedType->arrayType(a_pInput->getItemCount());
                    }
                }
            }
            break;
        }
        return;

    case e_Function_ResolveTemplateDependencies:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pResolved = *(LanguageElement**)a_Data.out[0];
            Type* pNewItemType = o_resolveT(Type, a_pInput->getItemType());
            pResolved = pNewItemType ? pNewItemType->arrayType(a_pInput->getItemCount()) : nullptr;
        }
        return;

    case e_Function_Conversion:
        {
            Type* pOutput = *(Type* const *)a_Data.in[0];
            int iConversionType = *(int const*)a_Data.in[1];
            int iUserDefinedConversionsAllowed = *(int const*)a_Data.in[2];
            LanguageElement* pContextScope = *(LanguageElement**)a_Data.in[3];
            conversion*& conv = *(conversion**)a_Data.out[0];
            std::pair<Type*, Type*> constAdjustment;
            size_t adjustmentCount = 0;
            Type* pInputArrayItemType = a_pInput->getItemType();
            if(pOutput->getTypeId() == e_array)
            {
                ArrayType* pOutputArrayType = static_cast<ArrayType*>(pOutput);
                Type* pOutputArrayItemType = pOutputArrayType->getItemType();
                if(pOutputArrayType->getItemCount() == a_pInput->getItemCount() /// output array has same bound
                    OR pOutputArrayType->getItemCount() == 0) /// output array has unknown bound
                {
                    if(pOutputArrayItemType->asConstType())
                    {
                        /// X[N] -> X const[N]
                        ArrayType* adjustmentInput = pOutputArrayItemType->removeConst()->arrayType(pOutputArrayType->getItemCount());
                        constAdjustment.first = adjustmentInput;
                        /// merge const adjustments
                        constAdjustment.second = pOutputArrayType; 
                        adjustmentCount++;
                        pOutputArrayType = adjustmentInput;
                        pOutputArrayItemType = pOutputArrayType->getItemType();
                    }
                    else if(pInputArrayItemType->asConstType())
                    {
                        return; /// X const[N] -/-> X[N]
                    }
                    if(pOutputArrayItemType == a_pInput->getItemType())
                    {
                        if(adjustmentCount)
                            conv = new default_conversion_sequence(new qualification_adjustment(constAdjustment.first, constAdjustment.second, adjustmentCount));
                        conv = new default_conversion_sequence(a_pInput, (value_t)pOutput->removeQualifiers()); /// trivial 
                        return; /// success = X[N] -> X const[N]
                    }
                    if((pInputArrayItemType->asClass() != nullptr) AND (pOutputArrayItemType->asClass() != nullptr)) 
                    {
                        reflection::Class* pInputClass  = static_cast<reflection::Class*>(pInputArrayItemType);
                        reflection::Class* pOutputClass   = static_cast<reflection::Class*>(pOutputArrayItemType);
                        size_t level = pInputClass->getInheritanceLevelFromBase(pOutputClass);
                        if(level != ~size_t(0)) // level != -1 => inheritance relation => pointers are related
                        {
                            auto* pPtr = new pointer_conversion(a_pInput, pOutputArrayItemType, level, pInputClass->getBaseClassOffsetCascade(pOutputClass));
                            if(adjustmentCount)
                                conv = new default_conversion_sequence(pPtr, new qualification_adjustment(constAdjustment.first, constAdjustment.second, adjustmentCount));
                            conv = new default_conversion_sequence(pPtr);
                            return; /// success Derived[N] -> Base (const)[N]
                        }
                    }
                }
            }
            /// Array to pointer conversion
            else if(pOutput->asDataPointerType())
            {
                DataPointerType* pOutputPointerType = static_cast<DataPointerType*>(pOutput);
                a_pInput->removeArray()->pointerType()->visit(this, a_Data);
                if(conv)  /// success X[N] -> Y*
                {
                    conv->input = a_pInput;
                }
            }
        }
        return;
    }
    visit(static_cast<Type*>(a_pInput), a_Data);
}
void CPlusPlus::visit( Block*                       a_pInput, visitor_data a_Data)
{
    switch(a_Data.id)
    {
    case e_Function_QualifiedLookup:
        visit(static_cast<Statement*>(a_pInput), a_Data);
        return;

    case e_Function_UnqualifiedLookup:
        {
            if(NOT(a_pInput->isTemplateElement())) /// if template element, 'this' is template dependant and cannot be used in unqualified lookup
            {
                LocalVariable* pThis = a_pInput->getLocalVariable("this");
                if(pThis)
                {
                    const string& in_name = *(const string*)a_Data.in[0];
                    const vector<LanguageElement*>* in_pTemplateArguments = (const vector<LanguageElement*>*)a_Data.in[1];
                    const vector<Expression*>* in_pFunctionArguments = (const vector<Expression*>*)a_Data.in[2];
                    Type* in_pInitializationType = (Type*)a_Data.in[3];
                    LanguageElement* in_pContextScope = *(LanguageElement**)a_Data.in[4];
                    LanguageElement*& out_pResult = *(LanguageElement**)a_Data.out[0];
                    Expression* pThisExpression = pThis->toExpression()->dereference();
                    out_pResult = qualifiedLookup(pThisExpression, in_name, in_pTemplateArguments, in_pFunctionArguments, in_pContextScope, in_pInitializationType);
                    if(out_pResult == nullptr)
                    {
                        o_dynamic_delete pThisExpression;
                    }
                    else if(out_pResult->isInvalid())
                    {
                        if(out_pResult->getOwner() == nullptr)
                        {
                            o_dynamic_delete out_pResult;
                        }
                    }
                    else return;
                }
            }
            visit(static_cast<Statement*>(a_pInput), a_Data);
        }
        return;

    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            LocalVariable* pThis = a_pInput->getLocalVariable("this");
            pInstanciated = a_pInput->getParentBlock() 
                                ? o_new(Block)(a_pInput->getParentBlock()) 
                                : o_new(Block)(o_resolveT(Subroutine, a_pInput->getSubroutine()), pThis);
            Block* pBlock = static_cast<Block*>(pInstanciated);
            for(auto it = a_pInput->beginLocalVariables(); it != a_pInput->endLocalVariables(); ++it)
            {
                pBlock->addLocalVariable(o_instanciateT(LocalVariable, *it));
            }
            for(auto it = a_pInput->beginStatements(); it != a_pInput->endStatements(); ++it)
            {
                pBlock->addStatement(o_instanciateT(Statement, *it));
            }
            for(auto it = a_pInput->beginRAIIDestructionStatements(); it != a_pInput->endRAIIDestructionStatements(); ++it)
            {
                pBlock->addRAIIDestructionStatement(o_instanciateT(Statement, *it));
            }
            visit(static_cast<Scope*>(a_pInput), a_Data);
        }
        return;
    }
    visit(static_cast<Statement*>(a_pInput), a_Data);
}
void CPlusPlus::visit( BranchIfNotStatement*        a_pInput, visitor_data a_Data)
{
    switch(a_Data.id)
    {
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(BranchIfNotStatement)(o_instanciateT(Expression, a_pInput->getExpression())
                , o_instanciateT(LabelStatement, a_pInput->getLabelStatement()));
        }
        return;
    }
    visit(static_cast<BranchStatement*>(a_pInput), a_Data);
}
void CPlusPlus::visit( BranchIfStatement*           a_pInput, visitor_data a_Data)
{
    switch(a_Data.id)
    {
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(BranchIfStatement)(o_instanciateT(Expression, a_pInput->getExpression())
                                                    , o_instanciateT(LabelStatement, a_pInput->getLabelStatement()));
        }
        return;
    }
    visit(static_cast<BranchStatement*>(a_pInput), a_Data);
}
void CPlusPlus::visit( BranchStatement*             a_pInput, visitor_data a_Data)
{
    switch(a_Data.id)
    {
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(BranchStatement)(o_instanciateT(LabelStatement, a_pInput->getLabelStatement()));
        }
        return;
    }
    visit(static_cast<Statement*>(a_pInput), a_Data);
}
void CPlusPlus::visit( BuiltInConversionExpression* a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_definition)
            {
                if(a_pInput->getConversionType() == e_implicit_conversion)
                {
                    a_pInput->getInputExpression()->visit(this, a_Data);
                }
                else 
                {
                    LanguageElement* in_pScope = *(LanguageElement**)a_Data.in[1];
                    string& translation = *(string*)a_Data.out[0];
                    switch(a_pInput->getConversionType())
                    {
                    case e_const_cast:
                        translation += "const_cast<";
                        break;
                    case e_static_cast:
                        translation += "static_cast<";
                        break;
                    case e_reinterpret_cast:
                        translation += "reinterpret_cast<";
                        break;
                    case e_explicit_cast:
                        translation += "(";
                        translate(a_pInput->getValueType(), translation, e_translation_qualified_decorated_name, in_pScope);
                        translation += ")(";
                        a_pInput->getInputExpression()->visit(this, a_Data);
                        translation += ")";
                        return;
                    }
                    translate(a_pInput->getValueType(), translation, e_translation_qualified_decorated_name, in_pScope);
                    translation += ">(";
                    a_pInput->getInputExpression()->visit(this, a_Data);
                    translation += ")";
                }
            }
        }
        return;
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(BuiltInConversionExpression)(o_instanciateT(Expression, a_pInput->getInputExpression())
                                                                , a_pInput->getConversion()->clone(), a_pInput->getConversionType());
        }
        return;
    }
    visit(static_cast<Expression*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( BuiltInOperator*             a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void CPlusPlus::visit( BuiltInOperatorExpression*   a_pInput, visitor_data a_Data) 
{ 
    switch(a_Data.id)
    {
    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_definition)
            {
                LanguageElement* in_pScope = *(LanguageElement**)a_Data.in[1];
                string& translation = *(string*)a_Data.out[0];
                string name = a_pInput->getOperator()->getName();
                switch(a_pInput->getOperator()->getOperatorType())
                {
                case e_OperatorType_Binary:
                    translation += '(';
                    a_pInput->getArgument(0)->visit(this, a_Data);
                    translation += ")";
                    translation += name;
                    translation += '(';
                    a_pInput->getArgument(1)->visit(this, a_Data);
                    translation += ")";
                    break;
                case e_OperatorType_UnaryPrefixed:
                    translation += name;
                    translation += '(';
                    a_pInput->getArgument(0)->visit(this, a_Data);
                    translation += ")";
                    break;
                case e_OperatorType_UnaryPostfixed:
                    translation += '(';
                    a_pInput->getArgument(0)->visit(this, a_Data);
                    translation += ")";
                    translation += name;
                    break;
                case e_OperatorType_Ternary:
                    translation += '(';
                    a_pInput->getArgument(0)->visit(this, a_Data);
                    translation += ")?(";
                    a_pInput->getArgument(1)->visit(this, a_Data);
                    translation += "):(";
                    a_pInput->getArgument(2)->visit(this, a_Data);
                    translation += ')';
                    break;
                }
            }
        }
        return;
    }
    visit(static_cast<Expression*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( CallExpression*              a_pInput, visitor_data a_Data) 
{ 
    switch(a_Data.id)
    {
    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_definition)
            {
                LanguageElement* in_pScope = *(LanguageElement**)a_Data.in[1];
                string& translation = *(string*)a_Data.out[0];
                Subroutine* pSubroutine = a_pInput->getSubroutine();
                o_assert(pSubroutine);
                const vector<Expression*>& arguments = a_pInput->getArguments();
                string subroutineName;
                translate(pSubroutine, subroutineName, e_translation_qualified_name, in_pScope);
                o_assert(subroutineName.size());
                if(pSubroutine->asMemberFunction())
                {
                    if(subroutineName.compare(0, 8, "operator") == 0)
                    {
                        char c = subroutineName[8];
                        if( NOT((c >= 'a' AND c <= 'z' )
                            OR (c >= 'A' AND c <= 'Z' )
                            OR (c >= '0' AND c <= '9')
                            OR  c == '_'))
                        {
                            string op = subroutineName.substr(8);
                            if(op == "[]")
                            {
                                translation += '(';
                                arguments[0]->visit(this, a_Data);
                                translation += ")[";
                                arguments[1]->visit(this, a_Data);
                                translation += ']';
                            }
                            else if(op == "()")
                            {
                                translation += '(';
                                arguments[0]->visit(this, a_Data);
                                translation += ")(";
                                if(arguments.size() > 1)
                                {
                                    for(size_t i = 1; i<arguments.size(); ++i)
                                    {
                                        if(i != 1)
                                            translation += ',';
                                        arguments[i]->visit(this, a_Data);
                                    }
                                }
                                translation += ')';
                            }
                            else
                            {
                                // Create operator expression
                                translation += '(';
                                arguments[0]->visit(this, a_Data);
                                translation += ')';
                                translation += op;
                                if(arguments.size() == 2)
                                {
                                    translation += '(';
                                    arguments[1]->visit(this, a_Data);
                                    translation += ')';
                                }
                            }
                            return;
                        }
                    }
                    translation += '(';
                    arguments[0]->visit(this, a_Data);
                    translation += ')';
                    translation += '.';
                    translation += subroutineName;
                    translation += '(';
                    if(arguments.size() > 1)
                    {
                        for(size_t i = 1; i<arguments.size(); ++i)
                        {
                            if(i != 1)
                                translation += ',';
                            arguments[i]->visit(this, a_Data);
                        }
                    }
                    translation += ')';
                }
                else 
                {
                    translation += subroutineName;
                    translation += '(';
                    if(arguments.size())
                    {
                        for(size_t i = 0; i<arguments.size(); ++i)
                        {
                            if(i != 0)
                                translation += ',';
                            arguments[i]->visit(this, a_Data);
                        }
                    }
                    translation += ')';
                }
            }
        }
        break;
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            vector<Expression*> newArguments;
            for(auto it = a_pInput->beginArguments(); it != a_pInput->endArguments(); ++it)
            {
                newArguments.push_back(o_instanciateT(Expression, *it));
            }
            Type* pConstructionType = a_pInput->getValueType() == a_pInput->getSubroutine()->getReturnType() ? nullptr : a_pInput->getValueType();
            pInstanciated = o_new(CallExpression)(o_resolveT(Subroutine, a_pInput->getSubroutine()), newArguments, pConstructionType);
//             }
//             else 
//             {
//                 o_assert(a_pInput->getSubroutine()->asPlaceholder());
//                 Expression* pThis = arguments[0];
//                 arguments.erase(arguments.begin());
//                 string name = a_pInput->getSubroutine()->getName();
//                 size_t pos = 0;
//                 if((pos = name.find_last_of(":")) != string::npos)
//                 {
//                     Class* pClass = pThis->getValueType()->removeConstReference()->asClass();
//                     if(pClass == nullptr) 
//                     {
//                         pInstanciated = o_new(CallExpression)(o_resolveT(Subroutine, a_pInput->getSubroutine()), arguments, pConstrucionType, a_pCallExpression->getModifiers());
//                         return; 
//                     }
//                     LanguageElement* pScope = phantom::elementByName(name.substr(0, pos-1), pClass);
//                     if(pScope == nullptr 
//                         OR pScope->asClass() == nullptr 
//                         OR NOT(pClass->hasBaseClassCascade(pScope->asClass())))
//                     {
//                         pInstanciated = o_new(CallExpression)(o_resolveT(Subroutine, a_pInput->getSubroutine()), arguments, pConstrucionType, a_pCallExpression->getModifiers());
//                         return; 
//                     }
//                     pInstanciated = pClass->precompileDotExpression(this, pThis->implicitCast(pClass->lvalueReferenceType()), name.substr(pos+1), nullptr, &arguments);
//                 }
//                 else pInstanciated = pThis->getValueType()->precompileDotExpression(this, pThis, name, nullptr, &arguments);
//             }
        }
        return;
    }
    visit(static_cast<Expression*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( Class*                       a_pInput, visitor_data a_Data)
{
    switch(a_Data.id)
    {
    case e_Function_QualifiedNameLookup:
        {
            vector<LanguageElement*>& out_candidates = *(vector<LanguageElement*>*)a_Data.out[0];
            vector<modifiers_t>& out_accesses = *(vector<modifiers_t>*)a_Data.out[1];
            visit(static_cast<ClassType*>(a_pInput), a_Data);
            if(out_candidates.size()) 
                return;
            const string& in_name = *(const string*)a_Data.in[0];
            for(auto it = a_pInput->beginBaseClasses(); it != a_pInput->endBaseClasses(); ++it)
            {
                if(it->m_pClass->getName() == in_name)
                {
                    out_candidates.push_back(it->m_pClass);
                    out_accesses.push_back(it->m_Access);
                    return;
                }
            }
            for(auto it = a_pInput->beginBaseClasses(); it != a_pInput->endBaseClasses(); ++it)
            {
                it->m_pClass->visit(this, a_Data);
            }
        }
        return;

    case e_Function_SubroutineResolution:
        {
            LanguageElement*& out_pResult = *(LanguageElement**)a_Data.out[0];
            if(out_pResult) return;
            visit(static_cast<ClassType*>(a_pInput), a_Data);
            if(out_pResult) return;
            for(auto it = a_pInput->beginBaseClasses(); it != a_pInput->endBaseClasses(); ++it)
            {
                visitor_data subData = a_Data;
                LanguageElement* pSubResult = 0;
                void* out[1] = {&pSubResult};
                subData.out = out;
                it->m_pClass->visit(this, subData);
                if(pSubResult)
                {
                    if(out_pResult) 
                    {
                        //o_semantic_error("ambiguous base member function selection");
                        out_pResult = nullptr;
                        return;
                    }
                    else 
                    {
                        out_pResult = pSubResult;
                    }
                }
            }
        }
        return;

    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            if(pInstanciated == nullptr) pInstanciated = o_new(Class)(a_pInput->getName(), a_pInput->getModifiers());
            Class* pClass = pInstanciated->asClass();
            o_assert(pClass);
            for(auto it = a_pInput->beginBaseClasses(); it != a_pInput->beginBaseClasses(); ++it)
            {
                pClass->addBaseClass(o_instanciateT(Class, it->m_pClass));
            }
            for(auto it = a_pInput->beginSignals(); it != a_pInput->endSignals(); ++it)
            {
                pClass->addSignal(o_instanciateT(Signal, *it));
            }
            visit(static_cast<ClassType*>(a_pInput), a_Data);
        }
        return;
    }
    visit(static_cast<ClassType*>(a_pInput), a_Data);
}
void CPlusPlus::visit( ClassType*                   a_pInput, visitor_data a_Data)
{
    switch(a_Data.id)
    {
    case e_Function_SubroutineResolution:
        visit(static_cast<Scope*>(a_pInput), a_Data);
        return;
    case e_Function_QualifiedLookup:
        visit(static_cast<Type*>(a_pInput), a_Data);
        return;

    case e_Function_QualifiedNameLookup:
        {
            const string& in_name = *(const string*)a_Data.in[0];
            vector<LanguageElement*>& out_candidates = *(vector<LanguageElement*>*)a_Data.out[0];
            if(a_pInput->isNative() AND a_pInput->getTemplateSpecialization() AND phantom::reflection::native::currentScope()) /// for native C++ reflection declaration symbol resolution
            {
                LanguageElement* pElement = a_pInput->getTemplateSpecialization()->getArgument(in_name);
                if(pElement) 
                {
                    out_candidates.push_back(pElement);
                    return;
                }
            }
        }
        break;

    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            if(pInstanciated)
            {
                visit(static_cast<Type*>(a_pInput), a_Data);
                visit(static_cast<Scope*>(a_pInput), a_Data);
                ClassType* pClassType = pInstanciated->asClassType();
                for(auto it = a_pInput->beginMemberFunctions(); it != a_pInput->endMemberFunctions(); ++it)
                {
                    MemberFunction* pMemberFunction = o_instanciateT(MemberFunction, *it);
                    if(pMemberFunction->asSignal() == nullptr)
                    {
                        pClassType->addMemberFunction(pMemberFunction);
                    }
                }
                for(auto it = a_pInput->beginDataMembers(); it != a_pInput->endDataMembers(); ++it)
                {
                    pClassType->addDataMember(o_instanciateT(DataMember, *it));
                }
                for(auto it = a_pInput->beginConstructors(); it != a_pInput->endConstructors(); ++it)
                {
                    pClassType->addConstructor(o_instanciateT(Constructor, *it));
                }
                for(auto it = a_pInput->beginProperties(); it != a_pInput->endProperties(); ++it)
                {
                    pClassType->addProperty(o_instanciateT(Property, *it));
                }
            }
        }
        return;
    }
    visit(static_cast<Type*>(a_pInput), a_Data);
}
void CPlusPlus::visit( CompositionClass* a_pInput, visitor_data a_Data )
{
    visit(static_cast<Class*>(a_pInput), a_Data);
}
void CPlusPlus::visit( Constant*                    a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_definition)
            {
                LanguageElement* in_pScope = *(LanguageElement**)a_Data.in[1];
                string& translation = *(string*)a_Data.out[0];
                a_pInput->toString(translation);
            }
        }
        return;
    case e_Function_ToExpression:
        {
            Expression* in_pLeftExpression = *(Expression**)a_Data.in[0];
            Expression*& out_pExpression = *(Expression**)a_Data.out[0];
            if(in_pLeftExpression) return;
            out_pExpression = a_pInput->toExpression();
            return;
        }
    }
    visit(static_cast<NamedElement*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( ConstantExpression*          a_pInput, visitor_data a_Data) 
{ 
    switch(a_Data.id)
    {
    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_definition)
            {
                LanguageElement* in_pScope = *(LanguageElement**)a_Data.in[1];
                string& translation = *(string*)a_Data.out[0];
                a_pInput->getConstant()->visit(this, a_Data);
            }
        }
        return;

    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(ConstantExpression)(o_resolveT(Constant, a_pInput->getConstant()));
        }
        return;
    }
    visit(static_cast<Expression*>(a_pInput), a_Data);
}
void CPlusPlus::visit( Constructor*                 a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(Constructor)(a_pInput->getName(), o_instanciateT(Signature, a_pInput->getSignature()), a_pInput->getModifiers());
            visit(static_cast<MemberFunction*>(a_pInput), a_Data);
        }
        return;
    }
    visit(static_cast<MemberFunction*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( ConstructorCallExpression*   a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_definition)
            {
                LanguageElement* in_pScope = *(LanguageElement**)a_Data.in[1];
                string& translation = *(string*)a_Data.out[0];
                translate(a_pInput->getSubroutine()->getOwner(), translation, e_translation_qualified_decorated_name, in_pScope);
                translation += '(';
                for(auto it = a_pInput->beginArguments(); it != a_pInput->endArguments(); ++it)
                {
                    if(it != a_pInput->beginArguments())
                    {
                        translation+=',';
                    }
                    (*it)->visit(this, a_Data);
                }
                translation += ')';
            }
        }
        return;

    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];  
            vector<Expression*> newArguments;
            for(auto it = a_pInput->beginArguments(); it != a_pInput->endArguments(); ++it)
            {
                newArguments.push_back(o_instanciateT(Expression, *it));
            }
            pInstanciated = o_new(ConstructorCallExpression)(
                o_resolveT(Constructor, a_pInput->getSubroutine())
                , newArguments
            ); 
            visit(static_cast<CallExpression*>(a_pInput), a_Data); 
        }
        return;
    }
    visit(static_cast<CallExpression*>(a_pInput), a_Data);  
}
void CPlusPlus::visit( ConstType*                   a_pInput, visitor_data a_Data)
{
    switch(a_Data.id)
    {
    case e_Function_TemplateArgumentDeduction:
        {
            LanguageElement* pArgument = *(LanguageElement* const *)a_Data.in[0];
            LanguageElement*& pDeducedArgument = *(LanguageElement**)a_Data.out[0];
            map<Placeholder*, LanguageElement*>& deductions = *(map<Placeholder*, LanguageElement*>*)a_Data.out[1];
            ConstType* pType = pArgument->asConstType();
            if(pType)
            {
                Type* pDeducedType = templateArgumentDeduction(a_pInput->getConstedType(), pType->getConstedType(), deductions);
                if(pDeducedType)
                {
                    pDeducedArgument = pDeducedType->constType();
                }
            }
            else 
            {
                ConstVolatileType* pType = pArgument->asConstVolatileType();
                if(pType)
                {
                    Type* pDeducedType = templateArgumentDeduction(a_pInput->getConstedType(), pType->removeConst(), deductions);
                    if(pDeducedType)
                    {
                        pDeducedArgument = pDeducedType->constType();
                    }
                }
            }
        }
        return;

    case e_Function_Conversion:
        {
            /// Substitution
            a_pInput->getConstedType()->visit(this, a_Data);
        }
        return;

    case e_Function_ResolveTemplateDependencies:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pResolved = *(LanguageElement**)a_Data.out[0];
            Type* pType = o_resolveT(Type, a_pInput->getConstedType());
            pResolved = pType ? pType->constType() : nullptr;
        }
        return;
    }
    visit(static_cast<Type*>(a_pInput), a_Data);
}
void CPlusPlus::visit( ConstVolatileType*           a_pInput, visitor_data a_Data)
{
    switch(a_Data.id)
    {
    case e_Function_TemplateArgumentDeduction:
        {
            LanguageElement* pArgument = *(LanguageElement* const *)a_Data.in[0];
            LanguageElement*& pDeducedArgument = *(LanguageElement**)a_Data.out[0];
            map<Placeholder*, LanguageElement*>& deductions = *(map<Placeholder*, LanguageElement*>*)a_Data.out[1];
            ConstVolatileType* pType = pArgument->asConstVolatileType();
            if(pType)
            {
                Type* pDeducedType = templateArgumentDeduction(a_pInput->getConstVolatiledType(), pType->getConstVolatiledType(), deductions);
                if(pDeducedType)
                {
                    pDeducedArgument = pDeducedType->constVolatileType();
                }
            }
        }
        return;

    case e_Function_Conversion:
        {
            /// Substitution
            a_pInput->getConstVolatiledType()->visit(this, a_Data);
        }
        return;

    case e_Function_ResolveTemplateDependencies:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pResolved = *(LanguageElement**)a_Data.out[0];
            Type* pType = o_resolveT(Type, a_pInput->getConstVolatiledType());
            pResolved = pType ? pType->constVolatileType() : nullptr;
        }
        return;
    }
    visit(static_cast<Type*>(a_pInput), a_Data);
}
void CPlusPlus::visit( ContainerClass*              a_pInput, visitor_data a_Data) { visit(static_cast<Class*>(a_pInput), a_Data); }
void CPlusPlus::visit( DataExpression*              a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_definition)
            {
                LanguageElement* in_pScope = *(LanguageElement**)a_Data.in[1];
                string& translation = *(string*)a_Data.out[0];
                translation += "@(";
                a_pInput->getGuidExpression()->visit(this, a_Data);
                translation += ')';
            }
        }
        return;

    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(DataExpression)(a_pInput->getDataBase(), o_instanciateT(ConstantExpression, a_pInput->getGuidExpression()));
        }
        return;
    }
    visit(static_cast<Expression*>(a_pInput), a_Data);
}
void CPlusPlus::visit( DataMember*                  a_pInput, visitor_data a_Data) 
{ 
    switch(a_Data.id)
    {
    case e_Function_ToExpression:
        {
            Expression* in_pLeftExpression = *(Expression**)a_Data.in[0];
            Expression*& out_pExpression = *(Expression**)a_Data.out[0];
            if(in_pLeftExpression == nullptr) return;
            in_pLeftExpression = convert(in_pLeftExpression, in_pLeftExpression->getValueType()->replicate(a_pInput->getOwnerClassType()));
            if(in_pLeftExpression == nullptr) return; 
            out_pExpression = o_new(DataMemberExpression)(in_pLeftExpression, a_pInput);
        }
        return;
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(DataMember)(o_resolveT(Type, a_pInput->getValueType())
                , a_pInput->getName(), o_instanciateT(Range, a_pInput->getRange()), a_pInput->getSerializationMask(), a_pInput->getModifiers());
        }
        return;
    }
    visit(static_cast<NamedElement*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( DataMemberExpression*        a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_definition)
            {
                LanguageElement* in_pScope = *(LanguageElement**)a_Data.in[1];
                string& translation = *(string*)a_Data.out[0];
                translation += "(";
                a_pInput->getLeftExpression()->visit(this, a_Data);
                translation += ").";
                translation += a_pInput->getDataMember()->getName();
            }
        }
        return;
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            o_assert(a_pInput->getDataMember()->asPlaceholder());
            pInstanciated = o_new(DataMemberExpression)(o_instanciateT(Expression, a_pInput->getLeftExpression())
                    , o_resolveT(DataMember, a_pInput->getDataMember()));
        }
        return;
    }
    visit(static_cast<LValueExpression*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( DataMemberPointerExpression* a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_definition)
            {
                LanguageElement* in_pScope = *(LanguageElement**)a_Data.in[1];
                string& translation = *(string*)a_Data.out[0];
                translation += '(';
                a_pInput->getObjectExpression()->visit(this, a_Data);
                translation += ").*(";
                a_pInput->getMemberExpression()->visit(this, a_Data);
                translation += ')';
            }
        }
        return;

    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(DataMemberPointerExpression)(
                o_resolveT(DataMemberPointerType, a_pInput->getDataMemberPointerType())
                , o_instanciateT(Expression, a_pInput->getObjectExpression())
                , o_instanciateT(Expression, a_pInput->getMemberExpression())
                );
        }
        return;
    }
    visit(static_cast<Expression*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( DataMemberPointerType*       a_pInput, visitor_data a_Data)
{
    switch(a_Data.id)
    {
    case e_Function_Conversion:
        {
            Type* pOutput = *(Type* const *)a_Data.in[0];
            int iConversionType = *(int const*)a_Data.in[1];
            int iUserDefinedConversionsAllowed = *(int const*)a_Data.in[2];
            conversion*& conv = *(conversion**)a_Data.out[0];
            bool bConstRef = baseConversion(a_pInput, pOutput, iConversionType);

            if(pOutput->equals(a_pInput)) 
            {
                conv = bConstRef 
                    ? new default_conversion_sequence(new constref_conversion(pOutput))
                    : new default_conversion_sequence((value_t)a_pInput, (value_t)pOutput);
                return; /// success X (Class::*) -> X (Class::*)
            }

            if(pOutput->asDataMemberPointerType())
            {
                DataMemberPointerType* pOutputDataMemberPointerType = static_cast<DataMemberPointerType*>(pOutput);

                if(a_pInput->getValueType()->equals(pOutputDataMemberPointerType->getValueType())) /// same data member Type* type
                {
                    if((a_pInput->getObjectType()->asClass() != nullptr) AND (pOutputDataMemberPointerType->getObjectType()->asClass() != nullptr)) 
                    {
                        reflection::Class* pInputClass  = static_cast<reflection::Class*>(a_pInput->getObjectType());
                        reflection::Class* pOutputClass   = static_cast<reflection::Class*>(pOutputDataMemberPointerType->getObjectType());
                        size_t level = pInputClass->getInheritanceLevelFromBase(pOutputClass);
                        if(level != ~size_t(0)) // level != -1 => inheritance relation => pointers are related
                        {
                            auto* pPtr = new data_member_pointer_conversion(a_pInput, pOutputDataMemberPointerType, level, pInputClass->getBaseClassOffsetCascade(pOutputClass));

                            //                     if(adjustmentCount)
                            //                     {
                            //                         conv = bConstRef 
                            //                             ? new default_conversion_sequence(pPtr, new qualification_adjustment(constAdjustment.first, constAdjustment.second, adjustmentCount), new constref_conversion(pOutput))
                            //                             : new default_conversion_sequence(pPtr, new qualification_adjustment(constAdjustment.first, constAdjustment.second, adjustmentCount));
                            //                     }
                            conv = bConstRef 
                                ? new default_conversion_sequence(pPtr, new constref_conversion(pOutput))
                                : new default_conversion_sequence(pPtr);
                            return; /// success X (Derived::*) -> X (Base::*)

                        }
                    }
                }
            }
        }
        break;

    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_resolveT(ClassType, a_pInput->getObjectType())->dataMemberPointerType(o_resolveT(ClassType, a_pInput->getValueType()));
        }
        return;
    }
    visit(static_cast<MemberPointerType*>(a_pInput), a_Data);
}
void CPlusPlus::visit( DataPointerType*             a_pInput, visitor_data a_Data)
{
    switch(a_Data.id)
    {
    case e_Function_TemplateArgumentDeduction:
        {
            LanguageElement* pArgument = *(LanguageElement* const *)a_Data.in[0];
            LanguageElement*& pDeducedArgument = *(LanguageElement**)a_Data.out[0];
            map<Placeholder*, LanguageElement*>& deductions = *(map<Placeholder*, LanguageElement*>*)a_Data.out[1];
            DataPointerType* pDataPointerType = pArgument->asDataPointerType();
            if(pDataPointerType)
            {
                Type* pPointedDeducedType = templateArgumentDeduction(a_pInput->getPointedType(), pDataPointerType->getPointedType(), deductions);
                if(pPointedDeducedType)
                {
                    pDeducedArgument = pPointedDeducedType->pointerType();
                }
            }
        }
        return;

    case e_Function_Conversion:
        {
            Type* pOutput = *(Type* const *)a_Data.in[0];
            int iConversionType = *(int const*)a_Data.in[1];
            int iUserDefinedConversionsAllowed = *(int const*)a_Data.in[2];
            conversion*& conv = *(conversion**)a_Data.out[0];
            std::pair<Type*, Type*> constAdjustment;
            size_t adjustmentCount = 0;
            bool bConstRef;
            conv = baseStandardConversion(a_pInput, pOutput, iConversionType, bConstRef);
            if(conv) return;
            switch(iConversionType)
            {
            case e_const_cast: 
                {
                    Type* pInputNoConst = a_pInput->removeAllQualifiers();
                    Type* pOutputNoConst = pOutput->removeAllQualifiers();
                    if(pInputNoConst->equals(a_pInput) AND pOutputNoConst->equals(pOutput)) 
                    {
                        return; /// input or output do not have const (or volatile ?) => const_cast fail
                    }
                    if(pInputNoConst->equals(pOutputNoConst)) /// no-cv input == no-cv output => const_cast ok
                    {
                        conv = new default_conversion_sequence(pInputNoConst);
                    }
                    return;
                }
            case e_reinterpret_cast:
                {
                    if((pOutput->asIntegralType() AND pOutput->getSize() >= sizeof(void*) )
                        OR pOutput->asDataPointerType())
                    {
                        conv = new default_conversion_sequence(a_pInput, (value_t)pOutput);
                        return;
                    }
                }
            }
            /// ex: X*
            DataPointerType* pOutputPointerType = pOutput->asDataPointerType();
            /// ex X const*
            if(pOutputPointerType)
            {
                if(pOutputPointerType->getPointedType()->asConstType())
                {
                    /// X* => Y const*
                    DataPointerType* adjustmentInput = pOutputPointerType->getPointedType()->removeConst()->pointerType();
                    constAdjustment.first = adjustmentInput;
                    constAdjustment.second = pOutputPointerType; 
                    adjustmentCount++;
                    pOutputPointerType = adjustmentInput;
                }
                else if(a_pInput->getPointedType()->asConstType())
                {
                    return; /// X const* -/-> Y*
                }
                if(a_pInput->equals(pOutputPointerType))
                {
                    if(adjustmentCount)
                    {
                        conv = bConstRef 
                            ? new default_conversion_sequence(new qualification_adjustment(constAdjustment.first, constAdjustment.second, adjustmentCount), new constref_conversion(pOutput))
                            : new default_conversion_sequence(new qualification_adjustment(constAdjustment.first, constAdjustment.second, adjustmentCount));
                    }
                    else 
                    {
                        conv = bConstRef 
                            ? new default_conversion_sequence(new constref_conversion(pOutput)) 
                            : new default_conversion_sequence(a_pInput); // canonical conversion
                    }
                    return; /// success X* -> X const*
                }
                if(pOutputPointerType->getDataPointerLevel() == 1)
                {
                    Type* pOutputPointedType = pOutputPointerType->getPointedType();
                    if(a_pInput->getDataPointerLevel() == 1)
                    {
                        Type* pInputPointedType = a_pInput->getPointedType();
                        if((pInputPointedType->asClass() != nullptr) AND (pOutputPointedType->asClass() != nullptr)) 
                        {
                            reflection::Class* pInputClass  = static_cast<reflection::Class*>(pInputPointedType);
                            reflection::Class* pOutputClass   = static_cast<reflection::Class*>(pOutputPointedType);
                            size_t level = pInputClass->getInheritanceLevelFromBase(pOutputClass);

                            if(level != ~size_t(0)) // level != -1 => inheritance relation => pointers are related
                            {
                                auto* pPtr = new pointer_conversion(a_pInput, pOutputPointerType, level, pInputClass->getBaseClassOffsetCascade(pOutputClass));
                                if(adjustmentCount)
                                {
                                    conv = bConstRef 
                                        ? new default_conversion_sequence(pPtr, new qualification_adjustment(constAdjustment.first, constAdjustment.second, adjustmentCount), new constref_conversion(pOutput))
                                        : new default_conversion_sequence(pPtr, new qualification_adjustment(constAdjustment.first, constAdjustment.second, adjustmentCount));
                                }
                                else conv = bConstRef 
                                    ? new default_conversion_sequence(pPtr, new constref_conversion(pOutput)) 
                                    : new default_conversion_sequence(pPtr); // canonical conversion
                                return; /// success Derived* -> Base*
                            }
                            else if(iConversionType == e_explicit_cast OR iConversionType == e_static_cast)
                            {
                                level = pOutputClass->getInheritanceLevelFromBase(pInputClass);
                                if(level != ~size_t(0)) // level != -1 => inheritance relation => pointers are related
                                {
                                    auto* pPtr = new pointer_conversion(a_pInput, pOutputPointerType, level, -(ptrdiff_t)pOutputClass->getBaseClassOffsetCascade(pInputClass));
                                    conv = bConstRef 
                                        ? new default_conversion_sequence(pPtr, new constref_conversion(pOutput))
                                        : new default_conversion_sequence(pPtr);
                                    return; /// success Base* -> Derived*
                                }
                            }
                        }
                    }
                    if(pOutputPointedType == Types::TYPE_VOID)
                    {
                        auto* pPtr = new numeric_conversion(a_pInput, pOutputPointerType, false, ~size_t(0));
                        if(adjustmentCount)
                        {
                            conv = bConstRef 
                                ? new default_conversion_sequence(pPtr, new qualification_adjustment(constAdjustment.first, constAdjustment.second, adjustmentCount), new constref_conversion(pOutput))
                                : new default_conversion_sequence(pPtr, new qualification_adjustment(constAdjustment.first, constAdjustment.second, adjustmentCount));
                        }
                        else conv = bConstRef 
                            ? new default_conversion_sequence(pPtr, new constref_conversion(pOutput)) 
                            : new default_conversion_sequence(pPtr); // canonical conversion
                        return; /// success X* -> void*
                    }
                }
                if(iConversionType == e_explicit_cast) /// If nothing has been found for explicit until now, consider it as a pointer reinterpretation
                {
                    if(pOutput->removeQualifiers()->asDataPointerType()
                        OR pOutput->asIntegralType() AND pOutput->getSize() >= sizeof(void*))
                    {
                        conv = new default_conversion_sequence(a_pInput, (value_t)pOutput);
                        return; /// success X* -> Y* or int_X -> Y*
                    }
                }
            }
        }
        break;

    case e_Function_ResolveTemplateDependencies:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pResolved = *(LanguageElement**)a_Data.out[0];
            Type* pType = o_resolveT(Type, a_pInput->getPointedType());
            pResolved = pType ? pType->pointerType() : nullptr;
        }
        return;
    }
    visit(static_cast<PointerType*>(a_pInput), a_Data);
}
void CPlusPlus::visit( Ellipsis*                    a_pInput, visitor_data a_Data) { /*visit(static_cast<LanguageElement*>(a_pInput), a_Data);*/ }
void CPlusPlus::visit( Enum*                        a_pInput, visitor_data a_Data)
{
    switch(a_Data.id)
    {
    case e_Function_Conversion:
        {
            Type* pOutput = *(Type* const *)a_Data.in[0];
            int iConversionType = *(int const*)a_Data.in[1];
            int iUserDefinedConversionsAllowed = *(int const*)a_Data.in[2];
            conversion*& conv = *(conversion**)a_Data.out[0];
            bool bConstRef;
            baseStandardConversion(a_pInput, pOutput, iConversionType, bConstRef);
            if(pOutput->equals(a_pInput))
            {
                conv = bConstRef ? new default_conversion_sequence(new constref_conversion(pOutput)) : new default_conversion_sequence(a_pInput);
                return;
            }
            a_pInput->getIntType()->visit(this, a_Data);
            if(conv) 
            {
                conv->input = a_pInput;
                if(bConstRef)
                    static_cast<default_conversion_sequence*>(conv)->addConstRef();
                return;
            }
        }
    }
    visit(static_cast<Type*>(a_pInput), a_Data);
}
void CPlusPlus::visit( Evaluable*                   a_pInput, visitor_data a_Data) { visit(static_cast<LanguageElement*>(a_pInput), a_Data); }
void CPlusPlus::visit( Event*                       a_pInput, visitor_data a_Data) { visit(static_cast<StateMachineElement*>(a_pInput), a_Data); }
void CPlusPlus::visit( Expression*                  a_pInput, visitor_data a_Data)
{
    switch(a_Data.id)
    {
    case e_Function_ToExpression:
        {
            Expression* in_pLeftExpression = *(Expression**)a_Data.in[0];
            Expression*& out_pExpression = *(Expression**)a_Data.out[0];
            if(in_pLeftExpression) return;
            out_pExpression = a_pInput;
        }
        return;

    case e_Function_QualifiedLookup:
        {
            const string& in_name = *(const string*)a_Data.in[0];
            const vector<LanguageElement*>* in_pTemplateArguments = (const vector<LanguageElement*>*)a_Data.in[1];
            const vector<Expression*>* in_pFunctionArguments = (const vector<Expression*>*)a_Data.in[2];
            LanguageElement* in_pContextScope = *(LanguageElement**)a_Data.in[3];
            Type* in_pInitializationType = (Type*)a_Data.in[4];
            LanguageElement*& out_pResult = *(LanguageElement**)a_Data.out[0];

            Type* pExpressionEffectiveType = a_pInput->getValueType()->removeReference()->removeRValueReference()->removeConst();
            if(pExpressionEffectiveType->asClassType())
            {
                /// Find all candidates
                visitor_data data;
                vector<LanguageElement*> candidates;
                data.id = e_Function_QualifiedNameLookup;
                modifiers_t inAccess = o_public_access;
                const void* in[3] = {&in_name, &in_pContextScope, &inAccess};
                data.in = in;
                vector<modifiers_t> outAccesses;
                void* out[2] = { &candidates, &outAccesses };
                data.out = out;
                pExpressionEffectiveType->visit(this, data);

                if(candidates.size())
                {
                    /// If this is a call
                    if(in_pFunctionArguments)
                    {
                        vector<Expression*> arguments;
                        arguments.push_back(a_pInput); // add *this
                        arguments.insert(arguments.end(), in_pFunctionArguments->begin(), in_pFunctionArguments->end()); // then arguments
                        selectCallCandidate(candidates, in_pTemplateArguments, arguments, out_pResult, in_name, in_pContextScope, in_pInitializationType);
                    }
                    else 
                    {
                        if(in_pTemplateArguments)
                        {
                            out_pResult = o_new(DataMemberExpression)(a_pInput, DataMember::Invalid());
                            out_pResult->error("invalid use of template arguments on non template member function '%s'", in_name.c_str());
                            return;
                        }
                        /// if no function signature AND multiple candidates => ambiguous
                        if(candidates.size() == 1)
                        {
                            Expression* pExpression = toExpression(candidates[0], a_pInput);
                            if(pExpression)
                            {
                                out_pResult = pExpression;
                            }
                            else 
                            {
                                out_pResult = o_new(DataMemberExpression)(a_pInput, DataMember::Invalid());
                                out_pResult->error("no member found with name '%s' in class type '%s'", in_name.c_str(), pExpressionEffectiveType->getUniqueDecoratedName().c_str());
                            }
                        }
                        else 
                        {
                            out_pResult = o_new(DataMemberExpression)(a_pInput, DataMember::Invalid());
                            out_pResult->error("ambiguous access to multiple members");
                            for(auto it = candidates.begin(); it != candidates.end(); ++it)
                            {
                                const char* word;
                                if(it == candidates.begin()) word = _canBe;
                                else word = _or;
                                out_pResult->subError("%s '%s'", ((it == candidates.begin()) ? _canBe : _or), (*it)->asNamedElement()->getDecoratedName().c_str());
                            }
                        }
                    }
                }
                else 
                {
                    out_pResult = o_new(DataMemberExpression)(a_pInput, DataMember::Invalid());
                    out_pResult->error("no member found with name '%s' in class type '%s'", in_name.c_str(), pExpressionEffectiveType->getUniqueDecoratedName().c_str());
                }
            }
            else 
            {
                out_pResult = o_new(DataMemberExpression)(a_pInput, DataMember::Invalid());
                out_pResult->error("only class types have members");
            }
        }
        break;
    }
}
void CPlusPlus::visit( ExpressionStatement*         a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(ExpressionStatement)(o_instanciateT(Expression, a_pInput->getExpression()));
        }
        return;
    }
    visit(static_cast<Statement*>(a_pInput), a_Data);
}
void CPlusPlus::visit( Function*                    a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_IsViableCallCandidate:
        {
            const vector<LanguageElement*>* templateArguments = a_Data.in[0] ? (const vector<LanguageElement*>*)a_Data.in[0] : nullptr;
            const vector<Expression*>& functionArguments = *(const vector<Expression*>*)a_Data.in[1];
            modifiers_t modifiers = *(modifiers_t*)a_Data.in[2];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[3];
            conversions& out_conversions = *(conversions*)a_Data.out[0];
            Subroutine*& out_subroutine = *(Subroutine**)a_Data.out[1];
            out_subroutine = nullptr;

            if(modifiers & o_static) // static call (no this implied)
            {
                if(functionArguments.size() < a_pInput->getMinimumNeededParameterCount()
                    OR functionArguments.size() > a_pInput->getParameterCount())
                {
                    return;
                }
                vector<Expression*> arguments;
                for(size_t i = 0; i<a_pInput->getParameterCount(); ++i)
                {
                    if(i<functionArguments.size())
                    {
                        arguments.push_back(functionArguments[i]);
                    }
                    else 
                    {
                        arguments.push_back(a_pInput->getParameter(i)->getInitializationExpression());
                    }
                }
                a_pInput->getSignature()->implicitConversions(arguments, pScope, out_conversions);
            }
            else /// not static => first argument is the implicit object argument => we skip it but first assert that it is compatible
            {
                o_assert(a_pInput->getOwner()->asClassType());
                o_assert(functionArguments.front()->getValueType()->removeReference()->removeRValueReference()->removeQualifiers()->isKindOf(a_pInput->getOwner()->asClassType()));

                if((functionArguments.size()-1) < a_pInput->getMinimumNeededParameterCount()
                    OR (functionArguments.size()-1) > a_pInput->getParameterCount())
                {
                    out_subroutine = nullptr;
                    return;
                }
                vector<Expression*> arguments;
                for(size_t i = 0; i<a_pInput->getParameterCount(); ++i)
                {
                    if(i<(functionArguments.size()-1))
                    {
                        arguments.push_back(functionArguments[i+1]);
                    }
                    else 
                    {
                        arguments.push_back(a_pInput->getParameter(i)->getInitializationExpression());
                    }
                }
                a_pInput->getSignature()->implicitConversions(this, arguments, pScope, out_conversions);
                out_subroutine = a_pInput;
            }
            return;
        }
    case e_Function_IsViableSignatureCandidate:
        {
            const vector<LanguageElement*>* templateArguments = a_Data.in[0] ? (const vector<LanguageElement*>*)a_Data.in[0] : nullptr;
            const vector<Type*>& types = *(const vector<Type*>*)a_Data.in[1];
            modifiers_t modifiers = *(modifiers_t*)a_Data.in[2];
            bool& out_result = *(bool*)a_Data.out[0];

            out_result = templateArguments 
                ? a_pInput->matches(*templateArguments, types, modifiers)
                : a_pInput->matches(types, modifiers);
        }
        break;

    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(Function)(a_pInput->getName(), o_instanciateT(Signature, a_pInput->getSignature()), a_pInput->getABI(), a_pInput->getModifiers());
            visit(static_cast<Subroutine*>(a_pInput), a_Data);
        }
        return;
    }
    visit(static_cast<Subroutine*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( FunctionPointerType*         a_pInput, visitor_data a_Data)
{
    switch(a_Data.id)
    {
    case e_Function_Conversion:
        {
            Type* pOutput = *(Type* const *)a_Data.in[0];
            int iConversionType = *(int const*)a_Data.in[1];
            int iUserDefinedConversionsAllowed = *(int const*)a_Data.in[2];
            conversion*& conv = *(conversion**)a_Data.out[0];

            bool bConstRef = baseConversion(a_pInput, pOutput, iConversionType);
            if(pOutput == Types::TYPE_VOID_PTR)
            {
                auto* pPtr = new pointer_conversion(a_pInput, pOutput);
                conv = bConstRef 
                    ? new default_conversion_sequence(pPtr, new constref_conversion(pOutput))
                    : new default_conversion_sequence(pPtr);
                return; /// success X(*)(Y,Z) -> void*
            }
            else if(pOutput->equals(a_pInput)) 
            {
                conv = bConstRef 
                    ? new default_conversion_sequence(new constref_conversion(pOutput))
                    : new default_conversion_sequence(a_pInput, (value_t)pOutput);
                return; /// success X(*)(Y,Z) -> X(*)(Y,Z)
            }
        }
        break;

    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            vector<Type*> parameters;
            for(auto it = a_pInput->getSignature()->beginParameters(); it != a_pInput->getSignature()->endParameters(); ++it)
            {
                parameters.push_back(o_resolveT(Type, (*it) ? (*it)->getValueType() : nullptr));
            }
            pInstanciated = globalNamespace()->functionPointerType(o_resolveT(Type, a_pInput->getSignature()->getReturnType()), a_pInput->getABI(), parameters);
        }            
        return;

    }
    visit(static_cast<PointerType*>(a_pInput), a_Data);
}
void CPlusPlus::visit( Import*                      a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void CPlusPlus::visit( LabelStatement*              a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(LabelStatement)(a_pInput->getLabelName());
        }
    }
}
void CPlusPlus::visit( LanguageElement*             a_pInput, visitor_data a_Data)
{
    switch(a_Data.id)
    {
    case e_Function_TemplateArgumentDeduction:
        {
            LanguageElement* pArgument = *(LanguageElement* const *)a_Data.in[0];
            LanguageElement*& pDeducedArgument = *(LanguageElement**)a_Data.out[0];
            map<Placeholder*, LanguageElement*>& deductions = *(map<Placeholder*, LanguageElement*>*)a_Data.out[1];
            if(pArgument->equals(a_pInput))
            {
                pDeducedArgument = pArgument;
            }
        }
        return;
    case e_Function_UnqualifiedLookup:
        {
            const string& in_name = *(const string*)a_Data.in[0];
            const vector<LanguageElement*>* in_pTemplateArguments = (const vector<LanguageElement*>*)a_Data.in[1];
            const vector<Expression*>* in_pFunctionArguments = (const vector<Expression*>*)a_Data.in[2];
            Type* in_pInitializationType = (Type*)a_Data.in[3];
            LanguageElement* in_pContextScope = *(LanguageElement**)a_Data.in[4];
            LanguageElement*& out_pResult = *(LanguageElement**)a_Data.out[0];
            out_pResult = qualifiedLookup(a_pInput, in_name, in_pTemplateArguments, in_pFunctionArguments, in_pContextScope, in_pInitializationType);
            if(out_pResult) 
                return;
            if(a_Data.hasFlag(e_VisitorFlag_NamespaceMode))
            {
                NamedElement* pNamedElement = a_pInput->asNamedElement();
                if(pNamedElement AND pNamedElement->getNamespace())
                {
                    pNamedElement->getNamespace()->visit(this, a_Data);
                    return;
                }
            }
            if(a_pInput->getOwner())
            {
                a_pInput->getOwner()->visit(this, a_Data);
            }
        }
        return;

    case e_Function_QualifiedLookup:
        {
            const string& in_name = *(const string*)a_Data.in[0];
            const vector<LanguageElement*>* in_pTemplateArguments = (const vector<LanguageElement*>*)a_Data.in[1];
            const vector<Expression*>* in_pFunctionArguments = (const vector<Expression*>*)a_Data.in[2];
            LanguageElement* in_pContextScope = *(LanguageElement**)a_Data.in[3];
            Type* in_pInitializationType = (Type*)a_Data.in[4];
            LanguageElement*& out_pResult = *(LanguageElement**)a_Data.out[0];

            /// Find all candidates
            visitor_data data;
            vector<LanguageElement*> candidates;
            modifiers_t inAccess = o_public_access;
            data.id = e_Function_QualifiedNameLookup;
            const void* in[3] = {&in_name, &in_pContextScope, &inAccess};
            data.in = in;
            vector<modifiers_t> outAccesses;
            void* out[2] = { &candidates, &outAccesses };
            data.out = out;

            a_pInput->visit(this, data);

            if(candidates.size())
            {
                /// If this is a call
                if(in_pFunctionArguments)
                {
                    vector<Expression*> arguments;
                    arguments.insert(arguments.end(), in_pFunctionArguments->begin(), in_pFunctionArguments->end()); // then arguments
                    selectCallCandidate(candidates, in_pTemplateArguments, arguments, out_pResult, in_name, in_pContextScope, in_pInitializationType, o_static);
                    return;
                }
                else 
                {
                    /// if no function signature AND multiple candidates => ambiguous
                    if(candidates.size() == 1)
                    {
                        LanguageElement* pWinner = candidates[0];
                        if(pWinner->asConstructor()) /// avoid getting unique constructor while looking for current class type
                            return;
                        Alias* pAlias = pWinner->asAlias();
                        if(pAlias AND pAlias->getAliasedElement())
                        {
                            pWinner = pAlias->getAliasedElement();
                        }
                        Expression* pExpression = toExpression(pWinner);
                        if(pExpression)
                        {
                            out_pResult = pExpression;
                        }
                        else 
                        {
                            if(in_pTemplateArguments)
                            {
                                if(pWinner->asTemplate())
                                {
                                    Template* pTemplate = static_cast<Template*>(pWinner);
                                    if(pTemplate->getTemplateParameterCount() < in_pTemplateArguments->size())
                                    {
                                        /// TODO : handle parameter pack
                                        o_semantic_error("too many template arguments provided to template '"<<pTemplate->getName()<<"'");
                                        out_pResult = Type::Invalid();
                                        return;
                                    }
                                    else
                                    {
                                        map<Placeholder*, LanguageElement*> argumentsMap;
                                        TemplateSignature* pTemplateSignature = pTemplate->getTemplateSignature();
                                        size_t i = 0;
                                        size_t count = pTemplateSignature->getParameterCount();
                                        for(;i<count; ++i)
                                        {
                                            Placeholder* pPlaceholder = pTemplateSignature->getParameter(i)->getPlaceholder();

                                            if(i<in_pTemplateArguments->size())
                                            {
                                                if(pPlaceholder->accepts((*in_pTemplateArguments)[i]))
                                                {
                                                    argumentsMap[pPlaceholder] = (*in_pTemplateArguments)[i];
                                                }
                                                else 
                                                {
                                                    o_semantic_error("invalid template argument in template '"<<pTemplate->getName()<<"' for parameter '"<<pPlaceholder->asNamedElement()->getName()<<"'");
                                                    out_pResult = Type::Invalid();
                                                    return;
                                                }
                                            }
                                            else 
                                            { 
                                                LanguageElement* pDefaultArgument = pTemplateSignature->getDefaultArgument(i);
                                                if(pDefaultArgument == nullptr)
                                                {
                                                    o_semantic_error("not enough template arguments provided to template '"<<pTemplate->getName()<<"'");
                                                    out_pResult = Type::Invalid();
                                                    return;
                                                }
                                                pDefaultArgument = resolveTemplateDependency(pDefaultArgument, nullptr, argumentsMap, in_pContextScope);
                                                if(pDefaultArgument == nullptr)
                                                {
                                                    o_semantic_error("invalid default argument "<<(i+1)<<"for current template instanciation '"<<pTemplate->getName()<<"'");
                                                    out_pResult = Type::Invalid();
                                                    return;
                                                }
                                                argumentsMap[pPlaceholder] = pDefaultArgument;
                                            }
                                        }
                                        out_pResult = resolveTemplateDependency(pTemplate, nullptr, argumentsMap, in_pContextScope);
                                    }
                                }
                            }
                            else 
                            {
                                out_pResult = pWinner;
                            }
                        }
                    }
                    else 
                    {
                        o_semantic_error("ambiguous access to multiple symbols :");
                        for(auto it = candidates.begin(); it != candidates.end(); ++it)
                        {
                            const char* word;
                            if(it == candidates.begin()) word = _canBe;
                            else word = _or;
                            o_semantic_suberror(((it == candidates.begin()) ? _canBe : _or) << " '" <<(*it)->asNamedElement()->getDecoratedName()<<"'");
                        }
                        out_pResult = Type::Invalid();
                    }
                }
            }
//             else 
//             {
//                 o_semantic_error("no symbol found with name '"<<in_name<<"''");
//             }
        }
        break;

    case e_Function_QualifiedNameLookup:
        {
            const string& in_name = *(const string*)a_Data.in[0];
            LanguageElement* in_pScope = *(LanguageElement**)a_Data.in[1];
            modifiers_t in_context_access = *(modifiers_t*)a_Data.in[2];
            vector<LanguageElement*>& out_candidates = *(vector<LanguageElement*>*)a_Data.out[0];
            vector<modifiers_t>& out_context_accesses = *(vector<modifiers_t>*)a_Data.out[1];

            /// search for all elements with , => these are the candidates
            for(auto it = a_pInput->beginElements(); it != a_pInput->endElements(); ++it)
            {
                NamedElement * pNamedElement = (*it)->asNamedElement();

                if(pNamedElement
                    AND NOT(pNamedElement->testModifiers(o_private_visibility))
                    AND pNamedElement->getName() == in_name 
                    AND (in_pScope == a_pInput OR NOT(pNamedElement->testModifiers(o_protected_visibility))))
                {
                    out_candidates.push_back(pNamedElement);
                }
            }

            /// if no element found matching the name, we look for every anonymous element, and restart search inside them recursively
            if(out_candidates.empty())
            {
                for(auto it = a_pInput->beginElements(); it != a_pInput->endElements(); ++it)
                {
                    NamedElement * pNamedElement = (*it)->asNamedElement();

                    if(pNamedElement
                        AND NOT(pNamedElement->testModifiers(o_private_visibility))
                        AND pNamedElement->getName().empty() 
                        AND (in_pScope == a_pInput OR NOT(pNamedElement->testModifiers(o_protected_visibility))))
                    {
                        modifiers_t access = in_context_access;
                        /// Inherits access from anonymous element
                        if(pNamedElement->getAccess() > access) 
                            access = pNamedElement->getAccess();
                        vector<LanguageElement*> sub_candidates;
                        vector<modifiers_t> sub_context_accesses;
                        visitor_data data = a_Data;
                        data.id = e_Function_QualifiedNameLookup;
                        const void* in[3] = {&in_name, &in_pScope, &access};
                        void* out[2] = {&sub_candidates, &sub_context_accesses};
                        data.in = in;
                        data.out = out;
                        pNamedElement->visit(this, data);
                        out_candidates.insert(out_candidates.end(), sub_candidates.begin(), sub_candidates.end());
                        out_context_accesses.insert(out_context_accesses.end(), sub_context_accesses.begin(), sub_context_accesses.end());
                    }
                }
            }
        }
        break;
    }
}
void CPlusPlus::visit( LocalVariable*               a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_ToExpression:
        {
            Expression* in_pLeftExpression = *(Expression**)a_Data.in[0];
            Expression*& out_pExpression = *(Expression**)a_Data.out[0];
            if(in_pLeftExpression) return;
            out_pExpression = a_pInput->toExpression();
        }
        return;

    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(LocalVariable)(o_resolveT(Type, a_pInput->getValueType())
                                                    , a_pInput->getName()
                                                    , o_instanciateT(Expression, a_pInput->getInitializationExpression())
                                                    , a_pInput->getModifiers());
        } 
        return;
    }
    visit(static_cast<NamedElement*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( LocalVariableExpression*     a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_definition)
            {
                string& translation = *(string*)a_Data.out[0];
                translation += a_pInput->getLocalVariable()->getName();
            }
        }
        return;
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(LocalVariableExpression)(o_resolveT(LocalVariable, a_pInput->getLocalVariable()));
        }
        return;
    }
    visit(static_cast<LValueExpression*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( LocalVariableInitializationStatement* a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_definition)
            {
                LanguageElement* in_pScope = *(LanguageElement**)a_Data.in[1];
                string& translation = *(string*)a_Data.out[0];
                translate(a_pInput->getLocalVariable()->getValueType(), translation, e_translation_qualified_decorated_name, in_pScope);
                translation += " "+a_pInput->getLocalVariable()->getName();
                if(a_pInput->getRightExpression())
                {
                    ConstructorCallExpression* pCtorCall = a_pInput->getRightExpression()->asConstructorCallExpression();
                    if(pCtorCall)
                    {
                        translation += "(";
                        for(auto it = pCtorCall->beginArguments(); it != pCtorCall->endArguments(); ++it)
                        {
                            if(it != pCtorCall->beginArguments())
                                translation+=',';
                            (*it)->visit(this, a_Data);
                        }
                        translation += ")";
                    }
                    else 
                    {
                        translation += " = ";
                        a_pInput->getRightExpression()->visit(this, a_Data);
                    }
                }
                translation+=";";
            }
        }
        return;
    }
    visit(static_cast<LValueInitializationStatement*>(a_pInput), a_Data);
}
void CPlusPlus::visit( LValueExpression*            a_pInput, visitor_data a_Data) { visit(static_cast<Expression*>(a_pInput), a_Data); }
void CPlusPlus::visit( LValueInitializationStatement* a_pInput, visitor_data a_Data) { visit(static_cast<Statement*>(a_pInput), a_Data); }
void CPlusPlus::visit( LValueReferenceType*         a_pInput, visitor_data a_Data)
{
    switch(a_Data.id)
    {
    case e_Function_TemplateArgumentDeduction:
        {
            LanguageElement* pArgument = *(LanguageElement* const *)a_Data.in[0];
            LanguageElement*& pDeducedArgument = *(LanguageElement**)a_Data.out[0];
            map<Placeholder*, LanguageElement*>& deductions = *(map<Placeholder*, LanguageElement*>*)a_Data.out[1];
            LValueReferenceType* pReferenceType = pArgument->asLValueReferenceType();
            if(pReferenceType)
            {
                Type* pReferencedDeducedType = templateArgumentDeduction(a_pInput->getReferencedType(), pReferenceType->getReferencedType(), deductions);
                if(pReferencedDeducedType)
                {
                    pDeducedArgument = pReferencedDeducedType->lvalueReferenceType();
                }
            }
        }
        break;

    case e_Function_Conversion:
        {
            Type* pOutput = *(Type* const *)a_Data.in[0];
            int iConversionType = *(int const*)a_Data.in[1];
            int iUserDefinedConversionsAllowed = *(int const*)a_Data.in[2];
            LanguageElement* pContextScope = *(LanguageElement*const*)a_Data.in[3];
            conversion*& conv = *(conversion**)a_Data.out[0];
            if(pOutput->removeQualifiers()->equals(a_pInput))
            {
                conv = new default_conversion_sequence(new standard_conversion_sequence(a_pInput)); /// use a standard conversion to allow comparison with equivalent lvalue transformation : X& -> X
                return; /// success X& -> X&
            }
            switch(iConversionType)
            {
            case e_const_cast: 
                {
                    Type* pInputNoConst = a_pInput->removeAllQualifiers();
                    Type* pOutputNoConst = pOutput->removeAllQualifiers();
                    if(pInputNoConst->equals(a_pInput) AND pOutputNoConst->equals(pOutput)) 
                        return; /// input or output do not have const (or volatile ?) => const_cast fail
                    if(pInputNoConst->equals(pOutputNoConst)) /// no-cv input == no-cv output => const_cast ok
                        conv = new default_conversion_sequence(pInputNoConst);
                    return; /// const_cast ends here (no more user defined or else can be done)
                }
            case e_reinterpret_cast:
                {
                    if(pOutput->removeQualifiers()->asReferenceType())
                    {
                        conv = new default_conversion_sequence(a_pInput, (value_t)pOutput);
                        return; /// success X& -> Y&
                    }
                }
            }

            LValueReferenceType* pOutputReferenceType = pOutput->asLValueReferenceType();
            if(pOutputReferenceType == nullptr) /// output is not a reference type => lvalue -> rvalue transformation
            {
                pOutput = pOutput->removeQualifiers();
                if(pOutput->equals(a_pInput->getReferencedType()))
                {
                    /// X& -> X 
                    conv = new default_conversion_sequence(new lvalue_transformation(a_pInput));
                    return;
                }
//                 if(pOutput->asPlaceholder())
//                 {
//                     conv = new default_conversion_sequence(a_pInput, pOutput, 10);
//                     return;
//                 }
                ClassType* pOutputClassType = pOutput->asClassType();
                if(iUserDefinedConversionsAllowed AND pOutputClassType)
                {
                    /// X& -> Y(X&)
                    conv = userDefinedConversionByConstruction(a_pInput, pOutputClassType, (iConversionType == e_implicit_conversion) ? (iUserDefinedConversionsAllowed == e_explicit_functions) : true, pContextScope, false);
                    if(conv) return;
                }
                /// X& -> Y
                a_pInput->getReferencedType()->visit(this, a_Data);
                if(conv)
                {
                    /// We found a conversion from X -> Y, we just add a lvalue_transformation to it to obtain X& -> Y
                    static_cast<default_conversion_sequence*>(conv)->addLValueTransform();
                    return; /// success X& -> Y
                }
            }
            else /// X& -> Y& (output is a reference type)
            {
                Type* pInputReferencedType = a_pInput->getReferencedType(); /// X
                Type* pOutputReferencedType = pOutputReferenceType->getReferencedType(); /// X

//                 if(pInputReferencedType->asPlaceholder() AND pOutputReferencedType->asPlaceholder())
//                 {
//                     /// T& -> U&
//                     conv = new default_conversion_sequence(a_pInput, pOutput, 10);
//                     return;
//                 }
                /// X& -> Y&
                std::pair<Type*, Type*> constAdjustment;
                size_t adjustmentCount = 0;
                if(pOutputReferencedType->asConstType())
                {
                    /// X& -> Y const&
                    Type* pOutputReferencedTypeNoConst = pOutputReferencedType->removeConst(); /// Y
//                     if(pOutputReferencedTypeNoConst->asPlaceholder())
//                     {
//                         /// X& -> U const&
//                         conv = new default_conversion_sequence(a_pInput, pOutput, 10);
//                         return;
//                     }
                    Type* pInputReferencedTypeNoConst = pInputReferencedType->removeConst(); /// X
                    if(pInputReferencedTypeNoConst->isKindOf(pOutputReferencedTypeNoConst))
                    {
                        Type* pOutputReferenceTypeNoConst = pOutputReferencedTypeNoConst->lvalueReferenceType();
                        /// X and Y are related => make const adjustment
                        if(a_pInput->equals(pOutputReferenceTypeNoConst))
                        {
                            conv = new default_conversion_sequence(new qualification_adjustment(pOutputReferenceTypeNoConst, pOutputReferenceType, 1));
                            return; /// success X& -> X const&
                        }
                    }
                    else 
                    {
                        /// X and Y are not related => it's possibly a const ref conversion
                        /// Search conversion X& -> Y and, if found, add const ref conversion then to do X& -> Y const& 
                        a_Data.in[0] = &pOutputReferencedTypeNoConst; // modify output in visitor data
                        a_pInput->getReferencedType()->visit(this, a_Data);
                        if(conv)
                        {
                            static_cast<default_conversion_sequence*>(conv)->addConstRef();
                            return; /// success X& -> Y const& 
                        }
                        return;
                    }
                }
                else 
                {
                    if(a_pInput->getReferencedType()->asConstType())
                    {
                        return; /// failure X const& -/-> Y&
                    }

//                     if(pOutputReferencedTypeNoConst->asPlaceholder())
//                     {
//                         /// X& -> U const&
//                         conv = new default_conversion_sequence(a_pInput, pOutput, 10);
//                         return;
//                     }
                }
                if((pInputReferencedType->asClass() != nullptr) AND (pOutputReferencedType->asClass() != nullptr)) 
                {
                    reflection::Class* pInputClass       = static_cast<reflection::Class*>(pInputReferencedType);
                    reflection::Class* pOutputClass  = static_cast<reflection::Class*>(pOutputReferencedType);
                    size_t level = pInputClass->getInheritanceLevelFromBase(pOutputClass);
                    if(level != ~size_t(0)) // level != -1 => inheritance relation => pointers are related
                    {
                        auto* pPtr = new pointer_conversion(a_pInput, pOutputReferenceType, level, pInputClass->getBaseClassOffsetCascade(pOutputClass));
                        if(adjustmentCount)
                            conv = new default_conversion_sequence(pPtr, new qualification_adjustment(constAdjustment.first, constAdjustment.second, adjustmentCount));
                        conv = new default_conversion_sequence(pPtr);
                        return; /// success Derived& -> Base(const)&
                    }
                }
            }
        }
        break;

    case e_Function_ResolveTemplateDependencies:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pResolved = *(LanguageElement**)a_Data.out[0];
            Type* pNewReferencedType = o_resolveT(Type, a_pInput->getReferencedType());
            pResolved = pNewReferencedType ? pNewReferencedType->lvalueReferenceType() : nullptr;
        }
        return;

    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            Type* pType = o_instanciateT(Type, a_pInput->getReferencedType());
            if(pType)
            {
                pInstanciated = pType->lvalueReferenceType();
            }
        }
        return;
    }
    visit(static_cast<ReferenceType*>(a_pInput), a_Data);
}
void CPlusPlus::visit( MapContainerClass*           a_pInput, visitor_data a_Data) { visit(static_cast<Class*>(a_pInput), a_Data); }
void CPlusPlus::visit( Member*                      a_pInput, visitor_data a_Data) {                                                      }
void CPlusPlus::visit( MemberAnonymousSection*      a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void CPlusPlus::visit( MemberAnonymousStruct*       a_pInput, visitor_data a_Data) { visit(static_cast<MemberAnonymousSection*>(a_pInput), a_Data); }
void CPlusPlus::visit( MemberAnonymousUnion*        a_pInput, visitor_data a_Data) { visit(static_cast<MemberAnonymousSection*>(a_pInput), a_Data); }
void CPlusPlus::visit( MemberFunction*              a_pInput, visitor_data a_Data)
{
    switch(a_Data.id)
    {
    case e_Function_IsViableCallCandidate:
        {
            const vector<LanguageElement*>* templateArguments = (const vector<LanguageElement*>*)a_Data.in[0];
            const vector<Expression*>& functionArguments = *(const vector<Expression*>*)a_Data.in[1];
            modifiers_t modifiers = *(modifiers_t*)a_Data.in[2];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[3];
            conversions& out_conversions = *(conversions*)a_Data.out[0];
            Subroutine*& out_subroutine = *(Subroutine**)a_Data.out[1];
            out_subroutine = nullptr;
            if(modifiers & o_static)
            {
                // static call (no this implied)
                return;
            }
            /// not static => first argument is the implicit object argument 
            o_assert(a_pInput->getOwner()->asClassType());
            o_assert(functionArguments.front()->getValueType()->removeReference()->removeRValueReference()->removeConst()->isKindOf(a_pInput->getOwner()->asClassType()));

            if((functionArguments.size()-1) < a_pInput->getMinimumNeededParameterCount()
                OR (functionArguments.size()-1) > a_pInput->getParameterCount())
            {
                return;
            }
            if(a_pInput->acceptsObjectExpressionType(functionArguments.front()->getValueType()))
            {
                /// implicit conversion of the implicit object parameter
                Type* pOutput = a_pInput->getImplicitObjectParameterType();
                conversion* pConversion = 0;
                visitor_data conversionData;
                conversionData.id = e_Function_Conversion;
                int iConversionType = e_implicit_conversion;
                bool iUserDefinedConversionsAllowed = false;
                LanguageElement* pContextScope = pScope;
                const void* in[4] = { &pOutput, &iConversionType, &iUserDefinedConversionsAllowed, &pContextScope };
                void* out[1] = { &pConversion };
                conversionData.in = in;
                conversionData.out = out;
                functionArguments[0]->getValueType()->visit(this, conversionData);
                out_conversions.push_back(pConversion);

                /// list implicit conversions of arguments
                vector<Expression*> arguments;
                for(size_t i = 0; i<a_pInput->getParameterCount(); ++i)
                {
                    if(i<(functionArguments.size()-1))
                    {
                        arguments.push_back(functionArguments[i+1]);
                    }
                    else 
                    {
                        arguments.push_back(a_pInput->getParameter(i)->getInitializationExpression());
                    }
                }
                a_pInput->getSignature()->implicitConversions(this, arguments, pScope, out_conversions);
                out_subroutine = a_pInput;
            }
        }
        return;
    case e_Function_IsViableSignatureCandidate:
        {
            const vector<LanguageElement*>* templateArguments = a_Data.in[0] ? (const vector<LanguageElement*>*)a_Data.in[0] : nullptr;
            const vector<Type*>& types = *(const vector<Type*>*)a_Data.in[1];
            modifiers_t modifiers = *(modifiers_t*)a_Data.in[2];
            bool& out_result = *(bool*)a_Data.out[0];

            out_result = templateArguments 
                ? a_pInput->matches(*templateArguments, types, modifiers)
                : a_pInput->matches(types, modifiers);
        }
        return;
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(MemberFunction)(a_pInput->getName(), o_instanciateT(Signature, a_pInput->getSignature()), a_pInput->getModifiers());
            visit(static_cast<Subroutine*>(a_pInput), a_Data);
        } 
        return;
    }
    visit(static_cast<Subroutine*>(a_pInput), a_Data);
}
void CPlusPlus::visit( MemberFunctionPointerCallExpression* a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_definition)
            {
                LanguageElement* in_pScope = *(LanguageElement**)a_Data.in[1];
                string& translation = *(string*)a_Data.out[0];
                translation += "((";
                a_pInput->getObjectExpression()->visit(this, a_Data);
                translation += ").*(";
                a_pInput->getMemberExpression()->visit(this, a_Data);
                translation += "))(";
                for(auto it = a_pInput->beginArguments(); it != a_pInput->endArguments(); ++it)
                {
                    if(it != a_pInput->beginArguments())
                    {
                        translation+=',';
                    }
                    (*it)->visit(this, a_Data);
                }
                translation += ')';
            }
        }
        return;
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            vector<Expression*> newArguments;
            for(auto it = a_pInput->beginArguments(); it != a_pInput->endArguments(); ++it)
            {
                newArguments.push_back(o_instanciateT(Expression, *it));
            }
            pInstanciated = o_new(MemberFunctionPointerCallExpression)(
                                o_resolveT(MemberFunctionPointerType, a_pInput->getMemberFunctionPointerType())
                                , o_instanciateT(Expression, a_pInput->getObjectExpression())
                                , o_instanciateT(Expression, a_pInput->getMemberExpression())
                                , newArguments
                            ); 
        }
        return;
    }
    visit(static_cast<CallExpression*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( MemberFunctionPointerType*   a_pInput, visitor_data a_Data)
{
    switch(a_Data.id)
    {
    case e_Function_Conversion:
        {
            Type* pOutput = *(Type* const *)a_Data.in[0];
            int iConversionType = *(int const*)a_Data.in[1];
            int iUserDefinedConversionsAllowed = *(int const*)a_Data.in[2];
            LanguageElement* pContextScope = *(LanguageElement**)a_Data.in[3];
            conversion*& conv = *(conversion**)a_Data.out[0];
            std::pair<Type*, Type*> constAdjustment;
            size_t adjustmentCount = 0;
            bool bConstRef = baseConversion(a_pInput, pOutput, iConversionType);

            if(pOutput->equals(a_pInput)) 
            {
                if(adjustmentCount)
                {
                    conv = bConstRef 
                        ? new default_conversion_sequence(new qualification_adjustment(constAdjustment.first, constAdjustment.second, adjustmentCount), new constref_conversion(pOutput))
                        : new default_conversion_sequence(new qualification_adjustment(constAdjustment.first, constAdjustment.second, adjustmentCount));
                }
                conv = bConstRef 
                    ? new default_conversion_sequence(new constref_conversion(pOutput))
                    : new default_conversion_sequence(a_pInput, (value_t)pOutput);
                return; /// success X (Class::*)(...) -> X (Class::*)(...)
            }

            if(pOutput->asMemberFunctionPointerType())
            {
                MemberFunctionPointerType* pOutputMemberFunctionPointerType = static_cast<MemberFunctionPointerType*>(pOutput);

                if(a_pInput->getSignature()->equals(pOutputMemberFunctionPointerType->getSignature())) /// same signature
                {
                    if((a_pInput->getObjectType()->asClass() != nullptr) AND (pOutputMemberFunctionPointerType->getObjectType()->asClass() != nullptr)) 
                    {
                        reflection::Class* pInputClass  = static_cast<reflection::Class*>(a_pInput->getObjectType());
                        reflection::Class* pOutputClass   = static_cast<reflection::Class*>(pOutputMemberFunctionPointerType->getObjectType());
                        size_t level = pInputClass->getInheritanceLevelFromBase(pOutputClass);
                        if(level != ~size_t(0)) // level != -1 => inheritance relation => pointers are related
                        {
                            auto* pPtr = new member_function_pointer_conversion(a_pInput, pOutputMemberFunctionPointerType, level, pInputClass->getBaseClassOffsetCascade(pOutputClass));

                            if(adjustmentCount)
                            {
                                conv = bConstRef 
                                    ? new default_conversion_sequence(pPtr, new qualification_adjustment(constAdjustment.first, constAdjustment.second, adjustmentCount), new constref_conversion(pOutput))
                                    : new default_conversion_sequence(pPtr, new qualification_adjustment(constAdjustment.first, constAdjustment.second, adjustmentCount));
                            }
                            conv = bConstRef 
                                ? new default_conversion_sequence(pPtr, new constref_conversion(pOutput))
                                : new default_conversion_sequence(pPtr);
                            return; /// success X (Derived::*)(...) -> X (Base::*)(...)
                        }
                    }
                }
            }
        }
        break;

    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            vector<Type*> parameters;
            for(auto it = a_pInput->getSignature()->beginParameters(); it != a_pInput->getSignature()->endParameters(); ++it)
            {
                parameters.push_back(o_resolveT(Type, (*it) ? (*it)->getValueType() : nullptr));
            }
            ClassType* pObjectType = o_resolveT(ClassType, a_pInput->getObjectType());
            pInstanciated = pObjectType->memberFunctionPointerType(o_resolveT(Type, a_pInput->getSignature()->getReturnType()), parameters, a_pInput->getModifiers()&(o_lvalue_ref|o_const|o_rvalue_ref) );
        }           
        return;

    }
    visit(static_cast<MemberPointerType*>(a_pInput), a_Data);
}
void CPlusPlus::visit( MemberPointerType*           a_pInput, visitor_data a_Data) { visit(static_cast<Type*>(a_pInput), a_Data); }
void CPlusPlus::visit( Module*                      a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_UnqualifiedLookup:
        {
            a_pInput->getOwner()->visit(this, a_Data);
        }
        break;
    }
}
void CPlusPlus::visit( NamedElement*                a_pInput, visitor_data a_Data) 
{ 
    switch(a_Data.id)
    {
    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_qualified_decorated_name
                OR in_TranslationType == e_translation_qualified_name)
            {
                LanguageElement* pScope = *(LanguageElement**)a_Data.in[1];
                string& translation = *(string*)a_Data.out[0];
                TemplateSpecialization* pSpec = a_pInput->getOwner() ? a_pInput->getOwner()->asTemplateSpecialization() : nullptr;
                Scope* pNamingScope = pSpec ? pSpec->getNamingScope() : a_pInput->getNamingScope();
                if(pNamingScope AND NOT(pScope->hasNamingScopeCascade(pNamingScope)))
                {
                    pNamingScope->asLanguageElement()->visit(this, a_Data);
                }
                translation += m_ScopeDelimiter;
                translation += a_pInput->getName();
                if(pSpec AND in_TranslationType == e_translation_qualified_decorated_name)
                {
                    translation+="< ";
                    for(auto it = pSpec->beginArguments(); it != pSpec->endArguments(); ++it)
                    {
                        if(it != pSpec->beginArguments())
                            translation+=',';
                        (*it)->visit(this, a_Data);
                    }
                    translation+=" >";
                }
            }
        }
        return;
    case e_Function_ResolveTemplateDependencies:
        {
            *(LanguageElement**)a_Data.out[0] = a_pInput; /// By default any named element resolve to itself in a template context (only placeholders resolve to their underlying content)
        }
        return;
    case e_Function_UnqualifiedLookup:
        {
            const string& in_name = *(const string*)a_Data.in[0];
            const vector<LanguageElement*>* in_pTemplateArguments = (const vector<LanguageElement*>*)a_Data.in[1];
            const vector<Expression*>* in_pFunctionArguments = (const vector<Expression*>*)a_Data.in[2];
            Type* in_pInitializationType = (Type*)a_Data.in[3];
            LanguageElement* in_pContextScope = *(LanguageElement**)a_Data.in[4];
            LanguageElement*& out_pResult = *(LanguageElement**)a_Data.out[0];
            if(in_name == a_pInput->getName()) /// ex : in namespace phantom, we can access to ourself, i.e 'phantom', so we use qualified ::phantom to find it
            {
                if(a_Data.hasFlag(e_VisitorFlag_NamespaceMode))
                {
                    if(a_pInput->getNamespace())
                    {
                        out_pResult = qualifiedLookup(a_pInput->getNamespace(), in_name, in_pTemplateArguments, in_pFunctionArguments, in_pContextScope, in_pInitializationType);
                        return;
                    }
                }
                if(a_pInput->getOwner())
                {
                    out_pResult = qualifiedLookup(a_pInput->getOwner(), in_name, in_pTemplateArguments, in_pFunctionArguments, in_pContextScope, in_pInitializationType);
                }
                return;
            }
        }
        break;
    }
    visit(static_cast<LanguageElement*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( Namespace*                   a_pInput, visitor_data a_Data) 
{ 
    switch(a_Data.id)
    {
    case e_Function_SubroutineResolution:
        visit(static_cast<Scope*>(a_pInput), a_Data);
        return;

    case e_Function_QualifiedLookup:
        visit(static_cast<NamedElement*>(a_pInput), a_Data);
        return;

    case e_Function_UnqualifiedLookup:
        visit(static_cast<NamedElement*>(a_pInput), a_Data);
        return;

    case e_Function_QualifiedNameLookup:
        {
            const string& in_name = *(const string*)a_Data.in[0];
            LanguageElement* in_pScope = *(LanguageElement**)a_Data.in[1];
            modifiers_t in_context_access = *(modifiers_t*)a_Data.in[2];
            vector<LanguageElement*>& out_candidates = *(vector<LanguageElement*>*)a_Data.out[0];
            vector<modifiers_t>& out_context_accesses = *(vector<modifiers_t>*)a_Data.out[1];

            visit(static_cast<NamedElement*>(a_pInput), a_Data);

            if(out_candidates.size())
                return;

            /// In a namespace - except for child namespaces - elements are not owned, they are referenced, that's why we browse reference elements

            /// search for all elements with , => these are the candidates
            for(auto it = a_pInput->beginReferencedElements(); it != a_pInput->endReferencedElements(); ++it)
            {
                NamedElement * pNamedElement = (*it)->asNamedElement();

                if(pNamedElement
                    AND NOT(pNamedElement->testModifiers(o_private_visibility))
                    AND pNamedElement->getName() == in_name 
                    AND (in_pScope == a_pInput OR NOT(pNamedElement->testModifiers(o_protected_visibility))))
                {
                    out_candidates.push_back(pNamedElement);
                }
            }

            /// if no element found matching the name, we look for every anonymous element, and restart search inside them recursively
            if(out_candidates.empty())
            {
                for(auto it = a_pInput->beginReferencedElements(); it != a_pInput->endReferencedElements(); ++it)
                {
                    NamedElement * pNamedElement = (*it)->asNamedElement();

                    if(pNamedElement
                        AND NOT(pNamedElement->testModifiers(o_private_visibility))
                        AND pNamedElement->getName().empty() 
                        AND (in_pScope == a_pInput OR NOT(pNamedElement->testModifiers(o_protected_visibility))))
                    {
                        modifiers_t access = in_context_access;
                        /// Inherits access from anonymous element
                        if(pNamedElement->getAccess() > access) 
                            access = pNamedElement->getAccess();
                        vector<LanguageElement*> sub_candidates;
                        vector<modifiers_t> sub_context_accesses;
                        visitor_data data = a_Data;
                        data.id = e_Function_QualifiedNameLookup;
                        const void* in[3] = {&in_name, &in_pScope, &access};
                        void* out[2] = {&sub_candidates, &sub_context_accesses};
                        data.in = in;
                        data.out = out;
                        pNamedElement->visit(this, data);
                        out_candidates.insert(out_candidates.end(), sub_candidates.begin(), sub_candidates.end());
                        out_context_accesses.insert(out_context_accesses.end(), sub_context_accesses.begin(), sub_context_accesses.end());
                    }
                }
            }
        }
        break;
    }
}
void CPlusPlus::visit( NamespaceAlias*              a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void CPlusPlus::visit( NumericConstant*             a_pInput, visitor_data a_Data) { visit(static_cast<Constant*>(a_pInput), a_Data); }
void CPlusPlus::visit( Package*                     a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void CPlusPlus::visit( Parameter*                   a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_declaration
                OR in_TranslationType == e_translation_definition )
            {
                LanguageElement* in_pScope = *(LanguageElement**)a_Data.in[1];
                string& translation = *(string*)a_Data.out[0];
                translate(a_pInput->getValueType(), translation, e_translation_qualified_decorated_name, in_pScope);
                translation += " "+a_pInput->getName();
                if(a_pInput->getInitializationExpression())
                {
                    if(in_TranslationType == e_translation_definition)
                    {
                        translation += " = /*";
                        translate(a_pInput->getInitializationExpression(), translation, e_translation_definition, in_pScope);
                        translation += "*/";
                    }
                    else 
                    {
                        translation += " = ";
                        translate(a_pInput->getInitializationExpression(), translation, e_translation_definition, in_pScope);
                    }
                }
            }
        }
        return;

    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(Parameter)(o_resolveT(Type, a_pInput->getValueType())
                , a_pInput->getName()
                , o_instanciateT(Expression, a_pInput->getInitializationExpression())
                , a_pInput->getModifiers());
        } 
        return;
    } 
    visit(static_cast<LocalVariable*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( Placeholder*                 a_pInput, visitor_data a_Data) { }
void CPlusPlus::visit( PlaceholderClass*            a_pInput, visitor_data a_Data)
{
    switch(a_Data.id)
    {
    case e_Function_QualifiedNameLookup:
        {
            const string& in_name = *(const string*)a_Data.in[0];
            vector<LanguageElement*>& out_candidates = *(vector<LanguageElement*>*)a_Data.out[0];
            out_candidates.push_back(o_new(TemplateDependantElement)(a_pInput, in_name));
        }
        break;
    case e_Function_ResolveTemplateDependencies:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pResolved = *(LanguageElement**)a_Data.out[0];
            auto it = arguments.find(a_pInput->getOwner()->asPlaceholder());
            o_assert(it != arguments.end());
            pResolved = it->second;
            pResolved = pResolved->asClass();
        }
        return;
    }
}
void CPlusPlus::visit( PlaceholderClassType*        a_pInput, visitor_data a_Data )
{
    switch(a_Data.id)
    {
    case e_Function_QualifiedNameLookup:
        {
            const string& in_name = *(const string*)a_Data.in[0];
            vector<LanguageElement*>& out_candidates = *(vector<LanguageElement*>*)a_Data.out[0];
            out_candidates.push_back(o_new(TemplateDependantElement)(a_pInput, in_name));
        }
        break;
    case e_Function_ResolveTemplateDependencies:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pResolved = *(LanguageElement**)a_Data.out[0];
            auto it = arguments.find(a_pInput->getOwner()->asPlaceholder());
            o_assert(it != arguments.end());
            pResolved = it->second;
            pResolved = pResolved->asClassType();
        }
        return;
    }
}
void CPlusPlus::visit( PlaceholderConstant*         a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_TemplateArgumentDeduction:
        {
            LanguageElement* pArgument = *(LanguageElement* const *)a_Data.in[0];
            LanguageElement*& pDeducedArgument = *(LanguageElement**)a_Data.out[0];
            map<Placeholder*, LanguageElement*>& deductions = *(map<Placeholder*, LanguageElement*>*)a_Data.out[1];
            Expression* pArgumentExpression = pArgument->asExpression();
            if(pArgumentExpression == nullptr OR NOT(pArgument->isCompileTime())) /// argument not an expression or not compile time element
                return;

            auto alreadyDeduced = deductions.find(a_pInput);
            if(alreadyDeduced != deductions.end())
            {
                /// already deduced => needs perfect match
                if(pArgumentExpression->getValueType()->removeReference()->removeConst()->equals(alreadyDeduced->second))
                {
                    pDeducedArgument = pArgumentExpression;
                }
            }
            else 
            {
                if(pDeducedArgument = convert(pArgumentExpression, a_pInput->getValueType(), e_implicit_conversion, nullptr, false))
                {
                    deductions[a_pInput] = pDeducedArgument;
                }
            }
        }
        break;

    case e_Function_ResolveTemplateDependencies:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pResolved = *(LanguageElement**)a_Data.out[0];
            auto it = arguments.find(a_pInput);
            o_assert(it != arguments.end());
            pResolved = it->second;
        }
        return;
    }
    visit(static_cast<Constant*>(a_pInput), a_Data);
}
void CPlusPlus::visit( PlaceholderTemplate*         a_pInput, visitor_data a_Data )
{
    switch(a_Data.id)
    {
    case e_Function_TemplateArgumentDeduction:
        {
            LanguageElement* pArgument = *(LanguageElement* const *)a_Data.in[0];
            LanguageElement*& pDeducedArgument = *(LanguageElement**)a_Data.out[0];
            map<Placeholder*, LanguageElement*>& deductions = *(map<Placeholder*, LanguageElement*>*)a_Data.out[1];
            ClassType* pClassTypeArgument = pArgument->asClassType();
            size_t count = a_pInput->getTemplateSignature()->getParameterCount();
            if(pClassTypeArgument)
            {
                if(pClassTypeArgument->getTypeId() == e_template_dependant)
                {
                    TemplateDependantTemplateInstance* pTDTI = static_cast<TemplateDependantTemplateInstance*>(pClassTypeArgument);
                    /// Both template template parameter and template argument has same parameter/argument count
                    if(pTDTI->getTemplate()->getTemplateSignature()->getParameterCount() == count)
                    {
                        size_t i = 0;
                        for(; i<count; ++i)
                        {
                            TemplateParameter* pParameter = a_pInput->getTemplateSignature()->getParameter(i);
                            Placeholder* pPlaceholder = pParameter->getPlaceholder();
                            LanguageElement* pArgument = pTDTI->getArgument(pPlaceholder);
                            if(pArgument == nullptr) 
                                pArgument = pParameter->getDefaultArgument();
                            if(pArgument == nullptr)
                                return;
                            if(NOT(templateArgumentDeduction(pPlaceholder->asNamedElement(), pArgument, deductions)))
                                return;
                        }
                        pDeducedArgument = pClassTypeArgument;
                    }
                }
                TemplateSpecialization* pSpec = pClassTypeArgument->getOwner() ? pClassTypeArgument->getOwner()->asTemplateSpecialization() : nullptr;
                if(pSpec)
                {
                    /// Both template template parameter and template argument has same parameter/argument count
                    if(pSpec->getTemplateSignature()->getParameterCount() == count)
                    {
                        size_t i = 0;
                        for(; i<count; ++i)
                        {
                            LanguageElement* pArgument = pSpec->getArgument(i);
                            TemplateParameter* pParameter = a_pInput->getTemplateSignature()->getParameter(i);
                            NamedElement* pPlaceholder = pParameter->getPlaceholder()->asNamedElement();
                            if(NOT(templateArgumentDeduction(pPlaceholder, pArgument, deductions)))
                                return;
                        }
                        pDeducedArgument = pClassTypeArgument;
                    }
                }
            }
        }
        return;
    }
    o_assert_no_implementation();
    /*switch(a_Data.id)
    {
    case e_Function_QualifiedNameLookup:
        {
            const string& in_name = *(const string*)a_Data.in[0];
            vector<LanguageElement*>& out_candidates = *(vector<LanguageElement*>*)a_Data.out[0];
            out_candidates.push_back(o_new(TemplateDependantElement)(a_pInput, a_Data));
        }
        return;
    case e_Function_ResolveTemplateDependencies:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pResolved = *(LanguageElement**)a_Data.out[0];
            size_t paramIndex = pTemplateSignature->getParameterIndex(a_pInput->getName());
            if(paramIndex == ~size_t(0)) return nullptr;
            o_assert(paramIndex <arguments.size(), "argument count must have been checked before");
            LanguageElement* pElement = arguments[paramIndex];
            return pElement ? pElement->asType() : o_findT(Type, a_pInput);
        }
        return;
    }*/
    visit(static_cast<Template*>(a_pInput), a_Data);
}
void CPlusPlus::visit( PlaceholderType*             a_pInput, visitor_data a_Data )
{
    switch(a_Data.id)
    {
    case e_Function_TemplateArgumentDeduction:
        {
            LanguageElement* pArgument = *(LanguageElement* const *)a_Data.in[0];
            LanguageElement*& pDeducedArgument = *(LanguageElement**)a_Data.out[0];
            map<Placeholder*, LanguageElement*>& deductions = *(map<Placeholder*, LanguageElement*>*)a_Data.out[1];
            Type* pType = pArgument->asType();
            if(pType)
            {
                pDeducedArgument = pType; 
            }
            if(pDeducedArgument)
            {
                auto found = deductions.find(a_pInput);
                if(found != deductions.end())
                {
                    if(NOT(found->second->equals(pDeducedArgument))) 
                    {
                        pDeducedArgument = nullptr;
                        return;
                    }
                }
                deductions[a_pInput] = pDeducedArgument;
            }
        }
        break;

    case e_Function_QualifiedNameLookup:
        {
            const string& in_name = *(const string*)a_Data.in[0];
            vector<LanguageElement*>& out_candidates = *(vector<LanguageElement*>*)a_Data.out[0];
            out_candidates.push_back(o_new(TemplateDependantElement)(a_pInput, in_name));
        }
        return;
    case e_Function_ResolveTemplateDependencies:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pResolved = *(LanguageElement**)a_Data.out[0];
            auto it = arguments.find(a_pInput);
            o_assert(it != arguments.end());
            pResolved = it->second;
        }
        return;
    }
    visit(static_cast<Type*>(a_pInput), a_Data);
}
void CPlusPlus::visit( PlacementConstructionExpression* a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {

    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_definition)
            {
                LanguageElement* in_pScope = *(LanguageElement**)a_Data.in[1];
                string& translation = *(string*)a_Data.out[0]; 
                translation += "new(";
                a_pInput->getPlaceExpression()->visit(this, a_Data);
                translation += ')';
                translate(a_pInput->getSubroutine()->getOwner(), translation, e_translation_qualified_decorated_name, in_pScope);
                translation += '(';
                for(auto it = a_pInput->beginArguments(); it != a_pInput->endArguments(); ++it)
                {
                    if(it != a_pInput->beginArguments())
                    {
                        translation+=',';
                    }
                    (*it)->visit(this, a_Data);
                }
                translation += ')';
            }
        }
        return;

    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            vector<Expression*> newArguments;
            for(auto it = a_pInput->beginArguments(); it != a_pInput->endArguments(); ++it)
            {
                newArguments.push_back(o_instanciateT(Expression, *it));
            }
            pInstanciated = o_new(PlacementConstructionExpression)(
                o_resolveT(Constructor, a_pInput->getSubroutine())
                , o_instanciateT(Expression, a_pInput->getPlaceExpression())
                , newArguments
            ); 
        }
        return;
    }
    visit(static_cast<CallExpression*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( PointerType*                 a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void CPlusPlus::visit( PrimitiveType*               a_pInput, visitor_data a_Data) { visit(static_cast<Type*>(a_pInput), a_Data); }
void CPlusPlus::visit( Property*                    a_pInput, visitor_data a_Data) 
{ 
    switch(a_Data.id)
    {
    case e_Function_ToExpression:
        {
            Expression* in_pLeftExpression = *(Expression**)a_Data.in[0];
            Expression*& out_pExpression = *(Expression**)a_Data.out[0];
            if(in_pLeftExpression == nullptr) return;
            in_pLeftExpression = convert(in_pLeftExpression, in_pLeftExpression->getValueType()->replicate(a_pInput->getOwnerClassType()));
            if(in_pLeftExpression == nullptr) return; 
            out_pExpression = o_new(PropertyExpression)(in_pLeftExpression, a_pInput);
        }
        return;

    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(Property)(o_resolveT(Type, a_pInput->getValueType())
                , a_pInput->getName()
                , o_resolveT(MemberFunction, a_pInput->getGetMemberFunction())
                , o_resolveT(MemberFunction, a_pInput->getGetMemberFunction())
                , o_resolveT(Signal, a_pInput->getSignal())
                , o_instanciateT(Range, a_pInput->getRange())
                , a_pInput->getSerializationMask()
                , a_pInput->getModifiers());
        }
        return;
    }
    visit(static_cast<NamedElement*>(a_pInput), a_Data);
}
void CPlusPlus::visit( PropertyExpression*          a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_definition)
            {
                LanguageElement* in_pScope = *(LanguageElement**)a_Data.in[1];
                string& translation = *(string*)a_Data.out[0];
                translation += "(";
                a_pInput->getLeftExpression()->visit(this, a_Data);
                translation += ").";
                translation += a_pInput->getProperty()->getName();
            }
        }
        return;

    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(PropertyExpression)(o_instanciateT(Expression, a_pInput->getLeftExpression())
                , o_resolveT(Property, a_pInput->getProperty()));
        }
        return;
    }
    visit(static_cast<LValueExpression*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( Range*                       a_pInput, visitor_data a_Data) { visit(static_cast<LanguageElement*>(a_pInput), a_Data); }
void CPlusPlus::visit( ReferenceType*               a_pInput, visitor_data a_Data) { visit(static_cast<Type*>(a_pInput), a_Data); }
void CPlusPlus::visit( ReturnStatement*             a_pInput, visitor_data a_Data) 
{ 
    switch(a_Data.id)
    {
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            if(a_pInput->getExpression())
                pInstanciated = o_new(ReturnStatement)(o_instanciateT(Expression, a_pInput->getExpression()));
            else 
                pInstanciated = o_new(ReturnStatement)();
        }
        return;
    }
}
void CPlusPlus::visit( RValueReferenceType*         a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_TemplateArgumentDeduction:
        {
            Type* pArgument = *(Type* const *)a_Data.in[0];
            Type*& pDeducedType = *(Type**)a_Data.out[0];
            map<Placeholder*, LanguageElement*>& deductions = *(map<Placeholder*, LanguageElement*>*)a_Data.out[1];
            
            bool bUniversalReference = a_pInput->getReferencedType()->asPlaceholder() != nullptr; /// T&& represents a universal reference => it can be deduced as lvalue& or rvalue&& reference
            /// but T const&& is not an universal reference 

            RValueReferenceType* pRValueReferenceTypeArgument = pArgument->asRValueReferenceType();
            if(pRValueReferenceTypeArgument)
            {
                Type* pReferencedDeducedType = templateArgumentDeduction(a_pInput->getReferencedType(), pRValueReferenceTypeArgument->getReferencedType(), deductions);
                if(pReferencedDeducedType)
                {
                    pDeducedType = pReferencedDeducedType->rvalueReferenceType();
                }
            }
            else if(bUniversalReference) /// if an universal reference (T&&) we can accept lvalue references
            {
                LValueReferenceType* pLValueReferenceTypeArgument = pArgument->asLValueReferenceType();
                if(pLValueReferenceTypeArgument)
                {
                    Type* pReferencedDeducedType = templateArgumentDeduction(a_pInput->getReferencedType(), pLValueReferenceTypeArgument->getReferencedType(), deductions);
                    if(pReferencedDeducedType)
                    {
                        pDeducedType = pReferencedDeducedType->lvalueReferenceType();
                    }
                }
            }
        }
        break;
    case e_Function_Conversion:
        {
            Type* pOutput = *(Type* const *)a_Data.in[0];
            int iConversionType = *(int const*)a_Data.in[1];
            int iUserDefinedConversionsAllowed = *(int const*)a_Data.in[2];
            LanguageElement* pContextScope = *(LanguageElement**)a_Data.in[3];
            conversion*& conv = *(conversion**)a_Data.out[0];
            if(pOutput->removeQualifiers()->equals(a_pInput))
            {
                conv = new default_conversion_sequence(new standard_conversion_sequence(a_pInput)); /// use a standard conversion to allow comparison with equivalent lvalue transformation : X& -> X
                return; /// success X& -> X&
            }
            switch(iConversionType)
            {
            case e_const_cast: 
                {
                    Type* pInputNoConst = a_pInput->removeAllQualifiers();
                    Type* pOutputNoConst = pOutput->removeAllQualifiers();
                    if(pInputNoConst->equals(a_pInput) AND pOutputNoConst->equals(pOutput)) 
                        return; /// input or output do not have const (or volatile ?) => const_cast fail
                    if(pInputNoConst->equals(pOutputNoConst)) /// no-cv input == no-cv output => const_cast ok
                        conv = new default_conversion_sequence(pInputNoConst);
                    return; /// const_cast ends here (no more user defined or else can be done)
                }
            case e_reinterpret_cast:
                {
                    if(pOutput->removeQualifiers()->asReferenceType())
                    {
                        conv = new default_conversion_sequence(a_pInput, (value_t)pOutput);
                        return; /// success X& -> Y&
                    }
                }
            }

            RValueReferenceType* pOutputReferenceType = pOutput->asRValueReferenceType();
            if(pOutputReferenceType == nullptr) /// output is not a reference type => lvalue -> rvalue transformation
            {
                bool bConstRef = false;
                LValueReferenceType* pOutputLValueReferenceType = pOutput->asLValueReferenceType();
                if(pOutputLValueReferenceType)
                {
                    if(pOutputLValueReferenceType->getReferencedType()->asConstType())
                    {
                        /// X&& -> Y const& -> lvalue
                        Type* pOutputReferencedTypeNoConst = pOutputLValueReferenceType->removeReference()->removeConst(); /// Y
                        /// Search conversion X&& -> Y
                        a_Data.in[0] = &pOutputReferencedTypeNoConst; // modify output in visitor data
                        a_pInput->visit(this, a_Data);
                        if(conv)
                        {
                            ///  if found, add const ref 
                            static_cast<default_conversion_sequence*>(conv)->addConstRef(); /// Y -> Y const&
                            return; /// success X&& -> Y const&
                        }
                        return;
                    }
                    else 
                    {
                        /// X&& -> Y&
                        /// works in case of static cast if equivalent X& -> Y& exists
                        if(iConversionType == e_static_cast OR iConversionType == e_explicit_cast)
                        {
                            a_pInput->getReferencedType()->lvalueReferenceType()->visit(this, a_Data);
                        }
                        return;
                    }
                }
                else
                {
                    pOutput = pOutput->removeQualifiers();
                    if(pOutput->equals(a_pInput->getReferencedType()))
                    {
                        /// X& -> X
                        conv = new default_conversion_sequence(new lvalue_transformation(a_pInput));
                        return;
                    }
                    ClassType* pOutputClassType = pOutput->asClassType();
                    if(iUserDefinedConversionsAllowed AND pOutputClassType)
                    {
                        /// X& -> Y(X&)
                        conv = userDefinedConversionByConstruction(a_pInput, pOutputClassType, (iConversionType == e_implicit_conversion) ? (iUserDefinedConversionsAllowed == e_explicit_functions) : true, pContextScope, false);
                        if(conv) return;
                    }
                    /// X& -> Y
                    a_pInput->getReferencedType()->visit(this, a_Data);
                    if(conv)
                    {
                        /// We found a conversion from X -> Y, we just add a lvalue_transformation to it to obtain X& -> Y
                        static_cast<default_conversion_sequence*>(conv)->addLValueTransform();
                        return; /// success X& -> Y
                    }
                }
            }
            else /// X&& -> Y&& (output is a reference type)
            {
                Type* pInputReferencedType = a_pInput->getReferencedType(); /// X

                /// X&& -> Y&&
                std::pair<Type*, Type*> constAdjustment;
                size_t adjustmentCount = 0;
                if(pOutputReferenceType->getReferencedType()->asConstType())
                {
                    /// X&& -> Y const&&
                    Type* pOutputReferencedTypeNoConst = pOutputReferenceType->getReferencedType()->removeConst(); /// Y
                    if(pInputReferencedType->isKindOf(pOutputReferencedTypeNoConst))
                    {
                        /// X and Y are related => make const adjustment
                        RValueReferenceType* adjustmentInput = pOutputReferencedTypeNoConst->rvalueReferenceType();
                        constAdjustment.first = adjustmentInput;
                        /// merge const adjustments
                        constAdjustment.second = pOutputReferenceType; 
                        adjustmentCount++;
                        pOutputReferenceType = adjustmentInput;
                        if(a_pInput->equals(pOutputReferenceType))
                        {
                            conv = new default_conversion_sequence(new qualification_adjustment(constAdjustment.first, constAdjustment.second, adjustmentCount));
                            return; /// success X&& -> X const&&
                        }
                    }
//                     else 
//                     {
//                         /// X and Y are not related => it's possibly a const ref conversion
//                         /// Search conversion X& -> Y and, if found, add const ref conversion then to do X& -> Y const& 
//                         a_Data.in[0] = &pOutputReferencedTypeNoConst; // modify output in visitor data
//                         a_pInput->getReferencedType()->visit(this, a_Data);
//                         if(conv)
//                         {
//                             static_cast<default_conversion_sequence*>(conv)->addConstRef();
//                             return; /// success X&& -> Y const&
//                         }
//                         return;
//                     }
                }
                else if(a_pInput->getReferencedType()->asConstType())
                {
                    return; /// failure X const&& -/-> Y&&
                }
                Type* pOutputReferencedType = pOutputReferenceType->getReferencedType();
                if((pInputReferencedType->asClass() != nullptr) AND (pOutputReferencedType->asClass() != nullptr)) 
                {
                    reflection::Class* pInputClass       = static_cast<reflection::Class*>(pInputReferencedType);
                    reflection::Class* pOutputClass  = static_cast<reflection::Class*>(pOutputReferencedType);
                    size_t level = pInputClass->getInheritanceLevelFromBase(pOutputClass);
                    if(level != ~size_t(0)) // level != -1 => inheritance relation => pointers are related
                    {
                        auto* pPtr = new pointer_conversion(a_pInput, pOutputReferenceType, level, pInputClass->getBaseClassOffsetCascade(pOutputClass));
                        if(adjustmentCount)
                            conv = new default_conversion_sequence(pPtr, new qualification_adjustment(constAdjustment.first, constAdjustment.second, adjustmentCount));
                        conv = new default_conversion_sequence(pPtr);
                        /// success Derived&& -> Base(const)&&
                    }
                }
            }
        }
        break;

    case e_Function_ResolveTemplateDependencies:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pResolved = *(LanguageElement**)a_Data.out[0];
            Type* pNewReferencedType = o_resolveT(Type, a_pInput->getReferencedType());
            pResolved = pNewReferencedType ? pNewReferencedType->rvalueReferenceType() : nullptr;
        }
        return;
    }
    visit(static_cast<ReferenceType*>(a_pInput), a_Data);
}
void CPlusPlus::visit( Scope*                       a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_SubroutineResolution:
        {
            const string& in_name = *(const string*)a_Data.in[0];
            const vector<LanguageElement*>* in_pTemplateArguments = (const vector<LanguageElement*>*)a_Data.in[1];
            const vector<Type*>* in_pFunctionTypes = (const vector<Type*>*)a_Data.in[2];
            modifiers_t in_Qualifiers = *(modifiers_t*)a_Data.in[3];
            LanguageElement* in_pContextScope = *(LanguageElement**)a_Data.in[4];
            LanguageElement*& out_pResult = *(LanguageElement**)a_Data.out[0];
            if(in_pTemplateArguments)
            {
                /// TODO : template subroutines
                o_assert_no_implementation();
            }
            Subroutine* pSubroutine = a_pInput->getSubroutine(in_name, *in_pFunctionTypes, in_Qualifiers);
            if(pSubroutine)
            {
                out_pResult = pSubroutine;
                return;
            }
        }
        break;

    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            if(pInstanciated)
            {
                Scope* pEnclosingScope = pInstanciated->asScope();
                for(auto it = a_pInput->beginFunctions(); it != a_pInput->endFunctions(); ++it)
                {
                    pEnclosingScope->addFunction(o_instanciateT(Function, *it));
                }
                for(auto it = a_pInput->beginVariables(); it != a_pInput->endVariables(); ++it)
                {
                    pEnclosingScope->addVariable(o_instanciateT(Variable, *it));
                }
                for(auto it = a_pInput->beginAliases(); it != a_pInput->endAliases(); ++it)
                {
                    pEnclosingScope->addAlias(o_instanciateT(Alias, *it));
                }
                for(auto it = a_pInput->beginTypes(); it != a_pInput->endTypes(); ++it)
                {
                    pEnclosingScope->addType(o_instanciateT(Type, *it));
                }
                for(auto it = a_pInput->beginTemplates(); it != a_pInput->endTemplates(); ++it)
                {
                    pEnclosingScope->addTemplate(o_instanciateT(Template, *it));
                }
                for(auto it = a_pInput->beginTemplateSpecializations(); it != a_pInput->endTemplateSpecializations(); ++it)
                {
                    pEnclosingScope->addTemplateSpecialization(o_instanciateT(TemplateSpecialization, *it));
                }
            }
        }
        return;
    }
}
void CPlusPlus::visit( SequentialContainerClass*    a_pInput, visitor_data a_Data) { visit(static_cast<Class*>(a_pInput), a_Data); }
void CPlusPlus::visit( SetContainerClass*           a_pInput, visitor_data a_Data) { visit(static_cast<Class*>(a_pInput), a_Data); }
void CPlusPlus::visit( Signal*                      a_pInput, visitor_data a_Data) 
{ 
    switch(a_Data.id)
    {
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(Signal)(a_pInput->getName(), o_instanciateT(Signature, a_pInput->getSignature()), a_pInput->getModifiers());
            visit(static_cast<Subroutine*>(a_pInput), a_Data);
        }
        return;
    }
    visit(static_cast<NamedElement*>(a_pInput), a_Data);
}
void CPlusPlus::visit( Signature*                   a_pInput, visitor_data a_Data) 
{

    switch(a_Data.id)
    {
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            vector<Parameter*> parameters;
            for(auto it = a_pInput->beginParameters(); it != a_pInput->endParameters(); ++it)
            {
                parameters.push_back(o_instanciateT(Parameter, *it));
            }
            pInstanciated = o_new(Signature)(o_resolveT(Type, a_pInput->getReturnType())
                , parameters
                , a_pInput->getModifiers());
        } 
        return;
    }
    visit(static_cast<NamedElement*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( Source*                      a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_UnqualifiedLookup:
    case e_Function_QualifiedLookup:
    case e_Function_QualifiedNameLookup:
        visit(static_cast<LanguageElement*>(a_pInput), a_Data); 
        break;
    }
}
void CPlusPlus::visit( State*                       a_pInput, visitor_data a_Data) 
{ 
    switch(a_Data.id)
    {
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(State)(a_pInput->getName(), a_pInput->getModifiers());
            State* pState = static_cast<State*>(pInstanciated);
            for(auto it = a_pInput->beginTracks(); it != a_pInput->endTracks(); ++it)
            {
                pState->addTrack(o_instanciateT(Track, *it));
            }
        } 
        return;
    }
    visit(static_cast<StateMachineElement*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( StateMachine*                a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(StateMachine)(a_pInput->getModifiers());
            StateMachine* pStateMachine = static_cast<StateMachine*>(pInstanciated);
            pStateMachine->setRootTrack(o_instanciateT(Track, a_pInput->getRootTrack()));
        } 
        return;
    }
    visit(static_cast<NamedElement*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( StateMachineElement*         a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void CPlusPlus::visit( Statement*                   a_pInput, visitor_data a_Data) { visit(static_cast<Evaluable*>(a_pInput), a_Data); }
void CPlusPlus::visit( StringLiteralExpression*     a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_definition)
            {
                string& translation = *(string*)a_Data.out[0];
                translateLiteral(a_pInput->getString(), translation);
            }
        }
        return;

        o_instanciate_template_clone;
    }
    visit(static_cast<Expression*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( Structure*                   a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(Structure)(a_pInput->getName(), a_pInput->getModifiers());
            visit(static_cast<ClassType*>(a_pInput), a_Data);
        }
        return;
    }
    visit(static_cast<ClassType*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( Subroutine*                  a_pInput, visitor_data a_Data) 
{ 
    switch(a_Data.id)
    {
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            Subroutine* pSubroutine = static_cast<Subroutine*>(pInstanciated);
            o_assert(pSubroutine);
            if(a_pInput->getBlock()) { o_instanciateT(Block, a_pInput->getBlock()); }
        }
        return;
    }
    visit(static_cast<NamedElement*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( TDBinaryOperationExpression* a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_definition)
            {
                LanguageElement* in_pScope = *(LanguageElement**)a_Data.in[1];
                string& translation = *(string*)a_Data.out[0];
                translation += '(';
                a_pInput->getLeftExpression()->visit(this, a_Data);
                translation += ')';
                translation += a_pInput->getOperator();
                translation += '(';
                a_pInput->getRightExpression()->visit(this, a_Data);
                translation += ')';
            }
        }
        return;

    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            Expression* pLeft = o_instanciateT(Expression, a_pInput->getLeftExpression());
            Expression* pRight = o_instanciateT(Expression, a_pInput->getRightExpression());
            Expression* pOperation = solveBinaryOperator(a_pInput->getOperator(), pLeft, pRight, pScope);
            if(pOperation == nullptr)
            {
                o_semantic_error("no binary '"<<a_pInput->getOperator()<<"' operator found that takes left argument of type '"<<pLeft->getValueType()->getQualifiedDecoratedName()<<"' and right argument of type '"<<pRight->getValueType()->getQualifiedDecoratedName()<<"'");
            }
        }
        return;
    }
    visit(static_cast<Expression*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( TDUnaryPostOperationExpression*a_pInput, visitor_data a_Data) 
{ 
    switch(a_Data.id)
    {
    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_definition)
            {
                LanguageElement* in_pScope = *(LanguageElement**)a_Data.in[1];
                string& translation = *(string*)a_Data.out[0];
                translation += '(';
                a_pInput->getExpression()->visit(this, a_Data);
                translation += ')';
                translation += a_pInput->getOperator();
            }
        }
        return;
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            Expression* pExpression = o_instanciateT(Expression, a_pInput->getExpression());
            Expression* pOperation = solveUnaryPostOperator(a_pInput->getOperator(), pExpression, pScope);
            if(pOperation == nullptr)
            {
                o_semantic_error("no unary postfix '"<<a_pInput->getOperator()<<"' operator found that takes expression of type '"<<pExpression->getValueType()->getQualifiedDecoratedName()<<"'");
            }
        }
        return;
    }
    visit(static_cast<Expression*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( TDUnaryPreOperationExpression*a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_definition)
            {
                LanguageElement* in_pScope = *(LanguageElement**)a_Data.in[1];
                string& translation = *(string*)a_Data.out[0];
                translation += a_pInput->getOperator();
                translation += '(';
                a_pInput->getExpression()->visit(this, a_Data);
                translation += ')';
            }
        }
        return;

    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            Expression* pExpression = o_instanciateT(Expression, a_pInput->getExpression());
            Expression* pOperation = solveUnaryPreOperator(a_pInput->getOperator(), pExpression, pScope);
            if(pOperation == nullptr)
            {
                o_semantic_error("no unary prefix '"<<a_pInput->getOperator()<<"' operator found that takes expression of type '"<<pExpression->getValueType()->getQualifiedDecoratedName()<<"'");
            }
        }
        return;
    }
    visit(static_cast<Expression*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( Track*                       a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(Track)(a_pInput->getName(), a_pInput->getSerializationMask(), a_pInput->getModifiers());
            Track* pTrack = static_cast<Track*>(pInstanciated);
            for(auto it = a_pInput->beginStates(); it != a_pInput->endStates(); ++it)
            {
                pTrack->addState(o_instanciateT(State, *it));
            } 
        }
        return;
    }
    visit(static_cast<StateMachineElement*>(a_pInput), a_Data); 
}

void CPlusPlus::visit( Template*                    a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_ResolveTemplateDependencies:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            map<Placeholder*, LanguageElement*> arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pResolved = *(LanguageElement**)a_Data.out[0];

            /// update data for possible deeper resolution
            TemplateSignature* pInputTemplateSignature = a_pInput->getTemplateSignature();
            a_Data.in[0] = pInputTemplateSignature;
            a_Data.in[1] = &arguments;

            /// Do template accepts given arguments ?
            bool empty = true;
            bool full = true; 
            for(auto it = arguments.begin(); it != arguments.end(); ++it)
            {
                if(it->second->isTemplateDependant())
                {
                    /// if any template dependant element found, it's not a full instanciation
                    full = false;
                }
                else 
                {
                    /// if any template independant element found, it's not an empty instanciation
                    empty = false;
                }
            }
            if(full)
            {
                /// Full => start first by looking for full specializations

                /// if arguments are full, instanciate missing template default arguments
                size_t i = arguments.size();
                size_t count = a_pInput->getTemplateParameterCount();
                if(a_pInput->getDefaultArgumentCount() < (count-i))
                {
                    o_semantic_error("not enough template arguments provided");
                }
                if(count-i)
                {
                    LanguageElement* pSolvedArgument = nullptr;
                    a_Data.out[0] = &pSolvedArgument;
                    for(; i<count; ++i)
                    {
                        a_pInput->getDefaultArgument(i)->visit(this, a_Data);
                        Placeholder* pPlaceholder = a_pInput->getTemplateSignature()->getParameter(i)->getPlaceholder();
                        o_assert(arguments.find(pPlaceholder) == arguments.end());
                        arguments[pPlaceholder] = pSolvedArgument;
                    }
                }

                /// Find viable specializations
                vector<TemplateSpecialization*> viableSpecializations;
                vector<map<Placeholder*, LanguageElement*>> viableDeductions;
                for(auto it = a_pInput->beginTemplateSpecializations(); it != a_pInput->endTemplateSpecializations(); ++it)
                {
                    TemplateSpecialization* pT0 = *it;
                    bool result = true;
                    map<Placeholder*, LanguageElement*> deductions;
                    for(auto it = arguments.begin(); it != arguments.end(); ++it)
                    {
                        LanguageElement* pParameter = pT0->getArgument(static_cast<TemplateParameter*>(it->first->asNamedElement()->getOwner())->getIndex());
                        LanguageElement* pArgument = it->second;
                        if(NOT(templateArgumentDeduction(pParameter, pArgument, deductions)))
                        {
                            result = false;
                            break;
                        }
                    }
                    result = result AND (deductions.size() == pT0->getTemplateSignature()->getParameterCount());
                    if(result)
                    {
                        viableSpecializations.push_back(pT0);
                        viableDeductions.push_back(deductions);
                    }
                }
                /// Find best specialization
                TemplateSpecialization* pBestTemplateSpecialization = nullptr;
                map<Placeholder*, LanguageElement*>* pBestDeductions = nullptr;
                size_t viableSpecializationsCount = viableSpecializations.size();
                if(viableSpecializationsCount)
                {
                    if(viableSpecializationsCount == 1)
                    {
                        pBestTemplateSpecialization = viableSpecializations.back();
                        pBestDeductions = &viableDeductions.back();
                    }
                    else 
                    {
                        for(size_t i = 0; i<viableSpecializationsCount; ++i)
                        {
                            TemplateSpecialization* pT0 = viableSpecializations[i];

                            int bestResult = -1;
                            size_t j = 0;
                            for(; j<viableSpecializationsCount; ++j)
                            {
                                TemplateSpecialization* pT1 = viableSpecializations[j];
                                if((pT0 == pT1)) continue;

                                int result = compareSpecialized(pT0, pT1);
                                o_assert(-result == compareSpecialized(pT1, pT0));
                                if(result >= 0)
                                    bestResult = std::max(bestResult, result);
                                else 
                                    break;
                            }
                            if(j == viableSpecializationsCount)
                            {
                                if(bestResult == 1)
                                {
                                    pBestTemplateSpecialization = pT0;
                                    pBestDeductions = &viableDeductions[i];
                                    break;
                                }
                            }
                        }
                    }
                }
                     
                if(pBestTemplateSpecialization)
                {
                    if(pBestTemplateSpecialization->getBody() == nullptr)
                    {
                        o_semantic_error("instanciation of undefined template class specialization");
                        pResolved = nullptr;
                        return;
                    }
//                     if(a_Data.hasFlag(e_Flag_ExpressionMode) AND NOT(pBestTemplateSpecialization->getBody()->isFinalized()))
//                     {
//                         pResolved = nullptr;
//                         return;
//                     }

                    // If full just return the body
                    if(pBestTemplateSpecialization->isFull())
                    {
                        pResolved = pBestTemplateSpecialization->getBody();
                        return;
                    }

                    // Else create the full specialization based on the partial specialization + arguments
                    LanguageElement* pBestTemplateSpecializationResolved = resolveTemplateDependency(pBestTemplateSpecialization, pBestTemplateSpecialization->getTemplateSignature(), *pBestDeductions, pBestTemplateSpecialization->getOwner());

                    if(pBestTemplateSpecializationResolved AND pBestTemplateSpecializationResolved->asTemplateSpecialization())
                    {
                        if(pBestTemplateSpecialization->isFinalized()) 
                            static_cast<TemplateSpecialization*>(pBestTemplateSpecializationResolved)->setFinalized();
                        pResolved = static_cast<TemplateSpecialization*>(pBestTemplateSpecializationResolved)->getBody();
                        return;
                    }
                    pResolved = nullptr;
                    return;
                }
            }
            else 
            {
                TemplateSpecialization* pAscendantTemplateSpecialization = pScope->getAscendantTemplateSpecialization();
                o_assert(pAscendantTemplateSpecialization == nullptr OR pAscendantTemplateSpecialization->getTemplateSignature()->getParameterCount() != 0);

                ClassType* pClassType = nullptr;

                /// Declaration outside a template declaration 
                /// This case is for deferred template specialization member function definition 
                /// ex: template<typename T> void Foo<T, int>::bar() {}
                /// => we look for the specialization matching exactly the given arguments (not partially)
                if(pAscendantTemplateSpecialization == nullptr)
                {
                    if(pScope->asTemplateSignature())
                    {
                        TemplateSpecialization* pTemplateSpecialization = empty 
                            ? a_pInput->getEmptyTemplateSpecialization() 
                            : a_pInput->getTemplateSpecialization(arguments);
                        if(pTemplateSpecialization == nullptr)
                        {
                            if(empty)
                                o_semantic_error("no template declaration found that match the given template arguments");
                            else
                                o_semantic_error("no template partial specialization definition found that match the given template arguments");
                            return ;
                        }
                        else pClassType = pTemplateSpecialization->getBody()->asClassType();
                    }
                    else 
                    {
                        o_semantic_error("template declaration requires template signature");
                        return;
                    }
                }
                else /// Declaration inside a template declaration => we just look for any instance matching the template
                {
                    pClassType = o_new(TemplateDependantTemplateInstance)(a_pInput, arguments);
                    pAscendantTemplateSpecialization->addElement(pClassType);
                }
                pResolved = pClassType;
                return;
            }
        }
        return;
    }
    visit(static_cast<NamedElement*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( TemplateDependantArrayType*  a_pInput, visitor_data a_Data) 
{
    switch(a_Data.id)
    {
    case e_Function_TemplateArgumentDeduction:
        {
            Type* pArgument = *(Type* const *)a_Data.in[0];
            Type*& pDeducedType = *(Type**)a_Data.out[0];
            map<Placeholder*, LanguageElement*>& deductions = *(map<Placeholder*, LanguageElement*>*)a_Data.out[1];
            PlaceholderConstant* pDeductibleConstant = a_pInput->getDeductibleConstant();
            if(pDeductibleConstant)
            {
                ArrayType* pArrayTypeArgument = pArgument->asArrayType();
                if(pArrayTypeArgument)
                {
                    auto found = deductions.find(pDeductibleConstant);
                    if(found != deductions.end())
                    {
                        Expression* pOldExpression = found->second->asExpression();
                        Expression* pNewExpression = a_pInput->getItemCountExpression();
                        if(pOldExpression AND pOldExpression->isCompileTime()
                            AND pNewExpression AND pNewExpression->isCompileTime()
                            AND pOldExpression->getValueType()->removeReference()->equals(pNewExpression->getValueType()->removeReference()))
                        {
                            Expression* pExpression = solveBinaryOperator("==", pOldExpression, pNewExpression, nullptr);
                            o_assert(pExpression->isCompileTime());
                            bool equals = false;
                            pExpression->load(&equals);
                            o_dynamic_delete pExpression;
                            if(!equals)
                                return;
                        }
                        else return;
                    }
                    else deductions[pDeductibleConstant] = constant<size_t>(pArrayTypeArgument->getItemCount())->toExpression();
                    pDeducedType = pArgument;
                }
            }
        }
        break;
    }
    visit(static_cast<ArrayType*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( TemplateDependantElement*    a_pInput, visitor_data a_Data )
{
    switch(a_Data.id)
    {
    case e_Function_QualifiedNameLookup:
        {
            const string& in_name = *(const string*)a_Data.in[0];
            vector<LanguageElement*>& out_candidates = *(vector<LanguageElement*>*)a_Data.out[0];
            out_candidates.push_back(o_new(TemplateDependantElement)(a_pInput, in_name));
        }
        break;
    case e_Function_ResolveTemplateDependencies:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* in_pContextScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pResolved = *(LanguageElement**)a_Data.out[0];
            bool bDeepResolution = true;
            LanguageElement* pScope = in_pContextScope;
            if(a_pInput->getLeft())
            {
                bDeepResolution = false;
                pScope = o_resolveT(LanguageElement, a_pInput->getLeft());
                if(pScope == nullptr)
                {
                    o_semantic_error("invalid left hand side in template dependant expression resolution");
                    return;
                }
            }
            vector<Expression*> functionArguments;
            vector<Type*> functionTypes;
            vector<LanguageElement*> templateArguments;
            vector<Expression*>* pFunctionArguments = nullptr;
            vector<Type*>* pFunctionTypes = nullptr;
            vector<LanguageElement*>* pTemplateArguments = nullptr;
            bool bExpressions = true;
            bool bTypes = true;
            if(a_pInput->getFunctionArguments())
            {
                for(auto it = a_pInput->getFunctionArguments()->begin(); it != a_pInput->getFunctionArguments()->end(); ++it)
                {
                    LanguageElement* pElement = o_resolveT(LanguageElement, *it);
                    if(pElement->asExpression() AND bExpressions)
                    {
                        bTypes = false;
                        functionArguments.push_back(pElement->asExpression());
                        pFunctionArguments = &functionArguments;
                    }
                    else if(pElement->asType() AND bTypes)
                    {
                        bExpressions = false;
                        functionTypes.push_back(pElement->asType());
                        pFunctionTypes = &functionTypes;
                    }
                    else 
                    {
                        o_semantic_error("invalid expression in template dependant function signature");
                    }
                }
            }
            if(a_pInput->getTemplateArguments())
            {
                pTemplateArguments = &templateArguments;
                for(auto it = a_pInput->getTemplateArguments()->begin(); it != a_pInput->getTemplateArguments()->end(); ++it)
                {
                    LanguageElement* pElement = o_resolveT(LanguageElement, *it);
                    if(pElement == nullptr)
                    {
                        o_semantic_error("invalid template argument in template dependant expression resolution");
                    }
                    templateArguments.push_back(pElement);
                }
            }
            if(pFunctionTypes)
            {
                Subroutine* pSubroutine = bDeepResolution 
                                                ? solveSubroutineCascade(pScope, a_pInput->getName(), pTemplateArguments, *pFunctionTypes, a_pInput->getModifiers(), in_pContextScope)
                                                : solveSubroutine(pScope, a_pInput->getName(), pTemplateArguments, *pFunctionTypes, a_pInput->getModifiers(), in_pContextScope);
                if(pSubroutine)
                {
                    pResolved = pSubroutine;
                }
                else 
                {
                    o_semantic_error("template dependant subroutine resolution failed");
                }
                return;
            }
            pResolved = bDeepResolution 
                            ? unqualifiedLookup(a_pInput->getName(), pTemplateArguments, pFunctionArguments, in_pContextScope, nullptr)
                            : qualifiedLookup(pScope, a_pInput->getName(), pTemplateArguments, pFunctionArguments, in_pContextScope, nullptr);
            
            if(pResolved == nullptr)
            {
                o_semantic_error("template dependant element resolution failed");
            }
        }
        return;
    }
}
void CPlusPlus::visit( TemplateDependantExpression* a_pInput, visitor_data a_Data )
{
    switch(a_Data.id)
    {
    case e_Function_QualifiedNameLookup:
        {
            const string& in_name = *(const string*)a_Data.in[0];
            vector<LanguageElement*>& out_candidates = *(vector<LanguageElement*>*)a_Data.out[0];
            out_candidates.push_back(o_new(TemplateDependantElement)(a_pInput, in_name));
        }
        break;
    case e_Function_ResolveTemplateDependencies:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pResolved = *(LanguageElement**)a_Data.out[0];
            a_pInput->getOwner()->visit(this, a_Data);
            if(pResolved)
            {
                pResolved = pResolved->asExpression();
                if(pResolved == nullptr)
                {
                    o_semantic_error("expected valid value expression");
                }
            }
        }
        return;
    }
    visit(static_cast<Expression*>(a_pInput), a_Data);
}
void CPlusPlus::visit( TemplateDependantTemplateInstance* a_pInput, visitor_data a_Data )
{
    switch(a_Data.id)
    {
    case e_Function_TemplateArgumentDeduction:
        {
            LanguageElement* pArgument = *(LanguageElement* const *)a_Data.in[0];
            LanguageElement*& pDeducedArgument = *(LanguageElement**)a_Data.out[0];
            map<Placeholder*, LanguageElement*>& deductions = *(map<Placeholder*, LanguageElement*>*)a_Data.out[1];
            ClassType* pClassTypeArgument = pArgument->asClassType();
            size_t count = a_pInput->getTemplate()->getTemplateSignature()->getParameterCount();
            if(pClassTypeArgument)
            {
                if(pClassTypeArgument->getTypeId() == e_template_dependant)
                {
                    TemplateDependantTemplateInstance* pTDTI = static_cast<TemplateDependantTemplateInstance*>(pClassTypeArgument);
                    /// Both template template parameter and template argument has same parameter/argument count
                    if(pTDTI->getTemplate()->getTemplateSignature()->getParameterCount() == count)
                    {
                        size_t i = 0;
                        for(; i<count; ++i)
                        {
                            TemplateParameter* pTemplateParameter = a_pInput->getTemplate()->getTemplateSignature()->getParameter(i);
                            Placeholder* pPlaceholder = pTemplateParameter->getPlaceholder();
                            LanguageElement* pParameter = a_pInput->getArgument(pPlaceholder);
                            LanguageElement* pArgument = pTDTI->getArgument(pPlaceholder);
                            if(pArgument == nullptr) 
                                return;
                            if(NOT(templateArgumentDeduction(pParameter, pArgument, deductions)))
                                return;
                        }
                        pDeducedArgument = pClassTypeArgument;
                    }
                }
                else
                {
                    TemplateSpecialization* pSpec = pClassTypeArgument->getOwner() ? pClassTypeArgument->getOwner()->asTemplateSpecialization() : nullptr;
                    if(pSpec)
                    {
                        /// Both template template parameter and template argument has same parameter/argument count
                        if(pSpec->getTemplateSignature()->getParameterCount() == count)
                        {
                            size_t i = 0;
                            for(; i<count; ++i)
                            {
                                TemplateParameter* pTemplateParameter = a_pInput->getTemplate()->getTemplateSignature()->getParameter(i);
                                LanguageElement* pParameter = a_pInput->getArgument(pTemplateParameter->getPlaceholder());
                                LanguageElement* pArgument = pSpec->getArgument(i);
                                if(NOT(templateArgumentDeduction(pParameter, pArgument, deductions)))
                                    return;
                            }
                            pDeducedArgument = pClassTypeArgument;
                        }
                    }
                }
            }
        }
        return;
    
    case e_Function_QualifiedNameLookup:
        {
            const string& in_name = *(const string*)a_Data.in[0];
            vector<LanguageElement*>& out_candidates = *(vector<LanguageElement*>*)a_Data.out[0];
//             if(a_pInput->getTemplateSpecialization())
//             {
//                 LanguageElement* pBody = a_pInput->getTemplateSpecialization()->getBody();
//                 if(pBody == nullptr OR pBody->asClassType() == nullptr)
//                 {
//                     o_semantic_error("use of undefined template instanciation");
//                 }
//                 else pBody->visit(this, a_Data);
//                 return;
//             }
            out_candidates.push_back(o_new(TemplateDependantElement)(a_pInput, in_name));
        }

    case e_Function_ResolveTemplateDependencies:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pResolved = *(LanguageElement**)a_Data.out[0];
            LanguageElement* pElement = nullptr;
            map<Placeholder*, LanguageElement*> newArguments;
            for(auto it = a_pInput->beginArguments(); it != a_pInput->endArguments(); ++it)
            {
                newArguments[it->first] = o_resolveT(LanguageElement, it->second);
            }
            pResolved = resolveTemplateDependency(a_pInput->getTemplate(), pTemplateSignature, newArguments, pScope);
        }
        return;
    }
}
void CPlusPlus::visit( TemplateDependantType* a_pInput, visitor_data a_Data )
{
    switch(a_Data.id)
    {
    case e_Function_QualifiedNameLookup:
        {
            const string& in_name = *(const string*)a_Data.in[0];
            vector<LanguageElement*>& out_candidates = *(vector<LanguageElement*>*)a_Data.out[0];
            out_candidates.push_back(o_new(TemplateDependantElement)(a_pInput, in_name));
        }
        break;
    case e_Function_ResolveTemplateDependencies:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pResolved = *(LanguageElement**)a_Data.out[0];
            a_pInput->getOwner()->visit(this, a_Data);
            if(pResolved)
            {
                pResolved = pResolved->asType();
                if(pResolved == nullptr)
                {
                    o_semantic_error("expected valid type expression");
                }
            }
        }
        return;
    }
    visit(static_cast<Type*>(a_pInput), a_Data);
}
void CPlusPlus::visit( TemplateParameter*           a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void CPlusPlus::visit( TemplateSignature*           a_pInput, visitor_data a_Data) 
{ 
    switch(a_Data.id)
    {
    case e_Function_QualifiedNameLookup:
        {
            const string& in_name = *(const string*)a_Data.in[0];
            vector<LanguageElement*>& out_candidates = *(vector<LanguageElement*>*)a_Data.out[0];
            TemplateParameter* pParam = a_pInput->getParameter(in_name);
            if(pParam)
            {
                out_candidates.push_back(pParam->getPlaceholder()->asNamedElement());
                return;
            }
        }
    }
    visit(static_cast<NamedElement*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( TemplateSpecialization*      a_pInput, visitor_data a_Data) 
{ 
    switch(a_Data.id)
    {
    case e_Function_UnqualifiedLookup:
        {
            const string& in_name = *(const string*)a_Data.in[0];
            const vector<LanguageElement*>* in_pTemplateArguments = (const vector<LanguageElement*>*)a_Data.in[1];
            const vector<Expression*>* in_pFunctionArguments = (const vector<Expression*>*)a_Data.in[2];
            Type* in_pInitializationType = (Type*)a_Data.in[3];
            LanguageElement* in_pContextScope = *(LanguageElement**)a_Data.in[4];
            LanguageElement*& out_pResult = *(LanguageElement**)a_Data.out[0];
            out_pResult = qualifiedLookup(a_pInput->getTemplateSignature(), in_name, in_pTemplateArguments, in_pFunctionArguments, in_pContextScope, in_pInitializationType);
            if(out_pResult)
                return;
        }
        break;
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            vector<LanguageElement*> resolvedArguments;
            for(auto it = a_pInput->beginArguments(); it != a_pInput->endArguments(); ++it)
            {
                resolvedArguments.push_back(o_resolveT(LanguageElement, (*it)));
            }
            TemplateSignature* resolvedSignature =  o_instanciateT(TemplateSignature, a_pInput->getTemplateSignature());
            pInstanciated = o_new(TemplateSpecialization)(a_pInput->getTemplate()
                , resolvedSignature
                , resolvedArguments
                , o_instanciateT(ClassType, a_pInput->getBody()));
            Scope* pTemplateScope = a_pInput->getTemplate()->getOwner()->asScope();
            o_assert(pTemplateScope);
            pTemplateScope->addTemplateSpecialization(static_cast<TemplateSpecialization*>(pInstanciated));
        }
        return;
    case e_Function_ResolveTemplateDependencies:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];

            if(a_pInput->isFull())
            {
                pInstanciated = a_pInput;
            }
            else 
            {
                vector<LanguageElement*> newArguments;
                for(auto it = a_pInput->beginArguments(); it != a_pInput->endArguments(); ++it)
                {
                    newArguments.push_back(o_resolveT(LanguageElement, *it));
                }
                pInstanciated = o_new(TemplateSpecialization)(a_pInput->getTemplate()
                                                            , o_new(TemplateSignature)
                                                            , newArguments
                                                            , o_instanciateT(NamedElement, a_pInput->getBody()));
                Scope* pScope = a_pInput->getTemplate()->getOwner()->asScope();
                o_assert(pScope);
                pScope->addTemplateSpecialization(static_cast<TemplateSpecialization*>(pInstanciated));
            }
        }
        return;
    }
    visit(static_cast<NamedElement*>(a_pInput), a_Data);
}
void CPlusPlus::visit( Type*                        a_pInput, visitor_data a_Data) 
{ 
    switch(a_Data.id)
    {
    case e_Function_Conversion:
        {
            Type* pOutput = *(Type* const *)a_Data.in[0];
            int iConversionType = *(int const*)a_Data.in[1];
            int iUserDefinedConversionsAllowed = *(int const*)a_Data.in[2];
            LanguageElement* pContextScope = *(LanguageElement* const*)a_Data.in[3];
            conversion*& conv = *(conversion**)a_Data.out[0];
            bool bConstRef = baseConversion(a_pInput, pOutput, iConversionType);
            if(bConstRef AND a_pInput->equals(pOutput))
            {
                conv = new default_conversion_sequence(new constref_conversion(pOutput)) ;
                return;
            }
            if(iUserDefinedConversionsAllowed) 
            {
                conv = userDefinedConversion(a_pInput, pOutput, (iConversionType == e_implicit_conversion) ? (iUserDefinedConversionsAllowed == e_explicit_functions) : true, pContextScope, bConstRef);
                if(conv AND bConstRef)
                {
                    static_cast<default_conversion_sequence*>(conv)->addConstRef();
                }
            }
            return;
        }
    }
    visit(static_cast<NamedElement*>(a_pInput), a_Data);
}
void CPlusPlus::visit( Union*                       a_pInput, visitor_data a_Data) 
{ 
    switch(a_Data.id)
    {
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(Union)(a_pInput->getName(), a_pInput->getModifiers());
            visit(static_cast<ClassType*>(a_pInput), a_Data);
        }
        return;
    }
    visit(static_cast<ClassType*>(a_pInput), a_Data); 
}
void CPlusPlus::visit( ValueMember*                 a_pInput, visitor_data a_Data) 
{ 
    visit(static_cast<NamedElement*>(a_pInput), a_Data);
}
void CPlusPlus::visit( Variable*                    a_pInput, visitor_data a_Data) 
{ 
    switch(a_Data.id)
    {
    case e_Function_ToExpression:
        {
            Expression* in_pLeftExpression = *(Expression**)a_Data.in[0];
            Expression*& out_pExpression = *(Expression**)a_Data.out[0];
            out_pExpression = o_new(VariableExpression)(a_pInput, in_pLeftExpression);
        }
        return;
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(Variable)(o_resolveT(Type, a_pInput->getValueType())
                , a_pInput->getName(), o_instanciateT(Range, a_pInput->getRange()), a_pInput->getModifiers());
        }
        return;
    }
    visit(static_cast<NamedElement*>(a_pInput), a_Data);
}
void CPlusPlus::visit( VariableExpression*          a_pInput, visitor_data a_Data) 
{ 
    switch(a_Data.id)
    {
    case e_Function_Translate:
        {
            int in_TranslationType = *(int*)a_Data.in[0];
            if(in_TranslationType == e_translation_definition)
            {
                LanguageElement* in_pScope = *(LanguageElement**)a_Data.in[1];
                string& translation = *(string*)a_Data.out[0];
                translate(a_pInput->getVariable(), translation, e_translation_qualified_decorated_name, in_pScope);
            }
        }
        return;
    case e_Function_InstanciateTemplate:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pInstanciated = *(LanguageElement**)a_Data.out[0];
            pInstanciated = o_new(VariableExpression)(o_resolveT(Variable, a_pInput->getVariable()));
        }
        return;
    }
    visit(static_cast<LValueExpression*>(a_pInput), a_Data);    
}
void CPlusPlus::visit( VirtualMemberFunctionTable*  a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void CPlusPlus::visit( VolatileType*                a_pInput, visitor_data a_Data)
{
    switch(a_Data.id)
    {
    case e_Function_TemplateArgumentDeduction:
        {
            LanguageElement* pArgument = *(LanguageElement* const *)a_Data.in[0];
            LanguageElement*& pDeducedArgument = *(LanguageElement**)a_Data.out[0];
            map<Placeholder*, LanguageElement*>& deductions = *(map<Placeholder*, LanguageElement*>*)a_Data.out[1];
            VolatileType* pType = pArgument->asVolatileType();
            if(pType)
            {
                Type* pDeducedType = templateArgumentDeduction(a_pInput->getVolatiledType(), pType->getVolatiledType(), deductions);
                if(pDeducedType)
                {
                    pDeducedArgument = pDeducedType->volatileType();
                }
            }
            else 
            {
                ConstVolatileType* pType = pArgument->asConstVolatileType();
                if(pType)
                {
                    Type* pDeducedType = templateArgumentDeduction(a_pInput->getVolatiledType(), pType->removeVolatile(), deductions);
                    if(pDeducedType)
                    {
                        pDeducedArgument = pDeducedType->volatileType();
                    }
                }
            }
        }
        return;

    case e_Function_Conversion:
        {
            a_pInput->getVolatiledType()->visit(this, a_Data);
        }
        return;

    case e_Function_ResolveTemplateDependencies:
        {
            TemplateSignature* pTemplateSignature = *(TemplateSignature**)a_Data.in[0];
            const map<Placeholder*, LanguageElement*>& arguments = *(const map<Placeholder*, LanguageElement*>*)a_Data.in[1];
            LanguageElement* pScope = *(LanguageElement**)a_Data.in[2];
            LanguageElement*& pResolved = *(LanguageElement**)a_Data.out[0];
            Type* pType = o_resolveT(Type, a_pInput->getVolatiledType());
            pResolved = pType ? pType->volatileType() : nullptr;
        }
        return;
    }
    visit(static_cast<Type*>(a_pInput), a_Data);
}

void CPlusPlus::visit( native::TFundamentalType<void>* a_pInput, visitor_data a_Data) { return ; }
void CPlusPlus::visit( native::TFundamentalType<std::nullptr_t>* a_pInput, visitor_data a_Data )
{
    switch(a_Data.id)
    {
    case e_Function_Conversion:
        {
            Type* pOutput = (*(Type* const *)a_Data.in[0])->removeQualifiers();
            int iConversionType = *(int const*)a_Data.in[1];
            conversion*& conv = *(conversion**)a_Data.out[0];
            if(pOutput->asDataPointerType())
            {
                numeric_conversion* nconv = iConversionType == e_implicit_conversion                                                                               \
                    ? (numeric_conversion*)new tnumeric_conversion<std::nullptr_t, void*, e_implicit_conversion>(pOutput) 
                    : iConversionType == e_static_cast                                                                
                    ? (numeric_conversion*)new tnumeric_conversion<std::nullptr_t, void*, e_static_cast>(pOutput)  
                    : iConversionType == e_explicit_cast                                                              
                    ? (numeric_conversion*)new tnumeric_conversion<std::nullptr_t, void*, e_explicit_cast>(pOutput) 
                    : iConversionType == e_reinterpret_cast                                                           
                    ? (numeric_conversion*)new tnumeric_conversion<std::nullptr_t, void*, e_reinterpret_cast>(pOutput) 
                    : nullptr;
                o_assert(nconv);
                conv = new default_conversion_sequence(nconv);
                return;
            }
            else if(pOutput == typeOf<bool>())
            {
                numeric_conversion* nconv = iConversionType == e_implicit_conversion                                                                               \
                    ? (numeric_conversion*)new tnumeric_conversion<std::nullptr_t, bool, e_implicit_conversion>(pOutput) 
                    : iConversionType == e_static_cast                                                                
                    ? (numeric_conversion*)new tnumeric_conversion<std::nullptr_t, bool, e_static_cast>(pOutput) 
                    : iConversionType == e_explicit_cast                                                              
                    ? (numeric_conversion*)new tnumeric_conversion<std::nullptr_t, bool, e_explicit_cast>(pOutput) 
                    : iConversionType == e_reinterpret_cast                                                           
                    ? (numeric_conversion*)new tnumeric_conversion<std::nullptr_t, bool, e_reinterpret_cast>(pOutput) 
                    : nullptr;
                o_assert(nconv);
                conv = new default_conversion_sequence(nconv);
                return;
            }
        }
    }
    visit((PrimitiveType*)(a_pInput), a_Data);
}

template<typename t_Ty>
conversion* CPlusPlus::baseIntegralConversion(native::TIntegralType<t_Ty>* a_pInput, Type* pOutput, int iConversionType, bool& a_bConstRef)
{
    conversion* conv = baseStandardConversion(a_pInput, pOutput, iConversionType, a_bConstRef);
    if(conv) return conv;

    switch(iConversionType)
    {
    case e_explicit_cast:
        {
            if(pOutput->removeQualifiers()->asPointerType() OR pOutput->removeQualifiers()->asEnum())
                return integralConversion<t_Ty, e_explicit_cast>(a_pInput, pOutput->removeQualifiers(), false, a_bConstRef);
        }
        break;
    case e_reinterpret_cast:
        {
            if(pOutput->removeQualifiers()->asPointerType() OR pOutput->removeQualifiers()->asEnum())
                return integralConversion<t_Ty, e_reinterpret_cast>(a_pInput, pOutput->removeQualifiers(), false, a_bConstRef);
        }
        break;
    }
    return nullptr;
}

#define o_integralConversion(a_pInput, pOutput, bPromotion, bConstRef)\
    iConversionType == e_implicit_conversion                                                                                  \
        ? integralConversion<t_Ty, e_implicit_conversion>(a_pInput, pOutput, bPromotion, bConstRef)          \
        : iConversionType == e_static_cast                                                                                    \
            ? integralConversion<t_Ty, e_static_cast>(a_pInput, pOutput, bPromotion, bConstRef)              \
            : iConversionType == e_explicit_cast                                                                              \
                ? integralConversion<t_Ty, e_explicit_cast>(a_pInput, pOutput, bPromotion, bConstRef)        \
                : iConversionType == e_reinterpret_cast                                                                       \
                    ? integralConversion<t_Ty, e_reinterpret_cast>(a_pInput, pOutput, bPromotion, bConstRef) \
                    : nullptr

#define o_floatingPointConversion(a_pInput, pOutput, bPromotion, bConstRef)\
    iConversionType == e_implicit_conversion                                                                               \
        ? floatingPointConversion<t_Ty, e_implicit_conversion>(a_pInput, pOutput, bPromotion, bConstRef)  \
            : iConversionType == e_static_cast                                                                             \
            ? floatingPointConversion<t_Ty, e_static_cast>(a_pInput, pOutput, bPromotion, bConstRef)      \
            : iConversionType == e_explicit_cast                                                                           \
            ? floatingPointConversion<t_Ty, e_explicit_cast>(a_pInput, pOutput, bPromotion, bConstRef)    \
            : iConversionType == e_reinterpret_cast                                                                        \
            ? floatingPointConversion<t_Ty, e_reinterpret_cast>(a_pInput, pOutput, bPromotion, bConstRef) \
            : nullptr

template<typename t_Ty>
void CPlusPlus::visitIntegral( native::TIntegralType<t_Ty>* a_pInput, visitor_data a_Data )
{
    switch(a_Data.id)
    {
    case e_Function_Conversion:
        {
            Type* pOutput = *(Type* const *)a_Data.in[0];
            int iConversionType = *(int const*)a_Data.in[1];
            int iUserDefinedConversionsAllowed = *(int const*)a_Data.in[2];
            LanguageElement* pContextScope = *(LanguageElement* const*)a_Data.in[3];
            conversion*& conv = *(conversion**)a_Data.out[0];
            bool bConstRef;
            conv = baseIntegralConversion(a_pInput, pOutput, iConversionType, bConstRef); 
            if(!conv)
            {
                ETypeId typeId = pOutput->getTypeId();
                if(typeId >= e_bool AND typeId <= e_longdouble) // integral and floating
                {
                    if(pOutput->removeQualifiers() == a_pInput->promote())
                        conv = o_integralConversion(a_pInput, pOutput, true, bConstRef); 
                    else 
                        conv = o_integralConversion(a_pInput, pOutput, false, bConstRef);
                }
                else if(iConversionType >= e_reinterpret_cast AND typeId == e_pointer OR typeId == e_enum)
                {
                    conv = o_integralConversion(a_pInput, pOutput, false, bConstRef);
                }
            }
            if(conv) 
                return;
        }
    }
    visit(static_cast<native::TArithmeticType<t_Ty>*>(a_pInput), a_Data);
}

void CPlusPlus::visit( native::TIntegralType<bool>* a_pInput, visitor_data a_Data )
{
    visitIntegral(a_pInput, a_Data);
}

void CPlusPlus::visit( native::TIntegralType<char>* a_pInput, visitor_data a_Data )
{
    visitIntegral(a_pInput, a_Data);
}

void CPlusPlus::visit( native::TIntegralType<uchar>* a_pInput, visitor_data a_Data )
{
    visitIntegral(a_pInput, a_Data);
}

void CPlusPlus::visit( native::TIntegralType<schar>* a_pInput, visitor_data a_Data )
{
    visitIntegral(a_pInput, a_Data);
}

#if o_HAS_BUILT_IN_WCHAR_T
void CPlusPlus::visit( native::TIntegralType<wchar_t>* a_pInput, visitor_data a_Data )
{
    visitIntegral(a_pInput, a_Data);
}
#endif

#if o_HAS_BUILT_IN_CHAR16_T
void CPlusPlus::visit( native::TIntegralType<char16_t>* a_pInput, visitor_data a_Data )
{
    visitIntegral(a_pInput, a_Data);
}
#endif

#if o_HAS_BUILT_IN_CHAR32_T
void CPlusPlus::visit( native::TIntegralType<char32_t>* a_pInput, visitor_data a_Data )
{
    visitIntegral(a_pInput, a_Data);
}

#endif

void CPlusPlus::visit( native::TIntegralType<short>* a_pInput, visitor_data a_Data )
{
    visitIntegral(a_pInput, a_Data);
}

void CPlusPlus::visit( native::TIntegralType<ushort>* a_pInput, visitor_data a_Data )
{
    visitIntegral(a_pInput, a_Data);
}

void CPlusPlus::visit( native::TIntegralType<int>* a_pInput, visitor_data a_Data )
{
    visitIntegral(a_pInput, a_Data);
}

void CPlusPlus::visit( native::TIntegralType<uint>* a_pInput, visitor_data a_Data )
{
    visitIntegral(a_pInput, a_Data);
}

void CPlusPlus::visit( native::TIntegralType<long>* a_pInput, visitor_data a_Data )
{
    visitIntegral(a_pInput, a_Data);
}

void CPlusPlus::visit( native::TIntegralType<ulong>* a_pInput, visitor_data a_Data )
{
    visitIntegral(a_pInput, a_Data);
}

void CPlusPlus::visit( native::TIntegralType<longlong>* a_pInput, visitor_data a_Data )
{
    visitIntegral(a_pInput, a_Data);
}

void CPlusPlus::visit( native::TIntegralType<ulonglong>* a_pInput, visitor_data a_Data )
{
    visitIntegral(a_pInput, a_Data);
}

template<typename t_Ty>
void CPlusPlus::visitFloatingPoint( native::TFloatingPointType<t_Ty>* a_pInput, visitor_data a_Data )
{
    switch(a_Data.id)
    {
    case e_Function_Conversion:
        {
            Type* pOutput = *(Type* const *)a_Data.in[0];
            int iConversionType = *(int const*)a_Data.in[1];
            conversion*& conv = *(conversion**)a_Data.out[0];
            bool bConstRef;
            conv = baseStandardConversion(a_pInput, pOutput, iConversionType, bConstRef);
            if(!conv)
            {
                ETypeId typeId = pOutput->getTypeId();
                if(typeId >= e_bool AND typeId <= e_longdouble) // integral and floating
                {
                    if(pOutput->removeQualifiers() == a_pInput->promote())
                        conv = o_floatingPointConversion(a_pInput, pOutput, true, bConstRef); 
                    else 
                        conv = o_floatingPointConversion(a_pInput, pOutput, false, bConstRef);
                }
                else if(iConversionType >= e_reinterpret_cast AND typeId == e_enum)
                {
                    conv = o_floatingPointConversion(a_pInput, pOutput, false, bConstRef);
                }
            }
            if(conv) 
                return;
        }
    }
    visit(static_cast<native::TArithmeticType<t_Ty>*>(a_pInput), a_Data);
}

void CPlusPlus::visit( native::TFloatingPointType<float>* a_pInput, visitor_data a_Data )
{
    visitFloatingPoint(a_pInput, a_Data);
}

void CPlusPlus::visit( native::TFloatingPointType<double>* a_pInput, visitor_data a_Data )
{
    visitFloatingPoint(a_pInput, a_Data);
}

void CPlusPlus::visit( native::TFloatingPointType<longdouble>* a_pInput, visitor_data a_Data )
{
    visitFloatingPoint(a_pInput, a_Data);
}

void CPlusPlus::visit(CompositionGetSetExpression*         a_pInput, visitor_data a_Data) { visit(static_cast<Expression*>(a_pInput), a_Data); }
void CPlusPlus::visit(AggregationGetSetExpression*         a_pInput, visitor_data a_Data) { visit(static_cast<Expression*>(a_pInput), a_Data); }
void CPlusPlus::visit(CompositionInsertRemoveExpression*   a_pInput, visitor_data a_Data) { visit(static_cast<Expression*>(a_pInput), a_Data); }
void CPlusPlus::visit(AggregationInsertRemoveExpression*   a_pInput, visitor_data a_Data) { visit(static_cast<Expression*>(a_pInput), a_Data); }


Expression* CPlusPlus::solveBinaryOperator( const string& a_strOp, Expression* a_pLeft, Expression* a_pRight, LanguageElement* a_pScope )
{
    Type* pLeftNakedType = a_pLeft->getValueType()->removeQualifiers()->removeReference()->removeConst();
    Type* pRightNakedType = a_pRight->getValueType()->removeQualifiers()->removeReference()->removeConst();

    bool bLeftIsClassOrEnumeration = pLeftNakedType->asClassType() OR pLeftNakedType->asEnum();
    bool bRightIsClassOrEnumeration = pRightNakedType->asClassType() OR pRightNakedType->asEnum();

    LanguageElement* pResolved = nullptr;
    modifiers_t access = 0;
    void* binaryOperatorDataOut[1] = { &pResolved };

    if(bLeftIsClassOrEnumeration OR bRightIsClassOrEnumeration)
    {
        /// standard 13.3.1.1.2.2
        /// If either operand has a type that is a class or an enumeration, a user-defined operator function might be
        /// declared that implements this operator or a user-defined conversion can be necessary to convert the operand
        /// to a type that is appropriate for a built-in operator. In this case, overload resolution is used to determine
        /// which operator function or built-in operator is to be invoked to implement the operator. Therefore, the
        /// operator notation is first transformed to the equivalent function-call notation as summarized in Table 10
        /// (where @ denotes one of the operators covered in the specified subclause).

        /// first solving try with left.operator@(right) call
        visitor_data userDefinedbinaryOperatorData;
        string operatorFunctionName = "operator"+a_strOp;
        vector<Expression*> operatorArguments;
        operatorArguments.push_back(a_pRight);
        userDefinedbinaryOperatorData.id = e_Function_QualifiedLookup;
        Type* pInitializationType = nullptr;
        const void* userDefinedbinaryOperatorDataIn[5] = { &operatorFunctionName, nullptr, &operatorArguments, &a_pScope, &pInitializationType };
        userDefinedbinaryOperatorData.in = userDefinedbinaryOperatorDataIn;
        userDefinedbinaryOperatorData.out = binaryOperatorDataOut;
        a_pLeft->visit(this, userDefinedbinaryOperatorData);
        if(pResolved)
        {
            return pResolved->asExpression();
        }

        /// second solving try with ::operator@(left, right) call
        operatorArguments.front() = a_pLeft;
        operatorArguments.push_back(a_pRight);
        LanguageElement* pScope = a_pScope->getSource();
        if(pScope OR (pScope = a_pScope->getEnclosingNamespace()))
        {
            pScope->visit(this, userDefinedbinaryOperatorData);
        }
        if(pResolved)
        {
            return pResolved->asExpression();
        }
    }
    /// standard 13.3.1.1.2.1
    /// If no operand of an operator in an expression has a type that is a class or an enumeration, the operator
    /// is assumed to be a built-in operator and interpreted according to Clause 5. [ Note: Because ., .*, and ::
    /// cannot be overloaded, these operators are always built-in operators interpreted according to Clause 5. ?:
    /// cannot be overloaded, but the rules in this subclause are used to determine the conversions to be applied to
    /// the second and third operands when they have class or enumeration type (5.16).

    /// Built in operator
    visitor_data binaryOperatorData;
    vector<Expression*> operatorArguments;
    operatorArguments.push_back(a_pLeft);
    operatorArguments.push_back(a_pRight);
    binaryOperatorData.id = e_Function_BinaryOperator;
    const void* binaryOperatorDataIn[2] = { &a_strOp, operatorArguments.data() };
    binaryOperatorData.in = binaryOperatorDataIn;
    binaryOperatorData.out = binaryOperatorDataOut;
    application()->visit(this, binaryOperatorData);
    return pResolved 
                ? pResolved->asExpression()
                : o_new(TDBinaryOperationExpression)(Type::Invalid(), a_strOp, a_pLeft, a_pRight);
}
Expression* CPlusPlus::solveUnaryPreOperator( const string& a_strOp, Expression* a_pExpression, LanguageElement* a_pScope )
{
    Type* pNakedType = a_pExpression->getValueType()->removeQualifiers();

    bool bIsClassOrEnumeration = pNakedType->asClassType() OR pNakedType->asEnum();

    LanguageElement* pResolved = nullptr;
    void* binaryOperatorDataOut[1] = { &pResolved };

    if(bIsClassOrEnumeration)
    {
        /// standard 13.3.1.1.2.2
        /// If either operand has a type that is a class or an enumeration, a user-defined operator function might be
        /// declared that implements this operator or a user-defined conversion can be necessary to convert the operand
        /// to a type that is appropriate for a built-in operator. In this case, overload resolution is used to determine
        /// which operator function or built-in operator is to be invoked to implement the operator. Therefore, the
        /// operator notation is first transformed to the equivalent function-call notation as summarized in Table 10
        /// (where @ denotes one of the operators covered in the specified subclause).

        /// first solving try with expr.operator@() call
        visitor_data userDefinedbinaryOperatorData;
        string operatorFunctionName = "operator"+a_strOp;
        vector<Expression*> operatorArguments;
        userDefinedbinaryOperatorData.id = e_Function_QualifiedLookup;
        Type* pInitializationType = nullptr; // TODO : add as parameter
        const void* userDefinedbinaryOperatorDataIn[5] = { &operatorFunctionName, nullptr, &operatorArguments, &a_pScope, &pInitializationType };
        userDefinedbinaryOperatorData.in = userDefinedbinaryOperatorDataIn;
        userDefinedbinaryOperatorData.out = binaryOperatorDataOut;
        a_pExpression->visit(this, userDefinedbinaryOperatorData);
        if(pResolved)
        {
            return pResolved->asExpression();
        }

        /// second solving try with ::operator@(expr) call
        operatorArguments.push_back(a_pExpression);
        LanguageElement* pScope = a_pScope->getSource();
        if(pScope OR (pScope = a_pScope->getEnclosingNamespace()))
        {
            pScope->visit(this, userDefinedbinaryOperatorData);
        }
        if(pResolved)
        {
            return pResolved->asExpression();
        }
    }
    /// standard 13.3.1.1.2.1
    /// If no operand of an operator in an expression has a type that is a class or an enumeration, the operator
    /// is assumed to be a built-in operator and interpreted according to Clause 5. [ Note: Because ., .*, and ::
    /// cannot be overloaded, these operators are always built-in operators interpreted according to Clause 5. ?:
    /// cannot be overloaded, but the rules in this subclause are used to determine the conversions to be applied to
    /// the second and third operands when they have class or enumeration type (5.16).

    /// Built in operator
    visitor_data binaryOperatorData;
    vector<Expression*> operatorArguments;
    operatorArguments.push_back(a_pExpression);
    binaryOperatorData.id = e_Function_UnaryPreOperator;
    const void* binaryOperatorDataIn[2] = { &a_strOp, operatorArguments.data() };
    binaryOperatorData.in = binaryOperatorDataIn;
    binaryOperatorData.out = binaryOperatorDataOut;
    application()->visit(this, binaryOperatorData);
    return pResolved 
        ? pResolved->asExpression()
        : o_new(TDUnaryPreOperationExpression)(Type::Invalid(), a_strOp, a_pExpression);
}
Expression* CPlusPlus::solveUnaryPostOperator( const string& a_strOp, Expression* a_pExpression, LanguageElement* a_pScope )
{
    ConstantExpression* pZeroInt = o_new(ConstantExpression)(constant<int>(0));

    Type* pNakedType = a_pExpression->getValueType()->removeQualifiers();

    bool bIsClassOrEnumeration = pNakedType->asClassType() OR pNakedType->asEnum();

    LanguageElement* pResolved = nullptr;
    void* binaryOperatorDataOut[1] = { &pResolved };

    if(bIsClassOrEnumeration)
    {
        /// standard 13.3.1.1.2.2
        /// If either operand has a type that is a class or an enumeration, a user-defined operator function might be
        /// declared that implements this operator or a user-defined conversion can be necessary to convert the operand
        /// to a type that is appropriate for a built-in operator. In this case, overload resolution is used to determine
        /// which operator function or built-in operator is to be invoked to implement the operator. Therefore, the
        /// operator notation is first transformed to the equivalent function-call notation as summarized in Table 10
        /// (where @ denotes one of the operators covered in the specified subclause).

        /// first solving try with expr.operator@(0) call
        visitor_data userDefinedbinaryOperatorData;
        string operatorFunctionName = "operator"+a_strOp;
        vector<Expression*> operatorArguments;
        ConstantExpression* pZeroInt = o_new(ConstantExpression)(constant<int>(0));
        operatorArguments.push_back(pZeroInt);
        userDefinedbinaryOperatorData.id = e_Function_QualifiedLookup;
        Type* pInitializationType = nullptr; // TODO : add as parameter
        const void* userDefinedbinaryOperatorDataIn[5] = { &operatorFunctionName, nullptr, &operatorArguments, &a_pScope, &pInitializationType };
        userDefinedbinaryOperatorData.in = userDefinedbinaryOperatorDataIn;
        userDefinedbinaryOperatorData.out = binaryOperatorDataOut;
        a_pExpression->visit(this, userDefinedbinaryOperatorData);
        if(pResolved)
        {
            return pResolved->asExpression();
        }

        /// second solving try with ::operator@(expr, 0) call
        operatorArguments.front() = a_pExpression;
        operatorArguments.push_back(pZeroInt);
        LanguageElement* pScope = a_pScope->getSource();
        if(pScope OR (pScope = a_pScope->getEnclosingNamespace()))
        {
            pScope->visit(this, userDefinedbinaryOperatorData);
        }
        if(pResolved)
        {
            return pResolved->asExpression();
        }
    }
    /// standard 13.3.1.1.2.1
    /// If no operand of an operator in an expression has a type that is a class or an enumeration, the operator
    /// is assumed to be a built-in operator and interpreted according to Clause 5. [ Note: Because ., .*, and ::
    /// cannot be overloaded, these operators are always built-in operators interpreted according to Clause 5. ?:
    /// cannot be overloaded, but the rules in this subclause are used to determine the conversions to be applied to
    /// the second and third operands when they have class or enumeration type (5.16).

    /// Built in operator
    visitor_data binaryOperatorData;
    vector<Expression*> operatorArguments;
    operatorArguments.push_back(a_pExpression);
    operatorArguments.push_back(pZeroInt);
    binaryOperatorData.id = e_Function_UnaryPostOperator;
    const void* binaryOperatorDataIn[2] = { &a_strOp, operatorArguments.data() };  
    binaryOperatorData.in = binaryOperatorDataIn;
    binaryOperatorData.out = binaryOperatorDataOut;
    application()->visit(this, binaryOperatorData);
    if(pResolved == nullptr)
    {
        o_delete(ConstantExpression) pZeroInt;
        return o_new(TDUnaryPostOperationExpression)(Type::Invalid(), a_strOp, a_pExpression);
    }
    return pResolved->asExpression();
}

LanguageElement* CPlusPlus::resolveTemplateDependency( LanguageElement* a_pElement, TemplateSignature* a_pTemplateSignature, const map<Placeholder*, LanguageElement*>& a_Arguments, LanguageElement* a_pScope, int a_Flags /*= 0*/ )
{
    LanguageElement* pResult = nullptr;
    visitor_data data;
    data.id = e_Function_ResolveTemplateDependencies;
    const void* in[3] = {&a_pTemplateSignature, &a_Arguments, &a_pScope };
    void* out[1] = {&pResult};
    data.in = in;
    data.out = out;
    data.flags = a_Flags;
    a_pElement->visit(this, data);
    return pResult;
}

LanguageElement* CPlusPlus::instanciateTemplate( LanguageElement* a_pElement, TemplateSignature* a_pTemplateSignature, const map<Placeholder*, LanguageElement*>& a_Arguments, LanguageElement* a_pScope, int a_Flags /*= 0*/ )
{
    LanguageElement* pResult = nullptr;
    visitor_data data;
    data.id = e_Function_InstanciateTemplate;
    const void* in[3] = {&a_pTemplateSignature, &a_Arguments, &a_pScope };
    void* out[1] = {&pResult};
    data.in = in;
    data.out = out;
    data.flags = a_Flags;
    a_pElement->visit(this, data);
    return pResult;
}

conversion* CPlusPlus::userDefinedConversion( Type* a_pInput, Type* a_pOutput, bool a_bExplicit, LanguageElement* a_pContextScope /*= nullptr*/, bool a_bConstRef )
{
    conversions possibleConversions;
    ClassType* pInputClassType = a_pInput->removeQualifiers()->asClassType();
    ClassType* pOutputClassType = a_pOutput->removeQualifiers()->asClassType();
    if(pOutputClassType)
    {
        conversion* byConstruction = userDefinedConversionByConstruction(a_pInput, pOutputClassType, a_bExplicit, a_pContextScope, a_bConstRef);
        if(byConstruction)
            possibleConversions.push_back(byConstruction);
    }
    if(pInputClassType)
    {
        conversion* byConversionFunction = userDefinedConversionByConversionFunction(pInputClassType, a_pOutput, a_bExplicit, a_pContextScope, a_bConstRef);
        if(byConversionFunction)
            possibleConversions.push_back(byConversionFunction);
    }
    size_t index = 0;
    default_conversion_sequence* pBest = static_cast<default_conversion_sequence*>(possibleConversions.takeBest(&index));
    if(pBest)
    {
        if(a_bConstRef)
            pBest->addConstRef();
        return pBest;
    }
    return nullptr;
}

conversion* CPlusPlus::userDefinedConversionByConstruction( Type* a_pInput, ClassType* a_pOutput, bool a_bExplicits, LanguageElement* a_pContextScope, bool a_bConstRef )
{
    vector<Constructor*> constructors;
    conversions convs;
    if(a_bExplicits)
    {
        for(auto it = a_pOutput->beginConstructors(); it != a_pOutput->endConstructors(); ++it)
        {
            Constructor* pCtor = *it;
            if(pCtor->getParameterCount() == 1)
            {
                conversion* conv = typeConversion(a_pInput, pCtor->getParameterType(0), e_implicit_conversion, a_pContextScope, e_no_user_defined_functions);
                if(conv)
                {
                    constructors.push_back(pCtor);
                    convs.push_back(conv);
                }
            }
        }
    }
    else /// implicits
    {
        for(auto it = a_pOutput->beginConstructors(); it != a_pOutput->endConstructors(); ++it)
        {
            Constructor* pCtor = *it;
            if(pCtor->getParameterCount() == 1 AND NOT(pCtor->testModifiers(o_explicit)))
            {
                conversion* conv = typeConversion(a_pInput, pCtor->getParameterType(0), e_implicit_conversion, a_pContextScope, e_no_user_defined_functions);
                if(conv)
                {
                    constructors.push_back(pCtor);
                    convs.push_back(conv);
                }
            }
        }
    }
    size_t index = 0;
    default_conversion_sequence* pBest = static_cast<default_conversion_sequence*>(convs.takeBest(&index));
    if(pBest)
    {
        pBest->addUserDefinedByConstruction(constructors[index]);
        if(a_bConstRef)
            pBest->addConstRef();
        return pBest;
    }
    return nullptr;
}

conversion* CPlusPlus::userDefinedConversionByConversionFunction( ClassType* a_pInput, Type* a_pOutput, bool a_bExplicit, LanguageElement* a_pContextScope, bool bConstRef )
{
    vector<MemberFunction*> conversionFunctions;
    conversions convs;
    if(a_bExplicit)
    {
        for(auto it = a_pInput->beginMemberFunctions(); it != a_pInput->endMemberFunctions(); ++it)
        {
            MemberFunction* pMemberFunction = *it;
            const string& name = pMemberFunction->getName();
            if(name.size() >= 8 AND name[8] == ' ') // TODO : find a faster way to distinguish conversion functions
            {
                conversion* conv = typeConversion(pMemberFunction->getReturnType(), a_pOutput, e_implicit_conversion, a_pContextScope, e_no_user_defined_functions);
                if(conv)
                {
                    conversionFunctions.push_back(pMemberFunction);
                    convs.push_back(conv);
                }
            }
        }
    }
    else /// implicits
    {
        for(auto it = a_pInput->beginMemberFunctions(); it != a_pInput->endMemberFunctions(); ++it)
        {
            MemberFunction* pMemberFunction = *it;
            const string& name = pMemberFunction->getName();
            if(NOT(pMemberFunction->testModifiers(o_explicit)) AND name.size() >= 8 AND name[8] == ' ') // TODO : find a faster way to distinguish conversion functions
            {
                conversion* conv = typeConversion(pMemberFunction->getReturnType(), a_pOutput, e_implicit_conversion, a_pContextScope, e_no_user_defined_functions);
                if(conv)
                {
                    conversionFunctions.push_back(pMemberFunction);
                    convs.push_back(conv);
                }
            }
        }
    }
    size_t index = 0;
    default_conversion_sequence* pBest = static_cast<default_conversion_sequence*>(convs.takeBest(&index));
    if(pBest)
    {
        pBest->addUserDefinedByConversionFunction(conversionFunctions[index]);
        /// the best found is in fact the best second standard conversion sequence of an user defined conversion sequence by conversion function
        /// so we switch first standard and second standard in current conversion sequence
        o_assert(pBest->m_user_defined->m_standard == nullptr);
        pBest->m_user_defined->m_standard = pBest->m_standard;
        pBest->m_standard = nullptr;
        return pBest;
    }
    return nullptr;
}

void CPlusPlus::selectCallCandidate( vector<LanguageElement*>& candidates, const vector<LanguageElement*>* in_pTemplateArguments, vector<Expression*>& arguments, LanguageElement* &out_pResult, const string& in_name, LanguageElement* in_pContextScope, Type* in_pInitializationType, modifiers_t a_Modifiers /*= 0*/ )
{
    vector<Callable*> viableCandidates;
    vector<conversions*> viableImplicitConversions;

    /// Filter viable calls
    for(auto it = candidates.begin(); it != candidates.end(); ++it)
    {
        conversions* convs = new conversions;
        visitor_data data;
        Subroutine* out_pSubroutine = nullptr;
        const void* in[4] = { in_pTemplateArguments, &arguments, &a_Modifiers, &in_pContextScope };
        void* out[2] = { convs, &out_pSubroutine };
        data.id = e_Function_IsViableCallCandidate;
        data.in = in;
        data.out = out;
        (*it)->visit(this, data);
        if(out_pSubroutine) /// viable
        {
            viableCandidates.push_back(out_pSubroutine);
            viableImplicitConversions.push_back(convs);
        }
        else 
        {
            delete convs;
        }
    }
    if(viableImplicitConversions.size())
    {
        /// Find best viable call or display ambiguity error
        conversions* pBest = nullptr; 
        Callable* pBestCandidate = nullptr; 
        if(viableImplicitConversions.size() == 1)
        {
            pBest = viableImplicitConversions.back();
            pBestCandidate = viableCandidates.back();
        }
        else 
        {
            size_t bestIndex = 0;
            for(size_t i = 0; i<viableImplicitConversions.size(); ++i)
            {
                int bestResult = -1;
                size_t j = 0;
                for(; j<viableImplicitConversions.size(); ++j)
                {
                    int result = viableImplicitConversions[i]->compare(*viableImplicitConversions[j]);
                    o_assert(viableImplicitConversions[j]->compare(*viableImplicitConversions[i]) == -result); /// compare() coherence test
                    if(result >= 0)
                        bestResult = std::max(bestResult, result);
                    else 
                        break;
                }
                if(j == viableImplicitConversions.size()) /// superior or equal to every one (not worst to any)
                {
                    if(bestResult == 1)
                    {
                        /// found a best match (superior to at least one other signature and equal to the others)
                        pBest = viableImplicitConversions[i];
                        pBestCandidate = viableCandidates[i];
                        goto end_of_selection;
                    }
                }
            }
        }
    end_of_selection:
        if(pBest)
        {
            o_assert(pBestCandidate);
            if(pBest->size() == arguments.size()-1)
            {
                o_assert((a_Modifiers&o_static) == 0);
                o_dynamic_delete arguments.front(); // destroy useless 'this' expression
                arguments.erase(arguments.begin()); // remove 'this' expression
            }
            for(size_t k = 0; k<pBest->size(); ++k)
            {
                arguments[k] = (*pBest)[k]->convert(arguments[k]); /// convert arguments 
            }
            out_pResult = pBestCandidate->createCallExpression(arguments);
        }
        else 
        {
            string argumentsText;
            generateArgumentsText(arguments, argumentsText);
            CallExpression* pInvalidCallExpression = o_new(CallExpression)(Subroutine::Invalid(), arguments);
            pInvalidCallExpression->error("ambiguous call to multiple '%s' overloads with arguments %s", in_name.c_str(), argumentsText.c_str());
            for(auto it = viableCandidates.begin(); it != viableCandidates.end(); ++it)
            {
                pInvalidCallExpression->subError("%s '%'", ((it == viableCandidates.begin()) ? _canBe : _or), (*it)->asLanguageElement()->asNamedElement()->getDecoratedName().c_str());
            }
        }
        for(auto it = viableImplicitConversions.begin(); it != viableImplicitConversions.end(); ++it)
        {
            delete *it;
        }
    }
    else 
    {
        string argumentsText;
        generateArgumentsText(arguments, argumentsText);
        CallExpression* pInvalidCallExpression = o_new(CallExpression)(Subroutine::Invalid(), arguments);
        pInvalidCallExpression->error("no '%s' overload found that match the given arguments %s", in_name.c_str(), argumentsText.c_str());
        for(auto it = candidates.begin(); it != candidates.end(); ++it)
        {
            pInvalidCallExpression->subError("%s '%s'", ((it == candidates.begin()) ? _canBe : _or), (*it)->asNamedElement()->getDecoratedName().c_str());
        }
    }
}

LanguageElement* CPlusPlus::qualifiedLookup( LanguageElement* a_pElement
    , const string& a_strName
    , const vector<LanguageElement*>* a_pTemplateArguments
    , const vector<Expression*>* a_pFunctionArguments
    , LanguageElement* a_pScope
    , Type* a_pInitializationType)
{
    LanguageElement* pResult = nullptr;
    visitor_data data;
    data.id = e_Function_QualifiedLookup;
    const void* in[5] = {&a_strName, a_pTemplateArguments, a_pFunctionArguments, &a_pScope, &a_pInitializationType};
    void* out[1] = {&pResult};
    data.in = in;
    data.out = out;
    a_pElement->visit(this, data);
    return pResult;
}

LanguageElement* CPlusPlus::unqualifiedLookup( const string& a_strName, const vector<LanguageElement*>* a_pTemplateArguments, const vector<Expression*>* a_pFunctionArguments, LanguageElement* a_pScope, Type* a_pInitializationType )
{
    LanguageElement* pResult = nullptr;
    visitor_data data;
    data.id = e_Function_UnqualifiedLookup;
    const void* in[5] = {&a_strName, a_pTemplateArguments, a_pFunctionArguments, &a_pInitializationType, &a_pScope};
    void* out[1] = {&pResult};
    data.in = in;
    data.out = out;
    data.flags = e_VisitorFlag_NamespaceMode;
    a_pScope->visit(this, data);
    return pResult;
}

Subroutine* CPlusPlus::solveSubroutine( LanguageElement* a_pElement
    , const string& a_strName
    , const vector<LanguageElement*>* a_pTemplateArguments
    , const vector<Type*>& a_ParameterTypes
    , modifiers_t a_Qualifiers
    , LanguageElement* a_pScope
    )
{
    Subroutine* pResult = nullptr;
    visitor_data data;
    modifiers_t access = 0;
    data.id = e_Function_SubroutineResolution;
    const void* in[5] = {&a_strName, a_pTemplateArguments, &a_ParameterTypes, &a_Qualifiers, &a_pScope};
    void* out[2] = {&pResult, &access};
    data.in = in;
    data.out = out;
    a_pElement->visit(this, data);
    return pResult ? pResult : Subroutine::Invalid();
}

Subroutine* CPlusPlus::solveSubroutineCascade( LanguageElement* a_pElement, const string& a_strName, const vector<LanguageElement*>* a_pTemplateArguments, const vector<Type*>& a_ParameterTypes, modifiers_t a_Qualifiers, LanguageElement* a_pScope )
{
    Subroutine* pSubroutine = solveSubroutine(a_pElement, a_strName, a_pTemplateArguments, a_ParameterTypes, a_Qualifiers, a_pScope);
    if(pSubroutine AND !pSubroutine->isInvalid()) 
        return pSubroutine;
    NamedElement* pNamedElement = a_pElement->asNamedElement();
    if(pNamedElement AND pNamedElement->getNamespace())
    {
        return solveSubroutineCascade(pNamedElement->getNamespace(), a_strName, a_pTemplateArguments, a_ParameterTypes, a_Qualifiers, a_pScope) ;
    }
    if(a_pElement->getOwner())
    {
        return solveSubroutineCascade(a_pElement->getOwner(), a_strName, a_pTemplateArguments, a_ParameterTypes, a_Qualifiers, a_pScope) ;
    }
    return Subroutine::Invalid();
}

Expression* CPlusPlus::convert( Expression* a_pInputExpression, Type* a_pOutputType, int a_iConversionType, LanguageElement* a_pContextScope, bool a_bEmitError /*= true*/ )
{
    if(a_pOutputType->removeQualifiers()->equals(a_pInputExpression->getValueType()->removeQualifiers()) && a_iConversionType == e_implicit_conversion)
        return a_pInputExpression;
    conversion* conv = typeConversion(a_pInputExpression->getValueType(), a_pOutputType, a_iConversionType, a_pContextScope, (a_iConversionType == e_implicit_conversion) ? e_implicit_functions : e_explicit_functions);
    if(conv == nullptr) 
    {
        Expression* pResult = nullptr;
        LanguageElement* pErrorHolder = nullptr;
        if(a_iConversionType == e_implicit_conversion)
        {
            pResult = Expression::Invalid();
            pErrorHolder = a_pInputExpression;
        }
        else 
        {
            pResult = o_new(BuiltInConversionExpression)(a_pInputExpression, nullptr, a_iConversionType);
            pErrorHolder = pResult;
        }
        if(a_bEmitError)
        {
            pErrorHolder->error("cannot convert from '%s' to '%s'", a_pInputExpression->getValueType()->getQualifiedDecoratedName().c_str(), a_pOutputType->getQualifiedDecoratedName().c_str());
        }
        return pResult;
    }
    Expression* pConversion = conv->convert(a_pInputExpression);
    o_assert(pConversion);
    delete conv;
    return pConversion;
}

Type* CPlusPlus::templateArgumentDeduction(LanguageElement* a_pParameter, Type* a_pArgument, map<Placeholder*, LanguageElement*>& deductions)
{
    LanguageElement* pElement = templateArgumentDeduction(a_pParameter, (LanguageElement*)a_pArgument, deductions);
    return pElement ? pElement->asType() : nullptr;
}

LanguageElement* CPlusPlus::templateArgumentDeduction(LanguageElement* a_pParameter, LanguageElement* a_pArgument, map<Placeholder*, LanguageElement*>& deductions)
{
    LanguageElement* pResult = nullptr;
    visitor_data data;
    data.id = e_Function_TemplateArgumentDeduction;
    const void* in[1] = {&a_pArgument};
    void* out[2] = {&pResult, &deductions};
    data.in = in;
    data.out = out;
    a_pParameter->visit(this, data);
    return pResult;
}

int CPlusPlus::compareSpecialized( TemplateSpecialization* a_pT0, TemplateSpecialization* a_pT1 )
{
    TemplateDependantTemplateInstance* fictiousT0 = o_new(TemplateDependantTemplateInstance)(a_pT0->getTemplate(), a_pT0->getArguments());
    TemplateDependantTemplateInstance* fictiousT1 = o_new(TemplateDependantTemplateInstance)(a_pT1->getTemplate(), a_pT1->getArguments());

    bool result0 = true;
    bool result1 = true;
    map<Placeholder*, LanguageElement*> deductions0;
    map<Placeholder*, LanguageElement*> deductions1;
    result0 = templateArgumentDeduction(fictiousT1, fictiousT0, deductions1) != nullptr;
    result1 = templateArgumentDeduction(fictiousT0, fictiousT1, deductions0) != nullptr;

    return (result0>result1) - (result0<result1);
}

int CPlusPlus::partialOrdering( const vector<LanguageElement*>& P0, const vector<LanguageElement*>& A0, const vector<LanguageElement*>& P1, const vector<LanguageElement*>& A1 )
{
    bool result0 = true;
    bool result1 = true;
    o_assert(P0.size() == A0.size() AND A0.size() == P1.size() AND P1.size() == A1.size());
    for(size_t i = 0; i<P0.size(); ++i)
    {
        map<Placeholder*, LanguageElement*> deductions;
        if(NOT(templateArgumentDeduction(P0[i], A1[i], deductions)))
        {
            result0 = false;
            break;
        }
    }
    for(size_t i = 0; i<P1.size(); ++i)
    {
        map<Placeholder*, LanguageElement*> deductions;
        if(NOT(templateArgumentDeduction(P1[i], A0[i], deductions)))
        {
            result1 = false;
            break;
        }
    }
    return (result0>result1) - (result0<result1);
}

void CPlusPlus::generateArgumentsText( const vector<Expression*> &arguments, string& argumentsText )
{
    argumentsText = "(";
    for(auto it = arguments.begin(); it != arguments.end(); ++it)
    {
        if(it != arguments.begin())
            argumentsText += ", ";
        argumentsText += (*it)->getValueType()->getQualifiedDecoratedName();
    }
    argumentsText+= ')';
}

o_namespace_end(phantom, reflection)
