
template<typename t_Ty>
inline object::object(t_Ty* const a_address)
{
    // class
    const rtti_data& rd = rttiDataOf(a_address);
    m_address = rd.base ? rd.base : a_address;
    if(rd.object_class)
        m_class_type = (phantom::reflection::ClassType*)rd.object_class ;
    else
        m_class_type = typeOf<t_Ty>();
}

template<typename t_Ty>
inline object& object::operator=(t_Ty* const a_address)
{
    const rtti_data& rd = rttiDataOf(a_address);
    m_address = rd.base ? rd.base : a_address;
    if(rd.object_class)
        m_class_type = (phantom::reflection::ClassType*)rd.object_class ;
    else
        m_class_type = typeOf<t_Ty>();
    return *this;
}