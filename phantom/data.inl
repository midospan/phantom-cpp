

template<typename t_Ty>
inline data::data(t_Ty* const a_address)
{
    const rtti_data& rd = rttiDataOf(a_address);
    m_address = rd.base ? rd.base : a_address;
    if(rd.object_class)
        m_type = (phantom::reflection::Type*)rd.object_class ;
    else
        m_type = typeOf<t_Ty>();
    o_assert(m_type, "t_Ty must have reflection");
}


template<typename t_Ty>
inline data const& data::operator=(t_Ty* const a_address)
{
    const rtti_data& rd = rttiDataOf(a_address);
    m_address = rd.base ? rd.base : a_address;
    if(rd.object_class)
        m_type = (phantom::reflection::Type*)rd.object_class ;
    else
        m_type = typeOf<t_Ty>();
    return *this;
}