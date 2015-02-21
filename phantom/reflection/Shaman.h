#ifndef o_phantom_reflection_Shaman_h__
#define o_phantom_reflection_Shaman_h__


/* ****************** Includes ******************* */
#include <phantom/reflection/CPlusPlus.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Shaman);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Shaman : public CPlusPlus
{
    friend class CPlusPlus;
public:
    Shaman(void);
	~Shaman(void);

    virtual Subroutine* solveSubroutineCascade( LanguageElement* a_pElement, const string& a_strName, const vector<LanguageElement*>* a_pTemplateArguments, const vector<Type*>& a_ParameterTypes, modifiers_t a_Qualifiers, LanguageElement* a_pScope );
    virtual LanguageElement* unqualifiedLookup( const string& a_strName, const vector<LanguageElement*>* a_pTemplateArguments, const vector<Expression*>* a_pFunctionArguments, LanguageElement* a_pScope, Type* a_pInitializationType );

protected:
    virtual Precompiler*        createPrecompiler(Source* a_pSource) const ;
    virtual void                destroyPrecompiler(Precompiler* a_pPrecompiler) const ;
    virtual LanguageElement*    elementByName( const string& a_strName, LanguageElement* a_pScope = (LanguageElement*)phantom::rootPackageFolder(), modifiers_t a_Modifiers = 0 ) const;

protected:
    LanguageElement* internalElementByName(bool a_bNamespaceMode, const string& a_strName, LanguageElement* a_pScope = (LanguageElement*)phantom::rootPackageFolder(), modifiers_t a_Modifiers = 0) const; 
};

o_namespace_end(phantom, reflection)

#endif // o_phantom_reflection_Shaman_h__
