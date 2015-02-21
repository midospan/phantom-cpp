/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/FunctionPointerType.h>
#include <phantom/reflection/FunctionPointerType.hxx>
/* *********************************************** */
o_registerN((phantom, reflection), FunctionPointerType);

o_namespace_begin(phantom, reflection) 

o_define_meta_type(FunctionPointerType);

FunctionPointerType::FunctionPointerType( Signature* a_pSignature, EABI a_eABI, modifiers_t a_Modifiers ) 
    : PointerType(""
                , sizeof(void(*)())
                , boost::alignment_of<void(*)()>::value
                , a_Modifiers)    
                , m_pSignature(a_pSignature)
    , m_eABI(a_eABI)
{
    addElement(m_pSignature);
}

FunctionPointerType::~FunctionPointerType()
{

}

void FunctionPointerType::referencedElementRemoved( LanguageElement* a_pElement )
{
    Type::referencedElementRemoved(a_pElement);
}

void FunctionPointerType::valueToLiteral( string& a_str, const void* src ) const
{
    o_exception(exception::base_exception, "valueToLiteral not defined for member function pointer types");
}

void FunctionPointerType::valueToString( string& a_str, const void* src ) const
{
    o_exception(exception::base_exception, "valueToString not defined for member function pointer types");
}

void FunctionPointerType::valueFromString( const string& a_str, void* dest ) const
{
    o_exception(exception::base_exception, "valueFromString not defined for member function pointer types");
}

void FunctionPointerType::copy( void* a_pDest, void const* a_pSrc ) const
{
    memcpy(a_pDest, a_pSrc, m_uiSize);
}

/// Non native function pointers contains the meta function they point to 

void FunctionPointerType::call( void* a_pPointer, void** a_pArgs ) const
{
    o_assert(as<Function*>(a_pPointer));
    static_cast<Function*>(a_pPointer)->call(a_pArgs);
}

void FunctionPointerType::call( void* a_pPointer, void** a_pArgs, void* a_pReturnAddress ) const
{
    o_assert(as<Function*>(a_pPointer));
    static_cast<Function*>(a_pPointer)->call(a_pArgs, a_pReturnAddress);
}

void* FunctionPointerType::getClosure( void* a_pPointer ) const
{
    return static_cast<Function*>(a_pPointer)->getClosure();
}

o_namespace_end(phantom, reflection)