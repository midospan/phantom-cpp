#ifndef o_JitSignal_h__
#define o_JitSignal_h__


/* ****************** Includes ******************* */
#include <phantom/jit.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection, jit), JitSignal);
/* *********************************************** */

o_namespace_begin(phantom, reflection, jit)


class o_jit_export JitSignal : public JitInstanceMemberFunction
{
    friend class JitClass;
public:
    JitSignal(Signal* a_pSignal);
    ~JitSignal(void);
    
    Signal* getSignal() const { return static_cast<Signal*>(m_pSubroutine); }
    
    void compile();

protected:
    size_t                  m_uiDataOffset;
};

o_namespace_end(phantom, reflection, jit)

#endif
