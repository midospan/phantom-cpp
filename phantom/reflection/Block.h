

#ifndef o_reflection_Block_h__
#define o_reflection_Block_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Statement.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Block);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class LocalVariable;
class MemberFunction;

class o_export Block : public Statement
{
    friend class Subroutine;

public:
    Block();
    Block(const string& a_strName);
    ~Block();

    virtual Block* asBlock() const  { return (Block*)this; }

	void addLocalVariable(LocalVariable* a_pVariable);
    void addStatement(Statement* a_pStatement);
    void addExpressionStatement(Expression* a_pExpression);

    void prependStatements(const vector<Statement*>& a_Statements);

	LocalVariable*	getLocalVariableCascade(const string& a_strName ) const;
    LocalVariable*	getLocalVariable(const string& a_strName) const;
    LocalVariable*	getLocalVariable(size_t i) const { return m_LocalVariables[i]; }

    uint		    getLocalVariableCount() const { return m_LocalVariables.size(); } 

    Statement*      getStatement(size_t i) const { return m_Statements[i]; }
    size_t          getStatementCount() const { return m_Statements.size(); }

    Statement*      getFirstStatementCascade() const;

    Subroutine*     getSubroutine() const;
    
    void getAccessibleLocalVariables(vector<LocalVariable*>& out, const CodePosition& position) const;

    void getLocalVariablesCascade(vector<LocalVariable*>& out) const;

    LocalVariable* getAccessibleLocalVariable(const string& name, const CodePosition& position) const;

    bool containsLine(int line) const;

    virtual LanguageElement* solveElement(const string& a_strName, const vector<TemplateElement*>* , const vector<LanguageElement*>* , bitfield a_Modifiers /* = bitfield */) const;

    Block* findBlockAtCodePosition(const CodePosition& a_Position) const;

    virtual void getAccessibleElementsAt(const CodePosition& a_Position, vector<LanguageElement*>& a_Elements) const;

    virtual void eval() const;

    vector<LocalVariable*>::const_iterator  beginLocalVariables() const { return m_LocalVariables.begin(); }
    vector<LocalVariable*>::const_iterator  endLocalVariables() const { return m_LocalVariables.end(); }

    vector<Statement*>    ::const_iterator  beginStatements() const { return m_Statements.begin(); }
    vector<Statement*>    ::const_iterator  endStatements() const { return m_Statements.end(); }

    vector<Statement*>    ::const_iterator  beginRAIIDestructionStatements() const { return m_RAIIDestructionStatements.begin(); }
    vector<Statement*>    ::const_iterator  endRAIIDestructionStatements() const { return m_RAIIDestructionStatements.end(); }

    void addRAIIDestructionStatement(Statement* a_pStatement)
    {
        m_RAIIDestructionStatements.insert(m_RAIIDestructionStatements.begin(), a_pStatement);
    }

    virtual variant compile(Compiler* a_pCompiler);

    Block*  getRootBlock() const { return (m_pOwner && m_pOwner->asBlock()) ? m_pOwner->asBlock()->getRootBlock() : const_cast<Block*>(this); }
    
protected:
    virtual void ancestorChanged(LanguageElement* a_pOwner)
    {
        if(m_pOwner == a_pOwner)
        {
            o_assert(m_LocalVariables.empty());
        }
    }

protected:
    vector<LocalVariable*>  m_LocalVariables;
    vector<Statement*>      m_Statements;
    vector<Statement*>      m_RAIIDestructionStatements;
};

o_namespace_end(phantom, reflection)

#endif