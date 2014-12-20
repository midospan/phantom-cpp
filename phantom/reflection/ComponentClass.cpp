/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "ComponentClass.h"
#include "ComponentClass.hxx"
/* *********************************************** */
o_registerN((phantom, reflection), ComponentClass);

o_namespace_begin(phantom, reflection)

o_define_meta_type(ComponentClass) = o_type_of(ComponentClass);

bool ComponentClass::referencesData( const void* a_pComponent, const phantom::data& a_Data ) const
{
    void* pPointer = nullptr;
    get(a_pComponent, &pPointer);
    return baseOf(pPointer) == a_Data.address();
}

void ComponentClass::fetchExpressions( Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter, uint a_uiSerializationMask ) const
{
    if(a_Filter(getPointedClass()->pointerType()))
    {
        out.push_back(a_pInstanceExpression->clone()->dereference()->address());
    }
}

o_namespace_end(phantom, reflection)