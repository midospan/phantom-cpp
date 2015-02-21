/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/TemplateSpecialization.h>
#include <phantom/reflection/TemplateSpecialization.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), TemplateSpecialization);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(TemplateSpecialization);

/// Full specialization constructor
TemplateSpecialization::TemplateSpecialization( Template* a_pTemplate, TemplateSignature* a_pSignature, const vector<LanguageElement*>& arguments, NamedElement* a_pBody )
    : NamedElement("", a_pTemplate->getModifiers()|o_private_visibility)
    , m_pTemplate(a_pTemplate)
    , m_pTemplateSignature(a_pSignature)
    , m_pBody(a_pBody)
    , m_pDefaultArguments(nullptr)
{
    if(a_pBody->getQualifiedDecoratedName() == "std::allocator< char >")
    {
        int i=0;
        ++i;
    }
    if(m_pBody)
    {
        if(m_pBody->isDefined())
            setDefined();
        addElement(m_pBody);
    }
    else setInvalid();
    if(m_pTemplateSignature)
    {
        addElement(m_pTemplateSignature);
    }
    else setInvalid();
    if(m_pTemplate)
    {
        if(m_pTemplate->isInvalid() OR !m_pTemplate->getTemplateSignature()->acceptsArguments(arguments))
        {
            setInvalid();
        }
        addReferencedElement(m_pTemplate);
        m_pTemplate->addSpecialization(this);
    }
    else setInvalid();
    m_Arguments.resize(arguments.size());
    for(size_t i=0; i<arguments.size();++i)
    {
        setArgument(i, arguments[i]);
    }
}

/// Partial specialization constructor
TemplateSpecialization::TemplateSpecialization( Template* a_pTemplate, TemplateSignature* a_pSignature, const vector<LanguageElement*>& arguments )
    : NamedElement("", a_pTemplate->getModifiers()|o_private_visibility)
    , m_pTemplateSignature(a_pSignature)
    , m_pTemplate(a_pTemplate)
    , m_pBody(nullptr)
    , m_pDefaultArguments(nullptr)
{
    if(m_pTemplateSignature)
    {
        addElement(m_pTemplateSignature);
    }
    else setInvalid();
    if(m_pTemplate)
    {
        if(!m_pTemplate->getTemplateSignature()->acceptsArguments(arguments))
        {
            setInvalid();
        }
        addReferencedElement(m_pTemplate);
        m_pTemplate->addSpecialization(this);
    }
    else setInvalid();
    m_Arguments.resize(arguments.size());
    for(size_t i=0; i<arguments.size();++i)
    {
        setArgument(i, arguments[i]);
    }
}

TemplateSpecialization::~TemplateSpecialization()
{
}

string TemplateSpecialization::getDecoration() const 
{
    string decoration = "< ";
    uint i = 0;
    uint count = m_Arguments.size();
    for(;i<count;++i)
    {
        LanguageElement*  pElement = m_Arguments[i];
        LanguageElement*  pLanguageElement = pElement->asLanguageElement();
        if(i != 0) decoration += ", ";
        decoration += pLanguageElement->getQualifiedDecoratedName();
    }
    decoration += " >";
    return decoration;
}

phantom::string TemplateSpecialization::getDecoratedName() const
{
    return getName()+getDecoration();
}

phantom::string TemplateSpecialization::getQualifiedName() const
{
    return m_pTemplate->getQualifiedName();
}

phantom::string TemplateSpecialization::getQualifiedDecoratedName() const
{
    return getQualifiedName()+getDecoration();
}

LanguageElement* TemplateSpecialization::getArgument( const string& a_strParameterName ) const
{
    size_t index = m_pTemplate->getTemplateParameterIndex(a_strParameterName);
    return (index != ~size_t(0)) ? m_Arguments[index] : nullptr;
}

Type* TemplateSpecialization::getType(const string& a_strParameterName) const
{
    LanguageElement* pTemplateElement = getArgument(a_strParameterName);
    if(pTemplateElement) return pTemplateElement->asType();
    return nullptr;
}

void TemplateSpecialization::setArgument( size_t a_uiIndex, LanguageElement* a_pElement )
{
    size_t index = a_uiIndex;
    o_assert(index != ~size_t(0));
    o_assert(m_Arguments[index] == nullptr);
    if(a_pElement == nullptr) setInvalid();
    m_Arguments[index] = a_pElement;
    if(a_pElement)
    {
        if( (a_pElement->asPlaceholder() OR NOT(a_pElement->asType())) AND a_pElement->getOwner() == nullptr)
            addElement(a_pElement);
        else 
            addReferencedElement(a_pElement);
    }
}

void TemplateSpecialization::setDefaultArgument( const string& a_strParameterName, LanguageElement* a_pElement )
{
    size_t index = m_pTemplate->getTemplateParameterIndex(a_strParameterName);
    o_assert(index != ~size_t(0), "no parameter found matching given name");
    setDefaultArgument(index, a_pElement);
}

void TemplateSpecialization::setDefaultArgument( size_t index, LanguageElement* a_pElement )
{
    o_assert(index < getArgumentCount());
    o_assert(isFull() AND isNative(), "can only set default arguments for native full specializations");
    if(a_pElement == nullptr)
        setInvalid();
    o_assert(a_pElement == nullptr OR getDefaultArgument(index) == nullptr, "default argument already defined");
    if(m_pDefaultArguments == nullptr) 
    {
        m_pDefaultArguments = new vector<LanguageElement*>;
        m_pDefaultArguments->resize(m_pTemplate->getTemplateParameterCount(), nullptr);
    }
    (*m_pDefaultArguments)[index] = a_pElement;
    if(a_pElement)
    {
        if( (a_pElement->asPlaceholder() OR NOT(a_pElement->asType())) AND a_pElement->getOwner() == nullptr)
            addElement(a_pElement);
        else 
            addReferencedElement(a_pElement);
    }
}

