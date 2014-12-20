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
/* Line 279 of lalr1.cc  */
#line 19 "CxxParser.y"

#include "CxxToken.h"
#include "CxxLexer.h"
#include "CxxParser.hxx"
#include "CxxPrecompiler.hxx"
#include "CxxDriver.h"

#define yylex2(a,b) m_pDriver->getLexer()->lex(a,b); m_pDriver->getLexer()->setYYChar(&yychar)
#undef yylex
#define yylex yylex2
#undef yyerror
#define yyerror m_pDriver->getLexer()->error


/* Line 279 of lalr1.cc  */
#line 55 "CxxParser.cxx"


#include "CxxParser.hxx"

/* User implementation prologue.  */

/* Line 285 of lalr1.cc  */
#line 63 "CxxParser.cxx"


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
/* Line 353 of lalr1.cc  */
#line 158 "CxxParser.cxx"

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
/* Line 545 of lalr1.cc  */
#line 57 "CxxParser.y"
{
    // initialize the initial location object
    yylloc.begin.filename = yylloc.end.filename = m_pDriver->getFileName();
}
/* Line 545 of lalr1.cc  */
#line 359 "CxxParser.cxx"

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
/* Line 670 of lalr1.cc  */
#line 356 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].identifier); }
    break;

  case 3:
/* Line 670 of lalr1.cc  */
#line 357 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 4:
/* Line 670 of lalr1.cc  */
#line 365 "CxxParser.y"
    { (yyval.name) = YACC_NAME((yysemantic_stack_[(1) - (1)].name)); }
    break;

  case 5:
/* Line 670 of lalr1.cc  */
#line 366 "CxxParser.y"
    { (yyval.name) = YACC_TEMPLATE_NAME((yysemantic_stack_[(5) - (1)].name), (yysemantic_stack_[(5) - (4)].template_arguments)); }
    break;

  case 6:
/* Line 670 of lalr1.cc  */
#line 367 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(4) - (1)].name); ERRMSG("Empty template-argument-list"); }
    break;

  case 7:
/* Line 670 of lalr1.cc  */
#line 368 "CxxParser.y"
    { (yyval.name) = YACC_NAME((yysemantic_stack_[(3) - (1)].name)); }
    break;

  case 9:
/* Line 670 of lalr1.cc  */
#line 370 "CxxParser.y"
    { m_pDriver->getLexer()->template_test(); }
    break;

  case 10:
/* Line 670 of lalr1.cc  */
#line 371 "CxxParser.y"
    { (yyval.is_template) = IS_DEFAULT; }
    break;

  case 11:
/* Line 670 of lalr1.cc  */
#line 372 "CxxParser.y"
    { (yyval.is_template) = IS_TEMPLATE; }
    break;

  case 12:
/* Line 670 of lalr1.cc  */
#line 373 "CxxParser.y"
    { (yyval.name) = YACC_NESTED_SCOPE((yysemantic_stack_[(2) - (1)].name)); }
    break;

  case 14:
