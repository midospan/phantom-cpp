#ifndef CXXTOKEN_HXX
#define CXXTOKEN_HXX

#include <iostream>
#include <stdlib.h>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/ConstantExpression.h>
#include <phantom/reflection/Block.h>
#include <phantom/reflection/LocalVariable.h>
#include <phantom/reflection/ArrayExpression.h>
#include <phantom/reflection/StringLiteralExpression.h>
#include <phantom/reflection/WStringLiteralExpression.h>
#include <phantom/reflection/ConditionalExpression.h>
#include <phantom/reflection/PlacementConstructionExpression.h>
#include <phantom/reflection/AssignmentExpression.h>
#include <phantom/reflection/InstanceDataMemberExpression.h>
#include <phantom/reflection/AddressExpression.h>
#include <phantom/reflection/CallExpression.h>
#include <phantom/reflection/CastExpression.h>
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
#include <phantom/reflection/BinaryOperationExpression.h>
#include <phantom/reflection/Parameter.h>
#include <phantom/reflection/ReturnStatement.h>
#include <phantom/reflection/ReturnStatement.h>
#include <phantom/reflection/ReturnStatement.h>
#include <phantom/reflection/ReturnStatement.h>
#include <phantom/reflection/ReturnStatement.h>

#define o__bool__add_reflection_to_precompiled_elements 1

#if o__bool__add_reflection_to_precompiled_elements
#   define o_new_elem(...) o_new(__VA_ARGS__)
#else
#   define o_new_elem(...) new (o_allocate(__VA_ARGS__)) __VA_ARGS__
#endif

namespace phantom {

    using reflection::Expression;
    using reflection::ConstantExpression;
    using reflection::LanguageElement;
    using reflection::Signature;
    using reflection::Namespace;
    using reflection::Block;
    using reflection::LocalVariable;
    using reflection::ArrayExpression;
    using reflection::Type;
    using reflection::ClassType;
    using reflection::Class;
    using reflection::Structure;
    using reflection::Precompiler;
    using reflection::LanguageElement;
    using reflection::StringLiteralExpression;
    using reflection::WStringLiteralExpression;
    using reflection::ConditionalExpression;
    using reflection::PlacementConstructionExpression;
    using reflection::InstanceDataMember;
    using reflection::Constructor;
    using reflection::AssignmentExpression;
    using reflection::InstanceDataMemberExpression;
    using reflection::AddressExpression;
    using reflection::CallExpression;
    using reflection::CastExpression;
    using reflection::MemberFunctionPointerCallExpression;
    using reflection::DataMemberPointerExpression;
    using reflection::MemberFunctionPointerType;
    using reflection::DataMemberPointerType;
    using reflection::Enum;
    using reflection::NumericConstant;
    using reflection::LabelStatement;
    using reflection::BranchIfStatement;
    using reflection::BranchIfNotStatement;
    using reflection::BranchStatement;
    using reflection::Constant;
    using reflection::Subroutine;
    using reflection::Statement;
    using reflection::ExpressionStatement;
    using reflection::ReturnStatement;
    using reflection::BinaryOperationExpression;
    using reflection::Parameter;
    using reflection::ReturnStatement;
    using reflection::ReturnStatement;
    using reflection::ReturnStatement;
    using reflection::ReturnStatement;
    using reflection::ReturnStatement;

#define YYSTYPE CxxTokenType
#define YY_parse_STYPE CxxTokenType
#define YACC_BANG_TYPE size_t
#define YACC_MARK_TYPE size_t

#define YACC_BANG() m_pDriver->getLexer()->push_bang()
#define YACC_UNBANG(bangValue, msg) m_pDriver->getLexer()->pop_bang(bangValue); yyerrok; yyclearin; yyerror(msg);

#define ERRMSG(a) do { std::cout << "error : syntax : " << a << std::endl; CxxDriver::Instance()->increment_error_count(); } while (0)

#define o_semantic_error(a)  do { if(CxxPrecompiler::Top()->hasFlag(CxxPrecompiler::e_Flag_PrintErrors)) std::cout << "error : semantic : " << a << std::endl;  CxxPrecompiler::Top()->increment_error_count(); } while (0)

#ifdef NEEDS_BOOL
enum bool { false, true };
#endif

#define PARSE_TOKEN(a) ::phantom::CxxParser::token::a

extern size_t line_number;
extern bool c_keywords;
extern bool echo_line_numbers;
extern bool echo_line_text;
extern int tokenMarkDepth;

struct CxxCharacterLiteral;
struct CxxStrings;
typedef CxxStrings CxxStringLiteral;

template<typename t_Ty>
struct CxxNumberLiteral;

struct CxxName;
struct CxxToken;

struct CxxToken
{
private:
    int malloced;
	int _value;
private:
	CxxToken(const CxxToken&);
	CxxToken& operator=(const CxxToken&);
public:
	CxxToken(int tokenValue = 0);
	virtual ~CxxToken();
	int value() const { return _value; }

public:
    static CxxToken* angleToken;
    static CxxToken* colonToken;
    static CxxToken* hashToken ;
    static CxxToken* plusToken ;
    static CxxToken* minusToken;
    static CxxToken* dollarToken;
    static CxxToken *asciiTokens[256];

    static CxxToken *yyToken;

    static CxxCharacterLiteral* make_character(const char *someText, size_t aLength);
    static CxxCharacterLiteral* make_narrow_character(const char *someText, size_t aLength);
    static CxxCharacterLiteral *make_wide_character(const char *someText, size_t aLength);

    static CxxStringLiteral* make_string(const char *someText, size_t aLength);
    static CxxStringLiteral* make_narrow_string(const char *someText, size_t aLength);
    static CxxStringLiteral* make_wide_string(const char *someText, size_t aLength);

    static CxxName*  make_identifier(const char *someText, size_t aLength);
    static CxxName*  make_keyword(int tokenValue, const char *someText, size_t aLength);
    static void      make_line(const char *yyText, size_t yyLeng);
    static CxxToken* make_literal_character(const char *someText, size_t aLength);
    static CxxNumberLiteral<ulonglong>* make_hex_number(const char *someText, size_t aLength);
    static CxxNumberLiteral<longdouble>* make_longdouble_number(const char *someText, size_t aLength);
    static CxxNumberLiteral<double>* make_double_number(const char *someText, size_t aLength);
    static CxxNumberLiteral<float>* make_float_number(const char *someText, size_t aLength);
    static CxxNumberLiteral<uint>* make_uint_number(const char *someText, size_t aLength);
    static CxxNumberLiteral<ulong>* make_ulong_number(const char *someText, size_t aLength);
    static CxxNumberLiteral<ulonglong>* make_ulonglong_number(const char *someText, size_t aLength);
    static CxxToken* get_ascii_token(size_t aCxxToken);
    static void Initialize(bool a_bInitialize);

    struct op_category
    {
        enum type
        {
            equality                    = 0x0001000,
            greater                     = 0x0002000,
            lesser                      = 0x0004000,
            shift                       = 0x0008000,
            additive                    = 0x0010000,
            multiplicative              = 0x0020000,
            member_pointer              = 0x0040000,
            reference                   = 0x0080000,
            unary_binary_logical        = 0x0100000,
            assignment_equality         = 0x0200000,
            assignment_shift            = 0x0400000,
            assignment_additive         = 0x0800000,
            assignment_multiplicative   = 0x1000000,
            assignment_binary_logical   = 0x2000000,
            inc_dec                     = 0x4000000,
            overloadable                = 0x8000000,
        };
    };

