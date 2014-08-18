/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <boost/spirit/include/qi.hpp>
#include "precompiler.h"
#include "phantom/reflection/LocalVariable.h"
#include "phantom/reflection/LocalVariableAccess.h"
#include "phantom/reflection/StaticVariableAccess.h"
#include "phantom/reflection/ConstantExpression.h"
#include "phantom/reflection/StringLiteralExpression.h"
#include "phantom/reflection/ExpressionStatement.h"
#include "phantom/reflection/LabelStatement.h"
#include "phantom/reflection/Block.h"
#include "phantom/reflection/CallExpression.h"
#include "phantom/reflection/AddressExpression.h"
#include "phantom/reflection/ArrayElementAccess.h"
#include "phantom/reflection/BranchIfNotStatement.h"
#include "phantom/reflection/BranchIfStatement.h"
#include "phantom/reflection/ReturnStatement.h"
#include "phantom/util/Message.h"
#include <stdarg.h>
/* *********************************************** */
o_namespace_begin(phantom, reflection, cpp, ast)

class array_initializer_or_expression_visitor
    : public boost::static_visitor<>
{
public:
    array_initializer_or_expression_visitor(array_initializer** a_pp_array_initializer, expression** a_pp_expression)
        : m_pp_array_initializer(a_pp_array_initializer)
        , m_pp_expression(a_pp_expression) {}

    void operator()(array_initializer & arg) const // if we go here, it's a array_initializer
    {
        *m_pp_array_initializer = &arg;
    }

    void operator()(expression& arg) const // if we go here, it's an expression
    {
        *m_pp_expression = &arg;
    }

    array_initializer** m_pp_array_initializer;
    expression**        m_pp_expression;
};
class variable_declaration_or_expression_visitor
    : public boost::static_visitor<>
{
public:
    variable_declaration_or_expression_visitor(variable_declaration** a_pp_variable_declaration, expression** a_pp_expression)
        : m_pp_variable_declaration(a_pp_variable_declaration)
        , m_pp_expression(a_pp_expression) {}

    void operator()(variable_declaration & arg) const // if we go here, it's a variable_declaration
    {
        *m_pp_variable_declaration = &arg;
    }

    void operator()(expression& arg) const // if we go here, it's an expression
    {
        *m_pp_expression = &arg;
    }

    variable_declaration** m_pp_variable_declaration;
    expression**        m_pp_expression;
};

class type_or_class_declaration_visitor
    : public boost::static_visitor<>
{
public:
    type_or_class_declaration_visitor(type** a_pp_type, class_declaration** a_pp_class_declaration)
        : m_pp_type(a_pp_type)
        , m_pp_class_declaration(a_pp_class_declaration) {}

    void operator()(type & arg) const // if we go here, it's a type
    {
        *m_pp_type = &arg;
    }

    void operator()(class_declaration& arg) const // if we go here, it's an class_declaration
    {
        *m_pp_class_declaration = &arg;
    }

    type**           m_pp_type;
    class_declaration**  m_pp_class_declaration;
};

class qualifier_or_extent_visitor
    : public boost::static_visitor<>
{
public:
    qualifier_or_extent_visitor(fundamental_node<char>** a_pp_qualifier, extent** a_pp_extent)
        : m_pp_qualifier(a_pp_qualifier)
        , m_pp_extent(a_pp_extent) {}

    void operator()(fundamental_node<char> & arg) const // if we go here, it's a qualifier
    {
        *m_pp_qualifier = &arg;
    }

    void operator()(extent& arg) const // if we go here, it's an extent
    {
        *m_pp_extent = &arg;
    }

    fundamental_node<char>**           m_pp_qualifier;
    extent**  m_pp_extent;
};

class extent_or_function_signature_visitor
{
public:
    extent_or_function_signature_visitor(extent** a_pp_extent, function_signature** a_pp_function_signature)
        : m_pp_extent(a_pp_extent)
        , m_pp_function_signature(a_pp_function_signature) {}

    void operator()(extent & arg) const // if we go here, it's a qualifier
    {
        *m_pp_extent = &arg;
    }

    void operator()(function_signature& arg) const // if we go here, it's an extent
    {
        *m_pp_function_signature = &arg;
    }

    extent**           m_pp_extent;
    function_signature**  m_pp_function_signature;
};

class statement_or_case_label_visitor
    : public boost::static_visitor<>
{
public:
    statement_or_case_label_visitor(statement** a_pp_statement, case_label** a_pp_case_label)
        : m_pp_statement(a_pp_statement)
        , m_pp_case_label(a_pp_case_label) {}

    void operator()(statement & arg) const // if we go here, it's a qualifier
    {
        *m_pp_statement = &arg;
    }

    void operator()(case_label& arg) const // if we go here, it's an extent
    {
        *m_pp_case_label = &arg;
    }

    statement**   m_pp_statement;
    case_label**  m_pp_case_label;
};

class named_or_unnamed_class_declaration_visitor
    : public boost::static_visitor<>
{
public:
    named_or_unnamed_class_declaration_visitor(named_class_declaration** a_pp_named_class_declaration, unnamed_class_declaration** a_pp_unnamed_class_declaration)
        : m_pp_named_class_declaration(a_pp_named_class_declaration)
        , m_pp_unnamed_class_declaration(a_pp_unnamed_class_declaration) {}

    void operator()(named_class_declaration & arg) const // if we go here, it's a qualifier
    {
        *m_pp_named_class_declaration = &arg;
    }

    void operator()(unnamed_class_declaration& arg) const // if we go here, it's an extent
    {
        *m_pp_unnamed_class_declaration = &arg;
    }

    named_class_declaration**   m_pp_named_class_declaration;
    unnamed_class_declaration**  m_pp_unnamed_class_declaration;
};

class statement_visitor
    : public boost::static_visitor<>
{
public:
    statement_visitor(
        expression** a_pp_expression
        , block** a_pp_block
        , if_statement**                  a_pp_if_statement 
        , for_statement**                 a_pp_for_statement
        , while_statement**               a_pp_while_statement 
        , do_while_statement**            a_pp_do_while_statement
        , switch_statement**              a_pp_switch_statement
        , goto_statement**                a_pp_goto_statement 
        , label_statement**               a_pp_label_statement
        , variable_declaration**          a_pp_variable_declaration
        , return_statement**          a_pp_return_statement
        , fundamental_node<int>** a_pp_keyword_statement) 
        : m_pp_expression(a_pp_expression)
        , m_pp_block(a_pp_block) 
        , m_pp_if_statement  (a_pp_if_statement) 
        , m_pp_for_statement (a_pp_for_statement)
        , m_pp_while_statement  (a_pp_while_statement) 
        , m_pp_do_while_statement (a_pp_do_while_statement)
        , m_pp_switch_statement (a_pp_switch_statement)
        , m_pp_goto_statement  (a_pp_goto_statement) 
        , m_pp_label_statement (a_pp_label_statement)
        , m_pp_variable_declaration (a_pp_variable_declaration)
        , m_pp_return_statement(a_pp_return_statement)
        , m_pp_keyword_statement(a_pp_keyword_statement)
    {}


    void operator()(expression& arg) const
    {
        *m_pp_expression = &arg;
    }

    void operator()(block& arg) const
    {
        *m_pp_block = &arg;
    }

    void operator()(if_statement& arg) const
    {
        *m_pp_if_statement = &arg;
    }

    void operator()(for_statement& arg) const
    {
        *m_pp_for_statement = &arg;
    }

    void operator()(while_statement& arg) const
    {
        *m_pp_while_statement = &arg;
    }

    void operator()(do_while_statement& arg) const
    {
        *m_pp_do_while_statement = &arg;
    }

    void operator()(switch_statement& arg) const
    {
        *m_pp_switch_statement = &arg;
    }

    void operator()(goto_statement& arg) const
    {
        *m_pp_goto_statement = &arg;
    }

    void operator()(label_statement& arg) const
    {
        *m_pp_label_statement = &arg;
    }

    void operator()(variable_declaration& arg) const
    {
        *m_pp_variable_declaration = &arg;
    }

    void operator()(fundamental_node<int>& arg) const
    {
        *m_pp_keyword_statement = &arg;
    }

    void operator()(return_statement& arg) const
    {
        *m_pp_return_statement = &arg;
    }


protected:
    expression**                    m_pp_expression;
    block**                         m_pp_block;
    if_statement**                  m_pp_if_statement ;
    for_statement**                 m_pp_for_statement;
    while_statement**               m_pp_while_statement ;
    do_while_statement**            m_pp_do_while_statement;
    switch_statement**              m_pp_switch_statement;
    goto_statement**                m_pp_goto_statement ;
    label_statement**               m_pp_label_statement;
    return_statement**              m_pp_return_statement;
    variable_declaration**          m_pp_variable_declaration;
    fundamental_node<int>**         m_pp_keyword_statement;
};

class template_element_visitor
    : public boost::static_visitor<>
{
public:
    template_element_visitor(
        type** a_pp_type
        , integral_literal** a_pp_integral_literal) : m_pp_type(a_pp_type), m_pp_integral_literal(a_pp_integral_literal) {}


    void operator()(type& arg) const
    {
        *m_pp_type = &arg;
    }

    void operator()(integral_literal& arg) const
    {
        *m_pp_integral_literal = &arg;
    }

protected:
    type** m_pp_type;
    integral_literal** m_pp_integral_literal;
};

class literal_visitor
    : public boost::static_visitor<>
{
public:
    literal_visitor(
        fundamental_literal** a_pp_fundamental_literal
        , string_node** a_pp_string) : m_pp_fundamental_literal(a_pp_fundamental_literal), m_pp_string(a_pp_string) {}


    void operator()(fundamental_literal& arg) const
    {
        *m_pp_fundamental_literal = &arg;
    }

    void operator()(string_node& arg) const
    {
        *m_pp_string = &arg;
    }

protected:
    fundamental_literal** m_pp_fundamental_literal;
    string_node** m_pp_string;
};


class fundamental_literal_visitor
    : public boost::static_visitor<>
{
public:
    fundamental_literal_visitor(fundamental_node<hex_t>** a_pp_hex_t
        , fundamental_node<float>** a_pp_float
        , fundamental_node<double>** a_pp_double
        , fundamental_node<longdouble>** a_pp_longdouble
        , fundamental_node<int>** a_pp_int
        , fundamental_node<uint>** a_pp_uint
        , fundamental_node<longlong>** a_pp_longlong
        , fundamental_node<ulonglong>** a_pp_ulonglong
        , fundamental_node<char>** a_pp_char
        , fundamental_node<bool>** a_pp_bool
        , fundamental_node<std::nullptr_t>** a_pp_nullptr
        ) : m_pp_hex_t(a_pp_hex_t), m_pp_float (a_pp_float), m_pp_double (a_pp_double), m_pp_longdouble (a_pp_longdouble), m_pp_int (a_pp_int), m_pp_uint (a_pp_uint), m_pp_longlong (a_pp_longlong), m_pp_ulonglong (a_pp_ulonglong), m_pp_char (a_pp_char), m_pp_bool (a_pp_bool), m_pp_nullptr(a_pp_nullptr)
    {

    }

    void operator()(fundamental_node<hex_t>& arg) const
    {
        *m_pp_hex_t = &arg;
    }

    void operator()(fundamental_node<float>& arg) const
    {
        *m_pp_float = &arg;
    }

    void operator()(fundamental_node<double>& arg) const
    {
        *m_pp_double = &arg;
    }

    void operator()(fundamental_node<longdouble>& arg) const
    {
        *m_pp_longdouble = &arg;
    }

    void operator()(fundamental_node<int>& arg) const
    {
        *m_pp_int = &arg;
    }

    void operator()(fundamental_node<uint>& arg) const
    {
        *m_pp_uint = &arg;
    }

    void operator()(fundamental_node<longlong>& arg) const
    {
        *m_pp_longlong = &arg;
    }

    void operator()(fundamental_node<ulonglong>& arg) const
    {
        *m_pp_ulonglong = &arg;
    }

    void operator()(fundamental_node<char>& arg) const
    {
        *m_pp_char = &arg;
    }

    void operator()(fundamental_node<bool>& arg) const
    {
        *m_pp_bool = &arg;
    }

    void operator()(fundamental_node<std::nullptr_t>& arg) const
    {
        *m_pp_nullptr = &arg;
    }

protected:
    fundamental_node<hex_t>** m_pp_hex_t;
    fundamental_node<float>** m_pp_float; 
    fundamental_node<double>** m_pp_double; 
    fundamental_node<longdouble>** m_pp_longdouble; 
    fundamental_node<int>** m_pp_int; 
    fundamental_node<uint>** m_pp_uint; 
    fundamental_node<longlong>** m_pp_longlong; 
    fundamental_node<ulonglong>** m_pp_ulonglong; 
    fundamental_node<char>** m_pp_char; 
    fundamental_node<bool>** m_pp_bool;
    fundamental_node<std::nullptr_t>** m_pp_nullptr;
};


