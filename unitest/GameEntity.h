/* TODO LICENCE HERE */

#ifndef unitest_GameEntity_h__
#define unitest_GameEntity_h__

/* ****************** Includes ******************* */
#include "phantom/phantom.h"
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(sc2)

class GameEntity 
{
    o_statemachine;

public:
    GameEntity(void) {}
    o_destructor ~GameEntity(void) {}

    o_initialize() 
    {

    }

    o_terminate() 
    {

    }

    o_restore(filter, pass) 
    {
        return phantom::restore_complete;
    }


    o_enter(Pooled) { }
    o_update(Pooled) { }
    o_leave(Pooled) {  }
  
    o_enter(Spawned) { }
    o_update(Spawned) { }
    o_leave(Spawned) { }

};

o_namespace_end(sc2)

#if o__int__reflection_template_use_level == 3
#include "GameEntity.hxx"
#else 
    o_declareN(class, (sc2), GameEntity);
#endif

#endif
