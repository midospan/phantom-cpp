/* ******************* Includes ****************** */
#include <phantom/phantom.h>
#include "StateMachineTest.h"
/* *********************************************** */
o_registerN((unitest), StateMachineTest);

o_namespace_begin(unitest)

o_enter(StateMachineTest::A) {}
o_update(StateMachineTest::A){}
o_leave(StateMachineTest::A) { o_statemachine_post(this, CtoD); }

o_enter(StateMachineTest::B) {  }
o_update(StateMachineTest::B) {}
o_leave(StateMachineTest::B) {}

o_enter(StateMachineTest::C) {}
o_update(StateMachineTest::C) {}
o_leave(StateMachineTest::C) { o_statemachine_post(this, AtoB); }

o_enter(StateMachineTest::D) { o_statemachine_post(this, BtoA); }
o_update(StateMachineTest::D) {}
o_leave(StateMachineTest::D) {}

o_namespace_end(unitest)