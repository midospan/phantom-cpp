/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/MemberFunctionPointerType.h>
#include <phantom/reflection/MemberFunctionPointerType.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), MemberFunctionPointerType);

o_namespace_begin(phantom, reflection) 

o_invalid_def(MemberFunctionPointerType, ClassType::Invalid(), Signature::Invalid(), o_invalid);

o_define_meta_type(MemberFunctionPointerType);

MemberFunctionPointerType::MemberFunctionPointerType( ClassType* a_pObjectType, Signature* a_pSignature, modifiers_t a_Modifiers )
    : MemberPointerType(a_pObjectType
    , sizeof(MemberFunction*)
    , boost::alignment_of<MemberFunction*>::value
    , a_Modifiers)    
    , m_pSignature(a_pSignature)
{
    o_assert(!isNative());
    addElement(m_pSignature);
}

MemberFunctionPointerType::MemberFunctionPointerType( ClassType* a_pObjectType, Signature* a_pSignature, size_t a_Size, size_t a_Alignment, modifiers_t a_Modifiers ) 
: MemberPointerType(a_pObjectType
            , a_Size
            , a_Alignment
            , a_Modifiers)    
            , m_pSignature(a_pSignature)
{
    o_assert(isNative());
    addElement(m_pSignature);
}

MemberFunctionPointerType::~MemberFunctionPointerType()
{

}

void MemberFunctionPointerType::referencedElementRemoved( LanguageElement* a_pElement )
{
    Type::referencedElementRemoved(a_pElement);
    if(m_pObjectType == a_pElement)
    {
        m_pObjectType = nullptr;
    }
}

void MemberFunctionPointerType::valueToLiteral( string& a_str, const void* src ) const
{
    o_exception(exception::base_exception, "valueToLiteral not defined for member function pointer types");
}

void MemberFunctionPointerType::valueToString( string& a_str, const void* src ) const
{
    o_exception(exception::base_exception, "valueToString not defined for member function pointer types");
}

void MemberFunctionPointerType::valueFromString( const string& a_str, void* dest ) const
{
    o_exception(exception::base_exception, "valueFromString not defined for member function pointer types");
}

void MemberFunctionPointerType::copy( void* a_pDest, void const* a_pSrc ) const
{
    memcpy(a_pDest, a_pSrc, m_uiSize);
}

void* MemberFunctionPointerType::getClosure( void* a_pPointer ) const
{
    return static_cast<MemberFunction*>(a_pPointer)->getClosure();
}

void MemberFunctionPointerType::call( void* a_pPointer, void* a_pThis, void** a_pArgs ) const
{
    o_assert(as<MemberFunction*>(a_pPointer));
    static_cast<MemberFunction*>(a_pPointer)->call(a_pThis, a_pArgs);
}

void MemberFunctionPointerType::call( void* a_pPointer, void* a_pThis, void** a_pArgs, void* a_pReturnAddress ) const
{
    o_assert(as<MemberFunction*>(a_pPointer));
    static_cast<MemberFunction*>(a_pPointer)->call(a_pThis, a_pArgs, a_pReturnAddress);
}

void MemberFunctionPointerType::implicitConversions( const vector<Type*>& a_FunctionSignature, LanguageElement* a_pContextScope, conversions& a_ImplicitConversions ) const
{
    m_pSignature->implicitConversions(a_FunctionSignature, a_pContextScope, a_ImplicitConversions);
}

void MemberFunctionPointerType::implicitConversions( const vector<Expression*>& a_Arguments, LanguageElement* a_pContextScope, conversions& a_ImplicitConversions ) const
{
    m_pSignature->implicitConversions(a_Arguments, a_pContextScope, a_ImplicitConversions);
}

void MemberFunctionPointerType::implicitConversions( Language* a_pLanguage, const vector<Type*>& a_FunctionSignature, LanguageElement* a_pContextScope, conversions& a_ImplicitConversions ) const
{
    m_pSignature->implicitConversions(a_pLanguage, a_FunctionSignature, a_pContextScope, a_ImplicitConversions);
}

void MemberFunctionPointerType::implicitConversions( Language* a_pLanguage, const vector<Expression*>& a_Arguments, LanguageElement* a_pContextScope, conversions& a_ImplicitConversions ) const
{
    m_pSignature->implicitConversions(a_pLanguage, a_Arguments, a_pContextScope, a_ImplicitConversions);
}

bool MemberFunctionPointerType::matches( const vector<Type*>& parameters, modifiers_t a_Qualifiers ) const
{
    return m_pSignature->matches(parameters, a_Qualifiers);
}

bool MemberFunctionPointerType::matches( const vector<Expression*>& args, modifiers_t a_Qualifiers ) const
{
    return m_pSignature->matches(args, a_Qualifiers);
}

o_namespace_end(phantom, reflection)