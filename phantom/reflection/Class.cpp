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
#include <phantom/reflection/Class.h>
/* *********************************************** */
o_cpp_begin 


ReflectionCPP__________________________________________________________________________________
    
__________________________________________________________________________________ReflectionCPP


Class::Class(const string& a_strName, bitfield a_Modifiers)
: ClassType(a_strName, a_Modifiers)
, m_uiRegisteredInstances(0)
, m_pStateMachine(NULL)
{
}

Class::Class(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_Modifiers)
: ClassType(a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
, m_uiRegisteredInstances(0)
, m_pStateMachine(NULL)
{
}

Class::~Class()
{
    o_assert(m_DerivedClasses.empty(), "A class can be destroyed only if all it's derived classes have been destroyed");
    super_class_table::iterator it = m_SuperClasses.begin();
    super_class_table::iterator end = m_SuperClasses.end();
    for(; it != end; ++it)
    {
        it->m_pClass->removeDerivedClass(this);
    }
}    



DataMember* Class::getDataMemberCascade( const string& a_strName) const
{
    DataMember* pDataMember = getDataMember(a_strName);
    if(pDataMember != NULL) return pDataMember;
    o_foreach(Class* pClass, m_SuperClasses)
    {
        DataMember* pSuperDataMember = pClass->getDataMemberCascade(a_strName);
        if(pSuperDataMember != NULL)
        {
            if(pDataMember != NULL) 
            {
                // ambiguous access, so we return nothing
                return NULL;
            }
            pDataMember = pSuperDataMember;
        }
    }
    return pDataMember;
}



InstanceDataMember* Class::getInstanceDataMemberCascade( const string& a_strName ) const
{
    InstanceDataMember* pDataMember = getInstanceDataMember(a_strName);
    if(pDataMember != NULL) return pDataMember;
    o_foreach(Class* pClass, m_SuperClasses)
    {
        InstanceDataMember* pSuperDataMember = pClass->getInstanceDataMemberCascade(a_strName);
        if(pSuperDataMember != NULL)
        {
            if(pDataMember != NULL) 
            {
                // ambiguous access, so we return nothing
                return NULL;
            }
            pDataMember = pSuperDataMember;
        }
    }
    return pDataMember;
}

StaticDataMember* Class::getStaticDataMemberCascade( const string& a_strName ) const
{
    StaticDataMember* pDataMember = getStaticDataMember(a_strName);
    if(pDataMember != NULL) return pDataMember;
    o_foreach(Class* pClass, m_SuperClasses)
    {
        StaticDataMember* pSuperDataMember = pClass->getStaticDataMemberCascade(a_strName);
        if(pSuperDataMember != NULL)
        {
            if(pDataMember != NULL) 
            {
                // ambiguous access, so we return nothing
                return NULL;
            }
            pDataMember = pSuperDataMember;
        }
    }
    return pDataMember;
}

void Class::addExtension( ClassExtension* a_pExtension )
{
    addMember(a_pExtension);
}

ClassExtension* Class::getExtension( Class* a_pExtensionClass )
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<ClassExtension>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<ClassExtension>());
    for(; it != end; ++it)
    {
        if( phantom::is(a_pExtensionClass, it->second) ) 
            return static_cast<ClassExtension*>(it->second);
    }
    return NULL;
}

void Class::addSignal( Signal* a_pSignal )
{
    addMember(a_pSignal);
}

Signal* Class::getSignal( const string& a_strIdentifierString ) const
{
    InstanceMemberFunction* pMemberFunction = getInstanceMemberFunction(a_strIdentifierString);
    if(pMemberFunction != NULL AND pMemberFunction->isSignal()) return static_cast<Signal*>(pMemberFunction);
    return NULL;
}

Signal* Class::getSignalCascade( const string& a_strIdentifierString ) const
{
    Signal* pSignal = getSignal(a_strIdentifierString);
    if(pSignal != NULL) return pSignal;
    o_foreach(Class* pClass, m_SuperClasses)
    {
        Signal* pSuperSignal = pClass->getSignalCascade(a_strIdentifierString);
        if(pSuperSignal != NULL)
        {
            if(pSignal != NULL) 
            {
                // ambiguous access, so we return nothing
                return NULL;
            }
            pSignal = pSuperSignal;
        }
    }
    return pSignal;
}

InstanceMemberFunction* Class::getSlot( const string& a_strIdentifierString ) const
{
    InstanceMemberFunction* pMemberFunction = getInstanceMemberFunction(a_strIdentifierString);
    if(pMemberFunction != NULL AND pMemberFunction->isSlot()) return pMemberFunction;
    return NULL;
}

