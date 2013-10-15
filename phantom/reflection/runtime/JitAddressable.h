#ifndef o_reflection_runtime_JitAddressable_h__
#define o_reflection_runtime_JitAddressable_h__


/* ****************** Includes ******************* */
#include "phantom/def_runtime.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection, runtime)

class JitLocalVariable;
class InstanceAttributeVariable;

class o_runtime_export JitAddressable
{
public:
	JitAddressable(void) {}
	~JitAddressable(void) {}

    virtual int store(jit_phantom_value_t value) const = 0;
    virtual jit_phantom_value_t load() const = 0;
    virtual jit_function_t getJitFunction() const = 0;
    virtual reflection::Type*   getValueType() const = 0;
    virtual jit_phantom_value_t address() const = 0;
    jit_phantom_value_t implicitCast(reflection::Type* a_pType) const;

protected:

};

o_namespace_end(phantom, reflection, runtime)

o_classN((phantom, reflection, runtime), JitAddressable)
{
	o_reflection
	{
		
	};
};
o_exposeN((phantom, reflection, runtime), JitAddressable);

#endif
