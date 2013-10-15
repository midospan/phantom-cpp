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


Class::Class(const string& a_strName, bitfield a_bfModifiers)
: ClassType(a_strName, a_bfModifiers)
, m_uiRegisteredInstances(0)
, m_pStateMachine(NULL)
{
}

Class::Class(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_bfModifiers)
: ClassType(a_strName, a_uiSize, a_uiAlignment, a_bfModifiers)
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



Attribute* Class::getAttributeCascade( const string& a_strName) const
{
    Attribute* pAttribute = getAttribute(a_strName);
    if(pAttribute != NULL) return pAttribute;
    o_foreach(Class* pClass, m_SuperClasses)
    {
        Attribute* pSuperAttribute = pClass->getAttributeCascade(a_strName);
        if(pSuperAttribute != NULL)
        {
            if(pAttribute != NULL) 
            {
                // ambiguous access, so we return nothing
                return NULL;
            }
            pAttribute = pSuperAttribute;
        }
    }
    return pAttribute;
}



InstanceAttribute* Class::getInstanceAttributeCascade( const string& a_strName ) const
{
    InstanceAttribute* pAttribute = getInstanceAttribute(a_strName);
    if(pAttribute != NULL) return pAttribute;
    o_foreach(Class* pClass, m_SuperClasses)
    {
        InstanceAttribute* pSuperAttribute = pClass->getInstanceAttributeCascade(a_strName);
        if(pSuperAttribute != NULL)
        {
            if(pAttribute != NULL) 
            {
                // ambiguous access, so we return nothing
                return NULL;
            }
            pAttribute = pSuperAttribute;
        }
    }
    return pAttribute;
}

