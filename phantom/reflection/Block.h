

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
class ReturnStatement;

class o_export Block : public Statement
{
    friend class Subroutine;
    friend class ClassType;
    friend class ReturnStatement;

public:
#ifndef WIN32
    Block(); // used for serialization
#endif //WIN32
    Block(Block* a_pBlock, const string& a_strName = "");
    virtual ~Block();

    virtual Block* asBlock() const  { return (Block*)this; }

    void addLocalVariable(Type* a_pType, const string& a_strName, modifiers_t a_Modifiers = 0);
	void addLocalVariable(LocalVariable* a_pVariable);
    void addStatement(Statement* a_pStatement);
    
    void addExpressionStatement(Expression* a_pExpression);
    void addExpressionStatement(const string& a_strExpression);

    void addReturnStatement(const string& a_strExpression);
    void addReturnStatement(Expression* a_pExpression);
    void addReturnStatement();

    void addForStatement(const string& a_strInitTestUpdate, Block** a_pBlock);
    void addForStatement(Type* a_pInitType, const string& a_strName, Expression* a_pInitExpression, Expression* a_pTest, const vector<Expression*>& a_Updates, Block** a_pBlock);
    void addForStatement(LocalVariable* a_pLocalVariable, Expression* a_pInitExpression, Expression* a_pTest, const vector<Expression*>& a_Updates, Block** a_pBlock);

    void addWhileStatement(const string& a_strInitTest, Block** a_pBlock);
    void addWhileStatement(Type* a_pInitType, const string& a_strName, Expression* a_pTextExpression, Block** a_pBlock);
    void addWhileStatement(LocalVariable* a_pLocalVariable, Expression* a_pTextExpression, Block** a_pBlock);

    void addIfStatement(const string& a_strInitTest, Block** a_pThen, Block** a_pElse);
    void addIfStatement(Type* a_pInitType, const string& a_strName, Expression* a_pTextExpression, Block** a_pThen, Block** a_pElse);
    void addIfStatement(LocalVariable* a_pLocalVariable, Expression* a_pTextExpression, Block** a_pThen, Block** a_pElse);

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

    virtual LanguageElement* solveElement(const string& a_strName, const vector<TemplateElement*>* , const vector<LanguageElement*>* , modifiers_t a_Modifiers /* = modifiers_t */) const;

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

    void addRAIIDestructionExpressionStatement(Expression* a_pExpression);

    virtual variant compile(Compiler* a_pCompiler);

    Block*  getRootBlock() const { return (m_pOwner && m_pOwner->asBlock()) ? m_pOwner->asBlock()->getRootBlock() : const_cast<Block*>(this); }
    
protected:
    virtual void restore();
    virtual void elementRemoved( LanguageElement* a_pElement );

protected:
    vector<LocalVariable*>  getLocalVariables() const { return m_LocalVariables; }
    vector<Statement*>      getStatements() const {return m_Statements; }
    vector<Statement*>      getRAIIDestructionStatements() const { return m_RAIIDestructionStatements; } 
    void                    getRAIIDestructionStatementsCascade(vector<Statement*>& out) const;
    void                    setLocalVariables(vector<LocalVariable*> list);
    void                    setStatements(vector<Statement*> list);
    void                    setRAIIDestructionStatements(vector<Statement*> list);

protected:
#ifdef WIN32
    Block(); // used for serialization
#endif //WIN32
    Block(Subroutine* a_pSubroutine, LocalVariable* a_pThis = nullptr); // used to create root block in a subroutine

protected:
    vector<LocalVariable*>  m_LocalVariables;
    vector<Statement*>      m_Statements;
    vector<Statement*>      m_RAIIDestructionStatements;
};

o_namespace_end(phantom, reflection)

#endif