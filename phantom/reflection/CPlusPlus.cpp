/* ******************* Includes ****************** */
#include "phantom/phantom.h"
// #define o_USE_BOOST_SPIRIT_CPLUSPLUS_PARSER // uncomment to disable parser
#include "phantom/reflection/Expression.h"
#include "CPlusPlus.h"
#include "CPlusPlus.hxx"

#if (o_USE_BOOST_SPIRIT_CPLUSPLUS_PARSER)
#   include "detail/lexer.h"
#   include "detail/grammar.h"
#   include "detail/precompiler.h"
#else
#   include "detail/CxxLexer.h"
#   include "detail/CxxParser.h"
#   include "detail/CxxDriver.h"
#   include "detail/CxxPrecompiler.hxx"
#endif
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
#include <phantom/reflection/CastExpression.h>
#include <phantom/reflection/DereferenceExpression.h>
#include <phantom/reflection/AddressExpression.h>
#include <phantom/reflection/ReferenceExpression.h>
#include <phantom/reflection/ConstantExpression.h>
#include <phantom/reflection/DataExpression.h>
#include <phantom/reflection/InstanceDataMemberExpression.h>
#include <phantom/reflection/LocalVariableExpression.h>
#include <phantom/reflection/PropertyExpression.h>
#include <phantom/reflection/StaticVariableExpression.h>
#include <phantom/reflection/ArrayExpression.h>
#include <phantom/reflection/StringLiteralExpression.h>
#include <phantom/reflection/MemberFunctionPointerCallExpression.h>
#include <phantom/reflection/DataMemberPointerExpression.h>
#include <phantom/reflection/AssignmentExpression.h>
#include <phantom/reflection/ConstructorCallExpression.h>
#include <phantom/reflection/PlacementConstructionExpression.h>
#include <phantom/reflection/BinaryOperationExpression.h>
#include <phantom/reflection/PreUnaryOperationExpression.h>
#include <phantom/reflection/PostUnaryOperationExpression.h>
#include <phantom/reflection/SingleParameterFunctionExpression.h>
#include <phantom/reflection/AggregationClass.h>
#include <phantom/reflection/CompositionClass.h>
/* *********************************************** */

#include <stdio.h>

o_registerN((phantom, reflection), CPlusPlus);

o_namespace_begin(phantom, reflection)


string formatIndexString(string a_Input, size_t a_CharCount = 10)
{
    long long value = 0;
    if(sscanf(a_Input.c_str(), "%d", &value))
    {
        while(a_Input.size() < a_CharCount)
        {
            a_Input = ' ' + a_Input;
        }
    }
    return a_Input;
}

#if o_USE_BOOST_SPIRIT_CPLUSPLUS_PARSER


CPlusPlus::CPlusPlus( void )
{
}

CPlusPlus::~CPlusPlus( void )
{
}

typedef boost::spirit::classic::position_iterator<string::const_iterator, boost::spirit::classic::file_position_base<SourceFile*> > cpp_position_iterator_t;
typedef cpp::lexer<cpp_position_iterator_t> lexer_t;

typedef cpp::grammar<lexer_t::iterator_type, lexer_t> grammar_t;

static lexer_t& cpp_lexer()
{
    static lexer_t m_cpp_lexer;
    return m_cpp_lexer;
}

static grammar_t& cpp_grammar()
{
    static grammar_t m_cpp_grammar(cpp_lexer());
    return m_cpp_grammar;
}


LanguageElement* CPlusPlus::elementByName( const string& a_strName, LanguageElement* a_pScope /*= phantom::globalNamespace()*/ ) const
{
    cpp::ast::element element;
    auto first = a_strName.begin();
    auto last = a_strName.end();
    bool result = cpp_grammar().parse(first, last, cpp_grammar().r_element, element);
    if(!result) return nullptr;

#if defined(BOOST_SPIRIT_QI_DEBUG)
    static bool compiling = false;
    if(!compiling)
    {
        compiling = true;
        auto pExp = phantom::expressionByName(compilationTest());
        compiling = false;
    }
#endif
    cpp::ast::precompiler precompiler;
    LanguageElement* pElement = precompiler.precompile_element_recursive(element, a_pScope);
    return pElement ? pElement->hatch() : nullptr;
}

