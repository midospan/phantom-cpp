#include "Marine.hxx"

o_classNS((sc2), Bench, (Marine))
{
    o_reflection 
    {
        o_property(float,          value0, setValue0, getValue0, o_no_signal, o_no_range, o_public);
        o_property(int,            value1, setValue1, getValue1, o_no_signal, o_no_range, o_public);
        o_property(unsigned int,   value2, setValue2, getValue2, o_no_signal, o_no_range, o_public);
        o_property(unsigned long,  value3, setValue3, getValue3, o_no_signal, o_no_range, o_public);
        o_property(bool,           value4, setValue4, getValue4, o_no_signal, o_no_range, o_public);
        o_property(char,           value5, setValue5, getValue5, o_no_signal, o_no_range, o_public);
        o_property(short,          value6, setValue6, getValue6, o_no_signal, o_no_range, o_public);
        o_property(long,           value7, setValue7, getValue7, o_no_signal, o_no_range, o_public);
        o_property(long long,      value8, setValue8, getValue8, o_no_signal, o_no_range, o_public);
        o_property(double,         value9, setValue9, getValue9, o_no_signal, o_no_range, o_public);
    };
    o_statechart
    {
        o_track(BenchTrack0, StimPackDisabled)
            o_state(BenchState0, BenchTrack0)
            o_track(BenchTrack1, BenchState0)
            o_state(BenchState1, BenchTrack1)
            o_track(BenchTrack2, BenchState1)
            o_state(BenchState2, BenchTrack2)
            o_track(BenchTrack3, BenchState2)
            o_state(BenchState3, BenchTrack3)
            o_track(BenchTrack4, BenchState3)
            o_state(BenchState4, BenchTrack4)
            o_track(BenchTrack5, BenchState4)
            o_state(BenchState5, BenchTrack5)
            o_track(BenchTrack6, BenchState5)
            o_state(BenchState6, BenchTrack6)
            o_track(BenchTrack7, BenchState6)
            o_state(BenchState7, BenchTrack7)
            o_track(BenchTrack8, BenchState7)
            o_state(BenchState8, BenchTrack8)
            o_track(BenchTrack9, BenchState8)
            o_state(BenchState9, BenchTrack9)
    };
};
o_exposeN((sc2), Bench);

o_static_assert(phantom::has_initializer_member_function_initialize<sc2::Bench>::value);
o_static_assert(!phantom::has_initializer_member_function_initialize_declared<sc2::Bench>::value);