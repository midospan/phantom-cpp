#include "CxxToken.h"
#include <stdio.h>
#ifndef _MSC_VER
#include <alloca.h>
#else
#include <malloc.h>
//#define alloca _alloca
#endif

#include "CxxDriver.h"

namespace phantom 
{
void classify_argument();
void classify_function();
void dollar_kill();
CxxTokens *get_code(CxxToken *);
CxxTokens *get_expr();
CxxTokens *get_for_init();
CxxTokens *get_for_next();
CxxTokens *get_for_test();
CxxTokens *get_func();
CxxTokens *get_raw(CxxToken *);
CxxTokens *get_statement();
void make(CxxToken *);
void queue(CxxToken *);
int set_replace_formals(int);

extern CxxToken *_list_token;
// 
// #ifndef BISON_PP_CLASS
// void yyerror(const char *s);
// #define yylex buffered_yylex
// int yylex();
// #endif
// 
// 
// 

struct yy_scoped_printer
{
    static int level(int v = 0) 
    { 
        static int l = 0; 
        l+=v;
        return l; 
    }
    yy_scoped_printer(const char* func)
    {
        int l = level();
        char buffer[1024] = "";
        char* b = buffer;
        for(int i = 0; i<l; ++i)
        {
            *b = '\t';
            ++b;
        }
        while(*b = *func++) ++b;
        *b = '\n';
        b++;
        *b = '\0';
        printf(buffer);
        level(1);
    }
    ~yy_scoped_printer() { level(-1); }
};
//#define YACC_DEBUG_PRINT_ENABLED
#if defined(YACC_DEBUG_PRINT_ENABLED)
#   define YACC_DEBUG_PRINT yy_scoped_printer _yy_scoped_printer(__FUNCTION__);
#else 
#   define YACC_DEBUG_PRINT 
#endif

#define LOCATION(loc) phantom::reflection::CodeLocation(phantom::reflection::CodePosition((loc).begin.line, (loc).begin.column), phantom::reflection::CodePosition((loc).end.line, (loc).end.column))
#define YY_LOC(what, where) if(what) (what)->setLocation(LOCATION(where))

#define YACC_ABSTRACT_ARRAY_EXPRESSION(a) CxxTokenizer::make_abstract_array_expression(a)
#define YACC_ABSTRACT_FUNCTION_EXPRESSION(a) CxxTokenizer::make_abstract_function_expression(a)
#define YACC_ACCESSIBILITY_SPECIFIER(a) CxxTokenizer::make_accessibility_specifier(a)
#define YACC_ACCESS_BASE_SPECIFIER(a,b) CxxTokenizer::make_access_base_specifier(a,b)
#define YACC_ADD_EXPRESSION(a,b) CxxTokenizer::make_add_expression(a, b)
#define YACC_AND_EXPRESSION(a,b) CxxTokenizer::make_and_expression(a,b)
#define YACC_ARRAY_EXPRESSION(a,b) CxxTokenizer::make_array_expression(a,b)
#define YACC_ARROW_EXPRESSION(a,b) CxxTokenizer::make_arrow_expression(a,b)
#define YACC_ARROW_STAR_EXPRESSION(a,b) CxxTokenizer::make_arrow_star_expression(a,b)
#define YACC_ASM_DEFINITION(a) CxxTokenizer::make_asm_definition(a)
#define YACC_ASSIGNMENT_EXPRESSION(a,b,c) CxxTokenizer::make_assignment_expression(a,b,c)
#define YACC_BASE_SPECIFIER(a) CxxTokenizer::make_base_specifier(a)
#define YACC_BASE_SPECIFIERS(a,b) CxxTokenizer::make_base_specifiers(a,b)
#define YACC_BIT_FIELD_EXPRESSION(a,b) CxxTokenizer::make_bit_field_expression(a,b)
#define YACC_BREAK_STATEMENT() CxxTokenizer::make_break_statement()
#define YACC_BUILT_IN_ID(a) CxxTokenizer::make_built_in_id(a)
// #define YACC_BUILT_IN_ID_ID(a) CxxTokenizer::make_built_in_id_id(a)
#define YACC_BUILT_IN_IDS(a,b) CxxTokenizer::make_built_in_ids(a,b)
#define YACC_BUILT_IN_NAME(a,b) CxxTokenizer::make_built_in_name(a,b)
#define YACC_CALL_EXPRESSION(a,b) CxxTokenizer::make_call_expression(a,b)
#define YACC_CASE_STATEMENT(a,b) CxxTokenizer::make_case_statement(a,b)
#define YACC_CAST_EXPRESSION(a,b) CxxTokenizer::make_cast_expression(a,b)
#define YACC_HEX_LITERAL_EXPRESSION(a) CxxTokenizer::make_hex_literal_expression(a)
#define YACC_LONGDOUBLE_LITERAL_EXPRESSION(a) CxxTokenizer::make_longdouble_literal_expression(a)
#define YACC_DOUBLE_LITERAL_EXPRESSION(a) CxxTokenizer::make_double_literal_expression(a)
#define YACC_FLOAT_LITERAL_EXPRESSION(a) CxxTokenizer::make_float_literal_expression(a)
#define YACC_UINT_LITERAL_EXPRESSION(a) CxxTokenizer::make_uint_literal_expression(a)
#define YACC_ULONG_LITERAL_EXPRESSION(a) CxxTokenizer::make_ulong_literal_expression(a)
#define YACC_ULONGLONG_LITERAL_EXPRESSION(a) CxxTokenizer::make_ulonglong_literal_expression(a)
#define YACC_CHARACTER_LITERAL_EXPRESSION(a) CxxTokenizer::make_character_literal_expression(a)
#define YACC_CLASS_MEMBERS(a,b) CxxTokenizer::make_class_members(a,b)
#define YACC_CLASS_SPECIFIER_ID(a,b,c) CxxTokenizer::make_class_specifier_id(a,b,c)
#define YACC_CLASS_TYPE_PARAMETER(a) CxxTokenizer::make_class_type_parameter(a)
#define YACC_COMPILE_DECLARATION(a,b) CxxTokenizer::compile_declaration(a,b)
#define YACC_COMPILE_MEMBER_DECLARATION(a,b) CxxTokenizer::compile_member_declaration(a,b)
#define YACC_COMPILE_STATEMENT(a) CxxTokenizer::compile_statement(a)
#define YACC_COMPLEMENT_EXPRESSION(a) CxxTokenizer::make_complement_expression(a)
#define YACC_COMPOUND_STATEMENT(a) CxxTokenizer::make_compound_statement(a)
#define YACC_CONDITION(a) CxxTokenizer::make_condition(a)
#define YACC_CONDITIONAL_EXPRESSION(a,b,c) CxxTokenizer::make_conditional_expression(a,b,c)
#define YACC_CONST_CAST_EXPRESSION(a,b) CxxTokenizer::make_const_cast_expression(a,b)
#define YACC_CONTINUE_STATEMENT() CxxTokenizer::make_continue_statement()
#define YACC_CONVERSION_FUNCTION_ID(a) CxxTokenizer::make_conversion_function_id(a)
#define YACC_CTOR_DEFINITION(a,b) CxxTokenizer::make_ctor_definition(a,b)
#define YACC_CTOR_FUNCTION_BLOCK(a,b) CxxTokenizer::make_ctor_function_block(a,b)
#define YACC_CV_DECLARATOR(a,b) CxxTokenizer::make_cv_declarator(a,b)
#define YACC_CV_DECL_SPECIFIER(a) CxxTokenizer::make_cv_decl_specifier(a)
#define YACC_CV_QUALIFIERS(a,b) CxxTokenizer::make_cv_qualifiers(a,b)
#define YACC_DECLARATIONS(a,b) CxxTokenizer::make_declarations(a,b)
#define YACC_DECLARATION_STATEMENT(a) CxxTokenizer::make_declaration_statement(a)
#define YACC_DECL_SPECIFIER_DECLARATION(a,b) CxxTokenizer::make_decl_specifier_declaration(a,b)
#define YACC_DECL_SPECIFIER_EXPRESSION(a,b) CxxTokenizer::make_decl_specifier_expression(a,b)
#define YACC_DECL_SPECIFIER_NAME(a,b) CxxTokenizer::make_decl_specifier_name(a,b)
#define YACC_DECL_SPECIFIER_PARAMETER(a,b) CxxTokenizer::make_decl_specifier_parameter(a,b)
#define YACC_DECL_SPECIFIERS(a,b) CxxTokenizer::make_decl_specifiers(a,b)
#define YACC_DEFAULT_STATEMENT(a) CxxTokenizer::make_default_statement(a)
#define YACC_DELETE_EXPRESSION(a) CxxTokenizer::make_delete_expression(a)
#define YACC_DERIVED_CLAUSE(a,b) CxxTokenizer::make_derived_clause(a,b)
#define YACC_DESTRUCTOR_ID(a) CxxTokenizer::make_destructor_id(a)
#define YACC_DIVIDE_EXPRESSION(a,b) CxxTokenizer::make_divide_expression(a,b)
#define YACC_DOT_EXPRESSION(a,b) CxxTokenizer::make_dot_expression(a,b)
#define YACC_DOT_STAR_EXPRESSION(a,b) CxxTokenizer::make_dot_star_expression(a,b)
#define YACC_DO_WHILE_STATEMENT(a,b) CxxTokenizer::make_do_while_statement(a,b)
#define YACC_DYNAMIC_CAST_EXPRESSION(a,b) CxxTokenizer::make_dynamic_cast_expression(a,b)
#define YACC_ELABORATED_TYPE_SPECIFIER(a,b) CxxTokenizer::make_elaborated_type_specifier(a,b)
#define YACC_ELLIPSIS_EXPRESSION() CxxTokenizer::make_ellipsis_expression()
#define YACC_ENUMERATOR(a,b) CxxTokenizer::make_enumerator(a,b)
#define YACC_ENUMERATORS(a,b) CxxTokenizer::make_enumerators(a,b)
#define YACC_ENUM_SPECIFIER_ID(a,b) CxxTokenizer::make_enum_specifier_id(a,b)
#define YACC_EPSILON() CxxTokenizer::make_epsilon()
#define YACC_EQUAL_EXPRESSION(a,b) CxxTokenizer::make_equal_expression(a,b)
#define YACC_EXCEPTION_DECLARATION(a) CxxTokenizer::make_exception_declaration(a)
#define YACC_EXCEPTION_SPECIFICATION(a) CxxTokenizer::make_exception_specification(a)
#define YACC_EXCLUSIVE_OR_EXPRESSION(a,b) CxxTokenizer::make_exclusive_or_expression(a,b)
#define YACC_EXPLICIT_IMPLEMENTATION_DECLARATION(a) CxxTokenizer::make_explicit_implementation_declaration(a)
#define YACC_EXPLICIT_INTERFACE_DECLARATION(a) CxxTokenizer::make_explicit_interface_declaration(a)
#define YACC_EXPLICIT_SPECIALIZATION(a) CxxTokenizer::make_explicit_specialization(a)
#define YACC_EXPRESSION(a) CxxTokenizer::make_expression(a)
#define YACC_SINGLE_EXPRESSION(a) if(m_pDriver->getParseType() != CxxDriver::e_ParseType_Expression) { yyerror("Unexpected character found : '$'"); } else CxxTokenizer::make_single_expression(a)
#define YACC_EXPRESSIONS(a,b) CxxTokenizer::make_expressions(a,b)
#define YACC_EXPRESSION_PARAMETER(a) CxxTokenizer::make_expression_parameter(a)
#define YACC_FALSE_EXPRESSION() CxxTokenizer::make_false_expression()
#define YACC_FOR_STATEMENT(a,b,c,d) CxxTokenizer::make_for_statement(a,b,c,d)
#define YACC_FRIEND() CxxTokenizer::make_friend()
#define YACC_FUNCTION_BLOCK(a) CxxTokenizer::make_function_block(a)
#define YACC_FUNCTION_DECLARATIONS(a,b) CxxTokenizer::make_function_declarations(a,b)
#define YACC_FUNCTION_DEFINITION(a,b) CxxTokenizer::make_function_definition(a,b)
#define YACC_GLOBAL_DECLARATOR(a,b) CxxTokenizer::make_global_declarator(a,b)
#define YACC_GLOBAL_EXPRESSION(a, b) CxxTokenizer::make_global_expression(a,b)
#define YACC_GLOBAL_ID(a,b) CxxTokenizer::make_global_id(a,b)
#define YACC_GOTO_STATEMENT(a) CxxTokenizer::make_goto_statement(a)
#define YACC_GREATER_EQUAL_EXPRESSION(a,b) CxxTokenizer::make_greater_equal_expression(a,b)
#define YACC_GREATER_THAN_EXPRESSION(a,b) CxxTokenizer::make_greater_than_expression(a,b)
#define YACC_HANDLER(a,b) CxxTokenizer::make_handler(a,b)
#define YACC_HANDLERS(a,b) CxxTokenizer::make_handlers(a,b)
#define YACC_IF_STATEMENT(a,b,c) CxxTokenizer::make_if_statement(a,b,c)
#define YACC_INCLUSIVE_OR_EXPRESSION(a,b) CxxTokenizer::make_inclusive_or_expression(a,b)
#define YACC_INITIALIZED_PARAMETER(a,b) CxxTokenizer::make_initialized_parameter(a, b)
#define YACC_INITIALIZER_CLAUSES(a,b) CxxTokenizer::make_initializer_clauses(a,b)
#define YACC_INITIALIZER_EXPRESSION_CLAUSE(a) CxxTokenizer::make_initializer_expression_clause(a)
#define YACC_INITIALIZER_LIST_CLAUSE(a) CxxTokenizer::make_initializer_list_clause(a)
#define YACC_INIT_SIMPLE_TYPE_PARAMETER(a,b) CxxTokenizer::make_init_simple_type_parameter(a,b)
#define YACC_INIT_TEMPLATED_PARAMETER(a,b) CxxTokenizer::make_init_templated_parameter(a,b)
#define YACC_LABEL_STATEMENT(a,b) CxxTokenizer::make_label_statement(a,b)
#define YACC_LESS_EQUAL_EXPRESSION(a,b) CxxTokenizer::make_less_equal_expression(a,b)
#define YACC_LESS_THAN_EXPRESSION(a,b) CxxTokenizer::make_less_than_expression(a,b)
#define YACC_LINE() CxxTokenizer::make_line()
#define YACC_LINED_DECLARATION(a,b) CxxTokenizer::make_lined_declaration(a,b)
#define YACC_LINED_MEMBER_DECLARATION(a,b) CxxTokenizer::make_lined_member_declaration(a,b)
#define YACC_LINED_STATEMENT(a,b) CxxTokenizer::make_lined_statement(a,b)
#define YACC_LINED_TOKEN(a,b) CxxTokenizer::make_lined_token(a,b)
#define YACC_LINKAGE_SPECIFICATION(a) CxxTokenizer::make_linkage_specification(a)
#define YACC_LINKAGE_SPECIFIER(a,b) CxxTokenizer::make_linkage_specifier(a,b)
#define YACC_LOGICAL_AND_EXPRESSION(a,b) CxxTokenizer::make_logical_and_expression(a,b)
#define YACC_LOGICAL_OR_EXPRESSION(a,b) CxxTokenizer::make_logical_or_expression(a,b)
#define YACC_MEMBER_DECLARATION(a) CxxTokenizer::make_member_declaration(a)
#define YACC_MEMBER_DECLARATIONS(a,b) CxxTokenizer::make_member_declarations(a,b)
#define YACC_MEM_INITIALIZER(a,b) CxxTokenizer::make_mem_initializer(a,b)
#define YACC_MEM_INITIALIZERS(a,b) CxxTokenizer::make_mem_initializers(a,b)
#define YACC_MINUS_EXPRESSION(a) CxxTokenizer::make_minus_expression(a)
#define YACC_MODULUS_EXPRESSION(a,b) CxxTokenizer::make_modulus_expression(a,b)
#define YACC_MULTIPLY_EXPRESSION(a,b,c) CxxTokenizer::make_multiply_expression(a,b,c)
#define YACC_COMPLEX_POINTER_EXPRESSION(a,b,c) CxxTokenizer::make_complex_pointer_expression(a,b,c)
#define YACC_NAME(a) CxxTokenizer::make_name(a)
#define YACC_NAMESPACE_ALIAS_DEFINITION(a,b) CxxTokenizer::make_namespace_alias_definition(a,b)
#define YACC_NAMESPACE_DECLARATION(a) CxxTokenizer::make_namespace_declaration(a)
#define YACC_NAMESPACE_DEFINITION(a,b) CxxTokenizer::make_namespace_definition(a,b)
#define YACC_NAME_EXPRESSION(a) CxxTokenizer::make_name_expression(a)
#define YACC_NESTED_DECLARATOR(a,b) CxxTokenizer::make_nested_ptr_declarator(a,b)
#define YACC_NESTED_ID(a,b) CxxTokenizer::make_nested_id(a,b)
#define YACC_NESTED_SCOPE(a) CxxTokenizer::make_nested_scope(a)
#define YACC_NEW_EXPRESSION(a,b,c) CxxTokenizer::make_new_expression(a,b,c)
#define YACC_NEW_TYPE_ID_EXPRESSION(a,b,c) CxxTokenizer::make_new_type_id_expression(a,b,c)
#define YACC_NOT_EQUAL_EXPRESSION(a,b) CxxTokenizer::make_not_equal_expression(a,b)
#define YACC_NOT_EXPRESSION(a) CxxTokenizer::make_not_expression(a)
#define YACC_OPERATOR_ADD_ID() CxxTokenizer::make_operator_add_id()
#define YACC_OPERATOR_ARROW_ID() CxxTokenizer::make_operator_arrow_id()
#define YACC_OPERATOR_ARROW_STAR_ID() CxxTokenizer::make_operator_arrow_star_id()
#define YACC_OPERATOR_ASS_ADD_ID() CxxTokenizer::make_operator_ass_add_id()
#define YACC_OPERATOR_ASS_BIT_AND_ID() CxxTokenizer::make_operator_ass_bit_and_id()
#define YACC_OPERATOR_ASS_BIT_OR_ID() CxxTokenizer::make_operator_ass_bit_or_id()
#define YACC_OPERATOR_ASS_DIV_ID() CxxTokenizer::make_operator_ass_div_id()
#define YACC_OPERATOR_ASS_ID() CxxTokenizer::make_operator_ass_id()
#define YACC_OPERATOR_ASS_MOD_ID() CxxTokenizer::make_operator_ass_mod_id()
#define YACC_OPERATOR_ASS_MUL_ID() CxxTokenizer::make_operator_ass_mul_id()
#define YACC_OPERATOR_ASS_SHL_ID() CxxTokenizer::make_operator_ass_shl_id()
#define YACC_OPERATOR_ASS_SHR_ID() CxxTokenizer::make_operator_ass_shr_id()
#define YACC_OPERATOR_ASS_SUB_ID() CxxTokenizer::make_operator_ass_sub_id()
#define YACC_OPERATOR_ASS_XOR_ID() CxxTokenizer::make_operator_ass_xor_id()
#define YACC_OPERATOR_BIT_AND_ID() CxxTokenizer::make_operator_bit_and_id()
#define YACC_OPERATOR_BIT_NOT_ID() CxxTokenizer::make_operator_bit_not_id()
#define YACC_OPERATOR_BIT_OR_ID() CxxTokenizer::make_operator_bit_or_id()
#define YACC_OPERATOR_CALL_ID() CxxTokenizer::make_operator_call_id()
#define YACC_OPERATOR_COMMA_ID() CxxTokenizer::make_operator_comma_id()
#define YACC_OPERATOR_DEC_ID() CxxTokenizer::make_operator_dec_id()
#define YACC_OPERATOR_DELETE_ID() CxxTokenizer::make_operator_delete_id()
#define YACC_OPERATOR_DIV_ID() CxxTokenizer::make_operator_div_id()
#define YACC_OPERATOR_EQ_ID() CxxTokenizer::make_operator_eq_id()
#define YACC_OPERATOR_FUNCTION_ID(a) CxxTokenizer::make_operator_function_id(a)
#define YACC_OPERATOR_GE_ID() CxxTokenizer::make_operator_ge_id()
#define YACC_OPERATOR_GT_ID() CxxTokenizer::make_operator_gt_id()
#define YACC_OPERATOR_INC_ID() CxxTokenizer::make_operator_inc_id()
#define YACC_OPERATOR_INDEX_ID() CxxTokenizer::make_operator_index_id()
#define YACC_OPERATOR_LE_ID() CxxTokenizer::make_operator_le_id()
#define YACC_OPERATOR_LOG_AND_ID() CxxTokenizer::make_operator_log_and_id()
#define YACC_OPERATOR_LOG_NOT_ID() CxxTokenizer::make_operator_log_not_id()
#define YACC_OPERATOR_LOG_OR_ID() CxxTokenizer::make_operator_log_or_id()
#define YACC_OPERATOR_LT_ID() CxxTokenizer::make_operator_lt_id()
#define YACC_OPERATOR_MOD_ID() CxxTokenizer::make_operator_mod_id()
#define YACC_OPERATOR_MUL_ID() CxxTokenizer::make_operator_mul_id()
#define YACC_OPERATOR_NE_ID() CxxTokenizer::make_operator_ne_id()
#define YACC_OPERATOR_NEW_ID() CxxTokenizer::make_operator_new_id()
#define YACC_OPERATOR_SHL_ID() CxxTokenizer::make_operator_shl_id()
#define YACC_OPERATOR_SHR_ID() CxxTokenizer::make_operator_shr_id()
#define YACC_OPERATOR_SUB_ID() CxxTokenizer::make_operator_sub_id()
#define YACC_OPERATOR_XOR_ID() CxxTokenizer::make_operator_xor_id()
#define YACC_PARAMETERS(a,b) CxxTokenizer::make_parameters(a,b)
#define YACC_PARENTHESISED(a,b,c,d) CxxTokenizer::make_parenthesised(a,b,c,d)
#define YACC_POINTER_DECLARATOR() CxxTokenizer::make_pointer_declarator()
#define YACC_POINTER_EXPRESSION(a,b) CxxTokenizer::make_pointer_expression(a,b)
#define YACC_PLUS_EXPRESSION(a) CxxTokenizer::make_plus_expression(a)
#define YACC_POST_DECREMENT_EXPRESSION(a) CxxTokenizer::make_post_decrement_expression(a)
#define YACC_POST_INCREMENT_EXPRESSION(a) CxxTokenizer::make_post_increment_expression(a)
#define YACC_PRE_DECREMENT_EXPRESSION(a) CxxTokenizer::make_pre_decrement_expression(a)
#define YACC_PRE_INCREMENT_EXPRESSION(a) CxxTokenizer::make_pre_increment_expression(a)
#define YACC_PSEUDO_DESTRUCTOR_ID(a,b) CxxTokenizer::make_pseudo_destructor_id(a,b)
#define YACC_PURE_VIRTUAL() CxxTokenizer::make_pure_virtual()
#define YACC_REFERENCE_DECLARATOR() CxxTokenizer::make_reference_declarator()
#define YACC_DATA_EXPRESSION(a) CxxDriver::Instance()->isShaman() ? CxxTokenizer::make_data_expression(a) : (yyerror("unexpected character '@'"), 0)
#define YACC_REINTERPRET_CAST_EXPRESSION(a,b) CxxTokenizer::make_reinterpret_cast_expression(a,b)
#define YACC_TEMPLATE_PARAMETERS(a,b) CxxTokenizer::make_template_parameters(a,b)
#define YACC_TEMPLATED_TYPE_PARAMETER(a,b) CxxTokenizer::make_templated_type_parameter(a,b)
#define YACC_TRANSLATION_UNIT(a) CxxTokenizer::make_translation_unit(a)
#define YACC_TYPEDEF() CxxTokenizer::make_typedef()
#define YACC_RETURN_STATEMENT(a) CxxTokenizer::make_return_statement(a)
#define YACC_SCOPED_POINTER_EXPRESSION(a,b,c) CxxTokenizer::make_scoped_pointer_expression(a,b,c)
#define YACC_SCOPED_ID(a,b) CxxTokenizer::make_scoped_id(a,b)
#define YACC_SET_TEMPLATE_DECLARATION(a) CxxTokenizer::make_set_template_declaration(a)
#define YACC_SET_TEMPLATE_DECL_SPECIFIER(a) CxxTokenizer::make_set_template_decl_specifier(a)
#define YACC_SET_TEMPLATE_EXPRESSION(a) CxxTokenizer::make_set_template_expression(a)
#define YACC_SET_TEMPLATE_ID(a) CxxTokenizer::make_set_template_id(a)
#define YACC_SET_TEMPLATE_NAME(a) CxxTokenizer::make_set_template_name(a)
#define YACC_SET_TEMPLATE_SCOPE(a) CxxTokenizer::make_set_template_scope(a)
#define YACC_SHIFT_LEFT_EXPRESSION(a,b) CxxTokenizer::make_shift_left_expression(a,b)
#define YACC_SHIFT_RIGHT_EXPRESSION(a,b) CxxTokenizer::make_shift_right_expression(a,b)
#define YACC_SIMPLE_DECLARATION(a) CxxTokenizer::make_simple_declaration(a)
#define YACC_IMPORT_DECLARATION(a,b) CxxTokenizer::make_import_declaration(a,b)
#define YACC_IMPORT_SYMBOL_DECLARATION(a,b) CxxTokenizer::make_import_symbol_declaration(a,b)
#define YACC_IMPORT_SYMBOL_DECLARATIONS(a,b) CxxTokenizer::make_import_symbol_declarations(a,b)
#define YACC_SIZEOF_EXPRESSION(a) CxxTokenizer::make_sizeof_expression(a)
#define YACC_STATEMENTS(a,b) CxxTokenizer::make_statements(a,b)
#define YACC_STATIC_CAST_EXPRESSION(a,b) CxxTokenizer::make_static_cast_expression(a,b)
#define YACC_STRING_LITERAL_EXPRESSION(a) CxxTokenizer::make_string_literal_expression(a)
#define YACC_SUBTRACT_EXPRESSION(a,b) CxxTokenizer::make_subtract_expression(a,b)
#define YACC_SWITCH_STATEMENT(a,b) CxxTokenizer::make_switch_statement(a,b)
#define YACC_TEMPLATE_ARGUMENT(a) CxxTokenizer::make_template_argument(a)
#define YACC_TEMPLATE_ARGUMENTS(a,b) CxxTokenizer::make_template_arguments(a,b)
#define YACC_TEMPLATE_DECLARATION(a,b) CxxTokenizer::make_template_declaration(a,b)
#define YACC_TEMPLATE_NAME(a,b) CxxTokenizer::make_template_name(a,b)
#define YACC_TEMPLATE_PARAMETER(a) CxxTokenizer::make_template_parameter(a)
#define YACC_THIS_EXPRESSION() CxxTokenizer::make_this_expression()
#define YACC_THROW_EXPRESSION(a) CxxTokenizer::make_throw_expression(a)
#define YACC_TRUE_EXPRESSION() CxxTokenizer::make_true_expression()
#define YACC_TRY_BLOCK(a,b) CxxTokenizer::make_try_block(a,b)
#define YACC_TRY_BLOCK_STATEMENT(a) CxxTokenizer::make_try_block_statement(a)
#define YACC_TRY_FUNCTION_BLOCK(a,b) CxxTokenizer::make_try_function_block(a,b)
#define YACC_TYPE1_EXPRESSION(a,b,c) CxxTokenizer::make_type1_expression(a,b,c)
#define YACC_TYPE1_PARAMETERS(a,b) CxxTokenizer::make_type1_parameters(a,b)
#define YACC_TYPED_EXPRESSION(a,b) CxxTokenizer::make_typed_expression(a,b)
#define YACC_TYPED_NAME(a,b) CxxTokenizer::make_typed_name(a,b)
#define YACC_TYPEID_EXPRESSION(a) CxxTokenizer::make_typeid_expression(a)
#define YACC_TYPENAME_TYPE_PARAMETER(a) CxxTokenizer::make_typename_type_parameter(a)
#define YACC_USING_DECLARATION(a,b) CxxTokenizer::make_using_declaration(a,b)
#define YACC_USING_DIRECTIVE(a) CxxTokenizer::make_using_namespace_directive(a)
#define YACC_UTILITY(a) CxxTokenizer::make_utility(0)
#define YACC_UTILITY_MODE() CxxTokenizer::make_utility_mode()
#define YACC_VIRTUAL_BASE_SPECIFIER(a) CxxTokenizer::make_virtual_base_specifier(a)
#define YACC_WHILE_STATEMENT(a,b) CxxTokenizer::make_while_statement(a,b)
#define YACC_DOT_QUALIFIED_NAME(a,b) CxxTokenizer::make_dot_qualified_name(a,b)

struct CxxTokenizer 
{

