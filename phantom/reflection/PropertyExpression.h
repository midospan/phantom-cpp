/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_PropertyExpression_h__
#define o_phantom_reflection_PropertyExpression_h__

/* ****************** Includes ******************* */
#include <phantom/reflection/LValueExpression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), PropertyExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export PropertyExpression : public LValueExpression
{
    o_language_element;

public:
    PropertyExpression(Expression* a_pLeftExpression, Property* a_pProperty);

    o_terminate();

    virtual PropertyExpression* asPropertyExpression() const { return (PropertyExpression*)this; }

    virtual void*        internalEvalAddress() const;

    Expression*         getLeftExpression() const 
    { 
        return m_pLeftExpression; 
    }

    Property*           getProperty() const { return m_pProperty; }

    virtual void        flush() const;

    virtual bool        isPersistent() const;

    virtual PropertyExpression*  clone() const;

    virtual LanguageElement* getHatchedElement() const;

protected:
    void referencedElementRemoved( LanguageElement* a_pElement );

protected:
    Expression*         m_pLeftExpression;
    Property*           m_pProperty;
    void*               m_pBuffer;

};

o_namespace_end(phantom, reflection)



#endif
