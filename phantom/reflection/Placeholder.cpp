/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/Placeholder.h>
#include <phantom/reflection/Placeholder.hxx>
#include <phantom/reflection/ConstantExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), Placeholder);
o_registerN((phantom, reflection), PlaceholderType);
o_registerN((phantom, reflection), PlaceholderClassType);
o_registerN((phantom, reflection), PlaceholderClass);
o_registerN((phantom, reflection), PlaceholderConstant);
o_registerN((phantom, reflection), TemplateDependantArrayType);
o_registerN((phantom, reflection), TemplateDependantTemplateInstance);
o_registerN((phantom, reflection), TemplateDependantElement);
o_registerN((phantom, reflection), TemplateDependantExpression);
o_registerN((phantom, reflection), TemplateDependantType);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(PlaceholderType);
o_define_meta_type(PlaceholderConstant);

Constant* PlaceholderConstant::clone() const
{
    o_assert_no_implementation();
    return nullptr;
}

bool PlaceholderConstant::accepts( LanguageElement* a_pLanguageElement ) const
{
    return a_pLanguageElement->asConstant() != nullptr OR a_pLanguageElement->asExpression() AND a_pLanguageElement->asExpression()->asConstantExpression();
}

bool PlaceholderConstant::equals( LanguageElement* a_pOther ) const
{
    if(Constant::equals(a_pOther)) return true;
    Placeholder* pPH = a_pOther->asPlaceholder();
    PlaceholderConstant* pPHC = pPH ? pPH->asPlaceholderConstant() : nullptr;
    return pPHC AND pPHC->m_pType->equals(m_pType);
}

string TemplateDependantArrayType::getQualifiedDecoratedName() const
{
    return getItemType()->getQualifiedDecoratedName()+"["+m_pItemCountExpression->translate()+"]";
}

string TemplateDependantArrayType::getDecoratedName() const
{
    return getItemType()->getDecoratedName()+"["+m_pItemCountExpression->translate()+"]";
}

bool TemplateDependantArrayType::equals( LanguageElement* a_pOther ) const
{
    Placeholder* pPH = a_pOther->asPlaceholder();
    TemplateDependantArrayType* pTDAT = pPH ? pPH->asTemplateDependantArrayType() : nullptr;
    if(pTDAT == nullptr) return false;
    Precompiler* pPrecompiler = getLanguage()->createPrecompiler(nullptr);
    return pTDAT AND pTDAT->m_pItemCountExpression->equals(m_pItemCountExpression);
}

Class* PlaceholderType::asClass() const
{
    if(m_pAsClass == nullptr)
    {
        m_pAsClass = o_new(PlaceholderClass)((PlaceholderType*)this);
        ((PlaceholderType*)this)->addElement(m_pAsClass);
    }
    return m_pAsClass;
}

ClassType* PlaceholderType::asClassType() const
{
    if(m_pAsClassType == nullptr)
    {
        m_pAsClassType = o_new(PlaceholderClassType)((PlaceholderType*)this);
        ((PlaceholderType*)this)->addElement(m_pAsClassType);
    }
    return m_pAsClassType;
}

bool PlaceholderTemplate::accepts( LanguageElement* a_pLanguageElement ) const
{
    ClassType* pClassType = a_pLanguageElement->asClassType();
    return pClassType AND m_pTemplateSignature->acceptsArguments(pClassType->getTemplateSpecialization()->getArguments());
}

TemplateDependantTemplateInstance::TemplateDependantTemplateInstance( TemplateSpecialization* a_pTemplateSpecialization, const map<Placeholder*, LanguageElement*>& a_Arguments ) 
    : ClassType(e_template_dependant, (a_pTemplateSpecialization AND a_pTemplateSpecialization->getTemplate()) ? a_pTemplateSpecialization->getTemplate()->getName() : "", 0, 0, o_template_dependant) 
    , m_pTemplate(a_pTemplateSpecialization ? a_pTemplateSpecialization->getTemplate() : nullptr)
    , m_pTemplateSpecialization(a_pTemplateSpecialization)
    , m_Arguments(a_Arguments)
{
    if(m_pTemplate)
    {
        addReferencedElement(m_pTemplate);
    } 
    else setInvalid();
    if(m_pTemplateSpecialization)
    {
        addReferencedElement(m_pTemplateSpecialization);
    }
    for(auto it = m_Arguments.begin(); it != m_Arguments.end(); ++it)
    {
        addReferencedElement(it->second);
    }
}

