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
#include <phantom/reflection/ReturnStatement.h>
#include <phantom/reflection/ReturnStatement.hxx>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/Compiler.h>
#include <phantom/reflection/Interpreter.h>
#include <phantom/reflection/Block.h>
/* *********************************************** */
o_registerN((phantom, reflection), ReturnStatement);

o_namespace_begin(phantom, reflection) 

ReturnStatement::ReturnStatement() 
    : Statement("")
    , m_pReturnExpression(nullptr)
    , m_pConvertedReturnExpression(nullptr)
    , m_pExpressionString(nullptr)
{
}

ReturnStatement::ReturnStatement(Expression* a_pExpression) 
    : Statement("")
    , m_pReturnExpression(nullptr)
    , m_pConvertedReturnExpression(nullptr)
    , m_pExpressionString(nullptr)
{
    setReturnExpression(a_pExpression);
}

void ReturnStatement::internalEval() const 
{
    if(m_pConvertedReturnExpression)
    {
        m_pConvertedReturnExpression->internalEval(phantom::interpreter()->getReturnAddress());
    }
    for(auto it = m_RAIIDestructionStatements.begin(); it != m_RAIIDestructionStatements.end(); ++it)
    {
        (*it)->eval();
    }
    phantom::interpreter()->setNextStatement(nullptr);
}

void ReturnStatement::checkValidity()
{
    o_assert(getSubroutine());
    if(getSubroutine()->getReturnType() == typeOf<void>() && m_pReturnExpression)
    {
        setInvalid();
    }
    else if(getSubroutine()->getReturnType() != typeOf<void>() && m_pReturnExpression == nullptr)
    {
        setInvalid();
    }
    else if(NOT(m_pReturnExpression->getValueType()->isImplicitlyConvertibleTo(getSubroutine()->getReturnType())))
    {
        setInvalid();
    }
}

void ReturnStatement::setReturnExpression( Expression* a_pReturnExpression )
{
    o_assert(m_pConvertedReturnExpression == nullptr);
    m_pReturnExpression = (a_pReturnExpression AND a_pReturnExpression->getOwner()) ? a_pReturnExpression->clone() : a_pReturnExpression ;
    
    if(m_pReturnExpression)
    {
        if(getSubroutine())
        {
            checkValidity();
            m_pConvertedReturnExpression = m_pReturnExpression->implicitCast(getSubroutine()->getReturnType());
            addElement(m_pConvertedReturnExpression);
        }
    }
}

void ReturnStatement::setExpressionString( string a_Expression )
{
    if(a_Expression.size())
    {
        m_pExpressionString = new string(a_Expression);
    }
}

string ReturnStatement::getExpressionString() const
{
    return m_pReturnExpression ? m_pReturnExpression->translate() : string();
}

void ReturnStatement::restore()
{
    if(m_pReturnExpression == nullptr AND m_pExpressionString)
    {
        Expression* pExpression = phantom::expressionByName(*m_pExpressionString, this);
        if(pExpression)
        {
            setReturnExpression(pExpression);
        }
        delete m_pExpressionString;
        m_pExpressionString = nullptr;
    }
}

void ReturnStatement::ancestorChanged( LanguageElement* a_pOwner )
{
    o_assert(m_pOwner == a_pOwner 
        AND m_pOwner->asBlock() 
        AND getSubroutine() 
        AND m_pConvertedReturnExpression == nullptr);
    if(m_pReturnExpression)
    {
        checkValidity();
        m_pConvertedReturnExpression = m_pReturnExpression->implicitCast(getSubroutine()->getReturnType());
        addElement(m_pConvertedReturnExpression);
    }
    m_pOwner->asBlock()->getRAIIDestructionStatementsCascade(m_RAIIDestructionStatements);
}

o_namespace_end(phantom, reflection)