    struct op
    {
        enum type
        {
            // binary
            comma = 256,
            assign,
            plus_assign,
            minus_assign,
            times_assign,
            divide_assign,
            mod_assign,
            bit_and_assign,
            bit_xor_assign,
            bit_or_assign,
            shift_left_assign,
            shift_right_assign,
            logical_or,
            logical_and,
            bit_or,
            bit_xor,
            bit_and,
            equal,
            not_equal,
            less,
            less_equal,
            greater,
            greater_equal,
            shift_left,
            shift_right,
            plus,
            minus,
            times,
            divide,
            mod,
            dot,
            dot_star,
            minus_greater,
            minus_greater_star,

            // unary
            plus_plus,
            minus_minus,
            compl_,
            not_,
            arobase,
            question,

            brackets,
            parenthesis,
            left_paren    ,      
            right_paren   ,      
            left_bracket  ,      
            right_bracket ,      
            left_brace    ,      
            right_brace   ,      
            semi_colon    ,      
            colon         ,       
            double_colon  ,       
        };
    };

    enum type
    {
        // pseudo tags
        invalid             = -1,

        identifier          = 1,
        comment                ,
        whitespace             ,
        float_literal          ,
        double_literal         ,
        longdouble_literal     ,
        int_literal            ,
        uint_literal           ,
        long_literal           ,
        ulong_literal          ,
        longlong_literal       ,
        ulonglong_literal      ,
        hex_ulonglong_literal      ,
        string_literal          ,
        char_literal            ,
        true_or_false           ,
        first_keyword_id        ,
        // binary / unary operators with common tokens
        // '+' and '-' can be binary or unary
        // (the lexer cannot distinguish which)
        plus                = op::plus | op_category::additive | op_category::overloadable,
        minus               = op::minus| op_category::additive | op_category::overloadable,

        // binary operators   // binary operators       ,
        comma               = op::comma                 ,
        assign              = op::assign                | op_category::overloadable,
        plus_assign         = op::plus_assign           | op_category::assignment_additive | op_category::overloadable,
        minus_assign        = op::minus_assign          | op_category::assignment_additive | op_category::overloadable,
        times_assign        = op::times_assign          | op_category::assignment_multiplicative | op_category::overloadable,
        divide_assign       = op::divide_assign         | op_category::assignment_multiplicative | op_category::overloadable,
        mod_assign          = op::mod_assign            | op_category::assignment_multiplicative | op_category::overloadable,
        bit_and_assign      = op::bit_and_assign        | op_category::assignment_binary_logical | op_category::overloadable,
        bit_xor_assign      = op::bit_xor_assign        | op_category::assignment_binary_logical | op_category::overloadable,
        bit_or_assign       = op::bit_or_assign         | op_category::assignment_binary_logical | op_category::overloadable,
        shift_left_assign   = op::shift_left_assign     | op_category::assignment_shift | op_category::overloadable,
        shift_right_assign  = op::shift_right_assign    | op_category::assignment_shift | op_category::overloadable,
        logical_or          = op::logical_or            | op_category::overloadable,
        logical_and         = op::logical_and           | op_category::overloadable,
        bit_or              = op::bit_or                | op_category::overloadable,
        bit_xor             = op::bit_xor               | op_category::overloadable,
        bit_and             = op::bit_and               | op_category::reference | op_category::overloadable,
        equal               = op::equal                 | op_category::equality | op_category::overloadable,
        not_equal           = op::not_equal             | op_category::equality | op_category::overloadable,
        less                = op::less                  | op_category::lesser | op_category::overloadable,
        less_equal          = op::less_equal            | op_category::lesser | op_category::overloadable,
        greater             = op::greater               | op_category::greater | op_category::overloadable,
        greater_equal       = op::greater_equal         | op_category::greater | op_category::overloadable,
        shift_left          = op::shift_left            | op_category::shift | op_category::overloadable,
        shift_right         = op::shift_right           | op_category::shift | op_category::overloadable,
        times               = op::times                 | op_category::multiplicative | op_category::overloadable,
        divide              = op::divide                | op_category::multiplicative | op_category::overloadable,
        mod                 = op::mod                   | op_category::multiplicative | op_category::overloadable,
        dot                 = op::dot                   ,
        dot_star            = op::dot_star              ,
        minus_greater       = op::minus_greater         | op_category::member_pointer | op_category::overloadable,
        minus_greater_star  = op::minus_greater_star    | op_category::member_pointer | op_category::overloadable,

        // unary operators wit// unary operators w      ,
        // '++' and '--' can b// '++' and '--' can      ,
        // (the lexer cannot d// (the lexer cannot      ,
        plus_plus           = op::plus_plus             | op_category::inc_dec | op_category::overloadable,
        minus_minus         = op::minus_minus           | op_category::inc_dec | op_category::overloadable,

        // unary operators    // unary operators        ,
        compl_              = op::compl_                | op_category::unary_binary_logical | op_category::overloadable,
        not_                = op::not_                  | op_category::unary_binary_logical | op_category::overloadable,

        brackets            = op::brackets              | op_category::overloadable,
        parenthesis         = op::parenthesis           | op_category::overloadable,
        arobase             = op::arobase               | op_category::reference,
        question            = op::question              ,

        left_paren          = op::left_paren            ,
        right_paren         = op::right_paren           ,

        left_bracket        = op::left_bracket          ,
        right_bracket       = op::right_bracket         ,

        left_brace          = op::left_brace            ,
        right_brace         = op::right_brace           ,
        semi_colon          = op::semi_colon            ,
        colon               = op::colon                 ,
        double_colon        = op::double_colon            ,
        // misc tags                                    ,
    };

    static const string& operator_string_from_token_id(size_t token_id);
};

enum CxxIsTemplate { IS_DEFAULT, IS_TEMPLATE };
enum CxxIsTree { IS_SCALAR, IS_TREE };

/// EXPRESSIONS

struct CxxClassKey;
struct CxxCaseStatement;
struct CxxStatements;
struct CxxName;

typedef CxxName CxxDeclSpecifierId;
typedef CxxName CxxCvQualifiers;
typedef CxxName CxxKeyword;

struct CxxStatement : public CxxToken 
{
    CxxStatement(int tokenValue = 0) : CxxToken(tokenValue), classKey(nullptr), declSpecifier(nullptr) {}
    CxxClassKey *classKey;
    CxxDeclSpecifierId *declSpecifier;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr) = 0;
    virtual CxxStatements* asStatements() { return nullptr; }
    virtual CxxCaseStatement* asCaseStatement() { return nullptr; }
};

struct CxxName;

struct CxxLabelStatement : public CxxStatement
{
    CxxLabelStatement(CxxName *aLabel, CxxStatement *aStmt) 
        : label(aLabel), statement(aStmt) {}
    CxxName* label;
    CxxStatement* statement;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);

};

struct CxxStatements;

struct CxxBlock : public CxxStatement
{
    CxxBlock(CxxStatements* aStatements) : statements(aStatements) {}
    CxxStatements* statements;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};

struct CxxName;

struct CxxGotoStatement : public CxxStatement
{
    CxxGotoStatement(CxxName* l) : label(l) {}

    CxxName* label;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};

struct CxxCondition;

struct CxxIfStatement : public CxxStatement
{
    CxxIfStatement(CxxCondition *testExpr, CxxStatement *trueStmt, CxxStatement *falseStmt) 
        : test(testExpr), thenContent(trueStmt), elseContent(falseStmt)
    {

    }
    CxxCondition* test;
    CxxStatement* thenContent;
    CxxStatement* elseContent;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};

struct CxxExpression;

struct CxxDoWhileStatement : public CxxStatement
{
    CxxDoWhileStatement(CxxStatement *s, CxxExpression *e) : statement(s), testExpr(e) {}
    CxxStatement* statement;
    CxxExpression* testExpr;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};

struct CxxParameters;
typedef CxxDeclSpecifierId CxxCvQualifiers;
struct CxxExceptionSpecification;

