#include "phantom/phantom.h"

o_namespace_begin(phantom, serialization)

const phantom::data& data_guid_base::getData( uint a_guid ) const
{
    static phantom::data null_data(0,0);
    object_map::const_iterator found = m_object_map.find(a_guid);
    return found == m_object_map.end() ? null_data : found->second;
}

uint data_guid_base::getGuid( void* a_pAddress ) const
{
    guid_map::const_iterator found = m_guid_map.find(a_pAddress);
    return found == m_guid_map.end() ? 0xFFFFFFFF : found->second;
}

uint data_guid_base::getGuid( const phantom::data& a_Data ) const
{
    return getGuid(a_Data.address());
}

o_namespace_end(phantom, serialization)
