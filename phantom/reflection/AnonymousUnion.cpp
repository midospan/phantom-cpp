/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/AnonymousUnion.h>
#include <phantom/reflection/AnonymousUnion.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), AnonymousUnion);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(AnonymousUnion) = o_type_of(AnonymousUnion);

AnonymousUnion::AnonymousUnion( modifiers_t modifiers /*= 0*/ ) 
    : AnonymousSection(modifiers)
{

}

o_namespace_end(phantom, reflection)