LanguageElement* TemplateSpecialization::getDefaultArgument( const string& a_strParameterName ) const
{
    if(m_pDefaultArguments == nullptr) return nullptr;
    size_t index = m_pTemplate->getTemplateParameterIndex(a_strParameterName);
    if(index == ~size_t(0)) return nullptr;
    return (*m_pDefaultArguments)[index];
}

void TemplateSpecialization::removeArgument( LanguageElement* a_pElement )
{
    if(a_pElement->getOwner() != this)
        removeReferencedElement(a_pElement);
    else 
        removeElement(a_pElement);
}

void TemplateSpecialization::referencedElementAdded(LanguageElement* a_pElement)
{
}

void TemplateSpecialization::referencedElementRemoved(LanguageElement* a_pElement)
{
    for(auto it = m_Arguments.begin(); it != m_Arguments.end(); )
    {
        if(*it == a_pElement)
        {
            it = m_Arguments.erase(it);
        }
        else ++it;
    }
}

boolean TemplateSpecialization::matches( const vector<LanguageElement*>& a_Arguments ) const
{
    size_t count = a_Arguments.size();
    if(count != m_Arguments.size()) 
        return false;
    size_t i = 0;
    for(;i<count;++i)
    {
        if(a_Arguments[i] == nullptr 
            OR m_Arguments[i] == nullptr 
            OR NOT(a_Arguments[i]->equals(m_Arguments[i]))) 
            return false;
    }
    return true;
}

void TemplateSpecialization::checkCompleteness() const
{
    o_assert(m_pTemplate);
    if(m_pTemplate->getModule() == nullptr)
    {
        o_exception(exception::reflection_runtime_exception, "Template not registered for this template specialization");
    }
}

bool TemplateSpecialization::canBeDestroyed() const
{
    return LanguageElement::canBeDestroyed();
}

size_t TemplateSpecialization::getArgumentIndex( const string& a_strParameterName ) const
{
    return m_pTemplate->getTemplateParameterIndex(a_strParameterName);
}

void TemplateSpecialization::elementRemoved( LanguageElement* a_pElement )
{
    for(auto it = m_Arguments.begin(); it != m_Arguments.end(); )
    {
        if(*it == a_pElement)
        {
            it = m_Arguments.erase(it);
        }
        else ++it;
    }
    LanguageElement::elementRemoved(a_pElement);
}

bool TemplateSpecialization::isEmpty() const
{
    for(auto it = m_Arguments.begin(); it != m_Arguments.end(); ++it)
    {
        if(NOT((*it)->asPlaceholder())) return false; // not a placeholder => partial or full specialization
    }
    return true;
}

bool TemplateSpecialization::isPartial() const
{
    return m_pTemplateSignature AND m_pTemplateSignature->getParameterCount() != 0;
}

bool TemplateSpecialization::isSpecializingParameter( TemplateParameter* a_pParameter ) const
{
    size_t i = m_pTemplate->getTemplateParameterIndex(a_pParameter);
    return (i != ~size_t(0)) AND (m_Arguments[i] != nullptr);
}
// 
// bool TemplateSpecialization::isSpecializing( LanguageElement* a_pLanguageElement )
// {
//     if(a_pLanguageElement->m_pTemplateParameterDependencies == nullptr) return false;
//     for(auto it = a_pLanguageElement->m_pTemplateParameterDependencies->begin(); it != a_pLanguageElement->m_pTemplateParameterDependencies->end(); ++it)
//     {
//         TemplateParameter* pDependency = *it;
//         if(isSpecializingParameter(pDependency)) return true;
//         for(auto it = a_pLanguageElement->beginElements(); it != a_pLanguageElement->endElements(); ++it)
//         {
//             if(isSpecializing(*it)) return true;
//         }
//         for(auto it = a_pLanguageElement->beginReferencedElements(); it != a_pLanguageElement->endReferencedElements(); ++it)
//         {
//             if(isSpecializing(*it)) return true;
//         }
//     }
//     return false;
// }

bool TemplateSpecialization::equals( TemplateSpecialization* a_pTemplateSpecialization ) const
{
    return a_pTemplateSpecialization->getTemplate() == m_pTemplate 
        AND matches(a_pTemplateSpecialization->getArguments());
}

void TemplateSpecialization::setBody( NamedElement* a_pBody )
{
    o_assert(a_pBody);
    o_assert(NOT(isNative()) OR m_pBody == nullptr);
    if(m_pBody)
    {
        setInvalid();
    }
    else m_pBody = a_pBody;
    addElement(m_pBody);
}

bool TemplateSpecialization::isFull() const
{
    return !isPartial() AND !isEmpty();
}

bool TemplateSpecialization::partialAccepts( const vector<LanguageElement*>& a_Arguments, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_Deductions ) const
{
    size_t score = 0;
    /// add default arguments
    size_t i = a_Arguments.size();
    size_t count = m_pTemplate->getTemplateParameterCount();
    if(m_pTemplate->getDefaultArgumentCount() < (count-i))
    {
        return false;
    }
    for(size_t i = 0; i<a_Arguments.size(); ++i)
    {
        size_t subScore = 0;
        if(NOT(m_Arguments[i]->partialAccepts(a_Arguments[i], subScore, a_Deductions)))
            return false;
        score += subScore;
    }
    a_Score = score;
    return true;
}

void TemplateSpecialization::finalize()
{
    o_assert(getBody());
    if(isFull())
    {
        getBody()->setFinalized();
    }
}

o_namespace_end(phantom, reflection)