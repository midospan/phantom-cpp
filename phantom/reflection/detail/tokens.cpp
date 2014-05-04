#include "phantom/phantom.h"
#include "tokens.h"

o_namespace_begin(phantom, reflection)

namespace cpp {


    map<size_t, string> token_ids::m_operator_string_from_token_ids;

    const string& token_ids::operator_string_from_token_id( size_t token_id )
    {
        static string empty;
        if(m_operator_string_from_token_ids.empty())
        {
            m_operator_string_from_token_ids[plus                   ] = "+";
            m_operator_string_from_token_ids[minus                  ] = "-";
            m_operator_string_from_token_ids[comma                  ] = ",";
            m_operator_string_from_token_ids[assign                 ] = "=";
            m_operator_string_from_token_ids[plus_assign            ] = "+=";
            m_operator_string_from_token_ids[minus_assign           ] = "-=";
            m_operator_string_from_token_ids[times_assign           ] = "*=";
            m_operator_string_from_token_ids[divide_assign          ] = "/=";
            m_operator_string_from_token_ids[mod_assign             ] = "%=";
            m_operator_string_from_token_ids[bit_and_assign         ] = "&=";
            m_operator_string_from_token_ids[bit_xor_assign         ] = "|=";
            m_operator_string_from_token_ids[bit_or_assign          ] = "^=";
            m_operator_string_from_token_ids[shift_left_assign      ] = "<<=";
            m_operator_string_from_token_ids[shift_right_assign     ] = ">>=";
            m_operator_string_from_token_ids[logical_or             ] = "||";
            m_operator_string_from_token_ids[logical_and            ] = "&&";
            m_operator_string_from_token_ids[bit_or                 ] = "|";
            m_operator_string_from_token_ids[bit_xor                ] = "^";
            m_operator_string_from_token_ids[bit_and                ] = "&";
            m_operator_string_from_token_ids[equal                  ] = "==";
            m_operator_string_from_token_ids[not_equal              ] = "!=";
            m_operator_string_from_token_ids[less                   ] = "<";
            m_operator_string_from_token_ids[less_equal             ] = "<=";
            m_operator_string_from_token_ids[greater                ] = ">";
            m_operator_string_from_token_ids[greater_equal          ] = ">=";
            m_operator_string_from_token_ids[shift_left             ] = "<<";
            m_operator_string_from_token_ids[shift_right            ] = ">>";
            m_operator_string_from_token_ids[times                  ] = "*";
            m_operator_string_from_token_ids[divide                 ] = "/";
            m_operator_string_from_token_ids[mod                    ] = "%";
            m_operator_string_from_token_ids[dot                    ] = ".";
            m_operator_string_from_token_ids[dot_star               ] = ".*";
            m_operator_string_from_token_ids[minus_greater          ] = "->";
            m_operator_string_from_token_ids[minus_greater_star     ] = "->*";
            m_operator_string_from_token_ids[plus_plus              ] = "++";
            m_operator_string_from_token_ids[minus_minus            ] = "--";
            m_operator_string_from_token_ids[compl_                 ] = "~";
            m_operator_string_from_token_ids[not_                   ] = "!";
            m_operator_string_from_token_ids[brackets               ] = "[]";
            m_operator_string_from_token_ids[parenthesis            ] = "()";
        }
        auto it = m_operator_string_from_token_ids.find(token_id);
        return it != m_operator_string_from_token_ids.end() ? it->second : empty;
    }

}

o_namespace_end(phantom, reflection)