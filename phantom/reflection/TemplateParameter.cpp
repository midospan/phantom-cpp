/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "TemplateParameter.h"
#include "TemplateParameter.hxx"
#include "Expression.h"
#include "Block.h"
#include <phantom/std/vector.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), TemplateParameter);
o_registerNTI((phantom), vector, (phantom::reflection::TemplateParameter*));

o_namespace_begin(phantom, reflection) 

o_define_meta_type(TemplateParameter);

TemplateParameter::TemplateParameter()
    , m_pElementType(nullptr)
    , m_pDefaultArgument(nullptr)
{

}

TemplateParameter::TemplateParameter( Type* a_pElementType, const string& a_strName, LanguageElement* a_pDefaultArgument, modifiers_t a_Modifiers /*= 0*/ ) 
    : LanguageElement(a_strName, a_Modifiers)
    , m_pElementType(a_pElementType)
    , m_pDefaultArgument(nullptr)
{
    if(m_pElementType)
    {
        addReferencedElement(m_pElementType);
    }
    else setInvalid();
    setDefaultArgument(a_pDefaultArgument);
}

TemplateParameter* TemplateParameter::clone() const
{
    return o_new(TemplateParameter)(m_pElementType, m_strName, m_pDefaultArgument, m_Modifiers);
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

o_namespace_end(phantom, reflection)