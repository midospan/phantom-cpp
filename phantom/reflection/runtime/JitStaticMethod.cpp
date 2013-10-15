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
#include "JitStaticMethod.h"
#include "JitLocalVariable.h"
#include "JitClass.h"
/* *********************************************** */
o_registerN((phantom, reflection, runtime), JitStaticMethod);

o_namespace_begin(phantom, reflection, runtime)

JitStaticMethod::JitStaticMethod( const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers ) : StaticMethod(a_strName, a_pSignature, a_Modifiers) 
    , m_jit_function(0)
{
    m_jit_context = jit_context_create();
    o_assert(m_jit_context);
    m_jit_function = jit_function_create(m_jit_context, jit_type_from_phantom_signature(jit_abi_cdecl, getSignature()));
    o_assert(m_jit_function);
}

JitStaticMethod::~JitStaticMethod( void )
{
    jit_context_destroy(m_jit_context);
}

jit_context_t JitStaticMethod::getContext() const
{
    return m_jit_context;
}

void JitStaticMethod::reset()
{
    jit_context_destroy(m_jit_context);
    m_jit_context = jit_context_create();
    m_jit_function = jit_function_create(m_jit_context, jit_type_from_phantom_signature(jit_abi_cdecl, getSignature()));
}

void JitStaticMethod::instructionCompilationCallback( jit_insn_t insn, byte* start, byte* end )
{   
    if(start == end) return; // empty instruction => skip
    JitStaticMethod* pCompiledStaticMethod = sm_Compiled[jit_insn_get_function(insn)];
    o_assert(pCompiledStaticMethod);
    if(pCompiledStaticMethod->getMemoryStart() == 0) 
        pCompiledStaticMethod->setMemoryStart(start);
    pCompiledStaticMethod->setMemoryEnd(end);
    unsigned short start_line;
    unsigned short start_column;
    unsigned short end_line;
    unsigned short end_column;
    jit_insn_get_code_location(insn, &start_line, &start_column, &end_line, &end_column);
    SourceFile* pSourceFile = pCompiledStaticMethod->getCodeLocation().getSourceFile();
    CodeLocation codeLocation(CodePosition(pSourceFile, start_line, start_column)
        , CodePosition(pSourceFile, end_line, end_column));
    pCompiledStaticMethod->addInstruction(new Instruction(jit_insn_get_opcode(insn), codeLocation, MemoryLocation(start, end)));
}

void JitStaticMethod::startCompilation()
{
    o_assert(!jit_function_is_compiled(m_jit_function));
    o_assert(sm_Compiled[m_jit_function] == nullptr);
    sm_Compiled[m_jit_function] = this;
    jit_function_set_insn_compilation_callback(m_jit_function, &JitStaticMethod::instructionCompilationCallback);
    jit_function_set_compilation_success_callback(m_jit_function, &JitStaticMethod::compilationSuccessCallback);
    jit_context_build_start(m_jit_context);
}

void JitStaticMethod::endCompilation()
{
    jit_context_build_end(m_jit_context);
    jit_function_set_insn_compilation_callback(m_jit_function, nullptr);
    sm_Compiled.erase(m_jit_function);
}

void JitStaticMethod::compilationSuccessCallback(jit_function_t func)
{
    JitStaticMethod* pCompiledStaticMethod = sm_Compiled[func];
    o_assert(pCompiledStaticMethod);
    vector<LocalVariable*> localVariables;
    pCompiledStaticMethod->getBlock()->getLocalVariablesCascade(localVariables);
    for(auto it = localVariables.begin(); it != localVariables.end(); ++it)
    {
        JitLocalVariable* pLocalVariable = static_cast<JitLocalVariable*>(*it);
        pLocalVariable->setupFrame();
    }
}

void JitStaticMethod::abortCompilation()
{
    jit_function_set_insn_compilation_callback(m_jit_function, nullptr);
    jit_context_build_end(m_jit_context);
    jit_function_abandon(m_jit_function);
    sm_Compiled.erase(m_jit_function);
    reset();
}
map<jit_function_t, JitStaticMethod*> JitStaticMethod::sm_Compiled;

o_namespace_end(phantom, reflection, runtime)