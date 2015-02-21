/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_MemberFunctionPointerCallExpression_h__
#define o_phantom_reflection_MemberFunctionPointerCallExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/CallExpression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), MemberFunctionPointerCallExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export MemberFunctionPointerCallExpression : public CallExpression
{
    o_language_element;

public:
    MemberFunctionPointerCallExpression(MemberFunctionPointerType* a_pMemberFunctionPointerType, Expression* a_pObjectExpression, Expression* a_pMemberExpression, const vector<Expression*>& a_Arguments);
    ~MemberFunctionPointerCallExpression();

    o_terminate();

    virtual MemberFunctionPointerCallExpression* asMemberFunctionPointerCallExpression() const { return (MemberFunctionPointerCallExpression*)this; }

    virtual void internalEval(void* a_pDest) const ;

    virtual void internalEval() const ;

    Expression* getObjectExpression() const { return m_pObjectExpression; }

    Expression* getMemberExpression() const { return m_pMemberExpression; }

    MemberFunctionPointerType* getMemberFunctionPointerType() const { return m_pMemberFunctionPointerType; }

protected:
    virtual Type* returnStorageType() const { return m_pMemberFunctionPointerType->getReturnType(); }

protected:
    MemberFunctionPointerType* m_pMemberFunctionPointerType;
    Expression* m_pObjectExpression;
    Expression* m_pMemberExpression;
};

o_namespace_end(phantom, reflection)



#endif
