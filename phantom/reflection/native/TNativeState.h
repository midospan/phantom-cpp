/* TODO LICENCE HERE */

#ifndef state_native_TNativeState_h__
#define state_native_TNativeState_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection, native)

template <typename _StateClass, typename t_ObjectClass>
class native_state_registrer
{
public:
    native_state_registrer()
    {
        typename _StateClass::placeholder_type* pState = _StateClass::Instance();
        string name = pState->getName();
        string enter_func_name = name+o_CS("_enter");
        string update_func_name = name+o_CS("_update");
        string leave_func_name = name+o_CS("_leave");
        phantom::reflection::MemberFunction*    pEnterMemberFunction = phantom::reflection::native::currentClass()->getMemberFunctionCascade(enter_func_name+"()");
        if(pEnterMemberFunction == NULL)
        {
            phantom::reflection::native::TNativeMemberFunctionProvider<t_ObjectClass, 0, void()>::CreateMemberFunction(
                enter_func_name
                , "void()"
                , pState->getEnterFunctionPointer());
        }
        phantom::reflection::MemberFunction*    pUpdateMemberFunction = phantom::reflection::native::currentClass()->getMemberFunctionCascade(update_func_name+"()");
        if(pUpdateMemberFunction == NULL)
        {
            phantom::reflection::native::TNativeMemberFunctionProvider<t_ObjectClass, 0, void()>::CreateMemberFunction(
                update_func_name
                , "void()"
                , pState->getUpdateFunctionPointer());
        }

        phantom::reflection::MemberFunction*    pLeaveMemberFunction = phantom::reflection::native::currentClass()->getMemberFunctionCascade(leave_func_name+"()");
        if(pLeaveMemberFunction == NULL)
        {
            phantom::reflection::native::TNativeMemberFunctionProvider<t_ObjectClass, 0, void()>::CreateMemberFunction(
                leave_func_name
                , "void()"
                , pState->getLeaveFunctionPointer());
        }
    }
};


o_namespace_end(phantom, reflection, native)

o_namespace_begin(phantom, reflection, native)

#define TNativeState_smdataptr(_object_) ((instance_data*)(static_cast<root_object_class*>(static_cast<t_ObjectClass*>(_object_))->PHANTOM_CODEGEN_m_smdataptr))

template <typename t_ObjectClass>
class TNativeState : public State
{
public:
   friend class TNativeTrack<t_ObjectClass>;

    typedef void (t_ObjectClass::*state_function_pointer)(void);
    typedef TNativeState<t_ObjectClass> self_type;
    typedef TNativeTrack<t_ObjectClass> track_class;
    typedef TNativeStateMachine<t_ObjectClass> statemachine_class;
    typedef t_ObjectClass object_class;
    typedef reflection::native::TNativeMemberFunction<t_ObjectClass, void()>    NativeMemberFunctionClass;
    typedef state_machine_data<object_class>    instance_data;
    typedef o_NESTED_TYPE first_base_statechart_class_of<t_ObjectClass>::type        root_object_class;

public:
    TNativeState(const string& a_strName
        , state_function_pointer a_pEnterFunctionPointer
        , state_function_pointer a_pUpdateFunctionPointer
        , state_function_pointer a_pLeaveFunctionPointer
        , uint a_uiOrderingFactor
        , modifiers_t bf = 0)
            : State(a_strName, a_uiOrderingFactor, bf)
            , m_pEnterFunctionPointer(a_pEnterFunctionPointer)
            , m_pUpdateFunctionPointer(a_pUpdateFunctionPointer)
            , m_pLeaveFunctionPointer(a_pLeaveFunctionPointer)
    {

    }
    o_destructor ~TNativeState(void)     {}

    virtual generic_member_func_ptr getEnterGenericMemberFunctionPointer() const 
    {
        return m_pEnterFunctionPointer;
    }
    virtual generic_member_func_ptr getUpdateGenericMemberFunctionPointer() const 
    {
        return m_pUpdateFunctionPointer;
    }
    virtual generic_member_func_ptr getLeaveGenericMemberFunctionPointer() const 
    {
        return m_pLeaveFunctionPointer;
    }

    inline void    enter(instance_data* smdataptr)
    {
        o_State_TraceEnter();
        (static_cast<object_class*>(smdataptr->owner)->*m_pEnterFunctionPointer)();
        o_foreach(Track* pTrack, m_Tracks)
        {
            static_cast<track_class*>(pTrack)->enter(smdataptr);
        }
    }

    inline void    update(instance_data* smdataptr)
    {
        (static_cast<object_class*>(smdataptr->owner)->*m_pUpdateFunctionPointer)();
        o_foreach(Track* pTrack, m_Tracks)
        {
            static_cast<track_class*>(pTrack)->update(smdataptr);
        }
    }

    inline void    leave(instance_data* smdataptr)
    {
        o_State_TraceLeave();
        o_foreach(Track* pTrack, m_Tracks)
        {
            static_cast<track_class*>(pTrack)->leave(smdataptr);
        }
        (static_cast<object_class*>(smdataptr->owner)->*m_pLeaveFunctionPointer)();
    }
    
    state_function_pointer getEnterFunctionPointer() const {return m_pEnterFunctionPointer; }
    state_function_pointer getUpdateFunctionPointer() const {return m_pUpdateFunctionPointer;}
    state_function_pointer getLeaveFunctionPointer() const {return m_pLeaveFunctionPointer; }

protected:
    state_function_pointer m_pEnterFunctionPointer;
    state_function_pointer m_pUpdateFunctionPointer;
    state_function_pointer m_pLeaveFunctionPointer;
};

o_namespace_end(phantom, reflection, native)

#undef TNativeState_smdataptr

#endif
