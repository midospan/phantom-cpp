#ifndef TAggregationClass_h__
#define TAggregationClass_h__

/* ****************** Includes ******************* */
#include <phantom/reflection/AggregationClass.h>
/* **************** Declarations ***************** */
o_declareNT(class, (phantom, reflection, native), (typename), (t_Ty), TAggregationIterator);
o_declareNT(class, (phantom, reflection, native), (typename), (t_Ty), TAggregationReverseIterator);
o_declareNT(class, (phantom, reflection, native), (typename), (t_Ty), TAggregationClass);
/* *********************************************** */

o_namespace_begin(phantom, reflection, native)

template<typename t_Ty>
class TAggregationIterator : public ConstIterator 
{
public:
    typedef o_NESTED_TYPE t_Ty::sequence_type container_type;
    typedef o_NESTED_TYPE container_type::const_iterator const_iterator;
    typedef o_NESTED_TYPE container_type::value_type value_type;

    TAggregationIterator(const t_Ty& a_Aggregation)
        : m_Aggregation(a_Aggregation)
        , m_Iterator(a_Aggregation.begin())
    {

    }
    virtual boolean             hasNext() const 
    {
        return m_Iterator != m_Aggregation.end();
    }
    virtual const void*         pointer() const { return &(*m_Iterator); }
    virtual void                next(void* a_pDest) 
    {
        *static_cast<value_type*>(a_pDest) = *m_Iterator++;
    }
    virtual void                getValue(void* a_pDest) const 
    {
        *static_cast<value_type*>(a_pDest) = *m_Iterator;
    }
    virtual reflection::Type*   getValueType() const 
    { 
        return typeOf<value_type>(); 
    }
    virtual void                advance(size_t offset) 
    {
        std::advance(m_Iterator, offset);
    }

protected:
    const t_Ty&     m_Aggregation;
    const_iterator  m_Iterator;
};

template<typename t_Ty>
class TAggregationReverseIterator : public ConstIterator 
{
public:
    typedef o_NESTED_TYPE t_Ty::sequence_type container_type;
    typedef o_NESTED_TYPE container_type::const_reverse_iterator const_reverse_iterator;
    typedef o_NESTED_TYPE container_type::value_type value_type;

    TAggregationReverseIterator(const t_Ty& a_Aggregation)
        : m_Aggregation(a_Aggregation)
        , m_Iterator(a_Aggregation.rbegin())
    {

    }
    virtual const void* pointer() const { return &(*m_Iterator); }

    virtual boolean             hasNext() const 
    {
        return m_Iterator != m_Aggregation.rend();
    }
    virtual void                next(void* a_pDest) 
    {
        *static_cast<value_type*>(a_pDest) = *m_Iterator++;
    }
    virtual void                getValue(void* a_pDest) const 
    {
        *static_cast<value_type*>(a_pDest) = *m_Iterator;
    }
    virtual reflection::Type*   getValueType() const 
    { 
        return typeOf<value_type>(); 
    }
    virtual void                advance(size_t offset) 
    {
        std::advance(m_Iterator, offset);
    }

protected:
    const t_Ty&             m_Aggregation;
    const_reverse_iterator  m_Iterator;
};

template<typename t_Ty>
class TAggregationClass : public AggregationClass
{
    typedef o_NESTED_TYPE t_Ty::aggregate_type  aggregate_type;
    typedef t_Ty                                aggregation_type;

public:
    TAggregationClass(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0)
        : AggregationClass(typeOf<aggregate_type>(), a_strName, a_uiSize, a_uiAlignment, a_Modifiers|o_native)
    {
    }

    virtual void        blockSignals(void* a_pAggregation) const 
    {
        return static_cast<aggregation_type*>(a_pAggregation)->blockSignals();
    }

    virtual void        unblockSignals(void* a_pAggregation) const 
    {
        return static_cast<aggregation_type*>(a_pAggregation)->unblockSignals();
    }

    virtual void*       owner(const void* a_pAggregation) const 
    {
        return static_cast<const aggregation_type*>(a_pAggregation)->getOwner();
    }

    virtual void        add(void* a_pAggregation, const void* a_pSrc) const 
    {
        static_cast<aggregation_type*>(a_pAggregation)->add(*static_cast< aggregate_type*const*>(a_pSrc));
    }

