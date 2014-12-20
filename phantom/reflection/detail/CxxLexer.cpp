//
//	  Title:			C++ Grammar Lexer support compilation unit.
//
//	  File Name:		CxxLexer.cpp
//
//	  Author:			E.D.Willink
//END
//
#include <phantom/phantom.h>
#include <stdlib.h>

#include "location.hh"

void yy_register_location(const phantom::location& loc, int len)
{

}

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::flush;

#include "CxxDriver.h"
#include "CxxLexer.cxx"
#include "CxxSearchContext.h"

namespace phantom {

//
//	Advance the binary search of template attempts. Rewinds and forces true into the input sequence
//	to proceed with the search. Rewinds and forces false to terminate it. Also forces a # that may then
//	be used to initiate error propagation.
//
void CxxLexer::advance_search()
{
    CxxSearchContext::search_advances++;
    remark(CxxSearchContext::current()->mark());
    if (CxxSearchContext::current() && CxxSearchContext::current()->advance())
    {
        primed_tokens[0] = CxxToken::plusToken;
        primed_tokens[1] = 0;
    }
    else
    {
        primed_tokens[0] = CxxToken::minusToken;
        primed_tokens[1] = CxxToken::hashToken;
    }
}

//
//	Complete a search, releasing the search context object and popping a mark off the stack.
//
void CxxLexer::end_search(CxxToken *aToken)
{
    CxxSearchContext::release();
    unmark(aToken);
}

//
//	Notch up an error and establish a good break point.
//
void CxxLexer::increment_error_count()
{
    error_count++;
}

//
//	Push a new marked context onto the stack, returning its identity for use by remark().
//	Any parser readahead is incorporated within the marked region.
//
size_t CxxLexer::mark()
{
    if (primed_tokens[0])
        ERRMSG("Unexpected primed_tokens[0] in mark.");
    size_t markIndex = tokenReadIndex;
    if ((*_yychar) != -2)
    {
        //		if (primed_tokens[2])
        //			token_put(primed_tokens[2]);
        //		if (primed_tokens[1])
        //			token_put(primed_tokens[1]);
        //		if (primed_tokens[0])
        //			token_put(primed_tokens[0]);
        //		if (!tokenMarkDepth)
        if (!tokenReadIndex && !tokenWriteIndex)
        {
            token_put(static_cast<CxxParser::semantic_type*>(_yylval)->token);
            tokenReadIndex = 0;
        }
        else if (!tokenReadIndex)
            ERRMSG("Unexpected 0 read index in mark.");
        else if (tokenBuffer[--tokenReadIndex] != static_cast<CxxParser::semantic_type*>(_yylval)->token)
            ERRMSG("Unexpected unget in mark.");
        markIndex = tokenReadIndex;
        (*_yychar) = -2;
        printf(" ---------------------- mark() (*_yychar) != -2 ----------------------\n");
        primed_tokens[0] = 0;
        primed_tokens[1] = 0;
    }
    tokenMarkDepth++; 
    bang_depth++;
    return markIndex;
}

//
//	If it is appropriate to do type I function parameter parsing perform a mark and force a rrue token
//	into the input stream. Otherwise just force a false token in.
//
size_t CxxLexer::mark_type1()
{
    if (!in_type1 && CxxSearchContext::current() && CxxSearchContext::current()->enable_type1())
    {
        size_t markIndex = mark();
        primed_tokens[0] = CxxToken::plusToken;
        primed_tokens[1] = 0;
        in_type1 = true;
        return markIndex;
    }
    else
    {
        primed_tokens[0] = CxxToken::minusToken;
        primed_tokens[1] = ((*_yychar) != -2) ? static_cast<CxxParser::semantic_type*>(_yylval)->token : 0;
        return 0;			// Never used.
    }
}	

//
//	Push a bang context onto the error suppression stack, returning the context for restoration by pop_bang.
//
void CxxLexer::pop_bang(size_t bangValue)
{
    bang_depth = bangValue;
}

//
//	Push a bang context onto the error suppression stack, returning the context for restoration by pop_bang.
//
size_t CxxLexer::push_bang()
{
    return bang_depth++;
}

//
//	Reposition the input to restart at the position returned by a mark().
//
void CxxLexer::remark(size_t anIndex)
{
    tokenReadIndex = anIndex;
}

//
//	Reposition the input to restart at the position returned by a mark().
//
void CxxLexer::remark_type1(size_t anIndex)
{
    remark(anIndex);
    in_type1 = false;
}

//
//	Rewind the input stream back to anIndex and force a : prior to resuming input.
//
void CxxLexer::rewind_colon(size_t anIndex, const CxxToken *aToken)
{
    remark(anIndex);
    unmark();
    primed_tokens[0] = CxxToken::colonToken;
    primed_tokens[1] = static_cast<CxxParser::semantic_type*>(_yylval)->token;
}

//
//	Start a new binary search over the template/arithmetic alternative parses of a statement.
//	Marks the current position and saves it in a binary search context maintained on a private stack.
//
void CxxLexer::start_search(bool enableType1)
{
    bool type1Enabled = !CxxSearchContext::current() || CxxSearchContext::current()->enable_type1() ? true : false;
    CxxSearchContext::start(mark(), enableType1 && type1Enabled ? true : false, m_pDriver);
}

//
//	Determine whether the just parsed < should be interpreted as a template or arithmetic operator.
//	The implementation here intersacts with a binary search to traverse all possibilities in
//	multiple passes. The search proceeds by branch and bound presuming the template interpretation.
//	A true token is forced into the input stream to take the template interpretaion. A false token
//	otherwise.
//
//	An alternate implementation that keeps track of scopes may interact with semantic knowledge to make
//	the correct decision directly.
//
void CxxLexer::template_test()
{
    if (!CxxSearchContext::current() || CxxSearchContext::current()->is_template())
    {
        primed_tokens[0] = CxxToken::plusToken;
        primed_tokens[1] = 0;
    }
    else
    {
        primed_tokens[0] = CxxToken::minusToken;
        primed_tokens[1] = CxxToken::angleToken;
    }
}

void CxxLexer::token_put(CxxToken *aToken)
{
    if (!tokenBuffer || !tokenSize)
        tokenBuffer = new CxxToken *[tokenSize = 256];
    else if (tokenWriteIndex >= tokenSize)
    {
        CxxToken **oldTokenBuffer = tokenBuffer;
        size_t oldTokenSize = tokenSize;
        tokenBuffer = new CxxToken *[tokenSize *= 2];
        memcpy(tokenBuffer, oldTokenBuffer, oldTokenSize * sizeof(*oldTokenBuffer));
        delete[] oldTokenBuffer;
    }
    tokenBuffer[tokenWriteIndex++] = aToken;
    tokenReadIndex = tokenWriteIndex;
}

//
//	Pop a marked context off the stack.
//
void CxxLexer::unmark(const CxxToken *aToken)
{
    if (bang_depth)
        bang_depth--;
    else
        ERRMSG("BUG - should not unmark with 0 bang.");
    if (tokenMarkDepth <= 0)
        ERRMSG("Unexpected unmark.");
    else
        tokenMarkDepth--;
}

void CxxLexer::error(const char *s)
{
    if (!bang_depth && (tokenMarkDepth == 0))
    {
        std::cout << s << std::endl;
        increment_error_count();
    }
    else
    {
        if (show_marked)
            std::cout << "Marked " << s << std::endl;		
        marked_error_count++;
    }
}

//
//	Get the next token for the parser, invoking yylex_token to get the next token from the lexer.
//	This routine gets renamed to buffered_yylex by a #define when using yacc so that the two purposes
//	above are split allowing lookahead buffering and primimimg to occur.
//
int CxxLexer::lex(CxxParser::semantic_type* yylval, CxxParser::location_type* yylloc)
{
    this->_yylval = yylval;
//     if(CxxDriver::Instance()->waitForExpressionParsingStart())
//     {
//         CxxDriver::Instance()->setExpressionParsingStarted();
//         yylval->token = CxxToken::dollarToken;
//         return yylval->token->value();
//     }
    CxxToken *aToken = primed_tokens[0];
    if (aToken)
    {
        primed_tokens[0] = primed_tokens[1];
        primed_tokens[1] = primed_tokens[2];
        primed_tokens[2] = 0;
    }
    else if (tokenReadIndex < tokenWriteIndex)
    {
        aToken = tokenBuffer[tokenReadIndex++];
    }
    else
    {
        aToken = (!_lex(yylval, yylloc)) ? 0 : CxxToken::yyToken;
        if (!aToken)
            return 0;
        if (tokenMarkDepth > 0)
            token_put(aToken);
        else
        {
            tokenWriteIndex = 0;
            tokenReadIndex = 0;
        }
    }
    yylval->token = aToken;
    return aToken->value();
}

}