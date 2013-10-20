/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "JitSignal.h"
#include "JitClass.h"
#include "JitInstanceDataMember.h"
/* *********************************************** */
static void* g_ptr_test = (void*)0xffffffff;
o_registerN((phantom, reflection, jit), JitSignal);

o_classN((phantom, connection), slot)
{
    o_reflection {};
};
o_exposeN((phantom, connection), slot);
o_registerN((phantom, connection), slot);

o_classNC((phantom, connection), (slot), list)
{
    o_reflection {};
};
o_exposeNC((phantom, connection), (slot), list);
o_registerNC((phantom, connection), (slot), list);

o_namespace_begin(phantom, reflection, jit)

JitSignal::JitSignal( const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers ) 
    : Signal(a_strName, a_pSignature, a_Modifiers) 
    , m_jit_function(nullptr)
    , m_uiDataOffset(0xffffffff)
    , m_pDataMember(o_new(phantom::reflection::jit::JitInstanceDataMember)(
                    "PHANTOM_RESERVED_m_slot_list_of_"+a_strName+boost::lexical_cast<string>((int)this)
                    , phantom::typeByName("phantom::connection::slot::list"), 0, o_protected))
{
    o_assert(a_pSignature->getReturnType() == typeOf<signal_t>());
    o_assert(m_pDataMember->getValueType() == typeOf<connection::slot::list>());
    m_jit_context = jit_context_create();
    o_assert(m_jit_context);
    m_jit_function = jit_function_create(m_jit_context, jit_type_from_phantom_signature(jit_abi_thiscall, getSignature()));
    o_assert(m_jit_function);
}

JitSignal::~JitSignal( void )
{
    jit_context_destroy(m_jit_context);
}

jit_context_t JitSignal::getContext() const
{
    return m_jit_context;
}

void JitSignal::compile()
{
    o_assert(m_pOwner AND as<JitClass*>(m_pOwner)->getState() == JitClass::e_State_Compiling);
    o_assert(m_uiDataOffset == 0xffffffff);
    m_uiDataOffset = m_pDataMember->getOffset();
    o_assert(m_uiDataOffset != 0xffffffff);
    jit_context_build_start(m_jit_context);

//     slot::list*                m_list_pointer;   0
//     void*                      m_receiver;       4
//     reflection::Subroutine*    m_subroutine;     8
//     slot*                      m_next;           12
//     slot*                      m_prev;           16

    jit_value_t this_value = jit_value_get_param(m_jit_function, 0);

    // connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_destroyed.head();
    jit_value_t head_slot_ptr_value = jit_insn_load_relative(m_jit_function, this_value, m_uiDataOffset, jit_type_void_ptr);

    jit_value_t slot_ptr_value = jit_insn_load(m_jit_function, head_slot_ptr_value);
    jit_value_set_addressable(slot_ptr_value);
    //while(pSlot)
    

    jit_label_t label_break = jit_label_undefined;
    jit_label_t label_continue = jit_label_undefined;
    jit_label_t label_first_instruction = jit_label_undefined;

    jit_insn_label(m_jit_function, &label_continue);

    jit_value_t while_condition_value = jit_insn_ne(m_jit_function, slot_ptr_value, jit_value_create_nint_constant(m_jit_function, jit_type_void_ptr, NULL)); 

    //{

    
    // if !while_condition => break;
    jit_insn_branch_if_not(m_jit_function, while_condition_value, &label_break);

    
    jit_insn_store_relative(m_jit_function, jit_value_create_nint_constant(m_jit_function, jit_type_void_ptr, (int)&g_ptr_test), 0, slot_ptr_value);
    jit_insn_check_null(m_jit_function, slot_ptr_value);

    // compile while block instructions
    
    // connection::pair::push(const_cast<Object*>(this), pSlot->receiver());

    jit_value_t receiver_value = jit_insn_load_relative(m_jit_function, slot_ptr_value, 4, jit_type_void_ptr);
    jit_insn_check_null(m_jit_function, receiver_value);
    jit_value_t push_args[2] = 
    { 
        this_value // this
        ,  slot_ptr_value // receiver
    };
    jit_type_t push_types[2] = 
    { 
        jit_type_void_ptr
        , jit_type_void_ptr
    };
    jit_insn_call_native(m_jit_function, "connection::pair::push"
        , (void*)connection::pair::push
        , jit_type_create_signature(jit_abi_cdecl, jit_type_void, push_types, 2, 0)
        , push_args
        , 2
        , 0);


    // pSlot->subroutine()->call(pSlot->receiver(), args );
    jit_value_t subroutine_ptr_value = jit_insn_load_relative(m_jit_function, slot_ptr_value, 8, jit_type_void_ptr); 

    jit_insn_check_null(m_jit_function, subroutine_ptr_value);

    jit_value_t argument_ptr_array_ptr = 0;
     
    size_t argumentCount = m_pSignature->getParameterCount();
    jit_type_t* argmentTypes = nullptr;
    if(argumentCount)
    {
        argmentTypes = o_allocate_n(argumentCount, jit_type_t);
        for(size_t i = 0; i < argumentCount; ++i)
        {
            argmentTypes[i] = jit_type_void_ptr;
        }

        jit_value_t argument_ptr_array = jit_value_create(m_jit_function, jit_type_create_struct(argmentTypes, argumentCount, 0));
        argument_ptr_array_ptr = jit_insn_address_of(m_jit_function, argument_ptr_array);

        for(size_t i = 0; i < argumentCount; ++i)
        {
            jit_insn_store_relative(m_jit_function, argument_ptr_array_ptr, i*4, jit_insn_address_of(m_jit_function, jit_value_get_param(m_jit_function, i+1)));
        }
    }
    else
    {
        argument_ptr_array_ptr = jit_value_create_nint_constant(m_jit_function, jit_type_void_ptr, 0);
    }

    jit_value_t invoke_args[3] = {
        subroutine_ptr_value
        , receiver_value
        , argument_ptr_array_ptr
    };

    jit_type_t invoke_types[3] = {
        jit_type_void_ptr
        , jit_type_void_ptr
        , jit_type_void_ptr
    };

    union 
    {
        void (Subroutine::*invoke_func)(void*, void**) const;
        void* hacked;
    } un;

    un.invoke_func = &Subroutine::call;
    
    jit_insn_call_native(m_jit_function, "call", un.hacked, jit_type_create_signature(jit_abi_thiscall, jit_type_void, invoke_types, 3, 0), invoke_args, 3, 0);

    // pSlot = pSlot->next();
    jit_insn_store(m_jit_function, slot_ptr_value, jit_insn_load_relative(m_jit_function, slot_ptr_value, 12, jit_type_void_ptr));
    
    // connection::pair::pop();
    jit_insn_call_native(m_jit_function, "connection::pair::pop", (void*)connection::pair::pop, jit_type_create_signature(jit_abi_cdecl, jit_type_void, NULL, 0, 0), NULL, 0, 0);
    
    // set continue label position
    //jit_insn_label(m_jit_function, &label_continue);

    // branch first instruction
    jit_insn_branch(m_jit_function, &label_continue);

    // set break/out label position
    jit_insn_label(m_jit_function, &label_break);

    jit_value_t return_value = jit_value_create(m_jit_function, jit_type_from_phantom_type(phantom::typeOf<signal_t>()));

    jit_insn_return(m_jit_function, return_value);

    int result = jit_function_compile(m_jit_function);
    o_assert(result);

    jit_context_build_end(m_jit_context);

    if(argmentTypes)
    {
        o_deallocate_n(argmentTypes, argumentCount, jit_type_t);
    }
}

o_namespace_end(phantom, reflection, jit)
