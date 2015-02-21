#ifndef o_phantom_reflection_CPlusPlus_h__
#define o_phantom_reflection_CPlusPlus_h__


/* ****************** Includes ******************* */
#include <phantom/reflection/Language.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), CPlusPlus);
o_fwd(struct, phantom, reflection, numeric_conversion);
o_fwd(struct, phantom, CxxStatement);
o_fwd(struct, phantom, CxxStatements);
o_fwd(struct, phantom, CxxParenthesised);
o_fwd(struct, phantom, CxxExpression);
o_fwd(struct, phantom, CxxToken);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

enum EOperatorType
{
    e_OperatorType_Binary,
    e_OperatorType_UnaryPrefixed,
    e_OperatorType_UnaryPostfixed,
    e_OperatorType_Ternary,
};

enum EOperator
{
    e_Operator_Plus,
    e_Operator_Minus,
    e_Operator_Add,
    e_Operator_Subtract,
    e_Operator_Multiply,
    e_Operator_Divide,
    e_Operator_Address,
    e_Operator_Dereference,
    e_Operator_Arrow,
    e_Operator_ArrowStar,
    e_Operator_PreDecrement,
    e_Operator_PreIncrement,
    e_Operator_PostDecrement,
    e_Operator_PostIncrement,
    e_Operator_Equal,
    e_Operator_NotEqual,
    e_Operator_Greater,
    e_Operator_Less,
    e_Operator_GreaterEqual,
    e_Operator_LessEqual,
    e_Operator_LogicalAnd,
    e_Operator_LogicalOr,
    e_Operator_XOr,
    e_Operator_Not,
    e_Operator_BitAnd,
    e_Operator_BitOr,
    e_Operator_Complement,
    e_Operator_Modulo,
    e_Operator_ShiftLeft,
    e_Operator_ShiftRight,
    e_Operator_Assignment,
    e_Operator_AssignmentAdd,
    e_Operator_AssignmentSubtract,
    e_Operator_AssignmentMultiply,
    e_Operator_AssignmentDivide,
    e_Operator_AssignmentBitAnd,
    e_Operator_AssignmentBitOr,
    e_Operator_AssignmentModulo,
    e_Operator_AssignmentShiftLeft,
    e_Operator_AssignmentShiftRight,
    e_Operator_AssignmentXOr,
    e_Operator_Bracket,

    e_Operator_Count,
};

enum EUserDefinedFunctions
{
    e_no_user_defined_functions = 0,
    e_implicit_functions,
    e_explicit_functions,
};

enum EValueCategory
{
    e_prvalue,
    e_rvalue,
    e_glvalue,
    e_lvalue,
    e_xvalue,
};

enum EConversionType
{
    e_implicit_conversion,
    e_const_cast,
    e_reinterpret_cast,
    e_static_cast,
    e_explicit_cast,
};

enum ETranslationType
{
    e_translation_qualified_name,
    e_translation_qualified_decorated_name,
    e_translation_declaration,
    e_translation_definition,
};

class o_export CPlusPlus : public Language
{
public:
    CPlusPlus(const char* a_ScopeDelimiter = "::");
	~CPlusPlus(void);

    enum EVisitorFlag
    {
        e_VisitorFlag_NamespaceMode = 0x1,
    };

    enum ETranslationOption
    {
        e_TranslationOption_Declaration = 0x1,
        e_TranslationOption_Definition = 0x2,
        e_TranslationOption_FixedSizeIndexes = 0x4,
    };

    enum EFunction
    {
        e_Function_Conversion = Language::e_Function_Conversion,
        e_Function_ToExpression = Language::e_Function_ToExpression,
        e_Function_Translate = Language::e_Function_Translate,
        e_Function_SubroutineResolution,
        e_Function_UnqualifiedLookup,
        e_Function_TemplateArgumentDeduction,
        e_Function_QualifiedLookup,
        e_Function_UnqualifiedNameLookup,
        e_Function_QualifiedNameLookup,
        e_Function_IsViableCallCandidate,
        e_Function_IsViableSignatureCandidate,
        e_Function_InstanciateTemplate,
        e_Function_ResolveTemplateDependencies,
        e_Function_BinaryOperator,
        e_Function_UnaryPreOperator,
        e_Function_UnaryPostOperator,
    };

    static string compilationTest();

    /// Translation
       
    virtual LanguageElement* elementByName(const string& a_strName, LanguageElement* a_pScope = (LanguageElement*)globalNamespace(), modifiers_t a_Modifiers = 0) const;


