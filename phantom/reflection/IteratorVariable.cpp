/* ******************* Includes ****************** */
#include "phantom/phantom.h"
/* ** The Class Header must be the last #include * */
#include "IteratorVariable.h"
/* *********************************************** */
o_cpp_begin

ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP

boolean IteratorVariable::hasNext() const
{
    return NOT(m_pContainerClass->isEndIterator(m_pContainer, const_cast<IteratorVariable*>(this)));
}

o_cpp_end