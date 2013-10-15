

#include <stdio.h>
#include <jit/jit.h>
#include "NativeVTableIndexInspector.h"
#include <iostream>
#include <pthread.h>

class MyClass
{
public:
    void doSmth()
    {
        if(this == NULL)
        {
            std::cout<<"HACKED NULL !!!!\n"<<std::endl;
        }
        std::cout<<"HACKED doSmth !!!!\n"<<std::endl;
    }
    virtual void* doSmthElse()
    {
        std::cout<<"doSmthElse\n"<<std::endl;
        return NULL;
    }
    virtual void doAnotherSmthElse()
    {
        std::cout<<"doSmthElse\n"<<std::endl;
    }
};

class MySubClass : public MyClass
{
public:
    virtual void doSmth()
    {
        std::cout<<"doSmthElse\n"<<std::endl;
        
    }
    virtual void* doSmthElse()
    {
        std::cout<<"doSmthElse\n"<<std::endl;
        return NULL;
    }
    virtual void doAnotherSmthElse2()
    {
        std::cout<<"doSmthElse\n"<<std::endl;
    }
};

class MySecondSubClass : public MySubClass
{
    virtual void doAnotherSmthElse()
    {
        std::cout<<"doSmthElse\n"<<std::endl;
    }
    
};


class Expression 
{
public:
    virtual jit_value_t jit_compile(jit_function_t func) = 0;
    
};

class ThisVariableAccess : public Expression
{
    virtual jit_value_t jit_compile(jit_function_t func) 
    {
        return jit_value_get_param(func, 0);
    }
};

class ArgumentAccess : public Expression
{
public:
    ArgumentAccess(int index) : m_index(index)
    {
        
    }
    virtual jit_value_t jit_compile(jit_function_t func) 
    {
        return jit_value_get_param(func, m_index+1); // +1 to skip "this" pointer
    }
    
protected:
    int m_index;
};

class BinaryExpression : public Expression
{
    public:
    BinaryExpression( Expression* _first, Expression* _second) : m_first(_first), m_second(_second) {}
public:
    Expression* m_first;
    Expression* m_second;
};

class And : public BinaryExpression
{
public:
    And( Expression* _first, Expression* _second) : BinaryExpression(_first,_second) {}
    virtual jit_value_t jit_compile(jit_function_t func)
    {
        jit_value_t v0 = m_first->jit_compile(func);
        jit_value_t v1 = m_second->jit_compile(func);
        return jit_insn_and(func, v0, v1);
    }
    
};

class Or : public BinaryExpression
{
public:
    Or( Expression* _first, Expression* _second) : BinaryExpression(_first,_second) {}
    virtual jit_value_t jit_compile(jit_function_t func)
    {
        jit_value_t v0 = m_first->jit_compile(func);
        jit_value_t v1 = m_second->jit_compile(func);
        return jit_insn_or(func, v0, v1);
    }
};

class NativeMethodCall : public Expression
{
public:
    typedef bool (*method_t)();
    
    NativeMethodCall(method_t t)
    : m_method(t)
    {
        
    }
    
public:
    virtual jit_value_t jit_compile(jit_function_t func)
    {
        return jit_insn_call_native(func
                                    ,"native"
                                    , (void*)m_method
                                    , jit_type_create_signature(jit_abi_stdcall, jit_type_sys_bool, 0, 0, 1)
                                    , 0, 0, 0);
    }
    
    method_t m_method;
};

int compile_mul_add(jit_function_t function)
{
	jit_value_t x, y, z;
	jit_value_t temp1, temp2;
    
	printf("Compiling mul_add on demand\n");
    
	x = jit_value_get_param(function, 0);
	y = jit_value_get_param(function, 1);
	z = jit_value_get_param(function, 2);
    
	temp1 = jit_insn_mul(function, x, y);
	temp2 = jit_insn_add(function, temp1, z);
    
	jit_insn_return(function, temp2);
	return 1;
}

bool native_method()
{
    return false;
}

void doSmthHacked()
{
    std::cout<<"doSmthHacked\n"<<std::endl;
    
}

void doSmthElseHacked()
{
    std::cout<<"doSmthElseHacked\n"<<std::endl;
}

jit_debugger_t debugger;
/*
void* thread0_func(void* param)
{
    jit_debugger_attach_self(debugger, true);
    while(true)
    {
        std::cout<<"thread0"<<std::endl;
        jit_debugger_event_t event;
        jit_debugger_wait_event(debugger, &event, 0);
        switch(event.data1)
        {
            case JIT_DEBUGGER_DATA1_LINE:
                std::cout<<"break on line\n";
        }
    }
    jit_debugger_detach_self(debugger);
    return NULL;
}*/

