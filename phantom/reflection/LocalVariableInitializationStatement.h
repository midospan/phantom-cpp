/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_LocalVariableInitializationStatement_h__
#define o_phantom_reflection_LocalVariableInitializationStatement_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/LValueInitializationStatement.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), LocalVariableInitializationStatement);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export LocalVariableInitializationStatement : public LValueInitializationStatement
{
    o_language_element;

public:
    LocalVariableInitializationStatement( LocalVariable* a_pLocalVariable, Expression* a_pRightExpression = nullptr );
    ~LocalVariableInitializationStatement();

    virtual LocalVariableInitializationStatement* asLocalVariableInitializationStatement() const { return (LocalVariableInitializationStatement*)this; }

    virtual void    internalEval() const;

    virtual void    flush() const {}

    LocalVariable*  getLocalVariable() const { return m_pLocalVariable; }
    Type*           getValueType() const;

    virtual LocalVariableInitializationStatement*     clone() const;

protected:
    LocalVariable*     m_pLocalVariable;
};

o_namespace_end(phantom, reflection)



#endif
