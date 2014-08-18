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

#ifndef o_phantom_reflection_SwitchStatement_h__
#define o_phantom_reflection_SwitchStatement_h__



/* ****************** Includes ******************* */
#include "phantom/reflection/Block.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), SwitchStatement);
o_fwd(class, phantom, reflection, CaseStatement);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export SwitchStatement : public Block
{
public:
    SwitchStatement();

    virtual variant         compile(Compiler* a_pCompiler);

    virtual void            eval() const 
    { 
        o_assert(false);
    }

    virtual void            flush() const {}

    Expression*             getTestValue() const { return m_pTestValue; }

    void                    setTestValue( Expression* a_pExpression );

    void                    setBlock( Block* a_pBlock );

    Block*                  getBlock() const { return m_pBlock; }

    void                    addCaseStatement(CaseStatement* a_pCaseStatement);

    vector<CaseStatement*>::const_iterator beginCaseStatements() const { return m_CaseStatements.begin(); }
    vector<CaseStatement*>::const_iterator endCaseStatements() const { return m_CaseStatements.end(); }

protected:
    Expression*             m_pTestValue;
    vector<CaseStatement*>  m_CaseStatements;
    Block*                  m_pBlock;
};

o_namespace_end(phantom, reflection)



#endif
