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
#include "FedMethod.h"
/* *********************************************** */
o_cpp_begin 

void FedMethod::invoke( void* a_pInstance, argument::list* a_pArgumentListPointer, void* a_pReturnAddress ) const
{
    Signature* pCompleteSignature = m_pInstanceMethod->getSignature();
    uint i = 0;
    uint count = pCompleteSignature->getParameterCount();
    Type::aligner    writer(reinterpret_cast<byte*>(a_pArgumentListPointer));
    Type::aligner    reader(reinterpret_cast<byte*>(m_pArguments));
    for(;i<count;++i)
    {
        Type* pType = pCompleteSignature->getParameterType(i);
        if(m_FedArgumentsTable.isBitSet(i))
        {
            writer.push(pType, reader.address());
        }
        else
        {
            writer.skip(pType);
        }
        reader.skip(pType);
    }
    m_pInstanceMethod->invoke(a_pInstance, a_pArgumentListPointer, a_pReturnAddress);
}

void FedMethod::invoke( void* a_pInstance, argument::list* a_pArgumentListPointer ) const
{
    Signature* pCompleteSignature = m_pInstanceMethod->getSignature();
    uint i = 0;
    uint count = pCompleteSignature->getParameterCount();
    Type::aligner    writer(reinterpret_cast<byte*>(a_pArgumentListPointer));
    Type::aligner    reader(reinterpret_cast<byte*>(m_pArguments));
    for(;i<count;++i)
    {
        Type* pType = pCompleteSignature->getParameterType(i);
        if(m_FedArgumentsTable.isBitSet(i))
        {
            writer.push(pType, reader.address());
        }
        else
        {
            writer.skip(pType);
        }
        reader.skip(pType);
    }
    m_pInstanceMethod->invoke(a_pInstance, a_pArgumentListPointer);
}

void FedMethod::invoke( void* a_pInstance, void** a_pArgumentListPointer, void* a_pReturnAddress ) const
{
    o_assert_no_implementation();
//     Signature* pCompleteSignature = m_pInstanceMethod->getSignature();
//     uint i = 0;
//     uint count = pCompleteSignature->getParameterCount();
//     Type::aligner    writer(reinterpret_cast<byte*>(a_pArgumentListPointer));
//     Type::aligner    reader(reinterpret_cast<byte*>(m_pArguments));
//     for(;i<count;++i)
//     {
//         Type* pType = pCompleteSignature->getParameterType(i);
//         if(m_FedArgumentsTable.isBitSet(i))
//         {
//             writer.push(pType, reader.address());
//         }
//         else
//         {
//             writer.skip(pType);
//         }
//         reader.skip(pType);
//     }
//     m_pInstanceMethod->call(a_pInstance, a_pArgumentListPointer, a_pReturnAddress);
}

void FedMethod::invoke( void* a_pInstance, void** a_pArgumentListPointer ) const
{
    o_assert_no_implementation();
//     Signature* pCompleteSignature = m_pInstanceMethod->getSignature();
//     uint i = 0;
//     uint count = pCompleteSignature->getParameterCount();
//     Type::aligner    writer(reinterpret_cast<byte*>(a_pArgumentListPointer));
//     Type::aligner    reader(reinterpret_cast<byte*>(m_pArguments));
//     for(;i<count;++i)
//     {
//         Type* pType = pCompleteSignature->getParameterType(i);
//         if(m_FedArgumentsTable.isBitSet(i))
//         {
//             writer.push(pType, reader.address());
//         }
//         else
//         {
//             writer.skip(pType);
//         }
//         reader.skip(pType);
//     }
//     m_pInstanceMethod->call(a_pInstance, a_pArgumentListPointer);
}


void FedMethod::_rebuildSignature()
{
    if(m_pSignature)
    {
        o_dynamic_delete_clean(m_pSignature);
    }
    m_pSignature = o_new(Signature);
    m_pSignature->beginConstruction();
    m_pSignature->setReturnType(m_pInstanceMethod->getReturnType());
    Signature* pCompleteSignature = m_pInstanceMethod->getSignature();
    uint i = 0;
    uint count = pCompleteSignature->getParameterCount();
    for(;i<count;++i)
    {
        if(NOT(m_FedArgumentsTable.isBitSet(i)))
        {
            m_pSignature->addParameterType(pCompleteSignature->getParameterType(i));
        }
    }
    m_pSignature->endConstruction();
}

o_cpp_end