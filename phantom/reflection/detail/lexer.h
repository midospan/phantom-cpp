#ifndef o_reflecion_eval_lexer_h__
#define o_reflecion_eval_lexer_h__

#undef OR
#undef AND

#include "tokens.h"
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/lex_lexertl_position_token.hpp>
#include <boost/spirit/include/lex_static_lexertl.hpp>
#include <boost/spirit/home/qi/numeric/uint.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>

#define OR ||
#define AND &&

namespace boost { namespace spirit { namespace traits 
{ 
    template <typename Iterator> 
    struct assign_to_attribute_from_iterators< 
        phantom::reflection::cpp::hex_t, Iterator> 
    { 
        static void call(Iterator const& first, Iterator const& last, 
            phantom::reflection::cpp::hex_t& attr) 
        { 
            unsigned long long x; 
            qi::parse(first, last, "0x" >> qi::hex, x); 
            attr = phantom::reflection::cpp::hex_t(x); 
        } 
    }; 
/*

#define o_reflection_cpp_lexer_specialize_assign_to_attribute_from_iterators(type)                      \
    template <typename Iterator>                                                                        \
    struct assign_to_attribute_from_iterators<                                                          \
        type, classic::position_iterator<Iterator>>                                                     \
    {                                                                                                   \
        typedef classic::position_iterator<Iterator> iterator_t;                                        \
        static void call(iterator_t const& first, iterator_t const& last,                               \
            type& attr)                                                                                 \
        {                                                                                               \
            auto firstPos = first.get_position();                                                       \
            auto lastPos = last.get_position();                                                         \
            std::string str(first.base(), last.base());                                                 \
            std::cout<<firstPos.line<<'|'<<firstPos.column<<" - "<<lastPos.line<<'|'<<lastPos.column<<" : "<<str<<std::endl;\
            assign_to_attribute_from_iterators<type, Iterator>::call(first.base(), last.base(), attr);  \
        }                                                                                               \
    }; 

    o_reflection_cpp_lexer_specialize_assign_to_attribute_from_iterators(phantom::string                );
    o_reflection_cpp_lexer_specialize_assign_to_attribute_from_iterators(char                           );
    o_reflection_cpp_lexer_specialize_assign_to_attribute_from_iterators(int                            );
    o_reflection_cpp_lexer_specialize_assign_to_attribute_from_iterators(unsigned int                   );
    o_reflection_cpp_lexer_specialize_assign_to_attribute_from_iterators(long                           );
    o_reflection_cpp_lexer_specialize_assign_to_attribute_from_iterators(unsigned long                  );
    o_reflection_cpp_lexer_specialize_assign_to_attribute_from_iterators(long long                      );
    o_reflection_cpp_lexer_specialize_assign_to_attribute_from_iterators(unsigned long long             );
    o_reflection_cpp_lexer_specialize_assign_to_attribute_from_iterators(phantom::reflection::cpp::hex_t);
    o_reflection_cpp_lexer_specialize_assign_to_attribute_from_iterators(float                          );
    o_reflection_cpp_lexer_specialize_assign_to_attribute_from_iterators(double                         );
    o_reflection_cpp_lexer_specialize_assign_to_attribute_from_iterators(long double                    );
    o_reflection_cpp_lexer_specialize_assign_to_attribute_from_iterators(bool                           );
*/



}}} 


o_namespace_begin(phantom, reflection, cpp)

namespace lex = boost::spirit::lex;

///////////////////////////////////////////////////////////////////////////
namespace detail
{
    namespace lex = boost::spirit::lex;

    template <typename t_BaseIterator>
    struct get_lexer_type
    {
        // Our token needs to be able to carry several token values:
        // string, unsigned int, and bool
        typedef boost::mpl::vector<string
                                  , char
                                  , int
                                  , unsigned int
                                  , long
                                  , unsigned long
                                  , long long
                                  , unsigned long long
                                  , hex_t
                                  , float
                                  , double
                                  , long double
                                  , bool>
            token_value_types;

