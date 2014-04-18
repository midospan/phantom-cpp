#ifndef o_reflection_TNativeSequentialCollection_h__
#define o_reflection_TNativeSequentialCollection_h__


/* ****************** Includes ******************* */

/* **************** Declarations ***************** */
o_declareNT(class, (phantom, reflection, native), (typename, typename, typename), (t_OwnerTy, t_KeyTy, t_ElementTy), TNativeSequentialCollection);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

    template<typename t_OwnerTy, typename t_KeyTy, typename t_ElementTy>
struct TNativeMapCollection : public MapCollection
{
    o_static_assert_msg((phantom::container::has_member_function_add<t_OwnerTy, void(t_KeyTy, t_ElementTy)>::value), "missing add function");
    o_static_assert_msg((phantom::container::has_member_function_remove<t_OwnerTy, void(t_KeyTy)>::value), "missing remove function");
    o_static_assert_msg((phantom::container::has_member_function_set<t_OwnerTy, void(t_KeyTy, t_ElementTy)>::value), "missing set function");
    o_static_assert_msg((phantom::container::has_member_function_added<t_OwnerTy, signal_t(t_KeyTy)>::value), "missing added function");
    o_static_assert_msg((phantom::container::has_member_function_aboutToBeRemoved<t_OwnerTy, signal_t(t_KeyTy)>::value), "missing aboutToBeRemoved function"); 
    o_static_assert_msg((phantom::container::has_member_function_removed<t_OwnerTy, signal_t(t_KeyTy, t_ElementTy)>::value), "missing removed function");
    o_static_assert_msg((phantom::container::has_member_function_swap<t_OwnerTy, void(size_t, size_t)>::value), "missing swap function");
    o_static_assert_msg((phantom::container::has_member_function_swaped<t_OwnerTy, signal_t(size_t, size_t)>::value), "missing swaped function");
    o_static_assert_msg((phantom::container::has_member_function_iterator<t_OwnerTy, void(TIterator<t_ElementTy>**)>::value), "missing iterator function");

    virtual Signal* getAddedSignal() const { return phantom::typeOf<t_OwnerTy>()->getSignal("added("+typeNameOf<t_KeyTy>()+")"); }
    virtual Signal* getRemovedSignal() const { return phantom::typeOf<t_OwnerTy>()->getSignal("removed("+typeNameOf<t_KeyTy>()+","+typeNameOf<t_ElementTy>()+")"); }
    virtual Signal* getAboutToBeRemovedSignal() const { return phantom::typeOf<t_OwnerTy>()->getSignal("aboutToBeRemoved("+typeNameOf<t_KeyTy>()+")"); }
    virtual Signal* getSwapedSignal() const { return phantom::typeOf<t_OwnerTy>()->getSignal("swaped(size_t,size_t)"); }

    virtual void add(void* a_pInstance, const void* a_pKeySrc, void* a_pSrc)  const
    {
        static_cast<t_OwnerTy*>(a_pInstance)->add(*static_cast<t_ElementTy*>(a_pSrc));
    }
    virtual void remove(void* a_pInstance, const void* a_pKeySrc) const
    {
        static_cast<t_OwnerTy*>(a_pInstance)->remove(*static_cast<const t_KeyTy*>(a_pKeySrc));
    }
    virtual void set(void* a_pInstance, const void* a_pKeySrc, void* a_pSrc) const
    {
        static_cast<t_OwnerTy*>(a_pInstance)->set(*const t_KeyTy*>(a_pKeySrc), *static_cast<t_ElementTy*>(a_pSrc));
    }
    virtual void get(void* a_pInstance, const void* a_pKeySrc, void* a_pDest) const
    {
        static_cast<t_OwnerTy*>(a_pInstance)->get(*const t_KeyTy*>(a_pKeySrc), static_cast<t_ElementTy*>(a_pDest));
    }
    virtual void swap(void* a_pInstance, const void* a_pKeySrc0, const void* a_pKeySrc1) const
    {
        static_cast<t_OwnerTy*>(a_pInstance)->swap(*const t_KeyTy*>(a_pKeySrc0), *const t_KeyTy*>(a_pKeySrc1));
    }
    virtual void iterator(Iterator** a_ppIterator) const
    {
        static_cast<t_OwnerTy*>(a_pInstance)->iterator((TMapIterator<t_KeyTy, t_ElementTy>**)a_ppIterator);
    }

};

o_namespace_end(phantom, reflection)

#endif // o_reflection_TNativeSequentialCollection_h__
