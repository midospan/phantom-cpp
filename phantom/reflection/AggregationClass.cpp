/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "AggregationClass.h"
#include "AggregationClass.hxx"
#include <phantom/reflection/ConstantExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), AggregationClass);
o_registerN((phantom, reflection), AggregationGetSetExpression);
o_registerN((phantom, reflection), AggregationInsertRemoveExpression);

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

void AggregationClass::fetchExpressions( Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter, uint a_uiSerializationMask ) const
{
    if(a_Filter(getAggregateClass()->pointerType()))
    {
        void* pInstance = a_pInstanceExpression->loadEffectiveAddress();
        size_t count = this->count(pInstance);
        for(size_t i = 0; i<count; ++i)
        {
            out.push_back(o_new(AggregationInsertRemoveExpression)(a_pInstanceExpression, o_new(ConstantExpression)(phantom::constant<size_t>(i)), const_cast<AggregationClass*>(this)));
        }
    }
}

AggregationGetSetExpression::AggregationGetSetExpression( Expression* a_pLeftExpression, Expression* a_pIndexExpression, AggregationClass* a_pAggregationClass ) 
    : Expression(a_pLeftExpression->isConstExpression() 
                    ? a_pAggregationClass->getAggregateClass()->pointerType()->constType()->referenceType()
                    : a_pAggregationClass->getAggregateClass()->pointerType()->referenceType()
    , a_pLeftExpression->getModifiers())
    , m_pLeftExpression(a_pLeftExpression)
    , m_pIndexExpression(a_pIndexExpression)
    , m_pAggregationClass(a_pAggregationClass)
    , m_pBufferedPointer(nullptr)
{
    addSubExpression(m_pLeftExpression);
    addSubExpression(m_pIndexExpression);
    reflection::Type* pPointerType = a_pAggregationClass->getAggregateClass()->pointerType();
}

void AggregationGetSetExpression::internalEval( void* a_pDest ) const
{
    size_t uiIndex = 0;
    m_pIndexExpression->load(&uiIndex);
    m_pAggregationClass->get(m_pLeftExpression->loadEffectiveAddress(), uiIndex, &m_pBufferedPointer);
    *((void**)a_pDest) = &m_pBufferedPointer;
}

AggregationGetSetExpression* AggregationGetSetExpression::clone() const
{
    return o_new(AggregationGetSetExpression)(m_pLeftExpression, m_pIndexExpression, m_pAggregationClass);
}

void AggregationGetSetExpression::flush() const
{
    size_t uiIndex = 0;
    m_pIndexExpression->load(&uiIndex);
    m_pAggregationClass->set(m_pLeftExpression->loadEffectiveAddress(), uiIndex, &m_pBufferedPointer);
    m_pLeftExpression->flush();
}

void AggregationGetSetExpression::setValue( void const* a_pSrc ) const
{
    size_t uiIndex = 0;
    m_pIndexExpression->load(&uiIndex);
    void* pCaller = m_pLeftExpression->loadEffectiveAddress();
    m_pAggregationClass->set(pCaller, uiIndex, a_pSrc);
    m_pAggregationClass->get(pCaller, uiIndex, &m_pBufferedPointer); // store the value back in the buffer
}


AggregationInsertRemoveExpression::AggregationInsertRemoveExpression( Expression* a_pLeftExpression, Expression* a_pIndexExpression, AggregationClass* a_pAggregationClass ) 
    : Expression(a_pLeftExpression->isConstExpression() 
    ? a_pAggregationClass->getAggregateClass()->pointerType()->constType()->referenceType()
    : a_pAggregationClass->getAggregateClass()->pointerType()->referenceType()
    , a_pLeftExpression->getModifiers())
    , m_pLeftExpression(a_pLeftExpression)
    , m_pIndexExpression(a_pIndexExpression)
    , m_pAggregationClass(a_pAggregationClass)
    , m_pBufferedPointer(nullptr)
{
    addSubExpression(m_pLeftExpression);
    addSubExpression(m_pIndexExpression);
    reflection::Type* pPointerType = a_pAggregationClass->getAggregateClass()->pointerType();
}

void AggregationInsertRemoveExpression::internalEval( void* a_pDest ) const
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

AggregationInsertRemoveExpression* AggregationInsertRemoveExpression::clone() const
{
    return o_new(AggregationInsertRemoveExpression)(m_pLeftExpression, m_pIndexExpression, m_pAggregationClass);
}

void AggregationInsertRemoveExpression::setValue( void const* a_pSrc ) const
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

void AggregationInsertRemoveExpression::flush() const
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