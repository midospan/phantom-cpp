

#ifndef o_reflection_Precompiler_h__
#define o_reflection_Precompiler_h__
// #pragma __PragmaPrintFile__


/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Precompiler);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class Precompiler 
{
public:
    /// SCOPE RESOLUTION

    // Default cplusplus like elements
    virtual LanguageElement* precompileScope(LanguageElement* a_pElement, const string& a_strName, const vector<LanguageElement*>* a_pTemplate = nullptr, const vector<LanguageElement*>* a_pFuncSignature = nullptr, modifiers_t a_Modifiers = 0);

    // Namespace
    virtual LanguageElement* precompileScope(Namespace* a_pNamespace, const string& a_strName, const vector<LanguageElement*>* a_pTemplate = nullptr, const vector<LanguageElement*>* a_pFuncSignature = nullptr, modifiers_t a_Modifiers = 0);

    // Types 
    virtual LanguageElement* precompileScope(Type* a_pType, const string& a_strName, const vector<LanguageElement*>* a_pTemplate = nullptr, const vector<LanguageElement*>* a_pFuncSignature = nullptr, modifiers_t a_Modifiers = 0);
    virtual LanguageElement* precompileScope(ConstType* a_pType, const string& a_strName, const vector<LanguageElement*>* a_pTemplate = nullptr, const vector<LanguageElement*>* a_pFuncSignature = nullptr, modifiers_t a_Modifiers = 0);
    virtual LanguageElement* precompileScope(Enum* a_pEnum, const string& a_strName, const vector<LanguageElement*>* a_pTemplate = nullptr, const vector<LanguageElement*>* a_pFuncSignature = nullptr, modifiers_t a_Modifiers = 0);
    virtual LanguageElement* precompileScope(ClassType* a_pClassType, const string& a_strName, const vector<LanguageElement*>* a_pTemplate = nullptr, const vector<LanguageElement*>* a_pFuncSignature = nullptr, modifiers_t a_Modifiers = 0);
    virtual LanguageElement* precompileScope(Class* a_pClass, const string& a_strName, const vector<LanguageElement*>* a_pTemplate = nullptr, const vector<LanguageElement*>* a_pFuncSignature = nullptr, modifiers_t a_Modifiers = 0);
  
    // Statechart
    virtual LanguageElement* precompileScope(state::StateMachine* a_pStateMachine, const string& a_strName, const vector<LanguageElement*>* a_pTemplate = nullptr, const vector<LanguageElement*>* a_pFuncSignature = nullptr, modifiers_t a_Modifiers = 0);
    virtual LanguageElement* precompileScope(state::State* a_pState, const string& a_strName, const vector<LanguageElement*>* a_pTemplate = nullptr, const vector<LanguageElement*>* a_pFuncSignature = nullptr, modifiers_t a_Modifiers = 0);
    virtual LanguageElement* precompileScope(state::Track* a_pTrack, const string& a_strName, const vector<LanguageElement*>* a_pTemplate = nullptr, const vector<LanguageElement*>* a_pFuncSignature = nullptr, modifiers_t a_Modifiers = 0);

    // Statements
    virtual LanguageElement* precompileScope(Block* a_pBlock, const string& a_strName, const vector<LanguageElement*>* a_pTemplate = nullptr, const vector<LanguageElement*>* a_pFuncSignature = nullptr, modifiers_t a_Modifiers = 0);
   
    // Default cplusplus like elements
    virtual LanguageElement* precompileScope(Expression* a_pExpression, const string& a_strName, const vector<LanguageElement*>* a_pTemplate = nullptr, const vector<LanguageElement*>* a_pFuncSignature = nullptr, modifiers_t a_Modifiers = 0);

    /// EXPRESSION RESOLUTION

    // Default case
    virtual Expression* precompileExpression(LanguageElement* a_pElement, Expression* a_pExpression, const string& a_strName, const vector<LanguageElement*>* a_pTemplate = nullptr, const vector<Expression*>* a_pFuncSignature = nullptr, modifiers_t a_Modifiers = 0) { return nullptr; }

    // Types 
    virtual Expression* precompileExpression(ReferenceType* a_pType, Expression* a_pExpression, const string& a_strName, const vector<LanguageElement*>* a_pTemplate = nullptr, const vector<Expression*>* a_pFuncSignature = nullptr, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileExpression(ConstType* a_pType, Expression* a_pExpression, const string& a_strName, const vector<LanguageElement*>* a_pTemplate = nullptr, const vector<Expression*>* a_pFuncSignature = nullptr, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileExpression(ClassType* a_pClassType, Expression* a_pExpression, const string& a_strName, const vector<LanguageElement*>* a_pTemplate = nullptr, const vector<Expression*>* a_pFuncSignature = nullptr, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileExpression(Class* a_pClass, Expression* a_pExpression, const string& a_strName, const vector<LanguageElement*>* a_pTemplate = nullptr, const vector<Expression*>* a_pFuncSignature = nullptr, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileExpression(AggregationClass* a_pType, Expression* a_pExpression, const string& a_strName, const vector<LanguageElement*>* a_pTemplate = nullptr, const vector<Expression*>* a_pFuncSignature = nullptr, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileExpression(CompositionClass* a_pType, Expression* a_pExpression, const string& a_strName, const vector<LanguageElement*>* a_pTemplate = nullptr, const vector<Expression*>* a_pFuncSignature = nullptr, modifiers_t a_Modifiers = 0);

    /// OPERATOR RESOLUTION

    // Default case
    virtual Expression* precompileOperator(LanguageElement* a_pElement, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0) { return nullptr; }

    // Types 
    virtual Expression* precompileOperator(PointerType* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(MemberPointerType* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(DataPointerType* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(ReferenceType* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(ConstType* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(ArrayType* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(Enum* a_pEnum, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(ClassType* a_pClassType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(native::TFundamentalType<void>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(native::TIntegralType<bool>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(native::TIntegralType<char>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(native::TIntegralType<uchar>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
#if o_HAS_BUILT_IN_WCHAR_T
    virtual Expression* precompileOperator(native::TIntegralType<wchar_t>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
#endif
    virtual Expression* precompileOperator(native::TIntegralType<short>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(native::TIntegralType<ushort>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(native::TIntegralType<int>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(native::TIntegralType<uint>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(native::TIntegralType<long>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(native::TIntegralType<ulong>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(native::TIntegralType<longlong>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(native::TIntegralType<ulonglong>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(native::TFloatingPointType<float>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(native::TFloatingPointType<double>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);
    virtual Expression* precompileOperator(native::TFloatingPointType<longdouble>* a_pType,const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);

    template<typename t_Ty>
    Expression* precompileArithmeticOperator(native::TArithmeticType<t_Ty>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);

    template<typename t_Ty>
    Expression* precompileFloatingPointOperator(native::TFloatingPointType<t_Ty>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);

    template<typename t_Ty>
    Expression* precompileIntegralOperator(native::TIntegralType<t_Ty>* a_pType, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers = 0);

    // Expression
    virtual Expression* precompileOperator( Expression* a_pExpression, const string& a_strOperator, const vector<Expression*>& a_Arguments, modifiers_t a_Modifiers /*= 0*/ );

    /// TEMPLATE INSTANCIATION
    

    // Default cplusplus like elements
    virtual void instanciateTemplate(LanguageElement* a_pElement, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);

    virtual void instanciateTemplate(Namespace* a_pNamespace, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);

    // Types 
    virtual void instanciateTemplate(Type* a_pType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(PrimitiveType* a_pType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(FunctionPointerType* a_pType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(MemberFunctionPointerType* a_pType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(DataMemberPointerType* a_pType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(DataPointerType* a_pType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(ReferenceType* a_pType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(ConstType* a_pType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(ArrayType* a_pType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(Enum* a_pEnum, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(ClassType* a_pClassType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(Class* a_pClass, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(Structure* a_pStructure, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(Union* a_pUnion, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(PODUnion* a_pPODUnion, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(AnonymousSection* a_pAnonymousSection, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(AnonymousStruct* a_pAnonymousStruct, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(AnonymousUnion* a_pAnonymousUnion, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(Template* a_pTemplate, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(TemplateSpecialization* a_pTemplateSpecialization, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);

    // Subroutines
    virtual void instanciateTemplate(Subroutine* a_pSubroutine, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(Constructor* a_pConstructor, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(Function* a_pFunction, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(StaticMemberFunction* a_pStaticMemberFunction, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(InstanceMemberFunction* a_pInstanceMemberFunction, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(Signal* a_pSignal, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);

    // Variables
    virtual void instanciateTemplate(StaticDataMember* a_pStaticDataMember, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(StaticVariable* a_pStaticVariable, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(InstanceDataMember* a_pInstanceDataMember, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(Property* a_pProperty, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);

    // Statechart
    virtual void instanciateTemplate(state::StateMachine* a_pStateMachine, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(state::State* a_pState, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(state::Track* a_pTrack, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);

    // Statements
    virtual void instanciateTemplate(Block* a_pBlock, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(LocalVariable* a_pLocalVariable, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(Parameter* a_pParameter, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(Signature* a_pSignature, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(BranchStatement* a_pBranchStatement, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(BranchIfStatement* a_pBranchIfStatement, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(BranchIfNotStatement* a_pBranchIfNotStatement, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(ExpressionStatement* a_pExpressionStatement, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(ReturnStatement* a_pReturnStatement, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(LabelStatement* a_pLabelStatement, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);

    // Expressions
    virtual void instanciateTemplate(CallExpression* a_pCallExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(CastExpression* a_pCastExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(DereferenceExpression* a_pDereferenceExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(AddressExpression* a_pAddressExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(ReferenceExpression* a_pReferenceExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(ConstantExpression* a_pConstantExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(DataExpression* a_pDataExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(InstanceDataMemberExpression* a_pInstanceDataMemberExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(LocalVariableExpression* a_pLocalVariableExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(PropertyExpression* a_pPropertyExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(StaticVariableExpression* a_pStaticVariableExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(ArrayExpression* a_pArrayExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(StringLiteralExpression* a_pStringLiteralExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(MemberFunctionPointerCallExpression* a_pMemberFunctionPointerCallExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(DataMemberPointerExpression* a_pDataMemberPointerExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(AssignmentExpression* a_pAssignmentExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(ConstructorCallExpression* a_pConstructorCallExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(PlacementConstructionExpression* a_pPlacementConstructionExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(BinaryOperationExpression* a_pBinaryOperatorExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(PreUnaryOperationExpression* a_pPreUnaryOperationExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(PostUnaryOperationExpression* a_pPostUnaryOperationExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(CompositionGetSetExpression* a_pCompositionGetSetExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(AggregationGetSetExpression* a_pAggregationGetSetExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(CompositionInsertRemoveExpression* a_pCompositionInsertRemoveExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(AggregationInsertRemoveExpression* a_pAggregationInsertRemoveExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(SingleParameterFunctionExpression* a_pSingleParameterFunctionExpression, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);

    // Constant
    virtual void instanciateTemplate(Constant* a_pConstant, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
   
    // Placeholders
    virtual void instanciateTemplate(PlaceholderConstant* a_pPlaceholderConstant, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(PlaceholderType* a_pPlaceholderType, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(PlaceholderClass* a_pPlaceholderClass, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(PlaceholderInstanceDataMember* a_pPlaceholderInstanceDataMember, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);
    virtual void instanciateTemplate(PlaceholderSubroutine* a_pPlaceholderSubroutine, TemplateSpecialization* a_pSpec, LanguageElement*& a_pInstanciated);

protected:
    map<TemplateSpecialization*, map<LanguageElement*, LanguageElement*>> m_Templated;

};

o_namespace_end(phantom, reflection)




#endif