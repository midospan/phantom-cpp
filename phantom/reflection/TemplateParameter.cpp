/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "TemplateParameter.h"
#include "TemplateParameter.hxx"
#include "Expression.h"
#include "Placeholder.h"
#include "Block.h"
#include <phantom/vector.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), TemplateParameter);
o_registerNTI((phantom), vector, (phantom::reflection::TemplateParameter*));

o_namespace_begin(phantom, reflection) 

o_define_meta_type(TemplateParameter);

TemplateParameter::TemplateParameter()
    : m_pDefaultArgument(nullptr)
    , m_pPlaceholder(nullptr)
{

}

TemplateParameter::TemplateParameter( Placeholder* a_pPlaceholder, LanguageElement* a_pDefaultArgument, modifiers_t a_Modifiers /*= 0*/ ) 
    : NamedElement(a_pPlaceholder ? a_pPlaceholder->asNamedElement()->getName() : "", a_Modifiers)
    , m_pDefaultArgument(nullptr)
    , m_pPlaceholder(a_pPlaceholder)
{
    if(m_pPlaceholder)
    {
        addElement(m_pPlaceholder->asNamedElement());
    }
    else setInvalid();
    if(a_pDefaultArgument)
    {
        setDefaultArgument(a_pDefaultArgument);
    }
}

TemplateParameter* TemplateParameter::clone() const
{
    return o_new(TemplateParameter)(m_pPlaceholder, m_pDefaultArgument, m_Modifiers);
}

void TemplateParameter::elementRemoved( LanguageElement* a_pElement )
{
    if(m_pDefaultArgument == a_pElement)
        m_pDefaultArgument = nullptr;
    LanguageElement::elementRemoved(a_pElement);
}

void TemplateParameter::referencedElementRemoved( LanguageElement* a_pElement )
{
    if(m_pDefaultArgument == a_pElement)
        m_pDefaultArgument = nullptr;
    LanguageElement::referencedElementRemoved(a_pElement);
}

void TemplateParameter::setDefaultArgument( LanguageElement* a_pElement )
{
    if(a_pElement == nullptr)
        setInvalid();
    o_assert(a_pElement == nullptr OR m_pDefaultArgument == nullptr, "default argument already defined");
    m_pDefaultArgument = a_pElement;
    if(m_pDefaultArgument)
    {
        if(m_pDefaultArgument->getOwner())
            addReferencedElement(m_pDefaultArgument);
        else 
            addElement(m_pDefaultArgument);
    }
}

bool TemplateParameter::partialAccepts( LanguageElement* a_pLanguageElement, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_Deductions ) const
{
    return m_pPlaceholder->asNamedElement()->partialAccepts(a_pLanguageElement, a_Score, a_Deductions);
}

bool TemplateParameter::acceptsArgument( LanguageElement* a_pLanguageElement ) const
{
    return m_pPlaceholder->accepts(a_pLanguageElement);
}

bool TemplateParameter::equals( TemplateParameter* a_pOther ) const
{
    return a_pOther->m_pPlaceholder 
            AND m_pPlaceholder 
            AND a_pOther->m_pPlaceholder->asNamedElement()->equals(m_pPlaceholder->asNamedElement());
}

size_t TemplateParameter::getIndex() const
{
    return static_cast<TemplateSignature*>(m_pOwner)->getParameterIndex(const_cast<TemplateParameter*>(this));
}

o_namespace_end(phantom, reflection)