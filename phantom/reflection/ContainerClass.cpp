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

void ContainerClass::release( Iterator* a_pIterator ) const
{
    a_pIterator->terminate(); a_pIterator->deleteNow();
}

void ContainerClass::release( ConstIterator* a_pIterator ) const
{
    a_pIterator->terminate(); a_pIterator->deleteNow();
}

/*

void ContainerClass::createKeyAccesses( Expression* a_pLeft, vector<Expression*>& out ) const
{
    if(!a_pLeft->isAddressable()) return;
    createKeyAccesses(a_pLeft->getAddress(), out);
}

void ContainerClass::createValueAccesses( Expression* a_pLeft, vector<Expression*>& out ) const
{
    if(!a_pLeft->isAddressable()) return;
    createValueAccesses(a_pLeft->getAddress(), out);
}

void ContainerClass::createMappedAccesses( Expression* a_pLeft, vector<Expression*>& out ) const
{
    if(!a_pLeft->isAddressable()) return;
    createMappedAccesses(a_pLeft->getAddress(), out);
}*/



o_namespace_end(phantom, reflection)