class integral_literal_visitor
    : public boost::static_visitor<>
{
public:
    integral_literal_visitor(fundamental_node<hex_t>** a_pp_hex_t
        , fundamental_node<int>** a_pp_int
        , fundamental_node<uint>** a_pp_uint
        , fundamental_node<longlong>** a_pp_longlong
        , fundamental_node<ulonglong>** a_pp_ulonglong
        , fundamental_node<char>** a_pp_char
        , fundamental_node<bool>** a_pp_bool
        ) : m_pp_hex_t(a_pp_hex_t), m_pp_int (a_pp_int), m_pp_uint (a_pp_uint), m_pp_longlong (a_pp_longlong), m_pp_ulonglong (a_pp_ulonglong), m_pp_char (a_pp_char), m_pp_bool (a_pp_bool)
    {

    }
    void operator()(fundamental_node<hex_t>& arg) const
    {
        *m_pp_hex_t = &arg;
    }

    void operator()(fundamental_node<int>& arg) const
    {
        *m_pp_int = &arg;
    }

    void operator()(fundamental_node<uint>& arg) const
    {
        *m_pp_uint = &arg;
    }

    void operator()(fundamental_node<longlong>& arg) const
    {
        *m_pp_longlong = &arg;
    }

    void operator()(fundamental_node<ulonglong>& arg) const
    {
        *m_pp_ulonglong = &arg;
    }

    void operator()(fundamental_node<char>& arg) const
    {
        *m_pp_char = &arg;
    }

    void operator()(fundamental_node<bool>& arg) const
    {
        *m_pp_bool = &arg;
    }

protected:
    fundamental_node<hex_t>** m_pp_hex_t;
    fundamental_node<int>** m_pp_int; 
    fundamental_node<uint>** m_pp_uint; 
    fundamental_node<longlong>** m_pp_longlong; 
    fundamental_node<ulonglong>** m_pp_ulonglong; 
    fundamental_node<char>** m_pp_char; 
    fundamental_node<bool>** m_pp_bool;
};


class expression_visitor
    : public boost::static_visitor<>
{
public:
    expression_visitor(
        cast_expression** a_pp_cast_expression
        , pre_unary_expression** a_pp_pre_unary_expression
        , post_unary_expression** a_pp_post_unary_expression
        //, binary_left_expression** a_pp_binary_left_expression
        , binary_right_expression** a_pp_binary_right_expression
        , ternary_if_expression** a_pp_ternary_if_expression
        , call_expression** a_pp_call_expression
        , bracket_expression** a_pp_bracket_expression
        , qualified_name** a_pp_qualified_name
        , literal** a_pp_literal)
        : m_pp_cast_expression(a_pp_cast_expression)
        , m_pp_pre_unary_expression(a_pp_pre_unary_expression)
        , m_pp_post_unary_expression(a_pp_post_unary_expression)
        , m_pp_binary_right_expression(a_pp_binary_right_expression)
        //, m_pp_binary_left_expression(a_pp_binary_left_expression)
        , m_pp_ternary_if_expression(a_pp_ternary_if_expression)
        , m_pp_call_expression(a_pp_call_expression)
        , m_pp_bracket_expression(a_pp_bracket_expression)
        , m_pp_qualified_name(a_pp_qualified_name)
        , m_pp_literal(a_pp_literal) {}

    void operator()(cast_expression& arg) const
    {
        *m_pp_cast_expression = &arg;
    }

    void operator()(pre_unary_expression& arg) const
    {
        *m_pp_pre_unary_expression = &arg;
    }

    void operator()(post_unary_expression& arg) const
    {
        *m_pp_post_unary_expression = &arg;
    }

    //     void operator()(binary_left_expression& arg) const
    //     {
    //         *m_pp_binary_left_expression = &arg;
    //     }

    void operator()(binary_right_expression& arg) const
    {
        *m_pp_binary_right_expression = &arg;
    }

    void operator()(ternary_if_expression& arg) const
    {
        *m_pp_ternary_if_expression = &arg;
    }

    void operator()(call_expression& arg) const
    {
        *m_pp_call_expression = &arg;
    }

    void operator()(bracket_expression& arg) const
    {
        *m_pp_bracket_expression = &arg;
    }

    void operator()(qualified_name& arg) const
    {
        *m_pp_qualified_name = &arg;
    }

    void operator()(literal& arg) const
    {
        *m_pp_literal = &arg;
    }

protected:
    cast_expression**       m_pp_cast_expression;
    pre_unary_expression**  m_pp_pre_unary_expression;
    post_unary_expression** m_pp_post_unary_expression;
    binary_right_expression**     m_pp_binary_right_expression;
    //binary_left_expression**     m_pp_binary_left_expression;
    ternary_if_expression** m_pp_ternary_if_expression;
    call_expression**       m_pp_call_expression;
    bracket_expression**    m_pp_bracket_expression;
    qualified_name**        m_pp_qualified_name;
    literal**              m_pp_literal;
};


class namespace_member_declaration_visitor
    : public boost::static_visitor<>
{
public:
    namespace_member_declaration_visitor(ambiguous_global_declaration** a_pp_ambiguous_global_declaration
                                        , namespace_declaration** a_pp_namespace_declaration
                                        , class_declaration** a_pp_class_declaration
                                        , typedef_declaration** a_pp_typedef_declaration)
            : m_pp_ambiguous_global_declaration(a_pp_ambiguous_global_declaration)
            , m_pp_namespace_declaration(a_pp_namespace_declaration)
            , m_pp_class_declaration(a_pp_class_declaration)
            , m_pp_typedef_declaration(a_pp_typedef_declaration) {}

    void operator()(ambiguous_global_declaration & arg) const
    {
        *m_pp_ambiguous_global_declaration = &arg;
    }

    void operator()(namespace_declaration& arg) const
    {
        *m_pp_namespace_declaration = &arg;
    }

    void operator()(class_declaration& arg) const 
    {
        *m_pp_class_declaration = &arg;
    }

    void operator()(typedef_declaration& arg) const 
    {
        *m_pp_typedef_declaration = &arg;
    }

protected:
    ambiguous_global_declaration**  m_pp_ambiguous_global_declaration;
    namespace_declaration** m_pp_namespace_declaration;
    class_declaration**     m_pp_class_declaration;
    typedef_declaration**   m_pp_typedef_declaration;
};

class class_member_declaration_visitor
    : public boost::static_visitor<>
{
public:
    class_member_declaration_visitor(member_declaration** a_pp_member_declaration
                                        , class_declaration** a_pp_class_declaration
                                        , typedef_declaration** a_pp_typedef_declaration
                                        , fundamental_node<int>** a_pp_access_qualifier)
            : m_pp_member_declaration(a_pp_member_declaration)
            , m_pp_class_declaration(a_pp_class_declaration)
            , m_pp_typedef_declaration(a_pp_typedef_declaration) 
            , m_pp_access_qualifier(a_pp_access_qualifier) {}
    
    void operator()(member_declaration& arg) const
    {
        *m_pp_member_declaration = &arg;
    }

    void operator()(class_declaration& arg) const 
    {
        *m_pp_class_declaration = &arg;
    }

    void operator()(typedef_declaration& arg) const 
    {
        *m_pp_typedef_declaration = &arg;
    }

    void operator()(fundamental_node<int>& arg) const 
    {
        *m_pp_access_qualifier = &arg;
    }

protected:
    member_declaration**    m_pp_member_declaration;
    class_declaration**     m_pp_class_declaration;
    typedef_declaration**   m_pp_typedef_declaration;
    fundamental_node<int>** m_pp_access_qualifier;
};

class member_declaration_visitor
    : public boost::static_visitor<>
{
public:
    member_declaration_visitor(ambiguous_member_declaration** a_pp_ambiguous_member_declaration
                                        , virtual_member_function_declaration** a_pp_virtual_member_function_declaration
                                        , static_ambiguous_member_declaration** a_pp_static_ambiguous_member_declaration)
            : m_pp_ambiguous_member_declaration(a_pp_ambiguous_member_declaration)
            , m_pp_virtual_member_function_declaration(a_pp_virtual_member_function_declaration)
            , m_pp_static_ambiguous_member_declaration(a_pp_static_ambiguous_member_declaration) {}
    
    void operator()(ambiguous_member_declaration& arg) const
    {
        *m_pp_ambiguous_member_declaration = &arg;
    }

    void operator()(virtual_member_function_declaration& arg) const 
    {
        *m_pp_virtual_member_function_declaration = &arg;
    }

    void operator()(static_ambiguous_member_declaration& arg) const 
    {
        *m_pp_static_ambiguous_member_declaration = &arg;
    }

protected:
    ambiguous_member_declaration**          m_pp_ambiguous_member_declaration;
    virtual_member_function_declaration**   m_pp_virtual_member_function_declaration;
    static_ambiguous_member_declaration**   m_pp_static_ambiguous_member_declaration;
};

class namespace_declaration_visitor
    : public boost::static_visitor<>
{
public:
    namespace_declaration_visitor(namespace_scope** a_pp_namespace_scope
                                        , namespace_alias** a_pp_namespace_alias)
            : m_pp_namespace_scope(a_pp_namespace_scope)
            , m_pp_namespace_alias(a_pp_namespace_alias){}

    void operator()(namespace_scope& arg) const 
    {
        *m_pp_namespace_scope = &arg;
    }

    void operator()(namespace_alias& arg) const 
    {
        *m_pp_namespace_alias = &arg;
    }

protected:
    namespace_scope**  m_pp_namespace_scope;
    namespace_alias** m_pp_namespace_alias;
};

void precompiler::element_garbage::add( LanguageElement* a_pElement )
{
    if(a_pElement AND (std::find(m_elements.begin(), m_elements.end(), a_pElement) == m_elements.end()))
    {
        m_elements.push_back(a_pElement);
    }
}

void precompiler::element_garbage::remove( LanguageElement* a_pElement )
{
    if(a_pElement)
    {
        m_elements.erase(std::find(m_elements.begin(), m_elements.end(), a_pElement));
    }
}

precompiler::element_garbage::~element_garbage()
{
    for(auto it = m_elements.begin(); it != m_elements.end(); ++it)
    {
        if((*it)->getOwner() == nullptr && NOT((*it)->isNative())) // if not in a module or not in another element we can delete it
        {
            phantom::deleteElement(*it);
        }
    }
}

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

