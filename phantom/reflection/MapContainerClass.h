#ifndef MapContainerClass_h__
#define MapContainerClass_h__


/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "MapContainerClass.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_h_begin


class MapContainerClass : public ContainerClass
{
    reflection_____________________________________________________________________
    _____________________________________________________________________reflection

public:
    MapContainerClass(Type* a_pKeyType, Type* a_pMappedType, Type* a_pValueType, const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_Modifiers = 0)
    : ContainerClass(a_pValueType, a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
    , m_pKeyType(a_pKeyType) 
    , m_pMappedType(a_pMappedType) 
    {
    }

    Type*   getKeyType() const { return m_pKeyType; }
    Type*   getMappedType() const { return m_pMappedType; }
    
    virtual void insertPair(void* a_pContainer, void const* a_pKey, void* a_pValue ) const = 0;
    virtual void insertKey(void* a_pContainer, void const* a_pKey) const = 0;
    virtual void eraseKey(void* a_pContainer, void const* a_pKey) const = 0;
    virtual bool containsKey(void const* a_pContainer, void const* a_pKey) const = 0;
    virtual void getValue(void const* a_pContainer, void* a_pDest, void const* a_pKey) const = 0;

protected:
    Type* m_pKeyType;
    Type* m_pMappedType;
};

o_h_end


#else
#include "MapContainerClass.classdef.h"
#endif