StaticAttribute* Class::getStaticAttributeCascade( const string& a_strName ) const
{
    StaticAttribute* pAttribute = getStaticAttribute(a_strName);
    if(pAttribute != NULL) return pAttribute;
    o_foreach(Class* pClass, m_SuperClasses)
    {
        StaticAttribute* pSuperAttribute = pClass->getStaticAttributeCascade(a_strName);
        if(pSuperAttribute != NULL)
        {
            if(pAttribute != NULL) 
            {
                // ambiguous access, so we return nothing
                return NULL;
            }
            pAttribute = pSuperAttribute;
        }
    }
    return pAttribute;
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
    InstanceMethod* pMethod = getInstanceMethod(a_strIdentifierString);
    if(pMethod != NULL AND pMethod->isSignal()) return static_cast<Signal*>(pMethod);
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

InstanceMethod* Class::getSlot( const string& a_strIdentifierString ) const
{
    InstanceMethod* pMethod = getInstanceMethod(a_strIdentifierString);
    if(pMethod != NULL AND pMethod->isSlot()) return pMethod;
    return NULL;
}

InstanceMethod* Class::getSlotCascade( const string& a_strIdentifierString ) const
{
    InstanceMethod* pSlot = getSlot(a_strIdentifierString);
    if(pSlot != NULL) return pSlot;
    o_foreach(Class* pClass, m_SuperClasses)
    {
        InstanceMethod* pSuperSlot = pClass->getSlotCascade(a_strIdentifierString);
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

    member_collection::const_iterator it = m_Members.lower_bound(classOf<Property>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<Property>());
    for(; it != end; ++it)
    {
        if(it->second->isInstanceAttribute())
        {
            InstanceAttribute* pInstanceAttribute = static_cast<InstanceAttribute*>(it->second);
            Type*    pAttributeType = pInstanceAttribute->getValueType();
            if(pAttributeType->isClass())
            {
                if(*static_cast<void**>(pInstanceAttribute->getAddress(a_pInstance)) == a_pOther) 
                    return true;
            }
        }
    }
    return false;
}

InstanceMethod** Class::getVfTable() const
{
    for(uint i=0; i<getVirtualMethodTableCount(); ++i)
    {
        VirtualMethodTable* pVTable = getVirtualMethodTable(i);
        if(pVTable->getBaseClass() == this)
        {
            return pVTable->getMethods();
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

void Class::setupVirtualMethodTables() const
{
    if(NOT(m_VirtualMethodTables.empty()))
        return;

    if(m_SuperClasses.empty())
    {
        instance_method_list methods;
        member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMethod>());
        member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMethod>());
        for(;it != end; ++it)
        {
            InstanceMethod* pMethod = static_cast<InstanceMethod*>(it->second);
            if(pMethod->isVirtual())
                methods.push_back(pMethod);
        }
        m_VirtualMethodTables.push_back(o_new(VirtualMethodTable)(const_cast<Class*>(this), &methods));
        return;
    }

    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        Class* pSuperType = it->m_pClass;
        pSuperType->setupVirtualMethodTables();

        uint i = 0;
        for(;i<pSuperType->getVirtualMethodTableCount(); ++i)
        {
            instance_method_list methods;
            instance_method_list rootMethods;
            sortSuperAndRootMethods(pSuperType->getVirtualMethodTable(i), &methods, &rootMethods);
            if(it == m_SuperClasses.begin() AND i == 0) // Common branch
            {
                methods.insert(methods.end(), rootMethods.begin(), rootMethods.end());
                m_VirtualMethodTables.push_back(o_new(VirtualMethodTable)(const_cast<Class*>(this), &methods));
            }
            else
            {
                m_VirtualMethodTables.push_back(o_new(VirtualMethodTable)(pSuperType->getVirtualMethodTable(i)->getBaseClass(), &methods));
            }
        }
    }
}

void Class::homonymousMethodSearch( method_search_data* a_pMethodRequest )
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMethod>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMethod>());

    for(;it != end; ++it)
    {
        InstanceMethod*    pMethod = static_cast<InstanceMethod*>(it->second);
        if(pMethod->getName() == a_pMethodRequest->getMethodName())
        {
            if(pMethod->getSignature()->getParameterCount() == a_pMethodRequest->getMethodSignature()->getParameterCount())
            {
                uint i = 0;
                boolean bIncompatibleParameterFound = false;
                for(;i<pMethod->getSignature()->getParameterCount();++i)
                {
                    if(pMethod->getSignature()->getParameterType(i) != a_pMethodRequest->getMethodSignature()->getParameterType(i))
                    {
                        bIncompatibleParameterFound = true;
                        break;
                    }
                }
                if(bIncompatibleParameterFound)
                {
                    a_pMethodRequest->populateWithResult(method_search_data::eResultType_IncompatibleParameterType, pMethod);
                    continue;
                }
                Type* pCurrentReturnType = pMethod->getSignature()->getReturnType();
                Type* pRequestReturnType = a_pMethodRequest->getMethodSignature()->getReturnType();
                if(pCurrentReturnType == pRequestReturnType)
                {
                    a_pMethodRequest->populateWithResult(method_search_data::eResultType_PerfectMatch, pMethod);
                }
                else if(pCurrentReturnType->isClass())
                {
                    if(NOT(pRequestReturnType->isClass()))
                    {
                        a_pMethodRequest->populateWithResult(method_search_data::eResultType_IncompatibleReturnType, pMethod);
                    }
                    else if( ((Class*)pCurrentReturnType)->isKindOf((Class*)pRequestReturnType) )
                    {
                        a_pMethodRequest->populateWithResult(method_search_data::eResultType_CovariantMatch, pMethod);
                    }
                    else if( ((Class*)pRequestReturnType)->isKindOf((Class*)pCurrentReturnType) )
                    {
                        a_pMethodRequest->populateWithResult(method_search_data::eResultType_ContravariantMatch, pMethod);
                    }
                }
                else
                {
                    a_pMethodRequest->populateWithResult(method_search_data::eResultType_IncompatibleReturnType, pMethod);
                }
            }
            else
            {
                a_pMethodRequest->populateWithResult(method_search_data::eResultType_IncompatibleParameterCount, pMethod);
            }
        }
    }
}

