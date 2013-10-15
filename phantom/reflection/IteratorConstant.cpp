/* ******************* Includes ****************** */
#include "phantom/phantom.h"
/* ** The Class Header must be the last #include * */
#include "IteratorConstant.h"
/* *********************************************** */
o_cpp_begin

ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP

boolean IteratorConstant::hasNext() const
{
    return NOT(m_pContainerClass->isEndIterator(m_pContainer, const_cast<IteratorConstant*>(this)));
}

o_cpp_end