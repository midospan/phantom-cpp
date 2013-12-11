

#ifndef o_reflection_Block_h__
#define o_reflection_Block_h__



/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class LocalVariable;
class MemberFunction;

class o_export Block : public LanguageElement
{
    friend class Subroutine;

public:

	Block();
    Block(Block* a_pParentBlock);
    ~Block();

	void addLocalVariable(LocalVariable* a_pVariable);
	void addChildBlock(Block* a_pBlock);

	LocalVariable*	getLocalVariableCascade(const string& a_strName ) const;
	LocalVariable*	getLocalVariable(const string& a_strName) const;

	vector<LocalVariable*>::const_iterator beginLocalVariables() const { return m_LocalVariables.begin(); }
	vector<LocalVariable*>::const_iterator endLocalVariables() const { return m_LocalVariables.end(); }

	Block*	    getParentBlock() const 
    { 
        return m_pOwner->asSubroutine() 
                ? nullptr 
                : static_cast<Block*>(m_pOwner); 
    }

	void		setParentBlock(Block*	a_pBlock) 
    { 
        a_pBlock->addChildBlock(this); 
    }

    Block* getChildBlock(size_t i) const { return m_ChildBlocks[i]; }
    size_t getChildBlockCount() const { return m_ChildBlocks.size(); }

    Subroutine* getSubroutine() const;

	Block*		getRootScope() const { return getParentBlock()?getParentBlock()->getRootScope():const_cast<Block*>(this); }

	uint		getLocalVariableCount() const { return m_LocalVariables.size(); } 
    
    void getAccessibleLocalVariables(vector<LocalVariable*>& out, const CodePosition& position) const;

    void getLocalVariablesCascade(vector<LocalVariable*>& out) const;

    LocalVariable* getAccessibleLocalVariable(const string& name, const CodePosition& position) const;

    bool containsLine(int line) const;

    virtual LanguageElement* getElement(const char* a_strName, template_specialization const* , function_signature const* , bitfield a_Modifiers /* = bitfield */) const;

    Block* findBlockAtCodePosition(const CodePosition& a_Position) const;

    virtual void getAccessibleElementsAt(const CodePosition& a_Position, vector<LanguageElement*>& a_Elements) const;

protected:
	vector<LocalVariable*>  m_LocalVariables;
	vector<Block*>          m_ChildBlocks;
};

o_namespace_end(phantom, reflection)

o_classNS((phantom, reflection), Block, (LanguageElement))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, reflection), Block);
 

#endif