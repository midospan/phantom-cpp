/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/Expression.hxx>
#include <phantom/reflection/Statement.h>
#include <phantom/reflection/Application.h>
#include <phantom/reflection/Interpreter.h>
#include <phantom/reflection/CallExpression.h>
#include <phantom/reflection/ConstantExpression.h>
#include <phantom/reflection/BuiltInOperatorExpression.h>
#include <phantom/reflection/BuiltInConversionExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), Expression);
o_registerN((phantom, reflection), InvalidExpression);

o_namespace_begin(phantom, reflection) 

o_invalid_custom_def(Expression, InvalidExpression);

Expression::Expression( Type* a_pType ) 
    : m_pValueType(a_pType)
    , m_bSignalsBlocked(false)
{
    if(m_pValueType)
    {
        if(m_pValueType->getOwner())
            addReferencedElement(m_pValueType);
        else 
            addElement(m_pValueType);
    }
    else setInvalid();
}

void Expression::load( void* a_pDest ) const
{
    if(isInvalid())
    {
        o_exception(exception::reflection_runtime_exception, "Invalid expression cannot be evaluated");
    }
    if(!m_pValueType->removeConstReference()->isCopyable())
    {
        o_exception(exception::reflection_runtime_exception, "non-copyable expression value cannot be loaded");
    }
    ReferenceType* pReferenceType = m_pValueType->asReferenceType();
    if(pReferenceType)
    {
        void* pBuffer;
        internalEval(&pBuffer);
        pReferenceType->getReferencedType()->copy(a_pDest, pBuffer);
    }
    else internalEval(a_pDest);
}

void Expression::setValue( void const* a_pSrc ) const
{
    o_exception(exception::reflection_runtime_exception, "Expression is not an l-value");
}

void Expression::store( void const* a_pSrc ) const
{
    if(isInvalid())
    {
        o_exception(exception::reflection_runtime_exception, "Invalid expression cannot be evaluated");
    }
    if(m_pValueType->asConstReferenceType())
    {
        o_exception(exception::reflection_runtime_exception, "Expression is const and cannot be modified");
    }
    ReferenceType* pReferenceType = m_pValueType->asReferenceType();
    if(pReferenceType)
    {
        void* pBuffer;
        internalEval(&pBuffer);
        pReferenceType->getReferencedType()->copy(pBuffer, a_pSrc);
    }
    else setValue(a_pSrc);
    flush();
}

void* Expression::loadEffectiveAddress() const
{
    if(isInvalid())
    {
        o_exception(exception::reflection_runtime_exception, "Invalid expression cannot be evaluated");
    }
    if(m_pValueType->asReferenceType())
    {
        void* pAddress;
        internalEval(&pAddress);
        return pAddress;
    }
    else if(hasValueStorage())
    {
        return evalStorage();
    }
    else
    {
        o_exception(exception::reflection_runtime_exception, "Expression value does not have memory storage"); return nullptr;
    }
}

Type* Expression::storageType(Type* a_pType) const
{
    Type* pStorageType = a_pType;
    if(pStorageType == typeOf<void>()) return nullptr;
    if(pStorageType == typeOf<signal_t>()) return nullptr;
    if(pStorageType->asLValueReferenceType())
    {
        pStorageType = pStorageType->asLValueReferenceType()->getReferencedType()->pointerType();
    }
    return pStorageType;
}

variant Expression::get() const
{
    variant v;
    v.setType(m_pValueType->removeReference()->removeQualifiers());
    load((void*)v.buffer());
    return v;
}

void Expression::set( const variant& v )
{
    if(v.type() == m_pValueType->removeReference())
    {
        store(v.buffer());
    }
    else 
    {
        variant casted = v.as(m_pValueType->removeReference());
        if(casted.isNull())
        {
            o_exception(exception::reflection_runtime_exception, "Cannot convert variant to expression value type");
        }
        store(casted.buffer());
    }
}

bool Expression::isDereferenceable() const
{
    return m_pValueType->removeReference()->removeQualifiers()->asDataPointerType() != nullptr;
}

void Expression::referencedElementRemoved( LanguageElement* a_pElement )
{
    if(a_pElement == m_pValueType) // Type destroyed => expression cannot exist anymore
    {
        m_pValueType = nullptr;
    }
    Evaluable::referencedElementRemoved(a_pElement);
}

