
#include "phantom/phantom.h"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/repository/include/qi_distinct.hpp>
#include "phantom/reflection/StaticVariableAccess.h"
#include "phantom/reflection/ConstantExpression.h"
#include "phantom/reflection/StringLiteralExpression.h"
#include "phantom/reflection/ExpressionStatement.h"
#include "element_finder_spirit.h"
#include "solver_procedural.h"
#include "tokens.h"

using boost::spirit::repository::qi::distinct;

o_namespace_begin(phantom, reflection, eval, procedural)
    

using namespace ::boost::spirit;

class element_spirit_parser : public boost::spirit::qi::grammar<
    phantom::string::const_iterator
    , ast::root()
    , boost::spirit::ascii::space_type>
{
public:
    typedef phantom::string::const_iterator t_Iterator;
    typedef boost::spirit::qi::grammar<
        t_Iterator
        , ast::root()
        , boost::spirit::ascii::space_type> super_type;

    element_spirit_parser()
        : super_type(r_root)
    {

        // r_statement ...
        // (...) moved to statement_grammar.h

    }

    // rules

    

    qi::rule<t_Iterator, ast::block(), ascii::space_type >                              r_block;
    qi::rule<t_Iterator, ast::root(), ascii::space_type >                               r_root;


    qi::rule<t_Iterator, ast::expression(), ascii::space_type >                         r_expression;

    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_binary_assignment_operator ;
    qi::rule<t_Iterator, ast::binary_left_expression(), ascii::space_type >          r_binary_assignment_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_shift_assignment_operator ;
    qi::rule<t_Iterator, ast::binary_left_expression(), ascii::space_type >          r_shift_assignment_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_multiplicative_assignment_operator ;
    qi::rule<t_Iterator, ast::binary_left_expression(), ascii::space_type >          r_multiplicative_assignment_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_additive_assignment_operator ;
    qi::rule<t_Iterator, ast::binary_left_expression(), ascii::space_type >          r_additive_assignment_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_assignment_operator ;
    qi::rule<t_Iterator, ast::binary_left_expression(), ascii::space_type >          r_assignment_expression ;
    qi::rule<t_Iterator, ast::ternary_if_expression(), ascii::space_type >      r_ternary_if_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_logical_or_operator ;
    qi::rule<t_Iterator, ast::binary_right_expression(), ascii::space_type >          r_logical_or_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_logical_and_operator ;
    qi::rule<t_Iterator, ast::binary_right_expression(), ascii::space_type >          r_logical_and_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_binary_or_operator ;
    qi::rule<t_Iterator, ast::binary_right_expression(), ascii::space_type >          r_binary_or_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_binary_xor_operator ;
    qi::rule<t_Iterator, ast::binary_right_expression(), ascii::space_type >          r_binary_xor_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_binary_and_operator ;
    qi::rule<t_Iterator, ast::binary_right_expression(), ascii::space_type >          r_binary_and_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_equality_operator ;
    qi::rule<t_Iterator, ast::binary_right_expression(), ascii::space_type >          r_equality_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_greater_operator ;
    qi::rule<t_Iterator, ast::binary_right_expression(), ascii::space_type >          r_greater_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_lesser_operator ;
    qi::rule<t_Iterator, ast::binary_right_expression(), ascii::space_type >          r_lesser_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_shift_operator ;
    qi::rule<t_Iterator, ast::binary_right_expression(), ascii::space_type >          r_shift_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_additive_operator ;
    qi::rule<t_Iterator, ast::binary_right_expression(), ascii::space_type >          r_additive_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_multiplicative_operator ;
    qi::rule<t_Iterator, ast::binary_right_expression(), ascii::space_type >          r_multiplicative_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_member_pointer_operator ;
    qi::rule<t_Iterator, ast::binary_right_expression(), ascii::space_type >          r_member_pointer_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_reference_operator ;
    qi::rule<t_Iterator, ast::pre_unary_expression(), ascii::space_type >       r_reference_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_dereference_operator ;
    qi::rule<t_Iterator, ast::pre_unary_expression(), ascii::space_type >       r_dereference_expression ;
    qi::rule<t_Iterator, ast::cast_expression(), ascii::space_type >            r_cast_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_unary_logical_operator ;
    qi::rule<t_Iterator, ast::pre_unary_expression(), ascii::space_type >       r_unary_logical_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_unary_arithmetic_operator ;
    qi::rule<t_Iterator, ast::pre_unary_expression(), ascii::space_type >       r_unary_arithmetic_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_dec_inc_operator ;
    qi::rule<t_Iterator, ast::pre_unary_expression(), ascii::space_type >       r_pre_dec_inc_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_indirection_operator ;
    qi::rule<t_Iterator, ast::binary_right_expression(), ascii::space_type >          r_indirection_expression ;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_member_access_operator ;
    qi::rule<t_Iterator, ast::binary_right_expression(), ascii::space_type >          r_member_access_expression ;
    qi::rule<t_Iterator, ast::call_expression(), ascii::space_type >            r_call_expression ;
    qi::rule<t_Iterator, ast::post_unary_expression(), ascii::space_type >      r_post_dec_inc_expression ;
    qi::rule<t_Iterator, ast::expression(), ascii::space_type >                 r_primary_expression;
    qi::rule<t_Iterator, ast::expression(), ascii::space_type >                 r_complex_primary_expression;
    qi::rule<t_Iterator, ast::expression(), ascii::space_type >                 r_grouped_expression;
    qi::rule<t_Iterator, ast::fundamental_literal(), ascii::space_type >        r_fundamental_literal;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_string_literal;
    qi::rule<t_Iterator, char(), ascii::space_type >                            r_char_literal;
    qi::rule<t_Iterator, char(), ascii::space_type >                            r_escape_char;
    qi::rule<t_Iterator, ast::literal(), ascii::space_type >                    r_literal;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_identifier;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >                 r_operator_name;
    qi::rule<t_Iterator, ast::template_element(),ascii::space_type>             r_template_element;
    qi::rule<t_Iterator, vector<ast::template_element>(),ascii::space_type>     r_template_element_list;
    qi::rule<t_Iterator, long long(), ascii::space_type>                        r_integral_constant;
    qi::rule<t_Iterator, ast::name(), ascii::space_type>                        r_name;
    qi::rule<t_Iterator, ast::qualified_name(), ascii::space_type>              r_qualified_name;
    qi::rule<t_Iterator, phantom::vector<ast::expression>(), ascii::space_type> r_expression_list;
    qi::rule<t_Iterator, ast::extent_or_signature(), ascii::space_type>         r_function_signature;
    qi::rule<t_Iterator, ast::function_prototype(), ascii::space_type>          r_function_prototype;
    qi::rule<t_Iterator, vector<ast::template_element>(),ascii::space_type>     r_template_specialization;

};