    /// ------------------------------- VISIT -----------------------------------

    virtual void visit(AggregationClass*            a_pInput, visitor_data a_Data) ;
    virtual void visit(Alias*                       a_pInput, visitor_data a_Data) ;
    virtual void visit(AnonymousSection*            a_pInput, visitor_data a_Data) ;
    virtual void visit(AnonymousStruct*             a_pInput, visitor_data a_Data) ;
    virtual void visit(AnonymousUnion*              a_pInput, visitor_data a_Data) ;
    virtual void visit(Application*                 a_pInput, visitor_data a_Data) ;
    virtual void visit(ArrayType*                   a_pInput, visitor_data a_Data) ;
    virtual void visit(Block*                       a_pInput, visitor_data a_Data) ;
    virtual void visit(BranchIfNotStatement*        a_pInput, visitor_data a_Data) ;
    virtual void visit(BranchIfStatement*           a_pInput, visitor_data a_Data) ;
    virtual void visit(BranchStatement*             a_pInput, visitor_data a_Data) ;
    virtual void visit(BuiltInConversionExpression* a_pInput, visitor_data a_Data) ;
    virtual void visit(BuiltInOperator*             a_pInput, visitor_data a_Data) ;
    virtual void visit(BuiltInOperatorExpression*   a_pInput, visitor_data a_Data) ;
    virtual void visit(CallExpression*              a_pInput, visitor_data a_Data) ;
    virtual void visit(Class*                       a_pInput, visitor_data a_Data) ;
    virtual void visit(ClassType*                   a_pInput, visitor_data a_Data) ;
    virtual void visit(CompositionClass*            a_pInput, visitor_data a_Data) ;
    virtual void visit(Constant*                    a_pInput, visitor_data a_Data) ;
    virtual void visit(ConstantExpression*          a_pInput, visitor_data a_Data) ;
    virtual void visit(Constructor*                 a_pInput, visitor_data a_Data) ;
    virtual void visit(ConstructorCallExpression*   a_pInput, visitor_data a_Data) ;
    virtual void visit(ConstType*                   a_pInput, visitor_data a_Data) ;
    virtual void visit(ConstVolatileType*           a_pInput, visitor_data a_Data) ;
    virtual void visit(ContainerClass*              a_pInput, visitor_data a_Data) ;
    virtual void visit(DataExpression*              a_pInput, visitor_data a_Data) ;
    virtual void visit(DataMember*                  a_pInput, visitor_data a_Data) ;
    virtual void visit(DataMemberExpression*        a_pInput, visitor_data a_Data) ;
    virtual void visit(DataMemberPointerExpression* a_pInput, visitor_data a_Data) ;
    virtual void visit(DataMemberPointerType*       a_pInput, visitor_data a_Data) ;
    virtual void visit(DataPointerType*             a_pInput, visitor_data a_Data) ;
    virtual void visit(Ellipsis*                    a_pInput, visitor_data a_Data) ;
    virtual void visit(Enum*                        a_pInput, visitor_data a_Data) ;
    virtual void visit(Evaluable*                   a_pInput, visitor_data a_Data) ;
    virtual void visit(Event*                       a_pInput, visitor_data a_Data) ;
    virtual void visit(Expression*                  a_pInput, visitor_data a_Data) ;
    virtual void visit(ExpressionStatement*         a_pInput, visitor_data a_Data) ;
    virtual void visit(Function*                    a_pInput, visitor_data a_Data) ;
    virtual void visit(FunctionPointerType*         a_pInput, visitor_data a_Data) ;
    virtual void visit(Import*                      a_pInput, visitor_data a_Data) ;
    virtual void visit(LabelStatement*              a_pInput, visitor_data a_Data) ;
    virtual void visit(LanguageElement*             a_pInput, visitor_data a_Data) ;
    virtual void visit(LocalVariable*               a_pInput, visitor_data a_Data) ;
    virtual void visit(LocalVariableExpression*     a_pInput, visitor_data a_Data) ;
    virtual void visit(LocalVariableInitializationStatement* a_pInput, visitor_data a_Data) ;
    virtual void visit(LValueExpression*            a_pInput, visitor_data a_Data) ;
    virtual void visit(LValueInitializationStatement*            a_pInput, visitor_data a_Data) ;
    virtual void visit(LValueReferenceType*         a_pInput, visitor_data a_Data) ;
    virtual void visit(MapContainerClass*           a_pInput, visitor_data a_Data) ;
    virtual void visit(Member*                      a_pInput, visitor_data a_Data) ;
    virtual void visit(MemberAnonymousSection*      a_pInput, visitor_data a_Data) ;
    virtual void visit(MemberAnonymousStruct*       a_pInput, visitor_data a_Data) ;
    virtual void visit(MemberAnonymousUnion*        a_pInput, visitor_data a_Data) ;
    virtual void visit(MemberFunction*              a_pInput, visitor_data a_Data) ;
    virtual void visit(MemberFunctionPointerCallExpression* a_pInput, visitor_data a_Data);
    virtual void visit(MemberFunctionPointerType*   a_pInput, visitor_data a_Data) ;
    virtual void visit(MemberPointerType*           a_pInput, visitor_data a_Data) ;
    virtual void visit(Module*                      a_pInput, visitor_data a_Data) ;
    virtual void visit(NamedElement*                a_pInput, visitor_data a_Data) ;
    virtual void visit(Namespace*                   a_pInput, visitor_data a_Data) ;
    virtual void visit(NamespaceAlias*              a_pInput, visitor_data a_Data) ;
    virtual void visit(NumericConstant*             a_pInput, visitor_data a_Data) ;
    virtual void visit(Package*                     a_pInput, visitor_data a_Data) ;
    virtual void visit(Parameter*                   a_pInput, visitor_data a_Data) ;
    virtual void visit(Placeholder*                 a_pInput, visitor_data a_Data) ;
    virtual void visit(PlaceholderClass*            a_pInput, visitor_data a_Data) ;
    virtual void visit(PlaceholderClassType*        a_pInput, visitor_data a_Data) ;
    virtual void visit(PlaceholderConstant*         a_pInput, visitor_data a_Data) ;
    virtual void visit(PlaceholderTemplate*         a_pInput, visitor_data a_Data) ;
    virtual void visit(PlaceholderType*             a_pInput, visitor_data a_Data) ;
    virtual void visit(PlacementConstructionExpression* a_pInput, visitor_data a_Data) ;
    virtual void visit(PointerType*                 a_pInput, visitor_data a_Data) ;
    virtual void visit(PrimitiveType*               a_pInput, visitor_data a_Data) ;
    virtual void visit(Property*                    a_pInput, visitor_data a_Data) ;
    virtual void visit(PropertyExpression*          a_pInput, visitor_data a_Data) ;
    virtual void visit(Range*                       a_pInput, visitor_data a_Data) ;
    virtual void visit(ReferenceType*               a_pInput, visitor_data a_Data) ;
    virtual void visit(ReturnStatement*             a_pInput, visitor_data a_Data) ; 
    virtual void visit(RValueReferenceType*         a_pInput, visitor_data a_Data) ;
    virtual void visit(Scope*                       a_pInput, visitor_data a_Data) ;
    virtual void visit(SequentialContainerClass*    a_pInput, visitor_data a_Data) ;
    virtual void visit(SetContainerClass*           a_pInput, visitor_data a_Data) ;
    virtual void visit(Signal*                      a_pInput, visitor_data a_Data) ;
    virtual void visit(Signature*                   a_pInput, visitor_data a_Data) ;
    virtual void visit(Source*                      a_pInput, visitor_data a_Data) ;
    virtual void visit(State*                       a_pInput, visitor_data a_Data) ;
    virtual void visit(StateMachine*                a_pInput, visitor_data a_Data) ;
    virtual void visit(StateMachineElement*         a_pInput, visitor_data a_Data) ;
    virtual void visit(Statement*                   a_pInput, visitor_data a_Data) ;
    virtual void visit(StringLiteralExpression*     a_pInput, visitor_data a_Data) ;
    virtual void visit(Structure*                   a_pInput, visitor_data a_Data) ;
    virtual void visit(Subroutine*                  a_pInput, visitor_data a_Data) ;
    virtual void visit(TDBinaryOperationExpression*   a_pInput, visitor_data a_Data);
    virtual void visit(TDUnaryPostOperationExpression*a_pInput, visitor_data a_Data);
    virtual void visit(TDUnaryPreOperationExpression* a_pInput, visitor_data a_Data);
    virtual void visit(Track*                       a_pInput, visitor_data a_Data) ;
    virtual void visit(Template*                    a_pInput, visitor_data a_Data) ;
    virtual void visit(TemplateDependantArrayType*  a_pInput, visitor_data a_Data) ;
    virtual void visit(TemplateDependantElement*    a_pInput, visitor_data a_Data) ;
    virtual void visit(TemplateDependantExpression* a_pInput, visitor_data a_Data) ;
    virtual void visit(TemplateDependantTemplateInstance* a_pInput, visitor_data a_Data);
    virtual void visit(TemplateDependantType*       a_pInput, visitor_data a_Data) ;
    virtual void visit(TemplateParameter*           a_pInput, visitor_data a_Data) ;
    virtual void visit(TemplateSignature*           a_pInput, visitor_data a_Data) ;
    virtual void visit(TemplateSpecialization*      a_pInput, visitor_data a_Data) ;
    virtual void visit(Type*                        a_pInput, visitor_data a_Data) ;
    virtual void visit(Union*                       a_pInput, visitor_data a_Data) ;
    virtual void visit(ValueMember*                 a_pInput, visitor_data a_Data) ;
    virtual void visit(Variable*                    a_pInput, visitor_data a_Data) ;
    virtual void visit(VariableExpression*          a_pInput, visitor_data a_Data) ;
    virtual void visit(VirtualMemberFunctionTable*  a_pInput, visitor_data a_Data) ;
    virtual void visit(VolatileType*                a_pInput, visitor_data a_Data) ;

