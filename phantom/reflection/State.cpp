/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/State.h>
#include <phantom/reflection/State.hxx>
#include <phantom/reflection/Compiler.h>
/* *********************************************** */
o_registerN((phantom, reflection), State);

o_namespace_begin(phantom, reflection) 

Class* const State::metaType = o_type_of(State);

State::State( const string& a_strName , modifiers_t modifiers /*= 0*/) 
    : StateMachineElement(a_strName, modifiers)
    , m_pParentTrack(NULL)
    , m_uiKey(0xffffffff)
    , m_uiIndexInTrack(0xffffffff)
    , m_uiIndex(0xffffffff)
{
    m_pCompilationData = new state_compilation_data;
}

State::State(const string& a_strName, uint a_uiOrderingFactor, modifiers_t modifiers /*= 0*/)
    : StateMachineElement(a_strName, modifiers)
    , m_pParentTrack(NULL)
    , m_uiOrderingFactor(a_uiOrderingFactor)
    , m_uiKey(0xffffffff)
    , m_uiIndex(0xffffffff)
    , m_pCompilationData(nullptr)
{

}

State::~State( void )
{
    delete m_pCompilationData;
}

void State::addTrack( Track* a_pTrack )
{
    o_assert(getOwnerStateMachine(), "a State must be attached to a track attached itself to a StateMachine to receive child tracks");
    m_Tracks.push_back(a_pTrack);
    a_pTrack->setParentState(this);
    getOwnerStateMachine()->registerTrack(a_pTrack);
}

void State::removeTrack( Track* a_pTrack )
{
    track_vector::iterator it = m_Tracks.begin();
    for(;it != m_Tracks.end(); ++it)
    {
        if((*it) == a_pTrack) break;
    }
    if(it != m_Tracks.end())
    {
        m_Tracks.erase(it);
    }
    a_pTrack->m_pParentState = NULL;
}


void State::replaceTrack( Track* a_pOld, Track* a_pNew )
{
    track_vector::iterator it = m_Tracks.begin();
    for(;it != m_Tracks.end(); ++it)
    {
        if((*it) == a_pOld) break;
    }
    o_assert(it != m_Tracks.end());
    *it = a_pNew;
    a_pOld->m_pParentState = NULL;
    a_pNew->m_pParentState = this;
}

Track* State::getTrack( const string& a_strName ) const
{
    track_vector::const_iterator it = m_Tracks.begin();
    for( ; it != m_Tracks.end();++it)
    {
        if((*it)->getName() == a_strName) return *it;
    }
    return NULL;
}

bool State::equals( LanguageElement* a_pOther ) const
{
    if(a_pOther == this) return true;
    if(NOT(as<State*>(a_pOther))) return false;
    if(static_cast<State*>(a_pOther)->getName() != getName()) return false;
    Class* pThisOwner = getOwnerStateMachine()->getOwnerClass();
    Class* pOtherOwner = static_cast<State*>(a_pOther)->getOwnerStateMachine()->getOwnerClass();
    Type::ERelation relation = pOtherOwner->getRelationWith(pThisOwner);
    return relation == Type::e_Relation_Equal
        OR relation == Type::e_Relation_Child
        OR relation == Type::e_Relation_Parent;
}

Track* State::getTrackCascade( const string& a_strName ) const
{
    o_foreach(Track* pTrack, m_Tracks)
    {
        if(pTrack->getName() == a_strName)
        {
            return pTrack;
        }
        o_foreach(State* pState, pTrack->m_States)
        {
            Track* pTrack = pState->getTrackCascade(a_strName);
            if(pTrack) return pTrack;
        }
    }
    return NULL;
}

void State::enter( dynamic_state_machine_data* smdataptr )
{
    o_assert(m_pCompilationData);
    o_State_TraceEnter();
    o_assert(m_pCompilationData->m_pEnterClosure);
    void* args[1] = { &smdataptr->owner };
    m_pCompilationData->m_ClosureCallDelegate( m_pCompilationData->m_pEnterClosure, args, 1, nullptr);
    o_foreach(Track* pTrack, m_Tracks)
    {
        ((Track*)pTrack)->enter(smdataptr);
    }
}

