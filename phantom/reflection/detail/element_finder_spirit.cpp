
#include "phantom/phantom.h"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/repository/include/qi_distinct.hpp>

#include "element_finder_spirit.h"

using boost::spirit::repository::qi::distinct;

o_namespace_begin(phantom, reflection, detail)

namespace ast {


struct modifier
{
    modifier() : value(0) {}
    modifier(uint v) : value(v) {}
    operator uint()
    {
        return value;
    }
    uint value;
};

struct name;
struct element;
struct type;

typedef boost::variant<boost::recursive_wrapper<type>, long long> template_element;

struct name
{
    string                      m_identifier;
    vector<template_element>    m_template_specialization;
};

typedef vector<name> qualified_name;

typedef boost::variant<size_t, boost::optional<qualified_name>> type_extent;
typedef boost::variant<char, type_extent> qualifier_or_extent;
typedef std::vector<qualifier_or_extent> qualifier_or_extents;

struct type
{
    modifier                    m_const_modifier;
    qualified_name              m_qualified_name;
    qualifier_or_extents        m_qualifiers;

    void* operator new(size_t size)
    {
        return o_allocate(type);
    }
    void operator delete(void* ptr)
    {
        o_deallocate(static_cast<type*>(ptr), type);
    }
    void* operator new(size_t size, void* ptr_)
    {
        return ptr_;
    }
    void operator delete(void* ptr, void* ptr_)
    {
    }
};
struct function_prototype
{
    vector<type>                m_function_signature;
    modifier                    m_modifiers;
};

typedef boost::variant<qualifier_or_extents, function_prototype> function_or_type_qualifiers;

struct element
{
    modifier                    m_const_modifier;
    qualified_name              m_qualified_name;
    function_or_type_qualifiers m_func_or_type;
};


class common_visitor : public boost::static_visitor<>
{
protected:
    common_visitor(LanguageElement* a_pScope)
        : m_pScope(a_pScope)
    {

    }
    LanguageElement* m_pScope;
};

LanguageElement*  solve_element(string const& str, reflection::LanguageElement* a_pScope, template_specialization const* ts)
{
    LanguageElement* pSolvedElement = a_pScope->getElement(
        str.c_str()
        , ts
        , NULL
        , 0
        );
    return pSolvedElement;
}

LanguageElement* solve_element_recursive( string const& str, LanguageElement* a_pRootScope, template_specialization const* ts = NULL)
{
    LanguageElement* pRootElement = a_pRootScope;
    LanguageElement* pSolvedElement = NULL;
    while(pRootElement)
    {
        pSolvedElement = solve_element(str, pRootElement, ts);
        if(pSolvedElement != NULL) return pSolvedElement;
        pRootElement = pRootElement->getOwner();
    }
    return pSolvedElement;
}


Type*   solve_type(LanguageElement* a_pScope, type& t);

class function_or_qualifier_or_extents_visitor
    : public boost::static_visitor<>
{
public:
    function_or_qualifier_or_extents_visitor(function_prototype** a_ppFuncProto, qualifier_or_extents** a_ppstrQualifierOrExtents)
        : m_ppstrQualifierOrExtents(a_ppstrQualifierOrExtents)
        , m_ppFuncProto(a_ppFuncProto) {}

    void operator()(qualifier_or_extents & str) const // if we go here, it's a type
    {
        *m_ppstrQualifierOrExtents = &str;
    }

    void operator()(function_prototype& fp) const // if we go here, it's a function
    {
        *m_ppFuncProto = &fp;
    }

    function_prototype**    m_ppFuncProto;
    qualifier_or_extents**  m_ppstrQualifierOrExtents;
};


class qualifier_or_extent_visitor
    : public boost::static_visitor<>
{
public:
    qualifier_or_extent_visitor(char** a_ppQualifiers, type_extent** a_ppExtents)
        : m_ppQualifiers(a_ppQualifiers)
        , m_ppExtents(a_ppExtents) {}

    void operator()(char & str) const // if we go here, it's a qualifier
    {
        *m_ppQualifiers = &str;
    }

    void operator()(type_extent& fp) const // if we go here, it's an extent
    {
        *m_ppExtents = &fp;
    }

    type_extent**    m_ppExtents;
    char**  m_ppQualifiers;
};


class type_extent_visitor
    : public boost::static_visitor<>
{
public:
    type_extent_visitor(size_t** a_pSize, qualified_name** a_pEnumName)
        : m_pSize(a_pSize)
        , m_pEnumName(a_pEnumName) {}

    void operator()(size_t & str) const // if we go here, it's a qualifier
    {
        *m_pSize = &str;
    }

    void operator()(boost::optional<qualified_name>& fp) const // if we go here, it's an extent
    {
        qualified_name& q = *fp;
        *m_pEnumName = &q;
    }

    size_t**    m_pSize;
    qualified_name**  m_pEnumName;
};

class template_element_visitor : public common_visitor
{
public:
    template_element_visitor(LanguageElement* a_pScope, TemplateElement** a_ppResultElement)
        : common_visitor(a_pScope)
        , m_ppResultElement(a_ppResultElement)
    {
    }

