#include "phantom/phantom.h"
#include "phantom/math/math.h"
#include "def_jit.h"
#include "def_jit_internal.h"
#include <jit/jit.h>
#include <windows.h>

o_registerN((phantom, reflection, jit), jit_value);

o_namespace_begin(phantom, reflection, jit)

int             jit_value::isTemporary () const 
{
	return jit_value_is_temporary((jit_value_t)value);
}

int             jit_value::isLocal () const 
{
    return jit_value_is_local((jit_value_t)value);
}

int             jit_value::isConstant () const 
{
    return jit_value_is_constant((jit_value_t)value);
}

int             jit_value::isParameter () const 
{
    return jit_value_is_parameter((jit_value_t)value);
}

void            jit_value::setVolatile () const 
{
    jit_value_set_volatile((jit_value_t)value);
}

int             jit_value::isVolatile () const 
{
    return jit_value_is_volatile((jit_value_t)value);
}

void            jit_value::setAddressable () const 
{
    jit_value_set_addressable((jit_value_t)value);
}

int             jit_value::isAddressable () const 
{
    return jit_value_is_addressable((jit_value_t)value);
}

Type*           jit_value::getType () const 
{
	return type;
}

JitSubroutine*  jit_value::getJitSubroutine() const 
{
    jit_function_t func = jit_value_get_function((jit_value_t)value);
    return jitSubroutine(func);
}

jit_block     jit_value::getBlock () const 
{
    return jit_block(jit_value_get_block((jit_value_t)value));
}

jit_context   jit_value::getContext () const 
{
    return jit_context(jit_value_get_context((jit_value_t)value));
}

jit_constant  jit_value::getConstant () const 
{
    jit_constant c;
    jit_constant_t ct = jit_value_get_constant((jit_value_t)value);
    c.type = fromJitType(ct.type);
    c.un.longlong_value = ct.un.long_value;
    return c;
}

int        jit_value::getIntConstant () const 
{
    return jit_value_get_nint_constant((jit_value_t)value);
}

longlong jit_value::getLongLongConstant () const 
{
    return jit_value_get_long_constant((jit_value_t)value);
}

float       jit_value::getFloatConstant () const 
{
    return jit_value_get_float32_constant((jit_value_t)value);
}

double      jit_value::getDoubleConstant () const 
{
    return jit_value_get_float64_constant((jit_value_t)value);
}

int             jit_value::isTrue () const 
{
    return jit_value_is_true((jit_value_t)value);
}

int             jit_value::convertConstant (jit_constant *result, const jit_constant *value, Type* a_pType, int overflow_check) 
{
    return jit_constant_convert((jit_constant_t*)result, (const jit_constant_t*)value, toJitType(a_pType), overflow_check);
}


jit_constant jit_value::create1Constant()
{
    jit_constant c;

    if(c.type == typeOf<int>())
        c.un.int_value = 1;
    else if(c.type == typeOf<uint>())
        c.un.uint_value = 1;
    else if(c.type == typeOf<longlong>())
        c.un.longlong_value = 1;
    else if(c.type == typeOf<ulonglong>())
        c.un.ulonglong_value = 1;
    else if(c.type == typeOf<float>())
        c.un.float_value = 1.f;
    else if(c.type == typeOf<double>())
        c.un.double_value = 1.0;
    else /*if(c.type == jit_type_void
        || c.type == jit_type_void_ptr
        || c.type == jit_type_sbyte
        || c.type == jit_type_ubyte
        || c.type == jit_type_short
        || c.type == jit_type_ushort)*/
    {
        o_assert(false, "Cannot increment this type or type not allowed");
    }
    return c;
}

jit_value::jit_value( void* a_Value ) : value(a_Value)
    , type(a_Value == 0 ? 0 : fromJitType(jit_value_get_type((jit_value_t)a_Value)))
{

}

jit_value::jit_value() : value(0), type(0)
{

}

jit_value::jit_value( void* a_Value, phantom::reflection::Type* a_pType ) : value(a_Value)
    , type(a_Value == 0 ? 0 : a_pType)
{

}

void jit_value::setLocal()
{
    jit_value_set_local((jit_value_t)value);
}

int jit_value::getFrameOffset() const
{
    return jit_value_get_frame_offset((jit_value_t)value);
}

Type* jit_constant::getType() const
{
    return type;
}

jit_constant::jit_constant()
    : type(nullptr)
{

}

int jit_constant::getIntValue() const
{
    return un.int_value;
}

uint jit_constant::getUIntValue() const
{
    return un.uint_value;
}

longlong jit_constant::getLongLongValue() const
{
    return un.longlong_value;
}

ulonglong jit_constant::getULongLongValue() const
{
    return un.ulonglong_value;
}

jit_label::jit_label() : label(jit_label_undefined)
{

}

jit_block::jit_block() : block(0)
{

}

jit_block::jit_block( void* b ) : block(b)
{

}


jit_context::jit_context()
{

}

jit_context::jit_context( void* b ) : context(b)
{

}

jit_function::jit_function()
    : function(0)
{

}

jit_function::jit_function( void* b ) : function(b)
{

}

o_namespace_end(phantom, reflection, jit)

o_module("jit");