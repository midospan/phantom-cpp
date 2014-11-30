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

Expression* ComponentClass::solveExpression( Expression* a_pLeftExpression , const string& a_strName , const vector<TemplateElement*>* a_pTS, const vector<LanguageElement*>* a_pFS, modifiers_t a_Modifiers ) const
{
    return Class::solveExpression(a_pLeftExpression, a_strName, a_pTS, a_pFS, a_Modifiers);
}

void ComponentClass::fetchExpressions( Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter, uint a_uiSerializationMask ) const
{
    if(a_Filter(getPointedClass()->pointerType()))
    {
        out.push_back(a_pInstanceExpression->clone()->dereference()->address());
    }
}

o_namespace_end(phantom, reflection)