    virtual void visit(native::TFundamentalType<void>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TFundamentalType<std::nullptr_t>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<bool>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<char>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<uchar>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<schar>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<short>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<ushort>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<int>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<uint>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TIntegralType<long>* a_pInput, visitor_data a_Data) ;
    virtual void visit(native::TIntegralType<ulong>* a_pInput, visitor_data a_Data) ;
    virtual void visit(native::TIntegralType<longlong>* a_pInput, visitor_data a_Data) ;
    virtual void visit(native::TIntegralType<ulonglong>* a_pInput, visitor_data a_Data);
    virtual void visit(native::TFloatingPointType<float>* a_pInput, visitor_data a_Data) ;
    virtual void visit(native::TFloatingPointType<double>* a_pInput, visitor_data a_Data) ;
    virtual void visit(native::TFloatingPointType<longdouble>* a_pInput, visitor_data a_Data) ;

    o_if_wchar_t(virtual void visit(native::TIntegralType<wchar_t>* a_pInput, visitor_data a_Data););
    o_if_char16_t(virtual void visit(native::TIntegralType<char16_t>* a_pInput, visitor_data a_Data););
    o_if_char32_t(virtual void visit(native::TIntegralType<char32_t>* a_pInput, visitor_data a_Data););

    virtual void visit(CompositionGetSetExpression*         a_pInput, visitor_data a_Data);
    virtual void visit(AggregationGetSetExpression*         a_pInput, visitor_data a_Data);
    virtual void visit(CompositionInsertRemoveExpression*   a_pInput, visitor_data a_Data);
    virtual void visit(AggregationInsertRemoveExpression*   a_pInput, visitor_data a_Data);

