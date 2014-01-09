#include "phantom/phantom.h"
#include "phantom/math/math.h"
#include "def_jit.h"
#include "def_jit_internal.h"
#include "phantom/reflection/jit/JitSubroutine.h"

o_namespace_begin(phantom, reflection, jit)

static struct jit_initializer {
    jit_initializer()
    {
        jit_init();
    }
} g_initializer;

    

static map<void*, JitSubroutine*> sm_FromJitFunction;

class JitSubroutine* jitSubroutine( jit_function func )
{
    return sm_FromJitFunction[func.function];
}

jit_value   jit_insn_phantom_implicit_cast(jit_function_t func, jit_value value, phantom::reflection::Type* a_pDestType ) 
{
    if(a_pDestType == value.type) return jit_value((jit_value_t)value.value, a_pDestType);
    if(!value.type->isConvertibleTo(a_pDestType)) 
        return jit_value();

    o_assert(!value.type->isDataPointerType() || a_pDestType->isDataPointerType(), " src is ptr => dest is ptr, or something is wrong in isConvertibleTo");
    if(a_pDestType->isDataPointerType())
    {
        o_assert(value.type->isDataPointerType());
        phantom::reflection::Type* pDestPointedType = a_pDestType->asDataPointerType()->getPointedType();
        phantom::reflection::Type* pSrcPointedType = value.type->asDataPointerType()->getPointedType();
        if(pDestPointedType->isClass() == pSrcPointedType->isClass())
        {
            if(pDestPointedType->isClass())
            {
                size_t offset = pSrcPointedType->asClass()->getSuperClassOffsetCascade(pDestPointedType->asClass());
                if(offset == 0xffffffff) return jit_value();
                if(offset == 0) return jit_value((jit_value_t)value.value, a_pDestType);
                return jit_value(jit_insn_add_relative(func, (jit_value_t)value.value, offset), a_pDestType);
            }
            else
            {
                return jit_value();
            }
        }
        else 
        {
            return jit_value();
        }
    }
    // TODO fix that shitty triple test
    else if(a_pDestType->isArithmeticType() AND value.type->isArithmeticType())
    {
        return jit_value(jit_insn_convert(func, (jit_value_t)value.value, toJitType(a_pDestType), 0), a_pDestType);
    }
    else if(a_pDestType->isIntegralType() AND value.type->isArithmeticType())
    {
        return jit_value(jit_insn_convert(func, (jit_value_t)value.value, toJitType(a_pDestType), 0), a_pDestType);
    }
    else if(a_pDestType->isArithmeticType() AND value.type->isIntegralType())
    {
        return jit_value(jit_insn_convert(func, (jit_value_t)value.value, toJitType(a_pDestType), 0), a_pDestType);
    }
    else if(a_pDestType->isReferenceType() AND NOT(value.type->isReferenceType()))
    {
        /// Convert from value to reference => address value
        if(value.isAddressable()) 
        {
            return jit_value(jit_insn_address_of(func, (jit_value_t)value.value), a_pDestType);
        }
        else if(a_pDestType->asReferenceType()->getReferencedType()->isConstType())
        {
            jit_value_t temp_value = jit_value_create(func, toJitType(a_pDestType->asReferenceType()->getReferencedType())) ;
            jit_value_set_addressable(temp_value);
            int result = jit_insn_store(func, temp_value, (jit_value_t)value.value);
            o_assert(result);
            return jit_value(jit_insn_address_of(func, temp_value), a_pDestType);
        }
    }
    else if(NOT(a_pDestType->isReferenceType()) AND value.type->isReferenceType())
    {
        /// Convert from reference to value (dereference) => get value content
        return jit_insn_load_relative(func, (jit_value_t)value.value, 0, toJitType(a_pDestType));
    }
    return jit_value();
}

static phantom::reflection::Type* phantom_type_float32 = phantom::typeOf<float>();
static phantom::reflection::Type* phantom_type_float64 = phantom::typeOf<double>();
static phantom::reflection::Type* phantom_type_int = phantom::typeOf<int>();
static phantom::reflection::Type* phantom_type_uint = phantom::typeOf<unsigned int>();
static phantom::reflection::Type* phantom_type_long = phantom::typeOf<long>();
static phantom::reflection::Type* phantom_type_ulong = phantom::typeOf<unsigned long>();
static phantom::reflection::Type* phantom_type_vector2f = phantom::typeOf<phantom::math::vector2<float>>();
static phantom::reflection::Type* phantom_type_vector3f = phantom::typeOf<phantom::math::vector3<float>>();
static phantom::reflection::Type* phantom_type_vector4f = phantom::typeOf<phantom::math::vector4<float>>();
static phantom::reflection::Type* phantom_type_vector2f_cr = phantom::typeOf< const phantom::math::vector2<float>&>();
static phantom::reflection::Type* phantom_type_vector3f_cr = phantom::typeOf<const phantom::math::vector3<float>&>();
static phantom::reflection::Type* phantom_type_vector4f_cr = phantom::typeOf<const phantom::math::vector4<float>&>();

static jit_type_t jit_type_phantom_signal_t = nullptr;
static jit_type_t jit_type_vector2f = nullptr;
static jit_type_t jit_type_vector3f = nullptr;
static jit_type_t jit_type_vector4f = nullptr;

