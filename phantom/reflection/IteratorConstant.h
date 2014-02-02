#ifndef o_phantom_reflection_IteratorConstant_h__
#define o_phantom_reflection_IteratorConstant_h__


/* ****************** Includes ******************* */
#include "phantom/util/Iterator.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export IteratorConstant : public Constant, public Iterator
{
public:
    IteratorConstant(void const* a_pContainer, ContainerClass* a_pContainerClass) 
        : m_pContainer(a_pContainer) 
        , m_pContainerClass(a_pContainerClass) 
    {

    }
    IteratorConstant(void const* a_pContainer, ContainerClass* a_pContainerClass, const string& a_strName, bitfield a_modifiers = 0)
        : Constant(a_strName, a_modifiers)
        , m_pContainer(a_pContainer) 
        , m_pContainerClass(a_pContainerClass) 
    {

    }

    virtual boolean     hasNext() const;
    const void*         getContainer() const { return m_pContainer; }
    ContainerClass*     getContainerClass() const { return m_pContainerClass; }

protected:
    const void*     m_pContainer;
    ContainerClass* m_pContainerClass;
};

o_namespace_end(phantom, reflection)


#endif // o_phantom_reflection_IteratorConstant_h__
