#ifndef o_phantom_moon_JitStateMachine_h__
#define o_phantom_moon_JitStateMachine_h__


/* ****************** Includes ******************* */
#include <phantom/jit.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, state, jit), JitStateMachine);
/* *********************************************** */

o_namespace_begin(phantom, state, jit)


class o_jit_export JitStateMachine : public StateMachine
{
    friend class reflection::jit::JitClass;

public:
	JitStateMachine(bitfield modifiers = bitfield());
	~JitStateMachine(void) {}
	

};

o_namespace_end(phantom, state, jit)

#endif
