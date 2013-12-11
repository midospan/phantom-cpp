/* ******************* Includes ****************** */
#include "phantom/phantom.h"
/* *********************************************** */
o_registerN((phantom, reflection), LocalVariable);

o_namespace_begin(phantom, reflection) 
    
LocalVariable::LocalVariable( Block* a_pBlock, reflection::Type* a_pType, const string& a_strName, const CodeLocation& a_Location, bitfield a_Modifiers /*= 0*/ ) 
    : LanguageElement(a_strName, a_Modifiers)
    , m_iFrameOffset(e_InvalidFrameOffset)
    , m_pType(a_pType)
{
    a_pBlock->addLocalVariable(this);
    addCodeLocation(a_Location);
}

bool LocalVariable::isAccessibleAtCodePosition( const CodePosition& position ) const
{
    return (position.line > getCodeLocation().getStart().line) AND (position.line <= getBlock()->getCodeLocation().getEnd().line);
}

Block* LocalVariable::getBlock() const
{
    return static_cast<Block*>(m_pOwner);
}

LanguageElement* LocalVariable::getElement( const char* a_strQualifiedName , template_specialization const* a_pTS, function_signature const* a_pFS, bitfield a_Modifiers /*= 0*/ ) const
{
    return nullptr;
}

o_namespace_end(phantom, reflection)