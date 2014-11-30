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
    : m_pBaseTable(NULL)
    , m_pMemberFunctions(new vector<InstanceMemberFunction*>)
    , m_ppClosures(nullptr)
    , m_bClosuresExtracted(false)
{

}
VirtualMemberFunctionTable::VirtualMemberFunctionTable(size_t a_uiSize) 
    : m_pBaseTable(NULL)
    , m_pMemberFunctions(new vector<InstanceMemberFunction*>(a_uiSize))
    , m_ppClosures(nullptr)
    , m_bClosuresExtracted(false)
{

}

VirtualMemberFunctionTable::VirtualMemberFunctionTable( VirtualMemberFunctionTable* a_pBaseTable )
    : m_pBaseTable(a_pBaseTable)
    , m_pMemberFunctions(a_pBaseTable->m_pMemberFunctions)
    , m_ppClosures(nullptr)
    , m_bClosuresExtracted(false)
{
    m_pBaseTable->m_DerivedTables.push_back(this);
}

VirtualMemberFunctionTable::VirtualMemberFunctionTable( VirtualMemberFunctionTable* a_pBaseTable, size_t a_uiSize )
    : m_pBaseTable(a_pBaseTable)
    , m_pMemberFunctions(new vector<InstanceMemberFunction*>(a_uiSize))
    , m_ppClosures(nullptr)
    , m_bClosuresExtracted(false)
{
    m_pBaseTable->m_DerivedTables.push_back(this);
    for(size_t i = 0; i<a_pBaseTable->m_pMemberFunctions->size(); ++i)
    {
        (*m_pMemberFunctions)[i] = (*(a_pBaseTable->m_pMemberFunctions))[i];
    }
}

o_destructor VirtualMemberFunctionTable::~VirtualMemberFunctionTable( void )
{
    if(m_pBaseTable)
        m_pBaseTable->m_DerivedTables.erase(std::find(m_pBaseTable->m_DerivedTables.begin(), m_pBaseTable->m_DerivedTables.end(), this));
    if(NOT(sharesMemberFunctions()))
        delete m_pMemberFunctions;
    if(m_ppClosures)
        o_free(m_ppClosures);
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
    return m_pBaseTable 
        ? getOwnerClass()->getBaseClassOffset(m_pBaseTable->getOwnerClass())
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
                *it = a_pMemberFunction; // replace base class member function by this one (overrides entry)
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
        m_pBaseTable->construct(a_pInstance);
        return; 
    }
    void*** pppWhere = (void***)((byte*)a_pInstance + getOffset());
    size_t count = getMemberFunctionCount();
    if(m_ppClosures == nullptr)
    {
        if(m_pBaseTable) 
        {
            size_t size = std::max(count, m_pBaseTable->getMemberFunctionCount());
            m_ppClosures = (void**)o_malloc(size * sizeof(void*));
        }
        else 
        {
            m_ppClosures = (void**)o_malloc(count * sizeof(void*));
        }
        void* non_init_ptr;
        memset(&non_init_ptr, 0xda, sizeof(void*));
        if(memcmp(pppWhere, &non_init_ptr, sizeof(void*)) != 0) // memory not equals 0xdadadada => closures already present => a base vtable has been installed here
        {
            memcpy(m_ppClosures, *pppWhere, count*sizeof(void*)); // extract native vtable closures
        }
        for(size_t i = 0; i<count; ++i)
        {
            if((*m_pMemberFunctions)[i])
            {
                void* pVTableClosure = (*m_pMemberFunctions)[i]->getVTableClosure(getOffset());
                if(pVTableClosure)
                {
                    m_ppClosures[i] = pVTableClosure; // write (resp. overwrite) closures (resp. base closures)
                }
                // o_assert(m_ppClosures[i], "No vtable closure found for given vtable offset, ensure your compiler has provided all the closures for each possible multi-inheritance this adjustment (thunk)");
            }
        }
        *pppWhere = m_ppClosures; // write (resp. overwrite) vtable pointer (resp. base vtable pointer)
    }
}

InstanceMemberFunction* VirtualMemberFunctionTable::getRootMemberFunction( size_t a_uiIndex ) const
{
    if(a_uiIndex >= m_pMemberFunctions->size()) 
        return nullptr;
    if(m_pBaseTable)
    {
        InstanceMemberFunction* pBase = m_pBaseTable->getRootMemberFunction(a_uiIndex);
        if(pBase) return pBase;
    }
    return (*m_pMemberFunctions)[a_uiIndex];
}

InstanceMemberFunction* VirtualMemberFunctionTable::getRootMemberFunction( InstanceMemberFunction* a_pInstanceMemberFunction ) const
{
    if(getOwnerClass() != a_pInstanceMemberFunction->getOwnerClass()) 
        return m_pBaseTable 
                ? m_pBaseTable->getRootMemberFunction(a_pInstanceMemberFunction) 
                : nullptr;
    for(size_t i = 0; i<m_pMemberFunctions->size(); ++i)
    {
        if((*m_pMemberFunctions)[i] == a_pInstanceMemberFunction)
            return getRootMemberFunction(i);
    }
    return nullptr;
}

bool VirtualMemberFunctionTable::canBeDestroyed() const
{
    return LanguageElement::canBeDestroyed() AND m_DerivedTables.empty();
}

void VirtualMemberFunctionTable::copyOnWrite()
{
    o_assert(sharesMemberFunctions());
    m_pMemberFunctions = new vector<InstanceMemberFunction*>;
    *m_pMemberFunctions = *(m_pBaseTable->m_pMemberFunctions);
}

o_namespace_end(phantom, reflection)