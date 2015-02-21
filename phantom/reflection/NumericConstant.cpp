/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/NumericConstant.h>
#include <phantom/reflection/NumericConstant.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), NumericConstant);

o_namespace_begin(phantom, reflection) 

o_static_assert(has_reflection_cascade<phantom::reflection::NumericConstant>::value);

Class* const NumericConstant::metaType = o_type_of(phantom::reflection::NumericConstant);

o_namespace_end(phantom, reflection)
