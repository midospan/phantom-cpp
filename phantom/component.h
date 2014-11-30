#ifndef o_component_h__
#define o_component_h__


/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
o_declareNT(class, (phantom), (typename), (t_Component), component);
/* *********************************************** */

o_namespace_begin(phantom)

template <typename t_Component>
class component
{
public:
    //o_static_assert_msg(boost::is_class<t_Component>::value AND (meta_specifiers<t_Component>::value&o_pod) == 0, "t_Component must be a non-declared-pod class");
    typedef component<t_Component> self_type;
    typedef t_Component pointed_type;
    typedef void* (t_Component::*owner_get_member_function_ptr)() const;
    typedef void (t_Component::*owner_set_member_function_ptr)(void*);

public:
    component() 
        : m_OwnerSetMemberFunctionPtr(nullptr)
        , m_OwnerGetMemberFunctionPtr(nullptr)
        , m_pPointer(nullptr)
#if !defined(_NDEBUG)
        , m_pOwnerClass(nullptr)
#endif
    {
    }
    component(t_Component* a_pPointer) 
        : m_OwnerSetMemberFunctionPtr(nullptr)
        , m_OwnerGetMemberFunctionPtr(nullptr)
        , m_pPointer(a_pPointer)
#if !defined(_NDEBUG)
        , m_pOwnerClass(nullptr)
#endif
    {
    }
    template<typename t_OwnerTy>
    component(void (t_Component::*a_OwnerSetMemberFunctionPtr)(t_OwnerTy*)  
        , t_OwnerTy* (t_Component::*a_OwnerGetMemberFunctionPtr)() const) 

        : m_OwnerSetMemberFunctionPtr((owner_set_member_function_ptr)a_OwnerSetMemberFunctionPtr)
        , m_OwnerGetMemberFunctionPtr((owner_get_member_function_ptr)a_OwnerGetMemberFunctionPtr)
        , m_pPointer(nullptr)
#if !defined(_NDEBUG)
        , m_pOwnerClass(typeOf<t_OwnerTy>())
#endif
    {
        o_assert(a_OwnerSetMemberFunctionPtr);
        o_assert(a_OwnerGetMemberFunctionPtr);
    }
    template<typename t_OwnerTy>
    component(t_Component* a_pPointer, void (t_Component::*a_OwnerSetMemberFunctionPtr)(t_OwnerTy*)  
                        , t_OwnerTy* (t_Component::*a_OwnerGetMemberFunctionPtr)() const) 

        : m_OwnerSetMemberFunctionPtr((owner_set_member_function_ptr)a_OwnerSetMemberFunctionPtr)
        , m_OwnerGetMemberFunctionPtr((owner_get_member_function_ptr)a_OwnerGetMemberFunctionPtr)
        , m_pPointer(a_pPointer)
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
        const rtti_data* owner = rttiDataOf(this).owner;
        o_assert(m_pOwnerClass == nullptr OR owner->layout_class->getBaseClassOffsetCascade(m_pOwnerClass) == 0, "Owner class must have the same layout position as the argument class pointer passed in set-owner (resp. retrived with get-owner) member functions");
#endif
    }
    o_restore(filter, pass)
    {
#if !defined(_NDEBUG)
        if(pass == 0)
        {
            const rtti_data* owner = rttiDataOf(this).owner;
            o_assert(m_pOwnerClass == nullptr OR owner->layout_class->getBaseClassOffsetCascade(m_pOwnerClass) == 0, "Owner class must have the same layout position as the argument class pointer passed in set-owner (resp. retrived with get-owner) member functions");
        }
#endif
        return restore_complete;
    }

    o_terminate()
    {
        if(m_pPointer)
        {
            o_dynamic_delete m_pPointer;
            m_pPointer = nullptr;
        }
    }

    o_forceinline void* getOwner() const 
    { 
        const rtti_data* ownerRtti = rttiDataOf(this).owner;
        return ownerRtti ? ownerRtti->layout : 0;
    }

    void blockSignals() 
    {
        o_block_signal(aboutToBeChanged);
        o_block_signal(changed);
    }

    void unblockSignals()
    {
        o_unblock_signal(changed);
        o_unblock_signal(changed);
    }

    t_Component* get() const { return m_pPointer; }

    operator t_Component*() const
    {
        return m_pPointer;
    }

    bool operator==(t_Component* a_pComponent) const { return a_pComponent == m_pPointer; }

    bool operator!=(t_Component* a_pComponent) const { return a_pComponent != m_pPointer; }

    bool operator<(t_Component* a_pPointer) const { return m_pPointer < a_pPointer; }

    bool operator>(t_Component* a_pPointer) const { return m_pPointer > a_pPointer; }

    bool operator<=(t_Component* a_pPointer) const { return m_pPointer <= a_pPointer; }

    bool operator>=(t_Component* a_pPointer) const { return m_pPointer >= a_pPointer; }

    bool operator!() const { return !m_pPointer; }

    self_type& operator=(t_Component* a_pPointer) 
    {
        if(m_pPointer != a_pPointer) 
        {
            t_Component* pOldPointer = m_pPointer;
            o_emit aboutToBeChanged(pOldPointer, a_pPointer);
            m_pPointer = a_pPointer;
            o_emit changed(pOldPointer, a_pPointer);
            if(pOldPointer)
            {
                o_dynamic_delete pOldPointer;
            }
        }
        return *this;
    }

    t_Component& operator*() const { return *m_pPointer; }

    t_Component* operator->() const { return m_pPointer; }

protected:
    o_signal_data(aboutToBeChanged, t_Component*, t_Component*);
    o_signal_data(changed, t_Component*, t_Component*);

protected:
    t_Component*        m_pPointer;
#if !defined(_NDEBUG)
    reflection::Class*  m_pOwnerClass; // Only for check in debug
#endif
    owner_get_member_function_ptr m_OwnerGetMemberFunctionPtr;
    owner_set_member_function_ptr m_OwnerSetMemberFunctionPtr;
}; 

o_namespace_end(phantom)

#endif // o_component_h__
