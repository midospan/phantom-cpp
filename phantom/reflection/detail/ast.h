#ifndef o_reflection_eval_cpp_ast_h__
#define o_reflection_eval_cpp_ast_h__


#include "phantom/phantom.h"
#include <boost/variant.hpp>
#include "tokens.h"

o_namespace_begin(phantom, reflection)

namespace cpp {
namespace ast {

struct node
{
    node() : m_text(0), m_length(0) {}
    const char*  m_text;
    size_t       m_length;
    CodeLocation m_location;
};

template<typename T>
struct fundamental_node : node
{
    o_forceinline fundamental_node() {}
    o_forceinline fundamental_node(T a_value) : m_value(a_value) {}

    o_forceinline fundamental_node<T>& operator=(T a_value) { m_value = a_value; return *this; }

    o_forceinline operator T() { return m_value; }

    T m_value;
};

typedef fundamental_node<string> string_node;
/*

class string_node : public string, public node
{
public:
    string_node() {}
    string_node(const string_node& other) : string(other) {}
    string_node(const char* other) : string(other) {}
    string_node(const string& other) : string(other) {}

    string_node(string_node&& _Right)
        : string(std::forward<string_node>(_Right))
    {	
    }

    string_node(string&& _Right)
        : string(std::forward<string>(_Right))
    {	
    }

    string_node& operator=(const string_node& other)
    {
        return (string_node&)assign(other);
    }

    string_node& operator=(string_node&& other)
    {
        return (string_node&)(assign(_STD forward<string_node>(other)));
    }

};*/

template<typename T>
inline std::ostream&  operator<<(std::ostream& stream, const fundamental_node<T>& expr)
{
    return stream<<expr.m_value;
}

template<typename AstNode>
struct location_assigner
{
    static void set(AstNode& a_Node, const CodeLocation& a_Location, const char* a_Text, size_t a_Length)
    {
        a_Node.m_location = a_Location;
        a_Node.m_text = a_Text;
        a_Node.m_length = a_Length;
    }
    static void get(const AstNode& a_Node, CodeLocation& a_Location, const char*& a_Text, size_t& a_Length)
    {
        a_Location = a_Node.m_location;
        a_Text = a_Node.m_text;
        a_Length = a_Node.m_length;
    }
};

template <
    typename T0_
    , BOOST_VARIANT_ENUM_SHIFTED_PARAMS(typename T)
>
struct location_assigner<boost::variant<T0_, BOOST_VARIANT_ENUM_SHIFTED_PARAMS(T)>>
{
    struct set_visitor : public boost::static_visitor<>
    {
        set_visitor(const CodeLocation& l, const char* a_Text, size_t a_Length) : location(l), text(a_Text), length(a_Length) {}
        template<typename T>
        void operator()(T& any) const
        {
            location_assigner<T>::set(any, location, text, length);
        }
        const CodeLocation& location;
        const char* text;
        size_t length;
    };
    struct get_visitor : public boost::static_visitor<>
    {
        get_visitor(CodeLocation& l, const char*& a_Text, size_t& a_Length) : location(l), text(a_Text), length(a_Length) {}
        template<typename T>
        void operator()(const T& any) const
        {
            location_assigner<T>::get(any, location, text, length);
        }
        CodeLocation& location;
        const char*& text;
        size_t& length;
    };

