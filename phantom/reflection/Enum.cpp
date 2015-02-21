/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/Enum.h>
#include <phantom/reflection/Enum.hxx>
#include <phantom/reflection/ConstantExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), Enum);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(Enum);

Enum::Enum() 
    : PrimitiveType(e_enum, "", 4, 4, 0)
    , m_pIntType(typeOf<int>())
{
    addReferencedElement(m_pIntType);
}

Enum::Enum( const string& a_strName, PrimitiveType* a_pIntType, modifiers_t a_Modifiers /*= 0*/ )
    : PrimitiveType(e_enum, a_strName, a_pIntType->getSize(), a_pIntType->getAlignment(), a_Modifiers)
    , m_pIntType(a_pIntType)
{
    addReferencedElement(m_pIntType);
}

Enum::Enum( PrimitiveType* a_pIntType, const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers /*= 0*/ ) 
    : PrimitiveType(e_enum, a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
    , m_pIntType(a_pIntType)
{
}

Enum::~Enum()
{
}

void Enum::addConstant( NumericConstant* a_pConstant )
{
    o_assert(getConstant(a_pConstant->getName()) == nullptr);
    o_assert(a_pConstant->getValueType() == this);
    addElement(a_pConstant);
    m_Constants.push_back(a_pConstant);
    if(m_pOwner)
    {
        o_assert(m_pOwner->asScope());
        Alias* pAlias = o_new(Alias)(a_pConstant, a_pConstant->getName());
        if(m_pNamespace)
        {
            m_pNamespace->addAlias(pAlias);
        }
        m_pOwner->asScope()->addAlias(pAlias); // ensure constants can be accessed from their enum's owner
    }
}

void Enum::removeConstant( NumericConstant* a_pConstant )
{
    o_assert(getConstant(a_pConstant->getName()) != nullptr);
    o_assert(a_pConstant->getValueType() == this);
    removeElement(a_pConstant);
}

NumericConstant* Enum::getConstant( const string& a_strKey ) const
{
    value_vector::const_iterator it = m_Constants.begin();
    value_vector::const_iterator end = m_Constants.end();
    for(;it!=end;++it)
    {
        if((*it)->getName() == a_strKey) return *it;
    }
    return nullptr;
}

void Enum::valueFromString( const string& a_strIn, void* a_pDest ) const
{
    size_t i = 0;
    size_t count = getConstantCount();
    for(;i<count;++i)
    {
        size_t constantValue = 0;
        reflection::NumericConstant* pConstant = getConstant(i);
        if(pConstant->getName() == a_strIn)
        {
            pConstant->getValue(a_pDest);
            return;
        }
    }
}

void Enum::valueToString( string& a_strOut, const void* a_pSrc ) const
{
    size_t i = 0;
    size_t count = getConstantCount();
    for(;i<count;++i)
    {
        size_t constantValue = 0;
        reflection::NumericConstant* pConstant = getConstant(i);
        pConstant->getValue(&constantValue);
        if(constantValue == *((size_t*)a_pSrc))
        {
            a_strOut = m_pOwner ? m_pOwner->getQualifiedName() + "::" + pConstant->getName() : pConstant->getName();
            return;
        }
    }
}

void Enum::elementRemoved( LanguageElement* a_pElement )
{
    NumericConstant* pConstant = a_pElement->asNumericConstant();
    o_assert(pConstant);
    m_Constants.erase(std::find(m_Constants.begin(), m_Constants.end(), pConstant));
}

void Enum::findConstantsWithValue( void* a_pSrc, vector<Constant*>& out ) const
{
    for(auto it = m_Constants.begin(); it != m_Constants.end(); ++it)
    {
        if((*it)->hasValue(a_pSrc)) out.push_back(*it);
    }
}

void Enum::ancestorChanged( LanguageElement* a_pOwner )
{
    if(m_pOwner AND (a_pOwner == m_pOwner))
    {
        o_assert(m_pOwner->asScope());
        for(auto it = m_Constants.begin(); it != m_Constants.end(); ++it)
        {
            Alias* pAlias = o_new(Alias)(*it, (*it)->getName());
            if(m_pNamespace)
            {
                m_pNamespace->addAlias(pAlias);
            }
            m_pOwner->asScope()->addAlias(pAlias); // ensure constants can be accessed from their enum's owner
        }
    }
}

o_namespace_end(phantom, reflection)