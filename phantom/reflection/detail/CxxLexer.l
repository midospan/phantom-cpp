/*
 *	  Title:			Miniature lexer for C++ parser.
 *
 *	  File Name:		CxxLexer.l
 *
 *	  Author:			E.D.Willink
 *
 *	This is a complete lexer for C++, intended for use with CxxParser.y.
 *	All actions are done by macros, so that there is some chance that customisation
 *	can be performed within the bounds of the CxxLexing.hxx and CxxLexing.cxx
 *	include files.
 *END
 */
%{
#include "CxxLexer.h"
#include "CxxParser.h"

/* By default yylex returns int, we use token_type. Unfortunately yyterminate
 * by default returns 0, which is not of token_type. */
#define yyterminate() return YY_NULL

%}

/*** Flex Declarations and Options ***/

/* enable c++ scanner class generation */
%option c++

/* change the name of the scanner class. results in "ExampleFlexLexer" */
%option prefix="Cxx"

/* the manual says "somewhat more optimized" */
%option batch

/* enable scanner to generate debug output. disable this for release
 * versions. */
%option debug

/* no support for include files is planned */
%option yywrap nounput 

/* enables the use of start condition stacks */
%option stack

/* The following paragraph suffices to track locations accurately. Each time
 * yylex is invoked, the begin position is moved onto the end position. */
%{
#define YY_USER_ACTION  \
		yylloc->columns(yyleng); \
		yy_register_location(*yylloc, yyleng);\
		
#define YY_CURRENT_BUFFER ( (yy_buffer_stack) \
                          ? (yy_buffer_stack)[(yy_buffer_stack_top)] \
                          : NULL)
%}

%a 5000
%e 1500
%n 1000
%o 10000
%p 10000
ws								[ \f\v\t]

