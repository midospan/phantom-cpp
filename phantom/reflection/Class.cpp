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
#include <phantom/reflection/Class.h>
#include <phantom/reflection/Class.hxx>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/Compiler.h>
#include <phantom/variant.h>
/* *********************************************** */
o_registerN((phantom, reflection), Class);
o_namespace_begin(phantom, reflection) 

o_static_assert((boost::is_same<phantom::reflection::ClassType, phantom::super_class_of<phantom::reflection::Class, 0>::type>::value));
// Set by reflection::Types::Install because Class meta type is a recursive meta type, indeed it's its own meta type (meta meta type)

o_define_meta_type(Class);

Class::Class(const string& a_strName, bitfield a_Modifiers)
: ClassType(new extra_data, a_strName, a_Modifiers)
, m_pStateMachine(NULL)
, m_pSingleton(nullptr)
, m_pSignals(nullptr)
{
}

Class::Class(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_Modifiers)
: ClassType(a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
, m_pStateMachine(NULL)
, m_pSingleton(nullptr)
, m_pSignals(nullptr)
{
}

Class::~Class()
{
    m_VirtualMemberFunctionTables.clear();
    if(m_pSignals)
    {
        delete m_pSignals;
    }

    while(m_DerivedClasses.size())
    {
        Class* pDerivedClass = m_DerivedClasses.back();
        pDerivedClass->ClassType::terminate();
        pDerivedClass->deleteNow();
    }
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

void Class::addInstanceMemberFunction(InstanceMemberFunction* a_pInstanceMemberFunction)
{
    if(a_pInstanceMemberFunction->isVirtual() AND m_VirtualMemberFunctionTables.empty())
    {
        addNewVirtualMemberFunctionTable();
    }
    for(auto it = beginVirtualMemberFunctionsTables(); it != endVirtualMemberFunctionsTables(); ++it)
    {
        (*it)->insertMemberFunction(a_pInstanceMemberFunction);
    }
    ClassType::addInstanceMemberFunction(a_pInstanceMemberFunction);
}

void Class::addSignal( Signal* a_pSignal )
{
    if(m_pSignals == nullptr)
    {
        m_pSignals = new vector<Signal*>;
    }
    m_pSignals->push_back(a_pSignal);
    addInstanceMemberFunction(a_pSignal);
}

void Class::removeSignal( Signal* a_pSignal )
{
    removeElement(a_pSignal);
}

Signal* Class::getSignal( const string& a_strIdentifierString ) const
{
    InstanceMemberFunction* pMemberFunction = getInstanceMemberFunction(a_strIdentifierString);
    return pMemberFunction ? pMemberFunction->asSignal() : nullptr;
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
    return pMemberFunction ? pMemberFunction->asSlot() : nullptr;
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

    auto it = m_ValueMembers.begin();
    auto end = m_ValueMembers.end();
    for(; it != end; ++it)
    {
        if((*it)->asInstanceDataMember())
        {
            InstanceDataMember* pInstanceDataMember = static_cast<InstanceDataMember*>(*it);
            Type*    pDataMemberType = pInstanceDataMember->getValueType();
            if(pDataMemberType->asClass())
            {
                if(*static_cast<void**>(pInstanceDataMember->getAddress(a_pInstance)) == a_pOther) 
                    return true;
            }
        }
    }
    return false;
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

void Class::addSuperClass(Class* a_pClass)
{
    o_assert(m_pExtraData);
    extra_data* pExtraData = static_cast<extra_data*>(m_pExtraData);
    if(NOT(m_SuperClasses.empty())) 
    {
        size_t modulo = pExtraData->m_uiSuperSize % pExtraData->m_AlignmentComputer.maxAlignment();
        if(modulo)
            pExtraData->m_uiSuperSize += (pExtraData->m_AlignmentComputer.maxAlignment() - modulo);
        o_assert(pExtraData->m_bHasStateMachineDataPtr OR a_pClass->getStateMachine() == nullptr, "Cannot inherit from two classes which have both a state machine");
    }
    else
    {
        pExtraData->m_AlignmentComputer.setMaxAlignement(std::max(pExtraData->m_AlignmentComputer.maxAlignment()
                                                                , (size_t)a_pClass->getAlignment()));
        // First class added, test if it's polymorphic, and add vtable requirement if not
        pExtraData->m_bHasVTablePtr = NOT(a_pClass->isPolymorphic());
    }

    if(a_pClass->getStateMachine() != nullptr)
    {
        pExtraData->m_uiStateMachineDataPtrOffset = a_pClass->getStateMachine()->getDataPtrOffset() + pExtraData->m_uiSuperSize;
        pExtraData->m_bHasStateMachineDataPtr = false;
    }

    size_t superClassOffset = pExtraData->m_uiSuperSize;

    addSuperClass(a_pClass, superClassOffset);

    pExtraData->m_uiSuperSize += a_pClass->getSize();

    // we update the max alignment from the new super class
    pExtraData->m_AlignmentComputer.setMaxAlignement(

        pExtraData->m_AlignmentComputer.maxAlignment() > a_pClass->getAlignment()
        ? pExtraData->m_AlignmentComputer.maxAlignment()
        : a_pClass->getAlignment()

        );
}

void Class::addSuperClass( Class* a_pClass, size_t a_uiOffset )
{
    o_assert(NOT(hasSuperClass(a_pClass)));
    m_SuperClasses.push_back(super_class_data(a_pClass, a_uiOffset));
    a_pClass->addDerivedClass(const_cast<Class*>(this));
    for(auto it = a_pClass->beginVirtualMemberFunctionsTables(); it != a_pClass->endVirtualMemberFunctionsTables(); ++it)
    {
        m_VirtualMemberFunctionTables.push_back(deriveVirtualMemberFunctionTable(*it));
        addElement(m_VirtualMemberFunctionTables.back());
    }
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
    addReferencedElement(a_pType);
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

void Class::homonymousMemberFunctionSearch( member_function_search_data* a_pMemberFunctionRequest )
{
    auto it = m_InstanceMemberFunctions.begin();
    auto end = m_InstanceMemberFunctions.end();

    for(;it != end; ++it)
    {
        InstanceMemberFunction*    pMemberFunction = *it;
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
                else if(pCurrentReturnType->asClass())
                {
                    if(pRequestReturnType->asClass() == nullptr)
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
    for(; i<a_pSuperVMT->getMemberFunctionCount(); ++i)
    {
        InstanceMemberFunction* pSuperMemberFunction = a_pSuperVMT->getMemberFunction(i);
        auto it = m_InstanceMemberFunctions.begin();
        auto end = m_InstanceMemberFunctions.end();
        for(;it != end; ++it)
        {
            InstanceMemberFunction* pMemberFunction = *it;
            if(pMemberFunction->isVirtual())
            {
                InstanceMemberFunction::EOverrideRelation eIR = pMemberFunction->getOverrideRelationWith(pSuperMemberFunction);
                o_assert(        eIR != InstanceMemberFunction::e_OverrideRelation_Contravariant
                                    AND eIR != InstanceMemberFunction::e_OverrideRelation_Forbidden);
                if(eIR == InstanceMemberFunction::e_OverrideRelation_None)
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
        return e_Relation_Equal;
    if(a_pType->asClass() == nullptr)
        return e_Relation_None;
    if(this->isKindOf((Class*)a_pType))
        return e_Relation_Child;
    if(static_cast<Class*>(a_pType)->isKindOf(const_cast<Class*>(this)))
        return e_Relation_Parent;

    return e_Relation_None;
}

void     Class::getInvokableMemberFunctionsCascade(const string& a_strName, const vector<Type*>& a_ArgumentTypeList, MemberFunction** a_pOutPerfectMatchMemberFunction, member_function_vector* a_pResultMemberFunctions)
{
    auto it = m_InstanceMemberFunctions.begin();
    auto end = m_InstanceMemberFunctions.end();
    for(;it != end; ++it)
    {
        InstanceMemberFunction*    pMemberFunction = *it;
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
            if(eTypeRelation != Type::e_Relation_Equal)
                bPerfectMatch = false;

            // Conversion works, we continue
            if(pArgumentType->isConvertibleTo(pParameterType))
                continue;

            // Other case means : no match
            if(        eTypeRelation == Type::e_Relation_None
                OR    eTypeRelation == Type::e_Relation_Parent)
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
            a_pResultMemberFunctions->push_back(*it);
    }

    // We browse the super types and treat recursively
    super_class_table::iterator it_super = m_SuperClasses.begin();
    super_class_table::iterator it_super_end = m_SuperClasses.end();
    for(;it_super != it_super_end; ++it_super)
    {
        it_super->m_pClass->getInvokableMemberFunctionsCascade(a_strName, a_ArgumentTypeList, a_pOutPerfectMatchMemberFunction, a_pResultMemberFunctions);
    }
}

void Class::findOverriddenMemberFunctions( InstanceMemberFunction* a_pOverridingCandidate, vector<InstanceMemberFunction*>& a_Result )
{
    auto it_member_function = m_InstanceMemberFunctions.begin();
    auto it_member_function_end = m_InstanceMemberFunctions.end();
    for(;it_member_function!=it_member_function_end;++it_member_function)
    {
        if(*it_member_function == a_pOverridingCandidate) continue;
        if(a_pOverridingCandidate->canOverride(*it_member_function))
        {
            bool bOverloadedAlreadyAddedForCurrentVTable = false;
            vector<InstanceMemberFunction*>::const_iterator it_result = a_Result.begin();
            vector<InstanceMemberFunction*>::const_iterator end_result = a_Result.end();
            for(;it_result!=end_result;++it_result)
            {
                InstanceMemberFunction* pResult = (*it_result);
                o_assert(pResult->getOwnerClass());
                if( pResult->getOwnerClass()->getSuperClassOffsetCascade((Class*)this) == 0 // in the same vtable
                    AND pResult->canOverride(*it_member_function))  // a result member_function can overload the current tested member_function, 
                                                                                                // which means that for the current VTable, 
                                                                                                // we already have found an overloaded member_function
                {
                    bOverloadedAlreadyAddedForCurrentVTable = true;
                    break;
                }
            }
            if(NOT(bOverloadedAlreadyAddedForCurrentVTable))
            {
                a_Result.push_back(*it_member_function);
            }
        }
    }
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        it->m_pClass->findOverriddenMemberFunctions(a_pOverridingCandidate, a_Result);
    }
}

boolean Class::acceptMemberFunction( const string& a_strName, Signature* a_pSignature, member_function_vector* a_pOutConflictingMemberFunctions ) const
{
    boolean bResult = true;
    {
        auto it = m_InstanceMemberFunctions.begin();
        auto end = m_InstanceMemberFunctions.end();
        for(; it != end; ++it)
        {
            InstanceMemberFunction* pInstanceMemberFunction = *it;
            InstanceMemberFunction::EOverrideRelation eOR = pInstanceMemberFunction->getOverrideRelationWith(a_strName, a_pSignature);
            if(eOR != InstanceMemberFunction::e_OverrideRelation_None)
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
        auto it = m_InstanceMemberFunctions.begin();
        auto end = m_InstanceMemberFunctions.end();
        for(; it != end; ++it)
        {
            InstanceMemberFunction* pInstanceMemberFunction = *it;
            InstanceMemberFunction::EOverrideRelation eOR = pInstanceMemberFunction->getOverrideRelationWith(a_strName, a_pSignature);
            if(eOR == InstanceMemberFunction::e_OverrideRelation_Forbidden
                OR eOR == InstanceMemberFunction::e_OverrideRelation_Covariant)
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
        auto it_met = m_InstanceMemberFunctions.begin();
        auto it_met_end = m_InstanceMemberFunctions.end();
        for(; it_met != it_met_end; ++it_met)
        {
            InstanceMemberFunction* pMemberFunction = *it_met;
            if(pMemberFunction->isAbstract()) continue;
            InstanceMemberFunction::EOverrideRelation eOR = pMemberFunction->getOverrideRelationWith(pPureVirtualMemberFunction);
            o_assert(eOR != InstanceMemberFunction::e_OverrideRelation_Forbidden);
            if(eOR != InstanceMemberFunction::e_OverrideRelation_None)
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
    auto it = m_InstanceMemberFunctions.begin();
    auto end = m_InstanceMemberFunctions.end();
    for(; it != end; ++it)
    {
        InstanceMemberFunction* pMemberFunction = *it;
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

StaticMemberFunction* Class::getStaticMemberFunctionCascade( const char* a_strName, const vector<Type*>& a_FunctionSignature, vector<size_t>* a_pPartialMatchesIndexes, bitfield a_Modifiers /*= 0*/ ) const
{
    StaticMemberFunction* pMemberFunction = getStaticMemberFunction(a_strName, a_FunctionSignature, a_pPartialMatchesIndexes, a_Modifiers);
    if(pMemberFunction != NULL) return pMemberFunction;
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        pMemberFunction = it->m_pClass->getStaticMemberFunctionCascade(a_strName, a_FunctionSignature, a_pPartialMatchesIndexes, a_Modifiers);
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

MemberFunction* Class::getMemberFunctionCascade(const string& a_strName, const vector<Type*>& a_FunctionSignature, vector<size_t>* a_pPartialMatchesIndexes, bitfield a_Modifiers /*= 0*/) const
{
    MemberFunction* pMemberFunction = getMemberFunction(a_strName, a_FunctionSignature, a_pPartialMatchesIndexes, a_Modifiers);
    if(pMemberFunction != NULL) return pMemberFunction;
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        pMemberFunction = it->m_pClass->getMemberFunctionCascade(a_strName, a_FunctionSignature, a_pPartialMatchesIndexes, a_Modifiers);
        if(pMemberFunction != NULL)
            return pMemberFunction;
    }
    return NULL;
}

void Class::getMembersCascade( vector<LanguageElement*>& a_out ) const
{
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        it->m_pClass->getMembersCascade(a_out);
    }
    getMembers(a_out);

}

#if o__bool__use_kind_creation_signal
void                Class::fireKindCreated(void* a_pObject) const
{
    // TODO : move this singleton code in a better place
    if(isSingleton())
    {
        o_assert(m_pSingleton == nullptr);
        ((Class*)this)->m_pSingleton = a_pObject;
    }
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
    // TODO : move this singleton code in a better place
    if(isSingleton())
    {
        o_assert(m_pSingleton == a_pObject);
        ((Class*)this)->m_pSingleton = nullptr;
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


void Class::getValueMembersCascade(vector<ValueMember*>& out) const
{
    out.insert(out.end(), m_ValueMembers.begin(), m_ValueMembers.end());
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        it->m_pClass->getValueMembersCascade(out);
    }
}

void Class::getCollectionsCascade(vector<Collection*>& out) const
{
    if(m_pCollections)
    {
        out.insert(out.end(), m_pCollections->begin(), m_pCollections->end());
    }
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        it->m_pClass->getCollectionsCascade(out);
    }
}


InstanceMemberFunction* Class::getInstanceMemberFunctionCascade( const string& a_strName, type_vector* a_pParameterTypes ) const
{
    auto it = m_InstanceMemberFunctions.begin();
    auto end = m_InstanceMemberFunctions.end();
    for(;it != end; ++it)
    {
        InstanceMemberFunction* pMemberFunction = *it;

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
    o_assert(a_pStateMachine && a_pStateMachine->m_pOwner == NULL, "the state machine has already been set in another class");
    addElement(a_pStateMachine);
}

void Class::elementAdded(LanguageElement* a_pElement)
{
    state::StateMachine* pStateMachine = a_pElement->asStateMachine();
    if(pStateMachine)
    {
        o_assert(m_pStateMachine == nullptr);
        m_pStateMachine = pStateMachine;
    }
    else ClassType::elementAdded(a_pElement);
}

void Class::elementRemoved(LanguageElement* a_pElement)
{
    if(m_pStateMachine == a_pElement)
    {
        m_pStateMachine = nullptr;
    }
    else if(m_pSignals && a_pElement->asSignal())
    {
        m_pSignals->erase(std::find(m_pSignals->begin(), m_pSignals->end(), a_pElement->asSignal()));
    }
    else if(a_pElement->asVirtualMemberFunctionTable())
    {
        m_VirtualMemberFunctionTables.erase(std::find(m_VirtualMemberFunctionTables.begin(), m_VirtualMemberFunctionTables.end(), a_pElement->asVirtualMemberFunctionTable()));
    }
    ClassType::elementRemoved(a_pElement);
}

void* Class::cast( Class* a_pSuperClass, void* a_pBaseAddress ) const
{
    if(a_pSuperClass == this) return a_pBaseAddress;
    int offset = getSuperClassOffsetCascade(a_pSuperClass);
    return (offset == -1) 
        ? NULL 
        : static_cast<byte*>(a_pBaseAddress)+offset;
}

void* Class::cast( Type* a_pTarget, void* a_pBase ) const
{
    if(a_pTarget->asClass()) return cast(static_cast<Class*>(a_pTarget), a_pBase);
    return nullptr;
}


void Class::valueToString( string& s, const void* src ) const
{
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        it->m_pClass->valueToString(s, ((byte*)src)+it->m_uiOffset);
    }
    ClassType::valueToString(s, src);
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

InstanceMemberFunction*        Class::getInstanceMemberFunctionCascade(const char* a_strName, const vector<Type*>& a_FunctionSignature, vector<size_t>* a_pPartialMatchesIndexes, bitfield a_Modifiers /*= 0*/) const
{
    InstanceMemberFunction* pMemberFunction = getInstanceMemberFunction(a_strName, a_FunctionSignature, a_pPartialMatchesIndexes, a_Modifiers);
    if(pMemberFunction != NULL) return pMemberFunction;
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        pMemberFunction = it->m_pClass->getInstanceMemberFunctionCascade(a_strName, a_FunctionSignature, a_pPartialMatchesIndexes, a_Modifiers);
        if(pMemberFunction != NULL) return pMemberFunction;
    }
    return NULL;
}

LanguageElement* Class::solveElement(
    const string& a_strName 
    , const vector<TemplateElement*>* a_TemplateSpecialization
    , const vector<LanguageElement*>* a_FunctionSignature
    , bitfield a_Modifiers /*= 0*/) const 
{
    LanguageElement* pElement = ClassType::solveElement(a_strName, a_TemplateSpecialization, a_FunctionSignature, a_Modifiers);
    if(pElement) return pElement;
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        if(pElement = it->m_pClass->solveElement(a_strName, a_TemplateSpecialization, a_FunctionSignature, a_Modifiers))
        {
            if(pElement->asConstructor() == nullptr)
            {
                return pElement;
            }
        }
    }
    return NULL;
}

void Class::destroyContent()
{
    ClassType::destroyContent();
    // remove from super
    for(auto it = m_VirtualMemberFunctionTables.begin(); it!=m_VirtualMemberFunctionTables.end(); it++)
    {
        (*it)->deleteNow();
    }
    m_VirtualMemberFunctionTables.clear();

    if(m_pStateMachine)
    {
        m_pStateMachine->deleteNow();
        m_pStateMachine = nullptr;
    }
}

void Class::registerRtti( void* a_pThis, void* a_pBase, Class* a_pObjectClass, connection::slot_pool* a_pSlotPool, dynamic_delete_func_t a_dynamic_delete_func, size_t a_uiLevel )
{
    if(m_SuperClasses.empty()) // Root class
    {
        registerRttiImpl(a_pThis, a_pBase, a_pObjectClass, a_pSlotPool, a_dynamic_delete_func, a_uiLevel);
    }
    else
    {
        super_class_table::const_iterator it = m_SuperClasses.begin();
        super_class_table::const_iterator end = m_SuperClasses.end();
        for(;it != end; ++it)
        {
            it->m_pClass->registerRtti(cast(it->m_pClass, a_pThis), a_pBase, a_pObjectClass, a_pSlotPool, a_dynamic_delete_func, a_uiLevel);
        }
    }
}

void Class::unregisterRtti( void* a_pThis, size_t a_uiLevel )
{
    if(m_pSingleton == a_pThis)
    {
        m_pSingleton = nullptr;
    }
    if(m_SuperClasses.empty()) // Root class
    {
        unregisterRttiImpl(a_pThis, a_uiLevel);
    }
    else
    {
        super_class_table::const_iterator it = m_SuperClasses.begin();
        super_class_table::const_iterator end = m_SuperClasses.end();
        for(;it != end; ++it)
        {
            it->m_pClass->unregisterRtti(cast(it->m_pClass, a_pThis), a_uiLevel);
        }
    }
}

void Class::smartCopy(void* a_pInstance, void const* a_pSource, reflection::Type* a_pSourceType) const
{
    Class* pSourceClass = a_pSourceType->asClass();
    o_assert(pSourceClass);
    vector<ValueMember*> valueMembers;
    pSourceClass->getValueMembersCascade(valueMembers);
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
    //o_check_phantom_setup_step(o_global_value_SetupStepIndex_Inheritance);
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

void Class::destroySingleton()
{
    o_assert(m_pSingleton && classOf(m_pSingleton) == this);
    deleteInstance(m_pSingleton);
    m_pSingleton = nullptr;
}

bool Class::canBeDestroyed() const
{
    return ClassType::canBeDestroyed() 
        AND m_DerivedClasses.empty() 
        AND (getInstanceCount() == 0 || (this == typeOf<Class>() && getInstanceCount() == 1));
}

void Class::referencedElementRemoved( LanguageElement* a_pElement )
{
    for(auto it = m_DerivedClasses.begin(); it != m_DerivedClasses.end(); ++it)
    {
        if(*it == a_pElement)
        {
            m_DerivedClasses.erase(it);
            break;
        }
    }
}

void Class::registerInstance( void* a_pInstance )
{
    o_assert(std::find(m_Instances.begin(), m_Instances.end(), a_pInstance) == m_Instances.end())
    m_Instances.push_back(a_pInstance);
}

void Class::unregisterInstance( void* a_pInstance )
{
    auto found = std::find(m_Instances.begin(), m_Instances.end(), a_pInstance);
    o_assert(found != m_Instances.end());
    m_Instances.erase(found);
}

size_t Class::getKindCount() const
{
    size_t count = m_Instances.size();
    class_vector::const_iterator it = m_DerivedClasses.begin();
    class_vector::const_iterator end = m_DerivedClasses.end();
    for(;it!=end;++it)
    {
        count += (*it)->getKindCount();
    }
    return count;
}

void Class::installInstanceDataMembers( void* a_pInstance, size_t a_uiLevel ) const
{
    for(auto it = m_InstanceDataMembers.begin(); it != m_InstanceDataMembers.end(); ++it)
    {
        (*it)->m_pValueType->install((byte*)a_pInstance+(*it)->m_uiOffset, a_uiLevel+1);
    }
}

void Class::installInstanceDataMembersCascade( void* a_pInstance, size_t a_uiLevel ) const
{
    for(auto it = m_SuperClasses.begin(); it != m_SuperClasses.end(); ++it)
    {
        it->m_pClass->installInstanceDataMembersCascade((byte*)a_pInstance+it->m_uiOffset, a_uiLevel);
    }
    installInstanceDataMembers(a_pInstance, a_uiLevel);
}

void Class::uninstallInstanceDataMembers( void* a_pInstance, size_t a_uiLevel ) const
{
    for(auto it = m_InstanceDataMembers.begin(); it != m_InstanceDataMembers.end(); ++it)
    {
        (*it)->m_pValueType->uninstall((byte*)a_pInstance+(*it)->m_uiOffset, a_uiLevel+1);
    }
}

void Class::uninstallInstanceDataMembersCascade( void* a_pInstance, size_t a_uiLevel ) const
{
    uninstallInstanceDataMembers(a_pInstance, a_uiLevel);
    for(auto it = m_SuperClasses.begin(); it != m_SuperClasses.end(); ++it)
    {
        it->m_pClass->uninstallInstanceDataMembersCascade((byte*)a_pInstance+it->m_uiOffset, a_uiLevel);
    }
}

void Class::initializeInstanceDataMembers( void* a_pInstance ) const
{
    for(auto it = m_InstanceDataMembers.begin(); it != m_InstanceDataMembers.end(); ++it)
    {
        (*it)->m_pValueType->initialize((byte*)a_pInstance+(*it)->m_uiOffset);
    }
}

void Class::initializeInstanceDataMembersCascade( void* a_pInstance ) const
{
    for(auto it = m_SuperClasses.begin(); it != m_SuperClasses.end(); ++it)
    {
        it->m_pClass->initializeInstanceDataMembersCascade((byte*)a_pInstance+it->m_uiOffset);
    }
    initializeInstanceDataMembers(a_pInstance);
}

void Class::terminateInstanceDataMembers( void* a_pInstance ) const
{
    for(auto it = m_InstanceDataMembers.begin(); it != m_InstanceDataMembers.end(); ++it)
    {
        (*it)->m_pValueType->terminate((byte*)a_pInstance+(*it)->m_uiOffset);
    }
}

void Class::terminateInstanceDataMembersCascade( void* a_pInstance ) const
{
    terminateInstanceDataMembers(a_pInstance);
    for(auto it = m_SuperClasses.begin(); it != m_SuperClasses.end(); ++it)
    {
        it->m_pClass->terminateInstanceDataMembersCascade((byte*)a_pInstance+it->m_uiOffset);
    }
}

restore_state Class::restoreInstanceDataMembers( void* a_pInstance, uint a_uiSerializationFlag, uint a_uiPass ) const
{
    restore_state result = restore_complete;
    for(auto it = m_InstanceDataMembers.begin(); it != m_InstanceDataMembers.end(); ++it)
    {
        result = combine_restore_states(result, (*it)->m_pValueType->restore((byte*)a_pInstance+(*it)->m_uiOffset, a_uiSerializationFlag, a_uiPass));
    }
    return result;
}

restore_state Class::restoreInstanceDataMembersCascade( void* a_pInstance, uint a_uiSerializationFlag, uint a_uiPass ) const
{
    restore_state result = restore_complete;
    for(auto it = m_SuperClasses.begin(); it != m_SuperClasses.end(); ++it)
    {
        result = combine_restore_states(result, it->m_pClass->restoreInstanceDataMembersCascade((byte*)a_pInstance+it->m_uiOffset, a_uiSerializationFlag, a_uiPass));
    }
    result = combine_restore_states(result, restoreInstanceDataMembers(a_pInstance, a_uiSerializationFlag, a_uiPass));
    return result;
}

Expression* Class::solveExpression( Expression* a_pLeftExpression
                                 , const string& a_strName 
                                 , const vector<TemplateElement*>* a_pTemplateSpecialization
                                 , const vector<LanguageElement*>* a_pFunctionSignature
                                 , bitfield a_Modifiers /*= 0*/ ) const
{
    o_assert(a_pLeftExpression->getValueType()->removeReference()->removeConst() == removeConst());
    Expression* pExpression = ClassType::solveExpression(a_pLeftExpression, a_strName, a_pTemplateSpecialization, a_pFunctionSignature, a_Modifiers);
    if(pExpression) return pExpression;
    auto it = m_SuperClasses.begin();
    auto end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        if(pExpression = it->m_pClass->solveExpression(a_pLeftExpression->implicitCast(it->m_pClass->referenceType()), a_strName, a_pTemplateSpecialization, a_pFunctionSignature, a_Modifiers))
            return pExpression;
    }
    return nullptr;
}

bool Class::referencesData(const void* a_pInstance, const phantom::data& a_Data) const
{
    if(ClassType::referencesData(a_pInstance, a_Data))
        return true;
    auto it = m_SuperClasses.begin();
    auto end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        if(it->m_pClass->referencesData((byte*)a_pInstance + it->m_uiOffset, a_Data))
            return true;
    }
    return false;
}

void Class::fetchPointerReferenceExpressions( Expression* a_pInstanceExpression, vector<Expression*>& out, uint a_uiSerializationMask ) const
{
    ClassType::fetchPointerReferenceExpressions(a_pInstanceExpression, out, a_uiSerializationMask);
    auto it = m_SuperClasses.begin();
    auto end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        Expression* pClone = a_pInstanceExpression->clone()->implicitCast(it->m_pClass->referenceType());
        it->m_pClass->fetchPointerReferenceExpressions(pClone, out, a_uiSerializationMask);
        phantom::deleteElement(pClone);
    }
}

bool Class::isCopyable() const
{
    for(auto it = m_InstanceDataMembers.begin(); it != m_InstanceDataMembers.end(); ++it)
    {
        if(NOT((*it)->getValueType()->isCopyable())) return false;
    }
    for(auto it = m_SuperClasses.begin(); it != m_SuperClasses.end(); ++it)
    {
        if(NOT(it->m_pClass->isCopyable())) return false;
    }
    return  m_pSignals == nullptr && m_pStateMachine == nullptr && isCopyConstructible() && !hasCopyDisabled();
}

bool Class::isPolymorphic() const
{
    return m_VirtualMemberFunctionTables.size() != 0;
}

void*   Class::allocate() const
{
    o_assert(m_pExtraData->m_iState == extra_data::e_State_Finalized);
    return Type::allocate();
}

void    Class::deallocate(void* a_pInstance) const
{
    o_assert(m_pExtraData->m_iState == extra_data::e_State_Finalized);
    Type::deallocate(a_pInstance);

}
void*   Class::allocate(size_t a_uiCount) const
{
    o_assert(m_pExtraData->m_iState == extra_data::e_State_Finalized);
    return Type::allocate(a_uiCount);

}
void    Class::deallocate(void* a_pInstance, size_t a_uiCount) const
{
    o_assert(m_pExtraData->m_iState == extra_data::e_State_Finalized);
    Type::deallocate(a_pInstance, a_uiCount);
}

void Class::construct( void* a_pInstance ) const
{
    o_assert(m_pExtraData);
    o_assert(m_pExtraData->m_iState == extra_data::e_State_Finalized);

    // Construct super classes
    {
        super_class_table::const_iterator it = m_SuperClasses.begin();
        super_class_table::const_iterator end = m_SuperClasses.end();
        for(;it!=end;++it)
        {
            it->m_pClass->construct(((byte*)a_pInstance) + it->m_uiOffset);
        }
    }

    // Install VTable(s) if not yet
    for(auto it = m_VirtualMemberFunctionTables.begin(); it != m_VirtualMemberFunctionTables.end(); ++it)
    {
        (*it)->construct(a_pInstance);
    }

    /*if(m_VirtualTableInfos.empty()) // not initialized
    {
        int vtable_info_index = 0;
        bool bVTableRequired = false;
        super_class_table::const_iterator it = m_SuperClasses.begin();
        super_class_table::const_iterator end = m_SuperClasses.end();
        for(;it!=end;++it)
        {
            Class* pSuperClass = it->m_pClass;
            size_t uiSuperClassOffset = it->m_uiOffset;
            byte* address = (byte*)a_pInstance + uiSuperClassOffset;

            if(m_SuperClasses.begin() == it AND uiSuperClassOffset != 0)
            {
                // first super class and offset > 0 => new vtable required
                vector<void*> virtualMemberFunctionCallAddresses;
                size_t virtualMemberFunctionIndexAcc = 0;
                auto it = m_InstanceMemberFunctions.begin();
                auto end = m_InstanceMemberFunctions.end();
                for(;it!=end;++it)
                {
                    InstanceMemberFunction* pMemberFunction = *it;
                    vector<InstanceMemberFunction*> overloadeds;
                    {
                        super_class_table::const_iterator it = m_SuperClasses.begin();
                        super_class_table::const_iterator end = m_SuperClasses.end();
                        for(;it!=end;++it)
                        {
                            it->m_pClass->findOverriddenMemberFunctions(pMemberFunction, overloadeds);
                        }
                    }
                    // Check if the method overloads another and if this another belongs to the 0-offset vtable
                    {
                        bool needToAddToTheFirstVtable = overloadeds.empty() AND pMemberFunction->isVirtual();
                        o_foreach(InstanceMemberFunction* pOverloaded, overloadeds)
                        {
                            if(getSuperClassOffsetCascade(pOverloaded->getOwnerClass()) != 0)
                            {
                                needToAddToTheFirstVtable = true;
                                break;
                            }
                            else
                            {
                                pMemberFunction->setVirtualTableIndex(pOverloaded->getVirtualTableIndex());
                            }
                        }
                        if(needToAddToTheFirstVtable)
                        {
                            pMemberFunction->setVirtualTableIndex(virtualMemberFunctionIndexAcc++);
                            virtualMemberFunctionCallAddresses.push_back(pMemberFunction->getThisShiftClosure(0));
                        }
                    }
                }
                void** member_functions = nullptr;
                if(virtualMemberFunctionIndexAcc)
                {
                    member_functions = o_allocate_n(virtualMemberFunctionIndexAcc, void*);
                }
                vtable_info new_vtable(0, member_functions, virtualMemberFunctionIndexAcc);
                size_t i = 0;
                for(;i<virtualMemberFunctionIndexAcc;++i)
                {
                    new_vtable.member_functions[i] = virtualMemberFunctionCallAddresses[i];
                }
                m_VirtualTableInfos.push_back(new_vtable);
                bVTableRequired = true;
                vtable_info_index++;
            }

            vector<vtable_info> super_vtables;
            pSuperClass->extractVirtualMemberFunctionTableInfos(a_pInstance, super_vtables);
            
            vector<vtable_info>::iterator it = super_vtables.begin();
            vector<vtable_info>::iterator end = super_vtables.end();
            for(;it!=end;++it)
            {
                size_t vtable_offset = it->offset;
                size_t vtable_count = it->count;
                address += vtable_offset;

                void** vptr = *((void***)address);
                
                // copy vtable pointers (each one may be replaced on the next step by overloading member_functions vtable pointer)

                vector<void*> virtualMemberFunctionCallAddresses;
                
                size_t i = 0;
                for(;i<vtable_count;++i)
                {
                    virtualMemberFunctionCallAddresses.push_back(vptr ? vptr[i] : nullptr);
                }


                // ---- INSERT VIRTUAL METHODS ------
                auto it = m_InstanceMemberFunctions.begin();
                auto end = m_InstanceMemberFunctions.end();
                for(;it!=end;++it)
                {
                    InstanceMemberFunction* pMemberFunction = *it;
                    vector<InstanceMemberFunction*> overloadeds;
                    pSuperClass->findOverriddenMemberFunctions(pMemberFunction, overloadeds);
                    size_t i = 0;
                    size_t count = overloadeds.size();
                    // no overloaded method + virtual => new virtual method => we add it to the 0-offset vtable
                    if(count == 0 AND pMemberFunction->isVirtual() AND uiSuperClassOffset == 0)
                    {
                        virtualMemberFunctionCallAddresses.push_back(pMemberFunction->getThisShiftClosure(0));
                    }
                    // browse overloaded and replace their vtable pointer by the overloading vtable pointer
                    else for(;i<count;++i)
                    {
                        InstanceMemberFunction* pOverloaded = overloadeds[i];
                        size_t class_offset = pSuperClass->getSuperClassOffsetCascade(pOverloaded->getOwnerClass());
                        if(class_offset == vtable_offset) // if the overloaded belongs to the current vtable/superclass offset
                        {
                            size_t vtable_index = pOverloaded->getVirtualTableIndex();
                            if(uiSuperClassOffset == 0)
                            {
                                pMemberFunction->setVirtualTableIndex(vtable_index);
                            }
                            virtualMemberFunctionCallAddresses.resize(std::max(virtualMemberFunctionCallAddresses.size(), size_t(vtable_index+1)));
                            virtualMemberFunctionCallAddresses[vtable_index] = pMemberFunction->getThisShiftClosure(uiSuperClassOffset);
                        }
                    }
                }
                // ---- END INSERT VIRTUAL METHODS ------
                void** newVTable = nullptr;
                if(virtualMemberFunctionCallAddresses.size())
                {
                    newVTable = o_allocate_n(virtualMemberFunctionCallAddresses.size(), void*);
                    memcpy(newVTable, virtualMemberFunctionCallAddresses.data(), virtualMemberFunctionCallAddresses.size()*sizeof(void*));
                }
                vtable_info vti(vtable_offset+uiSuperClassOffset, newVTable, virtualMemberFunctionCallAddresses.size());
                m_VirtualTableInfos.push_back(vti);
            }
        }
        o_assert(NOT(static_cast<extra_data*>(m_pExtraData)->m_bHasVTablePtr) OR NOT(m_VirtualTableInfos.empty()));
    }

    // Install vtable ptrs
    {
        size_t i = 0;
        for(;i<m_VirtualTableInfos.size(); ++i)
        {
            *((void***)((byte*)a_pInstance + m_VirtualTableInfos[i].offset)) = m_VirtualTableInfos[i].member_functions;
        }
    }*/

    ClassType::construct(a_pInstance);
    
}

void Class::construct( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    Type::construct(a_pChunk, a_uiCount, a_uiChunkSectionSize);
}

void Class::destroy( void* a_pObject ) const
{
    ClassType::destroy(a_pObject);
    auto it = m_SuperClasses.rbegin();
    auto end = m_SuperClasses.rend();
    for(; it != end; ++it)
    {
        it->m_pClass->destroy((byte*)a_pObject+it->m_uiOffset);
    }
}

void Class::destroy( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    Type::destroy(a_pChunk, a_uiCount, a_uiChunkSectionSize);
}

void Class::InstallHelper( Class* a_pBaseClass, void* a_pBase, Class* a_pLayoutClass, void* a_pLayout, connection::slot_pool* sp, size_t a_uiLevel )
{
    rtti_data rd;
    rd.base = a_pBase;
    rd.object_class = a_pBaseClass;
    rd.layout_class = a_pLayoutClass;
    rd.dynamic_delete_func = 0;
    rd.connection_slot_allocator = sp;
    rd.level = a_uiLevel;
    phantom::addRttiData(a_pLayout, rd);
    auto it = a_pLayoutClass->beginSuperClasses();
    auto end = a_pLayoutClass->endSuperClasses();
    for(; it != end; ++it)
    {
        Class* pSuperClass = it->m_pClass;
        size_t superClassOffset = it->m_uiOffset;
        if(superClassOffset != 0)
        {
            void* this_layout = (byte*)a_pLayout + superClassOffset;
            InstallHelper(a_pBaseClass, a_pBase, pSuperClass, this_layout, sp, a_uiLevel);
        }
    }
}

void Class::UninstallHelper( void* a_pLayout, Class* a_pLayoutClass, size_t a_uiLevel )
{
    phantom::removeRttiData(a_pLayout, a_uiLevel);
    auto it = a_pLayoutClass->beginSuperClasses();
    auto end = a_pLayoutClass->endSuperClasses();
    for(; it != end; ++it)
    {
        Class* pSuperClass = it->m_pClass;
        size_t superClassOffset = it->m_uiOffset;
        if(superClassOffset != 0)
        {
            void* this_layout = (byte*)a_pLayout + superClassOffset;
            UninstallHelper(this_layout, pSuperClass, a_uiLevel);
        }
    }
}

void Class::serialize( void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    o_assert(m_pExtraData);
    auto it = beginSuperClasses();
    auto end = endSuperClasses();
    for(; it != end; ++it)
    {
        Class* pSuperClass = it->m_pClass;
        pSuperClass->serialize((byte*)a_pInstance + it->m_uiOffset, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    property_tree class_tree;
    serializeLayout(a_pInstance, class_tree, a_uiSerializationMask, a_pDataBase);
    a_OutBranch.add_child(encodeQualifiedDecoratedNameToIdentifierName(getQualifiedDecoratedName()), class_tree);
}

void Class::deserialize( void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    o_assert(m_pExtraData);
    auto it = beginSuperClasses();
    auto end = endSuperClasses();
    for(; it != end; ++it)
    {
        Class* pSuperClass = it->m_pClass;
        pSuperClass->deserialize((byte*)a_pInstance + it->m_uiOffset, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    {
        auto it = a_InBranch.begin();
        auto end = a_InBranch.end();
        for(;it!=end;++it)
        {
            // The test below could seem dirty but it's useful to deserialize typedefs or placeholder types 
            // which goal is to point to a type without having the same representation name (ex: my_vector2 could point to phantom::math::vector2<float>)
            // It's also useful is you have a type versionning (a script class rebuilt with a different name but you still want to deserialize from the older type name
            reflection::Type* solvedType = a_pDataBase->solveTypeByName(decodeQualifiedDecoratedNameFromIdentifierName(it->first));
            if(solvedType == this)
            {
                deserializeLayout(a_pInstance, it->second, a_uiSerializationMask, a_pDataBase);
            }
        }
    }
}

void Class::serializeLayout( void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    auto it = beginValueMembers();
    auto end = endValueMembers();
    for(;it != end; ++it)
    {
        reflection::ValueMember*const pValueMember = static_cast<reflection::ValueMember*const>(*it);
        if(pValueMember->isSaved(a_uiSerializationMask))
            pValueMember->serializeValue(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
}

void Class::deserializeLayout( void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase ) const
{
    auto it = beginValueMembers();
    auto end = endValueMembers();
    for(;it != end; ++it)
    {
        reflection::ValueMember* const pValueMember = static_cast<reflection::ValueMember*const>(*it);
        if(pValueMember->isSaved(a_uiSerializationMask)) 
            pValueMember->deserializeValue(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
}


void Class::initialize( void* a_pInstance ) const
{
    o_assert(m_pExtraData);
    extra_data* pCompilationData = static_cast<extra_data*>(m_pExtraData);
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it!=end;++it)
    {
        it->m_pClass->initialize((byte*)a_pInstance+it->m_uiOffset);
    }
    initializeInstanceDataMembers(a_pInstance);

    if(pCompilationData->m_pInitializeClosure)
    {
        void* args[1] = {&a_pInstance};
        pCompilationData->m_ClosureCallDelegate(pCompilationData->m_pInitializeClosure, args, 1, nullptr);
    }
    if(pCompilationData->m_bHasStateMachineDataPtr)
    {
        m_pStateMachine->getInstanceData(a_pInstance)->initialize();
    }
}

void Class::terminate( void* a_pInstance ) const
{
    o_assert(m_pExtraData);
    extra_data* pCompilationData = static_cast<extra_data*>(m_pExtraData);
    if(pCompilationData->m_bHasStateMachineDataPtr)
    {
        m_pStateMachine->getInstanceData(a_pInstance)->terminate();
    }
    if(pCompilationData->m_pTerminateClosure)
    {
        void* args[1] = {&a_pInstance};
        pCompilationData->m_ClosureCallDelegate(pCompilationData->m_pTerminateClosure, args, 1, nullptr);
    }
    terminateInstanceDataMembers(a_pInstance);
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it!=end;++it)
    {
        it->m_pClass->terminate((byte*)a_pInstance+it->m_uiOffset);
    }
}

phantom::restore_state Class::restore( void* a_pInstance, uint a_uiSerializationFlag, uint a_uiPass ) const
{
    o_assert(m_pExtraData);
    extra_data* pCompilationData = static_cast<extra_data*>(m_pExtraData);
    restore_state result = restore_complete;
    super_class_table::const_iterator it = beginSuperClasses();
    super_class_table::const_iterator end = endSuperClasses();
    for(; it != end; ++it)
    {
        result = combine_restore_states(result, it->m_pClass->restore(((byte*)a_pInstance)+it->m_uiOffset, a_uiSerializationFlag, a_uiPass));
    }
    result = combine_restore_states(result, restoreInstanceDataMembers(a_pInstance, a_uiSerializationFlag, a_uiPass));

    if(pCompilationData->m_pRestoreClosure)
    {
        void* args[3] = {&a_pInstance, &a_uiSerializationFlag, &a_uiPass};
        phantom::restore_state func_result = phantom::restore_complete;
        pCompilationData->m_ClosureCallDelegate(pCompilationData->m_pRestoreClosure, args, 3, &func_result);
        result = combine_restore_states(result, func_result);
    }

    if(result == restore_complete AND pCompilationData->m_bHasStateMachineDataPtr)
    {
        m_pStateMachine->getInstanceData(a_pInstance)->initialize();
    }

    return result;
}
// TODO : COMPILER
/*

InstanceMemberFunction* Class::addInitializeMemberFunction()
{
    o_assert(m_pExtraData);
    extra_data* pCompilationData = static_cast<extra_data*>(m_pExtraData);
    o_assert(pCompilationData->m_pInitializeClosure == nullptr);
    Signature* pSignature = o_new(Signature);
    pSignature->setReturnType(phantom::typeOf<void>());
    auto pInstanceMemberFunction= o_new(InstanceMemberFunction)("PHANTOM_CODEGEN_initialize", pSignature, o_protected);
    addInstanceMemberFunction(pCompilationData->m_pInitializeMemberFunction);
    return pCompilationData->m_pInitializeMemberFunction;
}

InstanceMemberFunction* Class::addTerminateMemberFunction()
{
    o_assert(m_pExtraData);
    extra_data* pCompilationData = static_cast<extra_data*>(m_pExtraData);
    o_assert(pCompilationData->m_pTerminateClosure == nullptr);
    Signature* pSignature = o_new(Signature);
    pSignature->setReturnType(phantom::typeOf<void>());
    auto pInstanceMemberFunction = o_new(InstanceMemberFunction)("PHANTOM_CODEGEN_terminate", pSignature, o_protected);
    addInstanceMemberFunction(pCompilationData->m_pTerminateMemberFunction);
    return pCompilationData->m_pTerminateMemberFunction;
}

InstanceMemberFunction* Class::addRestoreMemberFunction()
{
    o_assert(m_pExtraData);
    extra_data* pCompilationData = static_cast<extra_data*>(m_pExtraData);
    o_assert(pCompilationData->m_pRestoreClosure == nullptr);
    Signature* pSignature = o_new(Signature);
    pSignature->setReturnType(phantom::typeOf<uint>());
    pSignature->addParameterType(phantom::typeOf<uint>());
    pSignature->addParameterType(phantom::typeOf<uint>());
    auto pInstanceMemberFunction = o_new(InstanceMemberFunction)("PHANTOM_CODEGEN_restore", pSignature, o_protected);
    addInstanceMemberFunction(pCompilationData->m_pRestoreMemberFunction);
    return pCompilationData->m_pRestoreMemberFunction;
}*/

void Class::finalize()
{
    o_assert(m_pExtraData);

    if(m_pExtraData->m_iState >= extra_data::e_State_Finalized)
    {
        o_exception(exception::reflection_runtime_exception, "Class already compiling or compiled");
    }

    extra_data* pCompilationData = static_cast<extra_data*>(m_pExtraData);

    // Check if we really need a vtableptr
    if(pCompilationData->m_bHasVTablePtr)
    {
        pCompilationData->m_bHasVTablePtr = false;
        auto it =  m_InstanceMemberFunctions.begin();
        auto end = m_InstanceMemberFunctions.end();
        for(;it != end; ++it)
        {
            InstanceMemberFunction* pMemberFunction = *it;
            if(pMemberFunction->isVirtual())
            {
                pCompilationData->m_bHasVTablePtr = true;
                break;
            }
        }
        // Shift super class offset depending on if we have a vtableptr
        if(pCompilationData->m_bHasVTablePtr)
        {
            super_class_table::iterator it = m_SuperClasses.begin();
            super_class_table::iterator end = m_SuperClasses.end();
            for(;it!=end;++it)
            {
                it->m_uiOffset += sizeof(void*);
            }
        }
    }

    // Check if we really need a smdataptr
    if(pCompilationData->m_bHasStateMachineDataPtr)
    {
        o_assert(pCompilationData->m_uiStateMachineDataPtrOffset == 0xffffffff);
        if(getStateMachine())
        {
            pCompilationData->m_uiStateMachineDataPtrOffset = pCompilationData->m_bHasVTablePtr*sizeof(void*)
                + pCompilationData->m_uiSuperSize;
        }
        else
        {
            pCompilationData->m_bHasStateMachineDataPtr = false;
        }
    }
    else 
    {
        o_assert(pCompilationData->m_uiStateMachineDataPtrOffset != 0xffffffff);
        pCompilationData->m_uiStateMachineDataPtrOffset += pCompilationData->m_bHasVTablePtr*sizeof(void*);
    }
    if(m_pStateMachine)
        m_pStateMachine->setDataPtrOffset(pCompilationData->m_uiStateMachineDataPtrOffset);

    m_uiSize = pCompilationData->m_uiSuperSize + pCompilationData->m_bHasVTablePtr*sizeof(void*) 
        + pCompilationData->m_bHasStateMachineDataPtr *sizeof(void*); 

    ClassType::finalize();
}

variant Class::compile(Compiler* a_pCompiler)
{
    // layout : [vtableptr] [superlayout] [smdataptr] [data_members]
    ClassType::compile(a_pCompiler);

    if(m_pStateMachine)
        a_pCompiler->compile(m_pStateMachine);

    return a_pCompiler->compile(this);
}

void Class::install( void* a_pInstance, size_t a_uiLevel ) const
{
    connection::slot_pool& ac = connection::slot_pool::allocationController(a_pInstance, const_cast<Class*>(this));
    InstallHelper(const_cast<Class*>(this), a_pInstance, const_cast<Class*>(this), a_pInstance, &ac, a_uiLevel);
    installInstanceDataMembers(a_pInstance, a_uiLevel);
    state::StateMachine* pStateMachine = getStateMachineCascade();
    if(pStateMachine)
    {
        pStateMachine->install(cast(pStateMachine->getOwnerClass(), a_pInstance));
    }
}

void Class::uninstall( void* a_pInstance, size_t a_uiLevel ) const
{
    state::StateMachine* pStateMachine = getStateMachineCascade();
    if(pStateMachine)
    {
        pStateMachine->uninstall(cast(pStateMachine->getOwnerClass(), a_pInstance));
    }
    uninstallInstanceDataMembers(a_pInstance, a_uiLevel);
    UninstallHelper(a_pInstance, const_cast<Class*>(this), a_uiLevel);
    connection::slot_pool::eraseAllocationController(a_pInstance, const_cast<Class*>(this));
}

VirtualMemberFunctionTable* Class::deriveVirtualMemberFunctionTable( VirtualMemberFunctionTable* a_pVirtualMemberFunctionTable ) const
{
    return a_pVirtualMemberFunctionTable->derive();
}

VirtualMemberFunctionTable* Class::createVirtualMemberFunctionTable() const
{
    return o_new(VirtualMemberFunctionTable);
}

size_t Class::getVirtualMemberFunctionCount( size_t a_uiOffset ) const
{
    for(auto it = beginVirtualMemberFunctionsTables(); it != endVirtualMemberFunctionsTables(); ++it)
    {
        if((*it)->getOffset() == a_uiOffset)
            return (*it)->getMemberFunctionCount();
    }
    return 0;
}

void Class::addNewVirtualMemberFunctionTable()
{
    o_assert(NOT(testModifiers(o_native))
        AND m_VirtualMemberFunctionTables.empty() 
        AND ( (getSuperClassCount() == 0) OR NOT(getSuperClass(0)->isPolymorphic()) )
    ); 
    m_VirtualMemberFunctionTables.push_back(createVirtualMemberFunctionTable());
    addElement(m_VirtualMemberFunctionTables.back());
}

bool Class::hasNewVTable() const
{
    return static_cast<extra_data*>(m_pExtraData)->m_bHasVTablePtr;
}

o_namespace_end(phantom, reflection)
