#ifndef o_phantom_def_jit
#define o_phantom_def_jit

namespace phantom { namespace reflection { namespace jit {}}}

o_declareN(struct, (phantom, reflection, jit), jit_label);
o_declareN(struct, (phantom, reflection, jit), jit_value);

o_namespace_begin(phantom, reflection, jit)

class reflection_jit_exception : public exception::reflection_runtime_exception
{
public:
    reflection_jit_exception(void) {}
    reflection_jit_exception(const char * const & _What)
        : reflection_runtime_exception(_What)
    {

    }

};

enum EJitAbi
{
    e_JitAbi_cdecl,			/* Native C calling conventions */
    e_JitAbi_vararg,			/* Native C with optional variable arguments */
    e_JitAbi_stdcall,		/* Win32 STDCALL (same as cdecl if not Win32) */
    e_JitAbi_fastcall,		/* Win32 FASTCALL (same as cdecl if not Win32) */
    e_JitAbi_thiscall		/* Method call */
};

struct o_jit_export jit_label
{
    bool isUndefined() const;
    jit_label();
    uint label;
};

struct o_jit_export jit_function
{
    jit_function();
    jit_function(void* b);
    void* function;
};

struct o_jit_export jit_context
{
    jit_context();
    jit_context(void* b);
    void* context;
};

struct o_jit_export jit_block
{
    jit_block();
    jit_block(void* b);
    void* block;
};

struct o_jit_export jit_constant
{
    jit_constant();
    Type* getType () const;
    int getIntValue() const;
    uint getUIntValue() const;
    longlong getLongLongValue() const;
    ulonglong getULongLongValue() const;
    Type*			type;
    union
    {
        void*       ptr_value;
        int			int_value;
        uint		uint_value;
        longlong	longlong_value;
        ulonglong	ulonglong_value;
        float		float_value;
        double		double_value;
    } un;
};

struct o_jit_export jit_value
{
    jit_value();
    jit_value(void* a_Value);
    jit_value(void* a_Value, phantom::reflection::Type* a_pType);

    bool isNull() const { return value == 0; }
    bool isNullPtr() const{ return type == nullptr; }

    void*     value;
    Type*     type;
    
    bool operator==(const jit_value& ptr) const { return value == ptr.value; }
    bool operator!=(const jit_value& ptr) const { return value != ptr.value; }

    int             isTemporary () const;
    void            setLocal();
    int             isLocal () const;
    int             isConstant () const;
    int             isParameter () const;
    void            ref() const;
    void            setVolatile () const;
    int             isVolatile () const;
    void            setAddressable () const;
    int             isAddressable () const;
    Type*           getType () const;
    jit_block       getBlock () const;
    jit_context     getContext () const;
    jit_constant    getConstant () const;
    int             getIntConstant () const;
    longlong        getLongLongConstant () const;
    float           getFloatConstant () const;
    double          getDoubleConstant () const;
    int             getFrameOffset() const;
    int             isTrue () const;
    static int      convertConstant (jit_constant *result, const jit_constant *value, Type* a_pType, int overflow_check);
    static jit_constant create1Constant();
};

o_namespace_end(phantom, reflection, jit)

#endif