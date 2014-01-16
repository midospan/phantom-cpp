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

#ifndef o_phantom_reflection_Subroutine_h__
#define o_phantom_reflection_Subroutine_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/LanguageElement.h>
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "Subroutine.classdef.h"
/* **************** Declarations ***************** */
o_declare(class, phantom, reflection, Signature)
o_declare(class, phantom, reflection, Block)
/* *********************************************** */

o_h_begin

struct MemoryLocation
{
    MemoryLocation() : m_pStart(0), m_pEnd(0) {}
    MemoryLocation(byte* start, byte* end) 
        : m_pStart(start), m_pEnd(end) 
    {
        o_assert(m_pStart && m_pEnd && (m_pStart < m_pEnd));
    }
    bool operator==(const MemoryLocation& other) const 
    {
        return m_pStart == other.m_pStart AND m_pEnd == other.m_pEnd;
    }

    bool operator<(const MemoryLocation& other) const 
    {
        return m_pStart < other.m_pStart;
    }

    bool isValid() const { return m_pStart && m_pEnd; }

    byte* getStart() const { return m_pStart; }
    byte* getEnd() const { return m_pEnd; }

    void setStart(byte* a_pAddress);
    void setEnd(byte* a_pAddress);

    bool containsMemoryAddress(const byte* a_pAddress) const;

    inline size_t getRange() const { return m_pEnd-m_pStart; }

protected:
    byte* m_pStart;
    byte* m_pEnd;
};

class Instruction
{
    friend class Subroutine;

public:
    Instruction(int a_iOpcode
        , const CodeLocation& a_CodeLocation
        , const MemoryLocation& a_MemoryLocation) 
        : m_pSubroutine(nullptr)
        , m_iOpcode(a_iOpcode)
        , m_CodeLocation(a_CodeLocation)
        , m_MemoryLocation(a_MemoryLocation)
        , m_pUserData(nullptr)
    {

    }

    bool operator<(const Instruction& other) const 
    {
        return m_MemoryLocation < other.m_MemoryLocation;
    }

    Subroutine* getSubroutine() const { return m_pSubroutine; }
    void setUserData(void* a_pUserData) const { m_pUserData = a_pUserData; }
    void* getUserData() const { return m_pUserData; }
    int getOpCode() const { return m_iOpcode; }
    const CodeLocation&     getCodeLocation() const { return m_CodeLocation; }
    const MemoryLocation&   getMemoryLocation() const { return m_MemoryLocation; }
    SourceFile* getSourceFile() const { return m_CodeLocation.getSourceFile(); }

    byte* getMemoryStart() const { return m_MemoryLocation.getStart(); }
    byte* getMemoryEnd() const { return m_MemoryLocation.getEnd(); }

    inline bool containsCodePosition(const CodePosition& position)
    {
        return m_CodeLocation.containsCodePosition(position);
    }

    inline bool containsMemoryAddress(const byte* a_pAddress)
    {
        return m_MemoryLocation.containsMemoryAddress(a_pAddress);
    }

protected:
    Subroutine*     m_pSubroutine;
    int             m_iOpcode;
    CodeLocation    m_CodeLocation;
    MemoryLocation  m_MemoryLocation;
    mutable void*   m_pUserData;
};

class o_export Subroutine : public LanguageElement
{
public:

    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

public:
    Subroutine(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers = 0);
    o_destructor ~Subroutine();

    virtual void terminate();

    virtual Subroutine* asSubroutine() const { return const_cast<Subroutine*>(this); }

    inline Signature*   getSignature() const { return m_pSignature; }
    void                setSignature(Signature* a_pSignature) { m_pSignature = a_pSignature; }

    virtual string      getDecoratedName() const;
    virtual string      getQualifiedName() const;
    virtual string      getQualifiedDecoratedName() const;

    Type*               getParameterType(uint i) const { return m_pSignature->getParameterType(i); }
    uint                getParameterCount() const { return m_pSignature->getParameterCount(); }

    Type*               getReturnType() const    {        return m_pSignature->getReturnType();    }
    
    boolean             matches( const string& a_strName, function_signature const* a_FunctionSignature, bitfield a_Modifiers /*= 0*/ ) const
    {
        return m_strName == a_strName
          AND m_pSignature->matches(a_FunctionSignature)
          AND testModifiers(a_Modifiers);
    }

    virtual void  call( void** a_pArgs ) const = 0;
    virtual void  call( void** a_pArgs, void* a_pReturnAddress ) const = 0;
    virtual void  call( void* a_pCallerAddress, void** a_pArgs ) const = 0;
    virtual void  call( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const = 0;

    void setMemoryLocation(const MemoryLocation& a_MemoryLocation ) { m_MemoryLocation = a_MemoryLocation; }
    const MemoryLocation& getMemoryLocation() const { return m_MemoryLocation; }
    byte* getMemoryStart() const { return m_MemoryLocation.getStart(); }
    byte* getMemoryEnd() const { return m_MemoryLocation.getEnd(); }
    void setMemoryStart(byte* b) 
    {
        m_MemoryLocation.setStart(b);
    }
    void setMemoryEnd(byte* b) 
    {
        m_MemoryLocation.setEnd(b);
    }

    void addInstruction(Instruction* a_pInstruction);

    Instruction* getInstruction(size_t i) const 
    { 
        o_assert(m_pInstructions && m_pInstructions->size() > i);
        return (*m_pInstructions)[i]; 
    }

    size_t getInstructionCount() const { return m_pInstructions ? m_pInstructions->size() : 0; }

    Instruction* findInstructionAtCodePosition(const CodePosition& position) const;
    Instruction* findInstructionAtMemoryAddress(byte* a_pAddress) const;
    Instruction* findInstructionStartingAtMemoryAddress(byte* a_pAddress) const;

    Block* findBlockAtCodePosition(const CodePosition& a_Position) const;

    Block*  getBlock() const { return m_pBlock; }
    void    setBlock(Block* a_pBlock);

    virtual LanguageElement* getElement( const char* a_strQualifiedName , template_specialization const* a_pTS, function_signature const* a_pFS, bitfield a_Modifiers /* = bitfield */ ) const;
    
    bool containsMemoryAddress(const byte* a_pAddress);

protected:
    virtual void referencedElementRemoved(LanguageElement* a_pElement);

protected:
    vector<Instruction*>*   m_pInstructions;
    Block*                  m_pBlock;
    Signature*              m_pSignature;
    MemoryLocation          m_MemoryLocation;
};

o_h_end


#else // o_phantom_reflection_Subroutine_h__
#include "Subroutine.classdef.h"
#endif
