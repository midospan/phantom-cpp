#ifndef o_JitStaticMethod_h__
#define o_JitStaticMethod_h__


/* ****************** Includes ******************* */
#include <phantom/def_runtime.h>
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection, runtime)

class o_runtime_export JitStaticMethod : public StaticMethod
{

public:
    JitStaticMethod(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers);
    ~JitStaticMethod(void);

    void startCompilation();
    void endCompilation();
    void abortCompilation();
    void reset();

    virtual void    invoke( void* a_pCallerAddress, argument::list* a_pArgs ) const 
    {
        o_assert(false, "invoke version not available with Jit compilation");
    }
    virtual void    invoke( void* a_pCallerAddress, argument::list* a_pArgs, void* a_pReturnAddress ) const 
    {
        o_assert(false, "invoke version not available with Jit compilation");
    }
    virtual void    invoke( void* a_pThis, void** a_ppArgs ) const 
    {
        jit_function_apply(m_jit_function, a_ppArgs, nullptr);
    }
    virtual void		invoke( void* a_pThis, void** a_ppArgs, void* a_pReturnArea ) const
    {
        jit_function_apply(m_jit_function, a_ppArgs, a_pReturnArea);
    }

    virtual void		call( void** args, void* a_pReturnArea ) const
    {
        jit_function_apply(m_jit_function, args, a_pReturnArea);
    }

    virtual void		call( void** args ) const
    {
        jit_function_apply(m_jit_function, args, nullptr);
    }

    jit_function_t getJitFunction() const { return m_jit_function; }
    void* getClosurePointer() const 
    { 
        o_assert(m_jit_function, "Closure not yet created, you must add this JitStaticMethod to a JitClass"); 
        return jit_function_to_closure(m_jit_function);
    }

    jit_context_t getContext() const;

    virtual LanguageElement* asLanguageElement() const { return const_cast<JitStaticMethod*>(this); }

protected:
    void createJitFunction(jit_context_t context)
    {
        m_jit_function = jit_function_create(context, jit_type_from_phantom_signature(jit_abi_cdecl, getSignature()));
    }
    static void instructionCompilationCallback( jit_insn_t insn, byte* start, byte* end );
    static void compilationSuccessCallback(jit_function_t func);

protected:
    static map<jit_function_t, JitStaticMethod*> sm_Compiled;
    jit_function_t  m_jit_function;
    jit_context_t   m_jit_context;
};

o_namespace_end(phantom, reflection, runtime)

    o_classNS((phantom, reflection, runtime), JitStaticMethod, (StaticMethod))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, reflection, runtime), JitStaticMethod);

#endif
