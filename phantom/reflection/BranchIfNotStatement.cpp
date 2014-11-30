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
#include <phantom/reflection/BranchIfNotStatement.h>
#include <phantom/reflection/BranchIfNotStatement.hxx>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/Compiler.h>
/* *********************************************** */
o_registerN((phantom, reflection), BranchIfNotStatement);

o_namespace_begin(phantom, reflection) 

BranchIfNotStatement::BranchIfNotStatement( Expression* a_pExpression ) 
    : m_pExpression((a_pExpression AND a_pExpression->getOwner()) ? a_pExpression->clone() : a_pExpression)
    , m_pExpressionString(nullptr)
{
    m_pConvertedExpression = m_pExpression ? m_pExpression->implicitCast(typeOf<bool>()) : nullptr;
    if(m_pExpression)
    {
        if(m_pConvertedExpression == nullptr)
            setInvalid();
        else
            addElement(m_pConvertedExpression);
    }
}

void BranchIfNotStatement::eval() const
{
    bool value;
    m_pConvertedExpression->getValue(&value);
    if(NOT(value))
    {
        BranchStatement::eval();
    }
}

void BranchIfNotStatement::flush() const
{
    m_pConvertedExpression->flush();
}

variant BranchIfNotStatement::compile( Compiler* a_pCompiler )
{
    return a_pCompiler->compile(this);
}

void BranchIfNotStatement::setExpressionString( string a_Expression )
{
    if(a_Expression.size())
    {
        m_pExpressionString = new string(a_Expression);
    }
}

string BranchIfNotStatement::getExpressionString() const
{
    return m_pExpression->getName();
}

void BranchIfNotStatement::restore()
{
    BranchStatement::restore();
    if(m_pExpression == nullptr AND m_pExpressionString)
    {
        m_pExpression = phantom::expressionByName(*m_pExpressionString, this);
        m_pConvertedExpression = m_pExpression ? m_pExpression->implicitCast(typeOf<bool>()) : nullptr;
        if(m_pExpression)
        {
            if(m_pConvertedExpression == nullptr)
                setInvalid();
            else
                addElement(m_pConvertedExpression);
        }
        else 
        {
            setInvalid();
        }
        delete m_pExpressionString;
        m_pExpressionString = nullptr;
    }
}

void BranchIfNotStatement::elementRemoved( LanguageElement* a_pElement )
{
    BranchStatement::elementRemoved(a_pElement);
    if(a_pElement == m_pExpression) // Type destroyed => expression cannot exist anymore
    {
        m_pExpression = nullptr;
    }
}

o_namespace_end(phantom, reflection)