void Class::sortSuperAndRootMethods( VirtualMethodTable* a_pSuperVMT, instance_method_list* a_OutSuperMethods, instance_method_list* a_OutRootMethods ) const
{
    uint i = 0;
    for(; i<a_pSuperVMT->getSize(); ++i)
    {
        InstanceMethod* pSuperMethod = a_pSuperVMT->getMethod(i);
        member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMethod>());
        member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMethod>());
        for(;it != end; ++it)
        {
            InstanceMethod* pMethod = static_cast<InstanceMethod*>(it->second);
            if(pMethod->isVirtual())
            {
                InstanceMethod::EOverloadRelation eIR = (static_cast<InstanceMethod*>(pMethod))->getOverloadRelationWith(pSuperMethod);
                o_assert(        eIR != InstanceMethod::e_OverloadRelation_Contravariant
                                    AND eIR != InstanceMethod::e_OverloadRelation_Forbidden);
                if(eIR == InstanceMethod::e_OverloadRelation_None)
                {
                    a_OutRootMethods->push_back(pMethod);
                }
                else
                {
                    a_OutSuperMethods->push_back(pMethod);
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

void     Class::getInvokableMethodsCascade(const string& a_strName, const vector<Type*>& a_ArgumentTypeList, Method** a_pOutPerfectMatchMethod, method_vector* a_pResultMethods)
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMethod>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMethod>());
    for(;it != end; ++it)
    {
        InstanceMethod*    pMethod = static_cast<InstanceMethod*>(it->second);
        Signature*    pSignature    = pMethod->getSignature();

        // Method name incompatibility => we skip
        if(pMethod->getName() != a_strName)
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

            // If one parameter type doesn't match perfectly, method doesn't perfectly match
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
        AND *a_pOutPerfectMatchMethod == NULL)
        {
            *a_pOutPerfectMatchMethod = pMethod;
        }
        if(NOT(bMatch)) continue;

        // We check if the method hasn't already been added in result methods ; if not, we add it
        boolean bAlreadyAdded = false;
        method_vector::iterator it_alreadyAdded =  a_pResultMethods->begin();
        for(; it_alreadyAdded != a_pResultMethods->end(); ++it_alreadyAdded)
        {
            if((*it_alreadyAdded) == pMethod)
            {
                bAlreadyAdded = true;
                break;
            }
        }
        if(NOT(bAlreadyAdded))
            a_pResultMethods->push_back(static_cast<InstanceMethod*>(it->second));
    }

    // We browse the super types and treat recursively
    super_class_table::iterator it_super = m_SuperClasses.begin();
    super_class_table::iterator it_super_end = m_SuperClasses.end();
    for(;it_super != it_super_end; ++it_super)
    {
        it_super->m_pClass->getInvokableMethodsCascade(a_strName, a_ArgumentTypeList, a_pOutPerfectMatchMethod, a_pResultMethods);
    }
}

void Class::findOverloadedMethods( InstanceMethod* a_pOverloadCandidate, vector<InstanceMethod*>& a_Result )
{
    member_collection::const_iterator it_method = m_Members.lower_bound(classOf<InstanceMethod>());
    member_collection::const_iterator it_method_end = m_Members.upper_bound(classOf<InstanceMethod>());
    for(;it_method!=it_method_end;++it_method)
    {
        if(it_method->second == a_pOverloadCandidate) continue;
        if(a_pOverloadCandidate->canOverload(static_cast<InstanceMethod*>(it_method->second)))
        {
            bool bOverloadedAlreadyAddedForCurrentVTable = false;
            vector<InstanceMethod*>::const_iterator it_result = a_Result.begin();
            vector<InstanceMethod*>::const_iterator end_result = a_Result.end();
            for(;it_result!=end_result;++it_result)
            {
                InstanceMethod* pResult = (*it_result);
                o_assert(pResult->getOwnerClass());
                if( pResult->getOwnerClass()->getSuperClassOffsetCascade((Class*)this) == 0 // in the same vtable
                    AND pResult->canOverload(static_cast<InstanceMethod*>(it_method->second)))  // a result method can overload the current tested method, 
                                                                                                // which means that for the current VTable, 
                                                                                                // we already have found an overloaded method
                {
                    bOverloadedAlreadyAddedForCurrentVTable = true;
                    break;
                }
            }
            if(NOT(bOverloadedAlreadyAddedForCurrentVTable))
            {
                a_Result.push_back(static_cast<InstanceMethod*>(it_method->second));
            }
        }
    }
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        it->m_pClass->findOverloadedMethods(a_pOverloadCandidate, a_Result);
    }
}

boolean Class::acceptMethod( const string& a_strName, Signature* a_pSignature, method_vector* a_pOutConflictingMethods ) const
{
    boolean bResult = true;
    {
        member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMethod>());
        member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMethod>());
        for(; it != end; ++it)
        {
            InstanceMethod* pInstanceMethod = static_cast<InstanceMethod*>(it->second);
            InstanceMethod::EOverloadRelation eOR = pInstanceMethod->getOverloadRelationWith(a_strName, a_pSignature);
            if(eOR != InstanceMethod::e_OverloadRelation_None)
            {
                if(a_pOutConflictingMethods) a_pOutConflictingMethods->push_back(pInstanceMethod);
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
            if(NOT(it->m_pClass->acceptsOverloadedMethod(a_strName,a_pSignature, a_pOutConflictingMethods)))
            {
                return false;
            }
        }
    }
    return true;
}

