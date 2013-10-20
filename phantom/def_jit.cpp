#include "phantom/phantom.h"
#include "phantom/math/math.h"
#include "def_jit.h"

o_register(jit_phantom_value_t);

static jit_type_t jit_type_phantom_signal_t = nullptr;
static jit_type_t jit_type_vector2f = nullptr;
static jit_type_t jit_type_vector3f = nullptr;
static jit_type_t jit_type_vector4f = nullptr;


o_jit_export jit_type_t jit_type_from_phantom_type( phantom::reflection::Type* a_pType )
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

o_jit_export phantom::reflection::Type* jit_type_to_phantom_type( jit_type_t type )
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

o_jit_export jit_type_t jit_type_from_phantom_signature( jit_abi_t abi, phantom::reflection::Signature* a_pSignature )
{
    size_t i = (abi == jit_abi_thiscall);
    size_t count = a_pSignature->getParameterCount() + (abi == jit_abi_thiscall);
    jit_type_t* params = count ? o_allocate_n(count, jit_type_t) : nullptr;
    for(;i<count;++i)
    {
        params[i] = jit_type_from_phantom_type(a_pSignature->getParameterType(i-(abi == jit_abi_thiscall)));
    }
    if((abi == jit_abi_thiscall))
    {
        params[0] = jit_type_void_ptr;
    }
    jit_type_t t = jit_type_create_signature(abi, jit_type_from_phantom_type(a_pSignature->getReturnType()), params, count, 0);
    if(params)
    {
        o_deallocate_n(params, count, jit_type_t);
    }
    return t;
}

o_jit_export jit_phantom_value_t jit_insn_phantom_implicit_cast( jit_function_t func, phantom::reflection::Type* a_pDestType, jit_phantom_value_t value )
{
    if(a_pDestType == value.type) return jit_phantom_value_t(value.value, a_pDestType);
    if(!value.type->isConvertibleTo(a_pDestType)) 
        return jit_phantom_value_t();

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
                if(offset == 0xffffffff) return jit_phantom_value_t();
                if(offset == 0) return jit_phantom_value_t(value.value, a_pDestType);
                return jit_phantom_value_t(jit_insn_add_relative(func, value, offset), a_pDestType);
            }
            else
            {
                return jit_phantom_value_t();
            }
        }
        else 
        {
            return jit_phantom_value_t();
        }
    }
    // TODO fix that shitty triple test
    else if(a_pDestType->isArithmeticType() AND value.type->isArithmeticType())
    {
        return jit_phantom_value_t(jit_insn_convert(func, value.value, jit_type_from_phantom_type(a_pDestType), 1), a_pDestType);
    }
    else if(a_pDestType->isIntegralType() AND value.type->isArithmeticType())
    {
        return jit_phantom_value_t(jit_insn_convert(func, value.value, jit_type_from_phantom_type(a_pDestType), 1), a_pDestType);
    }
    else if(a_pDestType->isArithmeticType() AND value.type->isIntegralType())
    {
        return jit_phantom_value_t(jit_insn_convert(func, value.value, jit_type_from_phantom_type(a_pDestType), 1), a_pDestType);
    }
    else if(a_pDestType->isReferenceType() AND NOT(value.type->isReferenceType()))
    {
        /// Convert from value to reference => address value
        if(jit_value_is_addressable(value)) 
        {
            return jit_phantom_value_t(jit_insn_address_of(func, value.value), a_pDestType);
        }
        else if(a_pDestType->asReferenceType()->getReferencedType()->isConstType())
        {
            jit_value_t temp_value = jit_value_create(func, jit_type_from_phantom_type(a_pDestType->asReferenceType()->getReferencedType())) ;
            jit_value_set_addressable(temp_value);
            int result = jit_insn_store(func, temp_value, value.value);
            o_assert(result);
            return jit_phantom_value_t(jit_insn_address_of(func, temp_value), a_pDestType);
        }
    }
    else if(NOT(a_pDestType->isReferenceType()) AND value.type->isReferenceType())
    {
        /// Convert from reference to value (dereference) => get value content
        return jit_insn_load_relative(func, value.value, 0, jit_type_from_phantom_type(a_pDestType));
    }
    return jit_phantom_value_t();
}

