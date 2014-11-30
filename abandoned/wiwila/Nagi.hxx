#pragma once

o_classN((wakhan), Nagi)
{
    o_reflection 
    {
        o_constructor((Nagi*), o_protected);
        o_data_member(Nagi*, m_pSpirit, o_no_range, o_protected);
        o_signal(loveReceived, (float), o_protected);
    };
};