struct CxxParenthesised : public CxxToken 
{
    CxxParenthesised(CxxParameters *aList, CxxCvQualifiers *cvQualifiers, CxxExceptionSpecification *exceptionSpecification)
        : parameters(aList), cvs(cvQualifiers), exceptionSpec(exceptionSpecification) {}

    CxxParameters* parameters;
    CxxCvQualifiers* cvs;
    CxxExceptionSpecification* exceptionSpec;

    virtual void precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, vector<LanguageElement*>& out, modifiers_t* modifiers = nullptr);
};

struct CxxExpression : public CxxStatement 
{
    CxxExpression(int tokenValue = 0) : CxxStatement(tokenValue) {}
    virtual CxxName* asName() { return nullptr; }
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr) = 0;
    virtual LanguageElement* precompileParenthesized(Precompiler* a_pPrecompiler, CxxParenthesised* a_pParen, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
    virtual LanguageElement* precompileTypedParenthesized(Precompiler* a_pPrecompiler, Type* a_pType, CxxParenthesised* a_pParen, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr) { return nullptr; }
    Expression* precompileExpression(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr)
    {
        LanguageElement* pElem = precompile(a_pPrecompiler, a_pScope, a_pLHS);
        return pElem ? pElem->asExpression() : nullptr;
    }
    Type* precompileType(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr)
    {
        LanguageElement* pElem = precompile(a_pPrecompiler, a_pScope, a_pLHS);
        return pElem ? pElem->asType() : nullptr;
    }
    Namespace* precompileNamespace(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr)
    {
        LanguageElement* pElem = precompile(a_pPrecompiler, a_pScope, a_pLHS);
        return pElem ? pElem->asNamespace() : nullptr;
    }
    LanguageElement* precompileTemplateElement(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr)
    {
        LanguageElement* pElem = precompile(a_pPrecompiler, a_pScope, a_pLHS);
        return pElem;
    }
    Constructor* precompileConstructor(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr)
    {
        LanguageElement* pElem = precompile(a_pPrecompiler, a_pScope, a_pLHS);
        return pElem ? pElem->asConstructor() : nullptr;
    }
    Constant* precompileConstant(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr)
    {
        LanguageElement* pElem = precompile(a_pPrecompiler, a_pScope, a_pLHS);
        return pElem ? pElem->asConstant() : nullptr;
    }
    virtual string toString() const { return "<no text>"; }
};

struct CxxConditionalExpression : public CxxExpression
{
    CxxConditionalExpression(CxxExpression *testExpr, CxxExpression *trueExpr, CxxExpression *falseExpr) 
        : test(testExpr), thenExpr(trueExpr), elseExpr(falseExpr) {}
    CxxExpression* test;
    CxxExpression* thenExpr;
    CxxExpression* elseExpr;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */)
    {
        return o_new_elem(ConditionalExpression)(test->precompileExpression(a_pPrecompiler, a_pScope), thenExpr->precompileExpression(a_pPrecompiler, a_pScope), elseExpr->precompileExpression(a_pPrecompiler, a_pScope));
    }
};

struct CxxCondition : public CxxExpression 
{
    CxxCondition(CxxParameters* aParameters)
        : parameters(aParameters) {}
    CxxParameters* parameters;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};

struct CxxGlobalExpression : public CxxExpression
{
    CxxGlobalExpression(bool aIsTemplate, CxxExpression* anExpr)
        : isTemplate(aIsTemplate), expr(anExpr) {}
    bool isTemplate;
    CxxExpression* expr;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */)
    {
        if(!isTemplate)
        {
            return expr->precompile(a_pPrecompiler, a_pScope, a_pLHS);
        }
        o_assert(false);
        return nullptr;
    }
};

struct CxxFunctionBody;

struct CxxFunctionDefinition : public CxxExpression
{
    CxxFunctionDefinition(CxxExpression *anExpr, CxxFunctionBody *functionBody)
        : header(anExpr), body(functionBody)
    {

    }
    CxxExpression* header;
    CxxFunctionBody* body;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */)
    {
        o_assert(false);
        return nullptr;
    }
};

struct CxxTemplateArguments;

struct CxxName : public CxxExpression 
{
    virtual CxxName* asName() { return this; }
    struct word
    {
        word(const string& i, CxxTemplateArguments* t = nullptr)
            : id(i), templateArgs(t) {}
        string id; 
        CxxTemplateArguments* templateArgs;
        bool operator==(const char* str) const 
        {
            return id == str AND templateArgs == nullptr;
        }
        bool operator!=(const char* str) const 
        {
            return !operator==(str);
        }
    };

    CxxName() : isTemplate(false) { }
    CxxName(int tokenValue, const char* someText, size_t len)  : CxxExpression(tokenValue), isTemplate(false) { words.push_back(word(string(someText, len))); }
    CxxName(CxxDeclSpecifierId* declSpec) : isTemplate(false) { declSpecifier = declSpec; } 
    CxxName(const string& i, bool aIsTemplate = false) 
        : isTemplate(aIsTemplate) 
    {
        words.push_back(word(i));
    }

    ~CxxName()
    {
    }

    CxxName* takeBack() 
    {
        if(size() == 0) return nullptr;
        CxxName* pBack = new CxxName(words.back());
        words.pop_back();
        return pBack;
    }

    vector<word>::const_iterator begin() const { return words.begin(); }
    vector<word>::const_iterator end() const { return words.end(); }
    vector<word>::const_reverse_iterator rbegin() const { return words.rbegin(); }
    vector<word>::const_reverse_iterator rend() const { return words.rend(); }

    size_t size() const { return words.size(); }

    void append(const string& name, CxxTemplateArguments* templateArgs = nullptr)
    {
        words.push_back(word(name, templateArgs));
    }

    void setLastTemplateArguments(CxxTemplateArguments* templateArgs)
    {
        words.back().templateArgs = templateArgs;
    }

    CxxTemplateArguments* getLastTemplateArguments() const
    {
        return words.back().templateArgs;
    }

    void swallow(CxxName* name)
    {
        for(auto it = name->words.begin(); it != name->words.end(); ++it)
        {
            words.push_back(*it);
        }
        // delete name;
    }

    const string& asIdentifier() const
    {
        static string null_str;
        if(size() == 1 AND words.front().templateArgs == 0)
        {
            return words.front().id;
        }
        return null_str;
    }

    virtual string toString() const;

    Type* specify(Type* a_pType, modifiers_t* modifiers = 0);