void State::update( dynamic_state_machine_data* smdataptr )
{
    o_assert(m_pCompilationData);
    o_assert(m_pCompilationData->m_pUpdateClosure);
    void* args[1] = { &smdataptr->owner };
    m_pCompilationData->m_ClosureCallDelegate( m_pCompilationData->m_pUpdateClosure, args, 1, nullptr);
    o_foreach(Track* pTrack, m_Tracks)
    {
        ((Track*)pTrack)->update(smdataptr);
    }
}

void State::leave( dynamic_state_machine_data* smdataptr )
{
    o_assert(m_pCompilationData);
    o_foreach(Track* pTrack, m_Tracks)
    {
        ((Track*)pTrack)->leave(smdataptr);
    }
    o_State_TraceLeave();
    o_assert(m_pCompilationData->m_pLeaveClosure);
    void* args[1] = { &smdataptr->owner };
    m_pCompilationData->m_ClosureCallDelegate( m_pCompilationData->m_pLeaveClosure, args, 1, nullptr);
}

void State::copyHierarchy( StateMachine* a_pStateMachine, State* a_pSourceState )
{
    size_t i = 0;
    size_t count = a_pSourceState->getTrackCount();
    m_Tracks.resize(count);
    for(;i<count;++i)
    {
        m_Tracks[i] = a_pStateMachine->getTrack(a_pSourceState->getTrack(i)->getIndex());
        static_cast<Track*>(m_Tracks[i])->m_pParentState = this;
        static_cast<Track*>(m_Tracks[i])->copyHierarchy(a_pStateMachine, a_pSourceState->getTrack(i));
    }
}

class FakeClosure
{
public:
    void method()
    {

    }
};

MemberFunction* State::createEnterMemberFunction( void )
{
    o_assert(m_pCompilationData->m_pEnterMemberFunction == nullptr); 
    o_assert(m_pOwner != nullptr, "this State must be added to a Track, itself attached to a StateMachine"); 
    m_pCompilationData->m_pEnterMemberFunction = o_new(MemberFunction)(string("PHANTOM_RESERVED_")+m_strName+"_enter", StateMachine::StateMemberFunctionSignature(), m_Modifiers);
    Class* pClass = as<Class*>(getOwnerStateMachine()->getOwnerClass());
    o_assert(pClass);
    pClass->addMemberFunction(m_pCompilationData->m_pEnterMemberFunction);
    return m_pCompilationData->m_pEnterMemberFunction;
}

MemberFunction* State::createUpdateMemberFunction( void )
{
    o_assert(m_pCompilationData->m_pUpdateMemberFunction == nullptr); 
    o_assert(m_pOwner != nullptr, "this State must be added to a Track, itself attached to a StateMachine"); 
    m_pCompilationData->m_pUpdateMemberFunction = o_new(MemberFunction)(string("PHANTOM_RESERVED_")+m_strName+"_update", StateMachine::StateMemberFunctionSignature(), m_Modifiers);
    Class* pClass = as<Class*>(getOwnerStateMachine()->getOwnerClass());
    o_assert(pClass);
    pClass->addMemberFunction(m_pCompilationData->m_pUpdateMemberFunction);
    return m_pCompilationData->m_pUpdateMemberFunction;
}

MemberFunction* State::createLeaveMemberFunction( void )
{
    o_assert(m_pCompilationData->m_pLeaveMemberFunction == nullptr); 
    o_assert(m_pOwner != nullptr, "this State must be added to a Track, itself attached to a StateMachine"); 
    m_pCompilationData->m_pLeaveMemberFunction = o_new(MemberFunction)(string("PHANTOM_RESERVED_")+m_strName+"_leave", StateMachine::StateMemberFunctionSignature(), m_Modifiers);
    Class* pClass = as<Class*>(getOwnerStateMachine()->getOwnerClass());
    o_assert(pClass);
    pClass->addMemberFunction(m_pCompilationData->m_pLeaveMemberFunction);
    return m_pCompilationData->m_pLeaveMemberFunction;
}

o_namespace_end(phantom, reflection)
