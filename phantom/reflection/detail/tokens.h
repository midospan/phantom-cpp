#ifndef o_reflection_eval_cpp_tokens_h__
#define o_reflection_eval_cpp_tokens_h__

o_namespace_begin(phantom, reflection)

namespace cpp {

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

struct token_ids
{
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
        logical_or          = op::logical_or            ,
        logical_and         = op::logical_and           ,
        bit_or              = op::bit_or                ,
        bit_xor             = op::bit_xor               ,
        bit_and             = op::bit_and               | op_category::reference,
        equal               = op::equal                 | op_category::equality,
        not_equal           = op::not_equal             | op_category::equality,
        less                = op::less                  | op_category::lesser,
        less_equal          = op::less_equal            | op_category::lesser,
        greater             = op::greater               | op_category::greater,
        greater_equal       = op::greater_equal         | op_category::greater,
        shift_left          = op::shift_left            | op_category::shift,
        shift_right         = op::shift_right           | op_category::shift,
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

    static map<size_t, string> m_operator_string_from_token_ids;
};

}

o_namespace_end(phantom, reflection)

#endif // tokens_h__
