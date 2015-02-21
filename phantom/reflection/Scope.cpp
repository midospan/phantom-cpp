/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <phantom/reflection/Scope.h>
#include <phantom/reflection/Scope.hxx>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/ConstructorCallExpression.h>
#include <phantom/reflection/Template.hxx>
#include <phantom/reflection/Application.h>
#include <phantom/reflection/Import.h>
/* *********************************************** */
o_registerN((phantom, reflection), Scope);

o_namespace_begin(phantom, reflection) 

static vector<Variable*>            m_EmptyVariables;
static vector<Function*>            m_EmptyFunctions;
static vector<Type*>                m_EmptyTypes;
static vector<Template*>            m_EmptyTemplates;
static vector<TemplateSpecialization*>m_EmptyTemplateSpecializations;
static vector<Alias*>               m_EmptyAliases;

Scope::Scope( LanguageElement* a_pThisElement ) 
    : m_pThisElement(a_pThisElement)
    , m_pFunctions(nullptr)
    , m_pTemplates(nullptr)
    , m_pTemplateSpecializations(nullptr)
    , m_pTypes(nullptr)
    , m_pVariables(nullptr)
    , m_pAliases(nullptr)
{
}

Type* Scope::getType( const string& a_strName ) const
{
    if(m_pTypes)
    {
        auto it = m_pTypes->begin();
        auto end = m_pTypes->end();
        for(;it != end; ++it)
        {
            if((*it)->getName() == a_strName) return *it;
        }
    }
    return false;
}

Type* Scope::getTypeByGuid( uint a_uiGuid ) const
{
    if(m_pTypes)
    {
        auto it = m_pTypes->begin();
        auto end = m_pTypes->end();
        for(;it != end; ++it)
        {
            if((*it)->getGuid() == a_uiGuid) return *it;
        }
    }
	return false;
}

Template* Scope::getTemplate( const string& a_strName ) const
{
    if(m_pTemplates)
    {
        auto it = m_pTemplates->begin();
        auto end = m_pTemplates->end();
        for(;it != end; ++it)
        {
            if((*it)->getName() == a_strName) return *it;
        }
    }
    return false;
}

Template* Scope::getTemplate( size_t a_uiIndex ) const
{
    o_assert(m_pTemplates);
    return (*m_pTemplates)[a_uiIndex];
}

TemplateSpecialization* Scope::getTemplateSpecialization( size_t a_uiIndex ) const
{
    o_assert(m_pTemplateSpecializations);
    return (*m_pTemplateSpecializations)[a_uiIndex];
}

void Scope::release(vector<Type*>& out_types)
{
    while(!m_pTypes->empty())
    {
        out_types.push_back(m_pTypes->back());
        removeType(m_pTypes->back());
    }
}

// #define o_list(elem) m_p##elem##s
// #define o_param(elem) a_p##elem
// #define o_notfound(elem) (o_list(elem) == nullptr OR std::find(o_list(elem)->begin(), o_list(elem)->end(), o_param(elem)) == o_list(elem)->end())

// #define o_check_simple_name_collision(elem) \
//     {\
//         LanguageElement* pElement = phantom::elementByName(o_param(elem)->getQualifiedDecoratedName(), m_pThisElement);\
//         if(NOT((pElement == nullptr) OR (pElement->getOwner() != m_pThisElement) OR (pElement->testModifiers(o_template|o_native)) OR ((pElement == o_param(elem)) AND o_notfound(elem)), "An element has already been registered with name %s in scope %s", o_param(elem)->getQualifiedDecoratedName().c_str(), m_pThisElement->getQualifiedDecoratedName().c_str()))\
//         {\
//             m_pThisElement->setInvalid();\
//         }\
//     }

void Scope::addType( Type* a_pType )
{
    // o_check_simple_name_collision(Type);
    if(m_pTypes == nullptr) m_pTypes = new vector<Type*>;
    m_pTypes->push_back(a_pType);
    addScopeElement(a_pType);
    if(application()->getLoadedModuleCount())
    {
        o_emit typeAdded(a_pType);
    }
}

