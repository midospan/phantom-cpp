/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "JitCollection.h"
#include "JitClass.h"
#include "JitSignal.h"
#include "JitInstanceMethod.h"
/* *********************************************** */
o_registerN((phantom, reflection, runtime), JitCollection);

o_namespace_begin(phantom, reflection, runtime)

    JitCollection:: JitCollection(const string& a_strName
    , Type* a_pElementType
    , JitInstanceMethod* a_pAdder
    , JitInstanceMethod* a_pRemover
    , JitInstanceMethod* a_pMover
    , JitInstanceMethod* a_pSetter
    , JitInstanceMethod* a_pGetter
    , JitInstanceMethod* a_pSizeGetter
    , bitfield a_Modifiers)
    : Collection(a_strName, a_pElementType, a_Modifiers) 
    , m_pAdder(a_pAdder)
    , m_pRemover(a_pRemover)
    , m_pSetter(a_pSetter)
    , m_pMover(a_pMover)
    , m_pGetter(a_pGetter)
    , m_pSizeGetter(a_pSizeGetter)
    , m_add_jit_function(0)
    , m_remove_jit_function(0)
    , m_move_jit_function(0)
    , m_set_jit_function(0)
    , m_get_jit_function(0)
    , m_size_jit_function(0)
{
    m_add_jit_function = m_pAdder->getJitGenericCallFunction();
    m_remove_jit_function = m_pRemover->getJitGenericCallFunction();
    m_move_jit_function = m_pMover->getJitGenericCallFunction();
    m_set_jit_function = m_pSetter->getJitGenericCallFunction();
    m_get_jit_function = m_pGetter->getJitGenericCallFunction();
    m_size_jit_function = m_pSizeGetter->getJitGenericCallFunction();
}

JitCollection::~JitCollection( void )
{
}

void JitCollection::addElement( void* a_pObject, const void* src ) const
{
    if(getElementType()->isReferenceType())
    {
        void* args[2] = { &a_pObject, (void*)&src };                   
        jit_function_apply(m_add_jit_function, args, nullptr);
    }
    else
    {
        void* args[2] = { &a_pObject, (void*)src };
        jit_function_apply(m_add_jit_function, args, nullptr);
    }
}

void JitCollection::setElement( void* a_pObject, size_t index, const void* src ) const
{
    if(getElementType()->isReferenceType())
    {
        void* args[3] = { &a_pObject, &index, (void*)&src };                   
        jit_function_apply(m_set_jit_function, args, nullptr);
    }
    else
    {
        void* args[3] = { &a_pObject, &index, (void*)src };
        jit_function_apply(m_set_jit_function, args, nullptr);
    }
}

void JitCollection::moveElement( void* a_pObject, const void* src, size_t index ) const
{
    if(getElementType()->isReferenceType())
    {
        void* args[3] = { &a_pObject, (void*)&src, &index };                   
        jit_function_apply(m_move_jit_function, args, nullptr);
    }
    else
    {
        void* args[3] = { &a_pObject, (void*)src, &index };
        jit_function_apply(m_move_jit_function, args, nullptr);
    }
}

void JitCollection::removeElement( void* a_pObject, const void* src ) const
{
    if(getElementType()->isReferenceType())
    {
        void* args[2] = { &a_pObject, (void*)&src };                   
        jit_function_apply(m_remove_jit_function, args, nullptr);
    }
    else
    {
        void* args[2] = { &a_pObject, (void*)src };
        jit_function_apply(m_remove_jit_function, args, nullptr);
    }
}

void JitCollection::getElement( void const* a_pObject, size_t a_uiIndex, void* dest ) const
{
    if(getElementType()->isReferenceType())
    {
        void* args[2] = { &a_pObject, &a_uiIndex };                   
        jit_function_apply(m_get_jit_function, args, &dest);
    }
    else
    {
        void* args[2] = { &a_pObject, &a_uiIndex };
        jit_function_apply(m_get_jit_function, args, dest);
    }
}

size_t JitCollection::getSize( void const* a_pObject ) const
{
    size_t result = 0;
    if(getElementType()->isReferenceType())
    {
        void* args[1] = { &a_pObject };                   
        jit_function_apply(m_size_jit_function, args, &result);
    }
    else
    {
        void* args[1] = { &a_pObject };
        jit_function_apply(m_size_jit_function, args, &result);
    }
    return result;
}


o_namespace_end(phantom, reflection, runtime)
