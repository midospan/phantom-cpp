/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "phantom/reflection/Expression.h"
#include "CPlusPlus.h"
#include "CPlusPlus.hxx"
#include "detail/lexer.h"
#include "detail/grammar.h"
#include "detail/precompiler.h"
/* *********************************************** */
o_registerN((phantom, reflection), CPlusPlus);
 
o_namespace_begin(phantom, reflection)

typedef boost::spirit::classic::position_iterator<string::const_iterator, boost::spirit::classic::file_position_base<SourceFile*>> cpp_position_iterator_t;
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


LanguageElement* CPlusPlus::elementByName( const string& a_strName, LanguageElement* a_pScope /*= phantom::rootNamespace()*/ ) const
{

    cpp::ast::element element;
    auto first = a_strName.begin();
    auto last = a_strName.end();
    bool result = cpp_grammar().parse(first, last, cpp_grammar().r_element, element);
    if(!result) return nullptr;
//     static bool compiling = false;
//     if(!compiling)
//     {
//         compiling = true;
//         phantom::cplusplus()->compile(
//             "class CompiledClass "                                                                     "\n"
//             "{"                                                                                         "\n"
//             "   void testIf() const"                                                                              "\n"
//             "   { int i = 0;"                                                                                                 "\n"
//             "       if(i%2 == 0)"                                                                              "\n"
//             "       {"                                                                                         "\n"
//             "           thenMethod();"                                                                         "\n"
//             "       }"                                                                                         "\n"
// //             "       else"                                                                                      "\n"
// //             "       {"                                                                                         "\n"
// //             "           elseMethod();"                                                                         "\n"
// //             "       }"                                                                                         "\n"
//             "   }"                                                                                                 "\n"
//             "};                                                                                          "       "\n"
//             , nullptr, nullptr, nullptr);
//         compiling = false;
//     }

    cpp::ast::precompiler precompiler;
    LanguageElement* pElement = precompiler.precompile_element_recursive(element, a_pScope);
    return pElement ? pElement->hatch() : nullptr;
}

Expression* CPlusPlus::expressionByName( const string& a_strName, LanguageElement* a_pScope /*= phantom::rootNamespace()*/ ) const
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

bool CPlusPlus::execute(const string& a_strCode, const vector<variable>& a_Arguments, variant& a_ReturnValue, Compiler* a_pCompiler) const
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
    for(auto it = a_Arguments.begin(); it != a_Arguments.end(); ++it)
    {
        Type* pParameterType = it->value.type();
        o_assert(pParameterType);
        argPtrs.push_back((void*)it->value.buffer());
        if(it != a_Arguments.end())
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

o_namespace_end(phantom, reflection)