o_jit_export jit_phantom_value_t jit_insn_phantom_cast( jit_function_t func, phantom::reflection::Type* dest, jit_phantom_value_t value )
{
    jit_phantom_value_t implicit_cast_result = jit_insn_phantom_implicit_cast(func, dest, value);
    if(NOT(implicit_cast_result.isNull()))
    {
        return implicit_cast_result;
    }
    o_assert(NOT(value.type->isDataPointerType()) || dest->isDataPointerType(), " src is ptr => dest is ptr, or something is wrong in isConvertibleTo");
    if(dest->isDataPointerType())
    {
        o_assert(value.type->isDataPointerType());
        phantom::reflection::Type* pDestPointedType = dest->asDataPointerType()->getPointedType();
        phantom::reflection::Type* pSrcPointedType = value.type->asDataPointerType()->getPointedType();
        if(pDestPointedType->isClass() AND pSrcPointedType->isClass())
        {
            // Down cast
            size_t offset = pDestPointedType->asClass()->getSuperClassOffsetCascade(pSrcPointedType->asClass());
            if(offset == 0xffffffff) return jit_phantom_value_t();
            return jit_phantom_value_t(jit_insn_add_relative(func, value, -(int)offset), dest);
        }
        else 
        {
            return jit_phantom_value_t();
        }
    }
    // Other cases should have be done in implicit cast
    return jit_phantom_value_t();
}

o_jit_export jit_phantom_value_t jit_insn_phantom_eq( jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r )
{
    return jit_phantom_value_t(jit_insn_eq(func, l.value, r.value), phantom::typeOf<bool>());
}

o_jit_export jit_phantom_value_t jit_insn_phantom_ne( jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r )
{
    return jit_phantom_value_t(jit_insn_ne(func, l.value, r.value), phantom::typeOf<bool>());
}

o_jit_export jit_phantom_value_t jit_insn_phantom_lt( jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r )
{
    return jit_phantom_value_t(jit_insn_lt(func, l.value, r.value), phantom::typeOf<bool>());
}

o_jit_export jit_phantom_value_t jit_insn_phantom_gt( jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r )
{
    return jit_phantom_value_t(jit_insn_gt(func, l.value, r.value), phantom::typeOf<bool>());
}

o_jit_export jit_phantom_value_t jit_insn_phantom_ge( jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r )
{
    return jit_phantom_value_t(jit_insn_ge(func, l.value, r.value), phantom::typeOf<bool>());
}

o_jit_export jit_phantom_value_t jit_insn_phantom_le( jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r )
{
    return jit_phantom_value_t(jit_insn_le(func, l.value, r.value), phantom::typeOf<bool>());
}

o_jit_export jit_phantom_value_t jit_insn_phantom_add( jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r )
{
    return jit_insn_add(func, l.value, r.value);
}

o_jit_export jit_phantom_value_t jit_insn_phantom_sub( jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r )
{
    return jit_insn_sub(func, l.value, r.value);
}

o_jit_export jit_phantom_value_t jit_insn_phantom_mul( jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r )
{
    return jit_insn_mul(func, l.value, r.value);
}

o_jit_export jit_phantom_value_t jit_insn_phantom_div( jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r )
{
    return jit_insn_div(func, l.value, r.value);
}

o_jit_export jit_phantom_value_t jit_insn_phantom_shr( jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r )
{
    return jit_insn_shr(func, l.value, r.value);
}

o_jit_export jit_phantom_value_t jit_insn_phantom_shl( jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r )
{
    //if(NOT(l.type->isIntegralType()) || NOT(r.type->isIntegralType())) return jit_phantom_value_t();
    return jit_insn_shl(func, l.value, r.value);
}

o_jit_export jit_phantom_value_t jit_insn_phantom_and( jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r )
{
    return jit_insn_and(func, l.value, r.value);
}

o_jit_export jit_phantom_value_t jit_insn_phantom_rem( jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r )
{
    return jit_insn_rem(func, l.value, r.value);
}

o_jit_export jit_phantom_value_t jit_insn_phantom_or( jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r )
{
    return jit_insn_or(func, l.value, r.value);
}

