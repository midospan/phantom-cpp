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

#ifndef o_phantom_reflection_VirtualMemberFunctionTable_h__
#define o_phantom_reflection_VirtualMemberFunctionTable_h__



/* ****************** Includes ******************* */


/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export VirtualMemberFunctionTable : public LanguageElement
{
    o_declare_meta_type(VirtualMemberFunctionTable);

    friend class Class;

public:
    VirtualMemberFunctionTable();
    VirtualMemberFunctionTable(size_t a_uiSize);
    o_destructor ~VirtualMemberFunctionTable(void);

    size_t getMemberFunctionCount() const { return m_pMemberFunctions->size(); }
    
    size_t getIndexOf(InstanceMemberFunction* a_pMemberFunction) const;

    vector<InstanceMemberFunction*>::const_iterator beginMemberFunctions() const { return m_pMemberFunctions->begin(); }
    vector<InstanceMemberFunction*>::const_iterator endMemberFunctions() const { return m_pMemberFunctions->end(); }

    InstanceMemberFunction*     getMemberFunction(size_t a_uiIndex) const 
    {
        return (*m_pMemberFunctions)[a_uiIndex];
    }

    Class*                      getOwnerClass() const { return m_pOwner ? m_pOwner->asClass() : nullptr; }

    Class*                      getSourceClass() const 
    { 
        return m_pSuperTable == nullptr ? getOwnerClass() : m_pSuperTable->getSourceClass(); 
    }

    size_t                      getOffset() const;

    VirtualMemberFunctionTable* derive(size_t a_uiSize = 0) const;

    void                        construct(void* a_pInstance);

    VirtualMemberFunctionTable* getRootTable() const { return m_pSuperTable ? m_pSuperTable->getRootTable() : const_cast<VirtualMemberFunctionTable*>(this); }

    InstanceMemberFunction*     getRootMemberFunction(size_t a_uiIndex) const;
    InstanceMemberFunction*     getRootMemberFunction( InstanceMemberFunction* a_pInstanceMemberFunction ) const;

    VirtualMemberFunctionTable* asVirtualMemberFunctionTable() const { return const_cast<VirtualMemberFunctionTable*>(this); }

private: // Derivation constructors
    VirtualMemberFunctionTable(VirtualMemberFunctionTable* a_pSuperTable);
    VirtualMemberFunctionTable(VirtualMemberFunctionTable* a_pSuperTable, size_t a_uiSize);

private:
    void                        addMemberFunction(InstanceMemberFunction* a_pMemberFunction);

    void                        setMemberFunction(size_t a_uiIndex, InstanceMemberFunction* a_pMemberFunction);

    void                        insertMemberFunction(InstanceMemberFunction* a_pMemberFunction);

    bool                        sharesMemberFunctions() const { return m_pSuperTable && m_pSuperTable->m_pMemberFunctions == m_pMemberFunctions; }

    void                        copyOnWrite()
    {
        o_assert(sharesMemberFunctions());
        m_pMemberFunctions = new vector<InstanceMemberFunction*>;
        *m_pMemberFunctions = *(m_pSuperTable->m_pMemberFunctions);
    }

private:
    vector<InstanceMemberFunction*>* m_pMemberFunctions;
    VirtualMemberFunctionTable* m_pSuperTable;
    void**                      m_ppClosures;
    bool                        m_bClosuresExtracted;
    
};

o_namespace_end(phantom, reflection)



#endif
