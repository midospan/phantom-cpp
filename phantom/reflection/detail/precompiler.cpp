/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <boost/spirit/include/qi.hpp>
#include "precompiler.h"
/* *********************************************** */
o_namespace_begin(phantom, reflection, cpp, ast)

LanguageElement*  precompiler::precompile_element(const string& a_strName, const vector<TemplateElement*>* a_pTemplateSignature, const vector<LanguageElement*>* a_pFunctionSignature, bool a_bConstSignature, reflection::LanguageElement* a_pScope)
{
    o_assert(!a_bConstSignature OR a_pFunctionSignature != nullptr);
    LanguageElement* pSolvedElement = a_pScope->solveElement(
        a_strName
        , a_pTemplateSignature
        , a_pFunctionSignature
        , a_bConstSignature ? o_const : 0
        );
    return pSolvedElement;
}

Type*   precompiler::precompile_type_qualifier(Type* a_pType, char qualifier)
{
    switch(qualifier)
    {
    case 'µ': // const
        return a_pType->constType();
    case '&': // ref
        return a_pType->referenceType();
    case '*': // pointer
        return a_pType->pointerType();
    default:
        o_assert(false);
    }
    return nullptr;
}

void precompiler::precompile_element_extension(element_extension & ee, qualifier_or_extent_or_signatures& extensions, bool* a_pConstSignature)
{
    *a_pConstSignature = false;
    qualifier_and_qualifier_or_extents* p_qualifier_and_qualifier_or_extents = nullptr;
    extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_signatures* p_extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_function_signatures = nullptr;
    function_prototype* p_function_prototype = nullptr;
    element_extension_visitor eev(&p_qualifier_and_qualifier_or_extents
        , &p_extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_function_signatures
        , &p_function_prototype);
    ee.apply_visitor(eev);
    if(p_qualifier_and_qualifier_or_extents)
    {
        extensions.push_back(p_qualifier_and_qualifier_or_extents->m_qualifier);
        auto& vec = p_qualifier_and_qualifier_or_extents->m_qualifier_or_extents;
        for(auto it = vec.begin(); it != vec.end(); ++it)
        {
            qualifier_or_extent_or_signature& qoe = *it;
            char* p_qualifier = nullptr;
            extent_or_signature* p_extent_or_signature = nullptr;
            qualifier_or_extent_or_signature_visitor qoev(&p_qualifier, &p_extent_or_signature);
            qoe.apply_visitor(qoev);
            if(p_qualifier)
            {
                extensions.push_back(*p_qualifier);
            }
            else 
            {
                o_assert(p_extent_or_signature);
                extensions.push_back(*p_extent_or_signature);
            }
        }
    }
    else if(p_extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_function_signatures)
    {

        extensions.push_back(p_extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_function_signatures->m_extent);
        qualifier_and_qualifier_or_extents_OR_extent_or_signatures& to_visit = p_extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_function_signatures->m_qualifier_and_qualifier_or_extents_OR_extent_or_signatures;
        qualifier_and_qualifier_or_extents* p_qualifier_and_qualifier_or_extents = nullptr;
        extent_or_signatures* p_extent_or_function_signatures = nullptr;
        qualifier_and_qualifier_or_extents_OR_extent_or_signatures_visitor visitor(&p_qualifier_and_qualifier_or_extents, &p_extent_or_function_signatures);
        to_visit.apply_visitor(visitor);
        if(p_qualifier_and_qualifier_or_extents)
        {
            extensions.push_back(p_qualifier_and_qualifier_or_extents->m_qualifier);
            for(auto it = p_qualifier_and_qualifier_or_extents->m_qualifier_or_extents.begin(); it != p_qualifier_and_qualifier_or_extents->m_qualifier_or_extents.end(); ++it)
            {
                qualifier_or_extent_or_signature& qoe = *it;
                char* p_qualifier = nullptr;
                extent_or_signature* p_extent_or_signature = nullptr;
                qualifier_or_extent_or_signature_visitor qoev(&p_qualifier, &p_extent_or_signature);
                qoe.apply_visitor(qoev);
                if(p_qualifier)
                {
                    extensions.push_back(*p_qualifier);
                }
                else 
                {
                    o_assert(p_extent_or_signature);
                    extensions.push_back(*p_extent_or_signature);
                }
            }
        }
        else 
        {
            o_assert(p_extent_or_function_signatures);
            for(auto it = p_extent_or_function_signatures->begin(); it != p_extent_or_function_signatures->end(); ++it)
            {
                extensions.push_back(*it);
            }
        }
    }
    else 
    {
        o_assert(p_function_prototype);
        extensions.push_back(p_function_prototype->m_signature);
        if(p_function_prototype->m_const_modifier.is_initialized())
        {
            *a_pConstSignature = (*p_function_prototype->m_const_modifier == 'µ');
        }
    }
}

