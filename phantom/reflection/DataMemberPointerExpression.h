/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_DataMemberPointerExpression_h__
#define o_phantom_reflection_DataMemberPointerExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), DataMemberPointerExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export DataMemberPointerExpression : public Expression
{
    o_language_element;

public:
    DataMemberPointerExpression(DataMemberPointerType* a_pDataMemberPointerType, Expression* a_pObjectExpression, Expression* a_pMemberExpression);
    ~DataMemberPointerExpression();

    o_terminate();

    virtual DataMemberPointerExpression* asDataMemberPointerExpression() const { return (DataMemberPointerExpression*)this; }

    virtual void internalEval(void* a_pDest) const ;

    DataMemberPointerType* getDataMemberPointerType() const { return m_pDataMemberPointerType; }

    Expression* getObjectExpression() const { return m_pObjectExpression; }

    Expression* getMemberExpression() const { return m_pMemberExpression; }

    virtual DataMemberPointerExpression* clone() const;

protected:
    DataMemberPointerType* m_pDataMemberPointerType;
    Expression* m_pObjectExpression;
    Expression* m_pMemberExpression;
};

o_namespace_end(phantom, reflection)



#endif
