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
/* ** The Class Header must be the last #include * */
#include "Subroutine.h"
/* *********************************************** */


o_cpp_begin 

ReflectionCPP__________________________________________________________________________________
__________________________________________________________________________________ReflectionCPP

Subroutine::Subroutine( const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers /*= 0*/ ) 
: LanguageElement(a_strName, a_Modifiers)
, m_pSignature(a_pSignature)
, m_pInstructions(nullptr)
, m_pBlock(nullptr)
{

}

Subroutine::~Subroutine()
{
    if(NOT(m_pSignature->isShared()))
    {
        o_dynamic_delete_clean(m_pSignature);
    }
    if(m_pBlock)
    {
        removeElement(m_pBlock);
        o_dynamic_delete m_pBlock;
    }
    if(m_pInstructions)
    {
        for(auto it = m_pInstructions->begin(); it != m_pInstructions->end(); ++it)
        {
            delete *it;
        }
        delete m_pInstructions;
    }
}

phantom::string Subroutine::getQualifiedName() const
{
    return getOwner()->getQualifiedName() + "::" + getName() ;
}

phantom::string Subroutine::getQualifiedDecoratedName() const
{
    return getOwner()->getQualifiedDecoratedName() + "::" + getName() + m_pSignature->getQualifiedDecoratedName();
}

phantom::string Subroutine::getDecoratedName() const
{
    return getName() + m_pSignature->getDecoratedName();
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

LanguageElement* Subroutine::getElement( const char* a_strQualifiedName , template_specialization const* a_pTS, function_signature const* a_pFS, bitfield a_bfModifiers /* = bitfield */ ) const
{
    if(m_pBlock) 
        return m_pBlock->getElement(a_strQualifiedName, a_pTS, a_pFS, a_bfModifiers);
    return nullptr;
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
        o_dynamic_delete m_pBlock;
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


o_cpp_end