    static CxxDeclaration *compile_declaration(CxxUtility *utilityMode, CxxDeclaration *aDeclaration) 
    {
        YACC_DEBUG_PRINT;
        return aDeclaration;
    }

    static CxxMemberDeclaration *compile_member_declaration(CxxUtility *utilityMode, CxxMemberDeclaration *aDeclaration) 
    {
        YACC_DEBUG_PRINT;
        return aDeclaration;
    }

    static CxxStatement *compile_statement(CxxStatement *aDeclaration) 
    {
        YACC_DEBUG_PRINT;
        return aDeclaration;
    }

    static void make_translation_unit(CxxDeclarations *aResult) 
    {
        CxxDriver::Instance()->m_Result.d = aResult;
    }

    static CxxDeclSpecifierId* make_typedef()
    {
        return new CxxDeclSpecifierId("typedef");
    }

    static CxxDeclSpecifierId* make_friend()
    {
        return new CxxDeclSpecifierId("friend");
    }

    static void make_single_expression(CxxExpression* aResult)
    {
        CxxDriver::Instance()->m_Result.e = aResult;
    }

    static CxxExpression* make_abstract_array_expression(CxxExpression *sizeExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxAbstractArrayExpression(sizeExpr);
    }

    static CxxExpression* make_abstract_function_expression(CxxParenthesised *aparenthesis) 
    {
        YACC_DEBUG_PRINT;
        return new CxxAbstractFunctionExpression(aparenthesis);
    }

