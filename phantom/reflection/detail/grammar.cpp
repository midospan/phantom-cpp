#include "phantom/phantom.h"
#if defined(_MSC_VER)
# pragma warning(disable: 4345)
#endif

#include "grammar.h"

o_namespace_begin(phantom, reflection, eval, cpp)

//string test;
/*

grammar<lexer<string::iterator>::iterator_type
    , lexer<string::iterator>> grammar_d(
    error_handler<string::iterator, lexer<string::iterator>::iterator_type>(test.begin(), test.end())
    , lexer<string::iterator>());*/

//auto g = grammar_d.generate(grammar_d.r_compilation_unit);

o_namespace_end(phantom, reflection, eval, cpp)