boolean Class::acceptsOverloadedMethod( const string& a_strName, Signature* a_pSignature, method_vector* a_pOutConflictingMethods ) const
{
    method_vector prevMethods;
    boolean bResult = true;
    {
        super_class_table::const_iterator it = m_SuperClasses.begin();
        super_class_table::const_iterator end = m_SuperClasses.end();
        for(;it != end; ++it)
        {
            if(NOT(it->m_pClass->acceptsOverloadedMethod(a_strName, a_pSignature, &prevMethods)))
            {
                bResult = false;
            }
        }
    }

    {
        member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMethod>());
        member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMethod>());
        for(; it != end; ++it)
        {
            InstanceMethod* pInstanceMethod = static_cast<InstanceMethod*>(it->second);
            InstanceMethod::EOverloadRelation eOR = pInstanceMethod->getOverloadRelationWith(a_strName, a_pSignature);
            if(eOR == InstanceMethod::e_OverloadRelation_Forbidden
                OR eOR == InstanceMethod::e_OverloadRelation_Covariant)
            {
                a_pOutConflictingMethods->push_back(pInstanceMethod);
                return false;
            }
        }
    }
    {
        method_vector::iterator it = prevMethods.begin();
        for(;it != prevMethods.end(); ++it)
        {
            a_pOutConflictingMethods->push_back(*it);
        }
    }

    return bResult;
}

void Class::filtersNonOverloadedAbstractMethodsCascade( instance_method_vector& a_Result ) const
{
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(; it != end; ++it)
    {
        it->m_pClass->filtersNonOverloadedAbstractMethodsCascade(a_Result);
    }
    phantom::list<instance_method_vector::iterator> toRemove;
    instance_method_vector::iterator it_abs = a_Result.begin();
    for(;it_abs != a_Result.end(); ++it_abs)
    {
        InstanceMethod* pAbstractMethod = *it_abs;
        member_collection::const_iterator it_met = m_Members.lower_bound(classOf<InstanceMethod>());
        member_collection::const_iterator it_met_end = m_Members.upper_bound(classOf<InstanceMethod>());
        for(; it_met != it_met_end; ++it_met)
        {
            InstanceMethod* pMethod = static_cast<InstanceMethod*>(it_met->second);
            if(pMethod->isAbstract()) continue;
            InstanceMethod::EOverloadRelation eOR = pMethod->getOverloadRelationWith(pAbstractMethod);
            o_assert(eOR != InstanceMethod::e_OverloadRelation_Forbidden);
            if(eOR != InstanceMethod::e_OverloadRelation_None)
            {
                toRemove.push_back(it_abs);
                break;
            }
        }
    }
    phantom::list<instance_method_vector::iterator>::iterator it_rem = toRemove.begin();
    phantom::list<instance_method_vector::iterator>::iterator it_rem_end = toRemove.end();
    for(; it_rem != it_rem_end; ++it_rem)
    {
        a_Result.erase(*it_rem);
    }

    findAbstractMethods(a_Result);
}

void Class::findAbstractMethods( instance_method_vector& a_Result ) const
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMethod>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMethod>());
    for(; it != m_Members.end(); ++it)
    {
        InstanceMethod* pMethod = static_cast<InstanceMethod*>(it->second);
        if(pMethod->isAbstract())
        {
            a_Result.push_back(pMethod);
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

StaticMethod*    Class::getStaticMethodCascade( const string& a_strIdentifierString ) const
{
    StaticMethod* pMethod = getStaticMethod(a_strIdentifierString);
    if(pMethod != NULL) return pMethod;
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        pMethod = it->m_pClass->getStaticMethodCascade(a_strIdentifierString);
        if(pMethod != NULL)
            return pMethod;
    }
    return NULL;
}

InstanceMethod*    Class::getInstanceMethodCascade( const string& a_strIdentifierString ) const
{
    InstanceMethod* pMethod = getInstanceMethod(a_strIdentifierString);
    if(pMethod != NULL) return pMethod;
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        pMethod = it->m_pClass->getInstanceMethodCascade(a_strIdentifierString);
        if(pMethod != NULL)
            return pMethod;
    }
    return NULL;
}

Method* Class::getMethodCascade( const string& a_strIdentifierString ) const
{
    Method* pMethod = getMethod(a_strIdentifierString);
    if(pMethod != NULL) return pMethod;
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        pMethod = it->m_pClass->getMethodCascade(a_strIdentifierString);
        if(pMethod != NULL)
            return pMethod;
    }
    return NULL;
}