    vector<word> words;
    bool isTemplate;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
    virtual LanguageElement* precompileParenthesized(Precompiler* a_pPrecompiler, CxxParenthesised* aParenthesised, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
    virtual LanguageElement* precompileTypedParenthesized(Precompiler* a_pPrecompiler, Type* a_pType, CxxParenthesised* a_pParen, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
    string toNamespaceQualifiedName() const;

protected:
    CxxName(const word& w) : isTemplate(false) { words.push_back(w); } 

};

struct CxxDotExpression : public CxxExpression
{
    CxxDotExpression(CxxExpression *aLeft, CxxName *aMember)
        : left(aLeft), member(aMember) {}
    CxxExpression *left;
    CxxName *member;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
    virtual LanguageElement* precompileParenthesized( Precompiler* a_pPrecompiler, CxxParenthesised* a_pParams, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ );
};

struct CxxArrowExpression : public CxxExpression
{
    CxxArrowExpression(CxxExpression *aLeft, CxxName *aMember)
        : left(aLeft), member(aMember) {}
    CxxExpression *left;
    CxxName *member;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
    virtual LanguageElement* precompileParenthesized( Precompiler* a_pPrecompiler, CxxParenthesised* a_pParams, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ );
};

struct CxxDotStarExpression : public CxxExpression
{
    CxxDotStarExpression(CxxExpression *aLeft, CxxExpression *aMember)
        : left(aLeft), member(aMember) {}
    CxxExpression *left;
    CxxExpression *member;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
    virtual LanguageElement* precompileParenthesized( Precompiler* a_pPrecompiler, CxxParenthesised* a_pParams, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ );
};

struct CxxArrowStarExpression : public CxxExpression
{
    CxxArrowStarExpression(CxxExpression *aLeft, CxxExpression *aMember)
        : left(aLeft), member(aMember) {}
    CxxExpression *left;
    CxxExpression *member;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
    virtual LanguageElement* precompileParenthesized( Precompiler* a_pPrecompiler, CxxParenthesised* a_pParams, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ );
};


struct CxxCallExpression : public CxxExpression 
{
    CxxCallExpression(CxxExpression* e, CxxParenthesised* p) : expr(e), parenthesised(p) {}
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
    CxxExpression* expr;
    CxxParenthesised* parenthesised;
};

struct CxxPreUnaryExpression : public CxxExpression
{
    CxxPreUnaryExpression(const string& o, CxxExpression* e) : op(o), expr(e) { o_assert(expr); }
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr) 
    {
        Expression* expr = this->expr->precompileExpression(a_pPrecompiler, a_pScope);
        return expr->precompilePreUnaryOperator(a_pPrecompiler, op);
    }
    string op;
    CxxExpression* expr;
};

struct CxxPostUnaryExpression : public CxxExpression
{
    CxxPostUnaryExpression(const string& o, CxxExpression* e) : op(o), expr(e) { o_assert(expr); }
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr) 
    {
        Expression* expr = this->expr->precompileExpression(a_pPrecompiler, a_pScope);
        return expr ? expr->precompileBinaryOperator(a_pPrecompiler, op, nullptr) : 0;
    }
    string op;
    CxxExpression* expr;
};

struct CxxInvalidExpression : CxxExpression
{
    CxxInvalidExpression(CxxExpression* e = nullptr) : expr(e) {}
    CxxExpression* expr;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */){return nullptr;}
};

struct CxxBinaryExpression : public CxxExpression 
{
    CxxBinaryExpression(const string& o, CxxExpression* l, CxxExpression* r) : op(o), left(l), right(r) 
    {
        o_assert(left AND right);
    }
    string op;
    CxxExpression* left;
    CxxExpression* right;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
};

struct CxxArrayAccessExpression : public CxxExpression
{
    CxxArrayAccessExpression(CxxExpression* e, CxxExpression* i) 
        : expression(e), index(i) {} 
    CxxExpression* expression;
    CxxExpression* index;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS);
};

struct CxxCastExpression : public CxxExpression 
{
    CxxCastExpression(CxxExpression* t, CxxExpression* e)
        : type(t), expr(e) {}
    CxxExpression* type;
    CxxExpression* expr;
};

struct CxxCStyleCastExpression : public CxxCastExpression 
{
    CxxCStyleCastExpression(CxxExpression* t, CxxExpression* e) : CxxCastExpression(t, e) {}

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};
struct CxxReinterpretCastExpression : public CxxCastExpression 
{
    CxxReinterpretCastExpression(CxxExpression* t, CxxExpression* e) : CxxCastExpression(t, e) {}

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};
struct CxxStaticCastExpression : public CxxCastExpression 
{
    CxxStaticCastExpression(CxxExpression* t, CxxExpression* e) : CxxCastExpression(t, e) {}

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};
struct CxxConstCastExpression : public CxxCastExpression 
{
    CxxConstCastExpression(CxxExpression* t, CxxExpression* e) : CxxCastExpression(t, e) {}

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};

struct CxxConversionFunction : public CxxName
{
    CxxConversionFunction(CxxExpression* anExpr) 
        : expr(anExpr)
    {
   
    }
    CxxExpression* expr;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */)
    {
        return expr->precompileType(a_pPrecompiler, a_pScope);
    }
};

struct CxxStringLiteralExpression : public CxxExpression
{
    CxxStringLiteralExpression(CxxStringLiteral* l) : stringLiteral(l) {}
    CxxStringLiteral* stringLiteral;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};

struct CxxDeclarator;

struct CxxScopedPointerExpression : public CxxExpression
{
    CxxScopedPointerExpression(CxxExpression *aScope, CxxDeclarator *aDeclarator, CxxExpression *anExpr) 
        : scope(aScope), declarator(aDeclarator), expr(anExpr)
    {

    }
    CxxExpression *scope;
    CxxDeclarator *declarator;
    CxxExpression *expr;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};

struct CxxSizeOfExpression : public CxxExpression
{
    CxxSizeOfExpression(CxxExpression* anExpr)
        : expr(anExpr)
    {

    }
    CxxExpression* expr;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr)
    {
        o_assert(a_pLHS == nullptr);
        Expression* pExpr = expr->precompileExpression(a_pPrecompiler, a_pScope);
        return o_new_elem(ConstantExpression)(constant<size_t>(pExpr->getValueType()->getSize()), pExpr);
    }
};

struct CxxVariableDeclarationExpression : public CxxExpression
{
    CxxVariableDeclarationExpression(CxxExpression* aTypeExpression, CxxDeclarator* aDeclarator, CxxExpression* aNameExpression)
        : typeExpression(aTypeExpression), declarator(aDeclarator), nameExpression(aNameExpression) {}
    CxxExpression* typeExpression;
    CxxDeclarator* declarator;
    CxxExpression* nameExpression;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};

struct CxxTypeIdExpression : public CxxExpression
{
    CxxTypeIdExpression(CxxExpression* anExpr)
        : expr(anExpr)
    {

    }
    CxxExpression* expr;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr)
    {
        o_assert(a_pLHS == nullptr);
        Expression* pExpr = expr->precompileExpression(a_pPrecompiler, a_pScope);
        return o_new_elem(ConstantExpression)(constant<size_t>(pExpr->getValueType()->getSize()), pExpr);
    }
};

struct CxxTokens : public CxxToken {};

struct CxxType1Parameters : public CxxTokens 
{
    void add(CxxParameters* params) { list.push_back(params); }
    vector<CxxParameters*> list;
};

struct CxxType1Expression : public CxxExpression
{
    CxxType1Expression(CxxExpression *afunctionName, CxxParenthesised *aParenthesis, CxxType1Parameters *atype1Parameters)
        : functionName(afunctionName), parenthesis(aParenthesis), type1Parameters(atype1Parameters)
    {

    }
    CxxExpression *functionName;
    CxxParenthesised *parenthesis;
    CxxType1Parameters *type1Parameters;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */)
    {
        LanguageElement* pCall = functionName->precompileParenthesized(a_pPrecompiler, parenthesis, a_pScope, a_pLHS);
        o_assert_no_implementation();
        return nullptr;
    }
};

struct CxxCharacterLiteral : public CxxToken 
{
    CxxCharacterLiteral(char c);
    CxxCharacterLiteral(wchar_t c);
    int chr;
    size_t size;
};

template<typename t_Ty>
struct CxxNumberLiteral : public CxxToken
{
    CxxNumberLiteral(int tokenValue, t_Ty n) 
        : CxxToken(tokenValue)
        , number(n) 
    {

    }
    t_Ty number;
};

struct CxxCharacterLiteralExpression : public CxxExpression 
{
    CxxCharacterLiteralExpression(CxxCharacterLiteral* c) : character(c) {}
    CxxCharacterLiteral* character;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */)
    {
        if(character->size == 1)
        {
            return o_new_elem(ConstantExpression)(constant<char>((char)character->chr));
        }
        return o_new_elem(ConstantExpression)(constant<wchar_t>((wchar_t)character->chr));
    }
};


