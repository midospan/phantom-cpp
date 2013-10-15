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

#ifndef o_phantom_reflection_JitClass_h__
#define o_phantom_reflection_JitClass_h__


/* ****************** Includes ******************* */
#include <phantom/def_runtime.h>
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection, runtime)

class o_runtime_export JitClass : public Class
{

    enum EState
    {
        e_State_InheritanceSetup,
        e_State_MemorySetup,
        e_State_MemoryFrozen,
        e_State_Finalized
    };

public:
    // Be careful using the modifier o_data_memory_shot : it uses types default constructor
    // to build a static data shot which will be used as a stamp on each new class instance.
    // That means that all attributes must generate direct and indirect data
    // on the stack to be cleanly destroyed on class destruction.
    // Use it only when class data is only componed of primitive types or basic structural type
    // which doesn't allocate data on the heap

public:
    JitClass(const string& a_strName, bitfield a_bfModifiers = bitfield());


public:
    o_destructor ~JitClass(void);

public:
    jit_context_t   getContext() const { return m_Context; }

    void        extractVirtualMethodTableInfos(const void* a_pInstance, vector<vtable_info>& vtables);

    bool    hasStateMachineDataPtr() const { return m_uiStateMachineDataPtrOffset == (hasVTableDataPtr()*sizeof(void*)); }
    bool    hasVTableDataPtr() const { return m_bHasVTablePtr; }

    virtual boolean                     isPolymorphic() const;

    void    addSuperClass(Class* a_pClass);
    void    setStateMachine(state::runtime::JitStateMachine* a_pStateMachine);
    void    addInstanceAttribute(JitInstanceAttribute* a_pAttribute);
    void    addAccessor( JitAccessor* a_pAccessor );
    void    addCollection( JitCollection* a_pCollection );
    void    addStaticAttribute(JitStaticAttribute* a_pAttribute);
    void    addInstanceMethod(JitInstanceMethod* a_pInstanceMethod);
    void    addSignal(JitSignal* a_pSignal);
    void    addStaticMethod(JitStaticMethod* a_pStaticMethod);
    void    addAbstractMethod( AbstractMethod* a_pInstanceMethod );

    static void InstallHelper(Class* a_pBaseClass, void* a_pBase, Class* a_pLayoutClass, void* a_pLayout, connection::slot_pool* sp);
    static void UninstallHelper(void* a_pLayout, Class* a_pLayoutClass);

    virtual void initialize( void* a_pInstance ) const;
    virtual void terminate( void* a_pInstance ) const;

