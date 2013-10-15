/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "JitAddressable.h"
/* *********************************************** */
o_registerN((phantom, reflection, runtime), JitAddressable);

o_namespace_begin(phantom, reflection, runtime)

jit_phantom_value_t JitAddressable::implicitCast( reflection::Type* a_pDestType ) const
{
    jit_function_t func = getJitFunction();
    jit_phantom_value_t value = load();
    if(a_pDestType == value.type) return jit_phantom_value_t(value.value, a_pDestType);
    if(!value.type->isConvertibleTo(a_pDestType)) 
        return jit_phantom_value_t();

    o_assert(!value.type->isDataPointerType() OR a_pDestType->isDataPointerType(), " src is ptr => dest is ptr, or something is wrong in isConvertibleTo");
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
    else if(a_pDestType->isArithmeticType() AND value.type->isArithmeticType())
    {
        return jit_phantom_value_t(jit_insn_convert(func, value.value, jit_type_from_phantom_type(a_pDestType), 1), a_pDestType);
    }
    else if(a_pDestType->isReferenceType() AND NOT(value.type->isReferenceType()))
    {
        /// Convert from value to reference => address value
        return address();
    }
    else if(NOT(a_pDestType->isReferenceType()) AND value.type->isReferenceType())
    {
        /// Convert from reference to value (dereference) => get value content
        return jit_insn_load_relative(func, address().value, 0, jit_type_from_phantom_type(a_pDestType));
    }
    return jit_phantom_value_t();
}

o_namespace_end(phantom, reflection, runtime)
