#ifndef o_reflection_eval_cpp_ast_h__
#define o_reflection_eval_cpp_ast_h__


#include "phantom/phantom.h"
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/variant.hpp>
#include "tokens.h"

o_namespace_begin(phantom, reflection)

namespace cpp {
namespace ast {

struct element;
struct name;
struct unnamed_class_declaration;
struct named_class_declaration;
struct cast_expression;
struct pre_unary_expression;
struct post_unary_expression;
struct binary_left_expression;
struct binary_right_expression;
struct ternary_if_expression;
struct call_expression;

typedef boost::variant<float, double, longdouble, int, uint, short, ushort, longlong, ulonglong, char, bool> fundamental_literal;

inline std::ostream&  operator<<(std::ostream& stream, const fundamental_literal& expr)
{
    return stream;
}

typedef boost::variant<fundamental_literal, string> literal;

inline std::ostream&  operator<<(std::ostream& stream, const literal& expr)
{
    return stream;
}

typedef boost::variant<literal
                     , boost::recursive_wrapper<cast_expression>
                     , boost::recursive_wrapper<pre_unary_expression>
                     , boost::recursive_wrapper<post_unary_expression>
                     , boost::recursive_wrapper<binary_left_expression>
                     , boost::recursive_wrapper<binary_right_expression>
                     , boost::recursive_wrapper<ternary_if_expression>
                     , boost::recursive_wrapper<call_expression>
                     , boost::recursive_wrapper<element>
                     > expression;

inline std::ostream&  operator<<(std::ostream& stream, const expression& expr)
{
    return stream;
}

struct block;
struct if_statement;
struct for_statement;
struct while_statement;
struct do_while_statement;
struct switch_statement;
struct goto_statement;
struct label_statement;
struct variable_declaration;

typedef boost::variant<expression
                    , boost::recursive_wrapper<block>
                     , boost::recursive_wrapper<if_statement>
                     , boost::recursive_wrapper<for_statement>
                     , boost::recursive_wrapper<while_statement>
                     , boost::recursive_wrapper<do_while_statement>
                     , boost::recursive_wrapper<switch_statement>
                     , boost::recursive_wrapper<goto_statement>
                     , boost::recursive_wrapper<label_statement>
                     , boost::recursive_wrapper<variable_declaration>
                     , int> statement;

inline std::ostream&  operator<<(std::ostream& stream, const statement& expr)
{
    return stream;
}

typedef boost::recursive_wrapper<element> template_element;

struct name
{
    name() {}
    name(const string& identifier) : m_identifier(identifier) {}
    string                      m_identifier;
    boost::optional<vector<template_element>> m_template_signature;
};

inline std::ostream&  operator<<(std::ostream& stream, name const& arg) { return stream; }

typedef vector<name> qualified_name;


struct extent_or_signature
{
    extent_or_signature() : m_opening(token_ids::left_paren), m_closing(token_ids::right_paren) {}
    extent_or_signature(const phantom::vector<expression>& list) : m_opening(token_ids::left_paren), m_list(list), m_closing(token_ids::right_paren) {}
    extent_or_signature(const expression& exp)
        : m_opening(token_ids::left_bracket)
        , m_closing(token_ids::right_bracket) 
    { 
        m_list.push_back(exp); 
    }

