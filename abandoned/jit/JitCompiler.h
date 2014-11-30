

#ifndef o_reflection_jit_JitCompiler_h__
#define o_reflection_jit_JitCompiler_h__
// #pragma __PragmaPrintFile__


/* ****************** Includes ******************* */
#include <phantom/reflection/Compiler.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), JitCompiler);
/* *********************************************** */
o_namespace_begin(phantom, reflection, jit)

class JitCompiler : public Compiler
{
public:
    enum EPass
    {
        e_Pass_Dependencies,
        e_Pass_Inheritance,
        e_Pass_Declarations,
        e_Pass_Definitions,
    };
    // Default basic elements

    // Statements
    virtual variant compile(Block* a_pBlock);
    virtual variant compile(ForStatement* a_pForStatement);
    virtual variant compile(WhileStatement* a_pWhileStatement);
    virtual variant compile(IfStatement* a_pIfStatement);
    virtual variant compile(SwitchStatement* a_pSwitchStatement);
    virtual variant compile(CaseStatement* a_pCaseStatement);
    virtual variant compile(LabelStatement* a_pLabelStatement);
    virtual variant compile(DoWhileStatement* a_pDoWhileStatement);
    virtual variant compile(ExpressionStatement* a_pExpressionStatement);
    virtual variant compile(BreakStatement* a_pBreakStatement);
    virtual variant compile(ContinueStatement* a_pContinueStatement);

    // Expressions
    virtual variant compile(CallExpression* a_pCallExpression);
    virtual variant compile(CastExpression* a_pCastExpression);
    virtual variant compile(DereferenceExpression* a_pDereferenceExpression);
    virtual variant compile(AddressExpression* a_pAddressExpression);
    virtual variant compile(ConstantExpression* a_pConstantExpression);
    virtual variant compile(DataExpression* a_pDataExpression) { return variant(); }
    virtual variant compile(InstanceDataMemberAccess* a_pInstanceDataMemberAccess);
    virtual variant compile(PropertyAccess* a_pPropertyAccess);
    virtual variant compile(StaticVariableAccess* a_pStaticVariableAccess);
    virtual variant compile(ArrayElementAccess* a_pArrayElementAccess);
    virtual variant compile(StringLiteralExpression* a_pStringLiteralExpression) { return variant(); }

    // Elements 
    virtual variant compile(Structure* a_pStructure) { return variant(); }
    virtual variant compile(ClassType* a_pType) { return variant(); }
    virtual variant compile(Class* a_pClass) { return variant(); }
    virtual variant compile(InstanceMemberFunction* a_pInstanceMemberFunction);
    virtual variant compile(Signal* a_pSignal);
    virtual variant compile(state::StateMachine* a_pStateMachine) { return variant(); }
    virtual variant compile(state::State* a_pState) { return variant(); }
    virtual variant compile(state::Track* a_pTrack) { return variant(); }

protected:
    void flush( PropertyAccess* a_pPropertyAccess, jit_value a_PointerValue );
};

o_namespace_end(phantom, reflection, jit)




#endif