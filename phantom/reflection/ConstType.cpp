/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/ConstType.h>
#include <phantom/reflection/ConstType.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), ConstType);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(ConstType);

ConstType::ConstType( Type* a_pType ) 
    : Type(a_pType->getTypeId()
            , "const"
            , a_pType->getSize()
            , a_pType->getAlignment()
            , a_pType->getModifiers()|o_const)
    , m_pConstedType(a_pType)
{
    addReferencedElement(a_pType);
}

ConstType::~ConstType()
{
}

string ConstType::getQualifiedName() const
{
    return m_pConstedType->getQualifiedName()+" const";
}

string ConstType::getDecoratedName() const
{
    return m_pConstedType->getDecoratedName()+" const";
}

string ConstType::getQualifiedDecoratedName() const
{
    return m_pConstedType->getQualifiedDecoratedName()+" const";
}

void ConstType::referencedElementRemoved( LanguageElement* a_pElement )
{
    if(m_pConstedType == a_pElement)
    {
        m_pConstedType = nullptr;
    }
}

void ConstType::getElements( vector<LanguageElement*>& out, Class* a_pClass /*= nullptr */ ) const
{
    m_pConstedType->getElements(out, a_pClass);
}

bool ConstType::referencesData( const void* a_pInstance, const phantom::data& a_Data ) const
{
    return m_pConstedType->referencesData(a_pInstance, a_Data);
}

void ConstType::fetchExpressions( Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter, uint a_uiSerializationMask ) const
{
    m_pConstedType->fetchExpressions(a_pInstanceExpression, out, a_Filter, a_uiSerializationMask);
}

bool ConstType::partialAccepts( Type* a_pType, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_Deductions ) const
{
    if(a_pType->asConstType())
    {
        a_Score += 10;
        return m_pConstedType ? m_pConstedType->partialAccepts(a_pType->removeConst(), a_Score, a_Deductions) : nullptr;
    }
    return false;
}

Type* ConstType::addConst() const
{
    return const_cast<ConstType*>(this);
}

Type* ConstType::addVolatile() const
{
    return m_pConstedType->constVolatileType();
}

Type* ConstType::addConstVolatile() const
{
    return m_pConstedType->constVolatileType();
}

o_namespace_end(phantom, reflection)