    size_t m_opening;
    phantom::vector<expression> m_list;
    size_t m_closing;
};

inline std::ostream&  operator<<(std::ostream& stream, const extent_or_signature& arg) { return stream; }

typedef boost::variant<char, extent_or_signature> qualifier_or_extent_or_signature;

inline std::ostream&  operator<<(std::ostream& stream, const qualifier_or_extent_or_signature& expr)
{
    return stream;
}

typedef phantom::vector<qualifier_or_extent_or_signature> qualifier_or_extent_or_signatures;

typedef phantom::vector<extent_or_signature> extent_or_signatures;

struct qualifier_and_qualifier_or_extents
{
    char m_qualifier;
    qualifier_or_extent_or_signatures m_qualifier_or_extents;
};

inline std::ostream&  operator<<(std::ostream& stream, const qualifier_and_qualifier_or_extents& arg) { return stream; }

typedef boost::variant<qualifier_and_qualifier_or_extents, extent_or_signatures>  qualifier_and_qualifier_or_extents_OR_extent_or_signatures;

inline std::ostream&  operator<<(std::ostream& stream, const qualifier_and_qualifier_or_extents_OR_extent_or_signatures& expr)
{
    return stream;
}

struct extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_signatures 
{
    extent_or_signature m_extent;
    qualifier_and_qualifier_or_extents_OR_extent_or_signatures m_qualifier_and_qualifier_or_extents_OR_extent_or_signatures;
};

inline std::ostream&  operator<<(std::ostream& stream, const extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_signatures& arg) { return stream; }

struct function_prototype
{
    extent_or_signature         m_signature;
    boost::optional<char>       m_const_modifier;
};

inline std::ostream&  operator<<(std::ostream& stream, const function_prototype& arg) { return stream; }

typedef boost::variant<qualifier_and_qualifier_or_extents
    , extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_signatures
    , function_prototype> element_extension;

inline std::ostream&  operator<<(std::ostream& stream, const element_extension& expr)
{
    return stream;
}

struct element
{
    boost::optional<char>               m_const_modifier;
    qualified_name                      m_qualified_name;
    boost::optional<element_extension>  m_element_extension;
};

inline std::ostream&  operator<<(std::ostream& stream, const element& arg) { return stream; }


typedef phantom::vector<element> elements;

struct cast_expression
{
    elements m_types;
    boost::recursive_wrapper<expression> m_casted_expression;
};

inline std::ostream&  operator<<(std::ostream& stream, const cast_expression& arg) { return stream; }

struct pre_unary_expression
{
    vector<size_t> m_ops;
    boost::recursive_wrapper<expression> m_expression;
};

inline std::ostream&  operator<<(std::ostream& stream, const pre_unary_expression& arg) { return stream; }

struct post_unary_expression
{
    boost::recursive_wrapper<expression> m_expression;
    vector<size_t> m_ops;
};

inline std::ostream&  operator<<(std::ostream& stream, const post_unary_expression& arg) { return stream; }

struct binary_op_left_expression
{
    boost::recursive_wrapper<expression> m_left;
    size_t m_op;
};

inline std::ostream&  operator<<(std::ostream& stream, const binary_op_left_expression& arg) { return stream; }

struct binary_op_right_expression
{
    size_t m_op;
    boost::recursive_wrapper<expression> m_right;
};

inline std::ostream&  operator<<(std::ostream& stream, const binary_op_right_expression& arg) { return stream; }

struct binary_right_expression
{
    boost::recursive_wrapper<expression>    m_left;
    vector<binary_op_right_expression>      m_op_rights;
};

inline std::ostream&  operator<<(std::ostream& stream, const binary_right_expression& arg) { return stream; }

struct binary_left_expression
{
    vector<binary_op_left_expression>      m_op_lefts;
    boost::recursive_wrapper<expression>    m_right;
};

inline std::ostream&  operator<<(std::ostream& stream, const binary_left_expression& arg) { return stream; }

struct call_expression
{
    boost::recursive_wrapper<expression> m_left;
    extent_or_signatures m_extent_or_signatures;
};

inline std::ostream&  operator<<(std::ostream& stream, const call_expression& arg) { return stream; }

struct ternary_if_expression_result
{
    boost::recursive_wrapper<expression> m_true;
    boost::recursive_wrapper<expression> m_false;
};

inline std::ostream&  operator<<(std::ostream& stream, const ternary_if_expression_result& arg) { return stream; }

struct ternary_if_expression
{
    boost::recursive_wrapper<expression> m_condition;
    phantom::vector<ternary_if_expression_result> m_results;
};

inline std::ostream&  operator<<(std::ostream& stream, const ternary_if_expression& arg) { return stream; }

typedef phantom::vector<statement> statements;

struct variable_declarator
{
    string m_identifier;
    boost::optional<expression> m_expression;
};

inline std::ostream&  operator<<(std::ostream& stream, const variable_declarator& arg) { return stream; }

struct extra_variable_declarator
{
    boost::optional<char> m_type_qualifier;
    variable_declarator m_variable_declarator;
};

inline std::ostream&  operator<<(std::ostream& stream, const extra_variable_declarator& arg) { return stream; }

struct parameter
{
    element m_type;
    boost::optional<variable_declarator> m_declarator;
};

inline std::ostream&  operator<<(std::ostream& stream, const parameter& arg) { return stream; }

typedef phantom::vector<extra_variable_declarator> extra_variable_declarators;

struct variable_declaration
{
    boost::optional<bool> m_is_static; 
    element m_type;
    variable_declarator m_declarator;
    extra_variable_declarators m_extra_declarators;
};

inline std::ostream&  operator<<(std::ostream& stream, const variable_declaration& arg) { return stream; }

struct block 
{
    block() {}
    block(const statements& a_statements): m_statements(a_statements) {}
    statements m_statements;
};

inline std::ostream&  operator<<(std::ostream& stream, const block& arg) { return stream; }

struct if_statement
{
    expression m_condition;
    statement m_then;
    boost::optional<statement> m_else;
};

inline std::ostream&  operator<<(std::ostream& stream, const if_statement& arg) { return stream; }

struct goto_statement
{
    string m_label;
};

inline std::ostream&  operator<<(std::ostream& stream, const goto_statement& arg) { return stream; }

struct label_statement
{
    string m_label;
};

inline std::ostream&  operator<<(std::ostream& stream, const label_statement& arg) { return stream; }

typedef boost::variant<variable_declaration, expression> for_init;

inline std::ostream&  operator<<(std::ostream& stream, const for_init& expr)
{
    return stream;
}

struct for_statement
{
    boost::optional<for_init> m_init;
    boost::optional<expression> m_condition;
    phantom::vector<expression> m_update;
    boost::optional<statement> m_statement;
};

inline std::ostream&  operator<<(std::ostream& stream, const for_statement& arg) { return stream; }

struct while_statement
{
    expression m_condition;
    boost::optional<statement> m_statement;
};

inline std::ostream&  operator<<(std::ostream& stream, const while_statement& arg) { return stream; }

struct do_while_statement
{
    boost::optional<statement> m_statement;
    expression m_condition;
};

inline std::ostream&  operator<<(std::ostream& stream, const do_while_statement& arg) { return stream; }

struct case_statement
{
    fundamental_literal m_value;
    statements m_statements;
};

inline std::ostream&  operator<<(std::ostream& stream, const case_statement& arg) { return stream; }

typedef phantom::vector<case_statement> case_statements;

struct switch_statement
{
    expression m_condition;
    case_statements m_case_statements;
};

inline std::ostream&  operator<<(std::ostream& stream, const switch_statement& arg) { return stream; }

typedef phantom::vector<parameter> parameters;

struct member_function_signature
{
    parameters m_parameters;
    boost::optional<char> m_const;
};

inline std::ostream&  operator<<(std::ostream& stream, const member_function_signature& arg) { return stream; }

struct static_member_function_signature
{
    parameters m_parameters;
};

inline std::ostream&  operator<<(std::ostream& stream, const static_member_function_signature& arg) { return stream; }

struct ambiguous_member_declaration_signature
{
    member_function_signature m_signature;
    boost::optional<block> m_block;
};

inline std::ostream&  operator<<(std::ostream& stream, const ambiguous_member_declaration_signature& arg) { return stream; }

struct ambiguous_member_declaration 
{
    element m_element ;
    string m_identifier ;
    boost::optional<ambiguous_member_declaration_signature> m_signature;
};

inline std::ostream&  operator<<(std::ostream& stream, const ambiguous_member_declaration& arg) { return stream; }

struct static_ambiguous_member_declaration_signature
{
    static_member_function_signature m_signature;
    boost::optional<block> m_block;
};

inline std::ostream&  operator<<(std::ostream& stream, const static_ambiguous_member_declaration_signature& arg) { return stream; }

struct static_ambiguous_member_declaration 
{
    element m_element ;
    string m_identifier ;
    boost::optional<static_ambiguous_member_declaration_signature> m_signature;
};

inline std::ostream&  operator<<(std::ostream& stream, const static_ambiguous_member_declaration& arg) { return stream; }

struct virtual_member_function_declaration 
{
    element r_element;
    string r_identifier ;
    member_function_signature r_member_function_signature;
    boost::optional<uint> m_abstract;
    boost::optional<block> m_block;
};

inline std::ostream&  operator<<(std::ostream& stream, const virtual_member_function_declaration& arg) { return stream; }

typedef boost::variant<ambiguous_member_declaration, static_ambiguous_member_declaration, virtual_member_function_declaration> member_declaration;

inline std::ostream&  operator<<(std::ostream& stream, const member_declaration& expr)
{
    return stream;
}

struct class_inheritance
{
    int m_access_specifier;
    qualified_name m_qualified_name;
};

inline std::ostream&  operator<<(std::ostream& stream, const class_inheritance& arg) { return stream; }

typedef vector<class_inheritance> class_inheritances;

struct named_class_declaration;
struct unnamed_class_declaration;

typedef boost::variant<boost::recursive_wrapper<unnamed_class_declaration>, boost::recursive_wrapper<named_class_declaration>> named_or_unnamed_class_declaration;

inline std::ostream&  operator<<(std::ostream& stream, const named_or_unnamed_class_declaration& expr)
{
    return stream;
}

struct class_declaration
{
    bool m_is_struct;
    named_or_unnamed_class_declaration m_named_or_unnamed_class_declaration;
};

inline std::ostream&  operator<<(std::ostream& stream, const class_declaration& arg) { return stream; }

typedef boost::variant<element, class_declaration> element_or_class_declaration;

inline std::ostream&  operator<<(std::ostream& stream, const element_or_class_declaration& expr)
{
    return stream;
}

typedef boost::variant<int, member_declaration, class_declaration, variable_declaration> class_member_declaration;

inline std::ostream&  operator<<(std::ostream& stream, const class_member_declaration& expr)
{
    return stream;
}

typedef phantom::vector<class_member_declaration> class_member_declarations;

struct class_scope
{
    class_inheritances m_class_inheritances;
    class_member_declarations m_class_member_declarations;
};

inline std::ostream&  operator<<(std::ostream& stream, const class_scope& arg) { return stream; }

struct class_variable_declarator
{
    variable_declarator m_variable_declarator;
    extra_variable_declarators m_extra_variable_declarators;
};

inline std::ostream&  operator<<(std::ostream& stream, const class_variable_declarator& arg) { return stream; }

struct named_class_declaration
{
    string m_name;
    boost::optional<class_scope> m_class_scope; 
    boost::optional<class_variable_declarator> m_variable_declarator;
};

inline std::ostream&  operator<<(std::ostream& stream, const named_class_declaration& arg) { return stream; }

struct unnamed_class_declaration
{
    class_scope m_class_scope; 
    class_variable_declarator m_variable_declarator;
};

inline std::ostream&  operator<<(std::ostream& stream, const unnamed_class_declaration& arg) { return stream; }

struct namespace_declaration;


struct typedef_declaration
{
    element_or_class_declaration m_type;
    string m_name;
};

inline std::ostream&  operator<<(std::ostream& stream, const typedef_declaration& arg) { return stream; }

typedef boost::variant<variable_declaration, class_declaration, boost::recursive_wrapper<namespace_declaration>, typedef_declaration> namespace_member_declaration;

inline std::ostream&  operator<<(std::ostream& stream, const namespace_member_declaration& expr)
{
    return stream;
}

typedef vector<namespace_member_declaration> namespace_scope;

typedef boost::variant<vector<string>, namespace_scope> namespace_alias_or_scope;

inline std::ostream&  operator<<(std::ostream& stream, const namespace_alias_or_scope& expr)
{
    return stream;
}

struct namespace_declaration
{
    string m_name;
    namespace_alias_or_scope m_alias_or_scope;
};

inline std::ostream&  operator<<(std::ostream& stream, const namespace_declaration& arg) { return stream; }


typedef namespace_scope compilation_unit;

class element_or_class_declaration_visitor
    : public boost::static_visitor<>
{
public:
    element_or_class_declaration_visitor(element** a_pp_element, class_declaration** a_pp_class_declaration)
        : m_pp_element(a_pp_element)
        , m_pp_class_declaration(a_pp_class_declaration) {}

    void operator()(element & arg) const // if we go here, it's a qualifier
    {
        *m_pp_element = &arg;
    }

    void operator()(class_declaration& arg) const // if we go here, it's an extent
    {
        *m_pp_class_declaration = &arg;
    }

    element**           m_pp_element;
    class_declaration**  m_pp_class_declaration;
};


class qualifier_or_extent_or_signature_visitor
    : public boost::static_visitor<>
{
public:
    qualifier_or_extent_or_signature_visitor(char** a_ppQualifiers, extent_or_signature** a_ppExtents)
        : m_ppQualifiers(a_ppQualifiers)
        , m_ppExtents(a_ppExtents) {}

    void operator()(char & str) const // if we go here, it's a qualifier
    {
        *m_ppQualifiers = &str;
    }

    void operator()(extent_or_signature& fp) const // if we go here, it's an extent
    {
        *m_ppExtents = &fp;
    }

    extent_or_signature**    m_ppExtents;
    char**  m_ppQualifiers;
};

class qualifier_and_qualifier_or_extents_OR_extent_or_signatures_visitor
    : public boost::static_visitor<>
{
public:
    qualifier_and_qualifier_or_extents_OR_extent_or_signatures_visitor(qualifier_and_qualifier_or_extents** a_pp_qualifier_and_qualifier_or_extents
        , extent_or_signatures** a_pp_extent_or_function_signatures)
        : m_pp_qualifier_and_qualifier_or_extents(a_pp_qualifier_and_qualifier_or_extents)
        , m_pp_extent_or_function_signatures(a_pp_extent_or_function_signatures) {}

    void operator()(qualifier_and_qualifier_or_extents & arg) const
    {
        *m_pp_qualifier_and_qualifier_or_extents = &arg;
    }

    void operator()(extent_or_signatures& arg) const
    {
        *m_pp_extent_or_function_signatures = &arg;
    }

protected:
    qualifier_and_qualifier_or_extents**      m_pp_qualifier_and_qualifier_or_extents;
    extent_or_signatures**   m_pp_extent_or_function_signatures;
};

class element_extension_visitor
    : public boost::static_visitor<>
{
public:
    element_extension_visitor(qualifier_and_qualifier_or_extents** a_pp_qualifier_and_qualifier_or_extents
                            , extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_signatures** a_pp_extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_function_signatures
                            , function_prototype** a_pp_function_prototype)
        : m_pp_qualifier_and_qualifier_or_extents(a_pp_qualifier_and_qualifier_or_extents)
        , m_pp_extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_function_signatures(a_pp_extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_function_signatures)
        , m_pp_function_prototype(a_pp_function_prototype) {}

    void operator()(qualifier_and_qualifier_or_extents & arg) const
    {
        *m_pp_qualifier_and_qualifier_or_extents = &arg;
    }

    void operator()(extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_signatures& arg) const
    {
        *m_pp_extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_function_signatures = &arg;
    }

    void operator()(function_prototype& arg) const 
    {
        *m_pp_function_prototype = &arg;
    }

protected:
    qualifier_and_qualifier_or_extents**      m_pp_qualifier_and_qualifier_or_extents;
    extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_signatures**   m_pp_extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_function_signatures;
    function_prototype**   m_pp_function_prototype;
};

class root_visitor
    : public boost::static_visitor<>
{
public:
    root_visitor(
        element** a_pp_element
        , block** a_pp_block) : m_pp_element(a_pp_element), m_pp_block(a_pp_block) {}


    void operator()(element& arg) const
    {
        *m_pp_element = &arg;
    }

    void operator()(block& arg) const
    {
        *m_pp_block = &arg;
    }

protected:
    element** m_pp_element;
    block** m_pp_block;
};


class statement_visitor
    : public boost::static_visitor<>
{
public:
    statement_visitor(
        expression** a_pp_expression
        , block** a_pp_block
        , if_statement**                  a_pp_if_statement 
        , for_statement**                 a_pp_for_statement
        , while_statement**               a_pp_while_statement 
        , do_while_statement**            a_pp_do_while_statement
        , switch_statement**              a_pp_switch_statement
        , goto_statement**                a_pp_goto_statement 
        , label_statement**               a_pp_label_statement
        , variable_declaration**          a_pp_variable_declaration
        , int** a_pp_keyword_statement) 
            : m_pp_expression(a_pp_expression)
            , m_pp_block(a_pp_block) 
            , m_pp_if_statement  (a_pp_if_statement) 
            , m_pp_for_statement (a_pp_for_statement)
            , m_pp_while_statement  (a_pp_while_statement) 
            , m_pp_do_while_statement (a_pp_do_while_statement)
            , m_pp_switch_statement (a_pp_switch_statement)
            , m_pp_goto_statement  (a_pp_goto_statement) 
            , m_pp_label_statement (a_pp_label_statement)
            , m_pp_variable_declaration (a_pp_variable_declaration)
            , m_pp_keyword_statement(a_pp_keyword_statement)
    {}


    void operator()(expression& arg) const
    {
        *m_pp_expression = &arg;
    }

    void operator()(block& arg) const
    {
        *m_pp_block = &arg;
    }

    void operator()(if_statement& arg) const
	{
		*m_pp_if_statement = &arg;
	}

    void operator()(for_statement& arg) const
	{
		*m_pp_for_statement = &arg;
	}

    void operator()(while_statement& arg) const
	{
		*m_pp_while_statement = &arg;
	}

    void operator()(do_while_statement& arg) const
	{
		*m_pp_do_while_statement = &arg;
	}

    void operator()(switch_statement& arg) const
	{
		*m_pp_switch_statement = &arg;
	}

    void operator()(goto_statement& arg) const
	{
		*m_pp_goto_statement = &arg;
	}

    void operator()(label_statement& arg) const
	{
		*m_pp_label_statement = &arg;
	}

    void operator()(variable_declaration& arg) const
	{
		*m_pp_variable_declaration = &arg;
    }

    void operator()(int& arg) const
    {
        *m_pp_keyword_statement = &arg;
    }


protected:
    expression**                    m_pp_expression;
    block**                         m_pp_block;
    if_statement**                  m_pp_if_statement ;
    for_statement**                 m_pp_for_statement;
    while_statement**               m_pp_while_statement ;
    do_while_statement**            m_pp_do_while_statement;
    switch_statement**              m_pp_switch_statement;
    goto_statement**                m_pp_goto_statement ;
    label_statement**               m_pp_label_statement;
    variable_declaration**          m_pp_variable_declaration;
    int**                           m_pp_keyword_statement;
};

class literal_visitor
    : public boost::static_visitor<>
{
public:
    literal_visitor(
        fundamental_literal** a_pp_fundamental_literal
        , string** a_pp_string) : m_pp_fundamental_literal(a_pp_fundamental_literal), m_pp_string(a_pp_string) {}


    void operator()(fundamental_literal& arg) const
    {
        *m_pp_fundamental_literal = &arg;
    }

    void operator()(string& arg) const
    {
        *m_pp_string = &arg;
    }

protected:
    fundamental_literal** m_pp_fundamental_literal;
    string** m_pp_string;
};


class fundamental_literal_visitor
    : public boost::static_visitor<>
{
public:
    fundamental_literal_visitor(
        float** a_pp_float, double** a_pp_double, longdouble** a_pp_longdouble, int** a_pp_int, uint** a_pp_uint, short** a_pp_short, ushort** a_pp_ushort, longlong** a_pp_longlong, ulonglong** a_pp_ulonglong, char** a_pp_char, bool** a_pp_bool
        
        ) : m_pp_float (a_pp_float), m_pp_double (a_pp_double), m_pp_longdouble (a_pp_longdouble), m_pp_int (a_pp_int), m_pp_uint (a_pp_uint), m_pp_short (a_pp_short), m_pp_ushort (a_pp_ushort), m_pp_longlong (a_pp_longlong), m_pp_ulonglong (a_pp_ulonglong), m_pp_char (a_pp_char), m_pp_bool (a_pp_bool)
    {

    }

    void operator()(float& arg) const
    {
        *m_pp_float = &arg;
    }

    void operator()(double& arg) const
    {
        *m_pp_double = &arg;
    }

    void operator()(longdouble& arg) const
    {
        *m_pp_longdouble = &arg;
    }

    void operator()(int& arg) const
    {
        *m_pp_int = &arg;
    }

    void operator()(uint& arg) const
    {
        *m_pp_uint = &arg;
    }

    void operator()(short& arg) const
    {
        *m_pp_short = &arg;
    }

    void operator()(ushort& arg) const
    {
        *m_pp_ushort = &arg;
    }

    void operator()(longlong& arg) const
    {
        *m_pp_longlong = &arg;
    }

    void operator()(ulonglong& arg) const
    {
        *m_pp_ulonglong = &arg;
    }

    void operator()(char& arg) const
    {
        *m_pp_char = &arg;
    }

    void operator()(bool& arg) const
    {
        *m_pp_bool = &arg;
    }

protected:
    float** m_pp_float; 
    double** m_pp_double; 
    longdouble** m_pp_longdouble; 
    int** m_pp_int; 
    uint** m_pp_uint; 
    short** m_pp_short; 
    ushort** m_pp_ushort; 
    longlong** m_pp_longlong; 
    ulonglong** m_pp_ulonglong; 
    char** m_pp_char; 
    bool** m_pp_bool;
};

class expression_visitor
    : public boost::static_visitor<>
{
public:
    expression_visitor(
          cast_expression** a_pp_cast_expression
        , pre_unary_expression** a_pp_pre_unary_expression
        , post_unary_expression** a_pp_post_unary_expression
        , binary_left_expression** a_pp_binary_left_expression
        , binary_right_expression** a_pp_binary_right_expression
        , ternary_if_expression** a_pp_ternary_if_expression
        , call_expression** a_pp_call_expression
        , element** a_pp_element
        , literal** a_pp_literal)
        : m_pp_cast_expression(a_pp_cast_expression)
        , m_pp_pre_unary_expression(a_pp_pre_unary_expression)
        , m_pp_post_unary_expression(a_pp_post_unary_expression)
        , m_pp_binary_right_expression(a_pp_binary_right_expression)
        , m_pp_binary_left_expression(a_pp_binary_left_expression)
        , m_pp_ternary_if_expression(a_pp_ternary_if_expression)
        , m_pp_call_expression(a_pp_call_expression)
        , m_pp_element(a_pp_element)
        , m_pp_literal(a_pp_literal) {}
    
    void operator()(cast_expression& arg) const
    {
        *m_pp_cast_expression = &arg;
    }

    void operator()(pre_unary_expression& arg) const
    {
        *m_pp_pre_unary_expression = &arg;
    }

    void operator()(post_unary_expression& arg) const
    {
        *m_pp_post_unary_expression = &arg;
    }

    void operator()(binary_left_expression& arg) const
    {
        *m_pp_binary_left_expression = &arg;
    }

    void operator()(binary_right_expression& arg) const
    {
        *m_pp_binary_right_expression = &arg;
    }

    void operator()(ternary_if_expression& arg) const
    {
        *m_pp_ternary_if_expression = &arg;
    }

    void operator()(call_expression& arg) const
    {
        *m_pp_call_expression = &arg;
    }

    void operator()(element& arg) const
    {
        *m_pp_element = &arg;
    }

    void operator()(literal& arg) const
    {
        *m_pp_literal = &arg;
    }

protected:
    cast_expression**       m_pp_cast_expression;
    pre_unary_expression**  m_pp_pre_unary_expression;
    post_unary_expression** m_pp_post_unary_expression;
    binary_right_expression**     m_pp_binary_right_expression;
    binary_left_expression**     m_pp_binary_left_expression;
    ternary_if_expression** m_pp_ternary_if_expression;
    call_expression**       m_pp_call_expression;
    element**               m_pp_element;
    literal**              m_pp_literal;
};

}}

