#ifndef o_reflection_eval_cpp_language_grammar_h__
#define o_reflection_eval_cpp_language_grammar_h__

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

///////////////////////////////////////////////////////////////////////////////
// Comment/Uncomment this if you want to disable/enable debugging
// #define BOOST_SPIRIT_QI_DEBUG 
///////////////////////////////////////////////////////////////////////////////

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
#include "ast.h"
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include "ast_adapted_structs.h"
#include "phantom/Message.h"

#define o_reflection_cpp_grammar_rule(name) \
    BOOST_SPIRIT_DEBUG_NODE(name); \
    qi::on_success(name, success_handler_function()(qi::_val, qi::_1, qi::_3));\
    qi::on_error<qi::fail>(name, error_handler_function()(&m_pMessage, #name, qi::_val, qi::_1, qi::_3));

#define o_reflection_cpp_grammar_rule_A(r, _, name) \
    o_reflection_cpp_grammar_rule(name)

#define o_reflection_cpp_grammar_rules(seq) \
    BOOST_PP_SEQ_FOR_EACH(o_reflection_cpp_grammar_rule_A, _, seq)

o_namespace_begin(phantom, reflection, cpp)

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

struct success_handler
{
    template <typename, typename, typename>
    struct result { typedef void type; };

    template <typename Attribute, typename Iter1, typename Iter2>
    void operator()(Attribute& attribute, Iter1 begin, Iter2 end) const
    {
        auto first = begin->begin(); 
        auto last = end->end();
        auto firstPos = first.get_position();                                                      
        auto lastPos = last.get_position();                                                    
        /*std::string str(first.base(), last.base());
        std::cout<<firstPos.line<<'|'<<firstPos.column<<" - "<<lastPos.line<<'|'<<lastPos.column<<" : "<<str<<std::endl;*/
        ast::location_assigner<Attribute>::set(attribute, CodeLocation(CodePosition(firstPos.file, firstPos.line, firstPos.column)
                                                                , CodePosition(lastPos.file, lastPos.line, lastPos.column))
                                                                , &(*first.base())
                                                                , last.base()-first.base()
                                                                );
    }
};

struct error_handler
{
    template <typename, typename, typename, typename, typename>
    struct result { typedef void type; };

    error_handler() {}

    template <typename Message, typename RuleText, typename Attribute, typename Iter1, typename Iter2>
    void operator()(Message a_ppMessage, RuleText a_RuleText, Attribute& attribute, Iter1 begin, Iter2 end) const
    {
        auto first = begin->begin(); 
        auto last = end->end();
        auto firstPos = first.get_position();                                                      
        auto lastPos = last.get_position();                                                    
        std::string str(first.base(), last.base());
        if(*a_ppMessage)
        {
            (*a_ppMessage)->error(CodeLocation(CodePosition(firstPos.file, firstPos.line, firstPos.column)
                , CodePosition(lastPos.file, lastPos.line, lastPos.column)), "Expecting '%s' after '%s'", &a_RuleText[2], str.c_str());
        }
        else 
        {
            printf("Expecting '%s' after '%s'", &a_RuleText[2], str.c_str());
        }
    }

};

typedef boost::phoenix::function<success_handler> success_handler_function;
typedef boost::phoenix::function<error_handler> error_handler_function;

template <typename t_Iterator, typename t_Lexer>
struct grammar 
{
    typedef typename t_Lexer::base_iterator_type base_iterator_type;
    
    grammar(t_Lexer const& l);

    template<typename t_Attribute, typename t_BaseIterator>
    bool parse( t_BaseIterator& a_First
        , t_BaseIterator a_Last
        , const qi::rule<t_Iterator, t_Attribute()>& a_Rule
        , t_Attribute& a_Result
        , SourceFile* a_pSourceFile = nullptr
        , Message* a_pMessage = nullptr  )
    {
        base_iterator_type position_begin(a_First, a_Last, a_pSourceFile);
        base_iterator_type position_end;
        setMessage(a_pMessage);
        return boost::spirit::lex::tokenize_and_parse(position_begin, position_end
            , m_lexer, boost::spirit::qi::grammar<t_Iterator, t_Attribute()>(a_Rule), a_Result);
    }

    void setMessage(Message* a_pMessage) { m_pMessage = a_pMessage; }

    Message* m_pMessage;

    t_Lexer const& m_lexer;

    // ELEMENT
    qi::rule<t_Iterator, ast::element()>                                r_element;
    qi::rule<t_Iterator, ast::type()>                                   r_type;
    qi::rule<t_Iterator, ast::name()>                                   r_this_name;
    qi::rule<t_Iterator, ast::qualified_name()>                         r_this;
    qi::rule<t_Iterator, phantom::string()>                             r_signed_type;
    qi::rule<t_Iterator, phantom::string()>                             r_unsigned_type;
    qi::rule<t_Iterator, phantom::string()>                             r_signable_type;
    qi::rule<t_Iterator, ast::name()>                                   r_fundamental_type_name;
    qi::rule<t_Iterator, ast::qualified_name()>                         r_fundamental_type;
    qi::rule<t_Iterator, ast::string_node()>                            r_operator;
    qi::rule<t_Iterator, phantom::string()>                             r_operator_name;
    qi::rule<t_Iterator, ast::fundamental_node<char>()>                 r_type_qualifier;
    qi::rule<t_Iterator, ast::fundamental_node<char>()>                 r_const_qualifier;
    qi::rule<t_Iterator, ast::qualifier_or_extent()>                    r_qualifier_or_extent;
    qi::rule<t_Iterator, phantom::vector<ast::qualifier_or_extent>()>   r_qualifier_or_extents;
    qi::rule<t_Iterator, ast::string_node()>                            r_identifier;
    qi::rule<t_Iterator, ast::template_element()>                       r_template_element;
    qi::rule<t_Iterator, vector<ast::template_element>()>               r_template_element_list;
    qi::rule<t_Iterator, ast::name()>                                   r_name;
    qi::rule<t_Iterator, ast::string_node()>                            r_root_namespace;
    qi::rule<t_Iterator, ast::name()>                                   r_root_namespace_name;
    qi::rule<t_Iterator, ast::qualified_name()>                         r_qualified_name;
    qi::rule<t_Iterator, phantom::vector<ast::name>()>                  r_names;
    qi::rule<t_Iterator, ast::function_signature()>                     r_function_signature;
    qi::rule<t_Iterator, ast::function_signature()>                     r_type_list;
    qi::rule<t_Iterator, ast::function_prototype()>                     r_function_prototype;
    qi::rule<t_Iterator, vector<ast::template_element>()>               r_template_signature;

    // EXPRESSION
    qi::rule<t_Iterator, ast::expression() >                            r_expression;
    qi::rule<t_Iterator, phantom::vector<ast::expression>()>            r_expression_list;
    qi::rule<t_Iterator, ast::binary_right_expression() >               r_binary_assignment_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >               r_shift_assignment_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >               r_multiplicative_assignment_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >               r_additive_assignment_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >               r_assignment_expression ;
    qi::rule<t_Iterator, ast::ternary_if_expression() >                 r_ternary_if_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >               r_logical_or_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >               r_logical_and_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >               r_binary_or_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >               r_binary_xor_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >               r_binary_and_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >               r_equality_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >               r_greater_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >               r_lesser_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >               r_shift_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >               r_additive_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >               r_multiplicative_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >               r_member_pointer_expression ;
    qi::rule<t_Iterator, ast::pre_unary_expression() >                  r_reference_expression ;
    qi::rule<t_Iterator, ast::pre_unary_expression() >                  r_dereference_expression ;
    qi::rule<t_Iterator, ast::cast_expression() >                       r_static_cast_expression ;
    qi::rule<t_Iterator, ast::cast_expression() >                       r_cast_expression ;
    qi::rule<t_Iterator, ast::cast_type() >                             r_cast_type ;
    qi::rule<t_Iterator, ast::pre_unary_expression() >                  r_unary_logical_expression ;
    qi::rule<t_Iterator, ast::pre_unary_expression() >                  r_unary_arithmetic_expression ;
    qi::rule<t_Iterator, ast::pre_unary_expression() >                  r_pre_dec_inc_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >               r_indirection_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >               r_member_access_expression ;
    qi::rule<t_Iterator, ast::call_expression() >                       r_call_expression;
    qi::rule<t_Iterator, ast::bracket_expression() >                    r_bracket_expression;
    qi::rule<t_Iterator, ast::argument_list() >                         r_argument_list;
    qi::rule<t_Iterator, ast::post_unary_expression() >                 r_post_dec_inc_expression ;
    qi::rule<t_Iterator, ast::expression() >                            r_primary_expression;
    qi::rule<t_Iterator, ast::expression() >                            r_complex_primary_expression;
    qi::rule<t_Iterator, ast::expression() >                            r_grouped_expression;
    qi::rule<t_Iterator, ast::fundamental_literal() >                   r_fundamental_literal;
    qi::rule<t_Iterator, ast::fundamental_node<hex_t>() >               r_hex;
    qi::rule<t_Iterator, ast::fundamental_node<float>() >               r_float;
    qi::rule<t_Iterator, ast::fundamental_node<double>() >              r_double;
    qi::rule<t_Iterator, ast::fundamental_node<longdouble>() >          r_longdouble;
    qi::rule<t_Iterator, ast::fundamental_node<uint>() >                r_uint;
    qi::rule<t_Iterator, ast::fundamental_node<ulonglong>() >           r_ulonglong;
    qi::rule<t_Iterator, ast::fundamental_node<char>()>                 r_char;
    qi::rule<t_Iterator, ast::fundamental_node<bool>()>                 r_bool;
    qi::rule<t_Iterator, ast::fundamental_node<std::nullptr_t>()>       r_nullptr;


    qi::rule<t_Iterator, ast::integral_literal() >                      r_integral_literal;
    qi::rule<t_Iterator, ast::string_node() >                           r_string_literal;
    qi::rule<t_Iterator, ast::fundamental_node<char>() >                r_char_literal;
    qi::rule<t_Iterator, ast::fundamental_node<char>() >                r_escape_char;
    qi::rule<t_Iterator, ast::literal() >                               r_literal;


    // STATEMENTS
    qi::rule<t_Iterator, ast::block()>                                  r_block;
    qi::rule<t_Iterator, ast::statement() >                             r_statement;
    qi::rule<t_Iterator, ast::statements() >                            r_statements;
    qi::rule<t_Iterator, ast::expression() >                            r_expression_statement;
    qi::rule<t_Iterator, ast::if_statement() >                          r_if_statement;
    qi::rule<t_Iterator, ast::statement() >                             r_else_statement;
    qi::rule<t_Iterator, ast::for_statement() >                         r_for_statement;
    qi::rule<t_Iterator, ast::variable_declaration_or_expression() >    r_variable_declaration_or_expression;
    qi::rule<t_Iterator, ast::while_statement() >                       r_while_statement;
    qi::rule<t_Iterator, ast::do_while_statement() >                    r_do_while_statement;
    qi::rule<t_Iterator, ast::switch_statement()  >                     r_switch_statement;
    qi::rule<t_Iterator, ast::statement_or_case_labels()  >             r_switch_block;
    qi::rule<t_Iterator, ast::statement_or_case_label()  >              r_statement_or_case_label;
    qi::rule<t_Iterator, ast::case_label()  >                           r_case_label;
    qi::rule<t_Iterator, ast::fundamental_node<bool>()>                 r_static;
    qi::rule<t_Iterator, ast::variable_declaration() >                  r_variable_declaration;
    qi::rule<t_Iterator, ast::variable_declaration() >                  r_variable_declaration_statement;
    qi::rule<t_Iterator, ast::template_element() >                      r_extent;
    qi::rule<t_Iterator, ast::array_initializer() >                     r_array_initializer;
    qi::rule<t_Iterator, ast::variable_declarator() >                   r_variable_declarator;
    qi::rule<t_Iterator, ast::variable_declarator_end() >               r_variable_declarator_end;
    qi::rule<t_Iterator, ast::extra_variable_declarator() >             r_extra_variable_declarator;
    qi::rule<t_Iterator, ast::extra_variable_declarators() >            r_extra_variable_declarators;
    qi::rule<t_Iterator, ast::string_node() >                           r_keyword_statement;
    qi::rule<t_Iterator, ast::label_statement() >                       r_label_statement;
    qi::rule<t_Iterator, ast::goto_statement() >                        r_goto_statement;
    qi::rule<t_Iterator, ast::return_statement() >                      r_return_statement;

    qi::rule<t_Iterator, ast::member_function_signature()>              r_member_function_signature;
    qi::rule<t_Iterator, ast::static_function_signature()>              r_static_function_signature;
    qi::rule<t_Iterator, ast::virtual_member_function_declaration()>    r_virtual_member_function_declaration;
    qi::rule<t_Iterator, ast::ambiguous_member_declaration()>           r_ambiguous_member_declaration;
    qi::rule<t_Iterator, ast::ambiguous_global_declaration()>           r_ambiguous_global_declaration;
    qi::rule<t_Iterator, ast::ambiguous_member_declaration_signature_and_block()> r_ambiguous_member_declaration_signature_and_block;
    qi::rule<t_Iterator, ast::ambiguous_global_declaration_signature_and_block()> r_ambiguous_global_declaration_signature_and_block;
    qi::rule<t_Iterator, ast::ambiguous_global_declaration_signature_and_block_or_declarator()> r_ambiguous_global_declaration_signature_and_block_or_declarator;
    qi::rule<t_Iterator, ast::static_ambiguous_member_declaration()>    r_static_ambiguous_member_declaration;
    qi::rule<t_Iterator, ast::static_ambiguous_member_declaration_signature_and_block()> r_static_ambiguous_member_declaration_signature_and_block;
    qi::rule<t_Iterator, ast::class_declaration()>                      r_class_declaration;
    qi::rule<t_Iterator, ast::fundamental_node<bool>()>                 r_struct_or_class;
    qi::rule<t_Iterator, ast::named_class_declaration()>                r_named_class_declaration;
    qi::rule<t_Iterator, ast::unnamed_class_declaration()>              r_unnamed_class_declaration;
    qi::rule<t_Iterator, ast::class_variable_declarator()>              r_class_variable_declarator;
    qi::rule<t_Iterator, ast::class_inheritance()>                      r_class_inheritance ;
    qi::rule<t_Iterator, ast::class_inheritances()>                     r_class_inheritances;
    qi::rule<t_Iterator, ast::class_scope()>                            r_class_scope;
    qi::rule<t_Iterator, ast::parameter()>                              r_parameter;
    qi::rule<t_Iterator, ast::fundamental_node<unsigned long long>()>   r_access_specifier;
    qi::rule<t_Iterator, ast::fundamental_node<unsigned long long>()>   r_access_declaration;
    qi::rule<t_Iterator, ast::member_declaration()>                     r_member_declaration;
    qi::rule<t_Iterator, ast::namespace_member_declaration()>           r_namespace_member_declaration;
    qi::rule<t_Iterator, ast::string_node()>                             r_namespace_declarator;
    qi::rule<t_Iterator, ast::namespace_scope()>                        r_namespace_scope;
    qi::rule<t_Iterator, ast::namespace_declaration()>                  r_namespace_declaration;
    qi::rule<t_Iterator, ast::namespace_alias()>                          r_namespace_alias_assign;
    qi::rule<t_Iterator, ast::typedef_declaration()>                    r_typedef_declaration;
    qi::rule<t_Iterator, ast::compilation_unit()>                       r_compilation_unit;
    
};

template <typename t_Iterator, typename t_Lexer>
grammar<t_Iterator, t_Lexer>::grammar(t_Lexer const& l)
    : m_lexer(l)
    , m_pMessage(nullptr)
{
    qi::_1_type _1;
    qi::_2_type _2;
    qi::_3_type _3;
    qi::_4_type _4;

    qi::_val_type _val;

    using qi::on_error;
    using qi::on_success;
    using qi::fail;
    using boost::phoenix::function;
    using boost::spirit::omit;

    /*typedef function<client::annotation<Iterator> > annotation_function;*/

    qi::tokenid_mask_type tkm;
    qi::tokenid_type tk;

    r_type %= -(r_const_qualifier) >> (r_qualified_name|r_fundamental_type) >> r_qualifier_or_extents;

    r_element %= r_type >> -r_function_prototype;

    r_identifier = l.t_identifier [qi::_val = qi::_1];

    r_operator = r_operator_name [qi::_val = qi::_1];

    r_operator_name = m_lexer("operator")[qi::_val = "operator"] >> (tkm(op_category::overloadable)[qi::_val = qi::_val + boost::phoenix::bind(&token_ids::operator_string_from_token_id, qi::_1)]
                                                                | (tk(token_ids::left_bracket) [qi::_val = qi::_val + boost::phoenix::bind(&token_ids::operator_string_from_token_id, qi::_1)] 
                                                                   >> tk(token_ids::right_bracket) [qi::_val = qi::_val + boost::phoenix::bind(&token_ids::operator_string_from_token_id, qi::_1)] 
                                                                   ));

    r_fundamental_type_name = (m_lexer("long") >> m_lexer("double"))[qi::_val = "long double"] 
    | r_signable_type [qi::_val = qi::_1]
    | r_unsigned_type [qi::_val = qi::_1]
    | r_signed_type [qi::_val = qi::_1]
    | m_lexer("float")[qi::_val = "float"] 
    | m_lexer("double")[qi::_val = "double"]
    | m_lexer("bool")[qi::_val = "bool"]
    | m_lexer("void")[qi::_val = "void"];
    
    r_fundamental_type = r_fundamental_type_name[boost::phoenix::push_back(qi::_val, qi::_1)];

    r_signed_type = m_lexer("signed") [qi::_val = "signed"] >> r_signable_type[qi::_val = qi::_val + ' ' + qi::_1] ;;
    r_unsigned_type = m_lexer("unsigned")[qi::_val = "unsigned"] >> r_signable_type[qi::_val = qi::_val + ' ' + qi::_1] ;

    r_signable_type = (m_lexer("long")>>m_lexer("long"))[qi::_val = "long long"] 
    | m_lexer("long")[qi::_val = "long"]
    | m_lexer("short")[qi::_val = "short"]
    | m_lexer("int")[qi::_val = "int"]
    | m_lexer("char")[qi::_val = "char"];

    r_name %= (r_identifier|r_operator) >> -r_template_signature;

    r_root_namespace = omit[tk(token_ids::double_colon)][qi::_val = ""];

    r_root_namespace_name %= r_root_namespace;

    r_qualified_name = -r_root_namespace_name[boost::phoenix::push_back(qi::_val, qi::_1)] 
                        >> r_name[boost::phoenix::push_back(qi::_val, qi::_1)] % omit[tk(token_ids::double_colon)];

    r_type_qualifier = (tk(token_ids::times) [qi::_val = '*'])
        | (tk(token_ids::bit_and) [qi::_val = '&'])
        | (m_lexer("const") [qi::_val = 'µ'])  ;

    r_template_element_list %= r_template_element % (',');

    r_template_element %= r_type | r_integral_literal;

    r_hex = l.t_hex [qi::_val = qi::_1];
    r_uint = l.t_uint [qi::_val = qi::_1];
    r_ulonglong = l.t_ulonglong [qi::_val = qi::_1];
    r_bool = l.t_true_or_false [qi::_val = qi::_1];
    r_char = l.t_char [qi::_val = qi::_1];

    r_integral_literal %= 
        r_hex
        | r_uint
        | r_ulonglong
        | r_bool
        | r_char;

    r_template_signature %= omit[tk(token_ids::less)] >> r_template_element_list >> omit[tk(token_ids::greater)];

    r_type_list %= r_type % ',';

    r_function_signature %= '(' >> -r_type_list >> ')';

    r_function_prototype %= r_function_signature >> -r_const_qualifier;

    r_qualifier_or_extent %= r_type_qualifier|r_extent;

    r_qualifier_or_extents %= *r_qualifier_or_extent;

    r_const_qualifier = (m_lexer("const") [qi::_val = 'µ']);

    r_extent %= '[' >> r_template_element >> ']';


    r_float = l.t_float [qi::_val = qi::_1];
    r_double = l.t_double [qi::_val = qi::_1];
    r_longdouble = l.t_longdouble [qi::_val = qi::_1];
    r_nullptr = m_lexer("nullptr") [qi::_val = nullptr];

    r_fundamental_literal %= 
    r_hex
    | r_float
    | r_double
    | r_longdouble
    | r_uint
    | r_ulonglong
    | r_bool
    | r_char
    | r_nullptr;

    r_expression %= r_binary_assignment_expression;
    
    r_binary_assignment_expression %= r_shift_assignment_expression >> *(tkm(op_category::assignment_shift) >> r_binary_assignment_expression);
    
    r_shift_assignment_expression %= r_multiplicative_assignment_expression >> *(tkm(op_category::assignment_shift) >> r_shift_assignment_expression);
    
    r_multiplicative_assignment_expression %= r_additive_assignment_expression >> *(tkm(op_category::assignment_multiplicative) >> r_multiplicative_assignment_expression);
    
    r_additive_assignment_expression %= r_assignment_expression >> *(tkm(op_category::assignment_additive) >> r_additive_assignment_expression);
    
    r_assignment_expression %= r_ternary_if_expression >> *(tk(token_ids::assign) >> r_assignment_expression);

    r_ternary_if_expression %= r_logical_or_expression >> *('?' >> r_expression >> ':' >> r_logical_or_expression);

    r_logical_or_expression %= r_logical_and_expression >> *(tkm(op::logical_or) >> r_logical_and_expression);

    r_logical_and_expression %= r_binary_or_expression >> *(tkm(op::logical_and) >> r_binary_or_expression);

    r_binary_or_expression %= r_binary_xor_expression >> *(tkm(op::bit_or) >> r_binary_xor_expression);

    r_binary_xor_expression %= r_binary_and_expression >> *(tkm(op::bit_xor) >> r_binary_and_expression);

    r_binary_and_expression %= r_equality_expression >> *(tkm(op::bit_and) >> r_equality_expression);

    r_equality_expression %= r_greater_expression >> *(tkm(op_category::equality) >> r_greater_expression);

    r_greater_expression %= r_lesser_expression >> *(tkm(op_category::greater) >> r_lesser_expression);

    r_lesser_expression %= r_shift_expression >> *(tkm(op_category::lesser) >> r_shift_expression);

    r_shift_expression %= r_additive_expression >> *(tkm(op_category::shift) >> r_additive_expression);

    r_additive_expression %= r_multiplicative_expression >> *(tkm(op_category::additive) >> r_multiplicative_expression);

    if(true)
    {
        r_multiplicative_expression %= r_member_pointer_expression >> *(tkm(op_category::multiplicative) >> r_member_pointer_expression);

        r_member_pointer_expression %= r_reference_expression >> *(tkm(op_category::member_pointer) >> r_reference_expression);

        r_reference_expression %= (+tkm(op_category::reference) >> r_reference_expression) | r_dereference_expression;

        r_dereference_expression %= (+tkm(op::times) >> r_reference_expression) | r_unary_logical_expression/*r_cast_expression*/;
    }
    else 
    {
        r_multiplicative_expression %= r_unary_logical_expression/*r_cast_expression*/ >> *(tkm(op_category::multiplicative) >> r_member_pointer_expression);
    }

//     r_cast_type %= '(' >> r_type >> ')';
// 
//     r_cast_expression %= (+r_cast_type >> -r_reference_expression) | r_unary_logical_expression;

    r_unary_logical_expression %= (+tkm(op_category::unary_binary_logical) >> r_reference_expression) | r_unary_arithmetic_expression;

    r_unary_arithmetic_expression %= (+tkm(op_category::additive) >> r_reference_expression) | r_pre_dec_inc_expression;

    if(true)
    {
        r_pre_dec_inc_expression %= (+tkm(op_category::inc_dec) >> r_reference_expression) | r_indirection_expression;

        r_indirection_expression %= r_member_access_expression >> *(tkm(op::minus_greater) >> r_member_access_expression);
    }
    else 
    {
        r_pre_dec_inc_expression %= (+tkm(op_category::inc_dec) >> r_reference_expression) | r_member_access_expression;
    }

    r_member_access_expression %= r_bracket_expression >> *(tkm(op::dot) >> r_bracket_expression);

    r_bracket_expression %= r_call_expression >> *('[' >> r_expression >> ']');

    r_argument_list %= '(' >> -(r_expression % ',') >> ')';

    r_call_expression %= r_post_dec_inc_expression >> *r_argument_list;

    r_post_dec_inc_expression %= r_primary_expression >> *tkm(op_category::inc_dec);

    r_primary_expression %= r_literal | r_complex_primary_expression;

    r_string_literal = l.t_string [qi::_val = qi::_1];

    r_literal %= r_fundamental_literal | r_string_literal; 

    r_static_cast_expression %= m_lexer("static_cast") > omit[tk(token_ids::less)] > r_type > omit[tk(token_ids::greater)] > '(' > r_expression > ')';

    r_cast_expression %= r_static_cast_expression;

    r_complex_primary_expression %= r_qualified_name | r_this | r_grouped_expression | r_cast_expression;

    r_grouped_expression %= '(' >> r_expression >> ')';

    r_expression_list %= r_expression % ',';

    r_this_name = m_lexer("this")[qi::_val = "this"];

    r_this = r_this_name[boost::phoenix::push_back(qi::_val, qi::_1)];

    

    r_statement %= 
          r_block
        | r_label_statement
        | r_variable_declaration_statement
        | r_if_statement
        | r_for_statement
        | r_while_statement
        | r_do_while_statement
        | r_switch_statement
        | r_goto_statement
        | r_return_statement
        | r_keyword_statement
        | r_expression_statement
        ;


    r_array_initializer %= '{' >> r_expression_list >> '}';
 
     r_variable_declarator_end %= *r_extent >> -(omit[tk(token_ids::assign)] >> (r_expression|r_array_initializer));

     r_variable_declarator %= r_identifier >> r_variable_declarator_end;

    r_static = m_lexer("static")[qi::_val = true];

    r_extra_variable_declarators %= -(r_extra_variable_declarator % ','); 

    r_variable_declaration %= -r_static >> r_type >> r_variable_declarator >> r_extra_variable_declarators;

    r_extra_variable_declarator %= -r_type_qualifier >> r_variable_declarator;

    r_variable_declaration_statement %= r_variable_declaration >> ';';

    r_expression_statement %= r_expression >> ';';

    r_statements %= *(';'|r_statement);

    r_block %= '{' >> r_statements >> '}';

    r_else_statement %= m_lexer("else") > r_statement;

    r_keyword_statement = m_lexer("break")[qi::_val = "break"] | m_lexer("continue")[qi::_val = "continue"];

    r_goto_statement %= m_lexer("goto") > r_identifier;

    r_return_statement %= m_lexer("return") >> -r_expression >> ';';

    r_label_statement %= r_identifier >> ':';

    r_if_statement %= m_lexer("if") > '(' > r_variable_declaration_or_expression > ')' > r_statement > -r_else_statement;

    r_while_statement %= m_lexer("while") > '(' > r_variable_declaration_or_expression > ')' > (r_statement | ';');

    r_do_while_statement %= m_lexer("do") > r_statement > m_lexer("while") > '(' > r_expression > ')' > ';';

    r_variable_declaration_or_expression %= r_variable_declaration | r_expression;

    r_for_statement %= m_lexer("for") > '(' >> -r_variable_declaration_or_expression > ';' >> -r_expression > ';' >> -(r_expression % ';') > ')' > (r_statement | ';');

    r_case_label %= ((m_lexer("case") > r_template_element) | m_lexer("default")) > ':';

    r_statement_or_case_label %= r_statement|r_case_label;

    r_switch_block %= '{' >> *r_statement_or_case_label > '}';

    r_switch_statement %= m_lexer("switch") > '(' > r_variable_declaration_or_expression > ')' > r_switch_block;

    r_parameter %= r_type >> -r_variable_declarator;

    r_block %= '{' >> *r_statement >> '}';

    r_member_function_signature %= '(' >> -(r_parameter % ',') >> ')' >> -r_const_qualifier ;

    r_static_function_signature %= '(' >> -(r_parameter % ',') >> ')';

    r_ambiguous_member_declaration_signature_and_block %= r_member_function_signature >> (';'|r_block);

    r_ambiguous_member_declaration %= r_type >> r_identifier >> (';'| r_ambiguous_member_declaration_signature_and_block) ;

     r_ambiguous_global_declaration_signature_and_block %= r_static_function_signature >> (';'|r_block);
 
     r_ambiguous_global_declaration_signature_and_block_or_declarator %= r_ambiguous_global_declaration_signature_and_block | r_variable_declarator_end;
 
     r_ambiguous_global_declaration %= -r_static >> r_type >> r_identifier >> (';'| r_ambiguous_global_declaration_signature_and_block_or_declarator) ;

    r_static_ambiguous_member_declaration_signature_and_block %= r_static_function_signature >> (';'|r_block);

    r_static_ambiguous_member_declaration %= m_lexer("static") >> r_type >> r_identifier >> (';'|r_static_ambiguous_member_declaration_signature_and_block) ;

    r_virtual_member_function_declaration %= m_lexer("virtual") >> r_type >> r_identifier >> r_member_function_signature >> -(omit[tk(token_ids::assign)] >> l.t_uint) >> (';'|r_block);

    r_access_specifier %= m_lexer("public")   [qi::_val = o_public_access] 
    | m_lexer("protected")[qi::_val = o_protected_access] 
    | m_lexer("private")  [qi::_val = 0];

    r_access_declaration %= r_access_specifier >> ':';

    r_member_declaration %= r_virtual_member_function_declaration 
        | r_ambiguous_member_declaration 
        | r_static_ambiguous_member_declaration;

    r_class_inheritance %= -(r_access_specifier) >> r_qualified_name;

    r_class_inheritances %=  ':' >> r_class_inheritance %  ',';

    r_class_variable_declarator %= r_variable_declarator >> -(r_extra_variable_declarator % ',');

    r_unnamed_class_declaration %= r_class_scope >> r_class_variable_declarator;

    r_named_class_declaration %= r_identifier >> -r_class_scope >> -r_class_variable_declarator ;

    r_struct_or_class = m_lexer("class")[qi::_val = false] | m_lexer("struct")[qi::_val = true];

    r_class_declaration %= r_struct_or_class >> (r_unnamed_class_declaration | r_named_class_declaration) >> ';'; 

    r_class_scope %= -(r_class_inheritances) >> '{' >> *(r_access_declaration | r_member_declaration | r_class_declaration | r_typedef_declaration) >> '}' ; 

    r_namespace_declarator %= m_lexer("namespace") > r_identifier;

    r_namespace_alias_assign = omit[tk(token_ids::assign)] >> -r_root_namespace >> (r_identifier % omit[tk(token_ids::double_colon)]) >> ';';

    r_namespace_declaration %= r_namespace_declarator >> (r_namespace_alias_assign | r_namespace_scope);

    r_typedef_declaration %= m_lexer("typedef") >> (r_type|r_class_declaration) >> r_identifier;

    r_namespace_scope %= '{' >> *r_namespace_member_declaration >> '}';

     r_namespace_member_declaration %= r_namespace_declaration | r_ambiguous_global_declaration | r_class_declaration | r_typedef_declaration;

    r_compilation_unit %= *r_namespace_member_declaration;

    o_reflection_cpp_grammar_rules(
        (r_element)
        (r_type)
        (r_fundamental_type)
        (r_operator)
        (r_type_qualifier)
        (r_const_qualifier)
        (r_extent)
        (r_qualifier_or_extent)
        (r_qualifier_or_extents)
        (r_identifier)
        (r_template_element)
        (r_template_element_list)
        (r_name)
        (r_qualified_name)
        (r_function_signature)
        (r_function_prototype)
        (r_template_signature)
        (r_expression)
        (r_expression_list)
        (r_binary_assignment_expression )
        (r_shift_assignment_expression )
        (r_multiplicative_assignment_expression )
        (r_additive_assignment_expression )
        (r_assignment_expression )
        (r_ternary_if_expression )
        (r_logical_or_expression )
        (r_logical_and_expression )
        (r_binary_or_expression )
        (r_binary_xor_expression )
        (r_binary_and_expression )
        (r_equality_expression )
        (r_greater_expression )
        (r_lesser_expression )
        (r_shift_expression )
        (r_additive_expression )
        (r_multiplicative_expression )
        (r_member_pointer_expression )
        (r_reference_expression )
        (r_dereference_expression )
        (r_cast_expression )
        (r_cast_type )
        (r_unary_logical_expression )
        (r_unary_arithmetic_expression )
        (r_pre_dec_inc_expression )
        (r_indirection_expression )
        (r_member_access_expression )
        (r_call_expression )
        (r_post_dec_inc_expression )
        (r_primary_expression)
        (r_complex_primary_expression)
        (r_grouped_expression)
        (r_fundamental_literal)
        (r_string_literal)
        (r_char_literal)
        (r_escape_char)
        (r_literal)

        (r_block)
        (r_statement)
        (r_statements)
        (r_expression_statement)
        (r_if_statement)
        (r_else_statement)
        (r_for_statement)
        (r_while_statement)
        (r_do_while_statement)
        (r_switch_statement)
        (r_static)
        (r_variable_declaration)
        (r_variable_declaration_statement)
        (r_variable_declarator)
        (r_extra_variable_declarator)
        (r_extra_variable_declarators)
        (r_keyword_statement)
        (r_label_statement)
        (r_goto_statement)
        (r_member_function_signature)
        (r_static_function_signature)
        (r_virtual_member_function_declaration)
        (r_ambiguous_member_declaration)
        (r_static_ambiguous_member_declaration)
        (r_class_declaration)
        (r_struct_or_class)
        (r_named_class_declaration)
        (r_unnamed_class_declaration)
        (r_class_variable_declarator)
        (r_class_inheritance )
        (r_class_inheritances)
        (r_class_scope)
        (r_parameter)
        (r_access_specifier)
        (r_access_declaration)
        (r_member_declaration)
        (r_namespace_member_declaration)
        (r_namespace_declarator)
        (r_namespace_scope)
        (r_namespace_declaration)
        (r_namespace_alias_assign)
        (r_typedef_declaration)
        (r_compilation_unit)

        );
}

o_namespace_end(phantom, reflection, cpp)

#endif // language_grammar_h__
