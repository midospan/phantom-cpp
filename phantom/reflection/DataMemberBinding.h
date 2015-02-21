/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_DataMemberBinding_h__
#define o_phantom_reflection_DataMemberBinding_h__



/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), DataMemberBinding);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export DataMemberBinding : public NamedElement
{
public:
    DataMemberBinding(void* a_pObject, DataMember* a_pDataMember);

    virtual Type*               getValueType() const 
    {
        return m_pDataMember->getValueType();
    }

    virtual void                getValue(void* dest) const 
    {
        m_pDataMember->getValue(m_pObject, dest);
    }

    virtual void                setValue(void const* src) const 
    {
        m_pDataMember->setValue(m_pObject, src);
    }

    virtual void*               getAddress() const 
    { 
        return m_pDataMember->getAddress(m_pObject); 
    }

    void*                       getObject() const { return m_pObject; }

    DataMember*        getDataMember() const { return m_pDataMember; }

protected:
    void referencedElementRemoved( LanguageElement* a_pElement );

protected:
    void*                   m_pObject;
    DataMember*     m_pDataMember;

};

o_namespace_end(phantom, reflection)



#endif
