#ifndef o_reflection_eval_cpp_language_grammar_h__
#define o_reflection_eval_cpp_language_grammar_h__

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

///////////////////////////////////////////////////////////////////////////////
// Uncomment this if you want to enable debugging
// #define BOOST_SPIRIT_QI_DEBUG
///////////////////////////////////////////////////////////////////////////////

#include <boost/spirit/include/qi.hpp>
#include "ast.h"
#include "error_handler.h"
#include <vector>

o_namespace_begin(phantom, reflection, cpp)

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename t_Iterator, typename t_Lexer>
struct grammar 
{
    typedef typename t_Lexer::base_iterator_type base_iterator_type;

    typedef error_handler<typename t_Lexer::base_iterator_type, t_Iterator> error_handler_type;
    
    grammar(t_Lexer const& l);

    void bind_error_handler(error_handler_type& a_ErrorHandler)
    {
        typedef boost::phoenix::function<error_handler_type> error_handler_function;

        ///////////////////////////////////////////////////////////////////////
        // Error handling: on error in expr, call error_handler.
//         on_error<fail>(expr,
//             error_handler_function(a_ErrorHandler)(
//             "Error! Expecting ", _4, _3));

        ///////////////////////////////////////////////////////////////////////
        // Annotation: on success in primary_expr, call annotation.
//         on_success(primary_expr,
//             annotation_function(a_ErrorHandler.iters)(_val, _1));
    }

    template<typename t_Attribute>
    bool parse( base_iterator_type& a_First
        , base_iterator_type a_Last
        , const qi::rule<t_Iterator, t_Attribute()>& a_Rule
        , t_Attribute& a_Result )
    {
        error_handler_type eh(a_First, a_Last);
        bind_error_handler(eh);
        return boost::spirit::lex::tokenize_and_parse(a_First, a_Last
            , m_lexer, boost::spirit::qi::grammar<t_Iterator, t_Attribute()>(a_Rule), a_Result);
    }

    t_Lexer const& m_lexer;

    // ELEMENT
    qi::rule<t_Iterator, ast::element()>                            r_element;
    qi::rule<t_Iterator, phantom::string()>                         r_signed_type;
    qi::rule<t_Iterator, phantom::string()>                         r_unsigned_type;
    qi::rule<t_Iterator, phantom::string()>                         r_signable_type;
    qi::rule<t_Iterator, phantom::string()>                         r_fundamental_type;
    qi::rule<t_Iterator, ast::name()>                               r_fundamental_type_name;
    qi::rule<t_Iterator, phantom::string()>                         r_long_type;
    qi::rule<t_Iterator, phantom::string()>                         r_operator;
    qi::rule<t_Iterator, char()>                                    r_type_qualifier;
    qi::rule<t_Iterator, char()>                                    r_const_qualifier;
    qi::rule<t_Iterator, ast::extent_or_signature()>                r_extent;
    qi::rule<t_Iterator, ast::qualifier_or_extent_or_signature()>   r_qualifier_or_extent;
    qi::rule<t_Iterator, ast::qualifier_or_extent_or_signatures()>  r_qualifier_or_extents;
    qi::rule<t_Iterator, ast::qualifier_and_qualifier_or_extents()> r_qualifier_and_qualifier_or_extents;
    qi::rule<t_Iterator, ast::extent_or_signature()>                r_extent_or_function_signature;
    qi::rule<t_Iterator, ast::extent_or_signatures()>               r_extent_or_function_signatures;
    qi::rule<t_Iterator, char()>                                    r_compound_id;
    qi::rule<t_Iterator, ast::element_extension()>                  r_element_extension;
    qi::rule<t_Iterator, phantom::string()>                         r_identifier;
    qi::rule<t_Iterator, phantom::string()>                         r_operator_name;
    qi::rule<t_Iterator, ast::template_element()>                     r_template_element;
    qi::rule<t_Iterator, vector<ast::template_element>()>             r_template_element_list;
    qi::rule<t_Iterator, long long()>                                r_integral_constant;
    qi::rule<t_Iterator, ast::name()>                                r_name;
    qi::rule<t_Iterator, ast::qualified_name()>                      r_qualified_name;
    qi::rule<t_Iterator, ast::extent_or_signature()>                 r_function_signature;
    qi::rule<t_Iterator, ast::function_prototype()>                  r_function_prototype;
    qi::rule<t_Iterator, vector<ast::template_element>()>             r_template_signature;

