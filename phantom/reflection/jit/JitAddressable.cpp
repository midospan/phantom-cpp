/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "JitAddressable.h"
#include "JitSubroutine.h"
/* *********************************************** */
o_registerN((phantom, reflection, jit), JitAddressable);

o_namespace_begin(phantom, reflection, jit)

jit_value JitAddressable::loadAs( reflection::Type* a_pDestType ) const
{
    jit_value value = load();
    return getJitSubroutine()->implicitCast(value, a_pDestType);
}

o_namespace_end(phantom, reflection, jit)
