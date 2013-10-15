#ifndef o_phantom_def_runtime
#define o_phantom_def_runtime


#include <phantom/phantom.h>
#include <jit/jit.h>


#if (o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS) && !defined(RUNTIME_STATIC_LIB)
#    ifdef _PHANTOM_RUNTIME
#        define o_runtime_export __declspec(dllexport)
#    else
#       if defined( __MINGW32__ )
#           define o_runtime_export
#       else
#            define o_runtime_export __declspec(dllimport)
#       endif
#    endif
#else
#    define o_runtime_export
#endif    // #if (o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS) && !defined(PHANTOM_STATIC_LIB)


o_fwd(class, phantom, reflection, runtime, JitClass);
o_fwd(class, phantom, reflection, runtime, JitEnum);
o_fwd(class, phantom, reflection, runtime, JitInstanceMethod);
o_fwd(class, phantom, reflection, runtime, JitInstanceAttribute);
o_fwd(class, phantom, reflection, runtime, JitStaticAttribute);
o_fwd(class, phantom, reflection, runtime, JitStaticMethod);
o_fwd(class, phantom, reflection, runtime, JitSignal);
o_fwd(class, phantom, reflection, runtime, JitAccessor);
o_fwd(class, phantom, reflection, runtime, JitCollection);
o_fwd(class, phantom, reflection, runtime, JitAddressable);
o_fwd(class, phantom, reflection, runtime, JitLocalVariable);

o_fwd(class, phantom, state, runtime, JitStateMachine);
o_fwd(class, phantom, state, runtime, JitTrack);
o_fwd(class, phantom, state, runtime, JitState);

namespace phantom { namespace reflection    { namespace runtime {} } }
namespace phantom { namespace state         { namespace runtime 
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

o_runtime_export jit_type_t jit_type_from_phantom_type(phantom::reflection::Type* a_pType);
o_runtime_export phantom::reflection::Type* jit_type_to_phantom_type(jit_type_t type);
o_runtime_export jit_type_t jit_type_from_phantom_signature(jit_abi_t abi, phantom::reflection::Signature* a_pSignature);


struct jit_phantom_value_t
{
    jit_phantom_value_t()
        : value(0), type(0) {}
    jit_phantom_value_t(jit_value_t a_Value)
        : value(a_Value)
        , type(a_Value == 0 ? 0 : jit_type_to_phantom_type(jit_value_get_type(a_Value)))
    {
    }
    jit_phantom_value_t(jit_value_t a_Value, phantom::reflection::Type* a_pType)
        : value(a_Value)
        , type(a_Value == 0 ? 0 : a_pType)
    {

    }

    bool isNull() const { return value == 0; }
    bool isNullPtr() const{ return type == nullptr; }

    jit_value_t     value;
    phantom::reflection::Type* type;

    operator jit_value_t ()
    {
        return (jit_value_t)value;
    }

    bool operator==(const jit_value_t ptr) const { return value == ptr; }
    bool operator!=(const jit_value_t ptr) const { return value != ptr; }
};

o_runtime_export jit_phantom_value_t jit_insn_phantom_implicit_cast(jit_function_t func, phantom::reflection::Type* dest, jit_phantom_value_t value );;
o_runtime_export jit_phantom_value_t jit_insn_phantom_cast(jit_function_t func, phantom::reflection::Type* dest, jit_phantom_value_t value );;
o_runtime_export jit_phantom_value_t jit_insn_phantom_eq(jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r);
o_runtime_export jit_phantom_value_t jit_insn_phantom_ne(jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r);
o_runtime_export jit_phantom_value_t jit_insn_phantom_lt(jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r);
o_runtime_export jit_phantom_value_t jit_insn_phantom_gt(jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r);
o_runtime_export jit_phantom_value_t jit_insn_phantom_ge(jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r);
o_runtime_export jit_phantom_value_t jit_insn_phantom_le(jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r);
o_runtime_export jit_phantom_value_t jit_insn_phantom_add(jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r);
o_runtime_export jit_phantom_value_t jit_insn_phantom_sub(jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r);
o_runtime_export jit_phantom_value_t jit_insn_phantom_mul(jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r);
o_runtime_export jit_phantom_value_t jit_insn_phantom_div(jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r);
// BITWISE OPERATIONS (only on integral types)
o_runtime_export jit_phantom_value_t jit_insn_phantom_shr(jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r);
o_runtime_export jit_phantom_value_t jit_insn_phantom_shl(jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r);
o_runtime_export jit_phantom_value_t jit_insn_phantom_rem(jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r);
o_runtime_export jit_phantom_value_t jit_insn_phantom_and(jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r);
o_runtime_export jit_phantom_value_t jit_insn_phantom_or(jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r);
o_runtime_export jit_phantom_value_t jit_insn_phantom_xor(jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r);
o_runtime_export jit_phantom_value_t jit_insn_phantom_not(jit_function_t func, jit_phantom_value_t value);
o_runtime_export void jit_value_phantom_create_1_constant(jit_constant_t& constant);
o_runtime_export jit_phantom_value_t jit_insn_phantom_neg( jit_function_t func, jit_phantom_value_t op );

o_runtime_export jit_phantom_value_t jit_phantom_math_operation(jit_function_t func, char op, jit_phantom_value_t l, jit_phantom_value_t r);
o_runtime_export jit_phantom_value_t jit_phantom_math_unary_intrinsic(jit_function_t func, const char* intrinsic, jit_phantom_value_t l);
o_runtime_export jit_phantom_value_t jit_phantom_math_binary_intrinsic(jit_function_t func, const char* intrinsic, jit_phantom_value_t l, jit_phantom_value_t r);

o_runtime_export jit_phantom_value_t jit_phantom_math_func(jit_function_t func, const char* function, jit_phantom_value_t v0);
o_runtime_export jit_phantom_value_t jit_phantom_math_func(jit_function_t func, const char* function, jit_phantom_value_t v0, jit_phantom_value_t v1);
o_runtime_export jit_phantom_value_t jit_phantom_math_func(jit_function_t func, const char* function, jit_phantom_value_t v0, jit_phantom_value_t v1, jit_phantom_value_t v2);

o_class(jit_phantom_value_t)
{
    o_reflection {};
};
o_expose(jit_phantom_value_t);

#endif