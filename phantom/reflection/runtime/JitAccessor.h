#ifndef o_reflection_runtime_JitAccessor_h__
#define o_reflection_runtime_JitAccessor_h__


/* ****************** Includes ******************* */
#include <phantom/def_runtime.h>
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection, runtime)


class o_runtime_export JitAccessor : public Accessor
{
    friend class JitClass;
public:
    JitAccessor(const string& a_strName, JitInstanceMethod* a_pSetter, JitInstanceMethod* a_pGetter, uint a_uiSerializationMask, bitfield a_Modifiers);
    ~JitAccessor(void);

    jit_function_t getSetJitFunction() const { return m_set_jit_function; }
    jit_function_t getGetJitFunction() const { return m_get_jit_function; }

    virtual Type* getValueType() const;
    void getValue( void const* a_pObject, void* dest ) const;
    void setValue( void* a_pObject, const void* src ) const;

protected:
    JitInstanceMethod*  m_pSetter;
    JitInstanceMethod*  m_pGetter;
    jit_function_t      m_get_jit_function;
    jit_function_t      m_set_jit_function;
};

o_namespace_end(phantom, reflection, runtime)

o_classNS((phantom, reflection, runtime), JitAccessor, (Accessor))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, reflection, runtime), JitAccessor);

#endif
