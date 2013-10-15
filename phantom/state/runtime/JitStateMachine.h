#ifndef o_phantom_moon_JitStateMachine_h__
#define o_phantom_moon_JitStateMachine_h__


/* ****************** Includes ******************* */
#include <phantom/def_runtime.h>
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, state, runtime)

#define JitStateMachine_smdataptr(a_pObject) (*((jit_state_machine_data**)((byte*)a_pObject + m_uiDataPtrOffset)))

class o_runtime_export JitStateMachine : public StateMachine
{
    friend class reflection::runtime::JitClass;

public:
	JitStateMachine(bitfield modifiers = bitfield()) 
        : StateMachine(modifiers)
        , m_uiDataSize(sizeof(jit_state_machine_data))
        , m_bFinalized(false)
    {
    }
	~JitStateMachine(void) {}
	
    // (Runtime)StateMachine interface definition

    size_t getDataSize() const { return m_uiDataSize; }
    
    virtual void setup(StateMachine* a_pSuper);
    
    virtual void install(void* a_pObject) const;
    
    virtual void uninstall(void* a_pObject) const;
    
    virtual void initialize(void* a_pObject);
    
    virtual void update(void* a_pObject);
    
    virtual void terminate(void* a_pObject);
    
    virtual void postEvent( void* a_pObject, uint a_uiEventId );
    
    virtual State*const* getTransitStates(void const* a_pObject) const;
    virtual State*const* getCurrentStates(void const* a_pObject) const;
    virtual State** getTransitStates(void* a_pObject) const { return (State**)JitStateMachine_smdataptr(a_pObject)->transit_states; }
    virtual State** getCurrentStates(void* a_pObject) const { return (State**)JitStateMachine_smdataptr(a_pObject)->current_states; }
    virtual State*  getCurrentState(void* a_pObject, const Track* a_pTrack) const;
    virtual State*  getTransitState(void* a_pObject, const Track* a_pTrack) const;

    virtual size_t  getDataPtrOffset() const { return m_uiDataPtrOffset; }
    
    // Internal methods
    void    solveQueuedTransitions(jit_state_machine_data* smdataptr);
    void    solveTransitions( jit_state_machine_data* smdataptr, uint a_uiEventId );
    void    queue(jit_state_machine_data* smdataptr, uint a_uiEventId);
    
    base_state_machine_data* getInstanceData(void * a_pObject) const
    {
        return JitStateMachine_smdataptr(a_pObject);
    }


protected:
    void finalize() const;

    void registerState(State* a_pState)
    {
        StateMachine::registerState(a_pState);
        if(m_bFinalized)
        {
            o_exception(std::exception, "The state machine is frozen, you cannot add any more state or tracks");
        }

    }
    void registerTrack(State* a_pState)
    {
        StateMachine::registerState(a_pState);
        if(m_bFinalized)
        {
            o_exception(std::exception, "The state machine is frozen, you cannot add any more state or tracks");
        }

    }

protected:
    void setDataPtrOffset(size_t offset)
    {
        m_uiDataPtrOffset = offset;
    }

protected:
    size_t m_uiDataSize;
    size_t m_uiDataPtrOffset;
    mutable bool m_bFinalized;

};

o_namespace_end(phantom, state, runtime)

o_classNS((phantom, state, runtime), JitStateMachine, (StateMachine))
{
	o_reflection
	{
		
	};
};
o_exposeN((phantom, state, runtime), JitStateMachine);

#endif
