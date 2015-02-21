/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/MemberFunction.h>
#include <phantom/reflection/MemberFunction.hxx>
#include <phantom/reflection/Block.h>
#include <phantom/reflection/LocalVariable.h>
#include <phantom/reflection/Compiler.h>
#include <phantom/vector.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), MemberFunction);
o_registerNTI((phantom), vector, (phantom::reflection::MemberFunction*));

o_namespace_begin(phantom, reflection) 

Class* const MemberFunction::metaType = o_type_of(MemberFunction);

MemberFunction::MemberFunction(modifiers_t a_Modifiers /*= 0*/)
    : Subroutine(e_thiscall, a_Modifiers)
    , m_uiVirtualTableIndex(~size_t(0))
    , m_pVTableClosures(nullptr)
{
}

MemberFunction::MemberFunction(const string& a_strName, Signature* a_pSignature, modifiers_t a_Modifiers /*= 0*/ )
    : Subroutine(a_strName
                , a_pSignature
                , e_thiscall
                , a_Modifiers & ~o_noconst )
    , m_uiVirtualTableIndex(~size_t(0))
    , m_pVTableClosures(nullptr)
{
    if(testModifiers(o_const) AND testModifiers(o_slot_member_function))
    {
        o_exception(exception::reflection_runtime_exception, "Slots cannot be const");
    }
}

MemberFunction::MemberFunction( ClassType* a_pClassType, const string& a_strName, const string& a_strSignature, modifiers_t a_Modifiers /*= 0*/ )
    : Subroutine(a_pClassType, a_strName
    , a_strSignature
    , e_thiscall
    , (a_Modifiers & ~o_noconst) )
    , m_uiVirtualTableIndex(~size_t(0))
    , m_pVTableClosures(nullptr)
{
    if(testModifiers(o_const) AND testModifiers(o_slot_member_function))
    {
        o_exception(exception::reflection_runtime_exception, "Slots cannot be const");
    }
}

MemberFunction::~MemberFunction()
{
    delete m_pVTableClosures;
}

bool MemberFunction::canOverride( MemberFunction* a_pMemberFunction ) const
{
    if(NOT(a_pMemberFunction->isVirtual())) 
        return false;
    ESignatureRelation r = getSignatureRelationWith(a_pMemberFunction);
    return (r == e_SignatureRelation_Covariant) OR (r == e_SignatureRelation_Equal);
}

bool MemberFunction::canOverride( const string& a_strName, Signature* a_pSignature, modifiers_t a_Modifiers ) const
{
    ESignatureRelation r = getSignatureRelationWith(a_strName, a_pSignature, a_Modifiers);
    return (r == e_SignatureRelation_Covariant) OR (r == e_SignatureRelation_Equal);
}

void MemberFunction::safeCall( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const
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

void MemberFunction::safePlacementCall( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const
{
    reflection::Class* pOwnerClass = m_pOwner->asClass();
    if(pOwnerClass)
    {
        const rtti_data& rttiData = phantom::rttiDataOf(a_pCallerAddress);
        placementCall( rttiData.cast(pOwnerClass), a_pArgs, a_pReturnAddress);
    }
    else
    {
        placementCall( a_pCallerAddress, a_pArgs, a_pReturnAddress);
    }
}

void MemberFunction::safeCall( void* a_pCallerAddress, void** a_pArgs ) const
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
jit_function MemberFunction::getVTableFunction( size_t a_uiThisOffset ) const
{
    o_assert(m_jit_function.function, "Closure not yet created, you must add this MemberFunction to a Class"); 
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
    //a_pMemberFunction->setVTableOffsetFixClosure[a_uiThisOffset] = func;
    return func;
}*/

void MemberFunction::setVirtual()
{
    if(isVirtual()) return;
    if(m_pOwner)
    {
        o_exception(exception::reflection_runtime_exception, "Member function cannot be set to virtual after being added to a class type")
    }
    m_Modifiers |= o_virtual;
}

void* MemberFunction::getVTableClosure( size_t a_uiOffset ) const
{
    if(m_pVTableClosures == nullptr) return nullptr;
    auto found = m_pVTableClosures->find(a_uiOffset);
    return (found == m_pVTableClosures->end()) 
        ? nullptr 
        : found->second;
}

void MemberFunction::setVTableClosure( size_t a_uiOffset, void* a_pClosure )
{
    o_assert(!testModifiers(o_native));
    if(m_pVTableClosures == nullptr)
    {
        m_pVTableClosures = new map<size_t, void*>;
    }
    (*m_pVTableClosures)[a_uiOffset] = a_pClosure;
}

void MemberFunction::getOriginalOverriddenMemberFunctions( vector<MemberFunction*>& a_Out ) const
{
    Class* pClass = getOwnerClass();
    if(pClass == nullptr) return;
    for(auto it = pClass->beginVirtualMemberFunctionsTables(); it != pClass->endVirtualMemberFunctionsTables(); ++it)
    {
        MemberFunction* pRootMemberFunction = (*it)->getRootMemberFunction(const_cast<MemberFunction*>(this));
        if(pRootMemberFunction) a_Out.push_back(pRootMemberFunction);
    }
}

Block* MemberFunction::createBlock()
{
    return Subroutine::createBlock(o_new(LocalVariable)(
        isConst() 
        ? m_pOwner->asClassType()->constType()->pointerType()->constType()
        : m_pOwner->asClassType()->pointerType()->constType(), "this"));
}

bool MemberFunction::acceptsObjectExpressionType( Type* a_pType ) const
{
    modifiers_t qualifiers = 0;
    a_pType = a_pType->removeQualifiers();
    if(a_pType->asLValueReferenceType())
    {
        qualifiers |= o_lvalue_ref;
        a_pType = static_cast<LValueReferenceType*>(a_pType);
    }
    else 
    {
        qualifiers |= o_rvalue_ref;
        a_pType = static_cast<RValueReferenceType*>(a_pType);
    }
    if(a_pType->asConstType())
    {
        qualifiers |= o_const;
    }
    return acceptsObjectExpressionQualifiers(qualifiers);
}

bool MemberFunction::acceptsObjectExpressionQualifiers( modifiers_t a_CallerQualifiers ) const
{
    o_assert((a_CallerQualifiers&(~(o_ref_qualifiers_mask|o_const))) == 0);
    o_assert(((a_CallerQualifiers&o_lvalue_ref) == o_lvalue_ref) ^ ((a_CallerQualifiers&o_rvalue_ref) == o_rvalue_ref));
    return (((a_CallerQualifiers&o_const) == o_const) <= ((m_Modifiers&o_const) == o_const)) // caller must be equally or less const qualified than member function (every one can call a const member function but a const cannot call a non const member function)
        AND (((m_Modifiers&(o_ref_qualifiers_mask)) == 0) 
        OR (m_Modifiers&o_ref_qualifiers_mask) == (a_CallerQualifiers&o_ref_qualifiers_mask));
}

Type* MemberFunction::getImplicitObjectParameterType() const
{
    Type* pImplicitObjectParameterType = getOwner()->asClassType();
    if(m_Modifiers&o_const)
    {
        pImplicitObjectParameterType = pImplicitObjectParameterType->constType();
    }
    if(m_Modifiers&o_rvalue_ref)
    {
        return pImplicitObjectParameterType->rvalueReferenceType();
    }
    return pImplicitObjectParameterType->lvalueReferenceType();
}

o_namespace_end(phantom, reflection) 