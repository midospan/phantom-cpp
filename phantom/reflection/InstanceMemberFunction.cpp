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
#include <phantom/reflection/InstanceMemberFunction.h>
#include <phantom/reflection/InstanceMemberFunction.hxx>
#include <phantom/reflection/Block.h>
#include <phantom/reflection/LocalVariable.h>
#include <phantom/reflection/Compiler.h>
/* *********************************************** */
o_registerN((phantom, reflection), InstanceMemberFunction);

o_namespace_begin(phantom, reflection) 

Class* const InstanceMemberFunction::metaType = o_type_of(InstanceMemberFunction);

InstanceMemberFunction::InstanceMemberFunction(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers /*= 0*/ )
    : Subroutine(a_strName
                , a_pSignature
                , e_ABI_thiscall
                , ((a_Modifiers & o_const) != 0) ? a_Modifiers : (a_Modifiers | o_noconst) )
    , m_uiVirtualTableIndex(~size_t(0))
    , m_pVTableClosures(nullptr)
{
}

InstanceMemberFunction::~InstanceMemberFunction()
{
    delete m_pVTableClosures;
}

InstanceMemberFunction::EOverrideRelation InstanceMemberFunction::getOverrideRelationWith( const string& a_strName, Signature* a_pSignature ) const
{
    if(a_strName != getName()) return e_OverrideRelation_None;

    if(getSignature()->getParameterCount() != a_pSignature->getParameterCount())
    {
        return e_OverrideRelation_None;
    }
    uint i = 0;
    for(;i<getSignature()->getParameterCount();++i)
    {
        if(getSignature()->getParameterType(i) != a_pSignature->getParameterType(i))
        {
            return e_OverrideRelation_None;
        }
    }

    // here, to sum, we have :
    // ¤ same name, 
    // ¤ same parameter count
    // ¤ same parameter types, 

    // We now look at the return types
    Type* thisReturnType = getSignature()->getReturnType();
    Type* otherReturnType = a_pSignature->getReturnType();
    if(thisReturnType == otherReturnType) 
    {
        return e_OverrideRelation_Equal;
    }

    // Primitive types cannot be covariant or contravariant
    if( NOT(thisReturnType->asClass())
        OR    NOT(otherReturnType->asClass()) )
    {
        return e_OverrideRelation_Forbidden;
    }

    // Covariance and Contravariance test
    if(static_cast<Class*>(thisReturnType)->isKindOf(static_cast<Class*>(otherReturnType)) )
    {
        return e_OverrideRelation_Covariant;
    }
    else if(static_cast<Class*>(otherReturnType)->isKindOf(static_cast<Class*>(thisReturnType)) )
    {
        // In the majority of case contravariance would be a forbidden case
        // We return a specific value for this result in case of ...
        return e_OverrideRelation_Contravariant;
    }

    // Return types don't have any inheritance relation
    return e_OverrideRelation_Forbidden;
}

InstanceMemberFunction::EOverrideRelation InstanceMemberFunction::getOverrideRelationWith( InstanceMemberFunction* a_pMemberFunction ) const
{
    if(NOT(a_pMemberFunction->isVirtual())) return e_OverrideRelation_None;
    return getOverrideRelationWith(a_pMemberFunction->getName(), a_pMemberFunction->getSignature());
}

bool InstanceMemberFunction::canOverride( InstanceMemberFunction* a_pInstanceMemberFunction ) const
{
    if(NOT(a_pInstanceMemberFunction->isVirtual())) 
        return false;
    EOverrideRelation r = getOverrideRelationWith(a_pInstanceMemberFunction);
    return (r == e_OverrideRelation_Covariant) OR (r == e_OverrideRelation_Equal);
}

bool InstanceMemberFunction::canOverride( const string& a_strName, Signature* a_pSignature ) const
{
    EOverrideRelation r = getOverrideRelationWith(a_strName, a_pSignature);
    return (r == e_OverrideRelation_Covariant) OR (r == e_OverrideRelation_Equal);
}

void InstanceMemberFunction::safeCall( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const
{
    reflection::Class* pOwnerClass = m_pOwner->asClass();
    if(pOwnerClass)
    {
        const rtti_data& rttiData = phantom::rttiDataOf(a_pCallerAddress);
        call( rttiData.cast(pOwnerClass), a_pArgs, a_pReturnAddress);
    }
    else
    {
        call( a_pCallerAddress, a_pArgs, a_pReturnAddress);
    }
}

void InstanceMemberFunction::safeCall( void* a_pCallerAddress, void** a_pArgs ) const
{
    reflection::Class* pOwnerClass = m_pOwner->asClass();
    if(pOwnerClass)
    {
        const rtti_data& rttiData = phantom::rttiDataOf(a_pCallerAddress);
        call( rttiData.cast(pOwnerClass), a_pArgs);
    }
    else
    {
        call( a_pCallerAddress, a_pArgs);
    }
}

/*
jit_function InstanceMemberFunction::getVTableFunction( size_t a_uiThisOffset ) const
{
    o_assert(m_jit_function.function, "Closure not yet created, you must add this InstanceMemberFunction to a Class"); 
    if(a_uiThisOffset == 0) return m_jit_function;
    auto found = m_VTableOffsetFixFunctions.find(a_uiThisOffset);
    if(found != m_VTableOffsetFixFunctions.end())
    {
        return found->second;
    }
    jit_function func = compileThisOffsetShiftFunction(a_uiThisOffset);
    // UNCOMMENT TO TEST APPLY
//     void* nul = 0;
//     void* null[] = { &nul };
//     jit_function_apply(func, null, nullptr);
    //a_pInstanceMemberFunction->setVTableOffsetFixClosure[a_uiThisOffset] = func;
    return func;
}*/

void InstanceMemberFunction::setVirtual()
{
    if(isVirtual()) return;
    if(m_pOwner)
    {
        o_exception(exception::reflection_runtime_exception, "Member function cannot be set to virtual after being added to a class type")
    }
    m_Modifiers.setMask(o_virtual);
}

variant InstanceMemberFunction::compile( Compiler* a_pCompiler )
{
    return a_pCompiler->compile(this);
}

void* InstanceMemberFunction::getVTableClosure( size_t a_uiOffset ) const
{
    if(m_pVTableClosures == nullptr) return nullptr;
    auto found = m_pVTableClosures->find(a_uiOffset);
    return (found == m_pVTableClosures->end()) 
        ? nullptr 
        : found->second;
}

void InstanceMemberFunction::setVTableClosure( size_t a_uiOffset, void* a_pClosure )
{
    o_assert(!testModifiers(o_native));
    if(m_pVTableClosures == nullptr)
    {
        m_pVTableClosures = new map<size_t, void*>;
    }
    (*m_pVTableClosures)[a_uiOffset] = a_pClosure;
}

void InstanceMemberFunction::getOriginalOverriddenMemberFunctions( vector<InstanceMemberFunction*>& a_Out ) const
{
    Class* pClass = getOwnerClass();
    if(pClass == nullptr) return;
    for(auto it = pClass->beginVirtualMemberFunctionsTables(); it != pClass->endVirtualMemberFunctionsTables(); ++it)
    {
        InstanceMemberFunction* pRootMemberFunction = (*it)->getRootMemberFunction(const_cast<InstanceMemberFunction*>(this));
        if(pRootMemberFunction) a_Out.push_back(pRootMemberFunction);
    }
}

o_namespace_end(phantom, reflection) 