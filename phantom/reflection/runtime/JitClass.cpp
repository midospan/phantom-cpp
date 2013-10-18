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
#include <phantom/def_runtime.h>
#include <phantom/reflection/runtime/JitClass.h>
#include <phantom/reflection/runtime/JitInstanceAttribute.h>
#include <phantom/reflection/runtime/JitStaticAttribute.h>
#include <phantom/reflection/runtime/JitInstanceMethod.h>
#include <phantom/reflection/runtime/JitSignal.h>
#include <phantom/reflection/runtime/JitStaticMethod.h>
#include <phantom/reflection/runtime/JitAccessor.h>
#include <phantom/reflection/runtime/JitCollection.h>
#include <phantom/state/runtime/JitStateMachine.h>
/* *********************************************** */
o_registerN((phantom, reflection, runtime), JitClass);


o_namespace_begin(phantom, reflection, runtime)

JitClass::JitClass( const string& a_strName, bitfield a_bfModifiers /*= bitfield()*/ ) : Class(a_strName, 0, 0, a_bfModifiers)
    , m_uiAttributeMemoryOffset(0)
    , m_uiDataTypeCount(0)
    , m_AlignmentComputer(0)
    , m_uiAlignmentFixingOffset(0)
    , m_uiSuperSize(0)
    , m_eState(e_State_InheritanceSetup)
    , m_bHasVTablePtr(true)
    , m_bHasStateMachineDataPtr(true)
    , m_uiStateMachineDataPtrOffset(0xffffffff)
{
    m_Context = jit_context_create();
    jit_context_build_start(m_Context);
}

void JitClass::setStateMachine( state::runtime::JitStateMachine* a_pStateMachine )
{
    if(m_pStateMachine)
    {
        o_exception(exception::reflection_runtime_exception, "StateMachine already added, you cannot add more than one state machine");
    }
    if(m_eState == e_State_InheritanceSetup)
    {
        m_eState = e_State_MemorySetup;
    }
    else if(m_eState >= e_State_MemoryFrozen)
    {
        o_exception(exception::reflection_runtime_exception, "JitClass memory frozen, you cannot add state machine anymore");
    }
    a_pStateMachine->setup(getStateMachineCascade());
    Class::setStateMachine(a_pStateMachine);
}

void JitClass::addInstanceAttribute( JitInstanceAttribute* a_pAttribute )
{
    if(m_eState > e_State_MemorySetup)
    {
        o_exception(exception::reflection_runtime_exception, "Memory already set up, you cannot add attributes anymore");
    }
    else
    {
        m_eState = e_State_MemorySetup;
    }
    Type* pContentType = a_pAttribute->getValueType();
    m_DataTypes.push_back(pContentType);
    a_pAttribute->setOffset(m_AlignmentComputer.push(pContentType)); // we store a relative-to-the-data-memory-start offset
    Class::addInstanceAttribute(a_pAttribute);
}

void JitClass::addInstanceAttribute( InstanceAttribute* a_pAttribute )
{
    JitInstanceAttribute* pAttribute = as<JitInstanceAttribute*>(a_pAttribute);
    if(pAttribute == nullptr)
    {
        o_exception(exception::invalid_argument_exception, "Should be a JitInstanceAttribute, other derived are not permitted"); 
    }
    else addInstanceAttribute(pAttribute);
}

void JitClass::addStaticAttribute( JitStaticAttribute* a_pAttribute )
{
    if(m_eState == e_State_Finalized)
    {
        o_exception(exception::reflection_runtime_exception, "JitClass already built, you cannot add members anymore");
    }
    Class::addStaticAttribute(a_pAttribute);
}

void JitClass::addStaticAttribute( StaticAttribute* a_pAttribute )
{
    JitStaticAttribute* pAttribute = as<JitStaticAttribute*>(a_pAttribute);
    if(pAttribute == nullptr)
    {
        o_exception(exception::invalid_argument_exception, "Should be a JitStaticAttribute, other derived are not permitted"); 
    }
    else addStaticAttribute(pAttribute);
}

