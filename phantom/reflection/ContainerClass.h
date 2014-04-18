#ifndef ContainerClass_h__
#define ContainerClass_h__


/* ****************** Includes ******************* */


/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export ContainerClass : public Class
{
    o_declare_meta_type(ContainerClass);

public:
    ContainerClass(Type* a_pValueType, const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_Modifiers = 0)
        : Class(a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
        , m_pValueType(a_pValueType) 
    {
    }

    virtual size_t     count(void const* a_pContainer) const = 0;
    virtual void       erase(void* a_pContainer, Iterator* first, Iterator* last) const = 0;
    virtual void       erase(void* a_pContainer, void* first, void* last) const = 0;
    virtual void       erase(void* a_pContainer, Iterator* it) const = 0;
    virtual size_t     replaceAll(void* a_pContainer, const void* a_pOld, const void* a_pNew) const = 0;
    virtual size_t     eraseAll(void* a_pContainer, const void* a_pOld) const = 0;

    Type*              getKeyType() const { return m_pValueType; }
    Type*              getValueType() const { return m_pValueType; }

    virtual ContainerClass* asContainerClass() const { return const_cast<ContainerClass*>(this); }

    virtual bool       isMapClass() const { return false; }
    virtual bool       isUnorderedMapClass() const { return false; }
    virtual bool       isMultimapClass() const { return false; }
    virtual bool       isSetClass() const { return false; }
    virtual bool       isUnorderedSetClass() const { return false; }
    virtual bool       isMultisetClass() const { return false; }
    virtual bool       isListClass() const { return false; }
    virtual bool       isVectorClass() const { return false; }
    virtual bool       isDequeClass() const { return false; }
    virtual bool       isStackClass() const { return false; }

    virtual Iterator*  begin(void* a_pContainer) const = 0;
    virtual ConstIterator*  begin(const void* a_pContainer) const = 0;
    virtual void       release(Iterator* a_pIterator) const { a_pIterator->deleteNow(); }
    virtual void       release(ConstIterator* a_pIterator) const { a_pIterator->deleteNow(); }

    virtual bool       referencesData(const void* a_pContainer, const phantom::data& a_Data) const;

protected:
    Type*   m_pValueType;
};

o_namespace_end(phantom, reflection)


#endif
