/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "StateMachineElement.h"
#include "StateMachineElement.hxx"
/* *********************************************** */
o_registerN((phantom, reflection), StateMachineElement);

o_namespace_begin(phantom, reflection) 

void StateMachineElement::setOwnerStateMachine( StateMachine* a_pStateMachine )
{
    m_pOwner = a_pStateMachine;
}

o_namespace_end(phantom, reflection) 