o_jit_export jit_phantom_value_t jit_insn_phantom_xor( jit_function_t func, jit_phantom_value_t l, jit_phantom_value_t r )
{
    return jit_insn_xor(func, l.value, r.value) ;
}

o_jit_export jit_phantom_value_t jit_insn_phantom_not( jit_function_t func, jit_phantom_value_t value )
{
    return jit_insn_not(func, value);
}

o_jit_export void jit_value_phantom_create_1_constant( jit_constant_t& constant )
{
    if(constant.type == jit_type_int)
        constant.un.int_value = 1;
    else if(constant.type == jit_type_uint)
        constant.un.uint_value = 1;
    else if(constant.type == jit_type_nint)
        constant.un.nint_value = 1;
    else if(constant.type == jit_type_nuint)
        constant.un.nuint_value = 1;
    else if(constant.type == jit_type_long)
        constant.un.long_value = 1;
    else if(constant.type == jit_type_ulong)
        constant.un.ulong_value = 1;
    else if(constant.type == jit_type_float32)
        constant.un.float64_value = 1.f;
    else if(constant.type == jit_type_float64)
        constant.un.float64_value = 1.0;
    else if(constant.type == jit_type_nfloat)
        constant.un.nfloat_value = 1.0;
    else if(constant.type == jit_type_void
        || constant.type == jit_type_void_ptr
        || constant.type == jit_type_sbyte
        || constant.type == jit_type_ubyte
        || constant.type == jit_type_short
        || constant.type == jit_type_ushort)
    {
        o_assert(false, "Cannot increment this type or type not allowed");
    }
}

o_jit_export jit_phantom_value_t jit_insn_phantom_neg( jit_function_t func, jit_phantom_value_t op )
{
    if(NOT(op.type->isArithmeticType())) 
        return jit_phantom_value_t();
    return jit_insn_neg(func, op.value);
}

o_jit_export jit_phantom_value_t jit_phantom_math_operation_real_real( jit_function_t func, char op, jit_phantom_value_t l, jit_phantom_value_t r )
{
    switch(op)
    {
    case '+':
        return jit_insn_phantom_add(func, l, r);
    case '-':
        return jit_insn_phantom_sub(func, l, r);
    case '*':
        return jit_insn_phantom_mul(func, l, r);
    case '/':
        return jit_insn_phantom_div(func, l, r);
    }
    return jit_phantom_value_t();
}

o_jit_export jit_phantom_value_t jit_phantom_math_operation_vector2f_real( jit_function_t func, char op, jit_phantom_value_t l, jit_phantom_value_t r )
{
    jit_type_t type = jit_value_get_type(l.value);
    jit_value_t result = jit_value_create(func, type);
    jit_type_t componentType = jit_type_get_field(type, 0);
    jit_value_set_addressable(result);
    jit_value_set_local(result);
    jit_nuint xOffset = jit_type_get_offset(type, 0);
    jit_nuint yOffset = jit_type_get_offset(type, 1);
    // distribute operation to each component x/y
    jit_value_t newX = jit_phantom_math_operation_real_real(func, op, jit_insn_load_relative(func, jit_insn_address_of(func, l), xOffset, componentType), r);
    jit_value_t newY = jit_phantom_math_operation_real_real(func, op, jit_insn_load_relative(func, jit_insn_address_of(func, l), yOffset, componentType), r);
    jit_insn_store_relative(func, jit_insn_address_of(func, result), yOffset, newX);
    jit_insn_store_relative(func, jit_insn_address_of(func, result), yOffset, newY);
    return result;
}

