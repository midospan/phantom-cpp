#ifndef o_phantom_def_jit_internal
#define o_phantom_def_jit_internal

#include "def_jit.h"
#include "jit/jit.h"

o_namespace_begin(phantom, reflection, jit)

o_jit_export jit_value jit_phantom_math_func(jit_function_t func, const char* function, jit_value v0);
o_jit_export jit_value jit_phantom_math_func(jit_function_t func, const char* function, jit_value v0, jit_value v1);
o_jit_export jit_value jit_phantom_math_func(jit_function_t func, const char* function, jit_value v0, jit_value v1, jit_value v2);
o_jit_export jit_value jit_phantom_math_func(jit_function_t func, const char* function, jit_value v0, jit_value v1, jit_value v2, jit_value v3);

jit_value   jit_insn_phantom_implicit_cast(jit_function_t func, jit_value value, phantom::reflection::Type* a_pDestType ); 

class JitSubroutine* jitSubroutine(jit_function func);
jit_function jitFunctionFromMemoryAddressEnd(byte* a_pAddress);
void registerJitFunction(jit_function, class JitSubroutine*);
void unregisterJitFunction(jit_function func);

Type* fromJitType(jit_type_t type) ;
jit_type_t toJitType(Type* a_pType);
jit_type_t toJitSignature(EJitAbi abi, Signature* a_pSignature) ;

void clearCache();

o_namespace_end(phantom, reflection, jit)

#endif