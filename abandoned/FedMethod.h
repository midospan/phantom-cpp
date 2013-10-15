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

#ifndef o_phantom_reflection_FedMethod_h__
#define o_phantom_reflection_FedMethod_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "FedMethod.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */
o_h_begin

o_static_assert(super_class_count_of<FedMethod>::value == 1);

class o_export FedMethod : public InstanceMethod
{
public:
    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection
public:

    FedMethod( InstanceMethod* a_pInstanceMethod )
        : InstanceMethod(a_pInstanceMethod->getName()
        , static_cast<Signature*>(a_pInstanceMethod->getSignature()->clone())
        , a_pInstanceMethod->getModifiers())
        , m_pInstanceMethod(a_pInstanceMethod)
    {
        m_pArguments = createArgumentList();
    }
    o_destructor ~FedMethod(void)
    {
        destroyArgumentList(m_pArguments);
    }

    virtual void    invoke( void* a_pInstance, argument::list* a_pArgumentListPointer ) const;
    virtual void    invoke( void* a_pInstance, argument::list* a_pArgumentListPointer, void* a_pReturnAddress ) const;
    virtual void    invoke( void* a_pInstance, void** a_pArgumentListPointer ) const;
    virtual void    invoke( void* a_pInstance, void** a_pArgumentListPointer, void* a_pReturnAddress ) const;

    template<typename t_Ty>
    void    setArgument( uint index, t_Ty* a_Value )
    {
        o_assert(index < m_pInstanceMethod->getParameterCount());
        m_FedArgumentsTable.setBit(index, true);
        Type* pValueType = phantom::typeOf<t_Ty>();
        Type* pSignatureType = m_pSignature->getParameterType(index);

        o_assert(pValueType->isClass() == pSignatureType->isClass());
        o_assert(pSignatureType->isClass()
            AND (static_cast<Class*>(pValueType)->isKindOf(
            static_cast<Class*>(pSignatureType))));

        Type::aligner    aligner((byte*)m_pArguments);
        uint i = 0;
        for(;i<index;++i)
        {
            aligner.skip(m_pSignature->getParameterType(i));
        }
        aligner.push(pValueType, &a_Value);
        _rebuildSignature();
    }

    void            unsetArgument(uint index)
    {
        m_FedArgumentsTable.setBit(index, false);
    }

    void            setParameter(uint i, void* a_pValue);
    void            setFedArgumentTable(bitfield a_uiValue)    {    m_FedArgumentsTable = a_uiValue;    }
    bitfield        getFedArgumentTable() const { return m_FedArgumentsTable; }

    virtual argument::list*    createArgumentList() const
    {
        return m_pInstanceMethod->createArgumentList();
    }
    virtual void    destroyArgumentList(argument::list* al) const
    {
        m_pInstanceMethod->destroyArgumentList(al);
    }
protected:
    void                _rebuildSignature();

protected:
    InstanceMethod*            m_pInstanceMethod;
    bitfield                m_FedArgumentsTable;
    argument::list*            m_pArguments;

};

o_h_end


#else // o_phantom_reflection_FedMethod_h__
#include "FedMethod.classdef.h"
#endif