Type*  precompiler::precompile_type(const string& a_strName, const vector<TemplateElement*>* a_pTemplateSignature, reflection::LanguageElement* a_pScope)
{
    LanguageElement* pSolvedElement = a_pScope->solveElement(
        a_strName
        , a_pTemplateSignature
        , nullptr
        , 0
        );
    return pSolvedElement ? pSolvedElement->asType() : nullptr;
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

LanguageElement* precompiler::precompile_template_element(template_element& e, LanguageElement* a_pScope)
{
    type* p_type = 0;
    integral_literal* p_integral_literal = 0;
    template_element_visitor tev(&p_type, &p_integral_literal);
    e.apply_visitor(tev);
    if(p_type)
    {
        return precompile_template_element_recursive(*p_type, a_pScope);
    }
    else if(p_integral_literal)
    {
        return precompile_integral_literal(*p_integral_literal);
    }
    return nullptr;
}

bool precompiler::precompile_function_signature(function_signature& fs, vector<LanguageElement*>& out, LanguageElement* a_pScope)
{
    element_garbage garbage;
    auto it = fs.begin();
    auto end = fs.end();
    for(;it!=end;++it)
    {
        Type* pType = precompile_type_recursive(*it, a_pScope);
        garbage.add(pType);
        if(pType == nullptr)
        {
            //error(node_location(*it), "Cannot solve parameter '%s'", node_string(*it).c_str());
            return false;
        }
        out.push_back(pType);
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
        type* p_type = 0;
        integral_literal* p_integral_literal = 0;
        template_element_visitor tev(&p_type, &p_integral_literal);
        it->apply_visitor(tev);
        TemplateElement* pTemplateElement  = nullptr;
        if(p_type)
        {
            LanguageElement* pElement = precompile_type_recursive(*p_type, a_pScope);
            if(pElement == nullptr) 
                return false;
            pElement = pElement->hatch();
            garbage.add(pElement);
            pTemplateElement = pElement->asTemplateElement();
        }
        else if(p_integral_literal)
        {
            ConstantExpression* pConstantExpression = precompile_integral_literal(*p_integral_literal);
            if(pConstantExpression == nullptr) 
                return false;
            NumericConstant* pNumericConstant = pConstantExpression->hatch()->asNumericConstant();
            garbage.add(pNumericConstant);
            pTemplateElement = pNumericConstant;
        }
        if(pTemplateElement == nullptr) 
            return false;
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
        {
            //error(node_location(n.m_template_signature), "Cannot solve expression '%s'", node_string(n.m_template_signature).c_str());
            return nullptr;
        }
        pElement = precompile_element(n.m_identifier, &templateSignature, a_pFunctionSignature, a_bConst, a_pLHS ? a_pLHS : a_pScope);
        garbage.add(pElement);
    }
    else
    {
        if(n.m_identifier.m_value.empty())
        {
            return a_pLHS ? nullptr : phantom::rootNamespace();
        }
        pElement = precompile_element(n.m_identifier, nullptr, a_pFunctionSignature, a_bConst, a_pLHS ? a_pLHS : a_pScope);
        garbage.add(pElement);
    }
    if(pElement == nullptr)
    {
        //error(node_location(n), "Cannot solve expression '%s'", node_string(n).c_str());
        return nullptr;
    }
    garbage.clear();
    return pElement;
}

LanguageElement* precompiler::precompile_element(LanguageElement* a_pLHS, element & e, LanguageElement* a_pScope)
{
    type& t = e.m_type;
    // name
    LanguageElement* pLHS = a_pLHS;
    bool bLookingForType = t.m_const_modifier.is_initialized() OR NOT(t.m_type_extension.empty());
    
    if(e.m_function_prototype.is_initialized())
    {
        function_signature& fs = (*(e.m_function_prototype)).m_signature;
        vector<LanguageElement*> argumentList;
        for(auto it = fs.begin(); it != fs.end(); ++it)
        {
            Type* pType = precompile_type_recursive(*it, a_pScope);
            if(pType == nullptr)
                return nullptr;
            argumentList.push_back(pType);
        }
        a_pLHS = precompile_qualified_name(a_pLHS, t.m_qualified_name, &argumentList, (*(e.m_function_prototype)).m_const_modifier.is_initialized(), a_pScope);
    }
    else
    {
        a_pLHS = precompile_qualified_name(a_pLHS, t.m_qualified_name, nullptr, false, a_pScope);
    }

    if(a_pLHS == nullptr)
    {
//        if(bLookingForType)
//            try_error(node_location(e), "Cannot solve type '%s'", node_string(t).c_str());
//        else 
//            try_error(node_location(e), "Cannot solve expression '%s'", node_string(t).c_str());
        return nullptr;
    }

    if(bLookingForType)
    {
        Type* pType = a_pLHS->asType();
        if(pType == nullptr)
        {
//            try_error(node_location(t), "'%s' is not a type", node_string(t).c_str());
            return nullptr;
        }

        string qualifiers;
        if(t.m_const_modifier.is_initialized())
        {
            pType = pType->constType();
            o_assert(pType);
        }

        for(auto it = t.m_type_extension.begin(); it != t.m_type_extension.end(); ++it)
        {
            fundamental_node<char>* p_qualifier = 0;
            extent* p_extent = 0;
            qualifier_or_extent_visitor qoev(&p_qualifier, &p_extent);
            it->apply_visitor(qoev);
            if(p_qualifier)
            {
                pType = precompile_type_qualifier(pType, *p_qualifier);
                if(pType == nullptr)
                {
//                    try_error(node_location(*it), "Invalid extra qualifier '%c'", *p_qualifier); 
                    return nullptr;
                }
            }
            else if(p_extent)
            {
                LanguageElement* pLanguageElement = precompile_template_element(*p_extent, a_pScope);
                if(pLanguageElement == nullptr) 
                {
//                    try_error(node_location(*p_extent), "Invalid extent '%s'", node_string(*p_extent).c_str()); 
                    return nullptr;
                }
                ConstantExpression* pConstantExpression = as<ConstantExpression*>(pLanguageElement);
                if(pConstantExpression == nullptr) 
                {
//                    try_error(node_location(*p_extent), "Expression '%s' must be a constant", node_string(*p_extent).c_str()); 
                    return nullptr;
                }
                Expression* pCastedExpression = pConstantExpression->implicitCast(typeOf<size_t>());
                if(pCastedExpression == nullptr) 
                {
//                    try_error(node_location(*p_extent), "Expression '%s' must be an integral constant", node_string(*p_extent).c_str()); 
                    return nullptr;
                }

                size_t value = 0;
                pCastedExpression->getValue(&value);
                if(value == 0)
                {
                    //  try_error(node_location(*p_extent), "Array cannot have '0' size", node_string(*p_extent).c_str()); 
                    phantom::deleteElement(pCastedExpression);
                    return nullptr;
                }
                pType = pType->arrayType(value);
                phantom::deleteElement(pCastedExpression);
            }
        }
        return pType;
    }
    return a_pLHS;
}

LanguageElement* precompiler::precompile_template_element(LanguageElement* a_pLHS, type & t, LanguageElement* a_pScope)
{
    element e;
    e.m_type = t;
    return precompile_element(a_pLHS, e, a_pScope);
}

Type* precompiler::precompile_type(LanguageElement* a_pLHS, type & e, LanguageElement* a_pScope)
{
    LanguageElement* pLanguageElement = precompile_template_element(a_pLHS, e, a_pScope);
    return pLanguageElement ? pLanguageElement->asType() : nullptr;
}

Type* precompiler::precompile_type_recursive(type & e, LanguageElement* a_pScope)
{
    LanguageElement* pScope = a_pScope;
    Type* pResult = nullptr;
    while(pResult == nullptr && pScope)
    {
        pResult = precompile_type(pScope, e, a_pScope);
        pScope = pScope->getOwner();
    }
    return pResult;
}

LanguageElement* precompiler::precompile_template_element_recursive(type & e, LanguageElement* a_pScope)
{
    LanguageElement* pScope = a_pScope;
    LanguageElement* pResult = nullptr;
    while(pResult == nullptr && pScope)
    {
        pResult = precompile_template_element(pScope, e, a_pScope);
        pScope = pScope->getOwner();
    }
    return pResult;
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

void precompiler::precompile_block(block& r, Block* a_pBlock)
{
    Block* pBlock = o_new(Block);
    a_pBlock->addStatement(pBlock);
    for(auto it = r.m_statements.begin(); it != r.m_statements.end(); ++it)
    {
        precompile_statement(*it, pBlock);
    }
}

Expression* precompiler::precompile_variable_declaration_or_expression(variable_declaration_or_expression& vde, Block* a_pBlock)
{
    variable_declaration* p_variable_declaration = 0;
    expression* p_expression = 0;
    variable_declaration_or_expression_visitor vdev(&p_variable_declaration, &p_expression);
    vde.apply_visitor(vdev);
    if(p_variable_declaration)
    {
        vector<LocalVariable*> localVariables;
        precompile_variable_declaration(*p_variable_declaration, a_pBlock, &localVariables);
        if(localVariables.size() == 1)
        {
            return o_new(LocalVariableAccess)(localVariables[0]);
        }
        else return nullptr;
    }
    else 
    {
        return precompile_expression(*p_expression, a_pBlock);
    }
}

void precompiler::precompile_if_statement(if_statement& is, Block* a_pBlock) 
{
    Block* pIfStatement = o_new(Block)("if");
    a_pBlock->addStatement(pIfStatement);
    Expression* pCondition = precompile_variable_declaration_or_expression(is.m_condition, pIfStatement);
    if(pCondition == nullptr)
    {
        pIfStatement->setInvalid();
        error(node_location(is.m_condition), "Invalid if condition");
    }
    LabelStatement* pElseLabel = o_new(LabelStatement)("else");
    LabelStatement* pEndLabel = nullptr;
    BranchIfNotStatement* pBranchIfNot = o_new(BranchIfNotStatement)(pCondition);
    pBranchIfNot->setLabelStatement(pElseLabel);
    pIfStatement->addStatement(pBranchIfNot);

    precompile_statement(is.m_then, pIfStatement);
    if(is.m_else.is_initialized())
    {
        // at the end of 'then' part, if 'else' exists, jump to end
        BranchStatement* pBranchToEnd = o_new(BranchStatement);
        pEndLabel = o_new(LabelStatement)("if");
        pBranchToEnd->setLabelStatement(pEndLabel);
        pIfStatement->addStatement(pBranchToEnd);
    }
    pIfStatement->addStatement(pElseLabel);
    if(pEndLabel)
    {
        precompile_statement(*is.m_else, pIfStatement);
        pIfStatement->addStatement(pEndLabel);
    }
}

void precompiler::precompile_for_statement(for_statement& fs, Block* a_pBlock) 
{ 
    Block* pForStatement = o_new(Block)("for");
    a_pBlock->addStatement(pForStatement);
    LabelStatement*     pBreakLabelStatement = o_new(LabelStatement)("break");
    LabelStatement*     pContinueLabelStatement = o_new(LabelStatement)("continue");
    LabelStatement*     pCodeStartLabelStatement = o_new(LabelStatement)("for");

    // Init
    if(fs.m_init.is_initialized())
    {
        Expression* pInit = precompile_variable_declaration_or_expression(*fs.m_init, pForStatement);
        if(pInit == nullptr)
        {
            error(node_location(fs.m_init), "Invalid for init");
        }
        else 
        {
            pForStatement->addStatement(o_new(ExpressionStatement)(pInit));
        }
    }

    // Condition
    Expression* pCondition = nullptr;
    Expression* pConditionClone = nullptr;
    if(fs.m_condition.is_initialized())
    {
        pCondition = precompile_expression(*fs.m_condition, pForStatement);
        pConditionClone = precompile_expression(*fs.m_condition, pForStatement);
        if(pCondition == nullptr)
        {
            error(node_location(fs.m_condition), "Invalid for condition");
        }
    }

    BranchIfNotStatement* pBranchIfNotStatement = pCondition ? o_new(BranchIfNotStatement)(pCondition) : nullptr;
    if(pBranchIfNotStatement)
    {
        pBranchIfNotStatement->setLabelStatement(pBreakLabelStatement);
    }

    BranchStatement* pBranchIfStatement = pConditionClone 
        ? o_new(BranchIfStatement)(pConditionClone) 
        : o_new(BranchStatement);

    pBranchIfStatement->setLabelStatement(pCodeStartLabelStatement);

    // If test exists, branch to break if test fails
    if(pBranchIfNotStatement)
    {
        pForStatement->addStatement(pBranchIfNotStatement);
    }

    // Code start label
    pForStatement->addStatement(pCodeStartLabelStatement);

    // Code
    if(fs.m_statement.is_initialized())
    {
        precompile_statement(*fs.m_statement, pForStatement);
    }

    // Updates

    // 'continue' goes here
    pForStatement->addStatement(pContinueLabelStatement);

    // updates
    for(auto it = fs.m_update.begin(); it != fs.m_update.end(); ++it)
    {
        pForStatement->addStatement(o_new(ExpressionStatement)(precompile_expression(*it, pForStatement)));
    }

    // branch to code if test exists and succeed, or direct branch if test doesn't exist
    pForStatement->addStatement(pBranchIfStatement);

    // 'break' goes here
    pForStatement->addStatement(pBreakLabelStatement);
}

void precompiler::precompile_while_statement(while_statement& ws, Block* a_pBlock) 
{ 
    Block* pWhileStatement = o_new(Block)("while");
    a_pBlock->addStatement(pWhileStatement);
    Expression* pCondition = precompile_variable_declaration_or_expression(ws.m_condition, pWhileStatement);

    if(pCondition)
    {
        if(NOT(pCondition->getValueType()->isConvertibleTo(typeOf<bool>())))
        {
            pWhileStatement->setInvalid();
            error(node_location(ws.m_condition), "Cannot convert from '%s' to 'bool' in while condition", pCondition->getValueType()->getQualifiedDecoratedName().c_str());
        }
    }
    else 
    {
        pWhileStatement->setInvalid();
        error(node_location(ws.m_condition), "Invalid while condition");
    }

    Expression* pConditionClone = precompile_variable_declaration_or_expression(ws.m_condition, pWhileStatement);

    LabelStatement*     pBreakLabelStatement = o_new(LabelStatement)("break");
    LabelStatement*     pContinueLabelStatement = o_new(LabelStatement)("continue");
    LabelStatement*     pCodeStartLabelStatement = o_new(LabelStatement)("while");

    BranchIfNotStatement* pBranchIfNotStatement = o_new(BranchIfNotStatement)(pCondition);
    pBranchIfNotStatement->setLabelStatement(pBreakLabelStatement);

    BranchIfStatement* pBranchIfStatement = o_new(BranchIfStatement)(pConditionClone);
    pBranchIfStatement->setLabelStatement(pCodeStartLabelStatement);
    
    // Branch to break if test fails
    pWhileStatement->addStatement(pBranchIfNotStatement);

    // Code start label
    pWhileStatement->addStatement(pCodeStartLabelStatement);

    // Code
    if(ws.m_statement.is_initialized())
    {
        precompile_statement(*ws.m_statement, pWhileStatement);
    }

    // 'continue' goes here
    pWhileStatement->addStatement(pContinueLabelStatement);

    // branch to code if test succeed
    pWhileStatement->addStatement(pBranchIfStatement);

    // 'break' goes here
    pWhileStatement->addStatement(pBreakLabelStatement);
}

void precompiler::precompile_do_while_statement(do_while_statement& dws, Block* a_pBlock) 
{
    Block* pDoWhileStatement = o_new(Block)("do");
    a_pBlock->addStatement(pDoWhileStatement);

    Expression* pCondition = precompile_expression(dws.m_condition, pDoWhileStatement);

    if(pCondition)
    {
        if(NOT(pCondition->getValueType()->isConvertibleTo(typeOf<bool>())))
        {
            pDoWhileStatement->setInvalid();
            error(node_location(dws.m_condition), "Cannot convert from '%s' to 'bool' in do while condition", pCondition->getValueType()->getQualifiedDecoratedName().c_str());
        }
    }
    else 
    {
        pDoWhileStatement->setInvalid();
        error(node_location(dws.m_condition), "Invalid do while condition");
    }

    LabelStatement*     pCodeStartLabelStatement = o_new(LabelStatement)("do");

    pDoWhileStatement->addStatement(pCodeStartLabelStatement);

    // do
    if(dws.m_statement.is_initialized())
    {
        precompile_statement(*dws.m_statement, pDoWhileStatement);
    }

    LabelStatement*     pBreakLabelStatement = o_new(LabelStatement)("break");
    LabelStatement*     pContinueLabelStatement = o_new(LabelStatement)("continue");

    // 'continue' goes here
    pDoWhileStatement->addStatement(pContinueLabelStatement);

    // test condition and jump to do block if succeeds
    BranchIfStatement* pBranchIfStatement = o_new(BranchIfStatement)(pCondition);
    pBranchIfStatement->setLabelStatement(pCodeStartLabelStatement);

    // 'break' goes here
    pDoWhileStatement->addStatement(pBreakLabelStatement);
}

void precompiler::precompile_switch_statement(switch_statement& s, Block* a_pBlock) 
{
    element_garbage garbage;

    Block* pSwitchStatement = o_new(Block)("switch");
    a_pBlock->addStatement(pSwitchStatement);

    Expression* pTestValue = precompile_variable_declaration_or_expression(s.m_test_value, pSwitchStatement);
    if(pTestValue == nullptr)
    {
        pSwitchStatement->setInvalid();
        error(node_location(s.m_test_value), "Invalid switch test expression");
    }
    else 
    {
        if(pTestValue->getValueType()->removeReference()->removeConst()->asIntegralType() == nullptr)
        {
            pSwitchStatement->setInvalid();
            error(node_location(s.m_test_value), "Switch expression of type '%s' is illegal", pTestValue->getValueType()->getQualifiedDecoratedName().c_str());
        }
    }

    Block* pInnerBlock = o_new(Block);
    pSwitchStatement->addStatement(pInnerBlock);

    vector<Statement*> branchIfs;
    BranchStatement* pDefaultBranch = nullptr;

    for(auto it = s.m_statement_or_case_labels.begin(); it != s.m_statement_or_case_labels.end(); ++it)
    {
        statement* p_statement = 0;
        case_label* p_case_label = 0;

        statement_or_case_label_visitor soclv(&p_statement, &p_case_label);
        it->apply_visitor(soclv);

        if(p_statement) 
        {
            precompile_statement(*p_statement, pInnerBlock);
        }
        else if(p_case_label) 
        {
            LabelStatement* pCaseLabel = o_new(LabelStatement)(p_case_label->m_value.is_initialized() ? "case" : "default");
            if(p_case_label->m_value.is_initialized())
            {
                LanguageElement* pValueElement = precompile_template_element(*(p_case_label->m_value), pInnerBlock);
                if(pValueElement == nullptr)
                {
                    error(node_location(p_case_label->m_value), "Invalid 'case' value expression", pTestValue->getValueType()->getQualifiedDecoratedName().c_str());
                }
                Expression* pValue = pValueElement->asExpression();
                if(pValue == nullptr)
                {
                    error(node_location(p_case_label->m_value), "'case' values must be constant integral expressions", pTestValue->getValueType()->getQualifiedDecoratedName().c_str());
                }
                Expression* pTest = pTestValue->solveBinaryOperator("==", pValue, 0);
                if(pTest == nullptr)
                {
                    error(node_location(p_case_label->m_value), "Illegal case value");
                }
                BranchIfStatement* pBranch = o_new(BranchIfStatement)(pTest);
                pBranch->setLabelStatement(pCaseLabel);
                branchIfs.push_back(pBranch);
            }
            else 
            {
                if(pDefaultBranch)
                {
                    error(node_location(*p_case_label), "'default' label already defined");
                }
                else pDefaultBranch = o_new(BranchStatement);
                pDefaultBranch->setLabelStatement(pCaseLabel);
            }
        }
    }
    if(pDefaultBranch)
        branchIfs.push_back(pDefaultBranch);
    pInnerBlock->prependStatements(branchIfs);
    pInnerBlock->addStatement(o_new(LabelStatement)("break"));
}

void precompiler::precompile_goto_statement(goto_statement&, Block* a_pBlock) 
{ 
//    o_new(GotoStatement)
}

void  precompiler::precompile_label_statement(label_statement& ls, Block* a_pBlock) 
{
    a_pBlock->addStatement(o_new(LabelStatement)(ls.m_label.m_value));
}

void  precompiler::precompile_return_statement(return_statement&  rs, Block* a_pBlock) 
{
    o_assert(a_pBlock->getSubroutine());
    ReturnStatement* pReturnStatement = o_new(ReturnStatement);
    a_pBlock->addStatement(pReturnStatement);
    Type* pReturnType = pReturnStatement->getSubroutine()->getReturnType();
    if(pReturnType == typeOf<void>() AND rs.m_return_value.is_initialized())
    {
        pReturnStatement->setInvalid();
        error(node_location(rs), "void function returning value");
    }
    else if(pReturnType != typeOf<void>() AND NOT(rs.m_return_value.is_initialized()))
    {
        pReturnStatement->setInvalid();
        error(node_location(rs), "non-void' function requires return value");
    }
    else if(rs.m_return_value.is_initialized())
    {
        Expression* pExpression = precompile_expression(*rs.m_return_value, a_pBlock);
        if(pExpression == nullptr)
        {
            error(node_location(rs.m_return_value), "Invalid return value");
        }
        else if(NOT(pExpression->getValueType()->isImplicitlyConvertibleTo(pReturnType)))
        {
            error(node_location(rs.m_return_value), "Cannot convert return value from '%s' to '%s'", pExpression->getValueType()->getQualifiedDecoratedName().c_str(), pReturnType->getQualifiedDecoratedName().c_str());
        }
        pReturnStatement->setReturnExpression(pExpression);
    }
}

struct addressed_access_builder
{
    virtual Expression* build() const = 0;
};

struct local_variable_addressed_access_builder : public addressed_access_builder
{
    local_variable_addressed_access_builder(LocalVariable* a_pLocalVariable)
        : m_pLocalVariable(a_pLocalVariable)
    {

    }
    virtual Expression* build() const 
    {
        return (o_new(LocalVariableAccess)(m_pLocalVariable))->address();
    }

protected:
    LocalVariable* m_pLocalVariable;
};

struct array_element_addressed_access_builder : public addressed_access_builder
{
    array_element_addressed_access_builder(LocalVariable* a_pLocalVariable, size_t a_uiIndex)
        : m_pLocalVariable(a_pLocalVariable)
        , m_uiIndex(a_uiIndex)
    {
        o_assert(m_pLocalVariable->getValueType()->asArrayType());
    }
    virtual Expression* build() const 
    {
        ConstantExpression* pIndexExpression = o_new(ConstantExpression)(
            o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<uint>)(
            lexical_cast<string>(m_uiIndex), m_uiIndex), nullptr, true
            );
        return (o_new(ArrayElementAccess)(m_pLocalVariable->getValueType()->asArrayType(), o_new(LocalVariableAccess)(m_pLocalVariable), pIndexExpression))->address();
    }

    LocalVariable* m_pLocalVariable;
    size_t m_uiIndex;
};

void precompiler::precompile_array_initializer(LocalVariable* a_pLocalVariable, ArrayType* a_pArrayType, array_initializer& ai, Block* a_pBlock )
{
    o_assert(a_pLocalVariable->getValueType() == a_pArrayType);
    Type* pElementType = a_pArrayType->getElementType();
    if(a_pArrayType->getElementCount() != ai.m_expressions.size())
    {
        error(node_location(ai), "Array initializer element count does not match array size");
    }
    size_t i = 0;
    size_t count = ai.m_expressions.size();
    for(; i<count; ++i)
    {
        expression& e = ai.m_expressions[i];
        Expression* pExpression = precompile_expression(e, a_pBlock);
        if(pExpression AND pExpression->getValueType()->isConvertibleTo(pElementType))
        {
            array_element_addressed_access_builder builder(a_pLocalVariable, i);
            precompile_initialization(pElementType, builder, pExpression, a_pBlock);
        }
        else
        {
            if(pExpression)
            {
                error(node_location(e), "Cannot convert from '%s' to '%s'", pExpression->getValueType()->getQualifiedDecoratedName().c_str(), pElementType->getQualifiedDecoratedName().c_str());
            }
            else
            {
                error(node_location(e), "Invalid expression");
            }
        }
    }
}

void precompiler::precompile_array_initializer_or_expression(LocalVariable* a_pLocalVariable, Type* a_pType, array_initializer_or_expression& aie, Block* a_pBlock )
{
    array_initializer* p_array_initializer = 0;
    expression* p_expression = 0;
    array_initializer_or_expression_visitor aiev(&p_array_initializer, &p_expression);
    aie.apply_visitor(aiev);
    if(p_array_initializer)
    {
        if(a_pType->asArrayType())
        {
             precompile_array_initializer(a_pLocalVariable, a_pType->asArrayType(), *p_array_initializer, a_pBlock);
        }
        else
        {
            error(node_location(aie), "Array initializer requires array type variable");
        }

    }
    else
    {
        o_assert(p_expression);
        Expression* pExpression = precompile_expression(*p_expression, a_pBlock);
        local_variable_addressed_access_builder builder(a_pLocalVariable);
        precompile_initialization(a_pType, builder, pExpression, a_pBlock);
    }
}

LocalVariable* precompiler::precompile_variable_declarator(Type* a_pType, variable_declarator& vd, Block* a_pBlock)
{
    string name = vd.m_identifier;
    bool bValid = true;
    for(auto it = vd.m_end.m_extents.begin(); it != vd.m_end.m_extents.end(); ++it)
    {
        LanguageElement* pElement = precompile_template_element(*it, a_pBlock);

        ConstantExpression* pConstantExpression = as<ConstantExpression*>(pElement);
        if(pConstantExpression == nullptr)
        {
            error(node_location(*it), "Expression '%s' must be a constant", node_string(*it).c_str());
            a_pBlock->setInvalid();
            continue;
        }
        Expression* pCastedExpression = pConstantExpression->implicitCast(typeOf<size_t>());
        if(pCastedExpression == nullptr)
        {
            error(node_location(*it), "Expression '%s' must be an integral constant", node_string(*it).c_str());
            a_pBlock->setInvalid();
            continue;
        }

        size_t value = 0;
        pCastedExpression->getValue(&value);
        if(value == 0)
        {
            error(node_location(*it), "Array cannot have '0' size", node_string(*it).c_str());
            a_pBlock->setInvalid();
            phantom::deleteElement(pCastedExpression);
            continue;
        }
        a_pType = a_pType->arrayType(value);
        phantom::deleteElement(pCastedExpression);
    }
    LocalVariable* pLocalVariable = o_new(LocalVariable)(a_pType, name);
    a_pBlock->addLocalVariable(pLocalVariable);
    if(a_pType)
    {
        if(vd.m_end.m_array_initializer_or_expression.is_initialized())
        {
            precompile_array_initializer_or_expression(pLocalVariable, a_pType, *vd.m_end.m_array_initializer_or_expression, a_pBlock);
        }
    }
    return pLocalVariable;
}

void precompiler::precompile_initialization(Type* a_pType, const addressed_access_builder& aab, Expression* a_pExpression, Block* a_pBlock)
{
    if(a_pType->asClassType())
    {
        vector<Expression*> arguments;
        vector<Expression*> noArguments;
        arguments.push_back(aab.build());
        arguments.push_back(a_pExpression);
        Constructor* pConstructor = a_pType->asClassType()->getConstructor(a_pExpression->getValueType());
        if(pConstructor)
        {
            a_pBlock->addStatement(o_new(ExpressionStatement)(o_new(CallExpression)(pConstructor, arguments)));
            vector<Expression*> destructorArguments;
            destructorArguments.push_back(aab.build());
            a_pBlock->addRAIIDestructionStatement(o_new(ExpressionStatement)(o_new(CallExpression)(a_pType->asClassType()->getDestructor(), destructorArguments)));
        }
        else 
        {
            vector<Type*> empty;
            Constructor* pDefaultConstructor = a_pType->asClassType()->getConstructor(empty, nullptr, o_public);
            if(pDefaultConstructor)
            {
                Expression* pAssignmentExpression = a_pType->solveOperator("=", arguments, o_public);
                if(pAssignmentExpression)
                {
                    // Default construction
                    vector<Expression*> defaultConstructorArguments;
                    defaultConstructorArguments.push_back(aab.build());
                    a_pBlock->addStatement(o_new(ExpressionStatement)(o_new(CallExpression)(pDefaultConstructor, defaultConstructorArguments)));

                    // Assignment operation
                    a_pBlock->addStatement(o_new(ExpressionStatement)(pAssignmentExpression));

                    // if not a POD
                    if(a_pType->asPOD() == nullptr)
                    {
                        // RAII Destruction
                        vector<Expression*> destructorArguments;
                        destructorArguments.push_back(aab.build());
                        a_pBlock->addRAIIDestructionStatement(o_new(ExpressionStatement)(o_new(CallExpression)(a_pType->asClassType()->getDestructor(), destructorArguments)));
                    }
                }
                else 
                {
                    a_pBlock->setInvalid();
                    error(a_pExpression->getCodeLocation(), "No constructor available matching initialization expression type '%s'", a_pExpression->getValueType()->getQualifiedDecoratedName().c_str());
                }
            }
            else if(a_pType->asPOD() == nullptr)
            {
                a_pBlock->setInvalid();
                error(a_pExpression->getCodeLocation(), "No default constructor available");
            }
        }
    }
    else 
    {
        vector<Expression*> arguments;
        arguments.push_back(aab.build()->dereference());
        arguments.push_back(a_pExpression);
        Expression* pAssignmentExpression = a_pType->solveOperator("=", arguments, o_public);
        if(pAssignmentExpression)
        {
            a_pBlock->addStatement(o_new(ExpressionStatement)(pAssignmentExpression));
        }
        else 
        {
            a_pBlock->setInvalid();
            error(a_pExpression->getCodeLocation(), "Cannot convert from '%s' to '%s'", a_pExpression->getValueType()->getQualifiedDecoratedName().c_str(), a_pType->getQualifiedDecoratedName().c_str());
        }
    }
}

void precompiler::precompile_variable_declaration(variable_declaration& vd, Block* a_pBlock, vector<LocalVariable*>* a_pOut)
{
    Type* pType = precompile_type_recursive(vd.m_type, a_pBlock);
    if(pType == nullptr)
    {
        error(node_location(vd.m_type), "Cannot solve variable type '%s'", node_string(vd.m_type).c_str());
    }
    LocalVariable* pLocalVariable = precompile_variable_declarator(pType, vd.m_declarator, a_pBlock);
    if(a_pOut)
    {
        a_pOut->push_back(pLocalVariable);
    }
    for(auto it = vd.m_extra_declarators.begin(); it != vd.m_extra_declarators.end(); ++it)
    {
        extra_variable_declarator& evd = *it;
        Type* pExtraType = pType;
        for(auto it = evd.m_type_qualifiers.begin(); it != evd.m_type_qualifiers.end(); ++it)
        {
            pExtraType = precompile_type_qualifier(pExtraType, it->m_value);
            if(pExtraType == nullptr)
                break;
        }
        pLocalVariable = precompile_variable_declarator(pExtraType, evd.m_variable_declarator, a_pBlock);
        if(a_pOut)
        {
            a_pOut->push_back(pLocalVariable);
        }
    }
}
void precompiler::precompile_variable_declaration(variable_declaration&, Namespace* a_pNamespace) 
{ 
}

void precompiler::precompile_statement(statement& s, Block* a_pBlock)
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
    return_statement*           p_return_statement= 0;
    variable_declaration*       p_variable_declaration= 0;
    fundamental_node<int>* p_keywords_statement = 0;

    statement_visitor sv(&p_expression, &p_block, &p_if_statement, &p_for_statement, &p_while_statement, &p_do_while_statement, &p_switch_statement, &p_goto_statement, &p_label_statement, &p_variable_declaration, &p_return_statement, &p_keywords_statement);
    s.apply_visitor(sv);
    if(p_expression)
    {
        Expression* pExpression = precompile_expression(*p_expression, a_pBlock);
        if(pExpression)
        {
            Statement* pStatement = o_new(ExpressionStatement)(pExpression);
            a_pBlock->addStatement(pStatement);
        }
        else 
        {
            error(node_location(s), "Invalid expression in statement");
        }
    }
    else if(p_block)
    {
        precompile_block(*p_block, a_pBlock);
    }
    else if(p_variable_declaration)
    {
        precompile_variable_declaration(*p_variable_declaration, a_pBlock, nullptr);
    }
    else if(p_if_statement)
    {
        precompile_if_statement(*p_if_statement, a_pBlock);
    }
    else if(p_for_statement)
    {
        precompile_for_statement(*p_for_statement, a_pBlock);
    }
    else if(p_while_statement)
    {
        precompile_while_statement(*p_while_statement, a_pBlock);
    }
    else if(p_switch_statement)
    {
        precompile_switch_statement(*p_switch_statement, a_pBlock);
    }
    else if(p_do_while_statement)
    {
        precompile_do_while_statement(*p_do_while_statement, a_pBlock);
    }
    else if(p_goto_statement)
    {
        precompile_goto_statement(*p_goto_statement, a_pBlock);
    }
    else if(p_label_statement)
    {
        precompile_label_statement(*p_label_statement, a_pBlock);
    }
    else if(p_return_statement)
    {
        precompile_return_statement(*p_return_statement, a_pBlock);
    }
}

