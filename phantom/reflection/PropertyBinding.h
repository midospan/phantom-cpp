/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_PropertyBinding_h__
#define o_phantom_reflection_PropertyBinding_h__

/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), PropertyBinding);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export PropertyBinding : public NamedElement
{
public:
    PropertyBinding(void* a_pObject, Property* a_pProperty);

    o_initialize();

    virtual Type*       getValueType() const 
    {
        return m_pProperty->getValueType();
    }

    virtual void        getValue(void* dest) const 
    {
        m_pProperty->getValue(m_pObject, dest);
    }

    virtual void        setValue(void const* src) const 
    {
        m_pProperty->setValue(m_pObject, src);
    }

    void*               getObject() const { return m_pObject; }

    Property*           getProperty() const { return m_pProperty; }

    virtual PropertyBinding* clone() const;

protected:
    void referencedElementRemoved( LanguageElement* a_pElement );

protected:
    void*           m_pObject;
    Property*       m_pProperty;

};

o_namespace_end(phantom, reflection)



#endif