InstanceMemberFunction* Class::getSlotCascade( const string& a_strIdentifierString ) const
{
    InstanceMemberFunction* pSlot = getSlot(a_strIdentifierString);
    if(pSlot != NULL) return pSlot;
    o_foreach(Class* pClass, m_SuperClasses)
    {
        InstanceMemberFunction* pSuperSlot = pClass->getSlotCascade(a_strIdentifierString);
        if(pSuperSlot != NULL)
        {
            if(pSlot != NULL) 
            {
                // ambiguous access, so we return nothing
                return NULL;
            }
            pSlot = pSuperSlot;
        }
    }
    return pSlot;
}

boolean Class::doesInstanceDependOn( void* a_pInstance, void* a_pOther ) const
{
    o_assert(a_pInstance);
    o_assert(classOf(a_pInstance)->isKindOf(const_cast<Class*>(this)));
    o_assert(a_pOther);

    o_foreach(Class* pClass, m_SuperClasses)
    {
        if(pClass->doesInstanceDependOn(a_pInstance, a_pOther)) return true;
    }

    member_collection::const_iterator it = m_Members.lower_bound(classOf<ValueMember>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<ValueMember>());
    for(; it != end; ++it)
    {
        if(it->second->isInstanceDataMember())
        {
            InstanceDataMember* pInstanceDataMember = static_cast<InstanceDataMember*>(it->second);
            Type*    pDataMemberType = pInstanceDataMember->getValueType();
            if(pDataMemberType->isClass())
            {
                if(*static_cast<void**>(pInstanceDataMember->getAddress(a_pInstance)) == a_pOther) 
                    return true;
            }
        }
    }
    return false;
}

InstanceMemberFunction** Class::getVfTable() const
{
    for(uint i=0; i<getVirtualMemberFunctionTableCount(); ++i)
    {
        VirtualMemberFunctionTable* pVTable = getVirtualMemberFunctionTable(i);
        if(pVTable->getBaseClass() == this)
        {
            return pVTable->getMemberFunctions();
        }
    }
    return NULL;
}

state::StateMachine* Class::getStateMachine() const
{
    return m_pStateMachine;
}

state::StateMachine* Class::getStateMachineCascade() const
{
    if(m_pStateMachine) return m_pStateMachine;
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(; it != end; ++it)
    {
        state::StateMachine* pSuperStateMachine = it->m_pClass->getStateMachineCascade();
        if(pSuperStateMachine) // Get the first available super state machine
        {
            return pSuperStateMachine;
        }
    }
    return NULL;
}

void Class::addSuperClass( Class* a_pClass, size_t a_uiOffset )
{
    o_assert(NOT(hasSuperClass(a_pClass)));
    m_SuperClasses.push_back(super_class_data(a_pClass, a_uiOffset));
    a_pClass->addDerivedClass(const_cast<Class*>(this));
}

boolean Class::hasSuperClass( Class* a_pClass ) const
{
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(; it != end; ++it)
    {
        if(it->m_pClass == a_pClass)
        {
            return true;
        }
    }
    return false;
}

void Class::addDerivedClass( Class* a_pType )
{
    m_DerivedClasses.push_back(a_pType);
}

boolean Class::hasDerivedClass( Class* a_pClass ) const
{
    uint i = 0;
    for(;i<m_DerivedClasses.size();++i)
    {
        if(m_DerivedClasses[i] == a_pClass)
        {
            return true;
        }
    }
    return false;
}

void Class::setupVirtualMemberFunctionTables() const
{
    if(NOT(m_VirtualMemberFunctionTables.empty()))
        return;

    if(m_SuperClasses.empty())
    {
        instance_member_function_list member_functions;
        member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMemberFunction>());
        member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMemberFunction>());
        for(;it != end; ++it)
        {
            InstanceMemberFunction* pMemberFunction = static_cast<InstanceMemberFunction*>(it->second);
            if(pMemberFunction->isVirtual())
                member_functions.push_back(pMemberFunction);
        }
        m_VirtualMemberFunctionTables.push_back(o_new(VirtualMemberFunctionTable)(const_cast<Class*>(this), &member_functions));
        return;
    }

    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        Class* pSuperType = it->m_pClass;
        pSuperType->setupVirtualMemberFunctionTables();

        uint i = 0;
        for(;i<pSuperType->getVirtualMemberFunctionTableCount(); ++i)
        {
            instance_member_function_list member_functions;
            instance_member_function_list rootMemberFunctions;
            sortSuperAndRootMemberFunctions(pSuperType->getVirtualMemberFunctionTable(i), &member_functions, &rootMemberFunctions);
            if(it == m_SuperClasses.begin() AND i == 0) // Common branch
            {
                member_functions.insert(member_functions.end(), rootMemberFunctions.begin(), rootMemberFunctions.end());
                m_VirtualMemberFunctionTables.push_back(o_new(VirtualMemberFunctionTable)(const_cast<Class*>(this), &member_functions));
            }
            else
            {
                m_VirtualMemberFunctionTables.push_back(o_new(VirtualMemberFunctionTable)(pSuperType->getVirtualMemberFunctionTable(i)->getBaseClass(), &member_functions));
            }
        }
    }
}

