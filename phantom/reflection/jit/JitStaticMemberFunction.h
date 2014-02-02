#ifndef o_JitStaticMemberFunction_h__
#define o_JitStaticMemberFunction_h__


/* ****************** Includes ******************* */
#include <phantom/jit.h>
#include <phantom/reflection/jit/JitSubroutine.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection, jit), JitStaticMemberFunction);
/* *********************************************** */

o_namespace_begin(phantom, reflection, jit)

class o_jit_export JitStaticMemberFunction : public StaticMemberFunction, public JitSubroutine
{

public:
    JitStaticMemberFunction(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers);
    ~JitStaticMemberFunction(void);

    void startCompilation();
    void endCompilation();
    void abortCompilation();
    void reset();

    virtual void    call( void* a_pCallerAddress, argument::list* a_pArgs ) const;
    virtual void    call( void* a_pCallerAddress, argument::list* a_pArgs, void* a_pReturnAddress ) const;
    virtual void    call( void* a_pThis, void** a_ppArgs ) const;
    virtual void	call( void* a_pThis, void** a_ppArgs, void* a_pReturnArea ) const;

    virtual void	call( void** args, void* a_pReturnArea ) const;

    virtual void	call( void** args ) const;

    virtual void*   getClosurePointer() const;

    virtual LanguageElement*    asLanguageElement() const { return const_cast<JitStaticMemberFunction*>(this); }
    virtual Subroutine*         asSubroutine() const { return const_cast<JitStaticMemberFunction*>(this); }
    virtual EJitAbi           getAbi() const { return e_JitAbi_stdcall; }

protected:
    jit_function createJitFunction(jit_context context);

protected:
};

o_namespace_end(phantom, reflection, jit)
    
#endif