void JitClass::addSuperClass( Class* a_pClass )
{
    if(m_eState != e_State_InheritanceSetup)
    {
        o_exception(exception::reflection_runtime_exception, "Once members have been added or class built you cannot add super classes anymore");
    }

    // We adjust class offset depending on added class alignment (ex : if the first super class is only a 1 byte aligned class, 
    // and the second a 4 byte aligned class, we need to put the the second super class 3 byte after the first one so that the alignment
    // is ok for the second one
    if(NOT(m_SuperClasses.empty())) 
    {
        size_t modulo = m_uiSuperSize % m_AlignmentComputer.maxAlignment();
        if(modulo)
            m_uiSuperSize += (m_AlignmentComputer.maxAlignment() - modulo);
        o_assert(m_bHasStateMachineDataPtr OR a_pClass->getStateMachine() == nullptr, "Cannot inherit from two classes which have both a state machine");
    }
    else
    {
        m_AlignmentComputer.setMaxAlignement(std::max(m_AlignmentComputer.maxAlignment(), (size_t)a_pClass->getAlignment()));
        // First class added, test if it's polymorphic, and add vtable requirement if not
        m_bHasVTablePtr = NOT(a_pClass->isPolymorphic());
    }
    
    if(a_pClass->getStateMachine() != nullptr)
    {
        m_uiStateMachineDataPtrOffset = a_pClass->getStateMachine()->getDataPtrOffset() + m_uiSuperSize;
        m_bHasStateMachineDataPtr = false;
    }

    size_t superClassOffset = m_uiSuperSize;

    Class::addSuperClass(a_pClass, superClassOffset);

    m_uiSuperSize += a_pClass->getSize();

    // we update the max alignment from the new super class
    m_AlignmentComputer.setMaxAlignement(

        m_AlignmentComputer.maxAlignment() > a_pClass->getAlignment()
        ? m_AlignmentComputer.maxAlignment()
        : a_pClass->getAlignment()

        );
}

void JitClass::finalize()
{
    if(m_eState == e_State_Finalized)
    {
        o_exception(exception::reflection_runtime_exception, "JitClass already built");
    }

    if(m_eState <= e_State_MemorySetup)
    {
        freezeMemory();
    }
    m_eState = e_State_Finalized;
}

void JitClass::addAbstractMethod( AbstractMethod* a_pInstanceMethod )
{
    if(m_eState == e_State_Finalized)
    {
        o_exception(exception::reflection_runtime_exception, "JitClass already built, you cannot add members anymore");
    }
    if(m_eState <= e_State_MemorySetup)
    {
        freezeMemory();
    }
    Class::addInstanceMethod(a_pInstanceMethod);
}

void JitClass::addInstanceMethod( JitInstanceMethod* a_pInstanceMethod )
{
    if(m_eState == e_State_Finalized)
    {
        o_exception(exception::reflection_runtime_exception, "JitClass already built, you cannot add members anymore");
    }
    if(m_eState <= e_State_MemorySetup)
    {
        freezeMemory();
    }
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    vector<InstanceMethod*> overloadeds;
    for(;it!=end;++it)
    {
        it->m_pClass->findOverloadedMethods(a_pInstanceMethod, overloadeds);
    }
    if(overloadeds.size())
    {
        // we found overloadable methods, so the added method becomes virtual
        a_pInstanceMethod->setVirtual();
    }
    Class::addInstanceMethod(a_pInstanceMethod);
}

void JitClass::addInstanceMethod( InstanceMethod* a_pMethod )
{
    JitInstanceMethod* pMethod = as<JitInstanceMethod*>(a_pMethod);
    if(pMethod == nullptr)
    {
        o_exception(exception::invalid_argument_exception, "Should be a JitInstanceAttribute, other derived are not permitted"); 
    }
    else addInstanceMethod(pMethod);
}

phantom::signal_t JitClass::aboutToBeReplaced( JitClass* a_pClass0, JitClass* a_pClass1 ) const
{
    connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_aboutToBeReplaced.head();
    while(pSlot)
    {
        connection::pair::push(const_cast<JitClass*>(this), pSlot);
        void* args[] = {&a_pClass0, &a_pClass1};
        pSlot->subroutine()->invoke(pSlot->receiver(), args );
        pSlot = pSlot->next();
        connection::pair::pop();
    }
    return signal_t();
}

