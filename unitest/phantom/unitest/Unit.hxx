#include "GameEntity.hxx"

o_classNS((sc2), Unit, (GameEntity))
{
    o_reflection 
    {
        o_typedef(Abilities);
        o_data_member(bool, m_bPatrolWay, o_no_range, o_protected);
        o_data_member(int, m_iLifePoints, o_no_range, o_protected);
        o_data_member(int, m_iInitialLifePoints, o_no_range, o_protected);
        o_data_member(Abilities, m_Abilities, o_no_range, o_protected);
    };
    o_statechart
    {
        o_track(Life, Spawned)

        o_state(Alive, Life)

        o_track(Motion, Alive)

        o_state(Idle, Motion)
        o_state(Move, Motion)
        o_state(Patrol, Motion)

        o_track(Attack, Alive)

        o_state(Pacific, Attack)
        o_state(Hit, Attack)
        o_state(CoolDown, Attack)

        o_track(Visibility, Alive)

        o_state(Visible, Visibility)
        o_state(Invisible, Visibility)

        o_track(Control, Alive)

        o_state(ControlOff, Control)
        o_state(ControlOn, Control)
        o_state(Dead, Life)

        o_event(CoolDownFinished)
        o_event(HitFinished)
        o_transition(CoolDown, CoolDownFinished, Hit)
        o_transition(Hit, HitFinished, CoolDown)
    };
};
o_exposeN((sc2), Unit);

o_static_assert(!phantom::has_initializer_member_function_initialize_declared<sc2::Unit>::value);
o_static_assert(phantom::has_initializer_member_function_initialize<sc2::Unit>::value);
o_static_assert(phantom::track_count_of<sc2::Unit>::value == 5);
o_static_assert(phantom::detail::has_enclosed_statechart<sc2::Unit>::value);
o_static_assert(phantom::detail::has_enclosed_statechart<sc2::GameEntity>::value);
o_static_assert(phantom::has_statechart<sc2::Unit>::value);
o_static_assert(!phantom::has_root_statechart<sc2::Unit>::value);
o_static_assert(!boost::is_same<phantom::proxy_of<sc2::GameEntity>::type, sc2::GameEntity>::value);
o_static_assert(phantom::has_statechart<sc2::GameEntity>::value);
o_static_assert(phantom::track_count_cascade_of<sc2::Unit>::value == 6);