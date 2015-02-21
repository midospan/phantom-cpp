#include "GameEntity.hxx"

o_classNB((sc2), ActorPlatform, (GameEntity))
(
    o_statechart
    (
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
    );
);


o_static_assert(!phantom::has_initializer_member_function_initialize_declared<sc2::ActorPlatform>::value);
o_static_assert(phantom::has_initializer_member_function_initialize<sc2::ActorPlatform>::value);
o_static_assert(phantom::track_count_of<sc2::ActorPlatform>::value == 3);
o_static_assert(phantom::track_count_cascade_of<sc2::ActorPlatform>::value == 4);