    typedef boost::variant<T0_, BOOST_VARIANT_ENUM_SHIFTED_PARAMS(T)> variant;
    static void set(variant& a_Node, const CodeLocation& a_Location, const char* a_Text, size_t a_Length)
    {
        set_visitor v(a_Location, a_Text, a_Length);
        a_Node.apply_visitor(v);
    }
    static void get(const variant& a_Node, CodeLocation& a_Location, const char*& a_Text, size_t& a_Length)
    {
        get_visitor v(a_Location, a_Text, a_Length);
        a_Node.apply_visitor(v);
    }
};

template <typename T>
struct location_assigner<phantom::vector<T>>
{
    static void set(phantom::vector<T>& a_Node, const CodeLocation& a_Location, const char* a_Text, size_t a_Length)
    {

    }
    static void get(const phantom::vector<T>& a_Node, CodeLocation& a_Location, const char*& a_Text, size_t& a_Length)
    {

    }
};

template <typename T>
struct location_assigner<boost::recursive_wrapper<T>>
{
    static void set(boost::recursive_wrapper<T>& a_Node, const CodeLocation& a_Location, const char* a_Text, size_t a_Length)
    {
        location_assigner<T>::set(a_Node.get(), a_Location, a_Text, a_Length);
    }
    static void get(const boost::recursive_wrapper<T>& a_Node, CodeLocation& a_Location, const char*& a_Text, size_t& a_Length)
    {
        location_assigner<T>::get(a_Node.get(), a_Location, a_Text, a_Length);
    }
};

template <typename T>
struct location_assigner<boost::optional<T>>
{
    static void set(boost::optional<T>& a_Node, const CodeLocation& a_Location, const char* a_Text, size_t a_Length)
    {
        if(a_Node.is_initialized())
        {
            location_assigner<T>::set(*a_Node, a_Location, a_Text, a_Length);
        }
    }
    static void get(const boost::optional<T>& a_Node, CodeLocation& a_Location, const char*& a_Text, size_t& a_Length)
    {
        if(a_Node.is_initialized())
        {
            location_assigner<T>::get(*a_Node, a_Location, a_Text, a_Length);
        }
    }
};

template<typename T>
string node_string(T& a_Node)
{
    CodeLocation location;
    const char* text = nullptr;
    size_t length;
    location_assigner<T>::get(a_Node, location, text, length);
    return text ? string(text, length) : string();
}

template<typename T>
CodeLocation node_location(T& a_Node)
{
    CodeLocation location;
    const char* text;
    size_t length;
    location_assigner<T>::get(a_Node, location, text, length);
    return location;
}


struct element;
struct type;
struct name;
struct unnamed_class_declaration;
struct named_class_declaration;
struct cast_expression;
struct pre_unary_expression;
struct post_unary_expression;
//struct binary_left_expression;
struct binary_right_expression;
struct ternary_if_expression;
struct call_expression;
struct bracket_expression;

typedef vector<boost::recursive_wrapper<name>> qualified_name;

typedef boost::variant<fundamental_node<hex_t>
                     , fundamental_node<float>
                     , fundamental_node<double>
                     , fundamental_node<longdouble>
                     , fundamental_node<int>
                     , fundamental_node<uint>
                     , fundamental_node<longlong>
                     , fundamental_node<ulonglong>
                     , fundamental_node<char>
                     , fundamental_node<bool>
                     , fundamental_node<std::nullptr_t>> fundamental_literal;

inline std::ostream&  operator<<(std::ostream& stream, const fundamental_literal& expr)
{
    return stream;
}

typedef boost::variant<fundamental_node<hex_t>
                     , fundamental_node<int>
                     , fundamental_node<uint>
                     , fundamental_node<longlong>
                     , fundamental_node<ulonglong>
                     , fundamental_node<char>
                     , fundamental_node<bool>> integral_literal;

inline std::ostream&  operator<<(std::ostream& stream, const integral_literal& expr)
{
    return stream;
}

typedef boost::variant<fundamental_literal, string_node> literal;

inline std::ostream&  operator<<(std::ostream& stream, const literal& expr)
{
    return stream;
}

typedef boost::variant<literal
                     , boost::recursive_wrapper<cast_expression>
                     , boost::recursive_wrapper<pre_unary_expression>
                     , boost::recursive_wrapper<post_unary_expression>
                     //, boost::recursive_wrapper<binary_left_expression>
                     , boost::recursive_wrapper<binary_right_expression>
                     , boost::recursive_wrapper<ternary_if_expression>
                     , boost::recursive_wrapper<call_expression>
                     , boost::recursive_wrapper<bracket_expression>
                     , boost::recursive_wrapper<qualified_name>
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

struct return_statement : node
{
    boost::optional<expression> m_return_value;
};


inline std::ostream&  operator<<(std::ostream& stream, const return_statement& arg) { return stream; }

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
                     , return_statement
                     , fundamental_node<int>> statement;

inline std::ostream&  operator<<(std::ostream& stream, const statement& expr)
{
    return stream;
}

typedef boost::variant<boost::recursive_wrapper<type>, integral_literal> template_element;

struct name : node
{
    name() {}
    name(const char* identifier) : m_identifier(identifier) {}
    name(const string& identifier) : m_identifier(identifier) {}
    name(const string_node& identifier) : m_identifier(identifier) {}
    string_node           m_identifier;
    boost::optional<vector<template_element>> m_template_signature;
};

inline std::ostream&  operator<<(std::ostream& stream, name const& arg) { return stream; }
/*

struct qualified_name : public node
{
    qualified_name() {}
    qualified_name(const vector<name>& a_names) { m_names = a_names; }
    qualified_name (const char* n) { m_names.push_back(name(string_node(n))); }
    qualified_name (const string& n) { m_names.push_back(name(string_node(n))); }
    vector<name> m_names;
};*/

//inline std::ostream&  operator<<(std::ostream& stream, qualified_name const& arg) { return stream; }


typedef vector<type> function_signature;

typedef template_element extent;

typedef boost::variant<template_element, function_signature> extent_or_function_signature;

inline std::ostream&  operator<<(std::ostream& stream, const extent_or_function_signature& arg) { return stream; }

typedef boost::variant<fundamental_node<char>, template_element> qualifier_or_extent;
typedef phantom::vector<qualifier_or_extent> qualifier_or_extents;


struct function_prototype : node
{
    function_signature                      m_signature;
    boost::optional<fundamental_node<char>> m_const_modifier;
};

inline std::ostream&  operator<<(std::ostream& stream, const function_prototype& arg) { return stream; }

struct type : node
{
    boost::optional<fundamental_node<char>> m_const_modifier;
    qualified_name                          m_qualified_name;
    vector<qualifier_or_extent>             m_type_extension;
};

inline std::ostream&  operator<<(std::ostream& stream, const type& arg) { return stream; }

struct element : node
{
    type m_type;
    boost::optional<function_prototype> m_function_prototype;
};

inline std::ostream&  operator<<(std::ostream& stream, const element& arg) { return stream; }


typedef phantom::vector<element> elements;

struct cast_type : public node
{
    cast_type() {}
    cast_type(const type& t) : m_type(t) {}
    type m_type;
};

inline std::ostream&  operator<<(std::ostream& stream, const cast_type& arg) { return stream; }

typedef phantom::vector<cast_type> cast_types;

struct cast_expression : node
{
    cast_expression() {}
    cast_expression(const expression& a_expression) : m_casted_expression(a_expression) {}
    cast_types m_types;
    boost::recursive_wrapper<expression> m_casted_expression;
};

inline std::ostream&  operator<<(std::ostream& stream, const cast_expression& arg) { return stream; }

struct pre_unary_expression : node
{
    pre_unary_expression() {}
    pre_unary_expression(const expression& a_expression) : m_expression(a_expression) {}
    vector<fundamental_node<size_t>> m_ops;
    boost::recursive_wrapper<expression> m_expression;
};

inline std::ostream&  operator<<(std::ostream& stream, const pre_unary_expression& arg) { return stream; }

struct post_unary_expression : node
{
    boost::recursive_wrapper<expression> m_expression;
    vector<fundamental_node<size_t>> m_ops;
};

inline std::ostream&  operator<<(std::ostream& stream, const post_unary_expression& arg) { return stream; }

struct binary_op_left_expression : node
{
    boost::recursive_wrapper<expression> m_left;
    fundamental_node<size_t> m_op;
};

inline std::ostream&  operator<<(std::ostream& stream, const binary_op_left_expression& arg) { return stream; }

struct binary_op_right_expression : node
{
    fundamental_node<size_t> m_op;
    boost::recursive_wrapper<expression> m_right;
};

inline std::ostream&  operator<<(std::ostream& stream, const binary_op_right_expression& arg) { return stream; }

struct binary_right_expression : node
{
    boost::recursive_wrapper<expression>    m_left;
    vector<binary_op_right_expression>      m_op_rights;
};

inline std::ostream&  operator<<(std::ostream& stream, const binary_right_expression& arg) { return stream; }

// struct binary_left_expression : node
// {
//     boost::recursive_wrapper<expression>        m_left;
//     boost::optional<binary_op_right_expression> m_op_right;
// };
// 
// inline std::ostream&  operator<<(std::ostream& stream, const binary_left_expression& arg) { return stream; }

struct bracket_expression : node
{
    boost::recursive_wrapper<call_expression> m_left;
    vector<expression> m_arguments;
};

inline std::ostream&  operator<<(std::ostream& stream, const bracket_expression& arg) { return stream; }

struct argument_list : public node
{
    vector<expression> m_expressions;
};

inline std::ostream&  operator<<(std::ostream& stream, const argument_list& arg) { return stream; }

struct call_expression : node
{
    boost::recursive_wrapper<post_unary_expression> m_left;
    vector<argument_list> m_argument_lists;
};

inline std::ostream&  operator<<(std::ostream& stream, const call_expression& arg) { return stream; }

struct ternary_if_expression_result : node
{
    boost::recursive_wrapper<expression> m_true;
    boost::recursive_wrapper<expression> m_false;
};

inline std::ostream&  operator<<(std::ostream& stream, const ternary_if_expression_result& arg) { return stream; }

struct ternary_if_expression : node
{
    boost::recursive_wrapper<expression> m_condition;
    phantom::vector<ternary_if_expression_result> m_results;
};

inline std::ostream&  operator<<(std::ostream& stream, const ternary_if_expression& arg) { return stream; }

typedef phantom::vector<statement> statements;

struct block  : node
{
    block() {}
    block(const statements& a_statements): m_statements(a_statements) {}
    statements m_statements;
};

inline std::ostream&  operator<<(std::ostream& stream, const block& arg) { return stream; }

struct array_initializer : node
{
    vector<expression> m_expressions;
};

inline std::ostream&  operator<<(std::ostream& stream, const array_initializer& arg) { return stream; }

typedef boost::variant<array_initializer, expression> array_initializer_or_expression;

struct variable_declarator_end : node
{
    phantom::vector<template_element> m_extents;
    boost::optional<array_initializer_or_expression> m_array_initializer_or_expression;
};

inline std::ostream&  operator<<(std::ostream& stream, const variable_declarator_end& arg) { return stream; }

struct variable_declarator : node
{
    string_node m_identifier;
    variable_declarator_end m_end;
};

inline std::ostream&  operator<<(std::ostream& stream, const variable_declarator& arg) { return stream; }

struct extra_variable_declarator : node
{
    phantom::vector<fundamental_node<char>> m_type_qualifiers;
    variable_declarator m_variable_declarator;
};

typedef phantom::vector<extra_variable_declarator> extra_variable_declarators;

inline std::ostream&  operator<<(std::ostream& stream, const extra_variable_declarator& arg) { return stream; }

struct parameter : node
{
    type m_type;
    boost::optional<variable_declarator> m_declarator;
};

typedef phantom::vector<parameter> parameters;

inline std::ostream&  operator<<(std::ostream& stream, const parameter& arg) { return stream; }

struct static_function_signature : node
{
    parameters m_parameters;
};

inline std::ostream&  operator<<(std::ostream& stream, const static_function_signature& arg) { return stream; }

struct ambiguous_global_declaration_signature_and_block : node
{
    static_function_signature m_signature;
    boost::optional<block> m_block;
};

inline std::ostream&  operator<<(std::ostream& stream, const ambiguous_global_declaration_signature_and_block& arg) { return stream; }

typedef boost::variant<ambiguous_global_declaration_signature_and_block, variable_declarator_end> ambiguous_global_declaration_signature_and_block_or_declarator;

struct ambiguous_global_declaration  : node
{
    boost::optional<fundamental_node<bool>> m_is_static; 
    type m_type ;
    string_node m_identifier ;
    boost::optional<ambiguous_global_declaration_signature_and_block_or_declarator> m_signature_and_block;
};

inline std::ostream&  operator<<(std::ostream& stream, const ambiguous_global_declaration& arg) { return stream; }


struct variable_declaration : node
{
    boost::optional<fundamental_node<bool>> m_is_static; 
    type m_type;
    variable_declarator m_declarator;
    extra_variable_declarators m_extra_declarators;
};

inline std::ostream&  operator<<(std::ostream& stream, const variable_declaration& arg) { return stream; }

typedef boost::variant<variable_declaration, boost::recursive_wrapper<expression>> variable_declaration_or_expression;

struct if_statement : node
{
    variable_declaration_or_expression m_condition;
    statement m_then;
    boost::optional<statement> m_else;
};

inline std::ostream&  operator<<(std::ostream& stream, const if_statement& arg) { return stream; }

struct goto_statement : node
{
    string_node m_label;
};

inline std::ostream&  operator<<(std::ostream& stream, const goto_statement& arg) { return stream; }

struct label_statement : node
{
    string_node m_label;
};

inline std::ostream&  operator<<(std::ostream& stream, const label_statement& arg) { return stream; }


struct for_statement : node
{
    boost::optional<variable_declaration_or_expression> m_init;
    boost::optional<expression> m_condition;
    phantom::vector<expression> m_update;
    boost::optional<statement> m_statement;
};

inline std::ostream&  operator<<(std::ostream& stream, const for_statement& arg) { return stream; }

struct while_statement : node
{
    variable_declaration_or_expression m_condition;
    boost::optional<statement> m_statement;
};

inline std::ostream&  operator<<(std::ostream& stream, const while_statement& arg) { return stream; }

struct do_while_statement : node
{
    boost::optional<statement> m_statement;
    expression m_condition;
};

inline std::ostream&  operator<<(std::ostream& stream, const do_while_statement& arg) { return stream; }

struct case_label : node
{
    boost::optional<template_element> m_value;
};

inline std::ostream&  operator<<(std::ostream& stream, const case_label& arg) { return stream; }

typedef boost::variant<statement, case_label> statement_or_case_label;

typedef phantom::vector<statement_or_case_label> statement_or_case_labels;

struct switch_statement : node
{
    variable_declaration_or_expression m_test_value;
    statement_or_case_labels m_statement_or_case_labels;
};

inline std::ostream&  operator<<(std::ostream& stream, const switch_statement& arg) { return stream; }

struct member_function_signature : node
{
    parameters m_parameters;
    boost::optional<fundamental_node<char>> m_const;
};

inline std::ostream&  operator<<(std::ostream& stream, const member_function_signature& arg) { return stream; }

struct ambiguous_member_declaration_signature_and_block : node
{
    member_function_signature m_signature;
    boost::optional<block> m_block;
};

inline std::ostream&  operator<<(std::ostream& stream, const ambiguous_member_declaration_signature_and_block& arg) { return stream; }

struct ambiguous_member_declaration  : node
{
    type m_type ;
    string_node m_identifier ;
    boost::optional<ambiguous_member_declaration_signature_and_block> m_signature_and_block;
};

inline std::ostream&  operator<<(std::ostream& stream, const ambiguous_member_declaration& arg) { return stream; }

struct static_ambiguous_member_declaration_signature_and_block : node
{
    static_function_signature m_signature;
    boost::optional<block> m_block;
};

inline std::ostream&  operator<<(std::ostream& stream, const static_ambiguous_member_declaration_signature_and_block& arg) { return stream; }

struct static_ambiguous_member_declaration  : node
{
    type m_type ;
    string_node m_identifier ;
    boost::optional<static_ambiguous_member_declaration_signature_and_block> m_signature_and_block;
};

inline std::ostream&  operator<<(std::ostream& stream, const static_ambiguous_member_declaration& arg) { return stream; }

struct virtual_member_function_declaration  : node
{
    type m_return_type;
    string_node m_identifier ;
    member_function_signature m_signature;
    boost::optional<uint> m_abstract;
    boost::optional<block> m_block;
};

inline std::ostream&  operator<<(std::ostream& stream, const virtual_member_function_declaration& arg) { return stream; }

typedef boost::variant<ambiguous_member_declaration, static_ambiguous_member_declaration, virtual_member_function_declaration> member_declaration;

inline std::ostream&  operator<<(std::ostream& stream, const member_declaration& expr)
{
    return stream;
}

struct class_inheritance : node
{
    fundamental_node<int> m_access_specifier;
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

struct class_declaration : node
{
    fundamental_node<bool> m_is_struct;
    named_or_unnamed_class_declaration m_named_or_unnamed_class_declaration;
};

inline std::ostream&  operator<<(std::ostream& stream, const class_declaration& arg) { return stream; }


typedef boost::variant<type, class_declaration> type_or_class_declaration;

inline std::ostream&  operator<<(std::ostream& stream, const type_or_class_declaration& expr)
{
    return stream;
}

struct typedef_declaration : node
{
    type_or_class_declaration m_type;
    string_node m_name;
};

inline std::ostream&  operator<<(std::ostream& stream, const typedef_declaration& arg) { return stream; }

typedef boost::variant<fundamental_node<int>, typedef_declaration, member_declaration, class_declaration> class_member_declaration;

inline std::ostream&  operator<<(std::ostream& stream, const class_member_declaration& expr)
{
    return stream;
}

typedef phantom::vector<class_member_declaration> class_member_declarations;

struct class_scope : node
{
    class_inheritances m_class_inheritances;
    class_member_declarations m_class_member_declarations;
};

inline std::ostream&  operator<<(std::ostream& stream, const class_scope& arg) { return stream; }

struct class_variable_declarator : node
{
    variable_declarator m_variable_declarator;
    extra_variable_declarators m_extra_variable_declarators;
};

inline std::ostream&  operator<<(std::ostream& stream, const class_variable_declarator& arg) { return stream; }

struct named_class_declaration : node
{
    string_node m_name;
    boost::optional<class_scope> m_class_scope; 
    boost::optional<class_variable_declarator> m_variable_declarator;
};

inline std::ostream&  operator<<(std::ostream& stream, const named_class_declaration& arg) { return stream; }

struct unnamed_class_declaration : node
{
    class_scope m_class_scope; 
    class_variable_declarator m_variable_declarator;
};

inline std::ostream&  operator<<(std::ostream& stream, const unnamed_class_declaration& arg) { return stream; }

struct namespace_declaration;

typedef boost::variant<ambiguous_global_declaration, class_declaration, boost::recursive_wrapper<namespace_declaration>, typedef_declaration> namespace_member_declaration;

inline std::ostream&  operator<<(std::ostream& stream, const namespace_member_declaration& expr)
{
    return stream;
}

typedef vector<namespace_member_declaration> namespace_scope;

typedef vector<string_node> namespace_alias;

typedef boost::variant<namespace_alias, namespace_scope> namespace_alias_or_scope;

inline std::ostream&  operator<<(std::ostream& stream, const namespace_alias_or_scope& expr)
{
    return stream;
}

struct namespace_declaration : node
{
    string_node m_name;
    namespace_alias_or_scope m_alias_or_scope;
};

inline std::ostream&  operator<<(std::ostream& stream, const namespace_declaration& arg) { return stream; }


typedef namespace_scope compilation_unit;


}}

o_namespace_end(phantom, reflection)


#endif // ast_h__