void JitClass::construct( void* a_pObject ) const
{
    if(m_eState != e_State_Finalized)
    {
        ((JitClass*)this)->finalize();
    }
    // Construct super classes
    {
        super_class_table::const_iterator it = m_SuperClasses.begin();
        super_class_table::const_iterator end = m_SuperClasses.end();
        for(;it!=end;++it)
        {
            it->m_pClass->construct(((byte*)a_pObject) + it->m_uiOffset);
        }
    }
    // Create VTable(s) if not yet
    if(m_VTableInfos.empty()) // not initialized
    {
        int vtable_info_index = 0;
        bool bVTableRequired = false;
        super_class_table::const_iterator it = m_SuperClasses.begin();
        super_class_table::const_iterator end = m_SuperClasses.end();
        for(;it!=end;++it)
        {
            Class* pSuperClass = it->m_pClass;
            size_t uiSuperClassOffset = it->m_uiOffset;
            byte* address = (byte*)a_pObject + uiSuperClassOffset;

            if(m_SuperClasses.begin() == it AND uiSuperClassOffset != 0)
            {
                // first super class and offset > 0 => new vtable required
                vector<void*> virtualMethodCallAddresses;
                size_t virtualMethodIndexAcc = 0;
                member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMethod>());
                member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMethod>());
                for(;it!=end;++it)
                {
                    JitInstanceMethod* pMethod = (JitInstanceMethod*)it->second;
                    vector<InstanceMethod*> overloadeds;
                    {
                        super_class_table::const_iterator it = m_SuperClasses.begin();
                        super_class_table::const_iterator end = m_SuperClasses.end();
                        for(;it!=end;++it)
                        {
                            it->m_pClass->findOverloadedMethods(pMethod, overloadeds);
                        }
                    }
                    // Check if the method overloads another and if this another belongs to the 0-offset vtable
                    {
                        bool needToAddToTheFirstVtable = overloadeds.empty() AND pMethod->isVirtual();
                        o_foreach(InstanceMethod* pOverloaded, overloadeds)
                        {
                            if(getSuperClassOffsetCascade(pOverloaded->getOwnerClass()) != 0)
                            {
                                needToAddToTheFirstVtable = true;
                                break;
                            }
                            else
                            {
                                pMethod->setVirtualTableIndex(pOverloaded->getVirtualTableIndex());
                                pMethod->compile_vtable_indirection_function();
                            }
                        }
                        if(needToAddToTheFirstVtable)
                        {
                            pMethod->setVirtualTableIndex(virtualMethodIndexAcc++);
                            pMethod->compile_vtable_indirection_function();
                            virtualMethodCallAddresses.push_back(pMethod->getVTablePointer(0));
                        }
                    }
                }
                void** methods = nullptr;
                if(virtualMethodIndexAcc)
                {
                    methods = o_allocate_n(virtualMethodIndexAcc, void*);
                }
                vtable_info new_vtable(0, methods, virtualMethodIndexAcc);
                size_t i = 0;
                for(;i<virtualMethodIndexAcc;++i)
                {
                    new_vtable.methods[i] = virtualMethodCallAddresses[i];
                }
                m_VTableInfos.push_back(new_vtable);
                bVTableRequired = true;
                vtable_info_index++;
            }

            vector<vtable_info> super_vtables;
            pSuperClass->extractVirtualMethodTableInfos(a_pObject, super_vtables);
            
            vector<vtable_info>::iterator it = super_vtables.begin();
            vector<vtable_info>::iterator end = super_vtables.end();
            for(;it!=end;++it)
            {
                size_t vtable_offset = it->offset;
                size_t vtable_count = it->count;
                address += vtable_offset;

                void** vptr = *((void***)address);
                
                // copy vtable pointers (each one may be replaced on the next step by overloading methods vtable pointer)

                vector<void*> virtualMethodCallAddresses;
                
                size_t i = 0;
                for(;i<vtable_count;++i)
                {
                    virtualMethodCallAddresses.push_back(vptr ? vptr[i] : nullptr);
                }


                // ---- INSERT VIRTUAL METHODS ------
                member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMethod>());
                member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMethod>());
                for(;it!=end;++it)
                {
                    JitInstanceMethod* pMethod = (JitInstanceMethod*)it->second;
                    vector<InstanceMethod*> overloadeds;
                    pSuperClass->findOverloadedMethods(pMethod, overloadeds);
                    size_t i = 0;
                    size_t count = overloadeds.size();
                    // no overloaded method + virtual => new virtual method => we add it to the 0-offset vtable
                    if(count == 0 AND pMethod->isVirtual() AND uiSuperClassOffset == 0)
                    {
                        virtualMethodCallAddresses.push_back(pMethod->getVTablePointer(0));
                    }
                    // browse overloaded and replace their vtable pointer by the overloading vtable pointer
                    else for(;i<count;++i)
                    {
                        InstanceMethod* pOverloaded = overloadeds[i];
                        size_t class_offset = pSuperClass->getSuperClassOffsetCascade(pOverloaded->getOwnerClass());
                        if(class_offset == vtable_offset) // if the overloaded belongs to the current vtable/superclass offset
                        {
                            size_t vtable_index = pOverloaded->getVirtualTableIndex();
                            if(uiSuperClassOffset == 0)
                            {
                                pMethod->setVirtualTableIndex(vtable_index);
                                pMethod->compile_vtable_indirection_function();
                            }
                            virtualMethodCallAddresses.resize(std::max(virtualMethodCallAddresses.size(), size_t(vtable_index+1)));
                            virtualMethodCallAddresses[vtable_index] = pMethod->getVTablePointer(uiSuperClassOffset);
                        }
                    }
                }
                // ---- END INSERT VIRTUAL METHODS ------
                void** newVTable = nullptr;
                if(virtualMethodCallAddresses.size())
                {
                    newVTable = o_allocate_n(virtualMethodCallAddresses.size(), void*);
                    memcpy(newVTable, virtualMethodCallAddresses.data(), virtualMethodCallAddresses.size()*sizeof(void*));
                }
                vtable_info vti(vtable_offset+uiSuperClassOffset, newVTable, virtualMethodCallAddresses.size());
                m_VTableInfos.push_back(vti);
            }
        }
        o_assert(NOT(m_bHasVTablePtr) OR NOT(m_VTableInfos.empty()));
        /*if(m_VTableInfos.empty()) // still no vtable created, we create one even if no virtual method is present 
                                  // => my convention = always create vtable to ensure easy cast with inherited 
                                  // class which implements virtual methods
        {
            vector<void*> virtualMethodCallAddresses;
            member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMethod>());
            member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMethod>());
            for(;it!=end;++it)
            {
                JitInstanceMethod* pMethod = (JitInstanceMethod*)it->second;
                if(pMethod->isVirtual())
                {
                    pMethod->setVirtualTableIndex(virtualMethodCallAddresses.size());
                    pMethod->compile_vtable_indirection_function();
                    virtualMethodCallAddresses.push_back(pMethod->getVTablePointer(0));
                }
            }
            void** newVTable = nullptr;
            if(virtualMethodCallAddresses.size())
            {
                newVTable = phantom::allocate<void*>(virtualMethodCallAddresses.size());
                memcpy(newVTable, virtualMethodCallAddresses.data(), virtualMethodCallAddresses.size()*sizeof(void*));
            }
            vtable_info vti(0, newVTable, virtualMethodCallAddresses.size());
            m_VTableInfos.push_back(vti);
        }*/
    }

    // Install vtable ptrs
    {
        size_t i = 0;
        for(;i<m_VTableInfos.size(); ++i)
        {
            *((void***)((byte*)a_pObject + m_VTableInfos[i].offset)) = m_VTableInfos[i].methods;
        }
    }

    // Construct attributes
    {
        size_t i = 0;
        Type::aligner aligner(reinterpret_cast<byte*>(a_pObject)+m_uiAttributeMemoryOffset);
        for(;i<m_DataTypes.size();++i)
        {
            aligner.construct(m_DataTypes[i]);
        }
    }
    
}