    static CxxBaseSpecifier* make_access_base_specifier(CxxBaseSpecifier *baseSpecifier, CxxAccessSpecifier *accessSpecifier) 
    {
        YACC_DEBUG_PRINT;
        baseSpecifier->accessSpecifier = accessSpecifier;
        return baseSpecifier;
    }

    static CxxMemberDeclaration* make_accessibility_specifier(CxxAccessSpecifier *accessSpecifier) 
    {
        YACC_DEBUG_PRINT;
        return new CxxMemberDeclaration(new CxxAccessibilitySpecifier(accessSpecifier));
    }

    static CxxExpression* make_add_expression(CxxExpression *leftExpr, CxxExpression *rightExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxBinaryExpression("+", leftExpr, rightExpr);
    }

    static CxxExpression* make_and_expression(CxxExpression *leftExpr, CxxExpression *rightExpr) 
    {
        YACC_DEBUG_PRINT;
        if(rightExpr == nullptr)
        {
            if(leftExpr->declSpecifier)
                leftExpr->declSpecifier->swallow(new CxxDeclSpecifierId("&"));
            else 
                leftExpr->declSpecifier = new CxxDeclSpecifierId("&");
            return leftExpr;
        }
        return new CxxBinaryExpression("&", leftExpr, rightExpr);
    }