template<typename t_Ty>
struct CxxUnderlyingFundamental { typedef t_Ty type; };

template<>
struct CxxUnderlyingFundamental<hex_t> { typedef unsigned long long type; };

template<typename t_Ty>
struct CxxNumberLiteralExpression : public CxxExpression
{
    CxxNumberLiteralExpression(CxxNumberLiteral<t_Ty>* n) : literal(n) {}
    CxxNumberLiteral<t_Ty>* literal;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */)
    {
        return o_new_elem(ConstantExpression)(constant<o_NESTED_TYPE CxxUnderlyingFundamental<t_Ty>::type>(literal->number));
    }
};

struct CxxTypedExpression : public CxxExpression 
{
    CxxTypedExpression(CxxName* n, CxxExpression* e) : name(n), expr(e) {}
    CxxName* name;
    CxxExpression* expr;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
    virtual LanguageElement* precompileParenthesized(Precompiler* a_pPrecompiler, CxxParenthesised* a_pParen, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};

struct CxxThisExpression : public CxxExpression 
{
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr)
    {
        Block* pBlock = a_pScope->asBlock();
        if(pBlock == nullptr)
            return nullptr;
        LocalVariable* pLocalVariable = pBlock->getLocalVariableCascade("this");
        if(pLocalVariable == nullptr)
            return nullptr;
        return pLocalVariable->createExpression();
    }
};

struct CxxThrowExpression : public CxxExpression
{
    CxxThrowExpression(CxxExpression* anExpr) : expr(anExpr) {}
    CxxExpression* expr;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */)
    {
        o_assert_no_implementation();
        return nullptr;
        //return o_new_elem(ThrowExceptionExpression)(anExpr);
    }
};

struct CxxBitfieldExpression : public CxxExpression 
{ 
    CxxBitfieldExpression(CxxExpression *nameExpr, CxxExpression *sizeExpr) 
        :expr(nameExpr)
        , size(sizeExpr)
    {
    }
    CxxExpression* expr;
    CxxExpression* size;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};
struct CxxAbstractArrayExpression : public CxxExpression 
{ 
    CxxAbstractArrayExpression(CxxExpression* anExpr) : expr(anExpr) {} 
    CxxExpression* expr; 
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */)
    {
        return nullptr;
    }
};
struct CxxAbstractFunctionExpression : public CxxExpression 
{ 
    CxxAbstractFunctionExpression(CxxParenthesised* p) : parenthesised(p) {} 
    CxxParenthesised* parenthesised; 
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};

struct CxxWhileStatement : public CxxStatement 
{
    CxxWhileStatement(CxxCondition *aTestExpr, CxxStatement *aStmt) 
        : testExpr(aTestExpr), statement(aStmt) {}
    CxxCondition *testExpr;
    CxxStatement *statement;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);

};
struct CxxForStatement : public CxxStatement 
{
    CxxForStatement(CxxExpression *initExpr, CxxCondition *testExpr, CxxExpression *stepExpr, CxxStatement *aStmt) 
        : init(initExpr), test(testExpr), step(stepExpr), content(aStmt)
    {

    }
    CxxExpression* init;
    CxxCondition* test;
    CxxExpression* step;
    CxxStatement* content;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};
struct CxxSwitchStatement : public CxxStatement 
{
    CxxSwitchStatement(CxxCondition *aTestExpr, CxxStatement *aStmt) 
        : testExpr(aTestExpr), statement(aStmt) {}
    CxxCondition *testExpr;
    CxxStatement *statement;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};
struct CxxTryBlockStatement : public CxxStatement 
{
    CxxTryBlockStatement(CxxFunctionBody *aTryBlock) : tryBlock(aTryBlock)    {    }
    CxxFunctionBody *tryBlock;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};
struct CxxCaseStatement : public CxxStatement 
{
    CxxCaseStatement(CxxExpression *anExpr, CxxStatement *aStmt) 
        : expr(anExpr), statement(aStmt) {}
    virtual CxxCaseStatement* asCaseStatement() { return this; }
    virtual Expression* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */)
    {
        o_assert(false, "should not be precompiled directly");
        return nullptr;
    }
    CxxExpression *expr;
    CxxStatement *statement;
};

struct CxxDefaultStatement : public CxxCaseStatement
{
    CxxDefaultStatement(CxxStatement* aStmt) : CxxCaseStatement(nullptr, aStmt) {}
};

typedef CxxStatement CxxDeclaration;

struct CxxUsingDeclaration : public CxxDeclaration
{
    CxxUsingDeclaration(bool aIsTypename, CxxName *aName) 
        : isTypename(aIsTypename), name(aName) {}
    bool isTypename;
    CxxName *name;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};

struct CxxSimpleDeclaration : public CxxDeclaration
{
    CxxSimpleDeclaration(CxxExpression* e) : expr(e) {}
    CxxExpression* expr;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};

struct CxxNamespaceAliasDeclaration : public CxxDeclaration
{
    CxxNamespaceAliasDeclaration(CxxName *aName, CxxName *forId)
        : name(aName), alias(forId) {}
    CxxName *name;
    CxxName *alias;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};

struct CxxTemplateParameters;

struct CxxTemplateDeclaration : public CxxDeclaration
{
    CxxTemplateDeclaration(CxxTemplateParameters *aList, CxxDeclaration *aDeclaration) 
        : parameters(aList), declaration(aDeclaration) {}
    CxxTemplateParameters* parameters;
    CxxDeclaration* declaration;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};

struct CxxUsingNamespaceDirective : public CxxDeclaration 
{
    CxxUsingNamespaceDirective(CxxName* aName) : name(aName) {}
    CxxName* name;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};
struct CxxReturnStatement : public CxxStatement 
{ 
    CxxReturnStatement(CxxExpression* anExpr) 
        : expr(anExpr) {} 
    CxxExpression* expr; 
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};

struct CxxAccessSpecifier;

struct CxxAccessibilitySpecifier : public CxxDeclaration 
{
    CxxAccessibilitySpecifier(CxxAccessSpecifier* spec) : specifier(spec) {}
    CxxAccessSpecifier* specifier;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
};
struct CxxBreakStatement : public CxxStatement 
{
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};
struct CxxContinueStatement : public CxxStatement 
{
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};
struct CxxStrings;
struct CxxAsmDefinition : public CxxDeclaration 
{ 
    CxxAsmDefinition(CxxStrings* strings) 
        : code(strings) {} 
    CxxStrings* code;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */)
    {
        o_assert_no_implementation();
        return nullptr;
    }
};
struct CxxStatements : public CxxStatement 
{
    virtual CxxStatements* asStatements() { return this; }
    void add(CxxStatement* aStatement) 
    {
        o_assert(aStatement);
        list.push_back(aStatement); 
    }
    vector<CxxStatement*> list;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr)
    {
        for(auto it = list.begin(); it != list.end(); ++it)
        {
            (*it)->precompile(a_pPrecompiler, a_pScope);
        }
        return nullptr;
    }
};
typedef CxxStatements CxxDeclarations;
typedef CxxExpression CxxTreeExpression;

struct CxxNamespaceDefinition : public CxxName
{
    CxxNamespaceDefinition(CxxName *aName, CxxDeclarations *decls)
        : name(aName), declarations(decls) {}
    CxxName *name;
    CxxDeclarations *declarations;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr )
    {
        Namespace* pParent = a_pScope->asNamespace();
        Namespace* pNamespace = pParent->findOrCreateNamespaceCascade(name->toNamespaceQualifiedName());
        if(pNamespace == nullptr) return nullptr;

        declarations->precompile(a_pPrecompiler, pNamespace);

        return pNamespace;
    }
};

