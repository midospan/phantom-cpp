#ifndef o_phantom_moon_JitState_h__
#define o_phantom_moon_JitState_h__


/* ****************** Includes ******************* */
#include <phantom/def_jit.h>
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, state, jit)

class o_jit_export JitState : public State
{
    friend class JitTrack;
    friend class JitStateMachine;
public:
    JitState(const string& a_strName, bitfield modifiers = bitfield());
    ~JitState(void) 
    {

    }
    
    void copyHierarchy(JitStateMachine* a_pStateMachine, State* a_pSourceState);
    
    reflection::jit::JitInstanceMemberFunction* getEnterMemberFunction(void) const { return m_pEnterMemberFunction; }
    reflection::jit::JitInstanceMemberFunction* getUpdateMemberFunction(void) const { return m_pUpdateMemberFunction; }
    reflection::jit::JitInstanceMemberFunction* getLeaveMemberFunction(void) const { return m_pLeaveMemberFunction; }

    reflection::jit::JitInstanceMemberFunction* createEnterMemberFunction(void);
    reflection::jit::JitInstanceMemberFunction* createUpdateMemberFunction(void);
    reflection::jit::JitInstanceMemberFunction* createLeaveMemberFunction(void);
    
    void setEnterClosure(void* a_pClosure)
    {
        m_pEnterClosure = a_pClosure;
    }
    
    void setLeaveClosure(void* a_pClosure)
    {
        m_pLeaveClosure = a_pClosure;
    }
    
    void setUpdateClosure(void* a_pClosure)
    {
        m_pUpdateClosure = a_pClosure;
    }

    virtual generic_member_func_ptr   getEnterGenericMemberFunctionPointer() const 
    {
        generic_member_func_ptr ptr;
        ptr.setClosurePointer(m_pEnterClosure);
        return ptr;
    }
    virtual generic_member_func_ptr   getUpdateGenericMemberFunctionPointer() const 
    {
        generic_member_func_ptr ptr;
        ptr.setClosurePointer(m_pUpdateClosure);
        return ptr;
    }
    virtual generic_member_func_ptr   getLeaveGenericMemberFunctionPointer() const 
    {
        generic_member_func_ptr ptr;
        ptr.setClosurePointer(m_pLeaveClosure);
        return ptr;
    }

    inline void enter( jit_state_machine_data* smdataptr );
    inline void update( jit_state_machine_data* smdataptr );
    inline void leave( jit_state_machine_data* smdataptr );

protected:
    void compile();

protected:
    reflection::jit::JitInstanceMemberFunction*       m_pEnterMemberFunction;
    reflection::jit::JitInstanceMemberFunction*       m_pUpdateMemberFunction;
    reflection::jit::JitInstanceMemberFunction*       m_pLeaveMemberFunction;
    void*       m_pEnterClosure;
    void*       m_pUpdateClosure;
    void*       m_pLeaveClosure;
    bool        m_bCompiled;
};

o_namespace_end(phantom, state, jit)

o_classNS((phantom, state, jit), JitState, (State))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, state, jit), JitState);


#endif