Method* Class::getMethodCascade(const string& a_strName, function_signature const* a_FunctionSignature, bitfield a_bfModifiers /*= bitfield()*/) const
{
    Method* pMethod = getMethod(a_strName, a_FunctionSignature, a_bfModifiers);
    if(pMethod != NULL) return pMethod;
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        pMethod = it->m_pClass->getMethodCascade(a_strName, a_FunctionSignature, a_bfModifiers);
        if(pMethod != NULL)
            return pMethod;
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


Property* Class::getPropertyCascade(const string& a_strIdentifierString) const
{
    Property* pFound = getProperty(a_strIdentifierString);
    if(pFound != NULL) return pFound;

    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        Property* pProperty = it->m_pClass->getPropertyCascade(a_strIdentifierString);
        if(pProperty != nullptr)
            return pProperty;
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


void Class::getAllPropertyCascade(vector<Property*>& out) const
{
    getAllProperty(out);
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        it->m_pClass->getAllPropertyCascade(out);
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


InstanceMethod* Class::getInstanceMethodCascade( const string& a_strName, type_vector* a_pParameterTypes ) const
{
    member_collection::const_iterator it = m_Members.lower_bound(classOf<InstanceMethod>());
    member_collection::const_iterator end = m_Members.upper_bound(classOf<InstanceMethod>());
    for(;it != end; ++it)
    {
        InstanceMethod* pMethod = static_cast<InstanceMethod*>(it->second);

        Signature* pSignature = pMethod->getSignature();

        // Method name incompatibility => we skip
        if(pMethod->getName() != a_strName)
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

        return pMethod;
    }
    {
        super_class_table::const_iterator it = m_SuperClasses.begin();
        super_class_table::const_iterator end = m_SuperClasses.end();
        for(;it != end; ++it)
        {
            InstanceMethod* pResultMethod = it->m_pClass->getInstanceMethodCascade(a_strName, a_pParameterTypes);
            if(pResultMethod != NULL)
                return pResultMethod;
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


void Class::valueToString( string& s, void* src ) const
{
    o_exception(exception::unsupported_method_exception, "TODO (not supported yet)");
}

void Class::valueFromString( const string& cs, void* dest ) const
{
    o_exception(exception::unsupported_method_exception, "TODO (not supported yet)");
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

InstanceMethod*        Class::getInstanceMethodCascade(const char* a_strName, function_signature const* a_FunctionSignature, bitfield a_bfModifiers /*= bitfield()*/) const
{
  InstanceMethod* pMethod = getInstanceMethod(a_strName, a_FunctionSignature, a_bfModifiers);
  if(pMethod != NULL) return pMethod;
  super_class_table::const_iterator it = m_SuperClasses.begin();
  super_class_table::const_iterator end = m_SuperClasses.end();
  for(;it != end; ++it)
  {
    pMethod = it->m_pClass->getInstanceMethodCascade(a_strName, a_FunctionSignature, a_bfModifiers);
    if(pMethod != NULL) return pMethod;
  }
  return NULL;
}

LanguageElement* Class::getElement(
    const char* a_strName 
    , template_specialization const* a_TemplateSpecialization
    , function_signature const* a_FunctionSignature
    , bitfield a_bfModifiers /*= bitfield()*/) const 
{
    LanguageElement* pElement = ClassType::getElement(a_strName, a_TemplateSpecialization, a_FunctionSignature, a_bfModifiers);
    if(pElement) return pElement;
    super_class_table::const_iterator it = m_SuperClasses.begin();
    super_class_table::const_iterator end = m_SuperClasses.end();
    for(;it != end; ++it)
    {
        if(pElement = it->m_pClass->getElement(a_strName, a_TemplateSpecialization, a_FunctionSignature, a_bfModifiers))
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
            vmt_vector::iterator it = m_VirtualMethodTables.begin();
            for(;it!=m_VirtualMethodTables.end();it++)
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
    vector<Property*> properties;
    pSourceClass->getAllPropertyCascade(properties);
    auto it = properties.begin();
    auto end = properties.end();
    for(; it!=end; ++it)
    {
        Property* pOldProperty = (*it);
        Property* pNewProperty = getPropertyCascade(pOldProperty->getName());
        Type* pOldPropertyType = pOldProperty->getValueType()->removeReference()->removeConst();
        Type* pNewPropertyType = nullptr;
        if(pNewProperty != nullptr 
            AND pOldPropertyType->isImplicitlyConvertibleTo((pNewPropertyType = pNewProperty->getValueType()->removeReference()->removeConst())))
        {
            // Create temp buffers
            void* sourceBuffer = pOldPropertyType->newInstance();
            void* newBuffer = pNewPropertyType->newInstance();
            
            // Apply conversion
            pOldProperty->getValue(pSourceClass->cast(pOldProperty->getOwnerClass(), (void*)a_pSource), sourceBuffer);
            pOldPropertyType->convertValueTo(pNewPropertyType, newBuffer, sourceBuffer);
            pNewProperty->setValue(cast(pNewProperty->getOwnerClass(), a_pInstance), newBuffer);

            // Destroy temp buffers
            pOldPropertyType->deleteInstance(sourceBuffer);
            pNewPropertyType->deleteInstance(newBuffer);
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

o_cpp_end
