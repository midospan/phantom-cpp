/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/Range.h>
#include <phantom/reflection/Range.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), Range);

o_namespace_begin(phantom, reflection)

Class* const Range::metaType = type_of<Range>::object();

Range::Range( Type* a_pType ) : m_pType(a_pType)
{
    // o_assert(a_pType->hasLess() && a_pType->hasEqualTo());
}


o_namespace_end(phantom, reflection)