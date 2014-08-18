

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
    byte*   m_pStack;
    byte*   m_pBasePointer;
    byte*   m_pStackPointer;
    vector<Statement*> m_StatementStack;
    vector<void*> m_ReturnAddresses;
};

o_namespace_end(phantom, reflection)




#endif