void Class::homonymousMemberFunctionSearch( member_function_search_data* a_pMemberFunctionRequest )
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMemberFunction>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMemberFunction>());

    for(;it != end; ++it)
    {
        InstanceMemberFunction*    pMemberFunction = static_cast<InstanceMemberFunction*>(it->second);
        if(pMemberFunction->getName() == a_pMemberFunctionRequest->getMemberFunctionName())
        {
            if(pMemberFunction->getSignature()->getParameterCount() == a_pMemberFunctionRequest->getMemberFunctionSignature()->getParameterCount())
            {
                uint i = 0;
                boolean bIncompatibleParameterFound = false;
                for(;i<pMemberFunction->getSignature()->getParameterCount();++i)
                {
                    if(pMemberFunction->getSignature()->getParameterType(i) != a_pMemberFunctionRequest->getMemberFunctionSignature()->getParameterType(i))
                    {
                        bIncompatibleParameterFound = true;
                        break;
                    }
                }
                if(bIncompatibleParameterFound)
                {
                    a_pMemberFunctionRequest->populateWithResult(member_function_search_data::eResultType_IncompatibleParameterType, pMemberFunction);
                    continue;
                }
                Type* pCurrentReturnType = pMemberFunction->getSignature()->getReturnType();
                Type* pRequestReturnType = a_pMemberFunctionRequest->getMemberFunctionSignature()->getReturnType();
                if(pCurrentReturnType == pRequestReturnType)
                {
                    a_pMemberFunctionRequest->populateWithResult(member_function_search_data::eResultType_PerfectMatch, pMemberFunction);
                }
                else if(pCurrentReturnType->isClass())
                {
                    if(NOT(pRequestReturnType->isClass()))
                    {
                        a_pMemberFunctionRequest->populateWithResult(member_function_search_data::eResultType_IncompatibleReturnType, pMemberFunction);
                    }
                    else if( ((Class*)pCurrentReturnType)->isKindOf((Class*)pRequestReturnType) )
                    {
                        a_pMemberFunctionRequest->populateWithResult(member_function_search_data::eResultType_CovariantMatch, pMemberFunction);
                    }
                    else if( ((Class*)pRequestReturnType)->isKindOf((Class*)pCurrentReturnType) )
                    {
                        a_pMemberFunctionRequest->populateWithResult(member_function_search_data::eResultType_ContravariantMatch, pMemberFunction);
                    }
                }
                else
                {
                    a_pMemberFunctionRequest->populateWithResult(member_function_search_data::eResultType_IncompatibleReturnType, pMemberFunction);
                }
            }
            else
            {
                a_pMemberFunctionRequest->populateWithResult(member_function_search_data::eResultType_IncompatibleParameterCount, pMemberFunction);
            }
        }
    }
}

void Class::sortSuperAndRootMemberFunctions( VirtualMemberFunctionTable* a_pSuperVMT, instance_member_function_list* a_OutSuperMemberFunctions, instance_member_function_list* a_OutRootMemberFunctions ) const
{
    uint i = 0;
    for(; i<a_pSuperVMT->getSize(); ++i)
    {
        InstanceMemberFunction* pSuperMemberFunction = a_pSuperVMT->getMemberFunction(i);
        member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMemberFunction>());
        member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMemberFunction>());
        for(;it != end; ++it)
        {
            InstanceMemberFunction* pMemberFunction = static_cast<InstanceMemberFunction*>(it->second);
            if(pMemberFunction->isVirtual())
            {
                InstanceMemberFunction::EOverloadRelation eIR = (static_cast<InstanceMemberFunction*>(pMemberFunction))->getOverloadRelationWith(pSuperMemberFunction);
                o_assert(        eIR != InstanceMemberFunction::e_OverloadRelation_Contravariant
                                    AND eIR != InstanceMemberFunction::e_OverloadRelation_Forbidden);
                if(eIR == InstanceMemberFunction::e_OverloadRelation_None)
                {
                    a_OutRootMemberFunctions->push_back(pMemberFunction);
                }
                else
                {
                    a_OutSuperMemberFunctions->push_back(pMemberFunction);
                }
            }
        }
    }
}

Class::ERelation Class::getRelationWith( Type* a_pType ) const
{
    if(a_pType == this)
        return eRelation_Equal;
    if(NOT(a_pType->isClass()))
        return eRelation_None;
    if(this->isKindOf((Class*)a_pType))
        return eRelation_Child;
    if(static_cast<Class*>(a_pType)->isKindOf(const_cast<Class*>(this)))
        return eRelation_Parent;

    return eRelation_None;
}

