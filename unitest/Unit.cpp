/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
/* ** The Class Header must be the last #include * */
#include "Unit.h"
#include "phantom/composition.hxx"
#include "Ability.h"
#include "phantom/vector.hxx"
/* *********************************************** */
#if o__int__reflection_template_use_level != 3
#include "Unit.hxx"
#endif

o_registerN((sc2), Unit);
o_registerNTI((phantom), composition, (sc2::Ability));

o_namespace_begin(sc2)

Unit::Unit( void ) 
    : m_Abilities(&Ability::setUnit, &Ability::getUnit) 
    , m_bPatrolWay(false)
    , m_iLifePoints(-1)
    , m_iInitialLifePoints(-1)
{

}

o_namespace_end(sc2)