    // EXPRESSION
    qi::rule<t_Iterator, ast::expression() >                 r_expression;
    qi::rule<t_Iterator, phantom::vector<ast::expression>()> r_expression_list;
    qi::rule<t_Iterator, ast::binary_left_expression() >     r_binary_assignment_expression ;
    qi::rule<t_Iterator, ast::binary_left_expression() >     r_shift_assignment_expression ;
    qi::rule<t_Iterator, phantom::string() >                 r_multiplicative_assignment_operator ;
    qi::rule<t_Iterator, ast::binary_left_expression() >     r_multiplicative_assignment_expression ;
    qi::rule<t_Iterator, ast::binary_left_expression() >     r_additive_assignment_expression ;
    qi::rule<t_Iterator, ast::binary_left_expression() >     r_assignment_expression ;
    qi::rule<t_Iterator, ast::ternary_if_expression() >      r_ternary_if_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >    r_logical_or_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >    r_logical_and_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >    r_binary_or_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >    r_binary_xor_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >    r_binary_and_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >    r_equality_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >    r_greater_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >    r_lesser_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >    r_shift_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >    r_additive_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >    r_multiplicative_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >    r_member_pointer_expression ;
    qi::rule<t_Iterator, ast::pre_unary_expression() >       r_reference_expression ;
    qi::rule<t_Iterator, ast::pre_unary_expression() >       r_dereference_expression ;
    qi::rule<t_Iterator, ast::cast_expression() >            r_cast_expression ;
    qi::rule<t_Iterator, ast::pre_unary_expression() >       r_unary_logical_expression ;
    qi::rule<t_Iterator, ast::pre_unary_expression() >       r_unary_arithmetic_expression ;
    qi::rule<t_Iterator, ast::pre_unary_expression() >       r_pre_dec_inc_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >    r_indirection_expression ;
    qi::rule<t_Iterator, ast::binary_right_expression() >    r_member_access_expression ;
    qi::rule<t_Iterator, ast::call_expression() >            r_call_expression ;
    qi::rule<t_Iterator, ast::post_unary_expression() >      r_post_dec_inc_expression ;
    qi::rule<t_Iterator, ast::expression() >                 r_primary_expression;
    qi::rule<t_Iterator, ast::expression() >                 r_complex_primary_expression;
    qi::rule<t_Iterator, ast::expression() >                 r_grouped_expression;
    qi::rule<t_Iterator, ast::fundamental_literal() >        r_fundamental_literal;
    qi::rule<t_Iterator, phantom::string() >                 r_string_literal;
    qi::rule<t_Iterator, char() >                            r_char_literal;
    qi::rule<t_Iterator, char() >                            r_escape_char;
    qi::rule<t_Iterator, ast::literal() >                    r_literal;

    // STATEMENTS
    qi::rule<t_Iterator, ast::block()>                               r_block;
    qi::rule<t_Iterator, ast::statement() >                          r_statement;
    qi::rule<t_Iterator, ast::statements() >                         r_statements;
    qi::rule<t_Iterator, ast::expression() >                         r_expression_statement;
    qi::rule<t_Iterator, ast::if_statement() >                       r_if_statement;
    qi::rule<t_Iterator, ast::statement() >                          r_else_statement;
    qi::rule<t_Iterator, ast::for_statement() >                      r_for_statement;
    qi::rule<t_Iterator, ast::for_init() >                           r_for_init;
    qi::rule<t_Iterator, ast::while_statement() >                    r_while_statement;
    qi::rule<t_Iterator, ast::do_while_statement() >                 r_do_while_statement;
    qi::rule<t_Iterator, ast::switch_statement()  >                  r_switch_statement;
    qi::rule<t_Iterator, bool()  >                                   r_static;
    qi::rule<t_Iterator, ast::variable_declaration() >               r_variable_declaration;
    qi::rule<t_Iterator, ast::variable_declaration() >               r_variable_declaration_statement;
    qi::rule<t_Iterator, ast::variable_declarator() >                r_variable_declarator;
    qi::rule<t_Iterator, ast::extra_variable_declarator() >          r_extra_variable_declarator;
    qi::rule<t_Iterator, ast::extra_variable_declarators() >         r_extra_variable_declarators;
    qi::rule<t_Iterator, phantom::string() >                         r_keyword_statement;
    qi::rule<t_Iterator, ast::label_statement() >                    r_label_statement;
    qi::rule<t_Iterator, ast::goto_statement() >                     r_goto_statement;

