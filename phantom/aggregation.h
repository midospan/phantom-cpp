#ifndef o_aggregation_h__
#define o_aggregation_h__


/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
o_declareNT(class, (phantom), (typename), (t_Aggregate), aggregation);
o_declareNT(class, (phantom), (typename), (t_Aggregate), aggregation_replacer);
o_declareNT(class, (phantom), (typename), (t_Aggregate), aggregation_inserter);
/* *********************************************** */

o_namespace_begin(phantom)

template<typename t_Aggregate>
class aggregation_replacer
{
public:
    aggregation_replacer(const aggregation_replacer& other)
        : m_pAggregation(other.m_pAggregation)
        , m_uiIndex(other.m_uiIndex)
    {

    }
    aggregation_replacer(aggregation<t_Aggregate>* a_pAggregation, size_t a_uiIndex)
        : m_pAggregation(a_pAggregation)
        , m_uiIndex(a_uiIndex)
    {

    }
    void operator=(const aggregation_replacer& other)
    {
        m_pAggregation = other.m_pAggregation;
        m_uiIndex = other.m_uiIndex;
    }
    void operator=(t_Aggregate* a_pAggregate)
    {
        m_pAggregation->set(m_uiIndex, a_pAggregate);
    }

    t_Aggregate* operator->() const
    {
        return m_pAggregation->get(m_uiIndex);
    }

    operator t_Aggregate*()
    {
        return m_pAggregation->get(m_uiIndex);
    }

protected:
    aggregation<t_Aggregate>* m_pAggregation;
    size_t m_uiIndex;
};

template<typename t_Aggregate>
class aggregation_inserter
{
public:
    aggregation_inserter(const aggregation_inserter& other)
        : m_pAggregation(other.m_pAggregation)
        , m_uiIndex(other.m_uiIndex)
    {

    }
    aggregation_inserter(aggregation<t_Aggregate>* a_pAggregation, size_t a_uiIndex)
        : m_pAggregation(a_pAggregation)
        , m_uiIndex(a_uiIndex)
    {

    }
    void operator=(const aggregation_inserter& other)
    {
        m_pAggregation = other.m_pAggregation;
        m_uiIndex = other.m_uiIndex;
    }
    void operator=(t_Aggregate* a_pAggregate)
    {
        if(a_pAggregate)
        {
            m_pAggregation->insert(m_uiIndex, a_pAggregate);
        }
        else
        {
            m_pAggregation->remove(m_uiIndex);
        }
    }

protected:
    aggregation<t_Aggregate>* m_pAggregation;
    size_t m_uiIndex;
};

template <typename t_Aggregate>
class aggregation
{
public:
    //o_static_assert_msg(boost::is_class<t_Aggregate>::value AND (meta_specifiers<t_Aggregate>::value&o_pod) == 0, "t_Aggregate must be a non-declared-pod class");
    typedef aggregation_inserter<t_Aggregate> inserter;
    typedef aggregation_replacer<t_Aggregate> replacer;
    typedef vector<t_Aggregate*> sequence_type;
    typedef aggregation<t_Aggregate> self_type;
    typedef t_Aggregate aggregate_type;
    typedef typename sequence_type::const_iterator const_iterator;
    typedef typename sequence_type::const_reverse_iterator const_reverse_iterator;

public:
    aggregation()
    {
    }
    o_initialize()
    {

    }
    o_restore(filter, pass)
    {
        return restore_complete;
    }

    o_terminate()
    {

    }

    void blockSignals()
    {
        o_block_signal(aboutToBeInserted);
        o_block_signal(inserted);
        o_block_signal(aboutToBeRemoved);
        o_block_signal(removed);
        o_block_signal(aboutToBeReplaced);
        o_block_signal(replaced);
        o_block_signal(aboutToBeMoved);
        o_block_signal(moved);
        o_block_signal(aboutToBeSwapped);
        o_block_signal(swapped);
    }

    void unblockSignals()
    {
        o_unblock_signal(aboutToBeInserted);
        o_unblock_signal(inserted);
        o_unblock_signal(aboutToBeRemoved);
        o_unblock_signal(removed);
        o_unblock_signal(aboutToBeReplaced);
        o_unblock_signal(replaced);
        o_unblock_signal(aboutToBeMoved);
        o_unblock_signal(moved);
        o_unblock_signal(aboutToBeSwapped);
        o_unblock_signal(swapped);
    }

    void* getOwner() const
    {
        const rtti_data* ownerRtti = rttiDataOf(this).owner;
        return ownerRtti ? ownerRtti->layout : 0;
    }

    void add(t_Aggregate* a_pAggregate)
    {
        insert(m_Aggregates.size(), a_pAggregate);
    }

    void insert(size_t a_uiIndex, t_Aggregate* a_pAggregate)
    {
        o_assert(a_pAggregate);
        o_assert(a_uiIndex <= m_Aggregates.size());
        o_emit aboutToBeInserted(a_uiIndex, a_pAggregate);
        m_Aggregates.insert(m_Aggregates.begin()+a_uiIndex, a_pAggregate);
        o_emit inserted(a_uiIndex, a_pAggregate);
    }