    virtual void install( void* a_pInstance ) const 
    {
        connection::slot_pool& ac = connection::slot_pool::allocationController(a_pInstance);
        InstallHelper((Class*)this, a_pInstance, (Class*)this, a_pInstance, &ac);
        state::StateMachine* pStateMachine = getStateMachineCascade();
        if(pStateMachine)
        {
            pStateMachine->install(cast(pStateMachine->getOwnerClass(), a_pInstance));
        }
    }
    virtual void uninstall( void* a_pInstance ) const 
    {
        state::StateMachine* pStateMachine = getStateMachineCascade();
        if(pStateMachine)
        {
            pStateMachine->uninstall(cast(pStateMachine->getOwnerClass(), a_pInstance));
        }
        UninstallHelper(a_pInstance, (Class*)this);
        connection::slot_pool::eraseAllocationController(a_pInstance);
    }
    virtual void install( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const { o_assert(false);   }
    virtual void uninstall( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const     { o_assert(false); }

    virtual restore_state   restore(void* a_pInstance, uint a_uiSerializationFlag, uint a_uiPass) const;


    virtual uint getVirtualMethodCount(uint index) const
    {
        o_error(false, "to implement");
        return 0;
    }

    virtual void*   allocate() const
    {
        if(m_eState != e_State_Finalized)
        {
            ((JitClass*)this)->finalize();
        }
        // allocate m_uiSize bytes
        void* memory = o_dynamic_pool_allocate(m_uiSize);
        
        // initialize memory to 0
        memset(memory, 0, m_uiSize);
        return memory;
    }
    virtual void    deallocate(void* a_pInstance) const
    {
        o_dynamic_pool_deallocate(a_pInstance, m_uiSize);
    }
    virtual void*   allocate(size_t a_uiCount) const
    {
        if(m_eState != e_State_Finalized)
        {
            ((JitClass*)this)->finalize();
        }
        return o_dynamic_pool_allocate_n(a_uiCount, m_uiSize); 
    }
    virtual void    deallocate(void* a_pChunk, size_t a_uiCount) const
    {
        o_dynamic_pool_deallocate_n(a_pChunk, a_uiCount, m_uiSize);
    }
    virtual void        construct(void* a_pObject) const;
    virtual void        destroy(void* a_pObject) const;
    virtual void        construct(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize) const;
    virtual void        destroy(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize) const;

    virtual void        serialize(void const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        deserialize(void* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        serialize(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const ;
    virtual void        deserialize(void* a_pInstance, const property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const ;
    virtual void        serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        serializeLayout(void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        deserializeLayout(void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        serializeLayout(void const* a_pInstance, property_tree& a_Branch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const ;
    virtual void        deserializeLayout(void* a_pInstance, const property_tree& a_Branch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const;
    virtual void        serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_Branch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_Branch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }

    virtual void        remember(void const* a_pInstance, byte*& a_pOutBuffer) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        reset(void* a_pInstance, byte const*& a_pInBuffer) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        remember(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void        reset(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }

    virtual
        serialization::Bundle*  createBundle(serialization::BundleNode* a_pOwnerNode) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); return NULL; }
    virtual void            destroyBundle(serialization::Bundle* a_pBundle) const { o_exception(exception::unsupported_method_exception, "not yet implemented"); }

protected:
    signal_t                aboutToBeReplaced(JitClass* a_pNew, JitClass* a_pOld) const;
    virtual Type*           createConstType() const;

private:
    // prevent from calling super add versions
    virtual void            addConstructor( Constructor* a_pConstructor ) { o_exception(exception::unsupported_method_exception, "not yet implemented"); }
    virtual void            addProperty( Property* a_pProperty ) { o_exception(exception::unsupported_method_exception, "shouldn't be used directly"); }
    virtual void            addAttribute( Attribute* a_pAttribute );
    virtual void            addStaticAttribute( StaticAttribute* a_pAttribute );
    virtual void            addInstanceAttribute( InstanceAttribute* a_pAttribute );
    virtual void            addAccessor( Accessor* a_pAccessor );
    virtual void            addMethod(Method* a_pMethod);
    virtual void            addInstanceMethod(InstanceMethod* a_MetaMethod);
    virtual void            addStaticMethod(StaticMethod* a_MetaMethod);

protected:
    void finalize();

    void freezeMemory();

protected:
    vector<Type*>                   m_DataTypes;
    Type::alignment::computer       m_AlignmentComputer;
    mutable connection::slot::list  PHANTOM_CODEGEN_m_slot_list_of_aboutToBeReplaced;
    mutable vector<vtable_info>     m_VTableInfos;
    jit_context_t                   m_Context;
    EState                          m_eState;

    size_t                          m_uiAttributeMemoryOffset;
    size_t                          m_uiClassPtrOffset;
    size_t                          m_uiDataTypeCount;
    size_t                          m_uiSuperSize;
    size_t                          m_uiAlignmentFixingOffset;
    size_t                          m_uiStateMachineDataPtrOffset;
    bool                            m_bHasVTablePtr;
    bool                            m_bHasStateMachineDataPtr;
};

o_namespace_end(phantom, reflection, runtime)

o_classNS((phantom, reflection, runtime), JitClass, (Class))
{
    o_reflection 
    {
        o_signal(aboutToBeReplaced, (JitClass*,JitClass*));
    };
};

o_exposeN((phantom, reflection, runtime), JitClass);

#endif
