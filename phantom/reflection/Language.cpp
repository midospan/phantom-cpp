/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Language.h"
#include "Language.hxx"
/* *********************************************** */
o_registerN((phantom, reflection), Language);

o_namespace_begin(phantom, reflection)

Type* Language::typeByName( const string& a_strName, LanguageElement* a_pScope /*= phantom::globalNamespace()*/ ) const
{
    LanguageElement* pElement = elementByName(a_strName, a_pScope);
    return pElement ? pElement->asType() : nullptr;
}

void Language::translate( LanguageElement* a_pElement, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( Namespace* a_pNamespace, string& translation, int options /*= 0*/ )
{
    translation += "<no-translation>";
}

void Language::translate( Type* a_pType, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( PrimitiveType* a_pType, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate(FunctionPointerType* a_pType, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate(MemberFunctionPointerType* a_pType, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate(DataMemberPointerType* a_pType, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate(DataPointerType* a_pType, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate(ReferenceType* a_pType, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate(ConstType* a_pType, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate(ArrayType* a_pType, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( Enum* a_pEnum, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( ClassType* a_pClassType, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( Class* a_pClass, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( Structure* a_pStructure, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( Union* a_pUnion, string& translation, int options /*= 0*/ )
{
    translation += "<no-translation>";
}

void Language::translate( PODUnion* a_pPODUnion, string& translation, int options /*= 0*/ )
{
    translation += "<no-translation>";
}

void Language::translate( AnonymousSection* a_pAnonymousSection, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( AnonymousStruct* a_pAnonymousStruct, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( AnonymousUnion* a_pAnonymousUnion, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( Template* a_pTemplate, string& translation, int options /*= 0*/ )
{
    translation += "<no-translation>";
}

void Language::translate( TemplateSpecialization* a_pTemplateSpecialization, string& translation, int options /*= 0*/ )
{
    translation += "<no-translation>";
}

void Language::translate( Subroutine* a_pSubroutine, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( Constructor* a_pConstructor, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( Function* a_pFunction, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( StaticMemberFunction* a_pStaticMemberFunction, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( InstanceMemberFunction* a_pInstanceMemberFunction, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( Signal* a_pSignal, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( StaticDataMember* a_pStaticDataMember, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( StaticVariable* a_pStaticVariable, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( InstanceDataMember* a_pInstanceDataMember, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( Property* a_pProperty, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( state::StateMachine* a_pStateMachine, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( state::State* a_pState, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( state::Track* a_pTrack, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( Block* a_pBlock, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( LocalVariable* a_pLocalVariable, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( Parameter* a_pParameter, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( Signature* a_pSignature, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( BranchStatement* a_pBranchStatement, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( BranchIfStatement* a_pBranchIfStatement, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( BranchIfNotStatement* a_pBranchIfNotStatement, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( ExpressionStatement* a_pExpressionStatement, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( ReturnStatement* a_pReturnStatement, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( LabelStatement* a_pLabelStatement, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( CallExpression* a_pCallExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( CastExpression* a_pCastExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( DereferenceExpression* a_pDereferenceExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( AddressExpression* a_pAddressExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( ReferenceExpression* a_pReferenceExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( ConstantExpression* a_pConstantExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( DataExpression* a_pDataExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( InstanceDataMemberExpression* a_pInstanceDataMemberExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( LocalVariableExpression* a_pLocalVariableExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( PropertyExpression* a_pPropertyExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( StaticVariableExpression* a_pStaticVariableExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( ArrayExpression* a_pArrayExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( StringLiteralExpression* a_pStringLiteralExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( MemberFunctionPointerCallExpression* a_pMemberFunctionPointerCallExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( DataMemberPointerExpression* a_pDataMemberPointerExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( AssignmentExpression* a_pAssignmentExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( ConstructorCallExpression* a_pConstructorCallExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( PlacementConstructionExpression* a_pPlacementConstructionExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( BinaryOperationExpression* a_pBinaryOperatorExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( PreUnaryOperationExpression* a_pPreUnaryOperationExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( PostUnaryOperationExpression* a_pPostUnaryOperationExpression, string& translation, int options )
{
    translation += "<no-translation>";
}

void Language::translate( CompositionGetSetExpression* a_pCompositionGetSetExpression, string& translation, int options /*= 0*/ )
{
    translation += "<no-translation>";
}

void Language::translate( AggregationGetSetExpression* a_pAggregationGetSetExpression, string& translation, int options /*= 0*/ )
{
    translation += "<no-translation>";
}

void Language::translate( CompositionInsertRemoveExpression* a_pCompositionInsertRemoveExpression, string& translation, int options /*= 0*/ )
{
    translation += "<no-translation>";
}

void Language::translate( AggregationInsertRemoveExpression* a_pAggregationInsertRemoveExpression, string& translation, int options /*= 0*/ )
{
    translation += "<no-translation>";
}

void Language::translate( SingleParameterFunctionExpression* a_pSingleParameterFunctionExpression, string& translation, int options /*= 0*/ )
{
    translation += "<no-translation>";
}

void Language::translate( Constant* a_pConstant, string& translation, int options )
{
    translation += "<no-translation>";
}

string Language::translate( LanguageElement* a_pElement, int options )
{
    string result;
    if(a_pElement)
    {
        a_pElement->translate(this, result, options);
    }
    else 
    {
        result = "<null>";
    }
    return result;
}

void Language::translateTo( LanguageElement* a_pElement, string& translation, int options )
{
    if(a_pElement)
    {
        a_pElement->translate(this, translation);
    }
    else 
    {
        translation += "<null>";
    }
}

const string& Language::name( LanguageElement* a_pElement, int options )
{
    static string null_name_str = "<null>";
    return a_pElement ? a_pElement->getName() : null_name_str;
}

void Language::name( LanguageElement* a_pElement, string& translation, int options )
{
    translation += a_pElement ? a_pElement->getName() : "<null>";
}

string Language::qualifiedName( LanguageElement* a_pElement, int options )
{
    return a_pElement ? a_pElement->getQualifiedName() : "<null>";
}

void Language::qualifiedName( LanguageElement* a_pElement, string& translation, int options /*= 0*/ )
{
    translation += a_pElement ? a_pElement->getQualifiedName() : "<null>";
}

string Language::qualifiedDecoratedName( LanguageElement* a_pElement, int options )
{
    return a_pElement ? a_pElement->getQualifiedDecoratedName() : "<null>";
}

void Language::qualifiedDecoratedName( LanguageElement* a_pElement, string& translation, int options )
{
    translation += a_pElement ? a_pElement->getQualifiedDecoratedName() : "<null>";
}

o_namespace_end(phantom, reflection)