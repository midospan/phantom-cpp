#ifndef o_phantom_statechart_h__
#define o_phantom_statechart_h__



#define o_enter(_name) void _name##_enter(void)
#define o_update(_name) void _name##_update(void)
#define o_leave(_name) void _name##_leave(void)

#define o_statemachine_data PHANTOM_CODEGEN_m_smdataptr
#define o_statemachine_get() o_statemachine_data->stateMachine()
#define o_statemachine_initialize() o_statemachine_data->initialize()
#define o_statemachine_terminate() o_statemachine_data->terminate()
#define o_statemachine_update() o_statemachine_data->update()
#define o_statemachine_reset() o_statemachine_data->reset()
#define o_statemachine_post_2(_class_, _event_) o_statemachine_data->postEvent(phantom::statechart<_class_,_class_>::_event_::Id())
#define o_statemachine_post_3(_ptr_, _class_, _event_) (_ptr_)->o_statemachine_post_2(_class_,_event_)

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#define o_statemachine_post(...) o_PP_CAT(o_PP_CAT(o_statemachine_post_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#define o_super_enter(...) o_PP_CAT(o_PP_CAT(o_super_enter_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#define o_super_update(...) o_PP_CAT(o_PP_CAT(o_super_update_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#define o_super_leave(...) o_PP_CAT(o_PP_CAT(o_super_leave_, o_PP_NARG(__VA_ARGS__)),(__VA_ARGS__))
#else
#define o_statemachine_post(...) o_PP_CAT(o_statemachine_post_, o_PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#define o_super_enter(...) o_PP_CAT(o_super_enter_, o_PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#define o_super_update(...) o_PP_CAT(o_super_update_, o_PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#define o_super_leave(...) o_PP_CAT(o_super_leave_, o_PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#endif

#define o_super_enter_2(_class_, _name)     _class_::_name##_enter()
#define o_super_update_2(_class_, _name)    _class_::_name##_update()
#define o_super_leave_2(_class_, _name)     _class_::_name##_leave()

#if o__bool__enable_state_machine_trace

#define o_StateMachine_TracePostEvent(_eventid_) \
    std::cout<<console::fg_blue<<"posted "\
    <<console::fg_white<<getEventName(_eventid_)<<std::endl 

#define o_StateMachine_TraceDispatchEvent(_eventid_) \
    std::cout<<console::fg_blue<<"dispatched "\
    <<console::fg_white<<getEventName(_eventid_)<<std::endl 

# define o_StateMachine_TraceLocked() \
    std::cout<<console::fg_magenta<<"locked "\
    <<console::fg_white<<smdataptr->lock_counter<<std::endl 

#define o_StateMachine_TraceEventQueueFull(_eventid_) \
    std::cout<<console::bg_red<<console::fg_white<<"dismissed "\
    <<console::bg_black<<smdataptr->state_machine->getEventName(_eventid_)<<std::endl 

#define o_StateMachine_TraceQueued(_eventid_) \
    std::cout<<console::fg_cyan<<"queued "\
    <<console::fg_white<<smdataptr->state_machine->getEventName(_eventid_)<<std::endl 


# define o_Track_TraceEnter() \
std::cout<<console::createSpaces(getLevel())\
<<console::fg_green<<"enter "\
<<console::fg_yellow<<getName()<<std::endl 

# define o_Track_TraceLeave() \
std::cout<<console::createSpaces(getLevel())\
<<console::fg_red<<"leave "\
<<console::fg_yellow<<getName()<<std::endl 

# define o_State_TraceEnter() \
std::cout<<console::createSpaces(getLevel())\
<<console::fg_green<<"enter "\
<<console::fg_white<<getName()<<std::endl

# define o_State_TraceLeave() \
std::cout<<console::createSpaces(getLevel())\
<<console::fg_red<<"leave "\
<<console::fg_white<<getName()<<std::endl

