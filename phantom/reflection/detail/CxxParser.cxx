/* A Bison parser, made by GNU Bison 2.7.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

// Take the name prefix into account.
#define yylex   phantomlex

/* First part of user declarations.  */


#include "CxxToken.h"
#include "CxxLexer.h"
#include "CxxParser.hxx"
#include "CxxTokenizer.h"
#include "CxxDriver.h"

#define yylex2(a,b) m_pDriver->getLexer()->lex(a,b); m_pDriver->getLexer()->setYYChar(&yychar)
#undef yylex
#define yylex yylex2
#undef yyerror
#define yyerror m_pDriver->getLexer()->error




#include "CxxParser.hxx"

/* User implementation prologue.  */




# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location) YYUSE(Type)
# define YY_REDUCE_PRINT(Rule)        static_cast<void>(0)
# define YY_STACK_PRINT()             static_cast<void>(0)

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace phantom {


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  CxxParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  CxxParser::CxxParser (class CxxDriver* m_pDriver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      m_pDriver (m_pDriver_yyarg)
  {
  }

  CxxParser::~CxxParser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  CxxParser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    std::ostream& yyo = debug_stream ();
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  CxxParser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  CxxParser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
  
	default:
	  break;
      }
  }

  void
  CxxParser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  CxxParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  CxxParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  CxxParser::debug_level_type
  CxxParser::debug_level () const
  {
    return yydebug_;
  }

  void
  CxxParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  inline bool
  CxxParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  CxxParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  CxxParser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    // State.
    int yyn;
    int yylen = 0;
    int yystate = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    static semantic_type yyval_default;
    semantic_type yylval = yyval_default;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[3];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


/* User initialization code.  */