digit							[0-9]
hex								[0-9A-Fa-f]
letter							[A-Z_a-z]
simple_escape_sequence			(\\\'|\\\"|\\\?|\\\\|\\a|\\b|\\f|\\n|\\r|\\t|\\v)
octal_escape_sequence			(\\[0-7]|\\[0-7][0-7]|\\[0-7][0-7][0-7])
hexadecimal_escape_sequence		(\\x{hex}+)
escape_sequence					({simple_escape_sequence}|{octal_escape_sequence}|{hexadecimal_escape_sequence})
universal_character_name		(\\u{hex}{hex}{hex}{hex}|\\U{hex}{hex}{hex}{hex}{hex}{hex}{hex}{hex})
non_digit						({letter}|{universal_character_name})
identifier						({non_digit}({non_digit}|{digit})*)

character_lit					(L?\'([^\'\\\n]|\\.)*)
character_literal				({character_lit}\')

string_lit						(L?\"([^\"\\\n]|\\.)*)
string_literal					({string_lit}\")

hex_number                      0[xX]{hex}+
longdouble_number               (({digit}+\.{digit}*([eE][-+]?{digit}+)?)|(\.{digit}+([eE][-+]?{digit}+)?))L
double_number                   (({digit}+\.{digit}*([eE][-+]?{digit}+)?)|(\.{digit}+([eE][-+]?{digit}+)?))
float_number                    (({digit}+\.{digit}*([eE][-+]?{digit}+)?)|(\.{digit}+([eE][-+]?{digit}+)?))f
uint_number                     {digit}+     
ulong_number                    {digit}+U?L
ulonglong_number                {digit}+U?LL


%%
^.*\n							{ LEX_SAVE_LINE(yytext, yyleng); REJECT; }
^{ws}*"#".*						{ /* Throw away preprocessor lines - hopefully only #line and equivalent. */ }

{character_lit}\'				{ LEX_CHARACTER_TOKEN(yytext, yyleng-1); };
{character_lit}\\				{ ERRMSG("End of line assumed to terminate character with trailing escape.");
								  LEX_CHARACTER_TOKEN(yytext, yyleng-1); };
{character_lit}					{ ERRMSG("End of line assumed to terminate character.");
								  LEX_CHARACTER_TOKEN(yytext, yyleng); };

{string_lit}\"					{ LEX_STRING_TOKEN(yytext, yyleng-1); };
{string_lit}\\					{ ERRMSG("End of line assumed to terminate string with trailing escape.");
								  LEX_STRING_TOKEN(yytext, yyleng-1); };
{string_lit}					{ ERRMSG("End of line assumed to terminate string.");
								  LEX_STRING_TOKEN(yytext, yyleng); };

"asm"							{ LEX_KEYWORD_TOKEN(ASM); }
"auto"							{ LEX_KEYWORD_TOKEN(AUTO); }
"bool"							{ LEX_KEYWORD_TOKEN(BOOL); }
"break"							{ LEX_KEYWORD_TOKEN(BREAK); }
"case"							{ LEX_KEYWORD_TOKEN(CASE); }
"catch"							{ LEX_KEYWORD_TOKEN(CATCH); }
"char"							{ LEX_KEYWORD_TOKEN(CHAR); }
"class"							{ LEX_KEYWORD_TOKEN(CLASS); }
"const"							{ LEX_KEYWORD_TOKEN(CONST); }
"const_cast"					{ LEX_KEYWORD_TOKEN(CONST_CAST); }
"continue"						{ LEX_KEYWORD_TOKEN(CONTINUE); }
"default"						{ LEX_KEYWORD_TOKEN(DEFAULT); }
"delete"						{ LEX_KEYWORD_TOKEN(DELETE); }
"do"							{ LEX_KEYWORD_TOKEN(DO); }
"double"						{ LEX_KEYWORD_TOKEN(DOUBLE); }
"dynamic_cast"					{ LEX_KEYWORD_TOKEN(DYNAMIC_CAST); }
"else"							{ LEX_KEYWORD_TOKEN(ELSE); }
"enum"							{ LEX_KEYWORD_TOKEN(ENUM); }
"explicit"						{ LEX_KEYWORD_TOKEN(EXPLICIT); }
"export"						{ LEX_KEYWORD_TOKEN(EXPORT); }
"extern"						{ LEX_KEYWORD_TOKEN(EXTERN); }
"false"							{ LEX_KEYWORD_TOKEN(FALSE); }
"float"							{ LEX_KEYWORD_TOKEN(FLOAT); }
"for"							{ LEX_KEYWORD_TOKEN(FOR); }
"friend"						{ LEX_KEYWORD_TOKEN(FRIEND); }
"goto"							{ LEX_KEYWORD_TOKEN(GOTO); }
"if"							{ LEX_KEYWORD_TOKEN(IF); }
"inline"						{ LEX_KEYWORD_TOKEN(INLINE); }
"int"							{ LEX_KEYWORD_TOKEN(INT); }
"long"							{ LEX_KEYWORD_TOKEN(LONG); }
"mutable"						{ LEX_KEYWORD_TOKEN(MUTABLE); }
"namespace"						{ LEX_KEYWORD_TOKEN(NAMESPACE); }
"new"							{ LEX_KEYWORD_TOKEN(NEW); }
"operator"						{ LEX_KEYWORD_TOKEN(OPERATOR); }
"private"						{ LEX_KEYWORD_TOKEN(PRIVATE); }
"protected"						{ LEX_KEYWORD_TOKEN(PROTECTED); }
"public"						{ LEX_KEYWORD_TOKEN(PUBLIC); }
"register"						{ LEX_KEYWORD_TOKEN(REGISTER); }
"reinterpret_cast"				{ LEX_KEYWORD_TOKEN(REINTERPRET_CAST); }
"return"						{ LEX_KEYWORD_TOKEN(RETURN); }
"short"							{ LEX_KEYWORD_TOKEN(SHORT); }
"signed"						{ LEX_KEYWORD_TOKEN(SIGNED); }
"sizeof"						{ LEX_KEYWORD_TOKEN(SIZEOF); }
"static"						{ LEX_KEYWORD_TOKEN(STATIC); }
"static_cast"					{ LEX_KEYWORD_TOKEN(STATIC_CAST); }
"struct"						{ LEX_KEYWORD_TOKEN(STRUCT); }
"switch"						{ LEX_KEYWORD_TOKEN(SWITCH); }
"template"						{ LEX_KEYWORD_TOKEN(TEMPLATE); }
"this"							{ LEX_KEYWORD_TOKEN(THIS); }
"throw"							{ LEX_KEYWORD_TOKEN(THROW); }
"true"							{ LEX_KEYWORD_TOKEN(TRUE); }
"try"							{ LEX_KEYWORD_TOKEN(TRY); }
"typedef"						{ LEX_KEYWORD_TOKEN(TYPEDEF); }
"typeid"						{ LEX_KEYWORD_TOKEN(TYPEID); }
"typename"						{ LEX_KEYWORD_TOKEN(TYPENAME); }
"union"							{ LEX_KEYWORD_TOKEN(UNION); }
"unsigned"						{ LEX_KEYWORD_TOKEN(UNSIGNED); }
"using"							{ LEX_KEYWORD_TOKEN(USING); }
"virtual"						{ LEX_KEYWORD_TOKEN(VIRTUAL); }
"void"							{ LEX_KEYWORD_TOKEN(VOID); }
"volatile"						{ LEX_KEYWORD_TOKEN(VOLATILE); }
"wchar_t"						{ LEX_KEYWORD_TOKEN(WCHAR_T); }
"while"							{ LEX_KEYWORD_TOKEN(WHILE); }

"::"							{ LEX_STATIC_TOKEN(SCOPE); }
"..."							{ LEX_STATIC_TOKEN(ELLIPSIS); }
"<<"							{ LEX_STATIC_TOKEN(SHL); }
">>"							{ LEX_STATIC_TOKEN(SHR); }
"=="							{ LEX_STATIC_TOKEN(EQ); }
"!="							{ LEX_STATIC_TOKEN(NE); }
"<="							{ LEX_STATIC_TOKEN(LE); }
">="							{ LEX_STATIC_TOKEN(GE); }
"&&"							{ LEX_STATIC_TOKEN(LOG_AND); }
"||"							{ LEX_STATIC_TOKEN(LOG_OR); }
"++"							{ LEX_STATIC_TOKEN(INC); }
"--"							{ LEX_STATIC_TOKEN(DEC); }
"->*"							{ LEX_STATIC_TOKEN(ARROW_STAR); }
"->"							{ LEX_STATIC_TOKEN(ARROW); }
".*"							{ LEX_STATIC_TOKEN(DOT_STAR); }
"+="							{ LEX_STATIC_TOKEN(ASS_ADD); }
"-="							{ LEX_STATIC_TOKEN(ASS_SUB); }
"*="							{ LEX_STATIC_TOKEN(ASS_MUL); }
"/="							{ LEX_STATIC_TOKEN(ASS_DIV); }
"%="							{ LEX_STATIC_TOKEN(ASS_MOD); }
"^="							{ LEX_STATIC_TOKEN(ASS_XOR); }
"&="							{ LEX_STATIC_TOKEN(ASS_AND); }
"|="							{ LEX_STATIC_TOKEN(ASS_OR); }
">>="							{ LEX_STATIC_TOKEN(ASS_SHR); }
"<<="							{ LEX_STATIC_TOKEN(ASS_SHL); }

{hex_number}                    { LEX_HEX_NUMBER_TOKEN(yytext, yyleng); }
{longdouble_number}             { LEX_LONGDOUBLE_NUMBER_TOKEN(yytext, yyleng); }
{double_number}                 { LEX_DOUBLE_NUMBER_TOKEN(yytext, yyleng); }
{float_number}                  { LEX_FLOAT_NUMBER_TOKEN(yytext, yyleng); }
{uint_number}                   { LEX_UINT_NUMBER_TOKEN(yytext, yyleng); }
{ulong_number}                  { LEX_ULONG_NUMBER_TOKEN(yytext, yyleng); }
{ulonglong_number}              { LEX_ULONGLONG_NUMBER_TOKEN(yytext, yyleng); }






{identifier}					{ LEX_IDENTIFIER_TOKEN(yytext, yyleng); }

{escape_sequence}				|
{universal_character_name}		{ LEX_ESCAPED_TOKEN(yytext, yyleng); }

\n								|
{ws}+							{ /* Throw away whitespace */ }
.								{ LEX_ASCII_TOKEN(yytext[0]); }

%%
/*** Additional Code ***/

namespace phantom {

CxxLexer::CxxLexer(std::istream* in,
		 std::ostream* out)
    : CxxFlexLexer(in, out)
{
    bang_depth = 0;
    error_count = 0;
    marked_error_count = 0;
    in_type1 = false;
    show_marked = false;
    primed_tokens[0] = 0; primed_tokens[1] = 0; primed_tokens[2] = 0;
    tokenMarkDepth = 0;
    tokenWriteIndex = 0;
    tokenSize = 0;
    tokenReadIndex = 0;
    tokenBuffer = nullptr;
    _yychar = nullptr;
    _yylval = nullptr;
    CxxToken::yyToken = nullptr;
}

CxxLexer::~CxxLexer()
{
    delete[] tokenBuffer;
}

void CxxLexer::set_debug(bool b)
{
    yy_flex_debug = b;
}

}

/* This implementation of ExampleFlexLexer::yylex() is required to fill the
 * vtable of the class ExampleFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Scanner class instead. */

#ifdef yylex
#undef yylex
#endif

int CxxFlexLexer::yylex()
{
   // std::cerr << "in ExampleFlexLexer::yylex() !" << std::endl;
    return 0;
}

/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */

int CxxFlexLexer::yywrap()
{
    return 1;
}
