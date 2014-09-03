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
#include <phantom/reflection/DataPointerType.h>
#include <phantom/reflection/DataPointerType.hxx>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/AssignmentExpression.h>
#include <phantom/reflection/BinaryLogicalExpression.h>
#include <phantom/reflection/PointerArithmeticExpression.h>
#include <phantom/reflection/TBinaryBooleanExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), DataPointerType);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(DataPointerType);

DataPointerType::DataPointerType( Type* a_pType ) 
: PointerType(a_pType->getName()+'*'
            , sizeof(void*)
            , boost::alignment_of<void*>::value
            , 0xFFFFFFFF
            , 0)    
, m_pPointedType(a_pType)
{
    addReferencedElement(a_pType);
}

DataPointerType::~DataPointerType()
{
}

boolean DataPointerType::isConvertibleTo( Type* a_pType ) const
{
    o_assert(a_pType);
    return a_pType->asIntegralType() OR a_pType->asPointerType() OR isImplicitlyConvertibleTo(a_pType);
    
}

bool DataPointerType::hasTrivialCastTo( Type* a_pType ) const
{
    
    return isImplicitlyConvertibleTo(a_pType);
}

boolean DataPointerType::isImplicitlyConvertibleTo( Type* a_pType ) const
{
    if(a_pType == this 
        OR (m_pPointedType->asConstType() == nullptr AND a_pType == typeOf<void*>()) 
        OR a_pType == typeOf<void const*>()
        OR a_pType == typeOf<bool>())
    {
        return true;
    }
    if(a_pType->getDataPointerLevel() == 1 AND getDataPointerLevel() == 1)
    {
        Type* pPointedType = static_cast<DataPointerType*>(a_pType)->getPointedType();
        if(pPointedType == m_pPointedType) return true;
        if(pPointedType->asConstType() AND pPointedType->asConstType() == nullptr)
        {
            return false;
        }
        if((pPointedType->asClass() != nullptr) AND (m_pPointedType->asClass() != nullptr)) 
        {
            reflection::Class* pDestClass  = static_cast<reflection::Class*>(pPointedType);
            reflection::Class* pClass       = static_cast<reflection::Class*>(m_pPointedType);
            return pClass->isKindOf(pDestClass);
        }
        return false;
    }
    return false;
}

void DataPointerType::convertValueTo( Type* a_pDestType, void* a_pDestValue, void const* a_pSrcValue ) const
{
    o_assert(isConvertibleTo(a_pDestType));
    if(m_pPointedType->removeConst() == typeOf<void>())
    {
        *((void**)a_pDestValue) = *((void**)a_pSrcValue);
        return;
    }
    reflection::Class* pPointedClass = m_pPointedType->removeConst()->asClass();
    if(pPointedClass == nullptr) 
    {
        Type::convertValueTo(a_pDestType, a_pDestValue, a_pSrcValue);
        return;
    }
    reflection::Type* pDestPointedType = a_pDestType->asDataPointerType()->getPointedType();
    if(a_pDestType == this OR pDestPointedType->removeConst() == typeOf<void>())
    {
        *((void**)a_pDestValue) = *((void**)a_pSrcValue);
    }
    else if(a_pDestType == typeOf<bool>())
    {
        *((bool*)a_pDestValue) = (*((void* const*)a_pSrcValue) != nullptr);
    }
    else
    {
        reflection::Class* pDestPointedClass = pDestPointedType->removeConst()->asClass();
        o_assert(pDestPointedClass);
        if(pPointedClass == pDestPointedClass) return Type::convertValueTo(a_pDestType, a_pDestValue, a_pSrcValue);
        size_t offset = pPointedClass->getSuperClassOffsetCascade(pDestPointedClass);
        if(offset != 0xffffffff) 
        {
            byte* ptr = *((byte**)a_pSrcValue);
            *((byte**)a_pDestValue) = (ptr == nullptr) ? nullptr : ptr+offset;
        }
        else 
        {
            offset = pDestPointedClass->getSuperClassOffsetCascade(pPointedClass);
            if(offset == 0xffffffff)
            {
                o_assert(pPointedClass->isKindOf(pDestPointedClass));
                offset = 0;
            }
            byte* ptr = *((byte**)a_pSrcValue);
            *((byte**)a_pDestValue) = (ptr == nullptr) ? nullptr : ptr-offset;
        }
    }
}