bool precompiler::precompile_function_signature(extent_or_signature& fs, vector<LanguageElement*>& out, LanguageElement* a_pScope)
{
    element_garbage garbage;
    LanguageElement* pFirstSignatureElement = nullptr;
    auto it = fs.m_list.begin();
    auto end = fs.m_list.end();
    for(;it!=end;++it)
    {
        LanguageElement* pElement = precompile_expression(*it, a_pScope);
        garbage.add(pElement);
        if(pElement == nullptr)
        {
            return false;
        }
        out.push_back(pElement);
    }
    garbage.clear();
    return true;
}

bool precompiler::precompile_template_signature(vector<template_element>& ts, vector<TemplateElement*>& out, LanguageElement* a_pScope)
{
    element_garbage garbage;
    auto it = ts.begin();
    auto end = ts.end();
    for(;it!=end;++it)
    {
        LanguageElement* pTemplateSignatureElement = precompile_element_recursive(it->get(), a_pScope);
        garbage.add(pTemplateSignatureElement);
        if(pTemplateSignatureElement == nullptr) 
            return false;
        TemplateElement* pTemplateElement = pTemplateSignatureElement->asTemplateElement();
        if(pTemplateElement == nullptr)
        {
            return false;
        }
        out.push_back(pTemplateElement);
    }
    garbage.clear();
    return true;
}

LanguageElement* precompiler::precompile_name(LanguageElement* a_pLHS, name& n, const vector<LanguageElement*>* a_pFunctionSignature, bool a_bConst, LanguageElement* a_pScope)
{
    element_garbage garbage;
    LanguageElement* pElement = nullptr;
    if(n.m_template_signature.is_initialized()) // has template signature
    {
        vector<TemplateElement*> templateSignature;
        if(NOT(precompile_template_signature(*n.m_template_signature, templateSignature, a_pScope)))
            return nullptr;
        pElement = precompile_element(n.m_identifier, &templateSignature, a_pFunctionSignature, a_bConst, a_pLHS);
        garbage.add(pElement);
    }
    else
    {
        pElement = precompile_element(n.m_identifier, nullptr, a_pFunctionSignature, a_bConst, a_pLHS);
        garbage.add(pElement);
    }
    if(pElement == nullptr)
        return nullptr;
    garbage.clear();
    return pElement;
}