#define JIT_PHANTOM_CALL_UNARY_INTRINSIC(type, name)\
    if(strcmp(function, #name) == 0)\
{\
    jit_intrinsic_descr_t desc;\
    desc.arg1_type = jit_type_##type;\
    desc.arg2_type = 0;\
    desc.return_type = jit_type_##type;\
    desc.ptr_result_type = 0;\
    return jit_insn_call_intrinsic(func, #name, jit_##type##_##name, &desc, (jit_value_t)args[0].value, 0);\
}

#define JIT_PHANTOM_CALL_BINARY_INTRINSIC(type, name)\
    if(strcmp(function, #name) == 0)\
{\
    jit_intrinsic_descr_t desc;\
    desc.arg1_type = jit_type_##type;\
    desc.arg2_type = jit_type_##type;\
    desc.return_type = jit_type_##type;\
    desc.ptr_result_type = 0;\
    return jit_insn_call_intrinsic(func, #name, jit_##type##_##name, &desc, (jit_value_t)args[0].value, (jit_value_t)args[1].value);\
}

#define JIT_PHANTOM_MAKE_PARAM(type) (jit_type_is_struct(jit_type_##type) \
    ? jit_type_void_ptr \
    : jit_type_##type)

#define JIT_PHANTOM_TYPE_OF_PARAM(type) (jit_type_is_struct(jit_type_##type) \
    ? (phantom_type_##type)->constType()->referenceType() \
    : phantom_type_##type)


#define JIT_PHANTOM_CONVERT_ARG(index, type)\
{\
    jit_value converted_value = jit_insn_phantom_implicit_cast(func, args[index], JIT_PHANTOM_TYPE_OF_PARAM(type));\
    if(converted_value.isNull()) return jit_value();\
    converted_args[index] = (jit_value_t)converted_value.value;\
}

#define JIT_PHANTOM_CALL_FUNC_1(type, rtype, name)\
    if(strcmp(function, #name) == 0)\
{\
    jit_value_t converted_args[1];\
    JIT_PHANTOM_CONVERT_ARG(0, type);\
    jit_type_t params[1] = {JIT_PHANTOM_MAKE_PARAM(type)};\
    return jit_insn_call_native(func, #name, jit_##type##_##name, jit_type_create_signature(jit_abi_stdcall, jit_type_##rtype, params, 1, 0), converted_args, 1, 0);\
}

#define JIT_PHANTOM_CALL_FUNC_1_RET_BY_REF(type, rtype, name)\
    if(strcmp(function, #name) == 0)\
    {\
    jit_value_t converted_args[1];\
    JIT_PHANTOM_CONVERT_ARG(0, type);\
    jit_type_t params[2] = {JIT_PHANTOM_MAKE_PARAM(type),jit_type_void_ptr};\
    jit_value_t temp = jit_value_create(func, jit_type_##rtype);\
    jit_value_set_local(temp);\
    jit_value_set_addressable(temp);\
    jit_value_t ex_args[2] = {converted_args[0], jit_insn_address_of(func, temp)};\
    jit_insn_call_native(func, #name, jit_##type##_##name, jit_type_create_signature(jit_abi_stdcall, jit_type_void, params, 2, 0), ex_args, 2, 0);\
    return temp;\
}

#define JIT_PHANTOM_CALL_FUNC_2(type0, type1, rtype, name)\
    if(strcmp(function, #name) == 0)\
    {\
    jit_value_t converted_args[2];\
    JIT_PHANTOM_CONVERT_ARG(0, type0);\
    JIT_PHANTOM_CONVERT_ARG(1, type1);\
    jit_type_t params[2] = {JIT_PHANTOM_MAKE_PARAM(type0), JIT_PHANTOM_MAKE_PARAM(type1)};\
    return jit_insn_call_native(func, #name, jit_##type0##_##type1##_##name, jit_type_create_signature(jit_abi_stdcall, jit_type_##rtype, params, 2, 0), converted_args, 2, 0);\
}

#define JIT_PHANTOM_CALL_FUNC_2_RET_BY_REF(type0, type1, rtype, name)\
    if(strcmp(function, #name) == 0)\
    {\
    jit_value_t converted_args[2];\
    JIT_PHANTOM_CONVERT_ARG(0, type0);\
    JIT_PHANTOM_CONVERT_ARG(1, type1);\
    jit_type_t params[3] = {JIT_PHANTOM_MAKE_PARAM(type0), JIT_PHANTOM_MAKE_PARAM(type1), jit_type_void_ptr};\
    jit_value_t temp = jit_value_create(func, jit_type_##rtype);\
    jit_value_set_local(temp);\
    jit_value_set_addressable(temp);\
    jit_value_t ex_args[3] = {converted_args[0], converted_args[1], jit_insn_address_of(func, temp)};\
    jit_insn_call_native(func, #name, jit_##type0##_##type1##_##name, jit_type_create_signature(jit_abi_stdcall, jit_type_void, params, 3, 0), ex_args, 3, 0);\
    return temp;\
}

#define JIT_PHANTOM_CALL_FUNC_3(type0, type1, type2, rtype, name)\
    if(strcmp(function, #name) == 0)\
    {\
    jit_value_t converted_args[3];\
    JIT_PHANTOM_CONVERT_ARG(0, type0);\
    JIT_PHANTOM_CONVERT_ARG(1, type1);\
    JIT_PHANTOM_CONVERT_ARG(2, type2);\
    jit_type_t params[3] = {JIT_PHANTOM_MAKE_PARAM(type0), JIT_PHANTOM_MAKE_PARAM(type1), JIT_PHANTOM_MAKE_PARAM(type2)};\
    return jit_insn_call_native(func, #name, jit_##type0##_##type1##_##type2##_##name, jit_type_create_signature(jit_abi_stdcall, jit_type_##rtype, params, 3, 0), converted_args, 3, 0);\
}

#define JIT_PHANTOM_CALL_FUNC_3_RET_BY_REF(type0, type1, type2, rtype, name)\
    if(strcmp(function, #name) == 0)\
    {\
    jit_value_t converted_args[3];\
    JIT_PHANTOM_CONVERT_ARG(0, type0);\
    JIT_PHANTOM_CONVERT_ARG(1, type1);\
    JIT_PHANTOM_CONVERT_ARG(2, type2);\
    jit_type_t params[4] = {JIT_PHANTOM_MAKE_PARAM(type0), JIT_PHANTOM_MAKE_PARAM(type1), JIT_PHANTOM_MAKE_PARAM(type2), jit_type_void_ptr};\
    jit_value_t temp = jit_value_create(func, jit_type_##rtype);\
    jit_value_set_local(temp);\
    jit_value_set_addressable(temp);\
    jit_value_t ex_args[4] = {converted_args[0], converted_args[1], converted_args[2], jit_insn_address_of(func, temp)};\
    jit_insn_call_native(func, #name, jit_##type0##_##type1##_##type2##_##name, jit_type_create_signature(jit_abi_stdcall, jit_type_void, params, 4, 0), ex_args, 4, 0);\
    return temp;\
}

#define JIT_PHANTOM_CALL_FUNC_4_RET_BY_REF(type0, type1, type2, type3, rtype, name)\
    if(strcmp(function, #name) == 0)\
    {\
    jit_value_t converted_args[4];\
    JIT_PHANTOM_CONVERT_ARG(0, type0);\
    JIT_PHANTOM_CONVERT_ARG(1, type1);\
    JIT_PHANTOM_CONVERT_ARG(2, type2);\
    JIT_PHANTOM_CONVERT_ARG(3, type3);\
    jit_type_t params[5] = {JIT_PHANTOM_MAKE_PARAM(type0), JIT_PHANTOM_MAKE_PARAM(type1), JIT_PHANTOM_MAKE_PARAM(type2), JIT_PHANTOM_MAKE_PARAM(type3), jit_type_void_ptr};\
    jit_value_t temp = jit_value_create(func, jit_type_##rtype);\
    jit_value_set_local(temp);\
    jit_value_set_addressable(temp);\
    jit_value_t ex_args[5] = {converted_args[0], converted_args[1], converted_args[2], converted_args[3], jit_insn_address_of(func, temp)};\
    jit_insn_call_native(func, #name, jit_##type0##_##type1##_##type2##_##type3##_##name, jit_type_create_signature(jit_abi_stdcall, jit_type_void, params, 5, 0), ex_args, 5, 0);\
    return temp;\
}
#define JIT_CALL_CONV __stdcall 

/// VECTOR2

void JIT_CALL_CONV jit_vector2f_normalize(const phantom::math::vector2<float>& vec, phantom::math::vector2<float>& out)
{
    out = vec.normalized();
}

float JIT_CALL_CONV jit_vector2f_length(const phantom::math::vector2<float>& vec)
{
    return vec.length();
}

float JIT_CALL_CONV jit_vector2f_length2(const phantom::math::vector2<float>& vec)
{
    return vec.lengthSquared();
}

/// VECTOR2 - VECTOR2

float JIT_CALL_CONV jit_vector2f_vector2f_distance(const phantom::math::vector2<float>& vec0, const phantom::math::vector2<float>& vec1)
{
    return vec0.distance(vec1);
}

float JIT_CALL_CONV jit_vector2f_vector2f_distance2(const phantom::math::vector2<float>& vec0, const phantom::math::vector2<float>& vec1)
{
    return (vec0-vec1).lengthSquared();
}

float JIT_CALL_CONV jit_vector2f_vector2f_cross(const phantom::math::vector2<float>& vec0, const phantom::math::vector2<float>& vec1)
{
    return vec0.cross(vec1);
}

float JIT_CALL_CONV jit_vector2f_vector2f_dot(const phantom::math::vector2<float>& vec0, const phantom::math::vector2<float>& vec1)
{
    return vec0.dot(vec1);
}

void JIT_CALL_CONV jit_vector2f_vector2f_add(const phantom::math::vector2<float>& vec0, const phantom::math::vector2<float>& vec1, phantom::math::vector2<float>& out)
{
    out = vec0 + vec1;
}

void JIT_CALL_CONV jit_vector2f_vector2f_sub(const phantom::math::vector2<float>& vec0, const phantom::math::vector2<float>& vec1, phantom::math::vector2<float>& out)
{
    out = vec0 - vec1;
}

void JIT_CALL_CONV jit_vector2f_vector2f_mul(const phantom::math::vector2<float>& vec0, const phantom::math::vector2<float>& vec1, phantom::math::vector2<float>& out)
{
    out = vec0 * vec1;
}

void JIT_CALL_CONV jit_vector2f_vector2f_div(const phantom::math::vector2<float>& vec0, const phantom::math::vector2<float>& vec1, phantom::math::vector2<float>& out)
{
    out = vec0 / vec1;
}

void JIT_CALL_CONV jit_vector2f_vector2f_reflect(const phantom::math::vector2<float>& i, const phantom::math::vector2<float>& n, phantom::math::vector2<float>& out)
{
    out = i - 2*n.dot(i) * n;
}

void JIT_CALL_CONV jit_vector2f_vector2f_vector4f(const phantom::math::vector2<float>& xy, const phantom::math::vector2<float>& zw, phantom::math::vector4<float>& out)
{
    out.x = xy.x;
    out.y = xy.y;
    out.z = zw.x;
    out.w = zw.y;
}

/// VECTOR2 - FLOAT

void JIT_CALL_CONV jit_vector2f_float32_add(const phantom::math::vector2<float>& vec0, float vec1, phantom::math::vector2<float>& out)
{
    out = vec0 + vec1;
}

void JIT_CALL_CONV jit_vector2f_float32_sub(const phantom::math::vector2<float>& vec0, float vec1, phantom::math::vector2<float>& out)
{
    out = vec0 - vec1;
}

void JIT_CALL_CONV jit_vector2f_float32_mul(const phantom::math::vector2<float>& vec0, float vec1, phantom::math::vector2<float>& out)
{
    out = vec0 * vec1;
}

void JIT_CALL_CONV jit_vector2f_float32_div(const phantom::math::vector2<float>& vec0, float vec1, phantom::math::vector2<float>& out)
{
    out = vec0 / vec1;
}
void JIT_CALL_CONV jit_vector2f_float32_rotate(const phantom::math::vector2<float>& vec, float angle, phantom::math::vector2<float>& out)
{
    out = rotate(vec, angle);
}

/// VECTOR3 - VECTOR3

void JIT_CALL_CONV jit_vector3f_vector3f_add(const phantom::math::vector3<float>& vec0, const phantom::math::vector3<float>& vec1, phantom::math::vector3<float>& out)
{
    out = vec0 + vec1;
}

void JIT_CALL_CONV jit_vector3f_vector3f_sub(const phantom::math::vector3<float>& vec0, const phantom::math::vector3<float>& vec1, phantom::math::vector3<float>& out)
{
    out = vec0 - vec1;
}

void JIT_CALL_CONV jit_vector3f_vector3f_mul(const phantom::math::vector3<float>& vec0, const phantom::math::vector3<float>& vec1, phantom::math::vector3<float>& out)
{
    out = vec0 * vec1;
}

void JIT_CALL_CONV jit_vector3f_vector3f_div(const phantom::math::vector3<float>& vec0, const phantom::math::vector3<float>& vec1, phantom::math::vector3<float>& out)
{
    out = vec0 / vec1;
}

/// VECTOR3 - FLOAT 

void JIT_CALL_CONV jit_vector3f_float32_add(const phantom::math::vector3<float>& vec0, float vec1, phantom::math::vector3<float>& out)
{
    out = vec0 + vec1;
}

void JIT_CALL_CONV jit_vector3f_float32_sub(const phantom::math::vector3<float>& vec0, float vec1, phantom::math::vector3<float>& out)
{
    out = vec0 - vec1;
}

void JIT_CALL_CONV jit_vector3f_float32_mul(const phantom::math::vector3<float>& vec0, float vec1, phantom::math::vector3<float>& out)
{
    out = vec0 * vec1;
}

void JIT_CALL_CONV jit_vector3f_float32_div(const phantom::math::vector3<float>& vec0, float vec1, phantom::math::vector3<float>& out)
{
    out = vec0 / vec1;
}

void JIT_CALL_CONV jit_vector3f_float32_vector4f(const phantom::math::vector3<float>& xyz, float w, phantom::math::vector4<float>& out)
{
    out.x = xyz.x;
    out.y = xyz.y;
    out.z = xyz.z;
    out.w = w;
}

/// VECTOR4 - VECTOR4

void JIT_CALL_CONV jit_vector4f_vector4f_add(const phantom::math::vector4<float>& vec0, const phantom::math::vector4<float>& vec1, phantom::math::vector4<float>& out)
{
    out = vec0 + vec1;
}

void JIT_CALL_CONV jit_vector4f_vector4f_sub(const phantom::math::vector4<float>& vec0, const phantom::math::vector4<float>& vec1, phantom::math::vector4<float>& out)
{
    out = vec0 - vec1;
}

void JIT_CALL_CONV jit_vector4f_vector4f_mul(const phantom::math::vector4<float>& vec0, const phantom::math::vector4<float>& vec1, phantom::math::vector4<float>& out)
{
    out = vec0 * vec1;
}

void JIT_CALL_CONV jit_vector4f_vector4f_div(const phantom::math::vector4<float>& vec0, const phantom::math::vector4<float>& vec1, phantom::math::vector4<float>& out)
{
    out = vec0 / vec1;
}

/// VECTOR4 - FLOAT

void JIT_CALL_CONV jit_vector4f_float32_add(const phantom::math::vector4<float>& vec0, float vec1, phantom::math::vector4<float>& out)
{
    out = vec0 + vec1;
}

void JIT_CALL_CONV jit_vector4f_float32_sub(const phantom::math::vector4<float>& vec0, float vec1, phantom::math::vector4<float>& out)
{
    out = vec0 - vec1;
}

void JIT_CALL_CONV jit_vector4f_float32_mul(const phantom::math::vector4<float>& vec0, float vec1, phantom::math::vector4<float>& out)
{
    out = vec0 * vec1;
}

void JIT_CALL_CONV jit_vector4f_float32_div(const phantom::math::vector4<float>& vec0, float vec1, phantom::math::vector4<float>& out)
{
    out = vec0 / vec1;
}

void JIT_CALL_CONV jit_float32_vector2f(float x, phantom::math::vector2<float>& out)
{
    out.x = x;
    out.y = x;
}

void JIT_CALL_CONV jit_float32_vector3f(float x, phantom::math::vector3<float>& out)
{
    out.x = x;
    out.y = x;
    out.z = x;
}

void JIT_CALL_CONV jit_float32_vector4f(float x, phantom::math::vector4<float>& out)
{
    out.x = x;
    out.y = x;
    out.w = x;
    out.z = x;
}

void JIT_CALL_CONV jit_float32_float32_vector2f(float x, float y, phantom::math::vector2<float>& out)
{
    out.x = x;
    out.y = y;
}

void JIT_CALL_CONV jit_vector2f_float32_vector3f(const phantom::math::vector2<float>& xy, float z, phantom::math::vector3<float>& out)
{
    out.x = xy.x;
    out.y = xy.y;
    out.z = z;
}

void JIT_CALL_CONV jit_float32_float32_float32_vector3f(float x, float y, float z, phantom::math::vector3<float>& out)
{
    out.x = x;
    out.y = y;
    out.z = z;
}

void JIT_CALL_CONV jit_vector2f_float32_float32_vector4f(const phantom::math::vector2<float>& xy, float z, float w, phantom::math::vector4<float>& out)
{
    out.x = xy.x;
    out.y = xy.y;
    out.z = z;
    out.w = w;
}

void JIT_CALL_CONV jit_float32_float32_float32_float32_vector4f(float x, float y, float z, float w, phantom::math::vector4<float>& out)
{
    out.x = x;
    out.y = y;
    out.z = z;
    out.w = w;
}

void JIT_CALL_CONV jit_vector2f_vector2f_float32_refract(phantom::math::vector2<float> i, phantom::math::vector2<float> n, float eta, phantom::math::vector2<float>& out)
{
    float ndi = n.dot(i);
    float k = 1.f - eta * eta * (1.f - ndi * ndi);
    if (k < 0.f)
        out = phantom::math::vector2<float>(0,0);   
    else
        out = eta * i - (eta * ndi + sqrt(k)) * n;
}

jit_value jit_phantom_math_unary_intrinsic_float32( jit_function_t func, const char* intrinsic, jit_value operand )
{
    return jit_value();
}

jit_value jit_phantom_math_func_float32( jit_function_t func, const char* function, jit_value args[1] )
{
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float32, sin)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float32, cos)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float32, abs)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float32, tan)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float32, atan)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float32, asin)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float32, acos)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float32, sqrt)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float32, cosh)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float32, exp)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float32, log)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float32, log10)
    JIT_PHANTOM_CALL_FUNC_1_RET_BY_REF(float32, vector2f, vector2f);
    JIT_PHANTOM_CALL_FUNC_1_RET_BY_REF(float32, vector3f, vector3f);
    JIT_PHANTOM_CALL_FUNC_1_RET_BY_REF(float32, vector4f, vector4f);
    return jit_value();
}

jit_value jit_phantom_math_unary_intrinsic_float64( jit_function_t func, const char* intrinsic, jit_value operand )
{
    return jit_value();
}

jit_value jit_phantom_math_func_float64( jit_function_t func, const char* function, jit_value args[1])
{
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float64, sin)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float64, cos)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float64, abs)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float64, tan)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float64, atan)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float64, asin)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float64, acos)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float64, sqrt)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float64, cosh)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float64, exp)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float64, log)
    JIT_PHANTOM_CALL_UNARY_INTRINSIC(float64, log10)
    return jit_value();
}


jit_value jit_phantom_math_binary_intrinsic_float32_float32( jit_function_t func, const char* intrinsic, jit_value l, jit_value r)
{
    return jit_value();
}

jit_value jit_phantom_math_binary_intrinsic_float64_float64( jit_function_t func, const char* intrinsic, jit_value l, jit_value r )
{
    return jit_value();
}

jit_value jit_phantom_math_func_vector2f( jit_function_t func, const char* function, jit_value* args )
{
    JIT_PHANTOM_CALL_FUNC_1(vector2f, float32, length)
    JIT_PHANTOM_CALL_FUNC_1(vector2f, float32, length2)
    JIT_PHANTOM_CALL_FUNC_1_RET_BY_REF(vector2f, vector2f, normalize)
    return jit_value();
}

jit_value jit_phantom_math_func_float32_float32( jit_function_t func, const char* function, jit_value args[2] )
{
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(float32, pow)
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(float32, atan2)
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(float32, min)
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(float32, max)
    JIT_PHANTOM_CALL_FUNC_2_RET_BY_REF(float32, float32, vector2f, vector2f);
    return jit_value(); 
}

jit_value jit_phantom_math_func_float64_float64( jit_function_t func, const char* function, jit_value args[2] )
{
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(float64, pow)
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(float64, atan2)
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(float64, min)
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(float64, max)
    return jit_value(); 
}

jit_value jit_phantom_math_func_int_int( jit_function_t func, const char* function, jit_value args[2] )
{
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(int, min)
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(int, max)
    return jit_value(); 
}

jit_value jit_phantom_math_func_uint_uint( jit_function_t func, const char* function, jit_value args[2] )
{
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(uint, min)
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(uint, max)
    return jit_value(); 
}

jit_value jit_phantom_math_func_long_long( jit_function_t func, const char* function, jit_value args[2] )
{
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(long, min)
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(long, max)
    return jit_value(); 
}

jit_value jit_phantom_math_func_ulong_ulong( jit_function_t func, const char* function, jit_value args[2] )
{
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(ulong, min)
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(ulong, max)
    return jit_value(); 
}

jit_value jit_phantom_math_func_float32_float32_float32( jit_function_t func, const char* function, jit_value args[3] )
{
    JIT_PHANTOM_CALL_FUNC_3_RET_BY_REF(float32, float32, float32, vector3f, vector3f);
    return jit_value(); 
}

jit_value jit_phantom_math_func_vector2f_float32_float32( jit_function_t func, const char* function, jit_value args[3] )
{
    JIT_PHANTOM_CALL_FUNC_3_RET_BY_REF(vector2f, float32, float32, vector4f, vector4f);
    return jit_value(); 
}

jit_value jit_phantom_math_func_float32_float32_float32_float32( jit_function_t func, const char* function, jit_value args[4] )
{
    JIT_PHANTOM_CALL_FUNC_4_RET_BY_REF(float32, float32, float32, float32, vector4f, vector4f);
    return jit_value(); 
}

jit_value jit_phantom_math_func_vector2f_vector2f( jit_function_t func, const char* function, jit_value args[2] )
{
    JIT_PHANTOM_CALL_FUNC_2(vector2f, vector2f, float32, distance)
    JIT_PHANTOM_CALL_FUNC_2(vector2f, vector2f, float32, distance2)
    JIT_PHANTOM_CALL_FUNC_2(vector2f, vector2f, float32, cross)
    JIT_PHANTOM_CALL_FUNC_2(vector2f, vector2f, float32, dot)
    JIT_PHANTOM_CALL_FUNC_2_RET_BY_REF(vector2f, vector2f, vector4f, vector4f);
    JIT_PHANTOM_CALL_FUNC_2_RET_BY_REF(vector2f, vector2f, vector2f, reflect);
    return jit_value(); 
}

jit_value jit_phantom_math_func_vector2f_float32( jit_function_t func, const char* function, jit_value args[2] )
{
    JIT_PHANTOM_CALL_FUNC_2_RET_BY_REF(vector2f, float32, vector3f, vector3f);
    JIT_PHANTOM_CALL_FUNC_2_RET_BY_REF(vector2f, float32, vector2f, rotate);
    return jit_value(); 
}

jit_value jit_phantom_math_func_vector3f_float32( jit_function_t func, const char* function, jit_value args[2] )
{
    JIT_PHANTOM_CALL_FUNC_2_RET_BY_REF(vector3f, float32, vector4f, vector4f);
    return jit_value(); 
}

jit_value jit_phantom_math_func_vector2f_vector2f_float32( jit_function_t func, const char* function, jit_value args[3] )
{
    JIT_PHANTOM_CALL_FUNC_3_RET_BY_REF(vector2f, vector2f, float32, vector2f, refract);
    return jit_value(); 
}

jit_value jit_phantom_math_func(jit_function_t func, const char* function, jit_value v0)
{
    jit_value args[1] = {v0};
    if(v0.type == phantom_type_vector2f || v0.type == phantom_type_vector2f_cr)
    {
        return jit_phantom_math_func_vector2f(func, function, args);
    } 
    else 
    {
        if(v0.type == phantom_type_float32)
        {
            return jit_phantom_math_func_float32(func, function, args);
        }
        else if(v0.type == phantom_type_float64)
        {
            return jit_phantom_math_func_float64(func, function, args);
        }
        else 
        {
            args[0] = jit_insn_convert(func, (jit_value_t)v0.value, jit_type_float32, 0);
            return jit_phantom_math_func_float32(func, function, args);
        }
    }
    return jit_value();
}

jit_value jit_phantom_math_func(jit_function_t func, const char* function, jit_value v0, jit_value v1)
{
    jit_value value;
    jit_value args[2] = {v0, v1};
    if(v0.type == phantom_type_vector2f || v0.type == phantom_type_vector2f_cr)
    {
        if(v1.type == phantom_type_vector2f || v1.type == phantom_type_vector2f_cr)
        {
            value = jit_phantom_math_func_vector2f_vector2f(func, function, args);
        }
        else
        {
            jit_value args[2] = {v0, jit_insn_convert(func, (jit_value_t)v1.value, jit_type_float32, 0)};
            value = jit_phantom_math_func_vector2f_float32(func, function, args);
        }
    } 
    else if(v0.type == phantom_type_vector3f || v0.type == phantom_type_vector3f_cr)
    {
        jit_value args[2] = {v0, jit_insn_convert(func, (jit_value_t)v1.value, jit_type_float32, 0)};
        value = jit_phantom_math_func_vector3f_float32(func, function, args);
    }
    else if(v0.type == phantom_type_float32 && v1.type == phantom_type_float32)
    {
        value = jit_phantom_math_func_float32_float32(func, function, args);
    }
    else if(v0.type == phantom_type_float64 && v1.type == phantom_type_float64)
    {
        value = jit_phantom_math_func_float64_float64(func, function, args);
    }
    else if(v0.type == phantom_type_int && v1.type == phantom_type_int)
    {
        value = jit_phantom_math_func_int_int(func, function, args);
    }
    else if(v0.type == phantom_type_uint && v1.type == phantom_type_uint)
    {
        value = jit_phantom_math_func_uint_uint(func, function, args);
    }
    else if(v0.type == phantom_type_long && v1.type == phantom_type_long)
    {
        value = jit_phantom_math_func_long_long(func, function, args);
    }
    else if(v0.type == phantom_type_ulong && v1.type == phantom_type_ulong)
    {
        value = jit_phantom_math_func_ulong_ulong(func, function, args);
    }
    else
    {
        if(v0.type == phantom_type_float64 || v1.type == phantom_type_float64)
        {
            jit_value args[2] = {jit_insn_convert(func, (jit_value_t)v0.value, jit_type_float64, 0), jit_insn_convert(func, (jit_value_t)v1.value, jit_type_float64, 0)};
            value = jit_phantom_math_func_float64_float64(func, function, args);
        }
        else if(v0.type == phantom_type_float32 || v1.type == phantom_type_float32)
        {
            jit_value args[2] = {jit_insn_convert(func, (jit_value_t)v0.value, jit_type_float32, 0), jit_insn_convert(func, (jit_value_t)v1.value, jit_type_float32, 0)};
            value = jit_phantom_math_func_float32_float32(func, function, args);
        }
        else 
        {
            jit_value args[2] = {jit_insn_convert(func, (jit_value_t)v0.value, jit_type_int, 0), jit_insn_convert(func, (jit_value_t)v1.value, jit_type_int, 0)};
            value = jit_phantom_math_func_int_int(func, function, args);
        }
    }
    if(value.isNull())
    {
        jit_value args[2] = {jit_insn_convert(func, (jit_value_t)v0.value, jit_type_float32, 0), jit_insn_convert(func, (jit_value_t)v1.value, jit_type_float32, 0)};
        return jit_phantom_math_func_float32_float32(func, function, args);
    }
    return value;
}

jit_value jit_phantom_math_func(jit_function_t func, const char* function, jit_value v0, jit_value v1, jit_value v2)
{
    if(v0.type == phantom_type_vector2f || v0.type == phantom_type_vector2f_cr)
    {
        if (v1.type == phantom_type_vector2f || v1.type == phantom_type_vector2f_cr)
        {
            jit_value args[3] = {v0, v1, jit_insn_convert(func, (jit_value_t)v2.value, jit_type_float32, 0) };
            return jit_phantom_math_func_vector2f_vector2f_float32(func, function, args);
        } 
        else 
        {
            jit_value args[3] = {v0, jit_insn_convert(func, (jit_value_t)v1.value, jit_type_float32, 0), jit_insn_convert(func, (jit_value_t)v2.value, jit_type_float32, 0) };
            return jit_phantom_math_func_vector2f_float32_float32(func, function, args);
        }
    }
    else 
    {
        jit_value args[3] = {
            jit_insn_convert(func, (jit_value_t)v0.value, jit_type_float32, 0)
            , jit_insn_convert(func, (jit_value_t)v1.value, jit_type_float32, 0)
            , jit_insn_convert(func, (jit_value_t)v2.value, jit_type_float32, 0) };
        return jit_phantom_math_func_float32_float32_float32(func, function, args);
    }
    return jit_value();
}

jit_value jit_phantom_math_func(jit_function_t func, const char* function, jit_value v0, jit_value v1, jit_value v2, jit_value v3)
{
    jit_value args[4] = {
        jit_insn_convert(func, (jit_value_t)v0.value, jit_type_float32, 0)
        , jit_insn_convert(func, (jit_value_t)v1.value, jit_type_float32, 0)
        , jit_insn_convert(func, (jit_value_t)v2.value, jit_type_float32, 0) 
        , jit_insn_convert(func, (jit_value_t)v3.value, jit_type_float32, 0)};
        return jit_phantom_math_func_float32_float32_float32_float32(func, function, args);
}

jit_type_t toJitType( Type* a_pType ) 
{
    if(jit_type_phantom_signal_t == nullptr)
    {
        // signal
        {
            jit_type_t t0 = jit_type_int;
            jit_type_phantom_signal_t = jit_type_create_struct(&t0, 1, 0);
        }
        // vector2f
        {
            jit_type_t t[2] = { jit_type_float32, jit_type_float32} ;
            jit_type_vector2f = jit_type_create_struct(t, 2, 0);
        }
        // vector3f
        {
            jit_type_t t[3] = { jit_type_float32, jit_type_float32, jit_type_float32} ;
            jit_type_vector3f = jit_type_create_struct(t, 3, 0);
        }
        // vector4f
        {
            jit_type_t t[4] = { jit_type_float32, jit_type_float32, jit_type_float32, jit_type_float32} ;
            jit_type_vector4f = jit_type_create_struct(t, 4, 0);
        }
    }
    while(a_pType->isConstType())
    {
        a_pType = a_pType->removeConst();
    }
    if(a_pType->asEnum()) 
    {
        switch(a_pType->getSize())
        {
        case 1: return jit_type_sbyte;
        case 2: return jit_type_short;
        case 4: return jit_type_int;
        case 8: return jit_type_long;
        default: o_assert(false);
        }
    }
    if(a_pType->isDataPointerType()) return jit_type_void_ptr;
    if(a_pType->isReferenceType()) return jit_type_void_ptr;
    if(a_pType == phantom::typeOf<phantom::signal_t>()) return jit_type_phantom_signal_t;
    if(a_pType == phantom::typeOf<phantom::math::vector2<float>>()) return jit_type_vector2f;
    if(a_pType == phantom::typeOf<phantom::math::vector3<float>>()) return jit_type_vector3f;
    if(a_pType == phantom::typeOf<phantom::math::vector4<float>>()) return jit_type_vector4f;
    if(a_pType == phantom::typeOf<bool>()) return jit_type_ubyte;
#if defined(__CHAR_UNSIGNED__)
    if(a_pType == phantom::typeOf<char>()) return jit_type_ubyte;
#else
    if(a_pType == phantom::typeOf<char>()) return jit_type_sbyte;
#endif
    if(a_pType == phantom::typeOf<phantom::schar>()) return jit_type_sbyte;
    if(a_pType == phantom::typeOf<phantom::uchar>()) return jit_type_ubyte;
    if(a_pType == phantom::typeOf<short>()) return jit_type_short;
    if(a_pType == phantom::typeOf<phantom::ushort>()) return jit_type_ushort;
    if(a_pType == phantom::typeOf<int>()) return jit_type_int;
    if(a_pType == phantom::typeOf<phantom::uint>()) return jit_type_uint;
    if(a_pType == phantom::typeOf<long>()) 
    {
        if(sizeof(long) == 8) return jit_type_long;
        else if(sizeof(long) == 2) return jit_type_short;
        else return jit_type_int;
    }
    if(a_pType == phantom::typeOf<phantom::ulong>()) 
    {
        if(sizeof(unsigned long) == 8)  return jit_type_ulong;
        else if(sizeof(unsigned long) == 2)  return jit_type_ushort;
        else return jit_type_uint;
    }
    if(a_pType == phantom::typeOf<phantom::longlong>()) return jit_type_long;
    if(a_pType == phantom::typeOf<phantom::ulonglong>()) return jit_type_ulong;
    if(a_pType == phantom::typeOf<float>()) return jit_type_float32;
    if(a_pType == phantom::typeOf<double>()) return jit_type_float64;
    if(a_pType == phantom::typeOf<phantom::longdouble>()) return jit_type_nfloat;
    if(a_pType == phantom::typeOf<void>()) return jit_type_void;
    o_assert(false, "Given phantom type cannot be converted to jit type");
    return jit_type_void;
}

jit_type_t toJitSignature( EJitAbi abi, Signature* a_pSignature ) 
{
    bool isThisCall = (abi == e_JitAbi_thiscall);
    size_t i = isThisCall;
    size_t count = a_pSignature->getParameterCount() + isThisCall;
    jit_type_t* params = count ? o_allocate_n(count, jit_type_t) : nullptr;
    for(;i<count;++i)
    {
        params[i] = toJitType(a_pSignature->getParameterType(i-isThisCall));
    }
    if(isThisCall)
    {
        params[0] = jit_type_void_ptr;
    }
    jit_type_t t = jit_type_create_signature((jit_abi_t)abi, toJitType(a_pSignature->getReturnType()), params, count, 0);
    if(params)
    {
        o_deallocate_n(params, count, jit_type_t);
    }
    return t;
}

Type* fromJitType( jit_type_t type ) 
{
    if(type == jit_type_vector2f) return phantom::typeOf<phantom::math::vector2<float>>();
    if(type == jit_type_vector3f) return phantom::typeOf<phantom::math::vector3<float>>();
    if(type == jit_type_vector4f) return phantom::typeOf<phantom::math::vector4<float>>();
    int kind = jit_type_get_kind(jit_type_remove_tags(type));
    switch(kind)
    {
    case JIT_TYPE_VOID			: return phantom::typeOf<void>();	
    case JIT_TYPE_SBYTE			: return phantom::typeOf<signed char>();	
    case JIT_TYPE_UBYTE			: return phantom::typeOf<unsigned char>();	
    case JIT_TYPE_SHORT			: return phantom::typeOf<short>();	
    case JIT_TYPE_USHORT		: return phantom::typeOf<unsigned short>();	
    case JIT_TYPE_INT			: return phantom::typeOf<int>();	
    case JIT_TYPE_UINT			: return phantom::typeOf<unsigned int>();	
    case JIT_TYPE_NINT			: return phantom::typeOf<int>();	// replace by a "unsigned" size_t
    case JIT_TYPE_NUINT			: return phantom::typeOf<size_t>();	
    case JIT_TYPE_LONG			: return phantom::typeOf<long long>();	
    case JIT_TYPE_ULONG			: return phantom::typeOf<unsigned long long>();	
    case JIT_TYPE_FLOAT32		: return phantom::typeOf<float>();	
    case JIT_TYPE_FLOAT64		: return phantom::typeOf<double>();	
    case JIT_TYPE_NFLOAT		: return phantom::typeOf<long double>();			
    case JIT_TYPE_PTR			: return phantom::typeOf<void*>();	
    case 10047                  : return phantom::typeOf<int>();	

    case JIT_TYPE_INVALID		: 	
    case JIT_TYPE_STRUCT		: 
    case JIT_TYPE_UNION			: 
    case JIT_TYPE_SIGNATURE		: 
    case JIT_TYPE_FIRST_TAGGED	: 
        o_assert(false, "Given phantom type cannot be converted from jit type");
    }
    return nullptr;
}

jit_function jitFunctionFromMemoryAddressEnd( byte* a_pAddress )
{
    for(auto it = sm_FromJitFunction.begin(); it != sm_FromJitFunction.end(); ++it)
    {
        JitSubroutine* pCompiled = it->second;
        if(pCompiled->asSubroutine()->getMemoryEnd() == a_pAddress)
        {
            return jit_function(it->first);
        }
    }
    return jit_function();
}

void registerJitFunction( jit_function func, class JitSubroutine* a_pJitSubroutine)
{
    sm_FromJitFunction[func.function] = a_pJitSubroutine;
}

void unregisterJitFunction( jit_function func )
{
    sm_FromJitFunction.erase(func.function);
}

o_namespace_end(phantom, reflection, jit)