    void selectCallCandidate( vector<LanguageElement*>& candidates, const vector<LanguageElement*>* in_pTemplateArguments, vector<Expression*>& arguments, LanguageElement* &out_pResult, const string& in_name, LanguageElement* in_pContextScope, Type* in_pInitializationType, modifiers_t a_Modifiers = 0 );

    void generateArgumentsText( const vector<Expression*> &arguments, string& argumentsText );

    Expression* solveBinaryOperator(const string& a_strOp, Expression* a_pLeft, Expression* a_pRight, LanguageElement* a_pScope = nullptr);
    Expression* solveUnaryPreOperator(const string& a_strOp, Expression* a_pExpression, LanguageElement* a_pScope = nullptr);
    Expression* solveUnaryPostOperator(const string& a_strOp, Expression* a_pExpression, LanguageElement* a_pScope = nullptr);
    LanguageElement* qualifiedLookup(LanguageElement* a_pElement, const string& a_strName, const vector<LanguageElement*>* a_pTemplateArguments, const vector<Expression*>* a_pFunctionArguments, LanguageElement* a_pScope = nullptr, Type* a_pInitializationType = nullptr);
    virtual LanguageElement* unqualifiedLookup(const string& a_strName, const vector<LanguageElement*>* a_pTemplateArguments, const vector<Expression*>* a_pFunctionArguments, LanguageElement* a_pScope = nullptr, Type* a_pInitializationType = nullptr);
    Subroutine* solveSubroutine(LanguageElement* a_pElement, const string& a_strName, const vector<LanguageElement*>* a_pTemplateArguments, const vector<Type*>& a_ParameterTypes, modifiers_t a_Qualifiers, LanguageElement* a_pScope = nullptr);
    virtual Subroutine* solveSubroutineCascade(LanguageElement* a_pElement, const string& a_strName, const vector<LanguageElement*>* a_pTemplateArguments, const vector<Type*>& a_ParameterTypes, modifiers_t a_Qualifiers, LanguageElement* a_pScope = nullptr);
    Expression* convert(Expression* a_pInputExpression, Type* a_pOutputType, int a_iConversionType = e_implicit_conversion, LanguageElement* a_pContextScope = nullptr, bool a_bEmitError = true);
    LanguageElement* resolveTemplateDependency(LanguageElement* a_pElement, TemplateSignature* a_pTemplateSignature, const map<Placeholder*, LanguageElement*>& a_Arguments, LanguageElement* a_pScope = nullptr, int a_Flags = 0);
    LanguageElement* instanciateTemplate(LanguageElement* a_pElement, TemplateSignature* a_pTemplateSignature, const map<Placeholder*, LanguageElement*>& a_Arguments, LanguageElement* a_pScope = nullptr, int a_Flags = 0);
    LanguageElement* templateArgumentDeduction(LanguageElement* a_pParameter, LanguageElement* a_pArgument, map<Placeholder*, LanguageElement*>& deductions);
    Type* templateArgumentDeduction(LanguageElement* a_pParameter, Type* a_pArgument, map<Placeholder*, LanguageElement*>& deductions);
    int compareSpecialized(TemplateSpecialization* a_pT0, TemplateSpecialization* a_pT1);
    int partialOrdering(const vector<LanguageElement*>& P0, const vector<LanguageElement*>& A0, const vector<LanguageElement*>& P1, const vector<LanguageElement*>& A1);
    
protected:
    template<typename t_Ty>
    void visitIntegral( native::TIntegralType<t_Ty>* a_pInput, visitor_data a_Data );
    template<typename t_Ty>
    void visitFloatingPoint( native::TFloatingPointType<t_Ty>* a_pInput, visitor_data a_Data );

