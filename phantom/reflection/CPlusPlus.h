#ifndef o_phantom_reflection_CPlusPlus_h__
#define o_phantom_reflection_CPlusPlus_h__


/* ****************** Includes ******************* */
#include <phantom/reflection/Language.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), CPlusPlus);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export CPlusPlus : public Language
{
public:
	CPlusPlus(void)  {}
	~CPlusPlus(void) {}

    virtual LanguageElement*elementByName(const string& a_strName, LanguageElement* a_pScope = phantom::rootNamespace()) const;

    virtual Expression*     expressionByName(const string& a_strName, LanguageElement* a_pScope = phantom::rootNamespace()) const;

    virtual void compile(const string& a_strCode, Compiler* a_pCompiler, SourceFile* a_pSourceFile, Message* a_pMessage) const;

    virtual bool execute(const string& a_strCode, const vector<variable>& a_Arguments, variant& a_ReturnValue, Compiler* a_pCompiler) const;
};

o_namespace_end(phantom, reflection)

#endif // o_phantom_reflection_CPlusPlus_h__
