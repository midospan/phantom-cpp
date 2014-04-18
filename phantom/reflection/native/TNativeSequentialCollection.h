#ifndef o_reflection_TNativeSequentialCollection_h__
#define o_reflection_TNativeSequentialCollection_h__


/* ****************** Includes ******************* */

/* **************** Declarations ***************** */
o_declareNT(class, (phantom, reflection, native), (typename, typename), (t_OwnerTy, t_ElementTy), TNativeSequentialCollection);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

template<typename t_OwnerTy, typename t_ElementTy>
struct TNativeSequentialCollection : public SequencialCollection
{
    o_static_assert_msg((phantom::container::has_member_function_add<t_OwnerTy, void(t_ElementTy)>::value), "missing add function");
    o_static_assert_msg((phantom::container::has_member_function_remove<t_OwnerTy, void(t_ElementTy)>::value), "missing remove function");
    o_static_assert_msg((phantom::container::has_member_function_set<t_OwnerTy, void(size_t, t_ElementTy)>::value), "missing set function");
    o_static_assert_msg((phantom::container::has_member_function_added<t_OwnerTy, signal_t(t_ElementTy)>::value), "missing added function");
    o_static_assert_msg((phantom::container::has_member_function_aboutToBeRemoved<t_OwnerTy, signal_t(t_ElementTy)>::value), "missing aboutToBeRemoved function"); 
    o_static_assert_msg((phantom::container::has_member_function_removed<t_OwnerTy, signal_t(t_ElementTy)>::value), "missing removed function");
    o_static_assert_msg((phantom::container::has_member_function_swap<t_OwnerTy, void(size_t, size_t)>::value), "missing swap function");
    o_static_assert_msg((phantom::container::has_member_function_swaped<t_OwnerTy, signal_t(size_t, size_t)>::value), "missing swaped function");
    o_static_assert_msg((phantom::container::has_member_function_iterator<t_OwnerTy, void(TIterator<t_ElementTy>**)>::value), "missing iterator function");
    o_static_assert_msg((phantom::container::has_member_function_indexOf<t_OwnerTy, size_t(t_ElementTy)>::value), "missing indexOf function");

    virtual Signal* getAddedSignal() const { return phantom::typeOf<t_OwnerTy>()->getSignal("added("+typeNameOf<t_ElementTy>()+")"); }
    virtual Signal* getRemovedSignal() const { return phantom::typeOf<t_OwnerTy>()->getSignal("removed("+typeNameOf<t_ElementTy>()+")"); }
    virtual Signal* getAboutToBeRemovedSignal() const { return phantom::typeOf<t_OwnerTy>()->getSignal("aboutToBeRemoved("+typeNameOf<t_ElementTy>()+")"); }
    virtual Signal* getSwapedSignal() const { return phantom::typeOf<t_OwnerTy>()->getSignal("swaped(size_t,size_t)"); }

    virtual void add(void* a_pInstance, void* a_pSrc) const 
    {
        static_cast<t_OwnerTy*>(a_pInstance)->add(*static_cast<t_ElementTy*>(a_pSrc));
    }
    virtual void remove(void* a_pInstance, void* a_pSrc) const 
    {
        static_cast<t_OwnerTy*>(a_pInstance)->remove(*static_cast<t_ElementTy*>(a_pSrc));
    }
    virtual void set(void* a_pInstance, size_t a_Index, void* a_pSrc) const 
    {
        static_cast<t_OwnerTy*>(a_pInstance)->set(a_Index, *static_cast<t_ElementTy*>(a_pSrc));
    }
    virtual void swap(void* a_pInstance, size_t a_Index0, size_t a_Index1) const 
    {
        static_cast<t_OwnerTy*>(a_pInstance)->swap(a_Index0, a_Index1);
    }
    virtual void iterator(Iterator** a_ppIterator) const 
    {
        static_cast<t_OwnerTy*>(a_pInstance)->iterator((Iterator**)a_ppIterator);
    }
    virtual size_t index(void* a_pInstance, void* a_pSrc) const 
    {
        return static_cast<t_OwnerTy*>(a_pInstance)->index(*static_cast<t_ElementTy*>(a_pSrc))
    }

};

o_namespace_end(phantom, reflection)

#endif // o_reflection_TNativeSequentialCollection_h__