void JitClass::construct( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    byte*    chunk_address = reinterpret_cast<byte*>(a_pChunk);
    while(a_uiCount--)
    {
        construct(a_pChunk);
        chunk_address += a_uiChunkSectionSize;
    }
}

void JitClass::destroy( void* a_pObject ) const
{
    size_t i = 0;
    Type::aligner aligner(reinterpret_cast<byte*>(a_pObject)+m_uiAttributeMemoryOffset);
    for(;i<m_DataTypes.size();++i)
    {
        aligner.destroy(m_DataTypes[i]);
    }
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(; it != end; ++it)
    {
        it->m_pClass->destroy((byte*)a_pObject+it->m_uiOffset);
    }
}

void JitClass::destroy( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    byte*    chunk_address = reinterpret_cast<byte*>(a_pChunk);
    while(a_uiCount--)
    {
        destroy(a_pChunk);
        chunk_address += a_uiChunkSectionSize;
    }
}

Type* JitClass::createConstType() const
{
    o_warning(false, "JitClass const version has not been implemented");
    return const_cast<JitClass*>(this);//o_new(native::TConstType<JitClass>)();
}

void JitClass::addAttribute( Attribute* a_pAttribute )
{
    JitInstanceAttribute* pAttribute = as<JitInstanceAttribute*>(a_pAttribute);
    if(pAttribute == nullptr)
    {
        o_exception(exception::invalid_argument_exception, "Should be a JitInstanceAttribute, other derived are not permitted"); 
    }
    else addInstanceAttribute(pAttribute);
}