element_finder_spirit::element_finder_spirit()
{

}

LanguageElement* element_finder_spirit::find( const string& a_strQualifiedName, LanguageElement* a_pRootScope /*= phantom::rootNamespace()*/ )
{
    element_spirit_parser g;
    ast::root    result;
    /*{
        // unit test
        string unitest_str[] = {
            "phantom::vector",
            "phantom::vector<caca>.test.bidule",
            "phantom::vector&",
            "phantom::vector<phantom::data>",
            "phantom::vector<phantom::data>&",
            "const phantom::vector<phantom::data>",
            "const phantom::vector<phantom::data>&"
        };
        for(int i = 0; i<sizeof(unitest_str)/sizeof(string); ++i)
        {
            ast::expression    unitest;
            boost::spirit::qi::phrase_parse(unitest_str[i].begin(), unitest_str[i].end(), g, boost::spirit::ascii::space, unitest);
            LanguageElement* pResultElement = ast::solve_expression(unitest, a_pRootScope);
            int j = 0;
            ++j;
        }
    }*/

    bool r = boost::spirit::qi::phrase_parse(a_strQualifiedName.begin(), a_strQualifiedName.end(), g, boost::spirit::ascii::space, result);

    LanguageElement* pResultElement = ast::solve_root(result, a_pRootScope);

    return pResultElement;//result
}


o_namespace_end(phantom, reflection, detail)