Expression* CPlusPlus::expressionByName( const string& a_strName, LanguageElement* a_pScope /*= phantom::globalNamespace()*/ ) const
{
    cpp::ast::expression exp;
    auto first = a_strName.begin();
    auto last = a_strName.end();
    bool result = cpp_grammar().parse(first, last, cpp_grammar().r_expression, exp);
    if(!result) return nullptr;
    cpp::ast::precompiler precompiler;
    return precompiler.precompile_expression(exp, a_pScope);
}

void CPlusPlus::compile( const string& a_strCode, Compiler* a_pCompiler, SourceFile* a_pSourceFile, Message* a_pMessage ) const
{
    cpp::ast::compilation_unit compilation_unit;
    auto first = a_strCode.begin();
    auto last = a_strCode.end();
    bool result = cpp_grammar().parse(first, last, cpp_grammar().r_compilation_unit, compilation_unit, a_pSourceFile, a_pMessage);
    if(!result) return; 
    cpp::ast::precompiler precompiler;
    precompiler.precompile_compilation_unit(compilation_unit);
}

bool CPlusPlus::execute(const string& a_strCode, const vector<variable>& arguments, variant& a_ReturnValue, Compiler* a_pCompiler) const
{
    static unsigned long long executionId = 0;
    // Build Signature based on arguments/returnvalue
    Type* pReturnType = a_ReturnValue.type();
    Signature* pSignature = o_new(Signature);
    pSignature->setReturnType(pReturnType ? pReturnType : typeOf<void>());
    string functionName = "__phantom_reflection_CPlusPlus_execute_"+lexical_cast<string>(executionId++); 
    string function = pReturnType->getQualifiedDecoratedName() + ' ' + functionName +  '(';
    string functionCode = function;
    vector<void*> argPtrs;
    for(auto it = arguments.begin(); it != arguments.end(); ++it)
    {
        Type* pParameterType = it->value.type();
        o_assert(pParameterType);
        argPtrs.push_back((void*)it->value.buffer());
        if(it != arguments.end())
        {
            functionCode += ',';
            function += ',';
        }
        functionCode += pParameterType->getQualifiedDecoratedName() + ' ' + it->name;
        function += pParameterType->getQualifiedDecoratedName();
    }
    functionCode += "{" + a_strCode + '}';
    compile(functionCode, a_pCompiler, nullptr, nullptr);
    LanguageElement* pLanguageElement = phantom::elementByName(function);
    if(pLanguageElement == nullptr)
        return false;
    Function* pFunction = pLanguageElement->asFunction();
    o_assert(pFunction);
    if(pReturnType)
    {
        pFunction->call(argPtrs.data(), (void*)a_ReturnValue.buffer());
    }
    else 
    {
        pFunction->call(argPtrs.data());
    }
    return true;

}

#else

CPlusPlus::CPlusPlus( void )
{
    CxxToken::Initialize(true);
}

CPlusPlus::~CPlusPlus( void )
{
    CxxToken::Initialize(false);
}

LanguageElement* CPlusPlus::elementByName( const string& a_strName, LanguageElement* a_pScope /*= phantom::globalNamespace()*/ ) const
{
    CxxExpression* astExpr = nullptr;
    vector<CxxToken*> tokens;
    {
        CxxDriver driverExpression(a_strName);
        int result = driverExpression.parse(tokens);
        if(result != 0) 
        {
            o_warning(false, "CPlusPlus::elementByName : parsing error");
            return nullptr;
        }
        astExpr = driverExpression.expression();
        o_assert(astExpr);
    }
    CxxPrecompiler precompiler(CxxPrecompiler::e_Flag_ExpressionMode);
    LanguageElement* pElement =  precompiler.precompile(astExpr, a_pScope);

    // Destroy tokens
    for(auto it = tokens.begin(); it != tokens.end(); ++it)
    {
        delete *it;
    }

    return pElement;
}

Expression* CPlusPlus::expressionByName( const string& a_strName, LanguageElement* a_pScope /*= phantom::globalNamespace()*/ ) const
{
    LanguageElement* pElement = elementByName(a_strName, a_pScope);
    return pElement ? pElement->asExpression() : nullptr;
}

