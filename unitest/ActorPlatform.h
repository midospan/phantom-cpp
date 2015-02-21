/* TODO LICENCE HERE */

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