o_namespace_end(phantom, reflection)

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::name,
(phantom::string, m_identifier)
(boost::optional<phantom::vector<phantom::reflection::cpp::ast::template_element>>, m_template_signature)
);

BOOST_FUSION_ADAPT_STRUCT(
    phantom::reflection::cpp::ast::element,
    (boost::optional<char>, m_const_modifier)
    (phantom::reflection::cpp::ast::qualified_name, m_qualified_name)
    (boost::optional<phantom::reflection::cpp::ast::element_extension>, m_element_extension)
);

BOOST_FUSION_ADAPT_STRUCT(
    phantom::reflection::cpp::ast::function_prototype,
    (phantom::reflection::cpp::ast::extent_or_signature, m_signature)
    (boost::optional<char>, m_const_modifier)
);

BOOST_FUSION_ADAPT_STRUCT(
    phantom::reflection::cpp::ast::extent_or_signature,
    (size_t, m_opening)
    (phantom::vector<phantom::reflection::cpp::ast::expression>, m_list)
    (size_t, m_closing)
);

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::cast_expression,
    (phantom::reflection::cpp::ast::elements, m_types)
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_casted_expression)
    );

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::pre_unary_expression ,
    (phantom::vector<size_t>, m_ops)
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_expression)
    );

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::post_unary_expression ,
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_expression)
    (phantom::vector<size_t>, m_ops)
    );


BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::binary_op_right_expression,
    (size_t, m_op)
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_right)
    );

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::binary_op_left_expression,
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_left)
    (size_t, m_op)
    );

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::binary_right_expression,
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_left)
    (phantom::vector<phantom::reflection::cpp::ast::binary_op_right_expression>, m_op_rights)
    );

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::binary_left_expression,
    (phantom::vector<phantom::reflection::cpp::ast::binary_op_left_expression>, m_op_lefts)
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_right)
    );

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::ternary_if_expression,
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_condition)
    (phantom::vector<phantom::reflection::cpp::ast::ternary_if_expression_result>, m_results)
    );

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::ternary_if_expression_result,
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_true)
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_false)
    );

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::cpp::ast::call_expression,
    (boost::recursive_wrapper<phantom::reflection::cpp::ast::expression>, m_left)
    (phantom::reflection::cpp::ast::extent_or_signatures, m_extent_or_signatures)
    );

BOOST_FUSION_ADAPT_STRUCT(
    phantom::reflection::cpp::ast::qualifier_and_qualifier_or_extents,
    (char, m_qualifier)
    (phantom::reflection::cpp::ast::qualifier_or_extent_or_signatures, m_qualifier_or_extents)
    );

BOOST_FUSION_ADAPT_STRUCT(
    phantom::reflection::cpp::ast::block,
    (phantom::reflection::cpp::ast::statements, m_statements)
    );

