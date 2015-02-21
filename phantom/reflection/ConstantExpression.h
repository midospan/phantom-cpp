/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_ConstantExpression_h__
#define o_phantom_reflection_ConstantExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), ConstantExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export ConstantExpression : public Expression
{
    o_language_element;

public:
    ConstantExpression(Constant* a_pConstant, Expression* a_pChildExpression = nullptr);
    o_destructor ~ConstantExpression(void);

    virtual  ConstantExpression* asConstantExpression() const { return (ConstantExpression*)this; }

    virtual void    setValue(void const* a_pSrc) const;

    virtual void    internalEval(void* a_pDest) const;

    Constant* getConstant() const { return m_pConstant; }

    virtual bool isConstExpression() const { return true; }

    virtual bool hasValueStorage() const { return true; }

    void* evalStorage() const { return m_pTempValue; }

    virtual void internalEval() const 
    {
    }

    virtual LanguageElement* hatch();   

    virtual LanguageElement* getHatchedElement() const { return m_pConstant; }
    virtual ConstantExpression*     clone() const;

    virtual bool isPersistent() const;

protected:
    virtual void elementRemoved( LanguageElement* a_pElement );
    virtual void referencedElementRemoved( LanguageElement* a_pElement );

protected:
    Constant*   m_pConstant;
    void*       m_pTempValue;
};

o_namespace_end(phantom, reflection)



#endif
