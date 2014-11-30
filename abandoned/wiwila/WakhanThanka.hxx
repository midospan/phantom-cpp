#include "Taku.hxx"

o_classN((wakhan), WakhanThanka, o_public|o_singleton)
{
    o_reflection 
    {
        o_data_member(phantom::component<Nagi>, m_Spirits, o_no_range, o_protected);
        o_signal(loveSpread, (float), o_protected);
    };
};
