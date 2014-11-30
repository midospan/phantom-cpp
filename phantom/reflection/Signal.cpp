/*
    This file is part of PHANTOM
         P reprocessed
         H igh-level
         A llocator
         N ested state-machines and
         T emplate
         O riented
         M eta-programming

    For the latest infos and sources, see http://code.google.com/p/phantom-cpp

    Copyright (C) 2008-2011 by Vivien MILLET

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE
*/

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Signal.h"
#include "Signal.hxx"
#include "Compiler.h"
#include "Block.h"
#include "LocalVariable.h"
#include "LocalVariableAccess.h"
#include "ConstantExpression.h"
#include "ArrayElementAccess.h"
#include "AssignmentExpression.h"
#include "BranchIfNotStatement.h"
#include "BranchIfStatement.h"
#include "ReturnStatement.h"
#include "LabelStatement.h"
#include "CallExpression.h"
/* *********************************************** */
o_registerN((phantom, reflection), Signal);

o_namespace_begin(phantom, reflection)

Class* const Signal::metaType = o_type_of(Signal);

Signal::Signal()
    : m_uiNodeDestructionGuardLevel(0)
    , m_uiConnectionCount(0)
    , m_pSlotListDataMember(nullptr)
    , m_pProperty(nullptr)
{

}

Signal::Signal( InstanceDataMember* a_pInstanceDataMember, const string& a_strName, Signature* a_pSignature, modifiers_t a_uiModifiers )
    : InstanceMemberFunction(a_strName, a_pSignature, a_uiModifiers|o_slot_member_function, (int)0)
    , m_uiNodeDestructionGuardLevel(0)
    , m_uiConnectionCount(0)
    , m_pSlotListDataMember(a_pInstanceDataMember)
    , m_pProperty(nullptr)
{
    if(testModifiers(o_virtual))
    {
        o_exception(exception::reflection_runtime_exception, "Signal cannot be virtual");
    }
    if(testModifiers(o_const))
    {
        o_exception(exception::reflection_runtime_exception, "Signal cannot be const");
    }
}

Signal::Signal( const string& a_strName, Signature* a_pSignature, modifiers_t a_Modifiers )
    : InstanceMemberFunction(a_strName, a_pSignature, a_Modifiers|o_slot_member_function)
    , m_uiNodeDestructionGuardLevel(0)
    , m_uiConnectionCount(0)
    , m_pProperty(nullptr)
    , m_pSlotListDataMember(nullptr)
{
    if(testModifiers(o_virtual))
    {
        o_exception(exception::reflection_runtime_exception, "Signal cannot be virtual");
    }
    if(testModifiers(o_const))
    {
        o_exception(exception::reflection_runtime_exception, "Signal cannot be const");
    }
    size_t paramCount = m_pSignature->getParameterCount();
    for(size_t i = 0;i<paramCount; ++i)
    {
        m_pSignature->setParameterName(i, "a_"+lexical_cast<string>(i));
    }
}

variant Signal::compile( Compiler* a_pCompiler )
{
    return a_pCompiler->compile(this);
}

connection::slot::list* Signal::getSlotList( void* a_pCaller ) const
{
    o_assert( getSlotListDataMemberOffset() != 0xffffffff);
    return reinterpret_cast<connection::slot::list*>( ((byte*)a_pCaller) + getSlotListDataMemberOffset() );
}

void Signal::finalize()
{
    InstanceMemberFunction::finalize();
    if(testModifiers(o_virtual))
    {
        o_exception(exception::reflection_runtime_exception, "Signal cannot be virtual");
    }
}

size_t Signal::getSlotListDataMemberOffset() const
{
    return m_pSlotListDataMember->getOffset();
}

