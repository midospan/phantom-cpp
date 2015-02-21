/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_CallExpression_h__
#define o_phantom_reflection_CallExpression_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), CallExpression);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export CallExpression : public Expression
{
    o_language_element;

public:
    CallExpression(Subroutine* a_pFunction, const vector<Expression*>& a_Arguments, Type* a_pConstructedType = nullptr);
    CallExpression(Subroutine* a_pFunction, Expression* a_pArgument, Type* a_pConstructedType = nullptr);
    CallExpression(Subroutine* a_pFunction, Type* a_pConstructedType = nullptr);

    o_initialize();
    o_terminate(); 

    virtual CallExpression* asCallExpression() const { return (CallExpression*)this; }

    size_t      getArgumentCount() const { return m_Arguments.size(); }

    Expression* getArgument(size_t i) const { return m_Arguments[i]; }

    virtual void  internalEval(void* a_pDest) const ;

    virtual void* evalStorage() const ;

    virtual bool hasValueStorage() const { return m_pReturnStorage != nullptr; }

    virtual void flush() const;

    virtual void internalEval() const ;

    Subroutine* getSubroutine() const { return m_pSubroutine; }

    vector<Expression*>::const_iterator beginArguments() const { return m_Arguments.begin(); }
    vector<Expression*>::const_iterator endArguments() const { return m_Arguments.end(); }

    vector<Expression*>::const_reverse_iterator rbeginArguments() const { return m_Arguments.rbegin(); }
    vector<Expression*>::const_reverse_iterator rendArguments() const { return m_Arguments.rend(); }

    const vector<Expression*>& getArguments() const { return m_Arguments; }

    virtual LanguageElement*hatch();

    virtual Expression*     clone() const;

    virtual LanguageElement*getHatchedElement() const { return m_pSubroutine; }

    virtual bool            isPersistent() const;

    void                    setImplicit() { m_bImplicitCall = true; }

protected:
    Statement* evaluateExpressionLifeTime( Expression* a_pExpression ) const
    {
        /// any argument (or implicit object) has a life time limited to the statement enclosing the call
        return getEnclosingStatement();
    }

protected:
    CallExpression(const vector<Expression*>& a_Arguments, Type* a_pConstructedType = nullptr);
    CallExpression(Expression* a_pArgument, Type* a_pConstructedType = nullptr);
    virtual void elementRemoved( LanguageElement* a_pElement );
    virtual void referencedElementRemoved( LanguageElement* a_pElement );
    virtual Type* returnStorageType() const ;

protected:
    Subroutine*         m_pSubroutine;
    vector<Expression*> m_Arguments;
    void*               m_pReturnStorage;
    bool                m_bSkipFirstArgument;
    bool                m_bImplicitCall;
    bool                m_bCalledOnce;
};

o_namespace_end(phantom, reflection)



#endif
