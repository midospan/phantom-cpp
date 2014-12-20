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
#include <phantom/reflection/Subroutine.h>
#include <phantom/reflection/Subroutine.hxx>
#include <phantom/reflection/Block.h>
#include <phantom/reflection/LabelStatement.h>
#include <phantom/reflection/Interpreter.h>
/* *********************************************** */
o_registerN((phantom, reflection), Subroutine);

o_namespace_begin(phantom, reflection) 

Subroutine::Subroutine()
    : LanguageElement()
    , m_pSignature(nullptr)
    , m_pInstructions(nullptr)
    , m_pBlock(nullptr)
    , m_pClosure(nullptr)
    , m_uiFrameSize(0)
    , m_eABI(e_stdcall)
    , m_pLabelStatements(nullptr)
{

}

Subroutine::Subroutine( EABI a_eABI ) 
    : LanguageElement()
    , m_pSignature(nullptr)
    , m_pInstructions(nullptr)
    , m_pBlock(nullptr)
    , m_pClosure(nullptr)
    , m_uiFrameSize(0)
    , m_eABI(a_eABI)
    , m_pLabelStatements(nullptr)
{

}

Subroutine::Subroutine( const string& a_strName, Signature* a_pSignature, EABI a_eABI, modifiers_t a_Modifiers /*= 0*/ ) 
    : LanguageElement(a_strName, a_Modifiers)
    , m_pSignature(a_pSignature)
    , m_pInstructions(nullptr)
    , m_pBlock(nullptr)
    , m_pClosure(nullptr)
    , m_uiFrameSize(0)
    , m_eABI(a_eABI)
    , m_pLabelStatements(nullptr)
{
    if(m_pSignature)
    {
        if(m_pSignature->isShared())
        {
            addReferencedElement(a_pSignature);
        }
        else 
        {
            addElement(m_pSignature);
        }
    }
    else 
    {
        setInvalid();
    }
}

Subroutine::~Subroutine()
{
    if(m_pLabelStatements)
    {
        delete m_pLabelStatements;
    }
}

o_terminate_cpp(Subroutine)
{
    if(m_pInstructions)
    {
        for(auto it = m_pInstructions->begin(); it != m_pInstructions->end(); ++it)
        {
            delete *it;
        }
        delete m_pInstructions;
        m_pInstructions = nullptr;
    }
}

phantom::string Subroutine::getQualifiedName() const
{
    return m_pOwner ? (m_pOwner->getQualifiedName() + "::" + getName()) : getName() ;
}

phantom::string Subroutine::getQualifiedDecoratedName() const
{
    return m_pOwner ? (m_pOwner->getQualifiedDecoratedName() + "::" + getName() + (m_pSignature ? m_pSignature->getQualifiedDecoratedName() : "")) : getDecoratedName();
}

phantom::string Subroutine::getDecoratedName() const
{
    return getName() + (m_pSignature ? m_pSignature->getQualifiedDecoratedName() : nullptr);
}

void Subroutine::addInstruction( Instruction* a_pInstruction )
{
    if(m_pInstructions == nullptr)
    {
        m_pInstructions = new vector<Instruction*>;
    }
    m_pInstructions->push_back(a_pInstruction);
    a_pInstruction->m_pSubroutine = this;
    struct InstructionSorter
    {
        bool operator()(Instruction* a_pI0, Instruction* a_pI1) const 
        {
            return *a_pI0 < *a_pI1;
        }
    };
    std::sort(m_pInstructions->begin(), m_pInstructions->end(), InstructionSorter());
}

Instruction* Subroutine::findInstructionAtCodePosition( const CodePosition& position ) const
{
    if(m_pInstructions == nullptr) return nullptr;
    if(NOT(containsCodePosition(position))) return nullptr;
    for(auto it = m_pInstructions->begin(); it != m_pInstructions->end(); ++it)
    {
        Instruction* pInstruction = *it;
        if(pInstruction->containsCodePosition(position)) 
            return pInstruction;
    }
    return nullptr;
}

Instruction* Subroutine::findInstructionAtMemoryAddress( byte* a_pAddress ) const
{
    if(m_pInstructions == nullptr) return nullptr;
    for(auto it = m_pInstructions->begin(); it != m_pInstructions->end(); ++it)
    {
        Instruction* pInstruction = *it;
        if(pInstruction->getMemoryStart() == a_pAddress)
            return pInstruction;
    }
    return nullptr;
}

Instruction* Subroutine::findInstructionStartingAtMemoryAddress( byte* a_pAddress ) const
{
    if(m_pInstructions == nullptr) return nullptr;
    for(auto it = m_pInstructions->begin(); it != m_pInstructions->end(); ++it)
    {
        Instruction* pInstruction = *it;
        if(pInstruction->getMemoryStart() == a_pAddress)
            return pInstruction;
    }
    return nullptr;
}

Block* Subroutine::findBlockAtCodePosition( const CodePosition& a_Position ) const
{
    if(m_pBlock AND m_pBlock->containsCodePosition(a_Position))
        return m_pBlock->findBlockAtCodePosition(a_Position);
    return nullptr;
}

void Subroutine::setBlock( Block* a_pBlock )
{
    if(m_pBlock)
    {
        removeElement(m_pBlock);
    }
    m_pBlock = a_pBlock;
    if(m_pBlock)
    {
        addElement(m_pBlock);
    }
}