LanguageElement* precompiler::precompile_element(LanguageElement* a_pLHS, element & e, LanguageElement* a_pScope)
{
    element_garbage garbage;
    // name
    LanguageElement* pLHS = a_pLHS;
    bool bNameFullySolved = true;

    qualified_name& q_name = e.m_qualified_name;
    if(q_name.empty())
        return nullptr;

    auto it = q_name.begin();
    auto end = it+q_name.size()-1;
    for(;it!=end;++it)
    {
        // Each name inside the qualified name is treated and has potentially
        // a template specialization if it's a class type

        LanguageElement* pElement = precompile_name(pLHS, *it, nullptr, false, a_pScope);
        garbage.add(pElement);
        if(pElement == nullptr)
        {
            return nullptr;
        }
        pLHS = pElement;
    }

    name& last_name = e.m_qualified_name.back();

    qualifier_or_extent_or_signatures fseqs;
    if(e.m_const_modifier.is_initialized())
    {
        fseqs.push_back('µ');
    }

    bool bConstSignature = false;

    if(e.m_element_extension.is_initialized())
    {
        precompile_element_extension(*e.m_element_extension, fseqs, &bConstSignature);
    }

    if(bConstSignature && fseqs.size() != 1) // if const function modifier is present, only the signature must be present
        return nullptr;

    if(fseqs.size())
    {
        // solve front and combine with name for the first solving
        auto fseq_it = fseqs.begin();
        auto last_fseq_it = fseq_it;
        std::advance(last_fseq_it, fseqs.size()-1);
        qualifier_or_extent_or_signature& fseq = *fseq_it++;

        extent_or_signature* p_extent_or_signature = nullptr;
        char* p_qualifier = nullptr;
        qualifier_or_extent_or_signature_visitor fseqv(&p_qualifier, &p_extent_or_signature);
        fseq.apply_visitor(fseqv);

        if(p_qualifier)
        {
            LanguageElement* pElement = precompile_name(pLHS, last_name, nullptr, false, a_pScope);
            garbage.add(pElement);
            if(pElement == nullptr)
                return nullptr;
            Type* pType = pElement->asType();
            if(pType == nullptr)
                return nullptr;
            pType = precompile_type_qualifier(pType, *p_qualifier);
            garbage.add(pType);
            if(pType == nullptr)
                return nullptr;
            pLHS = pType;
        }
        else if(p_extent_or_signature->m_opening == token_ids::left_paren)
        {
            vector<LanguageElement*> functionSignature;
            if(NOT(precompile_function_signature(*p_extent_or_signature, functionSignature, a_pScope)))
            {
                return nullptr;
            }
            LanguageElement* pElement = precompile_name(pLHS, last_name, &functionSignature, bConstSignature, a_pScope);
            if(pElement == nullptr)
                return nullptr;
            pLHS = pElement;
        }
        else if(p_extent_or_signature->m_opening == token_ids::left_bracket)
        {
            if(p_extent_or_signature->m_list.size() != 1) 
                return nullptr;
            LanguageElement* pElement = precompile_name(pLHS, last_name, nullptr, false, a_pScope);
            garbage.add(pElement);
            if(pElement == nullptr)
                return nullptr;
            LanguageElement* pExtentElement = precompile_expression(p_extent_or_signature->m_list.back(), a_pScope);
            garbage.add(pExtentElement);
            if(pExtentElement == nullptr)
                return nullptr;
            Expression* pExtentExpression = pExtentElement->asExpression();
            if(pExtentExpression == nullptr)
                return nullptr;
            pElement = pElement->solveBinaryOperator("[]", pExtentExpression);
            garbage.add(pElement);
            if(pElement == nullptr)
                return nullptr;
            pLHS = pElement;
        }
        else return nullptr;

        for(; fseq_it != fseqs.end();)
        {
            qualifier_or_extent_or_signature& fseq = *fseq_it++;

            extent_or_signature* p_extent_or_signature = nullptr;
            char* p_qualifier = nullptr;
            qualifier_or_extent_or_signature_visitor fseqv(&p_qualifier, &p_extent_or_signature);
            fseq.apply_visitor(fseqv);
            if(p_qualifier)
            {
                Type* pType = pLHS->asType();
                if(pType == nullptr)
                    return nullptr;
                pType = precompile_type_qualifier(pType, *p_qualifier);
                garbage.add(pType);
                if(pType == nullptr)
                    return nullptr;
                pLHS = pType;
            }
            else if(p_extent_or_signature->m_opening == token_ids::left_paren)
            {
                vector<LanguageElement*> functionSignature;
                if(NOT(precompile_function_signature(*p_extent_or_signature, functionSignature, a_pScope)))
                {
                    return nullptr;
                }
                LanguageElement* pElement = pLHS->solveOperator("()", functionSignature);
                garbage.add(pElement);
                if(pElement == nullptr)
                    return nullptr;
                pLHS = pElement;
            }
            else if(p_extent_or_signature->m_opening == token_ids::left_bracket)
            {
                if(p_extent_or_signature->m_list.size() != 1) 
                    return nullptr;
                LanguageElement* pExtentElement = precompile_expression(p_extent_or_signature->m_list.back(), a_pScope);
                garbage.add(pExtentElement);
                if(pExtentElement == nullptr)
                    return nullptr;
                Expression* pExtentExpression = pExtentElement->asExpression();
                if(pExtentExpression == nullptr)
                    return nullptr;
                LanguageElement* pElement = pLHS->solveBinaryOperator("[]", pExtentExpression);
                garbage.add(pElement);
                if(pElement == nullptr)
                    return nullptr;
                pLHS = pElement;
            }
        }
    }
    else 
    {
        o_assert(!bConstSignature);
        LanguageElement* pElement = precompile_name(pLHS, last_name, nullptr, false, a_pScope);
        garbage.add(pElement);
        if(pElement == nullptr)
            return nullptr;
        pLHS = pElement;
    }

    garbage.clear();

    return pLHS;
}