void CPlusPlus::compile( const string& a_strCode, Compiler* a_pCompiler, SourceFile* a_pSourceFile, Module* a_pModule, Message* a_pMessage ) const
{
    CxxDeclarations* astDecl = nullptr;
    vector<CxxToken*> tokens;
    {
        CxxDriver driverExpression(a_strCode, a_pModule);
        printf("#################### COMPILE ######################\n");
        int result = driverExpression.parse(tokens);
        if(result != 0) 
        {
            o_warning(false, "CPlusPlus::compile : parsing error");
            return;
        }
        astDecl = driverExpression.declarations();
        o_assert(astDecl);
    }
    CxxPrecompiler precompiler(CxxPrecompiler::e_Flag_PrintErrors);
    precompiler.precompile(astDecl, globalNamespace());
    // Destroy tokens
    for(auto it = tokens.begin(); it != tokens.end(); ++it)
    {
        delete *it;
    }
}

bool CPlusPlus::execute(const string& a_strCode, const vector<variable>& arguments, variant& a_ReturnValue, Compiler* a_pCompiler) const
{
    o_assert(false);
    return false;
}
#endif


void CPlusPlus::translate( LanguageElement* a_pElement, string& translation, int options )
{
    qualifiedDecoratedName(a_pElement, translation);
}

void CPlusPlus::translate( Namespace* a_pNamespace, string& translation, int options )
{
    qualifiedDecoratedName(a_pNamespace, translation);
}

void CPlusPlus::translate( Type* a_pType, string& translation, int options )
{
    qualifiedDecoratedName(a_pType, translation);
}

void CPlusPlus::translate( PrimitiveType* a_pType, string& translation, int options )
{
    qualifiedDecoratedName(a_pType, translation);
}

void CPlusPlus::translate(FunctionPointerType* a_pType, string& translation, int options )
{
    qualifiedDecoratedName(a_pType, translation);
}

void CPlusPlus::translate(MemberFunctionPointerType* a_pType, string& translation, int options )
{
    qualifiedDecoratedName(a_pType, translation);
}

void CPlusPlus::translate(DataMemberPointerType* a_pType, string& translation, int options )
{
    qualifiedDecoratedName(a_pType, translation);
}

void CPlusPlus::translate(DataPointerType* a_pType, string& translation, int options )
{
    qualifiedDecoratedName(a_pType, translation);
}

void CPlusPlus::translate(ReferenceType* a_pType, string& translation, int options )
{
    qualifiedDecoratedName(a_pType, translation);
}

void CPlusPlus::translate(ConstType* a_pType, string& translation, int options )
{
    qualifiedDecoratedName(a_pType, translation);
}

void CPlusPlus::translate(ArrayType* a_pType, string& translation, int options )
{
    qualifiedDecoratedName(a_pType, translation);
}

void CPlusPlus::translate( Enum* a_pEnum, string& translation, int options )
{
    qualifiedDecoratedName(a_pEnum, translation);
}

void CPlusPlus::translate( ClassType* a_pClassType, string& translation, int options )
{
    qualifiedDecoratedName(a_pClassType, translation);
}

void CPlusPlus::translate( Class* a_pClass, string& translation, int options )
{
    qualifiedDecoratedName(a_pClass, translation);
}

void CPlusPlus::translate( Structure* a_pStructure, string& translation, int options )
{
    qualifiedDecoratedName(a_pStructure, translation);
}

void CPlusPlus::translate( Union* a_pUnion, string& translation, int options /*= 0*/ )
{
    qualifiedDecoratedName(a_pUnion, translation);
}

void CPlusPlus::translate( PODUnion* a_pPODUnion, string& translation, int options /*= 0*/ )
{
    qualifiedDecoratedName(a_pPODUnion, translation);
}

void CPlusPlus::translate( AnonymousSection* a_pAnonymousSection, string& translation, int options )
{
    qualifiedDecoratedName(a_pAnonymousSection, translation);
}

void CPlusPlus::translate( AnonymousStruct* a_pAnonymousStruct, string& translation, int options )
{
    qualifiedDecoratedName(a_pAnonymousStruct, translation);
}

void CPlusPlus::translate( AnonymousUnion* a_pAnonymousUnion, string& translation, int options )
{
    qualifiedDecoratedName(a_pAnonymousUnion, translation);
}

