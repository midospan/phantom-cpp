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
#include "phantom/jit.h"
#include "JitClass.h"
#include "JitClass.hxx"
#include <phantom/def_jit.h>
#include "JitInstanceDataMember.h"
#include "JitStaticDataMember.h"
#include "JitInstanceMemberFunction.h"
#include "JitSignal.h"
#include "JitStaticMemberFunction.h"
#include "JitProperty.h"
#include "JitCollection.h"
#include <phantom/state/jit/JitStateMachine.h>
/* *********************************************** */
o_registerN((phantom, reflection, jit), JitClass);


o_namespace_begin(phantom, reflection, jit)

JitClass::JitClass( const string& a_strName, bitfield a_bfModifiers /*= bitfield()*/ ) 
    : Class(a_strName, 0, 0, a_bfModifiers)
    , m_uiDataMemberMemoryOffset(0)
    , m_uiDataTypeCount(0)
    , m_AlignmentComputer(0)
    , m_uiAlignmentFixingOffset(0)
    , m_uiSuperSize(0)
    , m_eState(e_State_InheritanceSetup)
    , m_bHasVTablePtr(true)
    , m_bHasStateMachineDataPtr(true)
    , m_uiStateMachineDataPtrOffset(0xffffffff)
    , m_pInitializeMemberFunction(nullptr)
    , m_pRestoreMemberFunction(nullptr)
    , m_pTerminateMemberFunction(nullptr)
{
}

o_destructor JitClass::~JitClass( void )
{
    auto it = m_VTableInfos.begin();
    auto end = m_VTableInfos.end();
    for(;it!=end;++it)
    {
        if(it->count)
            o_deallocate_n(it->member_functions, it->count, void*);
    }
}

void JitClass::setStateMachine( state::jit::JitStateMachine* a_pStateMachine )
{
    if(m_pStateMachine)
    {
        o_exception(reflection_jit_exception, "StateMachine already added, you cannot add more than one state machine");
    }
    if(m_eState == e_State_InheritanceSetup)
    {
        m_eState = e_State_MemberSetup;
    }
    else if(m_eState >= e_State_Compiling)
    {
        o_exception(reflection_jit_exception, "Class being compiling or compiled, you cannot add state machine anymore");
    }
    a_pStateMachine->setup(getStateMachineCascade());
    Class::setStateMachine(a_pStateMachine);
}

void JitClass::addInstanceDataMember( JitInstanceDataMember* a_pDataMember )
{
    if(m_eState >= e_State_Compiling)
    {
        o_exception(reflection_jit_exception, "Class being compiling or compiled, you cannot add attributes anymore");
    }
    else
    {
        m_eState = e_State_MemberSetup;
    }
    Type* pContentType = a_pDataMember->getValueType();
    m_DataTypes.push_back(pContentType);
    a_pDataMember->setOffset(m_AlignmentComputer.push(pContentType)); // we store a relative-to-the-data-memory-start offset
    Class::addInstanceDataMember(a_pDataMember);
}

void JitClass::addInstanceDataMember( InstanceDataMember* a_pDataMember )
{
    JitInstanceDataMember* pDataMember = as<JitInstanceDataMember*>(a_pDataMember);
    if(pDataMember == nullptr)
    {
        o_exception(exception::invalid_argument_exception, "Should be or should derive from JitInstanceDataMember"); 
    }
    else addInstanceDataMember(pDataMember);
}

void JitClass::addStaticDataMember( JitStaticDataMember* a_pDataMember )
{
    if(m_eState == e_State_Compiled)
    {
        o_exception(reflection_jit_exception, "JitClass already built, you cannot add members anymore");
    }
    Class::addStaticDataMember(a_pDataMember);
}

void JitClass::addStaticDataMember( StaticDataMember* a_pDataMember )
{
    JitStaticDataMember* pDataMember = as<JitStaticDataMember*>(a_pDataMember);
    if(pDataMember == nullptr)
    {
        o_exception(exception::invalid_argument_exception, "Should be or should derive from JitStaticDataMember"); 
    }
    else addStaticDataMember(pDataMember);
}

