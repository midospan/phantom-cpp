/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Expression_h__
#define o_phantom_reflection_Expression_h__



/* ****************** Includes ******************* */
#include "phantom/reflection/Evaluable.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Expression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Expression : public Evaluable
{
    o_language_element;

public:
    Expression(Type* a_pValueType);

    static Expression* Invalid();

    using Evaluable::eval;

    /// /!\ REMINDER : Evaluation is not intended to be highly efficient in terms of speed or performances, but convenient and user-friendly
    /// => To have close-to-native performances, use a JIT compiler
    void eval(void* a_pDest) const;

    virtual modifiers_t     getModifiers() const { return 0; }

    virtual void            internalEval() const { /*by default evaluating an expression do nothing, must be reimplemented to have significant role*/ }
    virtual void            internalEval(void* a_pDest) const = 0;

    Type*                   getValueType() const { return m_pValueType; }

    void                    load(void* a_pDest) const;

    void                    store(void const* a_pSrc) const;

    void                    storeWithSignalsBlocked(void const* a_pSrc) const;

    variant                 get() const;

    void                    set(const variant& v);

    virtual Expression*     asExpression() const { return (Expression*)this; }

    virtual Expression*     toExpression(Expression* a_pOptExpression = nullptr) const { return (Expression*)this; }

    virtual bool            isAddressable() const { return m_pValueType->asLValueReferenceType() != nullptr
                                                        OR m_pValueType->asRValueReferenceType() != nullptr; }

    virtual bool            isDereferenceable() const;

    virtual bool            isPersistent() const;

    virtual bool            hasValueStorage() const { return false; }

    bool                    hasValueStorageCascade() const;

    virtual void*           evalStorage() const { return nullptr; }

    bool                    hasEffectiveAddress() const { return (m_pValueType AND m_pValueType->asLValueReferenceType() != nullptr) OR hasValueStorage(); }

    void*                   loadEffectiveAddress() const;

    virtual void            flush() const {}

    virtual bool            isCompileTime() const;
    
    virtual Expression*     dereference() const;

    virtual Expression*     address() const;

    virtual Expression*     arrayAccess(size_t a_uiIndex);

    virtual Expression*     arrayAccess(Expression* a_pIndexExpression);

    virtual Expression*     store(Expression* a_pIndexExpression);

    virtual Expression*     clone() const = 0;

    virtual Expression*     convert(Type* a_pOutputType, int conversionType = e_implicit_conversion, LanguageElement* a_pContextScope = nullptr) const;

    void                    setSignalBlocked(bool a_bSignalsBlocked);

    void                    setSignalBlockedCascade(bool a_bSignalsBlocked);

    bool                    areSignalsBlocked() const { return m_bSignalsBlocked; }

    void                    detach();

    /// Dynamic Conversion helpers (useful if rtti not enabled for expressions)

    virtual ConditionalExpression*      asConditionalExpression() const { return nullptr; }
    virtual ConstantExpression*         asConstantExpression() const { return nullptr; }
    virtual CallExpression*             asCallExpression() const { return nullptr; }
    virtual BuiltInConversionExpression*asBuiltInConversionExpression() const { return nullptr; }
    virtual TDBinaryOperationExpression*  asTDBinaryOperationExpression() const { return nullptr; }
    virtual TDUnaryPreOperationExpression*asTDUnaryPreOperationExpression() const { return nullptr; }
    virtual TDUnaryPostOperationExpression*asTDUnaryPostOperationExpression() const { return nullptr; }
    virtual LocalVariableExpression*    asLocalVariableExpression() const { return nullptr; }
    virtual DataMemberExpression*       asDataMemberExpression() const { return nullptr; }
    virtual PropertyExpression*         asPropertyExpression() const { return nullptr; }
    virtual VariableExpression*         asVariableExpression() const { return nullptr; }
    virtual StringLiteralExpression*    asStringLiteralExpression() const { return nullptr; }
    virtual WStringLiteralExpression*   asWStringLiteralExpression() const { return nullptr; }
    virtual ConstructorCallExpression*  asConstructorCallExpression() const { return nullptr; }
    virtual DataExpression*             asDataExpression() const { return nullptr; }
    virtual PlacementConstructionExpression* asPlacementConstructionExpression() const { return nullptr; }
    virtual MemberFunctionPointerCallExpression* asMemberFunctionPointerCallExpression() const { return nullptr; }

protected:
    Statement* evaluateExpressionLifeTime( Expression* a_pExpression ) const
    {
        /// by default life time of a sub expression is the life time of its owner
        return evaluateLifeTime();
    }

    Statement* evaluateLifeTime() const;

protected:
    virtual void referencedElementRemoved(LanguageElement* a_pElement);
    virtual void elementRemoved(LanguageElement* a_pElement);
    Type* storageType(Type* a_pType) const;

    void evaluateArguments( const vector<Expression*>& a_Arguments, vector<void*> &addresses ) const;

protected:
    void setValue( void const* a_pSrc ) const;
    virtual void ancestorChanged(LanguageElement* a_pOwner);
    void pushDestruction(Type* a_pType, void* a_pBuffer) const;

protected:
    Type*                   m_pValueType;
    bool                    m_bSignalsBlocked;
};

class InvalidExpression : public Expression
{
public:
    InvalidExpression();
    InvalidExpression(Type* a_pType);

    virtual void internalEval(void* a_pDest) const { o_exception_no_implementation(); }

    virtual InvalidExpression* clone() const;
};

o_namespace_end(phantom, reflection)



#endif
