/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Precompiler.h"
#include "Precompiler.hxx"
#include "native/TFundamentals.h"
#include "Application.h"
#include "Source.h"
#include "Import.h"
#include "Package.h"
#include "Placeholder.h"
#include "BuiltInOperator.h"
#include "ConstructorCallExpression.h"
#include "LocalVariableExpression.h"
#include "VariableExpression.h"
#include "PointerAdjustmentExpression.h"
#include "BuiltInOperatorExpression.h"
#include "DataMemberPointerAdjustmentExpression.h"
#include "MemberFunctionPointerAdjustmentExpression.h"
#include "RValueExpression.h"
#include "LoadExpression.h"
#include "PropertyExpression.h"
#include "Expression.h"
#include "ConstantExpression.h"
#include "Block.h"
#include "LocalVariable.h"
#include "DataExpression.h"
#include "StringLiteralExpression.h"
#include "ConditionalExpression.h"
#include "PlacementConstructionExpression.h"
#include "DataMemberExpression.h"
#include "CallExpression.h"
#include "BuiltInConversionExpression.h"
#include "MemberFunctionPointerCallExpression.h"
#include "DataMemberPointerExpression.h"
#include "MemberFunctionPointerType.h"
#include "DataMemberPointerType.h"
#include "Enum.h"
#include "NumericConstant.h"
#include "LabelStatement.h"
#include "BranchIfStatement.h"
#include "BranchIfNotStatement.h"
#include "BranchStatement.h"
#include "Constant.h"
#include "Statement.h"
#include "ExpressionStatement.h"
#include "ReturnStatement.h"
#include "TDBinaryOperationExpression.h"
#include "TDUnaryPreOperationExpression.h"
#include "TDunaryPostOperationExpression.h"
#include "Parameter.h"
#include "AggregationClass.h"
#include "CompositionClass.h"
#include "CommaExpression.h"
#include "LocalVariableInitializationStatement.h"
/* *********************************************** */
o_registerN((phantom, reflection), Precompiler);


o_namespace_begin(phantom, reflection) 

