#ifndef o_composition_h__
#define o_composition_h__


/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
o_declareNT(class, (phantom), (typename), (t_Component), composition);
o_declareNT(class, (phantom), (typename), (t_Component), composition_replacer);
o_declareNT(class, (phantom), (typename), (t_Component), composition_inserter);
/* *********************************************** */

o_namespace_begin(phantom)


template<typename t_Component>
class composition_replacer
{
public:
    composition_replacer(const composition_replacer& other)
        : m_pComposition(other.m_pComposition)
        , m_uiIndex(other.m_uiIndex)
    {

    }
    composition_replacer(composition<t_Component>* a_pComposition, size_t a_uiIndex)
        : m_pComposition(a_pComposition)
        , m_uiIndex(a_uiIndex)
    {

    }
    void operator=(const composition_replacer& other)
    {
        m_pComposition = other.m_pComposition;
        m_uiIndex = other.m_uiIndex;
    }
    void operator=(t_Component* a_pComponent)
    {
        m_pComposition->set(m_uiIndex, a_pComponent);
    }

    t_Component* operator->() const
    {
        return m_pComposition->get(m_uiIndex);
    }

    operator t_Component*() 
    {
        return m_pComposition->get(m_uiIndex);
    }

protected:
    composition<t_Component>* m_pComposition;
    size_t m_uiIndex;
};

template<typename t_Component>
class composition_inserter
{
public:
    composition_inserter(const composition_inserter& other)
        : m_pComposition(other.m_pComposition)
        , m_uiIndex(other.m_uiIndex)
    {

    }
    composition_inserter(composition<t_Component>* a_pComposition, size_t a_uiIndex)
        : m_pComposition(a_pComposition)
        , m_uiIndex(a_uiIndex)
    {

    }
    void operator=(const composition_inserter& other)
    {
        m_pComposition = other.m_pComposition;
        m_uiIndex = other.m_uiIndex;
    }
    void operator=(t_Component* a_pComponent)
    {
        if(a_pComponent)
        {
            m_pComposition->insert(m_uiIndex, a_pComponent);
        }
        else 
        {
            m_pComposition->remove(m_uiIndex);
        }
    }

protected:
    composition<t_Component>* m_pComposition;
    size_t m_uiIndex;
};
    
template <typename t_Component>
class composition
{
public:
    //o_static_assert_msg(boost::is_class<t_Component>::value AND (meta_specifiers<t_Component>::value&o_pod) == 0, "t_Component must be a non-declared-pod class");
    typedef composition_inserter<t_Component> inserter;
    typedef composition_replacer<t_Component> replacer;
    typedef composition<t_Component> self_type;
    typedef vector<t_Component*> sequence_type;
    typedef t_Component component_type;
    typedef typename sequence_type::const_iterator const_iterator;
    typedef typename sequence_type::const_reverse_iterator const_reverse_iterator;
    typedef void* (t_Component::*owner_get_member_function_ptr)() const;
    typedef void (t_Component::*owner_set_member_function_ptr)(void*);
    typedef size_t (t_Component::*index_in_owner_set_member_function_ptr);

public:
    composition() 
        : m_OwnerSetMemberFunctionPtr(nullptr)
        , m_OwnerGetMemberFunctionPtr(nullptr)
        , m_IndexInOwnerDataMemberPtr(nullptr)
#if !defined(_NDEBUG)
        , m_pOwnerClass(nullptr)
#endif
    {
    }
    template<typename t_OwnerTy>
    composition(void (t_Component::*a_OwnerSetMemberFunctionPtr)(t_OwnerTy*)  
                        , t_OwnerTy* (t_Component::*a_OwnerGetMemberFunctionPtr)() const  
                        , index_in_owner_set_member_function_ptr a_IndexInOwnerDataMemberPtr = nullptr) 

        : m_OwnerSetMemberFunctionPtr((owner_set_member_function_ptr)a_OwnerSetMemberFunctionPtr)
        , m_OwnerGetMemberFunctionPtr((owner_get_member_function_ptr)a_OwnerGetMemberFunctionPtr)
        , m_IndexInOwnerDataMemberPtr(a_IndexInOwnerDataMemberPtr)
#if !defined(_NDEBUG)
        , m_pOwnerClass(typeOf<t_OwnerTy>())
#endif
    {
        o_assert(a_OwnerSetMemberFunctionPtr);
        o_assert(a_OwnerGetMemberFunctionPtr);
    }
    o_initialize()
    {
#if !defined(_NDEBUG)
        reflection::Class* pLayoutClass = rttiDataOf(this).owner->layout_class;
        o_assert(m_pOwnerClass == nullptr OR pLayoutClass->getBaseClassOffsetCascade(m_pOwnerClass) == 0, "Owner class must have the same layout position as the argument class pointer passed in set-owner (resp. retrived with get-owner) member functions");
#endif
    }
    o_restore(filter, pass)
    {
#if !defined(_NDEBUG)
        if(pass == restore_pass_local)
        {
            reflection::Class* pLayoutClass = rttiDataOf(this).owner->layout_class;
            o_assert(m_pOwnerClass == nullptr OR pLayoutClass->getBaseClassOffsetCascade(m_pOwnerClass) == 0, "Owner class must have the same layout position as the argument class pointer passed in set-owner (resp. retrived with get-owner) member functions");
        }
#endif
        return restore_complete;
    }

