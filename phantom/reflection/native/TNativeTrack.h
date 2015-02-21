/* TODO LICENCE HERE */

#ifndef state_TTrack_h__
#define state_TTrack_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */



o_namespace_begin(phantom, reflection, native)

template <typename _TrackClass>
class native_track_registrer
{
public:
    native_track_registrer()
    {
        _TrackClass::Instance();
    }
};


#define TNativeTrack_smdataptr(_object_) \
    ((phantom::state_machine_data<t_ObjectClass>*)(static_cast<root_object_class*>(static_cast<t_ObjectClass*>(_object_))->PHANTOM_CODEGEN_m_smdataptr))


template <typename t_ObjectClass>
class TNativeTrack : public Track
{
public:    
    typedef TNativeState<t_ObjectClass>         state_class;
    typedef TNativeTrack<t_ObjectClass>         self_type;
    typedef t_ObjectClass                       object_class;
    typedef TNativeStateMachine<t_ObjectClass>    statemachine_class;
    typedef o_NESTED_TYPE first_base_statechart_class_of<t_ObjectClass>::type        root_object_class;
    typedef state_machine_data<t_ObjectClass> instance_data;

    friend class phantom::reflection::State;
    friend class TNativeStateMachine<t_ObjectClass>;

    TNativeTrack( const string& a_strName
        , uint a_uiSerializationMask
        , modifiers_t bf )
            : Track(a_strName, a_uiSerializationMask
            , bf)
    {

    }
    o_destructor ~TNativeTrack(void)     {}

    o_forceinline State*    parent_state() const { return static_cast<State*>(m_pParentState); }

    void transit(instance_data* smdataptr, state_class* a_pNextState)
    {
        object_class* pObject = (object_class*)smdataptr->owner;
        state_class*& rpCurrentState = smdataptr->current_states[m_uiIndex];
        state_class*& rpTransitState = smdataptr->transit_states[m_uiIndex]; 
        if(rpCurrentState == NULL) /// Track isn't active
        {
            if(m_pParentState) /// if it's not the root track
            {
                rpTransitState = a_pNextState;
                static_cast<self_type*>(
                    static_cast<state_class*>(m_pParentState)->m_pParentTrack
                )->transit(smdataptr, static_cast<state_class*>(m_pParentState));
            }
            else /// the root track
            {
                rpTransitState = NULL;
                rpCurrentState = a_pNextState;
                smdataptr->lock();
                a_pNextState->enter(smdataptr);
                smdataptr->unlock();
            }
        }
        else if (rpCurrentState != a_pNextState)
        {
            state_class* pPreviousState = rpCurrentState;
            rpTransitState = NULL;
            State*& rpHistoryState = smdataptr->history_state;
            rpHistoryState = a_pNextState;
            smdataptr->lock();
            rpHistoryState = a_pNextState;
            pPreviousState->leave(smdataptr);
            rpCurrentState = a_pNextState;
            rpHistoryState = pPreviousState;
            a_pNextState->enter(smdataptr);
            smdataptr->unlock();
        }
    }

    virtual boolean isActive(void* a_pObject) const
    {
        return TNativeTrack_smdataptr(static_cast<object_class*>(a_pObject))->current_states[m_uiIndex] != NULL;
    }

    inline void enter(instance_data* smdataptr)
    {
        o_Track_TraceEnter();
        state_class*& rpCurrentState = smdataptr->current_states[m_uiIndex];
        state_class* pTransitState = smdataptr->transit_states[m_uiIndex];
        o_assert(rpCurrentState == NULL) ;
        if(pTransitState == NULL)
        {
            pTransitState = static_cast<state_class*>(m_States[0]);
        }
        else
        {
            smdataptr->transit_states[m_uiIndex] = NULL;
        }
        rpCurrentState = pTransitState;
        smdataptr->lock();
        pTransitState->enter(smdataptr);
        smdataptr->unlock();
    }

    inline void update(instance_data* smdataptr)
    {
        smdataptr->current_states[m_uiIndex]->update(smdataptr);
    }

    inline void leave(instance_data* smdataptr)
    {
        o_Track_TraceLeave();
        state_class*& rpCurrentState = smdataptr->current_states[m_uiIndex];
        smdataptr->lock();
        rpCurrentState->leave(smdataptr);
        smdataptr->unlock();
        rpCurrentState = NULL;
    }

};

#undef TNativeTrack_smdataptr

o_namespace_end(phantom, reflection, native)



    o_namespace_begin(phantom)



    template<typename t_ObjectClass, bool t_has_statechart>
class root_state_chart_helper
{
public:
    class Root
    {

    };
};

template<typename t_ObjectClass>
class root_state_chart_helper<t_ObjectClass, true>
{ 
    o_compiler_specific_friend phantom::detail::template_arg_friend_helper<t_ObjectClass>::type; 
    typedef void root_statechart_marker;

protected: 
    o_forceinline 
        root_state_chart_helper()            {} 

public:
    class Root 
    {
        friend class phantom::reflection::native::native_track_registrer<Root>;
        friend class phantom::reflection::native::TNativeTrack<t_ObjectClass>;
        Root() {}

    public: 
        typedef phantom::reflection::native::TNativeTrack<t_ObjectClass> placeholder_type;

        static placeholder_type* Instance()
        {
            static placeholder_type*    s_Instance = NULL;
            if(s_Instance == NULL)
            {
                s_Instance = o_dynamic_proxy_new(placeholder_type)(o_CS("Root"), 0, 0);
                phantom::reflection::native::TNativeStateMachine<t_ObjectClass>::Instance()->setRootTrack(s_Instance);
            }
            return s_Instance;
        }
    private:
        static const character*        RESERVED_getRoot() { return o_CS("Root"); }
    };

    typedef Root Root;
protected:
    phantom::reflection::native::native_track_registrer<Root> RESERVED_Root_registrer;
};


template<typename t_ObjectClass>
class root_statechart 
    : public root_state_chart_helper<t_ObjectClass, phantom::has_statechart_cascade<t_ObjectClass>::value>
{
public:
    o_forceinline root_statechart() {} 
    o_forceinline root_statechart(uint i)    {}
};

o_namespace_end(phantom)

#endif
