/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "LocalVariable.h"
#include "LocalVariable.hxx"
#include "Block.h"
/* *********************************************** */
o_registerN((phantom, reflection), LocalVariable);

o_namespace_begin(phantom, reflection) 
    
LocalVariable::LocalVariable( Type* a_pValueType, const string& a_strName, bitfield a_Modifiers /*= 0*/ ) 
    : LanguageElement(a_strName, a_Modifiers)
    , m_iFrameOffset(e_InvalidFrameOffset)
    , m_pValueType(a_pValueType)
    , m_uiIndexInBlock(~size_t(0))
{
    if(m_pValueType == nullptr)
        setInvalid();
}

bool LocalVariable::isAccessibleAtCodePosition( const CodePosition& position ) const
{
    if(getBlock() == nullptr) 
        return nullptr;
    return (position.line > getCodeLocation().getStart().line) AND (position.line <= getBlock()->getCodeLocation().getEnd().line);
}

Block* LocalVariable::getBlock() const
{
    return static_cast<Block*>(m_pOwner);
}

LanguageElement* LocalVariable::solveElement( const string& a_strName , const vector<TemplateElement*>* a_pTS, const vector<LanguageElement*>* a_pFS, bitfield a_Modifiers /*= 0*/ ) const
{
    return nullptr;
}

o_namespace_end(phantom, reflection)