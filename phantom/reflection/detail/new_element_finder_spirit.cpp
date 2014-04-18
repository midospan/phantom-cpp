
#include "phantom/phantom.h"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/repository/include/qi_distinct.hpp>
#include "phantom/reflection/DataExpression.h"

#include "element_finder_spirit.h"

using boost::spirit::repository::qi::distinct;

namespace phantom { namespace reflection { class LanguageElement; class TemplateElement; } }

o_namespace_begin(phantom, reflection, detail)

namespace ast {

struct expression;
struct element;
struct name;

LanguageElement* solve_expression(expression& e, LanguageElement* a_pScope);
LanguageElement* solve_element(LanguageElement* a_pLHS, element & e, LanguageElement* a_pScope);
LanguageElement* solve_element_recursive(element & e, LanguageElement* a_pScope);


typedef boost::recursive_wrapper<element> template_element;

struct name
{
    string                      m_identifier;
    boost::optional<vector<template_element>> m_template_signature;
};

typedef vector<name> qualified_name;

struct extent_or_signature
{
    extent_or_signature() : m_opening('('), m_closing(')') {}
    extent_or_signature(const phantom::vector<boost::recursive_wrapper<expression>>& list) : m_opening('('), m_list(list), m_closing(')') {}
    extent_or_signature(const expression& exp)
        : m_opening('[')
        , m_closing(']') { m_list.push_back(exp); }

    char m_opening;
    phantom::vector<boost::recursive_wrapper<expression>> m_list;
    char m_closing;
};

typedef boost::variant<char, extent_or_signature> qualifier_or_extent_or_signature;

typedef phantom::vector<qualifier_or_extent_or_signature> qualifier_or_extent_or_signatures;

class qualifier_or_extent_or_signature_visitor
    : public boost::static_visitor<>
{
public:
    qualifier_or_extent_or_signature_visitor(char** a_ppQualifiers, extent_or_signature** a_ppExtents)
        : m_ppQualifiers(a_ppQualifiers)
        , m_ppExtents(a_ppExtents) {}

    void operator()(char & str) const // if we go here, it's a qualifier
    {
        *m_ppQualifiers = &str;
    }

    void operator()(extent_or_signature& fp) const // if we go here, it's an extent
    {
        *m_ppExtents = &fp;
    }

    extent_or_signature**    m_ppExtents;
    char**  m_ppQualifiers;
};

struct function_prototype
{
    extent_or_signature         m_signature;
    boost::optional<char>       m_const_modifier;
};

struct qualifier_and_qualifier_or_extents
{
    char m_qualifier;
    qualifier_or_extent_or_signatures m_qualifier_or_extents;
};



typedef phantom::vector<extent_or_signature> extent_or_signatures;

typedef boost::variant<qualifier_and_qualifier_or_extents, extent_or_signatures>  qualifier_and_qualifier_or_extents_OR_extent_or_signatures;

struct extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_signatures 
{
    extent_or_signature m_extent;
    qualifier_and_qualifier_or_extents_OR_extent_or_signatures m_qualifier_and_qualifier_or_extents_OR_extent_or_signatures;
};

class qualifier_and_qualifier_or_extents_OR_extent_or_signatures_visitor
    : public boost::static_visitor<>
{
public:
    qualifier_and_qualifier_or_extents_OR_extent_or_signatures_visitor(qualifier_and_qualifier_or_extents** a_pp_qualifier_and_qualifier_or_extents
        , extent_or_signatures** a_pp_extent_or_function_signatures)
        : m_pp_qualifier_and_qualifier_or_extents(a_pp_qualifier_and_qualifier_or_extents)
        , m_pp_extent_or_function_signatures(a_pp_extent_or_function_signatures) {}

    void operator()(qualifier_and_qualifier_or_extents & arg) const
    {
        *m_pp_qualifier_and_qualifier_or_extents = &arg;
    }

    void operator()(extent_or_signatures& arg) const
    {
        *m_pp_extent_or_function_signatures = &arg;
    }

protected:
    qualifier_and_qualifier_or_extents**      m_pp_qualifier_and_qualifier_or_extents;
    extent_or_signatures**   m_pp_extent_or_function_signatures;
};

typedef boost::variant<qualifier_and_qualifier_or_extents
                    , extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_signatures
                    , function_prototype> element_extension;

class element_extension_visitor
    : public boost::static_visitor<>
{
public:
    element_extension_visitor(qualifier_and_qualifier_or_extents** a_pp_qualifier_and_qualifier_or_extents
                            , extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_signatures** a_pp_extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_function_signatures
                            , function_prototype** a_pp_function_prototype)
        : m_pp_qualifier_and_qualifier_or_extents(a_pp_qualifier_and_qualifier_or_extents)
        , m_pp_extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_function_signatures(a_pp_extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_function_signatures)
        , m_pp_function_prototype(a_pp_function_prototype) {}

    void operator()(qualifier_and_qualifier_or_extents & arg) const
    {
        *m_pp_qualifier_and_qualifier_or_extents = &arg;
    }

    void operator()(extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_signatures& arg) const
    {
        *m_pp_extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_function_signatures = &arg;
    }

    void operator()(function_prototype& arg) const 
    {
        *m_pp_function_prototype = &arg;
    }

protected:
    qualifier_and_qualifier_or_extents**      m_pp_qualifier_and_qualifier_or_extents;
    extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_signatures**   m_pp_extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_function_signatures;
    function_prototype**   m_pp_function_prototype;
};


struct element
{
    boost::optional<char>               m_const_modifier;
    qualified_name                      m_qualified_name;
    boost::optional<element_extension>  m_element_extension;
};

struct data
{
    size_t m_guid;
};
struct address
{
    size_t m_value;
};

typedef boost::variant<element, data, address> data_or_address_or_element;

struct expression
{
    data_or_address_or_element m_root;
    phantom::vector<element> m_elements;
};

class data_or_address_or_element_visitor
    : public boost::static_visitor<>
{
public:
    data_or_address_or_element_visitor(element** a_ppElement, data** a_ppData, address** a_ppAddress)
        : m_ppElement(a_ppElement)
        , m_ppData(a_ppData)
        , m_ppAddress(a_ppAddress) {}

    void operator()(element & e) const // if we go here, it's an element
    {
        *m_ppElement = &e;
    }

    void operator()(data& d) const // if we go here, it's a data
    {
        *m_ppData = &d;
    }

    void operator()(address& a) const // if we go here, it's an address
    {
        *m_ppAddress = &a;
    }

protected:
    data**      m_ppData;
    address**   m_ppAddress;
    element**   m_ppElement;
};

LanguageElement*  solve_element(const string& a_strName, const vector<TemplateElement*>* a_pTemplateSignature, const vector<LanguageElement*>* a_pFunctionSignature, bool a_bConstSignature, reflection::LanguageElement* a_pScope)
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
/*

LanguageElement* solve_element_recursive( const string& a_strName, LanguageElement* a_pRootScope, const vector<TemplateElement*>* a_TemplateSignature)
{
    LanguageElement* pRootElement = a_pRootScope;
    LanguageElement* pSolvedElement = NULL;
    while(pRootElement)
    {
        pSolvedElement = solve_element(str, pRootElement, a_TemplateSignature);
        if(pSolvedElement != NULL) return pSolvedElement;
        pRootElement = pRootElement->getOwner();
    }
    return pSolvedElement;
}*/

Type*   solve_type_qualifier(Type* a_pType, char qualifier)
{
    switch(qualifier)
    {
    case 'µ': // const
        return a_pType->constType();
    case '&': // ref
        return a_pType->referenceType();
    case '*': // pointer
        return a_pType->pointerType();
    }
    return nullptr;
}

struct element_garbage
{
    void add(LanguageElement* a_pElement)
    {
        if(a_pElement)
        m_elements.push_back(a_pElement);
    }

