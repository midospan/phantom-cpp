
#include "phantom/phantom.h"
#include "ast.h"
#include <boost/fusion/adapted/struct.hpp>
#include "phantom/reflection/StaticVariableAccess.h"
#include "phantom/reflection/ConstantExpression.h"
#include "phantom/reflection/StringLiteralExpression.h"
#include "phantom/reflection/ExpressionStatement.h"
#include "phantom/reflection/Block.h"

o_namespace_begin(phantom, reflection, cpp, ast)

struct o_export precompiler
{
    struct element_garbage
    {
        void add(LanguageElement* a_pElement)
        {
            if(a_pElement)
            {
                m_elements.push_back(a_pElement);
            }
        }

        ~element_garbage()
        {
            for(auto it = m_elements.begin(); it != m_elements.end(); ++it)
            {
                if((*it)->asEvaluable() && (*it)->getOwner() == nullptr && (*it)->getModule() == nullptr) // if not in a module or not in another element we can delete it
                {
                    (*it)->terminate();
                    (*it)->deleteNow();
                }
            }
        }

        void clear() { m_elements.clear(); }

        vector<LanguageElement*> m_elements;
    };

    ClassType*       precompile_class_declaration(class_declaration& a_class_declaration, LanguageElement* a_pScope);    
    Block*           precompile_block(block& b, LanguageElement* a_pScope);
    Block*           precompile_block(block& b, Block* a_pScope);

    LanguageElement* precompile_if_statement(if_statement&, Block* a_pBlock);
    LanguageElement* precompile_for_statement(for_statement&, Block* a_pBlock);
    LanguageElement* precompile_while_statement(while_statement&, Block* a_pBlock);
    LanguageElement* precompile_do_while_statement(do_while_statement&, Block* a_pBlock);
    LanguageElement* precompile_switch_statement(switch_statement&, Block* a_pBlock);
    LanguageElement* precompile_goto_statement(goto_statement&, Block* a_pBlock);
    LanguageElement* precompile_label_statement(label_statement&, Block* a_pBlock);
    LanguageElement* precompile_variable_declaration(variable_declaration&, Block* a_pBlock);
    LanguageElement* precompile_variable_declaration(variable_declaration&, Namespace* a_pNamespace);
    LanguageElement* precompile_statement(statement& s, LanguageElement* a_pScope);
    LanguageElement* precompile_statement(statement& s, Block* a_pBlock);
    LanguageElement* precompile_expression(expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
    LanguageElement* precompile_cast_expression(cast_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
    LanguageElement* precompile_pre_unary_expression(pre_unary_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
    LanguageElement* precompile_post_unary_expression(post_unary_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
    LanguageElement* precompile_binary_left_expression(binary_left_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
    LanguageElement* precompile_binary_right_expression(binary_right_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
    LanguageElement* precompile_ternary_if_expression(ternary_if_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
    LanguageElement* precompile_call_expression(call_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS = nullptr);
    LanguageElement* precompile_element(LanguageElement* a_pLHS, element & e, LanguageElement* a_pScope);
    LanguageElement* precompile_element(const string& a_strName, const vector<TemplateElement*>* a_pTemplateSignature, const vector<LanguageElement*>* a_pFunctionSignature, bool a_bConstSignature, reflection::LanguageElement* a_pScope);
    LanguageElement* precompile_element_recursive(element & e, LanguageElement* a_pScope);

    LanguageElement* precompile_compilation_unit(compilation_unit & e, LanguageElement* a_pScope);
    Type* precompile_type_qualifier(Type* a_pType, char qualifier);
    void precompile_element_extension(element_extension & ee, qualifier_or_extent_or_signatures& extensions, bool* a_pConstSignature);
    bool precompile_function_signature(extent_or_signature& fs, vector<LanguageElement*>& out, LanguageElement* a_pScope);
    bool precompile_template_signature(vector<template_element>& ts, vector<TemplateElement*>& out, LanguageElement* a_pScope);
    LanguageElement* precompile_name(LanguageElement* a_pLHS, name& n, const vector<LanguageElement*>* a_pFunctionSignature, bool a_bConst, LanguageElement* a_pScope);
};

o_namespace_end(phantom, reflection, cpp, ast)