o_jit_export jit_phantom_value_t jit_phantom_math_operation_vector2f_vector2f( jit_function_t func, char op, jit_phantom_value_t l, jit_phantom_value_t r )
{
    jit_type_t type = jit_value_get_type(l.value);
    jit_value_t result = jit_value_create(func, type);
    jit_type_t componentType = jit_type_get_field(type, 0);
    jit_value_set_addressable(result);
    jit_value_set_local(result);
    jit_nuint xOffset = jit_type_get_offset(type, 0);
    jit_nuint yOffset = jit_type_get_offset(type, 1);
    // distribute operation to each component x/y
    jit_value_t newX = jit_phantom_math_operation_real_real(func, op, jit_insn_load_relative(func, jit_insn_address_of(func, l), xOffset, componentType), jit_insn_load_relative(func, jit_insn_address_of(func, r), xOffset, componentType));
    jit_value_t newY = jit_phantom_math_operation_real_real(func, op, jit_insn_load_relative(func, jit_insn_address_of(func, l), yOffset, componentType), jit_insn_load_relative(func, jit_insn_address_of(func, r), yOffset, componentType));
    jit_insn_store_relative(func, jit_insn_address_of(func, result), yOffset, newX);
    jit_insn_store_relative(func, jit_insn_address_of(func, result), yOffset, newY);
    return result;
}

o_jit_export jit_phantom_value_t jit_phantom_math_operation_vector3f_real( jit_function_t func, char op, jit_phantom_value_t l, jit_phantom_value_t r )
{
    jit_type_t type = jit_value_get_type(l.value);
    jit_value_t result = jit_value_create(func, type);
    jit_type_t componentType = jit_type_get_field(type, 0);
    jit_value_set_addressable(result);
    jit_value_set_local(result);
    jit_nuint xOffset = jit_type_get_offset(type, 0);
    jit_nuint yOffset = jit_type_get_offset(type, 1);
    jit_nuint zOffset = jit_type_get_offset(type, 2);
    // distribute operation to each component x/y
    jit_value_t newX = jit_phantom_math_operation_real_real(func, op, jit_insn_load_relative(func, jit_insn_address_of(func, l), xOffset, componentType), r);
    jit_value_t newY = jit_phantom_math_operation_real_real(func, op, jit_insn_load_relative(func, jit_insn_address_of(func, l), yOffset, componentType), r);
    jit_value_t newZ = jit_phantom_math_operation_real_real(func, op, jit_insn_load_relative(func, jit_insn_address_of(func, l), zOffset, componentType), r);
    jit_insn_store_relative(func, jit_insn_address_of(func, result), xOffset, newX);
    jit_insn_store_relative(func, jit_insn_address_of(func, result), yOffset, newY);
    jit_insn_store_relative(func, jit_insn_address_of(func, result), zOffset, newZ);
    return result;
}

o_jit_export jit_phantom_value_t jit_phantom_math_operation_vector3f_vector3f( jit_function_t func, char op, jit_phantom_value_t l, jit_phantom_value_t r )
{
    jit_type_t type = jit_value_get_type(l.value);
    jit_value_t result = jit_value_create(func, jit_type_vector3f);
    jit_type_t componentType = jit_type_get_field(type, 0);
    jit_value_set_addressable(result);
    jit_value_set_local(result);
    jit_nuint xOffset = jit_type_get_offset(type, 0);
    jit_nuint yOffset = jit_type_get_offset(type, 1);
    jit_nuint zOffset = jit_type_get_offset(type, 2);
    // distribute operation to each component x/y
    jit_value_t newX = jit_phantom_math_operation_real_real(func, op, jit_insn_load_relative(func, jit_insn_address_of(func, l), xOffset, componentType), jit_insn_load_relative(func, jit_insn_address_of(func, r), xOffset, componentType));
    jit_value_t newY = jit_phantom_math_operation_real_real(func, op, jit_insn_load_relative(func, jit_insn_address_of(func, l), yOffset, componentType), jit_insn_load_relative(func, jit_insn_address_of(func, r), yOffset, componentType));
    jit_value_t newZ = jit_phantom_math_operation_real_real(func, op, jit_insn_load_relative(func, jit_insn_address_of(func, l), zOffset, componentType), jit_insn_load_relative(func, jit_insn_address_of(func, r), zOffset, componentType));
    jit_insn_store_relative(func, jit_insn_address_of(func, result), yOffset, newX);
    jit_insn_store_relative(func, jit_insn_address_of(func, result), yOffset, newY);
    jit_insn_store_relative(func, jit_insn_address_of(func, result), zOffset, newZ);
    return result;
}