void CPlusPlus::translate( Template* a_pTemplate, string& translation, int options /*= 0*/ )
{
    qualifiedDecoratedName(a_pTemplate, translation);
}

void CPlusPlus::translate( TemplateSpecialization* a_pTemplateSpecialization, string& translation, int options /*= 0*/ )
{
    qualifiedDecoratedName(a_pTemplateSpecialization, translation);
}

void CPlusPlus::translate( Subroutine* a_pSubroutine, string& translation, int options )
{
    qualifiedDecoratedName(a_pSubroutine, translation);
}

void CPlusPlus::translate( Constructor* a_pConstructor, string& translation, int options )
{
    qualifiedDecoratedName(a_pConstructor, translation);
}

void CPlusPlus::translate( Function* a_pFunction, string& translation, int options )
{
    qualifiedDecoratedName(a_pFunction, translation);
}

void CPlusPlus::translate( StaticMemberFunction* a_pStaticMemberFunction, string& translation, int options )
{
    qualifiedDecoratedName(a_pStaticMemberFunction, translation);
}

void CPlusPlus::translate( InstanceMemberFunction* a_pInstanceMemberFunction, string& translation, int options )
{
    qualifiedDecoratedName(a_pInstanceMemberFunction, translation);
}

void CPlusPlus::translate( Signal* a_pSignal, string& translation, int options )
{
    qualifiedDecoratedName(a_pSignal, translation);
}

void CPlusPlus::translate( StaticDataMember* a_pStaticDataMember, string& translation, int options )
{
    qualifiedDecoratedName(a_pStaticDataMember, translation);
}

void CPlusPlus::translate( StaticVariable* a_pStaticVariable, string& translation, int options )
{
    qualifiedDecoratedName(a_pStaticVariable, translation);
}

void CPlusPlus::translate( InstanceDataMember* a_pInstanceDataMember, string& translation, int options )
{
    qualifiedDecoratedName(a_pInstanceDataMember, translation);
}

void CPlusPlus::translate( Property* a_pProperty, string& translation, int options )
{
    qualifiedDecoratedName(a_pProperty, translation);
}

void CPlusPlus::translate( state::StateMachine* a_pStateMachine, string& translation, int options )
{
    qualifiedDecoratedName(a_pStateMachine, translation);
}

void CPlusPlus::translate( state::State* a_pState, string& translation, int options )
{
    qualifiedDecoratedName(a_pState, translation);
}

void CPlusPlus::translate( state::Track* a_pTrack, string& translation, int options )
{
    qualifiedDecoratedName(a_pTrack, translation);
}

void CPlusPlus::translate( Block* a_pBlock, string& translation, int options )
{
    qualifiedDecoratedName(a_pBlock, translation);
}

void CPlusPlus::translate( LocalVariable* a_pLocalVariable, string& translation, int options )
{
    translation += qualifiedDecoratedName(a_pLocalVariable->getValueType())+" "+name(a_pLocalVariable);
    if(a_pLocalVariable->getInitializationExpression())
    {
        translation += " = ";
        translateTo(a_pLocalVariable->getInitializationExpression(), translation);
    }
    translation+=";";
}

void CPlusPlus::translate( Parameter* a_pParameter, string& translation, int options )
{
    translation += qualifiedDecoratedName(a_pParameter->getValueType())+" "+name(a_pParameter);
    if(a_pParameter->getInitializationExpression())
    {
        if(options & e_TranslationOption_Definition)
        {
            translation += " = /*";
            translateTo(a_pParameter->getInitializationExpression(), translation);
            translation += "*/";
        }
        else 
        {
            translation += " = ";
            translateTo(a_pParameter->getInitializationExpression(), translation);
        }
    }
}

void CPlusPlus::translate( Signature* a_pSignature, string& translation, int options )
{
    qualifiedDecoratedName(a_pSignature, translation);
}

void CPlusPlus::translate( BranchStatement* a_pBranchStatement, string& translation, int options )
{
    qualifiedDecoratedName(a_pBranchStatement, translation);
}

void CPlusPlus::translate( BranchIfStatement* a_pBranchIfStatement, string& translation, int options )
{
    qualifiedDecoratedName(a_pBranchIfStatement, translation);
}

void CPlusPlus::translate( BranchIfNotStatement* a_pBranchIfNotStatement, string& translation, int options )
{
    qualifiedDecoratedName(a_pBranchIfNotStatement, translation);
}

