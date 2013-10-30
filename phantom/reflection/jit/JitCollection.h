#ifndef o_reflection_jit_JitCollection_h__
#define o_reflection_jit_JitCollection_h__


/* ****************** Includes ******************* */
#include <phantom/def_jit.h>
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection, jit)


class o_jit_export JitCollection : public Collection
{
    friend class JitClass;

public:
    JitCollection(const string& a_strName
        , Type* a_pElementType
        , JitInstanceMemberFunction* a_pAdder
        , JitInstanceMemberFunction* a_pRemover
        , JitInstanceMemberFunction* a_pMover
        , JitInstanceMemberFunction* a_pSetter
        , JitInstanceMemberFunction* a_pGetter
        , JitInstanceMemberFunction* a_pSizeGetter
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
    JitInstanceMemberFunction*  m_pAdder;
    JitInstanceMemberFunction*  m_pRemover;
    JitInstanceMemberFunction*  m_pSetter;
    JitInstanceMemberFunction*  m_pMover;
    JitInstanceMemberFunction*  m_pGetter;
    JitInstanceMemberFunction*  m_pSizeGetter;
    jit_function_t      m_add_jit_function;
    jit_function_t      m_remove_jit_function;
    jit_function_t      m_move_jit_function;
    jit_function_t      m_set_jit_function;
    jit_function_t      m_get_jit_function;
    jit_function_t      m_size_jit_function;

};

o_namespace_end(phantom, reflection, jit)

    o_classNS((phantom, reflection, jit), JitCollection, (Collection))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, reflection, jit), JitCollection);

#endif
