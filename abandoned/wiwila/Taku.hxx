#pragma once

o_classN((wakhan), Taku)
{
    o_reflection 
    {
        o_data_member(Nagi*, m_pSpirit, o_no_range, o_protected);
        o_property(Nagi*, spirit, setSpirit, getSpirit, spiritChanged, o_no_range, o_public);
    };
    o_statechart
    {
        o_state(Alive, Root);
            o_track(MindState, Alive);
                o_state(Mindfulness, MindState);
                o_state(Cerebration, MindState);
                o_event(Meditate);
                o_event(ThinkTooMuch);
                o_transition(Cerebration, Meditate, Mindfulness);
                o_transition(Mindfulness, ThinkTooMuch, Cerebration);
        o_state(Dead, Root);
        o_event(Created);
        o_event(Killed);
        o_transition(Dead, Created, Alive);
        o_transition(Alive, Killed, Dead);
    };
};














