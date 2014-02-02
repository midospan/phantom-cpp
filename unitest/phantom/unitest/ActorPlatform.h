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
o_declareN(class, (sc2), RallyPoint)
o_declareN(class, (sc2), Ability)
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

#if o__int__reflection_template_use_level == 3
#   include "ActorPlatform.hxx"
#else 
    o_declareN(class, (sc2), ActorPlatform);
#endif

#endif