BOOST_FUSION_ADAPT_STRUCT(
    phantom::reflection::cpp::ast::extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_signatures ,
    (phantom::reflection::cpp::ast::extent_or_signature, m_extent)
    (phantom::reflection::cpp::ast::qualifier_and_qualifier_or_extents_OR_extent_or_signatures, m_qualifier_and_qualifier_or_extents_OR_extent_or_signatures)
);

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::extra_variable_declarator,
    (boost::optional<char>, m_type_qualifier)
    (phantom::reflection::cpp::ast::variable_declarator, m_variable_declarator)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::variable_declarator,
    (phantom::string, m_identifier)
    (boost::optional<phantom::reflection::cpp::ast::expression>, m_expression)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::variable_declaration,
    (boost::optional<bool>, m_is_static)
    (phantom::reflection::cpp::ast::element, m_type)
    (phantom::reflection::cpp::ast::variable_declarator, m_declarator)
    (phantom::reflection::cpp::ast::extra_variable_declarators, m_extra_declarators)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::if_statement,
    (phantom::reflection::cpp::ast::expression, m_condition)
(phantom::reflection::cpp::ast::statement, m_then)
(boost::optional<phantom::reflection::cpp::ast::statement>, m_else)
);


BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::goto_statement,
    (phantom::string, m_label)
    );


BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::label_statement,
    (phantom::string, m_label)
    );


BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::for_statement,
    (boost::optional<phantom::reflection::cpp::ast::for_init>, m_init)
    (boost::optional<phantom::reflection::cpp::ast::expression>, m_condition)
    (phantom::vector<phantom::reflection::cpp::ast::expression>, m_update)
    (boost::optional<phantom::reflection::cpp::ast::statement>, m_statement)
    );


BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::while_statement,
    (phantom::reflection::cpp::ast::expression, m_condition)
    (boost::optional<phantom::reflection::cpp::ast::statement>, m_statement)
);

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::do_while_statement,
    (boost::optional<phantom::reflection::cpp::ast::statement>, m_statement)
    (phantom::reflection::cpp::ast::expression, m_condition)
);

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::case_statement,
    (phantom::reflection::cpp::ast::fundamental_literal, m_value)
    (phantom::reflection::cpp::ast::statements, m_statements)
);

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::switch_statement,
    (phantom::reflection::cpp::ast::expression, m_condition)
    (phantom::reflection::cpp::ast::case_statements, m_case_statements)
    );
BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::parameter,
    (phantom::reflection::cpp::ast::element, m_type)
    (boost::optional<phantom::reflection::cpp::ast::variable_declarator>, m_declarator)
);

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::member_function_signature,
    (phantom::reflection::cpp::ast::parameters, m_parameters)
    (boost::optional<char>, m_const)
);

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::static_member_function_signature,
    (phantom::reflection::cpp::ast::parameters, m_parameters)
);


