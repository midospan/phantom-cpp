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

#ifndef o_phantom_reflection_RuntimeClass_h__
#define o_phantom_reflection_RuntimeClass_h__


/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "RuntimeClass.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_h_begin

class o_export RuntimeClass : public Class
{


public:
    // Be careful using the modifier o_data_memory_shot : it uses types default constructor
    // to build a static data shot which will be used as a stamp on each new class instance.
    // That means that all attributes must generate direct and indirect data
    // on the stack to be cleanly destroyed on class destruction.
    // Use it only when class data is only componed of primitive types or basic structural type
    // which doesn't allocate data on the heap


    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

protected:
    RuntimeClass(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, size_t a_uiClassPtrOffset, bitfield a_bfModifiers = bitfield())
        : Class(a_strName, a_uiSize, a_uiAlignment, a_bfModifiers)
        , m_uiMemoryOffset(0)
        , m_uiClassPtrOffset(a_uiClassPtrOffset)
        , m_pDataTypes(0)
        , m_uiDataTypeCount(0)
    {
    }

public:
    o_destructor ~RuntimeClass(void)
    {
        if(m_uiDataTypeCount)
        {
            phantom::dynamicPoolDeallocate(m_uiDataTypeCount*sizeof(Type*), m_pDataTypes);
        }
    }

protected:
    size_t    getClassPtrOffset() const
    {
        if(m_uiClassPtrOffset == 0xffffffff)
        {
            o_assert(getSuperClassCount() != 0);
            o_assert(is<RuntimeClass>(getSuperClass(0)));
             return static_cast<RuntimeClass*>(getSuperClass(0))->getClassPtrOffset();
        }
        return m_uiClassPtrOffset;
    }

public:
    class builder
    {
        o_friend(class, phantom, reflection, runtime, RuntimeClass)
        enum EState
        {
            eInheritanceSetup,
            eAttributeSetup,
            eMethodSetup,
            eAccessorSetup,
            eDone
        };

    public:
        builder(const string& a_strName, bitfield a_bfModifiers)
            : m_AlignmentComputer(0)
            , m_uiDataStartOffset(0)
            , m_uiSize(0)
            , m_eState(eInheritanceSetup)
            , m_pBuiltRuntimeClass(NULL)
            , m_strName(a_strName)
            , m_bfModifiers(a_bfModifiers)
        {
        }
        ~builder()
        {
        }

        void    add(Class* a_pClass);
        void    add(RuntimeInstanceAttribute* a_pAttribute);
        void    add(RuntimeStaticAttribute* a_pAttribute);

        state::runtime::RuntimeStateMachine*    addStateMachine();

        RuntimeClass*    build();

    protected:
        void buildRuntimeClass()
        {
            m_pBuiltRuntimeClass = NULL;
            size_t    memorySize = m_AlignmentComputer.compute();
            size_t    modulo = m_uiSize % m_AlignmentComputer.maxAlignment();
            if(modulo)
                m_uiDataStartOffset = m_AlignmentComputer.maxAlignment() - modulo;
            size_t finalSize = m_uiSize+m_uiDataStartOffset+memorySize;
            size_t finalAlignment = m_AlignmentComputer.maxAlignment();

            m_pBuiltRuntimeClass = o_new(RuntimeClass)(m_strName, finalSize, finalAlignment, m_bfModifiers);
        }

    protected:
        string                                m_strName;
        bitfield                            m_bfModifiers;
        EState                                m_eState;
        RuntimeClass*                        m_pBuiltRuntimeClass;
        size_t                                m_uiSize;
        size_t                                m_uiDataStartOffset;
        Class::super_class_table            m_SuperClasses;
        vector<RuntimeInstanceAttribute*>    m_InstanceAttributes;
        vector<RuntimeStaticAttribute*>        m_StaticAttributes;
        Type::alignment::computer            m_AlignmentComputer;

    };

    friend class builder;

    boolean         restore( uint a_uiSerializationFlag, uint a_uiPass) { return true; }

    virtual uint getVirtualMethodCount(uint index) const
    {
        o_error(false, "to implement");
        return 0;
    }

    virtual void*   allocate() const
    {
        return phantom::dynamicPoolAllocate(m_uiSize);
    }
    virtual void    deallocate(void* a_pInstance) const
    {
        phantom::dynamicPoolDeallocate(m_uiSize, a_pInstance);
    }
    virtual void*   allocate(size_t a_uiCount) const
    {
        return phantom::dynamicPoolAllocate(m_uiSize);
    }
    virtual void    deallocate(void* a_pChunk, size_t a_uiCount) const
    {
        phantom::dynamicPoolDeallocate(m_uiSize, a_pChunk, a_uiCount);
    }
    virtual void        construct(void* a_pObject) const;
    virtual void        destroy(void* a_pObject) const;
    virtual void        construct(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize) const;
    virtual void        destroy(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize) const;

    virtual void        serialize(void const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        deserialize(void* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        serialize(void const* a_pInstance, const property_branch& a_OutBranch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        deserialize(void* a_pInstance, const property_branch& a_InBranch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_branch& a_OutBranch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_branch& a_InBranch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        serializeLayout(void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        deserializeLayout(void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        serializeLayout(void const* a_pInstance, const property_branch& a_Branch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        deserializeLayout(void* a_pInstance, const property_branch& a_Branch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_branch& a_Branch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_branch& a_Branch, uint a_uiSerializationMask, data_guid_base const* a_pGuidBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }

    virtual void        remember(void const* a_pInstance, byte*& a_pOutBuffer) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        reset(void* a_pInstance, byte const*& a_pInBuffer) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        remember(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        reset(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }



    virtual
        serialization::Bundle*  createBundle(serialization::BundleNode* a_pOwnerNode) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); return NULL; }
    virtual void            destroyBundle(serialization::Bundle* a_pBundle) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    void                setupBase( Object* a_pObject ) const;

protected:
    signal_t                aboutToBeReplaced(RuntimeClass* a_pNew, RuntimeClass* a_pOld) const;
    virtual Type*           createConstType() const;

protected:
    mutable connection::slot::list        PHANTOM_CODEGEN_m_slot_list_of_aboutToBeReplaced;
    size_t                m_uiMemoryOffset;
    size_t                m_uiClassPtrOffset;
    Type**                m_pDataTypes;
    size_t                m_uiDataTypeCount;

};

o_h_end


#else // RuntimeClass_h__
#include "RuntimeClass.classdef.h"
#endif
