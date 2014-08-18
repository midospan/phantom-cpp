#ifndef MapContainerClass_h__
#define MapContainerClass_h__


/* ****************** Includes ******************* */


/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), MapIterator);
o_declareN(class, (phantom, reflection), MapConstIterator);
o_declareN(class, (phantom, reflection), MapContainerClass);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class MapIterator : public Iterator
{
    o_declare_meta_type(MapIterator);
public:
    virtual void getKeyValue(void* a_pDest) const = 0;
    virtual void getMappedValue(void* a_pDest) const = 0;
    virtual void setMappedValue(const void* a_pDest) const = 0;
    virtual const void* keyPointer() const = 0;
    virtual void* mappedPointer() const = 0;
    virtual void setValue(const void* a_pSrc) const
    {
        o_exception(exception::reflection_runtime_exception, "Use setMappedValue to set the mapped value, the key-value pair is read only to keep map coherency");
    }

};

class MapConstIterator : public ConstIterator
{
    o_declare_meta_type(MapConstIterator);
public:
    virtual void getKeyValue(void* a_pDest) const = 0;
    virtual void getMappedValue(void* a_pDest) const = 0;

    virtual const void* keyPointer() const = 0;
    virtual const void* mappedPointer() const = 0;

};

class o_export MapContainerClass : public ContainerClass
{
    o_declare_meta_type(MapContainerClass);

public:
    MapContainerClass(Type* a_pKeyType, Type* a_pMappedType, Type* a_pValueType, const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_Modifiers = 0)
        : ContainerClass(a_pValueType, a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
        , m_pKeyType(a_pKeyType) 
        , m_pMappedType(a_pMappedType) 
    {
    }

    virtual Type*getKeyType() const { return m_pKeyType; }
    virtual Type*getMappedType() const { return m_pMappedType; }
    
    virtual void insertPair(void* a_pContainer, void const* a_pKey, void* a_pValue ) const = 0;
    virtual void insertKey(void* a_pContainer, void const* a_pKey) const = 0;
    virtual void eraseKey(void* a_pContainer, void const* a_pKey) const = 0;
    virtual bool containsKey(void const* a_pContainer, void const* a_pKey) const = 0;
    virtual void getValue(void const* a_pContainer, void* a_pDest, void const* a_pKey) const = 0;

    virtual MapIterator*        begin(void* a_pContainer) const = 0;
    virtual MapConstIterator*   begin(const void* a_pContainer) const = 0;

protected:
    Type* m_pKeyType;
    Type* m_pMappedType;
};

o_namespace_end(phantom, reflection)



#endif
