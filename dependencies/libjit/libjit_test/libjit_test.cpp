// libjit_test.cpp : Defines the entry point for the console application.
//

#include <jit/jit.h>

struct vector2f 
{
    vector2f() {}
    float x;
    float y;
};

vector2f normalize_vector2f(vector2f vec)
{
    return vec;
}

void test()
{
    vector2f vec;
    vec.x = 1.f;
    vec.y = 1.f;
    vec = normalize_vector2f(vec);
}

extern "C"
{
};


int main(int argc, char* argv[])
{
    test();

    jit_context_t context = jit_context_create();

    jit_type_t xy[2] = {jit_type_float32, jit_type_float32};

    jit_type_t vector2f_type = jit_type_create_struct(xy, 2, 0);

    jit_type_t signature = jit_type_create_signature(jit_abi_stdcall, jit_type_void, 0, 0, 0);
    jit_type_t normalize_vector2f_signature = jit_type_create_signature(jit_abi_stdcall, vector2f_type, &vector2f_type, 1, 0);

    jit_function_t func = jit_function_create(context, signature);

    jit_value_t value = jit_value_create(func, vector2f_type);
    jit_value_t constant = jit_value_create_float32_constant(func, jit_type_float32, 1.f);

    jit_insn_store_relative(func, jit_insn_address_of(func, value), jit_type_get_offset(vector2f_type, 0), constant);
    jit_insn_store_relative(func, jit_insn_address_of(func, value), jit_type_get_offset(vector2f_type, 1), constant);
    
    jit_insn_store(func, value, jit_insn_call_native(func, "normalize_vec2", normalize_vector2f, normalize_vector2f_signature, &value, 1, 0));

    jit_function_compile(func);

    jit_function_apply(func, 0, 0);

	return 0;
}

