#ifndef o_phantom_moon_JitState_h__
#define o_phantom_moon_JitState_h__


/* ****************** Includes ******************* */
#include <phantom/def_runtime.h>
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, state, runtime)

class o_runtime_export JitState : public State
{
    friend class JitTrack;
    friend class JitStateMachine;
public:
    JitState(const string& a_strName, bitfield modifiers = bitfield());
    ~JitState(void) 
    {

    }
    
    void copyHierarchy(JitStateMachine* a_pStateMachine, State* a_pSourceState);
    
    reflection::runtime::JitInstanceMethod* getEnterMethod(void) const { return m_pEnterMethod; }
    reflection::runtime::JitInstanceMethod* getUpdateMethod(void) const { return m_pUpdateMethod; }
    reflection::runtime::JitInstanceMethod* getLeaveMethod(void) const { return m_pLeaveMethod; }

    reflection::runtime::JitInstanceMethod* createEnterMethod(void);
    reflection::runtime::JitInstanceMethod* createUpdateMethod(void);
    reflection::runtime::JitInstanceMethod* createLeaveMethod(void);
    
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
    void finalize();

protected:
    jit_type_t  m_ClosureSignature;
    reflection::runtime::JitInstanceMethod*       m_pEnterMethod;
    reflection::runtime::JitInstanceMethod*       m_pUpdateMethod;
    reflection::runtime::JitInstanceMethod*       m_pLeaveMethod;
    void*       m_pEnterClosure;
    void*       m_pUpdateClosure;
    void*       m_pLeaveClosure;
};

o_namespace_end(phantom, state, runtime)

#include <phantom/state/runtime/JitTrack.h>

o_namespace_begin(phantom, state, runtime)

void JitState::enter( jit_state_machine_data* smdataptr )
{
    o_State_TraceEnter();
    o_assert(m_pEnterClosure);
    void* args[1] = { &smdataptr->owner };
    jit_apply( m_ClosureSignature, m_pEnterClosure, args, 1, nullptr);
    o_foreach(Track* pTrack, m_Tracks)
    {
        ((JitTrack*)pTrack)->enter(smdataptr);
    }
}

void JitState::update( jit_state_machine_data* smdataptr )
{
    o_assert(m_pUpdateClosure);
    void* args[1] = { &smdataptr->owner };
    jit_apply( m_ClosureSignature, m_pUpdateClosure, args, 1, nullptr);
    o_foreach(Track* pTrack, m_Tracks)
    {
        ((JitTrack*)pTrack)->update(smdataptr);
    }
}

void JitState::leave( jit_state_machine_data* smdataptr )
{
    o_foreach(Track* pTrack, m_Tracks)
    {
        ((JitTrack*)pTrack)->leave(smdataptr);
    }
    o_assert(m_pLeaveClosure);
    void* args[1] = { &smdataptr->owner };
    jit_apply( m_ClosureSignature, m_pLeaveClosure, args, 1, nullptr);
    o_State_TraceLeave();
}

o_namespace_end(phantom, state, runtime)


o_classNS((phantom, state, runtime), JitState, (State))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, state, runtime), JitState);


#endif