    virtual void        insert(void* a_pAggregation, size_t a_uiIndex, const void* a_pSrc) const
	{
		static_cast<aggregation_type*>(a_pAggregation)->insert(a_uiIndex, *static_cast<aggregate_type*const*>(a_pSrc));
	}

    virtual void        remove(void* a_pAggregation, size_t a_uiIndex) const 
	{
		static_cast<aggregation_type*>(a_pAggregation)->remove(a_uiIndex);
	}

    virtual void        removeAll(void* a_pAggregation, const void* a_pSrc) const 
	{
		static_cast<aggregation_type*>(a_pAggregation)->removeAll(*static_cast< aggregate_type*const*>(a_pSrc));
    }

    virtual void        removeLast(void* a_pAggregation, void* a_pDest) const 
    {
        *static_cast< aggregate_type**>(a_pDest) = static_cast<aggregation_type*>(a_pAggregation)->removeLast();
    }

    virtual void        set(void* a_pAggregation, size_t a_uiIndex, const void* a_pSrc) const 
	{
		static_cast<aggregation_type*>(a_pAggregation)->set(a_uiIndex, *static_cast<aggregate_type*const*>(a_pSrc));
	}

    virtual void        move(void* a_pAggregation, size_t a_uiOldIndex, size_t a_uiNewIndex) const 
    {
        static_cast<aggregation_type*>(a_pAggregation)->move(a_uiOldIndex, a_uiNewIndex);
    }

    virtual void        swap(void* a_pAggregation, size_t a_uiOldIndex, size_t a_uiNewIndex) const
	{
		static_cast<aggregation_type*>(a_pAggregation)->swap(a_uiOldIndex, a_uiNewIndex);
	}

    virtual size_t      countOf(const void* a_pAggregation, const void* a_pSrc) const 
	{
		return static_cast<const aggregation_type*>(a_pAggregation)->countOf(*static_cast<aggregate_type*const*>(a_pSrc));
	}

    virtual void        get(const void* a_pAggregation, size_t a_uiIndex, void* a_pDest) const
	{
		*static_cast<aggregate_type**>(a_pDest) = static_cast<const aggregation_type*>(a_pAggregation)->get(a_uiIndex);
	}

    virtual size_t      count(const void* a_pAggregation) const 
	{
		return static_cast<const aggregation_type*>(a_pAggregation)->count();
	}

    virtual ConstIterator* begin(const void* a_pAggregation) const 
    {
        return o_new(TAggregationIterator<t_Ty>)(*static_cast<const aggregation_type*>(a_pAggregation));
	}

    virtual ConstIterator*   rbegin(const void* a_pAggregation) const 
	{
		return o_new(TAggregationReverseIterator<t_Ty>)(*static_cast<const aggregation_type*>(a_pAggregation));
    }

    virtual void       release(ConstIterator* a_pIterator) const 
    {
        o_dynamic_delete a_pIterator;
    }

    virtual Signal* getAboutToBeInsertedSignal() const { return getSignal("aboutToBeInserted(size_t, t_Aggregate*)"); }
    virtual Signal* getInsertedSignal() const          { return getSignal("inserted(size_t, t_Aggregate*)"); }
    virtual Signal* getAboutToBeRemovedSignal() const  { return getSignal("aboutToBeRemoved(size_t, t_Aggregate*)"); }
    virtual Signal* getRemovedSignal() const           { return getSignal("removed(size_t, t_Aggregate*)"); }
    virtual Signal* getAboutToBeReplacedSignal() const { return getSignal("aboutToBeReplaced(size_t, t_Aggregate*, t_Aggregate*)"); }
    virtual Signal* getReplacedSignal() const          { return getSignal("replaced(size_t, t_Aggregate*, t_Aggregate*)"); }
    virtual Signal* getAboutToBeMovedSignal() const    { return getSignal("aboutToBeMoved(size_t, size_t, t_Aggregate*)"); }
    virtual Signal* getMovedSignal() const             { return getSignal("moved(size_t, size_t, t_Aggregate*)"); }
    virtual Signal* getAboutToBeSwappedSignal() const  { return getSignal("aboutToBeSwapped(size_t, size_t, t_Aggregate*, t_Aggregate*)"); }
    virtual Signal* getSwappedSignal() const           { return getSignal("swapped(size_t, size_t, t_Aggregate*, t_Aggregate*)"); }

};

o_namespace_end(phantom, reflection, native)


#endif
