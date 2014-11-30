/* ******************* Includes ****************** */
#include "phantom/jit.h"
#include "JitStateMachine.h"
#include "JitStateMachine.hxx"
#include "JitState.h"
#include "JitTrack.h"
/* *********************************************** */
o_registerN((phantom, state, jit), JitStateMachine);

o_namespace_begin(phantom, state, jit)

JitStateMachine::JitStateMachine( bitfield modifiers /*= bitfield()*/ ) 
: StateMachine(modifiers) , m_uiDataSize(sizeof(jit_state_machine_data)) , m_uiDataPtrOffset(0xffffffff) , m_bCompiled(false)
{

}


o_namespace_end(phantom, state, jit)