    ~element_garbage()
    {
        for(auto it = m_elements.begin(); it != m_elements.end(); ++it)
        {
            if((*it)->getModule() == nullptr && (*it)->getOwner() == nullptr) // if not in a module or not in another element we can delete it
            {
                o_dynamic_delete *it;
            }
        }
    }

    void clear() { m_elements.clear(); }

    vector<LanguageElement*> m_elements;
};

void solve_element_extension(element_extension & ee, qualifier_or_extent_or_signatures& extensions, bool* a_pConstSignature)
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

bool solve_function_signature(extent_or_signature& fs, vector<LanguageElement*>& out, LanguageElement* a_pScope)
{
    element_garbage garbage;
    LanguageElement* pFirstSignatureElement = nullptr;
    auto it = fs.m_list.begin();
    auto end = fs.m_list.end();
    for(;it!=end;++it)
    {
        LanguageElement* pElement = solve_expression(it->get(), a_pScope);
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

bool solve_template_signature(vector<template_element>& ts, vector<TemplateElement*>& out, LanguageElement* a_pScope)
{
    element_garbage garbage;
    auto it = ts.begin();
    auto end = ts.end();
    for(;it!=end;++it)
    {
        LanguageElement* pTemplateSignatureElement = solve_element_recursive(it->get(), a_pScope);
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

LanguageElement* solve_name(LanguageElement* a_pLHS, name& n, const vector<LanguageElement*>* a_pFunctionSignature, bool a_bConst, LanguageElement* a_pScope)
{
    element_garbage garbage;
    LanguageElement* pElement = nullptr;
    if(n.m_template_signature.is_initialized()) // has template signature
    {
        vector<TemplateElement*> templateSignature;
        if(NOT(solve_template_signature(*n.m_template_signature, templateSignature, a_pScope)))
            return nullptr;
        pElement = solve_element(n.m_identifier, &templateSignature, a_pFunctionSignature, a_bConst, a_pLHS);
        garbage.add(pElement);
    }
    else
    {
        pElement = solve_element(n.m_identifier, nullptr, a_pFunctionSignature, a_bConst, a_pLHS);
        garbage.add(pElement);
    }
    if(pElement == nullptr)
        return nullptr;
    garbage.clear();
    return pElement;
}

LanguageElement* solve_element(LanguageElement* a_pLHS, element & e, LanguageElement* a_pScope)
{
    element_garbage garbage;
    // name
    LanguageElement* pLHS = a_pLHS;
    bool bNameFullySolved = true;

    qualified_name& q_name = e.m_qualified_name;
    if(q_name.empty())
        return nullptr;
    
    auto it = q_name.begin();
    auto end = q_name.end()-1;
    for(;it!=end;++it)
    {
        // Each name inside the qualified name is treated and has potentially
        // a template specialization if it's a class type

        LanguageElement* pElement = solve_name(pLHS, *it, nullptr, false, a_pScope);
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
        solve_element_extension(*e.m_element_extension, fseqs, &bConstSignature);
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
            LanguageElement* pElement = solve_name(pLHS, last_name, nullptr, false, a_pScope);
            garbage.add(pElement);
            if(pElement == nullptr)
                return nullptr;
            Type* pType = pElement->asType();
            if(pType == nullptr)
                return nullptr;
            pType = solve_type_qualifier(pType, *p_qualifier);
            garbage.add(pType);
            if(pType == nullptr)
                return nullptr;
            pLHS = pType;
        }
        else if(p_extent_or_signature->m_opening == '(')
        {
            vector<LanguageElement*> functionSignature;
            if(NOT(solve_function_signature(*p_extent_or_signature, functionSignature, a_pScope)))
            {
                return nullptr;
            }
            LanguageElement* pElement = solve_name(pLHS, last_name, &functionSignature, bConstSignature, a_pScope);
            if(pElement == nullptr)
                return nullptr;
            pLHS = pElement;
        }
        else if(p_extent_or_signature->m_opening == '[')
        {
            if(p_extent_or_signature->m_list.size() != 1) 
                return nullptr;
            LanguageElement* pElement = solve_name(pLHS, last_name, nullptr, false, a_pScope);
            garbage.add(pElement);
            if(pElement == nullptr)
                return nullptr;
            LanguageElement* pExtentElement = solve_expression(p_extent_or_signature->m_list.back().get(), a_pScope);
            garbage.add(pExtentElement);
            if(pExtentElement == nullptr)
                return nullptr;
            Expression* pExtentExpression = pExtentElement->asExpression();
            if(pExtentExpression == nullptr)
                return nullptr;
            pElement = pElement->solveBracketOperator(pExtentExpression);
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
                pType = solve_type_qualifier(pType, *p_qualifier);
                garbage.add(pType);
                if(pType == nullptr)
                    return nullptr;
                pLHS = pType;
            }
            else if(p_extent_or_signature->m_opening == '(')
            {
                vector<LanguageElement*> functionSignature;
                if(NOT(solve_function_signature(*p_extent_or_signature, functionSignature, a_pScope)))
                {
                    return nullptr;
                }
                LanguageElement* pElement = pLHS->solveParenthesisOperator(functionSignature);
                garbage.add(pElement);
                if(pElement == nullptr)
                    return nullptr;
                pLHS = pElement;
            }
            else if(p_extent_or_signature->m_opening == '[')
            {
                if(p_extent_or_signature->m_list.size() != 1) 
                    return nullptr;
                LanguageElement* pExtentElement = solve_expression(p_extent_or_signature->m_list.back().get(), a_pScope);
                garbage.add(pExtentElement);
                if(pExtentElement == nullptr)
                    return nullptr;
                Expression* pExtentExpression = pExtentElement->asExpression();
                if(pExtentExpression == nullptr)
                    return nullptr;
                LanguageElement* pElement = pLHS->solveBracketOperator(pExtentExpression);
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
        LanguageElement* pElement = solve_name(pLHS, last_name, nullptr, false, a_pScope);
        garbage.add(pElement);
        if(pElement == nullptr)
            return nullptr;
        pLHS = pElement;
    }

    garbage.clear();

    return pLHS;
}

LanguageElement* solve_element_recursive(element & e, LanguageElement* a_pScope)
{
    LanguageElement* pScope = a_pScope;
    LanguageElement* pResult = nullptr;
    while(pResult == nullptr && pScope)
    {
        pResult = solve_element(pScope, e, a_pScope);
        pScope = pScope->getOwner();
    }
    return pResult;
}

LanguageElement* solve_expression(expression& e, LanguageElement* a_pScope)
{
    element_garbage garbage;
    element* pElement = nullptr;
    data*   pData = nullptr;
    address*pAddress = nullptr;
    data_or_address_or_element_visitor dae(&pElement, &pData, &pAddress);
    e.m_root.apply_visitor(dae);

    LanguageElement* pLHS = nullptr;

    if(pElement)
    {
        pLHS = solve_element_recursive(*pElement, a_pScope);
        garbage.add(pLHS);
        if(pLHS == nullptr) return nullptr;
    }
    else if(pData)
    {
        pLHS = o_new(DataExpression)(pData->m_guid);
        garbage.add(pLHS);
    } 
    else if(pAddress)
    {
        if(pAddress->m_value == 0)
            return nullptr;
        if(classOf((void*)pAddress->m_value) == nullptr) 
            return nullptr;
        pLHS = o_new(StaticVariable)((void*)pAddress->m_value);
        garbage.add(pLHS);
    }
    else return nullptr;

    auto it = e.m_elements.begin();
    auto end = e.m_elements.end();
    for(;it!=end;++it)
    {
        element& elem = *it;
        LanguageElement* pElement = solve_element(pLHS, elem, a_pScope);
        garbage.add(pElement);
        if(pElement == nullptr) 
            return nullptr;
        pLHS = pElement;
    }
    garbage.clear();
    return pLHS;
}


};

o_namespace_end(phantom, reflection, detail)

/*
BOOST_FUSION_ADAPT_STRUCT(
phantom::reflection::detail::ast::compound_type,
(boost::recursive_wrapper<phantom::reflection::detail::ast::type>, m_internal_type)
(char, m_typeid)
);*/


BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::detail::ast::name ,
(phantom::string, m_identifier)
(boost::optional<phantom::vector<phantom::reflection::detail::ast::template_element>>, m_template_signature)
);

BOOST_FUSION_ADAPT_STRUCT(
    phantom::reflection::detail::ast::element,
(boost::optional<char>, m_const_modifier)
(phantom::reflection::detail::ast::qualified_name, m_qualified_name)
(boost::optional<phantom::reflection::detail::ast::element_extension>, m_element_extension)
);

BOOST_FUSION_ADAPT_STRUCT(
    phantom::reflection::detail::ast::function_prototype,
    (phantom::reflection::detail::ast::extent_or_signature, m_signature)
    (boost::optional<char>, m_const_modifier)
);

BOOST_FUSION_ADAPT_STRUCT(
    phantom::reflection::detail::ast::extent_or_signature,
    (char, m_opening)
    (phantom::vector<boost::recursive_wrapper<phantom::reflection::detail::ast::expression>>, m_list)
    (char, m_closing)
);

BOOST_FUSION_ADAPT_STRUCT(phantom::reflection::detail::ast::expression ,
    (phantom::reflection::detail::ast::data_or_address_or_element, m_root)
    (phantom::vector<phantom::reflection::detail::ast::element>, m_elements)
    );

BOOST_FUSION_ADAPT_STRUCT(
    phantom::reflection::detail::ast::data,
    (size_t, m_guid)
    );

BOOST_FUSION_ADAPT_STRUCT(
    phantom::reflection::detail::ast::address,
    (size_t, m_value)
    );

BOOST_FUSION_ADAPT_STRUCT(
    phantom::reflection::detail::ast::qualifier_and_qualifier_or_extents,
    (char, m_qualifier)
    (phantom::reflection::detail::ast::qualifier_or_extent_or_signatures, m_qualifier_or_extents)
);

BOOST_FUSION_ADAPT_STRUCT(
    phantom::reflection::detail::ast::extent_AND_qualifier_and_qualifier_or_extents_OR_extent_or_signatures ,
    (phantom::reflection::detail::ast::extent_or_signature, m_extent)
    (phantom::reflection::detail::ast::qualifier_and_qualifier_or_extents_OR_extent_or_signatures, m_qualifier_and_qualifier_or_extents_OR_extent_or_signatures)
);

o_namespace_begin(phantom, reflection, detail)




using namespace ::boost::spirit;

/*

void append_template_element(ast::template_element const& te) {}
void append_type(ast::type const& te) {}
void solve_name(ast::name const& te) {}
void append_to_name(string const& s) {}
void make_pointer(char const& s) {}
void make_reference(char const& s) {}
void function_signature_parsed(vector<ast::type> const& s) {}
void template_element_is_a_type(ast::type const& t) {}
void template_element_is_an_int_const(long long ic) {}
void element_parsed(ast::element const& e) {}
void compound_type_parsed (ast::type const& e) {}*/
//template<typename t_Iterator>
class element_spirit_parser : public boost::spirit::qi::grammar<
    phantom::string::const_iterator
    , ast::expression()
    , boost::spirit::ascii::space_type>
{
public:
    typedef phantom::string::const_iterator t_Iterator;
    typedef boost::spirit::qi::grammar<
        t_Iterator
        , ast::expression()
        , boost::spirit::ascii::space_type> super_type;

    element_spirit_parser()
        : super_type(r_expression)
    {
#define qi_keyword distinct(qi::char_("a-zA-Z_0-9"))
        r_identifier %= 
             r_unsigned_type [ qi::_val = qi::_1 ]
            | r_signed_type [ qi::_val = qi::_1 ]
            | r_long_type [ qi::_val = qi::_1 ]
            | ((lexeme[qi::char_("a-zA-Z_") >> *qi::char_("a-zA-Z_0-9")])-(qi_keyword["long"]|qi_keyword["unsigned"]|qi_keyword["signed"]|qi_keyword["const"]|qi_keyword["operator"]))
            ;

        r_unsigned_keyword = qi_keyword["unsigned"] [qi::_val = "unsigned"];
        r_operator_keyword = qi_keyword["operator"] [qi::_val = "operator"];

        r_operator =  qi::lit("==") [qi::_val = "=="]
                    | qi::lit("!=") [qi::_val = "!="]
                    | qi::lit("()") [qi::_val = "()"]
                    | qi::lit("[]") [qi::_val = "[]"]
                    | qi::lit("-" ) [qi::_val = "-" ]
                    | qi::lit("+" ) [qi::_val = "+" ]
                    | qi::lit("*" ) [qi::_val = "*" ]
                    | qi::lit("/" ) [qi::_val = "/" ]
                    | qi::lit("/=") [qi::_val = "/="]
                    | qi::lit("*=") [qi::_val = "*="]
                    | qi::lit("+=") [qi::_val = "+="]
                    | qi::lit("-=") [qi::_val = "-="]
        ;

        r_operator_name = r_operator_keyword [qi::_val = qi::_1] >> r_operator [qi::_val = qi::_val + qi::_1];

        r_long_keyword = qi_keyword["long"] [qi::_val = "long"];
        r_signed_keyword = qi_keyword["signed"] [qi::_val = "signed"];
        r_unsigned_type = r_unsigned_keyword [qi::_val = qi::_1] 
                        >> lexeme[(qi::char_("a-zA-Z_")[qi::_val = qi::_val + ' ' + qi::_1] 
                        >> *qi::char_("a-zA-Z_0-9")[qi::_val += qi::_1])]
                        >> -lexeme[(qi::char_("a-zA-Z_")[qi::_val = qi::_val + ' ' + qi::_1] 
                        >> *qi::char_("a-zA-Z_0-9")[qi::_val += qi::_1])];
        r_signed_type = r_signed_keyword [qi::_val = qi::_1] >> *(qi::char_("a-zA-Z_")[qi::_val = qi::_val + ' ' + qi::_1] >> *qi::char_("a-zA-Z_0-9")[qi::_val += qi::_1]) ;
        r_long_type = r_long_keyword [qi::_val = qi::_1] >> *(qi::char_("a-zA-Z_")[qi::_val = qi::_val + ' ' + qi::_1] >> *qi::char_("a-zA-Z_0-9")[qi::_val += qi::_1]) ;

        r_name %=  (r_identifier|r_operator_name) >> -r_template_specialization;

        r_qualified_name %= -lexeme["::"] >> r_name % lexeme["::"] ;


        r_type_qualifier %= (qi::char_('*')
                            |qi::char_('&')
                            |qi_keyword["const"] [qi::_val = 'µ'] )
                            ;

        r_template_element_list %= r_template_element //[ &append_template_element ]
                                    % ',';

        r_template_element %= r_element   //[ &template_element_is_an_int_const ]
            ;

        r_template_specialization %= '<' >> r_template_element_list >> '>';

        r_function_signature %= '(' >> -r_expression_list >> ')' ;

        r_const_qualifier %= qi_keyword["const"] [qi::_val = 'µ'];

        r_function_prototype %= r_function_signature >> -r_const_qualifier;

        r_qualifier_or_extent %= r_type_qualifier|r_extent;

        r_qualifier_or_extents %= *r_qualifier_or_extent;

        r_qualifier_and_qualifier_or_extents %= r_type_qualifier >> -r_qualifier_or_extents;

        r_extent %= '[' >> r_expression >> ']';

        r_extent_or_function_signature = r_extent|r_function_signature;

        r_extent_or_function_signatures %= *r_extent_or_function_signature;

        r_element_extension %= r_qualifier_and_qualifier_or_extents
                             | ( r_extent >> -( r_qualifier_and_qualifier_or_extents | r_extent_or_function_signatures ) )
                             | ( r_function_prototype );

        r_element %= -(r_const_qualifier) >> r_qualified_name >> -r_element_extension;
        
        r_data %= '@' >> qi::hex;

        r_member_access_expression %= r_expression % '.';

        r_normal_char = qi::char_() - ('"'|'\\');

        r_escape_char = '\\' >> qi::char_();

        r_string_literal = '"' >> lexeme[ *(r_normal_char | r_escape_char) ] >> '"';

        r_char_literal = '\'' >> (qi::char_ - '\'') >> '\'';

        r_literal %= r_string_literal | r_char_literal | qi::int_ | qi::long_long | qi::float_ | qi::double_ | qi::hex;

        r_grouped_or_cast_expression %= '(' >> r_expression >> ')' >> -(r_expression);

        r_dereference_expression %= '*' >> r_expression;

        r_reference_expression %= '&' >> r_expression;

        r_statement_expression %= r_reference_expression | r_dereference_expression | r_member_access_expression;

        r_expression %= r_data | r_literal | r_statement_expression | r_grouped_or_cast_expression;

        r_member_access_expression %= (r_expression '.' r_identifier) >> -(r_function_signature); 

        // From highest priority to lowest

        primary_expression%=                 literal
        |                               THIS
        |                               suffix_decl_specified_ids
    /*  |                               SCOPE identifier                                            -- covered by suffix_decl_specified_ids */
    /*  |                               SCOPE operator_function_id                                  -- covered by suffix_decl_specified_ids */
    /*  |                               SCOPE qualified_id                                          -- covered by suffix_decl_specified_ids */
        |                               abstract_expression               %prec REDUCE_HERE_MOSTLY  /* Prefer binary to unary ops, cast to call */
    /*  |                               id_expression                                               -- covered by suffix_decl_specified_ids */
    /*
     *  Abstract-expression covers the () and [] of abstract-declarators.
     */
    abstract_expression%=                parenthesis_clause
        |                               '[' expression.opt ']'
        |                               TEMPLATE abstract_expression

    /*  Type I function parameters are ambiguous with respect to the generalised name, so we have to do a lookahead following
     *  any function-like parentheses. This unfortunately hits normal code, so kill the -- lines and add the ++ lines for efficiency.
     *  Supporting Type I code under the superset causes perhaps 25% of lookahead parsing. Sometimes complete class definitions
     *  get traversed since they are valid generalised type I parameters!
     */
    type1_parameters%=       /*----*/    parameter_declaration_list ';'
        |                   /*----*/    type1_parameters parameter_declaration_list ';'
    mark_type1%=                         /* empty */                                             { mark_type1(); yyclearin; }
    postfix_expression%=                 primary_expression
    /*  |                   /++++++/    postfix_expression parenthesis_clause */
        |                   /*----*/    postfix_expression parenthesis_clause mark_type1 '-'
        |                   /*----*/    postfix_expression parenthesis_clause mark_type1 '+' type1_parameters mark '{' error 
                            /*----*/                    { yyerrok; yyclearin; remark_type1(); unmark(); unmark(); }
        |                   /*----*/    postfix_expression parenthesis_clause mark_type1 '+' type1_parameters mark error 
                            /*----*/                    { yyerrok; yyclearin; remark_type1(); unmark(); unmark(); }
        |                   /*----*/    postfix_expression parenthesis_clause mark_type1 '+' error
                            /*----*/                    { yyerrok; yyclearin; remark_type1(); unmark(); }
        |                               postfix_expression '[' expression.opt ']'
    /*  |                               destructor_id '[' expression.opt ']'                    -- not semantically valid */
    /*  |                               destructor_id parenthesis_clause                        -- omitted to resolve known ambiguity */
    /*  |                               simple_type_specifier '(' expression_list.opt ')'       -- simple_type_specifier is a primary_expression */
        |                               postfix_expression '.' declarator_id
    /*  |                               postfix_expression '.' TEMPLATE declarator_id           -- TEMPLATE absorbed into declarator_id. */
        |                               postfix_expression '.' scoped_pseudo_destructor_id
        |                               postfix_expression ARROW declarator_id
    /*  |                               postfix_expression ARROW TEMPLATE declarator_id         -- TEMPLATE absorbed into declarator_id. */
        |                               postfix_expression ARROW scoped_pseudo_destructor_id   
        |                               postfix_expression INC
        |                               postfix_expression DEC
        |                               DYNAMIC_CAST '<' type_id '>' '(' expression ')'
        |                               STATIC_CAST '<' type_id '>' '(' expression ')'
        |                               REINTERPRET_CAST '<' type_id '>' '(' expression ')'
        |                               CONST_CAST '<' type_id '>' '(' expression ')'
        |                               TYPEID parameters_clause
    /*  |                               TYPEID '(' expression ')'                               -- covered by parameters_clause */
    /*  |                               TYPEID '(' type_id ')'                                  -- covered by parameters_clause */
    expression_list.opt%=                /* empty */
        |                               expression_list
    expression_list%=                    assignment_expression
        |                               expression_list ',' assignment_expression

    unary_expression%=                   postfix_expression
        |                               INC cast_expression
        |                               DEC cast_expression
        |                               ptr_operator cast_expression
    /*  |                               '*' cast_expression                                     -- covered by ptr_operator */
    /*  |                               '&' cast_expression                                     -- covered by ptr_operator */
    /*  |                               decl_specifier_seq '*' cast_expression                  -- covered by binary operator */
    /*  |                               decl_specifier_seq '&' cast_expression                  -- covered by binary operator */
        |                               suffix_decl_specified_scope star_ptr_operator cast_expression   /* covers e.g int %=%=type%=%=* const t = 4 */

        |                               '+' cast_expression
        |                               '-' cast_expression
        |                               '!' cast_expression
        |                               '~' cast_expression
        |                               SIZEOF unary_expression
    /*  |                               SIZEOF '(' type_id ')'                                  -- covered by unary_expression */
        |                               new_expression
        |                               global_scope new_expression
        |                               delete_expression
        |                               global_scope delete_expression
    /*  |                               DELETE '[' ']' cast_expression       -- covered by DELETE cast_expression since cast_expression covers ... */
    /*  |                               SCOPE DELETE '[' ']' cast_expression //  ... abstract_expression cast_expression and so [] cast_expression */

    delete_expression%=                  DELETE cast_expression                                  /* also covers DELETE[] cast_expression */

    new_expression%=                     NEW new_type_id new_initializer.opt
        |                               NEW parameters_clause new_type_id new_initializer.opt
        |                               NEW parameters_clause
    /*  |                               NEW '(' type-id ')'                                     -- covered by parameters_clause */
        |                               NEW parameters_clause parameters_clause new_initializer.opt
    /*  |                               NEW '(' type-id ')' new_initializer                     -- covered by parameters_clause parameters_clause */
    /*  |                               NEW parameters_clause '(' type-id ')'                   -- covered by parameters_clause parameters_clause */
                                                                                    /* ptr_operator_seq.opt production reused to save a %prec */
    new_type_id%=                        type_specifier ptr_operator_seq.opt
        |                               type_specifier new_declarator
        |                               type_specifier new_type_id
    new_declarator%=                     ptr_operator new_declarator
        |                               direct_new_declarator
    direct_new_declarator%=              '[' expression ']'
        |                               direct_new_declarator '[' constant_expression ']'
    new_initializer.opt%=                /* empty */
        |                               '(' expression_list.opt ')'

    /*  cast-expression is generalised to support a [] as well as a () prefix. This covers the omission of DELETE[] which when
     *  followed by a parenthesised expression was ambiguous. It also covers the gcc indexed array initialisation for free.
     */
    cast_expression%=                    unary_expression
        |                               abstract_expression cast_expression
    /*  |                               '(' type_id ')' cast_expression                             -- covered by abstract_expression */

    pm_expression%=                      cast_expression
        |                               pm_expression DOT_STAR cast_expression
        |                               pm_expression ARROW_STAR cast_expression
    multiplicative_expression%=          pm_expression
        |                               multiplicative_expression star_ptr_operator pm_expression
        |                               multiplicative_expression '/' pm_expression
        |                               multiplicative_expression '%' pm_expression
    additive_expression%=                multiplicative_expression
        |                               additive_expression '+' multiplicative_expression
        |                               additive_expression '-' multiplicative_expression
    shift_expression%=                   additive_expression
        |                               shift_expression SHL additive_expression
        |                               shift_expression SHR additive_expression
    relational_expression%=              shift_expression
        |                               relational_expression '<' shift_expression
        |                               relational_expression '>' shift_expression
        |                               relational_expression LE shift_expression
        |                               relational_expression GE shift_expression
    equality_expression%=                relational_expression
        |                               equality_expression EQ relational_expression
        |                               equality_expression NE relational_expression
    and_expression%=                     equality_expression
        |                               and_expression '&' equality_expression
    exclusive_or_expression%=            and_expression
        |                               exclusive_or_expression '^' and_expression
    inclusive_or_expression%=            exclusive_or_expression
        |                               inclusive_or_expression '|' exclusive_or_expression
    logical_and_expression%=             inclusive_or_expression
        |                               logical_and_expression LOG_AND inclusive_or_expression
    logical_or_expression%=              logical_and_expression
        |                               logical_or_expression LOG_OR logical_and_expression
    conditional_expression%=             logical_or_expression
        |                               logical_or_expression '?' expression '%=' assignment_expression


    /*  assignment-expression is generalised to cover the simple assignment of a braced initializer in order to contribute to the
     *  coverage of parameter-declaration and init-declaration.
     */
    assignment_expression%=              conditional_expression
        |                               logical_or_expression assignment_operator assignment_expression
        |                               logical_or_expression '=' braced_initializer
        |                               throw_expression
    assignment_operator%=                '=' | ASS_ADD | ASS_AND | ASS_DIV | ASS_MOD | ASS_MUL | ASS_OR | ASS_SHL | ASS_SHR | ASS_SUB | ASS_XOR

    /*  expression is widely used and usually single-element, so the reductions are arranged so that a
     *  single-element expression is returned as is. Multi-element expressions are parsed as a list that
     *  may then behave polymorphically as an element or be compacted to an element. */ 
    expression.opt%=                     /* empty */
        |                               expression
    expression%=                         assignment_expression
        |                               expression_list ',' assignment_expression
    constant_expression%=                conditional_expression

    /*  The grammar is repeated for when the parser stack knows that the next > must end a template.
     */
    templated_relational_expression%=    shift_expression
        |                               templated_relational_expression '<' shift_expression
        |                               templated_relational_expression LE shift_expression
        |                               templated_relational_expression GE shift_expression
    templated_equality_expression%=      templated_relational_expression
        |                               templated_equality_expression EQ templated_relational_expression
        |                               templated_equality_expression NE templated_relational_expression
    templated_and_expression%=           templated_equality_expression
        |                               templated_and_expression '&' templated_equality_expression
    templated_exclusive_or_expression%=  templated_and_expression
        |                               templated_exclusive_or_expression '^' templated_and_expression

    templated_inclusive_or_expression%=  templated_exclusive_or_expression
        |                               templated_inclusive_or_expression '|' templated_exclusive_or_expression

    templated_logical_and_expression%=   templated_inclusive_or_expression
        |                               templated_logical_and_expression LOG_AND templated_inclusive_or_expression

    templated_logical_or_expression%=    templated_logical_and_expression
        |                               templated_logical_or_expression LOG_OR templated_logical_and_expression

    templated_conditional_expression%=   templated_logical_or_expression
        |                               templated_logical_or_expression '?' templated_expression '%=' templated_assignment_expression

    templated_assignment_expression%=    templated_conditional_expression
        |                               templated_logical_or_expression assignment_operator templated_assignment_expression

        |                               templated_throw_expression
    templated_expression%=               templated_assignment_expression
        |                               templated_expression_list ',' templated_assignment_expression

    templated_expression_list%=          templated_assignment_expression
        |                               templated_expression_list ',' templated_assignment_expression
    }

    // rules
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >             r_signed_keyword;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >             r_signed_type;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >             r_long_keyword;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >             r_long_type;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >             r_unsigned_keyword;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >             r_operator_keyword;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >             r_operator;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >             r_unsigned_type;
    qi::rule<t_Iterator, char(), ascii::space_type >                        r_type_qualifier;
    qi::rule<t_Iterator, char(), ascii::space_type >                        r_const_qualifier;
    qi::rule<t_Iterator, ast::extent_or_signature(), ascii::space_type >                 r_extent;
    qi::rule<t_Iterator, ast::qualifier_or_extent_or_signature(), ascii::space_type >    r_qualifier_or_extent;
    qi::rule<t_Iterator, ast::qualifier_or_extent_or_signatures(), ascii::space_type >   r_qualifier_or_extents;
    qi::rule<t_Iterator, ast::qualifier_and_qualifier_or_extents(), ascii::space_type >    r_qualifier_and_qualifier_or_extents;
    qi::rule<t_Iterator, ast::extent_or_signature(), ascii::space_type >    r_extent_or_function_signature;
    qi::rule<t_Iterator, ast::extent_or_signatures(), ascii::space_type >    r_extent_or_function_signatures;
    qi::rule<t_Iterator, char(), ascii::space_type >                        r_compound_id;
    qi::rule<t_Iterator, ast::element(), ascii::space_type >                r_element;
    qi::rule<t_Iterator, ast::element_extension(), ascii::space_type >      r_element_extension;

    qi::rule<t_Iterator, ast::expression(), ascii::space_type >             r_expression;
    qi::rule<t_Iterator, ast::expression(), ascii::space_type >             r_reference_expression;
    qi::rule<t_Iterator, ast::expression(), ascii::space_type >             r_dereference_expression;
    qi::rule<t_Iterator, ast::expression(), ascii::space_type >             r_statement_expression;
    qi::rule<t_Iterator, ast::expression(), ascii::space_type >             r_member_access_expression;
    qi::rule<t_Iterator, char(), ascii::space_type >                        r_normal_char;
    qi::rule<t_Iterator, char(), ascii::space_type >                        r_escape_char;
    qi::rule<t_Iterator, char(), ascii::space_type >                        r_char_literal;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >             r_string_literal;
    qi::rule<t_Iterator, ast::expression(), ascii::space_type >             r_literal;
    qi::rule<t_Iterator, ast::expression(), ascii::space_type >             r_literal;
    qi::rule<t_Iterator, ast::expression(), ascii::space_type >             r_literal;
    qi::rule<t_Iterator, ast::expression(), ascii::space_type >             r_grouped_or_cast_expression;

    qi::rule<t_Iterator, ast::data(), ascii::space_type >                   r_data;
    qi::rule<t_Iterator, ast::address(), ascii::space_type >                r_address;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >             r_identifier;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >             r_operator_name;
    qi::rule<t_Iterator, ast::template_element(),ascii::space_type>         r_template_element;
    qi::rule<t_Iterator, vector<ast::template_element>(),ascii::space_type> r_template_element_list;
    qi::rule<t_Iterator, long long(), ascii::space_type>                    r_integral_constant;
    qi::rule<t_Iterator, ast::name(), ascii::space_type>                    r_name;
    qi::rule<t_Iterator, ast::qualified_name(), ascii::space_type>          r_qualified_name;
    qi::rule<t_Iterator, phantom::vector<boost::recursive_wrapper<ast::expression>>(), ascii::space_type>      r_expression_list;
    qi::rule<t_Iterator, ast::extent_or_signature(), ascii::space_type>      r_function_signature;
    qi::rule<t_Iterator, ast::function_prototype(), ascii::space_type>      r_function_prototype;
    qi::rule<t_Iterator, vector<ast::template_element>(),ascii::space_type> r_template_specialization;

};

element_finder_spirit::element_finder_spirit()
{

}

LanguageElement* element_finder_spirit::find( const string& a_strQualifiedName, LanguageElement* a_pRootScope /*= phantom::rootNamespace()*/ )
{
    element_spirit_parser g;
    ast::expression    result;
    {
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
    }

    bool r = boost::spirit::qi::phrase_parse(a_strQualifiedName.begin(), a_strQualifiedName.end(), g, boost::spirit::ascii::space, result);

    LanguageElement* pResultElement = ast::solve_expression(result, a_pRootScope);

    return pResultElement;//result
}


o_namespace_end(phantom, reflection, detail)
