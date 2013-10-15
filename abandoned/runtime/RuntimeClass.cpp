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
#include "phantom/def_runtime.h"
/* ** The Class Header must be the last #include * */
#include <phantom/reflection/runtime/RuntimeClass.h>
/* *********************************************** */
o_cpp_begin

ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP

state::runtime::RuntimeStateMachine* RuntimeClass::builder::addStateMachine()
{
    return NULL;
//     RuntimeStateMachine*    pRuntimeStateMachine = o_NewInstanceOf(RuntimeStateMachine);
//     m_pBuiltRuntimeClass->setStateMachine(pRuntimeStateMachine);
}

void RuntimeClass::builder::add( RuntimeInstanceAttribute* a_pAttribute )
{
    if(m_eState == eInheritanceSetup )
    {
        m_eState = eMethodSetup;
    }
    else if(m_eState != eAttributeSetup)
    {
        o_exception(exception::reflection_runtime_exception, "Adding order not respected. Must be superclasses->attributes->methods->accessors");
    }
    {
        Type* pContentType = a_pAttribute->getValueType();
        a_pAttribute->setAddressOffset(m_AlignmentComputer.push(pContentType)); // we store a relative-to-the-data-memory-start offset
        m_InstanceAttributes.push_back(a_pAttribute);
    }
}

void RuntimeClass::builder::add( RuntimeStaticAttribute* a_pAttribute )
{
    if(m_eState == eInheritanceSetup )
    {
        m_eState = eMethodSetup;
    }
    else if(m_eState != eAttributeSetup)
    {
        o_exception(exception::reflection_runtime_exception, "Adding order not respected. Must be superclasses->attributes->methods->accessors");
    }
    m_StaticAttributes.push_back(a_pAttribute);
}

void RuntimeClass::builder::add( Class* a_pClass )
{
    if(m_eState != eInheritanceSetup)
    {
        o_exception(exception::reflection_runtime_exception, "Once members have been added or class built you cannot add super classes anymore");
    }

    // We adjust class offset depending on added class alignment (ex : if the first super class is only a 1 byte aligned class, 
    // and the second a 4 byte aligned class, we need to put the the second super class 3 byte after the first one so that the alignment
    // is ok for the second one
    if(NOT(m_SuperClasses.empty())) 
    {
        size_t modulo = m_uiSize % m_AlignmentComputer.maxAlignment();
        if(modulo)
            m_uiSize += (m_AlignmentComputer.maxAlignment() - modulo);

    }
    m_SuperClasses.push_back(super_class_data(a_pClass, m_uiSize));

    m_uiSize += a_pClass->getSize();

    // we update the max alignment from the new super class
    m_AlignmentComputer.setMaxAlignement(

        m_AlignmentComputer.maxAlignment() > a_pClass->getAlignment()
        ? m_AlignmentComputer.maxAlignment()
        : a_pClass->getAlignment()

        );
}

RuntimeClass* RuntimeClass::builder::build()
{
    if(m_eState == eDone)
    {
        o_exception(exception::reflection_runtime_exception, "RuntimeClass already built");
    }
    m_eState = eDone;

    if(m_InstanceAttributes.empty())
        return m_pBuiltRuntimeClass;

    if(m_pBuiltRuntimeClass == NULL) buildRuntimeClass();

    m_pBuiltRuntimeClass->m_pDataTypes = (Type**)phantom::dynamicPoolAllocate(m_InstanceAttributes.size()*sizeof(Type*)) ;
    size_t i = 0;
    o_foreach(RuntimeInstanceAttribute* pAttribute, m_InstanceAttributes)
    {
        pAttribute->setAddressOffset(m_uiDataStartOffset+pAttribute->getAddressOffset()); // we convert from relative to absolute attribute offset
        m_pBuiltRuntimeClass->m_pDataTypes[i] = pAttribute->getContentType();
        ++i;
    }
    m_pBuiltRuntimeClass->m_uiDataTypeCount = m_InstanceAttributes.size();
    return m_pBuiltRuntimeClass;
}

phantom::signal_t RuntimeClass::aboutToBeReplaced( RuntimeClass* a_pClass0, RuntimeClass* a_pClass1 ) const
{
    connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_aboutToBeReplaced.head();
    while(pSlot)
    {
        connection::pair::push(const_cast<RuntimeClass*>(this), pSlot->receiver());
        void* args[] = {&a_pClass0, &a_pClass1};
        pSlot->subroutine()->invoke(pSlot->receiver(), args );
        pSlot = pSlot->next();
        connection::pair::pop();
    }
    return signal_t();
}

void RuntimeClass::construct( void* a_pObject ) const
{
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(; it != end; ++it)
    {
        it->m_pClass->construct(a_pObject);
    }
    *reinterpret_cast<Class**>(reinterpret_cast<byte*>(a_pObject)+getClassPtrOffset()) = const_cast<RuntimeClass*>(this);
    size_t i = 0;
    Type::aligner aligner(reinterpret_cast<byte*>(a_pObject)+m_uiMemoryOffset);
    for(;i<m_uiDataTypeCount;++i)
    {
        aligner.construct(m_pDataTypes[i]);
    }
}

void RuntimeClass::construct( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(; it != end; ++it)
    {
        it->m_pClass->construct(a_pChunk, a_uiCount, a_uiChunkSectionSize);
    }
    byte*    chunk_address = reinterpret_cast<byte*>(a_pChunk);
    while(a_uiCount--)
    {
        *reinterpret_cast<Class**>(chunk_address+getClassPtrOffset()) = const_cast<RuntimeClass*>(this);
        size_t i = 0;
        Type::aligner aligner(chunk_address+m_uiMemoryOffset);
        for(;i<m_uiDataTypeCount;++i)
        {
            aligner.construct(m_pDataTypes[i]);
        }
        chunk_address += a_uiChunkSectionSize;
    }
}

void RuntimeClass::destroy( void* a_pObject ) const
{
    size_t i = 0;
    Type::aligner aligner(reinterpret_cast<byte*>(a_pObject)+m_uiMemoryOffset);
    for(;i<m_uiDataTypeCount;++i)
    {
        aligner.destroy(m_pDataTypes[i]);
    }
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(; it != end; ++it)
    {
        it->m_pClass->destroy(a_pObject);
    }
}

void RuntimeClass::destroy( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    byte*    chunk_address = reinterpret_cast<byte*>(a_pChunk);
    while(a_uiCount--)
    {
        size_t i = 0;
        Type::aligner aligner(chunk_address+m_uiMemoryOffset);
        for(;i<m_uiDataTypeCount;++i)
        {
            aligner.destroy(m_pDataTypes[i]);
        }
        chunk_address += a_uiChunkSectionSize;
    }
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(; it != end; ++it)
    {
        it->m_pClass->destroy(a_pChunk, a_uiCount, a_uiChunkSectionSize);
    }
}

Type* RuntimeClass::createConstType() const
{
    o_warning(false, "RuntimeClass const version has not been implemented");
    return const_cast<RuntimeClass*>(this);//o_new(native::TConstType<RuntimeClass>)();
}

o_cpp_end
