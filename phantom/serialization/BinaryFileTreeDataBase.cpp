/*
    This file is part of PHANTOM
         P reprocessed 
         H igh-level 
         A llocator 
         N ested state-machines and 
         T emplate 
         O riented 
         M eta-programming

    For the latest infos and sources, see http://code.google.com/p/phantom-cpp

    Copyright (C) 2008-2011 by Vivien MILLET

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE
*/

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

void BinaryFileTreeDataBase::loadRuntimeTypes(Module* a_pModule)
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
            a_pModule->addLanguageElement(as<reflection::Type*>(pType));
        }
    }
    free(pBaseBuffer);
}

o_namespace_end(phantom, serialization)