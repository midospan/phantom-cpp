#pragma once
// Data serializer
namespace phantom
{
    namespace extension
    {
        template<>
        class serializer<phantom::data>
        {
        public:
            static void serialize(reflection::Type* a_pType, phantom::data const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                uint guid = a_pDataBase ? a_pDataBase->getGuid(*a_pInstance) : (uint)(a_pInstance->address());
                serializer<uint>::serialize(typeOf<uint>(), &guid, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            }
            static void deserialize(reflection::Type* a_pType, phantom::data* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                uint guid = 0;
                serializer<size_t>::deserialize(typeOf<uint>(), &guid, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
                *a_pInstance = a_pDataBase ? a_pDataBase->getData(guid) : phantom::data((void*)guid);
            }
            static void serialize(reflection::Type* a_pType, phantom::data const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
                while(a_uiCount--)
                {
                    phantom::data const* pInstance = reinterpret_cast<phantom::data const*>(pChunk);
                    serialize(a_pType, pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
                    pChunk += a_uiChunkSectionSize;
                }
            }
            static void deserialize(reflection::Type* a_pType, phantom::data* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
                while(a_uiCount--)
                {
                    phantom::data* pInstance = reinterpret_cast<phantom::data*>(pChunk);
                    deserialize(a_pType, pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
                    pChunk += a_uiChunkSectionSize;
                }
            }
            static void serialize(reflection::Type* a_pType, phantom::data const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                uint guid = a_pDataBase ? a_pDataBase->getGuid(*a_pInstance) : (uint)a_pInstance->address();
                a_OutBranch.put_value(phantom::lexical_cast<string>(guid));
            }
            static void deserialize(reflection::Type* a_pType, phantom::data* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                boost::optional<string> opt = a_InBranch.get_value_optional<string>();
                if(opt.is_initialized())
                {
                    uint guid = phantom::lexical_cast<uint>(*opt);
                    *a_pInstance = a_pDataBase ? a_pDataBase->getData(guid) : phantom::data((void*)guid);
                }
                else *a_pInstance = phantom::data();
            }
            static void serialize(reflection::Type* a_pType, phantom::data const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
                int i = 0;
                while(a_uiCount--)
                {
                    phantom::data const* pInstance = reinterpret_cast<phantom::data const*>(pChunk);
                    serialize(a_pType, pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
                    pChunk += a_uiChunkSectionSize;
                }
            }
            static void deserialize(reflection::Type* a_pType, phantom::data* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
                int i = 0;
                while(a_uiCount--)
                {
                    phantom::data* pInstance = reinterpret_cast<phantom::data*>(pChunk);
                    deserialize(a_pType, pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
                    pChunk += a_uiChunkSectionSize;
                }
            }
            static void serializeLayout(reflection::Type* a_pType, phantom::data const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                serialize(a_pType, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            }
            static void deserializeLayout(reflection::Type* a_pType, phantom::data* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                deserialize(a_pType, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            }
            static void serializeLayout(reflection::Type* a_pType, phantom::data const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            }
            static void deserializeLayout(reflection::Type* a_pType, phantom::data* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            }
            static void serializeLayout(reflection::Type* a_pType, phantom::data const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                serialize(a_pType, a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
            }
            static void deserializeLayout(reflection::Type* a_pType, phantom::data* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                deserialize(a_pType, a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
            }
            static void serializeLayout(reflection::Type* a_pType, phantom::data const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
            }
            static void deserializeLayout(reflection::Type* a_pType, phantom::data* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
            {
                deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
            }
        };
    }
}

o_classN((phantom), data)
{
    o_reflection
    {
        o_data_member(void*, m_address, o_no_range, o_public);
        o_data_member(phantom::reflection::Type*, m_type, o_no_range, o_public);
    };
};
o_exposeN((phantom), data);