void     Class::getInvokableMemberFunctionsCascade(const string& a_strName, const vector<Type*>& a_ArgumentTypeList, MemberFunction** a_pOutPerfectMatchMemberFunction, member_function_vector* a_pResultMemberFunctions)
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMemberFunction>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMemberFunction>());
    for(;it != end; ++it)
    {
        InstanceMemberFunction*    pMemberFunction = static_cast<InstanceMemberFunction*>(it->second);
        Signature*    pSignature    = pMemberFunction->getSignature();

        // MemberFunction name incompatibility => we skip
        if(pMemberFunction->getName() != a_strName)
            continue;

        // Parameter count incompatibility => we skip
        if(pSignature->getParameterCount() != a_ArgumentTypeList.size())
            continue;

        boolean bMatch = true;
        boolean bPerfectMatch = true;
        uint i = 0;
        for(; i < pSignature->getParameterCount(); ++i)
        {
            Type* pArgumentType = a_ArgumentTypeList[i];
            Type* pParameterType = pSignature->getParameterType(i);
            Type::ERelation eTypeRelation = pArgumentType->getRelationWith(pParameterType);

            // If one parameter type doesn't match perfectly, member_function doesn't perfectly match
            if(eTypeRelation != Type::eRelation_Equal)
                bPerfectMatch = false;

            // Conversion works, we continue
            if(pArgumentType->isConvertibleTo(pParameterType))
                continue;

            // Other case means : no match
            if(        eTypeRelation == Type::eRelation_None
                OR    eTypeRelation == Type::eRelation_Parent)
            {
                bMatch = false;
                break;
            }
        }

        // If we found a perfect match, we store it in corresponding out-parameter
        if(    bPerfectMatch
        AND *a_pOutPerfectMatchMemberFunction == NULL)
        {
            *a_pOutPerfectMatchMemberFunction = pMemberFunction;
        }
        if(NOT(bMatch)) continue;

        // We check if the member_function hasn't already been added in result member_functions ; if not, we add it
        boolean bAlreadyAdded = false;
        member_function_vector::iterator it_alreadyAdded =  a_pResultMemberFunctions->begin();
        for(; it_alreadyAdded != a_pResultMemberFunctions->end(); ++it_alreadyAdded)
        {
            if((*it_alreadyAdded) == pMemberFunction)
            {
                bAlreadyAdded = true;
                break;
            }
        }
        if(NOT(bAlreadyAdded))
            a_pResultMemberFunctions->push_back(static_cast<InstanceMemberFunction*>(it->second));
    }

    // We browse the super types and treat recursively
    super_class_table::iterator it_super = m_SuperClasses.begin();
    super_class_table::iterator it_super_end = m_SuperClasses.end();
    for(;it_super != it_super_end; ++it_super)
    {
        it_super->m_pClass->getInvokableMemberFunctionsCascade(a_strName, a_ArgumentTypeList, a_pOutPerfectMatchMemberFunction, a_pResultMemberFunctions);
    }
}

void Class::findOverloadedMemberFunctions( InstanceMemberFunction* a_pOverloadCandidate, vector<InstanceMemberFunction*>& a_Result )
{
    member_collection::const_iterator it_member_function = m_Members.lower_bound(classOf<InstanceMemberFunction>());
    member_collection::const_iterator it_member_function_end = m_Members.upper_bound(classOf<InstanceMemberFunction>());
    for(;it_member_function!=it_member_function_end;++it_member_function)
    {
        if(it_member_function->second == a_pOverloadCandidate) continue;
        if(a_pOverloadCandidate->canOverload(static_cast<InstanceMemberFunction*>(it_member_function->second)))
        {
            bool bOverloadedAlreadyAddedForCurrentVTable = false;
            vector<InstanceMemberFunction*>::const_iterator it_result = a_Result.begin();
            vector<InstanceMemberFunction*>::const_iterator end_result = a_Result.end();
            for(;it_result!=end_result;++it_result)
            {
                InstanceMemberFunction* pResult = (*it_result);
                o_assert(pResult->getOwnerClass());
                if( pResult->getOwnerClass()->getSuperClassOffsetCascade((Class*)this) == 0 // in the same vtable
                    AND pResult->canOverload(static_cast<InstanceMemberFunction*>(it_member_function->second)))  // a result member_function can overload the current tested member_function, 
                                                                                                // which means that for the current VTable, 
                                                                                                // we already have found an overloaded member_function
                {
                    bOverloadedAlreadyAddedForCurrentVTable = true;
                    break;
                }
            }
            if(NOT(bOverloadedAlreadyAddedForCurrentVTable))
            {
                a_Result.push_back(static_cast<InstanceMemberFunction*>(it_member_function->second));
            }
        }
    }
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        it->m_pClass->findOverloadedMemberFunctions(a_pOverloadCandidate, a_Result);
    }
}

