#include "Unit.hxx"
#include "phantom/variant.h"

o_classNB((sc2), Marine, (Unit))
(
    o_attribute("appearance", "rock");
    o_attribute("level", 10);
    o_friend(Ability);
    o_using_member(Unit::m_iLifePoints);
    o_statechart
    (
        o_track(StimPackAbility, Alive);
            o_state(StimPackDisabled, StimPackAbility);
            o_state(StimPackEnabled, StimPackAbility);
            o_event(StimPackRequested);
            o_event(StimPackFinished);
            o_transition(StimPackEnabled, StimPackRequested, StimPackEnabled);
            o_transition(StimPackDisabled, StimPackRequested, StimPackEnabled);
            o_transition(StimPackEnabled, StimPackFinished, StimPackDisabled);
    );
);


o_static_assert(phantom::has_initializer_member_function_initialize<sc2::Marine>::value);
o_static_assert(!phantom::has_initializer_member_function_initialize_declared<sc2::Marine>::value);