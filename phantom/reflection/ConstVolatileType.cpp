/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/ConstVolatileType.h>
#include <phantom/reflection/ConstVolatileType.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), ConstVolatileType);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(ConstVolatileType);

ConstVolatileType::ConstVolatileType( Type* a_pType ) 
    : Type(a_pType->getTypeId()
            , "const volatile"
            , a_pType->getSize()
            , a_pType->getAlignment()
            , a_pType->getModifiers()|o_volatile|o_const)
    , m_pConstVolatiledType(a_pType)
{
    addReferencedElement(a_pType);
}

ConstVolatileType::~ConstVolatileType()
{
}

string ConstVolatileType::getQualifiedName() const
{
    return m_pConstVolatiledType->getQualifiedName()+" const volatile";
}

string ConstVolatileType::getDecoratedName() const
{
    return m_pConstVolatiledType->getDecoratedName()+" const volatile";
}

string ConstVolatileType::getQualifiedDecoratedName() const
{
    return m_pConstVolatiledType->getQualifiedDecoratedName()+" const volatile";
}

void ConstVolatileType::referencedElementRemoved( LanguageElement* a_pElement )
{
    if(m_pConstVolatiledType == a_pElement)
    {
        m_pConstVolatiledType = nullptr;
    }
}

void ConstVolatileType::getElements( vector<LanguageElement*>& out, Class* a_pClass /*= nullptr */ ) const
{
    m_pConstVolatiledType->getElements(out, a_pClass);
}

bool ConstVolatileType::referencesData( const void* a_pInstance, const phantom::data& a_Data ) const
{
    return m_pConstVolatiledType->referencesData(a_pInstance, a_Data);
}

void ConstVolatileType::fetchExpressions( Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter, uint a_uiSerializationMask ) const
{
    m_pConstVolatiledType->fetchExpressions(a_pInstanceExpression, out, a_Filter, a_uiSerializationMask);
}

bool ConstVolatileType::partialAccepts( Type* a_pType, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_Deductions ) const
{
    if(a_pType->asConstVolatileType())
    {
        a_Score += 10;
        return m_pConstVolatiledType ? m_pConstVolatiledType->partialAccepts(a_pType->removeConstVolatile(), a_Score, a_Deductions) : nullptr;
    }
    return false;
}

o_namespace_end(phantom, reflection)



