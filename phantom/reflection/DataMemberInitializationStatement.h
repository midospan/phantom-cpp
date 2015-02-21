/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_DataMemberInitializationStatement_h__
#define o_phantom_reflection_DataMemberInitializationStatement_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/LValueInitializationStatement.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), DataMemberInitializationStatement);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export DataMemberInitializationStatement : public LValueInitializationStatement
{
    o_language_element;

public:
    DataMemberInitializationStatement( Expression* a_pThisExpression, DataMember* a_pDataMember, Expression* a_pRightExpression );
    ~DataMemberInitializationStatement();

    virtual DataMemberInitializationStatement* asDataMemberInitializationStatement() const { return (DataMemberInitializationStatement*)this; }

    virtual void    internalEval() const;

    virtual void    flush() const {}

    DataMember*     getDataMember() const { return m_pDataMember; }
    Type*           getValueType() const;

    virtual DataMemberInitializationStatement*     clone() const;

protected:
    Expression*     m_pThisExpression;
    DataMember*     m_pDataMember;
};

o_namespace_end(phantom, reflection)



#endif
