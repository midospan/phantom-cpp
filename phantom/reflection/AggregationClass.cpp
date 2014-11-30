/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "AggregationClass.h"
#include "AggregationClass.hxx"
#include <phantom/reflection/ConstantExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), AggregationClass);
o_registerNC((phantom, reflection), (AggregationClass), GetSetExpression);
o_registerNC((phantom, reflection), (AggregationClass), InsertRemoveExpression);

o_namespace_begin(phantom, reflection)

o_define_meta_type(AggregationClass) = o_type_of(AggregationClass);


bool AggregationClass::referencesData( const void* a_pContainer, const phantom::data& a_Data ) const
{
    ConstIterator* pIterator = begin(a_pContainer);
    o_assert(m_pAggregateClass->pointerType() == pIterator->getValueType());

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

Expression* AggregationClass::solveExpression( Expression* a_pLeftExpression , const string& a_strName , const vector<TemplateElement*>* a_pTS, const vector<LanguageElement*>* a_pFS, modifiers_t a_Modifiers ) const
{
    if(a_strName == "operator[]" AND a_pFS AND a_pFS->size() == 1 && a_pFS->back()->asExpression() && a_pFS->back()->asExpression()->getValueType()->isImplicitlyConvertibleTo(typeOf<size_t>()))
    {
        return o_new(GetSetExpression)(a_pLeftExpression, a_pFS->back()->asExpression()->implicitCast(typeOf<size_t>()), const_cast<AggregationClass*>(this));
    }
    else if(a_strName == "operator()" AND a_pFS AND a_pFS->size() == 1 && a_pFS->back()->asExpression() && a_pFS->back()->asExpression()->getValueType()->isImplicitlyConvertibleTo(typeOf<size_t>()))
    {
        return o_new(InsertRemoveExpression)(a_pLeftExpression, a_pFS->back()->asExpression()->implicitCast(typeOf<size_t>()), const_cast<AggregationClass*>(this));
    }
    return Class::solveExpression(a_pLeftExpression, a_strName, a_pTS, a_pFS, a_Modifiers);
}

void AggregationClass::fetchExpressions( Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter, uint a_uiSerializationMask ) const
{
    if(a_Filter(getAggregateClass()->pointerType()))
    {
        void* pInstance = a_pInstanceExpression->loadEffectiveAddress();
        size_t count = this->count(pInstance);
        for(size_t i = 0; i<count; ++i)
        {
            out.push_back(o_new(InsertRemoveExpression)(a_pInstanceExpression, o_new(ConstantExpression)(phantom::constant<size_t>(i)), const_cast<AggregationClass*>(this)));
        }
    }
}

AggregationClass::GetSetExpression::GetSetExpression( Expression* a_pLeftExpression, Expression* a_pIndexExpression, AggregationClass* a_pAggregationClass ) 
    : Expression(a_pLeftExpression->isConstExpression() 
                    ? a_pAggregationClass->getAggregateClass()->pointerType()->constType()->referenceType()
                    : a_pAggregationClass->getAggregateClass()->pointerType()->referenceType()
    , "("+a_pLeftExpression->getName()+")["+a_pIndexExpression->getName()+"]", a_pLeftExpression->getModifiers())
    , m_pLeftExpression(a_pLeftExpression)
    , m_pIndexExpression(a_pIndexExpression)
    , m_pAggregationClass(a_pAggregationClass)
    , m_pBufferedPointer(nullptr)
{
    addSubExpression(m_pLeftExpression);
    addSubExpression(m_pIndexExpression);
    reflection::Type* pPointerType = a_pAggregationClass->getAggregateClass()->pointerType();
}

void AggregationClass::GetSetExpression::getValue( void* a_pDest ) const
{
    size_t uiIndex = 0;
    m_pIndexExpression->load(&uiIndex);
    m_pAggregationClass->get(m_pLeftExpression->loadEffectiveAddress(), uiIndex, &m_pBufferedPointer);
    *((void**)a_pDest) = &m_pBufferedPointer;
}

void AggregationClass::GetSetExpression::setValue( void const* a_pSrc ) const
{
    size_t uiIndex = 0;
    m_pIndexExpression->load(&uiIndex);
    void* pCaller = m_pLeftExpression->loadEffectiveAddress();
    m_pAggregationClass->set(pCaller, uiIndex, a_pSrc);
    m_pAggregationClass->get(pCaller, uiIndex, &m_pBufferedPointer); // store the value back in the buffer
}

AggregationClass::GetSetExpression* AggregationClass::GetSetExpression::clone() const
{
    return o_new(GetSetExpression)(m_pLeftExpression, m_pIndexExpression, m_pAggregationClass);
}

void AggregationClass::GetSetExpression::flush() const
{
    size_t uiIndex = 0;
    m_pIndexExpression->load(&uiIndex);
    m_pAggregationClass->set(m_pLeftExpression->loadEffectiveAddress(), uiIndex, &m_pBufferedPointer);
    m_pLeftExpression->flush();
}

string AggregationClass_InsertRemoveExpression_formatIndexString(string a_Input, size_t a_CharCount)
{
    long long value = 0;
    if(sscanf(a_Input.c_str(), "%d", &value))
    {
        while(a_Input.size() < a_CharCount)
        {
            a_Input = ' ' + a_Input;
        }
    }
    return a_Input;
}

AggregationClass::InsertRemoveExpression::InsertRemoveExpression( Expression* a_pLeftExpression, Expression* a_pIndexExpression, AggregationClass* a_pAggregationClass ) 
    : Expression(a_pLeftExpression->isConstExpression() 
    ? a_pAggregationClass->getAggregateClass()->pointerType()->constType()->referenceType()
    : a_pAggregationClass->getAggregateClass()->pointerType()->referenceType()
    , "("+a_pLeftExpression->getName()+")("+AggregationClass_InsertRemoveExpression_formatIndexString(a_pIndexExpression->getName(), 10)+")", a_pLeftExpression->getModifiers())
    , m_pLeftExpression(a_pLeftExpression)
    , m_pIndexExpression(a_pIndexExpression)
    , m_pAggregationClass(a_pAggregationClass)
    , m_pBufferedPointer(nullptr)
{
    addSubExpression(m_pLeftExpression);
    addSubExpression(m_pIndexExpression);
    reflection::Type* pPointerType = a_pAggregationClass->getAggregateClass()->pointerType();
}

void AggregationClass::InsertRemoveExpression::getValue( void* a_pDest ) const
{
    size_t uiIndex = 0;
    m_pIndexExpression->load(&uiIndex);
    void* pCaller = m_pLeftExpression->loadEffectiveAddress();
    if(uiIndex < m_pAggregationClass->count(pCaller))
    {
        m_pAggregationClass->get(pCaller, uiIndex, &m_pBufferedPointer);
    }
    else 
    {
        m_pBufferedPointer = nullptr;
    }
    *((void**)a_pDest) = &m_pBufferedPointer;
}

void AggregationClass::InsertRemoveExpression::setValue( void const* a_pSrc ) const
{
    size_t uiIndex = 0;
    m_pIndexExpression->load(&uiIndex);
    void* pCaller = m_pLeftExpression->loadEffectiveAddress();
    void* pAggregate = *((void**)a_pSrc);
    if(pAggregate)
    {
        m_pAggregationClass->insert(pCaller, uiIndex, a_pSrc);
    }
    else 
    {
        m_pAggregationClass->remove(pCaller, uiIndex);
    }
}

AggregationClass::InsertRemoveExpression* AggregationClass::InsertRemoveExpression::clone() const
{
    return o_new(InsertRemoveExpression)(m_pLeftExpression, m_pIndexExpression, m_pAggregationClass);
}

void AggregationClass::InsertRemoveExpression::flush() const
{
    size_t uiIndex = 0;
    m_pIndexExpression->load(&uiIndex);
    void* pCaller = m_pLeftExpression->loadEffectiveAddress();
    if(m_pBufferedPointer)
    {
        m_pAggregationClass->insert(pCaller, uiIndex, &m_pBufferedPointer);
    }
    else 
    {
        m_pAggregationClass->remove(pCaller, uiIndex);
    }
    m_pLeftExpression->flush();
}

o_namespace_end(phantom, reflection)