/*
void* thread1_func(void* param)
{
    while(true)
    {
        std::cout<<"thread1"<<std::endl;
    }
    return NULL;
}
*/
void debugger_hook(jit_function_t func, jit_nint data1, jit_nint data2)
{
    switch(data1)
    {
        case JIT_DEBUGGER_DATA1_LINE:
            std::cout<<"break on line "<<data2<<"\n";
    }
}

 int __cdecl main(int argc, char **argv)
{
    
    
	jit_context_t context;
	jit_type_t params[5];
	jit_type_t signature;
	jit_function_t function;
    void* _this;
	bool a = true;
    bool b = true;
    bool c = true;
    bool d = true;
	void *args[5];
	//jit_int result;`
    
    
    
    MyClass* pMyClass = new MyClass;
    
    void*** pMyClassCasted = (void***)pMyClass;
    void ** vtable_ptr = *pMyClassCasted;
    
    std::cout<<vtable_ptr[0]<<std::endl;
    
    typedef void (*void_method)();
    
    void** new_vtable = (void**)malloc(sizeof(void*)*2);
    
    *pMyClassCasted = new_vtable;
    memcpy(new_vtable, vtable_ptr, NativeVTableIndexInspector::getVirtualMethodCount<MySubClass>()*sizeof(void*));

    auto method_ptr = &MyClass::doSmth;
    auto method_ptr2 = &MyClass::doSmthElse;

    
    //std::cout<< "index of MyClass::doSmth"<< NativeVTableIndexInspector::getIndexOf(&MyClass::doSmth) <<std::endl;
    
	/* Create a context to hold the JIT's primary state */
	context = jit_context_create();
    
    // DEBUGGER
    
    debugger = jit_debugger_create(context);
    
    jit_debugger_set_hook(context, debugger_hook);
                          /*
    
    // Create threads
    pthread_t thread0;
    pthread_t thread1;
    pthread_create(&thread0, NULL, thread0_func, NULL);
    pthread_create(&thread1, NULL, thread1_func, NULL);*/
    
	/* Lock the context while we construct the function */
	jit_context_build_start(context);
    
	/* Build the function signature */
	params[0] = jit_type_void_ptr; // this
	params[1] = jit_type_sys_bool; // a
	params[2] = jit_type_sys_bool; // b
	params[3] = jit_type_sys_bool; // c
	params[4] = jit_type_sys_bool; // d
	signature = jit_type_create_signature(jit_abi_thiscall, jit_type_void_ptr, params, 1, 1);
    
	/* Create the function object */
	function = jit_function_create(context, signature);
    
    
    //Expression* expression = new Or(new And(new ArgumentAccess(0), new ArgumentAccess(1))
    //                               , new And(new ArgumentAccess(2), new NativeMethodCall(native_method)));
    void* hacked_ptr = *reinterpret_cast<void**>(&method_ptr);
    signature = jit_type_create_signature(jit_abi_thiscall, jit_type_void, params, 1, 1);

    jit_value_t args_this = jit_value_create_nint_constant(function, jit_type_void_ptr, 0);
    jit_insn_call_native(function, "doSmth", hacked_ptr, signature, &args_this, 1, 0);
    jit_insn_mark_breakpoint (function, JIT_DEBUGGER_DATA1_LINE, 0);
    jit_insn_return(function, jit_value_get_param(function, 0));
    jit_insn_mark_breakpoint (function, JIT_DEBUGGER_DATA1_LINE, 1);
    
    
	/* Unlock the context.  It will be automatically locked for
     us when the on-demand compiler is called */
	jit_context_build_end(context);
    
	/* Execute the function and print the result.  This will arrange
     to call the on-demand compiler to build the function's body */
    
    jit_function_compile(function);
	
    _this = (void*)10;
    void* result;
	args[0] = &pMyClass;
	args[1] = &a;
	args[2] = &b;
	args[3] = &c;
	args[4] = &d;
    /*__asm
    {
        mov ecx, pMyClass
    };*/
	jit_function_apply(function, args, &result);
	printf("(a && b) || (c && call) = %d\n", result);
    
    new_vtable[1] = jit_function_to_vtable_pointer(function);
    
    result = pMyClass->doSmthElse();
    
	printf("(a && b) || (c && call) = %d\n", result);
    
	/* Execute the function again, to demonstrate that the
     on-demand compiler is not invoked a second time */
	/*arg1 = 13;
	arg2 = 5;
	arg3 = 7;
	args[0] = &arg1;
	args[1] = &arg2;
	args[2] = &arg3;
	jit_function_apply(function, args, &result);
	printf("mul_add(13, 5, 7) = %d\n", (int)result);*/
    
	/* Execute the function a third time, after it is recompiled */
	/*arg1 = 2;
	arg2 = 18;
	arg3 = -3;
	args[0] = &arg1;
	args[1] = &arg2;
	args[2] = &arg3;
	jit_function_apply(function, args, &result);
	printf("mul_add(2, 18, -3) = %d\n", (int)result);*/
    
	/* Clean up */
	jit_context_destroy(context);
    
    system("pause");

	/* Finished */
	return 0;
}