void Scope::addFunction( Function* a_pFunction )
{
    if(NOT(acceptsSubroutine(a_pFunction)))
    {
        m_pThisElement->setInvalid();
    }
    if(m_pFunctions == nullptr) m_pFunctions = new vector<Function*>;
    m_pFunctions->push_back(a_pFunction);
    addScopeElement(a_pFunction);
    if(application()->getLoadedModuleCount())
    {
        o_emit functionAdded(a_pFunction);
    }
}

void Scope::addVariable( Variable* a_pVariable )
{
    if(m_pVariables == nullptr) m_pVariables = new vector<Variable*>;
    m_pVariables->push_back(a_pVariable);
    addScopeElement(a_pVariable);
    if(application()->getLoadedModuleCount())
    {
        o_emit variableAdded(a_pVariable);
    }
}

void Scope::addTemplate( Template* a_pTemplate )
{
    if(m_pTemplates == nullptr) m_pTemplates = new vector<Template*>;
    m_pTemplates->push_back(a_pTemplate);
    addScopeElement(a_pTemplate);
    if(application()->getLoadedModuleCount())
    {
        o_emit templateAdded(a_pTemplate);
    }
}

void Scope::addTemplateSpecialization( TemplateSpecialization* a_pTemplateSpecialization )
{
    o_assert(a_pTemplateSpecialization->getTemplate() 
        AND a_pTemplateSpecialization->getTemplate()->getNamingScope() == this
        OR a_pTemplateSpecialization->getTemplate()->getOwner() == m_pThisElement, "template specialization must be declared in same scope as its specialized template");
    if(m_pTemplateSpecializations == nullptr) m_pTemplateSpecializations = new vector<TemplateSpecialization*>;
    m_pTemplateSpecializations->push_back(a_pTemplateSpecialization);
    addScopeElement(a_pTemplateSpecialization);
    if(application()->getLoadedModuleCount())
    {
        o_emit templateSpecializationAdded(a_pTemplateSpecialization);
    }
}

void Scope::addAlias( Alias* a_pAlias )
{
    if(m_pAliases == nullptr) m_pAliases = new vector<Alias*>;
    m_pAliases->push_back(a_pAlias);
    addScopeElement(a_pAlias);
    if(application()->getLoadedModuleCount())
    {
        o_emit aliasAdded(a_pAlias);
    }
}

Alias* Scope::addAlias( NamedElement* a_pNamedElement, const string& a_strAlias, modifiers_t a_Modifiers )
{
    Alias* pAlias = o_new(Alias)(a_pNamedElement, a_strAlias, a_Modifiers);
    addAlias(pAlias);
    return pAlias;
}

Alias* Scope::getAlias( size_t a_uiIndex ) const
{
    o_assert(m_pAliases);
    return (*m_pAliases)[a_uiIndex];
}

Alias* Scope::getAlias( const string& a_strName ) const
{
    if(m_pAliases)
    {
        for(auto it = beginAliases(); it != endAliases(); ++it)
        {
            if((*it)->getName() == a_strName) return *it;
        }
    }
    return nullptr;
}

size_t Scope::getAliasCount() const
{
    return m_pAliases ? m_pAliases->size() : 0;
}

vector<Alias*>::const_iterator Scope::beginAliases() const
{
    return m_pAliases ? m_pAliases->begin() : m_EmptyAliases.begin();
}

vector<Alias*>::const_iterator Scope::endAliases() const
{
    return m_pAliases ? m_pAliases->end() : m_EmptyAliases.end();
}

LanguageElement* Scope::getAliased( const string& a_strAlias ) const
{
    Alias* pAlias = getAlias(a_strAlias);
    return pAlias ? pAlias->getAliasedElement() : nullptr;
}

void Scope::removeAlias( Alias* a_pAlias )
{
    removeScopeElement(a_pAlias);
}

