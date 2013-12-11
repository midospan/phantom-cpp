#ifndef o_JitInstanceMemberFunction_h__
#define o_JitInstanceMemberFunction_h__


/* ****************** Includes ******************* */
#include <phantom/def_jit.h>
#include <phantom/reflection/jit/JitSubroutine.h>
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection, jit)


class o_jit_export JitInstanceMemberFunction : public InstanceMemberFunction, public JitSubroutine
{
    friend class JitClass;
public:
    JitInstanceMemberFunction(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers);
    ~JitInstanceMemberFunction(void);

    virtual void    call( void* a_pThis, void** a_ppArgs ) const;
    virtual void	call( void* a_pThis, void** a_ppArgs, void* a_pReturnArea ) const;

    virtual void	call( void** args, void* a_pReturnArea ) const;
    virtual void	call( void** args ) const;

    jit_function getJitVirtualIndirectionFunction() const { return m_jit_virtual_indirection_function; }

    jit_function getJitGenericCallFunction() const;
    
    jit_function getVTableJitFunction(size_t a_uiThisOffset) const;
    
    void* getClosurePointer() const;
    
    virtual void* getVTablePointer(size_t a_uiThisOffset) const;

    generic_member_func_ptr getGenericMemberFunctionPointer() const;
    void setVirtual();

    virtual LanguageElement* asLanguageElement() const { return const_cast<JitInstanceMemberFunction*>(this); }
    virtual Subroutine* asSubroutine() const { return const_cast<JitInstanceMemberFunction*>(this); }
    EJitAbi getAbi() const { return e_JitAbi_thiscall; }

protected:
    void compileVTableIndirectionFunction();
    jit_function compileThisOffsetShiftFunction(size_t a_uiThisOffset) const;
    jit_function createJitFunction( jit_context context );

protected:
    typedef map<size_t, jit_function> vtable_indirection_function_map;
    mutable vtable_indirection_function_map m_VTableOffsetFixFunctions;
    jit_function  m_jit_virtual_indirection_function;
    jit_function  m_jit_placeholder_function;
};

o_namespace_end(phantom, reflection, jit)

o_classNS((phantom, reflection, jit), JitInstanceMemberFunction, (InstanceMemberFunction, JitSubroutine))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, reflection, jit), JitInstanceMemberFunction);

#endif
