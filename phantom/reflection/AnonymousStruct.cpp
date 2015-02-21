/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/AnonymousStruct.h>
#include <phantom/reflection/AnonymousStruct.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), AnonymousStruct);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(AnonymousStruct) = o_type_of(AnonymousStruct);

AnonymousStruct::AnonymousStruct( modifiers_t modifiers /*= 0*/ ) 
    : AnonymousSection(modifiers)
{

}

o_namespace_end(phantom, reflection)
