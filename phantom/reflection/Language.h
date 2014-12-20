#ifndef o_phantom_reflection_Language_h__
#define o_phantom_reflection_Language_h__


/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Language);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Language
{
public:
	Language(void) {}
    ~Language(void) {}

    virtual string          translate(LanguageElement* a_pElement, int options = 0);
    virtual void            translateTo(LanguageElement* a_pElement, string& translation, int options = 0);

    virtual LanguageElement*elementByName(const string& a_strName, LanguageElement* a_pScope = (LanguageElement*)phantom::globalNamespace()) const = 0;
    virtual Type*           typeByName(const string& a_strName, LanguageElement* a_pScope = (LanguageElement*)phantom::globalNamespace()) const;
    virtual Expression*     expressionByName(const string& a_strName, LanguageElement* a_pScope = (LanguageElement*)phantom::globalNamespace()) const = 0;
    virtual void            compile(const string& a_strModuleName, Compiler* a_pCompiler, SourceFile* a_pSourceFile, Module* a_pModule, Message* a_pMessage) const = 0;

    virtual const string&   name(LanguageElement* a_pElement, int options = 0);
    virtual void            name(LanguageElement* a_pElement, string& translation, int options = 0);
    virtual string          qualifiedName(LanguageElement* a_pElement, int options = 0);
    virtual void            qualifiedName(LanguageElement* a_pElement, string& translation, int options = 0);
    virtual string          qualifiedDecoratedName(LanguageElement* a_pElement, int options = 0);
    virtual void            qualifiedDecoratedName(LanguageElement* a_pElement, string& translation, int options = 0);

    // Default cplusplus like elements
    virtual void translate(LanguageElement* a_pElement, string& translation, int options = 0);

    // Namespace
    virtual void translate(Namespace* a_pNamespace, string& translation, int options = 0);

    // Types 
    virtual void translate(Type* a_pType, string& translation, int options = 0);
    virtual void translate(PrimitiveType* a_pType, string& translation, int options = 0);
    virtual void translate(FunctionPointerType* a_pType, string& translation, int options = 0);
    virtual void translate(MemberFunctionPointerType* a_pType, string& translation, int options = 0);
    virtual void translate(DataMemberPointerType* a_pType, string& translation, int options = 0);
    virtual void translate(DataPointerType* a_pType, string& translation, int options = 0);
    virtual void translate(ReferenceType* a_pType, string& translation, int options = 0);
    virtual void translate(ConstType* a_pType, string& translation, int options = 0);
    virtual void translate(ArrayType* a_pType, string& translation, int options = 0);
    virtual void translate(Enum* a_pEnum, string& translation, int options = 0);
    virtual void translate(ClassType* a_pClassType, string& translation, int options = 0);
    virtual void translate(Class* a_pClass, string& translation, int options = 0);
    virtual void translate(Structure* a_pStructure, string& translation, int options = 0);
    virtual void translate(Union* a_pUnion, string& translation, int options = 0);
    virtual void translate(PODUnion* a_pPODUnion, string& translation, int options = 0);
    virtual void translate(AnonymousSection* a_pAnonymousSection, string& translation, int options = 0);
    virtual void translate(AnonymousStruct* a_pAnonymousStruct, string& translation, int options = 0);
    virtual void translate(AnonymousUnion* a_pAnonymousUnion, string& translation, int options = 0);
    virtual void translate(Template* a_pTemplate, string& translation, int options = 0);
    virtual void translate(TemplateSpecialization* a_pTemplateSpecialization, string& translation, int options = 0);

    // Subroutines
    virtual void translate(Subroutine* a_pSubroutine, string& translation, int options = 0);
    virtual void translate(Constructor* a_pConstructor, string& translation, int options = 0);
    virtual void translate(Function* a_pFunction, string& translation, int options = 0);
    virtual void translate(StaticMemberFunction* a_pStaticMemberFunction, string& translation, int options = 0);
    virtual void translate(InstanceMemberFunction* a_pInstanceMemberFunction, string& translation, int options = 0);
    virtual void translate(Signal* a_pSignal, string& translation, int options = 0);

    // Variables
    virtual void translate(StaticDataMember* a_pStaticDataMember, string& translation, int options = 0);
    virtual void translate(StaticVariable* a_pStaticVariable, string& translation, int options = 0);
    virtual void translate(InstanceDataMember* a_pInstanceDataMember, string& translation, int options = 0);
    virtual void translate(Property* a_pProperty, string& translation, int options = 0);

    // Statechart
    virtual void translate(state::StateMachine* a_pStateMachine, string& translation, int options = 0);
    virtual void translate(state::State* a_pState, string& translation, int options = 0);
    virtual void translate(state::Track* a_pTrack, string& translation, int options = 0);

    // Statements
    virtual void translate(Block* a_pBlock, string& translation, int options = 0);
    virtual void translate(LocalVariable* a_pLocalVariable, string& translation, int options = 0);
    virtual void translate(Parameter* a_pParameter, string& translation, int options = 0);
    virtual void translate(Signature* a_pSignature, string& translation, int options = 0);
    virtual void translate(BranchStatement* a_pBranchStatement, string& translation, int options = 0);
    virtual void translate(BranchIfStatement* a_pBranchIfStatement, string& translation, int options = 0);
    virtual void translate(BranchIfNotStatement* a_pBranchIfNotStatement, string& translation, int options = 0);
    virtual void translate(ExpressionStatement* a_pExpressionStatement, string& translation, int options = 0);
    virtual void translate(ReturnStatement* a_pReturnStatement, string& translation, int options = 0);
    virtual void translate(LabelStatement* a_pLabelStatement, string& translation, int options = 0);

    // Expressions
    virtual void translate(CallExpression* a_pCallExpression, string& translation, int options = 0);
    virtual void translate(CastExpression* a_pCastExpression, string& translation, int options = 0);
    virtual void translate(DereferenceExpression* a_pDereferenceExpression, string& translation, int options = 0);
    virtual void translate(AddressExpression* a_pAddressExpression, string& translation, int options = 0);
    virtual void translate(ReferenceExpression* a_pReferenceExpression, string& translation, int options = 0);
    virtual void translate(ConstantExpression* a_pConstantExpression, string& translation, int options = 0);
    virtual void translate(DataExpression* a_pDataExpression, string& translation, int options = 0);
    virtual void translate(InstanceDataMemberExpression* a_pInstanceDataMemberExpression, string& translation, int options = 0);
    virtual void translate(LocalVariableExpression* a_pLocalVariableExpression, string& translation, int options = 0);
    virtual void translate(PropertyExpression* a_pPropertyExpression, string& translation, int options = 0);
    virtual void translate(StaticVariableExpression* a_pStaticVariableExpression, string& translation, int options = 0);
    virtual void translate(ArrayExpression* a_pArrayExpression, string& translation, int options = 0);
    virtual void translate(StringLiteralExpression* a_pStringLiteralExpression, string& translation, int options = 0);
    virtual void translate(MemberFunctionPointerCallExpression* a_pMemberFunctionPointerCallExpression, string& translation, int options = 0);
    virtual void translate(DataMemberPointerExpression* a_pDataMemberPointerExpression, string& translation, int options = 0);
    virtual void translate(AssignmentExpression* a_pAssignmentExpression, string& translation, int options = 0);
    virtual void translate(ConstructorCallExpression* a_pConstructorCallExpression, string& translation, int options = 0);
    virtual void translate(PlacementConstructionExpression* a_pPlacementConstructionExpression, string& translation, int options = 0);
    virtual void translate(BinaryOperationExpression* a_pBinaryOperatorExpression, string& translation, int options = 0);
    virtual void translate(PreUnaryOperationExpression* a_pPreUnaryOperationExpression, string& translation, int options = 0);
    virtual void translate(PostUnaryOperationExpression* a_pPostUnaryOperationExpression, string& translation, int options = 0);
    virtual void translate(CompositionGetSetExpression* a_pCompositionGetSetExpression, string& translation, int options = 0);
    virtual void translate(AggregationGetSetExpression* a_pAggregationGetSetExpression, string& translation, int options = 0);
    virtual void translate(CompositionInsertRemoveExpression* a_pCompositionInsertRemoveExpression, string& translation, int options = 0);
    virtual void translate(AggregationInsertRemoveExpression* a_pAggregationInsertRemoveExpression, string& translation, int options = 0);
    virtual void translate(SingleParameterFunctionExpression* a_pSingleParameterFunctionExpression, string& translation, int options = 0);

    // Constant
    virtual void translate(Constant* a_pConstant, string& translation, int options = 0);

protected:
    map<Class*, fastdelegate::DelegateMemento> m_TranslationDelegates;
};

o_namespace_end(phantom, reflection)

#endif // o_phantom_reflection_Language_h__