    static CxxExpression* make_array_expression(CxxExpression *anExpr, CxxExpression *indexExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxArrayAccessExpression(anExpr, indexExpr);
    }

    static CxxExpression* make_arrow_expression(CxxExpression *anExpr, CxxName *aName) 
    {
        YACC_DEBUG_PRINT;
        return new CxxArrowExpression(anExpr, aName);
    }

    static CxxExpression* make_arrow_star_expression(CxxExpression *anExpr, CxxExpression *memberExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxArrowStarExpression(anExpr, memberExpr);
    }

    static CxxDeclaration* make_asm_definition(CxxStrings *aString) 
    {
        YACC_DEBUG_PRINT;
        return new CxxAsmDefinition(aString);
    }

    static const char* assop(int tokenValue)
    {
        switch(tokenValue)
        {
        case CxxParser::token::ASS_ADD:
            return "+=";
        case CxxParser::token::ASS_SUB:
            return "-=";
        case CxxParser::token::ASS_MUL:
            return "*=";
        case CxxParser::token::ASS_DIV:
            return "/=";
        case CxxParser::token::ASS_AND:
            return "&=";
        case CxxParser::token::ASS_OR:
            return "|=";
        case CxxParser::token::ASS_XOR:
            return "^=";
        case CxxParser::token::ASS_MOD:
            return "%=";
        case CxxParser::token::ASS_SHL:
            return "<<=";
        case CxxParser::token::ASS_SHR:
            return ">>=";
        default:
            return "=";
        }
    }

    static CxxExpression* make_assignment_expression(CxxExpression *leftExpr, CxxToken *assOp, CxxExpression *rightExpr) 
    {
        YACC_DEBUG_PRINT;
        if(assOp == nullptr)
        {
            o_assert(rightExpr == nullptr);
            return leftExpr;
        }
        return new CxxBinaryExpression(assop(assOp->value()), leftExpr, rightExpr);
    }

    static CxxBaseSpecifier* make_base_specifier(CxxName *aName) 
    {
        YACC_DEBUG_PRINT;
        return new CxxBaseSpecifier(aName);
    }

    static CxxBaseSpecifiers* make_base_specifiers(CxxBaseSpecifiers *aList, CxxBaseSpecifier *anElement) 
    {
        YACC_DEBUG_PRINT;
//         aList->add(anElement);
//         return aList;
        return 0;
    }

    static CxxExpression* make_bit_field_expression(CxxExpression *nameExpr, CxxExpression *sizeExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxBitfieldExpression(nameExpr, sizeExpr);
    }

    static CxxStatement* make_break_statement() 
    {
        YACC_DEBUG_PRINT;
        return new CxxBreakStatement();
    }

    static CxxName* make_built_in_id(CxxBuiltInId *aName) 
    {
        YACC_DEBUG_PRINT;
        return aName;
    }

    static CxxBuiltInId* make_built_in_ids(CxxBuiltInId *anExpr, CxxBuiltInId *anElement) 
    {
        o_assert(anExpr != anElement);
        anExpr->words.back().id += ' ';
        anExpr->words.back().id += anElement->words.back().id;
        // delete anElement;
        return anExpr;
    }

    static CxxName* make_built_in_name(CxxName *aName, CxxBuiltInId *anElement) 
    {
        o_assert(aName != anElement);
        aName->words.back().id += ' ';
        aName->words.back().id += anElement->words.back().id;
        // delete anElement;
        return aName;
    }

    static CxxExpression* make_call_expression(CxxExpression *anExpr, CxxParenthesised *aParenthesis) 
    {
        YACC_DEBUG_PRINT;
        return new CxxCallExpression(anExpr, aParenthesis);
    }

    static CxxStatement* make_case_statement(CxxExpression *anExpr, CxxStatement *aStmt) 
    {
        YACC_DEBUG_PRINT;
        return new CxxCaseStatement(anExpr, aStmt);
    }

    static CxxExpression* make_cast_expression(CxxExpression *aCast, CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxCStyleCastExpression(aCast, anExpr);
    }

    static CxxExpression* make_character_literal_expression(CxxCharacterLiteral *aLiteral) 
    {
        YACC_DEBUG_PRINT;
        return new CxxCharacterLiteralExpression(aLiteral);
    }

    static CxxExpression* make_hex_literal_expression(CxxNumberLiteral<hex_t> *aLiteral) 
    {
        YACC_DEBUG_PRINT;
        return new CxxNumberLiteralExpression<hex_t>(aLiteral);
    }

    static CxxExpression* make_longdouble_literal_expression(CxxNumberLiteral<long double> *aLiteral) 
    {
        YACC_DEBUG_PRINT;
        return new CxxNumberLiteralExpression<long double>(aLiteral);
    }

    static CxxExpression* make_double_literal_expression(CxxNumberLiteral<double> *aLiteral) 
    {
        YACC_DEBUG_PRINT;
        return new CxxNumberLiteralExpression<double>(aLiteral);
    }

    static CxxExpression* make_float_literal_expression(CxxNumberLiteral<float> *aLiteral) 
    {
        YACC_DEBUG_PRINT;
        return new CxxNumberLiteralExpression<float>(aLiteral);
    }

    static CxxExpression* make_uint_literal_expression(CxxNumberLiteral<unsigned int> *aLiteral) 
    {
        YACC_DEBUG_PRINT;
        return new CxxNumberLiteralExpression<unsigned int>(aLiteral);
    }

    static CxxExpression* make_ulong_literal_expression(CxxNumberLiteral<unsigned long>*aLiteral) 
    {
        YACC_DEBUG_PRINT;
        return new CxxNumberLiteralExpression<unsigned long>(aLiteral);
    }

    static CxxExpression* make_ulonglong_literal_expression(CxxNumberLiteral<unsigned long long> *aLiteral) 
    {
        YACC_DEBUG_PRINT;
        return new CxxNumberLiteralExpression<unsigned long long>(aLiteral);
    }
    

    static CxxName* make_class_members(CxxClass *aClass, CxxMemberDeclarations *memberDeclarations) 
    {
        YACC_DEBUG_PRINT;
        return new CxxClassMembers(aClass, memberDeclarations);
    }

    static CxxClass* make_class_specifier_id(CxxClassKey *classKey, CxxName *aName, CxxBaseSpecifiers *baseSpecifiers) 
    {
        YACC_DEBUG_PRINT;
        return new CxxClass(classKey, aName, baseSpecifiers);
    }

    static CxxSimpleTypeParameter* make_class_type_parameter(CxxName *aName) 
    {
        YACC_DEBUG_PRINT;
        return new CxxClassTypeParameter(aName);
    }