TemplateDependantTemplateInstance::TemplateDependantTemplateInstance( Template* a_pTemplate, const map<Placeholder*, LanguageElement*>& a_Arguments ) 
    : ClassType(e_template_dependant, a_pTemplate->getName(), 0, 0, o_template_dependant) 
    , m_pTemplate(a_pTemplate)
    , m_Arguments(a_Arguments)
    , m_pTemplateSpecialization(nullptr)
{
    addReferencedElement(a_pTemplate);
    for(auto it = m_Arguments.begin(); it != m_Arguments.end(); ++it)
    {
        addReferencedElement(it->second);
    }
}

TemplateDependantTemplateInstance::TemplateDependantTemplateInstance( Template* a_pTemplate, const vector<LanguageElement*>& a_Arguments )
    : ClassType(e_template_dependant, a_pTemplate->getName(), 0, 0, o_template_dependant) 
    , m_pTemplate(a_pTemplate)
    , m_pTemplateSpecialization(nullptr)
{
    for(size_t i=0;i<a_Arguments.size();++i)
    {
        m_Arguments[a_pTemplate->getTemplateSignature()->getParameter(i)->getPlaceholder()] = a_Arguments[i];
    }
}

bool TemplateDependantTemplateInstance::equals( LanguageElement* a_pOther ) const
{
    if(Type::equals(a_pOther)) return true;
    Placeholder* pPH = a_pOther->asPlaceholder();
    TemplateDependantTemplateInstance* pTDTI = pPH ? pPH->asTemplateDependantTemplateInstance() : nullptr;
    if(pTDTI == nullptr OR NOT(pTDTI->m_pTemplate->equals(m_pTemplate))) return false;
    size_t count = m_Arguments.size();
    if(count != pTDTI->m_Arguments.size()) return false;
    for(auto it = m_Arguments.begin(); it != m_Arguments.end(); ++it)
    {
        if(NOT((it->second)->equals(pTDTI->m_Arguments[it->first])))
            return false;
    }
    return true;
}

LanguageElement* TemplateDependantTemplateInstance::getArgument( Placeholder* a_pPlaceholder ) const
{
    auto found = m_Arguments.find(a_pPlaceholder);
    return found == m_Arguments.end() ? nullptr : found->second;
}

Type* TemplateDependantElement::asType() const
{
    if(m_pAsType == nullptr)
    {
        m_pAsType = o_new(TemplateDependantType)((TemplateDependantElement*)this);
        ((TemplateDependantElement*)this)->addElement(m_pAsType);
    }
    return m_pAsType;
}

Expression* TemplateDependantElement::asExpression() const
{
    return o_new(TemplateDependantExpression)((TemplateDependantElement*)this);
}

TemplateDependantDotExpression::TemplateDependantDotExpression( Expression* a_pElement, const string& a_strName, const vector<LanguageElement*>* a_pTemplate /*= nullptr*/, const vector<Expression*>* a_pArguments /*= nullptr*/ ) 
    : Expression(o_new(TemplateDependantType)) 
    , m_strName(a_strName)
    , m_pTemplate(a_pTemplate ? new vector<LanguageElement*>(*a_pTemplate) : nullptr)
    , m_pArguments(a_pArguments ? new vector<Expression*>(*a_pArguments) : nullptr)
{

}

TemplateDependantExpression::TemplateDependantExpression( TemplateDependantElement* a_pElement ) 
    : Expression(o_new(TemplateDependantType))
    , m_strName(a_pElement->getName())
{

}

o_namespace_end(phantom, reflection)