bool precompiler::precompile_string_literal(string_node& s, string& out)
{
    o_assert(s.m_value[0] == '"' AND s.m_value.back() == '"');
    for(size_t i = 1; i<s.m_value.size()-1; ++i)
    {
        if(s.m_value[i] == '\\')
        {
            ++i;
            if(i == s.m_value.size()) 
            {
                error(s.m_location, "Incomplete escape sequence in string literal");
                return false;
            }
            switch(s.m_value[i])
            {
                case 'n': out += '\n'; break;
                case 't': out += '\t'; break;
                case 'r': out += '\r'; break;
                case '0': out += '\0'; break;
                default:
                    out += s.m_value[i];
            }
        }
        else 
        {
            out += s.m_value[i];
        }
    }
    return true;
}

Expression* precompiler::precompile_expression(expression& e, Block* a_pBlock)
{
    LocalVariable* pThis = a_pBlock->getRootBlock()->getLocalVariable("this");
    Expression* pExpression = nullptr;
    if(pThis)
    {
        element_garbage garbage;
        Expression* pThisExpression = (o_new(LocalVariableAccess)(pThis))->dereference();
        garbage.add(pThisExpression);
        pExpression = precompile_expression(e, a_pBlock, pThisExpression);
        if(pExpression AND pExpression->isInvalid())
        {
            phantom::deleteElement(pExpression);
            pExpression = nullptr;
        }
    }
    if(pExpression == nullptr)
    {
        pExpression = precompile_expression(e, a_pBlock, nullptr);
    }
    return pExpression;
}

