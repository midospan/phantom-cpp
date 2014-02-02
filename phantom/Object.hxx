#pragma once
// Data serializer
o_classN((phantom), object)
{
    o_reflection
    {
        o_data_member(void*, m_address, o_no_range, o_public);
        o_data_member(phantom::reflection::ClassType*, m_class_type, o_no_range, o_public);
    };
};
o_exposeN((phantom), object);