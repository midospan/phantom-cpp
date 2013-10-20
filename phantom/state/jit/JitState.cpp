/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "JitState.h"
#include "JitStateMachine.h"
#include <phantom/reflection/jit/JitInstanceMemberFunction.h>
#include <phantom/reflection/jit/JitClass.h>
/* *********************************************** */
o_registerN((phantom, state, jit), JitState);

o_namespace_begin(phantom, state, jit)

    JitState::JitState( const string& a_strName, bitfield modifiers /*= bitfield()*/ ) : State(a_strName, modifiers)
    , m_pEnterMemberFunction(nullptr)
    , m_pUpdateMemberFunction(nullptr)
    , m_pLeaveMemberFunction(nullptr)
    , m_pEnterClosure(nullptr)
    , m_pUpdateClosure(nullptr)
    , m_pLeaveClosure(nullptr)
    , m_bCompiled(false)
{
    jit_type_t this_t = jit_type_void_ptr;
    m_ClosureSignature = jit_type_create_signature(jit_abi_thiscall, jit_type_void, &this_t, 1, 0);
}


void JitState::copyHierarchy( JitStateMachine* a_pStateMachine, State* a_pSourceState )
{
    size_t i = 0;
    size_t count = a_pSourceState->getTrackCount();
    m_Tracks.resize(count);
    for(;i<count;++i)
    {
        m_Tracks[i] = a_pStateMachine->getTrack(a_pSourceState->getTrack(i)->getIndex());
        static_cast<JitTrack*>(m_Tracks[i])->m_pParentState = this;
        static_cast<JitTrack*>(m_Tracks[i])->copyHierarchy(a_pStateMachine, a_pSourceState->getTrack(i));
    }
}

class FakeClosure
{
public:
    void method()
    {

    }
};

void JitState::compile()
{
    o_assert(!m_bCompiled);
    m_bCompiled = true;
    if(m_pEnterMemberFunction AND m_pEnterMemberFunction->getJitFunction())
    {
        m_pEnterClosure = m_pEnterMemberFunction->getClosurePointer();
    }
    if(m_pUpdateMemberFunction AND m_pUpdateMemberFunction->getJitFunction())
    {
        m_pUpdateClosure = m_pUpdateMemberFunction->getClosurePointer();
    }
    if(m_pLeaveMemberFunction AND m_pLeaveMemberFunction->getJitFunction())
    {
        m_pLeaveClosure = m_pLeaveMemberFunction->getClosurePointer();
    }
    auto closureptr = &FakeClosure::method;
    void* ptr = *((void**)&closureptr);
    if(m_pEnterClosure == nullptr)
    {
        m_pEnterClosure = ptr;
    }
    if(m_pUpdateClosure == nullptr)
    {
        m_pUpdateClosure = ptr;
    }
    if(m_pLeaveClosure == nullptr)
    {
        m_pLeaveClosure = ptr;
    }
}

reflection::jit::JitInstanceMemberFunction* JitState::createEnterMemberFunction( void )
{
    o_assert(m_pEnterMemberFunction == nullptr); 
    o_assert(m_pOwner != nullptr, "this JitState must be added to a JitTrack, itself attached to a JitStateMachine"); 
    m_pEnterMemberFunction = o_new(reflection::jit::JitInstanceMemberFunction)(string("PHANTOM_RESERVED_")+m_strName+"_enter", StateMachine::StateMemberFunctionSignature(), m_bfModifiers);
    reflection::jit::JitClass* pClass = as<reflection::jit::JitClass*>(getOwnerStateMachine()->getOwnerClass());
    o_assert(pClass);
    pClass->addInstanceMemberFunction(m_pEnterMemberFunction);
    return m_pEnterMemberFunction;
}

reflection::jit::JitInstanceMemberFunction* JitState::createUpdateMemberFunction( void )
{
    o_assert(m_pUpdateMemberFunction == nullptr); 
    o_assert(m_pOwner != nullptr, "this JitState must be added to a JitTrack, itself attached to a JitStateMachine"); 
    m_pUpdateMemberFunction = o_new(reflection::jit::JitInstanceMemberFunction)(string("PHANTOM_RESERVED_")+m_strName+"_update", StateMachine::StateMemberFunctionSignature(), m_bfModifiers);
    reflection::jit::JitClass* pClass = as<reflection::jit::JitClass*>(getOwnerStateMachine()->getOwnerClass());
    o_assert(pClass);
    pClass->addInstanceMemberFunction(m_pUpdateMemberFunction);
    return m_pUpdateMemberFunction;
}

reflection::jit::JitInstanceMemberFunction* JitState::createLeaveMemberFunction( void )
{
    o_assert(m_pLeaveMemberFunction == nullptr); 
    o_assert(m_pOwner != nullptr, "this JitState must be added to a JitTrack, itself attached to a JitStateMachine"); 
    m_pLeaveMemberFunction = o_new(reflection::jit::JitInstanceMemberFunction)(string("PHANTOM_RESERVED_")+m_strName+"_leave", StateMachine::StateMemberFunctionSignature(), m_bfModifiers);
    reflection::jit::JitClass* pClass = as<reflection::jit::JitClass*>(getOwnerStateMachine()->getOwnerClass());
    o_assert(pClass);
    pClass->addInstanceMemberFunction(m_pLeaveMemberFunction);
    return m_pLeaveMemberFunction;
}


o_namespace_end(phantom, state, jit)