    static CxxStatement* make_compound_statement(CxxStatements *statementList) 
    {
        YACC_DEBUG_PRINT;
        return new CxxBlock(statementList);
    }

    static CxxExpression* make_complement_expression(CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxPreUnaryExpression("~", anExpr);
    }

    static CxxCondition* make_condition(CxxParameters *aList) 
    {
        YACC_DEBUG_PRINT;
        return new CxxCondition(aList);
    }

    static CxxExpression* make_conditional_expression(CxxExpression *testExpr, CxxExpression *trueExpr, CxxExpression *falseExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxConditionalExpression(testExpr, trueExpr, falseExpr);
    }

    static CxxExpression* make_const_cast_expression(CxxExpression *aType, CxxExpression *anExpr)  
    {
        YACC_DEBUG_PRINT;
        return new CxxConstCastExpression(aType, anExpr);
    }

    static CxxStatement* make_continue_statement() 
    {
        YACC_DEBUG_PRINT;
        return new CxxContinueStatement();
    }

    static CxxName* make_conversion_function_id(CxxExpression *typeId) 
    {
        YACC_DEBUG_PRINT;
        return new CxxConversionFunction(typeId);
    }

    static CxxExpression* make_ctor_definition(CxxExpressions *anExpr, CxxFunctionBody *functionBody) 
    {
        YACC_DEBUG_PRINT;
        return new CxxConstructorDefinition(anExpr, functionBody);
    }

    static CxxFunctionBody* make_ctor_function_block(CxxFunctionBody *functionBody, CxxMemInitializers *ctorList) 
    {
        YACC_DEBUG_PRINT;
        o_assert(ctorList == nullptr);
        return functionBody;
    }

    static CxxDeclSpecifierId* make_cv_decl_specifier(CxxCvQualifiers *cvQualifiers) 
    {
        YACC_DEBUG_PRINT;
        return cvQualifiers;
    }

    static CxxPointerDeclarator* make_cv_declarator(CxxPointerDeclarator *aDeclarator, CxxCvQualifiers *cvQualifiers) 
    {
        YACC_DEBUG_PRINT;
        aDeclarator->name->declSpecifier->swallow(cvQualifiers);
        return aDeclarator;
    }

    static CxxCvQualifiers* make_cv_qualifiers(CxxCvQualifiers *aList, CxxCvQualifiers *anElement) 
    {
        YACC_DEBUG_PRINT;
        if(aList == nullptr) 
        {
            aList = anElement;
        }
        else if(anElement) aList->swallow(anElement);
        return aList;
    }

    static CxxDeclaration* make_decl_specifier_declaration(CxxDeclaration *aDeclaration, CxxDeclSpecifierId *declSpecifier) 
    {
        YACC_DEBUG_PRINT;
        if(aDeclaration->declSpecifier)
        {
            declSpecifier->swallow(aDeclaration->declSpecifier); // declSpecifier has higher specification precedence and must be before any '&' or '*' issued previously
            aDeclaration->declSpecifier = declSpecifier;
        }
        else aDeclaration->declSpecifier = declSpecifier;
        return aDeclaration;
    }

    static CxxExpression* make_decl_specifier_expression(CxxExpression *anExpr, CxxDeclSpecifierId *declSpecifier) 
    {
        YACC_DEBUG_PRINT;
        if(anExpr->declSpecifier)
        {
            declSpecifier->swallow(anExpr->declSpecifier); // declSpecifier has higher specification precedence and must be before any '&' or '*' issued previously
            anExpr->declSpecifier = declSpecifier;
        }
        else anExpr->declSpecifier = declSpecifier;
        return anExpr;
    }

    static CxxName* make_decl_specifier_name(CxxName *aName, CxxDeclSpecifierId *declSpecifier) 
    {
        YACC_DEBUG_PRINT;
        if(aName->declSpecifier)
        {
            declSpecifier->swallow(aName->declSpecifier); // declSpecifier has higher specification precedence and must be before any '&' or '*' issued previously
            aName->declSpecifier = declSpecifier;
        }
        else aName->declSpecifier = declSpecifier;
        return aName;
    }

    static CxxParameter* make_decl_specifier_parameter(CxxParameter *aName, CxxDeclSpecifierId *declSpecifier) 
    {
        YACC_DEBUG_PRINT;
        if(aName->expr->declSpecifier)
        {
            declSpecifier->swallow(aName->expr->declSpecifier); // declSpecifier has higher specification precedence and must be before any '&' or '*' issued previously
            aName->expr->declSpecifier = declSpecifier;
        }
        else aName->expr->declSpecifier = declSpecifier;
        return aName;
    }

    static CxxDeclSpecifierId* make_decl_specifiers(CxxDeclSpecifierId *aList, CxxDeclSpecifierId *anElement) 
    {
        YACC_DEBUG_PRINT;
        if(aList == nullptr) return anElement;
        aList->swallow(anElement);
        return aList;
    }

    static CxxDeclarations* make_declarations(CxxDeclarations *aList, CxxDeclaration *anElement) 
    {
        YACC_DEBUG_PRINT;
        if(aList == nullptr) 
        {
            if(anElement == nullptr) return nullptr;
            aList = new CxxDeclarations;
        }
        aList->add(anElement);
        return aList;
    }

    static CxxStatement* make_declaration_statement(CxxDeclaration *aDecl) 
    {
        YACC_DEBUG_PRINT;
        return aDecl;
    }

    static CxxStatement* make_default_statement(CxxStatement *aStmt) 
    {
        YACC_DEBUG_PRINT;
        return new CxxDefaultStatement(aStmt);
    }

    static CxxDeleteExpression* make_delete_expression(CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxDeleteExpression(anExpr);
    }

    static CxxDeclaration* make_derived_clause(CxxExpression *derivedPredicate, CxxDeclaration *aDeclaration) 
    {
        YACC_DEBUG_PRINT;
    }

    static CxxName* make_destructor_id(CxxName *aName) 
    {
        YACC_DEBUG_PRINT;
        aName->words.front().id = '~'+aName->words.front().id;
        return aName;
    }

    static CxxExpression* make_divide_expression(CxxExpression *leftExpr, CxxExpression *rightExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxBinaryExpression("/", leftExpr, rightExpr);
    }

    static CxxStatement* make_do_while_statement(CxxStatement *aStmt, CxxExpression *testExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxDoWhileStatement(aStmt, testExpr);
    }

    static CxxExpression* make_dot_expression(CxxExpression *anExpr, CxxName *aName) 
    {
        YACC_DEBUG_PRINT;
        return new CxxDotExpression(anExpr, aName);
    }

    static CxxExpression* make_dot_star_expression(CxxExpression *anExpr, CxxExpression *memberExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxDotStarExpression(anExpr, memberExpr);
    }

    static CxxExpression* make_dynamic_cast_expression(CxxExpression *aType, CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        // return new CxxDynamicCastExpression(anExpr, memberExpr);
        o_assert_no_implementation();
        return nullptr;
    }

    static CxxName* make_elaborated_type_specifier(CxxClassKey *classKey, CxxName *aName) 
    {
        YACC_DEBUG_PRINT;
        aName->classKey = classKey;
        return aName;
    }

    static CxxParameter* make_ellipsis_expression() 
    {
        YACC_DEBUG_PRINT;
        return new CxxVariadicParameter();
    }

    static CxxName* make_enum_specifier_id(CxxName *aName, CxxEnumerators *aList) 
    {
        YACC_DEBUG_PRINT;
        return new CxxEnumSpecifierId(aName, aList);
    }

    static CxxEnumerator* make_enumerator(CxxName *aName, CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxEnumerator(aName, anExpr);
    }

    static CxxEnumerators* make_enumerators(CxxEnumerators *aList, CxxEnumerator *anElement) 
    {
        YACC_DEBUG_PRINT;
        if(aList == nullptr) aList = new CxxEnumerators;
        aList->add(anElement);
        return aList; 
    }

    static CxxName* make_epsilon() 
    {
        YACC_DEBUG_PRINT;
        return 0;
    }

    static CxxExpression* make_equal_expression(CxxExpression *leftExpr, CxxExpression *rightExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxBinaryExpression("==", leftExpr, rightExpr);
    }

    static CxxExceptionDeclaration* make_exception_declaration(CxxParameter *aParameter) 
    {
        YACC_DEBUG_PRINT;
        return new CxxExceptionDeclaration(aParameter);
    }

    static CxxExceptionSpecification* make_exception_specification(CxxExpressions *typeIds) 
    {
        YACC_DEBUG_PRINT;
        return new CxxExceptionSpecification(typeIds);
    }

    static CxxExpression* make_exclusive_or_expression(CxxExpression *leftExpr, CxxExpression *rightExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxBinaryExpression("^", leftExpr, rightExpr);
    }

    static CxxDeclaration* make_explicit_implementation_declaration(CxxTokens *someTokens) 
    {
        YACC_DEBUG_PRINT;
    }

    static CxxDeclaration* make_explicit_interface_declaration(CxxTokens *someTokens) 
    {
        YACC_DEBUG_PRINT;
    }

    static CxxDeclaration* make_explicit_specialization(CxxDeclaration *aDeclaration) 
    {
        YACC_DEBUG_PRINT;
        return new CxxTemplateDeclaration(new CxxTemplateParameters, aDeclaration);
    }
    
    static CxxExpression* make_expression(CxxExpressions *aList) 
    {
        YACC_DEBUG_PRINT;
        return aList;
    }

    static CxxParameter* make_expression_parameter(CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxParameter(anExpr);
    }