void CPlusPlus::translate( ExpressionStatement* a_pExpressionStatement, string& translation, int options )
{
    qualifiedDecoratedName(a_pExpressionStatement, translation);
}

void CPlusPlus::translate( ReturnStatement* a_pReturnStatement, string& translation, int options )
{
    qualifiedDecoratedName(a_pReturnStatement, translation);
}

void CPlusPlus::translate( LabelStatement* a_pLabelStatement, string& translation, int options )
{
    qualifiedDecoratedName(a_pLabelStatement, translation);
}

// Expressions

void CPlusPlus::translate( CallExpression* a_pCallExpression, string& translation, int options )
{
    Subroutine* pSubroutine = a_pCallExpression->getSubroutine();
    const vector<Expression*>& arguments = a_pCallExpression->getArguments();
    const string& subroutineName = name(pSubroutine);
    if(pSubroutine AND pSubroutine->asInstanceMemberFunction())
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
                    translateTo(arguments[0], translation);
                    translation += ")[";
                    translateTo(arguments[1], translation);
                    translation += ']';
                }
                else if(op == "()")
                {
                    translation += '(';
                    translateTo(arguments[0], translation);
                    translation += ")(";
                    if(arguments.size() > 1)
                    {
                        for(size_t i = 1; i<arguments.size(); ++i)
                        {
                            if(i != 1)
                                translation += ',';
                            translateTo(arguments[i], translation);
                        }
                    }
                    translation += ')';
                }
                else
                {
                    // Create operator expression
                    translation += '(';
                    translateTo(arguments[0], translation);
                    translation += ')';
                    translation += op;
                    if(arguments.size() == 2)
                    {
                        translation += '(';
                        translateTo(arguments[1], translation);
                        translation += ')';
                    }
                }
                return;
            }
        }
        translation += '(';
        translateTo(arguments[0], translation);
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
                translateTo(arguments[i], translation);
            }
        }
        translation += ')';
    }
    else 
    {
        qualifiedName(pSubroutine, translation);
        translation += '(';
        if(arguments.size())
        {
            for(size_t i = 0; i<arguments.size(); ++i)
            {
                if(i != 0)
                    translation += ',';
                translateTo(arguments[i], translation);
            }
        }
        translation += ')';
    }
}

void CPlusPlus::translate( CastExpression* a_pCastExpression, string& translation, int options )
{
    switch(a_pCastExpression->getCastType())
    {
    case e_implicit_cast:
        translateTo(a_pCastExpression->getCastedExpression(), translation);
        break;
    case e_const_cast:
        translation += "const_cast<";
        qualifiedDecoratedName(a_pCastExpression->getValueType(), translation);
        translation += ">(";
        translateTo(a_pCastExpression->getCastedExpression(), translation);
        translation += ")";
        break;
    case e_static_cast:
        translation += "static_cast<";
        qualifiedDecoratedName(a_pCastExpression->getValueType(), translation);
        translation += ">(";
        translateTo(a_pCastExpression->getCastedExpression(), translation);
        translation += ")";
        break;
    case e_reinterpret_cast:
        translation += "reinterpret_cast<";
        qualifiedDecoratedName(a_pCastExpression->getValueType(), translation);
        translation += ">(";
        translateTo(a_pCastExpression->getCastedExpression(), translation);
        translation += ")";
        break;
    case e_cstyle_cast:
        translation += "(";
        qualifiedDecoratedName(a_pCastExpression->getValueType(), translation);
        translation += ")(";
        translateTo(a_pCastExpression->getCastedExpression(), translation);
        translation += ")";
        break;
    }
}

void CPlusPlus::translate( DereferenceExpression* a_pDereferenceExpression, string& translation, int options )
{
    translation += "*(";
    translateTo(a_pDereferenceExpression->getDereferencedExpression(), translation);
    translation += ')';
}

void CPlusPlus::translate( AddressExpression* a_pAddressExpression, string& translation, int options )
{
    translation += "&(";
    translateTo(a_pAddressExpression->getAddressedExpression(), translation);
    translation += ')';
}

void CPlusPlus::translate( ReferenceExpression* a_pReferenceExpression, string& translation, int options )
{
    translateTo(a_pReferenceExpression->getReferencedExpression(), translation);
}