boolean Class::acceptMemberFunction( const string& a_strName, Signature* a_pSignature, member_function_vector* a_pOutConflictingMemberFunctions ) const
{
    boolean bResult = true;
    {
        member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMemberFunction>());
        member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMemberFunction>());
        for(; it != end; ++it)
        {
            InstanceMemberFunction* pInstanceMemberFunction = static_cast<InstanceMemberFunction*>(it->second);
            InstanceMemberFunction::EOverloadRelation eOR = pInstanceMemberFunction->getOverloadRelationWith(a_strName, a_pSignature);
            if(eOR != InstanceMemberFunction::e_OverloadRelation_None)
            {
                if(a_pOutConflictingMemberFunctions) a_pOutConflictingMemberFunctions->push_back(pInstanceMemberFunction);
                bResult = false;
            }
        }
    }
    if(NOT(bResult))
    {
        return false;
    }
    {
        super_class_table::const_iterator it = m_SuperClasses.begin();
        super_class_table::const_iterator end = m_SuperClasses.end();
        for(;it != end; ++it)
        {
            if(NOT(it->m_pClass->acceptsOverloadedMemberFunction(a_strName,a_pSignature, a_pOutConflictingMemberFunctions)))
            {
                return false;
            }
        }
    }
    return true;
}

boolean Class::acceptsOverloadedMemberFunction( const string& a_strName, Signature* a_pSignature, member_function_vector* a_pOutConflictingMemberFunctions ) const
{
    member_function_vector prevMemberFunctions;
    boolean bResult = true;
    {
        super_class_table::const_iterator it = m_SuperClasses.begin();
        super_class_table::const_iterator end = m_SuperClasses.end();
        for(;it != end; ++it)
        {
            if(NOT(it->m_pClass->acceptsOverloadedMemberFunction(a_strName, a_pSignature, &prevMemberFunctions)))
            {
                bResult = false;
            }
        }
    }

    {
        member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMemberFunction>());
        member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMemberFunction>());
        for(; it != end; ++it)
        {
            InstanceMemberFunction* pInstanceMemberFunction = static_cast<InstanceMemberFunction*>(it->second);
            InstanceMemberFunction::EOverloadRelation eOR = pInstanceMemberFunction->getOverloadRelationWith(a_strName, a_pSignature);
            if(eOR == InstanceMemberFunction::e_OverloadRelation_Forbidden
                OR eOR == InstanceMemberFunction::e_OverloadRelation_Covariant)
            {
                a_pOutConflictingMemberFunctions->push_back(pInstanceMemberFunction);
                return false;
            }
        }
    }
    {
        member_function_vector::iterator it = prevMemberFunctions.begin();
        for(;it != prevMemberFunctions.end(); ++it)
        {
            a_pOutConflictingMemberFunctions->push_back(*it);
        }
    }

    return bResult;
}

void Class::filtersNonOverloadedPureVirtualMemberFunctionsCascade( instance_member_function_vector& a_Result ) const
{
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(; it != end; ++it)
    {
        it->m_pClass->filtersNonOverloadedPureVirtualMemberFunctionsCascade(a_Result);
    }
    phantom::list<instance_member_function_vector::iterator> toRemove;
    instance_member_function_vector::iterator it_abs = a_Result.begin();
    for(;it_abs != a_Result.end(); ++it_abs)
    {
        InstanceMemberFunction* pPureVirtualMemberFunction = *it_abs;
        member_collection::const_iterator it_met = m_Members.lower_bound(classOf<InstanceMemberFunction>());
        member_collection::const_iterator it_met_end = m_Members.upper_bound(classOf<InstanceMemberFunction>());
        for(; it_met != it_met_end; ++it_met)
        {
            InstanceMemberFunction* pMemberFunction = static_cast<InstanceMemberFunction*>(it_met->second);
            if(pMemberFunction->isAbstract()) continue;
            InstanceMemberFunction::EOverloadRelation eOR = pMemberFunction->getOverloadRelationWith(pPureVirtualMemberFunction);
            o_assert(eOR != InstanceMemberFunction::e_OverloadRelation_Forbidden);
            if(eOR != InstanceMemberFunction::e_OverloadRelation_None)
            {
                toRemove.push_back(it_abs);
                break;
            }
        }
    }
    phantom::list<instance_member_function_vector::iterator>::iterator it_rem = toRemove.begin();
    phantom::list<instance_member_function_vector::iterator>::iterator it_rem_end = toRemove.end();
    for(; it_rem != it_rem_end; ++it_rem)
    {
        a_Result.erase(*it_rem);
    }

    findPureVirtualMemberFunctions(a_Result);
}

void Class::findPureVirtualMemberFunctions( instance_member_function_vector& a_Result ) const
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMemberFunction>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMemberFunction>());
    for(; it != m_Members.end(); ++it)
    {
        InstanceMemberFunction* pMemberFunction = static_cast<InstanceMemberFunction*>(it->second);
        if(pMemberFunction->isAbstract())
        {
            a_Result.push_back(pMemberFunction);
        }
    }
}

