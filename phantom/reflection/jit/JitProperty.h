#ifndef o_reflection_jit_JitProperty_h__
#define o_reflection_jit_JitProperty_h__


/* ****************** Includes ******************* */
#include <phantom/def_jit.h>
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection, jit)


class o_jit_export JitProperty : public Property
{
    friend class JitClass;
public:
    JitProperty(const string& a_strName, Type* a_pValueType, JitInstanceMemberFunction* a_pSetter, JitInstanceMemberFunction* a_pGetter, uint a_uiSerializationMask, bitfield a_Modifiers);
    JitProperty(const string& a_strName, Type* a_pValueType, JitInstanceMemberFunction* a_pSetter, JitInstanceMemberFunction* a_pGetter, JitSignal* a_pChangeNotificationSignal, uint a_uiSerializationMask, bitfield a_Modifiers);
    ~JitProperty(void);

    jit_function getSetJitFunction() const { return m_set_jit_function; }
    jit_function getGetJitFunction() const { return m_get_jit_function; }

    void getValue( void const* a_pObject, void* dest ) const;
    void setValue( void* a_pObject, const void* src ) const;

    void setChangeNotificationSignal(JitSignal* a_pSignal);

protected:
    jit_function      m_get_jit_function;
    jit_function      m_set_jit_function;
};

o_namespace_end(phantom, reflection, jit)

o_classNS((phantom, reflection, jit), JitProperty, (Property))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, reflection, jit), JitProperty);

#endif
