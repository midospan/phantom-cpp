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
#include <phantom/reflection/BranchStatement.h>
#include <phantom/reflection/BranchStatement.hxx>
#include <phantom/reflection/LabelStatement.h>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/Compiler.h>
#include <phantom/reflection/Interpreter.h>
/* *********************************************** */
o_registerN((phantom, reflection), BranchStatement);

o_namespace_begin(phantom, reflection) 

BranchStatement::BranchStatement() 
    : Statement("")
    , m_pLabelStatement(nullptr)
    , m_uiLabelStatementIndex(0xffffffff)
{
}

void BranchStatement::eval() const
{
    phantom::interpreter()->setNextStatement(m_pLabelStatement);
}

variant BranchStatement::compile( Compiler* a_pCompiler )
{
    return a_pCompiler->compile(this);
}

void BranchStatement::setLabelStatement( LabelStatement* a_pLabelStatement )
{
    addReferencedElement(a_pLabelStatement);
    m_pLabelStatement = a_pLabelStatement;
    if(getSubroutine())
    {
        m_uiLabelStatementIndex = m_pLabelStatement->getIndex();
    }
}

void BranchStatement::restore()
{
    if(m_pLabelStatement == nullptr AND m_uiLabelStatementIndex != 0xffffffff)
    {
        m_pLabelStatement = getSubroutine()->getLabelStatement(m_uiLabelStatementIndex);
        if(m_pLabelStatement)
        {
            addReferencedElement(m_pLabelStatement);
        }
    }
}

void BranchStatement::elementRemoved( LanguageElement* a_pElement )
{
    Statement::elementRemoved(a_pElement);
    if(a_pElement == m_pLabelStatement) // Expression destroyed => invalid
    {
        m_pLabelStatement = nullptr;
        m_uiLabelStatementIndex = 0xffffffff;
    }
}

void BranchStatement::ancestorChanged( LanguageElement* a_pOwner )
{
    if(getSubroutine() AND m_uiLabelStatementIndex == 0xffffffff AND m_pLabelStatement)
    {
        m_uiLabelStatementIndex = m_pLabelStatement->getIndex();
    }
}

o_namespace_end(phantom, reflection)
