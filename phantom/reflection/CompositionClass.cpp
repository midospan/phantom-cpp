/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "CompositionClass.h"
#include "CompositionClass.hxx"
#include <phantom/reflection/ConstantExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), CompositionClass);
o_registerNC((phantom, reflection), (CompositionClass), GetSetExpression);
o_registerNC((phantom, reflection), (CompositionClass), InsertRemoveExpression);

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

Expression* CompositionClass::solveExpression( Expression* a_pLeftExpression , const string& a_strName , const vector<TemplateElement*>* a_pTS, const vector<LanguageElement*>* a_pFS, modifiers_t a_Modifiers ) const
{
    if(a_strName == "operator[]" AND a_pFS AND a_pFS->size() == 1 && a_pFS->back()->asExpression() && a_pFS->back()->asExpression()->getValueType()->isImplicitlyConvertibleTo(typeOf<size_t>()))
    {
        return o_new(GetSetExpression)(a_pLeftExpression, a_pFS->back()->asExpression()->implicitCast(typeOf<size_t>()), const_cast<CompositionClass*>(this));
    }
    else if(a_strName == "operator()" AND a_pFS AND a_pFS->size() == 1 && a_pFS->back()->asExpression() && a_pFS->back()->asExpression()->getValueType()->isImplicitlyConvertibleTo(typeOf<size_t>()))
    {
        return o_new(InsertRemoveExpression)(a_pLeftExpression, a_pFS->back()->asExpression()->implicitCast(typeOf<size_t>()), const_cast<CompositionClass*>(this));
    }
    return Class::solveExpression(a_pLeftExpression, a_strName, a_pTS, a_pFS, a_Modifiers);
}

void CompositionClass::fetchExpressions( Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter, uint a_uiSerializationMask ) const
{
    if(a_Filter(getComponentClass()->pointerType()))
    {
        void* pInstance = a_pInstanceExpression->loadEffectiveAddress();
        size_t count = this->count(pInstance);
        for(size_t i = 0; i<count; ++i)
        {
            out.push_back(o_new(InsertRemoveExpression)(a_pInstanceExpression, o_new(ConstantExpression)(phantom::constant<size_t>(i)), const_cast<CompositionClass*>(this)));
        }
    }
}

CompositionClass::GetSetExpression::GetSetExpression( Expression* a_pLeftExpression, Expression* a_pIndexExpression, CompositionClass* a_pCompositionClass ) 
    : Expression(a_pLeftExpression->isConstExpression() 
                    ? a_pCompositionClass->getComponentClass()->pointerType()->constType()->referenceType()
                    : a_pCompositionClass->getComponentClass()->pointerType()->referenceType()
    , "("+a_pLeftExpression->getName()+")["+a_pIndexExpression->getName()+"]", a_pLeftExpression->getModifiers())
    , m_pLeftExpression(a_pLeftExpression)
    , m_pIndexExpression(a_pIndexExpression)
    , m_pCompositionClass(a_pCompositionClass)
    , m_pBufferedPointer(nullptr)
{
    addSubExpression(m_pLeftExpression);
    addSubExpression(m_pIndexExpression);
    reflection::Type* pPointerType = a_pCompositionClass->getComponentClass()->pointerType();
}

void CompositionClass::GetSetExpression::getValue( void* a_pDest ) const
{
    size_t uiIndex = 0;
    m_pIndexExpression->load(&uiIndex);
    m_pCompositionClass->get(m_pLeftExpression->loadEffectiveAddress(), uiIndex, &m_pBufferedPointer);
    *((void**)a_pDest) = &m_pBufferedPointer;
}

void CompositionClass::GetSetExpression::setValue( void const* a_pSrc ) const
{
    size_t uiIndex = 0;
    m_pIndexExpression->load(&uiIndex);
    void* pCaller = m_pLeftExpression->loadEffectiveAddress();
    m_pCompositionClass->set(pCaller, uiIndex, a_pSrc);
    m_pCompositionClass->get(pCaller, uiIndex, &m_pBufferedPointer); // store the value back in the buffer
}

CompositionClass::GetSetExpression* CompositionClass::GetSetExpression::clone() const
{
    return o_new(GetSetExpression)(m_pLeftExpression, m_pIndexExpression, m_pCompositionClass);
}

void CompositionClass::GetSetExpression::flush() const
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

CompositionClass::InsertRemoveExpression::InsertRemoveExpression( Expression* a_pLeftExpression, Expression* a_pIndexExpression, CompositionClass* a_pCompositionClass ) 
    : Expression(a_pLeftExpression->isConstExpression() 
    ? a_pCompositionClass->getComponentClass()->pointerType()->constType()->referenceType()
    : a_pCompositionClass->getComponentClass()->pointerType()->referenceType()
    , "("+a_pLeftExpression->getName()+")("+CompositionClass_InsertRemoveExpression_formatIndexString(a_pIndexExpression->getName(), 10)+")", a_pLeftExpression->getModifiers())
    , m_pLeftExpression(a_pLeftExpression)
    , m_pIndexExpression(a_pIndexExpression)
    , m_pCompositionClass(a_pCompositionClass)
    , m_pBufferedPointer(nullptr)
{
    addSubExpression(m_pLeftExpression);
    addSubExpression(m_pIndexExpression);
    reflection::Type* pPointerType = a_pCompositionClass->getComponentClass()->pointerType();
}

void CompositionClass::InsertRemoveExpression::getValue( void* a_pDest ) const
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

void CompositionClass::InsertRemoveExpression::setValue( void const* a_pSrc ) const
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

CompositionClass::InsertRemoveExpression* CompositionClass::InsertRemoveExpression::clone() const
{
    return o_new(InsertRemoveExpression)(m_pLeftExpression, m_pIndexExpression, m_pCompositionClass);
}

void CompositionClass::InsertRemoveExpression::flush() const
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