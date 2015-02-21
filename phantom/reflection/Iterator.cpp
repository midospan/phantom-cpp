/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Iterator.h"
#include "Iterator.hxx"
/* *********************************************** */
o_registerN((phantom, reflection), Iterator);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(Iterator) = o_type_of(Iterator);

o_namespace_end(phantom, reflection)