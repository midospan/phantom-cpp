/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/Template.h>
#include <phantom/reflection/Template.hxx>
#include <phantom/reflection/Placeholder.h>
/* *********************************************** */
o_registerN((phantom, reflection), Template);

o_namespace_begin(phantom, reflection) 

    o_define_meta_type(Template);

Template::Template(modifiers_t a_Modifiers /*= 0*/)
    : NamedElement("", a_Modifiers|o_always_valid) /// templates are considered always valid because if any error is found in their declaration, 
    , m_pTemplateSignature(nullptr)                /// it's of interest of their empty specialization (it avoids contaminate every specialization if one happens to be invalid)
{

}

Template::Template( TemplateSignature* a_pSignature, const string& a_strName, modifiers_t a_Modifiers /*= 0*/ )
    : NamedElement(a_strName, a_Modifiers|o_always_valid)
    , m_pTemplateSignature(a_pSignature)
{
    createEmptyTemplateSpecialization();
}

Template::Template(const string& a_strTemplateTypes, const string& a_strTemplateParam, const string& a_strName, modifiers_t a_Modifiers /*= 0*/)
    : NamedElement(a_strName, a_Modifiers|o_always_valid)
    , m_pTemplateSignature(o_new(TemplateSignature)(a_strTemplateTypes, a_strTemplateParam))
{
    o_assert(isNative());
    createEmptyTemplateSpecialization();
}

Template::~Template()
{

}

size_t Template::getTemplateParameterIndex( const string& a_strName ) const
{
    return m_pTemplateSignature->getParameterIndex(a_strName);
}

size_t Template::getTemplateParameterIndex( TemplateParameter* a_pTemplateParameter ) const
{
    return m_pTemplateSignature->getParameterIndex(a_pTemplateParameter);
}

LanguageElement* Template::getDefaultArgument(const string& a_strParameterName) const 
{
    return m_pTemplateSignature->getDefaultArgument(a_strParameterName);
}

LanguageElement* Template::getDefaultArgument(size_t i) const 
{
    return m_pTemplateSignature->getDefaultArgument(i);
}

void Template::setDefaultArgument( const string& a_strParameterName, LanguageElement* a_pElement )
{
    m_pTemplateSignature->setDefaultArgument(a_strParameterName, a_pElement);
}

size_t Template::getDefaultArgumentCount() const
{
    return m_pTemplateSignature->getDefaultArgumentCount();
}

void Template::addTemplateParameter( TemplateParameter* a_pTemplateParameter )
{
    m_pTemplateSignature->addParameter(a_pTemplateParameter);
}

void Template::addTemplateParameterAliasName( size_t a_uiIndex, const string& a_strAlias )
{
    m_pTemplateSignature->addParameterAliasName(a_uiIndex, a_strAlias);
}

size_t Template::getTemplateParameterCount() const
{
    return m_pTemplateSignature->getParameterCount();
}

vector<TemplateParameter*>::const_iterator Template::beginTemplateParameters() const
{
    return m_pTemplateSignature->beginParameters();
}

vector<TemplateParameter*>::const_iterator Template::endTemplateParameters() const
{
    return m_pTemplateSignature->endParameters();
}

void Template::createEmptyTemplateSpecialization()
{
    o_new(TemplateSpecialization)(this, m_pTemplateSignature, m_pTemplateSignature->getPlaceholders());
}

TemplateSpecialization* Template::createEmptyTemplateSpecialization( NamedElement* a_pBody )
{
    o_assert(a_pBody AND !isNative());
    TemplateSpecialization* pSpec = o_new(TemplateSpecialization)(this, m_pTemplateSignature, m_pTemplateSignature->getPlaceholders(), a_pBody);
    return pSpec;
}

TemplateSpecialization* Template::getTemplateSpecialization(TemplateSpecialization* a_pTemplateSpecialization ) const 
{
    for(auto it = m_TemplateSpecializations.begin(); it != m_TemplateSpecializations.end(); ++it)
    {
        if((*it)->equals(a_pTemplateSpecialization)) return *it;
    }
    return nullptr;
}

TemplateSpecialization* Template::getTemplateSpecialization( const vector<LanguageElement*>& arguments ) const
{
    for(auto it = m_TemplateSpecializations.begin(); it != m_TemplateSpecializations.end(); ++it)
    {
        if((*it)->matches(arguments)) return *it;
    }
    return nullptr;
}

TemplateSpecialization* Template::getTemplateSpecialization( const map<Placeholder*, LanguageElement*>& arguments ) const
{
    vector<LanguageElement*> contiguous;
    contiguous.resize(arguments.size());
    for(auto it = arguments.begin(); it != arguments.end(); ++it)
    {
        contiguous[static_cast<TemplateParameter*>(it->first->asNamedElement()->getOwner())->getIndex()] = it->second;
    }
    return getTemplateSpecialization(contiguous);
}

void Template::addSpecialization( TemplateSpecialization* a_pTemplateSpecialization )
{
    o_assert(a_pTemplateSpecialization AND a_pTemplateSpecialization->getTemplate() == this);
//  if(getTemplateSpecialization(a_pTemplateSpecialization))
//  {
//      a_pTemplateSpecialization->setInvalid();
//  }
    if(getTemplateSpecialization(a_pTemplateSpecialization->getArguments()))
    {
        a_pTemplateSpecialization->setInvalid();
    }
    if(m_pNamespace) /// template specialization belongs so same namespace as their template (even if they can belong to different owners)
    {
        o_assert(a_pTemplateSpecialization->getNamespace() == nullptr);
        m_pNamespace->addTemplateSpecialization(a_pTemplateSpecialization);
    }
    m_TemplateSpecializations.push_back(a_pTemplateSpecialization);
    addReferencedElement(a_pTemplateSpecialization);
}

TemplateSpecialization*  Template::createTemplateSpecialization( const vector<LanguageElement*>& arguments, ClassType* a_pTemplated, TemplateSignature* a_pTemplateSignature )
{
    TemplateSpecialization* pSpec = o_new(TemplateSpecialization)(this, a_pTemplateSignature, arguments, a_pTemplated);
    return pSpec;
}

void Template::ancestorChanged( LanguageElement* a_pOwner )
{
    if(a_pOwner == m_pOwner)
    {
        if(m_TemplateSpecializations.size())
        {
            if(m_pNamespace) m_pNamespace->addTemplateSpecialization(m_TemplateSpecializations[0]);
            m_pOwner->asScope()->addTemplateSpecialization(m_TemplateSpecializations[0]);
        }
    }
}

bool Template::acceptsArguments( const vector<LanguageElement*>& a_Arguments ) const
{
    return m_pTemplateSignature->acceptsArguments(a_Arguments);
}

bool Template::mapArguments( const vector<LanguageElement*>& a_Arguments, map<Placeholder*, LanguageElement*>& a_Out ) const
{
    size_t i = 0;
    size_t count = m_pTemplateSignature->getParameterCount();
    for(;i<count; ++i)
    {
        if(i<a_Arguments.size())
        {
            a_Out[m_pTemplateSignature->getParameter(i)->getPlaceholder()] = a_Arguments[i];
        }
        else 
        { 
            a_Out[m_pTemplateSignature->getParameter(i)->getPlaceholder()] = getDefaultArgument(i);
        }
    }
    return true;
}

o_namespace_end(phantom, reflection)