    o_terminate()
    {
        for(auto it = m_Components.begin(); it != m_Components.end(); ++it)
        {
            o_dynamic_delete *it;
        }
    }

    o_forceinline void* getOwner() const 
    { 
        const rtti_data* ownerRtti = rttiDataOf(this).owner;
        return ownerRtti ? ownerRtti->layout : 0;
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

    void add(t_Component* a_pComponent)
    {
        insert(m_Components.size(), a_pComponent);
    }

    void insert(size_t a_uiIndex, t_Component* a_pComponent)
    {
        assert(a_uiIndex <= m_Components.size());
        assert(!has(a_pComponent));
        assert(m_OwnerSetMemberFunctionPtr == nullptr || (a_pComponent->*m_OwnerGetMemberFunctionPtr)() == nullptr);

        o_emit aboutToBeInserted(a_uiIndex, a_pComponent);
        // Increment all index of components after the new inserted component
        if(m_IndexInOwnerDataMemberPtr)
        {
            for(size_t i = a_uiIndex; i<m_Components.size(); ++i)
            {
                (m_Components[i]->*m_IndexInOwnerDataMemberPtr)++;
            }
        }
        m_Components.insert(m_Components.begin()+a_uiIndex, a_pComponent);
        if(m_OwnerSetMemberFunctionPtr)
        {
            (a_pComponent->*m_OwnerSetMemberFunctionPtr)(getOwner());
        }
        if(m_IndexInOwnerDataMemberPtr)
        {
            a_pComponent->*m_IndexInOwnerDataMemberPtr = a_uiIndex;
        }
        o_emit inserted(a_uiIndex, a_pComponent);
    }

    t_Component* remove(size_t a_uiIndex)
    {
        assert(a_uiIndex < m_Components.size());
        t_Component* pComponent = m_Components[a_uiIndex];
        assert(m_OwnerGetMemberFunctionPtr == nullptr || (pComponent->*m_OwnerGetMemberFunctionPtr)() == getOwner());
        o_emit aboutToBeRemoved(a_uiIndex, pComponent);
        if(m_OwnerSetMemberFunctionPtr)
        {
            (pComponent->*m_OwnerSetMemberFunctionPtr)(nullptr);
        }
        if(m_IndexInOwnerDataMemberPtr)
        {
            pComponent->*m_IndexInOwnerDataMemberPtr = std::numeric_limits<size_t>::max();
            for(size_t i = a_uiIndex+1; i<m_Components.size(); ++i)
            {
                (m_Components[i]->*m_IndexInOwnerDataMemberPtr)--;
            }
        }
        m_Components.erase(m_Components.begin()+a_uiIndex);
        o_emit removed(a_uiIndex, pComponent);
        return pComponent;
    }

    void remove(t_Component* a_pComponent)
    {
        remove(indexOf(a_pComponent));
    }

    t_Component* removeLast()
    {
        t_Component* pLast = m_Components.back();
        remove(m_Components.size()-1);
        return pLast;
    }

    void set(size_t a_uiIndex, t_Component* a_pComponent)
    {
        assert(a_uiIndex < m_Components.size());
        if(m_Components[a_uiIndex] == a_pComponent) 
            return;
        assert(!has(a_pComponent));
        if(a_pComponent == nullptr)
        {
            remove(a_uiIndex);
        }
        else
        {
            o_emit aboutToBeReplaced(a_uiIndex, a_pComponent, m_Components[a_uiIndex]);

            if(m_OwnerSetMemberFunctionPtr)
            {
                (m_Components[a_uiIndex]->*m_OwnerSetMemberFunctionPtr)(nullptr);
            }
            if(m_IndexInOwnerDataMemberPtr)
            {
                m_Components[a_uiIndex]->*m_IndexInOwnerDataMemberPtr = std::numeric_limits<size_t>::max();
            }

            m_Components[a_uiIndex] = a_pComponent;

            if(m_OwnerSetMemberFunctionPtr)
            {
                (m_Components[a_uiIndex]->*m_OwnerSetMemberFunctionPtr)(getOwner());
            }
            if(m_IndexInOwnerDataMemberPtr)
            {
                m_Components[a_uiIndex]->*m_IndexInOwnerDataMemberPtr = a_uiIndex;
            }

            o_emit replaced(a_uiIndex, a_pComponent, m_Components[a_uiIndex]);
        }
    }

    void move(size_t a_uiOldIndex, size_t a_uiNewIndex)
    {
        if(a_uiOldIndex == a_uiNewIndex) 
            return;
        o_assert(a_uiNewIndex < m_Components.size());
        o_assert(a_uiOldIndex < m_Components.size());
        o_assert(a_uiNewIndex >= 0);
        o_assert(a_uiOldIndex >= 0);
        t_Component* pComponent = m_Components[a_uiOldIndex];
        o_emit aboutToBeMoved(a_uiOldIndex, a_uiNewIndex, pComponent);
        if(m_IndexInOwnerDataMemberPtr)
        {
            if(a_uiOldIndex < a_uiNewIndex)
            {
                for(size_t i = a_uiOldIndex+1; i<=a_uiNewIndex; ++i)
                {
                    (m_Components[i]->*m_IndexInOwnerDataMemberPtr)--;
                }
            }
            else 
            {
                for(size_t i = a_uiNewIndex; i<a_uiOldIndex; ++i)
                {
                    (m_Components[i]->*m_IndexInOwnerDataMemberPtr)++;
                }
            }
        }
        if(a_uiOldIndex < a_uiNewIndex)
        {
            auto it = m_Components.begin() + a_uiOldIndex;
            auto to = m_Components.begin() + a_uiNewIndex+1;
            std::rotate(it, it+1, to);
        }
        else
        {
            auto rit = m_Components.rbegin() + m_Components.size()-1-a_uiOldIndex;
            auto rto = m_Components.rbegin() + m_Components.size()-a_uiNewIndex;
            std::rotate(rit, rit+1, rto);
        }
        o_emit moved(a_uiOldIndex, a_uiNewIndex, pComponent);
    }

    void move(t_Component* a_pComponent, size_t a_uiNewIndex)
    {
        move(indexOf(a_pComponent), a_uiNewIndex);
    }

    void swap(size_t a_Index0, size_t a_Index1)
    {
        swap(m_Components[a_Index0], m_Components[a_Index1]);
    }

    void swap(t_Component* a_pSrc, t_Component* a_pDest)
    {
        if(a_pDest == a_pSrc) 
            return;
        size_t indexDest = indexOf(a_pDest);
        size_t indexSrc = indexOf(a_pSrc);
        o_emit aboutToBeSwapped(indexSrc, indexDest, a_pSrc, a_pDest);
        m_Components[indexDest] = a_pSrc;
        m_Components[indexSrc] = a_pDest;
        if(m_IndexInOwnerDataMemberPtr) // Update component indexes
        {
            m_Components[indexSrc]->*m_IndexInOwnerDataMemberPtr = indexSrc;
            m_Components[indexDest]->*m_IndexInOwnerDataMemberPtr = indexDest;
        }
        o_emit swapped(indexSrc, indexDest, a_pSrc, a_pDest);
    }

    bool has(t_Component* a_pComponent) const 
    {
        return std::find(m_Components.begin(), m_Components.end(), a_pComponent) != m_Components.end();
    }

    size_t indexOf(t_Component* a_pComponent) const 
    {
        return std::find(m_Components.begin(), m_Components.end(), a_pComponent)-m_Components.begin();
    }

    t_Component* get(size_t a_uiIndex) const
    {
        assert(a_uiIndex < m_Components.size());
        return m_Components[a_uiIndex];
    }

    size_t count() const { return m_Components.size(); }

    const_iterator begin() const { return m_Components.begin(); }
    const_iterator end() const { return m_Components.end(); }

    const_reverse_iterator rbegin() const { return m_Components.rbegin(); }
    const_reverse_iterator rend() const { return m_Components.rend(); }

    replacer    operator[](size_t i) { return replacer(this, i); }
    inserter    operator()(size_t i) { return inserter(this, i); }

protected:
    o_signal_data(aboutToBeInserted, size_t, t_Component*);
    o_signal_data(inserted, size_t, t_Component*);

    o_signal_data(aboutToBeRemoved, size_t, t_Component*);
    o_signal_data(removed, size_t, t_Component*);

    o_signal_data(aboutToBeReplaced, size_t, t_Component*, t_Component*);
    o_signal_data(replaced, size_t, t_Component*, t_Component*);

    o_signal_data(aboutToBeMoved, size_t, size_t, t_Component*);
    o_signal_data(moved, size_t, size_t, t_Component*);

    o_signal_data(aboutToBeSwapped, size_t, size_t, t_Component*, t_Component*);
    o_signal_data(swapped, size_t, size_t, t_Component*, t_Component*);

protected:
    sequence_type                           m_Components;
    owner_set_member_function_ptr           m_OwnerSetMemberFunctionPtr;
    owner_get_member_function_ptr           m_OwnerGetMemberFunctionPtr;
    index_in_owner_set_member_function_ptr  m_IndexInOwnerDataMemberPtr;
#if !defined(_NDEBUG)
    reflection::Class*                      m_pOwnerClass; // Only for check in debug
#endif
}; 

o_namespace_end(phantom)

#endif // o_composition_h__
