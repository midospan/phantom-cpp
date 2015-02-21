

#ifndef o_reflection_Interpreter_h__
#define o_reflection_Interpreter_h__

/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Interpreter);
/* *********************************************** */

o_namespace_begin(phantom, reflection)
    
class Interpreter 
{
public:
	Interpreter(void);
	~Interpreter(void);

    virtual bool call( Subroutine* a_pSubroutine, void** a_ppArgs, size_t a_uiCount, void* a_pReturnAddress );

    void setNextStatement(Statement* a_pStatement);

    void pushDestruction(Expression* a_pRootExpression, Type* a_pType, void* a_pBuffer);

    void release(Expression* a_pRootExpression);

    byte*& stackPointer()
    {
        return m_pStackPointer;
    }

    byte* getBasePointer() const
    {
        return m_pBasePointer;
    }

    void* getReturnAddress() const
    {
        return m_ReturnAddresses.back();
    }

protected:
    typedef std::pair<Type*, void*> deferred_destruction;

protected:
    byte*   m_pStack;
    byte*   m_pBasePointer;
    byte*   m_pStackPointer;
    vector<Statement*> m_StatementStack;
    vector<void*> m_ReturnAddresses;
    map<Expression*, vector<deferred_destruction>> m_DeferredDestructions;
};

o_namespace_end(phantom, reflection)




#endif