void Class::removeDerivedClass( Class* a_pType )
{
    class_vector::iterator it = m_DerivedClasses.begin();
    for(; it != m_DerivedClasses.end(); ++it)
    {
        if( (*it) == a_pType ) break;
    }
    if(it != m_DerivedClasses.end())
    {
        m_DerivedClasses.erase(it);
    }
}

StaticMemberFunction*    Class::getStaticMemberFunctionCascade( const string& a_strIdentifierString ) const
{
    StaticMemberFunction* pMemberFunction = getStaticMemberFunction(a_strIdentifierString);
    if(pMemberFunction != NULL) return pMemberFunction;
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        pMemberFunction = it->m_pClass->getStaticMemberFunctionCascade(a_strIdentifierString);
        if(pMemberFunction != NULL)
            return pMemberFunction;
    }
    return NULL;
}

InstanceMemberFunction*    Class::getInstanceMemberFunctionCascade( const string& a_strIdentifierString ) const
{
    InstanceMemberFunction* pMemberFunction = getInstanceMemberFunction(a_strIdentifierString);
    if(pMemberFunction != NULL) return pMemberFunction;
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        pMemberFunction = it->m_pClass->getInstanceMemberFunctionCascade(a_strIdentifierString);
        if(pMemberFunction != NULL)
            return pMemberFunction;
    }
    return NULL;
}

MemberFunction* Class::getMemberFunctionCascade( const string& a_strIdentifierString ) const
{
    MemberFunction* pMemberFunction = getMemberFunction(a_strIdentifierString);
    if(pMemberFunction != NULL) return pMemberFunction;
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        pMemberFunction = it->m_pClass->getMemberFunctionCascade(a_strIdentifierString);
        if(pMemberFunction != NULL)
            return pMemberFunction;
    }
    return NULL;
}

MemberFunction* Class::getMemberFunctionCascade(const string& a_strName, function_signature const* a_FunctionSignature, bitfield a_Modifiers /*= 0*/) const
{
    MemberFunction* pMemberFunction = getMemberFunction(a_strName, a_FunctionSignature, a_Modifiers);
    if(pMemberFunction != NULL) return pMemberFunction;
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        pMemberFunction = it->m_pClass->getMemberFunctionCascade(a_strName, a_FunctionSignature, a_Modifiers);
        if(pMemberFunction != NULL)
            return pMemberFunction;
    }
    return NULL;
}

void Class::getAllMemberCascade( vector<LanguageElement*>& a_out ) const
{
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        it->m_pClass->getAllMemberCascade(a_out);
    }
    getAllMember(a_out);

}

#if o__bool__use_kind_creation_signal
void                Class::fireKindCreated(void* a_pObject) const
{
    {
        super_class_table::const_iterator it = m_SuperClasses.begin();
        super_class_table::const_iterator end = m_SuperClasses.end();
        for(;it != end; ++it)
        {
            it->m_pClass->fireKindCreated((byte*)a_pObject + it->m_uiOffset);
        }
    }
    o_emit kindCreated(a_pObject);
}
#endif

#if o__bool__use_kind_destruction_signal
void                Class::fireKindDestroyed(void* a_pObject) const
{
    o_emit kindDestroyed(a_pObject);
    {
        super_class_table::const_iterator it = m_SuperClasses.begin();
        super_class_table::const_iterator end = m_SuperClasses.end();
        for(;it != end; ++it)
        {
            it->m_pClass->fireKindDestroyed((byte*)a_pObject + it->m_uiOffset);
        }
    }
}
#endif


ValueMember* Class::getValueMemberCascade(const string& a_strIdentifierString) const
{
    ValueMember* pFound = getValueMember(a_strIdentifierString);
    if(pFound != NULL) return pFound;

    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        ValueMember* pValueMember = it->m_pClass->getValueMemberCascade(a_strIdentifierString);
        if(pValueMember != nullptr)
            return pValueMember;
    }
    return nullptr;
}

Collection* Class::getCollectionCascade(const string& a_strCollectionName) const
{
    Collection* pFound = getCollection(a_strCollectionName);
    if(pFound != nullptr) return pFound;

    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        Collection* pCollection = it->m_pClass->getCollectionCascade(a_strCollectionName);
        if(pCollection != nullptr)
            return pCollection;
    }
    return nullptr;
}


void Class::getAllValueMemberCascade(vector<ValueMember*>& out) const
{
    getAllValueMember(out);
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        it->m_pClass->getAllValueMemberCascade(out);
    }
}

void Class::getAllCollectionCascade(vector<Collection*>& out) const
{
    getAllCollection(out);
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        it->m_pClass->getAllCollectionCascade(out);
    }
}


