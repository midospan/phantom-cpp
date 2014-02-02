/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/IteratorConstant.h>
#include <phantom/reflection/IteratorConstant.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), IteratorConstant);
o_namespace_begin(phantom, reflection)

boolean IteratorConstant::hasNext() const
{
    return NOT(m_pContainerClass->isEndIterator(m_pContainer, const_cast<IteratorConstant*>(this)));
}

o_namespace_end(phantom, reflection)