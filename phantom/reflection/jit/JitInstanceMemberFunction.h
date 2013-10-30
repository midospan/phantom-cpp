#ifndef o_JitInstanceMemberFunction_h__
#define o_JitInstanceMemberFunction_h__


/* ****************** Includes ******************* */
#include <phantom/def_jit.h>
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection, jit)


class o_jit_export JitInstanceMemberFunction : public InstanceMemberFunction
{
    friend class JitClass;
public:
    JitInstanceMemberFunction(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers);
    ~JitInstanceMemberFunction(void);

    static void     CompileDebugMemberFunction(JitInstanceMemberFunction* pMemberFunction, const char* to_print);

    void startCompilation();
    void abortCompilation();
    void endCompilation();

    virtual void    call( void* a_pThis, void** a_ppArgs ) const;
    virtual void	call( void* a_pThis, void** a_ppArgs, void* a_pReturnArea ) const;

    virtual void	call( void** args, void* a_pReturnArea ) const;
    virtual void	call( void** args ) const;

    jit_function_t getJitFunction() const { return m_jit_function; }
    jit_function_t getJitVirtualIndirectionFunction() const { return m_jit_virtual_indirection_function; }

    jit_function_t getJitGenericCallFunction() const;
    
    jit_function_t getVTableJitFunction(size_t a_uiThisOffset) const;
    
    void* getClosurePointer() const;
    
    virtual void* getVTablePointer(size_t a_uiThisOffset) const 
    {
        return jit_function_to_vtable_pointer(getVTableJitFunction(a_uiThisOffset));
    }

    generic_member_func_ptr getGenericMemberFunctionPointer() const;
    void setVirtual();
    void reset();

    virtual LanguageElement* asLanguageElement() const { return const_cast<JitInstanceMemberFunction*>(this); }

protected:
    jit_context_t getContext() const;

    void compile_vtable_indirection_function();
    jit_function_t compile_this_offset_fix_function(size_t a_uiThisOffset) const;

    static void instructionCompilationCallback( jit_insn_t insn, byte* start, byte* end );
    static void compilationSuccessCallback(jit_function_t func);
    
protected:
    static map<jit_function_t, JitInstanceMemberFunction*> sm_Compiled;
    typedef map<size_t, jit_function_t> vtable_indirection_function_map;
    mutable vtable_indirection_function_map m_VTableOffsetFixFunctions;
    jit_function_t  m_jit_function;
    jit_function_t  m_jit_virtual_indirection_function;
    jit_function_t  m_jit_placeholder_function;
    jit_context_t   m_jit_context;
};

o_namespace_end(phantom, reflection, jit)

o_classNS((phantom, reflection, jit), JitInstanceMemberFunction, (InstanceMemberFunction))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, reflection, jit), JitInstanceMemberFunction);

#endif