void Scope::removeType( Type* a_pType )
{
    removeScopeElement(a_pType);
}

void Scope::removeFunction( Function* a_pFunction )
{
    removeScopeElement(a_pFunction);
}

void Scope::removeVariable( Variable* a_pVariable )
{
    removeScopeElement(a_pVariable);
}

void Scope::removeTemplate( Template* a_pTemplate )
{
    removeScopeElement(a_pTemplate);
}

void Scope::removeTemplateSpecialization( TemplateSpecialization* a_pTemplateSpecialization )
{
    removeScopeElement(a_pTemplateSpecialization);
}

PrimitiveType* Scope::getPrimitiveType( const string& a_strName ) const
{
    Type* pType = getType(a_strName);
    return pType ? pType->asPrimitiveType() : nullptr;
}

Class* Scope::getClass( size_t index ) const
{
    if(m_pTypes == nullptr) return nullptr;
    size_t i = 0;
    o_foreach(Type* pType, *m_pTypes)
    {
        if(pType->asClass())
        {
            if(i == index) return static_cast<Class*>(pType);
            ++i;
        }
    }
    return nullptr;
}

Class* Scope::getClass( const string& a_strName ) const
{
    Type* pType = getType(a_strName);
    return pType ? pType->asClass() : nullptr;
}

size_t Scope::getClassCount() const
{
    if(m_pTypes == nullptr) return 0;
    size_t i = 0;
    o_foreach(Type* pType, *m_pTypes)
    {
        if(pType->asClass())
        {
            ++i;
        }
    }
    return i;
}

void Scope::scopedElementRemoved(LanguageElement* a_pElement)
{
    if(m_pTypes AND a_pElement->asType())
    for(auto it = m_pTypes->begin(); it != m_pTypes->end(); ++it)
    {
        if(*it == a_pElement)
        {
            if(application()->getLoadedModuleCount())
            {
                o_emit typeRemoved(*it);
            }
            m_pTypes->erase(it);
            if(m_pTypes->empty())
            {
                delete m_pTypes;
                m_pTypes = nullptr;
            }
            return;
        }
    }
    else if(m_pAliases AND a_pElement->asAlias())
    for(auto it = m_pAliases->begin(); it != m_pAliases->end(); ++it)
    {
        if(*it == a_pElement)
        {
            if(application()->getLoadedModuleCount())
            {
                o_emit aliasRemoved(*it);
            }
            m_pAliases->erase(it);
            if(m_pAliases->empty())
            {
                delete m_pAliases;
                m_pAliases = nullptr;
            }
            return;
        }
    }
    else if(m_pVariables AND a_pElement->asVariable())
    for(auto it = m_pVariables->begin(); it != m_pVariables->end(); ++it)
    {
        if(*it == a_pElement)
        {
            if(application()->getLoadedModuleCount())
            {
                o_emit variableRemoved(*it);
            }
            m_pVariables->erase(it);
            if(m_pVariables->empty())
            {
                delete m_pVariables;
                m_pVariables = nullptr;
            }
            return;
        }
    }
    else if(m_pFunctions AND a_pElement->asFunction())
    for(auto it = m_pFunctions->begin(); it != m_pFunctions->end(); ++it)
    {
        if(*it == a_pElement)
        {
            if(application()->getLoadedModuleCount())
            {
                o_emit functionRemoved(*it);
            }
            m_pFunctions->erase(it);
            if(m_pFunctions->empty())
            {
                delete m_pFunctions;
                m_pFunctions = nullptr;
            }
            return;
        }
    }
    else if(m_pTemplates AND a_pElement->asTemplate())
    for(auto it = m_pTemplates->begin(); it != m_pTemplates->end(); ++it)
    {
        if(*it == a_pElement)
        {
            if(application()->getLoadedModuleCount())
            {
                o_emit templateRemoved(*it);
            }
            m_pTemplates->erase(it);
            if(m_pTemplates->empty())
            {
                delete m_pTemplates;
                m_pTemplates = nullptr;
            }
            return;
        }
    }
    else if(m_pTemplateSpecializations AND a_pElement->asTemplateSpecialization())
    for(auto it = m_pTemplateSpecializations->begin(); it != m_pTemplateSpecializations->end(); ++it)
    {
        if(*it == a_pElement)
        {
            if(application()->getLoadedModuleCount())
            {
                o_emit templateSpecializationRemoved(*it);
            }
            m_pTemplateSpecializations->erase(it);
            if(m_pTemplateSpecializations->empty())
            {
                delete m_pTemplateSpecializations;
                m_pTemplateSpecializations = nullptr;
            }
            return;
        }
    }
}