    static CxxExpressions* make_expressions(CxxExpressions *aList, CxxExpression *anElement) 
    {
        YACC_DEBUG_PRINT;
        if(aList == nullptr) 
        {
            if(anElement == nullptr) return nullptr;
            aList = new CxxExpressions;
        }
        aList->add(anElement);
        return aList;
    }

    static CxxExpression* make_false_expression() 
    {
        YACC_DEBUG_PRINT;
        return new CxxNumberLiteralExpression<bool>(new CxxNumberLiteral<bool>(0, false));
    }

    static CxxStatement* make_for_statement(CxxExpression *initExpr, CxxCondition *testExpr, CxxExpression *stepExpr, CxxStatement *aStmt) 
    {
        YACC_DEBUG_PRINT;
        return new CxxForStatement(initExpr, testExpr, stepExpr, aStmt);
    }

    static CxxFunctionBody* make_function_block(CxxStatement *aStatement) 
    {
        YACC_DEBUG_PRINT;
        return new CxxFunctionBody(aStatement);
    }

    static CxxFunctionDeclarations* make_function_declarations(CxxFunctionDeclarations *aList, CxxDeclaration *anElement) 
    {
        YACC_DEBUG_PRINT;
        if(aList == nullptr) aList = new CxxFunctionDeclarations;
        aList->add(anElement);
        return aList;
    }

    static CxxExpression* make_function_definition(CxxExpression *anExpr, CxxFunctionBody *functionBody) 
    {
        YACC_DEBUG_PRINT;
        return new CxxFunctionDefinition(anExpr, functionBody);
    }

    static CxxDeclarator* make_global_declarator(CxxIsTemplate isTemplate, CxxDeclarator *aDeclarator) 
    {
        YACC_DEBUG_PRINT;
        aDeclarator->isTemplate = IS_TEMPLATE == isTemplate;
        aDeclarator->isGlobal = true;
        return aDeclarator;
    }

    static CxxExpression* make_global_expression(CxxIsTemplate isTemplate, CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxGlobalExpression(IS_TEMPLATE == isTemplate, anExpr);
    }

    static CxxName* make_global_id(CxxIsTemplate isTemplate, CxxName *nestedId) 
    {
        YACC_DEBUG_PRINT;
        nestedId->isTemplate = (isTemplate == IS_TEMPLATE);
        nestedId->words.insert(nestedId->words.begin(), CxxName::word("")); // make global scope
        return nestedId;
    }

    static CxxStatement* make_goto_statement(CxxName *aLabel) 
    {
        YACC_DEBUG_PRINT;
        return new CxxGotoStatement(aLabel);
    }

    static CxxExpression* make_greater_equal_expression(CxxExpression *leftExpr, CxxExpression *rightExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxBinaryExpression(">=", leftExpr, rightExpr);
    }

    static CxxExpression* make_greater_than_expression(CxxExpression *leftExpr, CxxExpression *rightExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxBinaryExpression(">", leftExpr, rightExpr);
    }

    static CxxHandler* make_handler(CxxExceptionDeclaration *exceptionDeclaration, CxxStatement *aStatement) 
    {
        YACC_DEBUG_PRINT;
        return new CxxHandler(exceptionDeclaration, aStatement);
    }

    static CxxHandlers* make_handlers(CxxHandlers *aList, CxxHandler *anElement) 
    {
        YACC_DEBUG_PRINT;
        if(aList == nullptr) aList = new CxxHandlers;
        aList->add(anElement);
        return aList;
    }

    static CxxStatement* make_if_statement(CxxCondition *testExpr, CxxStatement *trueStmt, CxxStatement *falseStmt) 
    {
        YACC_DEBUG_PRINT;
        return new CxxIfStatement(testExpr, trueStmt, falseStmt);
    }

    static CxxExpression* make_inclusive_or_expression(CxxExpression *leftExpr, CxxExpression *rightExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxBinaryExpression("|", leftExpr, rightExpr);
    }

    static CxxParameter* make_initialized_parameter(CxxParameter *aParameter, CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        aParameter->init = anExpr;
        return aParameter;
    }

    static CxxInitializerClauses* make_initializer_clauses(CxxInitializerClauses *aList, CxxInitializerClause *anElement) 
    {
        YACC_DEBUG_PRINT;
        if(aList == nullptr) aList = new CxxInitializerClauses;
        aList->add(anElement);
        return aList;
    }

    static CxxInitializerClause* make_initializer_expression_clause(CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxInitializerClause(anExpr);
    }

    static CxxInitializerClause* make_initializer_list_clause(CxxInitializerClauses *aList) 
    {
        YACC_DEBUG_PRINT;
        return aList;
    }

    static CxxSimpleTypeParameter* make_init_simple_type_parameter(CxxSimpleTypeParameter *templateParameters, CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        templateParameters->init = anExpr;
        return templateParameters;
    }

    static CxxTemplatedTypeParameter* make_init_templated_parameter(CxxTemplatedTypeParameter *typeParameter, CxxName *aName) 
    {
        YACC_DEBUG_PRINT;
        typeParameter->expr = aName;
        return typeParameter;
    }

    static CxxStatement* make_label_statement(CxxName *aLabel, CxxStatement *aStmt) 
    {
        YACC_DEBUG_PRINT;
        return new CxxLabelStatement(aLabel, aStmt);
    }

    static CxxExpression* make_less_equal_expression(CxxExpression *leftExpr, CxxExpression *rightExpr) 
    {
        return new CxxBinaryExpression("<=", leftExpr, rightExpr);
    }

    static CxxExpression* make_less_than_expression(CxxExpression *leftExpr, CxxExpression *rightExpr) 
    {
        return new CxxBinaryExpression("<", leftExpr, rightExpr);
    }

    static CxxLine* make_line() 
    {
        YACC_DEBUG_PRINT;
        return 0;
    }

    static CxxDeclaration* make_lined_declaration(CxxDeclaration *aDeclaration, CxxLine *aLine) 
    {
        YACC_DEBUG_PRINT;
        return aDeclaration;
    }

    static CxxMemberDeclaration* make_lined_member_declaration(CxxMemberDeclaration *aDeclaration, CxxLine *aLine) 
    {
        YACC_DEBUG_PRINT;
        return aDeclaration;
    }

    static CxxStatement* make_lined_statement(CxxStatement *aStatement, CxxLine *aLine) 
    {
        YACC_DEBUG_PRINT;
        return aStatement;
    }

    static CxxToken* make_lined_token(CxxToken *aToken, CxxLine *aLine) 
    {
        YACC_DEBUG_PRINT;
        return aToken;
    }

    static CxxName* make_linkage_specifier(CxxStrings *aString, CxxDeclaration *aDeclaration) 
    {
        YACC_DEBUG_PRINT;
        o_assert_no_implementation(); // extern "C" & Co not supported
        return new CxxName;
    }

    static CxxExpression* make_logical_and_expression(CxxExpression *leftExpr, CxxExpression *rightExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxBinaryExpression("&&", leftExpr, rightExpr);
    }

    static CxxExpression* make_logical_or_expression(CxxExpression *leftExpr, CxxExpression *rightExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxBinaryExpression("||", leftExpr, rightExpr);
    }

    static CxxMemInitializer* make_mem_initializer(CxxName *aName, CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxMemInitializer(aName, anExpr);
    }

    static CxxMemInitializers* make_mem_initializers(CxxMemInitializers *aList, CxxMemInitializer *anElement) 
    {
        YACC_DEBUG_PRINT;
        if(aList == nullptr) 
        {
            if(anElement == nullptr) return nullptr;
            aList = new CxxMemInitializers;
        }
        aList->add(anElement);
        return aList;
    }

    static CxxMemberDeclaration* make_member_declaration(CxxDeclaration *aDeclaration) 
    {
        YACC_DEBUG_PRINT;
        return new CxxMemberDeclaration(aDeclaration);
    }

    static CxxMemberDeclarations* make_member_declarations(CxxMemberDeclarations *aList, CxxMemberDeclaration *aDeclaration) 
    {
        YACC_DEBUG_PRINT;
        if(aList == nullptr) 
        {
            if(aDeclaration == nullptr) return nullptr;
            aList = new CxxMemberDeclarations;
        }
        aList->add(aDeclaration);
        return aList;
    }

    static CxxDeclaration* make_linkage_specification(CxxName *aName) 
    {
        YACC_DEBUG_PRINT;
        o_assert_no_implementation();
        return 0;
    }

    static CxxDeclaration* make_namespace_alias_definition(CxxName *aName, CxxName *forId) 
    {
        YACC_DEBUG_PRINT;
        return new CxxNamespaceAliasDeclaration(aName, forId);
    }

    static CxxDeclaration* make_namespace_declaration(CxxName *aName) 
    {
        YACC_DEBUG_PRINT;
        return new CxxNamespaceDeclaration((CxxNamespaceDefinition*)aName);
    }

    static CxxName* make_namespace_definition(CxxName *aName, CxxDeclarations *aDeclaration) 
    {
        YACC_DEBUG_PRINT;
        return new CxxNamespaceDefinition(aName, aDeclaration);
    }

    static CxxDeclarator* make_nested_ptr_declarator(CxxName *aName, CxxDeclarator *aDeclarator) 
    {
        YACC_DEBUG_PRINT;
        aName->swallow(aDeclarator->name);
        aDeclarator->name = aName;
        return aDeclarator;
    }

    static CxxName* make_nested_id(CxxName *nestingId, CxxName *nestedId) 
    {
        YACC_DEBUG_PRINT;
        nestingId->swallow(nestedId);
        return nestingId;
    }