struct CxxNamespaceDeclaration : public CxxDeclaration
{
    CxxNamespaceDeclaration(CxxNamespaceDefinition* nd) : definition(nd) {}
    CxxNamespaceDefinition* definition;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS)
    {
        return definition->precompile(a_pPrecompiler, a_pScope);
    }
};

struct CxxAccessSpecifier : public CxxKeyword 
{
    void precompile(modifiers_t& modifiers);
};
struct CxxBaseSpecifier : public CxxToken 
{ 
    CxxBaseSpecifier(CxxName* n) : name(n), isVirtual(false) {}
    CxxName* name;
    CxxAccessSpecifier* accessSpecifier;
    bool isVirtual;
    Class* precompile(Precompiler* a_pPrecompiler, Class* a_pDerivedClass, modifiers_t& modifiers);
};
struct CxxBaseSpecifiers : public CxxTokens 
{
    void add(CxxBaseSpecifier* anElem) { list.push_back(anElem); }
    vector<CxxBaseSpecifier*> list;

    void precompile(Precompiler* a_pPrecompiler, Class* a_pClass);

};
struct CxxBrace : public CxxToken {};

typedef CxxName CxxBuiltInId;

struct CxxClassKey : public CxxKeyword {};

struct CxxClass : public CxxToken 
{
    CxxClass(CxxClassKey *classKey, CxxName *aName, CxxBaseSpecifiers *baseSpecifiers) 
        : key(classKey), name(aName), baseClasses(baseSpecifiers) {}

    CxxClassKey* key;
    CxxName* name;
    CxxBaseSpecifiers* baseClasses;

    ClassType* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope);
};

struct CxxMemberDeclaration : public CxxStatement
{
    CxxMemberDeclaration(CxxStatement* decl) : declaration(decl) {}
    CxxStatement* declaration;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
};

struct CxxMemberDeclarations : public CxxTokens
{
    void add(CxxMemberDeclaration* anElem) { list.push_back(anElem); }
    vector<CxxMemberDeclaration*> list;
    void precompile(Precompiler* a_pPrecompiler, ClassType* a_pClassType);
};

struct CxxClassMembers : public CxxName
{
    CxxClassMembers(CxxClass *aClass, CxxMemberDeclarations *memberDeclarations) 
        : class_(aClass), members(memberDeclarations) {}

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);

    CxxClass* class_;
    CxxMemberDeclarations* members;
};

struct CxxDeclarator : public CxxToken 
{ 
    explicit CxxDeclarator(char c) 
        : name(new CxxName(new CxxDeclSpecifierId(string(&c, 1)))), isTemplate(false), isGlobal(false) {}  
    explicit CxxDeclarator(CxxName* n) 
        : name(n), isTemplate(false), isGlobal(false) 
    { 
    } 
    CxxName* name; 
    bool isTemplate;
    bool isGlobal;
};

struct CxxDeleteExpression : public CxxExpression
{
    CxxDeleteExpression(CxxExpression* anExpr) : expr(anExpr) {}
    CxxExpression* expr;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */)
    {
        // return o_new_elem(DeleteExpression)(expr->precompileExpression(a_pPrecompiler, a_pScope, a_pLHS));
        o_assert_no_implementation();
        return nullptr;
    }
};
//struct CxxDerived : public CxxToken {};
//struct CxxEnum : public CxxToken {};
struct CxxEnumerator : public CxxToken 
{
    CxxEnumerator(CxxName *aName, CxxExpression *anExpr) 
        : name(aName), expr(anExpr) {}
    CxxName* name;
    CxxExpression* expr;
    ConstantExpression* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope) const;
};
struct CxxEnumerators : public CxxTokens 
{
    void add(CxxEnumerator* anElement) { list.push_back(anElement); }
    vector<CxxEnumerator*> list;
    Type* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, vector<NumericConstant*>& constants);
};
struct CxxEnumSpecifierId : public CxxName
{
    CxxEnumSpecifierId(CxxName* aName, CxxEnumerators* aEnumerators)
        : name(aName), enumerators(aEnumerators)
    {

    }
    CxxName* name;
    CxxEnumerators* enumerators;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS );
};
struct CxxParameter;
struct CxxExceptionDeclaration : public CxxToken 
{
    CxxExceptionDeclaration(CxxParameter *aParameter) : parameter(aParameter) {}
    CxxParameter* parameter;
};
struct CxxExceptionSpecification : public CxxToken 
{
    CxxExceptionSpecification(CxxExpression* anExpr) : expr(anExpr) {}
    CxxExpression* expr;
};
struct CxxExpressions : public CxxExpression 
{
    void add(CxxExpression* expr)
    {
        list.push_back(expr);
    }
    vector<CxxExpression*> list;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};
struct CxxFileId : public CxxToken {};
struct CxxFileIds : public CxxTokens {};
struct CxxFileName : public CxxToken {};
struct CxxFloatingLiteral : public CxxToken {};
struct CxxFunctionBody : public CxxStatement 
{
    CxxFunctionBody(CxxStatement* aStatement)
        : statement(aStatement) {}
    CxxStatement* statement;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */);
};

struct CxxConstructorDefinition : public CxxExpression
{
    CxxConstructorDefinition(CxxExpressions *anExprs, CxxFunctionBody *aFunctionBody) 
        : exprs(anExprs), functionBody(aFunctionBody)
    {

    }
    CxxExpressions* exprs;
    CxxFunctionBody* functionBody;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */)
    {
        CxxBitfieldExpression* first = static_cast<CxxBitfieldExpression*>(exprs->list.front());
        Constructor* pConstructor = first->expr->precompileConstructor(a_pPrecompiler, a_pScope);
        Block* pBlock = pConstructor->createBlock();
        exprs->precompile(a_pPrecompiler, pBlock->getLocalVariable("this"), nullptr);
        return pConstructor;
    }
};

struct CxxHandlers;

struct CxxTryFunctionBlock : public CxxFunctionBody 
{
    CxxTryFunctionBlock(CxxFunctionBody *aFunctionBody, CxxHandlers *aExceptionHandlers)
        : CxxFunctionBody(aFunctionBody), exceptionHandlers(aExceptionHandlers) {}
    CxxHandlers *exceptionHandlers;
};

struct CxxTryBlock : public CxxFunctionBody 
{
    CxxTryBlock(CxxStatement *aStatement, CxxHandlers *aExceptionHandlers)
        : CxxFunctionBody(aStatement), exceptionHandlers(aExceptionHandlers) {}
    CxxHandlers *exceptionHandlers;
};
struct CxxFunctionDeclarations : public CxxDeclarations {};
struct CxxHandler : public CxxToken 
{
    CxxHandler(CxxExceptionDeclaration *exceptionDeclaration, CxxStatement *aStatement) 
        : declaration(exceptionDeclaration), content(aStatement)
    {

    }
    CxxExceptionDeclaration* declaration;
    CxxStatement* content;
};
struct CxxHandlers : public CxxTokens 
{
    void add(CxxHandler* handler) { list.push_back(handler); }
    vector<CxxHandler*> list;
};
struct CxxIdentifier : public CxxName {};
//struct CxxIds : public CxxTokens {};
struct CxxInitializerClause : public CxxExpression 
{
    CxxInitializerClause(CxxExpression* e) : expr(e) {}
    CxxExpression* expr;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */)
    {
        return expr->precompile(a_pPrecompiler, a_pScope, a_pLHS);
    }
};
struct CxxInitializerClauses : public CxxInitializerClause 
{
    CxxInitializerClauses() : CxxInitializerClause(nullptr) {}
    vector<CxxInitializerClause*> list;
    void add(CxxInitializerClause* ic) { list.push_back(ic); }
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */)
    {
        o_assert(false);
        return nullptr;
    }
};
struct CxxIntegerLiteral : public CxxToken {};
struct CxxLine : public CxxToken {};
struct CxxMemInitializer : public CxxToken 
{
    CxxMemInitializer(CxxName *aName, CxxExpression *anExpr) 
        : name(aName), expr(anExpr) {}
    CxxName* name;
    CxxExpression* expr;
};
struct CxxMemInitializers : public CxxTokens 
{
    void add(CxxMemInitializer* param)
    {
        list.push_back(param);
    }
    vector<CxxMemInitializer*> list;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */)
    {
        o_assert_no_implementation();
        return nullptr;
    }
};
struct CxxNamespace : public CxxToken {};
struct CxxNewExpression : public CxxExpression 
{
    CxxNewExpression(CxxExpression *aPlace, CxxExpression *aType, CxxExpression *anInit) 
        : place(aPlace), type(aType), init(anInit) {}
    CxxExpression* place;
    CxxExpression* type;
    CxxExpression* init;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */)
    {
        o_assert(false, "not implemented : need phantom::reflection::NewExpression class")
            return nullptr;
    }
};
struct CxxNewParenthesisExpression : public CxxNewExpression 
{
    CxxNewParenthesisExpression(CxxParameters *aPlace, CxxParameters *aType, CxxExpression *anInit);
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */)
    {
        o_assert(false, "not implemented : need phantom::reflection::NewExpression class")
            return nullptr;
    }
};

