/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/MemberAnonymousUnion.h>
#include <phantom/reflection/MemberAnonymousUnion.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), MemberAnonymousUnion);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(MemberAnonymousUnion) = o_type_of(MemberAnonymousUnion);

MemberAnonymousUnion::MemberAnonymousUnion( modifiers_t modifiers /*= 0*/ ) 
    : MemberAnonymousSection(modifiers)
{

}

o_namespace_end(phantom, reflection)
