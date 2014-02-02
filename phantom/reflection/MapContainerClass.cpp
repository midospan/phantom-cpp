/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/MapContainerClass.h>
#include <phantom/reflection/MapContainerClass.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), MapContainerClass);
//o_registerN((phantom, reflection), MapValueIteratorVariable);
o_namespace_begin(phantom, reflection)

o_define_meta_type(MapContainerClass);

o_namespace_end(phantom, reflection)