InstanceMemberFunction* Class::getInstanceMemberFunctionCascade( const string& a_strName, type_vector* a_pParameterTypes ) const
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMemberFunction>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMemberFunction>());
    for(;it != end; ++it)
    {
        InstanceMemberFunction* pMemberFunction = static_cast<InstanceMemberFunction*>(it->second);

        Signature* pSignature = pMemberFunction->getSignature();

        // MemberFunction name incompatibility => we skip
        if(pMemberFunction->getName() != a_strName)
            continue;

        // Parameter count incompatibility => we skip
        if(pSignature->getParameterCount() != a_pParameterTypes->size())
            continue;

        boolean bMatch = true;
        uint i = 0;
        for(; i < pSignature->getParameterCount(); ++i)
        {
            if(pSignature->getParameterType(i) != (*a_pParameterTypes)[i])
            {
                bMatch = false;
                break;
            }
        }
        if(NOT(bMatch))
            continue;

        return pMemberFunction;
    }
    {
        super_class_table::const_iterator it = m_SuperClasses.begin();
        super_class_table::const_iterator end = m_SuperClasses.end();
        for(;it != end; ++it)
        {
            InstanceMemberFunction* pResultMemberFunction = it->m_pClass->getInstanceMemberFunctionCascade(a_strName, a_pParameterTypes);
            if(pResultMemberFunction != NULL)
                return pResultMemberFunction;
        }
    }
    return NULL;
}

void Class::interpolate( void* a_src_start, void* a_src_end, real a_fPercent, void* a_pDest, uint mode /*= 0*/ ) const
{
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        it->m_pClass->interpolate(a_src_start, a_src_end, a_fPercent, a_pDest, mode);
    }
    ClassType::interpolate(a_src_start, a_src_end, a_fPercent, a_pDest);
}

/* PHANTOM SPECIFIC EXTENSION */


void Class::setStateMachine( state::StateMachine* a_pStateMachine )
{
    o_assert(m_pStateMachine == NULL, "a state machine has already been set for this class");
    o_assert(a_pStateMachine->m_pOwner == NULL, "the state machine has already been set in another class");
    m_pStateMachine = a_pStateMachine;
    m_pStateMachine->m_pOwner = this;
}
  
void* Class::cast( Class* a_pSuperClass, void* a_pBaseAddress ) const
{
    if(a_pSuperClass == this) return a_pBaseAddress;
    int offset = getSuperClassOffsetCascade(a_pSuperClass);
    return (offset == -1) 
        ? NULL 
        : static_cast<byte*>(a_pBaseAddress)+offset;
}


void Class::valueToString( string& s, const void* src ) const
{
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        it->m_pClass->valueToString(s, ((byte*)src)+it->m_uiOffset);
    }
    valueToString(s, src);
}

void Class::valueFromString( const string& cs, void* dest ) const
{
    o_exception(exception::unsupported_member_function_exception, "TODO (not supported yet)");
}

void* Class::newInstance() const
{
    void* pInstance = allocate(); 
    construct(pInstance);
    install(pInstance);
    initialize(pInstance);
    return pInstance;
}

void* Class::newInstance(Constructor* a_pConstructor, void** a_pArgs) const
{
    void* pInstance = allocate(); 
    a_pConstructor->construct(pInstance, a_pArgs);
    install(pInstance);
    initialize(pInstance);
    return pInstance;
}

void* Class::newInstance(Constructor* a_pConstructor, argument::list* a_pArgs) const
{
    void* pInstance = o_dynamic_pool_allocate(m_uiSize); 
    a_pConstructor->construct(pInstance, a_pArgs);
    install(pInstance);
    initialize(pInstance);
    return pInstance;
}

void Class::deleteInstance( void* a_pInstance ) const
{
    terminate(a_pInstance);
    uninstall(a_pInstance);
    destroy(a_pInstance);
    deallocate(a_pInstance);
}

void Class::safeDeleteInstance( void* a_pObject ) const
{
    deleteInstance(phantom::rttiDataOf(a_pObject).cast(const_cast<Class*>(this)));
}

InstanceMemberFunction*        Class::getInstanceMemberFunctionCascade(const char* a_strName, function_signature const* a_FunctionSignature, bitfield a_Modifiers /*= 0*/) const
{
  InstanceMemberFunction* pMemberFunction = getInstanceMemberFunction(a_strName, a_FunctionSignature, a_Modifiers);
  if(pMemberFunction != NULL) return pMemberFunction;
  super_class_table::const_iterator it = m_SuperClasses.begin();
  super_class_table::const_iterator end = m_SuperClasses.end();
  for(;it != end; ++it)
  {
    pMemberFunction = it->m_pClass->getInstanceMemberFunctionCascade(a_strName, a_FunctionSignature, a_Modifiers);
    if(pMemberFunction != NULL) return pMemberFunction;
  }
  return NULL;
}