    qi::rule<t_Iterator, ast::member_function_signature()>          r_member_function_signature;
    qi::rule<t_Iterator, ast::static_member_function_signature()>   r_static_member_function_signature;
    qi::rule<t_Iterator, ast::virtual_member_function_declaration()>r_virtual_member_function_declaration;
    qi::rule<t_Iterator, ast::ambiguous_member_declaration()>       r_ambiguous_member_declaration;
    qi::rule<t_Iterator, ast::static_ambiguous_member_declaration()>r_static_ambiguous_member_declaration;
    qi::rule<t_Iterator, ast::class_declaration()>                  r_class_declaration;
    qi::rule<t_Iterator, bool()>                                    r_struct_or_class;
    qi::rule<t_Iterator, ast::named_class_declaration()>            r_named_class_declaration;
    qi::rule<t_Iterator, ast::unnamed_class_declaration()>          r_unnamed_class_declaration;
    qi::rule<t_Iterator, ast::class_variable_declarator()>          r_class_variable_declarator;
    qi::rule<t_Iterator, ast::class_inheritance()>                  r_class_inheritance ;
    qi::rule<t_Iterator, ast::class_inheritances()>                 r_class_inheritances;
    qi::rule<t_Iterator, ast::class_scope()>                        r_class_scope;
    qi::rule<t_Iterator, ast::parameter()>                          r_parameter;
    qi::rule<t_Iterator, int()>                                     r_access_specifier;
    qi::rule<t_Iterator, int()>                                     r_access_declaration;
    qi::rule<t_Iterator, ast::member_declaration()>                 r_member_declaration;
    qi::rule<t_Iterator, ast::namespace_member_declaration()>       r_namespace_member_declaration;
    qi::rule<t_Iterator, phantom::string()>                         r_namespace_declarator;
    qi::rule<t_Iterator, ast::namespace_scope()>                    r_namespace_scope;
    qi::rule<t_Iterator, ast::namespace_declaration()>              r_namespace_declaration;
    qi::rule<t_Iterator, vector<string>()>                          r_namespace_alias_assign;
    qi::rule<t_Iterator, ast::typedef_declaration()>                r_typedef_declaration;
    qi::rule<t_Iterator, ast::compilation_unit()>                   r_compilation_unit;
    
};


