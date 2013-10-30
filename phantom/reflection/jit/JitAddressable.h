#ifndef o_reflection_jit_JitAddressable_h__
#define o_reflection_jit_JitAddressable_h__


/* ****************** Includes ******************* */
#include "phantom/def_jit.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection, jit)

class JitLocalVariable;
class InstanceDataMemberVariable;

class o_jit_export JitAddressable
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

o_namespace_end(phantom, reflection, jit)

o_classN((phantom, reflection, jit), JitAddressable)
{
	o_reflection
	{
		
	};
};
o_exposeN((phantom, reflection, jit), JitAddressable);

#endif
