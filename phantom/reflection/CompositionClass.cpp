/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "CompositionClass.h"
#include "CompositionClass.hxx"
#include <phantom/reflection/ConstantExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), CompositionClass);
o_registerN((phantom, reflection), CompositionGetSetExpression);
o_registerN((phantom, reflection), CompositionInsertRemoveExpression);

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

void CompositionClass::fetchExpressions( Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter, uint a_uiSerializationMask ) const
{
    if(a_Filter(getComponentClass()->pointerType()))
    {
        void* pInstance = a_pInstanceExpression->loadEffectiveAddress();
        size_t count = this->count(pInstance);
        for(size_t i = 0; i<count; ++i)
        {
            out.push_back(o_new(CompositionInsertRemoveExpression)(a_pInstanceExpression, o_new(ConstantExpression)(phantom::constant<size_t>(i)), const_cast<CompositionClass*>(this)));
        }
    }
}

CompositionGetSetExpression::CompositionGetSetExpression( Expression* a_pLeftExpression, Expression* a_pIndexExpression, CompositionClass* a_pCompositionClass ) 
    : Expression(a_pLeftExpression->getValueType()->replicate(a_pCompositionClass->getComponentClass()->pointerType()))
    , m_pLeftExpression(a_pLeftExpression)
    , m_pIndexExpression(a_pIndexExpression)
    , m_pCompositionClass(a_pCompositionClass)
    , m_pBufferedPointer(nullptr)
{
    addSubExpression(m_pLeftExpression);
    addSubExpression(m_pIndexExpression);
    reflection::Type* pPointerType = a_pCompositionClass->getComponentClass()->pointerType();
}

void CompositionGetSetExpression::internalEval( void* a_pDest ) const
{
    size_t uiIndex = 0;
    m_pIndexExpression->load(&uiIndex);
    m_pCompositionClass->get(m_pLeftExpression->loadEffectiveAddress(), uiIndex, &m_pBufferedPointer);
    *((void**)a_pDest) = &m_pBufferedPointer;
}

void CompositionGetSetExpression::setValue( void const* a_pSrc ) const
{
    size_t uiIndex = 0;
    m_pIndexExpression->load(&uiIndex);
    void* pCaller = m_pLeftExpression->loadEffectiveAddress();
    m_pCompositionClass->set(pCaller, uiIndex, a_pSrc);
    m_pCompositionClass->get(pCaller, uiIndex, &m_pBufferedPointer); // store the value back in the buffer
}

CompositionGetSetExpression* CompositionGetSetExpression::clone() const
{
    return o_new(CompositionGetSetExpression)(m_pLeftExpression, m_pIndexExpression, m_pCompositionClass);
}

void CompositionGetSetExpression::flush() const
{
    size_t uiIndex = 0;
    m_pIndexExpression->load(&uiIndex);
    void* pComposition = m_pLeftExpression->loadEffectiveAddress();
    bool bBlockSignal = areSignalsBlocked();
    if(bBlockSignal)
    {
        m_pCompositionClass->blockSignals(pComposition);
    }
    m_pCompositionClass->set(pComposition, uiIndex, &m_pBufferedPointer);
    if(bBlockSignal)
    {
        m_pCompositionClass->unblockSignals(pComposition);
    }
    m_pLeftExpression->flush();
}

string CompositionClass_InsertRemoveExpression_formatIndexString(string a_Input, size_t a_CharCount)
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

CompositionInsertRemoveExpression::CompositionInsertRemoveExpression( Expression* a_pLeftExpression, Expression* a_pIndexExpression, CompositionClass* a_pCompositionClass ) 
    : Expression(a_pLeftExpression->getValueType()->replicate(a_pCompositionClass->getComponentClass()->pointerType()))
    , m_pLeftExpression(a_pLeftExpression)
    , m_pIndexExpression(a_pIndexExpression)
    , m_pCompositionClass(a_pCompositionClass)
    , m_pBufferedPointer(nullptr)
{
    addSubExpression(m_pLeftExpression);
    addSubExpression(m_pIndexExpression);
    reflection::Type* pPointerType = a_pCompositionClass->getComponentClass()->pointerType();
}

void CompositionInsertRemoveExpression::internalEval( void* a_pDest ) const
{
    size_t uiIndex = 0;
    m_pIndexExpression->load(&uiIndex);
    void* pCaller = m_pLeftExpression->loadEffectiveAddress();
    if(uiIndex < m_pCompositionClass->count(pCaller))
    {
        m_pCompositionClass->get(pCaller, uiIndex, &m_pBufferedPointer);
    }
    else 
    {
        m_pBufferedPointer = nullptr;
    }
    *((void**)a_pDest) = &m_pBufferedPointer;
}

void CompositionInsertRemoveExpression::setValue( void const* a_pSrc ) const
{
    size_t uiIndex = 0;
    m_pIndexExpression->load(&uiIndex);
    void* pComposition = m_pLeftExpression->loadEffectiveAddress();
    void* pComponent = *((void**)a_pSrc);
    bool bBlockSignal = areSignalsBlocked();
    if(bBlockSignal)
    {
        m_pCompositionClass->blockSignals(pComposition);
    }
    if(pComponent)
    {
        m_pCompositionClass->insert(pComposition, uiIndex, a_pSrc);
    }
    else 
    {
        m_pCompositionClass->remove(pComposition, uiIndex);
    }
    if(bBlockSignal)
    {
        m_pCompositionClass->unblockSignals(pComposition);
    }
}

CompositionInsertRemoveExpression* CompositionInsertRemoveExpression::clone() const
{
    return o_new(CompositionInsertRemoveExpression)(m_pLeftExpression, m_pIndexExpression, m_pCompositionClass);
}

void CompositionInsertRemoveExpression::flush() const
{
    size_t uiIndex = 0;
    m_pIndexExpression->load(&uiIndex);
    void* pComposition = m_pLeftExpression->loadEffectiveAddress();
    bool bBlockSignal = areSignalsBlocked();
    if(bBlockSignal)
    {
        m_pCompositionClass->blockSignals(pComposition);
    }
    if(m_pBufferedPointer)
    {
        m_pCompositionClass->insert(pComposition, uiIndex, &m_pBufferedPointer);
    }
    else 
    {
        m_pCompositionClass->remove(pComposition, uiIndex);
    }
    if(bBlockSignal)
    {
        m_pCompositionClass->unblockSignals(pComposition);
    }
    m_pLeftExpression->flush();
}

o_namespace_end(phantom, reflection)