LanguageElement* precompiler::precompile_element_recursive(element & e, LanguageElement* a_pScope)
{
    LanguageElement* pScope = a_pScope;
    LanguageElement* pResult = nullptr;
    while(pResult == nullptr && pScope)
    {
        pResult = precompile_element(pScope, e, a_pScope);
        pScope = pScope->getOwner();
    }
    return pResult;
}
/*

LanguageElement* precompile_root(root& r, LanguageElement* a_pScope)
{
    element* p_element = 0;
    block* p_block = 0;
    root_visitor rv(&p_element, &p_block);
    if(p_element)
    {
        return precompile_element_recursive(*p_element, a_pScope);
    }
    else if(p_block)
    {
        return precompile_block(*p_block, a_pScope);
    }
    return nullptr;
}*/

Block* precompiler::precompile_block(block& r, LanguageElement* a_pScope)
{
    Block* pBlock = o_new(Block);
    for(auto it = r.m_statements.begin(); it != r.m_statements.end(); ++it)
    {
        precompile_statement(*it, pBlock);
    }
    return pBlock;
}

Block* precompiler::precompile_block(block& r, Block* a_pBlock)
{
    Block* pBlock = precompile_block(r, (LanguageElement*)a_pBlock);
    a_pBlock->addStatement(pBlock);
    return pBlock;
}

LanguageElement* precompiler::precompile_if_statement(if_statement&, Block* a_pBlock) { return nullptr; }
LanguageElement* precompiler::precompile_for_statement(for_statement&, Block* a_pBlock) { return nullptr; }
LanguageElement* precompiler::precompile_while_statement(while_statement&, Block* a_pBlock) { return nullptr; }
LanguageElement* precompiler::precompile_do_while_statement(do_while_statement&, Block* a_pBlock) { return nullptr; }
LanguageElement* precompiler::precompile_switch_statement(switch_statement&, Block* a_pBlock) { return nullptr; }
LanguageElement* precompiler::precompile_goto_statement(goto_statement&, Block* a_pBlock) { return nullptr; }
LanguageElement* precompiler::precompile_label_statement(label_statement&, Block* a_pBlock) { return nullptr; }
LanguageElement* precompiler::precompile_variable_declaration(variable_declaration&, Block* a_pBlock) { return nullptr; }
LanguageElement* precompiler::precompile_variable_declaration(variable_declaration&, Namespace* a_pNamespace) { return nullptr; }

