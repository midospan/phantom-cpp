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
    typedef composition_inserter<t_Component> inserter;
    typedef composition_replacer<t_Component> replacer;
    typedef vector<t_Component*> sequence_type;
    typedef t_Component component_type;
    typedef typename sequence_type::const_iterator const_iterator;
    typedef typename sequence_type::const_reverse_iterator const_reverse_iterator;
    typedef void* (t_Component::*owner_get_member_function_ptr)() const;
    typedef void (t_Component::*owner_set_member_function_ptr)(void*);
    typedef size_t (t_Component::*index_in_owner_set_member_function_ptr);

public:
    composition() 
        : m_pOwner(nullptr)
        , m_OwnerSetMemberFunctionPtr(nullptr)
        , m_OwnerGetMemberFunctionPtr(nullptr)
        , m_IndexInOwnerDataMemberPtr(nullptr)
    {
    }
    template<typename t_OwnerTy>
    composition(t_OwnerTy* a_pOwner
                            , void (t_Component::*a_OwnerSetMemberFunctionPtr)(t_OwnerTy*)  
                        , t_OwnerTy* (t_Component::*a_OwnerGetMemberFunctionPtr)() const  
                        , index_in_owner_set_member_function_ptr a_IndexInOwnerDataMemberPtr = nullptr) 

        : m_pOwner(a_pOwner)
        , m_OwnerSetMemberFunctionPtr((owner_set_member_function_ptr)a_OwnerSetMemberFunctionPtr)
        , m_OwnerGetMemberFunctionPtr((owner_get_member_function_ptr)a_OwnerGetMemberFunctionPtr)
        , m_IndexInOwnerDataMemberPtr(a_IndexInOwnerDataMemberPtr)
    {
        o_assert(a_OwnerSetMemberFunctionPtr);
        o_assert(a_OwnerGetMemberFunctionPtr);
    }
    o_initialize()
    {

    }
    o_restore(filter, pass)
    {
        if(m_IndexInOwnerDataMemberPtr)
        {
            for(size_t i = 0; i<m_Components.size(); ++i)
            {
                m_Components[i]->*m_IndexInOwnerDataMemberPtr = i;
            }
        }
        if(m_OwnerSetMemberFunctionPtr)
        {
            for(auto it = begin(); it != end(); ++it)
            {
                ((*it)->*m_OwnerSetMemberFunctionPtr)(m_pOwner);
            }
        }
        return restore_complete;
    }

    o_terminate()
    {

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
            (a_pComponent->*m_OwnerSetMemberFunctionPtr)(m_pOwner);
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
        assert(m_OwnerGetMemberFunctionPtr == nullptr || (pComponent->*m_OwnerGetMemberFunctionPtr)() == m_pOwner);
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
                (m_Components[a_uiIndex]->*m_OwnerSetMemberFunctionPtr)(m_pOwner);
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
        o_emit aboutToBeMoved(pComponent, a_uiOldIndex, a_uiNewIndex);
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
        o_emit moved(pComponent, a_uiOldIndex, a_uiNewIndex);
    }

    void move(t_Component* a_pComponent, size_t a_uiNewIndex)
    {
        move(indexOf(a_pComponent), a_uiNewIndex);
    }

    void swap(t_Component* a_pDest, t_Component* a_pSrc)
    {
        if(a_pDest == a_pSrc) 
            return;
        o_emit aboutToBeSwapped(a_pDest, a_pSrc);
        size_t indexDest = indexOf(a_pDest);
        size_t indexSrc = indexOf(a_pSrc);
        m_Components[indexDest] = a_pSrc;
        m_Components[indexSrc] = a_pDest;
        if(m_IndexInOwnerDataMemberPtr) // Update component indexes
        {
            m_Components[indexSrc]->*m_IndexInOwnerDataMemberPtr = indexSrc;
            m_Components[indexDest]->*m_IndexInOwnerDataMemberPtr = indexDest;
        }
        o_emit swapped(a_pDest, a_pSrc);
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

    o_signal_data(aboutToBeMoved, t_Component*, size_t, size_t);
    o_signal_data(moved, t_Component*, size_t, size_t);

    o_signal_data(aboutToBeSwapped, t_Component*, t_Component*);
    o_signal_data(swapped, t_Component*, t_Component*);

protected:
    void*                                   m_pOwner;
    sequence_type                           m_Components;
    owner_set_member_function_ptr           m_OwnerSetMemberFunctionPtr;
    owner_get_member_function_ptr           m_OwnerGetMemberFunctionPtr;
    index_in_owner_set_member_function_ptr  m_IndexInOwnerDataMemberPtr;
}; 

o_namespace_end(phantom)

#endif // o_composition_h__
