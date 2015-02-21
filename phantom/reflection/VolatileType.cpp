/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/VolatileType.h>
#include <phantom/reflection/VolatileType.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), VolatileType);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(VolatileType);

VolatileType::VolatileType( Type* a_pType ) 
    : Type(a_pType->getTypeId()
            , "volatile"
            , a_pType->getSize()
            , a_pType->getAlignment()
            , a_pType->getModifiers()|o_volatile)
    , m_pVolatiledType(a_pType)
{
    addReferencedElement(a_pType);
}

VolatileType::~VolatileType()
{
}

string VolatileType::getQualifiedName() const
{
    return m_pVolatiledType->getQualifiedName()+" volatile";
}

string VolatileType::getDecoratedName() const
{
    return m_pVolatiledType->getDecoratedName()+" volatile";
}

string VolatileType::getQualifiedDecoratedName() const
{
    return m_pVolatiledType->getQualifiedDecoratedName()+" volatile";
}

void VolatileType::referencedElementRemoved( LanguageElement* a_pElement )
{
    if(m_pVolatiledType == a_pElement)
    {
        m_pVolatiledType = nullptr;
    }
}

void VolatileType::getElements( vector<LanguageElement*>& out, Class* a_pClass /*= nullptr */ ) const
{
    m_pVolatiledType->getElements(out, a_pClass);
}

bool VolatileType::referencesData( const void* a_pInstance, const phantom::data& a_Data ) const
{
    return m_pVolatiledType->referencesData(a_pInstance, a_Data);
}

void VolatileType::fetchExpressions( Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter, uint a_uiSerializationMask ) const
{
    m_pVolatiledType->fetchExpressions(a_pInstanceExpression, out, a_Filter, a_uiSerializationMask);
}

bool VolatileType::partialAccepts( Type* a_pType, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_Deductions ) const
{
    if(a_pType->asVolatileType())
    {
        a_Score += 10;
        return m_pVolatiledType ? m_pVolatiledType->partialAccepts(a_pType->removeVolatile(), a_Score, a_Deductions) : nullptr;
    }
    return false;
}

Type* VolatileType::addConst() const
{
    return m_pVolatiledType->constVolatileType();
}

Type* VolatileType::addVolatile() const
{
    return const_cast<VolatileType*>(this);
}

Type* VolatileType::addConstVolatile() const
{
    return m_pVolatiledType->constVolatileType();
}

Type* VolatileType::replicate( Type* a_pSource ) const
{
    return m_pVolatiledType->replicate(a_pSource->removeVolatile())->addVolatile();
}

o_namespace_end(phantom, reflection)