vector<Variable*>::const_iterator Scope::beginVariables() const
{
    return m_pVariables ? m_pVariables->begin() : m_EmptyVariables.begin();
}

vector<Variable*>::const_iterator Scope::endVariables() const
{
    return m_pVariables ? m_pVariables->end() : m_EmptyVariables.end();
}

vector<Function*>::const_iterator Scope::beginFunctions() const
{
    return m_pFunctions ? m_pFunctions->begin() : m_EmptyFunctions.begin();
}

vector<Function*>::const_iterator Scope::endFunctions() const
{
    return m_pFunctions ? m_pFunctions->end() : m_EmptyFunctions.end();
}

void Scope::finalize()
{
    for(auto it = beginTypes(); it != endTypes(); ++it)
    {
        (*it)->setFinalized();
    }
    for(auto it = beginTemplateSpecializations(); it != endTemplateSpecializations(); ++it)
    {
        (*it)->setFinalized();
    }
}

size_t Scope::getFunctionCount() const
{
    return m_pFunctions ? m_pFunctions->size() : 0;
}

Function* Scope::getFunction( const string& a_strName, const vector<Type*>& a_Types  ) const
{
    if(m_pFunctions == nullptr) 
        return nullptr;
    {
        auto it = m_pFunctions->begin();
        auto end = m_pFunctions->end();
        for(; it != end; ++it)
        {
            Function* pFunction = static_cast<Function*>((*it));
            if(pFunction->matches(a_strName, a_Types))
            {
                return pFunction;
            }
        }
    }
    return nullptr;
}

Function* Scope::getFunction( size_t a_uiIndex ) const
{
    o_assert(m_pFunctions);
    return (*m_pFunctions)[a_uiIndex];
}

Variable* Scope::getVariable( const string& a_strName) const
{
    if(m_pVariables) 
    {
        auto it = m_pVariables->begin();
        auto end = m_pVariables->end();
        for(; it != end; ++it)
        {
            Variable* pVariable = static_cast<Variable*>((*it));
            if(pVariable->getName() == a_strName)
                return pVariable;
        }
    }
    return nullptr;
}

Variable* Scope::getVariable( size_t a_uiIndex ) const
{
    o_assert(m_pVariables);
    return (*m_pVariables)[a_uiIndex];
}

vector<Type*>::const_iterator Scope::beginTypes() const
{
    return m_pTypes ? m_pTypes->begin() : m_EmptyTypes.begin();
}

vector<Type*>::const_iterator Scope::endTypes() const
{
    return m_pTypes ? m_pTypes->end() : m_EmptyTypes.end();
}

vector<Template*>::const_iterator Scope::beginTemplates() const
{
    return m_pTemplates ? m_pTemplates->begin() : m_EmptyTemplates.begin();
}

vector<Template*>::const_iterator Scope::endTemplates() const
{
    return m_pTemplates ? m_pTemplates->end() : m_EmptyTemplates.end();
}

vector<TemplateSpecialization*>::const_iterator Scope::beginTemplateSpecializations() const
{
    return m_pTemplateSpecializations ? m_pTemplateSpecializations->begin() : m_EmptyTemplateSpecializations.begin();
}

