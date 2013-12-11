#ifndef SequentialContainerClass_h__
#define SequentialContainerClass_h__


/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "SequentialContainerClass.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_h_begin

class SequentialContainerClass : public ContainerClass
{
    reflection_____________________________________________________________________
    _____________________________________________________________________reflection

public:
    SequentialContainerClass(Type* a_pValueType
        , const string& a_strName
        , ushort a_uiSize
        , ushort a_uiAlignment
        , bitfield a_Modifiers = 0) 
    : ContainerClass(a_pValueType, a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
    {

    }

    virtual void append(void* a_pContainer, void const* a_pValue) const = 0;

};

o_h_end

#else
#include "SequentialContainerClass.classdef.h"
#endif