void CPlusPlus::translate( ConstantExpression* a_pConstantExpression, string& translation, int options )
{
    translateTo(a_pConstantExpression->getConstant(), translation);
}

void CPlusPlus::translate( DataExpression* a_pDataExpression, string& translation, int options )
{
    translation += "@(";
    translateTo(a_pDataExpression->getGuidExpression(), translation);
    translation += ')';
}

void CPlusPlus::translate( InstanceDataMemberExpression* a_pInstanceDataMemberExpression, string& translation, int options )
{
    translation += "(";
    translateTo(a_pInstanceDataMemberExpression->getLeftExpression(), translation);
    translation += ").";
    name(a_pInstanceDataMemberExpression->getInstanceDataMember(), translation);
}

void CPlusPlus::translate( LocalVariableExpression* a_pLocalVariableExpression, string& translation, int options )
{
    name(a_pLocalVariableExpression->getLocalVariable(), translation);
}

void CPlusPlus::translate( PropertyExpression* a_pPropertyExpression, string& translation, int options )
{
    translation += "(";
    translateTo(a_pPropertyExpression->getLeftExpression(), translation);
    translation += ").";
    name(a_pPropertyExpression->getProperty(), translation);
}

void CPlusPlus::translate( StaticVariableExpression* a_pStaticVariableExpression, string& translation, int options )
{
    qualifiedDecoratedName(a_pStaticVariableExpression->getStaticVariable(), translation);
}

void CPlusPlus::translate( ArrayExpression* a_pArrayExpression, string& translation, int options )
{
    translation += "(";
    translateTo(a_pArrayExpression->getLeftExpression(), translation);
    translation += ")[";
    string index;
    translateTo(a_pArrayExpression->getIndexExpression(), index);
    translation += (options & e_TranslationOption_FixedSizeIndexes) ? formatIndexString(index) : index;
    translation += "]";
}

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

void CPlusPlus::translate( StringLiteralExpression* a_pStringLiteralExpression, string& translation, int options )
{
    translateLiteral(a_pStringLiteralExpression->getString(), translation);
}

void CPlusPlus::translate( MemberFunctionPointerCallExpression* a_pMemberFunctionPointerCallExpression, string& translation, int options )
{
    translation += "((";
    translateTo(a_pMemberFunctionPointerCallExpression->getObjectExpression(), translation);
    translation += ").*(";
    translateTo(a_pMemberFunctionPointerCallExpression->getMemberExpression(), translation);
    translation += "))(";
    for(auto it = a_pMemberFunctionPointerCallExpression->beginArguments(); it != a_pMemberFunctionPointerCallExpression->endArguments(); ++it)
    {
        if(it != a_pMemberFunctionPointerCallExpression->beginArguments())
        {
            translation+=',';
        }
        translateTo(*it, translation);
    }
    translation += ')';
}

void CPlusPlus::translate( DataMemberPointerExpression* a_pDataMemberPointerExpression, string& translation, int options )
{
    translation += '(';
    translateTo(a_pDataMemberPointerExpression->getObjectExpression(), translation);
    translation += ").*(";
    translateTo(a_pDataMemberPointerExpression->getMemberExpression(), translation);
    translation += ')';
}

void CPlusPlus::translate( AssignmentExpression* a_pAssignmentExpression, string& translation, int options )
{
    translation += '(';
    translateTo(a_pAssignmentExpression->getLeftExpression(), translation);
    translation += ")=(";
    translateTo(a_pAssignmentExpression->getRightExpression(), translation);
    translation += ')';
}

void CPlusPlus::translate( ConstructorCallExpression* a_pConstructorCallExpression, string& translation, int options )
{
    qualifiedDecoratedName(a_pConstructorCallExpression->getSubroutine()->getOwner(), translation);
    translation += '(';
    for(auto it = a_pConstructorCallExpression->beginArguments(); it != a_pConstructorCallExpression->endArguments(); ++it)
    {
        if(it != a_pConstructorCallExpression->beginArguments())
        {
            translation+=',';
        }
        translateTo(*it, translation);
    }
    translation += ')';
}

