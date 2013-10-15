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

#ifndef unitest_ActorPlatform_h__
#define unitest_ActorPlatform_h__
// #pragma __PragmaPrintActorPlatform__


/* ****************** Includes ******************* */
#include "GameEntity.h"
/* **************** Declarations ***************** */
o_declare(class, sc2, RallyPoint)
o_declare(class, sc2, Ability)
/* *********************************************** */

o_namespace_begin(sc2)

class ActorPlatform : public GameEntity
{

public:
    ActorPlatform(void) {}

    o_destructor ~ActorPlatform(void) {}

	o_enter(OnGround) {}
    o_update(OnGround) ;
	o_leave(OnGround) {}

	o_enter(Static) {}
	o_update(Static) {}
	o_leave(Static) {}

	o_enter(Alt_Static) {}
	o_update(Alt_Static) {}
	o_leave(Alt_Static) {}

	o_enter(Walk) {}
	o_update(Walk) {}
	o_leave(Walk) {}

	o_enter(Run) {}
	o_update(Run) {}
	o_leave(Run) {}

	o_enter(Slide) {}
	o_update(Slide) {}
	o_leave(Slide) {}

	o_enter(Stop) {}
	o_update(Stop) {}
	o_leave(Stop) {}

	o_enter(InTheAir) {}
	o_update(InTheAir) {}
	o_leave(InTheAir) {}

	o_enter(Jump) {}
	o_update(Jump) {}
	o_leave(Jump) {}

	o_enter(Fall) {}
	o_update(Fall) {}
	o_leave(Fall) {}

	o_enter(Land) {}
	o_update(Land) {}
	o_leave(Land) {}


protected:

};

o_namespace_end(sc2)

o_classNS((sc2), ActorPlatform, (GameEntity))
{
    o_reflection 
    {

    };
    o_statechart
    {
		o_track(Behavior, Spawned);

		o_state(OnGround, Behavior);
			o_track(Ground, OnGround);
				o_state(Static, Ground);
				o_state(Alt_Static, Ground);
				o_state(Walk, Ground);
				o_state(Run, Ground);
				o_state(Slide, Ground);
				o_state(Stop, Ground);
		o_state(InTheAir, Behavior);
			o_track(Air, InTheAir);
				o_state(Jump, Air);
				o_state(Fall, Air);
				o_state(Land, Air);

		o_event(NSecondsInStatic);
		o_event(WalkRequired);
		o_event(WalkCanceled);
		o_event(RunRequired);
		o_event(RunCanceled);
		o_event(StopRequired);
		o_event(SlideRequired);
		o_event(AnimationEnded);
		o_event(JumpRequired);
		o_event(Fell);
		o_event(Landed);

		// On ground
		o_transition(OnGround, JumpRequired, Jump);
		o_transition(OnGround, Fell, Fall);

		o_transition(Static, NSecondsInStatic, Alt_Static);
		o_transition(Static, WalkRequired, Walk);

		o_transition(Alt_Static, WalkRequired, Walk);
		o_transition(Alt_Static, AnimationEnded, Static);

		o_transition(Walk, WalkCanceled, Static);
		o_transition(Walk, RunRequired, Run);
		o_transition(Walk, SlideRequired, Slide);

		o_transition(Run, RunCanceled, Walk);
		o_transition(Run, StopRequired, Stop);
		o_transition(Run, SlideRequired, Slide);

		o_transition(Stop, AnimationEnded, Static);
		o_transition(Slide, AnimationEnded, Static);

		// In the air
		o_transition(InTheAir, JumpRequired, Jump);

		o_transition(Jump, Fell, Fall);
		o_transition(Fall, Landed, Land);
		o_transition(Land, AnimationEnded, Static);
    };
};
o_exposeN((sc2), ActorPlatform);

o_static_assert(!phantom::has_initializer_method_initialize_declared<sc2::ActorPlatform>::value);
o_static_assert(phantom::has_initializer_method_initialize<sc2::ActorPlatform>::value);
o_static_assert(phantom::track_count_of<sc2::ActorPlatform>::value == 3);
o_static_assert(phantom::track_count_cascade_of<sc2::ActorPlatform>::value == 4);

#endif