void JitClass::addAccessor( Accessor* a_pAccessor )
{
    o_exception(exception::unsupported_method_exception, "shouldn't be used directly");
}

void JitClass::addAccessor( JitAccessor* a_pAccessor )
{
    if(m_eState <= e_State_MemorySetup)
    {
        freezeMemory();
    }

    Class::addAccessor(a_pAccessor);
}

void JitClass::addCollection( JitCollection* a_pCollection )
{
    if(m_eState <= e_State_MemorySetup)
    {
        freezeMemory();
    }

    Class::addCollection(a_pCollection);
}

void JitClass::addMethod( Method* a_pMethod )
{
    JitInstanceMethod* pMethod = as<JitInstanceMethod*>(a_pMethod);
    if(pMethod == nullptr)
    {
        o_exception(exception::invalid_argument_exception, "Should be a JitInstanceAttribute, other derived are not permitted"); 
    }
    else addInstanceMethod(pMethod);
}

void JitClass::addStaticMethod( JitStaticMethod* a_pMethod )
{
    Class::addStaticMethod(a_pMethod);
}

void JitClass::addStaticMethod( StaticMethod* a_pMethod )
{
    JitStaticMethod* pMethod = as<JitStaticMethod*>(a_pMethod);
    if(pMethod == nullptr)
    {
        o_exception(exception::invalid_argument_exception, "Should be a JitStaticAttribute, other derived are not permitted"); 
    }
    else addStaticMethod(pMethod);
}

boolean JitClass::isPolymorphic() const
{
    // Search for virtual methods
    {
        member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMethod>());
        member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMethod>());
        for(;it != end; ++it)
        {
            InstanceMethod* pMethod = static_cast<InstanceMethod*>(it->second);
            if(pMethod->isVirtual())
                return true;
        }
    }

    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(; it != end; ++it)
    {
        if(it->m_pClass->isPolymorphic()) return true;
    }
    return false;
}

void JitClass::InstallHelper( Class* a_pBaseClass, void* a_pBase, Class* a_pLayoutClass, void* a_pLayout, connection::slot_pool* sp )
{
    rtti_data rd;
    rd.base = a_pBase;
    rd.object_class = a_pBaseClass;
    rd.layout_class = a_pLayoutClass;
    rd.dynamic_delete_func = 0;
    rd.connection_slot_allocator = sp;
    phantom::addRttiData(a_pLayout, rd);
    super_class_table::const_iterator it = a_pLayoutClass->superClassBegin();
    super_class_table::const_iterator end = a_pLayoutClass->superClassEnd();
    for(; it != end; ++it)
    {
        Class* pSuperClass = it->m_pClass;
        size_t superClassOffset = it->m_uiOffset;
        if(superClassOffset != 0)
        {
            void* this_layout = (byte*)a_pLayout + superClassOffset;
            InstallHelper(a_pBaseClass, a_pBase, pSuperClass, this_layout, sp);
        }
    }
}

