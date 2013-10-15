#ifndef ContainerClass_h__
#define ContainerClass_h__


/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "ContainerClass.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_h_begin

class ContainerClass : public Class
{
    reflection_____________________________________________________________________
    _____________________________________________________________________reflection

public:
    ContainerClass(Type* a_pValueType, const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_bfModifiers = bitfield())
        : Class(a_strName, a_uiSize, a_uiAlignment, a_bfModifiers)
        , m_pValueType(a_pValueType) 
    {
    }

    virtual size_t     getCount(void const* a_pContainer) const = 0;
    virtual void       createIteratorVariables(void* a_pContainer, vector<IteratorVariable*>& out) const = 0;
    virtual void       erase(void* a_pContainer, IteratorVariable* first, IteratorVariable* last) const = 0;
    virtual void       erase(void* a_pContainer, void* first, void* last) const = 0;
    virtual void       erase(void* a_pContainer, IteratorVariable* it) const = 0;
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

    virtual IteratorVariable*       begin(void* a_pContainer) const=0;
    virtual IteratorConstant*       begin(void const* a_pContainer) const=0;

    virtual bool        isEndIterator(void* a_pContainer, IteratorVariable* a_pIterator) const = 0;
    virtual bool        isEndIterator(void const* a_pContainer, IteratorConstant* a_pIterator) const = 0;

protected:
    Type*   m_pValueType;
};

o_h_end

#else
#include "ContainerClass.classdef.h"
#endif