LanguageElement* precompiler::precompile_statement(statement& s, Block* a_pBlock)
{
    expression*                 p_expression = 0;
    block*                      p_block = 0;
    if_statement*               p_if_statement= 0 ;
    for_statement*              p_for_statement= 0;
    while_statement*            p_while_statement = 0;
    do_while_statement*         p_do_while_statement= 0;
    switch_statement*           p_switch_statement= 0;
    goto_statement*             p_goto_statement = 0;
    label_statement*            p_label_statement= 0;
    variable_declaration*       p_variable_declaration= 0;
    int* p_keywords_statement = 0;

    statement_visitor sv(&p_expression, &p_block, &p_if_statement, &p_for_statement, &p_while_statement, &p_do_while_statement, &p_switch_statement, &p_goto_statement, &p_label_statement, &p_variable_declaration, &p_keywords_statement);
    s.apply_visitor(sv);
    if(p_expression)
    {
        LanguageElement* pElement = precompile_expression(*p_expression, a_pBlock);
        if(pElement->asExpression())
        {
            Statement* pStatement = o_new(ExpressionStatement)(pElement->asExpression());
            a_pBlock->addStatement(pStatement);
            return pStatement;
        }
    }
    else if(p_block)
    {
        return precompile_block(*p_block, a_pBlock);
    }
    else if(p_variable_declaration)
    {
        return precompile_variable_declaration(*p_variable_declaration, a_pBlock);
    }
    else if(p_if_statement)
    {
        return precompile_if_statement(*p_if_statement, a_pBlock);
    }
    else if(p_for_statement)
    {
        return precompile_for_statement(*p_for_statement, a_pBlock);
    }
    else if(p_while_statement)
    {
        return precompile_while_statement(*p_while_statement, a_pBlock);
    }
    else if(p_switch_statement)
    {
        return precompile_switch_statement(*p_switch_statement, a_pBlock);
    }
    else if(p_do_while_statement)
    {
        return precompile_do_while_statement(*p_do_while_statement, a_pBlock);
    }
    else if(p_goto_statement)
    {
        return precompile_goto_statement(*p_goto_statement, a_pBlock);
    }
    else if(p_label_statement)
    {
        return precompile_label_statement(*p_label_statement, a_pBlock);
    }
    return nullptr;
}

