/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/serialization/BinaryFileTreeDataBase.h>
#include <phantom/serialization/BinaryFileTreeDataBase.hxx>
#include "phantom/serialization/BinaryFileTreeNode.h"
/* *********************************************** */
o_registerN((phantom, serialization), BinaryFileTreeDataBase);

o_namespace_begin(phantom, serialization)

BinaryFileTreeDataBase::BinaryFileTreeDataBase( const string& url, uint a_uiSerializationFlag ) 
: FileTreeDataBase(url, a_uiSerializationFlag)
, m_uiBufferSize(0)
{

}

Node* BinaryFileTreeDataBase::createNode( uint a_Guid, Node* a_pParentNode ) const
{
  return o_new(BinaryFileTreeNode)(
    const_cast<BinaryFileTreeDataBase*>(this)
    , a_Guid
    , phantom::as<BinaryFileTreeNode*>(a_pParentNode));
}

void BinaryFileTreeDataBase::destroyNode( Node* a_pNode ) const
{
    o_delete(BinaryFileTreeNode) a_pNode; 
}

void BinaryFileTreeDataBase::saveRuntimeTypes()
{ 
    byte buffer[1000000];
    byte* pBuffer = &(buffer[0]);
    uint count = m_RuntimeTypes.size();

    serializer<uint>::serialize(typeOf<uint>(), &count, pBuffer, 0xffffffff, nullptr);

    auto it = m_RuntimeTypes.begin();
    auto end = m_RuntimeTypes.end();
    for(;it != end; ++it)
    {
        reflection::Type* pType = it->baseInfo.pointer;
        reflection::Class* pClass = classOf(pType);
        uint classGuid = pClass->getGuid();

        string moduleName = pClass->getModule()->getFileName();
        typeOf<string>()->serialize(&moduleName, pBuffer, 0xffffffff, nullptr);

        // Add type guid to buffer
        serializer<uint>::serialize(typeOf<uint>(), &classGuid, pBuffer, 0xffffffff, 0);

        // Add guid to buffer
        const string & typeName = pType->getQualifiedDecoratedName();
        typeOf<string>()->serialize(&typeName, pBuffer, 0xffffffff, nullptr);

        pClass->serialize(typeOf<reflection::Type>()->cast(pClass, pType), pBuffer, 0xffffffff, nullptr);
    }

    uint uiBufferSize = pBuffer - &(buffer[0]);
    static_cast<BinaryFileTreeNode*>(rootNode())->writeBinary(getUrl()+'/'+"types", &(buffer[0]), uiBufferSize);
}

void BinaryFileTreeDataBase::loadRuntimeTypes(reflection::Module* a_pModule)
{
    byte* pBaseBuffer = (byte*)malloc(1000000 * sizeof(byte));
    size_t bufferSize = 0;
    static_cast<BinaryFileTreeNode*>(rootNode())->readBinary(getUrl()+'/'+"types", pBaseBuffer, bufferSize);

    const byte* pBuffer = pBaseBuffer;
    const byte*& pBufferRef = pBuffer;
    m_uiBufferSize = 0;
    uint count;
    serializer<uint>::deserialize(typeOf<uint>(), &count, pBufferRef, 0xffffffff, nullptr);

    for(size_t i = 0; i<count; ++i)
    {
        uint classGuid;

        string moduleName;
        typeOf<string>()->deserialize(&moduleName, pBufferRef, 0xffffffff, nullptr);

        serializer<uint>::deserialize(typeOf<uint>(), &classGuid, pBufferRef, 0xffffffff, 0);

        reflection::Class* pClass = solveTypeById(classGuid)->asClass();

        string typeName;
        typeOf<string>()->deserialize(&typeName, pBufferRef, 0xffffffff, nullptr);

        if(moduleName == a_pModule->getFileName())
        {
            void* pType = pClass->allocate();
            pClass->construct(pType);
            pClass->install(pType, 0);
            pClass->deserialize(pType, pBufferRef, 0xffffffff, nullptr);
            restore_pass pass = restore_pass_local;
            restore_state state;  
            while((state = pClass->restore(pType, 0xffffffff, pass)) == restore_incomplete)
                pass = restore_pass(pass+1);
            o_assert_no_implementation();
            //a_pModule->addElement(as<reflection::Type*>(pType));
        }
    }
    free(pBaseBuffer);
}

o_namespace_end(phantom, serialization)