#else
# define o_StateMachine_TracePostEvent(_event_) 
# define o_StateMachine_TraceTrackLocked(_track_index_) 
# define o_StateMachine_TraceDispatchEvent(_event_)
# define o_Track_TraceEnter()
# define o_Track_TraceLeave()
# define o_StateMachine_TraceEventQueueFull(_event_)
# define o_StateMachine_TraceQueued(_event_)
# define o_StateMachine_TraceLocked()
# define o_State_TraceEnter() 
# define o_State_TraceLeave() 
#endif

#define o_statechart_begin \
    private: \
        typedef o_global_value_Type phantom_proxy_generator_statechart_self_type;\
    o_statechart {


#define o_statechart_end \
    }; 

#define o_event(_name, ...)\
    public:\
class _name  \
{\
    friend class phantom::state::native::native_event_registrer<_name>;\
    friend class phantom::state::Event;\
    _name() {};\
public: \
    static phantom::uint Id()\
    {\
        static phantom::uint    s_id = 0xffffffff;\
        if(s_id == 0xffffffff)\
        {\
            s_id = phantom::state::native::TNativeStateMachine<t_PHANTOM_RESERVED_statechart_objectclass>::Instance()->getEventId(#_name);\
            if(s_id == 0xffffffff)\
            {\
                s_id = phantom::state::native::TNativeStateMachine<t_PHANTOM_RESERVED_statechart_objectclass>::Instance()->addEvent(#_name);\
            }\
        }\
        return s_id;\
    }\
};\
phantom::state::native::native_event_registrer<_name> RESERVED_##_name##_registrer;

#define o_statemachine \
    public:\
    typedef int PHANTOM_CODEGEN_smdataptr_marker; \
    const phantom::state::base_state_machine_data* PHANTOM_CODEGEN_m_smdataptr;\
    protected:

#define o_TRACK o_track
#define o_Track o_track
#define o_track(_name, _parent, ...)\
    public:\
    struct phantom_proxy_generator_track_counter_marker;\
template<typename t_Ty, int t_count>\
struct phantom_proxy_generator_track_counter;\
template<typename t_Ty>\
struct phantom_proxy_generator_track_counter<t_Ty,__COUNTER__-phantom_proxy_generator_track_counter_base_value-1> { typedef t_Ty phantom_proxy_generator_track_counter_defined; };\
class _name\
{\
    friend class phantom::state::native::native_track_registrer<_name>;\
    friend class phantom::state::native::TNativeTrack<t_PHANTOM_RESERVED_statechart_objectclass>;\
    _name() {}\
public: \
    typedef phantom::state::native::TNativeTrack<t_PHANTOM_RESERVED_statechart_objectclass> placeholder_type;\
    static placeholder_type* Instance()\
    {\
        static placeholder_type*    s_Instance = NULL;\
        if(s_Instance == NULL)\
        {\
            s_Instance = (placeholder_type*)phantom::state::native::TNativeStateMachine<t_PHANTOM_RESERVED_statechart_objectclass>::Instance()->getTrack(o_CS(#_name));\
            if(s_Instance == NULL)\
            {\
                phantom::state::State* pParentState = _parent::Instance();\
                s_Instance = o_new(placeholder_type)(o_CS(#_name), phantom::detail::int_embedder<__VA_ARGS__>::value);\
                pParentState->addTrack(s_Instance);\
            }\
        }\
        return s_Instance;\
    }\
};\
phantom::state::native::native_track_registrer<_name> RESERVED_##_name##_registrer;

#define o_State o_state
#define o_STATE o_state
#define o_state(_name, _parent, ...)\
    public:\
class _name \
{\
    friend class phantom::state::native::native_state_registrer<_name, t_PHANTOM_RESERVED_statechart_objectclass>;\
    static const phantom::character* RESERVED_get_name() { return o_CS(#_name); } \
    _name() {}\
public: \
    typedef phantom::state::native::TNativeState<t_PHANTOM_RESERVED_statechart_objectclass> placeholder_type;\
    static placeholder_type* Instance()\
    {\
        static placeholder_type*    s_Instance = NULL;\
        if(s_Instance == NULL)\
        {\
            s_Instance = (placeholder_type*)phantom::state::native::TNativeStateMachine<t_PHANTOM_RESERVED_statechart_objectclass>::Instance()->getState(o_CS(#_name));\
            if(s_Instance == NULL)\
            {\
                phantom::state::Track* pParentTrack = _parent::Instance();\
                s_Instance = o_new(placeholder_type)(\
                o_CS(#_name)\
                , &t_PHANTOM_RESERVED_statechart_objectclass::_name##_enter\
                , &t_PHANTOM_RESERVED_statechart_objectclass::_name##_update\
                , &t_PHANTOM_RESERVED_statechart_objectclass::_name##_leave\
                , __LINE__\
                , phantom::detail::int_embedder<__VA_ARGS__>::value);\
                pParentTrack->addState(s_Instance);\
            }\
        }\
        return s_Instance;\
    }\
};\
phantom::state::native::native_state_registrer<_name, t_PHANTOM_RESERVED_statechart_objectclass> RESERVED_##_name##_registrer;\


#define o_Transition o_transition
#define o_TRANSITION o_transition
#define o_transition(_state_src, _event, _state_tgt)\
    phantom::state::native::native_transition_registrer< t_PHANTOM_RESERVED_statechart_objectclass, _state_src, _event, _state_tgt >    m_TNativeTransition_##_state_src##_event##_state_tgt;



o_namespace_begin(phantom, state, detail)


template<typename t_Ty>
struct state_machine_serializer
{
    static void serialize(t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)   ;
    static void deserialize(t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)   ;
    static void serialize(t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)    ;
    static void deserialize(t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)    ;

    o_forceinline static void serialize(t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
            serialize(reinterpret_cast<t_Ty const*>(pChunk), a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
    }
    o_forceinline static void deserialize(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
            deserialize(reinterpret_cast<t_Ty*>(pChunk), a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        }
    }
    o_forceinline static void serialize(t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
            serialize(reinterpret_cast<t_Ty const*>(pChunk), a_OutBranch, a_uiSerializationMask, a_pDataBase);
        }
    }
    o_forceinline static void deserialize(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
            deserialize(reinterpret_cast<t_Ty*>(pChunk), a_InBranch, a_uiSerializationMask, a_pDataBase);
        }
    }
};


template<typename t_Ty>
struct state_machine_resetter
{
    static void remember(t_Ty const* a_pInstance, byte*& a_pOutBuffer)   ;
    static void reset(t_Ty* a_pInstance, byte const*& a_pInBuffer)   ;

    o_forceinline static void remember(t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
            remember(reinterpret_cast<t_Ty const*>(pChunk), a_pOutBuffer);
        }
    }
    o_forceinline static void reset(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
            reset(reinterpret_cast<t_Ty*>(pChunk), a_pInBuffer);
        }
    }
    
};


template<typename t_Ty, boolean t_is_root>
struct root_class_state_machine_serializer_helper
{
    o_forceinline static void serialize(t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) {    }
    o_forceinline static void deserialize(t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)     {    }
    o_forceinline static void serialize(t_Ty const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)     {    }
    o_forceinline static void deserialize(t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)    {    }
    o_forceinline static void serialize(t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)    {    }
    o_forceinline static void deserialize(t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)     {    }
    o_forceinline static void serialize(t_Ty const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)     {    }
    o_forceinline static void deserialize(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)    {    }
};

template<typename t_Ty, boolean t_is_root>
struct root_class_state_machine_resetter_helper
{
    o_forceinline static void remember(t_Ty const* a_pInstance, byte*& a_pOutBuffer) {    }
    o_forceinline static void reset(t_Ty* a_pInstance, byte const*& a_pInBuffer)     {    }
    o_forceinline static void remember(t_Ty const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)     {    }
    o_forceinline static void reset(t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)    {    }
};

template<typename t_Ty>
struct root_class_state_machine_serializer_helper<t_Ty, true> 
    : public state_machine_serializer<t_Ty>
{

};

template<typename t_Ty>
struct root_class_state_machine_resetter_helper<t_Ty, true> 
    : public state_machine_resetter<t_Ty>
{

};

template<typename t_Ty>
struct root_class_state_machine_serializer 
    : public root_class_state_machine_serializer_helper<t_Ty
    , has_root_statechart<t_Ty>::value>
{

};

template<typename t_Ty>
struct root_class_state_machine_resetter
    : public root_class_state_machine_resetter_helper<t_Ty
    , has_root_statechart<t_Ty>::value>
{

};

o_namespace_end(phantom, state, detail)

o_namespace_begin(phantom, state)

class base_state_machine_data
{
public:
    enum EFlag
    {
        e_Flag_Updating = 1,
        e_Flag_Dispatching = 2,
        e_Flag_Inactive = 4,
    };
    o_forceinline StateMachine* stateMachine() const { return state_machine; }
    o_forceinline void          initialize() const ;
    o_forceinline void          terminate() const ;
    o_forceinline void          update() const ;
    o_forceinline void          reset() const ;
    o_forceinline void          postEvent(uint a_uiEventId) const ;

public:
    base_state_machine_data(void* a_pOwner, StateMachine* a_pStateMachine) 
        : owner(a_pOwner)
        , state_machine(a_pStateMachine) 
        , flags(e_Flag_Inactive) 
        , lock_counter(0L)
        , event_queue_size(0)
    {
        memset(event_queue, 0xff, sizeof(event_queue));
    }

    o_forceinline void lock() 
    { 
        o_assert(lock_counter < UCHAR_MAX);
        lock_counter++; 
    }
    o_forceinline void unlock() 
    { 
        lock_counter--; 
        o_assert(lock_counter < UCHAR_MAX);
    }
    o_forceinline bool isLocked() const
    {
        return lock_counter != 0;
    }

protected:
    void*                   owner;
    StateMachine*           state_machine;
    phantom::state::State*  history_state;
    phantom::uint8          event_queue[o__uint__state_machine_event_queue_size];
    phantom::uint8          lock_counter;
    phantom::uint8          flags;
    phantom::uint8          event_queue_size;
};

o_namespace_end(phantom, state)



o_namespace_begin(phantom, state, native)

template<typename t_ObjectClass>
class state_machine_data : public base_state_machine_data
{
public:
    template <typename> friend class phantom::reflection::native::TType;
    template <typename> friend struct phantom::state::detail::state_machine_serializer;
    template <typename> friend struct phantom::state::detail::state_machine_resetter;
    template <typename, typename, typename, typename> friend class phantom::state::native::TNativeTransition;
    friend class phantom::state::native::TNativeStateMachine<t_ObjectClass>;
    friend class phantom::state::native::TNativeState<t_ObjectClass>;
    friend class phantom::state::native::TNativeTrack<t_ObjectClass>;
    template<typename, uint> friend class default_installer_helper;
    
    typedef phantom::state::native::TNativeStateMachine<t_ObjectClass> state_machine_class;
    typedef phantom::state::native::TNativeState<t_ObjectClass> state_class;
    typedef phantom::state::native::TNativeTrack<t_ObjectClass> track_class;
    
public:
    state_machine_data(void* a_pBase)
    : base_state_machine_data(a_pBase, native::TNativeStateMachine<t_ObjectClass>::Instance()) 
    
    {
        memset(current_states, 0, phantom::track_count_cascade_of<t_ObjectClass>::value*sizeof(state_class*));
        memset(transit_states, 0, phantom::track_count_cascade_of<t_ObjectClass>::value*sizeof(state_class*));
    }
    
protected:
    state_class*    current_states[phantom::track_count_cascade_of<t_ObjectClass>::value];    
    state_class*    transit_states[phantom::track_count_cascade_of<t_ObjectClass>::value];
    
};

template <typename _EventClass>
class native_event_registrer
{
public:
    native_event_registrer()
    {
        _EventClass::Id();
    }
};

template <typename t_Ty, typename t_Src, typename t_Event, typename t_Dest>
struct native_transition_registrer
{
    native_transition_registrer()
    {
        TNativeStateMachine<t_Ty>::Instance()->addTransition(t_Src::Instance(), t_Event::Id(), t_Dest::Instance());
    }
};

o_namespace_end(phantom, state, native)


#endif // statechart_h__