LanguageElement* precompiler::precompile_expression(expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/)
{
    cast_expression* p_cast_expression = 0;
    pre_unary_expression* p_pre_unary_expression = 0;
    post_unary_expression* p_post_unary_expression = 0;
    binary_right_expression* p_binary_right_expression = 0;
    binary_left_expression* p_binary_left_expression = 0;
    ternary_if_expression* p_ternary_if_expression = 0;
    call_expression* p_call_expression = 0;
    element* p_element = 0;
    literal* p_literal = 0;
    expression_visitor ev(&p_cast_expression, &p_pre_unary_expression, &p_post_unary_expression, &p_binary_left_expression, &p_binary_right_expression, &p_ternary_if_expression, &p_call_expression, &p_element, &p_literal);
    e.apply_visitor(ev);
    {
        if(p_literal)
        {
            fundamental_literal* p_fundamental_literal;
            string* p_string;
            literal_visitor lv(&p_fundamental_literal, &p_string);
            p_literal->apply_visitor(lv);
            if(p_fundamental_literal)
            {
                float* p_float = 0; 
                double* p_double = 0; 
                longdouble* p_longdouble = 0; 
                int* p_int = 0; 
                uint* p_uint = 0; 
                short* p_short = 0; 
                ushort* p_ushort = 0; 
                longlong* p_longlong = 0; 
                ulonglong* p_ulonglong = 0; 
                char* p_char = 0; 
                bool* p_bool = 0;
                fundamental_literal_visitor flv(&p_float, &p_double, &p_longdouble, &p_int, &p_uint, &p_short, &p_ushort, &p_longlong, &p_ulonglong, &p_char, &p_bool);
                p_fundamental_literal->apply_visitor(flv);
                if(p_float) return o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::Constant, phantom::reflection::Constant::metaType, phantom::reflection::native::TNumericConstant<float>)(lexical_cast<string>(*p_float),*p_float), nullptr, true);
                else if(p_double) return o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::Constant, phantom::reflection::Constant::metaType, phantom::reflection::native::TNumericConstant<double>)(lexical_cast<string>(*p_double),*p_double), nullptr, true); 
                else if(p_longdouble) return o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::Constant, phantom::reflection::Constant::metaType, phantom::reflection::native::TNumericConstant<longdouble>)(lexical_cast<string>(*p_longdouble),*p_longdouble), nullptr, true); 
                else if(p_int) return o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::Constant, phantom::reflection::Constant::metaType, phantom::reflection::native::TNumericConstant<int>)(lexical_cast<string>(*p_int),*p_int), nullptr, true); 
                else if(p_uint) return o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::Constant, phantom::reflection::Constant::metaType, phantom::reflection::native::TNumericConstant<uint>)(lexical_cast<string>(*p_uint),*p_uint), nullptr, true); 
                else if(p_short) return o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::Constant, phantom::reflection::Constant::metaType, phantom::reflection::native::TNumericConstant<short>)(lexical_cast<string>(*p_short),*p_short), nullptr, true); 
                else if(p_ushort) return o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::Constant, phantom::reflection::Constant::metaType, phantom::reflection::native::TNumericConstant<ushort>)(lexical_cast<string>(*p_ushort),*p_ushort), nullptr, true); 
                else if(p_longlong) return o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::Constant, phantom::reflection::Constant::metaType, phantom::reflection::native::TNumericConstant<longlong>)(lexical_cast<string>(*p_longlong),*p_longlong), nullptr, true); 
                else if(p_ulonglong) return o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::Constant, phantom::reflection::Constant::metaType, phantom::reflection::native::TNumericConstant<ulonglong>)(lexical_cast<string>(*p_ulonglong),*p_ulonglong), nullptr, true); 
                else if(p_char) return o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::Constant, phantom::reflection::Constant::metaType, phantom::reflection::native::TNumericConstant<char>)(lexical_cast<string>(*p_char),*p_char), nullptr, true); 
                else if(p_bool) return o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::Constant, phantom::reflection::Constant::metaType, phantom::reflection::native::TNumericConstant<bool>)(lexical_cast<string>(*p_bool),*p_bool), nullptr, true);
            }
            else if(p_string)
            {
                return o_new(StringLiteralExpression)(*p_string);
            }
            //return o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::Constant, phantom::reflection::Constant::metaType, phantom::reflection::native::TNumericConstant<longlong>)(lexical_cast<string>(*p_longlong),*p_longlong), nullptr, true);
        }
        else if(p_element)
        {
            if(a_pLHS)
            {
                return precompile_element(a_pLHS, *p_element, a_pScope);
            }
            return precompile_element_recursive(*p_element, a_pScope);
        }
        else if(p_cast_expression)
        {
            return precompile_cast_expression(*p_cast_expression, a_pScope, a_pLHS);
        }
        else if(p_pre_unary_expression)
        {
            return precompile_pre_unary_expression(*p_pre_unary_expression, a_pScope, a_pLHS);
        }
        else if(p_post_unary_expression)
        {
            return precompile_post_unary_expression(*p_post_unary_expression, a_pScope, a_pLHS);
        }
        else if(p_binary_left_expression)
        {
            return precompile_binary_left_expression(*p_binary_left_expression, a_pScope, a_pLHS);
        }
        else if(p_binary_right_expression)
        {
            return precompile_binary_right_expression(*p_binary_right_expression, a_pScope, a_pLHS);
        }
        else if(p_ternary_if_expression)
        {
            return precompile_ternary_if_expression(*p_ternary_if_expression, a_pScope, a_pLHS);
        }
        else if(p_call_expression)
        {
            return precompile_call_expression(*p_call_expression, a_pScope, a_pLHS);
        }
    }
    return nullptr;
}

