#ifndef o_phantom_reflection_SetContainerClass_h__
#define o_phantom_reflection_SetContainerClass_h__


/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "SetContainerClass.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_h_begin

class SetContainerClass : public ContainerClass
{
    reflection_____________________________________________________________________
    _____________________________________________________________________reflection

public:
    SetContainerClass(Type* a_pValueType, const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_Modifiers = 0)
    : ContainerClass(a_pValueType, a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
    {
    }

    Type*   getKeyType() const { return m_pValueType; }
    
    virtual void insertKey(void* a_pContainer, void const* a_pKey) const = 0;
    virtual void eraseKey(void* a_pContainer, void const* a_pKey) const = 0;
    virtual bool containsKey(void const* a_pContainer, void const* a_pKey) const = 0;
    virtual void getValue(void const* a_pContainer, void* a_pDest, void const* a_pKey) const = 0;

protected:
};

o_h_end

#else
#include "SetContainerClass.classdef.h"
#endif
