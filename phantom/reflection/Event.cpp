/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/Event.h>
#include <phantom/reflection/Event.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), Event);

o_namespace_begin(phantom, reflection) 

Event::Event( const string& a_strName, uint id, modifiers_t a_Modifiers /*= 0*/ ) 
: StateMachineElement(a_strName, a_Modifiers)
, m_uiId(id)
{

}

o_namespace_end(phantom, reflection)

