/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Range_h__
#define o_phantom_reflection_Range_h__

/* ****************** Includes ******************* */
#include <phantom/phantom.h>

/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Range : public LanguageElement
{
public:
    static Class* const metaType;

public:
    Range(Type* a_pType);

    Type* getType() const { return m_pType; }

    virtual void getMin(void* a_pDest) const = 0;
    virtual void getMax(void* a_pDest) const = 0;
    virtual void getDefault(void* a_pDest) const = 0;

    virtual void setMin(const void* a_pSrc) = 0;
    virtual void setMax(const void* a_pSrc) = 0;
    virtual void setDefault(const void* a_pSrc) = 0;

    virtual Range* clone() const = 0;

protected:
    Type* m_pType;
};

o_namespace_end(phantom, reflection)



#endif
