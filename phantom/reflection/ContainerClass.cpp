/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/ContainerClass.h>
#include <phantom/reflection/ContainerClass.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), ContainerClass);

o_namespace_begin(phantom, reflection)

o_define_meta_type(ContainerClass);

bool ContainerClass::referencesData( const void* a_pContainer, const phantom::data& a_Data ) const
{
    ConstIterator* pIterator = begin(a_pContainer);
    o_assert(m_pValueType == pIterator->getValueType());

    bool result = false;

    while(pIterator->hasNext())
    {
        const void* ptr = pIterator->pointer();
        if(m_pValueType->referencesData(ptr, a_Data))
        {
            return true;
        }
    }

    release(pIterator);

    return result;
}



o_namespace_end(phantom, reflection)