void JitClass::addSuperClass( Class* a_pClass )
{
    if(m_eState != e_State_InheritanceSetup)
    {
        o_exception(reflection_jit_exception, "Members have been added or class compiled, you cannot add super classes anymore");
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

void JitClass::endCompilation()
{
    o_assert(m_eState == e_State_Compiling);

    m_eState = e_State_Compiled;
}

void JitClass::addPureVirtualMemberFunction( PureVirtualMemberFunction* a_pInstanceMemberFunction )
{
    if(m_eState >= e_State_Compiling)
    {
        o_exception(reflection_jit_exception, "Class compiling or compiled, you cannot add members anymore");
    }
    Class::addInstanceMemberFunction(a_pInstanceMemberFunction);
}

void JitClass::addInstanceMemberFunction( JitInstanceMemberFunction* a_pInstanceMemberFunction )
{
    if(m_eState >= e_State_Compiling)
    {
        o_exception(reflection_jit_exception, "Class compiling or compiled, you cannot add members anymore");
    }
    else if(m_eState == e_State_InheritanceSetup)
    {
        m_eState = e_State_MemberSetup;
    }
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    vector<InstanceMemberFunction*> overloadeds;
    for(;it!=end;++it)
    {
        it->m_pClass->findOverloadedMemberFunctions(a_pInstanceMemberFunction, overloadeds);
    }
    if(overloadeds.size())
    {
        // we found overloadable member_functions, so the added method becomes virtual
        a_pInstanceMemberFunction->setVirtual();
    }
    Class::addInstanceMemberFunction(a_pInstanceMemberFunction);
}

void JitClass::addInstanceMemberFunction( InstanceMemberFunction* a_pMemberFunction )
{
    JitInstanceMemberFunction* pMemberFunction = as<JitInstanceMemberFunction*>(a_pMemberFunction);
    if(pMemberFunction == nullptr)
    {
        o_exception(exception::invalid_argument_exception, "Should be or should derive from JitInstanceMemberFunction"); 
    }
    else addInstanceMemberFunction(pMemberFunction);
}

phantom::signal_t JitClass::aboutToBeReplaced( JitClass* a_pClass0, JitClass* a_pClass1 ) const
{
    connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_aboutToBeReplaced.head();
    while(pSlot)
    {
        connection::pair::push(const_cast<JitClass*>(this), pSlot);
        void* args[] = {&a_pClass0, &a_pClass1};
        pSlot->subroutine()->call(pSlot->receiver(), args );
        pSlot = pSlot->next();
        connection::pair::pop();
    }
    return signal_t();
}

void JitClass::construct( void* a_pObject ) const
{
    o_assert(m_eState == e_State_Compiled);
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
                vector<void*> virtualMemberFunctionCallAddresses;
                size_t virtualMemberFunctionIndexAcc = 0;
                member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMemberFunction>());
                member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMemberFunction>());
                for(;it!=end;++it)
                {
                    JitInstanceMemberFunction* pMemberFunction = (JitInstanceMemberFunction*)it->second;
                    vector<InstanceMemberFunction*> overloadeds;
                    {
                        super_class_table::const_iterator it = m_SuperClasses.begin();
                        super_class_table::const_iterator end = m_SuperClasses.end();
                        for(;it!=end;++it)
                        {
                            it->m_pClass->findOverloadedMemberFunctions(pMemberFunction, overloadeds);
                        }
                    }
                    // Check if the method overloads another and if this another belongs to the 0-offset vtable
                    {
                        bool needToAddToTheFirstVtable = overloadeds.empty() AND pMemberFunction->isVirtual();
                        o_foreach(InstanceMemberFunction* pOverloaded, overloadeds)
                        {
                            if(getSuperClassOffsetCascade(pOverloaded->getOwnerClass()) != 0)
                            {
                                needToAddToTheFirstVtable = true;
                                break;
                            }
                            else
                            {
                                pMemberFunction->setVirtualTableIndex(pOverloaded->getVirtualTableIndex());
                                pMemberFunction->compileVTableIndirectionFunction();
                            }
                        }
                        if(needToAddToTheFirstVtable)
                        {
                            pMemberFunction->setVirtualTableIndex(virtualMemberFunctionIndexAcc++);
                            pMemberFunction->compileVTableIndirectionFunction();
                            virtualMemberFunctionCallAddresses.push_back(pMemberFunction->getVTablePointer(0));
                        }
                    }
                }
                void** member_functions = nullptr;
                if(virtualMemberFunctionIndexAcc)
                {
                    member_functions = o_allocate_n(virtualMemberFunctionIndexAcc, void*);
                }
                vtable_info new_vtable(0, member_functions, virtualMemberFunctionIndexAcc);
                size_t i = 0;
                for(;i<virtualMemberFunctionIndexAcc;++i)
                {
                    new_vtable.member_functions[i] = virtualMemberFunctionCallAddresses[i];
                }
                m_VTableInfos.push_back(new_vtable);
                bVTableRequired = true;
                vtable_info_index++;
            }

            vector<vtable_info> super_vtables;
            pSuperClass->extractVirtualMemberFunctionTableInfos(a_pObject, super_vtables);
            
            vector<vtable_info>::iterator it = super_vtables.begin();
            vector<vtable_info>::iterator end = super_vtables.end();
            for(;it!=end;++it)
            {
                size_t vtable_offset = it->offset;
                size_t vtable_count = it->count;
                address += vtable_offset;

                void** vptr = *((void***)address);
                
                // copy vtable pointers (each one may be replaced on the next step by overloading member_functions vtable pointer)

                vector<void*> virtualMemberFunctionCallAddresses;
                
                size_t i = 0;
                for(;i<vtable_count;++i)
                {
                    virtualMemberFunctionCallAddresses.push_back(vptr ? vptr[i] : nullptr);
                }


                // ---- INSERT VIRTUAL METHODS ------
                member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMemberFunction>());
                member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMemberFunction>());
                for(;it!=end;++it)
                {
                    JitInstanceMemberFunction* pMemberFunction = (JitInstanceMemberFunction*)it->second;
                    vector<InstanceMemberFunction*> overloadeds;
                    pSuperClass->findOverloadedMemberFunctions(pMemberFunction, overloadeds);
                    size_t i = 0;
                    size_t count = overloadeds.size();
                    // no overloaded method + virtual => new virtual method => we add it to the 0-offset vtable
                    if(count == 0 AND pMemberFunction->isVirtual() AND uiSuperClassOffset == 0)
                    {
                        virtualMemberFunctionCallAddresses.push_back(pMemberFunction->getVTablePointer(0));
                    }
                    // browse overloaded and replace their vtable pointer by the overloading vtable pointer
                    else for(;i<count;++i)
                    {
                        InstanceMemberFunction* pOverloaded = overloadeds[i];
                        size_t class_offset = pSuperClass->getSuperClassOffsetCascade(pOverloaded->getOwnerClass());
                        if(class_offset == vtable_offset) // if the overloaded belongs to the current vtable/superclass offset
                        {
                            size_t vtable_index = pOverloaded->getVirtualTableIndex();
                            if(uiSuperClassOffset == 0)
                            {
                                pMemberFunction->setVirtualTableIndex(vtable_index);
                                pMemberFunction->compileVTableIndirectionFunction();
                            }
                            virtualMemberFunctionCallAddresses.resize(std::max(virtualMemberFunctionCallAddresses.size(), size_t(vtable_index+1)));
                            virtualMemberFunctionCallAddresses[vtable_index] = pMemberFunction->getVTablePointer(uiSuperClassOffset);
                        }
                    }
                }
                // ---- END INSERT VIRTUAL METHODS ------
                void** newVTable = nullptr;
                if(virtualMemberFunctionCallAddresses.size())
                {
                    newVTable = o_allocate_n(virtualMemberFunctionCallAddresses.size(), void*);
                    memcpy(newVTable, virtualMemberFunctionCallAddresses.data(), virtualMemberFunctionCallAddresses.size()*sizeof(void*));
                }
                vtable_info vti(vtable_offset+uiSuperClassOffset, newVTable, virtualMemberFunctionCallAddresses.size());
                m_VTableInfos.push_back(vti);
            }
        }
        o_assert(NOT(m_bHasVTablePtr) OR NOT(m_VTableInfos.empty()));
        /*if(m_VTableInfos.empty()) // still no vtable created, we create one even if no virtual method is present 
                                  // => my convention = always create vtable to ensure easy cast with inherited 
                                  // class which implements virtual member_functions
        {
            vector<void*> virtualMemberFunctionCallAddresses;
            member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMemberFunction>());
            member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMemberFunction>());
            for(;it!=end;++it)
            {
                JitInstanceMemberFunction* pMemberFunction = (JitInstanceMemberFunction*)it->second;
                if(pMemberFunction->isVirtual())
                {
                    pMemberFunction->setVirtualTableIndex(virtualMemberFunctionCallAddresses.size());
                    pMemberFunction->compileVTableIndirectionFunction();
                    virtualMemberFunctionCallAddresses.push_back(pMemberFunction->getVTablePointer(0));
                }
            }
            void** newVTable = nullptr;
            if(virtualMemberFunctionCallAddresses.size())
            {
                newVTable = phantom::allocate<void*>(virtualMemberFunctionCallAddresses.size());
                memcpy(newVTable, virtualMemberFunctionCallAddresses.data(), virtualMemberFunctionCallAddresses.size()*sizeof(void*));
            }
            vtable_info vti(0, newVTable, virtualMemberFunctionCallAddresses.size());
            m_VTableInfos.push_back(vti);
        }*/
    }

    // Install vtable ptrs
    {
        size_t i = 0;
        for(;i<m_VTableInfos.size(); ++i)
        {
            *((void***)((byte*)a_pObject + m_VTableInfos[i].offset)) = m_VTableInfos[i].member_functions;
        }
    }

    // Construct attributes
    {
        size_t i = 0;
        Type::aligner aligner(reinterpret_cast<byte*>(a_pObject)+m_uiDataMemberMemoryOffset);
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
    Type::aligner aligner(reinterpret_cast<byte*>(a_pObject)+m_uiDataMemberMemoryOffset);
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

void JitClass::addDataMember( DataMember* a_pDataMember )
{
    JitInstanceDataMember* pDataMember = as<JitInstanceDataMember*>(a_pDataMember);
    if(pDataMember == nullptr)
    {
        o_exception(exception::invalid_argument_exception, "Should be or should derive from JitInstanceDataMember"); 
    }
    else addInstanceDataMember(pDataMember);
}

void JitClass::addProperty( Property* a_pProperty )
{
    JitProperty* pJitProperty = as<JitProperty*>(a_pProperty);
    if(pJitProperty == nullptr)
    {
        o_exception(exception::invalid_argument_exception, "Should be or should derive from JitProperty"); 
    }
    addProperty(pJitProperty);
}

void JitClass::addProperty( JitProperty* a_pProperty )
{
    if(m_eState == e_State_InheritanceSetup)
    {
        m_eState = e_State_MemberSetup;
    }
    else if(m_eState >= e_State_Compiling)
    {
        o_exception(reflection_jit_exception, "Class compiling or compiled, you cannot add members anymore");
    }

    Class::addProperty(a_pProperty);
}

void JitClass::addCollection( JitCollection* a_pCollection )
{
    if(m_eState == e_State_InheritanceSetup)
    {
        m_eState = e_State_MemberSetup;
    }
    else if(m_eState >= e_State_Compiling)
    {
        o_exception(reflection_jit_exception, "Class compiling or compiled, you cannot add members anymore");
    }

    Class::addCollection(a_pCollection);
}

void JitClass::addMemberFunction( MemberFunction* a_pMemberFunction )
{
    JitInstanceMemberFunction* pMemberFunction = as<JitInstanceMemberFunction*>(a_pMemberFunction);
    if(pMemberFunction == nullptr)
    {
        o_exception(exception::invalid_argument_exception, "Should be or should derive from JitInstanceDataMember"); 
    }
    else addInstanceMemberFunction(pMemberFunction);
}

void JitClass::addStaticMemberFunction( JitStaticMemberFunction* a_pMemberFunction )
{
    Class::addStaticMemberFunction(a_pMemberFunction);
}

void JitClass::addSignal( JitSignal* a_pSignal )
{
    addInstanceDataMember(a_pSignal->getDataMember());
    Class::addSignal(a_pSignal);
}

void JitClass::addStaticMemberFunction( StaticMemberFunction* a_pMemberFunction )
{
    JitStaticMemberFunction* pMemberFunction = as<JitStaticMemberFunction*>(a_pMemberFunction);
    if(pMemberFunction == nullptr)
    {
        o_exception(exception::invalid_argument_exception, "Should be or should derive from JitStaticDataMember"); 
    }
    else addStaticMemberFunction(pMemberFunction);
}

boolean JitClass::isPolymorphic() const
{
    // Search for virtual member_functions
    {
        member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMemberFunction>());
        member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMemberFunction>());
        for(;it != end; ++it)
        {
            InstanceMemberFunction* pMemberFunction = static_cast<InstanceMemberFunction*>(it->second);
            if(pMemberFunction->isVirtual())
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
    reflection::ClassType::member_const_iterator it = beginValueMembers();
    reflection::ClassType::member_const_iterator end = endValueMembers();
    for(;it != end; ++it)
    {
        reflection::ValueMember*const pValueMember = static_cast<reflection::ValueMember*const>(it->second);
        if(pValueMember->isSaved(a_uiSerializationMask))
            pValueMember->serializeValue(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
}

void JitClass::deserializeLayout( void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    auto it = beginValueMembers();
    auto end = endValueMembers();
    for(;it != end; ++it)
    {
        reflection::ValueMember* const pValueMember = static_cast<reflection::ValueMember*const>(it->second);
        if(pValueMember->isSaved(a_uiSerializationMask)) 
            pValueMember->deserializeValue(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
}


phantom::restore_state JitClass::restore( void* a_pInstance, uint a_uiSerializationFlag, uint a_uiPass ) const
{
    restore_state result = restore_complete;
    super_class_table::const_iterator it = superClassBegin();
    super_class_table::const_iterator end = superClassEnd();
    for(; it != end; ++it)
    {
        result = combine_restore_states(result, it->m_pClass->restore(((byte*)a_pInstance)+it->m_uiOffset, a_uiSerializationFlag, a_uiPass));
    }
    if(result == restore_complete AND m_bHasStateMachineDataPtr)
    {
        m_pStateMachine->getInstanceData(a_pInstance)->initialize();
    }
    if(m_pRestoreMemberFunction)
    {
        if(NOT(m_pRestoreMemberFunction->isCompiled()))
        {
            // Finalize restore function by inserting this code ...
            // return (pass >= 1) ? phantom::restore_complete : phantom::restore_incomplete;
            m_pRestoreMemberFunction->startCompilation();
            jit_value pass_value = m_pRestoreMemberFunction->getParameter(1);
            jit_label if_label;
            m_pRestoreMemberFunction->branchIf(m_pRestoreMemberFunction->lt(pass_value, m_pRestoreMemberFunction->createUIntConstant(1)), &if_label);
            m_pRestoreMemberFunction->returnValue(m_pRestoreMemberFunction->createUIntConstant(phantom::restore_complete));
            m_pRestoreMemberFunction->label(&if_label);
            m_pRestoreMemberFunction->returnValue(m_pRestoreMemberFunction->createUIntConstant(phantom::restore_incomplete));

            // ...and of course by compiling it
            m_pRestoreMemberFunction->endCompilation();
        }

        void* args[3] = {&a_pInstance, &a_uiSerializationFlag, &a_uiPass};

        phantom::restore_state func_result = phantom::restore_complete;
        m_pRestoreMemberFunction->call(args, &func_result);

        result = combine_restore_states(result, func_result);
    }
    return result;
}

void JitClass::startCompilation()
{
    // layout : [vtableptr] [superlayout] [smdataptr] [data_members]

    if(m_eState >= e_State_Compiling)
    {
        o_exception(reflection_jit_exception, "Class already compiling or compiled");
    }
    m_eState = e_State_Compiling;

    // Check if we really need a vtableptr
    if(m_bHasVTablePtr)
    {
        m_bHasVTablePtr = false;
        member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMemberFunction>());
        member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMemberFunction>());
        for(;it != end; ++it)
        {
            InstanceMemberFunction* pMemberFunction = static_cast<InstanceMemberFunction*>(it->second);
            if(pMemberFunction->isVirtual())
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
    if(m_pStateMachine)
        ((state::jit::JitStateMachine*)getStateMachine())->setDataPtrOffset(m_uiStateMachineDataPtrOffset);

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
    m_uiDataMemberMemoryOffset = rootSize+m_uiAlignmentFixingOffset;

    m_uiSize = m_uiDataMemberMemoryOffset+memorySize;
    m_uiAlignment = m_AlignmentComputer.maxAlignment();

    member_collection::const_iterator it = m_Members.lower_bound(classOf<ValueMember>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<ValueMember>());
    for(;it != end; ++it)
    {
        JitInstanceDataMember* pDataMember = as<JitInstanceDataMember*>(it->second);
        // Finalize attribute offset
        if(pDataMember)
        {
            pDataMember->setOffset(m_uiDataMemberMemoryOffset+pDataMember->getOffset()); // we convert from relative to absolute attribute offset
        }
    }
    if(m_pStateMachine)
        ((state::jit::JitStateMachine*)getStateMachine())->compile();
}

void JitClass::extractVirtualMemberFunctionTableInfos( const void* a_pInstance, vector<vtable_info>& vtables )
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
        m_pStateMachine->getInstanceData(a_pInstance)->initialize();
    }

    if(m_pInitializeMemberFunction)
    {
        if(NOT(m_pInitializeMemberFunction->isCompiled()))
        {
            // ...and of course by compiling it
            m_pInitializeMemberFunction->startCompilation();
            m_pInitializeMemberFunction->endCompilation();
            void* args[1] = {&a_pInstance};
            m_pInitializeMemberFunction->call(args, nullptr);
        }
    }
}

void JitClass::terminate( void* a_pInstance ) const
{
    if(m_pTerminateMemberFunction)
    {
        if(NOT(m_pTerminateMemberFunction->isCompiled()))
        {
            // ...and of course by compiling it
            m_pTerminateMemberFunction->startCompilation();
            m_pTerminateMemberFunction->endCompilation();
            void* args[1] = {&a_pInstance};
            m_pTerminateMemberFunction->call(args, nullptr);
        }
    }
    if(m_bHasStateMachineDataPtr)
    {
        m_pStateMachine->getInstanceData(a_pInstance)->terminate();
    }
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it!=end;++it)
    {
        it->m_pClass->terminate((byte*)a_pInstance+it->m_uiOffset);
    }
}
JitInstanceMemberFunction* JitClass::addInitializeMemberFunction()
{
    o_assert(m_pInitializeMemberFunction == nullptr);
    Signature* pSignature = o_new(Signature);
    pSignature->setReturnType(phantom::typeOf<void>());
    m_pInitializeMemberFunction = o_new(JitInstanceMemberFunction)("PHANTOM_CODEGEN_initialize", pSignature, o_protected);
    addInstanceMemberFunction(m_pInitializeMemberFunction);
    return m_pInitializeMemberFunction;
}

JitInstanceMemberFunction* JitClass::addTerminateMemberFunction()
{
    o_assert(m_pTerminateMemberFunction == nullptr);
    Signature* pSignature = o_new(Signature);
    pSignature->setReturnType(phantom::typeOf<void>());
    m_pTerminateMemberFunction = o_new(JitInstanceMemberFunction)("PHANTOM_CODEGEN_terminate", pSignature, o_protected);
    addInstanceMemberFunction(m_pTerminateMemberFunction);
    return m_pTerminateMemberFunction;
}

JitInstanceMemberFunction* JitClass::addRestoreMemberFunction()
{
    o_assert(m_pRestoreMemberFunction == nullptr);
    Signature* pSignature = o_new(Signature);
    pSignature->setReturnType(phantom::typeOf<uint>());
    pSignature->addParameterType(phantom::typeOf<uint>());
    pSignature->addParameterType(phantom::typeOf<uint>());
    m_pRestoreMemberFunction = o_new(JitInstanceMemberFunction)("PHANTOM_CODEGEN_restore", pSignature, o_protected);
    addInstanceMemberFunction(m_pRestoreMemberFunction);
    return m_pRestoreMemberFunction;
}

o_namespace_end(phantom, reflection, jit)