void Signal::ancestorChanged( LanguageElement* a_pLanguageElement )
{
    if(a_pLanguageElement == m_pOwner)
    {
        if(m_pSlotListDataMember == nullptr )
        {
            m_pSlotListDataMember = m_pOwner->asClass()->getInstanceDataMember("PHANTOM_CODEGEN_m_slot_list_of_"+m_strName);
            if(m_pSlotListDataMember == nullptr )
            {
                m_pSlotListDataMember = o_new(InstanceDataMember)(typeOf<connection::slot::list>(), "PHANTOM_CODEGEN_m_slot_list_of_"+m_strName, o_protected_access);
            }
        }
        if(m_pSlotListDataMember->getOwner() == nullptr)
        {
            getOwnerClass()->addInstanceDataMember(m_pSlotListDataMember);
        }
        else
        {
            o_assert(m_pSlotListDataMember->getOwner() == m_pOwner);
        }
        if(NOT(testModifiers(o_native)) AND m_pBlock == nullptr)
        {
            generateCode();
        }
    }
}

void Signal::generateCode()
{
    if(m_pSignature->getReturnType() != typeOf<signal_t>())
    {
        o_exception(exception::reflection_runtime_exception, "Signal return type must be 'signal_t'");
    }
    size_t paramCount = m_pSignature->getParameterCount();
    m_pSignature->setReturnType(typeOf<signal_t>());
    LocalVariable* pThis = o_new(LocalVariable)(getOwnerClass()->pointerType()->constType(), "this");
    createBlock(pThis);
    Block* pBlock = o_new(Block)(m_pBlock);
    Expression* pThisAccess = o_new(LocalVariableAccess)(pThis);
    m_pBlock->addLocalVariable(pThis);
    vector<LocalVariable*> parameters;
    for(size_t i = 0; i<paramCount; i++)
    {
        LocalVariable* pParameter = m_pBlock->getLocalVariable("a_"+lexical_cast<string>(i));
        parameters.push_back(pParameter);
    }
    Expression* pSlotListAccess = m_pSlotListDataMember->createAccessExpression(pThisAccess->dereference());
    ///     if(PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.unblocked())
    ///     {
    InstanceMemberFunction* pFunc_unblocked = typeOf<connection::slot::list>()->getInstanceMemberFunction("unblocked()");
    Expression* pCall_unblocked = o_new(CallExpression)(pFunc_unblocked, pSlotListAccess);
    Block* pBlock_if_unblocked = o_new(Block)(pBlock, "if");
    BranchIfNotStatement* pIfBranch = o_new(BranchIfNotStatement)(pCall_unblocked);
    LabelStatement* pIfLabel = o_new(LabelStatement);
    pIfBranch->setLabelStatement(pIfLabel);
    pBlock_if_unblocked->addStatement(pIfBranch);

    ///         phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_##_signal_name_.head();
    LocalVariable* pSlot = o_new(LocalVariable)(typeOf<connection::slot>()->pointerType(), "pSlot");
    pBlock_if_unblocked->addLocalVariable(pSlot);
    Expression* pSlotAccess = o_new(LocalVariableAccess)(pSlot);
    InstanceMemberFunction* pFunc_head = typeOf<connection::slot::list>()->getInstanceMemberFunction("head()");
    Expression* pCall_head = o_new(CallExpression)(pFunc_head, pSlotListAccess);
    Expression* pSlotAssignment = o_new(AssignmentExpression)(pSlotAccess, pCall_head);
    pBlock_if_unblocked->addExpressionStatement(pSlotAssignment);

    ///         while(pSlot )
    ///         {
    Block* pBlock_while_pSlot = o_new(Block)(pBlock_if_unblocked, "while");

    LabelStatement*     pBreakLabelStatement = o_new(LabelStatement)("break");
    LabelStatement*     pCodeStartLabelStatement = o_new(LabelStatement)("while");

    BranchIfNotStatement* pWhileBranchIfNotStatement = o_new(BranchIfNotStatement)(pSlotAccess->clone());
    pWhileBranchIfNotStatement->setLabelStatement(pBreakLabelStatement);

    BranchIfStatement* pWhileBranchIfStatement = o_new(BranchIfStatement)(pSlotAccess->clone());
    pWhileBranchIfStatement->setLabelStatement(pCodeStartLabelStatement);

    // Branch to break if test fails
    pBlock_while_pSlot->addStatement(pWhileBranchIfNotStatement);

    // Code start label
    pBlock_while_pSlot->addStatement(pCodeStartLabelStatement);

    ///             phantom::connection::pair::push(this, pSlot);
    Function* pFunc_push = elementByName("phantom::connection::pair::push(void const*, phantom::connection::slot*)")->asFunction();
    vector<Expression*> args;
    args.push_back(pThisAccess);
    args.push_back(pSlotAccess);
    CallExpression* pCall_push = o_new(CallExpression)(pFunc_push, args);
    pBlock_while_pSlot->addExpressionStatement(pCall_push);
    Expression* pCall_slot_subroutine = o_new(CallExpression)(typeOf<connection::slot>()->getInstanceMemberFunction("subroutine()"), pSlotAccess->dereference());
    Expression* pCall_slot_receiver = o_new(CallExpression)(typeOf<connection::slot>()->getInstanceMemberFunction("receiver()"), pSlotAccess->dereference());
    Expression* pCall_slot_next = o_new(CallExpression)(typeOf<connection::slot>()->getInstanceMemberFunction("next()"), pSlotAccess->clone()->dereference());
    if(paramCount)
    {
    ///             void* args[?] = { (void*)(&a_0), (void*)(&a_1), ... };
        ArrayType* pArrayType = typeOf<void*>()->arrayType(paramCount);
        LocalVariable* pArgs = o_new(LocalVariable)(pArrayType, "args");
        pBlock_while_pSlot->addLocalVariable(pArgs);
        LocalVariableAccess* pArgsAccess = o_new(LocalVariableAccess)(pArgs);
        for(size_t i = 0; i<paramCount; ++i)
        {
            ArrayElementAccess* pElementAccess = o_new(ArrayElementAccess)(pArrayType, pArgsAccess, o_new(ConstantExpression)(constant<size_t>(i)));
            Expression* pParameterAccess = o_new(LocalVariableAccess)(parameters[i]);
            Expression* pElementAssignment = o_new(AssignmentExpression)(pElementAccess, pParameterAccess->address()->cast(typeOf<void*>()));
            pBlock_while_pSlot->addExpressionStatement(pElementAssignment);
        }
    ///             pSlot->subroutine()->call( pSlot->receiver(), args );

        vector<Expression*> args;
        args.push_back(pCall_slot_subroutine->dereference());
        args.push_back(pCall_slot_receiver);
        args.push_back(pArgsAccess->clone());
        Expression* pCall_slot_subroutine_call = o_new(CallExpression)(typeOf<reflection::Subroutine>()->getInstanceMemberFunction("call(void*, void**)"), args);
        pBlock_while_pSlot->addExpressionStatement(pCall_slot_subroutine_call);
    }
    else
    {
    ///             pSlot->subroutine()->call(pSlot->receiver(), o_no_arg );
        vector<Expression*> args;
        args.push_back(pCall_slot_subroutine->dereference());
        args.push_back(pCall_slot_receiver);
        args.push_back(o_new(ConstantExpression)(constant<void*>(0)));
        Expression* pCall_slot_subroutine_call = o_new(CallExpression)(typeOf<reflection::Subroutine>()->getInstanceMemberFunction("call(void*, void**)"), args);
        pBlock_while_pSlot->addExpressionStatement(pCall_slot_subroutine_call);
    }
    ///             pSlot = pSlot->next();
    Expression* pSlotAssignNextExpression = o_new(AssignmentExpression)(pSlotAccess->clone(), pCall_slot_next);
    pBlock_while_pSlot->addExpressionStatement(pSlotAssignNextExpression);

    ///             phantom::connection::pair::pop();
    Function* pFunc_pop = elementByName("phantom::connection::pair::pop()")->asFunction();
    CallExpression* pCall_pop = o_new(CallExpression)(pFunc_pop, vector<Expression*>());
    pBlock_while_pSlot->addExpressionStatement(pCall_pop);

    ///         }
    // branch to code if test succeed
    pBlock_while_pSlot->addStatement(pWhileBranchIfStatement);

    // 'break' goes here (no break in this code, but the label is required for the first branch-if-not test
    pBlock_while_pSlot->addStatement(pBreakLabelStatement);

    ///     }

    pBlock_if_unblocked->addStatement(pIfLabel);

    /// return phantom::signal_t();
    // we can skip it in runtime code, it is required only for compile validation in C++
}


o_namespace_end(phantom, reflection)


