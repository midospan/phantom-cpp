#ifndef AggregationClass_h__
#define AggregationClass_h__


/* ****************** Includes ******************* */
#include <phantom/phantom.h>
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), AggregationClass);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export AggregationClass : public Class
{
    o_type;

    o_declare_meta_type(AggregationClass);

public:
    AggregationClass(Class* a_pAggregateClass, const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0)
        : Class(a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
        , m_pAggregateClass(a_pAggregateClass) 
    {
    }

    virtual void blockSignals(void* a_pAggregation) const = 0;

    virtual void unblockSignals(void* a_pAggregation) const = 0;

    virtual void* owner(const void* a_pAggregation) const = 0;

    virtual void add(void* a_pAggregation, const void* a_pSrc) const = 0;

    virtual void insert(void* a_pAggregation, size_t a_uiIndex, const void* a_pSrc) const = 0;

    virtual void remove(void* a_pAggregation, size_t a_uiIndex) const = 0;

    virtual void removeAll(void* a_pAggregation, const void* a_pSrc) const = 0;

    virtual void removeLast(void* a_pAggregation, void* a_pDest) const = 0;

    virtual void set(void* a_pAggregation, size_t a_uiIndex, const void* a_pSrc) const = 0;

    virtual void move(void* a_pAggregation, size_t a_uiOldIndex, size_t a_uiNewIndex) const = 0;

    virtual void swap(void* a_pAggregation, size_t a_uiOldIndex, size_t a_uiNewIndex) const = 0;

    virtual size_t countOf(const void* a_pAggregation, const void* a_pSrc) const = 0;

    virtual void get(const void* a_pAggregation, size_t a_uiIndex, void* a_pDest) const = 0;

    virtual size_t      count(const void* a_pAggregation) const = 0;

    virtual ConstIterator*   begin(const void* a_pAggregation) const = 0;

    virtual ConstIterator*   rbegin(const void* a_pAggregation) const = 0;

    virtual void        release(ConstIterator* a_pIterator) const = 0;

    Type*               getKeyType() const { return m_pAggregateClass; }
    Type*               getValueType() const { return m_pAggregateClass; }

    Class*              getAggregateClass() const { return m_pAggregateClass; }

    virtual AggregationClass* asAggregationClass() const { return const_cast<AggregationClass*>(this); }

    virtual Signal* getAboutToBeInsertedSignal() const = 0;
    virtual Signal* getInsertedSignal() const          = 0;
    virtual Signal* getAboutToBeRemovedSignal() const  = 0;
    virtual Signal* getRemovedSignal() const           = 0;
    virtual Signal* getAboutToBeReplacedSignal() const = 0;
    virtual Signal* getReplacedSignal() const          = 0;
    virtual Signal* getAboutToBeMovedSignal() const    = 0;
    virtual Signal* getMovedSignal() const             = 0;
    virtual Signal* getAboutToBeSwappedSignal() const  = 0;
    virtual Signal* getSwappedSignal() const           = 0;
    
    virtual bool referencesData( const void* a_pContainer, const phantom::data& a_Data ) const;

    virtual void fetchExpressions( Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter, uint a_uiSerializationMask ) const;

public:

protected:
    Class*   m_pAggregateClass;

};
class o_export AggregationGetSetExpression : public Expression
{
    o_language_element;

public:
    AggregationGetSetExpression(Expression* a_pLeftExpression, Expression* a_pIndexExpression, AggregationClass* a_pAggregationClass);

    virtual void internalEval(void* a_pDest) const;

    virtual bool hasValueStorage() const { return false; }

    virtual void setValue( void const* a_pSrc ) const;

    virtual void flush() const;

    Expression* getLeftExpression() const { return m_pLeftExpression; }

    Expression* getIndexExpression() const { return m_pIndexExpression; }

    virtual AggregationGetSetExpression*     clone() const;

protected:
    Expression* m_pLeftExpression;
    Expression* m_pIndexExpression;
    AggregationClass* m_pAggregationClass;
    mutable void* m_pBufferedPointer;
};
class o_export AggregationInsertRemoveExpression : public Expression
{
    o_language_element;

public:
    AggregationInsertRemoveExpression(Expression* a_pLeftExpression, Expression* a_pIndexExpression, AggregationClass* a_pAggregationClass);

    virtual void internalEval(void* a_pDest) const;

    virtual bool hasValueStorage() const { return false; }

    virtual void setValue( void const* a_pSrc ) const;

    virtual void flush() const;

    Expression* getLeftExpression() const { return m_pLeftExpression; }

    Expression* getIndexExpression() const { return m_pIndexExpression; }

    virtual AggregationInsertRemoveExpression*     clone() const;

    AggregationClass* getAggregationClass() const { return m_pAggregationClass; }

    Expression* getAggregationExpression() const { return m_pLeftExpression; }

protected:
    Expression* m_pLeftExpression;
    Expression* m_pIndexExpression;
    AggregationClass* m_pAggregationClass;
    mutable void* m_pBufferedPointer;
};

o_namespace_end(phantom, reflection)

o_declareN((phantom, reflection), AggregationInsertRemoveExpression);
o_declareN((phantom, reflection), AggregationGetSetExpression);

#endif
