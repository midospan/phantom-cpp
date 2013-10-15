/* ******************* Includes ****************** */
#include "phantom/phantom.h"
/* ** The Class Header must be the last #include * */
/* *********************************************** */
o_registerN((phantom, reflection), Block);
o_namespace_begin(phantom, reflection) 

Block::Block()
{

}

Block::Block(Block* a_pParentBlock)
{
    setParentBlock(a_pParentBlock);
}

Block::~Block()
{
    auto localVariablesCopy = m_LocalVariables;
	for(auto it = localVariablesCopy.begin(); it != localVariablesCopy.end(); ++it)
	{
        o_dynamic_delete (*it);
    }
    auto childBlocksCopy = m_ChildBlocks;
    for(auto it = childBlocksCopy.begin(); it != childBlocksCopy.end(); ++it)
	{
		o_dynamic_delete (*it);
	}
}

void Block::addLocalVariable( LocalVariable* a_pVariable )
{
	o_assert(getLocalVariable(a_pVariable->getName()) == nullptr);
	m_LocalVariables.push_back(a_pVariable);
    addElement(a_pVariable);
}

void Block::addChildBlock( Block* a_pBlock )
{
    m_ChildBlocks.push_back(a_pBlock); 
    addElement(a_pBlock);
}

LocalVariable* Block::getLocalVariableCascade( const string& a_strName ) const
{
	LocalVariable* pResult = getLocalVariable(a_strName);
	return pResult 
            ? pResult 
            : getParentBlock() 
                ? getParentBlock()->getLocalVariableCascade(a_strName) 
                : nullptr;
}

LocalVariable* Block::getLocalVariable( const string& a_strName ) const
{
    for(auto it = m_LocalVariables.begin(); it != m_LocalVariables.end(); ++it)
    {
        if((*it)->getName() == a_strName)
        {
            return *it;
        }
    }
    return nullptr;
}

void Block::getAccessibleLocalVariables( vector<LocalVariable*>& out, const CodePosition& position ) const
{
    if(getParentBlock()) getParentBlock()->getAccessibleLocalVariables(out, position);
    for(auto it = m_LocalVariables.begin(); it != m_LocalVariables.end(); ++it)
    {
        LocalVariable* pLocalVariable = *it;
        if(pLocalVariable->isAccessibleAtCodePosition(position))
        {
            out.push_back(pLocalVariable);
        }
    }
}

LocalVariable* Block::getAccessibleLocalVariable( const string& a_strName, const CodePosition& a_Position ) const
{
    LocalVariable* pLocalVariable = getLocalVariable(a_strName);
    if(pLocalVariable && pLocalVariable->isAccessibleAtCodePosition(a_Position)) return pLocalVariable;
    return getParentBlock() ? getParentBlock()->getAccessibleLocalVariable(a_strName, a_Position) : nullptr;
}

reflection::LanguageElement* Block::getElement( const char* a_strName, template_specialization const* a_pTS, function_signature const* a_pFS, bitfield a_bfModifiers /* = bitfield */ ) const
{
    LocalVariable* pLocal = getLocalVariable(a_strName);
    if(pLocal) return pLocal;
    int blockIndex = -1;
    sscanf(a_strName, "%d", &blockIndex);
    if(blockIndex >= 0 AND blockIndex < (int)m_ChildBlocks.size())
    {
        return getChildBlock(blockIndex);
    }
    return nullptr;
}

Block* Block::findBlockAtCodePosition( const CodePosition& a_Position ) const
{
    if(containsCodePosition(a_Position))
    {
        for(auto it = m_ChildBlocks.begin(); it != m_ChildBlocks.end(); ++it)
        {
            Block* pBlock = (*it)->findBlockAtCodePosition(a_Position);
            if(pBlock) return pBlock;
        }
        return const_cast<Block*>(this);
    }
    return nullptr;
}

void Block::getLocalVariablesCascade( vector<LocalVariable*>& out ) const
{
    out.insert(out.end(), m_LocalVariables.begin(), m_LocalVariables.end());
    for(auto it = m_ChildBlocks.begin(); it != m_ChildBlocks.end(); ++it)
    {
        (*it)->getLocalVariablesCascade(out);
    }
}

Subroutine* Block::getSubroutine() const
{
    return getParentBlock() ? getParentBlock()->getSubroutine() : m_pOwner->asSubroutine();
}

bool Block::containsLine( int line ) const
{
    return getCodeLocation().containsLine(line);
}

void Block::getAccessibleElementsAt( const CodePosition& a_Position, vector<LanguageElement*>& a_Elements ) const
{
    vector<reflection::LocalVariable*> locals;
    getAccessibleLocalVariables(locals, a_Position);
    a_Elements.insert(a_Elements.end(), locals.begin(), locals.end());
    vector<reflection::Block*> blocks;
    size_t i = 0;
    for(;i<getChildBlockCount(); ++i)
    {
        getChildBlock(i)->getAccessibleElementsAt(a_Position, a_Elements);
    }
}

o_namespace_end(phantom, reflection)