vector<TemplateSpecialization*>::const_iterator Scope::endTemplateSpecializations() const
{
    return m_pTemplateSpecializations ? m_pTemplateSpecializations->end() : m_EmptyTemplateSpecializations.end();
}

void Scope::addSubroutine( Subroutine* a_pSubroutine )
{
    o_assert(a_pSubroutine);
    if(a_pSubroutine->asFunction())
        addFunction(a_pSubroutine->asFunction());
    else o_exception_no_implementation();
}

size_t Scope::getVariableCount() const
{
    return m_pVariables ? m_pVariables->size() : 0;
}

Subroutine* Scope::getSubroutine( const string& a_strName, const vector<Type*>& a_ParameterTypes, modifiers_t a_Qualifiers ) const
{
    o_assert(a_Qualifiers == (a_Qualifiers & o_member_function_qualifiers_mask));
    if(a_Qualifiers == 0)
        return getFunction(a_strName, a_ParameterTypes);
    return nullptr;
}

Subroutine* Scope::getSubroutine( Type* a_pReturnType, const string& a_strName, const vector<Type*>& a_ParameterTypes, modifiers_t a_Modifiers ) const
{
    Subroutine* pSubroutine = getSubroutine(a_strName, a_ParameterTypes, a_Modifiers);
    if(pSubroutine AND pSubroutine->getReturnType() AND pSubroutine->getReturnType()->equals(a_pReturnType))
        return pSubroutine;
    return nullptr;
}

bool Scope::acceptsSubroutine( Type* a_pReturnType, const string& a_strName, const vector<Type*>& a_Types, modifiers_t a_Modifiers, vector<Subroutine*>* a_pOutConflictingSubroutines /*= nullptr*/ ) const
{
    bool bResult = true;
    if(m_pFunctions)
    {
        auto it = m_pFunctions->begin();
        auto end = m_pFunctions->end();
        for(; it != end; ++it)
        {
            Function* pFunction = *it;
            ESignatureRelation eOR = pFunction->getSignatureRelationWith(a_pReturnType, a_strName, a_Types, 0); // 0 because static functions consider const and non-const as conflicting
            if(eOR != e_SignatureRelation_None)
            {
                if(a_pOutConflictingSubroutines) 
                {
                    a_pOutConflictingSubroutines->push_back(pFunction);
                    bResult = false;
                }
                else return false;
            }
        }
    }
    return bResult;
}

bool Scope::acceptsSubroutine( Subroutine* a_pSubroutine ) const
{
    return acceptsSubroutine(a_pSubroutine->getReturnType(), a_pSubroutine->getName(), a_pSubroutine->getParameterTypes(), a_pSubroutine->getModifiers());
}

void Scope::getElementDoubles( NamedElement* a_pElement, vector<NamedElement*>& out ) const
{
    size_t elementIndex = m_pThisElement->getElementIndex(a_pElement);
    o_assert(elementIndex != ~size_t(0));
    NamedElement* pThisNamedElement = m_pThisElement->asNamedElement();
    if(pThisNamedElement)
    {
        vector<NamedElement*> thisDoubles;
        pThisNamedElement->getDoubles(thisDoubles);
        for(auto it = thisDoubles.begin(); it != thisDoubles.end(); ++it)
        {
            NamedElement* pDouble = static_cast<NamedElement*>((*it)->getElement(elementIndex));
            o_assert(pDouble->getQualifiedDecoratedName() == a_pElement->getQualifiedDecoratedName());
            out.push_back(pDouble);
        }
    }
}

Alias* Scope::getTypedef( const string& a_strTypedef ) const
{
    Alias* pAlias = getAlias(a_strTypedef); 
    return pAlias->getAliasedElement()->asType() ? pAlias : nullptr;
}

void Scope::addUsing( NamedElement* a_pElement )
{
    addAlias(o_new(Alias)(a_pElement, a_pElement->getName()));
}

o_namespace_end(phantom, reflection)
