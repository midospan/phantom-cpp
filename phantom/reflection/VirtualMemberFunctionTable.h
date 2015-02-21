/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_VirtualMemberFunctionTable_h__
#define o_phantom_reflection_VirtualMemberFunctionTable_h__



/* ****************** Includes ******************* */


/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export VirtualMemberFunctionTable : public NamedElement
{
    o_declare_meta_type(VirtualMemberFunctionTable);

    friend class Class;

public:
    VirtualMemberFunctionTable();
    VirtualMemberFunctionTable(size_t a_uiSize);
    VirtualMemberFunctionTable(void** a_ppClosures, size_t a_uiSize);
    o_destructor ~VirtualMemberFunctionTable(void);

    size_t getMemberFunctionCount() const { return m_pMemberFunctions->size(); }
    
    size_t getIndexOf(MemberFunction* a_pMemberFunction) const;

    vector<MemberFunction*>::const_iterator beginMemberFunctions() const { return m_pMemberFunctions->begin(); }
    vector<MemberFunction*>::const_iterator endMemberFunctions() const { return m_pMemberFunctions->end(); }

    MemberFunction*     getMemberFunction(size_t a_uiIndex) const 
    {
        return (*m_pMemberFunctions)[a_uiIndex];
    }

    Class*                      getOwnerClass() const { return m_pOwner ? m_pOwner->asClass() : nullptr; }

    Class*                      getSourceClass() const 
    { 
        return m_pBaseTable == nullptr ? getOwnerClass() : m_pBaseTable->getSourceClass(); 
    }

    size_t                      getOffset() const;

    VirtualMemberFunctionTable* derive(size_t a_uiSize = 0) const;

    void                        construct(void* a_pInstance);

    VirtualMemberFunctionTable* getRootTable() const { return m_pBaseTable ? m_pBaseTable->getRootTable() : const_cast<VirtualMemberFunctionTable*>(this); }

    MemberFunction*     getRootMemberFunction(size_t a_uiIndex) const;
    MemberFunction*     getRootMemberFunction( MemberFunction* a_pMemberFunction ) const;

    VirtualMemberFunctionTable* asVirtualMemberFunctionTable() const { return const_cast<VirtualMemberFunctionTable*>(this); }

private: // Derivation constructors
    VirtualMemberFunctionTable(VirtualMemberFunctionTable* a_pBaseTable);
    VirtualMemberFunctionTable(VirtualMemberFunctionTable* a_pBaseTable, size_t a_uiSize);

private:
    void                        addMemberFunction(MemberFunction* a_pMemberFunction);

    void                        setMemberFunction(size_t a_uiIndex, MemberFunction* a_pMemberFunction);

    void                        insertMemberFunction(MemberFunction* a_pMemberFunction);

    bool                        sharesMemberFunctions() const { return m_pBaseTable && m_pBaseTable->m_pMemberFunctions == m_pMemberFunctions; }

    void                        copyOnWrite();

    virtual bool                canBeDestroyed() const;

private:
    vector<MemberFunction*>* m_pMemberFunctions;
    VirtualMemberFunctionTable* m_pBaseTable;
    vector<VirtualMemberFunctionTable*> m_DerivedTables;
    void**                      m_ppClosures;
    bool                        m_bClosuresExtracted;
    
};

o_namespace_end(phantom, reflection)



#endif
