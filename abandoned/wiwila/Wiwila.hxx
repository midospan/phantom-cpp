#include "Taku.hxx"

o_classNB((wakhan), Wiwila, (Taku))
{
    o_reflection 
    {
        o_data_member(phantom::aggregation<Takula>, m_Entities, o_no_range, o_protected);
        o_data_member(phantom::component<Mni>, m_Water, o_no_range, o_protected);
    };
    o_statechart
    {
        o_track(Flow, Alive);
            o_state(Flows, Flow);
            o_state(Drought, Flow);
    };
};