void Expression::elementRemoved( LanguageElement* a_pElement )
{
    if(a_pElement == m_pValueType) // Type destroyed => expression cannot exist anymore
    {
        m_pValueType = nullptr;
    }
}

bool Expression::isPersistent() const
{
    if(isInvalid()) return false;

    if(m_pSubExpressions)
    {
        for(auto it = m_pSubExpressions->begin(); it != m_pSubExpressions->end(); ++it)
        {
            if(NOT((*it)->isPersistent()))
                return false;
        }
    }
    return m_pValueType->isNative();
}

void Expression::setSignalBlockedCascade( bool a_bSignalsBlocked )
{
    setSignalBlocked(a_bSignalsBlocked);
    if(m_pSubExpressions)
    {
        for(auto it = m_pSubExpressions->begin(); it != m_pSubExpressions->end(); ++it)
        {
            (*it)->setSignalBlockedCascade(a_bSignalsBlocked);
        }
    }
}

void Expression::setSignalBlocked( bool a_bSignalsBlocked )
{
    m_bSignalsBlocked = a_bSignalsBlocked;
}

bool Expression::hasValueStorageCascade() const
{
    if(hasValueStorage())
        return true;
    if(m_pSubExpressions)
    {
        for(auto it = m_pSubExpressions->begin(); it != m_pSubExpressions->end(); ++it)
        {
            if((*it)->hasValueStorageCascade()) return true;
        }
    }
    return false;
}

void Expression::detach()
{
    if(m_pOwner)
    {
        static_cast<Expression*>(m_pOwner)->removeElement(this);
    }
}

void Expression::ancestorChanged( LanguageElement* a_pLanguageElement )
{
    if(getEnclosingBlock())
    {
        Class* pClass = getValueType()->removeRValueReference()->asClass();
        if(pClass)
        {
            void* pStorageAddress = evalStorage();
            o_assert(pStorageAddress);
            Expression* pThis = (o_new(ConstantExpression)(phantom::constant<void*>(pStorageAddress)))->convert(getValueType()->pointerType())->dereference();
            Statement* pLifeTimeStatement = evaluateLifeTime();
            o_assert(pLifeTimeStatement);
            CallExpression* pDestructionExpression = o_new(CallExpression)(getValueType()->asClass()->getDestructor(), pThis);
            pLifeTimeStatement->addTemporaryObjectDestruction(pDestructionExpression);
        }
    }
}

Expression* Expression::convert( Type* a_pOutputType, int conversionType /*= e_implicit_conversion*/, LanguageElement* a_pContextScope ) const
{
    if(a_pOutputType->removeQualifiers()->equals(m_pValueType->removeQualifiers()) && conversionType == e_implicit_conversion)
        return const_cast<Expression*>(this);
    conversion* conv = getValueType()->conversionTo(a_pOutputType, conversionType, a_pContextScope);
    if(conv == nullptr) return o_new(BuiltInConversionExpression)(const_cast<Expression*>(this), nullptr, conversionType);
    Expression* pConversion = conv->convert(const_cast<Expression*>(this));
    o_assert(pConversion);
    delete conv;
    return pConversion;
}

Statement* Expression::evaluateLifeTime() const
{
    if(m_pOwner)
    {
        Evaluable* pOwnerEvaluable = m_pOwner ? m_pOwner->asEvaluable() : nullptr;
        if(pOwnerEvaluable) 
        {
            return pOwnerEvaluable->evaluateExpressionLifeTime(const_cast<Expression*>(this));
        }
    }
    return nullptr;
}

void Expression::evaluateArguments( const vector<Expression*>& a_Arguments, vector<void*> &addresses ) const
{
    addresses.resize(a_Arguments.size());
    size_t i = a_Arguments.size();
    while(i--) // evaluate arguments from right to left
    {
        Expression* pArgument = a_Arguments[i];
        addresses[i] = pArgument->loadEffectiveAddress();
    }
}

Expression* Expression::dereference() const
{
    DataPointerType* pPointerType = m_pValueType->asDataPointerType();
    Expression* args[2] = { (Expression*)this, 0 };
    if(pPointerType == nullptr) 
        return o_new(BuiltInOperatorExpression)( application()->getBuiltInOperator(e_Operator_Dereference), Type::Invalid(), args, operation_delegate_t()); 
    return o_new(BuiltInOperatorExpression)(application()->getBuiltInOperator(e_Operator_Dereference), pPointerType->removePointer()->addLValueReference(), args, operation_delegate_t(pPointerType, &DataPointerType::dereference));
}

