/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "JitProperty.h"
#include "JitClass.h"
#include "JitSignal.h"
#include "JitInstanceMemberFunction.h"
/* *********************************************** */
o_registerN((phantom, reflection, jit), JitProperty);

o_namespace_begin(phantom, reflection, jit)

JitProperty::JitProperty( const string& a_strName, Type* a_pValueType, JitInstanceMemberFunction* a_pSetter, JitInstanceMemberFunction* a_pGetter, JitSignal* a_pChangeNotificationSignal, uint a_uiSerializationMask, bitfield a_Modifiers ) 
    : Property(a_strName, a_pGetter->getReturnType(), a_pSetter, a_pGetter, a_pChangeNotificationSignal, a_uiSerializationMask, a_Modifiers) 
    , m_set_jit_function(0)
    , m_get_jit_function(0)
{
    m_set_jit_function = a_pSetter->getJitGenericCallFunction();
    m_get_jit_function = a_pGetter->getJitGenericCallFunction();
}

JitProperty::JitProperty( const string& a_strName, Type* a_pValueType,JitInstanceMemberFunction* a_pSetter, JitInstanceMemberFunction* a_pGetter, uint a_uiSerializationMask, bitfield a_Modifiers )
    : Property(a_strName, a_pGetter->getReturnType(), a_pSetter, a_pGetter, nullptr, a_uiSerializationMask, a_Modifiers) 
    , m_set_jit_function(0)
    , m_get_jit_function(0)
{
    m_set_jit_function = a_pSetter->getJitGenericCallFunction();
    m_get_jit_function = a_pGetter->getJitGenericCallFunction();
}

JitProperty::~JitProperty( void )
{
}

void JitProperty::setChangeNotificationSignal( JitSignal* a_pSignal )
{
    m_pChangeNotificationSignal = a_pSignal;
}

void JitProperty::getValue( void const* a_pObject, void* dest ) const
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

void JitProperty::setValue( void* a_pObject, const void* src ) const
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


o_namespace_end(phantom, reflection, jit)