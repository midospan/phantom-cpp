
#include "phantom/phantom.h"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/repository/include/qi_distinct.hpp>

#include "element_finder_spirit.h"

using boost::spirit::repository::qi::distinct;

o_namespace_begin(phantom, reflection, detail)

namespace ast {

struct expression;
struct element;
struct name;


typedef boost::recursive_wrapper<element> template_element;

struct name
{
    string                      m_identifier;
    boost::optional<vector<template_element>> m_template_signature;
};

typedef vector<name> qualified_name;

struct extent_or_signature
{
    extent_or_signature() : m_opening(0), m_closing(0) {}
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
        LanguageElement* pTemplateSignatureElement = solve_element(a_pScope, it->get(), a_pScope);
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

        LanguageElement* pFirstElement = nullptr;

        if(p_qualifier)
        {
            pFirstElement = solve_name(pLHS, last_name, nullptr, false, a_pScope);
            garbage.add(pFirstElement);
            if(pFirstElement == nullptr)
                return nullptr;
            Type* pFirstType = pFirstElement->asType();
            if(pFirstType == nullptr)
                return nullptr;
            pFirstType = solve_type_qualifier(pFirstType, *p_qualifier);
            garbage.add(pFirstType);
            if(pFirstType == nullptr)
                return nullptr;
        }
        else if(p_extent_or_signature->m_opening == '(')
        {
            vector<LanguageElement*> functionSignature;
            if(NOT(solve_function_signature(*p_extent_or_signature, functionSignature, a_pScope)))
            {
                return nullptr;
            }
            pFirstElement = solve_name(pLHS, last_name, &functionSignature, bConstSignature, a_pScope);
            if(pFirstElement == nullptr)
                return nullptr;
        }
        else if(p_extent_or_signature->m_opening == '[')
        {
            if(p_extent_or_signature->m_list.size() != 1) 
                return nullptr;
            pFirstElement = solve_name(pLHS, last_name, nullptr, false, a_pScope);
            garbage.add(pFirstElement);
            if(pFirstElement == nullptr)
                return nullptr;
            LanguageElement* pExtentElement = solve_expression(p_extent_or_signature->m_list.back().get(), a_pScope);
            garbage.add(pExtentElement);
            if(pExtentElement == nullptr)
                return nullptr;
            Constant* pExtentConstant = pExtentElement->asConstant();
            if(pExtentConstant == nullptr)
                return nullptr;
            pFirstElement = pFirstElement->solveBracketOperator(pExtentConstant);
            garbage.add(pFirstElement);
            if(pFirstElement == nullptr)
                return nullptr;
        }

        pLHS = pFirstElement;

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
                Constant* pExtentConstant = pExtentElement->asConstant();
                if(pExtentConstant == nullptr)
                    return nullptr;
                LanguageElement* pElement = pLHS->solveBracketOperator(pExtentConstant);
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
        LanguageElement* pScope = a_pScope;
        while(pLHS == nullptr && pScope)
        {
            pLHS = solve_element(pScope, *pElement, a_pScope);
            pScope = pScope->getOwner();
        }
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

        r_qualifier_and_qualifier_or_extents %= r_type_qualifier >> r_qualifier_or_extents;

        r_extent %= '[' >> r_expression >> ']';

        r_extent_or_function_signature = r_extent|r_function_signature;

        r_extent_or_function_signatures %= *r_extent_or_function_signature;

        r_element_extension %= r_qualifier_and_qualifier_or_extents
                             | ( r_extent >> ( r_qualifier_and_qualifier_or_extents | r_extent_or_function_signatures ) )
                             | ( r_function_prototype );

        r_element %= -(r_const_qualifier) >> r_qualified_name >> -r_element_extension;
        
        r_data %= '@' >> qi::hex;

        r_address %= '&' >> qi::hex;

        r_expression %= (r_data | r_address | r_element) >> -(*('.' >> r_element));

        r_expression_list %= r_expression % ',';

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

    bool r = boost::spirit::qi::phrase_parse(a_strQualifiedName.begin(), a_strQualifiedName.end(), g, boost::spirit::ascii::space, result);

    LanguageElement* pResultElement = ast::solve_expression(result, a_pRootScope);

    return pResultElement;//result
}


o_namespace_end(phantom, reflection, detail)
