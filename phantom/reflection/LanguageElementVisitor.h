

#ifndef o_reflection_LanguageElementVisitor_h__
#define o_reflection_LanguageElementVisitor_h__
// #pragma __PragmaPrintFile__


/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), LanguageElementVisitor);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

struct visitor_data
{
    visitor_data() : id(0), in(0), out(0), flags(0) {}
    visitor_data(int aid, const void** ain = 0, void** aout = 0, int aflags = 0) : id(aid), in(ain), out(aout), flags(aflags) {}
    int id;
    const void** in;
    void** out;
    int flags;
    bool hasFlag(int f) const { return (flags&f) == f; }
};

class o_export LanguageElementVisitor 
{
public:
    virtual void visit(AggregationClass*            a_pInput, visitor_data a_Data);
    virtual void visit(Alias*                       a_pInput, visitor_data a_Data);
    virtual void visit(AnonymousSection*            a_pInput, visitor_data a_Data);
    virtual void visit(AnonymousStruct*             a_pInput, visitor_data a_Data);
    virtual void visit(AnonymousUnion*              a_pInput, visitor_data a_Data);
    virtual void visit(Application*                 a_pInput, visitor_data a_Data);
    virtual void visit(ArrayType*                   a_pInput, visitor_data a_Data);
    virtual void visit(Block*                       a_pInput, visitor_data a_Data);
    virtual void visit(BranchIfNotStatement*        a_pInput, visitor_data a_Data);
    virtual void visit(BranchIfStatement*           a_pInput, visitor_data a_Data);
    virtual void visit(BranchStatement*             a_pInput, visitor_data a_Data);
    virtual void visit(BuiltInConversionExpression* a_pInput, visitor_data a_Data);
    virtual void visit(BuiltInOperator*             a_pInput, visitor_data a_Data);
    virtual void visit(BuiltInOperatorExpression*   a_pInput, visitor_data a_Data);
    virtual void visit(CallExpression*              a_pInput, visitor_data a_Data);
    virtual void visit(Class*                       a_pInput, visitor_data a_Data);
    virtual void visit(ClassType*                   a_pInput, visitor_data a_Data);
    virtual void visit(CompositionClass*            a_pInput, visitor_data a_Data);
    virtual void visit(Constant*                    a_pInput, visitor_data a_Data);
    virtual void visit(ConstantExpression*          a_pInput, visitor_data a_Data);
    virtual void visit(Constructor*                 a_pInput, visitor_data a_Data);
    virtual void visit(ConstructorCallExpression*   a_pInput, visitor_data a_Data);
    virtual void visit(ConstType*                   a_pInput, visitor_data a_Data);
    virtual void visit(ConstVolatileType*           a_pInput, visitor_data a_Data);
    virtual void visit(ContainerClass*              a_pInput, visitor_data a_Data);
    virtual void visit(DataExpression*              a_pInput, visitor_data a_Data);
    virtual void visit(DataMember*                  a_pInput, visitor_data a_Data);
    virtual void visit(DataMemberExpression*        a_pInput, visitor_data a_Data);
    virtual void visit(DataMemberPointerExpression* a_pInput, visitor_data a_Data);
    virtual void visit(DataMemberPointerType*       a_pInput, visitor_data a_Data);
    virtual void visit(DataPointerType*             a_pInput, visitor_data a_Data);
    virtual void visit(Ellipsis*                    a_pInput, visitor_data a_Data);
    virtual void visit(Enum*                        a_pInput, visitor_data a_Data);
    virtual void visit(Evaluable*                   a_pInput, visitor_data a_Data);
    virtual void visit(Event*                       a_pInput, visitor_data a_Data);
    virtual void visit(Expression*                  a_pInput, visitor_data a_Data);
    virtual void visit(ExpressionStatement*         a_pInput, visitor_data a_Data);
    virtual void visit(Function*                    a_pInput, visitor_data a_Data);
    virtual void visit(FunctionPointerType*         a_pInput, visitor_data a_Data);
    virtual void visit(Import*                      a_pInput, visitor_data a_Data);
    virtual void visit(LabelStatement*              a_pInput, visitor_data a_Data);
    virtual void visit(LanguageElement*             a_pInput, visitor_data a_Data);
    virtual void visit(LocalVariable*               a_pInput, visitor_data a_Data);
    virtual void visit(LocalVariableExpression*     a_pInput, visitor_data a_Data);
    virtual void visit(LocalVariableInitializationStatement* a_pInput, visitor_data a_Data);
    virtual void visit(LValueExpression*            a_pInput, visitor_data a_Data);
    virtual void visit(LValueInitializationStatement*a_pInput, visitor_data a_Data);
    virtual void visit(LValueReferenceType*         a_pInput, visitor_data a_Data);
    virtual void visit(MapContainerClass*           a_pInput, visitor_data a_Data);
    virtual void visit(Member*                      a_pInput, visitor_data a_Data);
    virtual void visit(MemberAnonymousSection*      a_pInput, visitor_data a_Data);
    virtual void visit(MemberAnonymousStruct*       a_pInput, visitor_data a_Data);
    virtual void visit(MemberAnonymousUnion*        a_pInput, visitor_data a_Data);