struct CxxParameter : public CxxExpression 
{
    CxxParameter(CxxExpression* anExpr) : expr(anExpr), init(0) {}
    CxxExpression* expr;
    CxxExpression* init;

    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
};

struct CxxVariadicParameter : public CxxParameter
{
    CxxVariadicParameter() : CxxParameter(nullptr) {}
};

struct CxxParameters : public CxxExpression 
{
    void add(CxxParameter* param)
    {
        o_assert(param);
        list.push_back(param);
    }
    vector<CxxParameter*> list;
    virtual LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */)
    {
        o_assert(false);
        return Signature::Create();
    }
};
struct CxxPointerDeclarator : public CxxDeclarator 
{
    CxxPointerDeclarator() : CxxDeclarator('*') {}
};
struct CxxPosition : public CxxName {};
struct CxxSegment : public CxxName {};
struct CxxSpacing : public CxxToken {};

struct CxxStrings : public CxxToken 
{
    CxxStrings(const char* someText, size_t len, bool awide = false);
    ~CxxStrings() { if(wide) delete wstr; else delete str; }
    union { string* str; wstring* wstr; };
    string literal;
    bool wide;
};
struct CxxSubspace : public CxxToken {};
struct CxxSyntaxMacroParameter : public CxxToken {};
struct CxxSyntaxMacroParameters : public CxxTokens {};
struct CxxTemplateArgument : public CxxToken 
{
    CxxTemplateArgument(CxxParameter *aParameter) 
        : parameter(aParameter) {}
    CxxParameter* parameter;

    LanguageElement* precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope)
    {
        return parameter->expr->precompileTemplateElement(a_pPrecompiler, a_pScope);
    }
    virtual string toString() const
    {
        return parameter->toString();
    }
};

struct CxxTemplateArguments : public CxxTokens 
{
    void add(CxxTemplateArgument* arg) { list.push_back(arg); }
    void precompile(Precompiler* a_pPrecompiler, LanguageElement* a_pScope, vector<LanguageElement*>& out)
    {
        for(auto it = list.begin(); it != list.end(); ++it)
        {
            out.push_back((*it)->precompile(a_pPrecompiler, a_pScope));
        }
    }
    vector<CxxTemplateArgument*> list;
    virtual string toString() const;
};
struct CxxTemplateParameter : public CxxToken 
{
    CxxTemplateParameter(CxxExpression* e) : expr(e) {}
    CxxExpression* expr;
};
struct CxxTemplateParameters : public CxxTokens 
{
    void add(CxxTemplateParameter* arg) { list.push_back(arg); }
    vector<CxxTemplateParameter*> list;
};
struct CxxSimpleTypeParameter : public CxxTemplateParameter 
{
    CxxSimpleTypeParameter(CxxName* aName) : CxxTemplateParameter(aName) {} 
};
struct CxxClassTemplateParameter : public CxxSimpleTypeParameter 
{
    CxxClassTemplateParameter(CxxName *aName) : CxxSimpleTypeParameter(aName) {}
};
struct CxxClassTypeParameter : public CxxSimpleTypeParameter 
{
    CxxClassTypeParameter(CxxName *aName) : CxxSimpleTypeParameter(aName) {}
};
struct CxxTemplatedTypeParameter : public CxxTemplateParameter 
{
    CxxTemplatedTypeParameter(CxxTemplateParameters* aParameters, CxxName* aName)
        : CxxTemplateParameter(aName), parameters(aParameters)
    {

    }
    CxxTemplateParameters* parameters;
};
struct CxxTokenStatements : public CxxTokens {};
struct CxxTreeArguments : public CxxTokens {};
struct CxxTypeId : public CxxToken {};
struct CxxTypeIds : public CxxTokens {};
struct CxxUtility : public CxxToken {};

#define FOGPARSERVALUE_ENUM(T,N) \
	const T *name2(u_,N); \
	const T& N() const { return *name2(u_,N); } \
	const T* & N() { return name2(u_,N); }
#define FOGPARSERVALUE_POINTER(T,N) T *N;
#define FOGPARSERVALUE_VALUE(T,N) T N;

union CxxTokenType
{
	CxxToken *_token;

	FOGPARSERVALUE_VALUE(bool, _bool)
	FOGPARSERVALUE_VALUE(long, _long)
	FOGPARSERVALUE_POINTER(CxxBrace, brace)
	FOGPARSERVALUE_POINTER(CxxSpacing, spacing)

