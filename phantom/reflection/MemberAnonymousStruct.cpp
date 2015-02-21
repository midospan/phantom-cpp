/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/MemberAnonymousStruct.h>
#include <phantom/reflection/MemberAnonymousStruct.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), MemberAnonymousStruct);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(MemberAnonymousStruct) = o_type_of(MemberAnonymousStruct);

MemberAnonymousStruct::MemberAnonymousStruct( modifiers_t modifiers /*= 0*/ ) 
    : MemberAnonymousSection(modifiers)
{

}

o_namespace_end(phantom, reflection)