LanguageElement* Class::getElement(
    const char* a_strName 
    , template_specialization const* a_TemplateSpecialization
    , function_signature const* a_FunctionSignature
    , bitfield a_Modifiers /*= 0*/) const 
{
    LanguageElement* pElement = ClassType::getElement(a_strName, a_TemplateSpecialization, a_FunctionSignature, a_Modifiers);
    if(pElement) return pElement;
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        if(pElement = it->m_pClass->getElement(a_strName, a_TemplateSpecialization, a_FunctionSignature, a_Modifiers))
            return pElement;
    }
    return NULL;
}

void Class::destroyContent()
{
    ClassType::destroyContent();
    // remove from super
    if(Phantom::getState() != Phantom::eState_Uninstalling)
    {
        {
            vmt_vector::iterator it = m_VirtualMemberFunctionTables.begin();
            for(;it!=m_VirtualMemberFunctionTables.end();it++)
            {
                o_dynamic_delete_clean(*it);
            }
        }
    }

    if(m_pStateMachine)
        o_dynamic_delete_clean(m_pStateMachine);
}

void Class::registerRtti( void* a_pThis, void* a_pBase, Class* a_pObjectClass, connection::slot_pool* a_pSlotPool, dynamic_delete_func_t a_dynamic_delete_func )
{
    if(m_SuperClasses.empty()) // Root class
    {
        registerRttiImpl(a_pThis, a_pBase, a_pObjectClass, a_pSlotPool, a_dynamic_delete_func);
    }
    else
    {
        super_class_table::const_iterator it = m_SuperClasses.begin();
        super_class_table::const_iterator end = m_SuperClasses.end();
        for(;it != end; ++it)
        {
            it->m_pClass->registerRtti(cast(it->m_pClass, a_pThis), a_pBase, a_pObjectClass, a_pSlotPool, a_dynamic_delete_func);
        }
    }
}

void Class::unregisterRtti( void* a_pThis )
{
    if(m_SuperClasses.empty()) // Root class
    {
        unregisterRttiImpl(a_pThis);
    }
    else
    {
        super_class_table::const_iterator it = m_SuperClasses.begin();
        super_class_table::const_iterator end = m_SuperClasses.end();
        for(;it != end; ++it)
        {
            it->m_pClass->unregisterRtti(cast(it->m_pClass, a_pThis));
        }
    }
}

void Class::smartCopy(void* a_pInstance, void const* a_pSource, reflection::Type* a_pSourceType) const
{
    Class* pSourceClass = a_pSourceType->asClass();
    o_assert(pSourceClass);
    vector<ValueMember*> valueMembers;
    pSourceClass->getAllValueMemberCascade(valueMembers);
    auto it = valueMembers.begin();
    auto end = valueMembers.end();
    for(; it!=end; ++it)
    {
        ValueMember* pOldValueMember = (*it);
        ValueMember* pNewValueMember = getValueMemberCascade(pOldValueMember->getName());
        Type* pOldValueMemberType = pOldValueMember->getValueType()->removeReference()->removeConst();
        Type* pNewValueMemberType = nullptr;
        if(pNewValueMember != nullptr 
            AND pOldValueMemberType->isImplicitlyConvertibleTo((pNewValueMemberType = pNewValueMember->getValueType()->removeReference()->removeConst())))
        {
            // Create temp buffers
            void* sourceBuffer = pOldValueMemberType->newInstance();
            void* newBuffer = pNewValueMemberType->newInstance();
            
            // Apply conversion
            pOldValueMember->getValue(pSourceClass->cast(pOldValueMember->getOwnerClass(), (void*)a_pSource), sourceBuffer);
            pOldValueMemberType->convertValueTo(pNewValueMemberType, newBuffer, sourceBuffer);
            pNewValueMember->setValue(cast(pNewValueMember->getOwnerClass(), a_pInstance), newBuffer);

            // Destroy temp buffers
            pOldValueMemberType->deleteInstance(sourceBuffer);
            pNewValueMemberType->deleteInstance(newBuffer);
        }
    }
}


boolean            Class::isKindOf( Class* a_pType ) const
{
    if(this == a_pType) return true;
    o_check_phantom_setup_step(o_global_value_SetupStepIndex_Inheritance);
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(; it != end; ++it)
    {
        if(it->m_pClass->isKindOf(a_pType)) return true;
    }
    return false;
}

const variant& Class::getAttributeCascade( const string& a_strName ) const
{
    const variant& v = getAttribute(a_strName);
    if(v.isValid()) return v;
    for(auto it = m_SuperClasses.begin(); it != m_SuperClasses.end(); ++it)
    {
        const variant& v = it->m_pClass->getAttributeCascade(a_strName);
        if(v.isValid()) return v;
    }
    return variant::null;
}


o_cpp_end