    bool baseConversion(Type* a_pInput, Type*& a_pOutput, int a_ConversionType);
    conversion* userDefinedConversion(Type* a_pInput, Type* a_pOutput, bool a_bExplicit, LanguageElement* a_pContextScope = nullptr, bool a_bConstRef = false);
    conversion* baseUserDefinedConversion(Type* a_pInput, Type* a_pOutput, int a_ConversionType, LanguageElement* a_pContextScope);
    conversion* userDefinedConversionByConstruction(Type* a_pInput, ClassType* a_pOutput, bool a_bExplicit, LanguageElement* a_pContextScope, bool bConstRef);
    conversion* userDefinedConversionByConversionFunction(ClassType* a_pInput, Type* a_pOutput, bool a_bExplicit, LanguageElement* a_pContextScope, bool bConstRef);
    conversion* baseStandardConversion(Type* a_pInput, Type* a_pOutput, int a_ConversionType, bool& a_bConstRef);

    template<typename t_Ty> 
    conversion* baseIntegralConversion(native::TIntegralType<t_Ty>* a_pInput, Type* pOutput, int iConversionType, bool& a_bConstRef);
    template<typename t_Ty, int> 
    conversion* integralConversion(native::TIntegralType<t_Ty>* a_pInput, Type* pOutput, bool a_bPromotion, bool a_bConstRef);
    template<typename t_Ty, int> 
    numeric_conversion* integralConversion(native::TIntegralType<t_Ty>* a_pInput, Type* pOutput, bool a_bPromotion);
    template<typename t_Ty, int> 
    numeric_conversion* arithmeticConversion(native::TArithmeticType<t_Ty>* a_pInput, Type* pOutput, bool a_bPromotion = false);
    template<typename t_Ty, int> 
    numeric_conversion* floatingPointConversion(native::TFloatingPointType<t_Ty>* a_pInput, Type* pOutput, bool a_bPromotion = false);
    template<typename t_Ty, int> 
    conversion* floatingPointConversion(native::TFloatingPointType<t_Ty>* a_pInput, Type* pOutput, bool a_bPromotion, bool a_bConstRef);

protected:
    virtual Precompiler*    createPrecompiler(Source* a_pSource) const { o_error(false, "no C++ precompiler available"); return nullptr; }
    virtual void            destroyPrecompiler(Precompiler* a_pPrecompiler) const { o_error(false, "no C++ precompiler available"); }

protected:
    void translateLiteral(const string& a_Value, string& translation, int options = 0);

protected:
    const char* m_ScopeDelimiter;
};

o_namespace_end(phantom, reflection)

#endif // o_phantom_reflection_CPlusPlus_h__
