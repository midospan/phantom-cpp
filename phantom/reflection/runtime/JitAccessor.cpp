/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "JitAccessor.h"
#include "JitClass.h"
#include "JitInstanceMethod.h"
/* *********************************************** */
o_registerN((phantom, reflection, runtime), JitAccessor);

o_namespace_begin(phantom, reflection, runtime)

JitAccessor::JitAccessor( const string& a_strName, JitInstanceMethod* a_pSetter, JitInstanceMethod* a_pGetter, uint a_uiSerializationMask, bitfield a_Modifiers ) 
    : Accessor(a_strName, a_uiSerializationMask, a_Modifiers) 
    , m_pSetter(a_pSetter)
    , m_pGetter(a_pGetter)
    , m_set_jit_function(0)
    , m_get_jit_function(0)
{
    m_set_jit_function = m_pSetter->getJitGenericCallFunction();
    m_get_jit_function = m_pGetter->getJitGenericCallFunction();
}

JitAccessor::~JitAccessor( void )
{
}

void JitAccessor::getValue( void const* a_pObject, void* dest ) const
{
    void* pThis = &a_pObject;
    if(getValueType()->isReferenceType())
    {
        void* reference_address = nullptr;
        jit_function_apply(m_get_jit_function, &pThis, &reference_address);
        getValueType()->removeReference()->removeConst()->copy(dest, reference_address);
    }
    else 
    {
        jit_function_apply(m_get_jit_function, &pThis, dest);
    }
}

void JitAccessor::setValue( void* a_pObject, const void* src ) const
{
    if(getValueType()->isReferenceType())
    {
        void* args[2] = { &a_pObject, (void*)&src };                   
        jit_function_apply(m_set_jit_function, args, nullptr);
    }
    else
    {
        void* args[2] = { &a_pObject, (void*)src };
        jit_function_apply(m_set_jit_function, args, nullptr);
    }
}

Type* JitAccessor::getValueType() const
{
    return m_pGetter->getReturnType();
}


o_namespace_end(phantom, reflection, runtime)