void CPlusPlus::translate( PlacementConstructionExpression* a_pPlacementConstructionExpression, string& translation, int options )
{
    translation += "new(";
    translateTo(a_pPlacementConstructionExpression->getPlaceExpression(), translation);
    translation += ')';
    qualifiedDecoratedName(a_pPlacementConstructionExpression->getSubroutine()->getOwner(), translation);
    translation += '(';
    for(auto it = a_pPlacementConstructionExpression->beginArguments(); it != a_pPlacementConstructionExpression->endArguments(); ++it)
    {
        if(it != a_pPlacementConstructionExpression->beginArguments())
        {
            translation+=',';
        }
        translateTo(*it, translation);
    }
    translation += ')';
}

void CPlusPlus::translate( BinaryOperationExpression* a_pBinaryOperatorExpression, string& translation, int options )
{
    translation += '(';
    translateTo(a_pBinaryOperatorExpression->getLeftExpression(), translation);
    translation += ')';
    translation += a_pBinaryOperatorExpression->getOperator();
    translation += '(';
    translateTo(a_pBinaryOperatorExpression->getRightExpression(), translation);
    translation += ')';
}

void CPlusPlus::translate( PreUnaryOperationExpression* a_pPreUnaryOperationExpression, string& translation, int options )
{
    translation += a_pPreUnaryOperationExpression->getOperator();
    translation += '(';
    translateTo(a_pPreUnaryOperationExpression->getExpression(), translation);
    translation += ')';
}

void CPlusPlus::translate( PostUnaryOperationExpression* a_pPostUnaryOperationExpression, string& translation, int options )
{
    translation += '(';
    translateTo(a_pPostUnaryOperationExpression->getExpression(), translation);
    translation += ')';
    translation += a_pPostUnaryOperationExpression->getOperator();
}

void CPlusPlus::translate( CompositionGetSetExpression* a_pCompositionGetSetExpression, string& translation, int options /*= 0*/ )
{
    translation += '(';
    translateTo(a_pCompositionGetSetExpression->getLeftExpression(), translation, options);
    translation += ")[";
    string index;
    translateTo(a_pCompositionGetSetExpression->getIndexExpression(), index);
    translation += (options & e_TranslationOption_FixedSizeIndexes) ? formatIndexString(index) : index;
    translation += ']';
}

void CPlusPlus::translate( AggregationGetSetExpression* a_pAggregationGetSetExpression, string& translation, int options /*= 0*/ )
{
    translation += '(';
    translateTo(a_pAggregationGetSetExpression->getLeftExpression(), translation, options);
    translation += ")[";
    string index;
    translateTo(a_pAggregationGetSetExpression->getIndexExpression(), index);
    translation += (options & e_TranslationOption_FixedSizeIndexes) ? formatIndexString(index) : index;
    translation += ']';
}

void CPlusPlus::translate( CompositionInsertRemoveExpression* a_pCompositionInsertRemoveExpression, string& translation, int options /*= 0*/ )
{
    translation += '(';
    translateTo(a_pCompositionInsertRemoveExpression->getLeftExpression(), translation, options);
    translation += ")(";
    string index;
    translateTo(a_pCompositionInsertRemoveExpression->getIndexExpression(), index);
    translation += (options & e_TranslationOption_FixedSizeIndexes) ? formatIndexString(index) : index;
    translation += ')';
}

void CPlusPlus::translate( AggregationInsertRemoveExpression* a_pAggregationInsertRemoveExpression, string& translation, int options /*= 0*/ )
{
    translation += '(';
    translateTo(a_pAggregationInsertRemoveExpression->getLeftExpression(), translation, options);
    translation += ")(";
    string index;
    translateTo(a_pAggregationInsertRemoveExpression->getIndexExpression(), index);
    translation += (options & e_TranslationOption_FixedSizeIndexes) ? formatIndexString(index) : index; 
    translation += ')';
}

void CPlusPlus::translate( SingleParameterFunctionExpression* a_pSingleParameterFunctionExpression, string& translation, int options /*= 0*/ )
{
    translation += '(';
    translateTo(a_pSingleParameterFunctionExpression->getLeftExpression(), translation);
    translation += ").";
    name(a_pSingleParameterFunctionExpression->getSubroutine(), translation);
}

void CPlusPlus::translate( Constant* a_pConstant, string& translation, int options )
{
    a_pConstant->toString(translation);
}

o_namespace_end(phantom, reflection)
