#pragma once

//#if defined(o__bool__enable_bitfield_type)
o_classN((phantom), bitfield)
{
    o_reflection
    {
        o_data_member(int, m_iContent, o_no_range, o_protected);
    };
};
o_exposeN((phantom), bitfield);
//#endif