        // Using the position_token class as the token type to be returned
        // from the lexer iterators allows to retain positional information
        // as every token instance stores an iterator pair pointing to the
        // matched input sequence.
        typedef lex::lexertl::position_token<
            t_BaseIterator, token_value_types, boost::mpl::false_
        > token_type;

//#if CONJURE_LEXER_DYNAMIC_TABLES != 0
        // use the lexer based on runtime generated DFA tables
        typedef lex::lexertl::actor_lexer<token_type> type;
// #elif CONJURE_LEXER_STATIC_TABLES != 0
//             // use the lexer based on pre-generated static DFA tables
//             typedef lex::lexertl::static_actor_lexer<
//                 token_type
//               , boost::spirit::lex::lexertl::static_::lexer_conjure_static
//             > type;
// #elif CONJURE_LEXER_STATIC_SWITCH != 0
//             // use the lexer based on pre-generated static code
//             typedef lex::lexertl::static_actor_lexer<
//                 token_type
//               , boost::spirit::lex::lexertl::static_::lexer_conjure_static_switch
//             > type;
// #else
// #error "Configuration problem: please select exactly one type of lexer to build"
// #endif
    };
}

///////////////////////////////////////////////////////////////////////////
template <typename t_BaseIterator>
struct lexer
    : lex::lexer<typename detail::get_lexer_type<t_BaseIterator>::type>
{
private:
    // get the type of any qi::raw_token(...) and qi::token(...) constructs
    typedef typename boost::spirit::result_of::terminal<
        boost::spirit::tag::raw_token(token_ids::type)
    >::type raw_token_spec;

    typedef typename boost::spirit::result_of::terminal<
        boost::spirit::tag::token(token_ids::type)
    >::type token_spec;

    typedef map<std::string, token_ids::type> keyword_map_type;

protected:
    // add a keyword to the mapping table
    bool add_keyword(std::string const& keyword);

public:
    typedef t_BaseIterator base_iterator_type;

    lexer();

    // extract a raw_token(id) for the given registered keyword
    raw_token_spec operator()(std::string const& kwd) const
    {
        namespace qi = boost::spirit::qi;
        qi::raw_token_type raw_token;

        typename keyword_map_type::const_iterator it = m_keywords.find(kwd);
        o_assert(it != m_keywords.end());
        return raw_token((it != m_keywords.end()) ? (*it).second : token_ids::invalid);
    }

    // extract a token(id) for the given registered keyword
    token_spec token(std::string const& kwd) const
    {
        namespace qi = boost::spirit::qi;
        qi::token_type token;

        typename keyword_map_type::const_iterator it = m_keywords.find(kwd);
        o_assert(it != m_keywords.end());
        return token((it != m_keywords.end()) ? (*it).second : token_ids::invalid);
    }

    lex::token_def<string> t_identifier;
    lex::token_def<string> t_string;
    lex::token_def<unsigned int> t_uint;
    lex::token_def<char> t_char;
    lex::token_def<unsigned long> t_ulong;
    lex::token_def<hex_t> t_hex;
    lex::token_def<unsigned int> t_ulonglong;
    lex::token_def<long double> t_longdouble;
    lex::token_def<double> t_double;
    lex::token_def<float> t_float;
    lex::token_def<bool> t_true_or_false;

    keyword_map_type m_keywords;
    std::set<token_ids::type> m_unicity_checker;
    size_t m_keyword_id_pool;
};

template <typename t_BaseIterator>
bool lexer<t_BaseIterator>::add_keyword(std::string const& keyword)
{
    // add the token to the lexer
    token_ids::type id = token_ids::type(m_keyword_id_pool++);
    o_assert(m_unicity_checker.insert(id).second && id < 256);
    this->self.add(keyword, id);

    // store the mapping for later retrieval
    std::pair<typename keyword_map_type::iterator, bool> p =
        m_keywords.insert(typename keyword_map_type::value_type(keyword, id));

    return p.second;
}