void JitClass::UninstallHelper( void* a_pLayout, Class* a_pLayoutClass )
{
    phantom::removeRttiData(a_pLayout);
    super_class_table::const_iterator it = a_pLayoutClass->superClassBegin();
    super_class_table::const_iterator end = a_pLayoutClass->superClassEnd();
    for(; it != end; ++it)
    {
        Class* pSuperClass = it->m_pClass;
        size_t superClassOffset = it->m_uiOffset;
        if(superClassOffset != 0)
        {
            void* this_layout = (byte*)a_pLayout + superClassOffset;
            UninstallHelper(this_layout, pSuperClass);
        }
    }
}

void JitClass::addSignal( JitSignal* a_pSignal )
{
    Class::addSignal(a_pSignal);
}

void JitClass::serialize( void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    super_class_table::const_iterator it = superClassBegin();
    super_class_table::const_iterator end = superClassEnd();
    for(; it != end; ++it)
    {
        Class* pSuperClass = it->m_pClass;
        pSuperClass->serialize((byte*)a_pInstance + it->m_uiOffset, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    property_tree class_tree;
    serializeLayout(a_pInstance, class_tree, a_uiSerializationMask, a_pDataBase);
    a_OutBranch.add_child(encodeQualifiedDecoratedNameToIdentifierName(getQualifiedDecoratedName()), class_tree);
}

void JitClass::deserialize( void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    auto it = superClassBegin();
    auto end = superClassEnd();
    for(; it != end; ++it)
    {
        Class* pSuperClass = it->m_pClass;
        pSuperClass->deserialize((byte*)a_pInstance + it->m_uiOffset, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    {
        auto it = a_InBranch.begin();
        auto end = a_InBranch.end();
        for(;it!=end;++it)
        {
            // The test below could seem dirty but it's useful to deserialize typedefs or placeholder types 
            // which goal is to point to a type without having the same representation name (ex: my_vector2 could point to phantom::math::vector2<float>)
            // It's also useful is you have a type versionning (a script class rebuilt with a different name but you still want to deserialize from the older type name
            reflection::Type* solvedType = a_pDataBase->solveTypeByName(decodeQualifiedDecoratedNameFromIdentifierName(it->first));
            if(solvedType == this)
            {
                deserializeLayout(a_pInstance, it->second, a_uiSerializationMask, a_pDataBase);
            }
        }
    }
}

void JitClass::serializeLayout( void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    reflection::ClassType::member_const_iterator it = propertiesBegin();
    reflection::ClassType::member_const_iterator end = propertiesEnd();
    for(;it != end; ++it)
    {
        reflection::Property*const pProperty = static_cast<reflection::Property*const>(it->second);
        if(pProperty->isSaved(a_uiSerializationMask))
            pProperty->serializeValue(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
}

void JitClass::deserializeLayout( void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    auto it = propertiesBegin();
    auto end = propertiesEnd();
    for(;it != end; ++it)
    {
        reflection::Property* const pProperty = static_cast<reflection::Property*const>(it->second);
        if(pProperty->isSaved(a_uiSerializationMask)) 
            pProperty->deserializeValue(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
}


o_destructor JitClass::~JitClass( void )
{
    jit_context_destroy(m_Context);
    auto it = m_VTableInfos.begin();
    auto end = m_VTableInfos.end();
    for(;it!=end;++it)
    {
        if(it->count)
        o_deallocate_n(it->methods, it->count, void*);
    }
}

phantom::restore_state JitClass::restore( void* a_pInstance, uint a_uiSerializationFlag, uint a_uiPass ) const
{
    restore_state rs = restore_complete;
    super_class_table::const_iterator it = superClassBegin();
    super_class_table::const_iterator end = superClassEnd();
    for(; it != end; ++it)
    {
        rs = combine_restore_states(rs, it->m_pClass->restore(((byte*)a_pInstance)+it->m_uiOffset, a_uiSerializationFlag, a_uiPass));
    }
    if(rs == restore_complete AND m_bHasStateMachineDataPtr)
    {
        m_pStateMachine->initialize(a_pInstance);
    }
    return rs;
}

void JitClass::freezeMemory()
{
    // layout : [vtableptr] [superlayout] [smdataptr] [attributes]

    if(m_eState == e_State_InheritanceSetup)
    {
        m_eState = e_State_MemorySetup;
    }
    if(m_eState != e_State_MemorySetup)
    {
        o_exception(exception::reflection_runtime_exception, "Memory already frozen");
    }

    // Check if we really need a vtableptr
    if(m_bHasVTablePtr)
    {
        m_bHasVTablePtr = false;
        member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMethod>());
        member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMethod>());
        for(;it != end; ++it)
        {
            InstanceMethod* pMethod = static_cast<InstanceMethod*>(it->second);
            if(pMethod->isVirtual())
            {
                m_bHasVTablePtr = true;
                break;
            }
        }
        // Shift super class offset depending on if we have a vtableptr
        if(m_bHasVTablePtr)
        {
            super_class_table::iterator it = m_SuperClasses.begin();
            super_class_table::iterator end = m_SuperClasses.end();
            for(;it!=end;++it)
            {
                it->m_uiOffset += sizeof(void*);
            }
        }
    }

    // Check if we really need a smdataptr
    if(m_bHasStateMachineDataPtr)
    {
        o_assert(m_uiStateMachineDataPtrOffset == 0xffffffff);
        if(getStateMachine())
        {
            m_uiStateMachineDataPtrOffset = hasVTableDataPtr()*sizeof(void*)+m_uiSuperSize;
            ((state::runtime::JitStateMachine*)getStateMachine())->setDataPtrOffset(m_uiStateMachineDataPtrOffset);
        }
        else
        {
            m_bHasStateMachineDataPtr = false;
        }
    }
    else 
    {
        o_assert(m_uiStateMachineDataPtrOffset != 0xffffffff);
        m_uiStateMachineDataPtrOffset += m_bHasVTablePtr*sizeof(void*);
    }

    size_t  rootSize = m_uiSuperSize + m_bHasVTablePtr*sizeof(void*) + m_bHasStateMachineDataPtr *sizeof(void*); 
    size_t  memorySize = m_AlignmentComputer.compute();
    if(memorySize == 0 AND rootSize == 0)
    {
        memorySize = 4;
    }
    if(m_AlignmentComputer.maxAlignment() == 0 && memorySize == 0)
    {
        m_AlignmentComputer.setMaxAlignement(1);
    }
    size_t  modulo = rootSize ? rootSize % m_AlignmentComputer.maxAlignment() : 0;
    if(modulo)
        m_uiAlignmentFixingOffset = m_AlignmentComputer.maxAlignment() - modulo;
    m_uiAttributeMemoryOffset = rootSize+m_uiAlignmentFixingOffset;

    m_uiSize = m_uiAttributeMemoryOffset+memorySize;
    m_uiAlignment = m_AlignmentComputer.maxAlignment();

    member_collection::const_iterator it = m_Members.lower_bound(classOf<Property>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<Property>());
    for(;it != end; ++it)
    {
        JitInstanceAttribute* pAttribute = as<JitInstanceAttribute*>(it->second);
        // Finalize attribute offset
        if(pAttribute)
        {
            pAttribute->setOffset(m_uiAttributeMemoryOffset+pAttribute->getOffset()); // we convert from relative to absolute attribute offset
        }
    }
    m_eState = e_State_MemoryFrozen;
}

void JitClass::extractVirtualMethodTableInfos( const void* a_pInstance, vector<vtable_info>& vtables )
{
    vtables.insert(vtables.end(), m_VTableInfos.begin(), m_VTableInfos.end());
}

void JitClass::initialize( void* a_pInstance ) const
{
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it!=end;++it)
    {
        it->m_pClass->initialize((byte*)a_pInstance+it->m_uiOffset);
    }
    if(m_bHasStateMachineDataPtr)
    {
        m_pStateMachine->initialize(a_pInstance);
    }
}

void JitClass::terminate( void* a_pInstance ) const
{
    if(m_bHasStateMachineDataPtr)
    {
        m_pStateMachine->terminate(a_pInstance);
    }
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it!=end;++it)
    {
        it->m_pClass->terminate((byte*)a_pInstance+it->m_uiOffset);
    }
}

o_namespace_end(phantom, reflection, runtime)