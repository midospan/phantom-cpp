#ifndef o_JitSignal_h__
#define o_JitSignal_h__


/* ****************** Includes ******************* */
#include <phantom/def_jit.h>
/* **************** Declarations ***************** */

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
    virtual void    call( void* a_pThis, void** a_ppArgs ) const 
    {
        void* shiftedArgs[32];
        if(a_ppArgs)
        {
            memcpy(&shiftedArgs[1], a_ppArgs, getSignature()->getParameterCount());
        }
        shiftedArgs[0] = &a_pThis;
        jit_function_apply(m_jit_function, shiftedArgs, nullptr);
    }
    virtual void		call( void* a_pThis, void** a_ppArgs, void* a_pReturnArea ) const
    {
        void* shiftedArgs[32];
        if(a_ppArgs)
        {
            memcpy(&shiftedArgs[1], a_ppArgs, getSignature()->getParameterCount());
        }
        shiftedArgs[0] = &a_pThis;
        jit_function_apply(m_jit_function, shiftedArgs, a_pReturnArea);
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
    
    JitInstanceDataMember* getDataMember() const {return m_pDataMember; }
   
    void* getClosurePointer() const 
    {
        return jit_function_to_closure(m_jit_function);
    }

    generic_member_func_ptr getGenericMemberFunctionPointer() const
    {
        generic_member_func_ptr ptr;
        ptr.setClosurePointer(jit_function_to_closure(m_jit_function));
        return ptr;
    }

    bool isCompiled() const { return m_uiDataOffset != 0xffffffff; }
    void compile();

protected:
    jit_context_t getContext() const;

    virtual connection::slot::list* getSlotList( void* a_pCaller ) const 
    {
        o_assert(m_uiDataOffset != 0xffffffff);
        return reinterpret_cast<connection::slot::list*>( ((byte*)a_pCaller) + m_uiDataOffset );
    }

protected:
    jit_function_t  m_jit_function;
    jit_context_t   m_jit_context;
    JitInstanceDataMember* m_pDataMember;
    size_t          m_uiDataOffset;
};

o_namespace_end(phantom, reflection, jit)

o_classNS((phantom, reflection, jit), JitSignal, (Signal))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, reflection, jit), JitSignal);

#endif
