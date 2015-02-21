/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Function_h__
#define o_phantom_reflection_Function_h__

/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Function : public Subroutine
{
    o_language_element;

    friend class Scope;

public:
    static Class* const metaType;

public:
    Function(modifiers_t a_Modifiers = 0);
    Function(const string& a_strName, EABI a_eABI, modifiers_t a_Modifiers = 0);
    Function(const string& a_strName, Signature* a_pSignature, modifiers_t a_Modifiers = 0);
    Function(const string& a_strName, Signature* a_pSignature, EABI a_eABI, modifiers_t a_Modifiers = 0);
    
    virtual Function* asFunction() const { return (Function*)this; }

    virtual void call( void** a_pArgs ) const { Subroutine::call(a_pArgs); }
    virtual void call( void** a_pArgs, void* a_pReturnAddress ) const { Subroutine::call(a_pArgs, a_pReturnAddress); }

protected:
    Function(LanguageElement* a_pScope, const string& a_strName, const string& a_strSignature, EABI a_eABI, modifiers_t a_Modifiers = 0);
};

o_namespace_end(phantom, reflection)


#endif