Expression* precompiler::precompile_expression(expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/)
{
    cast_expression* p_cast_expression = 0;
    pre_unary_expression* p_pre_unary_expression = 0;
    post_unary_expression* p_post_unary_expression = 0;
    binary_right_expression* p_binary_right_expression = 0;
    ternary_if_expression* p_ternary_if_expression = 0;
    call_expression* p_call_expression = 0;
    bracket_expression* p_bracket_expression = 0;
    qualified_name* p_qualified_name = 0;
    literal* p_literal = 0;
    expression_visitor ev(&p_cast_expression, &p_pre_unary_expression, &p_post_unary_expression, /*&p_binary_left_expression, */&p_binary_right_expression, &p_ternary_if_expression, &p_call_expression, &p_bracket_expression, &p_qualified_name, &p_literal);
    e.apply_visitor(ev);
    {
        if(p_literal)
        {
            fundamental_literal* p_fundamental_literal = 0;
            string_node* p_string = 0;
            literal_visitor lv(&p_fundamental_literal, &p_string);
            p_literal->apply_visitor(lv);
            if(p_fundamental_literal)
            {
                return precompile_fundamental_literal(*p_fundamental_literal);                
            }
            else if(p_string)
            {
                string unescaped;
                if(NOT(precompile_string_literal(*p_string, unescaped)))
                {
                    return nullptr;
                }
                return o_new(StringLiteralExpression)(unescaped);
            }
            //return o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<longlong>)(lexical_cast<string>(*p_longlong),*p_longlong), nullptr, true);
        }
        else if(p_qualified_name)
        {
            LanguageElement* pElement = nullptr;
            if(a_pLHS)
            {
                pElement = precompile_qualified_name(a_pLHS, *p_qualified_name, nullptr, false, a_pScope);
            }
            else
            {
                pElement = precompile_qualified_name_recursive(*p_qualified_name, nullptr, false, a_pScope);
            }
            return pElement ? pElement->asExpression() : nullptr;
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
//         else if(p_binary_left_expression)
//         {
//             return precompile_binary_left_expression(*p_binary_left_expression, a_pScope, a_pLHS);
//         }
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
        else if(p_bracket_expression)
        {
            return precompile_bracket_expression(*p_bracket_expression, a_pScope, a_pLHS);
        }
    }
    return nullptr;
}

Expression* precompiler::precompile_cast_expression(cast_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS)
{
    element_garbage garbage;

    Expression* pCastedExpression = precompile_expression(e.m_casted_expression.get(), a_pScope, a_pLHS);
    if(pCastedExpression == nullptr) return nullptr;
    garbage.add(pCastedExpression);

    if(e.m_types.size()) 
    {
        for(auto it = e.m_types.rbegin(); it != e.m_types.rend(); ++it)
        {
            Type* pType = precompile_type_recursive(it->m_type, a_pScope);
            if(pType == nullptr) return nullptr;
            garbage.add(pType);
            pType->setCodeLocation(it->m_location | pCastedExpression->getCodeLocation());
            Expression* pNewCastedExpression = pCastedExpression->cast(pType);
            if(pNewCastedExpression == nullptr) return nullptr;
            garbage.add(pNewCastedExpression);
            pCastedExpression = pNewCastedExpression;
        }
    }
    
    garbage.clear();
    return pCastedExpression;
}

Expression* precompiler::precompile_ternary_if_expression(ternary_if_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS)
{
    element_garbage garbage;
    Expression* pCondElement = precompile_expression(e.m_condition.get(), a_pScope, a_pLHS);
    garbage.add(pCondElement);
    if(pCondElement == nullptr) return nullptr;
    pCondElement->setCodeLocation(e.m_location);
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

Expression* precompiler::precompile_bracket_expression(bracket_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS)
{
    element_garbage garbage;
    Expression* pExpression = precompile_call_expression(e.m_left.get(), a_pScope, a_pLHS);
    if(pExpression == nullptr) 
    {
        return nullptr;
    }
    garbage.add(pExpression);
    auto it = e.m_arguments.begin();
    for(;it != e.m_arguments.end(); ++it)
    {
        vector<Expression*> argumentList;
        argumentList.push_back(precompile_expression(*it, a_pScope, nullptr));
        Expression* pCall = pExpression->solveOperator("[]", argumentList);
        if(pCall == nullptr) 
        {
            error(node_location(*it), "Cannot solve operator[] with given arguments");
            return nullptr;
        }
        pCall->setCodeLocation(node_location(*it));
        garbage.add(pCall);
        pExpression = pCall;
    }

    garbage.clear();
    pExpression->setCodeLocation(e.m_location);
    return pExpression;
}


Expression* precompiler::precompile_call_expression(call_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS)
{
    element_garbage garbage;
    Expression* pExpression = nullptr;
    auto it = e.m_argument_lists.begin();
    if(e.m_argument_lists.size())
    {
        auto& argument_list = e.m_argument_lists.front();
        post_unary_expression& pue = e.m_left.get();
        if(pue.m_ops.empty()) // not really a post unary expression, forwards to primary_expression
        {
            qualified_name* p_qualified_name = boost::get<qualified_name>(&pue.m_expression.get());
            if(p_qualified_name)
            {
                // solve function call
                vector<Expression*> argumentList;
                for(auto it = argument_list.m_expressions.begin(); it != argument_list.m_expressions.end(); ++it)
                {
                    argumentList.push_back(precompile_expression(*it, a_pScope, nullptr));
                }
                LanguageElement* pQualifiedName = a_pLHS 
                                                     ? precompile_qualified_name(a_pLHS, *p_qualified_name, (vector<LanguageElement*>*)&argumentList, false, a_pScope)
                                                     : precompile_qualified_name_recursive(*p_qualified_name, (vector<LanguageElement*>*)&argumentList, false, a_pScope);
                if(pQualifiedName == nullptr)
                    return nullptr;
                pExpression = (pQualifiedName->asExpression());
                o_assert(pExpression);
            }
        }
    }

    if(pExpression == nullptr)
    {
        pExpression = precompile_post_unary_expression(e.m_left.get(), a_pScope, a_pLHS);
        if(pExpression == nullptr) 
            return nullptr;
        garbage.add(pExpression);
    }
    else 
    {
        ++it;
    }

    for(;it != e.m_argument_lists.end(); ++it)
    {
        auto& argument_list = *it;
        auto& list = argument_list.m_expressions;
        vector<Expression*> argumentList;
        for(auto it = list.begin(); it != list.end(); ++it)
        {
            argumentList.push_back(precompile_expression(*it, a_pScope, nullptr));
        }
        Expression* pCall = pExpression->solveOperator("()", argumentList);
        pCall->setCodeLocation(node_location(argument_list));
        if(pCall == nullptr) 
        {
            error(node_location(argument_list), "Cannot solve operator() with given arguments");
            return nullptr;
        }
        garbage.add(pCall);
        pExpression = pCall;
    }

    garbage.clear();
    pExpression->setCodeLocation(e.m_location);
    return pExpression;
}

Expression* precompiler::precompile_pre_unary_expression(pre_unary_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS)
{
    element_garbage garbage;
    Expression* pExpression = precompile_expression(e.m_expression.get(), a_pScope, a_pLHS);
    garbage.add(pExpression);
    if(pExpression == nullptr) return nullptr;

    for(auto it = e.m_ops.rbegin(); it != e.m_ops.rend(); ++it)
    {
        const string& opName = token_ids::operator_string_from_token_id(*it);
        Expression* pOperation = pExpression->solveUnaryOperator(opName);
        pOperation->setCodeLocation(pExpression->getCodeLocation()|it->m_location);
        if(pOperation == nullptr) 
        {
            error(node_location(*it), "Cannot solve prefix unary operator%s", opName.c_str());
            return nullptr;
        }
        garbage.add(pOperation);
        pExpression = pOperation;
    }
    garbage.clear();
    return pExpression;
}

Expression* precompiler::precompile_post_unary_expression(post_unary_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS)
{
    element_garbage garbage;
    Expression* pExpression = precompile_expression(e.m_expression.get(), a_pScope, a_pLHS);
    if(pExpression == nullptr) return nullptr;

    for(auto it = e.m_ops.begin(); it != e.m_ops.end(); ++it)
    {
        const string& opName = token_ids::operator_string_from_token_id(*it);
        Expression* pOperation = (opName == "++") ? pExpression->solveBinaryOperator(opName, phantom::expressionByName("0")->implicitCast(typeOf<int>())) : pExpression->solveUnaryOperator(opName);
        pOperation->setCodeLocation(pExpression->getCodeLocation()|it->m_location);
        if(pOperation == nullptr) 
        {
            error(node_location(*it), "Cannot solve postfix unary operator%s", opName.c_str());
            return nullptr;
        }
        garbage.add(pOperation);
        pExpression = pOperation;
    }
    garbage.clear();
    return pExpression;
}

Expression* precompiler::precompile_binary_right_expression(binary_right_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS)
{
    element_garbage garbage;
    Expression* pLeftExpression = precompile_expression(e.m_left.get(), a_pScope, a_pLHS);
    if(pLeftExpression == nullptr) return nullptr;
    garbage.add(pLeftExpression);

    for(auto it = e.m_op_rights.begin(); it != e.m_op_rights.end(); ++it)
    {
        binary_op_right_expression& e = *it;

        // Either real operator or member access
        // MEMBER ACCESS / INDIRECTION :
        Expression* pRightExpression = nullptr;
        if(e.m_op == token_ids::dot) // MEMBER ACCESS
        { 
            Expression* pDotExpression = precompile_expression(e.m_right.get(), a_pScope, pLeftExpression);
            if(pDotExpression == nullptr)
            {
                error(node_location(*it), "Cannot solve member expression '%s'", node_string(e.m_right).c_str());
                return nullptr;
            }
            pLeftExpression = pDotExpression;
        }
        else if(e.m_op == token_ids::minus_greater)
        {
            Expression* pNewLeftExpression = pLeftExpression->dereference();
            garbage.add(pNewLeftExpression);
            if(pNewLeftExpression == nullptr) 
            {
                pLeftExpression = pLeftExpression->solveUnaryOperator("->");
                garbage.add(pLeftExpression);
                if(pLeftExpression == nullptr) 
                {
                    error(node_location(e.m_op), "Cannot solve binary operator->");
                    return nullptr;
                }
            }
            else pLeftExpression = pNewLeftExpression;
            Expression* pRightExpression = precompile_expression(e.m_right.get(), a_pScope, pLeftExpression);
            if(pRightExpression == nullptr)
            {
                error(node_location(e.m_right), "Cannot solve member expression '%s'", node_string(e.m_right).c_str());
                return nullptr;
            }
            garbage.add(pRightExpression);
            pLeftExpression = pRightExpression;
        }
        else 
        {
            pRightExpression = a_pScope->asBlock() 
                                    ? precompile_expression(e.m_right.get(), a_pScope->asBlock()) 
                                    : precompile_expression(e.m_right.get(), a_pScope, nullptr);
            garbage.add(pRightExpression);
            if(pRightExpression == nullptr) 
                return nullptr;
            const string& opName = token_ids::operator_string_from_token_id(e.m_op);
            auto codeLocation = (pLeftExpression->getCodeLocation() | pRightExpression->getCodeLocation());
            pLeftExpression = pLeftExpression->solveBinaryOperator(opName, pRightExpression);
            if(pLeftExpression == nullptr)
            {
                error(node_location(e.m_right), "Cannot solve binary operator%s", opName.c_str());
                return nullptr;
            }
            pLeftExpression->setCodeLocation(codeLocation);
            garbage.add(pLeftExpression);
        }
        if(pLeftExpression == nullptr) 
        {
            return nullptr;
        }
    }

    garbage.clear();
    return pLeftExpression;
}

//LanguageElement* precompiler::precompile_binary_left_expression(binary_left_expression& e, LanguageElement* a_pScope, LanguageElement* a_pLHS)
//{
    /*element_garbage garbage;
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
        const string& opName = token_ids::operator_string_from_token_id(e.m_op);
        pRight = pLeftExpression->solveBinaryOperator("$"+opName+"$", pRightExpression);
        if(pRight == nullptr)
        {
            error(node_location(e.m_left), "Cannot solve binary operator%s", opName.c_str());
            return nullptr;
        }
        garbage.add(pRight);
        pRight->setCodeLocation(pLeftExpression->getCodeLocation()|pRightExpression->getCodeLocation());
    }

    garbage.clear();
    return pRight;*/
//    return nullptr;
//}

ConstantExpression* precompiler::precompile_fundamental_literal( fundamental_literal& fl )
{
    fundamental_node<hex_t>* p_hex_t = 0;
    fundamental_node<float>* p_float = 0; 
    fundamental_node<double>* p_double = 0; 
    fundamental_node<longdouble>* p_longdouble = 0; 
    fundamental_node<int>* p_int = 0; 
    fundamental_node<uint>* p_uint = 0; 
    fundamental_node<longlong>* p_longlong = 0; 
    fundamental_node<ulonglong>* p_ulonglong = 0; 
    fundamental_node<char>* p_char = 0; 
    fundamental_node<bool>* p_bool = 0;
    fundamental_node<std::nullptr_t>* p_nullptr = 0;
    fundamental_literal_visitor flv(&p_hex_t, &p_float, &p_double, &p_longdouble, &p_int, &p_uint, &p_longlong, &p_ulonglong, &p_char, &p_bool, &p_nullptr);
    fl.apply_visitor(flv);
    ConstantExpression* pExpression = nullptr;
    node* node = nullptr;
    if(p_hex_t) { pExpression = o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<ulonglong>)(lexical_cast<string>(p_hex_t->m_value.val),p_hex_t->m_value.val), nullptr, true); node = p_hex_t; }
    else if(p_float) { pExpression = o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<float>)(lexical_cast<string>(*p_float),*p_float), nullptr, true); node = p_float; }
    else if(p_double) { pExpression = o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<double>)(lexical_cast<string>(*p_double),*p_double), nullptr, true); node = p_double; }
    else if(p_longdouble) { pExpression = o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<longdouble>)(lexical_cast<string>(*p_longdouble),*p_longdouble), nullptr, true); node = p_longdouble; }
    else if(p_int) { pExpression = o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<int>)(lexical_cast<string>(*p_int),*p_int), nullptr, true); node = p_int; }
    else if(p_uint) { pExpression = o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<uint>)(lexical_cast<string>(*p_uint),*p_uint), nullptr, true); node = p_uint; }
    else if(p_longlong) { pExpression = o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<longlong>)(lexical_cast<string>(*p_longlong),*p_longlong), nullptr, true); node = p_longlong; }
    else if(p_ulonglong) { pExpression = o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<ulonglong>)(lexical_cast<string>(*p_ulonglong),*p_ulonglong), nullptr, true); node = p_ulonglong; }
    else if(p_char) { pExpression = o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<char>)(lexical_cast<string>(*p_char),*p_char), nullptr, true); node = p_char; } 
    else if(p_bool) { pExpression = o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<bool>)(lexical_cast<string>(*p_bool),*p_bool), nullptr, true); node = p_bool; } 
    else if(p_nullptr) { pExpression = o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<std::nullptr_t>)("nullptr", 0), nullptr, true); node = p_nullptr; }
    if(pExpression)
    {
        pExpression->addCodeLocation(node->m_location);
    }
    return pExpression;
}

