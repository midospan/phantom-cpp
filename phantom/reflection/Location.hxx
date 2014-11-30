#pragma once

o_structureN((phantom, reflection), CodePosition)
(
    o_data_member(int, line, (0, std::numeric_limits<int>::max()));
    o_data_member(int, column, (0, std::numeric_limits<int>::max()));
);

o_structureN((phantom, reflection), CodeLocation)
(
o_public:
    o_property(const CodePosition&, start, setStart, getStart, o_no_signal, o_no_range, o_transient);
    o_property(const CodePosition&, end, setEnd, getEnd, o_no_signal, o_no_range, o_transient);

o_protected:
    o_data_member(CodePosition, m_Start);
    o_data_member(CodePosition, m_End);
);