template <typename t_BaseIterator>
lexer<t_BaseIterator>::lexer()
    : t_identifier("[a-zA-Z_][a-zA-Z_0-9]*", token_ids::identifier)
    , t_true_or_false("true|false", token_ids::true_or_false)
    , t_hex("0[xX][0-9a-fA-F]+", token_ids::hex_ulonglong_literal)
    , t_longdouble("[0-9]*\\.[0-9]+([eE][\\-\\+]?[0-9]+)?L", token_ids::longdouble_literal)   
    , t_double("[0-9]*\\.[0-9]+([eE][\\-\\+]?[0-9]+)?", token_ids::double_literal)      
    , t_float("[0-9]*\\.([0-9]+([eE][\\-\\+]?[0-9]+)?)?f", token_ids::float_literal)        
    , t_uint("[0-9]+", token_ids::uint_literal)            
    , t_ulong ("[0-9]+U?L", token_ids::ulong_literal)  
    , t_ulonglong ("[\\+]?[0-9]+U?LL", token_ids::ulonglong_literal)  
    , t_string("\\\"([^\\\"\\\\]|\\\\.)*\\\"", token_ids::string_literal)
    , t_char("'([^\n\r\\\\']|\\\\|\\.)'", token_ids::char_literal)
    , m_keyword_id_pool(token_ids::first_keyword_id)
{
    o_assert(m_unicity_checker.insert(token_ids::invalid                        ).second);
    o_assert(m_unicity_checker.insert(token_ids::plus                           ).second);
    o_assert(m_unicity_checker.insert(token_ids::minus                          ).second);
    o_assert(m_unicity_checker.insert(token_ids::comma                          ).second);
    o_assert(m_unicity_checker.insert(token_ids::assign                         ).second);
    o_assert(m_unicity_checker.insert(token_ids::plus_assign                    ).second);
    o_assert(m_unicity_checker.insert(token_ids::minus_assign                   ).second);
    o_assert(m_unicity_checker.insert(token_ids::times_assign                   ).second);
    o_assert(m_unicity_checker.insert(token_ids::divide_assign                  ).second);
    o_assert(m_unicity_checker.insert(token_ids::mod_assign                     ).second);
    o_assert(m_unicity_checker.insert(token_ids::bit_and_assign                 ).second);
    o_assert(m_unicity_checker.insert(token_ids::bit_xor_assign                 ).second);
    o_assert(m_unicity_checker.insert(token_ids::bit_or_assign                  ).second);
    o_assert(m_unicity_checker.insert(token_ids::shift_left_assign              ).second);
    o_assert(m_unicity_checker.insert(token_ids::shift_right_assign             ).second);
    o_assert(m_unicity_checker.insert(token_ids::logical_or                     ).second);
    o_assert(m_unicity_checker.insert(token_ids::logical_and                    ).second);
    o_assert(m_unicity_checker.insert(token_ids::bit_or                         ).second);
    o_assert(m_unicity_checker.insert(token_ids::bit_xor                        ).second);
    o_assert(m_unicity_checker.insert(token_ids::bit_and                        ).second);
    o_assert(m_unicity_checker.insert(token_ids::equal                          ).second);
    o_assert(m_unicity_checker.insert(token_ids::not_equal                      ).second);
    o_assert(m_unicity_checker.insert(token_ids::less                           ).second);
    o_assert(m_unicity_checker.insert(token_ids::less_equal                     ).second);
    o_assert(m_unicity_checker.insert(token_ids::greater                        ).second);
    o_assert(m_unicity_checker.insert(token_ids::greater_equal                  ).second);
    o_assert(m_unicity_checker.insert(token_ids::shift_left                     ).second);
    o_assert(m_unicity_checker.insert(token_ids::shift_right                    ).second);
    o_assert(m_unicity_checker.insert(token_ids::times                          ).second);
    o_assert(m_unicity_checker.insert(token_ids::divide                         ).second);
    o_assert(m_unicity_checker.insert(token_ids::mod                            ).second);
    o_assert(m_unicity_checker.insert(token_ids::dot                            ).second);
    o_assert(m_unicity_checker.insert(token_ids::dot_star                       ).second);
    o_assert(m_unicity_checker.insert(token_ids::minus_greater                  ).second);
    o_assert(m_unicity_checker.insert(token_ids::minus_greater_star             ).second);
    o_assert(m_unicity_checker.insert(token_ids::plus_plus                      ).second);
    o_assert(m_unicity_checker.insert(token_ids::minus_minus                    ).second);
    o_assert(m_unicity_checker.insert(token_ids::compl_                         ).second);
    o_assert(m_unicity_checker.insert(token_ids::not_                           ).second);
    o_assert(m_unicity_checker.insert(token_ids::brackets                       ).second);
    o_assert(m_unicity_checker.insert(token_ids::parenthesis                    ).second);
    o_assert(m_unicity_checker.insert(token_ids::arobase                        ).second);
    o_assert(m_unicity_checker.insert(token_ids::question                       ).second);
    o_assert(m_unicity_checker.insert(token_ids::left_paren                     ).second);
    o_assert(m_unicity_checker.insert(token_ids::right_paren                    ).second);
    o_assert(m_unicity_checker.insert(token_ids::left_bracket                   ).second);
    o_assert(m_unicity_checker.insert(token_ids::right_bracket                  ).second);
    o_assert(m_unicity_checker.insert(token_ids::left_brace                     ).second);
    o_assert(m_unicity_checker.insert(token_ids::right_brace                    ).second);
    o_assert(m_unicity_checker.insert(token_ids::semi_colon                     ).second);
    o_assert(m_unicity_checker.insert(token_ids::colon                          ).second);
    o_assert(m_unicity_checker.insert(token_ids::double_colon                   ).second);
    o_assert(m_unicity_checker.insert(token_ids::identifier                     ).second);
    o_assert(m_unicity_checker.insert(token_ids::comment                        ).second);
    o_assert(m_unicity_checker.insert(token_ids::whitespace                     ).second);
    o_assert(m_unicity_checker.insert(token_ids::float_literal                  ).second);
    o_assert(m_unicity_checker.insert(token_ids::double_literal                 ).second);
    o_assert(m_unicity_checker.insert(token_ids::longdouble_literal             ).second)
    o_assert(m_unicity_checker.insert(token_ids::hex_ulonglong_literal             ).second);
    o_assert(m_unicity_checker.insert(token_ids::int_literal                    ).second);
    o_assert(m_unicity_checker.insert(token_ids::uint_literal                   ).second);
    o_assert(m_unicity_checker.insert(token_ids::long_literal                   ).second);
    o_assert(m_unicity_checker.insert(token_ids::ulong_literal                  ).second);
    o_assert(m_unicity_checker.insert(token_ids::longlong_literal               ).second);
    o_assert(m_unicity_checker.insert(token_ids::ulonglong_literal              ).second);
    o_assert(m_unicity_checker.insert(token_ids::string_literal                 ).second);
    o_assert(m_unicity_checker.insert(token_ids::char_literal                   ).second);
    o_assert(m_unicity_checker.insert(token_ids::true_or_false                  ).second);

    lex::_pass_type _pass;

    this->self =  t_true_or_false;
    this->self += t_hex;
    this->self += t_longdouble;
    this->self += t_float;
    this->self += t_double;
    this->self += t_uint;
    this->self += t_ulong;
    this->self += t_ulonglong;

    add_keyword("auto");
    add_keyword("bool");
    add_keyword("break");
    add_keyword("case");
    add_keyword("char");
    add_keyword("class");
    add_keyword("const");
    add_keyword("continue");
    add_keyword("default");
    add_keyword("do");
    add_keyword("double");
    add_keyword("else");
    add_keyword("float");
    add_keyword("for");
    add_keyword("goto");
    add_keyword("if");
    add_keyword("inline");
    add_keyword("int");
    add_keyword("long");
    add_keyword("namespace");
    add_keyword("nullptr");
    add_keyword("mutable");
    add_keyword("operator");
    add_keyword("private");
    add_keyword("protected");
    add_keyword("public");
    add_keyword("return");
    add_keyword("short");
    add_keyword("signed");
    add_keyword("static");
    add_keyword("struct");
    add_keyword("switch");
    add_keyword("template");
    add_keyword("this");
    add_keyword("typedef");
    add_keyword("typename");
    add_keyword("unsigned");
    add_keyword("virtual");
    add_keyword("void");
    add_keyword("while");

    this->self.add
        ("\\=",    token_ids::assign                  )
        ("\\+\\=", token_ids::plus_assign             )
        ("\\-\\=", token_ids::minus_assign            )
        ("\\*\\=", token_ids::times_assign            )
        ("\\/\\=", token_ids::divide_assign           )
        ("\\%\\=", token_ids::mod_assign              )
        ("\\&\\=", token_ids::bit_and_assign          )
        ("\\^\\=", token_ids::bit_xor_assign          )
        ("\\|\\=", token_ids::bit_or_assign           )
        ("<<\\=", token_ids::shift_left_assign        )
        (">>\\=", token_ids::shift_right_assign       )
        ("\\+\\+", token_ids::plus_plus               )
        ("\\-\\-", token_ids::minus_minus             )
        ("\\+", token_ids::plus                       )
        ("\\-", token_ids::minus                      )
 //       (",", token_ids::comma                      )
        ("\\|\\|", token_ids::logical_or              )
        ("&&", token_ids::logical_and                 )
        ("\\|", token_ids::bit_or                     )
        ("\\^", token_ids::bit_xor                    )
        ("&", token_ids::bit_and                      )
        ("@", token_ids::arobase                      )
        ("==", token_ids::equal                       )
        ("!=", token_ids::not_equal                   )
        ("<=", token_ids::less_equal                  )
        ("<", token_ids::less                         )
        (">=", token_ids::greater_equal               )
        (">", token_ids::greater                      )
        ("<<", token_ids::shift_left                  )
        (">>", token_ids::shift_right                 )
        ("\\*", token_ids::times                      )
        ("\\/", token_ids::divide                     )
        ("\\%", token_ids::mod                        )
        ("\\.", token_ids::dot                        )
        ("\\.\\*", token_ids::dot_star                )
        ("\\->", token_ids::minus_greater             )
        ("\\->\\*", token_ids::minus_greater_star     )
        ("~", token_ids::compl_                       )
        ("!", token_ids::not_                         )
//         ("\\(", token_ids::left_paren                 )
//         ("\\)", token_ids::right_paren                )
//         ("\\[", token_ids::left_bracket               )
//         ("\\]", token_ids::right_bracket              )
//         ("\\{", token_ids::left_brace                 )
//         ("\\}", token_ids::right_brace                )
//         ("\\;", token_ids::semi_colon                 )
        ("\\:\\:", token_ids::double_colon            )
    ;

    this->self += t_string;
    this->self += t_char;

    this->self += lex::char_('(') | ')' | '{' | '}' | ',' | ';' | '=' | '[' | ']' | ':' | '?';
    
    this->self +=
            t_identifier
        |   lex::string("\\/\\*[^*]*\\*+([^/*][^*]*\\*+)*\\/", token_ids::comment)
            [
                lex::_pass = lex::pass_flags::pass_ignore
            ]
        |   lex::string("\\/\\/[^\\\n]*[\\\n]*", token_ids::comment)
            [
                lex::_pass = lex::pass_flags::pass_ignore
            ]
        |   lex::string("[ \t\n\r]+", token_ids::whitespace)
            [
                lex::_pass = lex::pass_flags::pass_ignore
            ]
        ;
}

o_namespace_end(phantom, reflection, cpp)

#endif // lexer_h__
