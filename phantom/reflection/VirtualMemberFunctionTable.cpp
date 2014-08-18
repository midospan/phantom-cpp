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
#include <phantom/reflection/VirtualMemberFunctionTable.h>
#include <phantom/reflection/VirtualMemberFunctionTable.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), VirtualMemberFunctionTable);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(VirtualMemberFunctionTable);  

VirtualMemberFunctionTable::VirtualMemberFunctionTable() 
    : m_pSuperTable(NULL)
    , m_pMemberFunctions(new vector<InstanceMemberFunction*>)
    , m_ppClosures(nullptr)
    , m_bClosuresExtracted(false)
{

}
VirtualMemberFunctionTable::VirtualMemberFunctionTable(size_t a_uiSize) 
    : m_pSuperTable(NULL)
    , m_pMemberFunctions(new vector<InstanceMemberFunction*>(a_uiSize))
    , m_ppClosures(nullptr)
    , m_bClosuresExtracted(false)
{

}

VirtualMemberFunctionTable::VirtualMemberFunctionTable( VirtualMemberFunctionTable* a_pSuperTable )
    : m_pSuperTable(a_pSuperTable)
    , m_pMemberFunctions(a_pSuperTable->m_pMemberFunctions)
    , m_ppClosures(nullptr)
    , m_bClosuresExtracted(false)
{

}

VirtualMemberFunctionTable::VirtualMemberFunctionTable( VirtualMemberFunctionTable* a_pSuperTable, size_t a_uiSize )
    : m_pSuperTable(a_pSuperTable)
    , m_pMemberFunctions(new vector<InstanceMemberFunction*>(a_uiSize))
    , m_ppClosures(nullptr)
    , m_bClosuresExtracted(false)
{
    for(size_t i = 0; i<a_pSuperTable->m_pMemberFunctions->size(); ++i)
    {
        (*m_pMemberFunctions)[i] = (*(a_pSuperTable->m_pMemberFunctions))[i];
    }
}

size_t VirtualMemberFunctionTable::getIndexOf( InstanceMemberFunction* a_pMemberFunction ) const
{
    size_t i = 0;
    for(;i<m_pMemberFunctions->size(); ++i )
    {
        if((*m_pMemberFunctions)[i] == a_pMemberFunction) return i;
    }
    return ~size_t(0);
}

o_destructor VirtualMemberFunctionTable::~VirtualMemberFunctionTable( void )
{
    if(NOT(sharesMemberFunctions()))
        delete m_pMemberFunctions;
    if(m_ppClosures)
        o_free(m_ppClosures);
}

VirtualMemberFunctionTable* VirtualMemberFunctionTable::derive(size_t a_uiSize  /*= 0*/) const
{
    if(a_uiSize == 0 OR a_uiSize == m_pMemberFunctions->size())
    {
        return o_new(VirtualMemberFunctionTable)(const_cast<VirtualMemberFunctionTable*>(this));
    }
    o_assert(a_uiSize > m_pMemberFunctions->size());
    return o_new(VirtualMemberFunctionTable)(const_cast<VirtualMemberFunctionTable*>(this), a_uiSize);
}

size_t VirtualMemberFunctionTable::getOffset() const
{
    if(m_pOwner == nullptr) return ~size_t(0);
    return m_pSuperTable 
        ? getOwnerClass()->getSuperClassOffset(m_pSuperTable->getOwnerClass())
        : 0;
}

void VirtualMemberFunctionTable::addMemberFunction( InstanceMemberFunction* a_pMemberFunction )
{
    a_pMemberFunction->setVirtualTableIndex(getMemberFunctionCount());
    setMemberFunction(getMemberFunctionCount(), a_pMemberFunction);
}

void VirtualMemberFunctionTable::setMemberFunction( size_t a_uiIndex, InstanceMemberFunction* a_pMemberFunction )
{
    o_assert(a_pMemberFunction->getVirtualTableIndex() == a_uiIndex);
    if(sharesMemberFunctions())
        copyOnWrite();
    m_pMemberFunctions->resize(std::max(a_uiIndex+1, getMemberFunctionCount()));
    (*m_pMemberFunctions)[a_uiIndex] = a_pMemberFunction;
}