    virtual void visit(MemberFunction*              a_pInput, visitor_data a_Data);
    virtual void visit(MemberFunctionPointerCallExpression* a_pInput, visitor_data a_Data);
    virtual void visit(MemberFunctionPointerType*   a_pInput, visitor_data a_Data);
    virtual void visit(MemberPointerType*           a_pInput, visitor_data a_Data);
    virtual void visit(Module*                      a_pInput, visitor_data a_Data);
    virtual void visit(NamedElement*                a_pInput, visitor_data a_Data);
    virtual void visit(Namespace*                   a_pInput, visitor_data a_Data);
    virtual void visit(NamespaceAlias*              a_pInput, visitor_data a_Data);
    virtual void visit(NumericConstant*             a_pInput, visitor_data a_Data);
    virtual void visit(Package*                     a_pInput, visitor_data a_Data);
    virtual void visit(Parameter*                   a_pInput, visitor_data a_Data);
    virtual void visit(Placeholder*                 a_pInput, visitor_data a_Data);
    virtual void visit(PlaceholderClass*            a_pInput, visitor_data a_Data);
    virtual void visit(PlaceholderClassType*        a_pInput, visitor_data a_Data);
    virtual void visit(PlaceholderConstant*         a_pInput, visitor_data a_Data);
    virtual void visit(PlaceholderTemplate*         a_pInput, visitor_data a_Data);
    virtual void visit(PlaceholderType*             a_pInput, visitor_data a_Data);
    virtual void visit(PlacementConstructionExpression* a_pInput, visitor_data a_Data);
    virtual void visit(PointerType*                 a_pInput, visitor_data a_Data);
    virtual void visit(PrimitiveType*               a_pInput, visitor_data a_Data);
    virtual void visit(Property*                    a_pInput, visitor_data a_Data);
    virtual void visit(PropertyExpression*          a_pInput, visitor_data a_Data);
    virtual void visit(Range*                       a_pInput, visitor_data a_Data);
    virtual void visit(ReferenceType*               a_pInput, visitor_data a_Data);
    virtual void visit(ReturnStatement*             a_pInput, visitor_data a_Data); 
    virtual void visit(RValueReferenceType*         a_pInput, visitor_data a_Data);
    virtual void visit(Scope*                       a_pInput, visitor_data a_Data);
    virtual void visit(SequentialContainerClass*    a_pInput, visitor_data a_Data);
    virtual void visit(SetContainerClass*           a_pInput, visitor_data a_Data);
    virtual void visit(Signal*                      a_pInput, visitor_data a_Data);
    virtual void visit(Signature*                   a_pInput, visitor_data a_Data);
    virtual void visit(Source*                      a_pInput, visitor_data a_Data);
    virtual void visit(State*                       a_pInput, visitor_data a_Data);
    virtual void visit(StateMachine*                a_pInput, visitor_data a_Data);
    virtual void visit(StateMachineElement*         a_pInput, visitor_data a_Data);
    virtual void visit(Statement*                   a_pInput, visitor_data a_Data);
    virtual void visit(StringLiteralExpression*     a_pInput, visitor_data a_Data);
    virtual void visit(Structure*                   a_pInput, visitor_data a_Data);
    virtual void visit(Subroutine*                  a_pInput, visitor_data a_Data);
    virtual void visit(TDBinaryOperationExpression* a_pInput, visitor_data a_Data);
    virtual void visit(TDUnaryPostOperationExpression* a_pInput, visitor_data a_Data);
    virtual void visit(TDUnaryPreOperationExpression* a_pInput, visitor_data a_Data);
    virtual void visit(Track*                       a_pInput, visitor_data a_Data);
    virtual void visit(Template*                    a_pInput, visitor_data a_Data);
    virtual void visit(TemplateDependantArrayType*  a_pInput, visitor_data a_Data);
    virtual void visit(TemplateDependantElement*    a_pInput, visitor_data a_Data);
    virtual void visit(TemplateDependantExpression* a_pInput, visitor_data a_Data);
    virtual void visit(TemplateDependantTemplateInstance* a_pInput, visitor_data a_Data );
    virtual void visit(TemplateDependantType*       a_pInput, visitor_data a_Data );
    virtual void visit(TemplateParameter*           a_pInput, visitor_data a_Data);
    virtual void visit(TemplateSignature*           a_pInput, visitor_data a_Data);
    virtual void visit(TemplateSpecialization*      a_pInput, visitor_data a_Data);
    virtual void visit(Type*                        a_pInput, visitor_data a_Data);
    virtual void visit(Union*                       a_pInput, visitor_data a_Data);
    virtual void visit(ValueMember*                 a_pInput, visitor_data a_Data);
    virtual void visit(Variable*                    a_pInput, visitor_data a_Data);
    virtual void visit(VariableExpression*          a_pInput, visitor_data a_Data);
    virtual void visit(VirtualMemberFunctionTable*  a_pInput, visitor_data a_Data);
    virtual void visit(VolatileType*                a_pInput, visitor_data a_Data);

    virtual void visit(native::TFundamentalType<void>* a_pInput, visitor_data a_Data) ;
    virtual void visit(native::TFundamentalType<std::nullptr_t>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<bool>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<char>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<uchar>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<schar>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<short>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<ushort>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<int>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<uint>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<long>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<ulong>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<longlong>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<ulonglong>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TFloatingPointType<float>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TFloatingPointType<double>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TFloatingPointType<longdouble>* a_pInput, visitor_data a_Data);

    o_if_wchar_t(virtual void visit(native::TIntegralType<wchar_t>* a_pInput, visitor_data a_Data)   ;)
    o_if_char16_t(virtual void visit(native::TIntegralType<char16_t>* a_pInput, visitor_data a_Data) ;)
    o_if_char32_t(virtual void visit(native::TIntegralType<char32_t>* a_pInput, visitor_data a_Data) ;)

    virtual void visit(CompositionGetSetExpression*         a_pInput, visitor_data a_Data);
    virtual void visit(AggregationGetSetExpression*         a_pInput, visitor_data a_Data);
    virtual void visit(CompositionInsertRemoveExpression*   a_pInput, visitor_data a_Data);
    virtual void visit(AggregationInsertRemoveExpression*   a_pInput, visitor_data a_Data);

};

o_namespace_end(phantom, reflection)




#endif