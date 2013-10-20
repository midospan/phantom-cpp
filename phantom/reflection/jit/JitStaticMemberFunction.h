#ifndef o_JitStaticMemberFunction_h__
#define o_JitStaticMemberFunction_h__


/* ****************** Includes ******************* */
#include <phantom/def_jit.h>
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection, jit)

class o_jit_export JitStaticMemberFunction : public StaticMemberFunction
{

public:
    JitStaticMemberFunction(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers);
    ~JitStaticMemberFunction(void);

    void startCompilation();
    void endCompilation();
    void abortCompilation();
    void reset();

    virtual void    call( void* a_pCallerAddress, argument::list* a_pArgs ) const 
    {
        o_assert(false, "call version not available with Jit compilation");
    }
    virtual void    call( void* a_pCallerAddress, argument::list* a_pArgs, void* a_pReturnAddress ) const 
    {
        o_assert(false, "call version not available with Jit compilation");
    }
    virtual void    call( void* a_pThis, void** a_ppArgs ) const 
    {
        jit_function_apply(m_jit_function, a_ppArgs, nullptr);
    }
    virtual void		call( void* a_pThis, void** a_ppArgs, void* a_pReturnArea ) const
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
        o_assert(m_jit_function, "Closure not yet created, you must add this JitStaticMemberFunction to a JitClass"); 
        return jit_function_to_closure(m_jit_function);
    }

    jit_context_t getContext() const;

    virtual LanguageElement* asLanguageElement() const { return const_cast<JitStaticMemberFunction*>(this); }

protected:
    void createJitFunction(jit_context_t context)
    {
        m_jit_function = jit_function_create(context, jit_type_from_phantom_signature(jit_abi_cdecl, getSignature()));
    }
    static void instructionCompilationCallback( jit_insn_t insn, byte* start, byte* end );
    static void compilationSuccessCallback(jit_function_t func);

protected:
    static map<jit_function_t, JitStaticMemberFunction*> sm_Compiled;
    jit_function_t  m_jit_function;
    jit_context_t   m_jit_context;
};

o_namespace_end(phantom, reflection, jit)

    o_classNS((phantom, reflection, jit), JitStaticMemberFunction, (StaticMemberFunction))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, reflection, jit), JitStaticMemberFunction);

#endif
