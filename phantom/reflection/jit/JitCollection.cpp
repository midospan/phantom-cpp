/* ******************* Includes ****************** */
#include "phantom/jit.h"
#include "JitCollection.h"
#include "JitCollection.hxx"
#include "phantom/def_jit_internal.h"
#include "JitClass.h"
#include "JitSignal.h"
#include "JitInstanceMemberFunction.h"
/* *********************************************** */
o_registerN((phantom, reflection, jit), JitCollection);

o_namespace_begin(phantom, reflection, jit)

    JitCollection:: JitCollection(const string& a_strName
    , Type* a_pElementType
    , JitInstanceMemberFunction* a_pAdder
    , JitInstanceMemberFunction* a_pRemover
    , JitInstanceMemberFunction* a_pMover
    , JitInstanceMemberFunction* a_pSetter
    , JitInstanceMemberFunction* a_pGetter
    , JitInstanceMemberFunction* a_pSizeGetter
    , bitfield a_Modifiers)
    : Collection(a_strName, a_pElementType, a_Modifiers) 
    , m_pAdder(a_pAdder)
    , m_pRemover(a_pRemover)
    , m_pSetter(a_pSetter)
    , m_pMover(a_pMover)
    , m_pGetter(a_pGetter)
    , m_pSizeGetter(a_pSizeGetter)
{
}

JitCollection::~JitCollection( void )
{
}

void JitCollection::addElement( void* a_pObject, const void* src ) const
{
    if(getElementType()->asReferenceType())
    {
        void* args[2] = { &a_pObject, (void*)&src };                   
        jit_function_apply((jit_function_t)m_pAdder->getJitGenericCallFunction().function, args, nullptr);
    }
    else
    {
        void* args[2] = { &a_pObject, (void*)src };
        jit_function_apply((jit_function_t)m_pAdder->getJitGenericCallFunction().function, args, nullptr);
    }
}

void JitCollection::setElement( void* a_pObject, size_t index, const void* src ) const
{
    if(getElementType()->asReferenceType())
    {
        void* args[3] = { &a_pObject, &index, (void*)&src };                   
        jit_function_apply((jit_function_t)m_pSetter->getJitGenericCallFunction().function, args, nullptr);
    }
    else
    {
        void* args[3] = { &a_pObject, &index, (void*)src };
        jit_function_apply((jit_function_t)m_pSetter->getJitGenericCallFunction().function, args, nullptr);
    }
}

void JitCollection::moveElement( void* a_pObject, const void* src, size_t index ) const
{
    if(getElementType()->asReferenceType())
    {
        void* args[3] = { &a_pObject, (void*)&src, &index };                   
        jit_function_apply((jit_function_t)m_pMover->getJitGenericCallFunction().function, args, nullptr);
    }
    else
    {
        void* args[3] = { &a_pObject, (void*)src, &index };
        jit_function_apply((jit_function_t)m_pMover->getJitGenericCallFunction().function, args, nullptr);
    }
}

void JitCollection::removeElement( void* a_pObject, const void* src ) const
{
    if(getElementType()->asReferenceType())
    {
        void* args[2] = { &a_pObject, (void*)&src };                   
        jit_function_apply((jit_function_t)m_pRemover->getJitGenericCallFunction().function, args, nullptr);
    }
    else
    {
        void* args[2] = { &a_pObject, (void*)src };
        jit_function_apply((jit_function_t)m_pRemover->getJitGenericCallFunction().function, args, nullptr);
    }
}

void JitCollection::getElement( void const* a_pObject, size_t a_uiIndex, void* dest ) const
{
    if(getElementType()->asReferenceType())
    {
        void* args[2] = { &a_pObject, &a_uiIndex };                   
        jit_function_apply((jit_function_t)m_pGetter->getJitGenericCallFunction().function, args, &dest);
    }
    else
    {
        void* args[2] = { &a_pObject, &a_uiIndex };
        jit_function_apply((jit_function_t)m_pGetter->getJitGenericCallFunction().function, args, dest);
    }
}

size_t JitCollection::getSize( void const* a_pObject ) const
{
    size_t result = 0;
    if(getElementType()->asReferenceType())
    {
        void* args[1] = { &a_pObject };                   
        jit_function_apply((jit_function_t)m_pSizeGetter->getJitGenericCallFunction().function, args, &result);
    }
    else
    {
        void* args[1] = { &a_pObject };
        jit_function_apply((jit_function_t)m_pSizeGetter->getJitGenericCallFunction().function, args, &result);
    }
    return result;
}


o_namespace_end(phantom, reflection, jit)
