/*
    This file is part of PHANTOM
         P reprocessed
         H igh-level
         A llocator
         N ested state-machines and
         T emplate
         O riented
         M eta-programming

    For the latest infos and sources, see http://code.google.com/p/phantom-cpp

    Copyright (C) 2008-2011 by Vivien MILLET

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE
*/

#ifndef state_native_TNativeState_h__
#define state_native_TNativeState_h__
// #pragma message("Including "__FILE__)

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, state, native)

template <typename _StateClass, typename t_ObjectClass>
class native_state_registrer
{
public:
    native_state_registrer()
    {
        typename _StateClass::placeholder_type* pState = _StateClass::Instance();
        string name = pState->getName();
        string enter_func_name = name+o_CS("_enter()");
        string update_func_name = name+o_CS("_update()");
        string leave_func_name = name+o_CS("_leave()");
        phantom::reflection::InstanceMemberFunction*    pEnterMemberFunction = classOf<t_ObjectClass>()->getInstanceMemberFunctionCascade(enter_func_name);
        if(pEnterMemberFunction == NULL)
        {
            classOf<t_ObjectClass>()->addMemberFunction(phantom::reflection::native::TNativeMemberFunctionProvider<t_ObjectClass, 0, void()>::CreateMemberFunction(
                enter_func_name
                , StateMachine::StateMemberFunctionSignature()
                , pState->getEnterFunctionPointer())
                );
        }
        phantom::reflection::InstanceMemberFunction*    pUpdateMemberFunction = classOf<t_ObjectClass>()->getInstanceMemberFunctionCascade(update_func_name);
        if(pUpdateMemberFunction == NULL)
        {
            classOf<t_ObjectClass>()->addMemberFunction(phantom::reflection::native::TNativeMemberFunctionProvider<t_ObjectClass, 0, void()>::CreateMemberFunction(
                update_func_name
                , StateMachine::StateMemberFunctionSignature()
                , pState->getUpdateFunctionPointer())
                );
        }

        phantom::reflection::InstanceMemberFunction*    pLeaveMemberFunction = classOf<t_ObjectClass>()->getInstanceMemberFunctionCascade(leave_func_name);
        if(pLeaveMemberFunction == NULL)
        {
            classOf<t_ObjectClass>()->addMemberFunction(phantom::reflection::native::TNativeMemberFunctionProvider<t_ObjectClass, 0, void()>::CreateMemberFunction(
                leave_func_name
                , StateMachine::StateMemberFunctionSignature()
                , pState->getLeaveFunctionPointer())
                );
        }
    }
};


o_namespace_end(phantom, state, native)

o_namespace_begin(phantom, state, native)

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
    typedef reflection::native::TNativeInstanceMemberFunction<t_ObjectClass, void()>    NativeInstanceMemberFunctionClass;
    typedef native::state_machine_data<object_class>    instance_data;
    typedef o_NESTED_TYPE first_super_statechart_class_of<t_ObjectClass>::type        root_object_class;

public:
    TNativeState(const string& a_strName
        , state_function_pointer a_pEnterFunctionPointer
        , state_function_pointer a_pUpdateFunctionPointer
        , state_function_pointer a_pLeaveFunctionPointer
        , uint a_uiOrderingFactor
        , bitfield bf = 0)
            : State(a_strName, a_uiOrderingFactor, bf)
            , m_pEnterFunctionPointer(a_pEnterFunctionPointer)
            , m_pUpdateFunctionPointer(a_pUpdateFunctionPointer)
            , m_pLeaveFunctionPointer(a_pLeaveFunctionPointer)
    {

    }
    o_destructor ~TNativeState(void)     {}

    virtual void deleteNow() { o_dynamic_proxy_delete(phantom::state::State, phantom::state::State::metaType, self_type) this; }

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

o_namespace_end(phantom, state, native)

#undef TNativeState_smdataptr

    /*o_traits_specialize_all_super_traitNTS(
    (phantom,state,native)
    , (typename)
    , (t_Ty)
    , TNativeState
    , (State)
    )*/

#endif
