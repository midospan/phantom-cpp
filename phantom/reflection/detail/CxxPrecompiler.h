#ifndef o_ghost_reflection_CxxPrecompiler_h__
#define o_ghost_reflection_CxxPrecompiler_h__


/* ****************** Includes ******************* */
#include <phantom/reflection/Precompiler.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), CxxPrecompiler);
o_fwd(struct, phantom, reflection, numeric_conversion);
o_fwd(struct, phantom, CxxStatement);
o_fwd(struct, phantom, CxxStatements);
o_fwd(struct, phantom, CxxParenthesised);
o_fwd(struct, phantom, CxxExpression);
o_fwd(struct, phantom, CxxToken);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export CxxPrecompiler : public Precompiler
{
public:

    struct scope_declarations_data
    {
        scope_declarations_data(LanguageElement* s, LanguageElement*lh,
            CxxToken* d,
            CxxParenthesised* p = 0,
            Type* t = 0,
            TemplateSignature* ts = 0) : scope(s), lhs(lh), decl(d), paren(p), type(t), templateSignature(ts) {}
        LanguageElement* scope;
        LanguageElement* lhs;
        CxxToken* decl;
        CxxParenthesised* paren;
        Type* type;
        TemplateSignature* templateSignature;
    };

    enum EPass 
    {
        e_Pass_Parsing,
        e_Pass_SourceMembersLocal,
        e_Pass_SourceMembersGlobal,
        e_Pass_Members,
        e_Pass_Blocks,

        e_Pass_Count,
    };

    enum EFlag
    {
        e_Flag_None = 0,
        e_Flag_PrintErrors = 0x1,
        e_Flag_ExpressionMode = 0x2,
        e_Flag_NamespaceMode = 0x4,
    };

    o_declare_flags(EFlags, EFlag);

    CxxPrecompiler(reflection::Source* a_pSource);

    CxxPrecompiler(bool a_bNamespaceMode);

    ~CxxPrecompiler();

    EFlags getFlags() const { return m_Flags; }

    void setFlags(EFlags flags) { m_Flags = flags; }

    bool hasFlag(EFlag flag) const { return (m_Flags & flag) == flag; }

    virtual int runPass(int pass);

    void queue(EPass pass, LanguageElement* a_pScope, LanguageElement* a_pLHS, CxxToken* a_pToken, CxxParenthesised* a_pParen = 0, Type* a_pType = 0, TemplateSignature* a_pTemplateSignature = 0)
    {
        m_PassDeclarations[pass].push_back(scope_declarations_data(a_pScope, a_pLHS, a_pToken, a_pParen, a_pType, a_pTemplateSignature));
    }

    void queueTemplateSpecializationFinalization(TemplateSpecialization* a_pSpec)
    {
        o_assert(getPass() < e_Pass_Blocks);
        m_TemplateSpecializationsToFinalize.push_back(a_pSpec);
    }

    virtual LanguageElement* precompileElement(const string& a_strExpression, LanguageElement* a_pScope, modifiers_t a_Modifiers = 0);

    LanguageElement* precompile(CxxExpression* expr, LanguageElement* a_pScope, modifiers_t a_Modifiers = 0);

    void precompile(CxxStatements* decls, LanguageElement* a_pScope);

    LabelStatement* topBreakLabel();
    LabelStatement* topContinueLabel();

    LabelStatement* pushBreakLabel();
    LabelStatement* pushContinueLabel();
    void popBreakLabel(LabelStatement* a_pLabel);
    void popContinueLabel(LabelStatement* a_pLabel);

    LabelStatement* findOrCreateLabel(Subroutine* pSubroutine, const string& name);

    void incrementErrorCount()
    {
        m_uiErrorCount++;
    }

    size_t getErrorCount() const { return m_uiErrorCount; }

    Source* getSource() const { return m_pSource; }

    CPlusPlus* getLanguage() const { return static_cast<CPlusPlus*>(m_pLanguage); }

protected:
    map<const vector<LanguageElement*>*, map<LanguageElement*, LanguageElement*>> m_Templated;

    vector<reflection::LanguageElement*> m_PrecompilationScopeStack;
    vector<reflection::LanguageElement*> m_Elements;
    /// members

    vector<CxxToken*> m_Tokens;
    size_t m_uiErrorCount;
    vector<vector<scope_declarations_data>> m_PassDeclarations;
    std::stack<LabelStatement*> breakLabels;
    std::stack<LabelStatement*> continueLabels;
    map<Subroutine*, map<string, LabelStatement*>> labelMap; 
    vector<TemplateSpecialization*> m_TemplateSpecializationsToFinalize;
    EFlags m_Flags;

};

o_namespace_end(phantom, reflection)

#endif // o_reflection_CxxPrecompiler_h__
