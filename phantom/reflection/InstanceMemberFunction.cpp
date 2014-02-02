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
/* *********************************************** */
o_registerN((phantom, reflection), InstanceMemberFunction);

o_namespace_begin(phantom, reflection) 

Class* const InstanceMemberFunction::metaType = o_type_of(InstanceMemberFunction);

InstanceMemberFunction::InstanceMemberFunction(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers /*= 0*/ )
: Subroutine(a_strName, a_pSignature, a_Modifiers )
, m_iVirtualTableIndex(-1)
{

}

InstanceMemberFunction::EOverloadRelation InstanceMemberFunction::getOverloadRelationWith( const string& a_strName, Signature* a_pSignature ) const
{
    if(a_strName != getName()) return e_OverloadRelation_None;

    if(getSignature()->getParameterCount() != a_pSignature->getParameterCount())
    {
        return e_OverloadRelation_None;
    }
    uint i = 0;
    for(;i<getSignature()->getParameterCount();++i)
    {
        if(getSignature()->getParameterType(i) != a_pSignature->getParameterType(i))
        {
            return e_OverloadRelation_None;
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
        return e_OverloadRelation_Equal;
    }

    // Primitive types cannot be covariant or contravariant
    if( NOT(thisReturnType->asClass())
        OR    NOT(otherReturnType->asClass()) )
    {
        return e_OverloadRelation_Forbidden;
    }

    // Covariance and Contravariance test
    if(static_cast<Class*>(thisReturnType)->isKindOf(static_cast<Class*>(otherReturnType)) )
    {
        return e_OverloadRelation_Covariant;
    }
    else if(static_cast<Class*>(otherReturnType)->isKindOf(static_cast<Class*>(thisReturnType)) )
    {
        // In the majority of case contravariance would be a forbidden case
        // We return a specific value for this result in case of ...
        return e_OverloadRelation_Contravariant;
    }

    // Return types don't have any inheritance relation
    return e_OverloadRelation_Forbidden;
}

InstanceMemberFunction::EOverloadRelation InstanceMemberFunction::getOverloadRelationWith( InstanceMemberFunction* a_pMemberFunction ) const
{
    if(NOT(a_pMemberFunction->isVirtual())) return e_OverloadRelation_None;
    return getOverloadRelationWith(a_pMemberFunction->getName(), a_pMemberFunction->getSignature());
}


void InstanceMemberFunction::findOverloadedMemberFunctions(vector<InstanceMemberFunction*>& a_Result) const
{
    if(m_pOwner == NULL) return;
    if(m_pOwner->asClass()) 
        static_cast<Class*>(m_pOwner)->findOverloadedMemberFunctions(const_cast<InstanceMemberFunction*>(this), a_Result);
}

Class* InstanceMemberFunction::getSortingCategoryClass() const
{
    return classOf<InstanceMemberFunction>();
}

bool InstanceMemberFunction::canOverload( InstanceMemberFunction* a_pInstanceMemberFunction ) const
{
    EOverloadRelation r = getOverloadRelationWith(a_pInstanceMemberFunction);
    return (r == e_OverloadRelation_Covariant) OR (r == e_OverloadRelation_Equal);
}

bool InstanceMemberFunction::canOverload( const string& a_strName, Signature* a_pSignature ) const
{
    EOverloadRelation r = getOverloadRelationWith(a_strName, a_pSignature);
    return (r == e_OverloadRelation_Covariant) OR (r == e_OverloadRelation_Equal);
}

void InstanceMemberFunction::call( void** a_pArgs ) const
{
    void* caller = *a_pArgs++;
    call( caller, a_pArgs);
}

void InstanceMemberFunction::call( void** a_pArgs, void* a_pReturnAddress ) const
{
    void* caller = *a_pArgs++;
    call( caller, a_pArgs);
}

void InstanceMemberFunction::safeInvoke( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const
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

void InstanceMemberFunction::safeInvoke( void* a_pCallerAddress, void** a_pArgs ) const
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







o_namespace_end(phantom, reflection) 