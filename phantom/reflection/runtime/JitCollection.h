#ifndef o_reflection_runtime_JitCollection_h__
#define o_reflection_runtime_JitCollection_h__


/* ****************** Includes ******************* */
#include <phantom/def_runtime.h>
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection, runtime)


class o_runtime_export JitCollection : public Collection
{
    friend class JitClass;

public:
    JitCollection(const string& a_strName
        , Type* a_pElementType
        , JitInstanceMethod* a_pAdder
        , JitInstanceMethod* a_pRemover
        , JitInstanceMethod* a_pMover
        , JitInstanceMethod* a_pSetter
        , JitInstanceMethod* a_pGetter
        , JitInstanceMethod* a_pSizeGetter
        , bitfield a_Modifiers);
    ~JitCollection(void);

    jit_function_t  getAddJitFunction() const { return m_add_jit_function; }
    jit_function_t  getRemoveJitFunction() const { return m_remove_jit_function; }
    jit_function_t  getMoveJitFunction() const { return m_move_jit_function; }
    jit_function_t  getSetJitFunction() const { return m_set_jit_function; }
    jit_function_t  getGetJitFunction() const { return m_get_jit_function; }
    jit_function_t  getSizeJitFunction() const { return m_size_jit_function; }

    virtual void    addElement( void* a_pObject, const void* src ) const;
    virtual void    removeElement( void* a_pObject, const void* src ) const;
    virtual void    setElement( void* a_pObject, size_t index, const void* src ) const;
    virtual void    moveElement( void* a_pObject, const void* src, size_t index ) const;
    virtual void    getElement(void const* a_pObject, size_t a_uiIndex, void* dest) const;
    virtual size_t  getSize(void const* a_pObject) const;


protected:
    JitInstanceMethod*  m_pAdder;
    JitInstanceMethod*  m_pRemover;
    JitInstanceMethod*  m_pSetter;
    JitInstanceMethod*  m_pMover;
    JitInstanceMethod*  m_pGetter;
    JitInstanceMethod*  m_pSizeGetter;
    jit_function_t      m_add_jit_function;
    jit_function_t      m_remove_jit_function;
    jit_function_t      m_move_jit_function;
    jit_function_t      m_set_jit_function;
    jit_function_t      m_get_jit_function;
    jit_function_t      m_size_jit_function;

};

o_namespace_end(phantom, reflection, runtime)

    o_classNS((phantom, reflection, runtime), JitCollection, (Collection))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, reflection, runtime), JitCollection);

#endif
