#ifndef o_phantom_reflection_Language_h__
#define o_phantom_reflection_Language_h__


/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Language);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Language
{
public:
	Language(void) {}
	~Language(void) {}

    virtual LanguageElement*elementByName(const string& a_strName, LanguageElement* a_pScope = phantom::rootNamespace()) const = 0;
    virtual Type*           typeByName(const string& a_strName, LanguageElement* a_pScope = phantom::rootNamespace()) const;
    virtual Expression*     expressionByName(const string& a_strName, LanguageElement* a_pScope = phantom::rootNamespace()) const = 0;
    virtual void            compile(const string& a_strModuleName, Compiler* a_pCompiler, SourceFile* a_pSourceFile, Message* a_pMessage) const = 0;

};

o_namespace_end(phantom, reflection)

#endif // o_phantom_reflection_Language_h__