LanguageElement* precompiler::precompile_cast_expression(cast_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS)
{
    element_garbage garbage;

    LanguageElement* pCasted = precompile_expression(e.m_casted_expression.get(), a_pScope, a_pLHS);
    garbage.add(pCasted);
    if(pCasted == nullptr) return nullptr;
    
    if(e.m_types.size()) 
    {
        Expression* pCastedExpression = pCasted->asExpression();
        if(pCastedExpression == nullptr) return nullptr;

        for(auto it = e.m_types.rbegin(); it != e.m_types.rend(); ++it)
        {
            LanguageElement* pElement = precompile_element_recursive(*it, a_pScope);
            garbage.add(pElement);
            Type* pType = pElement->asType();
            if(pType == nullptr) return nullptr;
            pCasted = pCastedExpression = pCastedExpression->cast(pType);
            garbage.add(pCasted);
            if(pCastedExpression == nullptr) return nullptr;
        }
    }
    
    garbage.clear();
    return pCasted;
}

LanguageElement* precompiler::precompile_ternary_if_expression(ternary_if_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS)
{
    element_garbage garbage;
    LanguageElement* pCondElement = precompile_expression(e.m_condition.get(), a_pScope, a_pLHS);
    garbage.add(pCondElement);
    if(pCondElement == nullptr) return nullptr;
    /*Expression* pCondExpression = pCondElement->asExpression();
    if(pCondExpression == nullptr) return nullptr;*/
    garbage.clear();
    return pCondElement;
    /*
    LanguageElement* pTrueElement = precompile_expression(e.m_true.get(), a_pScope);
    if(pTrueElement == nullptr) return nullptr;
    Expression* pTrueExpression = pTrueElement->asExpression();
    garbage.add(pTrueExpression);
    if(pTrueExpression == nullptr) return nullptr;

    LanguageElement* pFalseElement = precompile_expression(e.m_false.get(), a_pScope);
    if(pFalseElement == nullptr) return nullptr;
    Expression* pFalseExpression = pFalseElement->asExpression();
    garbage.add(pFalseExpression);
    if(pFalseExpression == nullptr) return nullptr;*/
    //
    //garbage.clear(); return o_new(TernaryIfExpression)(pCondExpression, pTrueExpression, pFalseExpression);

}

LanguageElement* precompiler::precompile_call_expression(call_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS)
{
    element_garbage garbage;
    LanguageElement* pElement = precompile_expression(e.m_left.get(), a_pScope, a_pLHS);
    garbage.add(pElement);
    if(pElement == nullptr) return nullptr;

    for(auto it = e.m_extent_or_signatures.begin() ;it != e.m_extent_or_signatures.end(); ++it)
    {
        vector<LanguageElement*> expressions;
        precompile_function_signature(*it, expressions, a_pScope);

        char opening = it->m_opening == token_ids::left_bracket ? '[' : '(';
        char closing = it->m_closing == token_ids::right_bracket ? ']' : ')';
        pElement = pElement->solveOperator(string()+opening+closing, expressions);
        garbage.add(pElement);
        if(pElement == nullptr) return nullptr;
    }

    garbage.clear();
    return pElement;
}

LanguageElement* precompiler::precompile_pre_unary_expression(pre_unary_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS)
{
    element_garbage garbage;
    LanguageElement* pElement = precompile_expression(e.m_expression.get(), a_pScope, a_pLHS);
    garbage.add(pElement);
    if(pElement == nullptr) return nullptr;

    for(auto it = e.m_ops.rbegin(); it != e.m_ops.rend(); ++it)
    {
        pElement = pElement->solveUnaryOperator(token_ids::operator_string_from_token_id(*it)+"$");
        garbage.add(pElement);
        if(pElement == nullptr) return nullptr;
    }
    garbage.clear();
    return pElement;
}