void        DataPointerType::serialize(void const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
{
    void* ptr = *reinterpret_cast<void* const*>(a_pInstance);
    const rtti_data& rttiData = phantom::rttiDataOf(ptr);
    o_assert(ptr == nullptr OR NOT(rttiData.isNull()));
    void* ptr_base = rttiData.base;
    // save the offset from the base address to restore the correct inheritance layout address later
    size_t offset = reinterpret_cast<size_t>(ptr)-reinterpret_cast<size_t>(ptr_base);
    uint guid = a_pDataBase ? a_pDataBase->getGuid(ptr_base) : (uint)ptr_base;
    *reinterpret_cast<uint*>(a_pOutBuffer) = guid;
    a_pOutBuffer += sizeof(uint);
    *reinterpret_cast<size_t*>(a_pOutBuffer) = offset;
    a_pOutBuffer += sizeof(size_t);
    if(guid == 0xffffffff) // Object not stored in database, we try to save it
    {
        if(ptr_base)
        {
            // we "inline" it if it's a class instance and we know the said class
            reflection::Class*  pClass = rttiData.object_class;
            o_assert(pClass, "The object is not stored in the data base and its type is unknown"
                ", we cannot save it, ensure the pointer valueMember you are trying to serialize is transient or "
                "that the internal types are either serializable class instances installed with phantom (o_classX + o_new)"
                " either data stored in database ");

            *reinterpret_cast<uint*>(a_pOutBuffer) = pClass->getGuid(); // Save the class guid ; TODO : little/big endian managment
            a_pOutBuffer += sizeof(uint);
            pClass->serialize(ptr_base, a_pOutBuffer, a_uiSerializationMask, a_pDataBase); // Save the instance
        }
        else
        {
            *reinterpret_cast<uint*>(a_pOutBuffer) = 0; // Ptr null => we save a null guid
            a_pOutBuffer += sizeof(uint);
        }
    }
}

void        DataPointerType::deserialize(void* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
{
    uint guid = *reinterpret_cast<uint const*>(a_pInBuffer);
    a_pInBuffer += sizeof(uint);
    // read the offset from the base address to restore the correct inheritance layout address
    size_t offset = *reinterpret_cast<size_t const*>(a_pInBuffer);
    a_pInBuffer += sizeof(size_t);

    if(guid == 0xffffffff) // Object not stored in database, we try to rebuild it
    {
        // We find the instance class thanks to the stored guid 
        uint classGuid = *reinterpret_cast<uint const*>(a_pInBuffer);
        a_pInBuffer += sizeof(uint);
        if(classGuid != 0)
        {
            // we "uninline" it if it's a class instance and we know the said class
            reflection::Type*  pType = phantom::typeByGuid(classGuid);
            o_assert(pType AND pType->asClass(), "The class associated with the given serialized data cannot be found, "
                "ensure all the class are registered correctly before deserializing data");

            reflection::Class* pClass = static_cast<reflection::Class*>(pType);
            void* newInstance = pClass->allocate();
            pClass->build(newInstance);
            pClass->deserialize(newInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase); // Save the instance

            // we restore all the pass here, because we can't do it later, 
            // we won't have any pointer to this object after this member_function
            uint pass = 0;
            restore_state restored = restore_incomplete;
            while(restored == restore_incomplete)
            {
                // be sure for this kind of objects that you don't have dependencies 
                // with other stored object which couln't be totally restored at this point
                restored = pClass->restore(newInstance, a_uiSerializationMask, pass++);
            }
            if(restored == restore_failed)
            {
                pClass->deleteInstance(newInstance);
                *reinterpret_cast<void**>(a_pInstance) = NULL;
            }
            else
            {
                *reinterpret_cast<void**>(a_pInstance) = reinterpret_cast<byte*>(newInstance)+offset; // restore the correct layout
            }
        }
        else
        {
            *reinterpret_cast<void**>(a_pInstance) = NULL; // restore the null pointer (if classGuid == 0)
        }
    }
    else 
    {
        o_assert(a_pDataBase == nullptr || a_pDataBase->getDataType(guid)->isKindOf(m_pPointedType)); // in binary mode we assert this (type not supposed to change between serialization and deserialization
        *reinterpret_cast<void**>(a_pInstance) = reinterpret_cast<byte*>( a_pDataBase ? a_pDataBase->getDataAddress(guid) : (void*)guid )+offset; // restore the correct layout
    }
    
}

void DataPointerType::serialize( void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    void* ptr = *reinterpret_cast<void* const*>(a_pInstance);
    const rtti_data& rttiData = phantom::rttiDataOf(ptr);
    o_assert(ptr == nullptr OR NOT(rttiData.isNull()));
    void* ptr_base = rttiData.base;
    uint guid = a_pDataBase ? a_pDataBase->getGuid(ptr_base) : (uint)ptr_base;
    a_OutBranch.put<string>("guid", phantom::lexical_cast<string>(guid));
    if((guid == 0xffffffff) AND (ptr_base != NULL))
    {
        a_OutBranch.put<string>("type", /*encodeQualifiedDecoratedNameToIdentifierName*/(rttiData.object_class->getQualifiedDecoratedName())); 
        property_tree data_tree;
        rttiData.object_class->serialize(ptr_base, data_tree, a_uiSerializationMask, a_pDataBase);
        a_OutBranch.add_child("data", data_tree);
    }
}

void DataPointerType::deserialize( void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    string guid_str = a_InBranch.get<string>("guid");
    uint guid = phantom::lexical_cast<uint>(guid_str);
    if(guid == 0xffffffff)
    {
        boost::optional<string> typeName_opt = a_InBranch.get_optional<string>("type"); 
        if(typeName_opt.is_initialized())
        {
            const string& typeName = *typeName_opt;
            reflection::Type* pType = a_pDataBase ? a_pDataBase->solveTypeByName(/*decodeQualifiedDecoratedNameFromIdentifierName*/(typeName)) : phantom::typeByName(decodeQualifiedDecoratedNameFromIdentifierName(typeName));
            o_assert(pType AND pType->asClass(), "The class associated with the given serialized data cannot be found, "
                "ensure all the class are registered correctly before deserializing data");
            reflection::Class* pClass = static_cast<reflection::Class*>(pType);
            void* newInstance = pClass->allocate();
            pClass->build(newInstance);
            const property_tree& data_tree = a_InBranch.get_child("data");
            pClass->deserialize(newInstance, data_tree, a_uiSerializationMask, a_pDataBase);

            // we restore all the pass here, because we can't do it later, 
            // we won't have any pointer to this object after this member_function
            uint pass = 0;
            restore_state restored = restore_incomplete;
            while(restored == restore_incomplete)
            {
                // be sure for this kind of objects that you don't have dependencies 
                // with other stored object which couln't be totally restored at this point
                restored = pClass->restore(newInstance, a_uiSerializationMask, pass++);
            }
            if(restored == restore_failed)
            {
                pClass->deleteInstance(newInstance);
                *reinterpret_cast<void**>(a_pInstance) = NULL;
            }
            else
            {
                *reinterpret_cast<void**>(a_pInstance) = pClass->cast(m_pPointedType, newInstance); // restore the correct layout
            }
        }
        else
        {
            *reinterpret_cast<void**>(a_pInstance) = NULL;
        }
    }
    else 
    {
		phantom::data d = a_pDataBase ? a_pDataBase->getData(guid) : phantom::data((void*)guid);
		if (NOT(d.isNull()))
		{
			*reinterpret_cast<void**>(a_pInstance) = d.cast(m_pPointedType).address();
		}
		else
		{
			*reinterpret_cast<void**>(a_pInstance) = NULL;
		}
    }
}

void        DataPointerType::serialize(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
{
    byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
    while(a_uiCount--)
    {
        void* ptr = *reinterpret_cast<void* const*>(pChunk);
        const rtti_data& rttiData = phantom::rttiDataOf(ptr);
        o_assert(ptr == nullptr OR NOT(rttiData.isNull()));
        void* ptr_base = rttiData.base;
        // save the offset from the base address to restore the correct inheritance layout address later
        size_t offset = reinterpret_cast<size_t>(ptr)-reinterpret_cast<size_t>(ptr_base);
        uint guid = a_pDataBase ? a_pDataBase->getGuid(ptr_base) : (uint)ptr_base;
        *reinterpret_cast<uint*>(a_pOutBuffer) = guid; // TODO : little/big endian managment
        a_pOutBuffer += sizeof(uint);
        *reinterpret_cast<size_t*>(a_pOutBuffer) = offset; // TODO : little/big endian managment
        a_pOutBuffer += sizeof(size_t);
        if(guid == 0xffffffff) // Object not stored in database, we try to save it
        {
            if(ptr_base)
            {
                // we "inline" it if it's a class instance and we know the said class
                reflection::Class*  pClass = rttiData.object_class;
                o_assert(pClass, "The object is not stored in the data base and its type is unknown"
                    ", we cannot save it, ensure the pointer valueMember you are trying to serialize is transient or "
                    "that the internal types are either serializable class instances installed with phantom (o_classX + o_new)"
                    " either data stored in database ");

                *reinterpret_cast<uint*>(a_pOutBuffer) = pClass->getGuid(); // Save the class guid ; TODO : little/big endian managment
                a_pOutBuffer += sizeof(uint);
                pClass->serialize(ptr_base, a_pOutBuffer, a_uiSerializationMask, a_pDataBase); // Save the instance
            }
            else
            {
                *reinterpret_cast<uint*>(a_pOutBuffer) = 0; // Ptr null => we save a null guid
                a_pOutBuffer += sizeof(uint);
            }
        }
        pChunk += a_uiChunkSectionSize;
    }
}

void        DataPointerType::deserialize(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
{
    byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
    while(a_uiCount--)
    {
        uint guid = *reinterpret_cast<uint const*>(a_pInBuffer);
        a_pInBuffer += sizeof(uint);
        // read the offset from the base address to restore the correct inheritance layout address
        size_t offset = *reinterpret_cast<size_t const*>(a_pInBuffer);
        a_pInBuffer += sizeof(size_t);

        if(guid == 0xffffffff) // Object not stored in database, we try to rebuild it
        {
            // We find the instance class thanks to the stored guid 
            uint classGuid = *reinterpret_cast<uint const*>(a_pInBuffer);
            a_pInBuffer += sizeof(uint);

            if(classGuid != 0)
            {
                // we "uninline" it if it's a class instance and we know the said class
                reflection::Type*  pType = phantom::typeByGuid(classGuid);
                o_assert(pType AND pType->asClass(), "The class associated with the given serialized data cannot be found, "
                    "ensure all the class are registered correctly before deserializing data");

                reflection::Class* pClass = static_cast<reflection::Class*>(pType);
                void* newInstance = pClass->allocate();
                pClass->build(newInstance);
                pClass->deserialize(newInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase); // Save the instance

                // we restore all the pass here, because we can't do it later, 
                // we won't have any pointer to this object after this member_function
                uint pass = 0;
                restore_state restored = restore_incomplete;
                while(restored == restore_incomplete)
                {
                    // be sure for this kind of objects that you don't have dependencies 
                    // with other stored object which couln't be totally restored at this point
                    restored = pClass->restore(newInstance, a_uiSerializationMask, pass++);
                }
                if(restored == restore_failed)
                {
                    pClass->deleteInstance(newInstance);
                    *reinterpret_cast<void**>(pChunk) = NULL;
                }
                else
                {
                    *reinterpret_cast<void**>(pChunk) = reinterpret_cast<byte*>(newInstance)+offset; // restore the correct layout
                }
            }
            else
            {
                *reinterpret_cast<void**>(pChunk) = NULL;
            }
        }
        else
        {
            o_assert(a_pDataBase == nullptr || a_pDataBase->getDataType(guid)->isKindOf(m_pPointedType));
            *reinterpret_cast<void**>(pChunk) = reinterpret_cast<byte*>(a_pDataBase ? a_pDataBase->getDataAddress(guid) : (void*)guid)+offset; // TODO : little/big endian managment
        }
        pChunk += a_uiChunkSectionSize;
    }
}

void        DataPointerType::serialize(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
{
    byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
    int i = 0;
    while(a_uiCount--)
    {
        char index_buffer[32]="";
        o_secured_sprintf(index_buffer, 32, "_%d", i++);
        void* ptr = *reinterpret_cast<void* const*>(pChunk);
        const rtti_data& rttiData = phantom::rttiDataOf(ptr);
        o_assert(ptr == nullptr OR NOT(rttiData.isNull()));
        void* ptr_base = rttiData.base;
        uint guid = a_pDataBase ? a_pDataBase->getGuid(ptr_base) : (uint)ptr_base;
        property_tree index_tree;
        index_tree.put<string>("guid", phantom::lexical_cast<string>(guid));
        if((guid == 0xffffffff) AND (ptr_base != NULL))
        {
            index_tree.put<string>("type", /*encodeQualifiedDecoratedNameToIdentifierName*/(rttiData.object_class->getQualifiedDecoratedName())); 
            property_tree data_tree; 
            rttiData.object_class->serialize(ptr_base, data_tree, a_uiSerializationMask, a_pDataBase);
            index_tree.add_child("data", data_tree);
        }
        a_OutBranch.add_child(index_buffer, index_tree);
        pChunk += a_uiChunkSectionSize;
    }
}

void        DataPointerType::deserialize(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
{
    byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
    int i = 0;
    while(a_uiCount--)
    {
        char index_buffer[32]="";
        o_secured_sprintf(index_buffer, 32, "_%d", i++);
        boost::optional<const property_tree&> index_tree_opt = a_InBranch.get_child_optional(index_buffer);
        if(index_tree_opt.is_initialized())
        {
            const property_tree& index_tree = *index_tree_opt;
            const string& guid_str = index_tree.get<string>("guid");
            uint guid = phantom::lexical_cast<uint>(guid_str);
            if(guid == 0xffffffff)
            {
                boost::optional<string> typeName_opt = index_tree.get_optional<string>("type"); 
                if(typeName_opt.is_initialized())
                {
                    const string& typeName = *typeName_opt;
                    reflection::Type* pType = a_pDataBase ? a_pDataBase->solveTypeByName(/*decodeQualifiedDecoratedNameFromIdentifierName*/(typeName)) : phantom::typeByName(decodeQualifiedDecoratedNameFromIdentifierName(typeName));
                    o_assert(pType AND pType->asClass(), "The class associated with the given serialized data cannot be found, "
                        "ensure all the class are registered correctly before deserializing data");
                    reflection::Class* pClass = static_cast<reflection::Class*>(pType);
                    void* newInstance = pClass->allocate();
                    pClass->build(newInstance);
                    const property_tree& data_tree = index_tree.get_child("data"); 
                    pClass->deserialize(newInstance, data_tree, a_uiSerializationMask, a_pDataBase);
                    // we restore all the pass here, because we can't do it later, 
                    // we won't have any pointer to this object after this member_function
                    uint pass = 0;
                    restore_state restored = restore_incomplete;
                    while(restored == restore_incomplete)
                    {   // be sure for this kind of objects that you don't have dependencies 
                        // with other stored object which couln't be totally restored at this point
                        restored = pClass->restore(newInstance, a_uiSerializationMask, pass++);
                    }
                    if(restored == restore_failed)
                    {
                        pClass->deleteInstance(newInstance);
                        *reinterpret_cast<void**>(pChunk) = nullptr;
                    }
                    else
                    {
                        *reinterpret_cast<void**>(pChunk) = pClass->cast(m_pPointedType, newInstance); // restore the correct layout
                    }
                }
                else
                {
                    *reinterpret_cast<void**>(pChunk) = nullptr;
                }
            }
            else
            {
                if(a_pDataBase)
                {
                    *reinterpret_cast<void**>(pChunk) = a_pDataBase->getData(guid).cast(m_pPointedType).address();
                }
                else  if(m_pPointedType->asClass())
                {
                    phantom::rtti_data rd = phantom::rttiDataOf((void*)guid);
                    if(rd.isNull())
                    {
                        *reinterpret_cast<void**>(pChunk)  = nullptr;
                    }
                    else
                    {
                        *reinterpret_cast<void**>(pChunk) = rd.cast(m_pPointedType->asClass());
                    }
                }
            }
        }
        pChunk += a_uiChunkSectionSize;
    }
}

void DataPointerType::referencedElementRemoved( LanguageElement* a_pElement )
{
    Type::referencedElementRemoved(a_pElement);
    if(m_pPointedType == a_pElement)
        m_pPointedType = nullptr;
}

bool DataPointerType::referencesData( const void* a_pInstance, const phantom::data& a_Data ) const
{
    const void* pointerValue = *((const void**)a_pInstance);
    if(pointerValue == nullptr) 
        return false;
    return m_pPointedType->cast(a_Data.type(), (void*)pointerValue) == a_Data.address();
}

void DataPointerType::fetchPointerReferenceExpressions( Expression* a_pInstanceExpression, vector<Expression*>& out, uint a_uiSerializationMask ) const
{
    out.push_back(a_pInstanceExpression);
}

Expression* DataPointerType::solveOperator(const string& a_strOp, const vector<Expression*>& a_Expressions, bitfield a_Modifiers) const
{
    o_assert(a_Expressions[0]->getValueType()->removeReference() == this);
    if(a_strOp == "*" && a_Expressions.size() == 1)
    {
        return a_Expressions.back()->dereference();
    }
    if(a_strOp == "->")
    {
        if(a_Expressions.size() != 1) return nullptr;
        return a_Expressions.back()->dereference();
    }
    else if(a_strOp.size() == 2 && a_Expressions.size() == 2)
    {
        if(a_strOp == "&&" OR a_strOp == "||")
        {
            return o_new(BinaryLogicalExpression)(a_strOp, a_Expressions[0], a_Expressions[1]);
        }/*
        else if(a_strOp == ">>" OR a_strOp == "<<")
        {
            return o_new(TBinaryBitExpression<void*>)(a_strOp, a_Expressions[0], a_Expressions[1]);
        }*/
        else if(a_strOp[1] == '=') // Assignment operation
        {
            Expression* pSubExpression = nullptr;
            switch(a_strOp[0])
            {
            case '+':
            case '-':
                if(a_Expressions[1]->getValueType()->isImplicitlyConvertibleTo(typeOf<int>()))
                {
                    pSubExpression = o_new(PointerArithmeticExpression)(a_strOp.substr(0, 1), a_Expressions[0], a_Expressions[1]);
                }
                break;
            case '=':
            case '!':
            case '<':
            case '>':
                return o_new(TBinaryBooleanExpression<void*>)(a_strOp, a_Expressions[0], a_Expressions[1]);
            /*case '|':
            case '&':
            case '^':
                pSubExpression = o_new(TBinaryBitExpression<void*>)(a_strOp.substr(0, 1), a_Expressions[0], a_Expressions[1]);
                break;*/

            }
            if(pSubExpression)
            {
                return o_new(AssignmentExpression)(a_Expressions[0], pSubExpression);
            }
        }
    }
    else if(a_strOp.size() == 1 && a_Expressions.size() == 2)
    {
        switch(a_strOp[0])
        {
        case '=': // Assignment operation
            {
                if(a_Expressions[1]->getValueType()->isImplicitlyConvertibleTo(a_Expressions[0]->getValueType()->removeReference()))
                {
                    return o_new(AssignmentExpression)(a_Expressions[0], a_Expressions[1]);
                }
            }
    
        case '<':
        case '>':
            return o_new(TBinaryBooleanExpression<void*>)(a_strOp, a_Expressions[0], a_Expressions[1]);
        }
    }
    return PointerType::solveOperator(a_strOp, a_Expressions, a_Modifiers);
}

void DataPointerType::valueToLiteral( string& a_str, const void* src ) const
{
    a_str += "(" + getQualifiedDecoratedName() + ")0x";
    DataPointerType::valueToString(a_str, src);
}

void DataPointerType::valueToString( string& a_str, const void* src ) const
{
    a_str += ::phantom::lexical_cast<string>(*((void**)(src)));;
}

void DataPointerType::valueFromString( const string& a_str, void* dest ) const
{
    *reinterpret_cast<void**>(dest) = ::phantom::lexical_cast<void*>(a_str);
}

void DataPointerType::copy( void* a_pDest, void const* a_pSrc ) const
{
    *static_cast<void**>(a_pDest) = *static_cast<void* const*>(a_pSrc);
}

o_namespace_end(phantom, reflection)