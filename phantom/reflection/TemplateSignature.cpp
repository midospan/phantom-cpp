/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/TemplateSignature.h>
#include <phantom/reflection/TemplateSignature.hxx>
#include <phantom/reflection/Placeholder.h>
#include <boost/algorithm/string.hpp>
/* *********************************************** */
o_registerN((phantom, reflection), TemplateSignature);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(TemplateSignature);

TemplateSignature::TemplateSignature()
{

}

TemplateSignature::TemplateSignature(size_t a_uiParameterCount)
{
    m_Parameters.resize(a_uiParameterCount);
}

TemplateSignature::TemplateSignature( const string& a_strTemplateTypes, const string& a_strTemplateParams )
{
    vector<Type*> templateTypes;
    vector<string> types;
    split( types, a_strTemplateTypes, boost::is_any_of(","), boost::token_compress_on );
    vector<string> names;
    split( names, a_strTemplateParams, boost::is_any_of(","), boost::token_compress_on );
    o_assert(types.size() == names.size());
    for(size_t i = 0; i<types.size(); ++i)
    {
        if(types[i].find("typename") != string::npos OR types[i].find("class") != string::npos)
        {
            boost::replace_all(types[i], " ", "");
            if(types[i] == "typename" OR types[i] == "class")
            {
                addParameter(o_new(TemplateParameter)(o_new(PlaceholderType)(names[i])));
                continue;
            }
            goto else_;
        }
        else 
        {
else_:
            Type* pType = typeByName(types[i], namespaceByName("phantom"));
            o_assert(pType AND pType->asIntegralType());
            addParameter(o_new(TemplateParameter)(o_new(PlaceholderConstant)(pType, names[i])));
        }
    }
}

TemplateSignature::TemplateSignature( const vector<TemplateParameter*>& a_Parameters )
{
    for(auto it = a_Parameters.begin(); it != a_Parameters.end(); ++it)
    {
        addParameter(*it);
    }
}

TemplateSignature::~TemplateSignature()
{

}

size_t TemplateSignature::getParameterIndex( const string& a_strName ) const
{
    for(size_t i = 0; i<m_Parameters.size(); ++i)
    {
        if(m_Parameters[i]->getName() == a_strName) return i;
    }
    auto found = m_ParameterAliasNames.find(a_strName);
    return found != m_ParameterAliasNames.end() ? found->second : ~size_t(0);
}

size_t TemplateSignature::getParameterIndex( TemplateParameter* a_pParameter ) const
{
    for(size_t i = 0; i<m_Parameters.size(); ++i)
    {
        if(m_Parameters[i] == a_pParameter) return i;
    }
    return ~size_t(0);
}

LanguageElement* TemplateSignature::getDefaultArgument(const string& a_strParameterName) const 
{
    size_t index = getParameterIndex(a_strParameterName);
    o_assert(index != ~size_t(0));
    return m_Parameters[index]->getDefaultArgument();
}

LanguageElement* TemplateSignature::getDefaultArgument( size_t i ) const
{
    return m_Parameters[i]->getDefaultArgument();
}

void TemplateSignature::setDefaultArgument( const string& a_strParameterName, LanguageElement* a_pElement )
{
    size_t index = getParameterIndex(a_strParameterName);
    o_assert(index != ~size_t(0));
    m_Parameters[index]->setDefaultArgument(a_pElement);
}

size_t TemplateSignature::getDefaultArgumentCount() const
{
    size_t i = 0;
    for(; i<m_Parameters.size(); ++i)
    {
        if(m_Parameters[i]->getDefaultArgument() == nullptr) return i;
    }
    return i;
}

void TemplateSignature::addParameter( TemplateParameter* a_pTemplateParameter )
{
    if(a_pTemplateParameter == nullptr OR getParameterIndex(a_pTemplateParameter->getName()) != ~size_t(0))
    {
        setInvalid();
    }
    if(a_pTemplateParameter)
    {
        addElement(a_pTemplateParameter);
    }
    m_Parameters.push_back(a_pTemplateParameter);
    NamedElement* pPH = (a_pTemplateParameter AND a_pTemplateParameter->getPlaceholder()) ? a_pTemplateParameter->getPlaceholder()->asNamedElement() : nullptr;
    m_Placeholders.push_back(pPH);
    if(pPH)
    {
        addReferencedElement(pPH);
    }
}

void TemplateSignature::addParameterAliasName( size_t a_uiIndex, const string& a_strAlias )
{
    size_t existingIndex = getParameterIndex(a_strAlias);
    if(existingIndex == ~size_t(0))
    {
        m_ParameterAliasNames[a_strAlias] = a_uiIndex;
    }
    else if(existingIndex != a_uiIndex)
    {
        o_exception(exception::reflection_runtime_exception, "parameter alias already used by another parameter");
    }
}

bool TemplateSignature::acceptsArguments( const vector<LanguageElement*>& a_Arguments ) const
{
    if(getParameterCount() != a_Arguments.size()) return false;
    for(size_t i = 0; i<m_Parameters.size(); ++i)
    {
        if(a_Arguments[i] == nullptr OR m_Parameters[i] == nullptr OR NOT(m_Parameters[i]->acceptsArgument(a_Arguments[i])))
            return false;
    }
    return true;
}

bool TemplateSignature::equals( TemplateSignature* a_pOther ) const
{
    size_t count = m_Parameters.size();
    if(count != a_pOther->m_Parameters.size()) 
        return false;
    for(size_t i = 0; i<count; ++i)
    {
        if(NOT(m_Parameters[i]->equals(a_pOther->m_Parameters[i]))) return false;
    }
    return true;
}

o_namespace_end(phantom, reflection)