/* ******************* Includes ****************** */
#include "phantom/phantom.h"
// #define o_USE_BOOST_SPIRIT_CPLUSPLUS_PARSER // uncomment to disable parser
#include "phantom/reflection/Expression.h"
#include "Shaman.h"
#include "Shaman.hxx"

#include "detail/CxxLexer.h"
#include "detail/CxxParser.h"
#include "detail/CxxDriver.h"
#include "detail/CxxTokenizer.h"
#include "detail/CxxPrecompiler.h"

#include <phantom/reflection/Block.h>
#include <phantom/reflection/LocalVariable.h>
#include <phantom/reflection/Parameter.h>
#include <phantom/reflection/Signature.h>
#include <phantom/reflection/BranchStatement.h>
#include <phantom/reflection/BranchIfStatement.h>
#include <phantom/reflection/BranchIfNotStatement.h>
#include <phantom/reflection/ExpressionStatement.h>
#include <phantom/reflection/ReturnStatement.h>
#include <phantom/reflection/LabelStatement.h>
#include <phantom/reflection/CallExpression.h>
#include <phantom/reflection/BuiltInConversionExpression.h>
#include <phantom/reflection/ConstantExpression.h>
#include <phantom/reflection/DataExpression.h>
#include <phantom/reflection/DataMemberExpression.h>
#include <phantom/reflection/LocalVariableExpression.h>
#include <phantom/reflection/PropertyExpression.h>
#include <phantom/reflection/VariableExpression.h>
#include <phantom/reflection/StringLiteralExpression.h>
#include <phantom/reflection/MemberFunctionPointerCallExpression.h>
#include <phantom/reflection/DataMemberPointerExpression.h>
#include <phantom/reflection/ConstructorCallExpression.h>
#include <phantom/reflection/PlacementConstructionExpression.h>
#include <phantom/reflection/TDBinaryOperationExpression.h>
#include <phantom/reflection/TDUnaryPreOperationExpression.h>
#include <phantom/reflection/TDUnaryPostOperationExpression.h>
#include <phantom/reflection/AggregationClass.h>
#include <phantom/reflection/CompositionClass.h>
#include <stdio.h>
/* *********************************************** */
o_registerN((phantom, reflection), Shaman);

o_namespace_begin(phantom, reflection)

Precompiler* Shaman::createPrecompiler( Source* a_pSource ) const
{
    return new(CxxPrecompiler)(a_pSource);
}

void Shaman::destroyPrecompiler( Precompiler* a_pPrecompiler ) const
{
    delete a_pPrecompiler;
}

Shaman::Shaman( void )
{
    CxxToken::Initialize(true);
}

Shaman::~Shaman( void )
{
    CxxToken::Initialize(false);
}

LanguageElement* Shaman::elementByName( const string& a_strName, LanguageElement* a_pScope, modifiers_t a_Modifiers /*= 0*/ ) const
{
    return internalElementByName(false, a_strName, a_pScope, a_Modifiers);
}

LanguageElement* Shaman::internalElementByName( bool a_bNamespaceMode, const string& a_strName, LanguageElement* a_pScope /*= (LanguageElement*)phantom::rootPackageFolder()*/, modifiers_t a_Modifiers /*= 0*/ ) const
{
    CxxPrecompiler* pPrecompiler = new CxxPrecompiler(a_bNamespaceMode);
    LanguageElement* pElement = pPrecompiler->precompileElement(a_strName, a_pScope, a_Modifiers);
    delete pPrecompiler;
    return (pElement AND !pElement->isInvalid()) ? pElement : nullptr;
}

Subroutine* Shaman::solveSubroutineCascade( LanguageElement* a_pElement, const string& a_strName, const vector<LanguageElement*>* a_pTemplateArguments, const vector<Type*>& a_ParameterTypes, modifiers_t a_Qualifiers, LanguageElement* a_pScope )
{
    Subroutine* pSubroutine = solveSubroutine(a_pElement, a_strName, a_pTemplateArguments, a_ParameterTypes, a_Qualifiers, a_pScope);
    if(pSubroutine) return pSubroutine;
    if(a_pElement->getOwner())
    {
        return solveSubroutineCascade(a_pElement->getOwner(), a_strName, a_pTemplateArguments, a_ParameterTypes, a_Qualifiers, a_pScope) ;
    }
    return Subroutine::Invalid();
}

LanguageElement* Shaman::unqualifiedLookup( const string& a_strName, const vector<LanguageElement*>* a_pTemplateArguments, const vector<Expression*>* a_pFunctionArguments, LanguageElement* a_pScope, Type* a_pInitializationType )
{
    LanguageElement* pResult = nullptr;
    visitor_data data;
    data.id = e_Function_UnqualifiedLookup;
    const void* in[5] = {&a_strName, a_pTemplateArguments, a_pFunctionArguments, &a_pInitializationType, &a_pScope};
    void* out[1] = {&pResult};
    data.in = in;
    data.out = out;
    a_pScope->visit(this, data);
    return pResult;
}

o_namespace_end(phantom, reflection)
