/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_DataMemberExpression_h__
#define o_phantom_reflection_DataMemberExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/LValueExpression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), DataMemberExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export DataMemberExpression : public LValueExpression
{
    o_language_element;

public:
    DataMemberExpression(Expression* a_pLeftExpression, DataMember* a_pDataMember);

    virtual DataMemberExpression* asDataMemberExpression() const { return (DataMemberExpression*)this; }

    virtual void*    internalEvalAddress() const;

    Expression*                 getLeftExpression() const { return m_pLeftExpression; }

    DataMember*         getDataMember() const { return m_pDataMember; }

    virtual void                flush() const { m_pLeftExpression->flush(); }

    virtual LanguageElement*    getHatchedElement() const;

    virtual bool                isPersistent() const;

    virtual DataMemberExpression* clone() const;

protected:
    void referencedElementRemoved( LanguageElement* a_pElement );

protected:
    Expression*             m_pLeftExpression;
    DataMember*     m_pDataMember;

};

o_namespace_end(phantom, reflection)



#endif
