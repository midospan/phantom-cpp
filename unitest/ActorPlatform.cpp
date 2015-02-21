/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
/* ** The Class Header must be the last #include * */
#include "ActorPlatform.h"
#if o__int__reflection_template_use_level != 3
#include "ActorPlatform.hxx"
#endif
/* *********************************************** */
o_registerN((sc2), ActorPlatform)

o_namespace_begin(sc2)


o_update(ActorPlatform::OnGround) { 
    o_statemachine_post(JumpRequired);
}

o_namespace_end(sc2)