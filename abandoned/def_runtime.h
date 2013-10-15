#include <phantom/phantom.h>


#define o_state_ppCurrentState(_pObject_) \
    reinterpret_cast<State**>(reinterpret_cast<byte*>(_pObject_)+m_uiCurrentStateOffset)
#define o_state_ppTransitState(_pObject_) \
    reinterpret_cast<State**>(reinterpret_cast<byte*>(_pObject_)+m_uiTransitStateOffset)
#define o_state_ppHistoryState(_pObject_) \
    reinterpret_cast<State**>(reinterpret_cast<byte*>(_pObject_)+static_cast<RuntimeStateMachine*>(m_pStateMachine)->m_uiHistoryStateOffset)


#include <phantom/state/runtime/RuntimeTrack.h>
#include <phantom/state/runtime/RuntimeState.h>
#include <phantom/state/runtime/RuntimeTransition.h>
#include <phantom/state/runtime/RuntimeStateMachine.h>

#include <phantom/reflection/runtime/RuntimeClass.h>
#include <phantom/reflection/runtime/RuntimeInstanceAttribute.h>
#include <phantom/reflection/runtime/RuntimeStaticAttribute.h>
#include <phantom/reflection/runtime/ScriptClass.h>

/*
o_reflection_in_cpp_deferred_setup(phantom, reflection, runtime, RuntimeClass)
o_reflection_in_cpp_deferred_setup(phantom, reflection, runtime, RuntimeInstanceAttribute)
o_reflection_in_cpp_deferred_setup(phantom, reflection, runtime, RuntimeStaticAttribute)
o_reflection_in_cpp_deferred_setup(phantom, reflection, runtime, ScriptClass)

o_reflection_in_cpp_deferred_setup(phantom, state, runtime, RuntimeState)
o_reflection_in_cpp_deferred_setup(phantom, state, runtime, RuntimeTrack)
o_reflection_in_cpp_deferred_setup(phantom, state, runtime, RuntimeStateMachine)
o_reflection_in_cpp_deferred_setup(phantom, state, runtime, RuntimeTransition)*/