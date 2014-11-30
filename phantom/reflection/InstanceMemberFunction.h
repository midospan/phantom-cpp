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

#ifndef o_phantom_reflection_InstanceMemberFunction_h__
#define o_phantom_reflection_InstanceMemberFunction_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Subroutine.h>
#include <phantom/reflection/MemberFunction.h>
/* *********************************************** */

o_namespace_begin(phantom, reflection)
    
class o_export InstanceMemberFunction : public Subroutine, public MemberFunction
{
    friend class Class;
    friend class ClassType;
    friend class Structure;
    friend class VirtualMemberFunctionTable;

public:
    enum EOverrideRelation
    {
        e_OverrideRelation_None = 0,
        e_OverrideRelation_Equal,
        e_OverrideRelation_Covariant,
        e_OverrideRelation_Contravariant,
        e_OverrideRelation_Forbidden,
    };
    static Class* const metaType;

public:
    InstanceMemberFunction();
    InstanceMemberFunction(const string& a_strName, Signature* a_pSignature, modifiers_t a_Modifiers = 0);
    ~InstanceMemberFunction();

    reflection::ClassType*              getOwnerClassType() const { return static_cast<reflection::ClassType*>(m_pOwner); }
    reflection::Class*                  getOwnerClass() const { return static_cast<reflection::ClassType*>(m_pOwner)->asClass(); }

    virtual void                        call( void* a_pCallerAddress, void** a_pArgs ) const { Subroutine::call(a_pCallerAddress, a_pArgs); }
    virtual void                        call( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const { Subroutine::call(a_pCallerAddress, a_pArgs, a_pReturnAddress); }
    virtual void                        call( void** a_pArgs ) const { Subroutine::call(a_pArgs); }
    virtual void                        call( void** a_pArgs, void* a_pReturnAddress ) const { Subroutine::call(a_pArgs, a_pReturnAddress); }
    void                                safeCall( void* a_pCallerAddress, void** a_pArgs ) const;
    void                                safeCall( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const;

    bool                                canOverride(InstanceMemberFunction* a_pInstanceMemberFunction) const;
    bool                                canOverride(const string& a_strName, Signature* a_pSignature) const;
    EOverrideRelation                   getOverrideRelationWith(const string& a_strName, Signature* a_pSignature) const;
    EOverrideRelation                   getOverrideRelationWith(InstanceMemberFunction* a_pMemberFunction) const;

    virtual InstanceMemberFunction*     asSlot() const { return (((m_Modifiers & o_slot_member_function) == o_slot_member_function)) ? const_cast<InstanceMemberFunction*>(this) : nullptr; }
    virtual LanguageElement*            asLanguageElement() const { return const_cast<InstanceMemberFunction*>(this); }
    virtual Subroutine*                 asSubroutine() const { return const_cast<InstanceMemberFunction*>(this); }
    virtual InstanceMemberFunction*     asInstanceMemberFunction() const { return const_cast<InstanceMemberFunction*>(this); }
    virtual MemberFunction*             asMemberFunction() const { return const_cast<InstanceMemberFunction*>(this); }

    size_t                              getVirtualTableIndex() const { return m_uiVirtualTableIndex; }
    
    void                                setVirtual();

    virtual variant                     compile(Compiler* a_pCompiler);

    virtual void*                       getVTableClosure(size_t a_uiOffset) const;

    void                                setVTableClosure(size_t a_uiOffset, void* a_pClosure);

    void                                getOriginalOverriddenMemberFunctions(vector<InstanceMemberFunction*>& a_Out) const;

protected:
    InstanceMemberFunction(const string& a_strName, Signature* a_pSignature, modifiers_t a_Modifiers, int);
    virtual void                        setVirtualTableIndex(int index)
    { 
        o_assert(m_uiVirtualTableIndex == ~size_t(0)); 
        m_uiVirtualTableIndex = index; 
    }

    void ancestorChanged(LanguageElement* a_pOwner);

protected:
    size_t              m_uiVirtualTableIndex;
    map<size_t, void*>* m_pVTableClosures;

/// -----------------------
};

o_namespace_end(phantom, reflection)



#endif