{
    // initialize the initial location object
    yylloc.begin.filename = yylloc.end.filename = m_pDriver->getFileName();
}


    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
        YYCDEBUG << "Reading a token: ";
        yychar = yylex (&yylval, &yylloc);
      }

    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yy_table_value_is_error_ (yyn))
	  goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    // Compute the default @$.
    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }

    // Perform the reduction.
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
          case 2:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].identifier); }
    break;

  case 3:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 4:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 14:

    { (yyval.name) = YACC_NAME((yysemantic_stack_[(4) - (3)].keyword)); }
    break;

  case 15:

    { (yyval.name) = YACC_NAME((yysemantic_stack_[(1) - (1)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 16:

    { (yyval.name) = YACC_TEMPLATE_NAME((yysemantic_stack_[(5) - (1)].name), (yysemantic_stack_[(5) - (4)].template_arguments)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 17:

    { (yyval.name) = (yysemantic_stack_[(4) - (1)].name); ERRMSG("Empty template-argument-list"); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 18:

    { (yyval.name) = YACC_NAME((yysemantic_stack_[(3) - (1)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 20:

    { m_pDriver->getLexer()->template_test(); }
    break;

  case 21:

    { (yyval.is_template) = IS_DEFAULT; }
    break;

  case 22:

    { (yyval.is_template) = IS_TEMPLATE; }
    break;

  case 23:

    { (yyval.name) = YACC_NESTED_SCOPE((yysemantic_stack_[(2) - (1)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 25:

    { (yyval.name) = YACC_NESTED_ID((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 26:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 27:

    { (yyval.name) = YACC_GLOBAL_ID((yysemantic_stack_[(2) - (1)].is_template), (yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 28:

    { (yyval.name) = YACC_DESTRUCTOR_ID((yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 29:

    { (yyval.name) = YACC_SET_TEMPLATE_ID((yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 30:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 31:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 32:

    { (yyval.name) = YACC_SET_TEMPLATE_ID((yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 33:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 34:

    { (yyval.name) = YACC_NESTED_ID((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 35:

    { (yyval.name) = YACC_NESTED_ID((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 36:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 37:

    { (yyval.name) = YACC_GLOBAL_ID((yysemantic_stack_[(2) - (1)].is_template), (yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 38:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 39:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 40:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 42:

    { (yyval.built_in_id) = YACC_BUILT_IN_IDS((yysemantic_stack_[(2) - (1)].built_in_id), (yysemantic_stack_[(2) - (2)].built_in_id)); YY_LOC((yyval.built_in_id), (yyloc)); }
    break;

  case 43:

    { (yyval.name) = YACC_PSEUDO_DESTRUCTOR_ID((yysemantic_stack_[(4) - (1)].built_in_id), (yysemantic_stack_[(4) - (4)].built_in_id)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 44:

    { (yyval.name) = YACC_PSEUDO_DESTRUCTOR_ID(0, (yysemantic_stack_[(2) - (2)].built_in_id)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 45:

    { (yyval.name) = YACC_SET_TEMPLATE_ID((yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 46:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 47:

    { (yyval.name) = YACC_NESTED_ID((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 48:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 49:

    { (yyval.name) = YACC_GLOBAL_ID((yysemantic_stack_[(2) - (1)].is_template), (yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 50:

    { (yyval.strings) = (yysemantic_stack_[(1) - (1)].string_literal); }
    break;

  case 51:

    { (yyval.expression) = YACC_HEX_LITERAL_EXPRESSION((yysemantic_stack_[(1) - (1)].hex_literal)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 52:

    { (yyval.expression) = YACC_LONGDOUBLE_LITERAL_EXPRESSION((yysemantic_stack_[(1) - (1)].longdouble_literal)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 53:

    { (yyval.expression) = YACC_DOUBLE_LITERAL_EXPRESSION((yysemantic_stack_[(1) - (1)].double_literal)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 54:

    { (yyval.expression) = YACC_FLOAT_LITERAL_EXPRESSION((yysemantic_stack_[(1) - (1)].float_literal)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 55:

    { (yyval.expression) = YACC_UINT_LITERAL_EXPRESSION((yysemantic_stack_[(1) - (1)].uint_literal)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 56:

    { (yyval.expression) = YACC_ULONG_LITERAL_EXPRESSION((yysemantic_stack_[(1) - (1)].ulong_literal)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 57:

    { (yyval.expression) = YACC_ULONGLONG_LITERAL_EXPRESSION((yysemantic_stack_[(1) - (1)].ulonglong_literal)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 58:

    { (yyval.expression) = YACC_CHARACTER_LITERAL_EXPRESSION((yysemantic_stack_[(1) - (1)].character_literal)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 59:

    { (yyval.expression) = YACC_STRING_LITERAL_EXPRESSION((yysemantic_stack_[(1) - (1)].strings)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 60:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 61:

    { (yyval.expression) = YACC_FALSE_EXPRESSION(); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 62:

    { (yyval.expression) = YACC_TRUE_EXPRESSION(); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 63:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 64:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 65:

    { (yyval.expression) = YACC_DECL_SPECIFIER_EXPRESSION((yysemantic_stack_[(2) - (2)].expression), (yysemantic_stack_[(2) - (1)].decl_specifier_id)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 66:

    { YACC_TRANSLATION_UNIT((yysemantic_stack_[(1) - (1)].declarations)); }
    break;

  case 67:

    { YACC_SINGLE_EXPRESSION((yysemantic_stack_[(4) - (3)].expression)); m_pDriver->getLexer()->end_search((yysemantic_stack_[(4) - (3)].expression)); }
    break;

  case 69:

    { (yyval.expression) = YACC_THIS_EXPRESSION(); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 70:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 71:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 72:

    { (yyval.expression) = YACC_ABSTRACT_FUNCTION_EXPRESSION((yysemantic_stack_[(1) - (1)].parenthesised)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 73:

    { (yyval.expression) = YACC_ABSTRACT_ARRAY_EXPRESSION((yysemantic_stack_[(3) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 74:

    { (yyval.expression) = YACC_SET_TEMPLATE_EXPRESSION(YACC_ABSTRACT_FUNCTION_EXPRESSION((yysemantic_stack_[(2) - (2)].parenthesised))); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 75:

    { (yyval.type1_parameters) = YACC_TYPE1_PARAMETERS(0, (yysemantic_stack_[(2) - (1)].parameters)); YY_LOC((yyval.type1_parameters), (yyloc)); }
    break;

  case 76:

    { (yyval.type1_parameters) = YACC_TYPE1_PARAMETERS((yysemantic_stack_[(3) - (1)].type1_parameters), (yysemantic_stack_[(3) - (2)].parameters)); YY_LOC((yyval.type1_parameters), (yyloc)); }
    break;

  case 77:

    { (yyval.mark) = m_pDriver->getLexer()->mark_type1(); yyclearin; }
    break;

  case 78:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 79:

    { (yyval.expression) = YACC_CALL_EXPRESSION((yysemantic_stack_[(4) - (1)].expression), (yysemantic_stack_[(4) - (2)].parenthesised)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 80:

    { yyerrok; yyclearin; m_pDriver->getLexer()->remark_type1((yysemantic_stack_[(8) - (6)].mark)); m_pDriver->getLexer()->unmark(); m_pDriver->getLexer()->unmark((yysemantic_stack_[(8) - (5)].type1_parameters)); (yyval.expression) = YACC_TYPE1_EXPRESSION((yysemantic_stack_[(8) - (1)].expression), (yysemantic_stack_[(8) - (2)].parenthesised), (yysemantic_stack_[(8) - (5)].type1_parameters)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 81:

    { yyerrok; yyclearin; m_pDriver->getLexer()->remark_type1((yysemantic_stack_[(7) - (3)].mark)); m_pDriver->getLexer()->unmark(); m_pDriver->getLexer()->unmark(); (yyval.expression) = YACC_CALL_EXPRESSION((yysemantic_stack_[(7) - (1)].expression), (yysemantic_stack_[(7) - (2)].parenthesised)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 82:

    { yyerrok; yyclearin; m_pDriver->getLexer()->remark_type1((yysemantic_stack_[(5) - (3)].mark)); m_pDriver->getLexer()->unmark(); (yyval.expression) = YACC_CALL_EXPRESSION((yysemantic_stack_[(5) - (1)].expression), (yysemantic_stack_[(5) - (2)].parenthesised)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 83:

    { (yyval.expression) = YACC_ARRAY_EXPRESSION((yysemantic_stack_[(4) - (1)].expression), (yysemantic_stack_[(4) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 84:

    { (yyval.expression) = YACC_DOT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].name)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 85:

    { (yyval.expression) = YACC_DOT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].name)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 86:

    { (yyval.expression) = YACC_ARROW_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].name)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 87:

    { (yyval.expression) = YACC_ARROW_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].name)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 88:

    { (yyval.expression) = YACC_POST_INCREMENT_EXPRESSION((yysemantic_stack_[(2) - (1)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 89:

    { (yyval.expression) = YACC_POST_DECREMENT_EXPRESSION((yysemantic_stack_[(2) - (1)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 90:

    { (yyval.expression) = YACC_DYNAMIC_CAST_EXPRESSION((yysemantic_stack_[(7) - (3)].expression), (yysemantic_stack_[(7) - (6)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 91:

    { (yyval.expression) = YACC_STATIC_CAST_EXPRESSION((yysemantic_stack_[(7) - (3)].expression), (yysemantic_stack_[(7) - (6)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 92:

    { (yyval.expression) = YACC_REINTERPRET_CAST_EXPRESSION((yysemantic_stack_[(7) - (3)].expression), (yysemantic_stack_[(7) - (6)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 93:

    { (yyval.expression) = YACC_CONST_CAST_EXPRESSION((yysemantic_stack_[(7) - (3)].expression), (yysemantic_stack_[(7) - (6)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 94:

    { (yyval.expression) = YACC_TYPEID_EXPRESSION((yysemantic_stack_[(2) - (2)].parameters)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 95:

    { (yyval.expressions) = YACC_EXPRESSIONS(0, 0); YY_LOC((yyval.expressions), (yyloc)); }
    break;

  case 96:

    { (yyval.expressions) = (yysemantic_stack_[(1) - (1)].expressions); }
    break;

  case 97:

    { (yyval.expressions) = YACC_EXPRESSIONS(0, (yysemantic_stack_[(1) - (1)].expression)); YY_LOC((yyval.expressions), (yyloc)); }
    break;

  case 98:

    { (yyval.expressions) = YACC_EXPRESSIONS((yysemantic_stack_[(3) - (1)].expressions), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expressions), (yyloc)); }
    break;

  case 99:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 100:

    { (yyval.expression) = YACC_PRE_INCREMENT_EXPRESSION((yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 101:

    { (yyval.expression) = YACC_PRE_DECREMENT_EXPRESSION((yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 102:

    { (yyval.expression) = YACC_POINTER_EXPRESSION((yysemantic_stack_[(2) - (1)].declarator), (yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 103:

    { (yyval.expression) = YACC_DATA_EXPRESSION((yysemantic_stack_[(2) - (2)].hex_literal)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 104:

    { (yyval.expression) = YACC_SCOPED_POINTER_EXPRESSION((yysemantic_stack_[(3) - (1)].name), (yysemantic_stack_[(3) - (2)].pointer_declarator), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 105:

    { (yyval.expression) = YACC_PLUS_EXPRESSION((yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 106:

    { (yyval.expression) = YACC_MINUS_EXPRESSION((yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 107:

    { (yyval.expression) = YACC_NOT_EXPRESSION((yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 108:

    { (yyval.expression) = YACC_COMPLEMENT_EXPRESSION((yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 109:

    { (yyval.expression) = YACC_SIZEOF_EXPRESSION((yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 110:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].new_expression); }
    break;

  case 111:

    { (yyval.expression) = YACC_GLOBAL_EXPRESSION((yysemantic_stack_[(2) - (1)].is_template), (yysemantic_stack_[(2) - (2)].new_expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 112:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].delete_expression); }
    break;

  case 113:

    { (yyval.expression) = YACC_GLOBAL_EXPRESSION((yysemantic_stack_[(2) - (1)].is_template), (yysemantic_stack_[(2) - (2)].delete_expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 114:

    { (yyval.delete_expression) = YACC_DELETE_EXPRESSION((yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.delete_expression), (yyloc)); }
    break;

  case 115:

    { (yyval.new_expression) = YACC_NEW_TYPE_ID_EXPRESSION(0, (yysemantic_stack_[(3) - (2)].expression), (yysemantic_stack_[(3) - (3)].expressions)); YY_LOC((yyval.new_expression), (yyloc)); }
    break;

  case 116:

    { (yyval.new_expression) = YACC_NEW_TYPE_ID_EXPRESSION((yysemantic_stack_[(4) - (2)].parameters), (yysemantic_stack_[(4) - (3)].expression), (yysemantic_stack_[(4) - (4)].expressions)); YY_LOC((yyval.new_expression), (yyloc)); }
    break;

  case 117:

    { (yyval.new_expression) = YACC_NEW_EXPRESSION((yysemantic_stack_[(2) - (2)].parameters), 0, 0); YY_LOC((yyval.new_expression), (yyloc)); }
    break;

  case 118:

    { (yyval.new_expression) = YACC_NEW_EXPRESSION((yysemantic_stack_[(4) - (2)].parameters), (yysemantic_stack_[(4) - (3)].parameters), (yysemantic_stack_[(4) - (4)].expressions)); YY_LOC((yyval.new_expression), (yyloc)); }
    break;

  case 119:

    { (yyval.expression) = YACC_TYPED_EXPRESSION((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 120:

    { (yyval.expression) = YACC_TYPED_EXPRESSION((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 121:

    { (yyval.expression) = YACC_TYPED_EXPRESSION((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 122:

    { (yyval.expression) = YACC_POINTER_EXPRESSION((yysemantic_stack_[(2) - (1)].declarator), (yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 123:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 124:

    { (yyval.expression) = YACC_ABSTRACT_ARRAY_EXPRESSION((yysemantic_stack_[(3) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 125:

    { (yyval.expression) = YACC_ARRAY_EXPRESSION((yysemantic_stack_[(4) - (1)].expression), (yysemantic_stack_[(4) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 126:

    { (yyval.expressions) = YACC_EXPRESSIONS(0, 0); YY_LOC((yyval.expressions), (yyloc)); }
    break;

  case 127:

    { (yyval.expressions) = (yysemantic_stack_[(3) - (2)].expressions); }
    break;

  case 128:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 129:

    { (yyval.expression) = YACC_CAST_EXPRESSION((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 130:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 131:

    { (yyval.expression) = YACC_DOT_STAR_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 132:

    { (yyval.expression) = YACC_ARROW_STAR_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 133:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 134:

    { (yyval.expression) = YACC_MULTIPLY_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (2)].pointer_declarator), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 135:

    { (yyval.expression) = YACC_DIVIDE_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 136:

    { (yyval.expression) = YACC_MODULUS_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 137:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 138:

    { (yyval.expression) = YACC_ADD_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 139:

    { (yyval.expression) = YACC_SUBTRACT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 140:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 141:

    { (yyval.expression) = YACC_SHIFT_LEFT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 142:

    { (yyval.expression) = YACC_SHIFT_RIGHT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 143:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 144:

    { (yyval.expression) = YACC_LESS_THAN_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 145:

    { (yyval.expression) = YACC_GREATER_THAN_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 146:

    { (yyval.expression) = YACC_LESS_EQUAL_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 147:

    { (yyval.expression) = YACC_GREATER_EQUAL_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 148:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 149:

    { (yyval.expression) = YACC_EQUAL_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 150:

    { (yyval.expression) = YACC_NOT_EQUAL_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 151:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 152:

    { (yyval.expression) = YACC_AND_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 153:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 154:

    { (yyval.expression) = YACC_EXCLUSIVE_OR_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 155:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 156:

    { (yyval.expression) = YACC_INCLUSIVE_OR_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 157:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 158:

    { (yyval.expression) = YACC_LOGICAL_AND_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 159:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 160:

    { (yyval.expression) = YACC_LOGICAL_OR_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 161:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 162:

    { (yyval.expression) = YACC_CONDITIONAL_EXPRESSION((yysemantic_stack_[(5) - (1)].expression), (yysemantic_stack_[(5) - (3)].expression), (yysemantic_stack_[(5) - (5)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 163:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 164:

    { (yyval.expression) = YACC_ASSIGNMENT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (2)].keyword), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 165:

    { (yyval.expression) = YACC_ASSIGNMENT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (2)].keyword), (yysemantic_stack_[(3) - (3)].initializer_clause)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 166:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 178:

    { (yyval.expression) = YACC_EXPRESSION(0); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 179:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 180:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 181:

    { (yyval.expression) = YACC_EXPRESSION(YACC_EXPRESSIONS((yysemantic_stack_[(3) - (1)].expressions), (yysemantic_stack_[(3) - (3)].expression))); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 182:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 183:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 184:

    { (yyval.expression) = YACC_LESS_THAN_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 185:

    { (yyval.expression) = YACC_LESS_EQUAL_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 186:

    { (yyval.expression) = YACC_GREATER_EQUAL_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 187:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 188:

    { (yyval.expression) = YACC_EQUAL_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 189:

    { (yyval.expression) = YACC_NOT_EQUAL_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 190:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 191:

    { (yyval.expression) = YACC_AND_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 192:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 193:

    { (yyval.expression) = YACC_EXCLUSIVE_OR_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 194:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 195:

    { (yyval.expression) = YACC_INCLUSIVE_OR_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 196:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 197:

    { (yyval.expression) = YACC_LOGICAL_AND_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 198:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 199:

    { (yyval.expression) = YACC_LOGICAL_OR_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 200:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 201:

    { (yyval.expression) = YACC_CONDITIONAL_EXPRESSION((yysemantic_stack_[(5) - (1)].expression), (yysemantic_stack_[(5) - (3)].expression), (yysemantic_stack_[(5) - (5)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 202:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 203:

    { (yyval.expression) = YACC_ASSIGNMENT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (2)].keyword), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 204:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 205:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 206:

    { (yyval.expression) = YACC_EXPRESSION(YACC_EXPRESSIONS((yysemantic_stack_[(3) - (1)].expressions), (yysemantic_stack_[(3) - (3)].expression))); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 207:

    { (yyval.expressions) = YACC_EXPRESSIONS(0, (yysemantic_stack_[(1) - (1)].expression)); YY_LOC((yyval.expressions), (yyloc)); }
    break;

  case 208:

    { (yyval.expressions) = YACC_EXPRESSIONS((yysemantic_stack_[(3) - (1)].expressions), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expressions), (yyloc)); }
    break;

  case 209:

    { (yyval.statement) = YACC_LINED_STATEMENT((yysemantic_stack_[(2) - (2)].statement), (yysemantic_stack_[(2) - (1)].line)); YY_LOC((yyval.statement), (yyloc)); m_pDriver->getLexer()->end_search((yyval.statement)); }
    break;

  case 210:

    { (yyval.statement) = (yysemantic_stack_[(1) - (1)].statement); }
    break;

  case 211:

    { (yyval.statement) = (yysemantic_stack_[(3) - (3)].statement); YY_LOC((yyval.statement), (yylocation_stack_[(3) - (3)])); }
    break;

  case 212:

    { (yyval.statement) = 0; }
    break;

  case 213:

    { (yyval.statement) = (yysemantic_stack_[(1) - (1)].statement); }
    break;

  case 214:

    { (yyval.statement) = (yysemantic_stack_[(1) - (1)].statement); }
    break;

  case 215:

    { (yyval.statement) = (yysemantic_stack_[(1) - (1)].statement); }
    break;

  case 216:

    { (yyval.statement) = YACC_TRY_BLOCK_STATEMENT((yysemantic_stack_[(1) - (1)].function_body)); YY_LOC((yyval.statement), (yyloc)); }
    break;

  case 217:

    { (yyval.statement) = (yysemantic_stack_[(1) - (1)].statement); }
    break;

  case 218:

    { (yyval.statement) = (yysemantic_stack_[(1) - (1)].statement); }
    break;

  case 219:

    { (yyval.statement) = (yysemantic_stack_[(1) - (1)].statement); }
    break;

  case 220:

    { (yyval.statement) = (yysemantic_stack_[(1) - (1)].statement); }
    break;

  case 221:

    { (yyval.statement) = YACC_LABEL_STATEMENT((yysemantic_stack_[(3) - (1)].name), (yysemantic_stack_[(3) - (3)].statement)); YY_LOC((yyval.statement), (yyloc)); }
    break;

  case 222:

    { (yyval.statement) = YACC_CASE_STATEMENT((yysemantic_stack_[(4) - (2)].expression), (yysemantic_stack_[(4) - (4)].statement)); YY_LOC((yyval.statement), (yyloc)); }
    break;

  case 223:

    { (yyval.statement) = YACC_DEFAULT_STATEMENT((yysemantic_stack_[(3) - (3)].statement)); YY_LOC((yyval.statement), (yyloc)); }
    break;

  case 224:

    { (yyval.statement) = YACC_COMPOUND_STATEMENT((yysemantic_stack_[(3) - (2)].statements)); YY_LOC((yyval.statement), (yyloc)); }
    break;

  case 225:

    { (yyval.statement) = (yysemantic_stack_[(7) - (2)].statements); YY_LOC((yyval.statement), (yylocation_stack_[(7) - (2)])); YACC_UNBANG((yysemantic_stack_[(7) - (5)].bang), "Bad statement-seq."); }
    break;

  case 226:

    { (yyval.statements) = YACC_STATEMENTS(0, 0); YY_LOC((yyval.statements), (yyloc)); }
    break;

  case 227:

    { (yyval.statements) = YACC_STATEMENTS((yysemantic_stack_[(2) - (1)].statements), YACC_COMPILE_STATEMENT((yysemantic_stack_[(2) - (2)].statement))); YY_LOC((yyval.statements), (yyloc)); }
    break;

  case 228:

    { (yyval.statements) = (yysemantic_stack_[(6) - (1)].statements); YACC_UNBANG((yysemantic_stack_[(6) - (4)].bang), "Bad statement."); }
    break;

  case 229:

    { (yyval.statement) = YACC_IF_STATEMENT((yysemantic_stack_[(5) - (3)].condition), (yysemantic_stack_[(5) - (5)].statement), 0); YY_LOC((yyval.statement), (yyloc)); }
    break;

  case 230:

    { (yyval.statement) = YACC_IF_STATEMENT((yysemantic_stack_[(7) - (3)].condition), (yysemantic_stack_[(7) - (5)].statement), (yysemantic_stack_[(7) - (7)].statement)); YY_LOC((yyval.statement), (yyloc)); }
    break;

  case 231:

    { (yyval.statement) = YACC_SWITCH_STATEMENT((yysemantic_stack_[(5) - (3)].condition), (yysemantic_stack_[(5) - (5)].statement)); YY_LOC((yyval.statement), (yyloc)); }
    break;

  case 232:

    { (yyval.condition) = YACC_CONDITION(0); }
    break;

  case 233:

    { (yyval.condition) = (yysemantic_stack_[(1) - (1)].condition); }
    break;

  case 234:

    { (yyval.condition) = YACC_CONDITION((yysemantic_stack_[(1) - (1)].parameters)); YY_LOC((yyval.condition), (yyloc)); }
    break;

  case 235:

    { (yyval.statement) = YACC_WHILE_STATEMENT((yysemantic_stack_[(5) - (3)].condition), (yysemantic_stack_[(5) - (5)].statement)); YY_LOC((yyval.statement), (yyloc)); }
    break;

  case 236:

    { (yyval.statement) = YACC_DO_WHILE_STATEMENT((yysemantic_stack_[(7) - (2)].statement), (yysemantic_stack_[(7) - (5)].expression)); YY_LOC((yyval.statement), (yyloc)); }
    break;

  case 237:

    { (yyval.statement) = YACC_FOR_STATEMENT((yysemantic_stack_[(8) - (3)].expression), (yysemantic_stack_[(8) - (4)].condition), (yysemantic_stack_[(8) - (6)].expression), (yysemantic_stack_[(8) - (8)].statement)); YY_LOC((yyval.statement), (yyloc)); }
    break;

  case 238:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 239:

    { (yyval.statement) = YACC_BREAK_STATEMENT(); YY_LOC((yyval.statement), (yyloc)); }
    break;

  case 240:

    { (yyval.statement) = YACC_CONTINUE_STATEMENT(); YY_LOC((yyval.statement), (yyloc)); }
    break;

  case 241:

    { (yyval.statement) = YACC_RETURN_STATEMENT((yysemantic_stack_[(3) - (2)].expression)); YY_LOC((yyval.statement), (yyloc)); }
    break;

  case 242:

    { (yyval.statement) = YACC_GOTO_STATEMENT((yysemantic_stack_[(3) - (2)].name)); YY_LOC((yyval.statement), (yyloc)); }
    break;

  case 243:

    { (yyval.statement) = YACC_DECLARATION_STATEMENT((yysemantic_stack_[(1) - (1)].declaration)); YY_LOC((yyval.statement), (yyloc)); }
    break;

  case 244:

    { (yyval.declarations) = (yysemantic_stack_[(4) - (3)].declarations); m_pDriver->getLexer()->unnest((yysemantic_stack_[(4) - (2)].nest)); }
    break;

  case 245:

    { (yyval.declarations) = (yysemantic_stack_[(9) - (3)].declarations); m_pDriver->getLexer()->unnest((yysemantic_stack_[(9) - (2)].nest)); YACC_UNBANG((yysemantic_stack_[(9) - (7)].bang), "Bad declaration-seq."); }
    break;

  case 246:

    { (yyval.declarations) = YACC_DECLARATIONS(0, 0); YY_LOC((yyval.declarations), (yyloc)); }
    break;

  case 247:

    { (yyval.declarations) = YACC_DECLARATIONS((yysemantic_stack_[(3) - (1)].declarations), YACC_COMPILE_DECLARATION((yysemantic_stack_[(3) - (2)].utility), (yysemantic_stack_[(3) - (3)].declaration))); YY_LOC((yyval.declarations), (yyloc)); }
    break;

  case 248:

    { (yyval.declarations) = (yysemantic_stack_[(7) - (1)].declarations); YACC_UNBANG((yysemantic_stack_[(7) - (5)].bang), "Bad declaration."); }
    break;

  case 249:

    { (yyval.declaration) = YACC_LINED_DECLARATION((yysemantic_stack_[(2) - (2)].declaration), (yysemantic_stack_[(2) - (1)].line)); m_pDriver->getLexer()->end_search((yyval.declaration)); YY_LOC((yyval.declaration), (yyloc)); }
    break;

  case 250:

    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 251:

    { (yyval.declaration) = (yysemantic_stack_[(3) - (3)].declaration); }
    break;

  case 252:

    { (yyval.declaration) = 0; }
    break;

  case 253:

    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 254:

    { (yyval.declaration) = YACC_SIMPLE_DECLARATION((yysemantic_stack_[(1) - (1)].expression)); YY_LOC((yyval.declaration), (yyloc)); }
    break;

  case 255:

    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 256:

    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 257:

    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 258:

    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 259:

    { (yyval.declaration) = YACC_LINKAGE_SPECIFICATION((yysemantic_stack_[(1) - (1)].name)); YY_LOC((yyval.declaration), (yyloc)); }
    break;

  case 260:

    { (yyval.declaration) = YACC_NAMESPACE_DECLARATION((yysemantic_stack_[(1) - (1)].name)); YY_LOC((yyval.declaration), (yyloc)); }
    break;

  case 261:

    { (yyval.declaration) = YACC_SET_TEMPLATE_DECLARATION((yysemantic_stack_[(2) - (2)].declaration)); YY_LOC((yyval.declaration), (yyloc)); }
    break;

  case 262:

    { (yyval.import_symbol_declaration) = YACC_IMPORT_SYMBOL_DECLARATION((yysemantic_stack_[(1) - (1)].name), 0); YY_LOC((yyval.import_symbol_declaration), (yyloc)); }
    break;

  case 263:

    { (yyval.import_symbol_declaration) = YACC_IMPORT_SYMBOL_DECLARATION((yysemantic_stack_[(3) - (1)].name), (yysemantic_stack_[(3) - (3)].name)); YY_LOC((yyval.import_symbol_declaration), (yyloc)); }
    break;

  case 264:

    { (yyval.import_symbol_declarations) = 0; }
    break;

  case 265:

    { (yyval.import_symbol_declarations) = YACC_IMPORT_SYMBOL_DECLARATIONS(0, (yysemantic_stack_[(2) - (2)].import_symbol_declaration)); YY_LOC((yyval.import_symbol_declarations), (yyloc)); }
    break;

  case 266:

    { (yyval.import_symbol_declarations) = YACC_IMPORT_SYMBOL_DECLARATIONS((yysemantic_stack_[(3) - (1)].import_symbol_declarations), (yysemantic_stack_[(3) - (3)].import_symbol_declaration)); YY_LOC((yyval.import_symbol_declarations), (yyloc)); }
    break;

  case 267:

    { (yyval.name) = YACC_DOT_QUALIFIED_NAME((yysemantic_stack_[(1) - (1)].name), 0); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 268:

    { (yyval.name) = YACC_DOT_QUALIFIED_NAME((yysemantic_stack_[(3) - (1)].name), (yysemantic_stack_[(3) - (3)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 269:

    { (yyval.declaration) = YACC_IMPORT_DECLARATION((yysemantic_stack_[(3) - (2)].name), (yysemantic_stack_[(3) - (3)].import_symbol_declarations)); YY_LOC((yyval.declaration), (yyloc)); }
    break;

  case 270:

    { (yyval.declaration) = YACC_SIMPLE_DECLARATION((yysemantic_stack_[(1) - (1)].expression)); YY_LOC((yyval.declaration), (yyloc)); }
    break;

  case 271:

    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 272:

    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 273:

    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 274:

    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 275:

    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 276:

    { (yyval.declaration) = YACC_SET_TEMPLATE_DECLARATION((yysemantic_stack_[(2) - (2)].declaration)); YY_LOC((yyval.declaration), (yyloc)); }
    break;

  case 277:

    { (yyval.expression) = YACC_EXPRESSION(0); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 278:

    { (yyval.expression) = (yysemantic_stack_[(2) - (1)].expression); }
    break;

  case 279:

    { (yyval.expression) = (yysemantic_stack_[(2) - (1)].expressions); }
    break;

  case 280:

    { (yyval.expression) = YACC_DECL_SPECIFIER_EXPRESSION((yysemantic_stack_[(2) - (2)].expression), (yysemantic_stack_[(2) - (1)].decl_specifier_id)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 281:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 282:

    { (yyval.name) = YACC_BUILT_IN_NAME((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].built_in_id)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 283:

    { (yyval.name) = YACC_DECL_SPECIFIER_NAME((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].decl_specifier_id)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 284:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 285:

    { (yyval.name) = YACC_SET_TEMPLATE_NAME((yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 286:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 287:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 288:

    { (yyval.name) = YACC_DECL_SPECIFIER_NAME((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].decl_specifier_id)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 289:

    { (yyval.name) = YACC_NAME_EXPRESSION((yysemantic_stack_[(1) - (1)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 290:

    { (yyval.name) = YACC_TYPED_NAME((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 291:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 292:

    { (yyval.name) = YACC_TYPED_NAME((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 293:

    { (yyval.name) = YACC_NAME_EXPRESSION((yysemantic_stack_[(1) - (1)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 294:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 295:

    { (yyval.name) = YACC_TYPED_NAME((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 296:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 297:

    { (yyval.name) = YACC_TYPED_NAME((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 298:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 299:

    { (yyval.name) = YACC_NAME_EXPRESSION((yysemantic_stack_[(2) - (1)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 300:

    { (yyval.name) = YACC_TYPED_NAME((yysemantic_stack_[(3) - (1)].name), (yysemantic_stack_[(3) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 301:

    { (yyval.name) = (yysemantic_stack_[(2) - (1)].name); }
    break;

  case 302:

    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 303:

    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 304:

    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 305:

    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 306:

    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].cv_qualifiers); }
    break;

  case 307:

    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 308:

    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 309:

    { (yyval.decl_specifier_id) = YACC_SET_TEMPLATE_DECL_SPECIFIER((yysemantic_stack_[(2) - (2)].decl_specifier_id)); YY_LOC((yyval.decl_specifier_id), (yyloc)); }
    break;

  case 310:

    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 311:

    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 312:

    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 313:

    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 314:

    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 315:

    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 316:

    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 317:

    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 318:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 319:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 320:

    { (yyval.name) = YACC_CV_DECL_SPECIFIER((yysemantic_stack_[(1) - (1)].cv_qualifiers)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 321:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 322:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 323:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 324:

    { (yyval.name) = YACC_SET_TEMPLATE_ID((yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 325:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 326:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 327:

    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 328:

    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 329:

    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 330:

    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 331:

    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 332:

    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 333:

    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 334:

    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 335:

    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 336:

    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 337:

    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 338:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 339:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 340:

    { (yyval.name) = YACC_ELABORATED_TYPE_SPECIFIER((yysemantic_stack_[(2) - (1)].class_key), (yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 341:

    { (yyval.name) = YACC_ELABORATED_TYPE_SPECIFIER((yysemantic_stack_[(2) - (1)].class_key), (yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 342:

    { (yyval.name) = YACC_ENUM_SPECIFIER_ID((yysemantic_stack_[(3) - (2)].name), (yysemantic_stack_[(3) - (3)].enumerators)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 343:

    { (yyval.name) = YACC_ENUM_SPECIFIER_ID(0, (yysemantic_stack_[(2) - (2)].enumerators)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 344:

    { (yyval.enumerators) = YACC_ENUMERATORS(0, 0); YY_LOC((yyval.enumerators), (yyloc)); }
    break;

  case 345:

    { (yyval.enumerators) = (yysemantic_stack_[(3) - (2)].enumerators); }
    break;

  case 346:

    { (yyval.enumerators) = (yysemantic_stack_[(4) - (2)].enumerators); }
    break;

  case 347:

    { }
    break;

  case 348:

    { YACC_UNBANG((yysemantic_stack_[(3) - (1)].bang), "Bad enumerator-list."); }
    break;

  case 349:

    { }
    break;

  case 350:

    { YACC_UNBANG((yysemantic_stack_[(3) - (1)].bang), "Bad enumerator-definition."); }
    break;

  case 352:

    { YACC_UNBANG((yysemantic_stack_[(3) - (1)].bang), "Bad enumerator-definition."); }
    break;

  case 353:

    { (yyval.enumerators) = YACC_ENUMERATORS(0, 0); YY_LOC((yyval.enumerators), (yyloc)); }
    break;

  case 355:

    { (yyval.enumerators) = YACC_ENUMERATORS((yysemantic_stack_[(2) - (1)].enumerators), (yysemantic_stack_[(2) - (2)].enumerator)); YY_LOC((yyval.enumerators), (yyloc)); }
    break;

  case 356:

    { (yyval.enumerator) = YACC_ENUMERATOR((yysemantic_stack_[(1) - (1)].name), 0); YY_LOC((yyval.enumerator), (yyloc)); }
    break;

  case 357:

    { (yyval.enumerator) = YACC_ENUMERATOR((yysemantic_stack_[(3) - (1)].name), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.enumerator), (yyloc)); }
    break;

  case 358:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 359:

    { (yyval.name) = YACC_NAMESPACE_DEFINITION((yysemantic_stack_[(3) - (2)].name), (yysemantic_stack_[(3) - (3)].declarations)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 360:

    { (yyval.name) = YACC_NAMESPACE_DEFINITION(0, (yysemantic_stack_[(2) - (2)].declarations)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 361:

    { (yyval.declaration) = YACC_NAMESPACE_ALIAS_DEFINITION((yysemantic_stack_[(5) - (2)].name), (yysemantic_stack_[(5) - (4)].name)); YY_LOC((yyval.declaration), (yyloc)); }
    break;

  case 362:

    { (yyval.declaration) = YACC_USING_DECLARATION(false, (yysemantic_stack_[(3) - (2)].name)); YY_LOC((yyval.declaration), (yyloc)); }
    break;

  case 363:

    { (yyval.declaration) = YACC_USING_DECLARATION(true, (yysemantic_stack_[(4) - (3)].name)); YY_LOC((yyval.declaration), (yyloc)); }
    break;

  case 364:

    { (yyval.declaration) = YACC_USING_DIRECTIVE((yysemantic_stack_[(4) - (3)].name)); YY_LOC((yyval.declaration), (yyloc)); }
    break;

  case 365:

    { (yyval.declaration) = YACC_ASM_DEFINITION((yysemantic_stack_[(5) - (3)].strings)); YY_LOC((yyval.declaration), (yyloc)); }
    break;

  case 366:

    { (yyval.name) = YACC_LINKAGE_SPECIFIER((yysemantic_stack_[(3) - (2)].strings), (yysemantic_stack_[(3) - (3)].declaration)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 367:

    { (yyval.name) = YACC_LINKAGE_SPECIFIER((yysemantic_stack_[(3) - (2)].strings), (yysemantic_stack_[(3) - (3)].declarations)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 368:

    { (yyval.expressions) = YACC_EXPRESSIONS(YACC_EXPRESSIONS(0, (yysemantic_stack_[(3) - (1)].expression)), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expressions), (yyloc)); }
    break;

  case 369:

    { (yyval.expressions) = YACC_EXPRESSIONS((yysemantic_stack_[(3) - (1)].expressions), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expressions), (yyloc)); }
    break;

  case 371:

    { (yyval.pointer_declarator) = YACC_POINTER_DECLARATOR(); YY_LOC((yyval.pointer_declarator), (yyloc)); }
    break;

  case 372:

    { (yyval.pointer_declarator) = YACC_CV_DECLARATOR((yysemantic_stack_[(2) - (1)].pointer_declarator), (yysemantic_stack_[(2) - (2)].cv_qualifiers)); YY_LOC((yyval.pointer_declarator), (yyloc)); }
    break;

  case 373:

    { (yyval.declarator) = (yysemantic_stack_[(1) - (1)].pointer_declarator); }
    break;

  case 374:

    { (yyval.declarator) = YACC_NESTED_DECLARATOR((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].declarator)); YY_LOC((yyval.declarator), (yyloc)); }
    break;

  case 375:

    { (yyval.declarator) = YACC_REFERENCE_DECLARATOR(); YY_LOC((yyval.declarator), (yyloc)); }
    break;

  case 376:

    { (yyval.declarator) = (yysemantic_stack_[(1) - (1)].declarator); }
    break;

  case 377:

    { (yyval.declarator) = YACC_GLOBAL_DECLARATOR((yysemantic_stack_[(2) - (1)].is_template), (yysemantic_stack_[(2) - (2)].declarator)); YY_LOC((yyval.declarator), (yyloc)); }
    break;

  case 378:

    { (yyval.expression) = YACC_POINTER_EXPRESSION((yysemantic_stack_[(1) - (1)].declarator), YACC_EPSILON()); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 379:

    { (yyval.expression) = YACC_POINTER_EXPRESSION((yysemantic_stack_[(2) - (1)].declarator), (yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 380:

    { (yyval.expression) = YACC_EXPRESSION(0); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 381:

    { (yyval.expression) = YACC_POINTER_EXPRESSION((yysemantic_stack_[(2) - (1)].declarator), (yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 382:

    { (yyval.cv_qualifiers) = YACC_CV_QUALIFIERS(0, 0); YY_LOC((yyval.cv_qualifiers), (yyloc)); }
    break;

  case 383:

    { (yyval.cv_qualifiers) = YACC_CV_QUALIFIERS((yysemantic_stack_[(2) - (1)].cv_qualifiers), (yysemantic_stack_[(2) - (2)].cv_qualifiers)); YY_LOC((yyval.cv_qualifiers), (yyloc)); }
    break;

  case 384:

    { (yyval.cv_qualifiers) = (yysemantic_stack_[(1) - (1)].cv_qualifiers); }
    break;

  case 385:

    { (yyval.cv_qualifiers) = (yysemantic_stack_[(1) - (1)].cv_qualifiers); }
    break;

  case 386:

    { (yyval.expression) = YACC_TYPED_EXPRESSION((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 387:

    { (yyval.expression) = YACC_TYPED_EXPRESSION((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 388:

    { (yyval.expression) = YACC_EPSILON(); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 389:

    { (yyval.expression) = YACC_POINTER_EXPRESSION((yysemantic_stack_[(2) - (1)].declarator), (yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 390:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 391:

    { (yyval.expression) = YACC_EPSILON(); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 392:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 393:

    { (yyval.expression) = YACC_CALL_EXPRESSION((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].parenthesised)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 394:

    { (yyval.expression) = YACC_ARRAY_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), 0); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 395:

    { (yyval.expression) = YACC_ARRAY_EXPRESSION((yysemantic_stack_[(4) - (1)].expression), (yysemantic_stack_[(4) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 396:

    { (yyval.name) = YACC_OPERATOR_LOG_AND_ID(); }
    break;

  case 397:

    { (yyval.name) = YACC_OPERATOR_BIT_AND_ID(); }
    break;

  case 398:

    { (yyval.name) = 0; }
    break;

  case 399:

    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 400:

    { (yyval.parenthesised) = YACC_PARENTHESISED((yysemantic_stack_[(3) - (1)].parameters), (yysemantic_stack_[(3) - (2)].cv_qualifiers), (yysemantic_stack_[(3) - (3)].name), 0); YY_LOC((yyval.parenthesised), (yyloc)); }
    break;

  case 401:

    { (yyval.parenthesised) = YACC_PARENTHESISED((yysemantic_stack_[(4) - (1)].parameters), (yysemantic_stack_[(4) - (2)].cv_qualifiers), (yysemantic_stack_[(4) - (3)].name), (yysemantic_stack_[(4) - (4)].exception_specification)); YY_LOC((yyval.parenthesised), (yyloc)); }
    break;

  case 402:

    { (yyval.parameters) = (yysemantic_stack_[(3) - (2)].parameters); }
    break;

  case 403:

    { (yyval.parameters) = YACC_PARAMETERS(0, 0); YY_LOC((yyval.parameters), (yyloc)); }
    break;

  case 404:

    { (yyval.parameters) = (yysemantic_stack_[(1) - (1)].parameters); }
    break;

  case 405:

    { (yyval.parameters) = YACC_PARAMETERS((yysemantic_stack_[(2) - (1)].parameters), YACC_ELLIPSIS_EXPRESSION()); YY_LOC((yyval.parameters), (yyloc)); }
    break;

  case 406:

    { (yyval.parameters) = YACC_PARAMETERS(0, (yysemantic_stack_[(1) - (1)].parameter)); YY_LOC((yyval.parameters), (yyloc)); }
    break;

  case 407:

    { (yyval.parameters) = YACC_PARAMETERS((yysemantic_stack_[(3) - (1)].parameters), (yysemantic_stack_[(3) - (3)].parameter)); YY_LOC((yyval.parameters), (yyloc)); }
    break;

  case 408:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 409:

    { (yyval.expression) = YACC_COMPLEX_POINTER_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (2)].pointer_declarator), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 410:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 411:

    { (yyval.expression) = YACC_AND_EXPRESSION((yysemantic_stack_[(2) - (1)].expression), YACC_EPSILON()); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 412:

    { (yyval.expression) = YACC_AND_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 413:

    { (yyval.expression) = YACC_ASSIGNMENT_EXPRESSION((yysemantic_stack_[(1) - (1)].expression), 0, 0); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 414:

    { (yyval.expression) = YACC_ASSIGNMENT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (2)].keyword), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 415:

    { (yyval.expression) = YACC_ELLIPSIS_EXPRESSION(); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 416:

    { (yyval.parameter) = YACC_EXPRESSION_PARAMETER((yysemantic_stack_[(1) - (1)].expression)); YY_LOC((yyval.parameter), (yyloc)); }
    break;

  case 417:

    { (yyval.parameter) = YACC_EXPRESSION_PARAMETER((yysemantic_stack_[(1) - (1)].expression)); YY_LOC((yyval.parameter), (yyloc)); }
    break;

  case 418:

    { (yyval.parameter) = YACC_DECL_SPECIFIER_PARAMETER((yysemantic_stack_[(2) - (2)].parameter), (yysemantic_stack_[(2) - (1)].decl_specifier_id)); YY_LOC((yyval.parameter), (yyloc)); }
    break;

  case 419:

    { (yyval.parameter) = YACC_EXPRESSION_PARAMETER((yysemantic_stack_[(1) - (1)].expression)); YY_LOC((yyval.parameter), (yyloc)); }
    break;

  case 420:

    { (yyval.parameter) = YACC_EXPRESSION_PARAMETER((yysemantic_stack_[(1) - (1)].expression)); YY_LOC((yyval.parameter), (yyloc)); }
    break;

  case 421:

    { (yyval.parameter) = YACC_EXPRESSION_PARAMETER(YACC_ASSIGNMENT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (2)].keyword), (yysemantic_stack_[(3) - (3)].expression))); YY_LOC((yyval.parameter), (yyloc)); }
    break;

  case 422:

    { (yyval.parameter) = YACC_DECL_SPECIFIER_PARAMETER((yysemantic_stack_[(2) - (2)].parameter), (yysemantic_stack_[(2) - (1)].decl_specifier_id)); YY_LOC((yyval.parameter), (yyloc)); }
    break;

  case 423:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 424:

    { (yyval.expression) = YACC_AND_EXPRESSION((yysemantic_stack_[(2) - (1)].expression), 0); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 425:

    { (yyval.expression) = YACC_AND_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 426:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 427:

    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 428:

    { (yyval.expression) = YACC_FUNCTION_DEFINITION((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].function_body)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 429:

    { (yyval.expression) = YACC_FUNCTION_DEFINITION((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].function_body)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 430:

    { (yyval.expression) = YACC_DECL_SPECIFIER_EXPRESSION((yysemantic_stack_[(2) - (2)].expression), (yysemantic_stack_[(2) - (1)].decl_specifier_id)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 431:

    { (yyval.expression) = YACC_CTOR_DEFINITION((yysemantic_stack_[(2) - (1)].expressions), (yysemantic_stack_[(2) - (2)].function_body)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 432:

    { (yyval.expression) = YACC_CTOR_DEFINITION((yysemantic_stack_[(2) - (1)].expressions), (yysemantic_stack_[(2) - (2)].function_body)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 433:

    { (yyval.expression) = YACC_DECL_SPECIFIER_EXPRESSION((yysemantic_stack_[(2) - (2)].expression), (yysemantic_stack_[(2) - (1)].decl_specifier_id));YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 434:

    { (yyval.expressions) = YACC_EXPRESSIONS(0, (yysemantic_stack_[(1) - (1)].expression)); YY_LOC((yyval.expressions), (yyloc)); }
    break;

  case 435:

    { (yyval.expressions) = YACC_EXPRESSIONS((yysemantic_stack_[(3) - (1)].expressions), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expressions), (yyloc)); }
    break;

  case 436:

    { (yyval.function_body) = YACC_TRY_FUNCTION_BLOCK((yysemantic_stack_[(3) - (2)].function_body), (yysemantic_stack_[(3) - (3)].handlers)); YY_LOC((yyval.function_body), (yyloc)); }
    break;

  case 437:

    { (yyval.function_body) = YACC_CTOR_FUNCTION_BLOCK((yysemantic_stack_[(2) - (2)].function_body), (yysemantic_stack_[(2) - (1)].mem_initializers)); YY_LOC((yyval.function_body), (yyloc)); }
    break;

  case 438:

    { (yyval.function_body) = YACC_FUNCTION_BLOCK((yysemantic_stack_[(1) - (1)].statement)); YY_LOC((yyval.function_body), (yyloc)); }
    break;

  case 439:

    { (yyval.initializer_clause) = YACC_INITIALIZER_EXPRESSION_CLAUSE((yysemantic_stack_[(1) - (1)].expression)); YY_LOC((yyval.initializer_clause), (yyloc)); }
    break;

  case 441:

    { (yyval.initializer_clause) = YACC_INITIALIZER_LIST_CLAUSE((yysemantic_stack_[(3) - (2)].initializer_clauses)); YY_LOC((yyval.initializer_clause), (yyloc)); }
    break;

  case 442:

    { (yyval.initializer_clause) = YACC_INITIALIZER_LIST_CLAUSE((yysemantic_stack_[(4) - (2)].initializer_clauses)); YY_LOC((yyval.initializer_clause), (yyloc)); }
    break;

  case 443:

    { (yyval.initializer_clause) = YACC_INITIALIZER_LIST_CLAUSE(0); YY_LOC((yyval.initializer_clause), (yyloc)); }
    break;

  case 444:

    { (yyval.initializer_clause) = 0; YACC_UNBANG((yysemantic_stack_[(6) - (4)].bang), "Bad initializer_clause."); }
    break;

  case 445:

    { (yyval.initializer_clause) = (yysemantic_stack_[(8) - (2)].initializer_clauses); YACC_UNBANG((yysemantic_stack_[(8) - (6)].bang), "Bad initializer_clause."); }
    break;

  case 446:

    { (yyval.initializer_clauses) = YACC_INITIALIZER_CLAUSES(0, (yysemantic_stack_[(1) - (1)].initializer_clause)); YY_LOC((yyval.initializer_clauses), (yyloc)); }
    break;

  case 447:

    { (yyval.initializer_clauses) = YACC_INITIALIZER_CLAUSES((yysemantic_stack_[(3) - (1)].initializer_clauses), (yysemantic_stack_[(3) - (3)].initializer_clause)); YY_LOC((yyval.initializer_clauses), (yyloc)); }
    break;

  case 448:

    { (yyval.initializer_clause) = (yysemantic_stack_[(2) - (2)].initializer_clause); m_pDriver->getLexer()->end_search((yyval.initializer_clause)); }
    break;

  case 450:

    { (yyval.initializer_clause) = (yysemantic_stack_[(3) - (3)].initializer_clause); }
    break;

  case 451:

    { (yyval.initializer_clause) = 0; }
    break;

  case 452:

    { (yyval.mark) = m_pDriver->getLexer()->mark(); }
    break;

  case 453:

    { (yyval.name) = YACC_ELABORATED_TYPE_SPECIFIER((yysemantic_stack_[(2) - (1)].class_key), (yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 454:

    { (yyval.name) = YACC_ELABORATED_TYPE_SPECIFIER((yysemantic_stack_[(4) - (1)].class_key), (yysemantic_stack_[(4) - (2)].name)); YY_LOC((yyval.name), (yyloc)); m_pDriver->getLexer()->rewind_colon((yysemantic_stack_[(4) - (3)].mark), (yyval.name)); }
    break;

  case 455:

    { m_pDriver->getLexer()->unmark((yysemantic_stack_[(5) - (4)].base_specifiers)); (yyval._class) = YACC_CLASS_SPECIFIER_ID((yysemantic_stack_[(5) - (1)].class_key), (yysemantic_stack_[(5) - (2)].name), (yysemantic_stack_[(5) - (4)].base_specifiers)); YY_LOC((yyval._class), (yyloc)); }
    break;

  case 456:

    { (yyval._class) = YACC_CLASS_SPECIFIER_ID((yysemantic_stack_[(4) - (1)].class_key), 0, (yysemantic_stack_[(4) - (3)].base_specifiers)); YY_LOC((yyval._class), (yyloc)); }
    break;

  case 457:

    { (yyval._class) = YACC_CLASS_SPECIFIER_ID((yysemantic_stack_[(3) - (1)].class_key), (yysemantic_stack_[(3) - (2)].name), 0); YY_LOC((yyval._class), (yyloc)); }
    break;

  case 458:

    { (yyval._class) = YACC_CLASS_SPECIFIER_ID((yysemantic_stack_[(2) - (1)].class_key), 0, 0); YY_LOC((yyval._class), (yyloc)); }
    break;

  case 462:

    { (yyval.name) = YACC_CLASS_MEMBERS((yysemantic_stack_[(3) - (1)]._class), (yysemantic_stack_[(3) - (2)].member_declarations)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 463:

    { (yyval.name) = YACC_CLASS_MEMBERS((yysemantic_stack_[(8) - (1)]._class), (yysemantic_stack_[(8) - (2)].member_declarations)); YACC_UNBANG((yysemantic_stack_[(8) - (6)].bang), "Bad member_specification.opt."); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 464:

    { (yyval.member_declarations) = YACC_MEMBER_DECLARATIONS(0, 0); YY_LOC((yyval.member_declarations), (yyloc)); }
    break;

  case 465:

    { (yyval.member_declarations) = YACC_MEMBER_DECLARATIONS((yysemantic_stack_[(3) - (1)].member_declarations), YACC_COMPILE_MEMBER_DECLARATION((yysemantic_stack_[(3) - (2)].utility), (yysemantic_stack_[(3) - (3)].member_declaration))); YY_LOC((yyval.member_declarations), (yyloc)); }
    break;

  case 466:

    { (yyval.member_declarations) = (yysemantic_stack_[(7) - (1)].member_declarations); YACC_UNBANG((yysemantic_stack_[(7) - (5)].bang), "Bad member-declaration."); }
    break;

  case 467:

    { (yyval.member_declaration) = YACC_LINED_MEMBER_DECLARATION((yysemantic_stack_[(2) - (2)].member_declaration), (yysemantic_stack_[(2) - (1)].line)); YY_LOC((yyval.member_declaration), (yyloc)); m_pDriver->getLexer()->end_search((yyval.member_declaration)); }
    break;

  case 469:

    { (yyval.member_declaration) = (yysemantic_stack_[(3) - (3)].member_declaration); }
    break;

  case 470:

    { (yyval.member_declaration) = 0; }
    break;

  case 471:

    { (yyval.member_declaration) = (yysemantic_stack_[(1) - (1)].member_declaration); }
    break;

  case 472:

    { (yyval.member_declaration) = YACC_MEMBER_DECLARATION((yysemantic_stack_[(1) - (1)].expression)); YY_LOC((yyval.member_declaration), (yyloc)); }
    break;

  case 473:

    { (yyval.member_declaration) = YACC_MEMBER_DECLARATION((yysemantic_stack_[(1) - (1)].expression)); YY_LOC((yyval.member_declaration), (yyloc)); }
    break;

  case 474:

    { (yyval.member_declaration) = YACC_MEMBER_DECLARATION((yysemantic_stack_[(1) - (1)].declaration)); YY_LOC((yyval.member_declaration), (yyloc)); }
    break;

  case 475:

    { (yyval.member_declaration) = YACC_MEMBER_DECLARATION((yysemantic_stack_[(1) - (1)].declaration)); YY_LOC((yyval.member_declaration), (yyloc)); }
    break;

  case 476:

    { (yyval.expression) = YACC_EXPRESSION(0); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 477:

    { (yyval.expression) = (yysemantic_stack_[(2) - (1)].expression); }
    break;

  case 478:

    { (yyval.expression) = (yysemantic_stack_[(2) - (1)].expressions); }
    break;

  case 479:

    { (yyval.expression) = (yysemantic_stack_[(2) - (1)].expressions); }
    break;

  case 480:

    { (yyval.expression) = YACC_DECL_SPECIFIER_EXPRESSION((yysemantic_stack_[(2) - (2)].expression), (yysemantic_stack_[(2) - (1)].decl_specifier_id)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 481:

    { (yyval.expressions) = YACC_EXPRESSIONS(YACC_EXPRESSIONS(0, (yysemantic_stack_[(3) - (1)].expression)), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expressions), (yyloc)); }
    break;

  case 482:

    { (yyval.expressions) = YACC_EXPRESSIONS((yysemantic_stack_[(3) - (1)].expressions), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expressions), (yyloc)); }
    break;

  case 483:

    { (yyval.expressions) = YACC_EXPRESSIONS((yysemantic_stack_[(3) - (1)].expressions), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expressions), (yyloc)); }
    break;

  case 486:

    { (yyval.member_declaration) = YACC_ACCESSIBILITY_SPECIFIER((yysemantic_stack_[(2) - (1)].access_specifier)); YY_LOC((yyval.member_declaration), (yyloc)); }
    break;

  case 487:

    { (yyval.expression) = YACC_BIT_FIELD_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 488:

    { (yyval.expression) = YACC_BIT_FIELD_EXPRESSION(0, (yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 490:

    { (yyval.expression) = YACC_CONDITIONAL_EXPRESSION((yysemantic_stack_[(5) - (1)].expression), (yysemantic_stack_[(5) - (3)].expression), (yysemantic_stack_[(5) - (5)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 492:

    { (yyval.expression) = YACC_ASSIGNMENT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (2)].keyword), (yysemantic_stack_[(3) - (3)].initializer_clause)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 493:

    { (yyval.base_specifiers) = YACC_BASE_SPECIFIERS(0, (yysemantic_stack_[(1) - (1)].base_specifier)); YY_LOC((yyval.base_specifiers), (yyloc)); }
    break;

  case 494:

    { (yyval.base_specifiers) = YACC_BASE_SPECIFIERS((yysemantic_stack_[(3) - (1)].base_specifiers), (yysemantic_stack_[(3) - (3)].base_specifier)); YY_LOC((yyval.base_specifiers), (yyloc)); }
    break;

  case 495:

    { (yyval.base_specifier) = YACC_BASE_SPECIFIER((yysemantic_stack_[(1) - (1)].name)); YY_LOC((yyval.base_specifier), (yyloc)); }
    break;

  case 496:

    { (yyval.base_specifier) = YACC_ACCESS_BASE_SPECIFIER((yysemantic_stack_[(2) - (2)].base_specifier), (yysemantic_stack_[(2) - (1)].access_specifier)); YY_LOC((yyval.base_specifier), (yyloc)); }
    break;

  case 497:

    { (yyval.base_specifier) = YACC_VIRTUAL_BASE_SPECIFIER((yysemantic_stack_[(2) - (2)].base_specifier)); YY_LOC((yyval.base_specifier), (yyloc)); }
    break;

  case 501:

    { (yyval.name) = YACC_CONVERSION_FUNCTION_ID((yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 502:

    { (yyval.expression) = YACC_TYPED_EXPRESSION((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 503:

    { (yyval.expression) = YACC_TYPED_EXPRESSION((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 504:

    { (yyval.mem_initializers) = YACC_MEM_INITIALIZERS(0, 0); YY_LOC((yyval.mem_initializers), (yyloc)); }
    break;

  case 506:

    { (yyval.mem_initializers) = (yysemantic_stack_[(2) - (2)].mem_initializers); }
    break;

  case 507:

    { (yyval.mem_initializers) = (yysemantic_stack_[(4) - (2)].mem_initializers); YACC_UNBANG((yysemantic_stack_[(4) - (3)].bang), "Bad ctor-initializer."); }
    break;

  case 508:

    { (yyval.mem_initializers) = YACC_MEM_INITIALIZERS(0, (yysemantic_stack_[(1) - (1)].mem_initializer)); YY_LOC((yyval.mem_initializers), (yyloc)); }
    break;

  case 509:

    { (yyval.mem_initializers) = YACC_MEM_INITIALIZERS((yysemantic_stack_[(2) - (1)].mem_initializers), (yysemantic_stack_[(2) - (2)].mem_initializer)); YY_LOC((yyval.mem_initializers), (yyloc)); }
    break;

  case 511:

    { YACC_UNBANG((yysemantic_stack_[(4) - (2)].bang), "Bad mem-initializer."); }
    break;

  case 512:

    { (yyval.mem_initializer) = YACC_MEM_INITIALIZER((yysemantic_stack_[(4) - (1)].name), (yysemantic_stack_[(4) - (3)].expressions)); YY_LOC((yyval.mem_initializer), (yyloc)); }
    break;

  case 514:

    { (yyval.name) = YACC_OPERATOR_FUNCTION_ID((yysemantic_stack_[(2) - (2)].name)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 515:

    { (yyval.name) = YACC_OPERATOR_NEW_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 516:

    { (yyval.name) = YACC_OPERATOR_DELETE_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 517:

    { (yyval.name) = YACC_OPERATOR_ADD_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 518:

    { (yyval.name) = YACC_OPERATOR_SUB_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 519:

    { (yyval.name) = YACC_OPERATOR_MUL_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 520:

    { (yyval.name) = YACC_OPERATOR_DIV_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 521:

    { (yyval.name) = YACC_OPERATOR_MOD_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 522:

    { (yyval.name) = YACC_OPERATOR_XOR_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 523:

    { (yyval.name) = YACC_OPERATOR_BIT_AND_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 524:

    { (yyval.name) = YACC_OPERATOR_BIT_OR_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 525:

    { (yyval.name) = YACC_OPERATOR_BIT_NOT_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 526:

    { (yyval.name) = YACC_OPERATOR_LOG_NOT_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 527:

    { (yyval.name) = YACC_OPERATOR_ASS_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 528:

    { (yyval.name) = YACC_OPERATOR_LT_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 529:

    { (yyval.name) = YACC_OPERATOR_GT_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 530:

    { (yyval.name) = YACC_OPERATOR_ASS_ADD_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 531:

    { (yyval.name) = YACC_OPERATOR_ASS_SUB_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 532:

    { (yyval.name) = YACC_OPERATOR_ASS_MUL_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 533:

    { (yyval.name) = YACC_OPERATOR_ASS_DIV_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 534:

    { (yyval.name) = YACC_OPERATOR_ASS_MOD_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 535:

    { (yyval.name) = YACC_OPERATOR_ASS_XOR_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 536:

    { (yyval.name) = YACC_OPERATOR_ASS_BIT_AND_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 537:

    { (yyval.name) = YACC_OPERATOR_ASS_BIT_OR_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 538:

    { (yyval.name) = YACC_OPERATOR_SHL_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 539:

    { (yyval.name) = YACC_OPERATOR_SHR_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 540:

    { (yyval.name) = YACC_OPERATOR_ASS_SHR_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 541:

    { (yyval.name) = YACC_OPERATOR_ASS_SHL_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 542:

    { (yyval.name) = YACC_OPERATOR_EQ_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 543:

    { (yyval.name) = YACC_OPERATOR_NE_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 544:

    { (yyval.name) = YACC_OPERATOR_LE_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 545:

    { (yyval.name) = YACC_OPERATOR_GE_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 546:

    { (yyval.name) = YACC_OPERATOR_LOG_AND_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 547:

    { (yyval.name) = YACC_OPERATOR_LOG_OR_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 548:

    { (yyval.name) = YACC_OPERATOR_INC_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 549:

    { (yyval.name) = YACC_OPERATOR_DEC_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 550:

    { (yyval.name) = YACC_OPERATOR_COMMA_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 551:

    { (yyval.name) = YACC_OPERATOR_ARROW_STAR_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 552:

    { (yyval.name) = YACC_OPERATOR_ARROW_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 553:

    { (yyval.name) = YACC_OPERATOR_CALL_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 554:

    { (yyval.name) = YACC_OPERATOR_INDEX_ID(); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 555:

    { (yyval.declaration) = YACC_TEMPLATE_DECLARATION((yysemantic_stack_[(2) - (1)].template_parameters), (yysemantic_stack_[(2) - (2)].declaration)); YY_LOC((yyval.declaration), (yyloc)); }
    break;

  case 556:

    { (yyval.declaration) = YACC_DECL_SPECIFIER_DECLARATION((yysemantic_stack_[(2) - (2)].declaration), (yysemantic_stack_[(2) - (1)].decl_specifier_id)); YY_LOC((yyval.declaration), (yyloc)); }
    break;

  case 557:

    { (yyval.template_parameters) = (yysemantic_stack_[(4) - (3)].template_parameters); YY_LOC((yyval.template_parameters), (yyloc)); }
    break;

  case 558:

    { (yyval.template_parameters) = YACC_TEMPLATE_PARAMETERS(0, (yysemantic_stack_[(1) - (1)].template_parameter)); YY_LOC((yyval.template_parameters), (yyloc)); }
    break;

  case 559:

    { (yyval.template_parameters) = YACC_TEMPLATE_PARAMETERS((yysemantic_stack_[(3) - (1)].template_parameters), (yysemantic_stack_[(3) - (3)].template_parameter)); YY_LOC((yyval.template_parameters), (yyloc)); }
    break;

  case 560:

    { (yyval.template_parameter) = YACC_INIT_SIMPLE_TYPE_PARAMETER((yysemantic_stack_[(1) - (1)].simple_type_parameter), 0); YY_LOC((yyval.template_parameter), (yyloc)); }
    break;

  case 561:

    { (yyval.template_parameter) = YACC_INIT_SIMPLE_TYPE_PARAMETER((yysemantic_stack_[(3) - (1)].simple_type_parameter), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.template_parameter), (yyloc)); }
    break;

  case 562:

    { (yyval.template_parameter) = YACC_INIT_TEMPLATED_PARAMETER((yysemantic_stack_[(1) - (1)].templated_type_parameter), 0); YY_LOC((yyval.template_parameter), (yyloc)); }
    break;

  case 563:

    { (yyval.template_parameter) = YACC_INIT_TEMPLATED_PARAMETER((yysemantic_stack_[(3) - (1)].templated_type_parameter), (yysemantic_stack_[(3) - (3)].name)); YY_LOC((yyval.template_parameter), (yyloc)); }
    break;

  case 564:

    { (yyval.template_parameter) = YACC_TEMPLATE_PARAMETER((yysemantic_stack_[(1) - (1)].parameter)); YY_LOC((yyval.template_parameter), (yyloc)); }
    break;

  case 565:

    { (yyval.template_parameter) = 0; YACC_UNBANG((yysemantic_stack_[(2) - (1)].bang), "Bad template-parameter."); YY_LOC((yyval.template_parameter), (yyloc)); }
    break;

  case 566:

    { (yyval.simple_type_parameter) = YACC_CLASS_TYPE_PARAMETER(0); YY_LOC((yyval.simple_type_parameter), (yyloc)); }
    break;

  case 567:

    { (yyval.simple_type_parameter) = YACC_TYPENAME_TYPE_PARAMETER(0); YY_LOC((yyval.simple_type_parameter), (yyloc)); }
    break;

  case 568:

    { (yyval.templated_type_parameter) = YACC_TEMPLATED_TYPE_PARAMETER((yysemantic_stack_[(2) - (1)].template_parameters), 0); YY_LOC((yyval.templated_type_parameter), (yyloc)); }
    break;

  case 569:

    { (yyval.templated_type_parameter) = YACC_TEMPLATED_TYPE_PARAMETER((yysemantic_stack_[(3) - (1)].template_parameters), (yysemantic_stack_[(3) - (3)].name)); YY_LOC((yyval.templated_type_parameter), (yyloc)); }
    break;

  case 570:

    { (yyval.name) = YACC_TEMPLATE_NAME((yysemantic_stack_[(5) - (2)].name), (yysemantic_stack_[(5) - (4)].template_arguments)); YY_LOC((yyval.name), (yyloc)); }
    break;

  case 571:

    { (yyval.name) = (yysemantic_stack_[(2) - (2)].name); }
    break;

  case 572:

    { (yyval.template_arguments) = YACC_TEMPLATE_ARGUMENTS(0, (yysemantic_stack_[(1) - (1)].template_argument)); YY_LOC((yyval.template_arguments), (yyloc)); }
    break;

  case 573:

    { (yyval.template_arguments) = YACC_TEMPLATE_ARGUMENTS((yysemantic_stack_[(3) - (1)].template_arguments), (yysemantic_stack_[(3) - (3)].template_argument)); YY_LOC((yyval.template_arguments), (yyloc)); }
    break;

  case 574:

    { (yyval.template_argument) = YACC_TEMPLATE_ARGUMENT((yysemantic_stack_[(1) - (1)].parameter)); YY_LOC((yyval.template_argument), (yyloc)); }
    break;

  case 575:

    { (yyval.declaration) = YACC_EXPLICIT_SPECIALIZATION((yysemantic_stack_[(4) - (4)].declaration)); YY_LOC((yyval.declaration), (yyloc)); }
    break;

  case 576:

    { (yyval.function_body) = YACC_TRY_BLOCK((yysemantic_stack_[(3) - (2)].statement), (yysemantic_stack_[(3) - (3)].handlers)); YY_LOC((yyval.function_body), (yyloc)); }
    break;

  case 577:

    { (yyval.handlers) = YACC_HANDLERS(0, (yysemantic_stack_[(1) - (1)].handler)); YY_LOC((yyval.handlers), (yyloc)); }
    break;

  case 578:

    { (yyval.handlers) = YACC_HANDLERS((yysemantic_stack_[(2) - (2)].handlers), (yysemantic_stack_[(2) - (1)].handler)); YY_LOC((yyval.handlers), (yyloc)); }
    break;

  case 579:

    { (yyval.handler) = YACC_HANDLER((yysemantic_stack_[(5) - (3)].exception_declaration), (yysemantic_stack_[(5) - (5)].statement)); YY_LOC((yyval.handler), (yyloc)); }
    break;

  case 580:

    { (yyval.exception_declaration) = YACC_EXCEPTION_DECLARATION((yysemantic_stack_[(1) - (1)].parameter)); YY_LOC((yyval.exception_declaration), (yyloc)); }
    break;

  case 581:

    { (yyval.expression) = YACC_THROW_EXPRESSION(0); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 582:

    { (yyval.expression) = YACC_THROW_EXPRESSION((yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 583:

    { (yyval.expression) = YACC_THROW_EXPRESSION(0); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 584:

    { (yyval.expression) = YACC_THROW_EXPRESSION((yysemantic_stack_[(2) - (2)].expression)); YY_LOC((yyval.expression), (yyloc)); }
    break;

  case 585:

    { (yyval.exception_specification) = YACC_EXCEPTION_SPECIFICATION(0); YY_LOC((yyval.exception_specification), (yyloc)); }
    break;

  case 586:

    { (yyval.exception_specification) = YACC_EXCEPTION_SPECIFICATION((yysemantic_stack_[(4) - (3)].expressions)); YY_LOC((yyval.exception_specification), (yyloc)); }
    break;

  case 587:

    { (yyval.expressions) = YACC_EXPRESSIONS(0, (yysemantic_stack_[(1) - (1)].expression)); YY_LOC((yyval.expressions), (yyloc)); }
    break;

  case 588:

    { (yyval.expressions) = YACC_EXPRESSIONS((yysemantic_stack_[(3) - (1)].expressions), (yysemantic_stack_[(3) - (3)].expression)); YY_LOC((yyval.expressions), (yyloc)); }
    break;

  case 589:

    { yyerrok; yyclearin; m_pDriver->getLexer()->advance_search(); }
    break;

  case 590:

    { (yyval.bang) = YACC_BANG(); }
    break;

  case 591:

    { (yyval.mark) = m_pDriver->getLexer()->mark(); }
    break;

  case 592:

    { (yyval.nest) = m_pDriver->getLexer()->nest(); }
    break;

  case 593:

    { (yyval.line) = YACC_LINE(); m_pDriver->getLexer()->start_search(false); }
    break;

  case 594:

    { (yyval.line) = YACC_LINE(); m_pDriver->getLexer()->start_search(true); }
    break;

  case 595:

    { (yyval.utility) = YACC_UTILITY_MODE(); }
    break;



      default:
        break;
      }

    /* User semantic actions sometimes alter yychar, and that requires
       that yytoken be updated with the new translation.  We take the
       approach of translating immediately before every use of yytoken.
       One alternative is translating here after every semantic action,
       but that translation would be missed if the semantic action
       invokes YYABORT, YYACCEPT, or YYERROR immediately after altering
       yychar.  In the case of YYABORT or YYACCEPT, an incorrect
       destructor might then be invoked immediately.  In the case of
       YYERROR, subsequent parser actions might lead to an incorrect
       destructor call or verbose syntax error message before the
       lookahead is translated.  */
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yytranslate_ (yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	if (yychar == yyempty_)
	  yytoken = yyempty_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[1] = yylloc;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */
        if (yychar <= yyeof_)
          {
            /* Return failure if at end of input.  */
            if (yychar == yyeof_)
              YYABORT;
          }
        else
          {
            yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
            yychar = yyempty_;
          }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[1] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (!yy_pact_value_is_default_ (yyn))
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	  YYABORT;

	yyerror_range[1] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[2] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      {
        /* Make sure we have latest lookahead translation.  See comments
           at user semantic actions for why this is necessary.  */
        yytoken = yytranslate_ (yychar);
        yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval,
                     &yylloc);
      }

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystate_stack_.height ())
      {
        yydestruct_ ("Cleanup: popping",
                     yystos_[yystate_stack_[0]],
                     &yysemantic_stack_[0],
                     &yylocation_stack_[0]);
        yypop_ ();
      }

    return yyresult;
    }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (yychar != yyempty_)
          {
            /* Make sure we have latest lookahead translation.  See
               comments at user semantic actions for why this is
               necessary.  */
            yytoken = yytranslate_ (yychar);
            yydestruct_ (YY_NULL, yytoken, &yylval, &yylloc);
          }

        while (1 < yystate_stack_.height ())
          {
            yydestruct_ (YY_NULL,
                         yystos_[yystate_stack_[0]],
                         &yysemantic_stack_[0],
                         &yylocation_stack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  // Generate an error message.
  std::string
  CxxParser::yysyntax_error_ (int yystate, int yytoken)
  {
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yychar.
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            /* Stay within bounds of both yycheck and yytname.  */
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULL;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const short int CxxParser::yypact_ninf_ = -778;
  const short int
  CxxParser::yypact_[] =
  {
        37,  -778,   100,   103,  2767,  -778,  -778,  4423,  4423,  -778,
    -778,  4423,  4423,  4009,  2767,  -778,    -6,  4423,  4423,  -778,
    -778,  -778,  -778,  -778,  -778,  -778,  -778,  -778,  -778,  -778,
    -778,  -778,   626,  -778,    74,  -778,  -778,  -778,  -778,  -778,
    -778,  -778,  -778,  -778,  -778,  -778,  5028,  -778,  -778,   152,
    4423,   154,  -778,  5101,  4561,   174,  4423,   225,  -778,  4009,
    -778,   250,   307,  -778,  -778,  -778,  -778,  -778,  -778,  -778,
    -778,  -778,  -778,  -778,   332,  -778,   340,   342,   338,  -778,
    -778,  -778,  -778,  -778,  -778,  -778,  -778,   217,  -778,  4634,
     809,   353,  -778,  -778,  -778,  -778,   197,   516,   317,   425,
     559,   233,   382,   439,   401,   415,  2070,  -778,   429,  -778,
    5242,   923,  5242,  -778,   930,  -778,  -778,   451,  -778,  2767,
    -778,  -778,  -778,  -778,  -778,  -778,  -778,   414,  -778,  4423,
    -778,  -778,  -778,  -778,  -778,   448,  -778,  -778,  -778,   624,
    -778,  -778,  -778,  -778,  -778,   322,  1795,  5130,  -778,  4423,
    -778,  -778,  -778,   516,   463,   464,  -778,  -778,  2767,   466,
      44,  -778,  -778,  -778,  -778,  -778,   109,    74,   171,   171,
     479,  -778,  -778,  5422,   472,  -778,  -778,  -778,  -778,  -778,
    -778,  -778,  5495,  -778,  5495,  1438,  -778,   515,  1329,  -778,
    -778,  -778,  -778,  5101,  -778,  -778,  -778,  -778,  -778,  -778,
    -778,  -778,  -778,  -778,  -778,  -778,  -778,   484,   495,  -778,
    -778,  -778,  -778,  -778,  -778,  -778,  -778,  -778,  -778,  -778,
    -778,  -778,  -778,  -778,  -778,  -778,  -778,  -778,  -778,  -778,
    -778,  -778,  -778,  -778,  1473,  -778,  -778,  5495,  -778,  -778,
    5495,  -778,  -778,  1006,  -778,   503,  -778,   388,  -778,  -778,
    -778,  -778,  -778,   171,    71,  -778,  -778,  -778,  -778,  -778,
    -778,  4009,  1088,  1088,  -778,  -778,  -778,  4009,  4423,  4423,
    4423,  4423,  3595,  4423,  4423,  4423,  4423,  4423,  4423,  4423,
    4423,  4423,  4423,  4423,  4423,  4423,  4423,   519,  4009,  4423,
    -778,  -778,  -778,  -778,  -778,  -778,  -778,  -778,  -778,  -778,
    4009,  -778,  -778,  -778,   536,  1357,   388,    71,  1395,  -778,
    5242,  -778,   543,  -778,  -778,  3595,  -778,  -778,  -778,  -778,
     255,  4009,   540,   976,  -778,   426,  -778,  -778,  4423,  -778,
     691,   184,   456,  4802,    69,   580,   210,   119,  -778,  -778,
    -778,  -778,  -778,  -778,  -778,  2491,  -778,  -778,  -778,  -778,
    -778,  -778,   496,   578,  -778,  -778,  -778,    54,   551,  -778,
    -778,  2353,  -778,   554,  5524,  3595,  4423,  -778,  -778,  -778,
    2767,  -778,  -778,  -778,  -778,   210,   279,   609,   171,  -778,
    3319,  1217,   607,   613,  4009,  -778,  4009,   147,   147,  -778,
    -778,   606,   617,  -778,   515,   515,  -778,  -778,   642,  -778,
    -778,   619,   622,  -778,  -778,  -778,  -778,  -778,  -778,  -778,
    -778,  -778,   615,  2905,  -778,  -778,  -778,   621,  1920,  1088,
    1252,  1581,  -778,  -778,  -778,  -778,  1773,  -778,  -778,  -778,
    -778,  -778,  -778,   561,   618,  -778,  -778,   197,   197,   197,
    4423,  -778,   516,   516,   317,   317,   425,   425,   425,   425,
     559,   559,   233,  -778,   463,   439,   401,   632,  -778,   630,
     415,  -778,   649,  -778,  -778,  -778,  -778,  -778,   546,  -778,
    -778,  -778,  -778,  -778,  -778,   976,  -778,   315,  -778,   976,
    -778,  -778,   641,   657,   140,  -778,  -778,   347,  -778,   656,
    -778,   652,  3043,  5276,  -778,  -778,    74,   486,   486,   658,
     456,  -778,   107,  4423,  -778,  4009,   671,  -778,  -778,  -778,
    -778,  -778,  -778,  -778,  4009,  -778,  4009,  -778,  -778,  3733,
    -778,  1795,  -778,  -778,  -778,  -778,   681,   113,  -778,   696,
     345,  4147,   425,    73,   309,   693,   695,   697,   667,  2152,
    -778,  -778,  3319,  -778,  -778,   698,   235,  -778,  -778,   775,
    -778,  -778,   417,   438,   687,   699,   694,   686,  -778,   705,
    4423,   340,   147,   147,  -778,  -778,  -778,  -778,   706,   707,
    -778,  -778,   267,  -778,  1516,  -778,  1516,  1252,  4715,  -778,
    1581,  -778,   720,  -778,  2075,  -778,  -778,   381,   591,  2215,
    4009,   722,  -778,   598,  1935,  -778,  -778,   976,  -778,  -778,
     329,   718,  4423,  -778,    74,  -778,  3457,  -778,  -778,  2353,
     122,    74,  4882,  -778,   679,   273,  -778,   736,   740,   756,
     729,   733,  -778,   742,   210,   210,   739,  -778,   752,  -778,
    -778,    74,   683,   757,  -778,  -778,  -778,  -778,  -778,  -778,
    -778,  4423,  -778,  -778,  -778,   780,   763,  -778,  -778,   779,
    -778,  4423,  4423,  4423,  4423,  4423,  4423,  4423,  4423,  4423,
    -778,  4147,  4423,  4147,  -778,  4147,  -778,  3319,  -778,  4285,
    -778,  4009,  4009,  -778,  4009,  -778,   286,  -778,   771,  4009,
    4009,  -778,  4715,  4729,  1516,  -778,  2767,   545,  -778,   773,
    -778,  -778,  -778,   574,  -778,  5203,  -778,  -778,   905,   485,
    2629,  -778,  -778,   481,  -778,  -778,  -778,   553,  -778,   778,
    -778,   586,  -778,  -778,  -778,   781,   782,   761,  -778,   210,
    -778,  3457,  5495,   210,  -778,  -778,  -778,   768,   676,  -778,
    -778,   210,  -778,   660,  1654,  -778,    87,    74,  -778,   783,
     784,  -778,   683,  -778,  -778,   393,  4423,   425,   425,   425,
      73,    73,   309,  -778,   779,   695,   697,   776,   790,   777,
     667,  -778,  -778,  -778,  -778,   791,   792,   795,  -778,  -778,
     796,   797,  4729,  1516,   569,   238,  -778,  -778,   685,   823,
    2215,  -778,  -778,  -778,   180,   831,  -778,  3871,  -778,  -778,
    3871,  -778,  3871,  -778,  1935,  -778,  4423,  -778,  -778,  -778,
    -778,  -778,  -778,  -778,  -778,   210,  -778,  -778,    74,  4955,
     804,  4423,   806,   821,  -778,   826,   210,   827,  4009,   828,
     757,   829,   836,   811,  -778,  -778,  -778,  -778,  -778,  -778,
    -778,  -778,  -778,  -778,  3181,  -778,   588,  -778,   852,  -778,
    4009,  2767,  -778,  -778,  4147,  4147,  -778,  -778,  -778,  -778,
    -778,  -778,  -778,   853,  -778,   837,  -778,  -778,  5495,   349,
     839,  -778,  -778,   839,  -778,  -778,  -778,  -778,   715,  -778,
     860,   855,  5349,  -778,   851,  -778,  -778,   753,  3181,   841,
    2767,   843,  2767,   683,  2767,  -778,  1654,  -778,   862,   864,
    -778,   872,  -778,   865,  -778,   883,  -778,  -778,  -778,  -778,
    -778,   397,  -778,  -778,   876,  2767,  -778,  -778,   878,   868,
    -778,   879,  -778,   884,  -778,  -778,  -778,  -778,   757,   885,
     909,  -778,  -778,  -778,  4009,   888,  -778,  -778,  -778,  -778,
    -778,  -778,   403,   900,  4009,   822,  -778,  -778,  -778,   893,
     903,  -778,  -778,  -778,  -778,  -778
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned short int
  CxxParser::yydefact_[] =
  {
       246,   593,     0,   595,     0,     1,   594,     0,     0,   371,
     375,     0,     0,   178,   403,    21,     0,     0,     0,   415,
     329,   327,   336,   335,   331,   332,   330,   333,   334,   337,
     328,   459,     0,   460,     0,   461,   384,   385,   314,   315,
     313,   304,   316,   312,   310,   311,     0,   305,   317,     0,
       0,     0,    61,     0,     0,     0,     0,     0,    69,   581,
      62,     0,     0,    58,     2,    51,    52,    53,    54,    55,
      56,    57,    50,     3,    15,     4,    24,     0,     0,    26,
     286,    33,    36,   293,    59,    68,    60,     0,    78,    71,
      99,     0,   128,   112,   110,   130,   133,   137,   140,   143,
     148,   151,   153,   155,   157,   159,   161,   163,   180,    64,
     284,   296,   289,   291,   294,   298,    70,     0,   308,     0,
     302,   303,   287,   281,   323,   339,   322,   373,   376,   378,
     408,   306,    72,   382,   410,   413,    63,   338,   464,     0,
     321,    30,    31,    19,   166,   247,     0,     0,   105,     0,
     106,   108,   107,   137,   153,     0,   179,   416,     0,     0,
     404,   417,   406,   103,   101,   100,   351,     0,     0,     0,
     341,   343,   340,     0,     0,    22,    32,   285,   309,   324,
      74,   571,     0,   114,     0,     0,   325,   126,   380,   319,
     318,   326,   320,   117,   517,   518,   519,   520,   521,   522,
     523,   524,   525,   526,   528,   529,   527,     0,     0,   550,
     552,   551,   549,   542,   545,   548,   544,   546,   547,   543,
     538,   539,   530,   536,   533,   534,   532,   537,   541,   540,
     531,   535,   516,   515,   380,   501,   514,     0,    71,   109,
       0,   582,    94,     0,    20,     0,    23,     0,    27,    37,
     113,   111,   377,     0,     0,    25,    34,    35,   374,    67,
     129,   178,     0,     0,    89,    88,    77,     0,     0,     0,
       0,     0,   380,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   411,     0,     0,     0,   167,     0,     0,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
       0,   307,   283,   282,    21,     0,     0,     0,   294,   297,
     290,   288,    21,   295,   292,     0,    65,   372,   102,   379,
     398,     0,   595,     0,   458,   453,   590,   589,     0,   277,
       0,     0,   313,     0,     0,     0,     0,   370,   249,   250,
     257,   258,   253,   271,   270,     0,   260,   273,   274,   275,
     272,   259,     0,     0,   254,   427,   426,     0,   491,   434,
     255,     0,   256,     0,     0,     0,     0,    73,   418,   402,
       0,   405,   347,   344,   353,     0,   590,     0,     0,   342,
       0,   388,     0,     0,    95,   115,     0,     0,     0,   121,
     120,   123,   380,   119,   126,   126,   554,   553,   380,   502,
     503,     0,     0,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,    18,    28,    29,     0,     0,     0,
       0,     0,    38,    40,    39,    84,     0,    46,    48,    85,
      41,    86,    87,     0,   181,   132,   131,   135,   136,   134,
     380,   409,   138,   139,   141,   142,   144,   145,   147,   146,
     149,   150,   152,   412,   154,   156,   158,   593,   165,     0,
     160,   164,    21,   104,   397,   396,   383,   399,   400,   414,
     462,   593,   498,   499,   500,     0,   495,     0,   493,     0,
     452,   457,     0,     0,   489,   488,   592,     0,   360,     0,
     556,   594,   590,     0,   261,   276,     0,     0,     0,     0,
       0,   267,   264,     0,   226,     0,   504,   438,   428,   429,
     280,   430,   433,   279,     0,   278,     0,   431,   432,     0,
     555,     0,   252,   407,   358,   355,   356,   351,   345,     0,
       0,   583,   183,   187,   190,   192,   194,   196,   198,   200,
     202,   419,     0,   423,   574,   420,     0,   572,   204,   388,
     387,   386,     0,   390,     0,     0,     0,    96,    97,     0,
       0,     0,     0,     0,   122,   381,   116,   118,     0,     0,
      14,    17,     0,    83,    44,    45,     0,     0,     0,    49,
       0,    47,     0,    42,     0,    79,   443,     0,   446,     0,
       0,     0,   401,   465,     0,   497,   456,     0,   496,   454,
       0,     0,     0,   246,     0,   359,   590,   367,   366,     0,
     459,   567,     0,   564,     0,     0,   558,   560,   562,     0,
       0,     0,   362,     0,     0,     0,   269,   487,   593,   370,
     368,     0,     0,     0,   505,   369,   435,   439,   492,   440,
     251,     0,   349,   346,   354,     0,     0,   348,   352,   192,
     584,     0,     0,     0,     0,     0,   424,     0,     0,     0,
     167,     0,     0,     0,   422,     0,   570,     0,   389,     0,
     393,     0,     0,   127,     0,   124,   161,   182,     0,     0,
       0,    16,     0,     0,     0,    82,   591,     0,   441,   593,
     590,   449,   448,     0,   162,     0,   590,   476,     0,     0,
       0,   474,   473,     0,   467,   468,   472,     0,   471,     0,
     475,     0,   494,   455,   248,     0,   595,     0,   575,   568,
     557,   590,     0,     0,   565,   364,   363,     0,   262,   265,
     268,     0,   224,   227,     0,   513,   506,     0,   508,     0,
       0,   436,   577,   437,   357,     0,     0,   184,   186,   185,
     188,   189,   191,   425,   193,   195,   197,   205,     0,     0,
     199,   203,   421,   573,   394,     0,     0,     0,    98,   125,
       0,     0,     0,    43,     0,     0,    75,   442,   447,     0,
       0,   451,   585,   587,     0,     0,   477,     0,   480,   478,
       0,   479,     0,   486,     0,   470,     0,   244,   594,   361,
     569,   559,   561,   563,   365,     0,   266,   590,     0,     0,
       0,     0,     0,     0,   593,     0,     0,     0,   178,     0,
       0,     0,     3,   370,   209,   210,   213,   217,   214,   218,
     219,   220,   215,   243,     0,   216,     0,   510,     0,   509,
      95,     0,   578,   350,     0,     0,   395,    93,    90,    92,
      91,    76,    81,     0,   590,     0,   450,   586,     0,     0,
     484,   481,   485,   435,   482,   483,   469,   490,   247,   263,
       0,     0,     0,   239,     0,   240,   593,     0,     0,     0,
       0,     0,     0,     0,     0,   593,     0,   212,   507,     0,
     580,     0,   201,   206,    80,     0,   444,   588,   463,   466,
     590,     0,   593,   223,     0,   232,   238,   242,     0,   234,
     241,     0,   576,     0,   221,   211,   511,   512,     0,     0,
       0,   225,   228,   222,     0,     0,   233,   593,   593,   593,
     579,   445,     0,     0,   178,   229,   231,   235,   245,     0,
       0,   593,   236,   593,   230,   237
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  CxxParser::yypgoto_[] =
  {
      -778,  -663,   358,  -778,  -778,  -208,  -778,   628,   877,   366,
     -18,   -47,   719,     1,   -94,  -212,  -359,  -365,  -394,   352,
    -276,  -778,  -778,   807,  -778,  -778,   871,  -778,  -778,  -778,
      88,  -360,   881,   857,   866,   -63,   547,  -778,   222,    84,
      25,     3,   355,   965,   375,  -171,    -2,   647,   655,   659,
    -241,  -528,    35,   405,  -255,    -4,  -579,    31,  -595,   372,
     288,   290,   291,  -778,  -778,  -487,  -778,  -778,  -399,    64,
    -778,  -778,  -778,  -681,  -778,  -778,  -778,  -777,  -778,  -778,
    -778,  -778,   -73,   354,  -476,   431,  -339,  -268,   224,  -778,
    -778,  -778,  -658,  -310,  -341,   844,   -41,  -778,   -54,   848,
     849,  -778,  -778,   -55,   856,    26,  -778,  -778,   260,   247,
    -778,   835,  -778,  -778,  -778,   793,   589,  -778,   437,  -778,
    -778,  -778,  -778,  -778,  -778,  -568,  -778,  -778,  -778,  -778,
    -262,   -34,   -49,    -3,   838,   -80,  -778,    16,  -163,   422,
    -778,  -778,  -778,  -778,   -43,    36,  -778,     4,  -231,  -778,
      77,  -149,  -458,  -778,  -552,  -312,  -307,  -553,  -317,  -778,
    -318,   453,   688,  -778,   285,   196,  -778,  -778,  -778,  -778,
    -778,  -778,  -778,   183,  -778,   281,  -778,   187,  -778,  -778,
    -478,  -463,   502,  -411,  -536,  -778,   751,  -778,  -778,  -778,
    -778,   249,  -778,  -778,  -778,  -321,  -446,  -778,   266,  -778,
    -778,   -27,   576,   323,  -778,  -778,  -675,  -778,  -778,  -778,
    -778,  -778,  -778,  -546,  -129,  -778,  -778,    12,  -778,  -314
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  CxxParser::yydefgoto_[] =
  {
        -1,    73,    74,   412,    75,    76,   245,    77,    78,    79,
      80,   423,    81,    82,    83,   499,   426,   427,   428,   579,
      84,    85,    86,    87,     2,    88,    89,   686,   433,    90,
     556,    91,    92,    93,    94,   187,   390,   391,   385,    95,
      96,   153,    98,    99,   100,   101,   154,   103,   104,   105,
     106,   107,   108,   300,   155,   156,   678,   533,   534,   649,
     536,   537,   538,   539,   540,   541,   758,   759,   733,   824,
     825,   826,   827,   507,   628,   829,   925,   908,   830,   905,
     831,   832,   488,     3,   145,   338,   339,   340,   729,   626,
     502,   341,   342,   343,   344,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   302,   158,   120,   121,   381,   122,
     190,   123,   124,   125,   126,   171,   373,   643,   374,   375,
     376,   525,   526,   346,   347,   348,   349,   350,   351,   352,
     353,   127,   128,   149,   130,   565,   320,   131,   382,   551,
     552,   553,   467,   468,   132,   133,   159,   909,   134,   135,
     161,   162,   544,   545,   354,   355,   356,   357,   508,   632,
     509,   691,   639,   587,   588,   692,   482,   137,   138,   139,
     140,   322,   593,   704,   705,   706,   707,   861,   708,   358,
     485,   359,   477,   478,   479,   141,   235,   633,   634,   736,
     737,   738,   739,   142,   236,   360,   361,   615,   616,   617,
     618,   143,   546,   547,   362,   835,   741,   742,   891,   144,
     548,   592,   784,   363,   619,   775,   603,   734,   146,     6
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int CxxParser::yytable_ninf_ = -591;
  const short int
  CxxParser::yytable_[] =
  {
       109,   129,   102,   180,   510,   177,   417,    97,   471,   368,
     490,   129,   102,     4,   170,   608,   172,    97,   160,   181,
     313,   383,   520,   495,   557,   627,   701,   581,   252,   258,
     119,   256,   677,   511,   613,   186,   186,   377,   512,   518,
     517,   703,   702,   693,   650,   415,   614,   266,   711,   157,
     425,   431,   453,   828,   575,   301,   491,   301,   709,   574,
     314,   752,   744,   272,   595,   494,     1,   842,   598,   192,
     192,   822,   178,   504,   401,   370,   833,   402,   249,   257,
     253,   136,   253,   315,   664,   516,   651,   484,  -590,   193,
     765,   148,   150,    15,   241,   151,   152,   242,    15,   371,
       5,   164,   165,   -66,   180,   911,   177,   913,   393,   652,
    -590,   653,   452,   677,  -590,   109,   129,   102,   837,   365,
     181,   325,    97,   624,   715,   389,   129,   163,   926,   372,
     394,   625,   177,   642,   183,   503,  -566,  -566,   504,   883,
     181,   677,   496,   317,   497,   119,   181,   703,   613,   543,
     505,   752,     9,  -566,   399,   129,   102,   498,   181,   254,
     614,    97,   167,   602,   186,   182,   186,   184,   424,   424,
     186,   506,   345,   260,   757,   186,   761,    54,   762,    54,
     289,   337,   543,   495,   561,   392,   712,   237,   836,    62,
     561,    62,   441,   157,    62,   452,   136,   483,   192,   178,
     192,    64,   857,    64,   192,   828,    64,   416,   912,   192,
     415,   858,   575,   318,   313,   575,   186,   574,   550,   186,
     181,   523,   186,   822,   623,   494,   701,   181,   833,   395,
     268,   398,   874,   318,   693,   378,   506,   930,   240,   852,
     424,   703,   702,   630,   422,   422,   259,   529,   711,   666,
     192,   269,   635,   192,   314,   301,   192,   853,   709,   378,
     256,   543,   484,   613,   464,   331,   667,    62,   281,   440,
     718,    14,   489,   710,   282,   614,   442,   443,   181,    64,
     129,   681,   454,   677,   459,   621,    97,   720,   317,   581,
     180,    62,   177,   179,   465,   437,   438,   439,   667,   372,
     189,   189,   434,    64,   721,   476,   181,   249,   257,   288,
     527,   543,   487,   188,   234,   743,   422,   575,   867,   676,
     273,   274,   868,   177,   862,   773,   289,   864,   243,   862,
      62,   317,    36,    37,   596,   461,   466,   181,   252,   258,
     836,   561,    64,     9,   654,   244,   597,     9,   713,   253,
     655,   181,   435,   436,   561,   561,   469,   892,   893,   178,
     597,   484,   604,   186,   246,   647,   486,   129,   102,   898,
     561,   345,   416,    97,   256,   543,   648,   129,   549,   899,
     337,   317,   559,    97,   267,   518,   517,   345,   511,   392,
     439,   283,   181,   512,   179,   398,   337,   192,   645,   463,
     676,   688,   798,   424,   174,   157,   542,   575,   365,   365,
     129,   285,   689,   843,   605,   877,    97,   921,   607,   558,
     179,   249,   257,   938,   648,   753,   254,   922,   676,   189,
     247,   189,   179,   714,   669,   189,   543,   440,    14,   542,
     189,    50,   480,   248,   255,   481,    54,   284,   188,    53,
      54,   416,   177,   188,   286,  -392,     9,   476,    62,  -392,
     -97,   476,    62,   321,   476,   326,   181,   275,   276,   589,
      64,   181,   366,   710,    64,   561,   247,   903,   620,   422,
     557,   189,   367,   594,   189,   380,   914,   189,   369,   129,
     543,    36,    37,   510,   234,    97,    54,   253,   166,   495,
     504,   503,   396,   923,   504,   174,   413,   414,    62,   670,
      15,   789,   790,   252,   258,   786,   787,   397,   542,   178,
      64,     9,   270,   271,   318,   174,   513,   514,   935,   936,
     937,   174,   783,   416,   248,   255,   384,   906,   457,   129,
     629,  -301,   944,   174,   945,    97,   549,   345,  -299,   629,
     181,   636,   179,   181,   637,   484,   337,   521,   522,   802,
     470,   779,   495,   881,   584,   585,   519,   785,   542,   180,
     676,   177,   277,   278,   498,   776,   370,   780,   781,   476,
     179,   129,   102,   791,   792,   181,   717,    97,   687,   794,
     795,   886,   887,   172,    54,   279,    72,   280,   506,   851,
     370,   500,   506,   129,   424,   174,    62,   838,   515,    97,
     530,   179,   174,   735,   429,   432,   566,   567,    64,   157,
     700,   554,     9,   560,   637,   694,    10,   555,   189,   699,
     444,   445,   542,   568,   386,   345,   569,   570,   178,   573,
     323,    15,   599,   324,   337,   166,   590,     9,    15,   -98,
      15,    10,   586,   129,  -300,   181,   450,   451,   601,    97,
     168,   591,   168,   174,   129,    15,    15,   766,   767,   606,
      97,   486,   248,   255,   175,   770,   771,   186,   870,   940,
     422,   168,   168,   129,   102,   750,   751,   631,   622,    97,
     774,   174,   890,   542,   501,   897,   641,   646,   472,   473,
     474,   589,   656,   657,   186,   167,   659,   658,   671,   768,
     486,   192,   167,   665,   167,    15,   673,   674,   129,   735,
     672,   157,   174,   675,    97,   895,   700,   679,   680,   167,
     167,   684,   475,   524,   690,   699,   174,    62,   192,   306,
     179,   696,   306,   695,    62,   181,    62,   542,   714,    64,
     719,   722,   535,   248,   255,   723,    64,   724,    64,   725,
     834,    62,    62,   726,   727,   176,   180,   168,   177,   823,
     731,   920,   732,    64,    64,   175,   504,   174,   740,   167,
       9,   745,   181,   647,    10,   535,   248,   255,   746,   769,
     871,   799,  -391,   777,   793,   175,  -391,   796,   804,    15,
     805,   175,   797,   807,   840,   841,   844,  -207,   845,   846,
     168,    62,   168,   175,   847,   637,   387,   848,   849,   850,
     700,   168,   860,    64,   855,   863,   261,   860,   854,   699,
      14,   177,   859,   262,   873,   178,   875,   876,   129,   102,
     186,   263,   505,   264,    97,   181,   265,   878,   880,   882,
     884,   174,   885,   888,   894,   503,   174,   896,   900,   179,
     834,   901,   387,   167,   535,   168,   176,   902,   168,   823,
     604,   907,   904,   910,   192,   558,   157,   129,   102,   129,
     102,   129,   102,    97,   919,    97,   917,    97,   191,   191,
     420,   420,   176,   916,   918,    62,  -208,   924,   178,   370,
     927,   928,   129,   102,   834,   931,   929,    64,    97,   169,
     932,   169,   834,   823,   535,   157,   253,   157,   934,   157,
     933,   823,   939,   942,   941,   943,   316,   238,   889,    15,
     169,   169,   455,   175,   250,   174,   306,   239,   174,   564,
     157,   456,   189,   251,   663,   303,   755,   304,   460,   756,
     915,   168,   640,   760,   312,   806,   310,   716,   168,   308,
     309,   175,   306,   379,   644,   528,   176,   319,   311,   189,
     174,   668,   638,   176,   778,   458,   856,   866,   535,   865,
     497,   788,   728,   730,   600,   400,   839,   801,   307,   572,
     763,   307,   175,   498,    31,    32,     0,    33,    34,    35,
      15,    31,    32,     0,    33,    34,    35,     0,     0,   387,
       0,   305,     0,    54,     0,     0,   169,   191,   305,   191,
     562,     0,     0,   191,   176,    62,   562,     0,   191,   754,
       0,    54,     0,   472,   473,   474,     0,    64,    54,   535,
     174,     0,     0,    62,     0,   169,   169,   175,   578,     0,
      62,     0,   176,     0,     0,    64,   179,     0,     0,   169,
       0,   169,    64,     0,   167,   388,     0,   475,     0,   191,
     169,     0,   191,     0,     0,   191,     0,   800,     0,     0,
       0,   803,     0,   176,     0,     0,     0,     0,     0,   728,
       0,     0,     0,   535,     0,     0,    62,   430,   430,   418,
       0,     0,     0,   168,     0,   189,     0,   168,    64,     0,
     168,   388,    15,     0,   169,     0,     0,   169,     0,   179,
       0,   175,     0,     0,   168,   306,   175,   403,   404,   405,
     174,   406,   407,   408,   409,   410,   411,     0,   176,   421,
     421,     0,     0,     0,     0,   303,     0,     0,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,     0,
       0,     0,     0,   869,     0,     0,     0,   174,     0,     0,
       0,     0,     0,     0,   879,     0,   419,   562,     0,     0,
       0,     0,     0,   307,   307,   307,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    54,     0,     0,     0,
     169,     0,     0,     0,     0,   175,   578,   169,    62,     0,
       0,   307,   176,     0,     0,     0,   191,   176,     0,     0,
      64,     0,     9,     0,     0,   168,    10,     0,     0,     0,
     174,     0,   168,     0,  -391,     0,     0,     0,  -391,   168,
     175,    15,   446,   447,   448,   449,     0,     0,     0,     0,
       0,     0,     0,   430,   430,   430,   430,     0,   388,   168,
       0,   583,     0,   576,   388,   388,     0,     0,     0,   563,
       0,     0,     0,     0,     0,   563,    15,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
       0,    33,    34,    35,    36,    37,   176,   421,   421,   176,
       0,     0,     0,     0,     0,   185,     0,     0,     0,     0,
     175,     0,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   168,     0,     0,   306,     0,     0,     0,
       0,   176,     0,     0,     9,     0,     0,    62,    10,     0,
     577,     0,     0,     0,     0,   532,   386,     0,     0,    64,
     168,     0,   169,    15,     0,     0,   169,     0,     0,   169,
      54,     0,     0,     0,     0,   168,     0,     0,     0,     0,
       0,     0,    62,   169,   307,     0,     0,     0,   532,     0,
       0,    15,     0,     0,    64,     0,     0,     0,     0,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,     0,    33,    34,    35,    36,    37,     0,   583,
       0,   430,   430,   430,     0,   430,     0,   185,     0,   462,
       0,     0,     0,     0,     0,     0,   563,     0,    31,    32,
       0,    33,    34,    35,     0,     0,   168,   175,     0,   563,
     563,     0,     0,     0,     0,   305,     0,     0,     0,    62,
       0,     0,     0,     0,     0,   683,     0,   532,     0,     0,
       0,    64,    15,     0,     0,    54,    31,    32,     0,    33,
      34,    35,     0,     0,   169,     0,     0,    62,     9,     0,
       0,   169,    10,   305,     0,     0,   168,     0,   169,    64,
       0,     0,     0,     0,     0,     0,   532,    15,     0,     0,
     175,     0,     0,    54,     0,     0,     0,   532,   169,    31,
      32,     0,    33,    34,    35,    62,     0,   430,   430,   430,
       0,     0,     0,     0,     0,     0,   185,    64,   176,     0,
     191,     0,     0,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,     0,    33,    34,    35,
      36,    37,     0,     0,     0,     0,     0,   191,    62,     0,
     683,   185,     0,     0,     0,     0,     0,     0,     0,     0,
      64,   532,   169,     0,     0,   307,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,     0,     0,     0,
       0,   176,   418,    62,     0,     0,     0,     0,     0,   169,
       0,     0,     0,     0,     0,    64,     0,   430,   583,     0,
       0,     0,     0,     0,   169,     0,   747,   748,   749,   532,
     532,   532,   532,   532,   532,     0,   532,   532,   532,     0,
     532,     0,   532,     0,     0,     0,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,     0,     0,     0,   327,     0,     7,     8,     9,
       0,     0,     0,    10,     0,    11,    12,     0,     0,   580,
       0,    13,     0,   504,     0,    14,     0,     0,    15,     0,
       0,     0,    16,     0,   329,   169,   532,     0,    17,    54,
       0,    18,     0,   191,     0,     0,     0,     0,     0,     0,
       0,    62,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   532,     0,    64,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,   808,    33,    34,
      35,    36,    37,    38,    39,   169,    40,    41,    42,    43,
      44,    45,   809,    47,   334,    48,   335,   810,   811,     0,
      49,   812,   813,    50,   814,    51,     0,    52,   815,   816,
     817,    53,    54,    55,   818,    56,    57,   819,    58,    59,
      60,   820,    61,   821,    62,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,     0,   327,   582,     7,     8,
       9,     0,     0,     0,    10,     0,    11,    12,     0,   532,
     532,   328,    13,     0,     0,     0,    14,     0,     0,    15,
       0,     0,     0,    16,     0,   329,     0,     0,     0,    17,
       0,     0,    18,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,   330,    33,
      34,    35,    36,    37,    38,    39,   331,   332,    41,    42,
      43,    44,    45,   333,    47,   334,    48,   335,     0,     0,
       0,    49,     0,     0,    50,     0,    51,     0,    52,     0,
       0,     0,    53,    54,    55,     0,    56,    57,     0,    58,
      59,    60,     0,    61,     0,    62,     0,     0,   336,     0,
       0,     0,     0,     0,     0,     0,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,   327,     0,     7,     8,
       9,     0,     0,     0,    10,     0,    11,    12,     0,     0,
       0,   328,    13,     0,     0,     0,    14,     0,     0,    15,
       0,     0,     0,    16,     0,   697,     0,     0,     0,    17,
       0,     0,    18,     0,     0,     0,     0,     0,     0,     0,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,     0,   472,   473,   474,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,   378,    33,
      34,    35,    36,    37,    38,    39,   331,    40,    41,    42,
      43,    44,    45,   612,    47,   698,    48,     0,     0,     0,
       0,    49,     0,     0,    50,     0,    51,     0,    52,     0,
      62,     0,    53,    54,    55,     0,    56,    57,     0,    58,
      59,    60,    64,    61,     0,    62,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,   685,     0,     7,     8,
       9,     0,     0,     0,    10,   287,    11,    12,     0,     0,
       0,     0,    13,   288,     0,     0,    14,     0,     0,    15,
       0,     0,     0,    16,     0,     0,     0,     0,     0,    17,
     289,     0,    18,     0,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,     0,     0,     0,     0,     0,     0,
      19,     0,     0,     0,     0,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,     0,    33,
      34,    35,    36,    37,    38,    39,     0,    40,    41,    42,
      43,    44,    45,    46,    47,     0,    48,   660,     0,     0,
       0,    49,     0,     0,    50,   661,    51,     0,    52,     0,
       0,     0,    53,    54,    55,     0,    56,    57,     0,    58,
      59,    60,   662,    61,     0,    62,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,   327,     0,     7,     8,
       9,     0,     0,     0,    10,     0,    11,    12,     0,     0,
       0,     0,    13,     0,   457,     0,    14,     0,     0,    15,
       0,     0,     0,    16,     0,     0,     0,     0,     0,    17,
       0,     0,    18,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,     0,    33,
      34,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   147,     0,     0,     0,     0,     0,     0,
       0,    49,     0,     0,    50,     0,    51,     0,    52,     0,
       0,     0,    53,    54,    55,     0,    56,    57,     0,    58,
      59,    60,     0,    61,     0,    62,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,     7,     8,     9,     0,
       0,     0,    10,     0,    11,    12,     0,     0,     0,   328,
      13,     0,     0,     0,    14,     0,     0,    15,     0,     0,
       0,    16,     0,   329,     0,     0,     0,    17,     0,     0,
      18,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,   330,    33,    34,    35,
      36,    37,    38,    39,   331,   332,    41,    42,    43,    44,
      45,   333,    47,   334,    48,   335,     0,     0,     0,    49,
       0,     0,    50,     0,    51,     0,    52,     0,     0,     0,
      53,    54,    55,     0,    56,    57,     0,    58,    59,    60,
       0,    61,     0,    62,     0,     0,   336,     0,     0,     0,
       0,     0,     0,     0,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,     7,     8,     9,     0,     0,     0,
      10,     0,    11,    12,     0,     0,     0,   328,    13,     0,
       0,     0,    14,     0,     0,    15,     0,     0,     0,    16,
       0,   329,     0,     0,     0,    17,     0,     0,    18,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     0,    33,    34,    35,    36,    37,
      38,    39,     0,    40,    41,    42,    43,    44,    45,    46,
      47,     0,    48,     0,     0,     0,     0,    49,     0,     0,
      50,     0,    51,     0,    52,     0,     0,     0,    53,    54,
      55,     0,    56,    57,     0,    58,    59,    60,     0,    61,
       0,    62,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,     7,     8,     9,     0,     0,     0,    10,     0,
      11,    12,     0,     0,     0,   328,    13,     0,     0,     0,
      14,     0,     0,    15,     0,     0,     0,    16,     0,   697,
       0,     0,     0,    17,     0,     0,    18,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,     0,    33,    34,    35,    36,    37,    38,    39,
       0,    40,    41,    42,    43,    44,    45,    46,    47,     0,
      48,     0,     0,     0,     0,    49,     0,     0,    50,     0,
      51,     0,    52,     0,     0,     0,    53,    54,    55,     0,
      56,    57,     0,    58,    59,    60,     0,    61,     0,    62,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
       7,     8,     9,     0,     0,     0,    10,     0,    11,    12,
       0,     0,     0,     0,    13,     0,     0,     0,    14,     0,
       0,    15,     0,     0,     0,    16,     0,     0,     0,     0,
       0,    17,     0,     0,    18,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    19,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
       0,    33,    34,    35,    36,    37,    38,    39,     0,    40,
      41,    42,    43,    44,    45,    46,    47,     0,    48,     0,
       0,     0,     0,    49,     0,     0,    50,     0,    51,     0,
      52,     0,     0,     0,    53,    54,    55,     0,    56,    57,
       0,    58,    59,    60,     0,    61,     0,    62,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,     7,     8,
       9,     0,     0,     0,    10,     0,    11,    12,     0,   571,
       0,     0,    13,     0,     0,     0,    14,     0,     0,    15,
       0,     0,     0,    16,     0,     0,     0,     0,     0,    17,
       0,     0,    18,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,     0,    33,
      34,    35,    36,    37,    38,    39,     0,    40,    41,    42,
      43,    44,    45,    46,    47,     0,    48,     0,     0,     0,
       0,    49,     0,     0,    50,     0,    51,     0,    52,     0,
       0,     0,    53,    54,    55,     0,    56,    57,     0,    58,
     531,    60,     0,    61,     0,    62,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,     7,     8,     9,     0,
       0,     0,    10,     0,    11,    12,     0,   609,     0,     0,
      13,     0,     0,     0,    14,     0,     0,    15,     0,     0,
       0,    16,     0,     0,     0,     0,     0,    17,     0,     0,
      18,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,   610,    32,     0,    33,   611,    35,
      36,    37,    38,    39,     0,    40,    41,    42,    43,    44,
      45,   612,    47,     0,    48,     0,     0,     0,     0,    49,
       0,     0,    50,     0,    51,     0,    52,     0,     0,     0,
      53,    54,    55,     0,    56,    57,     0,    58,   531,    60,
       0,    61,     0,    62,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,     7,     8,     9,     0,     0,     0,
      10,     0,    11,    12,     0,     0,     0,     0,    13,     0,
       0,     0,    14,     0,     0,    15,     0,     0,     0,    16,
       0,   329,     0,     0,     0,    17,     0,     0,    18,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     0,    33,    34,    35,    36,    37,
      38,    39,     0,    40,    41,    42,    43,    44,    45,    46,
      47,     0,    48,     0,     0,     0,     0,    49,     0,     0,
      50,     0,    51,     0,    52,     0,     0,     0,    53,    54,
      55,     0,    56,    57,     0,    58,    59,    60,     0,    61,
       0,    62,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,     7,     8,     9,     0,     0,     0,    10,     0,
      11,    12,     0,     0,     0,     0,    13,     0,     0,     0,
      14,     0,     0,    15,     0,     0,     0,    16,     0,     0,
       0,     0,     0,    17,     0,     0,    18,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,     0,    33,    34,    35,    36,    37,    38,    39,
       0,    40,    41,    42,    43,    44,    45,    46,    47,     0,
      48,     0,     0,     0,     0,    49,     0,     0,    50,     0,
      51,     0,    52,     0,     0,     0,    53,    54,    55,     0,
      56,    57,     0,    58,   531,    60,     0,    61,     0,    62,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
       7,     8,     9,     0,     0,     0,    10,     0,    11,    12,
       0,     0,     0,     0,    13,     0,     0,     0,    14,     0,
       0,    15,     0,     0,     0,    16,     0,     0,     0,     0,
       0,    17,     0,     0,    18,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,   610,    32,
       0,    33,   611,    35,    36,    37,    38,    39,     0,    40,
      41,    42,    43,    44,    45,   612,    47,     0,    48,     0,
       0,     0,     0,    49,     0,     0,    50,     0,    51,     0,
      52,     0,     0,     0,    53,    54,    55,     0,    56,    57,
       0,    58,   531,    60,     0,    61,     0,    62,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,     7,     8,
       9,     0,     0,     0,    10,     0,    11,    12,     0,     0,
       0,     0,    13,     0,     0,     0,    14,     0,     0,    15,
       0,     0,     0,    16,     0,     0,     0,     0,     0,    17,
       0,     0,    18,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,     0,    33,
      34,    35,    36,    37,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   147,     0,     0,     0,     0,     0,     0,
       0,    49,     0,     0,    50,     0,    51,     0,    52,     0,
       0,     0,    53,    54,    55,     0,    56,    57,     0,    58,
       0,    60,     0,    61,     0,    62,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,     7,     8,     9,     0,
       0,     0,    10,     0,    11,    12,     0,     0,     0,     0,
      13,     0,   457,     0,    14,     0,     0,    15,     0,     0,
       0,    16,     0,     0,     0,     0,     0,    17,     0,     0,
      18,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,     0,    33,    34,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   147,     0,     0,     0,     0,     0,     0,     0,    49,
       0,     0,    50,     0,    51,     0,    52,     0,     0,     0,
      53,    54,    55,     0,    56,    57,     0,    58,    59,    60,
       0,    61,     0,    62,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,     7,     8,     9,     0,     0,     0,
      10,     0,    11,    12,     0,     0,     0,   328,    13,     0,
       0,     0,    14,     0,     0,    15,     0,     0,     0,    16,
       0,     0,     0,     0,     0,    17,     0,     0,    18,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     0,    33,    34,    35,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   147,
       0,     0,     0,     0,     0,     0,     0,    49,     0,     0,
      50,     0,    51,     0,    52,     0,     0,     0,    53,    54,
      55,     0,    56,    57,     0,    58,    59,    60,     0,    61,
       0,    62,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,     7,     8,     9,     0,     0,     0,    10,     0,
      11,    12,     0,     0,     0,     0,    13,     0,     0,     0,
      14,     0,     0,    15,     0,     0,     0,    16,     0,     0,
       0,     0,     0,    17,     0,     0,    18,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,     0,    33,    34,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   147,     0,     0,
       0,     0,     0,     0,     0,    49,     0,     0,    50,     0,
      51,     0,    52,     0,     0,     0,    53,    54,    55,     0,
      56,    57,     0,    58,    59,    60,     0,    61,     0,    62,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
       7,     8,     9,     0,     0,     0,    10,     0,    11,    12,
       0,     0,     0,     0,    13,     0,     0,     0,    14,     0,
       0,    15,     0,     0,     0,    16,     0,     0,     0,     0,
       0,    17,     0,     0,    18,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
       0,    33,    34,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   147,     0,     0,     0,     0,
       0,     0,     0,    49,     0,     0,    50,     0,    51,     0,
      52,     0,     0,     0,    53,    54,    55,     0,    56,    57,
       0,    58,   531,    60,     0,    61,     0,    62,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,     7,     8,
       9,     0,     0,     0,    10,     0,    11,    12,     0,     0,
       0,     0,    13,   764,     0,     0,    14,     0,     0,    15,
       0,     0,     0,    16,     0,     0,     0,     0,     0,    17,
       0,     0,    18,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,     0,    33,
      34,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   147,     0,     0,     0,     0,     0,     0,
       0,    49,     0,     0,    50,     0,    51,     0,    52,     0,
       0,     0,    53,    54,    55,     0,    56,    57,     0,    58,
       0,    60,     0,    61,     0,    62,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,     7,     8,     9,     0,
       0,     0,    10,     0,    11,    12,     0,     0,     0,     0,
      13,     0,     0,     0,    14,     0,     0,    15,     0,     0,
       0,    16,     0,     0,     0,     0,     0,    17,     0,     0,
      18,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,     0,    33,    34,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   147,     0,     0,     0,     0,     0,     0,     0,    49,
       0,     0,    50,     0,    51,     0,    52,     0,     0,     0,
      53,    54,    55,     0,    56,    57,     0,    58,     0,    60,
       0,    61,     0,    62,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,     0,   207,     0,
       0,     0,   208,     0,     0,    15,     0,     0,     0,     0,
       0,     0,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,     0,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     0,    33,    34,    35,    36,    37,
       0,     0,     0,     0,     0,    11,    12,     0,     0,   185,
       0,     0,     0,     0,     0,    14,     0,     0,     0,     0,
     232,     0,    16,     0,     0,     0,     0,     0,   233,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    62,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    64,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,     0,    33,    34,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   147,     0,     0,     0,   576,     0,     0,     0,
      49,     0,     0,    50,     0,    51,     0,    52,     0,    15,
     576,    53,    54,    55,     0,    56,    57,     0,    58,     0,
      60,     0,    61,     0,    62,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,     0,     0,     0,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
       0,     0,     0,   682,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   492,     0,   772,     0,     0,
       0,     0,     0,    14,     0,     0,    15,     0,     0,     0,
       0,     0,     0,     0,     0,    62,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    64,     0,    62,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,   330,    33,    34,    35,    36,
      37,    38,    39,     0,   332,    41,    42,    43,    44,    45,
     493,    47,   334,    48,   335,   606,     0,     0,     0,     0,
       0,     0,     0,    14,     0,     0,    15,     0,     0,     0,
      54,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    62,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    64,     0,     0,     0,     0,     0,
       0,     0,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,     0,    33,    34,    35,    36,
      37,    38,    39,     0,    40,    41,    42,    43,    44,    45,
     173,    47,     0,    48,     0,     0,    14,     0,     0,    15,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      54,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    62,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    64,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,   808,    33,
      34,    35,    36,    37,    38,    39,     0,    40,    41,    42,
      43,    44,    45,   872,    47,   334,    48,   335,     0,    14,
       0,     0,    15,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    54,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    62,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    64,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,     0,    33,    34,    35,    36,    37,    38,    39,     0,
      40,    41,    42,    43,    44,    45,   173,    47,     0,    48,
       0,     0,    14,     0,     0,    15,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    54,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    62,     0,
       0,    14,     0,     0,    15,     0,     0,     0,     0,     0,
      64,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     0,    33,    34,    35,    36,    37,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   185,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,     0,    33,    34,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   364,     0,
       0,    62,     0,     0,     0,   782,     0,    15,     0,     0,
       0,     0,     0,    64,     0,     0,     0,     0,    54,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    64,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,     0,    33,    34,    35,
      36,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   185,     0,     0,     0,     0,     0,     0,     0,     0,
      15,     0,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,     0,     0,     0,     0,     0,     0,    36,
      37,    38,    39,    62,    40,    41,    42,    43,    44,    45,
       0,    47,     0,    48,     0,    64,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,   330,
      33,    34,    35,    36,    37,    38,    39,     0,   332,    41,
      42,    43,    44,    45,   493,    47,   334,    48,   335,     0,
       0,     0,     0,    15,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    54,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    62,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    64,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,   808,    33,    34,    35,    36,    37,    38,    39,
       0,    40,    41,    42,    43,    44,    45,   872,    47,   334,
      48,   335,     0,     0,     0,     0,    15,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    54,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    62,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,     0,    33,    34,    35,    36,
      37,    38,    39,     0,    40,    41,    42,    43,    44,    45,
     173,    47,     0,    48,     0,     0,     0,     0,     0,    15,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      54,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    62,     0,     0,     0,     0,     0,    15,     0,
       0,     0,     0,     0,    64,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,     0,    33,
      34,    35,    36,    37,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   185,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,     0,    33,    34,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   364,     0,     0,    62,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    64,     0,     0,
       0,     0,    54,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    62,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    64
  };

  /* YYCHECK.  */
  const short int
  CxxParser::yycheck_[] =
  {
         4,     4,     4,    46,   345,    46,   261,     4,   322,   158,
     331,    14,    14,     1,    32,   491,    34,    14,    14,    46,
     114,   184,   361,   333,   384,   503,   594,   421,    77,    78,
       4,    78,   560,   345,   492,    53,    54,   166,   345,   357,
     357,   594,   594,   589,   531,   253,   492,    90,   594,    14,
     262,   263,   283,   734,   419,   110,   332,   112,   594,   418,
     114,   656,   641,    97,   475,   333,    29,   742,   479,    53,
      54,   734,    46,    19,   237,    31,   734,   240,    77,    78,
      11,     4,    11,   117,   542,    31,    13,   328,     1,    53,
     669,     7,     8,    24,    59,    11,    12,    61,    24,    55,
       0,    17,    18,     0,   147,   882,   147,   884,   188,    36,
       1,    38,   283,   641,     1,   119,   119,   119,    31,   153,
     147,   139,   119,    16,   602,   188,   129,   133,   905,    20,
     193,    24,   173,    20,    50,    16,    14,    15,    19,   820,
     167,   669,    73,   127,    75,   119,   173,   700,   606,   380,
      31,   746,     5,    31,   234,   158,   158,    88,   185,    88,
     606,   158,    88,    23,   182,    13,   184,    13,   262,   263,
     188,   117,   146,    89,   661,   193,   663,   108,   665,   108,
      40,   146,   413,   493,   392,   188,   597,    13,   734,   120,
     398,   120,   272,   158,   120,   366,   119,   326,   182,   173,
     184,   132,    22,   132,   188,   886,   132,   254,   883,   193,
     418,    31,   577,   129,   308,   580,   234,   576,   381,   237,
     247,   370,   240,   886,   500,   493,   794,   254,   886,   193,
      33,   234,   811,   149,   780,    88,   117,   918,    13,     1,
     334,   794,   794,   505,   262,   263,    29,   376,   794,    14,
     234,    54,   514,   237,   308,   310,   240,    19,   794,    88,
     307,   492,   503,   721,     9,    81,    31,   120,    35,   272,
     609,    21,    88,   594,    41,   721,   273,   274,   305,   132,
     283,    14,   284,   811,   288,   497,   283,    14,   272,   683,
     333,   120,   333,    46,    39,   270,   271,   272,    31,    20,
      53,    54,   267,   132,    31,   323,   333,   306,   307,    23,
      31,   542,   330,    53,    54,   633,   334,   682,   796,   560,
       3,     4,   798,   364,   787,   684,    40,   790,    21,   792,
     120,   315,    77,    78,    19,   300,   320,   364,   387,   388,
     886,   549,   132,     5,    35,    13,    31,     5,    19,    11,
      41,   378,   268,   269,   562,   563,   321,   844,   845,   333,
      31,   602,    15,   381,    24,    20,    19,   370,   370,    20,
     578,   345,   419,   370,   421,   606,    31,   380,   381,    30,
     345,   365,   386,   380,    31,   703,   703,   361,   700,   392,
     365,     9,   419,   700,   147,   398,   361,   381,   527,   315,
     641,    20,   716,   497,    46,   370,   380,   772,   442,   443,
     413,    10,    31,    20,   487,   814,   413,    20,   491,   384,
     173,   420,   421,    20,    31,   656,    88,    30,   669,   182,
      88,   184,   185,    30,    17,   188,   667,   440,    21,   413,
     193,    99,    16,    77,    78,    19,   108,     8,   188,   107,
     108,   498,   493,   193,    39,    17,     5,   475,   120,    21,
      31,   479,   120,    15,   482,   143,   493,    42,    43,   457,
     132,   498,     9,   794,   132,   683,    88,   876,   496,   497,
     840,   234,    18,   471,   237,    13,   885,   240,    22,   492,
     721,    77,    78,   834,   234,   492,   108,    11,    19,   809,
      19,    16,    18,   902,    19,   147,     3,     4,   120,   552,
      24,    30,    31,   562,   563,    30,    31,    22,   492,   493,
     132,     5,     6,     7,   440,   167,    30,    31,   927,   928,
     929,   173,   695,   580,   168,   169,    21,   878,    19,   542,
     505,     5,   941,   185,   943,   542,   549,   521,     5,   514,
     577,   516,   305,   580,   519,   796,   521,     3,     4,   722,
      20,   690,   872,   818,     3,     4,    15,   696,   542,   612,
     811,   612,    13,    14,    88,    30,    31,     3,     4,   597,
     333,   584,   584,    30,    31,   612,   604,   584,   584,     3,
       4,     3,     4,   611,   108,    36,   140,    38,   117,    30,
      31,    21,   117,   606,   698,   247,   120,   736,    30,   606,
       1,   364,   254,   631,   262,   263,   394,   395,   132,   584,
     594,    14,     5,    17,   589,   590,     9,    14,   381,   594,
     275,   276,   606,    14,    17,   609,    14,    22,   612,    18,
      16,    24,     1,    19,   609,    19,    16,     5,    24,    31,
      24,     9,    20,   656,     5,   682,   281,   282,     1,   656,
      32,   115,    34,   305,   667,    24,    24,   671,   672,    13,
     667,    19,   306,   307,    46,   679,   680,   695,   807,   934,
     698,    53,    54,   686,   686,   654,   655,    16,    30,   686,
     686,   333,   841,   667,   336,   858,    15,     1,    57,    58,
      59,   689,     9,     8,   722,    88,    39,    10,    21,   674,
      19,   695,    88,    15,    88,    24,    22,    31,   721,   737,
      21,   686,   364,    18,   721,   854,   700,    21,    21,    88,
      88,    11,    91,   375,   143,   700,   378,   120,   722,   111,
     493,   143,   114,    21,   120,   772,   120,   721,    30,   132,
      71,    15,   380,   387,   388,    15,   132,     1,   132,    30,
     734,   120,   120,    30,    22,    46,   809,   139,   809,   734,
      31,   900,    20,   132,   132,   147,    19,   419,    95,    88,
       5,     1,   809,    20,     9,   413,   420,   421,     9,    18,
     808,    30,    17,    20,    16,   167,    21,    16,    30,    24,
     124,   173,    20,   143,    21,    21,    16,    31,    31,    18,
     182,   120,   184,   185,    22,   780,   188,    22,    22,    22,
     794,   193,   787,   132,     1,   790,    17,   792,   143,   794,
      21,   872,     1,    24,    30,   809,    30,    16,   841,   841,
     858,    32,    31,    34,   841,   872,    37,    21,    21,    21,
      21,   493,    16,     1,     1,    16,   498,    20,   143,   612,
     834,     1,   234,    88,   492,   237,   147,    16,   240,   834,
      15,    30,   119,    30,   858,   840,   841,   880,   880,   882,
     882,   884,   884,   880,     1,   882,    22,   884,    53,    54,
     262,   263,   173,    31,    22,   120,    31,    21,   872,    31,
      22,    22,   905,   905,   878,    20,    22,   132,   905,    32,
       1,    34,   886,   878,   542,   880,    11,   882,    30,   884,
     924,   886,    22,    30,   102,    22,   119,    56,   840,    24,
      53,    54,   285,   305,    77,   577,   308,    56,   580,   392,
     905,   286,   695,    77,   539,   110,   658,    24,   289,   659,
     886,   323,   521,   662,    24,   731,   112,   603,   330,   111,
     111,   333,   334,   170,   527,   376,   247,   129,   112,   722,
     612,   549,   519,   254,   689,   287,   780,   794,   606,   792,
      75,   700,   624,   625,   482,   234,   737,   721,   111,   413,
     667,   114,   364,    88,    71,    72,    -1,    74,    75,    76,
      24,    71,    72,    -1,    74,    75,    76,    -1,    -1,   381,
      -1,    88,    -1,   108,    -1,    -1,   139,   182,    88,   184,
     392,    -1,    -1,   188,   305,   120,   398,    -1,   193,   657,
      -1,   108,    -1,    57,    58,    59,    -1,   132,   108,   667,
     682,    -1,    -1,   120,    -1,   168,   169,   419,   420,    -1,
     120,    -1,   333,    -1,    -1,   132,   809,    -1,    -1,   182,
      -1,   184,   132,    -1,    88,   188,    -1,    91,    -1,   234,
     193,    -1,   237,    -1,    -1,   240,    -1,   719,    -1,    -1,
      -1,   723,    -1,   364,    -1,    -1,    -1,    -1,    -1,   731,
      -1,    -1,    -1,   721,    -1,    -1,   120,   262,   263,    11,
      -1,    -1,    -1,   475,    -1,   858,    -1,   479,   132,    -1,
     482,   234,    24,    -1,   237,    -1,    -1,   240,    -1,   872,
      -1,   493,    -1,    -1,   496,   497,   498,   121,   122,   123,
     772,   125,   126,   127,   128,   129,   130,    -1,   419,   262,
     263,    -1,    -1,    -1,    -1,   310,    -1,    -1,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    -1,
      -1,    -1,    -1,   805,    -1,    -1,    -1,   809,    -1,    -1,
      -1,    -1,    -1,    -1,   816,    -1,    88,   549,    -1,    -1,
      -1,    -1,    -1,   306,   307,   308,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,
     323,    -1,    -1,    -1,    -1,   577,   578,   330,   120,    -1,
      -1,   334,   493,    -1,    -1,    -1,   381,   498,    -1,    -1,
     132,    -1,     5,    -1,    -1,   597,     9,    -1,    -1,    -1,
     872,    -1,   604,    -1,    17,    -1,    -1,    -1,    21,   611,
     612,    24,   277,   278,   279,   280,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   418,   419,   420,   421,    -1,   381,   631,
      -1,   426,    -1,    11,   387,   388,    -1,    -1,    -1,   392,
      -1,    -1,    -1,    -1,    -1,   398,    24,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    74,    75,    76,    77,    78,   577,   420,   421,   580,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
     682,    -1,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,   695,    -1,    -1,   698,    -1,    -1,    -1,
      -1,   612,    -1,    -1,     5,    -1,    -1,   120,     9,    -1,
      88,    -1,    -1,    -1,    -1,   380,    17,    -1,    -1,   132,
     722,    -1,   475,    24,    -1,    -1,   479,    -1,    -1,   482,
     108,    -1,    -1,    -1,    -1,   737,    -1,    -1,    -1,    -1,
      -1,    -1,   120,   496,   497,    -1,    -1,    -1,   413,    -1,
      -1,    24,    -1,    -1,   132,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    -1,    74,    75,    76,    77,    78,    -1,   574,
      -1,   576,   577,   578,    -1,   580,    -1,    88,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,   549,    -1,    71,    72,
      -1,    74,    75,    76,    -1,    -1,   808,   809,    -1,   562,
     563,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,   120,
      -1,    -1,    -1,    -1,    -1,   578,    -1,   492,    -1,    -1,
      -1,   132,    24,    -1,    -1,   108,    71,    72,    -1,    74,
      75,    76,    -1,    -1,   597,    -1,    -1,   120,     5,    -1,
      -1,   604,     9,    88,    -1,    -1,   858,    -1,   611,   132,
      -1,    -1,    -1,    -1,    -1,    -1,   531,    24,    -1,    -1,
     872,    -1,    -1,   108,    -1,    -1,    -1,   542,   631,    71,
      72,    -1,    74,    75,    76,   120,    -1,   682,   683,   684,
      -1,    -1,    -1,    -1,    -1,    -1,    88,   132,   809,    -1,
     695,    -1,    -1,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    -1,    74,    75,    76,
      77,    78,    -1,    -1,    -1,    -1,    -1,   722,   120,    -1,
     683,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     132,   606,   695,    -1,    -1,   698,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    -1,    -1,    -1,
      -1,   872,    11,   120,    -1,    -1,    -1,    -1,    -1,   722,
      -1,    -1,    -1,    -1,    -1,   132,    -1,   772,   773,    -1,
      -1,    -1,    -1,    -1,   737,    -1,   651,   652,   653,   654,
     655,   656,   657,   658,   659,    -1,   661,   662,   663,    -1,
     665,    -1,   667,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    -1,    -1,    -1,     1,    -1,     3,     4,     5,
      -1,    -1,    -1,     9,    -1,    11,    12,    -1,    -1,    88,
      -1,    17,    -1,    19,    -1,    21,    -1,    -1,    24,    -1,
      -1,    -1,    28,    -1,    30,   808,   721,    -1,    34,   108,
      -1,    37,    -1,   858,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   746,    -1,   132,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,   858,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    -1,
      96,    97,    98,    99,   100,   101,    -1,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,    -1,     1,    24,     3,     4,
       5,    -1,    -1,    -1,     9,    -1,    11,    12,    -1,   844,
     845,    16,    17,    -1,    -1,    -1,    21,    -1,    -1,    24,
      -1,    -1,    -1,    28,    -1,    30,    -1,    -1,    -1,    34,
      -1,    -1,    37,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    -1,    -1,
      -1,    96,    -1,    -1,    99,    -1,   101,    -1,   103,    -1,
      -1,    -1,   107,   108,   109,    -1,   111,   112,    -1,   114,
     115,   116,    -1,   118,    -1,   120,    -1,    -1,   123,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,     1,    -1,     3,     4,
       5,    -1,    -1,    -1,     9,    -1,    11,    12,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    21,    -1,    -1,    24,
      -1,    -1,    -1,    28,    -1,    30,    -1,    -1,    -1,    34,
      -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    88,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    -1,    -1,    -1,
      -1,    96,    -1,    -1,    99,    -1,   101,    -1,   103,    -1,
     120,    -1,   107,   108,   109,    -1,   111,   112,    -1,   114,
     115,   116,   132,   118,    -1,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,     1,    -1,     3,     4,
       5,    -1,    -1,    -1,     9,    15,    11,    12,    -1,    -1,
      -1,    -1,    17,    23,    -1,    -1,    21,    -1,    -1,    24,
      -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    34,
      40,    -1,    37,    -1,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    74,
      75,    76,    77,    78,    79,    80,    -1,    82,    83,    84,
      85,    86,    87,    88,    89,    -1,    91,    15,    -1,    -1,
      -1,    96,    -1,    -1,    99,    23,   101,    -1,   103,    -1,
      -1,    -1,   107,   108,   109,    -1,   111,   112,    -1,   114,
     115,   116,    40,   118,    -1,   120,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,     1,    -1,     3,     4,
       5,    -1,    -1,    -1,     9,    -1,    11,    12,    -1,    -1,
      -1,    -1,    17,    -1,    19,    -1,    21,    -1,    -1,    24,
      -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    74,
      75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    96,    -1,    -1,    99,    -1,   101,    -1,   103,    -1,
      -1,    -1,   107,   108,   109,    -1,   111,   112,    -1,   114,
     115,   116,    -1,   118,    -1,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,     3,     4,     5,    -1,
      -1,    -1,     9,    -1,    11,    12,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    21,    -1,    -1,    24,    -1,    -1,
      -1,    28,    -1,    30,    -1,    -1,    -1,    34,    -1,    -1,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    -1,    -1,    -1,    96,
      -1,    -1,    99,    -1,   101,    -1,   103,    -1,    -1,    -1,
     107,   108,   109,    -1,   111,   112,    -1,   114,   115,   116,
      -1,   118,    -1,   120,    -1,    -1,   123,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,     3,     4,     5,    -1,    -1,    -1,
       9,    -1,    11,    12,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    21,    -1,    -1,    24,    -1,    -1,    -1,    28,
      -1,    30,    -1,    -1,    -1,    34,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    -1,    74,    75,    76,    77,    78,
      79,    80,    -1,    82,    83,    84,    85,    86,    87,    88,
      89,    -1,    91,    -1,    -1,    -1,    -1,    96,    -1,    -1,
      99,    -1,   101,    -1,   103,    -1,    -1,    -1,   107,   108,
     109,    -1,   111,   112,    -1,   114,   115,   116,    -1,   118,
      -1,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,     3,     4,     5,    -1,    -1,    -1,     9,    -1,
      11,    12,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,
      21,    -1,    -1,    24,    -1,    -1,    -1,    28,    -1,    30,
      -1,    -1,    -1,    34,    -1,    -1,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    -1,    74,    75,    76,    77,    78,    79,    80,
      -1,    82,    83,    84,    85,    86,    87,    88,    89,    -1,
      91,    -1,    -1,    -1,    -1,    96,    -1,    -1,    99,    -1,
     101,    -1,   103,    -1,    -1,    -1,   107,   108,   109,    -1,
     111,   112,    -1,   114,   115,   116,    -1,   118,    -1,   120,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
       3,     4,     5,    -1,    -1,    -1,     9,    -1,    11,    12,
      -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,    21,    -1,
      -1,    24,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    34,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    -1,    -1,    -1,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    74,    75,    76,    77,    78,    79,    80,    -1,    82,
      83,    84,    85,    86,    87,    88,    89,    -1,    91,    -1,
      -1,    -1,    -1,    96,    -1,    -1,    99,    -1,   101,    -1,
     103,    -1,    -1,    -1,   107,   108,   109,    -1,   111,   112,
      -1,   114,   115,   116,    -1,   118,    -1,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,     3,     4,
       5,    -1,    -1,    -1,     9,    -1,    11,    12,    -1,    14,
      -1,    -1,    17,    -1,    -1,    -1,    21,    -1,    -1,    24,
      -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    74,
      75,    76,    77,    78,    79,    80,    -1,    82,    83,    84,
      85,    86,    87,    88,    89,    -1,    91,    -1,    -1,    -1,
      -1,    96,    -1,    -1,    99,    -1,   101,    -1,   103,    -1,
      -1,    -1,   107,   108,   109,    -1,   111,   112,    -1,   114,
     115,   116,    -1,   118,    -1,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,     3,     4,     5,    -1,
      -1,    -1,     9,    -1,    11,    12,    -1,    14,    -1,    -1,
      17,    -1,    -1,    -1,    21,    -1,    -1,    24,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    -1,    74,    75,    76,
      77,    78,    79,    80,    -1,    82,    83,    84,    85,    86,
      87,    88,    89,    -1,    91,    -1,    -1,    -1,    -1,    96,
      -1,    -1,    99,    -1,   101,    -1,   103,    -1,    -1,    -1,
     107,   108,   109,    -1,   111,   112,    -1,   114,   115,   116,
      -1,   118,    -1,   120,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,     3,     4,     5,    -1,    -1,    -1,
       9,    -1,    11,    12,    -1,    -1,    -1,    -1,    17,    -1,
      -1,    -1,    21,    -1,    -1,    24,    -1,    -1,    -1,    28,
      -1,    30,    -1,    -1,    -1,    34,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    -1,    74,    75,    76,    77,    78,
      79,    80,    -1,    82,    83,    84,    85,    86,    87,    88,
      89,    -1,    91,    -1,    -1,    -1,    -1,    96,    -1,    -1,
      99,    -1,   101,    -1,   103,    -1,    -1,    -1,   107,   108,
     109,    -1,   111,   112,    -1,   114,   115,   116,    -1,   118,
      -1,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,     3,     4,     5,    -1,    -1,    -1,     9,    -1,
      11,    12,    -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,
      21,    -1,    -1,    24,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    34,    -1,    -1,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    -1,    74,    75,    76,    77,    78,    79,    80,
      -1,    82,    83,    84,    85,    86,    87,    88,    89,    -1,
      91,    -1,    -1,    -1,    -1,    96,    -1,    -1,    99,    -1,
     101,    -1,   103,    -1,    -1,    -1,   107,   108,   109,    -1,
     111,   112,    -1,   114,   115,   116,    -1,   118,    -1,   120,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
       3,     4,     5,    -1,    -1,    -1,     9,    -1,    11,    12,
      -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,    21,    -1,
      -1,    24,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    34,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    74,    75,    76,    77,    78,    79,    80,    -1,    82,
      83,    84,    85,    86,    87,    88,    89,    -1,    91,    -1,
      -1,    -1,    -1,    96,    -1,    -1,    99,    -1,   101,    -1,
     103,    -1,    -1,    -1,   107,   108,   109,    -1,   111,   112,
      -1,   114,   115,   116,    -1,   118,    -1,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,     3,     4,
       5,    -1,    -1,    -1,     9,    -1,    11,    12,    -1,    -1,
      -1,    -1,    17,    -1,    -1,    -1,    21,    -1,    -1,    24,
      -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    74,
      75,    76,    77,    78,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    96,    -1,    -1,    99,    -1,   101,    -1,   103,    -1,
      -1,    -1,   107,   108,   109,    -1,   111,   112,    -1,   114,
      -1,   116,    -1,   118,    -1,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,     3,     4,     5,    -1,
      -1,    -1,     9,    -1,    11,    12,    -1,    -1,    -1,    -1,
      17,    -1,    19,    -1,    21,    -1,    -1,    24,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    -1,    74,    75,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,
      -1,    -1,    99,    -1,   101,    -1,   103,    -1,    -1,    -1,
     107,   108,   109,    -1,   111,   112,    -1,   114,   115,   116,
      -1,   118,    -1,   120,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,     3,     4,     5,    -1,    -1,    -1,
       9,    -1,    11,    12,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    21,    -1,    -1,    24,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    -1,    74,    75,    76,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,
      99,    -1,   101,    -1,   103,    -1,    -1,    -1,   107,   108,
     109,    -1,   111,   112,    -1,   114,   115,   116,    -1,   118,
      -1,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,     3,     4,     5,    -1,    -1,    -1,     9,    -1,
      11,    12,    -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,
      21,    -1,    -1,    24,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    34,    -1,    -1,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    99,    -1,
     101,    -1,   103,    -1,    -1,    -1,   107,   108,   109,    -1,
     111,   112,    -1,   114,   115,   116,    -1,   118,    -1,   120,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
       3,     4,     5,    -1,    -1,    -1,     9,    -1,    11,    12,
      -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,    21,    -1,
      -1,    24,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    34,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    96,    -1,    -1,    99,    -1,   101,    -1,
     103,    -1,    -1,    -1,   107,   108,   109,    -1,   111,   112,
      -1,   114,   115,   116,    -1,   118,    -1,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,     3,     4,
       5,    -1,    -1,    -1,     9,    -1,    11,    12,    -1,    -1,
      -1,    -1,    17,    18,    -1,    -1,    21,    -1,    -1,    24,
      -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    74,
      75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    96,    -1,    -1,    99,    -1,   101,    -1,   103,    -1,
      -1,    -1,   107,   108,   109,    -1,   111,   112,    -1,   114,
      -1,   116,    -1,   118,    -1,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,     3,     4,     5,    -1,
      -1,    -1,     9,    -1,    11,    12,    -1,    -1,    -1,    -1,
      17,    -1,    -1,    -1,    21,    -1,    -1,    24,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    -1,    74,    75,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,
      -1,    -1,    99,    -1,   101,    -1,   103,    -1,    -1,    -1,
     107,   108,   109,    -1,   111,   112,    -1,   114,    -1,   116,
      -1,   118,    -1,   120,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    17,    -1,
      -1,    -1,    21,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    -1,    74,    75,    76,    77,    78,
      -1,    -1,    -1,    -1,    -1,    11,    12,    -1,    -1,    88,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,
      99,    -1,    28,    -1,    -1,    -1,    -1,    -1,   107,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   132,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    -1,    74,    75,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      96,    -1,    -1,    99,    -1,   101,    -1,   103,    -1,    24,
      11,   107,   108,   109,    -1,   111,   112,    -1,   114,    -1,
     116,    -1,   118,    -1,   120,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    13,    -1,    88,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   132,    -1,   120,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   132,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    -1,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    -1,    24,    -1,    -1,    -1,
     108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   132,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    -1,    74,    75,    76,    77,
      78,    79,    80,    -1,    82,    83,    84,    85,    86,    87,
      88,    89,    -1,    91,    -1,    -1,    21,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   132,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    -1,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    -1,    21,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   132,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    -1,    74,    75,    76,    77,    78,    79,    80,    -1,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    91,
      -1,    -1,    21,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,    -1,
      -1,    21,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,
     132,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    -1,    74,    75,    76,    77,    78,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    -1,    74,    75,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      -1,   120,    -1,    -1,    -1,    22,    -1,    24,    -1,    -1,
      -1,    -1,    -1,   132,    -1,    -1,    -1,    -1,   108,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   132,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    -1,    74,    75,    76,
      77,    78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      78,    79,    80,   120,    82,    83,    84,    85,    86,    87,
      -1,    89,    -1,    91,    -1,   132,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    -1,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   132,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      -1,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   132,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    -1,    74,    75,    76,    77,
      78,    79,    80,    -1,    82,    83,    84,    85,    86,    87,
      88,    89,    -1,    91,    -1,    -1,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    -1,   132,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    74,
      75,    76,    77,    78,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    -1,    74,    75,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    -1,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   132,    -1,    -1,
      -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   132
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned short int
  CxxParser::yystos_[] =
  {
         0,    29,   168,   227,   361,     0,   363,     3,     4,     5,
       9,    11,    12,    17,    21,    24,    28,    34,    37,    55,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    74,    75,    76,    77,    78,    79,    80,
      82,    83,    84,    85,    86,    87,    88,    89,    91,    96,
      99,   101,   103,   107,   108,   109,   111,   112,   114,   115,
     116,   118,   120,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   145,   146,   148,   149,   151,   152,   153,
     154,   156,   157,   158,   164,   165,   166,   167,   169,   170,
     173,   175,   176,   177,   178,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   199,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   249,
     250,   251,   253,   255,   256,   257,   258,   275,   276,   277,
     278,   281,   288,   289,   292,   293,   294,   311,   312,   313,
     314,   329,   337,   345,   353,   228,   362,    88,   183,   277,
     183,   183,   183,   185,   190,   198,   199,   196,   249,   290,
     291,   294,   295,   133,   183,   183,    19,    88,   151,   152,
     154,   259,   154,    88,   146,   151,   156,   240,   249,   253,
     288,   345,    13,   183,    13,    88,   154,   179,   252,   253,
     254,   255,   281,   289,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    17,    21,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    99,   107,   252,   330,   338,    13,   170,   176,
      13,   196,   289,    21,    13,   150,    24,    88,   153,   157,
     177,   178,   276,    11,    88,   153,   155,   157,   276,    29,
     183,    17,    24,    32,    34,    37,   288,    31,    33,    54,
       6,     7,   275,     3,     4,    42,    43,    13,    14,    36,
      38,    35,    41,     9,     8,    10,    39,    15,    23,    40,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
     197,   247,   248,   255,    24,    88,   151,   152,   243,   244,
     239,   248,    24,   158,   242,   275,   167,   281,   183,   278,
     280,    15,   315,    16,    19,   154,   143,     1,    16,    30,
      73,    81,    82,    88,    90,    92,   123,   196,   229,   230,
     231,   235,   236,   237,   238,   249,   267,   268,   269,   270,
     271,   272,   273,   274,   298,   299,   300,   301,   323,   325,
     339,   340,   348,   357,    88,   275,     9,    18,   295,    22,
      31,    55,    20,   260,   262,   263,   264,   358,    88,   259,
      13,   252,   282,   282,    21,   182,    17,   151,   152,   179,
     180,   181,   277,   279,   179,   289,    18,    22,   277,   279,
     330,   282,   282,   121,   122,   123,   125,   126,   127,   128,
     129,   130,   147,     3,     4,   149,   155,   198,    11,    88,
     151,   152,   154,   155,   158,   159,   160,   161,   162,   163,
     255,   159,   163,   172,   196,   183,   183,   184,   184,   184,
     277,   279,   185,   185,   186,   186,   187,   187,   187,   187,
     188,   188,   189,   292,   190,   191,   192,    19,   306,   199,
     193,   196,    24,   183,     9,    39,   281,   286,   287,   196,
      20,   363,    57,    58,    59,    91,   154,   326,   327,   328,
      16,    19,   310,   358,   194,   324,    19,   154,   226,    88,
     339,   164,    13,    88,   231,   237,    73,    75,    88,   159,
      21,   146,   234,    16,    19,    31,   117,   217,   302,   304,
     238,   299,   300,    30,    31,    30,    31,   302,   304,    15,
     230,     3,     4,   295,   146,   265,   266,    31,   260,   358,
       1,   115,   187,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   249,   292,   296,   297,   346,   347,   354,   277,
     282,   283,   284,   285,    14,    14,   174,   175,   196,   199,
      17,   149,   151,   152,   180,   279,   182,   182,    14,    14,
      22,    14,   346,    18,   160,   161,    11,    88,   151,   163,
      88,   162,    24,   255,     3,     4,    20,   307,   308,   361,
      16,   115,   355,   316,   361,   327,    19,    31,   327,     1,
     326,     1,    23,   360,    15,   226,    13,   226,   228,    14,
      71,    75,    88,   296,   340,   341,   342,   343,   344,   358,
     154,   159,    30,   164,    16,    24,   233,   324,   218,   196,
     274,    16,   303,   331,   332,   274,   196,   196,   305,   306,
     229,    15,    20,   261,   262,   358,     1,    20,    31,   203,
     209,    13,    36,    38,    35,    41,     9,     8,    10,    39,
      15,    23,    40,   197,   296,    15,    14,    31,   283,    17,
     288,    21,    21,    22,    31,    18,   194,   195,   200,    21,
      21,    14,    88,   152,    11,     1,   171,   291,    20,    31,
     143,   305,   309,   357,   196,    21,   143,    30,    90,   196,
     249,   269,   298,   301,   317,   318,   319,   320,   322,   328,
     339,   357,   327,    19,    30,   324,   227,   154,   230,    71,
      14,    31,    15,    15,     1,    30,    30,    22,   146,   232,
     146,    31,    20,   212,   361,   154,   333,   334,   335,   336,
      95,   350,   351,   304,   200,     1,     9,   187,   187,   187,
     201,   201,   202,   292,   203,   204,   205,   209,   210,   211,
     206,   209,   209,   347,    18,   200,   199,   199,   196,    18,
     199,   199,    88,   160,   291,   359,    30,    20,   308,   358,
       3,     4,    22,   282,   356,   358,    30,    31,   319,    30,
      31,    30,    31,    16,     3,     4,    16,    20,   363,    30,
     146,   342,   282,   146,    30,   124,   232,   143,    73,    88,
      93,    94,    97,    98,   100,   104,   105,   106,   110,   113,
     117,   119,   145,   196,   213,   214,   215,   216,   217,   219,
     222,   224,   225,   236,   249,   349,   357,    31,   358,   335,
      21,    21,   350,    20,    16,    31,    18,    22,    22,    22,
      22,    30,     1,    19,   143,     1,   309,    22,    31,     1,
     196,   321,   325,   196,   325,   321,   317,   324,   228,   146,
     358,   154,    88,    30,   200,    30,    16,   212,    21,   146,
      21,   198,    21,   217,    21,    16,     3,     4,     1,   174,
     295,   352,   209,   209,     1,   358,    20,   282,    20,    30,
     143,     1,    16,   212,   119,   223,   238,    30,   221,   291,
      30,   221,   350,   221,   212,   213,    31,    22,    22,     1,
     358,    20,    30,   212,    21,   220,   221,    22,    22,    22,
     217,    20,     1,   199,    30,   212,   212,   212,    20,    22,
     198,   102,    30,    22,   212,   212
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  CxxParser::yytoken_number_[] =
  {
         0,   256,   257,    43,    45,    42,    47,    37,    94,    38,
     124,   126,    33,    60,    62,    61,    58,    91,    93,   123,
     125,    40,    41,    63,    46,    39,    34,    92,    64,    36,
      59,    44,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   368,    35
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned short int
  CxxParser::yyr1_[] =
  {
         0,   144,   145,   146,   146,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   148,   149,   149,   149,   149,   149,
     150,   151,   151,   152,   153,   153,   154,   154,   155,   155,
     156,   156,   156,   157,   157,   157,   158,   158,   159,   159,
     159,   160,   160,   161,   161,   161,   162,   162,   163,   163,
     164,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   166,   166,   167,   167,   167,   168,   168,   169,   169,
     169,   169,   170,   170,   170,   171,   171,   172,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   174,   174,   175,   175,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   177,   178,   178,   178,   178,   179,
     179,   179,   180,   180,   181,   181,   182,   182,   183,   183,
     184,   184,   184,   185,   185,   185,   185,   186,   186,   186,
     187,   187,   187,   188,   188,   188,   188,   188,   189,   189,
     189,   190,   190,   191,   191,   192,   192,   193,   193,   194,
     194,   195,   195,   196,   196,   196,   196,   197,   197,   197,
     197,   197,   197,   197,   197,   197,   197,   197,   198,   198,
     199,   199,   200,   201,   201,   201,   201,   202,   202,   202,
     203,   203,   204,   204,   205,   205,   206,   206,   207,   207,
     208,   208,   209,   209,   209,   210,   210,   211,   211,   212,
     213,   213,   213,   214,   214,   214,   214,   215,   215,   215,
     215,   216,   216,   216,   217,   217,   218,   218,   218,   219,
     219,   219,   220,   220,   221,   222,   222,   222,   223,   224,
     224,   224,   224,   225,   226,   226,   227,   227,   227,   228,
     229,   229,   229,   230,   230,   230,   230,   230,   230,   231,
     231,   231,   232,   232,   233,   233,   233,   234,   234,   235,
     236,   236,   237,   237,   237,   237,   237,   238,   238,   238,
     238,   239,   239,   239,   240,   240,   241,   241,   241,   242,
     242,   243,   243,   244,   244,   244,   245,   245,   245,   246,
     246,   246,   247,   247,   247,   247,   247,   248,   249,   249,
     250,   250,   250,   250,   250,   251,   251,   251,   252,   252,
     252,   253,   253,   253,   253,   254,   254,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   255,   255,   256,   256,
     256,   257,   258,   258,   259,   259,   259,   260,   260,   261,
     261,   262,   262,   263,   263,   264,   265,   265,   266,   267,
     267,   268,   269,   269,   270,   271,   272,   272,   273,   273,
     274,   275,   275,   276,   276,   277,   277,   277,   278,   278,
     279,   279,   280,   280,   281,   281,   282,   282,   283,   283,
     283,   284,   284,   285,   285,   285,   286,   286,   287,   287,
     288,   288,   289,   290,   290,   290,   291,   291,   292,   292,
     293,   293,   293,   294,   294,   294,   295,   295,   295,   296,
     296,   296,   296,   297,   297,   297,   298,   298,   299,   299,
     299,   300,   300,   300,   301,   301,   302,   303,   304,   305,
     305,   306,   306,   306,   306,   306,   307,   307,   308,   309,
     309,   309,   310,   311,   311,   312,   312,   312,   312,   313,
     313,   313,   314,   314,   315,   315,   315,   316,   317,   317,
     317,   318,   318,   318,   318,   318,   319,   319,   319,   319,
     319,   320,   320,   320,   321,   321,   322,   323,   323,   324,
     324,   325,   325,   326,   326,   327,   327,   327,   328,   328,
     328,   329,   330,   330,   331,   331,   332,   332,   333,   333,
     334,   334,   335,   336,   337,   338,   338,   338,   338,   338,
     338,   338,   338,   338,   338,   338,   338,   338,   338,   338,
     338,   338,   338,   338,   338,   338,   338,   338,   338,   338,
     338,   338,   338,   338,   338,   338,   338,   338,   338,   338,
     338,   338,   338,   338,   338,   339,   339,   340,   341,   341,
     342,   342,   342,   342,   342,   342,   343,   343,   344,   344,
     345,   345,   346,   346,   347,   348,   349,   350,   350,   351,
     352,   353,   353,   354,   354,   355,   355,   356,   356,   357,
     358,   359,   360,   361,   362,   363
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  CxxParser::yyr2_[] =
  {
         0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     1,     5,     4,     3,     1,
       1,     1,     2,     2,     1,     2,     1,     2,     2,     2,
       1,     1,     2,     1,     2,     2,     1,     2,     1,     1,
       1,     1,     2,     4,     2,     2,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     4,     1,     1,
       1,     1,     1,     3,     2,     2,     3,     0,     1,     4,
       8,     7,     5,     4,     3,     3,     3,     3,     2,     2,
       7,     7,     7,     7,     2,     0,     1,     1,     3,     1,
       2,     2,     2,     2,     3,     2,     2,     2,     2,     2,
       1,     2,     1,     2,     2,     3,     4,     2,     4,     2,
       2,     2,     2,     1,     3,     4,     0,     3,     1,     2,
       1,     3,     3,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     5,     1,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       1,     3,     1,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     5,     1,     3,     1,     1,     3,     1,     3,     2,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     4,     3,     3,     7,     0,     2,     6,     5,
       7,     5,     0,     1,     1,     5,     7,     8,     1,     2,
       2,     3,     3,     1,     4,     9,     0,     3,     7,     2,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     3,     0,     2,     3,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     2,
       2,     1,     2,     2,     1,     2,     1,     1,     2,     1,
       2,     1,     2,     1,     1,     2,     1,     2,     1,     2,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     3,     2,     2,     3,     4,     1,     3,     1,
       3,     0,     3,     1,     3,     2,     1,     3,     1,     3,
       2,     5,     3,     4,     4,     5,     3,     3,     3,     3,
       1,     1,     2,     1,     2,     1,     1,     2,     1,     2,
       0,     2,     0,     2,     1,     1,     2,     2,     0,     2,
       1,     0,     1,     2,     3,     4,     1,     1,     0,     1,
       3,     4,     3,     0,     1,     2,     1,     3,     1,     3,
       1,     2,     3,     1,     3,     1,     1,     1,     2,     1,
       1,     3,     2,     1,     2,     3,     1,     1,     2,     2,
       2,     2,     2,     2,     1,     3,     3,     2,     1,     1,
       1,     3,     4,     2,     6,     8,     1,     3,     2,     1,
       3,     2,     1,     2,     4,     5,     4,     3,     2,     1,
       1,     1,     3,     8,     0,     3,     7,     2,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       2,     3,     3,     3,     1,     1,     2,     3,     2,     1,
       5,     1,     3,     1,     3,     1,     2,     2,     1,     1,
       1,     2,     2,     2,     0,     1,     2,     4,     1,     2,
       2,     4,     4,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     4,     1,     3,
       1,     3,     1,     3,     1,     2,     1,     1,     2,     3,
       5,     2,     1,     3,     1,     4,     3,     1,     2,     5,
       1,     1,     2,     1,     2,     3,     4,     1,     3,     1,
       0,     0,     0,     0,     0,     0
  };


  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const CxxParser::yytname_[] =
  {
    "$end", "error", "$undefined", "'+'", "'-'", "'*'", "'/'", "'%'", "'^'",
  "'&'", "'|'", "'~'", "'!'", "'<'", "'>'", "'='", "':'", "'['", "']'",
  "'{'", "'}'", "'('", "')'", "'?'", "'.'", "'\\''", "'\"'", "'\\\\'",
  "'@'", "'$'", "';'", "','", "ARROW", "ARROW_STAR", "DEC", "EQ", "GE",
  "INC", "LE", "LOG_AND", "LOG_OR", "NE", "SHL", "SHR", "ASS_ADD",
  "ASS_AND", "ASS_DIV", "ASS_MOD", "ASS_MUL", "ASS_OR", "ASS_SHL",
  "ASS_SHR", "ASS_SUB", "ASS_XOR", "DOT_STAR", "ELLIPSIS", "SCOPE",
  "PRIVATE", "PROTECTED", "PUBLIC", "BOOL", "CHAR", "DOUBLE", "FLOAT",
  "INT", "LONG", "SHORT", "SIGNED", "UNSIGNED", "VOID", "WCHAR_T", "CLASS",
  "ENUM", "NAMESPACE", "STRUCT", "TYPENAME", "UNION", "CONST", "VOLATILE",
  "AUTO", "EXPLICIT", "EXPORT", "EXTERN", "FRIEND", "INLINE", "MUTABLE",
  "REGISTER", "STATIC", "TEMPLATE", "TYPEDEF", "USING", "VIRTUAL", "ASM",
  "BREAK", "CASE", "CATCH", "CONST_CAST", "CONTINUE", "DEFAULT", "DELETE",
  "DO", "DYNAMIC_CAST", "ELSE", "FALSE", "FOR", "GOTO", "IF", "NEW",
  "OPERATOR", "REINTERPRET_CAST", "RETURN", "SIZEOF", "STATIC_CAST",
  "SWITCH", "THIS", "THROW", "TRUE", "TRY", "TYPEID", "WHILE", "__ID",
  "PROPERTY", "SIGNAL", "IMPORT", "ALIAS", "SOURCE", "STRUCTURE",
  "STATEMACHINE", "STATE", "TRACK", "META", "CharacterLiteral",
  "Identifier", "HexLiteral", "LongDoubleLiteral", "DoubleLiteral",
  "FloatLiteral", "UIntLiteral", "ULongLiteral", "ULongLongLiteral",
  "StringLiteral", "SHIFT_THERE", "REDUCE_HERE_MOSTLY", "'#'", "$accept",
  "identifier_word", "identifier", "shaman_keyword",
  "convert_shaman_keyword_to_id", "id", "template_test", "global_scope",
  "id_scope", "nested_id", "scoped_id", "destructor_id",
  "special_function_id", "nested_special_function_id",
  "scoped_special_function_id", "declarator_id", "built_in_type_id",
  "pseudo_destructor_id", "nested_pseudo_destructor_id",
  "scoped_pseudo_destructor_id", "string", "literal", "boolean_literal",
  "single_expression", "translation_unit", "primary_expression",
  "abstract_expression", "type1_parameters", "mark_type1",
  "postfix_expression", "expression_list.opt", "expression_list",
  "unary_expression", "delete_expression", "new_expression", "new_type_id",
  "new_declarator", "direct_new_declarator", "new_initializer.opt",
  "cast_expression", "pm_expression", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "logical_and_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "assignment_operator", "expression.opt",
  "expression", "constant_expression", "templated_relational_expression",
  "templated_equality_expression", "templated_and_expression",
  "templated_exclusive_or_expression", "templated_inclusive_or_expression",
  "templated_logical_and_expression", "templated_logical_or_expression",
  "templated_conditional_expression", "templated_assignment_expression",
  "templated_expression", "templated_expression_list", "looping_statement",
  "looped_statement", "statement", "control_statement",
  "labeled_statement", "compound_statement", "statement_seq.opt",
  "selection_statement", "condition.opt", "condition",
  "iteration_statement", "for_init_statement", "jump_statement",
  "declaration_statement", "compound_declaration", "declaration_seq.opt",
  "looping_declaration", "looped_declaration", "declaration",
  "specialised_declaration", "import_symbol", "import_symbol_list.opt",
  "dot_qualified_name", "import_declaration", "block_declaration",
  "specialised_block_declaration", "simple_declaration",
  "suffix_built_in_decl_specifier.raw", "suffix_built_in_decl_specifier",
  "suffix_named_decl_specifier", "suffix_named_decl_specifier.bi",
  "suffix_named_decl_specifiers", "suffix_named_decl_specifiers.sf",
  "suffix_decl_specified_ids", "suffix_decl_specified_scope",
  "decl_specifier_affix", "decl_specifier_suffix", "decl_specifier_prefix",
  "storage_class_specifier", "function_specifier", "type_specifier",
  "elaborate_type_specifier", "simple_type_specifier",
  "built_in_type_specifier", "elaborated_type_specifier",
  "elaborated_enum_specifier", "enum_specifier", "enumerator_clause",
  "enumerator_list_ecarb", "enumerator_definition_ecarb",
  "enumerator_definition_filler", "enumerator_list_head",
  "enumerator_list", "enumerator_definition", "enumerator",
  "namespace_definition", "namespace_alias_definition",
  "using_declaration", "using_directive", "asm_definition",
  "linkage_specification", "init_declarations", "init_declaration",
  "star_ptr_operator", "nested_ptr_operator", "ptr_operator",
  "ptr_operator_seq", "ptr_operator_seq.opt", "cv_qualifier_seq.opt",
  "cv_qualifier", "type_id", "abstract_declarator.opt",
  "direct_abstract_declarator.opt", "direct_abstract_declarator",
  "ref_qualifier", "ref_qualifier.opt", "parenthesis_clause",
  "parameters_clause", "parameter_declaration_clause",
  "parameter_declaration_list", "abstract_pointer_declaration",
  "abstract_parameter_declaration", "special_parameter_declaration",
  "parameter_declaration", "templated_parameter_declaration",
  "templated_abstract_declaration", "function_definition",
  "func_definition", "ctor_definition", "constructor_head",
  "function_try_block", "function_block", "function_body",
  "initializer_clause", "braced_initializer", "initializer_list",
  "looping_initializer_clause", "looped_initializer_clause", "colon_mark",
  "elaborated_class_specifier", "class_specifier_head", "class_key",
  "class_specifier", "member_specification.opt",
  "looping_member_declaration", "looped_member_declaration",
  "member_declaration", "simple_member_declaration",
  "member_init_declarations", "member_init_declaration",
  "accessibility_specifier", "bit_field_declaration", "bit_field_width",
  "bit_field_init_declaration", "base_specifier_list", "base_specifier",
  "access_specifier", "conversion_function_id", "conversion_type_id",
  "ctor_initializer.opt", "ctor_initializer", "mem_initializer_list",
  "mem_initializer_list_head", "mem_initializer", "mem_initializer_id",
  "operator_function_id", "operator", "template_declaration",
  "template_parameter_clause", "template_parameter_list",
  "template_parameter", "simple_type_parameter",
  "templated_type_parameter", "template_id", "template_argument_list",
  "template_argument", "explicit_specialization", "try_block",
  "handler_seq", "handler", "exception_declaration", "throw_expression",
  "templated_throw_expression", "exception_specification", "type_id_list",
  "advance_search", "bang", "mark", "nest", "start_search",
  "start_search1", "util", YY_NULL
  };

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const CxxParser::rhs_number_type
  CxxParser::yyrhs_[] =
  {
       168,     0,    -1,   132,    -1,   145,    -1,   148,    -1,   121,
      -1,   122,    -1,   123,    -1,   125,    -1,   126,    -1,   127,
      -1,   128,    -1,   129,    -1,   130,    -1,   120,    21,   147,
      22,    -1,   146,    -1,   146,   150,     3,   346,    14,    -1,
     146,   150,     3,    14,    -1,   146,   150,     4,    -1,   345,
      -1,    13,    -1,    24,    -1,    88,   151,    -1,   149,    24,
      -1,   149,    -1,   152,   153,    -1,   153,    -1,   151,   153,
      -1,    11,   149,    -1,    88,   155,    -1,   329,    -1,   337,
      -1,    88,   156,    -1,   156,    -1,   152,   155,    -1,   152,
     157,    -1,   157,    -1,   151,   157,    -1,   154,    -1,   158,
      -1,   155,    -1,   255,    -1,   160,   255,    -1,   160,    24,
      11,   160,    -1,    11,   160,    -1,    88,   161,    -1,   161,
      -1,   152,   162,    -1,   162,    -1,   151,   163,    -1,   140,
      -1,   133,    -1,   134,    -1,   135,    -1,   136,    -1,   137,
      -1,   138,    -1,   139,    -1,   131,    -1,   164,    -1,   166,
      -1,   103,    -1,   116,    -1,   294,    -1,   199,    -1,   249,
     167,    -1,   227,    -1,    29,   361,   167,    29,    -1,   165,
      -1,   114,    -1,   245,    -1,   170,    -1,   288,    -1,    17,
     198,    18,    -1,    88,   288,    -1,   291,    30,    -1,   171,
     291,    30,    -1,    -1,   169,    -1,   173,   288,   172,     4,
      -1,   173,   288,   172,     3,   171,   359,    19,     1,    -1,
     173,   288,   172,     3,   171,   359,     1,    -1,   173,   288,
     172,     3,     1,    -1,   173,    17,   198,    18,    -1,   173,
      24,   159,    -1,   173,    24,   163,    -1,   173,    32,   159,
      -1,   173,    32,   163,    -1,   173,    37,    -1,   173,    34,
      -1,   101,    13,   282,    14,    21,   199,    22,    -1,   112,
      13,   282,    14,    21,   199,    22,    -1,   109,    13,   282,
      14,    21,   199,    22,    -1,    96,    13,   282,    14,    21,
     199,    22,    -1,   118,   289,    -1,    -1,   175,    -1,   196,
      -1,   175,    31,   196,    -1,   173,    -1,    37,   183,    -1,
      34,   183,    -1,   277,   183,    -1,    28,   133,    -1,   246,
     275,   183,    -1,     3,   183,    -1,     4,   183,    -1,    12,
     183,    -1,    11,   183,    -1,   111,   176,    -1,   178,    -1,
     151,   178,    -1,   177,    -1,   151,   177,    -1,    99,   183,
      -1,   107,   179,   182,    -1,   107,   289,   179,   182,    -1,
     107,   289,    -1,   107,   289,   289,   182,    -1,   252,   279,
      -1,   252,   180,    -1,   252,   179,    -1,   277,   180,    -1,
     181,    -1,    17,   199,    18,    -1,   181,    17,   200,    18,
      -1,    -1,    21,   174,    22,    -1,   176,    -1,   170,   183,
      -1,   183,    -1,   184,    54,   183,    -1,   184,    33,   183,
      -1,   184,    -1,   185,   275,   184,    -1,   185,     6,   184,
      -1,   185,     7,   184,    -1,   185,    -1,   186,     3,   185,
      -1,   186,     4,   185,    -1,   186,    -1,   187,    42,   186,
      -1,   187,    43,   186,    -1,   187,    -1,   188,    13,   187,
      -1,   188,    14,   187,    -1,   188,    38,   187,    -1,   188,
      36,   187,    -1,   188,    -1,   189,    35,   188,    -1,   189,
      41,   188,    -1,   189,    -1,   190,     9,   189,    -1,   190,
      -1,   191,     8,   190,    -1,   191,    -1,   192,    10,   191,
      -1,   192,    -1,   193,    39,   192,    -1,   193,    -1,   194,
      40,   193,    -1,   194,    -1,   194,    23,   199,    16,   196,
      -1,   195,    -1,   194,   197,   196,    -1,   194,    15,   306,
      -1,   353,    -1,    15,    -1,    44,    -1,    45,    -1,    46,
      -1,    47,    -1,    48,    -1,    49,    -1,    50,    -1,    51,
      -1,    52,    -1,    53,    -1,    -1,   199,    -1,   196,    -1,
     175,    31,   196,    -1,   195,    -1,   187,    -1,   201,    13,
     187,    -1,   201,    38,   187,    -1,   201,    36,   187,    -1,
     201,    -1,   202,    35,   201,    -1,   202,    41,   201,    -1,
     202,    -1,   203,     9,   202,    -1,   203,    -1,   204,     8,
     203,    -1,   204,    -1,   205,    10,   204,    -1,   205,    -1,
     206,    39,   205,    -1,   206,    -1,   207,    40,   206,    -1,
     207,    -1,   207,    23,   210,    16,   209,    -1,   208,    -1,
     207,   197,   209,    -1,   354,    -1,   209,    -1,   211,    31,
     209,    -1,   209,    -1,   211,    31,   209,    -1,   361,   213,
      -1,   214,    -1,   357,     3,   213,    -1,   357,     4,    -1,
     215,    -1,   217,    -1,   225,    -1,   349,    -1,   216,    -1,
     219,    -1,   222,    -1,   224,    -1,   145,    16,   212,    -1,
      94,   200,    16,   212,    -1,    98,    16,   212,    -1,    19,
     218,    20,    -1,    19,   218,   212,   143,   358,     1,    20,
      -1,    -1,   218,   212,    -1,   218,   212,   143,   358,     1,
      30,    -1,   106,    21,   221,    22,   212,    -1,   106,    21,
     221,    22,   212,   102,   212,    -1,   113,    21,   221,    22,
     212,    -1,    -1,   221,    -1,   291,    -1,   119,    21,   221,
      22,   212,    -1,   100,   212,   119,    21,   199,    22,    30,
      -1,   104,    21,   223,   220,    30,   198,    22,   212,    -1,
     238,    -1,    93,    30,    -1,    97,    30,    -1,   110,   198,
      30,    -1,   105,   146,    30,    -1,   236,    -1,    19,   360,
     227,    20,    -1,    19,   360,   227,   363,   228,   143,   358,
       1,    20,    -1,    -1,   227,   363,   228,    -1,   227,   363,
     228,   143,   358,     1,    30,    -1,   362,   229,    -1,   230,
      -1,   357,     3,   229,    -1,   357,     4,    -1,   236,    -1,
     298,    -1,   339,    -1,   348,    -1,   231,    -1,   235,    -1,
     272,    -1,   267,    -1,    88,   231,    -1,   146,    -1,   146,
     124,   146,    -1,    -1,    16,   232,    -1,   233,    31,   232,
      -1,   146,    -1,   234,    24,   146,    -1,   123,   234,   233,
      -1,   238,    -1,   237,    -1,   271,    -1,   268,    -1,   269,
      -1,   270,    -1,    88,   237,    -1,    30,    -1,   274,    30,
      -1,   273,    30,    -1,   249,   238,    -1,   255,    -1,   239,
     255,    -1,   239,   248,    -1,   239,    -1,    88,   240,    -1,
     154,    -1,   253,    -1,   241,   248,    -1,   241,    -1,   241,
     239,    -1,   242,    -1,   243,   242,    -1,   158,    -1,   243,
      -1,   243,   158,    -1,   240,    -1,   240,   244,    -1,   244,
      -1,   243,    24,    -1,   240,   243,    24,    -1,   240,    24,
      -1,   250,    -1,   251,    -1,    83,    -1,    89,    -1,   281,
      -1,   247,    -1,   247,    -1,    88,   249,    -1,    86,    -1,
      87,    -1,    85,    -1,    82,    -1,    79,    -1,    80,    -1,
      84,    -1,    91,    -1,   254,    -1,   253,    -1,   281,    -1,
     314,    -1,   258,    -1,   256,    -1,    88,   253,    -1,   154,
      -1,   255,    -1,    61,    -1,    70,    -1,    60,    -1,    66,
      -1,    64,    -1,    65,    -1,    67,    -1,    68,    -1,    63,
      -1,    62,    -1,    69,    -1,   311,    -1,   257,    -1,    75,
     154,    -1,    72,   154,    -1,    72,   154,   259,    -1,    72,
     259,    -1,    19,   260,    -1,    19,   264,   260,    -1,    19,
     264,    31,   261,    -1,    20,    -1,   358,     1,    20,    -1,
      20,    -1,   358,     1,    20,    -1,    -1,   358,     1,    31,
      -1,   262,    -1,   264,    31,   262,    -1,   263,   265,    -1,
     266,    -1,   266,    15,   200,    -1,   146,    -1,    73,   154,
     226,    -1,    73,   226,    -1,    73,   154,    15,   154,    30,
      -1,    90,   159,    30,    -1,    90,    75,   159,    30,    -1,
      90,    73,   154,    30,    -1,    92,    21,   164,    22,    30,
      -1,    82,   164,   228,    -1,    82,   164,   226,    -1,   196,
      31,   274,    -1,   273,    31,   274,    -1,   196,    -1,     5,
      -1,   275,   281,    -1,   275,    -1,   152,   276,    -1,     9,
      -1,   276,    -1,   151,   276,    -1,   277,    -1,   277,   278,
      -1,    -1,   277,   279,    -1,    -1,   280,   281,    -1,    77,
      -1,    78,    -1,   252,   283,    -1,   252,   282,    -1,    -1,
     277,   283,    -1,   285,    -1,    -1,   285,    -1,   284,   288,
      -1,   284,    17,    18,    -1,   284,    17,   200,    18,    -1,
      39,    -1,     9,    -1,    -1,   286,    -1,   289,   280,   287,
      -1,   289,   280,   287,   355,    -1,    21,   290,    22,    -1,
      -1,   291,    -1,   291,    55,    -1,   295,    -1,   291,    31,
     295,    -1,   278,    -1,   185,   275,   279,    -1,   292,    -1,
     190,     9,    -1,   190,     9,   292,    -1,   293,    -1,   293,
      15,   196,    -1,    55,    -1,   196,    -1,   294,    -1,   249,
     295,    -1,   209,    -1,   297,    -1,   297,    15,   209,    -1,
     249,   296,    -1,   292,    -1,   203,     9,    -1,   203,     9,
     292,    -1,   300,    -1,   299,    -1,   196,   302,    -1,   196,
     304,    -1,   249,   299,    -1,   301,   302,    -1,   301,   304,
      -1,   249,   300,    -1,   325,    -1,   301,    31,   196,    -1,
     117,   303,   350,    -1,   331,   304,    -1,   217,    -1,   196,
      -1,   306,    -1,    19,   307,    20,    -1,    19,   307,    31,
      20,    -1,    19,    20,    -1,    19,   308,   143,   358,     1,
      20,    -1,    19,   307,    31,   308,   143,   358,     1,    20,
      -1,   308,    -1,   307,    31,   308,    -1,   361,   309,    -1,
     305,    -1,   357,     3,   309,    -1,   357,     4,    -1,    16,
      -1,   313,   154,    -1,   313,   154,   310,     1,    -1,   313,
     154,   310,   326,    19,    -1,   313,    16,   326,    19,    -1,
     313,   154,    19,    -1,   313,    19,    -1,    71,    -1,    74,
      -1,    76,    -1,   312,   315,    20,    -1,   312,   315,   363,
     316,   143,   358,     1,    20,    -1,    -1,   315,   363,   316,
      -1,   315,   363,   316,   143,   358,     1,    30,    -1,   361,
     317,    -1,   318,    -1,   357,     3,   317,    -1,   357,     4,
      -1,   322,    -1,   319,    -1,   298,    -1,   269,    -1,   339,
      -1,    30,    -1,   196,    30,    -1,   301,    30,    -1,   320,
      30,    -1,   249,   319,    -1,   196,    31,   321,    -1,   301,
      31,   325,    -1,   320,    31,   321,    -1,   196,    -1,   325,
      -1,   328,    16,    -1,   196,    16,   324,    -1,    16,   324,
      -1,   194,    -1,   194,    23,   324,    16,   324,    -1,   323,
      -1,   323,    15,   305,    -1,   327,    -1,   326,    31,   327,
      -1,   154,    -1,   328,   327,    -1,    91,   327,    -1,    57,
      -1,    58,    -1,    59,    -1,   108,   330,    -1,   252,   279,
      -1,   252,   330,    -1,    -1,   332,    -1,    16,   333,    -1,
      16,   333,   358,     1,    -1,   335,    -1,   334,   335,    -1,
     333,    31,    -1,   333,   358,     1,    31,    -1,   336,    21,
     174,    22,    -1,   154,    -1,   108,   338,    -1,   107,    -1,
      99,    -1,     3,    -1,     4,    -1,     5,    -1,     6,    -1,
       7,    -1,     8,    -1,     9,    -1,    10,    -1,    11,    -1,
      12,    -1,    15,    -1,    13,    -1,    14,    -1,    44,    -1,
      52,    -1,    48,    -1,    46,    -1,    47,    -1,    53,    -1,
      45,    -1,    49,    -1,    42,    -1,    43,    -1,    51,    -1,
      50,    -1,    35,    -1,    41,    -1,    38,    -1,    36,    -1,
      39,    -1,    40,    -1,    37,    -1,    34,    -1,    31,    -1,
      33,    -1,    32,    -1,    21,    22,    -1,    17,    18,    -1,
     340,   230,    -1,    81,   339,    -1,    88,    13,   341,    14,
      -1,   342,    -1,   341,    31,   342,    -1,   343,    -1,   343,
      15,   282,    -1,   344,    -1,   344,    15,   146,    -1,   296,
      -1,   358,     1,    -1,    71,    -1,    75,    -1,   340,    71,
      -1,   340,    71,   146,    -1,    88,   146,    13,   346,    14,
      -1,    88,   345,    -1,   347,    -1,   346,    31,   347,    -1,
     296,    -1,    88,    13,    14,   230,    -1,   117,   217,   350,
      -1,   351,    -1,   351,   350,    -1,    95,    21,   352,    22,
     217,    -1,   295,    -1,   115,    -1,   115,   196,    -1,   115,
      -1,   115,   209,    -1,   115,    21,    22,    -1,   115,    21,
     356,    22,    -1,   282,    -1,   356,    31,   282,    -1,     1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  CxxParser::yyprhs_[] =
  {
         0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    32,    34,    40,    45,    49,
      51,    53,    55,    58,    61,    63,    66,    68,    71,    74,
      77,    79,    81,    84,    86,    89,    92,    94,    97,    99,
     101,   103,   105,   108,   113,   116,   119,   121,   124,   126,
     129,   131,   133,   135,   137,   139,   141,   143,   145,   147,
     149,   151,   153,   155,   157,   159,   162,   164,   169,   171,
     173,   175,   177,   179,   183,   186,   189,   193,   194,   196,
     201,   210,   218,   224,   229,   233,   237,   241,   245,   248,
     251,   259,   267,   275,   283,   286,   287,   289,   291,   295,
     297,   300,   303,   306,   309,   313,   316,   319,   322,   325,
     328,   330,   333,   335,   338,   341,   345,   350,   353,   358,
     361,   364,   367,   370,   372,   376,   381,   382,   386,   388,
     391,   393,   397,   401,   403,   407,   411,   415,   417,   421,
     425,   427,   431,   435,   437,   441,   445,   449,   453,   455,
     459,   463,   465,   469,   471,   475,   477,   481,   483,   487,
     489,   493,   495,   501,   503,   507,   511,   513,   515,   517,
     519,   521,   523,   525,   527,   529,   531,   533,   535,   536,
     538,   540,   544,   546,   548,   552,   556,   560,   562,   566,
     570,   572,   576,   578,   582,   584,   588,   590,   594,   596,
     600,   602,   608,   610,   614,   616,   618,   622,   624,   628,
     631,   633,   637,   640,   642,   644,   646,   648,   650,   652,
     654,   656,   660,   665,   669,   673,   681,   682,   685,   692,
     698,   706,   712,   713,   715,   717,   723,   731,   740,   742,
     745,   748,   752,   756,   758,   763,   773,   774,   778,   786,
     789,   791,   795,   798,   800,   802,   804,   806,   808,   810,
     812,   814,   817,   819,   823,   824,   827,   831,   833,   837,
     841,   843,   845,   847,   849,   851,   853,   856,   858,   861,
     864,   867,   869,   872,   875,   877,   880,   882,   884,   887,
     889,   892,   894,   897,   899,   901,   904,   906,   909,   911,
     914,   918,   921,   923,   925,   927,   929,   931,   933,   935,
     938,   940,   942,   944,   946,   948,   950,   952,   954,   956,
     958,   960,   962,   964,   966,   969,   971,   973,   975,   977,
     979,   981,   983,   985,   987,   989,   991,   993,   995,   997,
     999,  1002,  1005,  1009,  1012,  1015,  1019,  1024,  1026,  1030,
    1032,  1036,  1037,  1041,  1043,  1047,  1050,  1052,  1056,  1058,
    1062,  1065,  1071,  1075,  1080,  1085,  1091,  1095,  1099,  1103,
    1107,  1109,  1111,  1114,  1116,  1119,  1121,  1123,  1126,  1128,
    1131,  1132,  1135,  1136,  1139,  1141,  1143,  1146,  1149,  1150,
    1153,  1155,  1156,  1158,  1161,  1165,  1170,  1172,  1174,  1175,
    1177,  1181,  1186,  1190,  1191,  1193,  1196,  1198,  1202,  1204,
    1208,  1210,  1213,  1217,  1219,  1223,  1225,  1227,  1229,  1232,
    1234,  1236,  1240,  1243,  1245,  1248,  1252,  1254,  1256,  1259,
    1262,  1265,  1268,  1271,  1274,  1276,  1280,  1284,  1287,  1289,
    1291,  1293,  1297,  1302,  1305,  1312,  1321,  1323,  1327,  1330,
    1332,  1336,  1339,  1341,  1344,  1349,  1355,  1360,  1364,  1367,
    1369,  1371,  1373,  1377,  1386,  1387,  1391,  1399,  1402,  1404,
    1408,  1411,  1413,  1415,  1417,  1419,  1421,  1423,  1426,  1429,
    1432,  1435,  1439,  1443,  1447,  1449,  1451,  1454,  1458,  1461,
    1463,  1469,  1471,  1475,  1477,  1481,  1483,  1486,  1489,  1491,
    1493,  1495,  1498,  1501,  1504,  1505,  1507,  1510,  1515,  1517,
    1520,  1523,  1528,  1533,  1535,  1538,  1540,  1542,  1544,  1546,
    1548,  1550,  1552,  1554,  1556,  1558,  1560,  1562,  1564,  1566,
    1568,  1570,  1572,  1574,  1576,  1578,  1580,  1582,  1584,  1586,
    1588,  1590,  1592,  1594,  1596,  1598,  1600,  1602,  1604,  1606,
    1608,  1610,  1612,  1614,  1617,  1620,  1623,  1626,  1631,  1633,
    1637,  1639,  1643,  1645,  1649,  1651,  1654,  1656,  1658,  1661,
    1665,  1671,  1674,  1676,  1680,  1682,  1687,  1691,  1693,  1696,
    1702,  1704,  1706,  1709,  1711,  1714,  1718,  1723,  1725,  1729,
    1731,  1732,  1733,  1734,  1735,  1736
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  CxxParser::yyrline_[] =
  {
         0,   365,   365,   366,   367,   369,   369,   369,   369,   369,
     369,   369,   369,   369,   370,   379,   380,   381,   382,   383,
     384,   385,   386,   387,   392,   393,   394,   395,   402,   403,
     404,   405,   406,   407,   408,   409,   410,   411,   414,   415,
     416,   423,   424,   425,   426,   427,   428,   429,   430,   431,
     442,   445,   446,   447,   448,   449,   450,   451,   452,   453,
     454,   455,   456,   461,   462,   463,   464,   465,   497,   498,
     499,   503,   509,   510,   511,   518,   519,   520,   521,   523,
     524,   526,   528,   530,   534,   536,   537,   539,   540,   541,
     542,   543,   544,   545,   546,   549,   550,   551,   552,   554,
     555,   556,   557,   558,   563,   565,   566,   567,   568,   569,
     571,   572,   573,   574,   578,   580,   581,   582,   584,   588,
     589,   590,   591,   592,   593,   594,   595,   596,   601,   602,
     605,   606,   607,   608,   609,   610,   611,   612,   613,   614,
     615,   616,   617,   618,   619,   620,   621,   622,   623,   624,
     625,   626,   627,   628,   629,   630,   631,   632,   633,   634,
     635,   636,   637,   643,   644,   645,   646,   647,   647,   647,
     647,   647,   647,   647,   647,   647,   647,   647,   652,   653,
     654,   655,   656,   660,   661,   662,   663,   664,   665,   666,
     667,   668,   669,   670,   672,   673,   675,   676,   678,   679,
     681,   682,   684,   685,   687,   688,   689,   691,   692,   699,
     700,   701,   702,   703,   705,   706,   707,   708,   709,   710,
     711,   712,   713,   714,   716,   717,   718,   719,   720,   724,
     725,   726,   727,   728,   729,   732,   733,   734,   736,   738,
     739,   740,   741,   742,   747,   748,   750,   751,   752,   753,
     754,   755,   756,   757,   758,   759,   761,   762,   763,   764,
     765,   766,   767,   768,   769,   770,   771,   772,   773,   774,
     775,   776,   777,   778,   779,   780,   781,   782,   783,   784,
     785,   800,   801,   802,   803,   804,   805,   806,   807,   808,
     809,   810,   811,   812,   813,   814,   815,   816,   817,   818,
     819,   820,   822,   823,   824,   825,   826,   828,   830,   831,
     833,   834,   835,   836,   837,   839,   840,   841,   843,   844,
     845,   847,   848,   849,   850,   851,   852,   853,   854,   855,
     856,   857,   858,   859,   860,   861,   862,   863,   874,   875,
     876,   878,   879,   880,   881,   882,   883,   884,   885,   886,
     887,   888,   889,   890,   891,   892,   893,   894,   895,   897,
     898,   899,   901,   902,   904,   905,   906,   907,   914,   915,
     916,   923,   924,   925,   926,   927,   928,   929,   930,   931,
     933,   934,   936,   937,   938,   939,   942,   943,   946,   947,
     948,   949,   950,   951,   952,   953,   956,   957,   958,   959,
     961,   962,   963,   965,   966,   967,   968,   969,   976,   977,
     978,   979,   980,   981,   982,   983,   984,   985,   986,   990,
     991,   992,   993,   994,   995,   996,  1002,  1003,  1004,  1005,
    1006,  1007,  1008,  1009,  1010,  1011,  1012,  1013,  1014,  1021,
    1022,  1023,  1024,  1025,  1026,  1027,  1029,  1030,  1031,  1032,
    1033,  1034,  1049,  1050,  1051,  1052,  1053,  1054,  1055,  1056,
    1056,  1056,  1057,  1058,  1060,  1061,  1062,  1064,  1065,  1066,
    1067,  1068,  1069,  1070,  1073,  1074,  1081,  1082,  1083,  1084,
    1085,  1086,  1087,  1088,  1089,  1092,  1093,  1094,  1095,  1096,
    1098,  1099,  1100,  1106,  1107,  1108,  1109,  1110,  1111,  1111,
    1111,  1116,  1117,  1118,  1126,  1127,  1128,  1129,  1130,  1131,
    1132,  1133,  1134,  1135,  1140,  1150,  1151,  1156,  1157,  1158,
    1159,  1160,  1161,  1162,  1163,  1164,  1165,  1166,  1167,  1168,
    1169,  1170,  1171,  1172,  1173,  1174,  1175,  1176,  1177,  1178,
    1179,  1180,  1181,  1182,  1183,  1184,  1185,  1186,  1187,  1188,
    1189,  1190,  1191,  1192,  1193,  1198,  1199,  1200,  1201,  1202,
    1203,  1204,  1205,  1206,  1207,  1208,  1209,  1211,  1213,  1214,
    1215,  1216,  1220,  1221,  1222,  1232,  1237,  1239,  1240,  1241,
    1242,  1244,  1245,  1246,  1247,  1248,  1249,  1250,  1251,  1256,
    1257,  1258,  1259,  1260,  1261,  1262
  };

  // Print the state stack on the debug stream.
  void
  CxxParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  CxxParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  CxxParser::token_number_type
  CxxParser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    12,    26,   143,    29,     7,     9,    25,
      21,    22,     5,     3,    31,     4,    24,     6,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    16,    30,
      13,    15,    14,    23,    28,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    17,    27,    18,     8,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    19,    10,    20,    11,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int CxxParser::yyeof_ = 0;
  const int CxxParser::yylast_ = 5656;
  const int CxxParser::yynnts_ = 220;
  const int CxxParser::yyempty_ = -2;
  const int CxxParser::yyfinal_ = 5;
  const int CxxParser::yyterror_ = 1;
  const int CxxParser::yyerrcode_ = 256;
  const int CxxParser::yyntokens_ = 144;

  const unsigned int CxxParser::yyuser_token_number_max_ = 368;
  const CxxParser::token_number_type CxxParser::yyundef_token_ = 2;


} // phantom




void phantom::CxxParser::error(const CxxParser::location_type& l, const string& m)
{
}

/*EndTester*/