Expression* Expression::address() const
{
    ReferenceType* pReferenceType = m_pValueType->asReferenceType();
    Expression* args[2] = { (Expression*)this, 0 };
    if(pReferenceType == nullptr) 
        return o_new(BuiltInOperatorExpression)(application()->getBuiltInOperator(e_Operator_Address), Type::Invalid(), args, operation_delegate_t()); 
    return o_new(BuiltInOperatorExpression)(application()->getBuiltInOperator(e_Operator_Address), pReferenceType->removeReference()->addPointer(), args, operation_delegate_t(pReferenceType, &ReferenceType::address));
}

Expression* Expression::arrayAccess( Expression* a_pIndexExpression )
{
    ReferenceType* pReferenceType = m_pValueType->asReferenceType();
    Expression* args[2] = { (Expression*)this, a_pIndexExpression };
    if(pReferenceType == nullptr 
        OR pReferenceType->getReferencedType()->asArrayType() == nullptr 
        OR pReferenceType->getReferencedType()->asDataPointerType() == nullptr) 
        return o_new(BuiltInOperatorExpression)(application()->getBuiltInOperator(e_Operator_Bracket), Type::Invalid(), args, operation_delegate_t()); 
    Type* pElementType = pReferenceType->getReferencedType()->getUnderlyingType();
    Type* pResultType = pReferenceType->asRValueReferenceType() ? (Type*)pElementType->rvalueReferenceType() : pElementType->lvalueReferenceType();
    return o_new(BuiltInOperatorExpression)(application()->getBuiltInOperator(e_Operator_Bracket), pResultType, args, operation_delegate_t(pElementType->pointerType(), &DataPointerType::bracket));
}

Expression* Expression::arrayAccess( size_t a_uiIndex )
{
    return arrayAccess(o_new(ConstantExpression)(constant<size_t>(a_uiIndex)));
}

Expression* Expression::store( Expression* a_pRightExpression )
{
    ReferenceType* pReferenceType = m_pValueType->asReferenceType();
    Expression* args[2] = { (Expression*)this, a_pRightExpression };
    if(pReferenceType == nullptr 
        OR pReferenceType->getReferencedType()->asClassType() 
        OR pReferenceType->getReferencedType()->isConst()
        OR NOT(a_pRightExpression->getValueType()->equals(pReferenceType->getReferencedType()))) 
        return o_new(BuiltInOperatorExpression)(application()->getBuiltInOperator(e_Operator_Assignment), Type::Invalid(), args, operation_delegate_t()); 
    Type* pElementType = pReferenceType->getReferencedType()->getUnderlyingType();
    Type* pResultType = pReferenceType->asRValueReferenceType() ? (Type*)pElementType->rvalueReferenceType() : pElementType->lvalueReferenceType();
    return o_new(BuiltInOperatorExpression)(application()->getBuiltInOperator(e_Operator_Assignment), pResultType, args, operation_delegate_t(pReferenceType, &ReferenceType::memcpyStoreDelegate));
}

void Expression::eval( void* a_pDest ) const
{
    if(isInvalid())
    {
        o_exception(exception::reflection_runtime_exception, "Invalid expression cannot be evaluated");
    }
    internalEval(a_pDest);
    if(m_pOwner == nullptr)
    {
        interpreter()->release(const_cast<Expression*>(this));
    }
}

void Expression::pushDestruction( Type* a_pType, void* a_pBuffer ) const
{
    if(m_pOwner)
    {
        o_assert(m_pOwner->asExpression());
        m_pOwner->asExpression()->pushDestruction(a_pType, a_pBuffer);
    }
    else 
    {
        phantom::interpreter()->pushDestruction(const_cast<Expression*>(this), a_pType, a_pBuffer);
    }
}

bool Expression::isCompileTime() const
{
    return asConstantExpression() != nullptr;
}

InvalidExpression::InvalidExpression() : Expression(Type::Invalid())
{
    setInvalid();
}

InvalidExpression::InvalidExpression( Type* a_pType ) : Expression(a_pType)
{
    setInvalid();
}

InvalidExpression* InvalidExpression::clone() const
{
    return o_new(InvalidExpression)(m_pValueType);
}

o_namespace_end(phantom, reflection)

