#ifndef o_phantom_def_jit
#define o_phantom_def_jit

#include <phantom/phantom.h>

#if (o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS) && !defined(JIT_STATIC_LIB)
#    ifdef _PHANTOM_JIT
#        define o_jit_export __declspec(dllexport)
#    else
#       if defined( __MINGW32__ )
#           define o_jit_export
#       else
#            define o_jit_export __declspec(dllimport)
#       endif
#    endif
#else
#    define o_jit_export
#endif    // #if (o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS) && !defined(PHANTOM_STATIC_LIB)


o_fwd(class, phantom, reflection, jit, JitClass);
o_fwd(class, phantom, reflection, jit, JitEnum);
o_fwd(class, phantom, reflection, jit, JitInstanceMemberFunction);
o_fwd(class, phantom, reflection, jit, JitInstanceDataMember);
o_fwd(class, phantom, reflection, jit, JitStaticDataMember);
o_fwd(class, phantom, reflection, jit, JitStaticMemberFunction);
o_fwd(class, phantom, reflection, jit, JitSignal);
o_fwd(class, phantom, reflection, jit, JitProperty);
o_fwd(class, phantom, reflection, jit, JitCollection);
o_fwd(class, phantom, reflection, jit, JitAddressable);
o_fwd(class, phantom, reflection, jit, JitLocalVariable);
o_fwd(class, phantom, reflection, jit, JitSubroutine);

o_fwd(class, phantom, state, jit, JitStateMachine);
o_fwd(class, phantom, state, jit, JitTrack);
o_fwd(class, phantom, state, jit, JitState);

namespace phantom { namespace reflection    { namespace jit {} } }
namespace phantom { namespace state         { namespace jit 
    {
        class JitStateMachine;
        class JitState;
        struct jit_state_machine_data : base_state_machine_data
        {
            friend class JitStateMachine;
            friend class JitState;
            friend class JitTrack;
            jit_state_machine_data(void* a_pOwner, JitStateMachine* a_pSM)
                :  base_state_machine_data(a_pOwner, (StateMachine*)a_pSM)
            {
                current_states = o_allocate_n(state_machine->getTrackCount(), JitState*);
                memset(current_states, 0, state_machine->getTrackCount()*sizeof(void*));
                transit_states = o_allocate_n(state_machine->getTrackCount(), JitState*);
                memset(transit_states, 0, state_machine->getTrackCount()*sizeof(void*));
            }
            ~jit_state_machine_data()
            {
                o_deallocate_n(current_states, state_machine->getTrackCount(), JitState*);
                o_deallocate_n(transit_states, state_machine->getTrackCount(), JitState*);
            }
            JitState**  current_states;
            JitState**  transit_states;
        };
    } 
} 
}

o_namespace_begin(phantom, reflection, jit)

enum EJitAbi
{
    e_JitAbi_cdecl,			/* Native C calling conventions */
    e_JitAbi_vararg,			/* Native C with optional variable arguments */
    e_JitAbi_stdcall,		/* Win32 STDCALL (same as cdecl if not Win32) */
    e_JitAbi_fastcall,		/* Win32 FASTCALL (same as cdecl if not Win32) */
    e_JitAbi_thiscall		/* Method call */
};

struct o_jit_export jit_label
{
    jit_label();
    uint label;
};

struct o_jit_export jit_function
{
    jit_function();
    jit_function(void* b);
    void* function;
};

struct o_jit_export jit_context
{
    jit_context();
    jit_context(void* b);
    void* context;
};

struct o_jit_export jit_block
{
    jit_block();
    jit_block(void* b);
    void* block;
};

struct o_jit_export jit_constant
{
    jit_constant();
    Type* getType () const;
    int getIntValue() const;
    uint getUIntValue() const;
    longlong getLongLongValue() const;
    ulonglong getULongLongValue() const;
    Type*			type;
    union
    {
        void*       ptr_value;
        int			int_value;
        uint		uint_value;
        longlong	longlong_value;
        ulonglong	ulonglong_value;
        float		float_value;
        double		double_value;
    } un;
};

struct o_jit_export jit_value
{
    jit_value();
    jit_value(void* a_Value);
    jit_value(void* a_Value, phantom::reflection::Type* a_pType);

    bool isNull() const { return value == 0; }
    bool isNullPtr() const{ return type == nullptr; }

    void*     value;
    Type*     type;
    
    bool operator==(const jit_value& ptr) const { return value == ptr.value; }
    bool operator!=(const jit_value& ptr) const { return value != ptr.value; }

    int             isTemporary () const;
    void            setLocal();
    int             isLocal () const;
    int             isConstant () const;
    int             isParameter () const;
    void            ref() const;
    void            setVolatile () const;
    int             isVolatile () const;
    void            setAddressable () const;
    int             isAddressable () const;
    Type*           getType () const;
    JitSubroutine*  getJitSubroutine() const;
    jit_block       getBlock () const;
    jit_context     getContext () const;
    jit_constant    getConstant () const;
    int             getIntConstant () const;
    longlong        getLongLongConstant () const;
    float           getFloatConstant () const;
    double          getDoubleConstant () const;
    int             getFrameOffset() const;
    int             isTrue () const;
    static int      convertConstant (jit_constant *result, const jit_constant *value, Type* a_pType, int overflow_check);
    static jit_constant create1Constant();
};

o_namespace_end(phantom, reflection, jit)
    
o_classN((phantom, reflection, jit), jit_value)
{
    o_reflection {};
};
o_exposeN((phantom, reflection, jit), jit_value);

#endif