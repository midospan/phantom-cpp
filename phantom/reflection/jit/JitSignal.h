#ifndef o_JitSignal_h__
#define o_JitSignal_h__


/* ****************** Includes ******************* */
#include <phantom/jit.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection, jit), JitSignal);
/* *********************************************** */

o_namespace_begin(phantom, reflection, jit)


class o_jit_export JitSignal : public Signal
{
    friend class JitClass;
public:
    JitSignal(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers);
    ~JitSignal(void);

    virtual void    call( void* a_pCallerAddress, argument::list* a_pArgs ) const 
    {
        o_assert(false, "call version not available with Jit compilation");
    }
    virtual void    call( void* a_pCallerAddress, argument::list* a_pArgs, void* a_pReturnAddress ) const 
    {
        o_assert(false, "call version not available with Jit compilation");
    }
    virtual void    call( void* a_pThis, void** a_ppArgs ) const;
    virtual void	call( void* a_pThis, void** a_ppArgs, void* a_pReturnArea ) const;

    virtual void	call( void** args, void* a_pReturnArea ) const;

    virtual void	call( void** args ) const;

    jit_function getJitFunction() const { return m_jit_function; }
    
    JitInstanceDataMember* getDataMember() const {return m_pDataMember; }
   
    void* getClosurePointer() const;

    generic_member_func_ptr getGenericMemberFunctionPointer() const;

    bool isCompiled() const { return m_uiDataOffset != 0xffffffff; }
    void compile();

protected:
    jit_context getContext() const;

    virtual connection::slot::list* getSlotList( void* a_pCaller ) const 
    {
        o_assert(m_uiDataOffset != 0xffffffff);
        return reinterpret_cast<connection::slot::list*>( ((byte*)a_pCaller) + m_uiDataOffset );
    }

protected:
    jit_function            m_jit_function;
    jit_context             m_jit_context;
    JitInstanceDataMember*  m_pDataMember;
    size_t                  m_uiDataOffset;
};

o_namespace_end(phantom, reflection, jit)

#endif