void VirtualMemberFunctionTable::insertMemberFunction( InstanceMemberFunction* a_pMemberFunction )
{
    for(auto it = m_pMemberFunctions->begin(); it != m_pMemberFunctions->end(); ++it)
    {
        if(*it)
        {
            if(a_pMemberFunction->canOverride(*it))
            {
                a_pMemberFunction->setVirtual(); // Set virtual if not (indeed, even if not explicitely virtual, a member function which overrides a virtual becomes virtual 
                *it = a_pMemberFunction; // replace super class member function by this one (overrides entry)
                return;
            }
        }
    }
    // We did not find any overrides 
    if(getOffset() == 0 // and it's the main vtable 
        AND a_pMemberFunction->isVirtual()) // and the member function is virtual 
    {
        // => insert it 
        size_t uiIndex = a_pMemberFunction->getVirtualTableIndex();
        if(uiIndex == ~size_t(0))
        {
            // to a new index
            addMemberFunction(a_pMemberFunction);
        }
        else 
        {
            // to an index given by the function itself
            setMemberFunction(uiIndex, a_pMemberFunction);
        }
    }
}

void VirtualMemberFunctionTable::construct( void* a_pInstance )
{
    if(sharesMemberFunctions())
    {
        m_pSuperTable->construct(a_pInstance);
        return; 
    }
    void*** pppWhere = (void***)((byte*)a_pInstance + getOffset());
    size_t count = getMemberFunctionCount();
    if(m_ppClosures == nullptr)
    {
        if(m_pSuperTable) 
        {
            size_t size = std::max(count, m_pSuperTable->getMemberFunctionCount());
            m_ppClosures = (void**)o_malloc(size * sizeof(void*));
        }
        else 
        {
            m_ppClosures = (void**)o_malloc(count * sizeof(void*));
        }
        void* non_init_ptr;
        memset(&non_init_ptr, 0xda, sizeof(void*));
        if(memcmp(pppWhere, &non_init_ptr, sizeof(void*)) != 0) // memory not equals 0xdadadada => closures already present => a super vtable has been installed here
        {
            memcpy(m_ppClosures, *pppWhere, count*sizeof(void*)); // extract native vtable closures
        }
        for(size_t i = 0; i<count; ++i)
        {
            if((*m_pMemberFunctions)[i])
            {
                m_ppClosures[i] = (*m_pMemberFunctions)[i]->getVTableClosure(getOffset()); // write (resp. overwrite) closures (resp. super closures)
                o_assert(m_ppClosures[i], "No vtable closure found for given vtable offset, ensure your compiler has provided all the closures for each possible multi-inheritance this adjustment (thunk)");
            }
        }
        *pppWhere = m_ppClosures; // write (resp. overwrite) vtable pointer (resp. super vtable pointer)
    }
}

InstanceMemberFunction* VirtualMemberFunctionTable::getRootMemberFunction( size_t a_uiIndex ) const
{
    if(a_uiIndex >= m_pMemberFunctions->size()) 
        return nullptr;
    if(m_pSuperTable)
    {
        InstanceMemberFunction* pSuper = m_pSuperTable->getRootMemberFunction(a_uiIndex);
        if(pSuper) return pSuper;
    }
    return (*m_pMemberFunctions)[a_uiIndex];
}

InstanceMemberFunction* VirtualMemberFunctionTable::getRootMemberFunction( InstanceMemberFunction* a_pInstanceMemberFunction ) const
{
    if(getOwnerClass() != a_pInstanceMemberFunction->getOwnerClass()) 
        return m_pSuperTable 
                ? m_pSuperTable->getRootMemberFunction(a_pInstanceMemberFunction) 
                : nullptr;
    for(size_t i = 0; i<m_pMemberFunctions->size(); ++i)
    {
        if((*m_pMemberFunctions)[i] == a_pInstanceMemberFunction)
            return getRootMemberFunction(i);
    }
    return nullptr;
}

o_namespace_end(phantom, reflection)