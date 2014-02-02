/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/IteratorVariable.h>
#include <phantom/reflection/IteratorVariable.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), IteratorVariable);
o_namespace_begin(phantom, reflection)

boolean IteratorVariable::hasNext() const
{
    return NOT(m_pContainerClass->isEndIterator(m_pContainer, const_cast<IteratorVariable*>(this)));
}

o_namespace_end(phantom, reflection)