BOOST_FUSION_ADAPT_STRUCT(  phantom::reflection::cpp::ast::ambiguous_member_declaration_signature,
    (phantom::reflection::cpp::ast::member_function_signature, m_signature)
    (boost::optional<phantom::reflection::cpp::ast::block>, m_block)
);

BOOST_FUSION_ADAPT_STRUCT(  phantom::reflection::cpp::ast::ambiguous_member_declaration ,
    (phantom::reflection::cpp::ast::element, m_element )
    (phantom::string, m_identifier )
    (boost::optional<phantom::reflection::cpp::ast::ambiguous_member_declaration_signature>, m_signature)
    );

BOOST_FUSION_ADAPT_STRUCT(  phantom::reflection::cpp::ast::static_ambiguous_member_declaration_signature,
    (phantom::reflection::cpp::ast::static_member_function_signature, m_signature)
    (boost::optional<phantom::reflection::cpp::ast::block>, m_block)
    );

BOOST_FUSION_ADAPT_STRUCT(  phantom::reflection::cpp::ast::static_ambiguous_member_declaration ,
    (phantom::reflection::cpp::ast::element, m_element )
    (phantom::string, m_identifier )
    (boost::optional<phantom::reflection::cpp::ast::static_ambiguous_member_declaration_signature>, m_signature)
    );

