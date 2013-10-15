#ifndef o_phantom_serialization_h__
#define o_phantom_serialization_h__

o_namespace_begin(phantom, serialization)

class data_guid_base
{
    typedef unordered_map<void*,uint>    guid_map;
    typedef unordered_map<uint, phantom::data>    object_map;

public:
    typedef guid_map::const_iterator    guid_const_iterator;
    typedef object_map::const_iterator    object_const_iterator;

    object_const_iterator       objectBegin() const { return m_object_map.begin(); }
    object_const_iterator       objectEnd() const { return m_object_map.end(); }
    guid_const_iterator         guidBegin() const { return m_guid_map.begin(); }
    guid_const_iterator         guidEnd() const { return m_guid_map.end(); }

    size_t                      getSize() const { return m_guid_map.size(); }
    phantom::boolean            isEmpty() const { return m_guid_map.empty(); }

    const phantom::data&     getData(uint a_guid) const 
    {
        static phantom::data null_data(0,0);
        object_map::const_iterator found = m_object_map.find(a_guid);
        return found == m_object_map.end() ? null_data : found->second;
    }

    void*           dataAddress(uint guid) const 
    {
        return getData(guid).address();
    }

    reflection
        ::Type*     dataType(uint guid) const 
    {
        return getData(guid).type();
    }

    uint            getGuid(void* a_pAddress) const 
    {
        guid_map::const_iterator found = m_guid_map.find(a_pAddress);
        return found == m_guid_map.end() ? 0xFFFFFFFF : found->second;
    }

    uint            getGuid(const phantom::data& a_Data) const 
    {
        return getGuid(a_Data.address());
    }

    void            add(uint a_guid, const phantom::data& a_Data)
    {
        o_assert(m_guid_map.find(a_Data.address()) == m_guid_map.end());
        m_guid_map[a_Data.address()] = a_guid;
        m_object_map[a_guid] = a_Data;
    }

    void    remove(uint a_guid)
    {
        object_map::iterator object_found = m_object_map.find(a_guid);
        o_assert(object_found != m_object_map.end());
        guid_map::iterator guid_found = m_guid_map.find(object_found->second.address());
        m_guid_map.erase(guid_found);
        m_object_map.erase(object_found);
    }

    void    remove(void* a_object)
    {
        guid_map::iterator guid_found = m_guid_map.find(a_object);
        o_assert(guid_found != m_guid_map.end());
        object_map::iterator object_found = m_object_map.find(guid_found->second);
        m_guid_map.erase(guid_found);
        m_object_map.erase(object_found);
    }

protected:
    guid_map    m_guid_map;
    object_map    m_object_map;
};

o_namespace_end(phantom, serialization)

o_namespace_begin(phantom)

using serialization::data_guid_base;

o_namespace_end(phantom)

#endif // serialization_h__