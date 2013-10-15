#ifndef o_phantom_moon_TComposition_h__
#define o_phantom_moon_TComposition_h__


/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, util)

class Composition
{

};

o_namespace_end(phantom, util)

o_namespace_begin(phantom, util)

template<typename t_Owner, typename t_Component, int t_Modifiers = 0>
class TComposition : public Composition
{
    typedef t_Owner (t_Component::*owner_attribute);
    typedef vector<t_Component*> container;
public:
    TComposition(container& a_Container) 
        : m_PHANTOM_RESERVED_OwnerAttribute(nullptr)
        , m_PHANTOM_RESERVED_Components(a_Container)
    {}
	TComposition( container& a_Container, owner_attribute a_OwnerAttribute) 
        : m_PHANTOM_RESERVED_OwnerAttribute(a_OwnerAttribute)
        , m_PHANTOM_RESERVED_Components(a_Container)
    {}
	~TComposition(void) {}
	
    bool contains(t_Component* a_pComponent) const 
    {
        return std::find(m_PHANTOM_RESERVED_Components.begin(), m_PHANTOM_RESERVED_Components.end(), a_pComponent) != m_PHANTOM_RESERVED_Components.end();
    }

    void add(t_Component* a_pComponent) 
    {
        o_assert(NOT(contains(a_pComponent)));
        m_PHANTOM_RESERVED_Components.push_back(a_pComponent);
        if(m_PHANTOM_RESERVED_OwnerAttribute)
            a_pComponent->*m_PHANTOM_RESERVED_OwnerAttribute = phantom::as<t_Owner*>(this); 
        o_emit added(a_pComponent);
    }

    void set(size_t a_uiIndex, t_Component* a_pComponent)
    {
        if(m_PHANTOM_RESERVED_Components[a_uiIndex] == a_pComponent) return;
        if(m_PHANTOM_RESERVED_Components[a_uiIndex] != nullptr)
        {
            if(a_pComponent == nullptr) 
            {
                remove(m_PHANTOM_RESERVED_Components[a_uiIndex]);
                return;
            }
            o_emit removed(m_PHANTOM_RESERVED_Components[a_uiIndex]);
            if(m_PHANTOM_RESERVED_OwnerAttribute)
                m_PHANTOM_RESERVED_Components[a_uiIndex]->*m_PHANTOM_RESERVED_OwnerAttribute = nullptr;
            m_PHANTOM_RESERVED_Components[a_uiIndex] = a_pComponent;
            if(m_PHANTOM_RESERVED_OwnerAttribute)
                a_pComponent->*m_PHANTOM_RESERVED_OwnerAttribute = phantom::as<t_Owner*>(this); 
            o_emit added(a_pComponent);
        }
    }

    t_Component* get(size_t a_uiIndex) const { return m_PHANTOM_RESERVED_Components[a_uiIndex]; }

    size_t indexOf(t_Component* a_pComponent) const 
    {
        auto it = m_PHANTOM_RESERVED_Components.begin();
        auto end = m_PHANTOM_RESERVED_Components.end();
        size_t index = 0;
        for(;it!=end;++it)
        {
            if(a_pComponent == *it) return index;
            ++index;
        }
        return index;
    }

    void remove(t_Component* a_pComponent) 
    {
        o_assert(contains(a_pComponent));
        o_emit removed(a_pComponent);
        if(m_PHANTOM_RESERVED_OwnerAttribute)
            a_pComponent->*m_PHANTOM_RESERVED_OwnerAttribute = nullptr;
        m_PHANTOM_RESERVED_Components.erase(std::find(m_PHANTOM_RESERVED_Components.begin(), m_PHANTOM_RESERVED_Components.end(), a_pComponent));
    }

    void move(t_Component* a_pComponent, size_t a_uiNewIndex)
    {
        o_assert(a_uiNewIndex < m_PHANTOM_RESERVED_Components.size());
        auto it = std::find(m_PHANTOM_RESERVED_Components.begin(), m_PHANTOM_RESERVED_Components.end(), a_pComponent);
        auto to = m_PHANTOM_RESERVED_Components.begin() + index;
        if(it == to) return;
        if(it < to)
        {
            std::rotate(it, it+1, to);
        }
        else
        {
            auto rit = std::find(m_PHANTOM_RESERVED_Components.rbegin(),
                m_PHANTOM_RESERVED_Components.rend(), a_pComponent);
            auto rto = m_PHANTOM_RESERVED_Components.rbegin() + m_PHANTOM_RESERVED_Components.size()-index;
            std::rotate(rit, rit+1, rto);
        }
    }

    phantom::util::Iterator* getIterator() const
    {
        return typeOf<container>()->begin(&m_PHANTOM_RESERVED_Components);
    }

protected:
    o_signal_data(added, t_Component*);
    o_signal_data(removed, t_Component*);

protected:
    container&      m_PHANTOM_RESERVED_Components;
    owner_attribute m_PHANTOM_RESERVED_OwnerAttribute;

private:
    void ____defaultConstructibleAndIncludeChecker()
    {
        t_Component c;
    }
};

o_namespace_end(phantom, util)

o_classN((phantom, util), Composition)
{
    o_reflection
    {
    };
};
o_exposeN((phantom, util), Composition);

o_classNTS((phantom, util), (typename, typename, int), (t_Owner, t_Component, t_Modifiers), TComposition, (Composition))
{
	o_reflection
    {
        o_signal(added, (t_Component*));
        o_signal(removed, (t_Component*));
        o_collection(t_Component*, components, add, move, remove, set, get, indexOf, o_component|t_Modifiers);
	};
};
o_exposeNT((phantom, util), (typename, typename, int), (t_Owner, t_Component, t_Modifiers), TComposition);

#endif