ConstantExpression* precompiler::precompile_integral_literal( integral_literal& il )
{
    fundamental_node<hex_t>* p_hex_t = 0;
    fundamental_node<int>* p_int = 0; 
    fundamental_node<uint>* p_uint = 0; 
    fundamental_node<longlong>* p_longlong = 0; 
    fundamental_node<ulonglong>* p_ulonglong = 0; 
    fundamental_node<char>* p_char = 0; 
    fundamental_node<bool>* p_bool = 0;
    integral_literal_visitor ilv(&p_hex_t, &p_int, &p_uint, &p_longlong, &p_ulonglong, &p_char, &p_bool);
    il.apply_visitor(ilv);
    ConstantExpression* pExpression = nullptr;
    node* node = nullptr;
    if(p_hex_t) { pExpression = o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<ulonglong>)(lexical_cast<string>(p_hex_t->m_value.val),p_hex_t->m_value.val), nullptr, true); node = p_hex_t; }
    else if(p_int) { pExpression = o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<int>)(lexical_cast<string>(*p_int),*p_int), nullptr, true); node = p_int; }
    else if(p_uint) { pExpression = o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<uint>)(lexical_cast<string>(*p_uint),*p_uint), nullptr, true); node = p_uint; }
    else if(p_longlong) { pExpression = o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<longlong>)(lexical_cast<string>(*p_longlong),*p_longlong), nullptr, true); node = p_longlong; }
    else if(p_ulonglong) { pExpression = o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<ulonglong>)(lexical_cast<string>(*p_ulonglong),*p_ulonglong), nullptr, true); node = p_ulonglong; }
    else if(p_char) { pExpression = o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<char>)(lexical_cast<string>(*p_char),*p_char), nullptr, true); node = p_char; } 
    else if(p_bool) { pExpression = o_new(ConstantExpression)(o_dynamic_proxy_new(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, phantom::reflection::native::TNumericConstant<bool>)(lexical_cast<string>(*p_bool),*p_bool), nullptr, true); node = p_bool; }
    if(pExpression)
    {
        pExpression->addCodeLocation(node->m_location);
    }
    return pExpression;
}