    static CxxName* make_nested_scope(CxxName *nestingId) 
    {
        YACC_DEBUG_PRINT;
        return nestingId;
    }

    static CxxExpression* make_minus_expression(CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxPreUnaryExpression("-", anExpr);
    }

    static CxxExpression* make_modulus_expression(CxxExpression *leftExpr, CxxExpression *rightExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxBinaryExpression("%", leftExpr, rightExpr);
    }


    static CxxExpression* make_complex_pointer_expression(CxxExpression *leftExpr, CxxDeclarator *aDeclarator, CxxExpression *rightExpr) 
    {
        if(leftExpr)
        {
            if(leftExpr->declSpecifier == nullptr)
                leftExpr->declSpecifier = aDeclarator->name->declSpecifier;
            else 
                leftExpr->declSpecifier->swallow(aDeclarator->name->declSpecifier);
            if(rightExpr)
            {
                leftExpr->declSpecifier->swallow(rightExpr->asName());
            }
            return leftExpr;
        }
        o_assert_no_implementation();
        return nullptr;
    }

    static CxxExpression* make_multiply_expression(CxxExpression *leftExpr, CxxDeclarator *aDeclarator, CxxExpression *rightExpr) 
    {
        YACC_DEBUG_PRINT;
        if(leftExpr AND rightExpr)
        {
            if(aDeclarator->name->declSpecifier->asIdentifier() == "*")
            {
                // delete aDeclarator;
                return new CxxBinaryExpression("*", leftExpr, rightExpr);
            }
            else 
            {
                o_assert_no_implementation();
//                 if(leftExpr->declSpecifier == nullptr)
//                     leftExpr->declSpecifier = aDeclarator->name->declSpecifier;
//                 else 
//                     leftExpr->declSpecifier->swallow(aDeclarator->name->declSpecifier);
//                 CxxName* rightName = rightExpr->asName();
//                 if(rightName)
//                 {
//                     rightName->takeBack();
//                 }
//                 leftExpr->declSpecifier->swallow(rightName);
//                 return new CxxVariableDeclarationExpression;
            }
        }
        else 
        {
            o_assert(leftExpr);
            if(leftExpr->declSpecifier)
                leftExpr->declSpecifier->swallow(aDeclarator->name->declSpecifier);
            else 
                leftExpr->declSpecifier = aDeclarator->name->declSpecifier;
            aDeclarator->name->declSpecifier = nullptr;
            // delete aDeclarator;
            return leftExpr;
        }
        //return new CxxVariableDeclarationExpression(leftExpr, aDeclarator, rightExpr);
        return nullptr;
    }

    static CxxName* make_name(CxxName *aName) 
    {
        YACC_DEBUG_PRINT;
        return aName;
    }

    static CxxName* make_name_expression(CxxName *aName) 
    {
        YACC_DEBUG_PRINT;
        return aName;
    }

    static CxxNewExpression* make_new_expression(CxxParameters *aPlace, CxxParameters *aType, CxxExpression *anInit) 
    {
        YACC_DEBUG_PRINT;
        return new CxxNewParenthesisExpression(aPlace, aType, anInit);
    }

    static CxxNewExpression* make_new_type_id_expression(CxxParameters *aPlace, CxxExpression *aType, CxxExpression *anInit) 
    {
        YACC_DEBUG_PRINT;
        return new CxxNewExpression(aPlace, aType, anInit);
    }

    static CxxExpression* make_not_equal_expression(CxxExpression *leftExpr, CxxExpression *rightExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxBinaryExpression("!=", leftExpr, rightExpr);
    }

    static CxxExpression* make_not_expression(CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxPreUnaryExpression("!", anExpr);
    }

    static CxxName* make_operator_add_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("+");
    }

