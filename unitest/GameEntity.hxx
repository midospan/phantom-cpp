
o_classN((sc2), GameEntity)
(
    o_statechart
    (
        o_state(Pooled, Root)
        o_state(Spawned, Root)
        o_event(Spawn)
        o_transition(Pooled, Spawn, Spawned)
    );
);



o_static_assert(phantom::has_initializer_member_function_initialize_declared<sc2::GameEntity>::value);
o_static_assert(phantom::has_statechart<sc2::GameEntity>::value);
o_static_assert(phantom::has_root_statechart<sc2::GameEntity>::value);
o_static_assert(phantom::track_count_of<sc2::GameEntity>::value == 1);
o_static_assert(phantom::track_count_cascade_of<sc2::GameEntity>::value == 1);