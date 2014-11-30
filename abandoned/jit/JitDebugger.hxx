#pragma 

o_classN((phantom, reflection, jit), JitDebugger)
{
	o_reflection
    {
        o_signal(debuggerBroke, ());
        o_signal(debuggerResumed, ());
        o_slot(void, subroutineCreated, (void*));
        o_slot(void, subroutineDestroyed, (void*));
	};
};
o_exposeN((phantom, reflection, jit), JitDebugger);