void precompiler::error( const CodeLocation& a_Location, const char* a_Format, ... )
{
    va_list args;
    va_start(args, a_Format);
    if(m_pMessage)
    {
        m_pMessage->error(a_Location, a_Format, args);
    }
    else 
    {
        vprintf(a_Format, args);
        printf("\n");
    }
    va_end(args);
}

LanguageElement* precompiler::precompile_qualified_name_recursive( qualified_name & qn, vector<LanguageElement*>* a_pSignature, bool a_bConstSignature, LanguageElement* a_pScope )
{
    LanguageElement* pScope = a_pScope;
    while(pScope)
    {
        LanguageElement* pElement = precompile_qualified_name(nullptr, qn, a_pSignature, a_bConstSignature, pScope);
        if(pElement) 
        {
            return pElement->asExpression();
        }
        pScope = pScope->getOwner();
    }
    return nullptr;
}

LanguageElement* precompiler::precompile_qualified_name( LanguageElement* a_pLHS, qualified_name & qn, vector<LanguageElement*>* a_pSignature, bool a_bConstSignature, LanguageElement* a_pScope )
{
    element_garbage garbage;
    if(qn.empty())
    {
        return nullptr;
    }
    size_t i = 0;
    size_t count = qn.size();
    for(;i<count; ++i)
    {
        // Each name inside the qualified name is treated and has potentially
        // a template specialization if it's a class type
        if(i == 0 && qn[i].get().m_identifier.m_value == "")
        {
            a_pLHS = phantom::rootNamespace();
        }
        else
        {
            LanguageElement* pElement = precompile_name(a_pLHS, qn[i].get(), (i == count-1) ? a_pSignature : nullptr, (i == count-1) ? a_bConstSignature : false, a_pScope);
            garbage.add(pElement);
            if(pElement == nullptr)
            {
                return nullptr;
            }
            a_pLHS = pElement;
        }
    }
    garbage.clear();
    return a_pLHS;
}

void precompiler::precompile_compilation_unit(compilation_unit & cu, Namespace* a_pNamespace)
{
    for(auto it = cu.begin(); it != cu.end(); ++it)
    {
        precompile_namespace_member_declaration(*it, a_pNamespace);
    }
}

void precompiler::precompile_namespace_scope(namespace_scope & ns, Namespace* a_pNamespace)
{
    for(auto it = ns.begin(); it != ns.end(); ++it)
    {
        precompile_namespace_member_declaration(*it, a_pNamespace);
    }
}

void precompiler::precompile_namespace_member_declaration(namespace_member_declaration & nmd, Namespace* a_pNamespace)
{
    ambiguous_global_declaration* p_ambiguous_global_declaration = 0;
    namespace_declaration* p_namespace_declaration = 0;
    class_declaration* p_class_declaration = 0;
    typedef_declaration* p_typedef_declaration = 0;
    namespace_member_declaration_visitor nmdv(&p_ambiguous_global_declaration, &p_namespace_declaration, &p_class_declaration, &p_typedef_declaration);
    nmd.apply_visitor(nmdv);
    if(p_ambiguous_global_declaration)
    {
        //precompile_global_variable_declaration(*p_variable_declaration, a_pNamespace);
    }
    else if(p_namespace_declaration)
    {
        precompile_namespace_declaration(*p_namespace_declaration, a_pNamespace);
    }
    else if(p_class_declaration)
    {
        precompile_class_declaration(*p_class_declaration, a_pNamespace);
    }
    else if(p_typedef_declaration)
    {
        // precompile_typedef_declaration(*p_typedef_declaration, a_pNamespace);
    }
}

void             precompiler::precompile_namespace_declaration(namespace_declaration & nd, Namespace* a_pNamespace)
{
    namespace_scope* p_namespace_scope = 0;
    namespace_alias* p_namespace_alias = 0;
    namespace_declaration_visitor ndv(&p_namespace_scope, &p_namespace_alias);
    nd.m_alias_or_scope.apply_visitor(ndv);
    if(p_namespace_scope)
    {
        Namespace* pNamespace = a_pNamespace->findOrCreateNamespaceCascade(nd.m_name);
        precompile_namespace_scope(*p_namespace_scope, pNamespace);
    }
    else 
    {
        o_assert(p_namespace_alias);
        Namespace* pNamespace = a_pNamespace;
        for(auto it = p_namespace_alias->begin(); it != p_namespace_alias->end(); ++it)
        {
            if(it->m_value.empty())
            {
                o_assert(it == p_namespace_alias->begin());
                pNamespace = phantom::rootNamespace();
            }
            else 
            {
                Namespace* pChildNamespace = pNamespace->getNamespace(it->m_value);
                if(pChildNamespace == nullptr) 
                {
                    error(node_location(nd), "Namespace '%s' not declared in namespace '%s'", it->m_value, pNamespace->getQualifiedName().c_str());
                    return;
                }
                pNamespace = pChildNamespace;
            }
        }
        a_pNamespace->addNamespaceAlias(nd.m_name, pNamespace);
    }
}

void             precompiler::precompile_nested_class_declaration(class_declaration & cd, int a_Modifiers, Class* a_pClass)
{
    class_scope* classScope = nullptr;
    string_node name = precompile_named_or_unnamed_class_declaration(cd.m_named_or_unnamed_class_declaration, classScope);
    if(name.m_value.empty())
        return;
    LanguageElement* pAlreadyExisting = a_pClass->solveElement(name, nullptr, nullptr, 0);
    if(pAlreadyExisting)
    {
        error(node_location(name)
            , "A class, struct or function with same name '%s' already declared in class '%s'"
            , name.m_value.c_str()
            , a_pClass->getQualifiedName().c_str()); 
        return;
    }
    Class* pClass = o_new(Class)(name.m_value, a_Modifiers);
    a_pClass->addNestedType(pClass);
    if(classScope)
    {
        precompile_class_scope(*classScope, cd.m_is_struct ? o_public : 0, pClass);
    }
    pClass->finalize();
}

void             precompiler::precompile_class_declaration(class_declaration & cd, Namespace* a_pNamespace)
{
    class_scope* classScope = nullptr;
    string_node name = precompile_named_or_unnamed_class_declaration(cd.m_named_or_unnamed_class_declaration, classScope);
    if(name.m_value.empty())
        return;
    LanguageElement* pAlreadyExisting = a_pNamespace->solveElement(name, nullptr, nullptr, 0);
    if(pAlreadyExisting)
    {
        error(node_location(name)
            , "A class, struct or member with same name '%s' already declared in class '%s'"
            , name.m_value.c_str()
            , a_pNamespace->getQualifiedName().c_str()); 
        return;
    }
    Class* pClass = o_new(Class)(name.m_value, 0);
    a_pNamespace->addType(pClass);
    if(classScope)
    {
        precompile_class_scope(*classScope, cd.m_is_struct ? o_public : 0, pClass);
    }
    pClass->finalize();
}