template <typename t_Iterator, typename t_Lexer>
grammar<t_Iterator, t_Lexer>::grammar(t_Lexer const& l)
    : m_lexer(l)
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

    r_fundamental_type_name %= r_fundamental_type;

    r_element %= -(r_const_qualifier) >> (r_qualified_name|r_fundamental_type) >> -r_element_extension;

    r_identifier %= l.t_identifier;

    r_operator = m_lexer("operator")[qi::_val = "operator"] >> tkm(op_category::overloadable)[qi::_val = qi::_1];

    r_fundamental_type = (m_lexer("long") >> m_lexer("double"))[qi::_val = "long double"] 
        | r_signable_type [qi::_val = qi::_1]
        | r_unsigned_type [qi::_val = qi::_1]
        | r_signed_type [qi::_val = qi::_1]
        | m_lexer("float")[qi::_val = "float"] 
        | m_lexer("double")[qi::_val = "double"]
        | m_lexer("bool")[qi::_val = "bool"]
        | m_lexer("void")[qi::_val = "void"];

    r_signed_type = m_lexer("signed") [qi::_val = "signed"] >> r_signable_type[qi::_val = qi::_val + ' ' + qi::_1] ;;
    r_unsigned_type = m_lexer("unsigned")[qi::_val = "unsigned"] >> r_signable_type[qi::_val = qi::_val + ' ' + qi::_1] ;

    r_signable_type = (m_lexer("long")>>m_lexer("long"))[qi::_val = "long long"] 
    | m_lexer("long")[qi::_val = "long"]
    | m_lexer("short")[qi::_val = "short"]
    | m_lexer("int")[qi::_val = "int"]
    | m_lexer("char")[qi::_val = "char"];

    r_name %= ((r_identifier|r_operator) >> -r_template_signature);

    r_qualified_name %= -omit[tk(token_ids::double_colon)] >> r_name % omit[tk(token_ids::double_colon)] ;

    r_type_qualifier = (tk(token_ids::times) [qi::_val = '*'])
                      | (tk(token_ids::bit_and) [qi::_val = '&'])
                      | (m_lexer("const") [qi::_val = 'µ']) 
                      | (tk(token_ids::brackets) [qi::_val = '$']) ;

    r_template_element_list %= r_template_element % omit[tk(token_ids::comma)];

    r_template_element %= r_element;

    r_template_signature %= omit[tk(token_ids::less)] >> r_template_element_list >> omit[tk(token_ids::greater)];

    r_function_signature %= tk(token_ids::left_paren) >> -r_expression_list >> tk(token_ids::right_paren);

    r_function_prototype %= r_function_signature >> -r_const_qualifier;

    r_qualifier_or_extent %= r_type_qualifier|r_extent;

    r_qualifier_or_extents %= *r_qualifier_or_extent;

    r_qualifier_and_qualifier_or_extents %= r_type_qualifier >> -r_qualifier_or_extents;

    r_extent %= tk(token_ids::left_bracket) >> r_expression >>  tk(token_ids::right_bracket) ;

    r_extent_or_function_signature = r_extent|r_function_signature;

    r_extent_or_function_signatures %= *r_extent_or_function_signature;

    r_element_extension %= r_qualifier_and_qualifier_or_extents
        | ( r_extent >> -( r_qualifier_and_qualifier_or_extents | r_extent_or_function_signatures ) )
        | ( r_function_prototype );

    r_const_qualifier = (m_lexer("const") [qi::_val = 'µ']);

    r_expression %= r_ternary_if_expression;

    //         r_binary_assignment_operator = m_lexer("&=") 
    //                                      | m_lexer("|=")
    //                                      | m_lexer("^=");
    // 
    //         r_binary_assignment_expression %= *(r_shift_assignment_expression >> r_binary_assignment_operator) >> r_shift_assignment_expression;
    // 
    //         r_shift_assignment_operator = m_lexer(">>=") 
    //                                     | m_lexer("<<=");
    // 
    //         r_shift_assignment_expression %= *(r_multiplicative_assignment_expression >> r_shift_assignment_operator) >> r_multiplicative_assignment_expression;
    // 
    //         r_multiplicative_assignment_operator = m_lexer("*=") 
    //                                              | m_lexer("/=")
    //                                              | m_lexer("%=");
    // 
    //         r_multiplicative_assignment_expression %= *(r_additive_assignment_expression >> r_multiplicative_assignment_operator) >> r_additive_assignment_expression;
    // 
    //         r_additive_assignment_operator = m_lexer("+=") 
    //                                        | m_lexer("-=");
    // 
    //         r_additive_assignment_expression %= *(r_assignment_expression >> r_additive_assignment_operator) >> r_assignment_expression;
    // 
    //         r_assignment_operator = m_lexer("=");
    // 
    //         r_assignment_expression %= *(r_ternary_if_expression >> r_assignment_operator) >> r_ternary_if_expression;

    r_ternary_if_expression %= r_logical_or_expression >> *(omit[tk(token_ids::question)] >> r_expression >> omit[tk(token_ids::colon)] >> r_logical_or_expression);

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

        r_reference_expression %= *tkm(op_category::reference) >> r_dereference_expression;

        r_dereference_expression %= *tkm(op::times) >> r_cast_expression;
    }
    else 
    {
        r_multiplicative_expression %= r_cast_expression >> *(tkm(op_category::multiplicative) >> r_member_pointer_expression);
    }

    r_cast_expression %= *(omit[tk(token_ids::left_paren)] >> r_element >> omit[tk(token_ids::right_paren)]) >> r_unary_logical_expression;

    r_unary_logical_expression %= *tkm(op_category::unary_binary_logical) >> r_unary_arithmetic_expression;

    r_unary_arithmetic_expression %= *tkm(op_category::additive) >> r_pre_dec_inc_expression;

    if(true)
    {
        r_pre_dec_inc_expression %= *tkm(op_category::inc_dec) >> r_indirection_expression;

        r_indirection_expression %= r_member_access_expression >> *(tkm(op::minus_greater) >> r_member_access_expression);
    }
    else 
    {
        r_pre_dec_inc_expression %= *tkm(op_category::inc_dec) >> r_member_access_expression;
    }

    r_member_access_expression %= r_call_expression >> *(tkm(op::dot) >> r_call_expression);

    r_call_expression %= r_post_dec_inc_expression >> r_extent_or_function_signatures;

    r_post_dec_inc_expression %= r_primary_expression >> *tkm(op_category::inc_dec);

    r_primary_expression %= r_literal | r_complex_primary_expression;

    r_fundamental_literal %= l.t_float
        | l.t_double
        | l.t_longdouble
        | l.t_int
        | l.t_uint
        | l.t_longlong
        | l.t_ulonglong
        | l.t_true_or_false
        | l.t_char ;

    r_literal %= r_fundamental_literal | l.t_string;

    r_complex_primary_expression %= r_element | r_grouped_expression;

    r_grouped_expression %= omit[tk(token_ids::left_paren)] >> r_expression >> omit[tk(token_ids::right_paren)];

    r_expression_list %= r_expression % omit[tk(token_ids::comma)];

    r_statement %= r_expression_statement
        | r_block
        | r_label_statement
        | r_variable_declaration_statement
        | r_if_statement
        | r_for_statement
        | r_while_statement
        | r_do_while_statement
        | r_switch_statement
        | r_goto_statement
        | r_keyword_statement;

    r_variable_declarator %= r_identifier >> -(omit[tk(token_ids::assign)] >> r_expression);

    r_static = m_lexer("static")[qi::_val = true];

    r_extra_variable_declarators %= -(r_extra_variable_declarator % omit[tk(token_ids::comma)]); 

    r_variable_declaration %= -r_static >> r_element >> r_variable_declarator >> r_extra_variable_declarators;

    r_extra_variable_declarator %= -r_type_qualifier >> r_variable_declarator;

    r_variable_declaration_statement %= r_variable_declaration >> omit[tk(token_ids::semi_colon)];

    r_expression_statement %= r_expression >> omit[tk(token_ids::semi_colon)];

    r_statements %= *(omit[tk(token_ids::semi_colon)]|r_statement);

    r_block %= omit[tk(token_ids::left_brace)] >> r_statements >> omit[tk(token_ids::right_brace)];

    r_else_statement %= m_lexer("else") > r_statement;

    r_keyword_statement = m_lexer("break")[qi::_val = "break"] | m_lexer("continue")[qi::_val = "continue"];

    r_goto_statement %= m_lexer("goto") > r_identifier;

    r_label_statement %= r_identifier >> omit[tk(token_ids::colon)];

    r_if_statement %= m_lexer("if") > omit[tk(token_ids::left_paren)] > r_expression >> omit[tk(token_ids::right_paren)] >  r_statement >> -r_else_statement;

    r_while_statement %= m_lexer("while") > omit[tk(token_ids::left_paren)] > r_expression > omit[tk(token_ids::right_paren)] > (r_statement | omit[tk(token_ids::semi_colon)]);

    r_do_while_statement %= m_lexer("do") > r_statement > m_lexer("while") > omit[tk(token_ids::left_paren)] > r_expression > omit[tk(token_ids::right_paren)] > omit[tk(token_ids::semi_colon)];

    r_for_init %= r_variable_declaration | r_expression;

    r_for_statement %= m_lexer("for") > omit[tk(token_ids::left_paren)] > -r_for_init > omit[tk(token_ids::semi_colon)] > -r_expression > omit[tk(token_ids::semi_colon)] > *r_expression > omit[tk(token_ids::right_paren)] > (r_statement | omit[tk(token_ids::semi_colon)]);

    r_parameter %= r_element >> -r_variable_declarator;

    r_block %= omit[tk(token_ids::left_brace)] >> *r_statement >> omit[tk(token_ids::right_brace)];

    r_member_function_signature %= omit[tk(token_ids::left_paren)] >> (r_parameter % omit[tk(token_ids::comma)]) >> omit[tk(token_ids::right_paren)] >> -r_const_qualifier ;

    r_static_member_function_signature %= omit[tk(token_ids::left_paren)] >> (r_parameter % omit[tk(token_ids::comma)]) >> omit[tk(token_ids::left_paren)];

    r_ambiguous_member_declaration %= r_element >> r_identifier >> ( omit[tk(token_ids::semi_colon)] | (r_member_function_signature >> (omit[tk(token_ids::semi_colon)] |r_block)) ) ;

    r_static_ambiguous_member_declaration %= m_lexer("static") >> r_element >> r_identifier >> ( omit[tk(token_ids::semi_colon)]|(r_static_member_function_signature >> (omit[tk(token_ids::semi_colon)] |r_block)) ) ;

    r_virtual_member_function_declaration %= m_lexer("virtual") >> r_element >> r_identifier >> r_member_function_signature >> -(omit[tk(token_ids::assign)] >> l.t_uint) >> (omit[tk(token_ids::semi_colon)]|r_block);

    r_access_specifier %= m_lexer("public")   [qi::_val = o_public] 
                        | m_lexer("protected")[qi::_val = o_protected] 
                        | m_lexer("private")  [qi::_val = 0];

    r_access_declaration %= r_access_specifier >> omit[tk(token_ids::colon)];

    r_member_declaration %= r_virtual_member_function_declaration 
        | r_ambiguous_member_declaration 
        | r_static_ambiguous_member_declaration;

    r_class_inheritance %= -(r_access_specifier) >> r_qualified_name;

    r_class_inheritances %=  omit[tk(token_ids::colon)] >> r_class_inheritance %  omit[tk(token_ids::comma)];

    r_class_variable_declarator %= r_variable_declarator >> -(r_extra_variable_declarator % omit[tk(token_ids::comma)]);

    r_unnamed_class_declaration %= r_class_scope >> r_class_variable_declarator;

    r_named_class_declaration %= r_identifier >> -r_class_scope >> -r_class_variable_declarator ;

    r_struct_or_class = m_lexer("class")[qi::_val = false] | m_lexer("struct")[qi::_val = true];

    r_class_declaration %= r_struct_or_class >> (r_unnamed_class_declaration | r_named_class_declaration) >> omit[tk(token_ids::semi_colon)]; 

    r_class_scope %= -(r_class_inheritances) >> omit[tk(token_ids::left_brace)] >> *(r_access_declaration | r_member_declaration | r_class_declaration) >> omit[tk(token_ids::right_brace)] ; 
    
    r_namespace_declarator %= m_lexer("namespace") > r_identifier;

    r_namespace_alias_assign = omit[tk(token_ids::assign)] >> -omit[tk(token_ids::double_colon)] > (r_identifier % omit[tk(token_ids::double_colon)]) >> omit[tk(token_ids::semi_colon)];

    r_namespace_declaration %= r_namespace_declarator >> (r_namespace_alias_assign | r_namespace_scope);

    r_typedef_declaration %= m_lexer("typedef") >> (r_element|r_class_declaration) >> r_identifier;
    
    r_namespace_scope %= omit[tk(token_ids::left_brace)] >> *r_namespace_member_declaration >> omit[tk(token_ids::right_brace)];

    r_namespace_member_declaration %= r_namespace_declaration | r_variable_declaration_statement | r_class_declaration | r_typedef_declaration;

    r_compilation_unit %= *r_namespace_member_declaration;

    BOOST_SPIRIT_DEBUG_NODES(
        (r_element)
        (r_signed_type)
        (r_unsigned_type)
        (r_signable_type)
        (r_fundamental_type)
        (r_fundamental_type_name)
        (r_long_type)
        (r_operator)
        (r_type_qualifier)
        (r_const_qualifier)
        (r_extent)
        (r_qualifier_or_extent)
        (r_qualifier_or_extents)
        (r_qualifier_and_qualifier_or_extents)
        (r_extent_or_function_signature)
        (r_extent_or_function_signatures)
        (r_compound_id)
        (r_element_extension)
        (r_identifier)
        (r_operator_name)
        (r_template_element)
        (r_template_element_list)
        (r_integral_constant)
        (r_name)
        (r_qualified_name)
        (r_function_signature)
        (r_function_prototype)
        (r_template_signature)
        (r_expression)
        (r_expression_list)
        (r_binary_assignment_expression )
        (r_shift_assignment_expression )
        (r_multiplicative_assignment_operator )
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
        (r_for_init)
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
        (r_static_member_function_signature)
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
