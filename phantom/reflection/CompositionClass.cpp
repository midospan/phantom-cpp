/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "CompositionClass.h"
#include "CompositionClass.hxx"
/* *********************************************** */
o_registerN((phantom, reflection), CompositionClass);

o_namespace_begin(phantom, reflection)

o_define_meta_type(CompositionClass) = o_type_of(CompositionClass);

bool CompositionClass::referencesData( const void* a_pContainer, const phantom::data& a_Data ) const
{
    ConstIterator* pIterator = begin(a_pContainer);
    o_assert(m_pComponentClass->pointerType() == pIterator->getValueType());

    bool result = false;

    while(pIterator->hasNext())
    {
        const void* ptr = pIterator->pointer();
        if(pIterator->getValueType()->referencesData(ptr, a_Data))
        {
            return true;
        }
    }

    release(pIterator);

    return result;
}

o_namespace_end(phantom, reflection)