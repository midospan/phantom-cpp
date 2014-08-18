/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "CompositionClass.h"
#include "CompositionClass.hxx"
/* *********************************************** */
o_registerN((phantom, reflection), CompositionClass);
o_registerNC((phantom, reflection), (CompositionClass), GetSetExpression);

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

Expression* CompositionClass::solveExpression( Expression* a_pLeftExpression , const string& a_strName , const vector<TemplateElement*>* a_pTS, const vector<LanguageElement*>* a_pFS, bitfield a_Modifiers ) const
{
    Expression* pExpression = Class::solveExpression(a_pLeftExpression, a_strName, a_pTS, a_pFS, a_Modifiers);
    if(pExpression) return pExpression;
    if(a_strName == "operator[]" AND a_pFS AND a_pFS->size() == 1 && a_pFS->back()->asExpression() && a_pFS->back()->asExpression()->getValueType()->isImplicitlyConvertibleTo(typeOf<size_t>()))
    {
        return o_new(GetSetExpression)(a_pLeftExpression, a_pFS->back()->asExpression()->implicitCast(typeOf<size_t>()), const_cast<CompositionClass*>(this));
    }
    return nullptr;
}

CompositionClass::GetSetExpression::GetSetExpression( Expression* a_pLeftExpression, Expression* a_pIndexExpression, CompositionClass* a_pCompositionClass ) 
    : Expression(a_pCompositionClass->getComponentClass()->pointerType(), a_pLeftExpression->getName()+"["+a_pIndexExpression->getName()+"]")
    , m_pLeftExpression(a_pLeftExpression)
    , m_pIndexExpression(a_pIndexExpression)
    , m_pCompositionClass(a_pCompositionClass)
{
    addElement(m_pLeftExpression);
    addElement(m_pIndexExpression);
}

void CompositionClass::GetSetExpression::getValue( void* a_pDest ) const
{
    void* pCaller = 0;
    m_pLeftExpression->getValue(&pCaller);
    size_t uiIndex = 0;
    m_pIndexExpression->getValue(&uiIndex);
    m_pCompositionClass->get(pCaller, uiIndex, a_pDest);
}

void CompositionClass::GetSetExpression::setValue( void const* a_pSrc ) const
{
    void* pCaller = 0;
    m_pLeftExpression->getValue(&pCaller);
    size_t uiIndex = 0;
    m_pIndexExpression->getValue(&uiIndex);
    m_pCompositionClass->set(pCaller, uiIndex, a_pSrc);
}

CompositionClass::GetSetExpression* CompositionClass::GetSetExpression::clone() const
{
    return o_new(GetSetExpression)(m_pLeftExpression->clone(), m_pIndexExpression->clone(), m_pCompositionClass);
}


o_namespace_end(phantom, reflection)