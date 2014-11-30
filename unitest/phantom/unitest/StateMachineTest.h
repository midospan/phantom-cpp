#ifndef o_unitest_StateMachineTest_h__
#define o_unitest_StateMachineTest_h__


/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(unitest)

class StateMachineTest
{
    o_statemachine
public:
	StateMachineTest(void) {}
	~StateMachineTest(void) {}


    o_initialize()
    {
    }

    o_terminate()
    {
    }

    void update() { o_statemachine_update(); }

    o_enter(Active) {}
    o_update(Active) {}
    o_leave(Active) {}
	
    o_enter(A);
    o_update(A);
    o_leave(A);

    o_enter(B);
    o_update(B);
    o_leave(B) ;
               ;
    o_enter(C) ;
    o_update(C);
    o_leave(C) ;
               ;
    o_enter(D) ;
    o_update(D);
    o_leave(D) ;

protected:

};

o_namespace_end(unitest)

o_classN((unitest), StateMachineTest)
(
    o_statechart 
    (
        o_state(Active, Root);
        o_track(AB, Active);
            o_state(A, AB);
            o_state(B, AB);
        o_track(CD, Active);
            o_state(C, CD);
            o_state(D, CD);
            o_event(AtoB);
            o_event(AtoA);
        o_event(BtoA);
        o_event(CtoD);
        o_event(DtoC);
        o_transition(A, AtoB, B);
        o_transition(A, AtoA, A);
        o_transition(B, BtoA, A);
        o_transition(C, CtoD, D);
        o_transition(D, DtoC, C);
    );
);


#endif