o_jit_export jit_phantom_value_t jit_phantom_math_operation_vector4f_real( jit_function_t func, char op, jit_phantom_value_t l, jit_phantom_value_t r )
{
    jit_type_t type = jit_value_get_type(l.value);
    jit_value_t result = jit_value_create(func, type);
    jit_type_t componentType = jit_type_get_field(type, 0);
    jit_value_set_addressable(result);
    jit_value_set_local(result);
    jit_nuint xOffset = jit_type_get_offset(type, 0);
    jit_nuint yOffset = jit_type_get_offset(type, 1);
    jit_nuint zOffset = jit_type_get_offset(type, 2);
    jit_nuint wOffset = jit_type_get_offset(type, 3);
    // distribute operation to each component x/y
    jit_value_t newX = jit_phantom_math_operation_real_real(func, op, jit_insn_load_relative(func, jit_insn_address_of(func, l), xOffset, componentType), r);
    jit_value_t newY = jit_phantom_math_operation_real_real(func, op, jit_insn_load_relative(func, jit_insn_address_of(func, l), yOffset, componentType), r);
    jit_value_t newZ = jit_phantom_math_operation_real_real(func, op, jit_insn_load_relative(func, jit_insn_address_of(func, l), zOffset, componentType), r);
    jit_value_t newW = jit_phantom_math_operation_real_real(func, op, jit_insn_load_relative(func, jit_insn_address_of(func, l), wOffset, componentType), r);
    jit_insn_store_relative(func, jit_insn_address_of(func, result), xOffset, newX);
    jit_insn_store_relative(func, jit_insn_address_of(func, result), yOffset, newY);
    jit_insn_store_relative(func, jit_insn_address_of(func, result), zOffset, newZ);
    jit_insn_store_relative(func, jit_insn_address_of(func, result), wOffset, newW);
    return result;
}

o_jit_export jit_phantom_value_t jit_phantom_math_operation_vector4f_vector4f( jit_function_t func, char op, jit_phantom_value_t l, jit_phantom_value_t r )
{
    jit_type_t type = jit_value_get_type(l.value);
    jit_value_t result = jit_value_create(func, type);
    jit_type_t componentType = jit_type_get_field(type, 0);
    jit_value_set_addressable(result);
    jit_value_set_local(result);
    jit_nuint xOffset = jit_type_get_offset(type, 0);
    jit_nuint yOffset = jit_type_get_offset(type, 1);
    jit_nuint zOffset = jit_type_get_offset(type, 2);
    jit_nuint wOffset = jit_type_get_offset(type, 3);
    // distribute operation to each component x/y
    jit_value_t newX = jit_phantom_math_operation_real_real(func, op, jit_insn_load_relative(func, jit_insn_address_of(func, l), xOffset, componentType), jit_insn_load_relative(func, jit_insn_address_of(func, r), xOffset, componentType));
    jit_value_t newY = jit_phantom_math_operation_real_real(func, op, jit_insn_load_relative(func, jit_insn_address_of(func, l), yOffset, componentType), jit_insn_load_relative(func, jit_insn_address_of(func, r), yOffset, componentType));
    jit_value_t newZ = jit_phantom_math_operation_real_real(func, op, jit_insn_load_relative(func, jit_insn_address_of(func, l), zOffset, componentType), jit_insn_load_relative(func, jit_insn_address_of(func, r), zOffset, componentType));
    jit_value_t newW = jit_phantom_math_operation_real_real(func, op, jit_insn_load_relative(func, jit_insn_address_of(func, l), wOffset, componentType), jit_insn_load_relative(func, jit_insn_address_of(func, r), wOffset, componentType));
    jit_insn_store_relative(func, jit_insn_address_of(func, result), xOffset, newX);
    jit_insn_store_relative(func, jit_insn_address_of(func, result), yOffset, newY);
    jit_insn_store_relative(func, jit_insn_address_of(func, result), zOffset, newZ);
    jit_insn_store_relative(func, jit_insn_address_of(func, result), wOffset, newW);
    return result;
}

o_jit_export jit_phantom_value_t jit_phantom_math_operation_vector2f_any( jit_function_t func, char op, jit_phantom_value_t l, jit_phantom_value_t r )
{
    if(r.type->isIntegralType() || r.type->asEnum() || r.type->isArithmeticType())
    {
        return jit_phantom_math_operation_vector2f_real(func, op, l, r);
    }
    else if(jit_value_get_type(r.value) == jit_type_vector2f)
    {
        return jit_phantom_math_operation_vector2f_vector2f(func, op, l, r);
    }
    else return jit_phantom_value_t();
}

