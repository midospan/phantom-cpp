/* TODO LICENCE HERE */

#ifndef reflection_ConstIterator_h__
#define reflection_ConstIterator_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), ConstIterator)
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export ConstIterator : public NamedElement
{
    o_declare_meta_type(ConstIterator);

public:
    ConstIterator(void)              {}
    o_destructor ~ConstIterator(void){}

    virtual boolean             hasNext() const = 0;
    virtual const void*         pointer() const = 0;
    virtual void                next(void* ) = 0;
    virtual void                getValue(void* dest) const = 0;
    virtual reflection::Type*   getValueType() const = 0;
    virtual void                advance(size_t offset) = 0;

protected:
    
};

o_namespace_end(phantom, reflection)



#endif