/* Line 670 of lalr1.cc  */
#line 379 "CxxParser.y"
    { (yyval.name) = YACC_NESTED_ID((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 15:
/* Line 670 of lalr1.cc  */
#line 380 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 16:
/* Line 670 of lalr1.cc  */
#line 381 "CxxParser.y"
    { (yyval.name) = YACC_GLOBAL_ID((yysemantic_stack_[(2) - (1)].is_template), (yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 17:
/* Line 670 of lalr1.cc  */
#line 388 "CxxParser.y"
    { (yyval.name) = YACC_DESTRUCTOR_ID((yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 18:
/* Line 670 of lalr1.cc  */
#line 389 "CxxParser.y"
    { (yyval.name) = YACC_SET_TEMPLATE_ID((yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 19:
/* Line 670 of lalr1.cc  */
#line 390 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 20:
/* Line 670 of lalr1.cc  */
#line 391 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 21:
/* Line 670 of lalr1.cc  */
#line 392 "CxxParser.y"
    { (yyval.name) = YACC_SET_TEMPLATE_ID((yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 22:
/* Line 670 of lalr1.cc  */
#line 393 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 23:
/* Line 670 of lalr1.cc  */
#line 394 "CxxParser.y"
    { (yyval.name) = YACC_NESTED_ID((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 24:
/* Line 670 of lalr1.cc  */
#line 395 "CxxParser.y"
    { (yyval.name) = YACC_NESTED_ID((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 25:
/* Line 670 of lalr1.cc  */
#line 396 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 26:
/* Line 670 of lalr1.cc  */
#line 397 "CxxParser.y"
    { (yyval.name) = YACC_GLOBAL_ID((yysemantic_stack_[(2) - (1)].is_template), (yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 27:
/* Line 670 of lalr1.cc  */
#line 400 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 28:
/* Line 670 of lalr1.cc  */
#line 401 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 29:
/* Line 670 of lalr1.cc  */
#line 402 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 31:
/* Line 670 of lalr1.cc  */
#line 410 "CxxParser.y"
    { (yyval.built_in_id) = YACC_BUILT_IN_IDS((yysemantic_stack_[(2) - (1)].built_in_id), (yysemantic_stack_[(2) - (2)].built_in_id)); }
    break;

  case 32:
/* Line 670 of lalr1.cc  */
#line 411 "CxxParser.y"
    { (yyval.name) = YACC_PSEUDO_DESTRUCTOR_ID((yysemantic_stack_[(4) - (1)].built_in_id), (yysemantic_stack_[(4) - (4)].built_in_id)); }
    break;

  case 33:
/* Line 670 of lalr1.cc  */
#line 412 "CxxParser.y"
    { (yyval.name) = YACC_PSEUDO_DESTRUCTOR_ID(0, (yysemantic_stack_[(2) - (2)].built_in_id)); }
    break;

  case 34:
/* Line 670 of lalr1.cc  */
#line 413 "CxxParser.y"
    { (yyval.name) = YACC_SET_TEMPLATE_ID((yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 35:
/* Line 670 of lalr1.cc  */
#line 414 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 36:
/* Line 670 of lalr1.cc  */
#line 415 "CxxParser.y"
    { (yyval.name) = YACC_NESTED_ID((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 37:
/* Line 670 of lalr1.cc  */
#line 416 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 38:
/* Line 670 of lalr1.cc  */
#line 417 "CxxParser.y"
    { (yyval.name) = YACC_GLOBAL_ID((yysemantic_stack_[(2) - (1)].is_template), (yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 39:
/* Line 670 of lalr1.cc  */
#line 428 "CxxParser.y"
    { (yyval.strings) = (yysemantic_stack_[(1) - (1)].string_literal); }
    break;

  case 40:
/* Line 670 of lalr1.cc  */
#line 431 "CxxParser.y"
    { (yyval.expression) = YACC_HEX_LITERAL_EXPRESSION((yysemantic_stack_[(1) - (1)].hex_literal)); }
    break;

  case 41:
/* Line 670 of lalr1.cc  */
#line 432 "CxxParser.y"
    { (yyval.expression) = YACC_LONGDOUBLE_LITERAL_EXPRESSION((yysemantic_stack_[(1) - (1)].longdouble_literal)); }
    break;

  case 42:
/* Line 670 of lalr1.cc  */
#line 433 "CxxParser.y"
    { (yyval.expression) = YACC_DOUBLE_LITERAL_EXPRESSION((yysemantic_stack_[(1) - (1)].double_literal)); }
    break;

  case 43:
/* Line 670 of lalr1.cc  */
#line 434 "CxxParser.y"
    { (yyval.expression) = YACC_FLOAT_LITERAL_EXPRESSION((yysemantic_stack_[(1) - (1)].float_literal)); }
    break;

  case 44:
/* Line 670 of lalr1.cc  */
#line 435 "CxxParser.y"
    { (yyval.expression) = YACC_UINT_LITERAL_EXPRESSION((yysemantic_stack_[(1) - (1)].uint_literal)); }
    break;

  case 45:
/* Line 670 of lalr1.cc  */
#line 436 "CxxParser.y"
    { (yyval.expression) = YACC_ULONG_LITERAL_EXPRESSION((yysemantic_stack_[(1) - (1)].ulong_literal)); }
    break;

  case 46:
/* Line 670 of lalr1.cc  */
#line 437 "CxxParser.y"
    { (yyval.expression) = YACC_ULONGLONG_LITERAL_EXPRESSION((yysemantic_stack_[(1) - (1)].ulonglong_literal)); }
    break;

  case 47:
/* Line 670 of lalr1.cc  */
#line 438 "CxxParser.y"
    { (yyval.expression) = YACC_CHARACTER_LITERAL_EXPRESSION((yysemantic_stack_[(1) - (1)].character_literal)); }
    break;

  case 48:
/* Line 670 of lalr1.cc  */
#line 439 "CxxParser.y"
    { (yyval.expression) = YACC_STRING_LITERAL_EXPRESSION((yysemantic_stack_[(1) - (1)].strings)); }
    break;

  case 49:
/* Line 670 of lalr1.cc  */
#line 440 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 50:
/* Line 670 of lalr1.cc  */
#line 441 "CxxParser.y"
    { (yyval.expression) = YACC_FALSE_EXPRESSION(); }
    break;

  case 51:
/* Line 670 of lalr1.cc  */
#line 442 "CxxParser.y"
    { (yyval.expression) = YACC_TRUE_EXPRESSION(); }
    break;

  case 52:
/* Line 670 of lalr1.cc  */
#line 447 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 53:
/* Line 670 of lalr1.cc  */
#line 448 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 54:
/* Line 670 of lalr1.cc  */
#line 449 "CxxParser.y"
    { (yyval.expression) = YACC_DECL_SPECIFIER_EXPRESSION((yysemantic_stack_[(2) - (2)].expression), (yysemantic_stack_[(2) - (1)].decl_specifier_id)); }
    break;

  case 55:
/* Line 670 of lalr1.cc  */
#line 450 "CxxParser.y"
    { YACC_TRANSLATION_UNIT((yysemantic_stack_[(1) - (1)].declarations)); }
    break;

  case 56:
/* Line 670 of lalr1.cc  */
#line 451 "CxxParser.y"
    { YACC_SINGLE_EXPRESSION((yysemantic_stack_[(4) - (3)].expression)); m_pDriver->getLexer()->end_search((yysemantic_stack_[(4) - (3)].expression)); }
    break;

  case 58:
/* Line 670 of lalr1.cc  */
#line 484 "CxxParser.y"
    { (yyval.expression) = YACC_THIS_EXPRESSION(); }
    break;

  case 59:
/* Line 670 of lalr1.cc  */
#line 485 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 60:
/* Line 670 of lalr1.cc  */
#line 489 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 61:
/* Line 670 of lalr1.cc  */
#line 495 "CxxParser.y"
    { (yyval.expression) = YACC_ABSTRACT_FUNCTION_EXPRESSION((yysemantic_stack_[(1) - (1)].parenthesised)); }
    break;

  case 62:
/* Line 670 of lalr1.cc  */
#line 496 "CxxParser.y"
    { (yyval.expression) = YACC_ABSTRACT_ARRAY_EXPRESSION((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 63:
/* Line 670 of lalr1.cc  */
#line 497 "CxxParser.y"
    { (yyval.expression) = YACC_SET_TEMPLATE_EXPRESSION(YACC_ABSTRACT_FUNCTION_EXPRESSION((yysemantic_stack_[(2) - (2)].parenthesised))); }
    break;

  case 64:
/* Line 670 of lalr1.cc  */
#line 504 "CxxParser.y"
    { (yyval.type1_parameters) = YACC_TYPE1_PARAMETERS(0, (yysemantic_stack_[(2) - (1)].parameters)); }
    break;

  case 65:
/* Line 670 of lalr1.cc  */
#line 505 "CxxParser.y"
    { (yyval.type1_parameters) = YACC_TYPE1_PARAMETERS((yysemantic_stack_[(3) - (1)].type1_parameters), (yysemantic_stack_[(3) - (2)].parameters)); }
    break;

  case 66:
/* Line 670 of lalr1.cc  */
#line 506 "CxxParser.y"
    { (yyval.mark) = m_pDriver->getLexer()->mark_type1(); yyclearin; }
    break;

  case 67:
/* Line 670 of lalr1.cc  */
#line 507 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 68:
/* Line 670 of lalr1.cc  */
#line 509 "CxxParser.y"
    { (yyval.expression) = YACC_CALL_EXPRESSION((yysemantic_stack_[(4) - (1)].expression), (yysemantic_stack_[(4) - (2)].parenthesised)); }
    break;

  case 69:
/* Line 670 of lalr1.cc  */
#line 511 "CxxParser.y"
    { yyerrok; yyclearin; m_pDriver->getLexer()->remark_type1((yysemantic_stack_[(8) - (6)].mark)); m_pDriver->getLexer()->unmark(); m_pDriver->getLexer()->unmark((yysemantic_stack_[(8) - (5)].type1_parameters)); (yyval.expression) = YACC_TYPE1_EXPRESSION((yysemantic_stack_[(8) - (1)].expression), (yysemantic_stack_[(8) - (2)].parenthesised), (yysemantic_stack_[(8) - (5)].type1_parameters)); }
    break;

  case 70:
/* Line 670 of lalr1.cc  */
#line 513 "CxxParser.y"
    { yyerrok; yyclearin; m_pDriver->getLexer()->remark_type1((yysemantic_stack_[(7) - (3)].mark)); m_pDriver->getLexer()->unmark(); m_pDriver->getLexer()->unmark(); (yyval.expression) = YACC_CALL_EXPRESSION((yysemantic_stack_[(7) - (1)].expression), (yysemantic_stack_[(7) - (2)].parenthesised)); }
    break;

  case 71:
/* Line 670 of lalr1.cc  */
#line 515 "CxxParser.y"
    { yyerrok; yyclearin; m_pDriver->getLexer()->remark_type1((yysemantic_stack_[(5) - (3)].mark)); m_pDriver->getLexer()->unmark(); (yyval.expression) = YACC_CALL_EXPRESSION((yysemantic_stack_[(5) - (1)].expression), (yysemantic_stack_[(5) - (2)].parenthesised)); }
    break;

  case 72:
/* Line 670 of lalr1.cc  */
#line 516 "CxxParser.y"
    { (yyval.expression) = YACC_ARRAY_EXPRESSION((yysemantic_stack_[(4) - (1)].expression), (yysemantic_stack_[(4) - (3)].expression)); }
    break;

  case 73:
/* Line 670 of lalr1.cc  */
#line 520 "CxxParser.y"
    { (yyval.expression) = YACC_DOT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].name)); }
    break;

  case 74:
/* Line 670 of lalr1.cc  */
#line 522 "CxxParser.y"
    { (yyval.expression) = YACC_DOT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].name)); }
    break;

  case 75:
/* Line 670 of lalr1.cc  */
#line 523 "CxxParser.y"
    { (yyval.expression) = YACC_ARROW_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].name)); }
    break;

  case 76:
/* Line 670 of lalr1.cc  */
#line 525 "CxxParser.y"
    { (yyval.expression) = YACC_ARROW_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].name)); }
    break;

  case 77:
/* Line 670 of lalr1.cc  */
#line 526 "CxxParser.y"
    { (yyval.expression) = YACC_POST_INCREMENT_EXPRESSION((yysemantic_stack_[(2) - (1)].expression)); }
    break;

  case 78:
/* Line 670 of lalr1.cc  */
#line 527 "CxxParser.y"
    { (yyval.expression) = YACC_POST_DECREMENT_EXPRESSION((yysemantic_stack_[(2) - (1)].expression)); }
    break;

  case 79:
/* Line 670 of lalr1.cc  */
#line 528 "CxxParser.y"
    { (yyval.expression) = YACC_DYNAMIC_CAST_EXPRESSION((yysemantic_stack_[(7) - (3)].expression), (yysemantic_stack_[(7) - (6)].expression)); }
    break;

  case 80:
/* Line 670 of lalr1.cc  */
#line 529 "CxxParser.y"
    { (yyval.expression) = YACC_STATIC_CAST_EXPRESSION((yysemantic_stack_[(7) - (3)].expression), (yysemantic_stack_[(7) - (6)].expression)); }
    break;

  case 81:
/* Line 670 of lalr1.cc  */
#line 530 "CxxParser.y"
    { (yyval.expression) = YACC_REINTERPRET_CAST_EXPRESSION((yysemantic_stack_[(7) - (3)].expression), (yysemantic_stack_[(7) - (6)].expression)); }
    break;

  case 82:
/* Line 670 of lalr1.cc  */
#line 531 "CxxParser.y"
    { (yyval.expression) = YACC_CONST_CAST_EXPRESSION((yysemantic_stack_[(7) - (3)].expression), (yysemantic_stack_[(7) - (6)].expression)); }
    break;

  case 83:
/* Line 670 of lalr1.cc  */
#line 532 "CxxParser.y"
    { (yyval.expression) = YACC_TYPEID_EXPRESSION((yysemantic_stack_[(2) - (2)].parameters)); }
    break;

  case 84:
/* Line 670 of lalr1.cc  */
#line 535 "CxxParser.y"
    { (yyval.expressions) = YACC_EXPRESSIONS(0, 0); }
    break;

  case 85:
/* Line 670 of lalr1.cc  */
#line 536 "CxxParser.y"
    { (yyval.expressions) = (yysemantic_stack_[(1) - (1)].expressions); }
    break;

  case 86:
/* Line 670 of lalr1.cc  */
#line 537 "CxxParser.y"
    { (yyval.expressions) = YACC_EXPRESSIONS(0, (yysemantic_stack_[(1) - (1)].expression)); }
    break;

  case 87:
/* Line 670 of lalr1.cc  */
#line 538 "CxxParser.y"
    { (yyval.expressions) = YACC_EXPRESSIONS((yysemantic_stack_[(3) - (1)].expressions), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 88:
/* Line 670 of lalr1.cc  */
#line 540 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 89:
/* Line 670 of lalr1.cc  */
#line 541 "CxxParser.y"
    { (yyval.expression) = YACC_PRE_INCREMENT_EXPRESSION((yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 90:
/* Line 670 of lalr1.cc  */
#line 542 "CxxParser.y"
    { (yyval.expression) = YACC_PRE_DECREMENT_EXPRESSION((yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 91:
/* Line 670 of lalr1.cc  */
#line 543 "CxxParser.y"
    { (yyval.expression) = YACC_POINTER_EXPRESSION((yysemantic_stack_[(2) - (1)].declarator), (yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 92:
/* Line 670 of lalr1.cc  */
#line 549 "CxxParser.y"
    { (yyval.expression) = YACC_SCOPED_POINTER_EXPRESSION((yysemantic_stack_[(3) - (1)].name), (yysemantic_stack_[(3) - (2)].pointer_declarator), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 93:
/* Line 670 of lalr1.cc  */
#line 550 "CxxParser.y"
    { (yyval.expression) = YACC_PLUS_EXPRESSION((yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 94:
/* Line 670 of lalr1.cc  */
#line 551 "CxxParser.y"
    { (yyval.expression) = YACC_MINUS_EXPRESSION((yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 95:
/* Line 670 of lalr1.cc  */
#line 552 "CxxParser.y"
    { (yyval.expression) = YACC_NOT_EXPRESSION((yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 96:
/* Line 670 of lalr1.cc  */
#line 553 "CxxParser.y"
    { (yyval.expression) = YACC_COMPLEMENT_EXPRESSION((yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 97:
/* Line 670 of lalr1.cc  */
#line 554 "CxxParser.y"
    { (yyval.expression) = YACC_SIZEOF_EXPRESSION((yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 98:
/* Line 670 of lalr1.cc  */
#line 556 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].new_expression); }
    break;

  case 99:
/* Line 670 of lalr1.cc  */
#line 557 "CxxParser.y"
    { (yyval.expression) = YACC_GLOBAL_EXPRESSION((yysemantic_stack_[(2) - (1)].is_template), (yysemantic_stack_[(2) - (2)].new_expression)); }
    break;

  case 100:
/* Line 670 of lalr1.cc  */
#line 558 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].delete_expression); }
    break;

  case 101:
/* Line 670 of lalr1.cc  */
#line 559 "CxxParser.y"
    { (yyval.expression) = YACC_GLOBAL_EXPRESSION((yysemantic_stack_[(2) - (1)].is_template), (yysemantic_stack_[(2) - (2)].delete_expression)); }
    break;

  case 102:
/* Line 670 of lalr1.cc  */
#line 564 "CxxParser.y"
    { (yyval.delete_expression) = YACC_DELETE_EXPRESSION((yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 103:
/* Line 670 of lalr1.cc  */
#line 565 "CxxParser.y"
    { (yyval.new_expression) = YACC_NEW_TYPE_ID_EXPRESSION(0, (yysemantic_stack_[(3) - (2)].expression), (yysemantic_stack_[(3) - (3)].expressions)); }
    break;

  case 104:
/* Line 670 of lalr1.cc  */
#line 566 "CxxParser.y"
    { (yyval.new_expression) = YACC_NEW_TYPE_ID_EXPRESSION((yysemantic_stack_[(4) - (2)].parameters), (yysemantic_stack_[(4) - (3)].expression), (yysemantic_stack_[(4) - (4)].expressions)); }
    break;

  case 105:
/* Line 670 of lalr1.cc  */
#line 567 "CxxParser.y"
    { (yyval.new_expression) = YACC_NEW_EXPRESSION((yysemantic_stack_[(2) - (2)].parameters), 0, 0); }
    break;

  case 106:
/* Line 670 of lalr1.cc  */
#line 569 "CxxParser.y"
    { (yyval.new_expression) = YACC_NEW_EXPRESSION((yysemantic_stack_[(4) - (2)].parameters), (yysemantic_stack_[(4) - (3)].parameters), (yysemantic_stack_[(4) - (4)].expressions)); }
    break;

  case 107:
/* Line 670 of lalr1.cc  */
#line 573 "CxxParser.y"
    { (yyval.expression) = YACC_TYPED_EXPRESSION((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 108:
/* Line 670 of lalr1.cc  */
#line 574 "CxxParser.y"
    { (yyval.expression) = YACC_TYPED_EXPRESSION((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 109:
/* Line 670 of lalr1.cc  */
#line 575 "CxxParser.y"
    { (yyval.expression) = YACC_TYPED_EXPRESSION((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 110:
/* Line 670 of lalr1.cc  */
#line 576 "CxxParser.y"
    { (yyval.expression) = YACC_POINTER_EXPRESSION((yysemantic_stack_[(2) - (1)].declarator), (yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 111:
/* Line 670 of lalr1.cc  */
#line 577 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 112:
/* Line 670 of lalr1.cc  */
#line 578 "CxxParser.y"
    { (yyval.expression) = YACC_ABSTRACT_ARRAY_EXPRESSION((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 113:
/* Line 670 of lalr1.cc  */
#line 579 "CxxParser.y"
    { (yyval.expression) = YACC_ARRAY_EXPRESSION((yysemantic_stack_[(4) - (1)].expression), (yysemantic_stack_[(4) - (3)].expression)); }
    break;

  case 114:
/* Line 670 of lalr1.cc  */
#line 580 "CxxParser.y"
    { (yyval.expressions) = YACC_EXPRESSIONS(0, 0); }
    break;

  case 115:
/* Line 670 of lalr1.cc  */
#line 581 "CxxParser.y"
    { (yyval.expressions) = (yysemantic_stack_[(3) - (2)].expressions); }
    break;

  case 116:
/* Line 670 of lalr1.cc  */
#line 586 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 117:
/* Line 670 of lalr1.cc  */
#line 587 "CxxParser.y"
    { (yyval.expression) = YACC_CAST_EXPRESSION((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 118:
/* Line 670 of lalr1.cc  */
#line 590 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 119:
/* Line 670 of lalr1.cc  */
#line 591 "CxxParser.y"
    { (yyval.expression) = YACC_DOT_STAR_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 120:
/* Line 670 of lalr1.cc  */
#line 592 "CxxParser.y"
    { (yyval.expression) = YACC_ARROW_STAR_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 121:
/* Line 670 of lalr1.cc  */
#line 593 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 122:
/* Line 670 of lalr1.cc  */
#line 594 "CxxParser.y"
    { (yyval.expression) = YACC_MULTIPLY_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (2)].pointer_declarator), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 123:
/* Line 670 of lalr1.cc  */
#line 595 "CxxParser.y"
    { (yyval.expression) = YACC_DIVIDE_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 124:
/* Line 670 of lalr1.cc  */
#line 596 "CxxParser.y"
    { (yyval.expression) = YACC_MODULUS_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 125:
/* Line 670 of lalr1.cc  */
#line 597 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 126:
/* Line 670 of lalr1.cc  */
#line 598 "CxxParser.y"
    { (yyval.expression) = YACC_ADD_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 127:
/* Line 670 of lalr1.cc  */
#line 599 "CxxParser.y"
    { (yyval.expression) = YACC_SUBTRACT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 128:
/* Line 670 of lalr1.cc  */
#line 600 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 129:
/* Line 670 of lalr1.cc  */
#line 601 "CxxParser.y"
    { (yyval.expression) = YACC_SHIFT_LEFT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 130:
/* Line 670 of lalr1.cc  */
#line 602 "CxxParser.y"
    { (yyval.expression) = YACC_SHIFT_RIGHT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 131:
/* Line 670 of lalr1.cc  */
#line 603 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 132:
/* Line 670 of lalr1.cc  */
#line 604 "CxxParser.y"
    { (yyval.expression) = YACC_LESS_THAN_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 133:
/* Line 670 of lalr1.cc  */
#line 605 "CxxParser.y"
    { (yyval.expression) = YACC_GREATER_THAN_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 134:
/* Line 670 of lalr1.cc  */
#line 606 "CxxParser.y"
    { (yyval.expression) = YACC_LESS_EQUAL_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 135:
/* Line 670 of lalr1.cc  */
#line 607 "CxxParser.y"
    { (yyval.expression) = YACC_GREATER_EQUAL_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 136:
/* Line 670 of lalr1.cc  */
#line 608 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 137:
/* Line 670 of lalr1.cc  */
#line 609 "CxxParser.y"
    { (yyval.expression) = YACC_EQUAL_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 138:
/* Line 670 of lalr1.cc  */
#line 610 "CxxParser.y"
    { (yyval.expression) = YACC_NOT_EQUAL_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 139:
/* Line 670 of lalr1.cc  */
#line 611 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 140:
/* Line 670 of lalr1.cc  */
#line 612 "CxxParser.y"
    { (yyval.expression) = YACC_AND_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 141:
/* Line 670 of lalr1.cc  */
#line 613 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 142:
/* Line 670 of lalr1.cc  */
#line 614 "CxxParser.y"
    { (yyval.expression) = YACC_EXCLUSIVE_OR_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 143:
/* Line 670 of lalr1.cc  */
#line 615 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 144:
/* Line 670 of lalr1.cc  */
#line 616 "CxxParser.y"
    { (yyval.expression) = YACC_INCLUSIVE_OR_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 145:
/* Line 670 of lalr1.cc  */
#line 617 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 146:
/* Line 670 of lalr1.cc  */
#line 618 "CxxParser.y"
    { (yyval.expression) = YACC_LOGICAL_AND_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 147:
/* Line 670 of lalr1.cc  */
#line 619 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 148:
/* Line 670 of lalr1.cc  */
#line 620 "CxxParser.y"
    { (yyval.expression) = YACC_LOGICAL_OR_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 149:
/* Line 670 of lalr1.cc  */
#line 621 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 150:
/* Line 670 of lalr1.cc  */
#line 623 "CxxParser.y"
    { (yyval.expression) = YACC_CONDITIONAL_EXPRESSION((yysemantic_stack_[(5) - (1)].expression), (yysemantic_stack_[(5) - (3)].expression), (yysemantic_stack_[(5) - (5)].expression)); }
    break;

  case 151:
/* Line 670 of lalr1.cc  */
#line 628 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 152:
/* Line 670 of lalr1.cc  */
#line 629 "CxxParser.y"
    { (yyval.expression) = YACC_ASSIGNMENT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (2)].keyword), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 153:
/* Line 670 of lalr1.cc  */
#line 630 "CxxParser.y"
    { (yyval.expression) = YACC_ASSIGNMENT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (2)].keyword), (yysemantic_stack_[(3) - (3)].initializer_clause)); }
    break;

  case 154:
/* Line 670 of lalr1.cc  */
#line 631 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 166:
/* Line 670 of lalr1.cc  */
#line 637 "CxxParser.y"
    { (yyval.expression) = YACC_EXPRESSION(0); }
    break;

  case 167:
/* Line 670 of lalr1.cc  */
#line 638 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 168:
/* Line 670 of lalr1.cc  */
#line 639 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 169:
/* Line 670 of lalr1.cc  */
#line 640 "CxxParser.y"
    { (yyval.expression) = YACC_EXPRESSION(YACC_EXPRESSIONS((yysemantic_stack_[(3) - (1)].expressions), (yysemantic_stack_[(3) - (3)].expression))); }
    break;

  case 170:
/* Line 670 of lalr1.cc  */
#line 641 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 171:
/* Line 670 of lalr1.cc  */
#line 645 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 172:
/* Line 670 of lalr1.cc  */
#line 646 "CxxParser.y"
    { (yyval.expression) = YACC_LESS_THAN_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 173:
/* Line 670 of lalr1.cc  */
#line 647 "CxxParser.y"
    { (yyval.expression) = YACC_LESS_EQUAL_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 174:
/* Line 670 of lalr1.cc  */
#line 648 "CxxParser.y"
    { (yyval.expression) = YACC_GREATER_EQUAL_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 175:
/* Line 670 of lalr1.cc  */
#line 649 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 176:
/* Line 670 of lalr1.cc  */
#line 650 "CxxParser.y"
    { (yyval.expression) = YACC_EQUAL_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 177:
/* Line 670 of lalr1.cc  */
#line 651 "CxxParser.y"
    { (yyval.expression) = YACC_NOT_EQUAL_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 178:
/* Line 670 of lalr1.cc  */
#line 652 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 179:
/* Line 670 of lalr1.cc  */
#line 653 "CxxParser.y"
    { (yyval.expression) = YACC_AND_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 180:
/* Line 670 of lalr1.cc  */
#line 654 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 181:
/* Line 670 of lalr1.cc  */
#line 656 "CxxParser.y"
    { (yyval.expression) = YACC_EXCLUSIVE_OR_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 182:
/* Line 670 of lalr1.cc  */
#line 657 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 183:
/* Line 670 of lalr1.cc  */
#line 659 "CxxParser.y"
    { (yyval.expression) = YACC_INCLUSIVE_OR_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 184:
/* Line 670 of lalr1.cc  */
#line 660 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 185:
/* Line 670 of lalr1.cc  */
#line 662 "CxxParser.y"
    { (yyval.expression) = YACC_LOGICAL_AND_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 186:
/* Line 670 of lalr1.cc  */
#line 663 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 187:
/* Line 670 of lalr1.cc  */
#line 665 "CxxParser.y"
    { (yyval.expression) = YACC_LOGICAL_OR_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 188:
/* Line 670 of lalr1.cc  */
#line 666 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 189:
/* Line 670 of lalr1.cc  */
#line 668 "CxxParser.y"
    { (yyval.expression) = YACC_CONDITIONAL_EXPRESSION((yysemantic_stack_[(5) - (1)].expression), (yysemantic_stack_[(5) - (3)].expression), (yysemantic_stack_[(5) - (5)].expression)); }
    break;

  case 190:
/* Line 670 of lalr1.cc  */
#line 669 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 191:
/* Line 670 of lalr1.cc  */
#line 671 "CxxParser.y"
    { (yyval.expression) = YACC_ASSIGNMENT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (2)].keyword), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 192:
/* Line 670 of lalr1.cc  */
#line 672 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 193:
/* Line 670 of lalr1.cc  */
#line 673 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 194:
/* Line 670 of lalr1.cc  */
#line 675 "CxxParser.y"
    { (yyval.expression) = YACC_EXPRESSION(YACC_EXPRESSIONS((yysemantic_stack_[(3) - (1)].expressions), (yysemantic_stack_[(3) - (3)].expression))); }
    break;

  case 195:
/* Line 670 of lalr1.cc  */
#line 676 "CxxParser.y"
    { (yyval.expressions) = YACC_EXPRESSIONS(0, (yysemantic_stack_[(1) - (1)].expression)); }
    break;

  case 196:
/* Line 670 of lalr1.cc  */
#line 677 "CxxParser.y"
    { (yyval.expressions) = YACC_EXPRESSIONS((yysemantic_stack_[(3) - (1)].expressions), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 197:
/* Line 670 of lalr1.cc  */
#line 684 "CxxParser.y"
    { (yyval.statement) = YACC_LINED_STATEMENT((yysemantic_stack_[(2) - (2)].statement), (yysemantic_stack_[(2) - (1)].line)); m_pDriver->getLexer()->end_search((yyval.statement)); }
    break;

  case 198:
/* Line 670 of lalr1.cc  */
#line 685 "CxxParser.y"
    { (yyval.statement) = (yysemantic_stack_[(1) - (1)].statement); }
    break;

  case 199:
/* Line 670 of lalr1.cc  */
#line 686 "CxxParser.y"
    { (yyval.statement) = (yysemantic_stack_[(3) - (3)].statement); }
    break;

  case 200:
/* Line 670 of lalr1.cc  */
#line 687 "CxxParser.y"
    { (yyval.statement) = 0; }
    break;

  case 201:
/* Line 670 of lalr1.cc  */
#line 688 "CxxParser.y"
    { (yyval.statement) = (yysemantic_stack_[(1) - (1)].statement); }
    break;

  case 202:
/* Line 670 of lalr1.cc  */
#line 690 "CxxParser.y"
    { (yyval.statement) = (yysemantic_stack_[(1) - (1)].statement); }
    break;

  case 203:
/* Line 670 of lalr1.cc  */
#line 691 "CxxParser.y"
    { (yyval.statement) = (yysemantic_stack_[(1) - (1)].statement); }
    break;

  case 204:
/* Line 670 of lalr1.cc  */
#line 692 "CxxParser.y"
    { (yyval.statement) = YACC_TRY_BLOCK_STATEMENT((yysemantic_stack_[(1) - (1)].function_body)); }
    break;

  case 205:
/* Line 670 of lalr1.cc  */
#line 693 "CxxParser.y"
    { (yyval.statement) = (yysemantic_stack_[(1) - (1)].statement); }
    break;

  case 206:
/* Line 670 of lalr1.cc  */
#line 694 "CxxParser.y"
    { (yyval.statement) = (yysemantic_stack_[(1) - (1)].statement); }
    break;

  case 207:
/* Line 670 of lalr1.cc  */
#line 695 "CxxParser.y"
    { (yyval.statement) = (yysemantic_stack_[(1) - (1)].statement); }
    break;

  case 208:
/* Line 670 of lalr1.cc  */
#line 696 "CxxParser.y"
    { (yyval.statement) = (yysemantic_stack_[(1) - (1)].statement); }
    break;

  case 209:
/* Line 670 of lalr1.cc  */
#line 697 "CxxParser.y"
    { (yyval.statement) = YACC_LABEL_STATEMENT((yysemantic_stack_[(3) - (1)].name), (yysemantic_stack_[(3) - (3)].statement)); }
    break;

  case 210:
/* Line 670 of lalr1.cc  */
#line 698 "CxxParser.y"
    { (yyval.statement) = YACC_CASE_STATEMENT((yysemantic_stack_[(4) - (2)].expression), (yysemantic_stack_[(4) - (4)].statement)); }
    break;

  case 211:
/* Line 670 of lalr1.cc  */
#line 699 "CxxParser.y"
    { (yyval.statement) = YACC_DEFAULT_STATEMENT((yysemantic_stack_[(3) - (3)].statement)); }
    break;

  case 212:
/* Line 670 of lalr1.cc  */
#line 701 "CxxParser.y"
    { (yyval.statement) = YACC_COMPOUND_STATEMENT((yysemantic_stack_[(3) - (2)].statements)); }
    break;

  case 213:
/* Line 670 of lalr1.cc  */
#line 702 "CxxParser.y"
    { (yyval.statement) = (yysemantic_stack_[(7) - (2)].statements); YACC_UNBANG((yysemantic_stack_[(7) - (5)].bang), "Bad statement-seq."); }
    break;

  case 214:
/* Line 670 of lalr1.cc  */
#line 703 "CxxParser.y"
    { (yyval.statements) = YACC_STATEMENTS(0, 0); }
    break;

  case 215:
/* Line 670 of lalr1.cc  */
#line 704 "CxxParser.y"
    { (yyval.statements) = YACC_STATEMENTS((yysemantic_stack_[(2) - (1)].statements), YACC_COMPILE_STATEMENT((yysemantic_stack_[(2) - (2)].statement))); }
    break;

  case 216:
/* Line 670 of lalr1.cc  */
#line 705 "CxxParser.y"
    { (yyval.statements) = (yysemantic_stack_[(6) - (1)].statements); YACC_UNBANG((yysemantic_stack_[(6) - (4)].bang), "Bad statement."); }
    break;

  case 217:
/* Line 670 of lalr1.cc  */
#line 709 "CxxParser.y"
    { (yyval.statement) = YACC_IF_STATEMENT((yysemantic_stack_[(5) - (3)].condition), (yysemantic_stack_[(5) - (5)].statement), 0); }
    break;

  case 218:
/* Line 670 of lalr1.cc  */
#line 710 "CxxParser.y"
    { (yyval.statement) = YACC_IF_STATEMENT((yysemantic_stack_[(7) - (3)].condition), (yysemantic_stack_[(7) - (5)].statement), (yysemantic_stack_[(7) - (7)].statement)); }
    break;

  case 219:
/* Line 670 of lalr1.cc  */
#line 711 "CxxParser.y"
    { (yyval.statement) = YACC_SWITCH_STATEMENT((yysemantic_stack_[(5) - (3)].condition), (yysemantic_stack_[(5) - (5)].statement)); }
    break;

  case 220:
/* Line 670 of lalr1.cc  */
#line 712 "CxxParser.y"
    { (yyval.condition) = YACC_CONDITION(0); }
    break;

  case 221:
/* Line 670 of lalr1.cc  */
#line 713 "CxxParser.y"
    { (yyval.condition) = (yysemantic_stack_[(1) - (1)].condition); }
    break;

  case 222:
/* Line 670 of lalr1.cc  */
#line 714 "CxxParser.y"
    { (yyval.condition) = YACC_CONDITION((yysemantic_stack_[(1) - (1)].parameters)); }
    break;

  case 223:
/* Line 670 of lalr1.cc  */
#line 717 "CxxParser.y"
    { (yyval.statement) = YACC_WHILE_STATEMENT((yysemantic_stack_[(5) - (3)].condition), (yysemantic_stack_[(5) - (5)].statement)); }
    break;

  case 224:
/* Line 670 of lalr1.cc  */
#line 718 "CxxParser.y"
    { (yyval.statement) = YACC_DO_WHILE_STATEMENT((yysemantic_stack_[(7) - (2)].statement), (yysemantic_stack_[(7) - (5)].expression)); }
    break;

  case 225:
/* Line 670 of lalr1.cc  */
#line 720 "CxxParser.y"
    { (yyval.statement) = YACC_FOR_STATEMENT((yysemantic_stack_[(8) - (3)].expression), (yysemantic_stack_[(8) - (4)].condition), (yysemantic_stack_[(8) - (6)].expression), (yysemantic_stack_[(8) - (8)].statement)); }
    break;

  case 226:
/* Line 670 of lalr1.cc  */
#line 721 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 227:
/* Line 670 of lalr1.cc  */
#line 723 "CxxParser.y"
    { (yyval.statement) = YACC_BREAK_STATEMENT(); }
    break;

  case 228:
/* Line 670 of lalr1.cc  */
#line 724 "CxxParser.y"
    { (yyval.statement) = YACC_CONTINUE_STATEMENT(); }
    break;

  case 229:
/* Line 670 of lalr1.cc  */
#line 725 "CxxParser.y"
    { (yyval.statement) = YACC_RETURN_STATEMENT((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 230:
/* Line 670 of lalr1.cc  */
#line 726 "CxxParser.y"
    { (yyval.statement) = YACC_GOTO_STATEMENT((yysemantic_stack_[(3) - (2)].name)); }
    break;

  case 231:
/* Line 670 of lalr1.cc  */
#line 727 "CxxParser.y"
    { (yyval.statement) = YACC_DECLARATION_STATEMENT((yysemantic_stack_[(1) - (1)].declaration)); }
    break;

  case 232:
/* Line 670 of lalr1.cc  */
#line 732 "CxxParser.y"
    { (yyval.declarations) = (yysemantic_stack_[(4) - (3)].declarations); m_pDriver->getLexer()->unnest((yysemantic_stack_[(4) - (2)].nest)); }
    break;

  case 233:
/* Line 670 of lalr1.cc  */
#line 734 "CxxParser.y"
    { (yyval.declarations) = (yysemantic_stack_[(9) - (3)].declarations); m_pDriver->getLexer()->unnest((yysemantic_stack_[(9) - (2)].nest)); YACC_UNBANG((yysemantic_stack_[(9) - (7)].bang), "Bad declaration-seq."); }
    break;

  case 234:
/* Line 670 of lalr1.cc  */
#line 735 "CxxParser.y"
    { (yyval.declarations) = YACC_DECLARATIONS(0, 0); }
    break;

  case 235:
/* Line 670 of lalr1.cc  */
#line 736 "CxxParser.y"
    { (yyval.declarations) = YACC_DECLARATIONS((yysemantic_stack_[(3) - (1)].declarations), YACC_COMPILE_DECLARATION((yysemantic_stack_[(3) - (2)].utility), (yysemantic_stack_[(3) - (3)].declaration))); }
    break;

  case 236:
/* Line 670 of lalr1.cc  */
#line 737 "CxxParser.y"
    { (yyval.declarations) = (yysemantic_stack_[(7) - (1)].declarations); YACC_UNBANG((yysemantic_stack_[(7) - (5)].bang), "Bad declaration."); }
    break;

  case 237:
/* Line 670 of lalr1.cc  */
#line 738 "CxxParser.y"
    { (yyval.declaration) = YACC_LINED_DECLARATION((yysemantic_stack_[(2) - (2)].declaration), (yysemantic_stack_[(2) - (1)].line)); m_pDriver->getLexer()->end_search((yyval.declaration)); }
    break;

  case 238:
/* Line 670 of lalr1.cc  */
#line 739 "CxxParser.y"
    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 239:
/* Line 670 of lalr1.cc  */
#line 740 "CxxParser.y"
    { (yyval.declaration) = (yysemantic_stack_[(3) - (3)].declaration); }
    break;

  case 240:
/* Line 670 of lalr1.cc  */
#line 741 "CxxParser.y"
    { (yyval.declaration) = 0; }
    break;

  case 241:
/* Line 670 of lalr1.cc  */
#line 742 "CxxParser.y"
    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 242:
/* Line 670 of lalr1.cc  */
#line 743 "CxxParser.y"
    { (yyval.declaration) = YACC_SIMPLE_DECLARATION((yysemantic_stack_[(1) - (1)].expression)); }
    break;

  case 243:
/* Line 670 of lalr1.cc  */
#line 744 "CxxParser.y"
    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 244:
/* Line 670 of lalr1.cc  */
#line 746 "CxxParser.y"
    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 245:
/* Line 670 of lalr1.cc  */
#line 747 "CxxParser.y"
    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 246:
/* Line 670 of lalr1.cc  */
#line 748 "CxxParser.y"
    { (yyval.declaration) = YACC_LINKAGE_SPECIFICATION((yysemantic_stack_[(1) - (1)].name)); }
    break;

  case 247:
/* Line 670 of lalr1.cc  */
#line 749 "CxxParser.y"
    { (yyval.declaration) = YACC_NAMESPACE_DECLARATION((yysemantic_stack_[(1) - (1)].name)); }
    break;

  case 248:
/* Line 670 of lalr1.cc  */
#line 750 "CxxParser.y"
    { (yyval.declaration) = YACC_SET_TEMPLATE_DECLARATION((yysemantic_stack_[(2) - (2)].declaration)); }
    break;

  case 249:
/* Line 670 of lalr1.cc  */
#line 751 "CxxParser.y"
    { (yyval.declaration) = YACC_SIMPLE_DECLARATION((yysemantic_stack_[(1) - (1)].expression)); }
    break;

  case 250:
/* Line 670 of lalr1.cc  */
#line 752 "CxxParser.y"
    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 251:
/* Line 670 of lalr1.cc  */
#line 753 "CxxParser.y"
    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 252:
/* Line 670 of lalr1.cc  */
#line 754 "CxxParser.y"
    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 253:
/* Line 670 of lalr1.cc  */
#line 755 "CxxParser.y"
    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 254:
/* Line 670 of lalr1.cc  */
#line 756 "CxxParser.y"
    { (yyval.declaration) = (yysemantic_stack_[(1) - (1)].declaration); }
    break;

  case 255:
/* Line 670 of lalr1.cc  */
#line 757 "CxxParser.y"
    { (yyval.declaration) = YACC_SET_TEMPLATE_DECLARATION((yysemantic_stack_[(2) - (2)].declaration)); }
    break;

  case 256:
/* Line 670 of lalr1.cc  */
#line 758 "CxxParser.y"
    { (yyval.expression) = YACC_EXPRESSION(0); }
    break;

  case 257:
/* Line 670 of lalr1.cc  */
#line 759 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(2) - (1)].expression); }
    break;

  case 258:
/* Line 670 of lalr1.cc  */
#line 760 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(2) - (1)].expressions); }
    break;

  case 259:
/* Line 670 of lalr1.cc  */
#line 761 "CxxParser.y"
    { (yyval.expression) = YACC_DECL_SPECIFIER_EXPRESSION((yysemantic_stack_[(2) - (2)].expression), (yysemantic_stack_[(2) - (1)].decl_specifier_id)); }
    break;

  case 260:
/* Line 670 of lalr1.cc  */
#line 776 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 261:
/* Line 670 of lalr1.cc  */
#line 777 "CxxParser.y"
    { (yyval.name) = YACC_BUILT_IN_NAME((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].built_in_id)); }
    break;

  case 262:
/* Line 670 of lalr1.cc  */
#line 778 "CxxParser.y"
    { (yyval.name) = YACC_DECL_SPECIFIER_NAME((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].decl_specifier_id)); }
    break;

  case 263:
/* Line 670 of lalr1.cc  */
#line 779 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 264:
/* Line 670 of lalr1.cc  */
#line 780 "CxxParser.y"
    { (yyval.name) = YACC_SET_TEMPLATE_NAME((yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 265:
/* Line 670 of lalr1.cc  */
#line 781 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 266:
/* Line 670 of lalr1.cc  */
#line 782 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 267:
/* Line 670 of lalr1.cc  */
#line 783 "CxxParser.y"
    { (yyval.name) = YACC_DECL_SPECIFIER_NAME((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].decl_specifier_id)); }
    break;

  case 268:
/* Line 670 of lalr1.cc  */
#line 784 "CxxParser.y"
    { (yyval.name) = YACC_NAME_EXPRESSION((yysemantic_stack_[(1) - (1)].name)); }
    break;

  case 269:
/* Line 670 of lalr1.cc  */
#line 785 "CxxParser.y"
    { (yyval.name) = YACC_TYPED_NAME((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 270:
/* Line 670 of lalr1.cc  */
#line 786 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 271:
/* Line 670 of lalr1.cc  */
#line 787 "CxxParser.y"
    { (yyval.name) = YACC_TYPED_NAME((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 272:
/* Line 670 of lalr1.cc  */
#line 788 "CxxParser.y"
    { (yyval.name) = YACC_NAME_EXPRESSION((yysemantic_stack_[(1) - (1)].name)); }
    break;

  case 273:
/* Line 670 of lalr1.cc  */
#line 789 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 274:
/* Line 670 of lalr1.cc  */
#line 790 "CxxParser.y"
    { (yyval.name) = YACC_TYPED_NAME((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 275:
/* Line 670 of lalr1.cc  */
#line 791 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 276:
/* Line 670 of lalr1.cc  */
#line 792 "CxxParser.y"
    { (yyval.name) = YACC_TYPED_NAME((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 277:
/* Line 670 of lalr1.cc  */
#line 793 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 278:
/* Line 670 of lalr1.cc  */
#line 794 "CxxParser.y"
    { (yyval.name) = YACC_NAME_EXPRESSION((yysemantic_stack_[(2) - (1)].name)); }
    break;

  case 279:
/* Line 670 of lalr1.cc  */
#line 795 "CxxParser.y"
    { (yyval.name) = YACC_TYPED_NAME((yysemantic_stack_[(3) - (1)].name), (yysemantic_stack_[(3) - (2)].name)); }
    break;

  case 280:
/* Line 670 of lalr1.cc  */
#line 796 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(2) - (1)].name); }
    break;

  case 281:
/* Line 670 of lalr1.cc  */
#line 798 "CxxParser.y"
    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 282:
/* Line 670 of lalr1.cc  */
#line 799 "CxxParser.y"
    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 283:
/* Line 670 of lalr1.cc  */
#line 800 "CxxParser.y"
    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 284:
/* Line 670 of lalr1.cc  */
#line 801 "CxxParser.y"
    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 285:
/* Line 670 of lalr1.cc  */
#line 802 "CxxParser.y"
    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].cv_qualifiers); }
    break;

  case 286:
/* Line 670 of lalr1.cc  */
#line 804 "CxxParser.y"
    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 287:
/* Line 670 of lalr1.cc  */
#line 806 "CxxParser.y"
    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 288:
/* Line 670 of lalr1.cc  */
#line 807 "CxxParser.y"
    { (yyval.decl_specifier_id) = YACC_SET_TEMPLATE_DECL_SPECIFIER((yysemantic_stack_[(2) - (2)].decl_specifier_id)); }
    break;

  case 289:
/* Line 670 of lalr1.cc  */
#line 809 "CxxParser.y"
    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 290:
/* Line 670 of lalr1.cc  */
#line 810 "CxxParser.y"
    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 291:
/* Line 670 of lalr1.cc  */
#line 811 "CxxParser.y"
    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 292:
/* Line 670 of lalr1.cc  */
#line 812 "CxxParser.y"
    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 293:
/* Line 670 of lalr1.cc  */
#line 813 "CxxParser.y"
    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 294:
/* Line 670 of lalr1.cc  */
#line 815 "CxxParser.y"
    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 295:
/* Line 670 of lalr1.cc  */
#line 816 "CxxParser.y"
    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 296:
/* Line 670 of lalr1.cc  */
#line 817 "CxxParser.y"
    { (yyval.decl_specifier_id) = (yysemantic_stack_[(1) - (1)].decl_specifier_id); }
    break;

  case 297:
/* Line 670 of lalr1.cc  */
#line 819 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 298:
/* Line 670 of lalr1.cc  */
#line 820 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 299:
/* Line 670 of lalr1.cc  */
#line 821 "CxxParser.y"
    { (yyval.name) = YACC_CV_DECL_SPECIFIER((yysemantic_stack_[(1) - (1)].cv_qualifiers)); }
    break;

  case 300:
/* Line 670 of lalr1.cc  */
#line 823 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 301:
/* Line 670 of lalr1.cc  */
#line 824 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 302:
/* Line 670 of lalr1.cc  */
#line 825 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 303:
/* Line 670 of lalr1.cc  */
#line 826 "CxxParser.y"
    { (yyval.name) = YACC_SET_TEMPLATE_ID((yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 304:
/* Line 670 of lalr1.cc  */
#line 827 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 305:
/* Line 670 of lalr1.cc  */
#line 828 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 306:
/* Line 670 of lalr1.cc  */
#line 829 "CxxParser.y"
    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 307:
/* Line 670 of lalr1.cc  */
#line 830 "CxxParser.y"
    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 308:
/* Line 670 of lalr1.cc  */
#line 831 "CxxParser.y"
    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 309:
/* Line 670 of lalr1.cc  */
#line 832 "CxxParser.y"
    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 310:
/* Line 670 of lalr1.cc  */
#line 833 "CxxParser.y"
    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 311:
/* Line 670 of lalr1.cc  */
#line 834 "CxxParser.y"
    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 312:
/* Line 670 of lalr1.cc  */
#line 835 "CxxParser.y"
    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 313:
/* Line 670 of lalr1.cc  */
#line 836 "CxxParser.y"
    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 314:
/* Line 670 of lalr1.cc  */
#line 837 "CxxParser.y"
    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 315:
/* Line 670 of lalr1.cc  */
#line 838 "CxxParser.y"
    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 316:
/* Line 670 of lalr1.cc  */
#line 839 "CxxParser.y"
    { (yyval.built_in_id) = (yysemantic_stack_[(1) - (1)].built_in_id); }
    break;

  case 317:
/* Line 670 of lalr1.cc  */
#line 850 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 318:
/* Line 670 of lalr1.cc  */
#line 851 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 319:
/* Line 670 of lalr1.cc  */
#line 852 "CxxParser.y"
    { (yyval.name) = YACC_ELABORATED_TYPE_SPECIFIER((yysemantic_stack_[(2) - (1)].class_key), (yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 320:
/* Line 670 of lalr1.cc  */
#line 854 "CxxParser.y"
    { (yyval.name) = YACC_ELABORATED_TYPE_SPECIFIER((yysemantic_stack_[(2) - (1)].class_key), (yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 321:
/* Line 670 of lalr1.cc  */
#line 855 "CxxParser.y"
    { (yyval.name) = YACC_ENUM_SPECIFIER_ID((yysemantic_stack_[(3) - (2)].name), (yysemantic_stack_[(3) - (3)].enumerators)); }
    break;

  case 322:
/* Line 670 of lalr1.cc  */
#line 856 "CxxParser.y"
    { (yyval.name) = YACC_ENUM_SPECIFIER_ID(0, (yysemantic_stack_[(2) - (2)].enumerators)); }
    break;

  case 323:
/* Line 670 of lalr1.cc  */
#line 857 "CxxParser.y"
    { (yyval.enumerators) = YACC_ENUMERATORS(0, 0); }
    break;

  case 324:
/* Line 670 of lalr1.cc  */
#line 858 "CxxParser.y"
    { (yyval.enumerators) = (yysemantic_stack_[(3) - (2)].enumerators); }
    break;

  case 325:
/* Line 670 of lalr1.cc  */
#line 859 "CxxParser.y"
    { (yyval.enumerators) = (yysemantic_stack_[(4) - (2)].enumerators); }
    break;

  case 326:
/* Line 670 of lalr1.cc  */
#line 860 "CxxParser.y"
    { }
    break;

  case 327:
/* Line 670 of lalr1.cc  */
#line 861 "CxxParser.y"
    { YACC_UNBANG((yysemantic_stack_[(3) - (1)].bang), "Bad enumerator-list."); }
    break;

  case 328:
/* Line 670 of lalr1.cc  */
#line 862 "CxxParser.y"
    { }
    break;

  case 329:
/* Line 670 of lalr1.cc  */
#line 863 "CxxParser.y"
    { YACC_UNBANG((yysemantic_stack_[(3) - (1)].bang), "Bad enumerator-definition."); }
    break;

  case 331:
/* Line 670 of lalr1.cc  */
#line 865 "CxxParser.y"
    { YACC_UNBANG((yysemantic_stack_[(3) - (1)].bang), "Bad enumerator-definition."); }
    break;

  case 332:
/* Line 670 of lalr1.cc  */
#line 866 "CxxParser.y"
    { (yyval.enumerators) = YACC_ENUMERATORS(0, 0); }
    break;

  case 334:
/* Line 670 of lalr1.cc  */
#line 868 "CxxParser.y"
    { (yyval.enumerators) = YACC_ENUMERATORS((yysemantic_stack_[(2) - (1)].enumerators), (yysemantic_stack_[(2) - (2)].enumerator)); }
    break;

  case 335:
/* Line 670 of lalr1.cc  */
#line 869 "CxxParser.y"
    { (yyval.enumerator) = YACC_ENUMERATOR((yysemantic_stack_[(1) - (1)].name), 0); }
    break;

  case 336:
/* Line 670 of lalr1.cc  */
#line 870 "CxxParser.y"
    { (yyval.enumerator) = YACC_ENUMERATOR((yysemantic_stack_[(3) - (1)].name), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 337:
/* Line 670 of lalr1.cc  */
#line 871 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(1) - (1)].name); }
    break;

  case 338:
/* Line 670 of lalr1.cc  */
#line 873 "CxxParser.y"
    { (yyval.name) = YACC_NAMESPACE_DEFINITION((yysemantic_stack_[(3) - (2)].name), (yysemantic_stack_[(3) - (3)].declarations)); }
    break;

  case 339:
/* Line 670 of lalr1.cc  */
#line 874 "CxxParser.y"
    { (yyval.name) = YACC_NAMESPACE_DEFINITION(0, (yysemantic_stack_[(2) - (2)].declarations)); }
    break;

  case 340:
/* Line 670 of lalr1.cc  */
#line 875 "CxxParser.y"
    { (yyval.declaration) = YACC_NAMESPACE_ALIAS_DEFINITION((yysemantic_stack_[(5) - (2)].name), (yysemantic_stack_[(5) - (4)].name)); }
    break;

  case 341:
/* Line 670 of lalr1.cc  */
#line 877 "CxxParser.y"
    { (yyval.declaration) = YACC_USING_DECLARATION(false, (yysemantic_stack_[(3) - (2)].name)); }
    break;

  case 342:
/* Line 670 of lalr1.cc  */
#line 878 "CxxParser.y"
    { (yyval.declaration) = YACC_USING_DECLARATION(true, (yysemantic_stack_[(4) - (3)].name)); }
    break;

  case 343:
/* Line 670 of lalr1.cc  */
#line 880 "CxxParser.y"
    { (yyval.declaration) = YACC_USING_DIRECTIVE((yysemantic_stack_[(4) - (3)].name)); }
    break;

  case 344:
/* Line 670 of lalr1.cc  */
#line 881 "CxxParser.y"
    { (yyval.declaration) = YACC_ASM_DEFINITION((yysemantic_stack_[(5) - (3)].strings)); }
    break;

  case 345:
/* Line 670 of lalr1.cc  */
#line 882 "CxxParser.y"
    { (yyval.name) = YACC_LINKAGE_SPECIFIER((yysemantic_stack_[(3) - (2)].strings), (yysemantic_stack_[(3) - (3)].declaration)); }
    break;

  case 346:
/* Line 670 of lalr1.cc  */
#line 883 "CxxParser.y"
    { (yyval.name) = YACC_LINKAGE_SPECIFIER((yysemantic_stack_[(3) - (2)].strings), (yysemantic_stack_[(3) - (3)].declarations)); }
    break;

  case 347:
/* Line 670 of lalr1.cc  */
#line 889 "CxxParser.y"
    { (yyval.expressions) = YACC_EXPRESSIONS(YACC_EXPRESSIONS(0, (yysemantic_stack_[(3) - (1)].expression)), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 348:
/* Line 670 of lalr1.cc  */
#line 890 "CxxParser.y"
    { (yyval.expressions) = YACC_EXPRESSIONS((yysemantic_stack_[(3) - (1)].expressions), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 350:
/* Line 670 of lalr1.cc  */
#line 898 "CxxParser.y"
    { (yyval.pointer_declarator) = YACC_POINTER_DECLARATOR(); }
    break;

  case 351:
/* Line 670 of lalr1.cc  */
#line 899 "CxxParser.y"
    { (yyval.pointer_declarator) = YACC_CV_DECLARATOR((yysemantic_stack_[(2) - (1)].pointer_declarator), (yysemantic_stack_[(2) - (2)].cv_qualifiers)); }
    break;

  case 352:
/* Line 670 of lalr1.cc  */
#line 900 "CxxParser.y"
    { (yyval.declarator) = (yysemantic_stack_[(1) - (1)].pointer_declarator); }
    break;

  case 353:
/* Line 670 of lalr1.cc  */
#line 901 "CxxParser.y"
    { (yyval.declarator) = YACC_NESTED_DECLARATOR((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].declarator)); }
    break;

  case 354:
/* Line 670 of lalr1.cc  */
#line 902 "CxxParser.y"
    { (yyval.declarator) = YACC_REFERENCE_DECLARATOR(); }
    break;

  case 355:
/* Line 670 of lalr1.cc  */
#line 903 "CxxParser.y"
    { (yyval.declarator) = (yysemantic_stack_[(1) - (1)].declarator); }
    break;

  case 356:
/* Line 670 of lalr1.cc  */
#line 904 "CxxParser.y"
    { (yyval.declarator) = YACC_GLOBAL_DECLARATOR((yysemantic_stack_[(2) - (1)].is_template), (yysemantic_stack_[(2) - (2)].declarator)); }
    break;

  case 357:
/* Line 670 of lalr1.cc  */
#line 905 "CxxParser.y"
    { (yyval.expression) = YACC_POINTER_EXPRESSION((yysemantic_stack_[(1) - (1)].declarator), YACC_EPSILON()); }
    break;

  case 358:
/* Line 670 of lalr1.cc  */
#line 906 "CxxParser.y"
    { (yyval.expression) = YACC_POINTER_EXPRESSION((yysemantic_stack_[(2) - (1)].declarator), (yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 359:
/* Line 670 of lalr1.cc  */
#line 908 "CxxParser.y"
    { (yyval.expression) = YACC_EXPRESSION(0); }
    break;

  case 360:
/* Line 670 of lalr1.cc  */
#line 909 "CxxParser.y"
    { (yyval.expression) = YACC_POINTER_EXPRESSION((yysemantic_stack_[(2) - (1)].declarator), (yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 361:
/* Line 670 of lalr1.cc  */
#line 911 "CxxParser.y"
    { (yyval.cv_qualifiers) = YACC_CV_QUALIFIERS(0, 0); }
    break;

  case 362:
/* Line 670 of lalr1.cc  */
#line 912 "CxxParser.y"
    { (yyval.cv_qualifiers) = YACC_CV_QUALIFIERS((yysemantic_stack_[(2) - (1)].cv_qualifiers), (yysemantic_stack_[(2) - (2)].cv_qualifiers)); }
    break;

  case 363:
/* Line 670 of lalr1.cc  */
#line 913 "CxxParser.y"
    { (yyval.cv_qualifiers) = (yysemantic_stack_[(1) - (1)].cv_qualifiers); }
    break;

  case 364:
/* Line 670 of lalr1.cc  */
#line 914 "CxxParser.y"
    { (yyval.cv_qualifiers) = (yysemantic_stack_[(1) - (1)].cv_qualifiers); }
    break;

  case 365:
/* Line 670 of lalr1.cc  */
#line 917 "CxxParser.y"
    { (yyval.expression) = YACC_TYPED_EXPRESSION((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 366:
/* Line 670 of lalr1.cc  */
#line 918 "CxxParser.y"
    { (yyval.expression) = YACC_TYPED_EXPRESSION((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 367:
/* Line 670 of lalr1.cc  */
#line 921 "CxxParser.y"
    { (yyval.expression) = YACC_EPSILON(); }
    break;

  case 368:
/* Line 670 of lalr1.cc  */
#line 922 "CxxParser.y"
    { (yyval.expression) = YACC_POINTER_EXPRESSION((yysemantic_stack_[(2) - (1)].declarator), (yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 369:
/* Line 670 of lalr1.cc  */
#line 923 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 370:
/* Line 670 of lalr1.cc  */
#line 924 "CxxParser.y"
    { (yyval.expression) = YACC_EPSILON(); }
    break;

  case 371:
/* Line 670 of lalr1.cc  */
#line 925 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 372:
/* Line 670 of lalr1.cc  */
#line 926 "CxxParser.y"
    { (yyval.expression) = YACC_CALL_EXPRESSION((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].parenthesised)); }
    break;

  case 373:
/* Line 670 of lalr1.cc  */
#line 927 "CxxParser.y"
    { (yyval.expression) = YACC_ARRAY_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), 0); }
    break;

  case 374:
/* Line 670 of lalr1.cc  */
#line 928 "CxxParser.y"
    { (yyval.expression) = YACC_ARRAY_EXPRESSION((yysemantic_stack_[(4) - (1)].expression), (yysemantic_stack_[(4) - (3)].expression)); }
    break;

  case 375:
/* Line 670 of lalr1.cc  */
#line 931 "CxxParser.y"
    { (yyval.parenthesised) = YACC_PARENTHESISED((yysemantic_stack_[(2) - (1)].parameters), (yysemantic_stack_[(2) - (2)].cv_qualifiers), 0); }
    break;

  case 376:
/* Line 670 of lalr1.cc  */
#line 932 "CxxParser.y"
    { (yyval.parenthesised) = YACC_PARENTHESISED((yysemantic_stack_[(3) - (1)].parameters), (yysemantic_stack_[(3) - (2)].cv_qualifiers), (yysemantic_stack_[(3) - (3)].exception_specification)); }
    break;

  case 377:
/* Line 670 of lalr1.cc  */
#line 933 "CxxParser.y"
    { (yyval.parameters) = (yysemantic_stack_[(3) - (2)].parameters); }
    break;

  case 378:
/* Line 670 of lalr1.cc  */
#line 935 "CxxParser.y"
    { (yyval.parameters) = YACC_PARAMETERS(0, 0); }
    break;

  case 379:
/* Line 670 of lalr1.cc  */
#line 936 "CxxParser.y"
    { (yyval.parameters) = (yysemantic_stack_[(1) - (1)].parameters); }
    break;

  case 380:
/* Line 670 of lalr1.cc  */
#line 937 "CxxParser.y"
    { (yyval.parameters) = YACC_PARAMETERS((yysemantic_stack_[(2) - (1)].parameters), YACC_ELLIPSIS_EXPRESSION()); }
    break;

  case 381:
/* Line 670 of lalr1.cc  */
#line 938 "CxxParser.y"
    { (yyval.parameters) = YACC_PARAMETERS(0, (yysemantic_stack_[(1) - (1)].parameter)); }
    break;

  case 382:
/* Line 670 of lalr1.cc  */
#line 939 "CxxParser.y"
    { (yyval.parameters) = YACC_PARAMETERS((yysemantic_stack_[(3) - (1)].parameters), (yysemantic_stack_[(3) - (3)].parameter)); }
    break;

  case 383:
/* Line 670 of lalr1.cc  */
#line 946 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 384:
/* Line 670 of lalr1.cc  */
#line 947 "CxxParser.y"
    { (yyval.expression) = YACC_MULTIPLY_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (2)].pointer_declarator), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 385:
/* Line 670 of lalr1.cc  */
#line 948 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 386:
/* Line 670 of lalr1.cc  */
#line 949 "CxxParser.y"
    { (yyval.expression) = YACC_AND_EXPRESSION((yysemantic_stack_[(2) - (1)].expression), YACC_EPSILON()); }
    break;

  case 387:
/* Line 670 of lalr1.cc  */
#line 950 "CxxParser.y"
    { (yyval.expression) = YACC_AND_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 388:
/* Line 670 of lalr1.cc  */
#line 951 "CxxParser.y"
    { (yyval.expression) = YACC_ASSIGNMENT_EXPRESSION((yysemantic_stack_[(1) - (1)].expression), 0, 0); }
    break;

  case 389:
/* Line 670 of lalr1.cc  */
#line 952 "CxxParser.y"
    { (yyval.expression) = YACC_ASSIGNMENT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (2)].keyword), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 390:
/* Line 670 of lalr1.cc  */
#line 953 "CxxParser.y"
    { (yyval.expression) = YACC_ELLIPSIS_EXPRESSION(); }
    break;

  case 391:
/* Line 670 of lalr1.cc  */
#line 954 "CxxParser.y"
    { (yyval.parameter) = YACC_EXPRESSION_PARAMETER((yysemantic_stack_[(1) - (1)].expression)); }
    break;

  case 392:
/* Line 670 of lalr1.cc  */
#line 955 "CxxParser.y"
    { (yyval.parameter) = YACC_EXPRESSION_PARAMETER((yysemantic_stack_[(1) - (1)].expression)); }
    break;

  case 393:
/* Line 670 of lalr1.cc  */
#line 956 "CxxParser.y"
    { (yyval.parameter) = YACC_DECL_SPECIFIER_PARAMETER((yysemantic_stack_[(2) - (2)].parameter), (yysemantic_stack_[(2) - (1)].decl_specifier_id)); }
    break;

  case 394:
/* Line 670 of lalr1.cc  */
#line 960 "CxxParser.y"
    { (yyval.parameter) = YACC_EXPRESSION_PARAMETER((yysemantic_stack_[(1) - (1)].expression)); }
    break;

  case 395:
/* Line 670 of lalr1.cc  */
#line 961 "CxxParser.y"
    { (yyval.parameter) = YACC_EXPRESSION_PARAMETER((yysemantic_stack_[(1) - (1)].expression)); }
    break;

  case 396:
/* Line 670 of lalr1.cc  */
#line 962 "CxxParser.y"
    { (yyval.parameter) = YACC_EXPRESSION_PARAMETER(YACC_ASSIGNMENT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (2)].keyword), (yysemantic_stack_[(3) - (3)].expression))); }
    break;

  case 397:
/* Line 670 of lalr1.cc  */
#line 963 "CxxParser.y"
    { (yyval.parameter) = YACC_DECL_SPECIFIER_PARAMETER((yysemantic_stack_[(2) - (2)].parameter), (yysemantic_stack_[(2) - (1)].decl_specifier_id)); }
    break;

  case 398:
/* Line 670 of lalr1.cc  */
#line 964 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 399:
/* Line 670 of lalr1.cc  */
#line 965 "CxxParser.y"
    { (yyval.expression) = YACC_AND_EXPRESSION((yysemantic_stack_[(2) - (1)].expression), 0); }
    break;

  case 400:
/* Line 670 of lalr1.cc  */
#line 966 "CxxParser.y"
    { (yyval.expression) = YACC_AND_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 401:
/* Line 670 of lalr1.cc  */
#line 972 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 402:
/* Line 670 of lalr1.cc  */
#line 973 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 403:
/* Line 670 of lalr1.cc  */
#line 974 "CxxParser.y"
    { (yyval.expression) = YACC_FUNCTION_DEFINITION((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].function_body)); }
    break;

  case 404:
/* Line 670 of lalr1.cc  */
#line 975 "CxxParser.y"
    { (yyval.expression) = YACC_FUNCTION_DEFINITION((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].function_body)); }
    break;

  case 405:
/* Line 670 of lalr1.cc  */
#line 976 "CxxParser.y"
    { (yyval.expression) = YACC_DECL_SPECIFIER_EXPRESSION((yysemantic_stack_[(2) - (2)].expression), (yysemantic_stack_[(2) - (1)].decl_specifier_id)); }
    break;

  case 406:
/* Line 670 of lalr1.cc  */
#line 977 "CxxParser.y"
    { (yyval.expression) = YACC_CTOR_DEFINITION((yysemantic_stack_[(2) - (1)].expressions), (yysemantic_stack_[(2) - (2)].function_body)); }
    break;

  case 407:
/* Line 670 of lalr1.cc  */
#line 978 "CxxParser.y"
    { (yyval.expression) = YACC_CTOR_DEFINITION((yysemantic_stack_[(2) - (1)].expressions), (yysemantic_stack_[(2) - (2)].function_body)); }
    break;

  case 408:
/* Line 670 of lalr1.cc  */
#line 979 "CxxParser.y"
    { (yyval.expression) = YACC_DECL_SPECIFIER_EXPRESSION((yysemantic_stack_[(2) - (2)].expression), (yysemantic_stack_[(2) - (1)].decl_specifier_id)); }
    break;

  case 409:
/* Line 670 of lalr1.cc  */
#line 980 "CxxParser.y"
    { (yyval.expressions) = YACC_EXPRESSIONS(0, (yysemantic_stack_[(1) - (1)].expression)); }
    break;

  case 410:
/* Line 670 of lalr1.cc  */
#line 981 "CxxParser.y"
    { (yyval.expressions) = YACC_EXPRESSIONS((yysemantic_stack_[(3) - (1)].expressions), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 411:
/* Line 670 of lalr1.cc  */
#line 982 "CxxParser.y"
    { (yyval.function_body) = YACC_TRY_FUNCTION_BLOCK((yysemantic_stack_[(3) - (2)].function_body), (yysemantic_stack_[(3) - (3)].handlers)); }
    break;

  case 412:
/* Line 670 of lalr1.cc  */
#line 983 "CxxParser.y"
    { (yyval.function_body) = YACC_CTOR_FUNCTION_BLOCK((yysemantic_stack_[(2) - (2)].function_body), (yysemantic_stack_[(2) - (1)].mem_initializers)); }
    break;

  case 413:
/* Line 670 of lalr1.cc  */
#line 984 "CxxParser.y"
    { (yyval.function_body) = YACC_FUNCTION_BLOCK((yysemantic_stack_[(1) - (1)].statement)); }
    break;

  case 414:
/* Line 670 of lalr1.cc  */
#line 991 "CxxParser.y"
    { (yyval.initializer_clause) = YACC_INITIALIZER_EXPRESSION_CLAUSE((yysemantic_stack_[(1) - (1)].expression)); }
    break;

  case 416:
/* Line 670 of lalr1.cc  */
#line 993 "CxxParser.y"
    { (yyval.initializer_clause) = YACC_INITIALIZER_LIST_CLAUSE((yysemantic_stack_[(3) - (2)].initializer_clauses)); }
    break;

  case 417:
/* Line 670 of lalr1.cc  */
#line 994 "CxxParser.y"
    { (yyval.initializer_clause) = YACC_INITIALIZER_LIST_CLAUSE((yysemantic_stack_[(4) - (2)].initializer_clauses)); }
    break;

  case 418:
/* Line 670 of lalr1.cc  */
#line 995 "CxxParser.y"
    { (yyval.initializer_clause) = YACC_INITIALIZER_LIST_CLAUSE(0); }
    break;

  case 419:
/* Line 670 of lalr1.cc  */
#line 996 "CxxParser.y"
    { (yyval.initializer_clause) = 0; YACC_UNBANG((yysemantic_stack_[(6) - (4)].bang), "Bad initializer_clause."); }
    break;

  case 420:
/* Line 670 of lalr1.cc  */
#line 998 "CxxParser.y"
    { (yyval.initializer_clause) = (yysemantic_stack_[(8) - (2)].initializer_clauses); YACC_UNBANG((yysemantic_stack_[(8) - (6)].bang), "Bad initializer_clause."); }
    break;

  case 421:
/* Line 670 of lalr1.cc  */
#line 999 "CxxParser.y"
    { (yyval.initializer_clauses) = YACC_INITIALIZER_CLAUSES(0, (yysemantic_stack_[(1) - (1)].initializer_clause)); }
    break;

  case 422:
/* Line 670 of lalr1.cc  */
#line 1000 "CxxParser.y"
    { (yyval.initializer_clauses) = YACC_INITIALIZER_CLAUSES((yysemantic_stack_[(3) - (1)].initializer_clauses), (yysemantic_stack_[(3) - (3)].initializer_clause)); }
    break;

  case 423:
/* Line 670 of lalr1.cc  */
#line 1001 "CxxParser.y"
    { (yyval.initializer_clause) = (yysemantic_stack_[(2) - (2)].initializer_clause); m_pDriver->getLexer()->end_search((yyval.initializer_clause)); }
    break;

  case 425:
/* Line 670 of lalr1.cc  */
#line 1003 "CxxParser.y"
    { (yyval.initializer_clause) = (yysemantic_stack_[(3) - (3)].initializer_clause); }
    break;

  case 426:
/* Line 670 of lalr1.cc  */
#line 1004 "CxxParser.y"
    { (yyval.initializer_clause) = 0; }
    break;

  case 427:
/* Line 670 of lalr1.cc  */
#line 1019 "CxxParser.y"
    { (yyval.mark) = m_pDriver->getLexer()->mark(); }
    break;

  case 428:
/* Line 670 of lalr1.cc  */
#line 1020 "CxxParser.y"
    { (yyval.name) = YACC_ELABORATED_TYPE_SPECIFIER((yysemantic_stack_[(2) - (1)].class_key), (yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 429:
/* Line 670 of lalr1.cc  */
#line 1021 "CxxParser.y"
    { (yyval.name) = YACC_ELABORATED_TYPE_SPECIFIER((yysemantic_stack_[(4) - (1)].class_key), (yysemantic_stack_[(4) - (2)].name)); m_pDriver->getLexer()->rewind_colon((yysemantic_stack_[(4) - (3)].mark), (yyval.name)); }
    break;

  case 430:
/* Line 670 of lalr1.cc  */
#line 1022 "CxxParser.y"
    { m_pDriver->getLexer()->unmark((yysemantic_stack_[(5) - (4)].base_specifiers)); (yyval._class) = YACC_CLASS_SPECIFIER_ID((yysemantic_stack_[(5) - (1)].class_key), (yysemantic_stack_[(5) - (2)].name), (yysemantic_stack_[(5) - (4)].base_specifiers)); }
    break;

  case 431:
/* Line 670 of lalr1.cc  */
#line 1023 "CxxParser.y"
    { (yyval._class) = YACC_CLASS_SPECIFIER_ID((yysemantic_stack_[(4) - (1)].class_key), 0, (yysemantic_stack_[(4) - (3)].base_specifiers)); }
    break;

  case 432:
/* Line 670 of lalr1.cc  */
#line 1024 "CxxParser.y"
    { (yyval._class) = YACC_CLASS_SPECIFIER_ID((yysemantic_stack_[(3) - (1)].class_key), (yysemantic_stack_[(3) - (2)].name), 0); }
    break;

  case 433:
/* Line 670 of lalr1.cc  */
#line 1025 "CxxParser.y"
    { (yyval._class) = YACC_CLASS_SPECIFIER_ID((yysemantic_stack_[(2) - (1)].class_key), 0, 0); }
    break;

  case 437:
/* Line 670 of lalr1.cc  */
#line 1027 "CxxParser.y"
    { (yyval.name) = YACC_CLASS_MEMBERS((yysemantic_stack_[(3) - (1)]._class), (yysemantic_stack_[(3) - (2)].member_declarations)); }
    break;

  case 438:
/* Line 670 of lalr1.cc  */
#line 1029 "CxxParser.y"
    { (yyval.name) = YACC_CLASS_MEMBERS((yysemantic_stack_[(8) - (1)]._class), (yysemantic_stack_[(8) - (2)].member_declarations)); YACC_UNBANG((yysemantic_stack_[(8) - (6)].bang), "Bad member_specification.opt."); }
    break;

  case 439:
/* Line 670 of lalr1.cc  */
#line 1030 "CxxParser.y"
    { (yyval.member_declarations) = YACC_MEMBER_DECLARATIONS(0, 0); }
    break;

  case 440:
/* Line 670 of lalr1.cc  */
#line 1031 "CxxParser.y"
    { (yyval.member_declarations) = YACC_MEMBER_DECLARATIONS((yysemantic_stack_[(3) - (1)].member_declarations), YACC_COMPILE_MEMBER_DECLARATION((yysemantic_stack_[(3) - (2)].utility), (yysemantic_stack_[(3) - (3)].member_declaration))); }
    break;

  case 441:
/* Line 670 of lalr1.cc  */
#line 1033 "CxxParser.y"
    { (yyval.member_declarations) = (yysemantic_stack_[(7) - (1)].member_declarations); YACC_UNBANG((yysemantic_stack_[(7) - (5)].bang), "Bad member-declaration."); }
    break;

  case 442:
/* Line 670 of lalr1.cc  */
#line 1034 "CxxParser.y"
    { (yyval.member_declaration) = YACC_LINED_MEMBER_DECLARATION((yysemantic_stack_[(2) - (2)].member_declaration), (yysemantic_stack_[(2) - (1)].line)); m_pDriver->getLexer()->end_search((yyval.member_declaration)); }
    break;

  case 444:
/* Line 670 of lalr1.cc  */
#line 1036 "CxxParser.y"
    { (yyval.member_declaration) = (yysemantic_stack_[(3) - (3)].member_declaration); }
    break;

  case 445:
/* Line 670 of lalr1.cc  */
#line 1037 "CxxParser.y"
    { (yyval.member_declaration) = 0; }
    break;

  case 446:
/* Line 670 of lalr1.cc  */
#line 1038 "CxxParser.y"
    { (yyval.member_declaration) = (yysemantic_stack_[(1) - (1)].member_declaration); }
    break;

  case 447:
/* Line 670 of lalr1.cc  */
#line 1039 "CxxParser.y"
    { (yyval.member_declaration) = YACC_MEMBER_DECLARATION((yysemantic_stack_[(1) - (1)].expression)); }
    break;

  case 448:
/* Line 670 of lalr1.cc  */
#line 1040 "CxxParser.y"
    { (yyval.member_declaration) = YACC_MEMBER_DECLARATION((yysemantic_stack_[(1) - (1)].expression)); }
    break;

  case 449:
/* Line 670 of lalr1.cc  */
#line 1043 "CxxParser.y"
    { (yyval.member_declaration) = YACC_MEMBER_DECLARATION((yysemantic_stack_[(1) - (1)].declaration)); }
    break;

  case 450:
/* Line 670 of lalr1.cc  */
#line 1044 "CxxParser.y"
    { (yyval.member_declaration) = YACC_MEMBER_DECLARATION((yysemantic_stack_[(1) - (1)].declaration)); }
    break;

  case 451:
/* Line 670 of lalr1.cc  */
#line 1051 "CxxParser.y"
    { (yyval.expression) = YACC_EXPRESSION(0); }
    break;

  case 452:
/* Line 670 of lalr1.cc  */
#line 1052 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(2) - (1)].expression); }
    break;

  case 453:
/* Line 670 of lalr1.cc  */
#line 1053 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(2) - (1)].expressions); }
    break;

  case 454:
/* Line 670 of lalr1.cc  */
#line 1054 "CxxParser.y"
    { (yyval.expression) = (yysemantic_stack_[(2) - (1)].expressions); }
    break;

  case 455:
/* Line 670 of lalr1.cc  */
#line 1055 "CxxParser.y"
    { (yyval.expression) = YACC_DECL_SPECIFIER_EXPRESSION((yysemantic_stack_[(2) - (2)].expression), (yysemantic_stack_[(2) - (1)].decl_specifier_id)); }
    break;

  case 456:
/* Line 670 of lalr1.cc  */
#line 1056 "CxxParser.y"
    { (yyval.expressions) = YACC_EXPRESSIONS(YACC_EXPRESSIONS(0, (yysemantic_stack_[(3) - (1)].expression)), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 457:
/* Line 670 of lalr1.cc  */
#line 1057 "CxxParser.y"
    { (yyval.expressions) = YACC_EXPRESSIONS((yysemantic_stack_[(3) - (1)].expressions), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 458:
/* Line 670 of lalr1.cc  */
#line 1058 "CxxParser.y"
    { (yyval.expressions) = YACC_EXPRESSIONS((yysemantic_stack_[(3) - (1)].expressions), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 461:
/* Line 670 of lalr1.cc  */
#line 1063 "CxxParser.y"
    { (yyval.member_declaration) = YACC_ACCESSIBILITY_SPECIFIER((yysemantic_stack_[(2) - (1)].access_specifier)); }
    break;

  case 462:
/* Line 670 of lalr1.cc  */
#line 1064 "CxxParser.y"
    { (yyval.expression) = YACC_BIT_FIELD_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 463:
/* Line 670 of lalr1.cc  */
#line 1065 "CxxParser.y"
    { (yyval.expression) = YACC_BIT_FIELD_EXPRESSION(0, (yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 465:
/* Line 670 of lalr1.cc  */
#line 1068 "CxxParser.y"
    { (yyval.expression) = YACC_CONDITIONAL_EXPRESSION((yysemantic_stack_[(5) - (1)].expression), (yysemantic_stack_[(5) - (3)].expression), (yysemantic_stack_[(5) - (5)].expression)); }
    break;

  case 467:
/* Line 670 of lalr1.cc  */
#line 1070 "CxxParser.y"
    { (yyval.expression) = YACC_ASSIGNMENT_EXPRESSION((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (2)].keyword), (yysemantic_stack_[(3) - (3)].initializer_clause)); }
    break;

  case 468:
/* Line 670 of lalr1.cc  */
#line 1076 "CxxParser.y"
    { (yyval.base_specifiers) = YACC_BASE_SPECIFIERS(0, (yysemantic_stack_[(1) - (1)].base_specifier)); }
    break;

  case 469:
/* Line 670 of lalr1.cc  */
#line 1077 "CxxParser.y"
    { (yyval.base_specifiers) = YACC_BASE_SPECIFIERS((yysemantic_stack_[(3) - (1)].base_specifiers), (yysemantic_stack_[(3) - (3)].base_specifier)); }
    break;

  case 470:
/* Line 670 of lalr1.cc  */
#line 1078 "CxxParser.y"
    { (yyval.base_specifier) = YACC_BASE_SPECIFIER((yysemantic_stack_[(1) - (1)].name)); }
    break;

  case 471:
/* Line 670 of lalr1.cc  */
#line 1079 "CxxParser.y"
    { (yyval.base_specifier) = YACC_ACCESS_BASE_SPECIFIER((yysemantic_stack_[(2) - (2)].base_specifier), (yysemantic_stack_[(2) - (1)].access_specifier)); }
    break;

  case 472:
/* Line 670 of lalr1.cc  */
#line 1080 "CxxParser.y"
    { (yyval.base_specifier) = YACC_VIRTUAL_BASE_SPECIFIER((yysemantic_stack_[(2) - (2)].base_specifier)); }
    break;

  case 476:
/* Line 670 of lalr1.cc  */
#line 1086 "CxxParser.y"
    { (yyval.name) = YACC_CONVERSION_FUNCTION_ID((yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 477:
/* Line 670 of lalr1.cc  */
#line 1087 "CxxParser.y"
    { (yyval.expression) = YACC_TYPED_EXPRESSION((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 478:
/* Line 670 of lalr1.cc  */
#line 1088 "CxxParser.y"
    { (yyval.expression) = YACC_TYPED_EXPRESSION((yysemantic_stack_[(2) - (1)].name), (yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 479:
/* Line 670 of lalr1.cc  */
#line 1096 "CxxParser.y"
    { (yyval.mem_initializers) = YACC_MEM_INITIALIZERS(0, 0); }
    break;

  case 481:
/* Line 670 of lalr1.cc  */
#line 1098 "CxxParser.y"
    { (yyval.mem_initializers) = (yysemantic_stack_[(2) - (2)].mem_initializers); }
    break;

  case 482:
/* Line 670 of lalr1.cc  */
#line 1099 "CxxParser.y"
    { (yyval.mem_initializers) = (yysemantic_stack_[(4) - (2)].mem_initializers); YACC_UNBANG((yysemantic_stack_[(4) - (3)].bang), "Bad ctor-initializer."); }
    break;

  case 483:
/* Line 670 of lalr1.cc  */
#line 1100 "CxxParser.y"
    { (yyval.mem_initializers) = YACC_MEM_INITIALIZERS(0, (yysemantic_stack_[(1) - (1)].mem_initializer)); }
    break;

  case 484:
/* Line 670 of lalr1.cc  */
#line 1101 "CxxParser.y"
    { (yyval.mem_initializers) = YACC_MEM_INITIALIZERS((yysemantic_stack_[(2) - (1)].mem_initializers), (yysemantic_stack_[(2) - (2)].mem_initializer)); }
    break;

  case 486:
/* Line 670 of lalr1.cc  */
#line 1103 "CxxParser.y"
    { YACC_UNBANG((yysemantic_stack_[(4) - (2)].bang), "Bad mem-initializer."); }
    break;

  case 487:
/* Line 670 of lalr1.cc  */
#line 1104 "CxxParser.y"
    { (yyval.mem_initializer) = YACC_MEM_INITIALIZER((yysemantic_stack_[(4) - (1)].name), (yysemantic_stack_[(4) - (3)].expressions)); }
    break;

  case 489:
/* Line 670 of lalr1.cc  */
#line 1110 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_FUNCTION_ID((yysemantic_stack_[(2) - (2)].name)); }
    break;

  case 490:
/* Line 670 of lalr1.cc  */
#line 1120 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_NEW_ID(); }
    break;

  case 491:
/* Line 670 of lalr1.cc  */
#line 1121 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_DELETE_ID(); }
    break;

  case 492:
/* Line 670 of lalr1.cc  */
#line 1126 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_ADD_ID(); }
    break;

  case 493:
/* Line 670 of lalr1.cc  */
#line 1127 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_SUB_ID(); }
    break;

  case 494:
/* Line 670 of lalr1.cc  */
#line 1128 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_MUL_ID(); }
    break;

  case 495:
/* Line 670 of lalr1.cc  */
#line 1129 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_DIV_ID(); }
    break;

  case 496:
/* Line 670 of lalr1.cc  */
#line 1130 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_MOD_ID(); }
    break;

  case 497:
/* Line 670 of lalr1.cc  */
#line 1131 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_XOR_ID(); }
    break;

  case 498:
/* Line 670 of lalr1.cc  */
#line 1132 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_BIT_AND_ID(); }
    break;

  case 499:
/* Line 670 of lalr1.cc  */
#line 1133 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_BIT_OR_ID(); }
    break;

  case 500:
/* Line 670 of lalr1.cc  */
#line 1134 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_BIT_NOT_ID(); }
    break;

  case 501:
/* Line 670 of lalr1.cc  */
#line 1135 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_LOG_NOT_ID(); }
    break;

  case 502:
/* Line 670 of lalr1.cc  */
#line 1136 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_ASS_ID(); }
    break;

  case 503:
/* Line 670 of lalr1.cc  */
#line 1137 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_LT_ID(); }
    break;

  case 504:
/* Line 670 of lalr1.cc  */
#line 1138 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_GT_ID(); }
    break;

  case 505:
/* Line 670 of lalr1.cc  */
#line 1139 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_ASS_ADD_ID(); }
    break;

  case 506:
/* Line 670 of lalr1.cc  */
#line 1140 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_ASS_SUB_ID(); }
    break;

  case 507:
/* Line 670 of lalr1.cc  */
#line 1141 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_ASS_MUL_ID(); }
    break;

  case 508:
/* Line 670 of lalr1.cc  */
#line 1142 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_ASS_DIV_ID(); }
    break;

  case 509:
/* Line 670 of lalr1.cc  */
#line 1143 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_ASS_MOD_ID(); }
    break;

  case 510:
/* Line 670 of lalr1.cc  */
#line 1144 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_ASS_XOR_ID(); }
    break;

  case 511:
/* Line 670 of lalr1.cc  */
#line 1145 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_ASS_BIT_AND_ID(); }
    break;

  case 512:
/* Line 670 of lalr1.cc  */
#line 1146 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_ASS_BIT_OR_ID(); }
    break;

  case 513:
/* Line 670 of lalr1.cc  */
#line 1147 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_SHL_ID(); }
    break;

  case 514:
/* Line 670 of lalr1.cc  */
#line 1148 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_SHR_ID(); }
    break;

  case 515:
/* Line 670 of lalr1.cc  */
#line 1149 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_ASS_SHR_ID(); }
    break;

  case 516:
/* Line 670 of lalr1.cc  */
#line 1150 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_ASS_SHL_ID(); }
    break;

  case 517:
/* Line 670 of lalr1.cc  */
#line 1151 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_EQ_ID(); }
    break;

  case 518:
/* Line 670 of lalr1.cc  */
#line 1152 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_NE_ID(); }
    break;

  case 519:
/* Line 670 of lalr1.cc  */
#line 1153 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_LE_ID(); }
    break;

  case 520:
/* Line 670 of lalr1.cc  */
#line 1154 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_GE_ID(); }
    break;

  case 521:
/* Line 670 of lalr1.cc  */
#line 1155 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_LOG_AND_ID(); }
    break;

  case 522:
/* Line 670 of lalr1.cc  */
#line 1156 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_LOG_OR_ID(); }
    break;

  case 523:
/* Line 670 of lalr1.cc  */
#line 1157 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_INC_ID(); }
    break;

  case 524:
/* Line 670 of lalr1.cc  */
#line 1158 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_DEC_ID(); }
    break;

  case 525:
/* Line 670 of lalr1.cc  */
#line 1159 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_COMMA_ID(); }
    break;

  case 526:
/* Line 670 of lalr1.cc  */
#line 1160 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_ARROW_STAR_ID(); }
    break;

  case 527:
/* Line 670 of lalr1.cc  */
#line 1161 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_ARROW_ID(); }
    break;

  case 528:
/* Line 670 of lalr1.cc  */
#line 1162 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_CALL_ID(); }
    break;

  case 529:
/* Line 670 of lalr1.cc  */
#line 1163 "CxxParser.y"
    { (yyval.name) = YACC_OPERATOR_INDEX_ID(); }
    break;

  case 530:
/* Line 670 of lalr1.cc  */
#line 1168 "CxxParser.y"
    { (yyval.declaration) = YACC_TEMPLATE_DECLARATION((yysemantic_stack_[(2) - (1)].template_parameters), (yysemantic_stack_[(2) - (2)].declaration)); }
    break;

  case 531:
/* Line 670 of lalr1.cc  */
#line 1169 "CxxParser.y"
    { (yyval.declaration) = YACC_DECL_SPECIFIER_DECLARATION((yysemantic_stack_[(2) - (2)].declaration), (yysemantic_stack_[(2) - (1)].decl_specifier_id)); }
    break;

  case 532:
/* Line 670 of lalr1.cc  */
#line 1170 "CxxParser.y"
    { (yyval.template_parameters) = (yysemantic_stack_[(4) - (3)].template_parameters); }
    break;

  case 533:
/* Line 670 of lalr1.cc  */
#line 1171 "CxxParser.y"
    { (yyval.template_parameters) = YACC_TEMPLATE_PARAMETERS(0, (yysemantic_stack_[(1) - (1)].template_parameter)); }
    break;

  case 534:
/* Line 670 of lalr1.cc  */
#line 1172 "CxxParser.y"
    { (yyval.template_parameters) = YACC_TEMPLATE_PARAMETERS((yysemantic_stack_[(3) - (1)].template_parameters), (yysemantic_stack_[(3) - (3)].template_parameter)); }
    break;

  case 535:
/* Line 670 of lalr1.cc  */
#line 1173 "CxxParser.y"
    { (yyval.template_parameter) = YACC_INIT_SIMPLE_TYPE_PARAMETER((yysemantic_stack_[(1) - (1)].simple_type_parameter), 0); }
    break;

  case 536:
/* Line 670 of lalr1.cc  */
#line 1174 "CxxParser.y"
    { (yyval.template_parameter) = YACC_INIT_SIMPLE_TYPE_PARAMETER((yysemantic_stack_[(3) - (1)].simple_type_parameter), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 537:
/* Line 670 of lalr1.cc  */
#line 1175 "CxxParser.y"
    { (yyval.template_parameter) = YACC_INIT_TEMPLATED_PARAMETER((yysemantic_stack_[(1) - (1)].templated_type_parameter), 0); }
    break;

  case 538:
/* Line 670 of lalr1.cc  */
#line 1176 "CxxParser.y"
    { (yyval.template_parameter) = YACC_INIT_TEMPLATED_PARAMETER((yysemantic_stack_[(3) - (1)].templated_type_parameter), (yysemantic_stack_[(3) - (3)].name)); }
    break;

  case 539:
/* Line 670 of lalr1.cc  */
#line 1177 "CxxParser.y"
    { (yyval.template_parameter) = YACC_TEMPLATE_PARAMETER((yysemantic_stack_[(1) - (1)].parameter)); }
    break;

  case 540:
/* Line 670 of lalr1.cc  */
#line 1178 "CxxParser.y"
    { (yyval.template_parameter) = 0; YACC_UNBANG((yysemantic_stack_[(2) - (1)].bang), "Bad template-parameter."); }
    break;

  case 541:
/* Line 670 of lalr1.cc  */
#line 1179 "CxxParser.y"
    { (yyval.simple_type_parameter) = YACC_CLASS_TYPE_PARAMETER(0); }
    break;

  case 542:
/* Line 670 of lalr1.cc  */
#line 1181 "CxxParser.y"
    { (yyval.simple_type_parameter) = YACC_TYPENAME_TYPE_PARAMETER(0); }
    break;

  case 543:
/* Line 670 of lalr1.cc  */
#line 1183 "CxxParser.y"
    { (yyval.templated_type_parameter) = YACC_TEMPLATED_TYPE_PARAMETER((yysemantic_stack_[(2) - (1)].template_parameters), 0); }
    break;

  case 544:
/* Line 670 of lalr1.cc  */
#line 1184 "CxxParser.y"
    { (yyval.templated_type_parameter) = YACC_TEMPLATED_TYPE_PARAMETER((yysemantic_stack_[(3) - (1)].template_parameters), (yysemantic_stack_[(3) - (3)].name)); }
    break;

  case 545:
/* Line 670 of lalr1.cc  */
#line 1185 "CxxParser.y"
    { (yyval.name) = YACC_TEMPLATE_NAME((yysemantic_stack_[(5) - (2)].name), (yysemantic_stack_[(5) - (4)].template_arguments)); }
    break;

  case 546:
/* Line 670 of lalr1.cc  */
#line 1186 "CxxParser.y"
    { (yyval.name) = (yysemantic_stack_[(2) - (2)].name); }
    break;

  case 547:
/* Line 670 of lalr1.cc  */
#line 1190 "CxxParser.y"
    { (yyval.template_arguments) = YACC_TEMPLATE_ARGUMENTS(0, (yysemantic_stack_[(1) - (1)].template_argument)); }
    break;

  case 548:
/* Line 670 of lalr1.cc  */
#line 1191 "CxxParser.y"
    { (yyval.template_arguments) = YACC_TEMPLATE_ARGUMENTS((yysemantic_stack_[(3) - (1)].template_arguments), (yysemantic_stack_[(3) - (3)].template_argument)); }
    break;

  case 549:
/* Line 670 of lalr1.cc  */
#line 1192 "CxxParser.y"
    { (yyval.template_argument) = YACC_TEMPLATE_ARGUMENT((yysemantic_stack_[(1) - (1)].parameter)); }
    break;

  case 550:
/* Line 670 of lalr1.cc  */
#line 1202 "CxxParser.y"
    { (yyval.declaration) = YACC_EXPLICIT_SPECIALIZATION((yysemantic_stack_[(4) - (4)].declaration)); }
    break;

  case 551:
/* Line 670 of lalr1.cc  */
#line 1207 "CxxParser.y"
    { (yyval.function_body) = YACC_TRY_BLOCK((yysemantic_stack_[(3) - (2)].statement), (yysemantic_stack_[(3) - (3)].handlers)); }
    break;

  case 552:
/* Line 670 of lalr1.cc  */
#line 1209 "CxxParser.y"
    { (yyval.handlers) = YACC_HANDLERS(0, (yysemantic_stack_[(1) - (1)].handler)); }
    break;

  case 553:
/* Line 670 of lalr1.cc  */
#line 1210 "CxxParser.y"
    { (yyval.handlers) = YACC_HANDLERS((yysemantic_stack_[(2) - (2)].handlers), (yysemantic_stack_[(2) - (1)].handler)); }
    break;

  case 554:
/* Line 670 of lalr1.cc  */
#line 1211 "CxxParser.y"
    { (yyval.handler) = YACC_HANDLER((yysemantic_stack_[(5) - (3)].exception_declaration), (yysemantic_stack_[(5) - (5)].statement)); }
    break;

  case 555:
/* Line 670 of lalr1.cc  */
#line 1212 "CxxParser.y"
    { (yyval.exception_declaration) = YACC_EXCEPTION_DECLARATION((yysemantic_stack_[(1) - (1)].parameter)); }
    break;

  case 556:
/* Line 670 of lalr1.cc  */
#line 1214 "CxxParser.y"
    { (yyval.expression) = YACC_THROW_EXPRESSION(0); }
    break;

  case 557:
/* Line 670 of lalr1.cc  */
#line 1215 "CxxParser.y"
    { (yyval.expression) = YACC_THROW_EXPRESSION((yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 558:
/* Line 670 of lalr1.cc  */
#line 1216 "CxxParser.y"
    { (yyval.expression) = YACC_THROW_EXPRESSION(0); }
    break;

  case 559:
/* Line 670 of lalr1.cc  */
#line 1217 "CxxParser.y"
    { (yyval.expression) = YACC_THROW_EXPRESSION((yysemantic_stack_[(2) - (2)].expression)); }
    break;

  case 560:
/* Line 670 of lalr1.cc  */
#line 1218 "CxxParser.y"
    { (yyval.exception_specification) = YACC_EXCEPTION_SPECIFICATION(0); }
    break;

  case 561:
/* Line 670 of lalr1.cc  */
#line 1219 "CxxParser.y"
    { (yyval.exception_specification) = YACC_EXCEPTION_SPECIFICATION((yysemantic_stack_[(4) - (3)].expressions)); }
    break;

  case 562:
/* Line 670 of lalr1.cc  */
#line 1220 "CxxParser.y"
    { (yyval.expressions) = YACC_EXPRESSIONS(0, (yysemantic_stack_[(1) - (1)].expression)); }
    break;

  case 563:
/* Line 670 of lalr1.cc  */
#line 1221 "CxxParser.y"
    { (yyval.expressions) = YACC_EXPRESSIONS((yysemantic_stack_[(3) - (1)].expressions), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 564:
/* Line 670 of lalr1.cc  */
#line 1226 "CxxParser.y"
    { yyerrok; yyclearin; m_pDriver->getLexer()->advance_search(); }
    break;

  case 565:
/* Line 670 of lalr1.cc  */
#line 1227 "CxxParser.y"
    { (yyval.bang) = YACC_BANG(); }
    break;

  case 566:
/* Line 670 of lalr1.cc  */
#line 1228 "CxxParser.y"
    { (yyval.mark) = m_pDriver->getLexer()->mark(); }
    break;

  case 567:
/* Line 670 of lalr1.cc  */
#line 1229 "CxxParser.y"
    { (yyval.nest) = m_pDriver->getLexer()->nest(); }
    break;

  case 568:
/* Line 670 of lalr1.cc  */
#line 1230 "CxxParser.y"
    { (yyval.line) = YACC_LINE(); m_pDriver->getLexer()->start_search(false); }
    break;

  case 569:
/* Line 670 of lalr1.cc  */
#line 1231 "CxxParser.y"
    { (yyval.line) = YACC_LINE(); m_pDriver->getLexer()->start_search(true); }
    break;

  case 570:
/* Line 670 of lalr1.cc  */
#line 1232 "CxxParser.y"
    { (yyval.utility) = YACC_UTILITY_MODE(); }
    break;


/* Line 670 of lalr1.cc  */
#line 3689 "CxxParser.cxx"
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
  const short int CxxParser::yypact_ninf_ = -652;
  const short int
  CxxParser::yypact_[] =
  {
       192,  -652,   265,   285,  2632,  -652,  -652,  4156,  4156,  -652,
    -652,  4156,  4156,  3775,  2632,  4156,  4156,  -652,  -652,  -652,
    -652,  -652,  -652,  -652,  -652,  -652,  -652,  -652,  -652,  -652,
    -652,    75,  -652,    28,  -652,  -652,  -652,  -652,  -652,  -652,
    -652,  -652,  -652,  -652,  -652,  4748,  -652,  -652,   290,  4156,
     314,  -652,  4817,  4283,   330,  4156,   371,  -652,  3775,  -652,
     273,  -652,  -652,  -652,  -652,  -652,  -652,  -652,  -652,  -652,
    -652,  -652,   433,   397,   229,   297,  -652,  -652,  -652,  -652,
    -652,  -652,  -652,  -652,   436,  -652,  4351,   540,   427,  -652,
    -652,  -652,  -652,    64,   498,   413,   388,   400,   346,   462,
     483,   463,   456,  1345,  -652,   468,  -652,  1957,   535,  1957,
    -652,   863,  -652,  -652,   501,  -652,  2632,  -652,  -652,  -652,
    -652,  -652,  -652,  -652,   407,  -652,  4156,  -652,  -652,  -652,
    -652,  -652,   493,  -652,  -652,  -652,    55,  -652,  -652,  -652,
    -652,  -652,   390,  1866,  4846,  -652,  4156,  -652,  -652,  -652,
     498,   504,   509,  -652,  -652,  2632,   511,    70,  -652,  -652,
    -652,  -652,   144,    28,     8,     8,   526,  -652,  -652,  5045,
     542,  -652,  -652,  -652,  -652,  -652,  -652,  -652,  5107,  -652,
    5107,  1117,  -652,   537,  4425,  -652,  -652,  -652,  -652,  4817,
    -652,  -652,  -652,  -652,  -652,  -652,  -652,  -652,  -652,  -652,
    -652,  -652,  -652,   544,   546,  -652,  -652,  -652,  -652,  -652,
    -652,  -652,  -652,  -652,  -652,  -652,  -652,  -652,  -652,  -652,
    -652,  -652,  -652,  -652,  -652,  -652,  -652,  -652,  -652,  -652,
    4459,  -652,  -652,  5107,  -652,  -652,  5107,  -652,  -652,  -652,
     513,  -652,    53,  -652,  -652,  -652,  -652,  -652,     8,   131,
    -652,  -652,  -652,  -652,  -652,  -652,  3775,  1159,  1159,  -652,
    -652,  -652,  3775,  4156,  4156,  4156,  4156,  3394,  4156,  4156,
    4156,  4156,  4156,  4156,  4156,  4156,  4156,  4156,  4156,  4156,
    4156,  4156,   551,  3775,  4156,  -652,  -652,  -652,  -652,  -652,
    -652,  -652,  -652,  -652,  -652,  3775,  -652,  -652,  -652,   568,
    1042,    53,   131,  1180,  -652,  1957,  -652,   573,  -652,  -652,
    3394,  -652,  -652,  -652,  -652,    12,  3775,   577,   819,  -652,
      87,  -652,  -652,  4156,  -652,   103,   261,   472,  4527,   659,
     593,   101,  -652,  -652,  -652,  -652,  -652,  -652,  2378,  -652,
    -652,  -652,  -652,  -652,  -652,   500,   604,  -652,  -652,  -652,
     307,   622,  -652,  -652,  2251,  -652,   550,  5136,  3394,  4156,
    -652,  -652,  -652,  2632,  -652,  -652,  -652,  -652,   524,    79,
     646,     8,  -652,  3140,  1436,   638,   641,  3775,  -652,  3775,
      51,    51,  -652,  -652,   642,   423,  -652,   537,   537,  -652,
    -652,   454,  -652,  -652,   647,   655,  2759,  -652,  -652,  -652,
     648,  1250,  1159,  1478,  1507,  -652,  -652,  -652,  -652,  1314,
    -652,  -652,  -652,  -652,  -652,  -652,   563,   644,  -652,  -652,
      64,    64,    64,  4156,  -652,   498,   498,   413,   413,   388,
     388,   388,   388,   400,   400,   346,  -652,   504,   483,   463,
     666,  -652,   663,   456,  -652,   684,  -652,   670,  -652,  -652,
    -652,  -652,  -652,  -652,  -652,  -652,   819,  -652,   115,  -652,
     819,  -652,  -652,   652,   700,   276,  -652,  -652,   235,  -652,
     693,  -652,   688,  2886,  4921,  -652,  -652,    28,   353,   353,
     682,   472,  4156,  -652,  3775,   697,  -652,  -652,  -652,  -652,
    -652,  -652,  -652,  3775,  -652,  3775,  -652,  -652,  3521,  -652,
    1866,  -652,  -652,  -652,  -652,   702,   281,  -652,   718,   124,
    3902,   388,   232,   367,   713,   715,   714,   687,  1609,  -652,
    -652,  3140,  -652,  -652,   712,   380,  -652,  -652,   279,  -652,
    -652,   434,   465,   716,   720,   723,   717,  -652,   731,  4156,
     397,    51,    51,  -652,  -652,  -652,  -652,   733,   736,  -652,
     381,  -652,  1367,  -652,  1367,  1478,   932,  -652,  1507,  -652,
     747,  -652,  1995,  -652,  -652,   159,   627,  2124,  3775,  4881,
     629,  1737,  -652,  -652,   819,  -652,  -652,   230,   732,  4156,
    -652,    28,  -652,  3267,  -652,  -652,  2251,   291,    28,  4607,
    -652,   698,   396,  -652,   755,   756,   773,   746,   751,  -652,
     760,  -652,   763,  -652,  -652,    28,   691,   768,  -652,  -652,
    -652,  -652,  -652,  -652,  -652,  4156,  -652,  -652,  -652,   787,
     770,  -652,  -652,   784,  -652,  4156,  4156,  4156,  4156,  4156,
    4156,  4156,  4156,  4156,  -652,  3902,  4156,  3902,  -652,  3902,
    -652,  3140,  -652,  4029,  -652,  3775,  3775,  -652,  3775,  -652,
     429,  -652,   776,  3775,  3775,  -652,   932,   966,  1367,  -652,
    2632,   508,  -652,   779,  -652,  -652,  -652,   580,  -652,  -652,
    -652,    73,  -652,  -652,   677,   518,  2505,  -652,  -652,   207,
    -652,  -652,  -652,   591,  -652,   780,  -652,   590,  -652,  -652,
    -652,   786,   783,   765,  -652,   524,  -652,  3267,  5107,   524,
    -652,  -652,  -652,   774,  -652,   673,  1608,  -652,    90,    28,
    -652,   789,   794,  -652,   691,  -652,  -652,   174,  4156,   388,
     388,   388,   232,   232,   367,  -652,   784,   715,   714,   785,
     802,   790,   687,  -652,  -652,  -652,  -652,   807,   805,   806,
    -652,  -652,   808,   809,   966,  1367,   595,   132,  -652,  -652,
     703,   831,  2124,  -652,  -652,  5107,   838,  -652,  3648,  -652,
    -652,  3648,  -652,  3648,  -652,  1737,  -652,  4156,  -652,  -652,
    -652,  -652,  -652,  -652,  -652,  -652,  -652,    28,  4676,   811,
    4156,   812,   827,  -652,   830,   524,   832,  3775,   834,   768,
     835,   841,   829,  -652,  -652,  -652,  -652,  -652,  -652,  -652,
    -652,  -652,  -652,  3013,  -652,   625,  -652,   865,  -652,  3775,
    2632,  -652,  -652,  3902,  3902,  -652,  -652,  -652,  -652,  -652,
    -652,  -652,   869,  -652,   851,  -652,  -652,   117,   857,  -652,
    -652,   857,  -652,  -652,  -652,  -652,   749,   878,   867,  4983,
    -652,   868,  -652,  -652,   764,  3013,   858,  2632,   860,  2632,
     691,  2632,  -652,  1608,  -652,   862,   872,  -652,   874,  -652,
     866,  -652,   898,  -652,  -652,  -652,  -652,   359,  -652,  -652,
     879,  2632,  -652,  -652,   880,   873,  -652,   881,  -652,   883,
    -652,  -652,  -652,  -652,   768,   886,   907,  -652,  -652,  -652,
    3775,   888,  -652,  -652,  -652,  -652,  -652,  -652,   437,   894,
    3775,   821,  -652,  -652,  -652,   891,   902,  -652,  -652,  -652,
    -652,  -652
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned short int
  CxxParser::yydefact_[] =
  {
       234,   568,     0,   570,     0,     1,   569,     0,     0,   350,
     354,     0,     0,   166,   378,     0,     0,   390,    10,   308,
     306,   315,   314,   310,   311,   309,   312,   313,   316,   307,
     434,     0,   435,     0,   436,   363,   364,   293,   294,   292,
     283,   295,   291,   289,   290,     0,   284,   296,     0,     0,
       0,    50,     0,     0,     0,     0,     0,    58,   556,    51,
       0,    47,     2,    40,    41,    42,    43,    44,    45,    46,
      39,     3,     4,    13,     0,     0,    15,   265,    22,    25,
     272,    48,    57,    49,     0,    67,    60,    88,     0,   116,
     100,    98,   118,   121,   125,   128,   131,   136,   139,   141,
     143,   145,   147,   149,   151,   168,    53,   263,   275,   268,
     270,   273,   277,    59,     0,   287,     0,   281,   282,   266,
     260,   302,   318,   301,   352,   355,   357,   383,   285,    61,
     361,   385,   388,    52,   317,   439,     0,   300,    19,    20,
       8,   154,   235,     0,     0,    93,     0,    94,    96,    95,
     125,   141,     0,   167,   391,     0,     0,   379,   392,   381,
      90,    89,   330,     0,     0,     0,   320,   322,   319,     0,
       0,    11,    21,   264,   288,   303,    63,   546,     0,   102,
       0,     0,   304,   114,   359,   298,   297,   305,   299,   105,
     492,   493,   494,   495,   496,   497,   498,   499,   500,   501,
     503,   504,   502,     0,     0,   525,   527,   526,   524,   517,
     520,   523,   519,   521,   522,   518,   513,   514,   505,   511,
     508,   509,   507,   512,   516,   515,   506,   510,   491,   490,
     359,   476,   489,     0,    60,    97,     0,   557,    83,     9,
       0,    12,     0,    16,    26,   101,    99,   356,     0,     0,
      14,    23,    24,   353,    56,   117,   166,     0,     0,    78,
      77,    66,     0,     0,     0,     0,     0,   359,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   386,     0,
       0,     0,   155,     0,     0,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,     0,   286,   262,   261,    10,
       0,     0,     0,   273,   276,   269,   267,    10,   274,   271,
       0,    54,   351,    91,   358,   375,     0,   570,     0,   433,
     428,   565,   564,     0,   256,     0,     0,   292,     0,     0,
       0,   349,   237,   238,   245,   241,   250,   249,     0,   247,
     252,   253,   254,   251,   246,     0,     0,   242,   402,   401,
       0,   466,   409,   243,     0,   244,     0,     0,     0,     0,
      62,   393,   377,     0,   380,   326,   323,   332,     0,   565,
       0,     0,   321,     0,   367,     0,     0,    84,   103,     0,
       0,     0,   109,   108,   111,   359,   107,   114,   114,   529,
     528,   359,   477,   478,     0,     0,     0,     7,    17,    18,
       0,     0,     0,     0,     0,    27,    29,    28,    73,     0,
      35,    37,    74,    30,    75,    76,     0,   169,   120,   119,
     123,   124,   122,   359,   384,   126,   127,   129,   130,   132,
     133,   135,   134,   137,   138,   140,   387,   142,   144,   146,
     568,   153,     0,   148,   152,    10,    92,     0,   362,   376,
     389,   437,   568,   473,   474,   475,     0,   470,     0,   468,
       0,   427,   432,     0,     0,   464,   463,   567,     0,   339,
       0,   531,   569,   565,     0,   248,   255,     0,     0,     0,
       0,     0,     0,   214,     0,   479,   413,   403,   404,   259,
     405,   408,   258,     0,   257,     0,   406,   407,     0,   530,
       0,   240,   382,   337,   334,   335,   330,   324,     0,     0,
     558,   171,   175,   178,   180,   182,   184,   186,   188,   190,
     394,     0,   398,   549,   395,     0,   547,   192,   367,   366,
     365,     0,   369,     0,     0,     0,    85,    86,     0,     0,
       0,     0,     0,   110,   360,   104,   106,     0,     0,     6,
       0,    72,    33,    34,     0,     0,     0,    38,     0,    36,
       0,    31,     0,    68,   418,     0,   421,     0,     0,     0,
     440,     0,   472,   431,     0,   471,   429,     0,     0,     0,
     234,     0,   338,   565,   346,   345,     0,   434,   542,     0,
     539,     0,     0,   533,   535,   537,     0,     0,     0,   341,
       0,   462,   568,   349,   347,     0,     0,     0,   480,   348,
     410,   414,   467,   415,   239,     0,   328,   325,   333,     0,
       0,   327,   331,   180,   559,     0,     0,     0,     0,     0,
     399,     0,     0,     0,   155,     0,     0,     0,   397,     0,
     545,     0,   368,     0,   372,     0,     0,   115,     0,   112,
     149,   170,     0,     0,     0,     5,     0,     0,     0,    71,
     566,     0,   416,   568,   565,   424,   423,     0,   150,   560,
     562,     0,   565,   451,     0,     0,     0,   449,   448,     0,
     442,   443,   447,     0,   446,     0,   450,     0,   469,   430,
     236,     0,   570,     0,   550,   543,   532,   565,     0,     0,
     540,   343,   342,     0,   212,   215,     0,   488,   481,     0,
     483,     0,     0,   411,   552,   412,   336,     0,     0,   172,
     174,   173,   176,   177,   179,   400,   181,   183,   185,   193,
       0,     0,   187,   191,   396,   548,   373,     0,     0,     0,
      87,   113,     0,     0,     0,    32,     0,     0,    64,   417,
     422,     0,     0,   426,   561,     0,     0,   452,     0,   455,
     453,     0,   454,     0,   461,     0,   445,     0,   232,   569,
     340,   544,   534,   536,   538,   344,   565,     0,     0,     0,
       0,     0,     0,   568,     0,     0,     0,   166,     0,     0,
       0,     3,   349,   197,   198,   201,   205,   202,   206,   207,
     208,   203,   231,     0,   204,     0,   485,     0,   484,    84,
       0,   553,   329,     0,     0,   374,    82,    79,    81,    80,
      65,    70,     0,   565,     0,   425,   563,     0,   459,   456,
     460,   410,   457,   458,   444,   465,   235,     0,     0,     0,
     227,     0,   228,   568,     0,     0,     0,     0,     0,     0,
       0,     0,   568,     0,   200,   482,     0,   555,     0,   189,
     194,    69,     0,   419,   438,   441,   565,     0,   568,   211,
       0,   220,   226,   230,     0,   222,   229,     0,   551,     0,
     209,   199,   486,   487,     0,     0,     0,   213,   216,   210,
       0,     0,   221,   568,   568,   568,   554,   420,     0,     0,
     166,   217,   219,   223,   233,     0,     0,   568,   224,   568,
     218,   225
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  CxxParser::yypgoto_[] =
  {
      -652,  -644,   587,   -94,  -652,   435,   781,   148,   889,   -56,
      41,    18,   -71,  -200,  -371,  -358,  -377,   382,  -267,  -652,
    -652,   795,  -652,  -652,   870,  -652,  -652,  -652,   118,  -364,
     871,   856,   859,   253,   547,  -652,   295,   665,    67,     3,
     414,   775,   420,  -209,    -2,   651,   669,   668,  -284,  -507,
      14,   418,  -252,    -4,  -560,    76,  -543,     5,   315,   320,
     318,  -652,  -652,  -469,  -652,  -652,  -165,   104,  -652,  -652,
    -652,  -618,  -652,  -652,  -652,  -445,  -652,  -652,  -652,  -652,
      22,   376,  -448,   460,  -317,  -297,  -640,  -318,  -322,   853,
     -39,  -652,   -52,   861,   864,  -652,  -652,   -58,   855,    19,
    -652,  -652,    27,    23,  -652,   896,  -652,  -652,  -652,   800,
     598,  -652,   467,  -652,  -652,  -652,  -652,  -652,  -652,  -525,
    -652,  -652,  -652,  -652,  -384,   -72,   -41,    -3,   842,  -102,
    -652,     0,  -166,   446,  -652,  -652,   -42,    13,  -652,    -6,
    -258,  -652,    57,  -146,  -423,  -652,  -523,  -320,  -313,  -536,
    -324,  -652,  -314,   478,   696,  -652,   316,   228,  -652,  -652,
    -652,  -652,  -652,  -652,  -652,   216,  -652,   306,  -652,   220,
    -652,  -652,  -453,  -286,   522,  -379,  -517,  -652,   757,  -652,
    -652,  -652,  -652,   277,  -652,  -652,  -652,  -311,  -435,  -652,
     308,  -652,  -652,    62,   610,   366,  -652,  -652,  -651,  -652,
    -652,  -652,  -652,  -652,  -652,  -524,   -77,  -652,  -652,     4,
    -652,  -296
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  CxxParser::yydefgoto_[] =
  {
        -1,    71,    72,    73,   240,    74,    75,    76,    77,   406,
      78,    79,    80,   480,   409,   410,   411,   557,    81,    82,
      83,    84,     2,    85,    86,   660,   416,    87,   535,    88,
      89,    90,    91,   183,   383,   384,   378,    92,    93,   150,
      95,    96,    97,    98,   151,   100,   101,   102,   103,   104,
     105,   295,   152,   153,   652,   512,   513,   623,   515,   516,
     517,   518,   519,   520,   730,   731,   705,   793,   794,   795,
     796,   486,   602,   798,   891,   874,   799,   871,   800,   801,
     469,     3,   142,   332,   333,   334,   335,   336,   337,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   297,   155,
     117,   118,   374,   119,   186,   120,   121,   122,   123,   167,
     366,   617,   367,   368,   369,   504,   505,   339,   340,   341,
     342,   343,   344,   345,   346,   124,   125,   146,   127,   544,
     315,   128,   375,   530,   531,   532,   129,   130,   156,   875,
     131,   132,   158,   159,   523,   524,   347,   348,   349,   350,
     487,   606,   488,   665,   613,   565,   566,   666,   463,   134,
     135,   136,   137,   317,   570,   680,   681,   682,   683,   829,
     684,   351,   466,   352,   458,   459,   460,   138,   231,   607,
     608,   708,   709,   710,   711,   139,   232,   353,   354,   592,
     593,   594,   595,   140,   525,   526,   355,   804,   713,   714,
     858,   141,   527,   449,   671,   356,   596,   747,   580,   706,
     143,     6
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int CxxParser::yytable_ninf_ = -566;
  const short int
  CxxParser::yytable_[] =
  {
       106,   126,    99,   176,   400,     4,   173,    94,   157,   361,
     476,   126,    99,   536,   376,   471,   489,    94,   490,   251,
     436,   452,   267,   116,   585,   491,   496,   559,   154,   601,
     552,   475,   651,   247,   253,   679,   497,   499,   591,   465,
     308,   624,   310,   667,   553,   261,   677,   687,   678,   296,
     590,   296,   188,   188,   685,   716,     9,   408,   414,   309,
     472,   133,   791,   811,   174,   189,   802,   394,   175,   435,
     395,   318,   237,   238,   319,   185,   185,   572,   358,   184,
     230,   575,   386,   737,    18,   370,   172,   724,   797,    35,
      36,  -565,   244,   252,   162,   754,   371,   263,   638,   365,
     604,   363,   176,   461,   755,   173,   462,   177,   651,   609,
     506,    18,   106,   126,    99,   522,   163,   482,   264,    94,
     483,   806,   467,   126,   312,   364,   691,   447,   392,    62,
     173,    18,   484,   821,   573,   116,   651,   864,   522,   371,
     679,   242,   248,   163,   621,  -565,   574,   865,   591,    62,
     435,   822,   126,    99,   398,   622,   476,   331,    94,    18,
     590,    53,   338,   163,   365,   424,   729,   175,   733,   154,
     734,   850,    62,   133,    62,   724,    62,   475,   188,   662,
     188,   385,   805,   552,   188,   172,   407,   407,   174,   188,
     663,   163,   175,   399,   812,   688,    62,   553,   465,   878,
     553,   185,   388,   185,   175,   622,   177,   185,   529,   791,
     172,   184,   185,   802,   600,   522,   184,   502,   485,   249,
     841,     1,   243,   250,    62,   177,   483,   391,   667,   679,
     188,   177,   308,   188,     9,   797,   188,   760,   761,    53,
     677,   687,   678,   177,   464,   625,   251,   296,   685,   689,
     581,   309,    62,   185,   467,   650,   185,   230,   407,   185,
     686,   574,   591,   522,   423,     5,   896,   312,   626,   694,
     627,   425,   426,   651,   590,   126,   417,   437,   598,   442,
     559,    94,  -565,   172,     9,   -55,   176,   745,    10,   173,
     172,   540,   508,   715,    14,   465,  -370,   540,   553,   579,
    -370,   616,     9,   178,   177,  -541,  -541,   398,   248,   444,
     312,   177,   243,   250,   835,   448,   284,   242,   173,   244,
     252,   836,  -541,   175,   485,   522,   483,   180,    49,   805,
     450,   650,   420,   421,   422,    18,    52,    53,   495,   247,
     253,   172,   326,   233,   859,   860,   399,   174,   251,   470,
      62,   175,   331,   358,   358,   496,   490,   338,   312,   650,
     126,    99,   177,   491,   248,   497,    94,   163,   331,   172,
     126,   528,   725,   338,   188,   538,    94,   154,   514,   887,
     175,   276,   385,   522,   236,   249,   553,   277,   391,   888,
     177,   537,   521,   126,   640,   655,   769,   185,   172,    94,
      62,   514,   628,   670,   877,    53,   879,   407,   629,    18,
     696,   641,   641,   272,   273,   521,   268,   269,    62,   177,
     423,   244,   252,   399,   485,   422,   892,   697,     9,   619,
     270,   271,    10,   177,   540,   173,   274,   382,   275,   522,
     379,   479,   387,   172,   567,   536,   239,   540,   540,   243,
     250,   643,   283,   241,   686,    14,   571,   904,   262,     9,
     476,    53,   540,    10,   177,   254,   164,   690,   164,   284,
     126,   278,   830,   280,    62,   832,    94,   830,   514,    18,
     171,   489,  -371,   465,    35,    36,  -371,   164,   164,   644,
     582,   279,   521,   174,   584,   281,   650,   175,   603,   -86,
     247,   253,   399,     9,   265,   266,     9,   603,   316,   610,
      18,   163,   611,   359,   331,   172,   396,   397,   126,   338,
     172,   476,   321,   872,    94,   528,   514,   360,   243,   250,
     492,   493,   773,   362,   482,   848,   177,   483,   748,   363,
     521,   177,   163,   301,    62,   162,   301,   176,   757,   758,
     173,   243,   250,   500,   501,   373,   661,   256,   377,   126,
      99,    14,   389,   540,   257,    94,   562,   563,   390,   188,
     440,   164,   258,  -280,   259,    62,   154,   260,  -278,   171,
     126,   611,   668,   752,   753,   675,    94,   751,   514,   826,
     676,   299,   185,   765,   766,   756,   172,   451,   171,   172,
     331,    70,   521,   407,   171,   338,    30,    31,   174,    32,
      33,    34,   175,   164,   481,   164,   171,   177,   844,   380,
     177,   762,   763,   300,   164,   820,   363,   126,   853,   854,
     172,   807,   170,    94,   494,   485,   726,   498,   126,   412,
     415,   738,   739,    53,    94,    62,   514,   509,   906,   742,
     743,   177,   533,   576,   746,   534,    62,   126,    99,   539,
     521,   547,   740,    94,   857,   380,   551,   567,   164,   548,
     248,   164,   145,   147,   154,   -87,   148,   149,   869,   568,
     160,   161,   545,   546,   427,   428,   564,   880,   248,  -279,
     675,   569,   403,   403,   126,   676,   433,   434,   188,   837,
      94,   578,   514,   889,   722,   723,   583,   467,    18,   453,
     454,   455,   599,   605,   179,    18,   521,   615,   177,   620,
     792,   185,   630,   631,   632,   803,   633,   639,   901,   902,
     903,   170,   477,    18,   478,   171,   176,   645,   301,   173,
     163,   646,   910,   456,   911,   647,   862,   479,   648,   649,
     170,   255,   478,   164,   653,   188,   170,   654,   658,   664,
     164,   672,   690,   171,   301,   479,   611,    53,   170,   695,
     698,   699,   828,    62,   700,   831,   701,   828,   185,   675,
      62,   702,   703,   704,   676,    53,   712,   483,   717,   886,
     621,   313,   171,   718,   741,   770,   764,   174,    62,   749,
     173,   175,   767,   768,   775,   776,   177,   126,    99,   380,
     809,   313,   165,    94,   165,   810,  -195,   792,   813,   172,
     541,   814,   803,   537,   154,   815,   541,   816,   817,   170,
     818,   819,   824,   165,   165,   823,   170,   171,   556,   827,
     177,   840,   842,   843,   126,    99,   126,    99,   126,    99,
      94,   845,    94,   847,    94,   849,   851,   852,   174,   792,
     484,   154,   175,   154,   803,   154,   855,   792,   126,    99,
     861,   863,   803,   482,    94,    18,   453,   454,   455,   867,
     172,   866,   581,   870,   868,   154,   899,   170,   873,   302,
     876,   164,   302,   882,   883,   164,   884,  -196,   164,   885,
     890,   177,   893,   894,   363,   895,   897,   163,   898,   171,
     456,   311,   164,   301,   171,   170,   905,   165,   900,   307,
     166,   908,   168,   907,   909,   234,   235,   856,   418,   419,
     245,   438,   543,   246,    30,    31,   637,    32,    33,    34,
      62,   182,   182,   554,   170,   165,   165,   727,   187,   187,
     439,   300,   443,   728,   732,   503,   692,   881,   170,   165,
     614,   165,   305,   541,   306,   381,   372,   507,   314,   303,
     165,    53,   304,   618,   642,   446,   612,   554,   441,   750,
     825,   834,   759,   833,    62,   577,   808,   393,    18,   170,
     171,   556,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,   298,   164,   772,   550,   735,     0,   164,
       0,   381,     0,     0,   165,     0,   164,   165,     0,     0,
     656,     0,     0,   164,   171,   320,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,     0,   404,   404,
     164,     0,     0,     0,     0,     0,     0,   429,   430,   431,
     432,     0,     0,    62,   744,     0,     0,     0,     0,     0,
       0,   170,     0,     0,     0,     0,   170,   182,     0,   182,
       0,     0,     0,   182,   187,     0,   187,     0,   182,     0,
     187,     0,   302,   302,   302,   187,     0,    62,   313,     0,
       0,   171,     0,     0,     0,     0,     0,     0,    18,   165,
       0,     0,     0,     0,     0,     0,   165,     0,     0,   301,
     302,     0,     0,    30,    31,     0,    32,    33,    34,   182,
       0,     0,   182,     0,     0,   182,   187,     0,     0,   187,
     300,     0,   187,   164,     0,     0,     0,     0,     0,     0,
       0,     0,   170,     0,   164,   170,   405,   405,   511,     0,
      53,     0,     0,   413,   413,   381,     0,     0,     0,     0,
       0,   381,   381,    62,     0,     0,   542,     0,     0,     0,
     401,   511,   542,    18,     0,     0,   170,     0,     0,     0,
       0,     0,     0,     0,   404,   404,     0,     0,    30,    31,
     164,    32,    33,    34,     0,     0,     0,     0,     0,     0,
       0,   298,     0,     0,     0,   181,     0,   457,     0,     0,
       0,     0,   164,   171,   468,    18,     0,     0,   405,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
       0,     0,     0,     0,     0,     0,   445,   165,    62,     0,
       0,   165,     0,   170,   165,     0,     0,   402,   511,     0,
       0,    30,    31,     0,    32,    33,    34,     0,   165,   302,
       0,     0,     0,   182,     0,     0,     0,    53,   300,     0,
     187,     0,     0,     0,   171,     0,     0,     0,     0,     0,
      62,     0,   771,     0,     0,   511,   774,     0,    53,     0,
       0,     0,     0,     0,     0,     0,   511,   413,   413,   413,
     413,    62,     0,     0,     0,   561,     0,     0,     0,   542,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,     0,   542,   542,     0,     0,     0,     0,     0,     0,
       0,   170,     0,     0,     0,     0,     0,   657,   371,     0,
       0,     0,     0,     0,     0,   457,     0,     0,     0,   457,
     165,     0,   457,     0,     0,   165,     0,     0,   511,     0,
     282,     0,   165,     0,     0,   170,   597,   405,   283,   165,
     560,    62,   846,     0,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,   284,   165,     0,     0,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,     0,
     719,   720,   721,   511,   511,   511,   511,   511,   511,     0,
     511,   511,   511,     0,   511,     0,   511,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   170,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,   657,     0,
       0,     9,     0,     0,     0,    10,     0,     0,   561,     0,
     413,   413,   413,  -370,   413,   302,     0,  -370,   182,     0,
       0,     0,     0,   457,     0,   187,     0,     0,     0,     0,
     693,     0,   511,     0,     0,     0,     0,   168,     0,   165,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   554,
     165,     0,    18,   511,   707,     0,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     0,
      32,    33,    34,    35,    36,     0,     0,     0,   401,     0,
       0,     0,     0,     0,   181,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    18,     0,   165,     0,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,     0,
       0,     0,   413,   413,   413,     0,     0,    62,   165,     0,
       0,     0,     0,   405,     0,     0,   555,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,     0,     0,
       0,     0,     0,     0,     0,     0,    53,   182,   511,   511,
       0,     0,     0,     0,   187,   558,     0,     0,   707,    62,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   322,
       0,     7,     8,     9,     0,    53,     0,    10,     0,    11,
      12,     0,     0,     0,   634,    13,     0,   483,    62,    14,
       0,     0,   635,     0,     0,     0,     0,     0,   324,     0,
     413,   561,    15,     0,   182,    16,     0,     0,     0,   636,
       0,   187,     0,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,     0,    18,     0,   838,     0,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,   777,    32,    33,    34,    35,    36,    37,    38,     0,
      39,    40,    41,    42,    43,    44,   778,    46,   329,    47,
     330,   779,   780,     0,    48,   781,   782,    49,   783,    50,
       0,    51,   784,   785,   786,    52,    53,    54,   787,    55,
      56,   788,    57,    58,    59,   789,    60,   790,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,   322,     0,
       7,     8,     9,     0,     0,     0,    10,     0,    11,    12,
       0,     0,     0,   323,    13,     0,     0,     0,    14,     0,
       0,     0,     0,     0,     0,     0,     0,   673,     0,     0,
       0,    15,     0,     0,    16,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    18,   453,   454,   455,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
       0,    32,    33,    34,    35,    36,    37,    38,   326,    39,
      40,    41,    42,    43,    44,   589,    46,   674,    47,     0,
       0,     0,     0,    48,     0,     0,    49,     0,    50,     0,
      51,     0,     0,     0,    52,    53,    54,     0,    55,    56,
       0,    57,    58,    59,     0,    60,     0,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,   322,     0,     7,
       8,     9,     0,     0,     0,    10,     0,    11,    12,     0,
       0,     0,   323,    13,     0,     0,     0,    14,     0,     0,
       0,     0,     0,     0,     0,     0,   324,     0,     0,     0,
      15,     0,     0,    16,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    18,     0,     0,     0,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,   325,
      32,    33,    34,    35,    36,    37,    38,   326,   327,    40,
      41,    42,    43,    44,   328,    46,   329,    47,   330,     0,
       0,     0,    48,     0,     0,    49,     0,    50,     0,    51,
       0,     0,     0,    52,    53,    54,     0,    55,    56,     0,
      57,    58,    59,     0,    60,     0,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,   659,     0,     7,     8,
       9,     0,     0,     0,    10,     0,    11,    12,     0,     0,
       0,     0,    13,     0,     0,     0,    14,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,     0,    15,
       0,     0,    16,     0,    35,    36,    37,    38,     0,    39,
      40,    41,    42,    43,    44,     0,    46,     0,    47,     0,
      17,    18,     0,     0,     0,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,     0,    32,
      33,    34,    35,    36,    37,    38,     0,    39,    40,    41,
      42,    43,    44,    45,    46,     0,    47,     0,     0,     0,
       0,    48,     0,     0,    49,     0,    50,     0,    51,     0,
       0,     0,    52,    53,    54,     0,    55,    56,     0,    57,
      58,    59,     0,    60,     0,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,   322,     0,     7,     8,     9,
       0,     0,     0,    10,     0,    11,    12,     0,     0,     0,
       0,    13,     0,   440,     0,    14,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    15,     0,
       0,    16,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      18,     0,     0,     0,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,     0,    32,    33,
      34,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   144,     0,     0,     0,     0,     0,     0,     0,
      48,     0,     0,    49,     0,    50,     0,    51,     0,     0,
       0,    52,    53,    54,     0,    55,    56,     0,    57,    58,
      59,     0,    60,     0,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,     7,     8,     9,     0,     0,     0,
      10,     0,    11,    12,     0,     0,     0,   323,    13,     0,
       0,     0,    14,     0,     0,     0,     0,     0,     0,     0,
       0,   324,     0,     0,     0,    15,     0,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    18,     0,     0,
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,   325,    32,    33,    34,    35,    36,
      37,    38,   326,   327,    40,    41,    42,    43,    44,   328,
      46,   329,    47,   330,     0,     0,     0,    48,     0,     0,
      49,     0,    50,     0,    51,     0,     0,     0,    52,    53,
      54,     0,    55,    56,     0,    57,    58,    59,     0,    60,
       0,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,     7,     8,     9,     0,     0,     0,    10,     0,    11,
      12,     0,     0,     0,   323,    13,     0,     0,     0,    14,
       0,     0,     0,     0,     0,     0,     0,     0,   324,     0,
       0,     0,    15,     0,     0,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    18,     0,     0,     0,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,     0,    32,    33,    34,    35,    36,    37,    38,     0,
      39,    40,    41,    42,    43,    44,    45,    46,     0,    47,
       0,     0,     0,     0,    48,     0,     0,    49,     0,    50,
       0,    51,     0,     0,     0,    52,    53,    54,     0,    55,
      56,     0,    57,    58,    59,     0,    60,     0,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,     7,     8,
       9,     0,     0,     0,    10,     0,    11,    12,     0,     0,
       0,   323,    13,     0,     0,     0,    14,     0,     0,     0,
       0,     0,     0,     0,     0,   673,     0,     0,     0,    15,
       0,     0,    16,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    18,     0,     0,     0,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,     0,    32,
      33,    34,    35,    36,    37,    38,     0,    39,    40,    41,
      42,    43,    44,    45,    46,     0,    47,     0,     0,     0,
       0,    48,     0,     0,    49,     0,    50,     0,    51,     0,
       0,     0,    52,    53,    54,     0,    55,    56,     0,    57,
      58,    59,     0,    60,     0,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,     7,     8,     9,     0,     0,
       0,    10,     0,    11,    12,     0,     0,     0,     0,    13,
       0,     0,     0,    14,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    15,     0,     0,    16,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    17,    18,     0,
       0,     0,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,     0,    32,    33,    34,    35,
      36,    37,    38,     0,    39,    40,    41,    42,    43,    44,
      45,    46,     0,    47,     0,     0,     0,     0,    48,     0,
       0,    49,     0,    50,     0,    51,     0,     0,     0,    52,
      53,    54,     0,    55,    56,     0,    57,    58,    59,     0,
      60,     0,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,     7,     8,     9,     0,     0,     0,    10,     0,
      11,    12,     0,   549,     0,     0,    13,     0,     0,     0,
      14,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    15,     0,     0,    16,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    18,     0,     0,     0,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,     0,    32,    33,    34,    35,    36,    37,    38,
       0,    39,    40,    41,    42,    43,    44,    45,    46,     0,
      47,     0,     0,     0,     0,    48,     0,     0,    49,     0,
      50,     0,    51,     0,     0,     0,    52,    53,    54,     0,
      55,    56,     0,    57,   510,    59,     0,    60,     0,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,     7,
       8,     9,     0,     0,     0,    10,     0,    11,    12,     0,
     586,     0,     0,    13,     0,     0,     0,    14,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      15,     0,     0,    16,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    18,     0,     0,     0,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,   587,    31,     0,
      32,   588,    34,    35,    36,    37,    38,     0,    39,    40,
      41,    42,    43,    44,   589,    46,     0,    47,     0,     0,
       0,     0,    48,     0,     0,    49,     0,    50,     0,    51,
       0,     0,     0,    52,    53,    54,     0,    55,    56,     0,
      57,   510,    59,     0,    60,     0,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,     7,     8,     9,     0,
       0,     0,    10,     0,    11,    12,     0,     0,     0,     0,
      13,     0,     0,     0,    14,     0,     0,     0,     0,     0,
       0,     0,     0,   324,     0,     0,     0,    15,     0,     0,
      16,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    18,
       0,     0,     0,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,     0,    32,    33,    34,
      35,    36,    37,    38,     0,    39,    40,    41,    42,    43,
      44,    45,    46,     0,    47,     0,     0,     0,     0,    48,
       0,     0,    49,     0,    50,     0,    51,     0,     0,     0,
      52,    53,    54,     0,    55,    56,     0,    57,    58,    59,
       0,    60,     0,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,     7,     8,     9,     0,     0,     0,    10,
       0,    11,    12,     0,     0,     0,     0,    13,     0,     0,
       0,    14,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    15,     0,     0,    16,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    18,     0,     0,     0,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,     0,    32,    33,    34,    35,    36,    37,
      38,     0,    39,    40,    41,    42,    43,    44,    45,    46,
       0,    47,     0,     0,     0,     0,    48,     0,     0,    49,
       0,    50,     0,    51,     0,     0,     0,    52,    53,    54,
       0,    55,    56,     0,    57,   510,    59,     0,    60,     0,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
       7,     8,     9,     0,     0,     0,    10,     0,    11,    12,
       0,     0,     0,     0,    13,     0,     0,     0,    14,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    15,     0,     0,    16,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    18,     0,     0,     0,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,   587,    31,
       0,    32,   588,    34,    35,    36,    37,    38,     0,    39,
      40,    41,    42,    43,    44,   589,    46,     0,    47,     0,
       0,     0,     0,    48,     0,     0,    49,     0,    50,     0,
      51,     0,     0,     0,    52,    53,    54,     0,    55,    56,
       0,    57,   510,    59,     0,    60,     0,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,     7,     8,     9,
       0,     0,     0,    10,     0,    11,    12,     0,     0,     0,
       0,    13,     0,     0,     0,    14,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    15,     0,
       0,    16,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      18,     0,     0,     0,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,     0,    32,    33,
      34,    35,    36,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   144,     0,     0,     0,     0,     0,     0,     0,
      48,     0,     0,    49,     0,    50,     0,    51,     0,     0,
       0,    52,    53,    54,     0,    55,    56,     0,    57,     0,
      59,     0,    60,     0,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,     7,     8,     9,     0,     0,     0,
      10,     0,    11,    12,     0,     0,     0,     0,    13,     0,
     440,     0,    14,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    15,     0,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    18,     0,     0,
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,     0,    32,    33,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   144,
       0,     0,     0,     0,     0,     0,     0,    48,     0,     0,
      49,     0,    50,     0,    51,     0,     0,     0,    52,    53,
      54,     0,    55,    56,     0,    57,    58,    59,     0,    60,
       0,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,     7,     8,     9,     0,     0,     0,    10,     0,    11,
      12,     0,     0,     0,   323,    13,     0,     0,     0,    14,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    15,     0,     0,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    18,     0,     0,     0,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,     0,    32,    33,    34,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   144,     0,     0,     0,
       0,     0,     0,     0,    48,     0,     0,    49,     0,    50,
       0,    51,     0,     0,     0,    52,    53,    54,     0,    55,
      56,     0,    57,    58,    59,     0,    60,     0,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,     7,     8,
       9,     0,     0,     0,    10,     0,    11,    12,     0,     0,
       0,     0,    13,     0,     0,     0,    14,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    15,
       0,     0,    16,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    18,     0,     0,     0,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,     0,    32,
      33,    34,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   144,     0,     0,     0,     0,     0,     0,
       0,    48,     0,     0,    49,     0,    50,     0,    51,     0,
       0,     0,    52,    53,    54,     0,    55,    56,     0,    57,
      58,    59,     0,    60,     0,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,     7,     8,     9,     0,     0,
       0,    10,     0,    11,    12,     0,     0,     0,     0,    13,
       0,     0,     0,    14,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    15,     0,     0,    16,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    18,     0,
       0,     0,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,     0,    32,    33,    34,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     144,     0,     0,     0,     0,     0,     0,     0,    48,     0,
       0,    49,     0,    50,     0,    51,     0,     0,     0,    52,
      53,    54,     0,    55,    56,     0,    57,   510,    59,     0,
      60,     0,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,     7,     8,     9,     0,     0,     0,    10,     0,
      11,    12,     0,     0,     0,     0,    13,   736,     0,     0,
      14,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    15,     0,     0,    16,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    18,     0,     0,     0,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,     0,    32,    33,    34,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   144,     0,     0,
       0,     0,     0,     0,     0,    48,     0,     0,    49,     0,
      50,     0,    51,     0,     0,     0,    52,    53,    54,     0,
      55,    56,     0,    57,     0,    59,     0,    60,     0,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,     7,
       8,     9,     0,     0,     0,    10,     0,    11,    12,     0,
       0,     0,     0,    13,     0,     0,     0,    14,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      15,     0,     0,    16,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    18,     0,     0,     0,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     0,
      32,    33,    34,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   144,     0,     0,     0,     0,     0,
       0,     0,    48,     0,     0,    49,     0,    50,     0,    51,
       0,     0,     0,    52,    53,    54,     0,    55,    56,     0,
      57,     0,    59,     0,    60,     0,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,     0,
     203,     0,     0,     0,   204,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,     0,     0,    18,
       0,     0,     0,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,     0,    32,    33,    34,
      35,    36,    11,    12,     0,     0,     0,     0,     0,     0,
       0,   181,    14,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   228,     0,     0,     0,     0,     0,     0,     0,
     229,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    62,     0,     0,    18,     0,     0,
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,     0,    32,    33,    34,     0,     0,
       9,     0,     0,     0,    10,     0,     0,     0,     0,   144,
       0,     0,   379,     0,     0,     0,     0,    48,     0,     0,
      49,     0,    50,     0,    51,     0,     0,     0,    52,    53,
      54,     0,    55,    56,     9,    57,     0,    59,    10,    60,
       0,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    18,     0,     0,     0,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,     0,    32,
      33,    34,    35,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   181,     0,    18,     0,     0,     0,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,     0,    32,    33,    34,    35,    36,     0,     0,
     473,     0,     0,     0,     0,     0,    62,   181,    14,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      62,     0,     0,    18,     0,     0,     0,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
     325,    32,    33,    34,    35,    36,    37,    38,     0,   327,
      40,    41,    42,    43,    44,   474,    46,   329,    47,   330,
     583,     0,     0,     0,     0,     0,     0,     0,    14,     0,
       0,     0,     0,     0,     0,    53,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    62,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    18,     0,     0,     0,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
       0,    32,    33,    34,    35,    36,    37,    38,     0,    39,
      40,    41,    42,    43,    44,   169,    46,    14,    47,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    53,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    62,     0,
       0,     0,    18,     0,     0,     0,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,   777,
      32,    33,    34,    35,    36,    37,    38,     0,    39,    40,
      41,    42,    43,    44,   839,    46,   329,    47,   330,    14,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    53,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    62,     0,     0,
       0,     0,     0,     0,    18,     0,     0,     0,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,     0,    32,    33,    34,    35,    36,    37,    38,     0,
      39,    40,    41,    42,    43,    44,   169,    46,    14,    47,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    53,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    14,     0,    62,
       0,     0,     0,    18,     0,     0,     0,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
       0,    32,    33,    34,    35,    36,     0,     0,     0,     0,
       0,     0,    18,   669,     0,   181,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     0,
      32,    33,    34,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   357,     0,     0,    18,    62,     0,
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    53,    32,    33,    34,    35,    36,
       0,     0,     0,     0,     0,     0,     0,    62,     0,   181,
       0,     0,     0,     0,     0,     0,     0,    18,     0,     0,
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,   325,    32,    33,    34,    35,    36,
      37,    38,    62,   327,    40,    41,    42,    43,    44,   474,
      46,   329,    47,   330,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    53,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    18,
       0,     0,    62,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,   777,    32,    33,    34,
      35,    36,    37,    38,     0,    39,    40,    41,    42,    43,
      44,   839,    46,   329,    47,   330,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    53,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    18,     0,     0,    62,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,     0,    32,
      33,    34,    35,    36,    37,    38,     0,    39,    40,    41,
      42,    43,    44,   169,    46,     0,    47,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    53,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    18,     0,     0,    62,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
       0,    32,    33,    34,    35,    36,     0,     0,     0,     0,
       0,     0,    18,     0,     0,   181,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     0,
      32,    33,    34,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   357,     0,     0,     0,    62,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    53,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    62
  };

  /* YYCHECK.  */
  const short int
  CxxParser::yycheck_[] =
  {
         4,     4,     4,    45,   256,     1,    45,     4,    14,   155,
     328,    14,    14,   377,   180,   326,   338,    14,   338,    75,
     278,   317,    94,     4,   472,   338,   350,   404,    14,   482,
     401,   328,   539,    74,    75,   571,   350,   354,   473,   323,
     111,   510,   114,   567,   402,    87,   571,   571,   571,   107,
     473,   109,    52,    53,   571,   615,     5,   257,   258,   111,
     327,     4,   706,   714,    45,    52,   706,   233,    45,   278,
     236,    16,    58,    60,    19,    52,    53,   456,   150,    52,
      53,   460,   184,   643,    56,   162,    45,   630,   706,    77,
      78,     1,    74,    75,    19,    22,    88,    33,   521,    20,
     484,    31,   144,    16,    31,   144,    19,    45,   615,   493,
      31,    56,   116,   116,   116,   373,    88,    16,    54,   116,
      19,    31,    19,   126,   124,    55,   579,   115,   230,   121,
     169,    56,    31,     1,    19,   116,   643,    20,   396,    88,
     676,    88,    11,    88,    20,     1,    31,    30,   583,   121,
     359,    19,   155,   155,   248,    31,   474,   143,   155,    56,
     583,   108,   143,    88,    20,   267,   635,   144,   637,   155,
     639,   789,   121,   116,   121,   718,   121,   474,   178,    20,
     180,   184,   706,   554,   184,   144,   257,   258,   169,   189,
      31,    88,   169,   249,    20,   574,   121,   555,   482,   850,
     558,   178,   189,   180,   181,    31,   144,   184,   374,   853,
     169,   184,   189,   853,   481,   473,   189,   363,   117,    88,
     780,    29,    74,    75,   121,   163,    19,   230,   752,   765,
     230,   169,   303,   233,     5,   853,   236,    30,    31,   108,
     765,   765,   765,   181,   321,    13,   302,   305,   765,    19,
      15,   303,   121,   230,    19,   539,   233,   230,   329,   236,
     571,    31,   697,   521,   267,     0,   884,   267,    36,   586,
      38,   268,   269,   780,   697,   278,   262,   279,   478,   283,
     657,   278,     1,   242,     5,     0,   328,   658,     9,   328,
     249,   385,   369,   607,    21,   579,    17,   391,   656,    23,
      21,    20,     5,    13,   242,    14,    15,   401,    11,   295,
     310,   249,   164,   165,   767,   315,    40,    88,   357,   301,
     302,   769,    31,   300,   117,   583,    19,    13,    99,   853,
     316,   615,   265,   266,   267,    56,   107,   108,    31,   380,
     381,   300,    81,    13,   813,   814,   402,   328,   404,    88,
     121,   328,   338,   425,   426,   679,   676,   338,   358,   643,
     363,   363,   300,   676,    11,   679,   363,    88,   354,   328,
     373,   374,   630,   354,   374,   379,   373,   363,   373,    20,
     357,    35,   385,   641,    13,    88,   744,    41,   391,    30,
     328,   377,   373,   396,    14,    14,   692,   374,   357,   396,
     121,   396,    35,   569,   849,   108,   851,   478,    41,    56,
      14,    31,    31,    13,    14,   396,     3,     4,   121,   357,
     423,   403,   404,   479,   117,   358,   871,    31,     5,   506,
      42,    43,     9,   371,   528,   474,    36,   184,    38,   697,
      17,    88,   189,   402,   440,   809,    13,   541,   542,   301,
     302,    17,    23,    56,   765,    21,   452,    20,    31,     5,
     778,   108,   556,     9,   402,    29,    31,    30,    33,    40,
     473,     9,   758,    10,   121,   761,   473,   763,   473,    56,
      45,   803,    17,   767,    77,    78,    21,    52,    53,   531,
     468,     8,   473,   474,   472,    39,   780,   474,   484,    31,
     541,   542,   558,     5,     6,     7,     5,   493,    15,   495,
      56,    88,   498,     9,   500,   474,     3,     4,   521,   500,
     479,   839,   132,   845,   521,   528,   521,    18,   380,   381,
      30,    31,   698,    22,    16,   787,   474,    19,    30,    31,
     521,   479,    88,   108,   121,    19,   111,   589,    30,    31,
     589,   403,   404,     3,     4,    13,   562,    17,    21,   562,
     562,    21,    18,   657,    24,   562,     3,     4,    22,   569,
      19,   136,    32,     5,    34,   121,   562,    37,     5,   144,
     583,   567,   568,     3,     4,   571,   583,   664,   583,   755,
     571,    56,   569,     3,     4,   672,   555,    20,   163,   558,
     586,   129,   583,   674,   169,   586,    71,    72,   589,    74,
      75,    76,   589,   178,    21,   180,   181,   555,   783,   184,
     558,    30,    31,    88,   189,    30,    31,   630,     3,     4,
     589,   708,    45,   630,    30,   117,   631,    15,   641,   257,
     258,   645,   646,   108,   641,   121,   641,     1,   900,   653,
     654,   589,    14,     1,   660,    14,   121,   660,   660,    17,
     641,    14,   648,   660,   810,   230,    18,   663,   233,    14,
      11,   236,     7,     8,   660,    31,    11,    12,   843,    16,
      15,    16,   387,   388,   270,   271,    20,   852,    11,     5,
     676,    21,   257,   258,   697,   676,   276,   277,   698,   776,
     697,     1,   697,   868,   628,   629,    13,    19,    56,    57,
      58,    59,    30,    16,    49,    56,   697,    15,   656,     1,
     706,   698,     9,     8,    10,   706,    39,    15,   893,   894,
     895,   144,    73,    56,    75,   300,   778,    21,   303,   778,
      88,    21,   907,    91,   909,    22,   823,    88,    31,    18,
     163,    86,    75,   318,    21,   755,   169,    21,    11,   132,
     325,   132,    30,   328,   329,    88,   752,   108,   181,    71,
      15,    15,   758,   121,     1,   761,    30,   763,   755,   765,
     121,    30,    22,    20,   765,   108,    95,    19,     1,   866,
      20,   126,   357,     9,    18,    30,    16,   778,   121,    20,
     839,   778,    16,    20,    30,   132,   744,   810,   810,   374,
      21,   146,    31,   810,    33,    21,    31,   803,    16,   778,
     385,    31,   803,   809,   810,    18,   391,    22,    22,   242,
      22,    22,     1,    52,    53,   132,   249,   402,   403,     1,
     778,    30,    30,    16,   847,   847,   849,   849,   851,   851,
     847,    21,   849,    21,   851,    21,    21,    16,   839,   845,
      31,   847,   839,   849,   845,   851,     1,   853,   871,   871,
       1,    20,   853,    16,   871,    56,    57,    58,    59,     1,
     839,   132,    15,   119,    16,   871,   890,   300,    30,   108,
      30,   456,   111,    31,    22,   460,    22,    31,   463,     1,
      21,   839,    22,    22,    31,    22,    20,    88,     1,   474,
      91,   116,   477,   478,   479,   328,    22,   136,    30,    56,
      31,    30,    33,   102,    22,    55,    55,   809,   263,   264,
      74,   280,   385,    74,    71,    72,   518,    74,    75,    76,
     121,    52,    53,    11,   357,   164,   165,   632,    52,    53,
     281,    88,   284,   633,   636,   368,   580,   853,   371,   178,
     500,   180,   109,   528,   109,   184,   166,   369,   126,   108,
     189,   108,   108,   506,   528,   310,   498,    11,   282,   663,
     752,   765,   676,   763,   121,   463,   709,   230,    56,   402,
     555,   556,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,   107,   569,   697,   396,   641,    -1,   574,
      -1,   230,    -1,    -1,   233,    -1,   581,   236,    -1,    -1,
      88,    -1,    -1,   588,   589,   136,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    -1,   257,   258,
     605,    -1,    -1,    -1,    -1,    -1,    -1,   272,   273,   274,
     275,    -1,    -1,   121,    88,    -1,    -1,    -1,    -1,    -1,
      -1,   474,    -1,    -1,    -1,    -1,   479,   178,    -1,   180,
      -1,    -1,    -1,   184,   178,    -1,   180,    -1,   189,    -1,
     184,    -1,   301,   302,   303,   189,    -1,   121,   423,    -1,
      -1,   656,    -1,    -1,    -1,    -1,    -1,    -1,    56,   318,
      -1,    -1,    -1,    -1,    -1,    -1,   325,    -1,    -1,   674,
     329,    -1,    -1,    71,    72,    -1,    74,    75,    76,   230,
      -1,    -1,   233,    -1,    -1,   236,   230,    -1,    -1,   233,
      88,    -1,   236,   698,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   555,    -1,   709,   558,   257,   258,   373,    -1,
     108,    -1,    -1,   257,   258,   374,    -1,    -1,    -1,    -1,
      -1,   380,   381,   121,    -1,    -1,   385,    -1,    -1,    -1,
      11,   396,   391,    56,    -1,    -1,   589,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   403,   404,    -1,    -1,    71,    72,
     755,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   305,    -1,    -1,    -1,    88,    -1,   318,    -1,    -1,
      -1,    -1,   777,   778,   325,    56,    -1,    -1,   329,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    56,   456,   121,    -1,
      -1,   460,    -1,   656,   463,    -1,    -1,    88,   473,    -1,
      -1,    71,    72,    -1,    74,    75,    76,    -1,   477,   478,
      -1,    -1,    -1,   374,    -1,    -1,    -1,   108,    88,    -1,
     374,    -1,    -1,    -1,   839,    -1,    -1,    -1,    -1,    -1,
     121,    -1,   695,    -1,    -1,   510,   699,    -1,   108,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   521,   401,   402,   403,
     404,   121,    -1,    -1,    -1,   409,    -1,    -1,    -1,   528,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,   541,   542,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   744,    -1,    -1,    -1,    -1,    -1,   556,    88,    -1,
      -1,    -1,    -1,    -1,    -1,   456,    -1,    -1,    -1,   460,
     569,    -1,   463,    -1,    -1,   574,    -1,    -1,   583,    -1,
      15,    -1,   581,    -1,    -1,   778,   477,   478,    23,   588,
      56,   121,   785,    -1,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    40,   605,    -1,    -1,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    -1,
     625,   626,   627,   628,   629,   630,   631,   632,   633,    -1,
     635,   636,   637,    -1,   639,    -1,   641,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   839,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,   657,    -1,
      -1,     5,    -1,    -1,    -1,     9,    -1,    -1,   552,    -1,
     554,   555,   556,    17,   558,   674,    -1,    21,   569,    -1,
      -1,    -1,    -1,   574,    -1,   569,    -1,    -1,    -1,    -1,
     581,    -1,   697,    -1,    -1,    -1,    -1,   588,    -1,   698,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    11,
     709,    -1,    56,   718,   605,    -1,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    -1,
      74,    75,    76,    77,    78,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,   755,    -1,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    -1,
      -1,    -1,   656,   657,   658,    -1,    -1,   121,   777,    -1,
      -1,    -1,    -1,   674,    -1,    -1,    88,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,   698,   813,   814,
      -1,    -1,    -1,    -1,   698,    88,    -1,    -1,   709,   121,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,     3,     4,     5,    -1,   108,    -1,     9,    -1,    11,
      12,    -1,    -1,    -1,    15,    17,    -1,    19,   121,    21,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    30,    -1,
     744,   745,    34,    -1,   755,    37,    -1,    -1,    -1,    40,
      -1,   755,    -1,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    -1,    56,    -1,   777,    -1,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    -1,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    -1,    96,    97,    98,    99,   100,   101,
      -1,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,     1,    -1,
       3,     4,     5,    -1,    -1,    -1,     9,    -1,    11,    12,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,
      -1,    34,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    -1,
      -1,    -1,    -1,    96,    -1,    -1,    99,    -1,   101,    -1,
     103,    -1,    -1,    -1,   107,   108,   109,    -1,   111,   112,
      -1,   114,   115,   116,    -1,   118,    -1,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,     1,    -1,     3,
       4,     5,    -1,    -1,    -1,     9,    -1,    11,    12,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      34,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      -1,    -1,    96,    -1,    -1,    99,    -1,   101,    -1,   103,
      -1,    -1,    -1,   107,   108,   109,    -1,   111,   112,    -1,
     114,   115,   116,    -1,   118,    -1,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,     1,    -1,     3,     4,
       5,    -1,    -1,    -1,     9,    -1,    11,    12,    -1,    -1,
      -1,    -1,    17,    -1,    -1,    -1,    21,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    -1,    34,
      -1,    -1,    37,    -1,    77,    78,    79,    80,    -1,    82,
      83,    84,    85,    86,    87,    -1,    89,    -1,    91,    -1,
      55,    56,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    74,
      75,    76,    77,    78,    79,    80,    -1,    82,    83,    84,
      85,    86,    87,    88,    89,    -1,    91,    -1,    -1,    -1,
      -1,    96,    -1,    -1,    99,    -1,   101,    -1,   103,    -1,
      -1,    -1,   107,   108,   109,    -1,   111,   112,    -1,   114,
     115,   116,    -1,   118,    -1,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,     1,    -1,     3,     4,     5,
      -1,    -1,    -1,     9,    -1,    11,    12,    -1,    -1,    -1,
      -1,    17,    -1,    19,    -1,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,
      -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    -1,    74,    75,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      96,    -1,    -1,    99,    -1,   101,    -1,   103,    -1,    -1,
      -1,   107,   108,   109,    -1,   111,   112,    -1,   114,   115,
     116,    -1,   118,    -1,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,     3,     4,     5,    -1,    -1,    -1,
       9,    -1,    11,    12,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    -1,    -1,    34,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    -1,    -1,    -1,    96,    -1,    -1,
      99,    -1,   101,    -1,   103,    -1,    -1,    -1,   107,   108,
     109,    -1,   111,   112,    -1,   114,   115,   116,    -1,   118,
      -1,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,     3,     4,     5,    -1,    -1,    -1,     9,    -1,    11,
      12,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    34,    -1,    -1,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    -1,    74,    75,    76,    77,    78,    79,    80,    -1,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    91,
      -1,    -1,    -1,    -1,    96,    -1,    -1,    99,    -1,   101,
      -1,   103,    -1,    -1,    -1,   107,   108,   109,    -1,   111,
     112,    -1,   114,   115,   116,    -1,   118,    -1,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,     3,     4,
       5,    -1,    -1,    -1,     9,    -1,    11,    12,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    34,
      -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    74,
      75,    76,    77,    78,    79,    80,    -1,    82,    83,    84,
      85,    86,    87,    88,    89,    -1,    91,    -1,    -1,    -1,
      -1,    96,    -1,    -1,    99,    -1,   101,    -1,   103,    -1,
      -1,    -1,   107,   108,   109,    -1,   111,   112,    -1,   114,
     115,   116,    -1,   118,    -1,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,     3,     4,     5,    -1,    -1,
      -1,     9,    -1,    11,    12,    -1,    -1,    -1,    -1,    17,
      -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    -1,    74,    75,    76,    77,
      78,    79,    80,    -1,    82,    83,    84,    85,    86,    87,
      88,    89,    -1,    91,    -1,    -1,    -1,    -1,    96,    -1,
      -1,    99,    -1,   101,    -1,   103,    -1,    -1,    -1,   107,
     108,   109,    -1,   111,   112,    -1,   114,   115,   116,    -1,
     118,    -1,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,     3,     4,     5,    -1,    -1,    -1,     9,    -1,
      11,    12,    -1,    14,    -1,    -1,    17,    -1,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    -1,    -1,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    -1,    74,    75,    76,    77,    78,    79,    80,
      -1,    82,    83,    84,    85,    86,    87,    88,    89,    -1,
      91,    -1,    -1,    -1,    -1,    96,    -1,    -1,    99,    -1,
     101,    -1,   103,    -1,    -1,    -1,   107,   108,   109,    -1,
     111,   112,    -1,   114,   115,   116,    -1,   118,    -1,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,     3,
       4,     5,    -1,    -1,    -1,     9,    -1,    11,    12,    -1,
      14,    -1,    -1,    17,    -1,    -1,    -1,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    -1,
      74,    75,    76,    77,    78,    79,    80,    -1,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    91,    -1,    -1,
      -1,    -1,    96,    -1,    -1,    99,    -1,   101,    -1,   103,
      -1,    -1,    -1,   107,   108,   109,    -1,   111,   112,    -1,
     114,   115,   116,    -1,   118,    -1,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,     3,     4,     5,    -1,
      -1,    -1,     9,    -1,    11,    12,    -1,    -1,    -1,    -1,
      17,    -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    -1,    -1,    34,    -1,    -1,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    -1,    74,    75,    76,
      77,    78,    79,    80,    -1,    82,    83,    84,    85,    86,
      87,    88,    89,    -1,    91,    -1,    -1,    -1,    -1,    96,
      -1,    -1,    99,    -1,   101,    -1,   103,    -1,    -1,    -1,
     107,   108,   109,    -1,   111,   112,    -1,   114,   115,   116,
      -1,   118,    -1,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,     3,     4,     5,    -1,    -1,    -1,     9,
      -1,    11,    12,    -1,    -1,    -1,    -1,    17,    -1,    -1,
      -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    -1,    -1,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    -1,    74,    75,    76,    77,    78,    79,
      80,    -1,    82,    83,    84,    85,    86,    87,    88,    89,
      -1,    91,    -1,    -1,    -1,    -1,    96,    -1,    -1,    99,
      -1,   101,    -1,   103,    -1,    -1,    -1,   107,   108,   109,
      -1,   111,   112,    -1,   114,   115,   116,    -1,   118,    -1,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
       3,     4,     5,    -1,    -1,    -1,     9,    -1,    11,    12,
      -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    74,    75,    76,    77,    78,    79,    80,    -1,    82,
      83,    84,    85,    86,    87,    88,    89,    -1,    91,    -1,
      -1,    -1,    -1,    96,    -1,    -1,    99,    -1,   101,    -1,
     103,    -1,    -1,    -1,   107,   108,   109,    -1,   111,   112,
      -1,   114,   115,   116,    -1,   118,    -1,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,     3,     4,     5,
      -1,    -1,    -1,     9,    -1,    11,    12,    -1,    -1,    -1,
      -1,    17,    -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,
      -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    -1,    74,    75,
      76,    77,    78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      96,    -1,    -1,    99,    -1,   101,    -1,   103,    -1,    -1,
      -1,   107,   108,   109,    -1,   111,   112,    -1,   114,    -1,
     116,    -1,   118,    -1,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,     3,     4,     5,    -1,    -1,    -1,
       9,    -1,    11,    12,    -1,    -1,    -1,    -1,    17,    -1,
      19,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    -1,    74,    75,    76,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,
      99,    -1,   101,    -1,   103,    -1,    -1,    -1,   107,   108,
     109,    -1,   111,   112,    -1,   114,   115,   116,    -1,   118,
      -1,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,     3,     4,     5,    -1,    -1,    -1,     9,    -1,    11,
      12,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    -1,    -1,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    96,    -1,    -1,    99,    -1,   101,
      -1,   103,    -1,    -1,    -1,   107,   108,   109,    -1,   111,
     112,    -1,   114,   115,   116,    -1,   118,    -1,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,     3,     4,
       5,    -1,    -1,    -1,     9,    -1,    11,    12,    -1,    -1,
      -1,    -1,    17,    -1,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    74,
      75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    96,    -1,    -1,    99,    -1,   101,    -1,   103,    -1,
      -1,    -1,   107,   108,   109,    -1,   111,   112,    -1,   114,
     115,   116,    -1,   118,    -1,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,     3,     4,     5,    -1,    -1,
      -1,     9,    -1,    11,    12,    -1,    -1,    -1,    -1,    17,
      -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    -1,    74,    75,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,
      -1,    99,    -1,   101,    -1,   103,    -1,    -1,    -1,   107,
     108,   109,    -1,   111,   112,    -1,   114,   115,   116,    -1,
     118,    -1,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,     3,     4,     5,    -1,    -1,    -1,     9,    -1,
      11,    12,    -1,    -1,    -1,    -1,    17,    18,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    -1,    -1,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    99,    -1,
     101,    -1,   103,    -1,    -1,    -1,   107,   108,   109,    -1,
     111,   112,    -1,   114,    -1,   116,    -1,   118,    -1,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,     3,
       4,     5,    -1,    -1,    -1,     9,    -1,    11,    12,    -1,
      -1,    -1,    -1,    17,    -1,    -1,    -1,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    -1,
      74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    96,    -1,    -1,    99,    -1,   101,    -1,   103,
      -1,    -1,    -1,   107,   108,   109,    -1,   111,   112,    -1,
     114,    -1,   116,    -1,   118,    -1,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      17,    -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    -1,    -1,    56,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    -1,    74,    75,    76,
      77,    78,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     107,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   121,    -1,    -1,    56,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    -1,    74,    75,    76,    -1,    -1,
       5,    -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    17,    -1,    -1,    -1,    -1,    96,    -1,    -1,
      99,    -1,   101,    -1,   103,    -1,    -1,    -1,   107,   108,
     109,    -1,   111,   112,     5,   114,    -1,   116,     9,   118,
      -1,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,    56,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    74,
      75,    76,    77,    78,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    56,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    -1,    74,    75,    76,    77,    78,    -1,    -1,
      13,    -1,    -1,    -1,    -1,    -1,   121,    88,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     121,    -1,    -1,    56,    -1,    -1,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    -1,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      -1,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    74,    75,    76,    77,    78,    79,    80,    -1,    82,
      83,    84,    85,    86,    87,    88,    89,    21,    91,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    -1,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    -1,    74,    75,    76,    77,    78,    79,    80,    -1,
      82,    83,    84,    85,    86,    87,    88,    89,    21,    91,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,   121,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    74,    75,    76,    77,    78,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    22,    -1,    88,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    -1,
      74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    56,   121,    -1,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,   108,    74,    75,    76,    77,    78,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,    -1,    88,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,   121,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    -1,   121,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    -1,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    -1,   121,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    74,
      75,    76,    77,    78,    79,    80,    -1,    82,    83,    84,
      85,    86,    87,    88,    89,    -1,    91,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    -1,   121,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      -1,    74,    75,    76,    77,    78,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    -1,    88,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    -1,
      74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,   121,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   121
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned short int
  CxxParser::yystos_[] =
  {
         0,    29,   155,   214,   342,     0,   344,     3,     4,     5,
       9,    11,    12,    17,    21,    34,    37,    55,    56,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    74,    75,    76,    77,    78,    79,    80,    82,
      83,    84,    85,    86,    87,    88,    89,    91,    96,    99,
     101,   103,   107,   108,   109,   111,   112,   114,   115,   116,
     118,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   134,   135,   136,   138,   139,   140,   141,   143,   144,
     145,   151,   152,   153,   154,   156,   157,   160,   162,   163,
     164,   165,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   186,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   232,   233,   234,   236,
     238,   239,   240,   241,   258,   259,   260,   261,   264,   269,
     270,   273,   274,   275,   292,   293,   294,   295,   310,   318,
     326,   334,   215,   343,    88,   170,   260,   170,   170,   170,
     172,   177,   185,   186,   183,   232,   271,   272,   275,   276,
     170,   170,    19,    88,   138,   139,   141,   242,   141,    88,
     135,   138,   143,   223,   232,   236,   269,   326,    13,   170,
      13,    88,   141,   166,   235,   236,   237,   238,   264,   270,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    17,    21,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    99,   107,
     235,   311,   319,    13,   157,   163,    13,   183,   270,    13,
     137,    56,    88,   140,   144,   164,   165,   259,    11,    88,
     140,   142,   144,   259,    29,   170,    17,    24,    32,    34,
      37,   269,    31,    33,    54,     6,     7,   258,     3,     4,
      42,    43,    13,    14,    36,    38,    35,    41,     9,     8,
      10,    39,    15,    23,    40,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,   184,   230,   231,   238,    56,
      88,   138,   139,   226,   227,   222,   231,    56,   145,   225,
     258,   154,   264,   170,   261,   263,    15,   296,    16,    19,
     141,   132,     1,    16,    30,    73,    81,    82,    88,    90,
      92,   183,   216,   217,   218,   219,   220,   221,   232,   250,
     251,   252,   253,   254,   255,   256,   257,   279,   280,   281,
     282,   304,   306,   320,   321,   329,   338,    88,   258,     9,
      18,   276,    22,    31,    55,    20,   243,   245,   246,   247,
     339,    88,   242,    13,   235,   265,   265,    21,   169,    17,
     138,   139,   166,   167,   168,   260,   262,   166,   270,    18,
      22,   260,   262,   311,   265,   265,     3,     4,   136,   142,
     185,    11,    88,   138,   139,   141,   142,   145,   146,   147,
     148,   149,   150,   238,   146,   150,   159,   183,   170,   170,
     171,   171,   171,   260,   262,   172,   172,   173,   173,   174,
     174,   174,   174,   175,   175,   176,   273,   177,   178,   179,
      19,   287,   186,   180,   183,    56,   170,   115,   264,   336,
     183,    20,   344,    57,    58,    59,    91,   141,   307,   308,
     309,    16,    19,   291,   339,   181,   305,    19,   141,   213,
      88,   320,   151,    13,    88,   218,   220,    73,    75,    88,
     146,    21,    16,    19,    31,   117,   204,   283,   285,   221,
     280,   281,    30,    31,    30,    31,   283,   285,    15,   217,
       3,     4,   276,   135,   248,   249,    31,   243,   339,     1,
     115,   174,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   232,   273,   277,   278,   327,   328,   335,   260,   265,
     266,   267,   268,    14,    14,   161,   162,   183,   186,    17,
     136,   138,   139,   167,   262,   169,   169,    14,    14,    14,
     327,    18,   147,   148,    11,    88,   138,   150,    88,   149,
      56,   238,     3,     4,    20,   288,   289,   342,    16,    21,
     297,   342,   308,    19,    31,   308,     1,   307,     1,    23,
     341,    15,   213,    13,   213,   215,    14,    71,    75,    88,
     277,   321,   322,   323,   324,   325,   339,   141,   146,    30,
     151,   305,   205,   183,   257,    16,   284,   312,   313,   257,
     183,   183,   286,   287,   216,    15,    20,   244,   245,   339,
       1,    20,    31,   190,   196,    13,    36,    38,    35,    41,
       9,     8,    10,    39,    15,    23,    40,   184,   277,    15,
      14,    31,   266,    17,   269,    21,    21,    22,    31,    18,
     181,   182,   187,    21,    21,    14,    88,   139,    11,     1,
     158,   272,    20,    31,   132,   286,   290,   338,   183,    22,
     265,   337,   132,    30,    90,   183,   232,   252,   279,   282,
     298,   299,   300,   301,   303,   309,   320,   338,   308,    19,
      30,   305,   214,   141,   217,    71,    14,    31,    15,    15,
       1,    30,    30,    22,    20,   199,   342,   141,   314,   315,
     316,   317,    95,   331,   332,   285,   187,     1,     9,   174,
     174,   174,   188,   188,   189,   273,   190,   191,   192,   196,
     197,   198,   193,   196,   196,   328,    18,   187,   186,   186,
     183,    18,   186,   186,    88,   147,   272,   340,    30,    20,
     289,   339,     3,     4,    22,    31,   339,    30,    31,   300,
      30,    31,    30,    31,    16,     3,     4,    16,    20,   344,
      30,   135,   323,   265,   135,    30,   132,    73,    88,    93,
      94,    97,    98,   100,   104,   105,   106,   110,   113,   117,
     119,   134,   183,   200,   201,   202,   203,   204,   206,   209,
     211,   212,   219,   232,   330,   338,    31,   339,   316,    21,
      21,   331,    20,    16,    31,    18,    22,    22,    22,    22,
      30,     1,    19,   132,     1,   290,   265,     1,   183,   302,
     306,   183,   306,   302,   298,   305,   215,   339,   141,    88,
      30,   187,    30,    16,   199,    21,   135,    21,   185,    21,
     204,    21,    16,     3,     4,     1,   161,   276,   333,   196,
     196,     1,   339,    20,    20,    30,   132,     1,    16,   199,
     119,   210,   221,    30,   208,   272,    30,   208,   331,   208,
     199,   200,    31,    22,    22,     1,   339,    20,    30,   199,
      21,   207,   208,    22,    22,    22,   204,    20,     1,   186,
      30,   199,   199,   199,    20,    22,   185,   102,    30,    22,
     199,   199
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
     356,   357,    35
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned short int
  CxxParser::yyr1_[] =
  {
         0,   133,   134,   135,   136,   136,   136,   136,   136,   137,
     138,   138,   139,   140,   140,   141,   141,   142,   142,   143,
     143,   143,   144,   144,   144,   145,   145,   146,   146,   146,
     147,   147,   148,   148,   148,   149,   149,   150,   150,   151,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     153,   153,   154,   154,   154,   155,   155,   156,   156,   156,
     156,   157,   157,   157,   158,   158,   159,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   161,   161,   162,   162,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   164,   165,   165,   165,   165,   166,   166,   166,
     167,   167,   168,   168,   169,   169,   170,   170,   171,   171,
     171,   172,   172,   172,   172,   173,   173,   173,   174,   174,
     174,   175,   175,   175,   175,   175,   176,   176,   176,   177,
     177,   178,   178,   179,   179,   180,   180,   181,   181,   182,
     182,   183,   183,   183,   183,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   185,   185,   186,   186,
     187,   188,   188,   188,   188,   189,   189,   189,   190,   190,
     191,   191,   192,   192,   193,   193,   194,   194,   195,   195,
     196,   196,   196,   197,   197,   198,   198,   199,   200,   200,
     200,   201,   201,   201,   201,   202,   202,   202,   202,   203,
     203,   203,   204,   204,   205,   205,   205,   206,   206,   206,
     207,   207,   208,   209,   209,   209,   210,   211,   211,   211,
     211,   212,   213,   213,   214,   214,   214,   215,   216,   216,
     216,   217,   217,   217,   217,   217,   218,   218,   218,   219,
     219,   220,   220,   220,   220,   220,   221,   221,   221,   221,
     222,   222,   222,   223,   223,   224,   224,   224,   225,   225,
     226,   226,   227,   227,   227,   228,   228,   228,   229,   229,
     229,   230,   230,   230,   230,   230,   231,   232,   232,   233,
     233,   233,   233,   233,   234,   234,   234,   235,   235,   235,
     236,   236,   236,   236,   237,   237,   238,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   238,   239,   239,   239,
     240,   241,   241,   242,   242,   242,   243,   243,   244,   244,
     245,   245,   246,   246,   247,   248,   248,   249,   250,   250,
     251,   252,   252,   253,   254,   255,   255,   256,   256,   257,
     258,   258,   259,   259,   260,   260,   260,   261,   261,   262,
     262,   263,   263,   264,   264,   265,   265,   266,   266,   266,
     267,   267,   268,   268,   268,   269,   269,   270,   271,   271,
     271,   272,   272,   273,   273,   274,   274,   274,   275,   275,
     275,   276,   276,   276,   277,   277,   277,   277,   278,   278,
     278,   279,   279,   280,   280,   280,   281,   281,   281,   282,
     282,   283,   284,   285,   286,   286,   287,   287,   287,   287,
     287,   288,   288,   289,   290,   290,   290,   291,   292,   292,
     293,   293,   293,   293,   294,   294,   294,   295,   295,   296,
     296,   296,   297,   298,   298,   298,   299,   299,   299,   299,
     299,   300,   300,   300,   300,   300,   301,   301,   301,   302,
     302,   303,   304,   304,   305,   305,   306,   306,   307,   307,
     308,   308,   308,   309,   309,   309,   310,   311,   311,   312,
     312,   313,   313,   314,   314,   315,   315,   316,   317,   318,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     320,   320,   321,   322,   322,   323,   323,   323,   323,   323,
     323,   324,   324,   325,   325,   326,   326,   327,   327,   328,
     329,   330,   331,   331,   332,   333,   334,   334,   335,   335,
     336,   336,   337,   337,   338,   339,   340,   341,   342,   343,
     344
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  CxxParser::yyr2_[] =
  {
         0,     2,     1,     1,     1,     5,     4,     3,     1,     1,
       1,     2,     2,     1,     2,     1,     2,     2,     2,     1,
       1,     2,     1,     2,     2,     1,     2,     1,     1,     1,
       1,     2,     4,     2,     2,     1,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     4,     1,     1,     1,
       1,     1,     3,     2,     2,     3,     0,     1,     4,     8,
       7,     5,     4,     3,     3,     3,     3,     2,     2,     7,
       7,     7,     7,     2,     0,     1,     1,     3,     1,     2,
       2,     2,     3,     2,     2,     2,     2,     2,     1,     2,
       1,     2,     2,     3,     4,     2,     4,     2,     2,     2,
       2,     1,     3,     4,     0,     3,     1,     2,     1,     3,
       3,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       5,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     1,     1,     3,
       1,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     5,
       1,     3,     1,     1,     3,     1,     3,     2,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       4,     3,     3,     7,     0,     2,     6,     5,     7,     5,
       0,     1,     1,     5,     7,     8,     1,     2,     2,     3,
       3,     1,     4,     9,     0,     3,     7,     2,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     2,     2,
       1,     2,     2,     1,     2,     1,     1,     2,     1,     2,
       1,     2,     1,     1,     2,     1,     2,     1,     2,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     3,     2,     2,     3,     4,     1,     3,     1,     3,
       0,     3,     1,     3,     2,     1,     3,     1,     3,     2,
       5,     3,     4,     4,     5,     3,     3,     3,     3,     1,
       1,     2,     1,     2,     1,     1,     2,     1,     2,     0,
       2,     0,     2,     1,     1,     2,     2,     0,     2,     1,
       0,     1,     2,     3,     4,     2,     3,     3,     0,     1,
       2,     1,     3,     1,     3,     1,     2,     3,     1,     3,
       1,     1,     1,     2,     1,     1,     3,     2,     1,     2,
       3,     1,     1,     2,     2,     2,     2,     2,     2,     1,
       3,     3,     2,     1,     1,     1,     3,     4,     2,     6,
       8,     1,     3,     2,     1,     3,     2,     1,     2,     4,
       5,     4,     3,     2,     1,     1,     1,     3,     8,     0,
       3,     7,     2,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     3,     3,     3,     1,
       1,     2,     3,     2,     1,     5,     1,     3,     1,     3,
       1,     2,     2,     1,     1,     1,     2,     2,     2,     0,
       1,     2,     4,     1,     2,     2,     4,     4,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       2,     2,     4,     1,     3,     1,     3,     1,     3,     1,
       2,     1,     1,     2,     3,     5,     2,     1,     3,     1,
       4,     3,     1,     2,     5,     1,     1,     2,     1,     2,
       3,     4,     1,     3,     1,     0,     0,     0,     0,     0,
       0
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
  "SWITCH", "THIS", "THROW", "TRUE", "TRY", "TYPEID", "WHILE",
  "CharacterLiteral", "Identifier", "HexLiteral", "LongDoubleLiteral",
  "DoubleLiteral", "FloatLiteral", "UIntLiteral", "ULongLiteral",
  "ULongLongLiteral", "StringLiteral", "SHIFT_THERE", "REDUCE_HERE_MOSTLY",
  "'#'", "$accept", "identifier_word", "identifier", "id", "template_test",
  "global_scope", "id_scope", "nested_id", "scoped_id", "destructor_id",
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
  "specialised_declaration", "block_declaration",
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
  "parenthesis_clause", "parameters_clause",
  "parameter_declaration_clause", "parameter_declaration_list",
  "abstract_pointer_declaration", "abstract_parameter_declaration",
  "special_parameter_declaration", "parameter_declaration",
  "templated_parameter_declaration", "templated_abstract_declaration",
  "function_definition", "func_definition", "ctor_definition",
  "constructor_head", "function_try_block", "function_block",
  "function_body", "initializer_clause", "braced_initializer",
  "initializer_list", "looping_initializer_clause",
  "looped_initializer_clause", "colon_mark", "elaborated_class_specifier",
  "class_specifier_head", "class_key", "class_specifier",
  "member_specification.opt", "looping_member_declaration",
  "looped_member_declaration", "member_declaration",
  "simple_member_declaration", "member_init_declarations",
  "member_init_declaration", "accessibility_specifier",
  "bit_field_declaration", "bit_field_width", "bit_field_init_declaration",
  "base_specifier_list", "base_specifier", "access_specifier",
  "conversion_function_id", "conversion_type_id", "ctor_initializer.opt",
  "ctor_initializer", "mem_initializer_list", "mem_initializer_list_head",
  "mem_initializer", "mem_initializer_id", "operator_function_id",
  "operator", "template_declaration", "template_parameter_clause",
  "template_parameter_list", "template_parameter", "simple_type_parameter",
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
       155,     0,    -1,   121,    -1,   134,    -1,   135,    -1,   135,
     137,     3,   327,    14,    -1,   135,   137,     3,    14,    -1,
     135,   137,     4,    -1,   326,    -1,    13,    -1,    56,    -1,
      88,   138,    -1,   136,    56,    -1,   136,    -1,   139,   140,
      -1,   140,    -1,   138,   140,    -1,    11,   136,    -1,    88,
     142,    -1,   310,    -1,   318,    -1,    88,   143,    -1,   143,
      -1,   139,   142,    -1,   139,   144,    -1,   144,    -1,   138,
     144,    -1,   141,    -1,   145,    -1,   142,    -1,   238,    -1,
     147,   238,    -1,   147,    56,    11,   147,    -1,    11,   147,
      -1,    88,   148,    -1,   148,    -1,   139,   149,    -1,   149,
      -1,   138,   150,    -1,   129,    -1,   122,    -1,   123,    -1,
     124,    -1,   125,    -1,   126,    -1,   127,    -1,   128,    -1,
     120,    -1,   151,    -1,   153,    -1,   103,    -1,   116,    -1,
     275,    -1,   186,    -1,   232,   154,    -1,   214,    -1,    29,
     342,   154,    29,    -1,   152,    -1,   114,    -1,   228,    -1,
     157,    -1,   269,    -1,    17,   185,    18,    -1,    88,   269,
      -1,   272,    30,    -1,   158,   272,    30,    -1,    -1,   156,
      -1,   160,   269,   159,     4,    -1,   160,   269,   159,     3,
     158,   340,    19,     1,    -1,   160,   269,   159,     3,   158,
     340,     1,    -1,   160,   269,   159,     3,     1,    -1,   160,
      17,   185,    18,    -1,   160,    24,   146,    -1,   160,    24,
     150,    -1,   160,    32,   146,    -1,   160,    32,   150,    -1,
     160,    37,    -1,   160,    34,    -1,   101,    13,   265,    14,
      21,   186,    22,    -1,   112,    13,   265,    14,    21,   186,
      22,    -1,   109,    13,   265,    14,    21,   186,    22,    -1,
      96,    13,   265,    14,    21,   186,    22,    -1,   118,   270,
      -1,    -1,   162,    -1,   183,    -1,   162,    31,   183,    -1,
     160,    -1,    37,   170,    -1,    34,   170,    -1,   260,   170,
      -1,   229,   258,   170,    -1,     3,   170,    -1,     4,   170,
      -1,    12,   170,    -1,    11,   170,    -1,   111,   163,    -1,
     165,    -1,   138,   165,    -1,   164,    -1,   138,   164,    -1,
      99,   170,    -1,   107,   166,   169,    -1,   107,   270,   166,
     169,    -1,   107,   270,    -1,   107,   270,   270,   169,    -1,
     235,   262,    -1,   235,   167,    -1,   235,   166,    -1,   260,
     167,    -1,   168,    -1,    17,   186,    18,    -1,   168,    17,
     187,    18,    -1,    -1,    21,   161,    22,    -1,   163,    -1,
     157,   170,    -1,   170,    -1,   171,    54,   170,    -1,   171,
      33,   170,    -1,   171,    -1,   172,   258,   171,    -1,   172,
       6,   171,    -1,   172,     7,   171,    -1,   172,    -1,   173,
       3,   172,    -1,   173,     4,   172,    -1,   173,    -1,   174,
      42,   173,    -1,   174,    43,   173,    -1,   174,    -1,   175,
      13,   174,    -1,   175,    14,   174,    -1,   175,    38,   174,
      -1,   175,    36,   174,    -1,   175,    -1,   176,    35,   175,
      -1,   176,    41,   175,    -1,   176,    -1,   177,     9,   176,
      -1,   177,    -1,   178,     8,   177,    -1,   178,    -1,   179,
      10,   178,    -1,   179,    -1,   180,    39,   179,    -1,   180,
      -1,   181,    40,   180,    -1,   181,    -1,   181,    23,   186,
      16,   183,    -1,   182,    -1,   181,   184,   183,    -1,   181,
      15,   287,    -1,   334,    -1,    15,    -1,    44,    -1,    45,
      -1,    46,    -1,    47,    -1,    48,    -1,    49,    -1,    50,
      -1,    51,    -1,    52,    -1,    53,    -1,    -1,   186,    -1,
     183,    -1,   162,    31,   183,    -1,   182,    -1,   174,    -1,
     188,    13,   174,    -1,   188,    38,   174,    -1,   188,    36,
     174,    -1,   188,    -1,   189,    35,   188,    -1,   189,    41,
     188,    -1,   189,    -1,   190,     9,   189,    -1,   190,    -1,
     191,     8,   190,    -1,   191,    -1,   192,    10,   191,    -1,
     192,    -1,   193,    39,   192,    -1,   193,    -1,   194,    40,
     193,    -1,   194,    -1,   194,    23,   197,    16,   196,    -1,
     195,    -1,   194,   184,   196,    -1,   335,    -1,   196,    -1,
     198,    31,   196,    -1,   196,    -1,   198,    31,   196,    -1,
     342,   200,    -1,   201,    -1,   338,     3,   200,    -1,   338,
       4,    -1,   202,    -1,   204,    -1,   212,    -1,   330,    -1,
     203,    -1,   206,    -1,   209,    -1,   211,    -1,   134,    16,
     199,    -1,    94,   187,    16,   199,    -1,    98,    16,   199,
      -1,    19,   205,    20,    -1,    19,   205,   199,   132,   339,
       1,    20,    -1,    -1,   205,   199,    -1,   205,   199,   132,
     339,     1,    30,    -1,   106,    21,   208,    22,   199,    -1,
     106,    21,   208,    22,   199,   102,   199,    -1,   113,    21,
     208,    22,   199,    -1,    -1,   208,    -1,   272,    -1,   119,
      21,   208,    22,   199,    -1,   100,   199,   119,    21,   186,
      22,    30,    -1,   104,    21,   210,   207,    30,   185,    22,
     199,    -1,   221,    -1,    93,    30,    -1,    97,    30,    -1,
     110,   185,    30,    -1,   105,   135,    30,    -1,   219,    -1,
      19,   341,   214,    20,    -1,    19,   341,   214,   344,   215,
     132,   339,     1,    20,    -1,    -1,   214,   344,   215,    -1,
     214,   344,   215,   132,   339,     1,    30,    -1,   343,   216,
      -1,   217,    -1,   338,     3,   216,    -1,   338,     4,    -1,
     219,    -1,   279,    -1,   320,    -1,   329,    -1,   218,    -1,
     255,    -1,   250,    -1,    88,   218,    -1,   221,    -1,   220,
      -1,   254,    -1,   251,    -1,   252,    -1,   253,    -1,    88,
     220,    -1,    30,    -1,   257,    30,    -1,   256,    30,    -1,
     232,   221,    -1,   238,    -1,   222,   238,    -1,   222,   231,
      -1,   222,    -1,    88,   223,    -1,   141,    -1,   236,    -1,
     224,   231,    -1,   224,    -1,   224,   222,    -1,   225,    -1,
     226,   225,    -1,   145,    -1,   226,    -1,   226,   145,    -1,
     223,    -1,   223,   227,    -1,   227,    -1,   226,    56,    -1,
     223,   226,    56,    -1,   223,    56,    -1,   233,    -1,   234,
      -1,    83,    -1,    89,    -1,   264,    -1,   230,    -1,   230,
      -1,    88,   232,    -1,    86,    -1,    87,    -1,    85,    -1,
      82,    -1,    79,    -1,    80,    -1,    84,    -1,    91,    -1,
     237,    -1,   236,    -1,   264,    -1,   295,    -1,   241,    -1,
     239,    -1,    88,   236,    -1,   141,    -1,   238,    -1,    61,
      -1,    70,    -1,    60,    -1,    66,    -1,    64,    -1,    65,
      -1,    67,    -1,    68,    -1,    63,    -1,    62,    -1,    69,
      -1,   292,    -1,   240,    -1,    75,   141,    -1,    72,   141,
      -1,    72,   141,   242,    -1,    72,   242,    -1,    19,   243,
      -1,    19,   247,   243,    -1,    19,   247,    31,   244,    -1,
      20,    -1,   339,     1,    20,    -1,    20,    -1,   339,     1,
      20,    -1,    -1,   339,     1,    31,    -1,   245,    -1,   247,
      31,   245,    -1,   246,   248,    -1,   249,    -1,   249,    15,
     187,    -1,   135,    -1,    73,   141,   213,    -1,    73,   213,
      -1,    73,   141,    15,   141,    30,    -1,    90,   146,    30,
      -1,    90,    75,   146,    30,    -1,    90,    73,   141,    30,
      -1,    92,    21,   151,    22,    30,    -1,    82,   151,   215,
      -1,    82,   151,   213,    -1,   183,    31,   257,    -1,   256,
      31,   257,    -1,   183,    -1,     5,    -1,   258,   264,    -1,
     258,    -1,   139,   259,    -1,     9,    -1,   259,    -1,   138,
     259,    -1,   260,    -1,   260,   261,    -1,    -1,   260,   262,
      -1,    -1,   263,   264,    -1,    77,    -1,    78,    -1,   235,
     266,    -1,   235,   265,    -1,    -1,   260,   266,    -1,   268,
      -1,    -1,   268,    -1,   267,   269,    -1,   267,    17,    18,
      -1,   267,    17,   187,    18,    -1,   270,   263,    -1,   270,
     263,   336,    -1,    21,   271,    22,    -1,    -1,   272,    -1,
     272,    55,    -1,   276,    -1,   272,    31,   276,    -1,   261,
      -1,   172,   258,   262,    -1,   273,    -1,   177,     9,    -1,
     177,     9,   273,    -1,   274,    -1,   274,    15,   183,    -1,
      55,    -1,   183,    -1,   275,    -1,   232,   276,    -1,   196,
      -1,   278,    -1,   278,    15,   196,    -1,   232,   277,    -1,
     273,    -1,   190,     9,    -1,   190,     9,   273,    -1,   281,
      -1,   280,    -1,   183,   283,    -1,   183,   285,    -1,   232,
     280,    -1,   282,   283,    -1,   282,   285,    -1,   232,   281,
      -1,   306,    -1,   282,    31,   183,    -1,   117,   284,   331,
      -1,   312,   285,    -1,   204,    -1,   183,    -1,   287,    -1,
      19,   288,    20,    -1,    19,   288,    31,    20,    -1,    19,
      20,    -1,    19,   289,   132,   339,     1,    20,    -1,    19,
     288,    31,   289,   132,   339,     1,    20,    -1,   289,    -1,
     288,    31,   289,    -1,   342,   290,    -1,   286,    -1,   338,
       3,   290,    -1,   338,     4,    -1,    16,    -1,   294,   141,
      -1,   294,   141,   291,     1,    -1,   294,   141,   291,   307,
      19,    -1,   294,    16,   307,    19,    -1,   294,   141,    19,
      -1,   294,    19,    -1,    71,    -1,    74,    -1,    76,    -1,
     293,   296,    20,    -1,   293,   296,   344,   297,   132,   339,
       1,    20,    -1,    -1,   296,   344,   297,    -1,   296,   344,
     297,   132,   339,     1,    30,    -1,   342,   298,    -1,   299,
      -1,   338,     3,   298,    -1,   338,     4,    -1,   303,    -1,
     300,    -1,   279,    -1,   252,    -1,   320,    -1,    30,    -1,
     183,    30,    -1,   282,    30,    -1,   301,    30,    -1,   232,
     300,    -1,   183,    31,   302,    -1,   282,    31,   306,    -1,
     301,    31,   302,    -1,   183,    -1,   306,    -1,   309,    16,
      -1,   183,    16,   305,    -1,    16,   305,    -1,   181,    -1,
     181,    23,   305,    16,   305,    -1,   304,    -1,   304,    15,
     286,    -1,   308,    -1,   307,    31,   308,    -1,   141,    -1,
     309,   308,    -1,    91,   308,    -1,    57,    -1,    58,    -1,
      59,    -1,   108,   311,    -1,   235,   262,    -1,   235,   311,
      -1,    -1,   313,    -1,    16,   314,    -1,    16,   314,   339,
       1,    -1,   316,    -1,   315,   316,    -1,   314,    31,    -1,
     314,   339,     1,    31,    -1,   317,    21,   161,    22,    -1,
     141,    -1,   108,   319,    -1,   107,    -1,    99,    -1,     3,
      -1,     4,    -1,     5,    -1,     6,    -1,     7,    -1,     8,
      -1,     9,    -1,    10,    -1,    11,    -1,    12,    -1,    15,
      -1,    13,    -1,    14,    -1,    44,    -1,    52,    -1,    48,
      -1,    46,    -1,    47,    -1,    53,    -1,    45,    -1,    49,
      -1,    42,    -1,    43,    -1,    51,    -1,    50,    -1,    35,
      -1,    41,    -1,    38,    -1,    36,    -1,    39,    -1,    40,
      -1,    37,    -1,    34,    -1,    31,    -1,    33,    -1,    32,
      -1,    21,    22,    -1,    17,    18,    -1,   321,   217,    -1,
      81,   320,    -1,    88,    13,   322,    14,    -1,   323,    -1,
     322,    31,   323,    -1,   324,    -1,   324,    15,   265,    -1,
     325,    -1,   325,    15,   135,    -1,   277,    -1,   339,     1,
      -1,    71,    -1,    75,    -1,   321,    71,    -1,   321,    71,
     135,    -1,    88,   135,    13,   327,    14,    -1,    88,   326,
      -1,   328,    -1,   327,    31,   328,    -1,   277,    -1,    88,
      13,    14,   217,    -1,   117,   204,   331,    -1,   332,    -1,
     332,   331,    -1,    95,    21,   333,    22,   204,    -1,   276,
      -1,   115,    -1,   115,   183,    -1,   115,    -1,   115,   196,
      -1,   115,    21,    22,    -1,   115,    21,   337,    22,    -1,
     265,    -1,   337,    31,   265,    -1,     1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  CxxParser::yyprhs_[] =
  {
         0,     0,     3,     5,     7,     9,    15,    20,    24,    26,
      28,    30,    33,    36,    38,    41,    43,    46,    49,    52,
      54,    56,    59,    61,    64,    67,    69,    72,    74,    76,
      78,    80,    83,    88,    91,    94,    96,    99,   101,   104,
     106,   108,   110,   112,   114,   116,   118,   120,   122,   124,
     126,   128,   130,   132,   134,   137,   139,   144,   146,   148,
     150,   152,   154,   158,   161,   164,   168,   169,   171,   176,
     185,   193,   199,   204,   208,   212,   216,   220,   223,   226,
     234,   242,   250,   258,   261,   262,   264,   266,   270,   272,
     275,   278,   281,   285,   288,   291,   294,   297,   300,   302,
     305,   307,   310,   313,   317,   322,   325,   330,   333,   336,
     339,   342,   344,   348,   353,   354,   358,   360,   363,   365,
     369,   373,   375,   379,   383,   387,   389,   393,   397,   399,
     403,   407,   409,   413,   417,   421,   425,   427,   431,   435,
     437,   441,   443,   447,   449,   453,   455,   459,   461,   465,
     467,   473,   475,   479,   483,   485,   487,   489,   491,   493,
     495,   497,   499,   501,   503,   505,   507,   508,   510,   512,
     516,   518,   520,   524,   528,   532,   534,   538,   542,   544,
     548,   550,   554,   556,   560,   562,   566,   568,   572,   574,
     580,   582,   586,   588,   590,   594,   596,   600,   603,   605,
     609,   612,   614,   616,   618,   620,   622,   624,   626,   628,
     632,   637,   641,   645,   653,   654,   657,   664,   670,   678,
     684,   685,   687,   689,   695,   703,   712,   714,   717,   720,
     724,   728,   730,   735,   745,   746,   750,   758,   761,   763,
     767,   770,   772,   774,   776,   778,   780,   782,   784,   787,
     789,   791,   793,   795,   797,   799,   802,   804,   807,   810,
     813,   815,   818,   821,   823,   826,   828,   830,   833,   835,
     838,   840,   843,   845,   847,   850,   852,   855,   857,   860,
     864,   867,   869,   871,   873,   875,   877,   879,   881,   884,
     886,   888,   890,   892,   894,   896,   898,   900,   902,   904,
     906,   908,   910,   912,   915,   917,   919,   921,   923,   925,
     927,   929,   931,   933,   935,   937,   939,   941,   943,   945,
     948,   951,   955,   958,   961,   965,   970,   972,   976,   978,
     982,   983,   987,   989,   993,   996,   998,  1002,  1004,  1008,
    1011,  1017,  1021,  1026,  1031,  1037,  1041,  1045,  1049,  1053,
    1055,  1057,  1060,  1062,  1065,  1067,  1069,  1072,  1074,  1077,
    1078,  1081,  1082,  1085,  1087,  1089,  1092,  1095,  1096,  1099,
    1101,  1102,  1104,  1107,  1111,  1116,  1119,  1123,  1127,  1128,
    1130,  1133,  1135,  1139,  1141,  1145,  1147,  1150,  1154,  1156,
    1160,  1162,  1164,  1166,  1169,  1171,  1173,  1177,  1180,  1182,
    1185,  1189,  1191,  1193,  1196,  1199,  1202,  1205,  1208,  1211,
    1213,  1217,  1221,  1224,  1226,  1228,  1230,  1234,  1239,  1242,
    1249,  1258,  1260,  1264,  1267,  1269,  1273,  1276,  1278,  1281,
    1286,  1292,  1297,  1301,  1304,  1306,  1308,  1310,  1314,  1323,
    1324,  1328,  1336,  1339,  1341,  1345,  1348,  1350,  1352,  1354,
    1356,  1358,  1360,  1363,  1366,  1369,  1372,  1376,  1380,  1384,
    1386,  1388,  1391,  1395,  1398,  1400,  1406,  1408,  1412,  1414,
    1418,  1420,  1423,  1426,  1428,  1430,  1432,  1435,  1438,  1441,
    1442,  1444,  1447,  1452,  1454,  1457,  1460,  1465,  1470,  1472,
    1475,  1477,  1479,  1481,  1483,  1485,  1487,  1489,  1491,  1493,
    1495,  1497,  1499,  1501,  1503,  1505,  1507,  1509,  1511,  1513,
    1515,  1517,  1519,  1521,  1523,  1525,  1527,  1529,  1531,  1533,
    1535,  1537,  1539,  1541,  1543,  1545,  1547,  1549,  1551,  1554,
    1557,  1560,  1563,  1568,  1570,  1574,  1576,  1580,  1582,  1586,
    1588,  1591,  1593,  1595,  1598,  1602,  1608,  1611,  1613,  1617,
    1619,  1624,  1628,  1630,  1633,  1639,  1641,  1643,  1646,  1648,
    1651,  1655,  1660,  1662,  1666,  1668,  1669,  1670,  1671,  1672,
    1673
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  CxxParser::yyrline_[] =
  {
         0,   356,   356,   357,   365,   366,   367,   368,   369,   370,
     371,   372,   373,   378,   379,   380,   381,   388,   389,   390,
     391,   392,   393,   394,   395,   396,   397,   400,   401,   402,
     409,   410,   411,   412,   413,   414,   415,   416,   417,   428,
     431,   432,   433,   434,   435,   436,   437,   438,   439,   440,
     441,   442,   447,   448,   449,   450,   451,   483,   484,   485,
     489,   495,   496,   497,   504,   505,   506,   507,   509,   510,
     512,   514,   516,   520,   522,   523,   525,   526,   527,   528,
     529,   530,   531,   532,   535,   536,   537,   538,   540,   541,
     542,   543,   548,   550,   551,   552,   553,   554,   556,   557,
     558,   559,   563,   565,   566,   567,   569,   573,   574,   575,
     576,   577,   578,   579,   580,   581,   586,   587,   590,   591,
     592,   593,   594,   595,   596,   597,   598,   599,   600,   601,
     602,   603,   604,   605,   606,   607,   608,   609,   610,   611,
     612,   613,   614,   615,   616,   617,   618,   619,   620,   621,
     622,   628,   629,   630,   631,   632,   632,   632,   632,   632,
     632,   632,   632,   632,   632,   632,   637,   638,   639,   640,
     641,   645,   646,   647,   648,   649,   650,   651,   652,   653,
     654,   655,   657,   658,   660,   661,   663,   664,   666,   667,
     669,   670,   672,   673,   674,   676,   677,   684,   685,   686,
     687,   688,   690,   691,   692,   693,   694,   695,   696,   697,
     698,   699,   701,   702,   703,   704,   705,   709,   710,   711,
     712,   713,   714,   717,   718,   719,   721,   723,   724,   725,
     726,   727,   732,   733,   735,   736,   737,   738,   739,   740,
     741,   742,   743,   744,   746,   747,   748,   749,   750,   751,
     752,   753,   754,   755,   756,   757,   758,   759,   760,   761,
     776,   777,   778,   779,   780,   781,   782,   783,   784,   785,
     786,   787,   788,   789,   790,   791,   792,   793,   794,   795,
     796,   798,   799,   800,   801,   802,   804,   806,   807,   809,
     810,   811,   812,   813,   815,   816,   817,   819,   820,   821,
     823,   824,   825,   826,   827,   828,   829,   830,   831,   832,
     833,   834,   835,   836,   837,   838,   839,   850,   851,   852,
     854,   855,   856,   857,   858,   859,   860,   861,   862,   863,
     864,   865,   866,   867,   868,   869,   870,   871,   873,   874,
     875,   877,   878,   880,   881,   882,   883,   889,   890,   891,
     898,   899,   900,   901,   902,   903,   904,   905,   906,   908,
     909,   911,   912,   913,   914,   917,   918,   921,   922,   923,
     924,   925,   926,   927,   928,   931,   932,   933,   935,   936,
     937,   938,   939,   946,   947,   948,   949,   950,   951,   952,
     953,   954,   955,   956,   960,   961,   962,   963,   964,   965,
     966,   972,   973,   974,   975,   976,   977,   978,   979,   980,
     981,   982,   983,   984,   991,   992,   993,   994,   995,   996,
     997,   999,  1000,  1001,  1002,  1003,  1004,  1019,  1020,  1021,
    1022,  1023,  1024,  1025,  1026,  1026,  1026,  1027,  1028,  1030,
    1031,  1032,  1034,  1035,  1036,  1037,  1038,  1039,  1040,  1043,
    1044,  1051,  1052,  1053,  1054,  1055,  1056,  1057,  1058,  1059,
    1062,  1063,  1064,  1065,  1066,  1068,  1069,  1070,  1076,  1077,
    1078,  1079,  1080,  1081,  1081,  1081,  1086,  1087,  1088,  1096,
    1097,  1098,  1099,  1100,  1101,  1102,  1103,  1104,  1105,  1110,
    1120,  1121,  1126,  1127,  1128,  1129,  1130,  1131,  1132,  1133,
    1134,  1135,  1136,  1137,  1138,  1139,  1140,  1141,  1142,  1143,
    1144,  1145,  1146,  1147,  1148,  1149,  1150,  1151,  1152,  1153,
    1154,  1155,  1156,  1157,  1158,  1159,  1160,  1161,  1162,  1163,
    1168,  1169,  1170,  1171,  1172,  1173,  1174,  1175,  1176,  1177,
    1178,  1179,  1181,  1183,  1184,  1185,  1186,  1190,  1191,  1192,
    1202,  1207,  1209,  1210,  1211,  1212,  1214,  1215,  1216,  1217,
    1218,  1219,  1220,  1221,  1226,  1227,  1228,  1229,  1230,  1231,
    1232
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
       2,     2,     2,    12,    26,   132,    29,     7,     9,    25,
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
     124,   125,   126,   127,   128,   129,   130,   131
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int CxxParser::yyeof_ = 0;
  const int CxxParser::yylast_ = 5257;
  const int CxxParser::yynnts_ = 212;
  const int CxxParser::yyempty_ = -2;
  const int CxxParser::yyfinal_ = 5;
  const int CxxParser::yyterror_ = 1;
  const int CxxParser::yyerrcode_ = 256;
  const int CxxParser::yyntokens_ = 133;

  const unsigned int CxxParser::yyuser_token_number_max_ = 357;
  const CxxParser::token_number_type CxxParser::yyundef_token_ = 2;


} // phantom
/* Line 1141 of lalr1.cc  */
#line 6064 "CxxParser.cxx"
/* Line 1142 of lalr1.cc  */
#line 1234 "CxxParser.y"


void phantom::CxxParser::error(const CxxParser::location_type& l, const string& m)
{
}

/*EndTester*/
