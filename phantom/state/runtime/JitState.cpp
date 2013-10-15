/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "JitState.h"
#include "JitStateMachine.h"
#include <phantom/reflection/runtime/JitInstanceMethod.h>
#include <phantom/reflection/runtime/JitClass.h>
/* *********************************************** */
o_registerN((phantom, state, runtime), JitState);

o_namespace_begin(phantom, state, runtime)

    JitState::JitState( const string& a_strName, bitfield modifiers /*= bitfield()*/ ) : State(a_strName, modifiers)
    , m_pEnterMethod(nullptr)
    , m_pUpdateMethod(nullptr)
    , m_pLeaveMethod(nullptr)
    , m_pEnterClosure(nullptr)
    , m_pUpdateClosure(nullptr)
    , m_pLeaveClosure(nullptr)
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

void JitState::finalize()
{
    if(m_pEnterMethod AND m_pEnterMethod->getJitFunction())
    {
        m_pEnterClosure = m_pEnterMethod->getClosurePointer();
    }
    if(m_pUpdateMethod AND m_pUpdateMethod->getJitFunction())
    {
        m_pUpdateClosure = m_pUpdateMethod->getClosurePointer();
    }
    if(m_pLeaveMethod AND m_pLeaveMethod->getJitFunction())
    {
        m_pLeaveClosure = m_pLeaveMethod->getClosurePointer();
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

reflection::runtime::JitInstanceMethod* JitState::createEnterMethod( void )
{
    o_assert(m_pEnterMethod == nullptr); 
    o_assert(m_pOwner != nullptr, "this JitState must be added to a JitTrack, itself attached to a JitStateMachine"); 
    m_pEnterMethod = o_new(reflection::runtime::JitInstanceMethod)(string("PHANTOM_RESERVED_")+m_strName+"_enter", StateMachine::StateMethodSignature(), m_bfModifiers);
    reflection::runtime::JitClass* pClass = as<reflection::runtime::JitClass*>(getOwnerStateMachine()->getOwnerClass());
    o_assert(pClass);
    pClass->addInstanceMethod(m_pEnterMethod);
    return m_pEnterMethod;
}

reflection::runtime::JitInstanceMethod* JitState::createUpdateMethod( void )
{
    o_assert(m_pUpdateMethod == nullptr); 
    o_assert(m_pOwner != nullptr, "this JitState must be added to a JitTrack, itself attached to a JitStateMachine"); 
    m_pUpdateMethod = o_new(reflection::runtime::JitInstanceMethod)(string("PHANTOM_RESERVED_")+m_strName+"_update", StateMachine::StateMethodSignature(), m_bfModifiers);
    reflection::runtime::JitClass* pClass = as<reflection::runtime::JitClass*>(getOwnerStateMachine()->getOwnerClass());
    o_assert(pClass);
    pClass->addInstanceMethod(m_pUpdateMethod);
    return m_pUpdateMethod;
}

reflection::runtime::JitInstanceMethod* JitState::createLeaveMethod( void )
{
    o_assert(m_pLeaveMethod == nullptr); 
    o_assert(m_pOwner != nullptr, "this JitState must be added to a JitTrack, itself attached to a JitStateMachine"); 
    m_pLeaveMethod = o_new(reflection::runtime::JitInstanceMethod)(string("PHANTOM_RESERVED_")+m_strName+"_leave", StateMachine::StateMethodSignature(), m_bfModifiers);
    reflection::runtime::JitClass* pClass = as<reflection::runtime::JitClass*>(getOwnerStateMachine()->getOwnerClass());
    o_assert(pClass);
    pClass->addInstanceMethod(m_pLeaveMethod);
    return m_pLeaveMethod;
}


o_namespace_end(phantom, state, runtime)