string_node   precompiler::precompile_named_or_unnamed_class_declaration(named_or_unnamed_class_declaration & cd, class_scope*& a_ClassScope)
{
    named_class_declaration* p_named_class_declaration = 0;
    unnamed_class_declaration* p_unnamed_class_declaration = 0;
    named_or_unnamed_class_declaration_visitor noucd(&p_named_class_declaration, &p_unnamed_class_declaration);
    cd.apply_visitor(noucd);
    if(p_named_class_declaration)
    {
        if(p_named_class_declaration->m_class_scope.is_initialized()) // has class scope, it is a definition
        {
            a_ClassScope = &*(p_named_class_declaration->m_class_scope);
        }
        return p_named_class_declaration->m_name;
    }
    else 
    {
        o_assert(p_unnamed_class_declaration);
        a_ClassScope = &p_unnamed_class_declaration->m_class_scope;
        return "__unamed_"+phantom::lexical_cast<string>((void*)p_unnamed_class_declaration);
    }
}

void             precompiler::precompile_class_scope(class_scope & cd, int a_iAccessQualifier, Class* a_pClass)
{
    vector<Class*> classes;
    for(auto it = cd.m_class_inheritances.begin(); it != cd.m_class_inheritances.end(); ++it)
    {
        LanguageElement* pQualifiedName = precompile_qualified_name_recursive(it->m_qualified_name, nullptr, false, a_pClass); 
        Class* pSuperClass = pQualifiedName->asClass();
        if(pSuperClass == nullptr) 
        {
            error(node_location(it->m_qualified_name), "Super type '%s' is not a class", node_string(it->m_qualified_name));
            continue;
        }
        if(NOT(pSuperClass->isDefined())) 
        {
            error(node_location(it->m_qualified_name), "Use of undefined class '%s'", pSuperClass->getQualifiedDecoratedName());
            continue;
        }
        a_pClass->addSuperClass(pSuperClass);
    }
    for(auto it = cd.m_class_member_declarations.begin(); it != cd.m_class_member_declarations.end(); ++it)
    {
        precompile_class_member_declaration(*it, a_iAccessQualifier, a_pClass);
    }
}

void             precompiler::precompile_class_member_declaration(class_member_declaration & cmd, int& a_iAccessQualifier, Class* a_pClass)
{
    member_declaration* p_member_declaration = 0;
    class_declaration* p_class_declaration = 0;
    typedef_declaration* p_typedef_declaration = 0;
    fundamental_node<int>* p_access_qualifier = 0;
    class_member_declaration_visitor cmdv(&p_member_declaration, &p_class_declaration, &p_typedef_declaration, &p_access_qualifier);
    cmd.apply_visitor(cmdv);
    if(p_member_declaration)
    {
        precompile_member_declaration(*p_member_declaration, a_iAccessQualifier, a_pClass);
    }
    else if(p_class_declaration)
    {
        precompile_nested_class_declaration(*p_class_declaration, a_iAccessQualifier, a_pClass);
    }
    else if(p_typedef_declaration)
    {
        // precompile_nested_typedef_declaration(*p_typedef_declaration, a_iAccessQualifier, a_pClass);
    }
    else 
    {
        o_assert(p_access_qualifier);
        a_iAccessQualifier = *p_access_qualifier;
    }
}

Signature*    precompiler::precompile_signature(type& return_type, parameters& params, LanguageElement* a_pScope)
{
    Signature* pSignature = o_new(Signature);
    Type* pReturnType = precompile_type_recursive(return_type, a_pScope);
    if(pReturnType == nullptr)
    {
        error(node_location(return_type), "Cannot solve return type '%s'", node_string(return_type));
    }
    else if(NOT(pReturnType->isDefined()))
    {
        error(node_location(return_type), "Use of undefined type '%s'", pReturnType->getQualifiedDecoratedName());
    }
    pSignature->setReturnType(pReturnType);

    for(size_t i = 0; i<params.size(); ++i)
    {
        parameter& param = params[i];
        Type* pParameterType = precompile_type_recursive(param.m_type, a_pScope);
        if(pParameterType == nullptr)
        {
            error(node_location(param.m_type), "Cannot solve parameter %i type '%s'", i+1, node_string(param.m_type));
        }
        else if(NOT(pParameterType->isDefined()))
        {
            error(node_location(param.m_type), "Use of undefined type '%s'", pParameterType->getQualifiedDecoratedName());
        }
        pSignature->addParameterType(pParameterType);
    }
    return pSignature;
}

void    precompiler::precompile_parameters_local_variables(parameters& params, Signature* a_pSignature, Block* a_pBlock)
{
    for(size_t i = 0 
        ; i < params.size()
        ; ++i)
    {
        parameter& param = params[i];
        if(!param.m_declarator.is_initialized()) continue;
        string_node& name = (*param.m_declarator).m_identifier;
        if(a_pBlock->getLocalVariable(name) != nullptr)
        {
            error(node_location(name), "Parameter name '%s' already used", node_string(name).c_str());
            a_pBlock->setInvalid();
            continue;
        }
        LocalVariable* pLocalVariable = o_new(LocalVariable)(a_pSignature->getParameterType(i), name);
        a_pBlock->addLocalVariable(pLocalVariable);
    }
}

void    precompiler::precompile_member_declaration(member_declaration& md, int a_Modifiers, Class* a_pClass)
{
    ambiguous_member_declaration*          p_ambiguous_member_declaration = 0;
    virtual_member_function_declaration*   p_virtual_member_function_declaration = 0;
    static_ambiguous_member_declaration*   p_static_ambiguous_member_declaration = 0;
    member_declaration_visitor mdv(&p_ambiguous_member_declaration, &p_virtual_member_function_declaration, &p_static_ambiguous_member_declaration);
    md.apply_visitor(mdv);
    if(p_ambiguous_member_declaration)
    {
        if(p_ambiguous_member_declaration->m_signature_and_block.is_initialized())
        {
            ambiguous_member_declaration_signature_and_block& signature_and_block = *(p_ambiguous_member_declaration->m_signature_and_block);
            Signature* pSignature = precompile_signature(p_ambiguous_member_declaration->m_type, signature_and_block.m_signature.m_parameters, a_pClass);
            InstanceMemberFunction* pInstanceMemberFunction = o_new(InstanceMemberFunction)(p_ambiguous_member_declaration->m_identifier, pSignature, (signature_and_block.m_signature.m_const.is_initialized() * o_const)|a_Modifiers);
            a_pClass->addInstanceMemberFunction(pInstanceMemberFunction);
            if(signature_and_block.m_block.is_initialized())
            {
                // block => definition
                // Create root block
                Block* pBlock = o_new(Block);
                pInstanceMemberFunction->setBlock(pBlock);
                const CodeLocation& location = node_location(md);
                pInstanceMemberFunction->setCodeLocation(location);
                pBlock->setCodeLocation(location);
                CodeLocation thisLocation(location.getStart(), location.getStart());
                CodePosition position(location.getStart());
                position.column+=1;
                thisLocation.setEnd(position);

                reflection::Type* pThisType = pInstanceMemberFunction->testModifiers(o_const) 
                                    ? pInstanceMemberFunction->getOwnerClassType()->constType()->pointerType()->constType()
                                    : pInstanceMemberFunction->getOwnerClassType()->pointerType()->constType();

                pBlock->addLocalVariable(o_new(LocalVariable)(pThisType, "this"));
                precompile_parameters_local_variables(signature_and_block.m_signature.m_parameters, pSignature, pBlock);
                precompile_block(*signature_and_block.m_block, pBlock);
            }
        }
        else 
        {
            Type* pType = precompile_type_recursive(p_ambiguous_member_declaration->m_type, a_pClass);
            InstanceDataMember* pInstanceDataMember = o_new(InstanceDataMember)(p_ambiguous_member_declaration->m_identifier, pType, nullptr, ~size_t(0), a_Modifiers);
            a_pClass->addInstanceDataMember(pInstanceDataMember);
        }
    }
    else if(p_virtual_member_function_declaration)
    {
        Signature* pSignature = precompile_signature(p_virtual_member_function_declaration->m_return_type, p_virtual_member_function_declaration->m_signature.m_parameters, a_pClass);
        InstanceMemberFunction* pInstanceMemberFunction = o_new(InstanceMemberFunction)(p_virtual_member_function_declaration->m_identifier
                                                                                , pSignature
                                                                                , (p_virtual_member_function_declaration->m_signature.m_const.is_initialized() * o_const)|a_Modifiers|(p_virtual_member_function_declaration->m_abstract.is_initialized() ? o_abstract : o_virtual));
        a_pClass->addInstanceMemberFunction(pInstanceMemberFunction);
        if(p_virtual_member_function_declaration->m_block.is_initialized())
        {
            // block => definition
            // Create root block
            Block* pBlock = o_new(Block);
            pInstanceMemberFunction->setBlock(pBlock);
            const CodeLocation& location = node_location(md);
            pInstanceMemberFunction->setCodeLocation(location);
            pBlock->setCodeLocation(location);
            CodeLocation thisLocation(location.getStart(), location.getStart());
            CodePosition position(location.getStart());
            position.column+=1;
            thisLocation.setEnd(position);

            reflection::Type* pThisType = pInstanceMemberFunction->testModifiers(o_const) 
                                ? pInstanceMemberFunction->getOwnerClassType()->constType()->pointerType()->constType()
                                : pInstanceMemberFunction->getOwnerClassType()->pointerType()->constType();

            pBlock->addLocalVariable(o_new(LocalVariable)(pThisType, "this"));
            precompile_parameters_local_variables(p_virtual_member_function_declaration->m_signature.m_parameters, pSignature, pBlock);
            precompile_block(*(p_virtual_member_function_declaration->m_block), pBlock);
        }
    }
    else 
    {
        o_assert(p_static_ambiguous_member_declaration);
        if(p_static_ambiguous_member_declaration->m_signature_and_block.is_initialized())
        {
            static_ambiguous_member_declaration_signature_and_block& signature_and_block = *(p_static_ambiguous_member_declaration->m_signature_and_block);
            Signature* pSignature = precompile_signature(p_static_ambiguous_member_declaration->m_type, signature_and_block.m_signature.m_parameters, a_pClass);
            StaticMemberFunction* pStaticMemberFunction = o_new(StaticMemberFunction)(p_static_ambiguous_member_declaration->m_identifier, pSignature, a_Modifiers);
            a_pClass->addStaticMemberFunction(pStaticMemberFunction);
            if(signature_and_block.m_block.is_initialized())
            {
                // block => definition
                // Create root block
                Block* pBlock = o_new(Block);
                pStaticMemberFunction->setBlock(pBlock);
                const CodeLocation& location = node_location(md);
                pStaticMemberFunction->setCodeLocation(location);
                pBlock->setCodeLocation(location);
                precompile_parameters_local_variables(signature_and_block.m_signature.m_parameters, pSignature, pBlock);
                precompile_block(*signature_and_block.m_block, pBlock);
            }
        }
        else 
        {
            Type* pType = precompile_type_recursive(p_static_ambiguous_member_declaration->m_type, a_pClass);
            StaticDataMember* pStaticDataMember = o_new(StaticDataMember)(p_static_ambiguous_member_declaration->m_identifier, pType, nullptr, a_Modifiers);
            a_pClass->addStaticDataMember(pStaticDataMember);
        }
    }
}

o_namespace_end(phantom, reflection, cpp, ast)