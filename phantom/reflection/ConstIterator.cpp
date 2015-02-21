/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "ConstIterator.h"
#include "ConstIterator.hxx"
/* *********************************************** */
o_registerN((phantom, reflection), ConstIterator);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(ConstIterator) = o_type_of(ConstIterator);

o_namespace_end(phantom, reflection)