LanguageElement* precompiler::precompile_post_unary_expression(post_unary_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS)
{
    element_garbage garbage;
    LanguageElement* pElement = precompile_expression(e.m_expression.get(), a_pScope, a_pLHS);
    if(pElement == nullptr) return nullptr;

    for(auto it = e.m_ops.begin(); it != e.m_ops.end(); ++it)
    {
        pElement = pElement->solveUnaryOperator("$"+token_ids::operator_string_from_token_id(*it));
        garbage.add(pElement);
        if(pElement == nullptr) return nullptr;
    }
    garbage.clear();
    return pElement;
}

LanguageElement* precompiler::precompile_binary_right_expression(binary_right_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS)
{
    element_garbage garbage;
    LanguageElement* pLeft = precompile_expression(e.m_left.get(), a_pScope, a_pLHS);
    garbage.add(pLeft);
    if(pLeft == nullptr) return nullptr;

    for(auto it = e.m_op_rights.begin(); it != e.m_op_rights.end(); ++it)
    {
        binary_op_right_expression& e = *it;

        Expression* pLeftExpression = pLeft->asExpression();
        if(pLeftExpression == nullptr) return nullptr;

        // Either real operator or member access
        // MEMBER ACCESS / INDIRECTION :
        LanguageElement* pRight = nullptr;
        if(e.m_op == token_ids::dot) // MEMBER ACCESS
        { 
            pLeft = precompile_expression(e.m_right.get(), a_pScope, pLeftExpression);
        }
        else if(e.m_op == token_ids::minus_greater)
        {
            pLeftExpression = pLeftExpression->dereference();
            garbage.add(pLeftExpression);
            if(pLeftExpression == nullptr) 
            {
                pLeft = pLeftExpression->solveUnaryOperator("$->");
                garbage.add(pLeft);
                if(pLeft == nullptr) return nullptr;
                pLeftExpression = pLeft->asExpression();
                if(pLeftExpression == nullptr) return nullptr;
            }
            pLeft = precompile_expression(e.m_right.get(), a_pScope, pLeftExpression);
        }
        else 
        {
            pRight = precompile_expression(e.m_right.get(), a_pScope);
            garbage.add(pRight);
            if(pRight == nullptr) return nullptr;
            Expression* pRightExpression = pRight->asExpression();
            if(pRightExpression == nullptr) return nullptr;
            pLeft = pLeftExpression->solveBinaryOperator("$"+token_ids::operator_string_from_token_id(e.m_op)+"$", pRightExpression);
        }
        garbage.add(pLeft);
        if(pLeft == nullptr) return nullptr;
    }

    garbage.clear();
    return pLeft;
}

LanguageElement* precompiler::precompile_binary_left_expression(binary_left_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS)
{
    element_garbage garbage;
    LanguageElement* pRight = precompile_expression(e.m_right.get(), a_pScope);
    garbage.add(pRight);
    if(pRight == nullptr) return nullptr;

    for(auto it = e.m_op_lefts.rbegin(); it != e.m_op_lefts.rend(); ++it)
    {
        binary_op_left_expression& e = *it;

        Expression* pRightExpression = pRight->asExpression();
        if(pRightExpression == nullptr) return nullptr;

        LanguageElement* pLeft = precompile_expression(e.m_left.get(), a_pScope);
        garbage.add(pLeft);
        if(pLeft == nullptr) return nullptr;

        Expression* pLeftExpression = pLeft->asExpression();
        if(pLeftExpression == nullptr) return nullptr;
        pRight = pLeftExpression->solveBinaryOperator("$"+token_ids::operator_string_from_token_id(e.m_op)+"$", pRightExpression);
        garbage.add(pRight);
        if(pRight == nullptr) return nullptr;
    }

    garbage.clear();
    return pRight;
}

o_namespace_end(phantom, reflection, cpp, ast)