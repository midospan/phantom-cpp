#ifndef precompiler_h__
#define precompiler_h__

#include "ast.h"

o_namespace_begin(phantom, reflection)

class LabelStatement;
class Statement;
class Expression;
class Block;
class ConstantExpression;
class ArrayInitializerExpression;

o_namespace_end(phantom, reflection)

o_namespace_begin(phantom, reflection, cpp, ast)

struct addressed_access_builder;

class precompiler
{
    friend class CPlusPlus;

    precompiler() : m_pMessage(nullptr) {}
    precompiler(Message* a_pMessage) : m_pMessage(a_pMessage) {}

    struct element_garbage
    {
        void add(LanguageElement* a_pElement);
        void remove(LanguageElement* a_pElement);

        ~element_garbage();

        void clear() { m_elements.clear(); }

        vector<LanguageElement*> m_elements;
    };

    Block*              precompile_block(block& b, LanguageElement* a_pScope);
    void                precompile_block(block& b, Block* a_pScope);

    void                precompile_if_statement(if_statement&, Block* a_pBlock);
    void                precompile_for_statement(for_statement&, Block* a_pBlock);
    void                precompile_while_statement(while_statement&, Block* a_pBlock);
    void                precompile_do_while_statement(do_while_statement&, Block* a_pBlock);
    void                precompile_switch_statement(switch_statement&, Block* a_pBlock);
    void                precompile_goto_statement(goto_statement&, Block* a_pBlock);
    void                precompile_return_statement(return_statement&, Block* a_pBlock);
    void                precompile_label_statement(label_statement&, Block* a_pBlock);
    void                precompile_variable_declaration(variable_declaration&, Block* a_pBlock, vector<LocalVariable*>* a_pOut);
    void                precompile_variable_declaration(variable_declaration&, Namespace* a_pNamespace);
    void                precompile_statement(statement& s, LanguageElement* a_pScope);
    void                precompile_statement(statement& s, Block* a_pBlock);
    Expression*         precompile_expression(expression& e, Block* a_pBlock);
    Expression*         precompile_expression(expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
    Expression*         precompile_cast_expression(cast_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
    Expression*         precompile_pre_unary_expression(pre_unary_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
    Expression*         precompile_post_unary_expression(post_unary_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
    //LanguageElement   * precompile_binary_left_expression(binary_left_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
    Expression*         precompile_binary_right_expression(binary_right_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
    Expression*         precompile_ternary_if_expression(ternary_if_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
    Expression*         precompile_call_expression(call_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
    Expression*         precompile_bracket_expression(bracket_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
    LanguageElement*    precompile_element(LanguageElement* a_pLHS, element & e, LanguageElement* a_pScope);
    LanguageElement*    precompile_element(const string& a_strName, const vector<TemplateElement*>* a_pTemplateSignature, const vector<LanguageElement*>* a_pFunctionSignature, bool a_bConstSignature, reflection::LanguageElement* a_pScope);
    LanguageElement*    precompile_element_recursive(element & e, LanguageElement* a_pScope);
    LanguageElement*    precompile_qualified_name(LanguageElement* a_pLHS, qualified_name & qn, vector<LanguageElement*>* a_pSignature, bool a_bConstSignature, LanguageElement* a_pScope);
    Type*               precompile_type(LanguageElement* a_pLHS, type & e, LanguageElement* a_pScope);
    Type*               precompile_type(const string& a_strName, const vector<TemplateElement*>* a_pTemplateSignature, reflection::LanguageElement* a_pScope);
    Type*               precompile_type_recursive(type & e, LanguageElement* a_pScope);
    LanguageElement*    precompile_template_element(LanguageElement* a_pLHS, type & e, LanguageElement* a_pScope);
    LanguageElement*    precompile_template_element_recursive(type & e, LanguageElement* a_pScope);
    void                precompile_compilation_unit(compilation_unit & e, Namespace* a_pNamespace = phantom::rootNamespace());
    Type*               precompile_type_qualifier(Type* a_pType, char qualifier);
    bool                precompile_function_signature(function_signature& fs, vector<LanguageElement*>& out, LanguageElement* a_pScope);
    bool                precompile_template_signature(vector<template_element>& ts, vector<TemplateElement*>& out, LanguageElement* a_pScope);
    LanguageElement*    precompile_template_element(template_element& e, LanguageElement* a_pScope);
    ConstantExpression* precompile_fundamental_literal( fundamental_literal& fl );
    ConstantExpression* precompile_integral_literal( integral_literal& il );
    LanguageElement*    precompile_name(LanguageElement* a_pLHS, name& n, const vector<LanguageElement*>* a_pFunctionSignature, bool a_bConst, LanguageElement* a_pScope);
    void                precompile_namespace_scope(namespace_scope & ns, Namespace* a_pNamespace);
    void                precompile_namespace_member_declaration(namespace_member_declaration & cu, Namespace* a_pNamespace);
    void                precompile_namespace_declaration(namespace_declaration & nd, Namespace* a_pNamespace);
    void                precompile_nested_class_declaration(class_declaration & cd, int a_Modifiers, Class* a_pClass);
    void                precompile_class_declaration(class_declaration & cd, Namespace* a_pNamespace);
    string_node         precompile_named_or_unnamed_class_declaration(named_or_unnamed_class_declaration & cd, class_scope*& a_ClassScope);
    void                precompile_class_scope(class_scope & cd, int a_iAccessQualifier, Class* a_pClass);
    void                precompile_class_member_declaration(class_member_declaration & cmd, int& a_iAccessQualifier, Class* a_pClass);
    Signature*          precompile_signature(type& return_type, parameters& params, LanguageElement* a_pScope);
    void                precompile_parameters_local_variables(parameters& params, Signature* a_pSignature, Block* a_pBlock);
    void                precompile_member_declaration(member_declaration& md, int a_Modifiers, Class* a_pClass);
    bool                precompile_string_literal(string_node& s, string& out);

    void error(const CodeLocation& a_Location, const char* a_Format, ...);
    void                precompile_array_initializer(LocalVariable* a_pLocalVariable, ArrayType* a_pArrayType, array_initializer& ai, Block* a_pBlock );
    void                precompile_array_initializer_or_expression(LocalVariable* a_pLocalVariable, Type* a_pType, array_initializer_or_expression& aie, Block* a_pBlock );
    LocalVariable*      precompile_variable_declarator(Type* a_pBaseType, variable_declarator& vd, Block* a_pBlock);
    void                precompile_initialization(Type* a_pBaseType, const addressed_access_builder& aab, Expression* a_pExpression, Block* a_pBlock);
    Expression*         precompile_variable_declaration_or_expression(variable_declaration_or_expression& vde, Block* a_pBlock);
    LanguageElement*    precompile_qualified_name_recursive( qualified_name & qn, vector<LanguageElement*>* a_pSignature, bool a_bConstSignature, LanguageElement* a_pScope );
    Message* m_pMessage;
};

o_namespace_end(phantom, reflection, cpp, ast)

#endif // precompiler_h__
