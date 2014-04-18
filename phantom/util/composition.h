#ifndef o_composition_h__
#define o_composition_h__


/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
o_declareNT(class, (phantom), (typename), (t_Component), composition);
/* *********************************************** */

o_namespace_begin(phantom)
    
template <typename t_Component>
class composition
{
public:
    typedef void* (t_Component::*owner_get_member_function_ptr)() const;
    typedef void (t_Component::*owner_set_member_function_ptr)(void*);
    typedef vector<t_Component*> sequence_type;
    typedef t_Component component_type;
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
                ((*it)->*m_OwnerSetMemberFunctionPtr)(this);
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
        }
        m_Components.erase(m_Components.begin()+a_uiIndex);
        o_emit removed(a_uiIndex, pComponent);
        return pComponent;
    }

    void remove(t_Component* a_pComponent)
    {
        remove(indexOf(a_pComponent));
    }

    void set(size_t a_uiIndex, t_Component* a_pComponent)
    {
        assert(a_uiIndex < m_Components.size());
        if(m_Components[a_uiIndex] == a_pComponent) 
            return;
        assert(!has(a_pComponent));
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

    void move(t_Component* a_pComponent, size_t a_uiNewIndex)
    {
        o_assert(has(a_pComponent));
        size_t uiOldIndex = indexOf(a_pComponent);
        if(uiOldIndex == a_uiNewIndex) 
            return;
        o_emit aboutToBeMoved(a_pComponent, a_uiNewIndex, uiOldIndex);
        o_assert(a_uiNewIndex < m_Components.size());
        auto it = m_Components.begin() + uiOldIndex;
        auto to = m_Components.begin() + a_uiNewIndex;
        if(it == to) return;
        if(it < to)
        {
            std::rotate(it, it+1, to);
        }
        else
        {
            auto rit = m_Components.rbegin() + m_Components.size()-uiOldIndex;
            auto rto = m_Components.rbegin() + m_Components.size()-a_uiNewIndex;
            std::rotate(rit, rit+1, rto);
        }
        o_emit moved(a_pComponent, a_uiNewIndex, uiOldIndex);
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

    typename sequence_type::const_iterator begin() const { return m_Components.begin(); }
    typename sequence_type::const_iterator end() const { return m_Components.end(); }

    typename sequence_type::const_reverse_iterator rbegin() const { return m_Components.rbegin(); }
    typename sequence_type::const_reverse_iterator rend() const { return m_Components.rend(); }

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