BOOST_FUSION_ADAPT_STRUCT(  phantom::reflection::cpp::ast::virtual_member_function_declaration ,
    (phantom::reflection::cpp::ast::element, r_element)
    (phantom::string, r_identifier )
    (phantom::reflection::cpp::ast::member_function_signature, r_member_function_signature)
    (boost::optional<phantom::uint>, m_abstract)
    (boost::optional<phantom::reflection::cpp::ast::block>, m_block)
);

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::class_inheritance,
    (int, m_access_specifier)
    (phantom::reflection::cpp::ast::qualified_name, m_qualified_name)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::class_scope, 
    (phantom::reflection::cpp::ast::class_inheritances, m_class_inheritances)
    (phantom::reflection::cpp::ast::class_member_declarations, m_class_member_declarations)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::namespace_declaration, 
    (phantom::string, m_name)
    (phantom::reflection::cpp::ast::namespace_alias_or_scope, m_alias_or_scope)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::class_declaration, 
    (bool, m_is_struct)
    (phantom::reflection::cpp::ast::named_or_unnamed_class_declaration, m_named_or_unnamed_class_declaration)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::class_variable_declarator, 
    (phantom::reflection::cpp::ast::variable_declarator, m_variable_declarator)
    (phantom::reflection::cpp::ast::extra_variable_declarators, m_extra_variable_declarators)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::named_class_declaration, 
    (phantom::string, m_name)
    (boost::optional<phantom::reflection::cpp::ast::class_scope>, m_class_scope)
    (boost::optional<phantom::reflection::cpp::ast::class_variable_declarator>, m_variable_declarator)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::unnamed_class_declaration, 
    (phantom::reflection::cpp::ast::class_scope, m_class_scope)
    (phantom::reflection::cpp::ast::class_variable_declarator, m_variable_declarator)
    );

BOOST_FUSION_ADAPT_STRUCT( phantom::reflection::cpp::ast::typedef_declaration, 
    (phantom::reflection::cpp::ast::element_or_class_declaration, m_type)
    (phantom::string, m_name)
    );

namespace boost { namespace spirit { namespace traits
{
    template <typename Out, typename T>
    struct print_attribute_debug<Out, boost::recursive_wrapper<T>>
    {
        static void call(Out& out, boost::recursive_wrapper<T> const& val)
        {
            // do your output here; Out is a std::ostream
            print_attribute_debug<Out, T>::call(out, val.get());
        }
    };
    template <typename Out, typename T>
    struct print_attribute_debug<Out, phantom::vector<T>>
    {
        static void call(Out& out, phantom::vector<T> const& val)
        {
            // do your output here; Out is a std::ostream
            for(auto it = val.begin(); it != val.end(); ++it)
            {
                if(it != val.begin()) 
                    out << ' ';
                print_attribute_debug<Out, T>::call(out, *it);
            }
        }
    };
}}}


#endif // ast_h__
