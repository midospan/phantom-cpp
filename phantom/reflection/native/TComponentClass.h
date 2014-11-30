#ifndef TComponentClass_h__
#define TComponentClass_h__

/* ****************** Includes ******************* */
#include <phantom/reflection/ComponentClass.h>
/* **************** Declarations ***************** */
o_declareNT(class, (phantom, reflection, native), (typename), (t_Ty), TComponentClass);
/* *********************************************** */

o_namespace_begin(phantom, reflection, native)

template<typename t_Ty>
class TComponentClass : public ComponentClass
{
    typedef o_NESTED_TYPE t_Ty::pointed_type pointed_type;
    typedef t_Ty                             component_type;

public:
    TComponentClass(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0)
        : ComponentClass(typeOf<pointed_type>(), a_strName, a_uiSize, a_uiAlignment, a_Modifiers|o_native)
    {
    }

    virtual void blockSignals(void* a_pComponent) const
    {
        static_cast<component_type*>(a_pComponent)->blockSignals();
    }

    virtual void unblockSignals(void* a_pComponent) const
    {
        static_cast<component_type*>(a_pComponent)->unblockSignals();
    }

    virtual void*       owner(const void* a_pComponent) const 
    {
        return static_cast<const component_type*>(a_pComponent)->getOwner();
    }

    virtual void        set(void* a_pComponent, const void* a_pSrc) const 
    {
        // *static_cast<component_type*>(a_pComponent) = *static_cast< pointed_type*const*>(a_pSrc);
    }

    virtual void        get(const void* a_pComponent, void* a_pDest) const
	{
		*static_cast<pointed_type**>(a_pDest) = static_cast<const component_type*>(a_pComponent)->get();
	}


    virtual Signal* getAboutToBeChangedSignal() const { return getSignal("aboutToBeChanged(t_Component*, t_Component*)"); }
    virtual Signal* getChangedSignal() const          { return getSignal("changed(t_Component*, t_Component*)"); }
    

};

o_namespace_end(phantom, reflection, native)


#endif
