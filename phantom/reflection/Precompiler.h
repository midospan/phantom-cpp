

#ifndef o_reflection_Precompiler_h__
#define o_reflection_Precompiler_h__
// #pragma __PragmaPrintFile__


/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Precompiler);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Precompiler : public LanguageElementVisitor
{
public:

public:
    Precompiler(int passCount, Source* a_pSource);
    ~Precompiler();

    void precompileSource(int pass);

    virtual void precompileSource() 
    {
        precompileSource(m_iPassCount-1);
    }

    virtual LanguageElement* precompileElement(const string& a_strExpression, LanguageElement* a_pScope, modifiers_t a_Modifiers = 0) = 0;

    int getPass() const { return m_iPass; }

    int getPassCount() const { return m_iPassCount; }

    virtual int runPass(int pass) = 0;

    inline Language* getLanguage() const { return m_pLanguage; }

    
protected:
    Language* m_pLanguage;
    Source* m_pSource;
    int m_iPass;
    int m_iPassCount;
};

o_namespace_end(phantom, reflection)




#endif