	FOGPARSERVALUE_POINTER(CxxAccessSpecifier, access_specifier)
	FOGPARSERVALUE_POINTER(CxxBaseSpecifier, base_specifier)
	FOGPARSERVALUE_POINTER(CxxBaseSpecifiers, base_specifiers)
	FOGPARSERVALUE_POINTER(CxxBuiltInId, built_in_id)
    FOGPARSERVALUE_POINTER(CxxCharacterLiteral, character_literal)
    FOGPARSERVALUE_POINTER(CxxNumberLiteral<hex_t>, hex_literal)
    FOGPARSERVALUE_POINTER(CxxNumberLiteral<long double>, longdouble_literal)
    FOGPARSERVALUE_POINTER(CxxNumberLiteral<double>, double_literal)
    FOGPARSERVALUE_POINTER(CxxNumberLiteral<float>, float_literal)
    FOGPARSERVALUE_POINTER(CxxNumberLiteral<uint>, uint_literal)
    FOGPARSERVALUE_POINTER(CxxNumberLiteral<ulong>, ulong_literal)
    FOGPARSERVALUE_POINTER(CxxNumberLiteral<ulonglong>, ulonglong_literal)
	FOGPARSERVALUE_POINTER(CxxClass, _class)
	FOGPARSERVALUE_POINTER(CxxClassKey, class_key)
	FOGPARSERVALUE_POINTER(CxxCondition, condition)
	FOGPARSERVALUE_POINTER(CxxCvQualifiers, cv_qualifiers)
	FOGPARSERVALUE_POINTER(CxxDeclSpecifierId, decl_specifier_id)
	FOGPARSERVALUE_POINTER(CxxDeclaration, declaration)
	FOGPARSERVALUE_POINTER(CxxDeclarations, declarations)
	FOGPARSERVALUE_POINTER(CxxDeclarator, declarator)
	FOGPARSERVALUE_POINTER(CxxDeleteExpression, delete_expression)
	FOGPARSERVALUE_POINTER(CxxEnumerator, enumerator)
	FOGPARSERVALUE_POINTER(CxxEnumerators, enumerators)
	FOGPARSERVALUE_POINTER(CxxExceptionDeclaration, exception_declaration)
	FOGPARSERVALUE_POINTER(CxxExceptionSpecification, exception_specification)
	FOGPARSERVALUE_POINTER(CxxExpression, expression)
	FOGPARSERVALUE_POINTER(CxxExpressions, expressions)
	FOGPARSERVALUE_POINTER(CxxFileId, file_id)
	FOGPARSERVALUE_POINTER(CxxFileIds, file_ids)
	FOGPARSERVALUE_POINTER(CxxFileName, file_name)
	FOGPARSERVALUE_POINTER(CxxFloatingLiteral, floating_literal)
	FOGPARSERVALUE_POINTER(CxxFunctionBody, function_body)
	FOGPARSERVALUE_POINTER(CxxHandler, handler)
	FOGPARSERVALUE_POINTER(CxxHandlers, handlers)
	FOGPARSERVALUE_POINTER(CxxIdentifier, identifier)
	FOGPARSERVALUE_POINTER(CxxInitializerClause, initializer_clause)
	FOGPARSERVALUE_POINTER(CxxInitializerClauses, initializer_clauses)
	FOGPARSERVALUE_POINTER(CxxIntegerLiteral, integer_literal)
	FOGPARSERVALUE_POINTER(CxxKeyword, keyword)
	FOGPARSERVALUE_POINTER(CxxLine, line)
	FOGPARSERVALUE_POINTER(CxxMemInitializer, mem_initializer)
    FOGPARSERVALUE_POINTER(CxxMemInitializers, mem_initializers)
    FOGPARSERVALUE_POINTER(CxxMemberDeclaration, member_declaration)
	FOGPARSERVALUE_POINTER(CxxMemberDeclarations, member_declarations)
	FOGPARSERVALUE_POINTER(CxxName, name)
	FOGPARSERVALUE_POINTER(CxxNewExpression, new_expression)
	FOGPARSERVALUE_POINTER(CxxParameter, parameter)
	FOGPARSERVALUE_POINTER(CxxParameters, parameters)
	FOGPARSERVALUE_POINTER(CxxParenthesised, parenthesised)
	FOGPARSERVALUE_POINTER(CxxPointerDeclarator, pointer_declarator)
	FOGPARSERVALUE_POINTER(CxxPosition, position)
	FOGPARSERVALUE_POINTER(CxxSegment, segment)
	FOGPARSERVALUE_POINTER(CxxSimpleTypeParameter, simple_type_parameter)
	FOGPARSERVALUE_POINTER(CxxStatement, statement)
	FOGPARSERVALUE_POINTER(CxxStatements, statements)
	FOGPARSERVALUE_POINTER(CxxStringLiteral, string_literal)
	FOGPARSERVALUE_POINTER(CxxStrings, strings)
	FOGPARSERVALUE_POINTER(CxxSubspace, subspace)
	FOGPARSERVALUE_POINTER(CxxSyntaxMacroParameter, syntax_macro_parameter)
	FOGPARSERVALUE_POINTER(CxxSyntaxMacroParameters, syntax_macro_parameters)
	FOGPARSERVALUE_POINTER(CxxTemplateArgument, template_argument)
	FOGPARSERVALUE_POINTER(CxxTemplateArguments, template_arguments)
	FOGPARSERVALUE_POINTER(CxxTemplateParameter, template_parameter)
	FOGPARSERVALUE_POINTER(CxxTemplateParameters, template_parameters)
	FOGPARSERVALUE_POINTER(CxxTemplatedTypeParameter, templated_type_parameter)
	FOGPARSERVALUE_POINTER(CxxToken, token)
	FOGPARSERVALUE_POINTER(CxxTokenStatements, token_statements)
	FOGPARSERVALUE_POINTER(CxxTokens, tokens)
	FOGPARSERVALUE_POINTER(CxxTreeArguments, tree_arguments)
	FOGPARSERVALUE_POINTER(CxxTreeExpression, tree_expression)
	FOGPARSERVALUE_POINTER(CxxType1Parameters, type1_parameters)
	FOGPARSERVALUE_POINTER(CxxUtility, utility)

	FOGPARSERVALUE_VALUE(int, bang)
	FOGPARSERVALUE_VALUE(CxxIsTemplate, is_template)
	FOGPARSERVALUE_VALUE(size_t, mark)
	FOGPARSERVALUE_VALUE(size_t, nest)
};

class CxxNaffToken : public CxxToken
{
	char *_text;
	int _leng;
private:
	CxxNaffToken(const CxxNaffToken&);
	CxxNaffToken& operator=(const CxxNaffToken&);
public:
	CxxNaffToken(int tokenValue, const char *yyText, int yyLeng);
	virtual ~CxxNaffToken();
};

#define LEX_SAVE_LINE(yyText, yyLeng) CxxToken::make_line(yyText, yyLeng);
#define LEX_ASCII_TOKEN(a) CxxToken::yyToken = CxxToken::get_ascii_token(a); return true;
#define LEX_STATIC_TOKEN(a) CxxToken::yyToken = new CxxToken(PARSE_TOKEN(a)); return true;
#define LEX_C_STATIC_TOKEN(a) \
    if (c_keywords) { LEX_IDENTIFIER_TOKEN(yytext, yyleng) } \
    else { LEX_STATIC_TOKEN(a) } return true;
#define LEX_ESCAPED_TOKEN(yyText, yyLeng)\
    	CxxToken::yyToken = CxxToken::make_literal_character(yytext, yyleng); return true;
#define LEX_CHARACTER_TOKEN(yyText, yyLeng)\
    	CxxToken::yyToken = CxxToken::make_character(yyText, yyLeng); return true;
#define LEX_STRING_TOKEN(yyText, yyLeng)\
    	CxxToken::yyToken = CxxToken::make_string(yyText, yyLeng); return true;
#define LEX_IDENTIFIER_TOKEN(yyText, yyLeng)\
    CxxToken::yyToken = CxxToken::make_identifier(yyText, yyLeng); return true;
#define LEX_KEYWORD_TOKEN(a)\
    CxxToken::yyToken = CxxToken::make_keyword(PARSE_TOKEN(a), yytext, yyleng); return true;

#define LEX_HEX_NUMBER_TOKEN(yyText, yyLeng)\
    CxxToken::yyToken = CxxToken::make_hex_number(yyText, yyLeng); return true;
#define LEX_LONGDOUBLE_NUMBER_TOKEN(yyText, yyLeng)\
    CxxToken::yyToken = CxxToken::make_longdouble_number(yyText, yyLeng); return true;
#define LEX_DOUBLE_NUMBER_TOKEN(yyText, yyLeng)\
    CxxToken::yyToken = CxxToken::make_double_number(yyText, yyLeng); return true;
#define LEX_FLOAT_NUMBER_TOKEN(yyText, yyLeng)\
    CxxToken::yyToken = CxxToken::make_float_number(yyText, yyLeng); return true;
#define LEX_UINT_NUMBER_TOKEN(yyText, yyLeng)\
    CxxToken::yyToken = CxxToken::make_uint_number(yyText, yyLeng); return true;
#define LEX_ULONG_NUMBER_TOKEN(yyText, yyLeng)\
    CxxToken::yyToken = CxxToken::make_ulong_number(yyText, yyLeng); return true;
#define LEX_ULONGLONG_NUMBER_TOKEN(yyText, yyLeng)\
    CxxToken::yyToken = CxxToken::make_ulonglong_number(yyText, yyLeng); return true;

}

#endif
