#pragma once

o_classN((phantom, reflection), CodePosition, o_pod)
{
    o_reflection
    {
        o_data_member(int, line, (0, std::numeric_limits<int>::max()), o_public);
        o_data_member(int, column, (0, std::numeric_limits<int>::max()), o_public);
    };
};
o_exposeN((phantom, reflection), CodePosition);

o_classN((phantom, reflection), CodeLocation, o_pod)
{
    o_reflection
    {
        o_data_member(CodePosition, m_Start, o_no_range, o_protected);
        o_data_member(CodePosition, m_End, o_no_range, o_protected);
        o_property(const CodePosition&, start, setStart, getStart, o_no_signal, o_no_range, o_transient|o_public);
        o_property(const CodePosition&, end, setEnd, getEnd, o_no_signal, o_no_range, o_transient|o_public);
    };
};
o_exposeN((phantom, reflection), CodeLocation);