o_jit_export jit_phantom_value_t jit_phantom_math_operation_vector3f_any( jit_function_t func, char op, jit_phantom_value_t l, jit_phantom_value_t r )
{
    if(r.type->isIntegralType() || r.type->asEnum() || r.type->isArithmeticType())
    {
        return jit_phantom_math_operation_vector3f_real(func, op, l, r);
    }
    else if(jit_value_get_type(r.value) == jit_type_vector3f)
    {
        return jit_phantom_math_operation_vector3f_vector3f(func, op, l, r);
    }
    else return jit_phantom_value_t();
}

o_jit_export jit_phantom_value_t jit_phantom_math_operation_vector4f_any( jit_function_t func, char op, jit_phantom_value_t l, jit_phantom_value_t r )
{
    if(r.type->isIntegralType() || r.type->asEnum() || r.type->isArithmeticType())
    {
        return jit_phantom_math_operation_vector4f_real(func, op, l, r);
    }
    else if(jit_value_get_type(r.value) == jit_type_vector4f)
    {
        return jit_phantom_math_operation_vector4f_vector4f(func, op, l, r);
    }
    else return jit_phantom_value_t();
}

o_jit_export jit_phantom_value_t jit_phantom_math_operation_real_any( jit_function_t func, char op, jit_phantom_value_t l, jit_phantom_value_t r )
{
    if(r.type->isIntegralType() || r.type->asEnum() || r.type->isArithmeticType())
    {
        return jit_phantom_math_operation_real_real(func, op, l, r);
    }
    else return jit_phantom_value_t();
}

o_jit_export jit_phantom_value_t jit_phantom_math_operation( jit_function_t func, char op, jit_phantom_value_t l, jit_phantom_value_t r )
{
    if(jit_value_get_type(l.value) == jit_type_vector2f)
    {
        return jit_phantom_math_operation_vector2f_any(func, op, l, r);
    }
    if(jit_value_get_type(l.value) == jit_type_vector3f)
    {
        return jit_phantom_math_operation_vector3f_any(func, op, l, r);
    }
    if(jit_value_get_type(l.value) == jit_type_vector4f)
    {
        return jit_phantom_math_operation_vector4f_any(func, op, l, r);
    }
    if(l.type->isIntegralType() || l.type->asEnum() || l.type->isArithmeticType())
    {
        return jit_phantom_math_operation_real_any(func, op, l, r);
    }
    return jit_phantom_value_t();
}

static phantom::reflection::Type* phantom_type_float32 = phantom::typeOf<float>();
static phantom::reflection::Type* phantom_type_float64 = phantom::typeOf<double>();
static phantom::reflection::Type* phantom_type_vector2f = phantom::typeOf<phantom::math::vector2<float>>();
static phantom::reflection::Type* phantom_type_vector3f = phantom::typeOf<phantom::math::vector3<float>>();
static phantom::reflection::Type* phantom_type_vector4f = phantom::typeOf<phantom::math::vector4<float>>();
static phantom::reflection::Type* phantom_type_vector2f_cr = phantom::typeOf< const phantom::math::vector2<float>&>();
static phantom::reflection::Type* phantom_type_vector3f_cr = phantom::typeOf<const phantom::math::vector3<float>&>();
static phantom::reflection::Type* phantom_type_vector4f_cr = phantom::typeOf<const phantom::math::vector4<float>&>();

