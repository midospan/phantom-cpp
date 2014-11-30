#ifndef o_phantom_moon_JitState_h__
#define o_phantom_moon_JitState_h__


/* ****************** Includes ******************* */
#include <phantom/jit.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, state, jit), JitState);
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
};

o_namespace_end(phantom, state, jit)

#endif