bool Subroutine::containsMemoryAddress( const byte* a_pAddress )
{
    return m_MemoryLocation.containsMemoryAddress(a_pAddress);
}

void Subroutine::referencedElementRemoved( LanguageElement* a_pElement )
{
    LanguageElement::referencedElementRemoved(a_pElement);
    if(m_pBlock == a_pElement)
        m_pBlock = nullptr;
    else if(m_pSignature == a_pElement)
        m_pSignature = nullptr;
}

bool Subroutine::matches( const string& a_strName, const vector<Type*>& a_FunctionSignature, vector<size_t>* a_pPartialMatches, modifiers_t a_Modifiers /*= 0*/ ) const
{
    return m_strName == a_strName
        AND m_pSignature != nullptr 
        AND m_pSignature->matches(a_FunctionSignature, a_pPartialMatches)
        AND testModifiers(a_Modifiers);
}

void Subroutine::call( void** a_pArgs ) const
{
    if(isInvalid())
    {
        o_exception(exception::reflection_runtime_exception, "Subroutine is invalid");
    }
    call(a_pArgs, m_pSignature->getParameterCount()+1, nullptr);
}

void Subroutine::call( void** a_pArgs, void* a_pReturnAddress ) const
{
    if(isInvalid())
    {
        o_exception(exception::reflection_runtime_exception, "Subroutine is invalid");
    }
    call(a_pArgs, m_pSignature->getParameterCount()+1, a_pReturnAddress);
}

void Subroutine::call( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const
{
    if(isInvalid())
    {
        o_exception(exception::reflection_runtime_exception, "Subroutine is invalid");
    }
    size_t argCount = m_pSignature->getParameterCount()+1;
    void** newArgs = (void**)o_malloc(argCount*sizeof(void*));
    newArgs[0] = &a_pCallerAddress;
    memcpy(&newArgs[1], a_pArgs, (argCount-1)*sizeof(void*));
    call(newArgs, argCount, a_pReturnAddress);
    o_free(newArgs);
}

void Subroutine::call( void* a_pCallerAddress, void** a_pArgs ) const
{
    if(isInvalid())
    {
        o_exception(exception::reflection_runtime_exception, "Subroutine is invalid");
    }
    size_t argCount = m_pSignature->getParameterCount()+1;
    void** newArgs = (void**)o_malloc(argCount*sizeof(void*));
    newArgs[0] = &a_pCallerAddress;
    memcpy(&newArgs[1], a_pArgs, (argCount-1)*sizeof(void*));
    call(newArgs, argCount, nullptr);
    o_free(newArgs);
}

void Subroutine::call( void** a_pArgs, size_t a_uiCount, void* a_pReturnAddress ) const
{
    o_assert(!testModifiers(o_native));
    if(isInvalid())
    {
        o_exception(exception::reflection_runtime_exception, "Subroutine is invalid");
    }
    if(!m_ClosureCallDelegate.empty() && m_pClosure)
    {
        m_ClosureCallDelegate(m_pClosure, a_pArgs, a_uiCount, a_pReturnAddress);
    }
    else 
    {
        phantom::interpreter()->call(const_cast<Subroutine*>(this), a_pArgs, a_uiCount, a_pReturnAddress);
    }
}

void Subroutine::registerLabelStatement( LabelStatement* a_pLabelStatement )
{
    if(m_pLabelStatements == nullptr)
    {
        m_pLabelStatements = new vector<LabelStatement*>;
    }
    a_pLabelStatement->m_uiIndex = m_pLabelStatements->size();
    m_pLabelStatements->push_back(a_pLabelStatement);
}

void Subroutine::unregisterLabelStatement( LabelStatement* a_pLabelStatement )
{
    o_assert(m_pLabelStatements);
    a_pLabelStatement->m_uiIndex = 0xffffffff;
    m_pLabelStatements->erase(std::find(m_pLabelStatements->begin(), m_pLabelStatements->end(), a_pLabelStatement));
    if(m_pLabelStatements->empty())
    {
        delete m_pLabelStatements;
        m_pLabelStatements = nullptr;
    }
}

void Subroutine::finalize()
{
    if(m_pSignature)
    {
        m_pSignature->finalize();
    }
}

Block* Subroutine::createBlock( LocalVariable* a_pThis )
{
    if(isNative())
    {
        o_exception(exception::reflection_runtime_exception, "Cannot create block on native subroutine");
    }
    if(testModifiers(o_pure_virtual))
    {
        o_exception(exception::reflection_runtime_exception, "Cannot create block on pure virtual subroutine");
    }
    return o_new(Block)(this, a_pThis);
}

void MemoryLocation::setStart( byte* a_pAddress )
{
    o_assert(a_pAddress);
    o_assert(m_pEnd == 0 || a_pAddress < m_pEnd); 
    m_pStart = a_pAddress;
}

void MemoryLocation::setEnd( byte* a_pAddress )
{
    o_assert(a_pAddress);
    o_assert(m_pStart == 0 || a_pAddress > m_pStart); 
    m_pEnd = a_pAddress;
}

bool MemoryLocation::containsMemoryAddress( const byte* a_pAddress ) const
{
    return a_pAddress >= m_pStart && a_pAddress < m_pEnd;
}


o_namespace_end(phantom, reflection)