#define JIT_PHANTOM_CALL_UNARY_INTRINSIC(type, name)\
    if(strcmp(intrinsic, #name) == 0)\
{\
    jit_intrinsic_descr_t desc;\
    desc.arg1_type = jit_type_##type;\
    desc.arg2_type = 0;\
    desc.return_type = jit_type_##type;\
    desc.ptr_result_type = 0;\
    return jit_insn_call_intrinsic(func, #name, jit_##type##_##name, &desc, operand.value, 0);\
}

#define JIT_PHANTOM_CALL_BINARY_INTRINSIC(type, name)\
    if(strcmp(intrinsic, #name) == 0)\
{\
    jit_intrinsic_descr_t desc;\
    desc.arg1_type = jit_type_##type;\
    desc.arg2_type = jit_type_##type;\
    desc.return_type = jit_type_##type;\
    desc.ptr_result_type = 0;\
    return jit_insn_call_intrinsic(func, #name, jit_##type##_##name, &desc, l, r);\
}

#define JIT_PHANTOM_MAKE_PARAM(type) (jit_type_is_struct(jit_type_##type) \
    ? jit_type_void_ptr \
    : jit_type_##type)

#define JIT_PHANTOM_TYPE_OF_PARAM(type) (jit_type_is_struct(jit_type_##type) \
    ? phantom::referenceTypeOf(phantom::constTypeOf(phantom_type_##type)) \
    : phantom_type_##type)


#define JIT_PHANTOM_CONVERT_ARG(index, type)\
{\
    jit_phantom_value_t converted_value = jit_insn_phantom_implicit_cast(func, JIT_PHANTOM_TYPE_OF_PARAM(type), args[index]);\
    if(converted_value.isNull()) return jit_phantom_value_t();\
    converted_args[index] = converted_value.value;\
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
    return jit_insn_call_native(func, #name, jit_##type0##_##name, jit_type_create_signature(jit_abi_stdcall, jit_type_##rtype, params, 2, 0), converted_args, 2, 0);\
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
    return jit_insn_call_native(func, #name, jit_##type0##_##name, jit_type_create_signature(jit_abi_stdcall, jit_type_##rtype, params, 3, 0), converted_args, 3, 0);\
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
#define JIT_CALL_CONV __stdcall 

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

float JIT_CALL_CONV jit_vector2f_distance(const phantom::math::vector2<float>& vec0, const phantom::math::vector2<float>& vec1)
{
    return vec0.distance(vec1);
}

float JIT_CALL_CONV jit_vector2f_distance2(const phantom::math::vector2<float>& vec0, const phantom::math::vector2<float>& vec1)
{
    return (vec0-vec1).lengthSquared();
}

float JIT_CALL_CONV jit_vector2f_cross(const phantom::math::vector2<float>& vec0, const phantom::math::vector2<float>& vec1)
{
    return vec0.cross(vec1);
}

float JIT_CALL_CONV jit_vector2f_dot(const phantom::math::vector2<float>& vec0, const phantom::math::vector2<float>& vec1)
{
    return vec0.dot(vec1);
}

void JIT_CALL_CONV jit_vector2f_vector2f_reflect(const phantom::math::vector2<float>& i, const phantom::math::vector2<float>& n, phantom::math::vector2<float>& out)
{
    out = i - 2*n.dot(i) * n;
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


o_jit_export jit_phantom_value_t jit_phantom_math_unary_intrinsic_float32( jit_function_t func, const char* intrinsic, jit_phantom_value_t operand )
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
    return jit_phantom_value_t();
}

o_jit_export jit_phantom_value_t jit_phantom_math_unary_intrinsic_float64( jit_function_t func, const char* intrinsic, jit_phantom_value_t operand )
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
    return jit_phantom_value_t();
}

o_jit_export jit_phantom_value_t jit_phantom_math_binary_intrinsic_float32_float32( jit_function_t func, const char* intrinsic, jit_phantom_value_t l, jit_phantom_value_t r)
{
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(float32, pow)
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(float32, atan2)
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(float32, min)
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(float32, max)
    return jit_phantom_value_t();
}

o_jit_export jit_phantom_value_t jit_phantom_math_binary_intrinsic_float64_float64( jit_function_t func, const char* intrinsic, jit_phantom_value_t l, jit_phantom_value_t r )
{
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(float64, pow)
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(float64, atan2)
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(float64, min)
    JIT_PHANTOM_CALL_BINARY_INTRINSIC(float64, max)
    return jit_phantom_value_t();
}

o_jit_export jit_phantom_value_t jit_phantom_math_func_vector2f( jit_function_t func, const char* function, jit_phantom_value_t* args )
{
    JIT_PHANTOM_CALL_FUNC_1(vector2f, float32, length)
    JIT_PHANTOM_CALL_FUNC_1(vector2f, float32, length2)
    JIT_PHANTOM_CALL_FUNC_1_RET_BY_REF(vector2f, vector2f, normalize)
    return jit_phantom_value_t();
}

o_jit_export jit_phantom_value_t jit_phantom_math_func_vector2f_vector2f( jit_function_t func, const char* function, jit_phantom_value_t args[2] )
{
    JIT_PHANTOM_CALL_FUNC_2(vector2f, vector2f, float32, distance)
    JIT_PHANTOM_CALL_FUNC_2(vector2f, vector2f, float32, distance2)
    JIT_PHANTOM_CALL_FUNC_2(vector2f, vector2f, float32, cross)
    JIT_PHANTOM_CALL_FUNC_2(vector2f, vector2f, float32, dot)
    JIT_PHANTOM_CALL_FUNC_2_RET_BY_REF(vector2f, vector2f, vector2f, reflect)
    return jit_phantom_value_t(); 
}

o_jit_export jit_phantom_value_t jit_phantom_math_func_vector2f_vector2f_float( jit_function_t func, const char* function, jit_phantom_value_t args[3] )
{
    JIT_PHANTOM_CALL_FUNC_3_RET_BY_REF(vector2f, vector2f, float32, vector2f, refract)
    return jit_phantom_value_t(); 
}

o_jit_export jit_phantom_value_t jit_phantom_math_unary_intrinsic( jit_function_t func, const char* intrinsic, jit_phantom_value_t l )
{
    if(l.type == phantom_type_float32)
    {
        return jit_phantom_math_unary_intrinsic_float32(func, intrinsic, l);
    }
    else if(l.type == phantom_type_float64)
    {
        return jit_phantom_math_unary_intrinsic_float64(func, intrinsic, l);
    }
    return jit_phantom_value_t();
}

o_jit_export jit_phantom_value_t jit_phantom_math_binary_intrinsic( jit_function_t func, const char* intrinsic, jit_phantom_value_t l, jit_phantom_value_t r )
{
    if(jit_value_get_type(l.value) == jit_type_float32 && jit_value_get_type(r.value) == jit_type_float32)
    {
        return jit_phantom_math_binary_intrinsic_float32_float32(func, intrinsic, l, r);
    }
    else if(jit_value_get_type(l.value) == jit_type_float64 && jit_value_get_type(r.value) == jit_type_float64)
    {
        return jit_phantom_math_binary_intrinsic_float64_float64(func, intrinsic, l, r);
    }
    return jit_phantom_value_t();
}

o_jit_export jit_phantom_value_t jit_phantom_math_func(jit_function_t func, const char* function, jit_phantom_value_t value)
{
    if(value.type == phantom_type_vector2f || value.type == phantom_type_vector2f_cr)
    {
        return jit_phantom_math_func_vector2f(func, function, &value);
    } 
    else 
    {
        return jit_phantom_math_unary_intrinsic(func, function, value);
    }
    return jit_phantom_value_t();
}

o_jit_export jit_phantom_value_t jit_phantom_math_func(jit_function_t func, const char* function, jit_phantom_value_t l, jit_phantom_value_t r)
{
    if(l.type == phantom_type_vector2f || l.type == phantom_type_vector2f_cr)
    {
        jit_phantom_value_t args[2] = {l, r};
        return jit_phantom_math_func_vector2f_vector2f(func, function, args);
    } 
    else 
    {
        return jit_phantom_math_binary_intrinsic(func, function, l, r);
    }
    return jit_phantom_value_t();
}

o_jit_export jit_phantom_value_t jit_phantom_math_func(jit_function_t func, const char* function, jit_phantom_value_t v0, jit_phantom_value_t v1, jit_phantom_value_t v2)
{
    if((v0.type == phantom_type_vector2f || v0.type == phantom_type_vector2f_cr) 
        && (v1.type == phantom_type_vector2f || v1.type == phantom_type_vector2f_cr) )
    {
        jit_phantom_value_t args[3] = {v0, v1, jit_insn_convert(func, v2.value, jit_type_float32, 1) };
        return jit_phantom_math_func_vector2f_vector2f_float(func, function, args);
    } 
    return jit_phantom_value_t();
}