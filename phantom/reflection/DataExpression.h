/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_DataExpression_h__
#define o_phantom_reflection_DataExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), DataExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export DataExpression : public Expression
{
    o_language_element;

public:
    DataExpression(serialization::DataBase* a_pDataBase, ConstantExpression* a_pGuidExpression);
    o_destructor ~DataExpression(void)     {}

    virtual DataExpression* asDataExpression() const { return (DataExpression*)this; }

    virtual bool hasValueStorage() const { return true; }

    virtual void* evalStorage() const;

    virtual void internalEval(void* a_pDest) const;

    virtual DataExpression* clone() const;

    virtual bool isEffectiveAddressFixed() const { return true; }

    ConstantExpression* getGuidExpression() const { return m_pGuidExpression; }

    serialization::DataBase* getDataBase() const { return m_pDataBase; }

protected:
    serialization::DataBase* m_pDataBase;
    ConstantExpression* m_pGuidExpression;
    void*   m_Buffer;
};

o_namespace_end(phantom, reflection)



#endif
