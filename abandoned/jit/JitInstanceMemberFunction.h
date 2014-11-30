#ifndef o_JitInstanceMemberFunction_h__
#define o_JitInstanceMemberFunction_h__


/* ****************** Includes ******************* */
#include <phantom/jit.h>
#include <phantom/reflection/jit/JitSubroutine.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection, jit), JitInstanceMemberFunction);
/* *********************************************** */

o_namespace_begin(phantom, reflection, jit)


class o_jit_export JitInstanceMemberFunction : public JitSubroutine
{
    friend class JitClass;
public:
    JitInstanceMemberFunction( InstanceMemberFunction* a_pInstanceMemberFunction )
        : JitSubroutine(a_pInstanceMemberFunction, e_JitAbi_thiscall)
    {

    }

    InstanceMemberFunction* getInstanceMemberFunction() const;

    jit_function getVTableJitFunction(size_t a_uiThisOffset) const;
    
    virtual jit_function getJitCallFunction() const;

protected:
    void compileVTableIndirectionFunction();
    void compileThisAdjustementThunk(size_t a_uiThisOffset) const;

protected:
    virtual void setClosures();

protected:
    typedef map<size_t, jit_function> vtable_indirection_function_map;
    mutable vtable_indirection_function_map m_ThisAdjustmentThunks;
    jit_function  m_jit_virtual_indirection_function;
};

o_namespace_end(phantom, reflection, jit)

#endif
