#ifndef o_phantom_reflection_IteratorVariable_h__
#define o_phantom_reflection_IteratorVariable_h__


/* ****************** Includes ******************* */

/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "IteratorVariable.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_h_begin

class o_export IteratorVariable : public Variable, public util::Iterator
{
    reflection_____________________________________________________________________
    _____________________________________________________________________reflection

public:
    IteratorVariable(void* a_pContainer, ContainerClass* a_pContainerClass) 
        : m_pContainer(a_pContainer) 
        , m_pContainerClass(a_pContainerClass) 
    {

    }
    IteratorVariable(void* a_pContainer, ContainerClass* a_pContainerClass, const string& a_strName, bitfield a_modifiers = 0)
        : Variable(a_strName, a_modifiers)
        , m_pContainer(a_pContainer) 
        , m_pContainerClass(a_pContainerClass) 
    {

    }

    virtual boolean hasNext() const;
    void*           getContainer() const { return m_pContainer; }
    ContainerClass* getContainerClass() const { return m_pContainerClass; }

protected:
    void*           m_pContainer;
    ContainerClass* m_pContainerClass;
};

o_h_end

#else
#include "IteratorVariable.classdef.h"
#endif // o_phantom_reflection_IteratorVariable_h__
