/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "StateOrderingComparator.h"
#include "StateOrderingComparator.hxx"
/* *********************************************** */
o_registerN((phantom, reflection), StateOrderingComparator);

o_namespace_begin(phantom, reflection)

int StateOrderingComparator::compare( void* a_pS0, void* a_pS1 ) const
{
    State*    pState0 = phantom::as<State*>(a_pS0);
    State*    pState1 = phantom::as<State*>(a_pS1);
    
    o_assert(pState0);
    o_assert(pState1);

    reflection::Class* pOC0 = pState0->getOwnerStateMachine()->getOwnerClass();
    reflection::Class* pOC1 = pState1->getOwnerStateMachine()->getOwnerClass();
    if(pOC0 == pOC1)
    {
        if(pState1->getOrderingFactor() == pState0->getOrderingFactor()) return 0;
        if(pState1->getOrderingFactor() > pState0->getOrderingFactor()) return 1;
        return -1;
    }
    else
    {
        if(pOC1->isKindOf(pOC0)) return 1;
        o_assert(pOC0->isKindOf(pOC1)); // Compared reflection must be from same class hierarchy
        return -1;
    }
    return 0;
}

StateOrderingComparator* StateOrderingComparator::Instance()
{
    static StateOrderingComparator* s_Instance = NULL;
    if(s_Instance == NULL) 
    {
        s_Instance = o_new(StateOrderingComparator);
    }
    return s_Instance;
}

o_namespace_end(phantom, reflection)