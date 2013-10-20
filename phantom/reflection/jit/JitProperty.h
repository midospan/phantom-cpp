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
    JitProperty(const string& a_strName, JitInstanceMemberFunction* a_pSetter, JitInstanceMemberFunction* a_pGetter, uint a_uiSerializationMask, bitfield a_Modifiers);
    JitProperty(const string& a_strName, JitSignal* a_pChangeNotificationSignal, JitInstanceMemberFunction* a_pSetter, JitInstanceMemberFunction* a_pGetter, uint a_uiSerializationMask, bitfield a_Modifiers);
    ~JitProperty(void);

    jit_function_t getSetJitFunction() const { return m_set_jit_function; }
    jit_function_t getGetJitFunction() const { return m_get_jit_function; }

    virtual Type* getValueType() const;
    void getValue( void const* a_pObject, void* dest ) const;
    void setValue( void* a_pObject, const void* src ) const;

    void setChangeNotificationSignal(JitSignal* a_pSignal);

protected:
    JitInstanceMemberFunction*  m_pSetter;
    JitInstanceMemberFunction*  m_pGetter;
    jit_function_t      m_get_jit_function;
    jit_function_t      m_set_jit_function;
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