    t_Aggregate* remove(size_t a_uiIndex)
    {
        o_assert(a_uiIndex < m_Aggregates.size());
        t_Aggregate* pAggregate = m_Aggregates[a_uiIndex];
        o_emit aboutToBeRemoved(a_uiIndex, pAggregate);
        m_Aggregates.erase(m_Aggregates.begin()+a_uiIndex);
        o_emit removed(a_uiIndex, pAggregate);
        return pAggregate;
    }

    void removeAll(t_Aggregate* a_pAggregate)
    {
        o_NESTED_TYPE sequence_type::iterator it;
        while((it = std::find(m_Aggregates.begin(), m_Aggregates.end(), a_pAggregate)) != m_Aggregates.end())
        {
            remove(it - m_Aggregates.begin());
        }
    }

    t_Aggregate* removeLast()
    {
        t_Aggregate* pLast = m_Aggregates.back();
        remove(m_Aggregates.size()-1);
        return pLast;
    }

    void set(size_t a_uiIndex, t_Aggregate* a_pAggregate)
    {
        if(m_Aggregates[a_uiIndex] == a_pAggregate)
            return;
        if(a_pAggregate == nullptr)
        {
            remove(a_uiIndex);
        }
        else
        {
            o_emit aboutToBeReplaced(a_uiIndex, a_pAggregate, m_Aggregates[a_uiIndex]);

            m_Aggregates[a_uiIndex] = a_pAggregate;

            o_emit replaced(a_uiIndex, a_pAggregate, m_Aggregates[a_uiIndex]);
        }
    }

    void move(size_t a_uiOldIndex, size_t a_uiNewIndex)
    {
        if(a_uiOldIndex == a_uiNewIndex)
            return;
        o_assert(a_uiNewIndex < m_Aggregates.size());
        o_assert(a_uiOldIndex < m_Aggregates.size());
        o_assert(a_uiNewIndex >= 0);
        o_assert(a_uiOldIndex >= 0);
        t_Aggregate* pAggregate = m_Aggregates[a_uiOldIndex];
        o_emit aboutToBeMoved(a_uiOldIndex, a_uiNewIndex, pAggregate);
        if(a_uiOldIndex < a_uiNewIndex)
        {
            auto it = m_Aggregates.begin() + a_uiOldIndex;
            auto to = m_Aggregates.begin() + a_uiNewIndex+1;
            std::rotate(it, it+1, to);
        }
        else
        {
            auto rit = m_Aggregates.rbegin() + m_Aggregates.size()-1-a_uiOldIndex;
            auto rto = m_Aggregates.rbegin() + m_Aggregates.size()-a_uiNewIndex;
            std::rotate(rit, rit+1, rto);
        }
        o_emit moved(a_uiOldIndex, a_uiNewIndex, pAggregate);
    }

    void swap(size_t a_uiFirst, size_t a_uiSecond)
    {
        if(a_uiFirst == a_uiSecond)
            return;
        t_Aggregate* pFirst = m_Aggregates[a_uiFirst];
        o_emit aboutToBeSwapped(a_uiFirst, a_uiSecond, pFirst, m_Aggregates[a_uiSecond]);
        m_Aggregates[a_uiFirst] = m_Aggregates[a_uiSecond];
        m_Aggregates[a_uiSecond] = pFirst;
        o_emit swapped(a_uiFirst, a_uiSecond, pFirst, m_Aggregates[a_uiFirst]);
    }

    size_t countOf(t_Aggregate* a_pAggregate) const
    {
        size_t c = 0;
        auto it = m_Aggregates.begin();
        while((it = std::find(it, m_Aggregates.end(), a_pAggregate)) != m_Aggregates.end())
        {
            c++;
            it++;
        }
        return c;
    }

    t_Aggregate* get(size_t a_uiIndex) const
    {
        o_assert(a_uiIndex < m_Aggregates.size());
        return m_Aggregates[a_uiIndex];
    }

    size_t count() const { return m_Aggregates.size(); }

    const_iterator begin() const { return m_Aggregates.begin(); }
    const_iterator end() const { return m_Aggregates.end(); }

    const_reverse_iterator rbegin() const { return m_Aggregates.rbegin(); }
    const_reverse_iterator rend() const { return m_Aggregates.rend(); }

    replacer    operator[](size_t i) { return replacer(this, i); }
    inserter    operator()(size_t i) { return inserter(this, i); }

protected:
    o_signal_data(aboutToBeInserted, size_t, t_Aggregate*);
    o_signal_data(inserted, size_t, t_Aggregate*);

    o_signal_data(aboutToBeRemoved, size_t, t_Aggregate*);
    o_signal_data(removed, size_t, t_Aggregate*);

    o_signal_data(aboutToBeReplaced, size_t, t_Aggregate*, t_Aggregate*);
    o_signal_data(replaced, size_t, t_Aggregate*, t_Aggregate*);

    o_signal_data(aboutToBeMoved, size_t, size_t, t_Aggregate*);
    o_signal_data(moved, size_t, size_t, t_Aggregate*);

    o_signal_data(aboutToBeSwapped, size_t, size_t, t_Aggregate*, t_Aggregate*);
    o_signal_data(swapped, size_t, size_t, t_Aggregate*, t_Aggregate*);

protected:
    sequence_type                           m_Aggregates;
    void*                                   m_pOwner;
};

o_namespace_end(phantom)

#endif // o_aggregation_h__