    void operator()(type& t) const
    {
        Type* pType = solve_type(m_pScope, t);
        *m_ppResultElement = pType;
    }
    void operator()(boost::recursive_wrapper<type>& t) const
    {
        Type* pType = solve_type(m_pScope, t.get());
        *m_ppResultElement = pType;
    }
    void operator()(long long& ic) const
    {
        *m_ppResultElement = NULL;
    }

protected:
    TemplateElement** m_ppResultElement;

};



Type*   solve_type_qualifiers(LanguageElement* a_pScope, Type* a_pType, const qualifier_or_extents& qoes)
{
    for(auto it = qoes.begin(); it != qoes.end(); ++it)
    {
        qualifier_or_extent qe = *it;
        char*  pQualifier = NULL;
        type_extent* pTypeExtent = NULL;
        qualifier_or_extent_visitor qoev(&pQualifier, &pTypeExtent);
        qe.apply_visitor(qoev);
        if(pQualifier)
        {
            switch(*pQualifier)
            {
            case 'µ': // const
                a_pType = a_pType->constType();
                break;
            case '&': // ref
                a_pType = a_pType->referenceType();
                break;
            case '*': // pointer
                a_pType = a_pType->pointerType();
                break;
            }
        }
        else 
        {
            o_assert(pTypeExtent);
            size_t* pSize = 0;
            qualified_name* pQualifiedName = 0;
            type_extent_visitor tev(&pSize, &pQualifiedName);
            pTypeExtent->apply_visitor(tev);
            if(pSize)
            {
                if(*pSize == 0) return nullptr; // array cannot have 0 size
                a_pType = a_pType->arrayType(*pSize);
            }
            else 
            {
                reflection::LanguageElement* pEnumScope = a_pScope;
                o_assert(pQualifiedName);
                auto it = pQualifiedName->begin();
                auto end = pQualifiedName->end();
                for(;it!=end;++it)
                {
                    pEnumScope = solve_element(it->m_identifier, pEnumScope, 0);
                    if(pEnumScope == nullptr) return nullptr;
                }
                reflection::Constant* pConstant = pEnumScope->asConstant();
                size_t size = 0;
                pConstant->getValue(&size);
                if(size == 0) return nullptr;
                a_pType = a_pType->arrayType(size); 
            }
        }
    }
    return a_pType;
}


Type*   solve_type(LanguageElement* a_pScope, type& t)
{
    Type* pType = NULL;
    LanguageElement* pScope = a_pScope;
    // Test first in local scope
    qualified_name& q_name = t.m_qualified_name;
    if(q_name.empty()) return NULL;

    // We extract the most significant word
    qualified_name::iterator it = q_name.begin();
    qualified_name::iterator end = q_name.end();
    for(;it!=end;++it)
    {
        template_specialization ts;

        vector<template_element>::iterator it2 = it->m_template_specialization.begin();
        vector<template_element>::iterator end2 = it->m_template_specialization.end();
        for(;it2!=end2;++it2)
        {
            TemplateElement* pType = NULL;
            template_element_visitor v(a_pScope, &pType);
            (*it2).apply_visitor(v);
            if(pType == NULL)
            {
                return NULL;
            }
            ts.push_back(pType);
        }

        pScope = solve_element_recursive(it->m_identifier, pScope, &ts);

        if(pScope != NULL AND pScope->asType())
        {
            pType = static_cast<Type*>(pScope);
        }
    }
    if(pType == NULL) return NULL;
    qualifier_or_extents qualifiers = t.m_qualifiers;
    if(t.m_const_modifier)
    {
        // add const
        qualifiers.insert(qualifiers.begin(), 'µ');
    }
    return solve_type_qualifiers(a_pScope, pType, qualifiers);
}



LanguageElement* solve_element(LanguageElement* a_pScope, element & e)
{
    // name
    LanguageElement* pScope = a_pScope;
    bool bNameFullySolved = true;

    qualified_name& q_name = e.m_qualified_name;
    if(q_name.empty())
        return NULL;

    qualified_name::iterator it = q_name.begin();
    qualified_name::iterator end = q_name.end();
    for(;it!=end;++it)
    {
        // Each name inside the qualified name is treated and has potentially
        // a template specialization if it's a class type
        template_specialization ts;

        vector<template_element>::iterator it2 = it->m_template_specialization.begin();
        vector<template_element>::iterator end2 = it->m_template_specialization.end();
        for(;it2!=end2;++it2)
        {
            TemplateElement* pType = NULL;
            template_element_visitor v(a_pScope, &pType);
            (*it2).apply_visitor(v);
            if(pType == NULL)
            {
                return NULL;
            }
            ts.push_back(pType);
        }
        LanguageElement* pChildScope = solve_element_recursive(it->m_identifier, pScope, &ts);
        if(pChildScope == NULL)
        {
            bNameFullySolved = false;
            break;
        }
        pScope = pChildScope;
    }

    function_prototype*  pFuncProto = NULL;
    qualifier_or_extents* pQualifierOrExtents = NULL;
    function_or_qualifier_or_extents_visitor fotv(&pFuncProto, &pQualifierOrExtents);
    e.m_func_or_type.apply_visitor(fotv);

    // name has been completely solved, which means that we have either a namespace/type/member
    if(bNameFullySolved)
    {
        // we are supposed to have qualifiers in all cases (boost::variant mecanism)
        o_assert(pQualifierOrExtents != NULL);
        qualifier_or_extents qoes = *pQualifierOrExtents;
        if(e.m_const_modifier)
        {
            qoes.insert(qoes.begin(), 'µ'); // insert the beginning const in the list
        }
        reflection::Type* pType = pScope->asType();
        if(pType)
        {
            pType = solve_type_qualifiers(a_pScope, pType, qoes);
            return pType;
        }
        else if(qoes.size())
        {
            // namespace or member should not have qualifiers
            return NULL;
        }
        
    }

    // not fully solved, we try again with functions
    // but only if only one name haven't been solved yet
    // which means that it can be a function
    // otherwise it's a type or namespace that couldn't have been solved in the previous step
    if(e.m_qualified_name.end()-1 != it OR pFuncProto == NULL) return NULL;

    function_signature fs;
    {
        vector<type>::iterator it = (*pFuncProto).m_function_signature.begin();
        vector<type>::iterator end = (*pFuncProto).m_function_signature.end();
        for(;it!=end;++it)
        {
            Type* pType = solve_type(pScope, *it);
            if(pType == NULL)
            {
                return NULL;
            }
            fs.push_back(pType);
        }
    }

    // we take the last element and try to solve it
    return pScope->getElement(e.m_qualified_name.back().m_identifier.c_str()
        , NULL // template member_function not supported ... yet ?
        , &fs
        , (*pFuncProto).m_modifiers.value);
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
(phantom::vector<phantom::reflection::detail::ast::template_element>, m_template_specialization)
);

BOOST_FUSION_ADAPT_STRUCT(
phantom::reflection::detail::ast::modifier,
(phantom::uint, value)
);

BOOST_FUSION_ADAPT_STRUCT(
    phantom::reflection::detail::ast::type,
    (phantom::reflection::detail::ast::modifier, m_const_modifier)
(phantom::reflection::detail::ast::qualified_name, m_qualified_name)
(phantom::reflection::detail::ast::qualifier_or_extents, m_qualifiers)
);

BOOST_FUSION_ADAPT_STRUCT(
    phantom::reflection::detail::ast::element,
(phantom::reflection::detail::ast::modifier, m_const_modifier)
(phantom::reflection::detail::ast::qualified_name, m_qualified_name)
(phantom::reflection::detail::ast::function_or_type_qualifiers, m_func_or_type)
);

BOOST_FUSION_ADAPT_STRUCT(
    phantom::reflection::detail::ast::function_prototype,
    (phantom::vector<phantom::reflection::detail::ast::type>, m_function_signature)
    (phantom::reflection::detail::ast::modifier, m_modifiers)
);

o_namespace_begin(phantom, reflection, detail)




using namespace ::boost::spirit;


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
void compound_type_parsed (ast::type const& e) {}
//template<typename t_Iterator>
class element_spirit_parser : public boost::spirit::qi::grammar<
    phantom::string::const_iterator
    , ast::element()
    , boost::spirit::ascii::space_type>
{
public:
    typedef phantom::string::const_iterator t_Iterator;
    typedef boost::spirit::qi::grammar<
        t_Iterator
        , ast::element()
        , boost::spirit::ascii::space_type> super_type;

    element_spirit_parser()
        : super_type(r_element)
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

        r_type %= -(r_const_qualifier) >> r_qualified_name >> r_type_qualifier_or_extents_opt;

        r_type_qualifier_or_extents_opt %= *r_type_qualifier_or_extent;
        r_type_qualifier_or_extents %= +r_type_qualifier_or_extent;

        r_type_extent %= '[' >> (qi::uint_|r_qualified_name) >> ']';

        r_type_qualifier_or_extent %= r_type_qualifier|r_type_extent;

        r_type_qualifier %= (qi::char_('*')
                            |qi::char_('&')
                            |qi_keyword["const"] [qi::_val = 'µ'] )
                            ;

        r_template_element_list %= r_template_element //[ &append_template_element ]
                                    % ',';

        r_template_element %= r_type [qi::_val = qi::_1] //[ &template_element_is_a_type ]
            | r_integral_constant   //[ &template_element_is_an_int_const ]
            ;

        r_template_specialization %= '<' >> r_template_element_list >> '>';
        r_function_signature %= '(' >> -r_type_list >> ')' ;
        r_const_qualifier %= qi_keyword["const"] [qi::_val = o_const];
        r_type_list %= r_type //[ &append_type ]
                        % ',';

        r_function_prototype %= r_function_signature [&function_signature_parsed]
            >> -r_const_qualifier;

        r_element %= -(r_const_qualifier) >> r_qualified_name >> -(r_type_qualifier_or_extents | r_function_prototype);

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
    qi::rule<t_Iterator, ast::qualifier_or_extents(), ascii::space_type >   r_type_qualifier_or_extents;
    qi::rule<t_Iterator, ast::qualifier_or_extents(), ascii::space_type >   r_type_qualifier_or_extents_opt;
    qi::rule<t_Iterator, char(), ascii::space_type >                        r_type_qualifier;
    qi::rule<t_Iterator, ast::type_extent(), ascii::space_type >            r_type_extent;
    qi::rule<t_Iterator, char(), ascii::space_type >                        r_compound_id;
    qi::rule<t_Iterator, ast::element(), ascii::space_type >                r_element;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >             r_identifier;
    qi::rule<t_Iterator, phantom::string(), ascii::space_type >             r_operator_name;
    qi::rule<t_Iterator, ast::template_element(),ascii::space_type>         r_template_element;
    qi::rule<t_Iterator, vector<ast::template_element>(),ascii::space_type> r_template_element_list;
    qi::rule<t_Iterator, long long(), ascii::space_type>                    r_integral_constant;
    qi::rule<t_Iterator, ast::modifier(), ascii::space_type>                r_const_qualifier;
    qi::rule<t_Iterator, ast::name(), ascii::space_type>                    r_name;
    qi::rule<t_Iterator, ast::qualified_name(), ascii::space_type>          r_qualified_name;
    qi::rule<t_Iterator, ast::type(), ascii::space_type>                    r_type;
    //qi::rule<t_Iterator, ast::compound_type(), ascii::space_type>           r_compound_type;
    qi::rule<t_Iterator, vector<ast::type>(), ascii::space_type>            r_type_list;
    qi::rule<t_Iterator, vector<ast::type>(), ascii::space_type>            r_function_signature;
    qi::rule<t_Iterator, ast::qualifier_or_extent(), ascii::space_type>     r_type_qualifier_or_extent;
    qi::rule<t_Iterator, ast::function_prototype(), ascii::space_type>      r_function_prototype;
    qi::rule<t_Iterator, vector<ast::template_element>(),ascii::space_type> r_template_specialization;

};

element_finder_spirit::element_finder_spirit()
{

}

LanguageElement* element_finder_spirit::find( const string& a_strQualifiedName, LanguageElement* a_pRootScope /*= phantom::rootNamespace()*/ )
{
    element_spirit_parser g;
    ast::element    result;

    bool r = boost::spirit::qi::phrase_parse(a_strQualifiedName.begin(), a_strQualifiedName.end(), g, boost::spirit::ascii::space, result);

    LanguageElement* pResultElement = ast::solve_element(a_pRootScope, result);

    return pResultElement;//result
}


o_namespace_end(phantom, reflection, detail)
