/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "CxxPrecompiler.h"
#include "CxxPrecompiler.hxx"
#include "CxxDriver.h"

// Fundamental expressions
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
#include <phantom/reflection/ReturnStatement.h>
#include <phantom/reflection/TDBinaryOperationExpression.h>
#include <phantom/reflection/TDUnaryPreOperationExpression.h>
#include <phantom/reflection/TDunaryPostOperationExpression.h>
#include <phantom/reflection/Parameter.h>
#include <phantom/reflection/AggregationClass.h>
#include <phantom/reflection/CompositionClass.h>
#include <phantom/reflection/CommaExpression.h>
#include "CxxToken.h"
/* *********************************************** */
o_registerN((phantom, reflection), CxxPrecompiler);

o_namespace_begin(phantom, reflection)
   
typedef CxxToken::op op;

CxxPrecompiler::CxxPrecompiler( reflection::Source* a_pSource ) 
    : Precompiler(e_Pass_Count, a_pSource)
    , m_uiErrorCount(0)
    , m_Flags(e_Flag_None)
{
    setFlags(e_Flag_PrintErrors);
    m_PassDeclarations.resize(e_Pass_Count);
}

CxxPrecompiler::CxxPrecompiler( bool a_bNamespaceMode ) 
    : Precompiler(e_Pass_Count, nullptr)
    , m_uiErrorCount(0)
    , m_Flags(e_Flag_None)
{
    setFlags((EFlags)(a_bNamespaceMode*e_Flag_NamespaceMode)|e_Flag_ExpressionMode);
    m_PassDeclarations.resize(e_Pass_Count);
}

CxxPrecompiler::~CxxPrecompiler()
{
    // Destroy tokens
    for(auto it = m_Tokens.begin(); it != m_Tokens.end(); ++it)
    {
        delete *it;
    }
}

LabelStatement* CxxPrecompiler::topBreakLabel()
{
    return this->breakLabels.empty() ? nullptr : this->breakLabels.top();
}

LabelStatement* CxxPrecompiler::topContinueLabel()
{
    return this->continueLabels.empty() ? nullptr : this->continueLabels.top();
}

LabelStatement* CxxPrecompiler::pushBreakLabel()
{
    LabelStatement* pLabel = o_new(LabelStatement)("break"); this->breakLabels.push(pLabel); return pLabel;
}

LabelStatement* CxxPrecompiler::pushContinueLabel()
{
    LabelStatement* pLabel = o_new(LabelStatement)("continue"); this->continueLabels.push(pLabel); return pLabel;
}

void CxxPrecompiler::popBreakLabel( LabelStatement* a_pLabel )
{
    o_assert(a_pLabel == topBreakLabel()); this->breakLabels.pop();
}

void CxxPrecompiler::popContinueLabel( LabelStatement* a_pLabel )
{
    o_assert(a_pLabel == topContinueLabel()); this->continueLabels.pop();
}

LabelStatement* CxxPrecompiler::findOrCreateLabel( Subroutine* pSubroutine, const string& name )
{
    LabelStatement*& rpLabel = this->labelMap[pSubroutine][name];
    if(rpLabel == nullptr)
        return (rpLabel = o_new(LabelStatement)(name));
    else
        return rpLabel;
}

int CxxPrecompiler::runPass( int pass )
{
    if(pass == e_Pass_Parsing)
    {
        o_assert(m_Tokens.empty());
        CxxDriver parsingDriver(m_pSource);
        int result = parsingDriver.parse(m_Tokens);
        if(result != 0) 
        {
            o_warning(false, "CPlusPlus::precompile : parsing error");
            m_PassDeclarations[e_Pass_SourceMembersLocal];
            return result;
        }
        m_PassDeclarations[e_Pass_SourceMembersLocal].push_back(scope_declarations_data(m_pSource, nullptr, parsingDriver.declarations()));
    }
    else 
    {
        for(auto it = m_PassDeclarations[pass].begin(); it != m_PassDeclarations[pass].end(); ++it)
        {
            if(it->scope)
            {
                if(it->paren)
                {
                    if(it->type)
                    {
                        if(it->templateSignature)
                        {
                            o_assert_no_implementation();
                            //it->decl->precompileTemplateTypedParenthesized(this, it->type, it->paren, pScope, it->lhs, 0);
                        }
                        else 
                        {
                            it->decl->precompileTypedParenthesized(this, it->type, it->paren, it->scope, it->lhs, 0);
                        }
                    }
                    else 
                    {
                        if(it->templateSignature)
                        {
                            it->decl->precompileTemplateParenthesized(this, it->templateSignature, it->paren, it->scope, it->lhs, 0);
                        }
                        else 
                        {
                            it->decl->precompileParenthesized(this, it->paren, it->scope, it->lhs, 0);
                        }
                    }
                }
                else
                {
                    if(it->templateSignature)
                    {
                        it->decl->precompileTemplate(this, it->templateSignature, it->scope, it->lhs, 0);
                    }
                    else 
                    {
                        it->decl->precompile(this, it->scope, it->lhs, 0);
                    }
                }
            }
        }
        if(pass == e_Pass_Members)
        {
            /// Once member pass has been done, finalize every element to freeze every memory and be able to compile function blocks
            if(m_pSource)
            {
                m_pSource->finalize();
            }
        }
    }
    return 0;
}

LanguageElement* CxxPrecompiler::precompileElement( const string& a_strExpression, LanguageElement* a_pScope, modifiers_t a_Modifiers /*= 0*/ )
{
    CxxExpression* astExpr = nullptr;
    {
        CxxDriver driverExpression(a_strExpression);
        int result = driverExpression.parse(m_Tokens);
        if(result != 0) 
        {
            return nullptr;
        }
        astExpr = driverExpression.expression();
        o_assert(astExpr);
    }
    m_iPass = e_Pass_Blocks;
    return precompile(astExpr, a_pScope, a_Modifiers);
}

LanguageElement* CxxPrecompiler::precompile( CxxExpression* expr, LanguageElement* a_pScope, modifiers_t a_Modifiers /*= 0*/ )
{
    return expr->precompile(this, a_pScope, nullptr, a_Modifiers);
}

void CxxPrecompiler::precompile( CxxStatements* decls, LanguageElement* a_pScope )
{
    decls->precompile(this, a_pScope);
}

o_namespace_end(phantom, reflection)