void LanguageElementVisitor::visit( AggregationClass* a_pInput, visitor_data a_Data )
{
    visit(static_cast<Class*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( Alias* a_pInput, visitor_data a_Data )
{
    visit(static_cast<NamedElement*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( AnonymousSection* a_pInput, visitor_data a_Data )
{
    visit(static_cast<NamedElement*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( AnonymousStruct* a_pInput, visitor_data a_Data )
{
    visit(static_cast<AnonymousSection*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( AnonymousUnion* a_pInput, visitor_data a_Data )
{
    visit(static_cast<AnonymousSection*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( Application* a_pInput, visitor_data a_Data )
{
    visit(static_cast<NamedElement*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( ArrayType* a_pInput, visitor_data a_Data )
{
    visit(static_cast<Type*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( Block* a_pInput, visitor_data a_Data )
{
    visit(static_cast<Statement*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( BranchIfNotStatement* a_pInput, visitor_data a_Data )
{
    visit(static_cast<BranchStatement*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( BranchIfStatement* a_pInput, visitor_data a_Data )
{
    visit(static_cast<BranchStatement*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( BranchStatement* a_pInput, visitor_data a_Data )
{
    visit(static_cast<Statement*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( BuiltInConversionExpression* a_pInput, visitor_data a_Data )
{
    visit(static_cast<Expression*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( BuiltInOperator* a_pInput, visitor_data a_Data )
{
    visit(static_cast<NamedElement*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( BuiltInOperatorExpression* a_pInput, visitor_data a_Data )
{
    visit(static_cast<Expression*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( CallExpression* a_pInput, visitor_data a_Data )
{
    visit(static_cast<Expression*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( Class* a_pInput, visitor_data a_Data )
{
    visit(static_cast<ClassType*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( ClassType* a_pInput, visitor_data a_Data )
{
    visit(static_cast<Type*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( CompositionClass* a_pInput, visitor_data a_Data )
{
    visit(static_cast<Class*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( Constant* a_pInput, visitor_data a_Data )
{
    visit(static_cast<NamedElement*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( ConstantExpression* a_pInput, visitor_data a_Data )
{
    visit(static_cast<Expression*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( Constructor* a_pInput, visitor_data a_Data )
{
    visit(static_cast<MemberFunction*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( ConstructorCallExpression* a_pInput, visitor_data a_Data )
{
    visit(static_cast<CallExpression*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( ConstType* a_pInput, visitor_data a_Data )
{
    visit(static_cast<Type*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( ConstVolatileType* a_pInput, visitor_data a_Data )
{
    visit(static_cast<Type*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( ContainerClass* a_pInput, visitor_data a_Data )
{
    visit(static_cast<Class*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( DataExpression* a_pInput, visitor_data a_Data )
{
    visit(static_cast<Expression*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( DataMember* a_pInput, visitor_data a_Data )
{
    visit(static_cast<NamedElement*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( DataMemberExpression* a_pInput, visitor_data a_Data )
{
    visit(static_cast<LValueExpression*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( DataMemberPointerExpression* a_pInput, visitor_data a_Data )
{
    visit(static_cast<Expression*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( DataMemberPointerType* a_pInput, visitor_data a_Data )
{
    visit(static_cast<MemberPointerType*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( DataPointerType* a_pInput, visitor_data a_Data )
{
    visit(static_cast<PointerType*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( Ellipsis* a_pInput, visitor_data a_Data )
{
    /// visit(static_cast<LanguageElement*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( Enum* a_pInput, visitor_data a_Data )
{
    visit(static_cast<Type*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( Evaluable* a_pInput, visitor_data a_Data )
{
    visit(static_cast<LanguageElement*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit( Event* a_pInput, visitor_data a_Data )
{
    visit(static_cast<StateMachineElement*>(a_pInput), a_Data);
}

void LanguageElementVisitor::visit(Expression*                  a_pInput, visitor_data a_Data) { visit(static_cast<Evaluable*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(ExpressionStatement*         a_pInput, visitor_data a_Data) { visit(static_cast<Statement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Function*                    a_pInput, visitor_data a_Data) { visit(static_cast<Subroutine*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(FunctionPointerType*         a_pInput, visitor_data a_Data) { visit(static_cast<PointerType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Import*                      a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(LabelStatement*              a_pInput, visitor_data a_Data) { visit(static_cast<Statement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(LanguageElement*             a_pInput, visitor_data a_Data) {                                                      }
void LanguageElementVisitor::visit(LocalVariable*               a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(LocalVariableExpression*     a_pInput, visitor_data a_Data) { visit(static_cast<LValueExpression*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(LocalVariableInitializationStatement* a_pInput, visitor_data a_Data) { visit(static_cast<LValueInitializationStatement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(LValueExpression*            a_pInput, visitor_data a_Data) { visit(static_cast<Expression*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(LValueInitializationStatement* a_pInput, visitor_data a_Data) { visit(static_cast<Statement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(LValueReferenceType*         a_pInput, visitor_data a_Data) { visit(static_cast<ReferenceType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(MapContainerClass*           a_pInput, visitor_data a_Data) { visit(static_cast<Class*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Member*                      a_pInput, visitor_data a_Data) {                                                      }
void LanguageElementVisitor::visit(MemberAnonymousSection*      a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(MemberAnonymousStruct*       a_pInput, visitor_data a_Data) { visit(static_cast<MemberAnonymousSection*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(MemberAnonymousUnion*        a_pInput, visitor_data a_Data) { visit(static_cast<MemberAnonymousSection*>(a_pInput), a_Data); }

void LanguageElementVisitor::visit(MemberFunction*              a_pInput, visitor_data a_Data) { visit(static_cast<Subroutine*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(MemberFunctionPointerCallExpression* a_pInput, visitor_data a_Data) { visit(static_cast<Expression*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(MemberFunctionPointerType*   a_pInput, visitor_data a_Data) { visit(static_cast<MemberPointerType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(MemberPointerType*           a_pInput, visitor_data a_Data) { visit(static_cast<Type*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Module*                      a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(NamedElement*                a_pInput, visitor_data a_Data) { visit(static_cast<LanguageElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Namespace*                   a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(NamespaceAlias*              a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(NumericConstant*             a_pInput, visitor_data a_Data) { visit(static_cast<Constant*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Package*                     a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Parameter*                   a_pInput, visitor_data a_Data) { visit(static_cast<LocalVariable*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Placeholder*                 a_pInput, visitor_data a_Data) {                                                      }
void LanguageElementVisitor::visit(PlaceholderClass*            a_pInput, visitor_data a_Data) { visit(static_cast<Class*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(PlaceholderClassType*        a_pInput, visitor_data a_Data) { visit(static_cast<ClassType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(PlaceholderConstant*         a_pInput, visitor_data a_Data) { visit(static_cast<Constant*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(PlaceholderTemplate*         a_pInput, visitor_data a_Data) { visit(static_cast<Template*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(PlaceholderType*             a_pInput, visitor_data a_Data) { visit(static_cast<Type*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(PlacementConstructionExpression* a_pInput, visitor_data a_Data) { visit(static_cast<CallExpression*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(PointerType*                 a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(PrimitiveType*               a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Property*                    a_pInput, visitor_data a_Data) { visit(static_cast<ValueMember*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(PropertyExpression*          a_pInput, visitor_data a_Data) { visit(static_cast<LValueExpression*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Range*                       a_pInput, visitor_data a_Data) { visit(static_cast<LanguageElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(ReferenceType*               a_pInput, visitor_data a_Data) { visit(static_cast<Type*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(ReturnStatement*             a_pInput, visitor_data a_Data) { visit(static_cast<Statement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(RValueReferenceType*         a_pInput, visitor_data a_Data) { visit(static_cast<ReferenceType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Scope*                       a_pInput, visitor_data a_Data) {                                                      }
void LanguageElementVisitor::visit(SequentialContainerClass*    a_pInput, visitor_data a_Data) { visit(static_cast<Class*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(SetContainerClass*           a_pInput, visitor_data a_Data) { visit(static_cast<Class*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Signal*                      a_pInput, visitor_data a_Data) { visit(static_cast<MemberFunction*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Signature*                   a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Source*                      a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(State*                       a_pInput, visitor_data a_Data) { visit(static_cast<StateMachineElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(StateMachine*                a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(StateMachineElement*         a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Statement*                   a_pInput, visitor_data a_Data) { visit(static_cast<Evaluable*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(StringLiteralExpression*     a_pInput, visitor_data a_Data) { visit(static_cast<Expression*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Structure*                   a_pInput, visitor_data a_Data) { visit(static_cast<ClassType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Subroutine*                  a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(TDBinaryOperationExpression* a_pInput, visitor_data a_Data) { visit(static_cast<Expression*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(TDUnaryPostOperationExpression* a_pInput, visitor_data a_Data) { visit(static_cast<Expression*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(TDUnaryPreOperationExpression* a_pInput, visitor_data a_Data) { visit(static_cast<Expression*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Track*                       a_pInput, visitor_data a_Data) { visit(static_cast<StateMachineElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Template*                    a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(TemplateDependantArrayType*  a_pInput, visitor_data a_Data) { visit(static_cast<ArrayType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(TemplateDependantElement*    a_pInput, visitor_data a_Data ){ visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(TemplateDependantExpression* a_pInput, visitor_data a_Data ){ visit(static_cast<Expression*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(TemplateDependantTemplateInstance* a_pInput, visitor_data a_Data ) { visit(static_cast<ClassType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(TemplateDependantType*       a_pInput, visitor_data a_Data ) { visit(static_cast<Type*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(TemplateParameter*           a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(TemplateSignature*           a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(TemplateSpecialization*      a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Type*                        a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Union*                       a_pInput, visitor_data a_Data) { visit(static_cast<ClassType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(ValueMember*                 a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(Variable*                    a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(VariableExpression*          a_pInput, visitor_data a_Data) { visit(static_cast<LValueExpression*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(VirtualMemberFunctionTable*  a_pInput, visitor_data a_Data) { visit(static_cast<NamedElement*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(VolatileType*                a_pInput, visitor_data a_Data) { visit(static_cast<Type*>(a_pInput), a_Data); }

void LanguageElementVisitor::visit(native::TFundamentalType<void>* a_pInput, visitor_data a_Data) { visit(static_cast<PrimitiveType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(native::TFundamentalType<std::nullptr_t>* a_pInput, visitor_data a_Data) { visit(static_cast<PrimitiveType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(native::TIntegralType<bool>* a_pInput, visitor_data a_Data) { visit(static_cast<PrimitiveType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(native::TIntegralType<char>* a_pInput, visitor_data a_Data) { visit(static_cast<PrimitiveType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(native::TIntegralType<uchar>* a_pInput, visitor_data a_Data) { visit(static_cast<PrimitiveType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(native::TIntegralType<schar>* a_pInput, visitor_data a_Data) { visit(static_cast<PrimitiveType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(native::TIntegralType<short>* a_pInput, visitor_data a_Data) { visit(static_cast<PrimitiveType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(native::TIntegralType<ushort>* a_pInput, visitor_data a_Data) { visit(static_cast<PrimitiveType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(native::TIntegralType<int>* a_pInput, visitor_data a_Data) { visit(static_cast<PrimitiveType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(native::TIntegralType<uint>* a_pInput, visitor_data a_Data) { visit(static_cast<PrimitiveType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(native::TIntegralType<long>* a_pInput, visitor_data a_Data) { visit(static_cast<PrimitiveType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(native::TIntegralType<ulong>* a_pInput, visitor_data a_Data) { visit(static_cast<PrimitiveType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(native::TIntegralType<longlong>* a_pInput, visitor_data a_Data) { visit(static_cast<PrimitiveType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(native::TIntegralType<ulonglong>* a_pInput, visitor_data a_Data) { visit(static_cast<PrimitiveType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(native::TFloatingPointType<float>* a_pInput, visitor_data a_Data) { visit(static_cast<PrimitiveType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(native::TFloatingPointType<double>* a_pInput, visitor_data a_Data) { visit(static_cast<PrimitiveType*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(native::TFloatingPointType<longdouble>* a_pInput, visitor_data a_Data) { visit(static_cast<PrimitiveType*>(a_pInput), a_Data); }

o_if_wchar_t(void LanguageElementVisitor::visit(native::TIntegralType<wchar_t>* a_pInput, visitor_data a_Data) { visit(static_cast<PrimitiveType*>(a_pInput), a_Data); });
o_if_char16_t(void LanguageElementVisitor::visit(native::TIntegralType<char16_t>* a_pInput, visitor_data a_Data) { visit(static_cast<PrimitiveType*>(a_pInput), a_Data); });
o_if_char32_t(void LanguageElementVisitor::visit(native::TIntegralType<char32_t>* a_pInput, visitor_data a_Data) { visit(static_cast<PrimitiveType*>(a_pInput), a_Data); });

void LanguageElementVisitor::visit(CompositionGetSetExpression*         a_pInput, visitor_data a_Data) { visit(static_cast<Expression*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(AggregationGetSetExpression*         a_pInput, visitor_data a_Data) { visit(static_cast<Expression*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(CompositionInsertRemoveExpression*   a_pInput, visitor_data a_Data) { visit(static_cast<Expression*>(a_pInput), a_Data); }
void LanguageElementVisitor::visit(AggregationInsertRemoveExpression*   a_pInput, visitor_data a_Data) { visit(static_cast<Expression*>(a_pInput), a_Data); }


o_namespace_end(phantom, reflection)