    static CxxName* make_operator_arrow_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("->");
    }

    static CxxName* make_operator_arrow_star_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("->*");
    }

    static CxxName* make_operator_ass_add_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("+=");
    }

    static CxxName* make_operator_ass_bit_and_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("&=");
    }

    static CxxName* make_operator_ass_bit_or_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("|=");
    }

    static CxxName* make_operator_ass_div_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("/=");
    }

    static CxxName* make_operator_ass_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("=");
    }

    static CxxName* make_operator_ass_mod_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("%=");
    }

    static CxxName* make_operator_ass_mul_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("*=");
    }

    static CxxName* make_operator_ass_shl_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("<<=");
    }

    static CxxName* make_operator_ass_shr_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName(">>=");
    }

    static CxxName* make_operator_ass_sub_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("-=");
    }

    static CxxName* make_operator_ass_xor_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("^=");
    }

    static CxxName* make_operator_bit_and_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("&");
    }

    static CxxName* make_operator_bit_not_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("~");
    }

    static CxxName* make_operator_bit_or_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("|");
    }

    static CxxName* make_operator_call_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("()");
    }

    static CxxName* make_operator_comma_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName(",");
    }

    static CxxName* make_operator_dec_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("--");
    }

    static CxxName* make_operator_delete_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("delete");
    }

    static CxxName* make_operator_div_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("/");
    }

    static CxxName* make_operator_eq_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("==");
    }

    static CxxName* make_operator_function_id(CxxName *operatorId) 
    {
        YACC_DEBUG_PRINT;
        operatorId->words.back().id = "operator"+operatorId->words.back().id;
        return operatorId;
    }

    static CxxName* make_operator_ge_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName(">=");
    }

    static CxxName* make_operator_gt_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName(">");
    }

    static CxxName* make_operator_inc_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("++");
    }

    static CxxName* make_operator_index_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("[]");
    }

    static CxxName* make_operator_le_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("<=");
    }

    static CxxName* make_operator_log_and_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("&&");
    }

    static CxxName* make_operator_log_not_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("!");
    }

    static CxxName* make_operator_log_or_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("||");
    }

    static CxxName* make_operator_lt_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("<");
    }

    static CxxName* make_operator_mod_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("%");
    }

    static CxxName* make_operator_mul_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("*");
    }

    static CxxName* make_operator_ne_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("!=");
    }

    static CxxName* make_operator_new_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("new");
    }

    static CxxName* make_operator_shl_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("<<");
    }

    static CxxName* make_operator_shr_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName(">>");
    }

    static CxxName* make_operator_sub_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("-");
    }

    static CxxName* make_operator_xor_id() 
    {
        YACC_DEBUG_PRINT;
        return new CxxName("^");
    }

    static CxxParameters* make_parameters(CxxParameters *aList, CxxParameter *anElement) 
    {
        YACC_DEBUG_PRINT;
        if(aList == nullptr) 
        {
            if(anElement == nullptr) return nullptr;
            aList = new CxxParameters;
        }
        o_assert(anElement);
        aList->add(anElement);
        return aList;
    }

    static CxxParenthesised* make_parenthesised(CxxParameters *aList, CxxCvQualifiers *cvQualifiers, CxxName *refQualifier, CxxExceptionSpecification *exceptionSpecification) 
    {
        YACC_DEBUG_PRINT;
        return new CxxParenthesised(aList, cvQualifiers, refQualifier, exceptionSpecification);
    }

    static CxxExpression* make_plus_expression(CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxPreUnaryExpression("+", anExpr);
    }

    static CxxPointerDeclarator* make_pointer_declarator() 
    {
        YACC_DEBUG_PRINT;
        return new CxxPointerDeclarator();
    }

    static CxxExpression* make_pointer_expression(CxxDeclarator *aDeclarator, CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        if(anExpr)
        {
            for(auto it = aDeclarator->name->declSpecifier->rbegin(); it != aDeclarator->name->declSpecifier->rend(); ++it)
            {
                if(*it == "&")
                    anExpr = new CxxPreUnaryExpression("&", anExpr);
                else if(*it == "*")
                    anExpr = new CxxPreUnaryExpression("*", anExpr);
                else if(*it == "@")
                    anExpr = new CxxPreUnaryExpression("@", anExpr);
                else
                {
                    // delete aDeclarator;
                    return new CxxInvalidExpression(anExpr);
                }
            }
        }
        else 
        {
            anExpr = aDeclarator->name->declSpecifier;
            aDeclarator->name->declSpecifier = nullptr;
        }
        // delete aDeclarator;
        return anExpr;
    }

    static CxxExpression* make_post_decrement_expression(CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxPostUnaryExpression("--",anExpr);
    }

    static CxxExpression* make_post_increment_expression(CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxPostUnaryExpression("++",anExpr);
    }

    static CxxExpression* make_pre_decrement_expression(CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxPreUnaryExpression("--",anExpr);
    }

    static CxxExpression* make_pre_increment_expression(CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxPreUnaryExpression("++",anExpr);
    }

    static CxxName* make_pseudo_destructor_id(CxxBuiltInId *aScope, CxxBuiltInId *aName) 
    {
        YACC_DEBUG_PRINT;
        aName->words.front().id = '~'+aName->words.front().id;
        aScope->swallow(aName);
        return aScope;
    }

    static CxxDeclSpecifierId* make_pure_virtual() 
    {
        YACC_DEBUG_PRINT;
        return new CxxDeclSpecifierId("abstract");
    }

    static CxxDeclarator* make_reference_declarator() 
    {
        YACC_DEBUG_PRINT;
        return new CxxDeclarator('&');
    }

    static CxxDataExpression* make_data_expression(CxxNumberLiteral<hex_t>* expr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxDataExpression(expr);
    }

    static CxxExpression* make_reinterpret_cast_expression(CxxExpression *aType, CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxReinterpretCastExpression(aType, anExpr);
    }

    static CxxStatement* make_return_statement(CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxReturnStatement(anExpr);
    }

    static CxxName* make_scoped_id(CxxName *globalId, CxxName *nestedId) 
    {
        YACC_DEBUG_PRINT;
        globalId->swallow(nestedId);
        return globalId;
    }

    static CxxExpression* make_scoped_pointer_expression(CxxExpression *aScope, CxxDeclarator *aDeclarator, CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxScopedPointerExpression(aScope, aDeclarator, anExpr);
    }

    static CxxDeclSpecifierId* make_set_template_decl_specifier(CxxDeclSpecifierId *aName) 
    {
        YACC_DEBUG_PRINT;
        return new CxxDeclSpecifierId("template");
    }

    static CxxDeclaration* make_set_template_declaration(CxxDeclaration *aDeclaration) 
    {
        YACC_DEBUG_PRINT;
        return aDeclaration;
    }

    static CxxExpression* make_set_template_expression(CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return anExpr;
    }

    static CxxName* make_set_template_id(CxxName *aName) 
    {
        YACC_DEBUG_PRINT;
        return aName;
    }

    static CxxName* make_set_template_name(CxxName *aName) 
    {
        YACC_DEBUG_PRINT;
        return aName;
    }

    static CxxName* make_set_template_scope(CxxName *aName) 
    {
        YACC_DEBUG_PRINT;
        return aName;
    }

    static CxxTemplateParameters* make_template_parameters(CxxTemplateParameters* aList, CxxTemplateParameter* anElement)
    {
        YACC_DEBUG_PRINT;
        if(aList == nullptr) 
        {
            if(anElement == nullptr) return nullptr;
            aList = new CxxTemplateParameters;
        }
        aList->add(anElement);
        return aList;
    }

    static CxxTemplatedTypeParameter* make_templated_type_parameter(CxxTemplateParameters* aList, CxxName* aName)
    {
        YACC_DEBUG_PRINT;
        return new CxxTemplatedTypeParameter(aList, aName);
    }

    static CxxExpression* make_shift_left_expression(CxxExpression *leftExpr, CxxExpression *rightExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxBinaryExpression("<<", leftExpr, rightExpr);
    }

    static CxxExpression* make_shift_right_expression(CxxExpression *leftExpr, CxxExpression *rightExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxBinaryExpression(">>", leftExpr, rightExpr);
    }

    static CxxDeclaration* make_simple_declaration(CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxSimpleDeclaration(anExpr);
    }

    static CxxImportSymbolDeclaration* make_import_symbol_declaration(CxxName* symbol, CxxName* alias)
    {
        YACC_DEBUG_PRINT;
        return new CxxImportSymbolDeclaration(symbol, alias);
    }

    static CxxImportSymbolDeclarations* make_import_symbol_declarations(CxxImportSymbolDeclarations* list, CxxImportSymbolDeclaration* elem)
    {
        YACC_DEBUG_PRINT;
        if(list == nullptr)
        {
            if(elem == nullptr) return nullptr;
            list = new CxxImportSymbolDeclarations;
        }
        list->add(elem);
        return list;
    }

    static CxxName* make_dot_qualified_name(CxxName* left, CxxName* right)
    {
        if(right != nullptr) 
            left->back().id += '.'+right->back().id;
        return left;
    }

    static CxxImportDeclaration* make_import_declaration(CxxName* dotQualifiedName, CxxImportSymbolDeclarations* symbolList ) 
    {
        YACC_DEBUG_PRINT;
        return new CxxImportDeclaration(dotQualifiedName, symbolList);
    }

    static CxxExpression* make_sizeof_expression(CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxSizeOfExpression(anExpr);
    }

    static CxxExpression* make_static_cast_expression(CxxExpression *aType, CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxStaticCastExpression(aType, anExpr);
    }

    static CxxExpression* make_string_literal_expression(CxxStrings *aString) 
    {
        YACC_DEBUG_PRINT;
        return new CxxStringLiteralExpression(aString);
    }

    static CxxExpression* make_subtract_expression(CxxExpression *leftExpr, CxxExpression *rightExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxBinaryExpression("-", leftExpr, rightExpr);
    }

    static CxxTemplateArgument* make_template_argument(CxxParameter *aParameter) 
    {
        YACC_DEBUG_PRINT;
        return new CxxTemplateArgument(aParameter);
    }

    static CxxTemplateArguments* make_template_arguments(CxxTemplateArguments *aList, CxxTemplateArgument *anElement) 
    {
        YACC_DEBUG_PRINT;
        if(aList == nullptr) aList = new CxxTemplateArguments;
        aList->add(anElement);
        return aList;
    }

    static CxxDeclaration* make_template_declaration(CxxTemplateParameters *aList, CxxDeclaration *aDeclaration) 
    {
        YACC_DEBUG_PRINT;
        return new CxxTemplateDeclaration(aList, aDeclaration);
    }

    static CxxName* make_template_name(CxxName *aName, CxxTemplateArguments *templateArguments) 
    {
        YACC_DEBUG_PRINT;
        aName->setLastTemplateArguments(templateArguments);
        return aName;
    }

    static CxxTemplateParameter* make_template_parameter(CxxParameter *aParameter) 
    {
        YACC_DEBUG_PRINT;
        CxxTemplateParameter* tp = new CxxTemplateParameter(aParameter->expr);
        aParameter->expr = nullptr;
        // delete aParameter;
        return tp;
    }

    static CxxExpression* make_this_expression() 
    {
        YACC_DEBUG_PRINT;
        return new CxxThisExpression();
    }

    static CxxExpression* make_throw_expression(CxxExpression *anExpr) 
    {
        YACC_DEBUG_PRINT;
        return new CxxThrowExpression(anExpr);
    }

    static CxxExpression* make_true_expression() 
    {
        YACC_DEBUG_PRINT;
        return new CxxNumberLiteralExpression<bool>(new CxxNumberLiteral<bool>(0, true));
    }

    static CxxExpression* make_type1_expression(CxxExpression *functionName, CxxParenthesised *aParenthesis, CxxType1Parameters *type1Parameters) 
    {
        YACC_DEBUG_PRINT;
        return new CxxType1Expression(functionName, aParenthesis, type1Parameters);
    }

    static CxxExpression* make_typed_expression(CxxName *frontName, CxxExpression *backName) 
    {
        YACC_DEBUG_PRINT;
        return new CxxTypedExpression(frontName, backName);
    }

    static CxxFunctionBody* make_try_block(CxxStatement *aStatement, CxxHandlers *exceptionHandlers) 
    {
        YACC_DEBUG_PRINT;
        return new CxxTryBlock(aStatement, exceptionHandlers);
    }

    static CxxStatement* make_switch_statement(CxxCondition *testExpr, CxxStatement *aStmt) 
    {
        YACC_DEBUG_PRINT;
        return new CxxSwitchStatement(testExpr, aStmt);
    }

    static CxxStatements* make_statements(CxxStatements * aStmts, CxxStatement *aStmt) 
    {
        YACC_DEBUG_PRINT;
        if(aStmts == nullptr) 
        {
            if(aStmt == nullptr) return nullptr;
            aStmts = new CxxStatements;
        }
        aStmts->add(aStmt);
        return aStmts;
    }

    static CxxStatement* make_try_block_statement(CxxFunctionBody *tryBlock) 
    {
        YACC_DEBUG_PRINT;
        return new CxxTryBlockStatement(tryBlock);
    }

    static CxxFunctionBody* make_try_function_block(CxxFunctionBody *functionBody, CxxHandlers *exceptionHandlers) 
    {
        YACC_DEBUG_PRINT;
        return new CxxTryFunctionBlock(functionBody, exceptionHandlers);
    }

    static CxxName* make_typed_name(CxxName *frontName, CxxName *backName) 
    {
        YACC_DEBUG_PRINT;
        return new CxxTypedName(frontName, backName);
    }

    static CxxExpression* make_typeid_expression(CxxExpression *aList) 
    {
        YACC_DEBUG_PRINT;
        return new CxxTypeIdExpression(aList);
    }

    static CxxSimpleTypeParameter* make_typename_type_parameter(CxxName *aName) 
    {
        YACC_DEBUG_PRINT;
        return new CxxClassTypeParameter(aName);
    }

    static CxxType1Parameters* make_type1_parameters(CxxType1Parameters *aList, CxxParameters *someParameters) 
    {
        YACC_DEBUG_PRINT;
        if(aList == nullptr) aList = new CxxType1Parameters;
        aList->add(someParameters);
        return aList;
    }

    static CxxDeclaration* make_using_declaration(bool isTypename, CxxName *aName) 
    {
        YACC_DEBUG_PRINT;
        return new CxxUsingDeclaration(isTypename, aName);
    }

    static CxxDeclaration* make_using_namespace_directive(CxxName *aName) 
    {
        YACC_DEBUG_PRINT;
        return new CxxUsingNamespaceDirective(aName);
    }

    static CxxUtility* make_utility(CxxUtility *aUtility) 
    {
        YACC_DEBUG_PRINT;
        return aUtility;
    }

    static CxxUtility* make_utility_mode() 
    {
        YACC_DEBUG_PRINT;
        return new CxxUtility;
    }

    static CxxBaseSpecifier* make_virtual_base_specifier(CxxBaseSpecifier *baseSpecifier) 
    {
        YACC_DEBUG_PRINT;
        o_assert_no_implementation();
        // o_semantic_error("phantom does not support virtual inheritance");
        baseSpecifier->isVirtual = true;
        return baseSpecifier;
    }

    static CxxStatement* make_while_statement(CxxCondition *testExpr, CxxStatement *aStmt) 
    {
        YACC_DEBUG_PRINT;
        return new CxxWhileStatement(testExpr, aStmt);
    }

};

}
