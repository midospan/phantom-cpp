/* TODO LICENCE HERE */

#ifndef reflection_Iterator_h__
#define reflection_Iterator_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Iterator)
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Iterator : public NamedElement
{
    o_declare_meta_type(Iterator);

public:
    Iterator(void)              {}
    o_destructor ~Iterator(void){}

    virtual boolean             hasNext() const = 0;
    virtual void*               pointer() const = 0;
    virtual void                next(void* ) = 0;
    virtual void                getValue(void* dest) const = 0;
    virtual void                setValue(const void* a_pSrc) const = 0;
    virtual reflection::Type*   getValueType() const = 0;
    virtual void                advance(size_t offset = 1) = 0;

protected:
    
};
/*


template<typename t_OwnerTy, typename t_ElementTy>
struct has_sequential_collection
{
    enum { value = phantom::container::has_member_function_add<t_OwnerTy, void(t_ElementTy)>::value
                && phantom::container::has_member_function_remove<t_OwnerTy, void(t_ElementTy)>::value 
                && phantom::container::has_member_function_set<t_OwnerTy, void(t_ElementTy, size_t)>::value 
                && phantom::container::has_member_function_added<t_OwnerTy, signal_t(t_ElementTy)>::value 
                && phantom::container::has_member_function_aboutToBeRemoved<t_OwnerTy, signal_t(t_ElementTy)>::value 
                && phantom::container::has_member_function_removed<t_OwnerTy, signal_t(t_ElementTy)>::value 
                && phantom::container::has_member_function_swap<t_OwnerTy, void(size_t, size_t)>::value  
                && phantom::container::has_member_function_swaped<t_OwnerTy, signal_t(size_t, size_t)>::value  
                && phantom::container::has_member_function_iterator<t_OwnerTy, void(TIterator<t_ElementTy>**)>::value
          
    };
};*/

o_namespace_end(phantom, reflection)



#endif
