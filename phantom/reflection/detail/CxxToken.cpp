//
//	  Title:			C++ Grammar Token support compilation unit.
//
//	  File Name:		CxxToken.cpp
//
//	  Author:			E.D.Willink
//END
//
#include <phantom/phantom.h>
#include "CxxDriver.h"
#include "CxxLexer.h"
#include "CxxParser.h"
#include "CxxPrecompiler.h"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#if o_COMPILER != o_COMPILER_VISUAL_STUDIO
#include <inttypes.h>
#else
#define SCNu64 "llu"
#endif

#include "CxxTokenizer.h"

#define o_semantic_error(a)  do { if(a_pPrecompiler->hasFlag(CxxPrecompiler::e_Flag_PrintErrors)) std::cout << "error : semantic : " << a << std::endl;  a_pPrecompiler->incrementErrorCount(); } while (0)
#define o_semantic_suberror(a)  do { if(a_pPrecompiler->hasFlag(CxxPrecompiler::e_Flag_PrintErrors)) std::cout << "    " << a << std::endl; } while (0)


namespace phantom
{

    CxxToken * CxxToken::yyToken;

    void CxxToken::Initialize(bool a_bInitialize)
    {
        if(a_bInitialize)
        {
            o_assert(CxxDriver::Instance() == nullptr);
            yyToken = 0;
            angleToken = new CxxToken('<');
            colonToken = new CxxToken(':');
            hashToken = new CxxToken('#');
            plusToken = new CxxToken('+');
            minusToken = new CxxToken('-');
            dollarToken = new CxxToken('$');
            for(int i = 0;i<256; ++i) asciiTokens[i] = new CxxToken(i);
        }
        else 
        {
            delete angleToken;
            delete colonToken;
            delete hashToken;
            delete plusToken;
            delete minusToken;
            delete dollarToken;
            for(int i = 0;i<256; ++i) delete asciiTokens[i];
        }
    }
    CxxNaffToken::CxxNaffToken(int tokenValue, const char *yyText, int yyLeng)
        :
    CxxToken(tokenValue), _text(new char[yyLeng+1]), _leng(yyLeng)
    {
        memcpy(_text, yyText, yyLeng);
        _text[_leng] = 0;
    }

    CxxNaffToken::~CxxNaffToken() { delete[] _text; }

    CxxToken* CxxToken::angleToken;
    CxxToken* CxxToken::colonToken;
    CxxToken* CxxToken::hashToken;
    CxxToken* CxxToken::plusToken;
    CxxToken* CxxToken::minusToken;
    CxxToken* CxxToken::dollarToken;
    CxxToken* CxxToken::asciiTokens[256];



    bool c_keywords = false;
    bool echo_line_numbers = false;
    bool echo_line_text = false;
    size_t line_number = 0;

    //
    //	Configure the lexer to reflect successful parsing of a character value, assigning it to yylval.
    //
    //	The source someText[aLength] should correspond to the parsed text including any L or ' prefix
    //	but excluding any ' suffix. In this way the return can indicate whether a wide character has
    //	been detected and the routine can accommodate a variety of erroneous terminations.
    //
    CxxCharacterLiteral *CxxToken::make_character(const char *someText, size_t aLength)
    {
        bool isWide = false;
        if (someText && aLength)
        {
            if (*someText == 'L')
            {
                isWide = true;
                someText++;
                aLength--;
            }
            if (!aLength || (*someText != '\''))
            {
                ERRMSG("BUG - bad start of character literal.");
                return nullptr;
            }
            if (aLength)
            {
                someText++;
                aLength--; // remove first '
                aLength--; // remove last '
            }
        }
        else 
        {
            return nullptr;
        }
        if (isWide)
            return make_wide_character(someText, aLength);
        else
            return make_narrow_character(someText, aLength);
    }

    CxxName* CxxToken::make_identifier(const char *someText, size_t aLength)
    {
        return new CxxName(PARSE_TOKEN(Identifier), someText, aLength);
    }

    CxxName* CxxToken::make_keyword( int tokenValue, const char *someText, size_t aLength)
    {
        return new CxxName(tokenValue, someText, aLength);
    }

    //
    //	Buffer the incoming line, before any characters are analysed.
    //
    void CxxToken::make_line(const char *yyText, size_t yyLeng)
    {
        if (echo_line_text)
            std::cout << CxxDriver::Instance()->getLexer()->tokenMarkDepth << ": "  << line_number << ": " << yyText << std::flush; 
        else if (echo_line_numbers)
            std::cout << line_number << std::endl; 
        line_number++ ; 
    }

    CxxToken *CxxToken::make_literal_character(const char *someText, size_t aLength)
    {
        return new CxxNaffToken(PARSE_TOKEN(CharacterLiteral), someText, aLength);
    }

    CxxCharacterLiteral* CxxToken::make_narrow_character(const char *someText, size_t aLength)
    {
        char c = *someText;
        if(aLength > 1)
        {
            if(c != '\\') 
            {
                ERRMSG("BUG - invalid character literal.");
                return nullptr;
            }
            someText++;
            aLength--;
            switch(*someText)
            {
            case 'n': c = '\n'; break;
            case 't': c = '\t'; break;
            case 'r': c = '\r'; break;
            case '0': c = '\0'; break;
            default: c = *someText;
            }
        }
        return new CxxCharacterLiteral(c);
    }

    CxxStringLiteral *CxxToken::make_narrow_string(const char *someText, size_t aLength)
    {
        return new CxxStringLiteral(someText, aLength);
    }

    CxxNumberLiteral<unsigned long long> * CxxToken::make_hex_number(const char *someText, size_t aLength)
    {
        ++(++someText);
        unsigned long long n;
        if(sscanf(someText, "%x", &n) == EOF)
        {
            ERRMSG("BUG - Invalid hex format");
            return nullptr;
        }
        return new CxxNumberLiteral<unsigned long long>(PARSE_TOKEN(HexLiteral), n);
    }

    CxxNumberLiteral<long double> * CxxToken::make_longdouble_number(const char *someText, size_t aLength)
    {
        long double n;
        if(sscanf(someText, "%Lf", &n) == EOF)
        {
            if(sscanf(someText, "%Le", &n) == EOF)
            {
                ERRMSG("BUG - invalid long double format");
                return nullptr;
            }
        }
        return new CxxNumberLiteral<long double>(PARSE_TOKEN(LongDoubleLiteral), n);
    }
    CxxNumberLiteral<double>* CxxToken::make_double_number(const char *someText, size_t aLength)
    {
        double n;
        if(sscanf(someText, "%lf", &n) == EOF)
        {
            if(sscanf(someText, "%le", &n) == EOF)
            {
                ERRMSG("BUG - invalid double format");
                return nullptr;
            }
        }
        return new CxxNumberLiteral<double>(PARSE_TOKEN(DoubleLiteral), n);
    }
    CxxNumberLiteral<float>* CxxToken::make_float_number(const char *someText, size_t aLength)
    {
        float n;
        if(sscanf(someText, "%f", &n) == EOF)
        {
            if(sscanf(someText, "%fe", &n) == EOF)
            {
                ERRMSG("BUG - invalid float format");
                return nullptr;
            }
        }
        return new CxxNumberLiteral<float>(PARSE_TOKEN(FloatLiteral), n);
    }
    CxxNumberLiteral<unsigned int>* CxxToken::make_uint_number(const char *someText, size_t aLength)
    {
        unsigned int n;
        if(sscanf(someText, "%u", &n) == EOF)
        {
            ERRMSG("BUG - invalid unsigned int format");
            return nullptr;
        }
        return new CxxNumberLiteral<unsigned int>(PARSE_TOKEN(UIntLiteral), n);
    }
    CxxNumberLiteral<unsigned long>* CxxToken::make_ulong_number(const char *someText, size_t aLength)
    {
        unsigned long n;
        if(sscanf(someText, "%lu", &n) == EOF)
        {
            ERRMSG("BUG - invalid unsigned long format");
            return nullptr;
        }
        return new CxxNumberLiteral<unsigned long>(PARSE_TOKEN(ULongLiteral), n);
    }
    CxxNumberLiteral<unsigned long long>* CxxToken::make_ulonglong_number(const char *someText, size_t aLength)
    {
        unsigned long long n;
        if(sscanf(someText, "%"SCNu64, &n) == EOF)
        {
            ERRMSG("BUG - invalid unsigned long long format");
            return nullptr;
        }
        return new CxxNumberLiteral<unsigned long long>(PARSE_TOKEN(ULongLongLiteral), n);
    }

    //
    //	Configure the lexer to reflect successful parsing of a categorised string.
    //
    //	The source someText[aLength] should correspond to the parsed text including any
    //	L or " prefix but excluding any " suffix. In this way the return can indicate whether a wide
    //	character has been detected and the routine can accommodate a variety of erroneous terminations.
    //
    CxxStringLiteral *CxxToken::make_string(const char *someText, size_t aLength)
    {
        bool isWide = false;
        if (someText && aLength)
        {
            if (*someText == 'L')
            {
                isWide = true;
                someText++;
                aLength--;
            }
            if (!aLength || (*someText != '"'))
                ERRMSG("BUG - bad start of string literal.");
            if (aLength)
            {
                someText++;
                aLength--;
            }
        }
        if (isWide)
            return make_wide_string(someText, aLength);
        else
            return make_narrow_string(someText, aLength);
    }

    //
    //	Return the appropriate 1 of 256 flyweight tokens for the ASCII characters.
    //
    CxxToken *CxxToken::get_ascii_token(size_t tokenValue)
    {
        o_assert(tokenValue < 256);
        return asciiTokens[tokenValue];
    }

    CxxCharacterLiteral *CxxToken::make_wide_character(const char *someText, size_t aLength)
    {
        if(*someText == '\\')
        {
            someText++;
            aLength--;
            if(*someText == 'u')
            {
                someText++;
                aLength--;
                // universal
                wchar_t c;
                if(sscanf(someText, "%x", &c) == EOF)
                {
                    ERRMSG("BUG - invalid unicode code point formatting " << someText);
                    return nullptr;
                }
                return new CxxCharacterLiteral(c);
            }
        }
        return nullptr;
    }

    CxxStringLiteral *CxxToken::make_wide_string(const char *someText, size_t aLength)
    {
        return new CxxStringLiteral(someText, aLength, true);
    }


    CxxCharacterLiteral::CxxCharacterLiteral( char c ) : CxxToken(PARSE_TOKEN(CharacterLiteral)), chr(c), size(1)
    {

    }

    CxxCharacterLiteral::CxxCharacterLiteral( wchar_t c ) : CxxToken(PARSE_TOKEN(CharacterLiteral)), chr(c), size(2)
    {

    }

    CxxToken::CxxToken( int tokenValue /*= 0*/ ) : _value(tokenValue)
    {
        if(CxxDriver::Instance())
        CxxDriver::Instance()->registerToken(this);
    }

    CxxToken::~CxxToken()
    {
        o_assert(CxxDriver::Instance() == nullptr);
    }

    LanguageElement* CxxExpression::precompileParenthesized( CxxPrecompiler* a_pPrecompiler, CxxParenthesised* a_pParen, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
    {
        Expression* pExpression = precompileExpression(a_pPrecompiler, a_pScope, a_pLHS, a_Modifiers);
        if(pExpression == nullptr)
        {
            o_semantic_error("invalid expression on left hand side of '()' operator");
            return o_new(CallExpression)(nullptr, nullptr, nullptr);
        }
        vector<Expression*> exprs;
        if(a_pParen->parameters)
        {
            for(auto it = a_pParen->parameters->list.begin(); it != a_pParen->parameters->list.end(); ++it)
            {
                exprs.push_back((*it)->expr->precompileExpression(a_pPrecompiler, a_pScope));
            }
        }
        return a_pPrecompiler->getLanguage()->qualifiedLookup(pExpression, "operator()", nullptr, &exprs, a_pScope, nullptr);
    }

    LanguageElement* CxxExpression::precompileTemplateParenthesized( CxxPrecompiler* a_pPrecompiler, TemplateSignature* a_pTemplateSignature, CxxParenthesised* a_pParen, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
    {
        o_assert_no_implementation();
        return nullptr; //a_pPrecompiler->getLanguage()->qualifiedLookup(pExpression, "operator()", nullptr, &exprs, a_pScope, nullptr);
    }

    LanguageElement* CxxScopedPointerExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        o_warning(false, __FUNCTION__ "not implemented");
        return nullptr;
    }

    LanguageElement* CxxCStyleCastExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        LanguageElement* pElement = type->precompile(a_pPrecompiler, a_pScope, nullptr, a_Modifiers);
        Type* pType = pElement->asType();
        if(pType == nullptr)
        {
            pType = Type::Invalid();
        }
        Expression* pExpr = expr->precompileExpression(a_pPrecompiler, a_pScope, nullptr, a_Modifiers);
        return a_pPrecompiler->getLanguage()->convert(pExpr, pType, reflection::e_explicit_cast, a_pScope);
    }

    LanguageElement* CxxName::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        if(words.empty())
        {
            o_semantic_error("empty name");
            return nullptr;
        }
        if(!isTemplate)
        {
            if(a_pScope->asTemplateSignature())
            {
                if(classKey)
                {
                    const string& id = classKey->asIdentifier();
                    o_assert(id.size());
                    if(id == "class" OR id == "typename")
                    {
                        string wordId = asIdentifier();
                        return o_new(TemplateParameter)(o_new(PlaceholderType)(wordId));
                    }
                }
            }

            LanguageElement* pScope = a_pScope;
            bool bUnqualified = true;
            if(a_pLHS)
            {
                pScope = a_pLHS;
                bUnqualified = false;
            }
            for(auto it = words.begin(); it != words.end(); ++it)
            {
                if(it->id.empty())
                {
                    if(it != words.begin())
                    {
                        o_semantic_error("empty scope name");
                        return nullptr;
                    }
                    pScope = globalNamespace();
                }
                else 
                {
                    bool namespaceMode = a_pPrecompiler->hasFlag(CxxPrecompiler::e_Flag_NamespaceMode);
                    LanguageElement* pChildScope = nullptr;

                    if(it->templateArgs != nullptr)
                    {
                        vector<LanguageElement*> templateElements;
                        it->templateArgs->precompile(a_pPrecompiler, a_pScope, templateElements);
                        pChildScope = bUnqualified // if we don't have a left-hand side, we look recursively through all scope hierarchy
                                        ? a_pPrecompiler->getLanguage()->unqualifiedLookup(it->id, &templateElements, nullptr, a_pScope, nullptr) 
                                        : a_pPrecompiler->getLanguage()->qualifiedLookup(pScope, it->id, &templateElements, nullptr, a_pScope, nullptr);
                    }
                    else 
                    {
                        pChildScope = bUnqualified // if we don't have a left-hand side, we look recursively through all scope hierarchy
                            ? a_pPrecompiler->getLanguage()->unqualifiedLookup(it->id, nullptr, nullptr, a_pScope, nullptr) 
                            : a_pPrecompiler->getLanguage()->qualifiedLookup(pScope, it->id, nullptr, nullptr, a_pScope, nullptr);
                    }
                    if(pChildScope == nullptr)
                    {
                        o_semantic_error("unknown symbol '"<<it->id<<"'");
                        return nullptr;
                    }
                    Source* pSource = a_pScope->getSource();
                    o_assert( namespaceMode
                            OR pSource 
                            OR a_pScope->asNamespace(), "scope must have a source");
//                     if(pSource)
//                     {
//                         o_semantic_error("inaccessible symbol '"<<it->id<<"' requires import in scope '"<<(a_pScope->asTemplateSignature() ? a_pScope->getOwner()->asNamedElement()->getQualifiedDecoratedName() : pScope->asNamedElement()->getQualifiedDecoratedName())<<"'");
//                     }
                    bUnqualified = false;
                    pScope = pChildScope;
                }
            }
            Type* pType = pScope->asType();
            if(pType)
            {
                if(declSpecifier)
                    return declSpecifier->specify(a_pPrecompiler, pType);
                return pType;
            }
            else if(declSpecifier)
            {
                o_semantic_error("declaration specifiers not allowed on non type symbols");
                return nullptr;
            }
            return pScope;
        }
        else 
        {
            o_assert(false, "template instanciation not supported by compilation yet");
            return nullptr;
        }
    }

    LanguageElement* CxxName::precompileParenthesized( CxxPrecompiler* a_pPrecompiler, CxxParenthesised* aParenthesised, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        if(words.empty())
        {
            o_semantic_error("empty name");
            return nullptr;
        }
        if(!isTemplate)
        {
            LanguageElement* pScope = a_pScope;
            bool bUnqualified = true;
            if(a_pLHS)
            {
                pScope = a_pLHS;
                bUnqualified = false;
            }
            auto end = words.end();
            auto last = --end;
            for(auto it = words.begin(); it != end; ++it)
            {
                if(it->id.empty())
                {
                    if(it != words.begin())
                    {
                        o_semantic_error("empty scope name");
                        return nullptr;
                    }
                    pScope = globalNamespace();
                }
                else 
                {
                    bool namespaceMode = a_pPrecompiler->hasFlag(CxxPrecompiler::e_Flag_NamespaceMode);
                    LanguageElement* pChildScope = nullptr;
                    if(it->templateArgs != nullptr)
                    {
                        vector<LanguageElement*> templateElements;
                        it->templateArgs->precompile(a_pPrecompiler, a_pScope, templateElements);
                        pChildScope = bUnqualified // if we don't have a left-hand side, we look recursively through all scope hierarchy
                            ? a_pPrecompiler->getLanguage()->unqualifiedLookup(it->id, &templateElements, nullptr, a_pScope, nullptr) 
                            : a_pPrecompiler->getLanguage()->qualifiedLookup(pScope, it->id, &templateElements, nullptr, a_pScope, nullptr);
                    }
                    else 
                    {
                        pChildScope = bUnqualified // if we don't have a left-hand side, we look recursively through all scope hierarchy
                            ? a_pPrecompiler->getLanguage()->unqualifiedLookup(it->id, nullptr, nullptr, a_pScope, nullptr) 
                            : a_pPrecompiler->getLanguage()->qualifiedLookup(pScope, it->id, nullptr, nullptr, a_pScope, nullptr);
                    }
                    if(pChildScope == nullptr)
                    {
                        o_semantic_error("undefined symbol '"<<it->id<<"' in scope '"<<pScope->asNamedElement()->getQualifiedDecoratedName()<<"'");
                        return nullptr;
                    }
                    Source* pSource = a_pScope->getSource();
                    o_assert(namespaceMode OR pSource, "scope must have a source");
//                     if(NOT(pSource->isAccessible(pChildScope)))
//                     {
//                         o_semantic_error("inaccessible symbol '"<<it->id<<"' requires import in scope '"<<(a_pScope->asTemplateSignature() ? a_pScope->getOwner()->asNamedElement()->getQualifiedDecoratedName() : pScope->asNamedElement()->getQualifiedDecoratedName())<<"'");
//                     }
                    pScope = pChildScope;
                }
                bUnqualified = false;
            }

            bool namespaceMode = a_pPrecompiler->hasFlag(CxxPrecompiler::e_Flag_NamespaceMode);

            vector<LanguageElement*> argumentsOrParameters;
            aParenthesised->precompile(a_pPrecompiler, pScope, argumentsOrParameters, &a_Modifiers);

            vector<Expression*> functionArguments;
            vector<Type*> functionTypes;
            vector<LanguageElement*> templateArguments;
            vector<Expression*>* pFunctionArguments = nullptr;
            vector<Type*>* pFunctionTypes = nullptr;
            vector<LanguageElement*>* pTemplateArguments = nullptr;
            bool bExpressions = true;
            bool bTypes = NOT(pScope->asExpression()); /// we don't expect signature with a left hand side being an evaluable expression
            if(argumentsOrParameters.empty())
            {
                pFunctionTypes = &functionTypes;
            }
            else for(auto it = argumentsOrParameters.begin(); it != argumentsOrParameters.end(); ++it)
            {
                LanguageElement* pElement = *it;
                if(pElement->asExpression() AND bExpressions)
                {
                    bTypes = false;
                    functionArguments.push_back(pElement->asExpression());
                    pFunctionArguments = &functionArguments;
                }
                else if(pElement->asType() AND bTypes)
                {
                    bExpressions = false;
                    functionTypes.push_back(pElement->asType());
                    pFunctionTypes = &functionTypes;
                }
                else 
                {
                    o_semantic_error("invalid expression in parenthesized expression");
                }
            }

            if(pFunctionTypes)
            {
                if(last->templateArgs != nullptr)
                {
                    vector<LanguageElement*> templateElements;
                    last->templateArgs->precompile(a_pPrecompiler, a_pScope, templateElements);
                    pScope = bUnqualified // if we don't have a left-hand side, we look recursively through all scope hierarchy
                        ? a_pPrecompiler->getLanguage()->solveSubroutineCascade(pScope, last->id, &templateElements, *pFunctionTypes, a_Modifiers, a_pScope) 
                        : a_pPrecompiler->getLanguage()->solveSubroutine(pScope, last->id, &templateElements, *pFunctionTypes, a_Modifiers, a_pScope);
                }
                else 
                {
                    pScope = bUnqualified // if we don't have a left-hand side, we look recursively through all scope hierarchy
                        ? a_pPrecompiler->getLanguage()->solveSubroutineCascade(pScope, last->id, nullptr, *pFunctionTypes, a_Modifiers, a_pScope) 
                        : a_pPrecompiler->getLanguage()->solveSubroutine(pScope, last->id, nullptr, *pFunctionTypes, a_Modifiers, a_pScope);
                }
            }
            else if(pFunctionArguments)
            {
                LanguageElement* pPrecompiled = nullptr;
                if(last->templateArgs != nullptr)
                {
                    vector<LanguageElement*> templateElements;
                    last->templateArgs->precompile(a_pPrecompiler, a_pScope, templateElements);
                    pScope = bUnqualified // if we don't have a left-hand side, we look recursively through all scope hierarchy
                        ? a_pPrecompiler->getLanguage()->unqualifiedLookup(last->id, &templateElements, pFunctionArguments, a_pScope, nullptr) 
                        : a_pPrecompiler->getLanguage()->qualifiedLookup(pScope, last->id, &templateElements, pFunctionArguments, a_pScope, nullptr);
                }
                else 
                {
                    pScope = bUnqualified // if we don't have a left-hand side, we look recursively through all scope hierarchy
                        ? a_pPrecompiler->getLanguage()->unqualifiedLookup(last->id, nullptr, pFunctionArguments, a_pScope, nullptr) 
                        : a_pPrecompiler->getLanguage()->qualifiedLookup(pScope, last->id, nullptr, pFunctionArguments, a_pScope, nullptr);
                }
            }
            return pScope;
        }
        else 
        {
            o_assert(false, "template explicit instanciation not supported by compilation yet");
            return nullptr;
        }
    }

    LanguageElement* CxxName::precompileTemplateParenthesized( CxxPrecompiler* a_pPrecompiler, TemplateSignature* a_pTemplateSignature, CxxParenthesised* aParenthesised, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
    {
        a_pScope->addScopedElement(a_pTemplateSignature);
        LanguageElement* pElement = precompileParenthesized(a_pPrecompiler, aParenthesised, a_pTemplateSignature, a_pLHS, a_Modifiers);
        a_pScope->removeScopedElement(a_pTemplateSignature);
        return pElement;
    }

    LanguageElement* CxxName::precompileTypedParenthesized( CxxPrecompiler* a_pPrecompiler, Type* a_pType, CxxParenthesised* a_pParen, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/, modifiers_t a_Modifiers )
    {
        const string& id = asIdentifier();
        if(id.empty())
        {
            o_semantic_error("illformed function identifier");
        }

        modifiers_t modifiers = 0;
        if(declSpecifier)
            declSpecifier->specify(a_pPrecompiler, a_pType, &modifiers);

        if(a_pPrecompiler->hasFlag(CxxPrecompiler::e_Flag_ExpressionMode))
        {
            // In expression mode, we just look for a perfect matching subroutine
            Scope* pScope = a_pLHS ? a_pLHS->asScope() : a_pScope->asScope();
            if(pScope == nullptr) return nullptr;
            vector<LanguageElement*> types;
            a_pParen->precompile(a_pPrecompiler, a_pScope, types, &modifiers);
            for(auto it = types.begin(); it != types.end(); ++it)
            {
                o_assert((*it) == nullptr OR (*it)->asType());
            }
            Subroutine* pSubroutine = pScope->getSubroutine(a_pType, id, (const vector<Type*>&)types, (modifiers&o_member_function_qualifiers_mask));
            if(pSubroutine AND (pSubroutine->isStatic() == ((modifiers&o_static) == o_static)))
            {
                return pSubroutine;
            }
            return nullptr;
        }
        else 
        {
            ClassType* pClassType = nullptr;
            Namespace* pNamespace = nullptr;
            bool isDefinition = (a_Modifiers&o_defined) == o_defined;
            bool isMemberFunction = (pClassType=a_pScope->asClassType()) != nullptr OR (a_pLHS AND (pClassType = a_pLHS->asClassType()));
            bool isExternal = a_pLHS != nullptr;
            bool isFunction = a_pLHS == nullptr AND !isMemberFunction;

            Signature* pSignature = o_new(Signature)(a_pType, (modifiers&o_member_function_qualifiers_mask));
            a_pScope->addScopedElement(pSignature);
            vector<LanguageElement*> argumentsOrParameters;
            vector<Parameter*> parameters;
            vector<Type*> types;
            a_pParen->precompile(a_pPrecompiler, pSignature, argumentsOrParameters, &modifiers);
            a_pScope->removeScopedElement(pSignature);
            for(auto it = argumentsOrParameters.begin(); it != argumentsOrParameters.end(); ++it)
            {
                LanguageElement* pElem = *it;
                Parameter* pParam = pElem->asParameter();
                Type* pType;
                if(pParam)
                {
                    pSignature->addParameter(pParam);
                    types.push_back(pParam->getValueType());
                }
                else if(pType = pElem->asType())
                {
                    types.push_back(pType);
                    pSignature->addParameter(o_new(Parameter)(pType));
                }
                else 
                {
                    types.push_back(nullptr);
                    pSignature->addParameter((Parameter*)nullptr);
                    o_semantic_error("unexpected expression in signature, expecting type or parameter declaration");
                }
            }

            if(isMemberFunction) // member function
            {
                Subroutine* pMemberFunction = nullptr;

                if(isExternal)
                {
                    bool bSourceIncompatibility = a_pLHS->getSource() != a_pPrecompiler->getSource();
                    if(bSourceIncompatibility)
                    {
                        o_semantic_error("out-of-class member function must be defined in the same source as its owner class");
                    }
                    if(modifiers & ~(o_member_function_qualifiers_mask|o_inline))
                    {
                        o_semantic_error("illegal specifiers on out of scope member function definition");
                    }
                    // if external definition we must already have created the member function
                    CxxTemplateArguments* pLastTemplateArgs = getLastTemplateArguments();
                    vector<LanguageElement*> templateArgs;
                    if(pLastTemplateArgs)
                    {
                        pLastTemplateArgs->precompile(a_pPrecompiler, a_pScope, templateArgs);
                    }
                    Subroutine* pMemberFunction = a_pPrecompiler->getLanguage()->solveSubroutine(a_pLHS, id, pLastTemplateArgs ? &templateArgs : nullptr, types, modifiers, a_pScope);
                    if(pMemberFunction->isInvalid())
                    {
                        o_semantic_error("member function declaration not found in class type '"<<a_pLHS->asNamedElement()->getQualifiedDecoratedName()<<"'");
                        if(pMemberFunction == Subroutine::Invalid())
                        {
                            if(bSourceIncompatibility)
                            {
                                Function* pFunction = o_new(Function)(id, pSignature, modifiers|o_invalid);
                                a_pPrecompiler->getSource()->addFunction(pFunction);
                                return pFunction;
                            }
                            else 
                            {
                                MemberFunction* pMemberFunction = o_new(MemberFunction)(id, pSignature, modifiers|o_invalid);
                                pClassType->addMemberFunction(pMemberFunction);
                                return pMemberFunction;
                            }
                        }
                    }
                    else 
                    {
                        if(pMemberFunction AND NOT(pSignature->matches(pMemberFunction->getSignature())))
                        {
                            o_semantic_error("member function definition only differs by return type from its declaration");
                            pMemberFunction->setInvalid();
                        }
                        else if(isDefinition) 
                        {
                            for(size_t i = 0; i<pSignature->getParameterCount(); ++i)
                            {
                                pMemberFunction->getSignature()->getParameter(i)->setDefinitionName(pSignature->getParameter(i)->getName());
                            }
                        }
                    }
                    o_delete(Signature) pSignature;
                    return pMemberFunction;
                }
                else 
                {
                    // internal
                    o_assert(pClassType);
                    vector<Subroutine*> conflicting;
                    string conflictingMessage;
                    if(NOT(pClassType->acceptsSubroutine(a_pType, id, types, modifiers, &conflicting)))
                    {
                        bool inSameClass = false;
                        bool isConflictingFunction = false;
                        for(auto it = conflicting.begin(); it != conflicting.end(); ++it)
                        {
                            Subroutine* pConflicting = *it;
                            if(pConflicting->getOwner() == pClassType)
                            {
                                inSameClass = true;
                                if(pConflicting->asFunction())
                                    isConflictingFunction = true;
                            }
                            conflictingMessage += "\t"+pConflicting->getReturnType()->getQualifiedDecoratedName()+" "+pConflicting->getQualifiedDecoratedName()+"\n";
                        }
                        if(inSameClass)
                        {
                            if(isFunction)
                            {
                                o_semantic_error("function with same parameters already defined in current class :\n"<<conflictingMessage);
                            }
                            else 
                            {
                                o_semantic_error("member function with same parameters already defined in current class :\n"<<conflictingMessage);
                            }
                        }
                        else 
                        {
                            o_semantic_error("overridding member function return type not covariant :\n"<<conflictingMessage);
                        }
                    }

                    if(modifiers & o_static)
                    {
                        pMemberFunction = o_new(Function)(id, pSignature, modifiers);
                        pClassType->addFunction(pMemberFunction->asFunction());
                        if(modifiers & o_virtual)
                        {
                            o_semantic_error("incompatible 'static' and 'virtual' specifiers");
                            pMemberFunction->setInvalid();
                        }
                        if(modifiers & o_member_function_qualifiers_mask)
                        {
                            o_semantic_error("incompatible 'static' and 'member function qualifier(s)' specifiers");
                            pMemberFunction->setInvalid();
                        }
                        return pMemberFunction;
                    }
                    else 
                    {
                        pMemberFunction = o_new(MemberFunction)(id, pSignature, modifiers);
                        pClassType->addMemberFunction(pMemberFunction->asMemberFunction());
                        return pMemberFunction;
                    }
                }
            }
            else 
            {
                if(modifiers & o_member_function_qualifiers_mask)
                {
                    o_semantic_error("illegal member function qualifier(s) on global function declaration");
                }
                // if external definition we must already have created the member function
                CxxTemplateArguments* pLastTemplateArgs = getLastTemplateArguments();
                vector<LanguageElement*> templateArgs;
                vector<LanguageElement*>* pTemplateArgs = nullptr;
                if(pLastTemplateArgs)
                {
                    pLastTemplateArgs->precompile(a_pPrecompiler, a_pScope, templateArgs);
                    pTemplateArgs = &templateArgs;
                }
                Subroutine* pDeclaredSubroutine = a_pPrecompiler->getLanguage()->solveSubroutine(a_pScope, id, pTemplateArgs, types, (modifiers&o_member_function_qualifiers_mask), a_pScope);
                Function* pFunction = nullptr;
                if(pDeclaredSubroutine->isInvalid())
                {
                    if(isExternal)
                    {
                        o_semantic_error("no function declared matching this definition");
                    }
                    // No previous declaration
                    pFunction = o_new(Function)(id, pSignature, e_defaultcall, modifiers|o_invalid);
                    a_pPrecompiler->getSource()->getPackage()->getCounterpartNamespace()->addFunction(pFunction);
                    a_pPrecompiler->getSource()->addFunction(pFunction);
                    return pFunction;
                }
                else
                {
                    pFunction = pDeclaredSubroutine->asFunction();
                    if(pFunction AND NOT(pSignature->matches(pFunction->asSubroutine()->getSignature())))
                    {
                        o_semantic_error("function definition only differs by return type from its declaration");
                        pFunction->setInvalid();
                    }
                    return pFunction;
                }
            }
        }
    }

    Type* CxxName::specify( CxxPrecompiler* a_pPrecompiler, Type* a_pType, modifiers_t* modifiers )
    {
        Type* specified = trySpecify(a_pPrecompiler, a_pType, modifiers);
        return specified ? specified : Type::Invalid();
    }

    Type* CxxName::trySpecify( CxxPrecompiler* a_pPrecompiler, Type* a_pType, modifiers_t* modifiers )
    {
        if(words.empty()) return nullptr;
        bool typeStarted = false;
        for(auto it = words.begin(); it != words.end(); ++it)
        {
            if(*it == "volatile")
            {
                typeStarted = true;
                a_pType = a_pType->addVolatile(); // a_pType->constType();
            }
            else if(*it == "const")
            {
                typeStarted = true;
                a_pType = a_pType->addConst();
            }
            else if(*it == "*")
            {
                typeStarted = true;
                a_pType = a_pType->addPointer();
            }
            else if(*it == "&")
            {
                typeStarted = true;
                a_pType = a_pType->addLValueReference();
            }
            else if(*it == "&&")
            {
                typeStarted = true;
                a_pType = a_pType->addRValueReference();
            }
            else if(modifiers)
            {
                if(typeStarted)
                {
                    o_semantic_error("illegal type specifier '"<<it->toString()<<"'");
                    return nullptr;
                }
                if(*it == "static")
                {
                    if(*modifiers & o_static)
                    {
                        o_semantic_error("multiple 'static' specifiers");
                    }
                    *modifiers |= o_static;
                }
                else if(*it == "inline")
                {
                    if(*modifiers & o_inline)
                    {
                        o_semantic_error("multiple 'inline' specifiers");
                    }
                    *modifiers |= o_inline;
                }
                else if(*it == "virtual")
                {
                    if(*modifiers & o_virtual)
                    {
                        o_semantic_error("multiple 'virtual' specifiers");
                    }
                    *modifiers |= o_virtual;
                }
            }
            else return nullptr;
        }
        return a_pType;
    }
    string CxxName::toNamespaceQualifiedName(CxxPrecompiler* a_pPrecompiler) const
    {
        string result;
        for(auto it = words.begin(); it != words.end(); ++it)
        {
            if(it != words.begin())
                result+="::";
            result += it->id;
            if(it->templateArgs)
            {
                o_semantic_error("namespace cannot be defined inside class types");
                return "";
            }
        }
        return result;
    }

    string CxxName::toString() const
    {
        string result;
        for(auto it = words.begin(); it != words.end(); ++it)
        {
            if(it != words.begin())
                result+="::";
            result += it->toString();
        }
        return result;
    }

    LanguageElement* CxxReinterpretCastExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        Type* pType = type->precompileType(a_pPrecompiler, a_pScope);
        Expression* pExpr = expr->precompileExpression(a_pPrecompiler, a_pScope);
        return a_pPrecompiler->getLanguage()->convert(pExpr, pType, reflection::e_reinterpret_cast, a_pScope);
    }

    LanguageElement* CxxStaticCastExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        Type* pType = type->precompileType(a_pPrecompiler, a_pScope);
        Expression* pExpr = expr->precompileExpression(a_pPrecompiler, a_pScope);
        return a_pPrecompiler->getLanguage()->convert(pExpr, pType, reflection::e_static_cast, a_pScope);
    }

    LanguageElement* CxxConstCastExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        Type* pType = type->precompileType(a_pPrecompiler, a_pScope);
        Expression* pExpr = expr->precompileExpression(a_pPrecompiler, a_pScope);
        return a_pPrecompiler->getLanguage()->convert(pExpr, pType, reflection::e_const_cast, a_pScope);
    }

    LanguageElement* CxxExpressions::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        LocalVariable* pLocalVariable = a_pScope->asLocalVariable();
        if(pLocalVariable AND pLocalVariable->getName() == "this")
        {
            Block* pBlock = pLocalVariable->getBlock();
            vector<DataMemberInitializationStatement*> explicitInitializations;
            // scope is the 'this' variable => precompile as member initializer list
            for(auto it = list.begin(); it != list.end(); ++it)
            {
                LanguageElement* pElement = (*it)->precompile(a_pPrecompiler, a_pScope);
                if(pElement->asStatement() == nullptr)
                {
                    o_semantic_error("ill-formed data member initializer");
                }
                explicitInitializations.push_back(static_cast<DataMemberInitializationStatement*>(pElement));
            }
            // Check initializations validity and fetch initialized members
            vector<DataMember*> explicitelyInitializedInstanceDataMembers;
            for(auto it = explicitInitializations.begin(); it != explicitInitializations.end(); ++it)
            {
                DataMember* pDataMember = (*it)->getDataMember();
                explicitelyInitializedInstanceDataMembers.push_back(pDataMember);
            }
            o_assert(explicitInitializations.size() == explicitelyInitializedInstanceDataMembers.size());
            vector<DataMemberInitializationStatement*> initializations;
            // One initializations gathered, we need to sort them in the member declaration order
            ClassType* pClassType = pBlock->getSubroutine()->getOwner()->asClassType();
            for(auto it = pClassType->beginDataMembers(); it != pClassType->endDataMembers(); ++it)
            {
                bool initialized = false;
                for(size_t i = 0; i<explicitInitializations.size(); ++i)
                {
                    if(explicitelyInitializedInstanceDataMembers[i] == *it)
                    {
                        initializations.push_back(explicitInitializations[i]);
                        initialized = true;
                        break;
                    }
                }
                if(!initialized)
                {
                    if((*it)->getValueType()->asReferenceType())
                    {
                        o_semantic_error((*it)->getName()<<" : reference data members must be explicitely initialized");
                    }
                    else if((*it)->getValueType()->asClassType())
                    {
                        if(NOT((*it)->getValueType()->asClassType()->isDefaultConstructible()))
                        {
                            o_semantic_error("class type '"<< (*it)->getValueType()->getQualifiedDecoratedName() << "' does not have default constructor");
                        }
                        else if((*it)->getValueType()->asClassType()->isAbstract())
                        {
                            o_semantic_error("class type '"<< (*it)->getValueType()->getQualifiedDecoratedName() << "' is abstract and cannot be used as member");
                        }
                        else 
                        {
                            pBlock->addStatement(
                                o_new_elem(DataMemberInitializationStatement)(
                                    pLocalVariable->toExpression()->dereference()
                                    , *it
                                    , o_new(ConstructorCallExpression)((*it)->getValueType()->asClassType()->getDefaultConstructor())
                                )
                            );
                        }
                    }
                }
            }
            return pLocalVariable; // return back the variable to indicate success
        }
        else 
        {
            Expression* pPrev = nullptr;
            // ((a, b), c), d
            for(auto it = list.begin(); it != list.end(); ++it)
            {
                Expression* pExpr = (*it)->precompileExpression(a_pPrecompiler, a_pScope);
                if(pPrev)
                {
                    pPrev = pPrev ? a_pPrecompiler->getLanguage()->solveBinaryOperator(",", pPrev, pExpr, a_pScope) : nullptr;
                }
                else 
                {
                    pPrev = pExpr;
                }
            }
            return pPrev;
        }
    }

    LanguageElement* CxxBitfieldExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        LocalVariable* pLocalVariable = a_pScope->asLocalVariable();
        if(pLocalVariable AND pLocalVariable->getName() == "this")
        {
            return size->precompileExpression(a_pPrecompiler, a_pScope);
        }
        return nullptr;
    }


    CxxStrings::CxxStrings( const char* someText, size_t len, bool awide /*= false*/ ) : CxxToken(PARSE_TOKEN(StringLiteral))
        , wide(awide)
    {
        literal = (wide) ? "L\"" : "\"";
        literal += string(someText, len);
        literal += "\"";
        if(wide)
        {
            wchar_t* buffer = (wchar_t*)malloc(sizeof(wchar_t)*(len+1));
            for(size_t i = 0; i<len; ++i)
                buffer[i] = someText[i];
            wstr = new wstring(buffer, len);
            wstr->reserve(len);
            for(size_t i = 0; i<len; )
            {
                char c = someText[i++];
                if(c == '\\')
                {
                    if(i == len) { ERRMSG("incomplement escape sequence, end of string found"); return; }
                    char ec = someText[i++];
                    switch(ec)
                    {
                    case 'n': *wstr += '\n'; break;
                    case 'r': *wstr += '\r'; break;
                    case 'a': *wstr += '\a'; break;
                    case 'b': *wstr += '\b'; break;
                    case 'f': *wstr += '\f'; break;
                    case 'v': *wstr += '\v'; break;
                    case 't': *wstr += '\t'; break;
                    case '\\':*wstr += '\\'; break;
                    case '"': *wstr += '"';  break;
                    case 'x':
                        {
                            char hex[3];
                            if(i == len) { ERRMSG("expected hexadecimal escape sequence, end of string found"); return; }
                            hex[0] = someText[i++];
                            if(i == len) { ERRMSG("uncomplete hexadecimal escape sequence, missing 1 hex digit, end of string found"); return; }
                            hex[1] = someText[i++];
                            hex[2] = '\0';
                            unsigned long long hexc = 0;
                            if(sscanf(hex, "%x", &hexc) != EOF)
                            {
                                if(hexc > 0xff)
                                {
                                    ERRMSG("out of range hexadecimal escape sequence");
                                }
                                else 
                                {
                                    *wstr += (wchar_t)hexc;
                                }
                            }
                            else 
                            {
                                ERRMSG("illformed hexadecimal escape sequence");
                            }
                        }
                        break;

                    case 'u':
                        {
                            char hex[5];
                            if(i == len) { ERRMSG("expected hexadecimal escape sequence, end of string found"); return; }
                            hex[0] = someText[i++];
                            if(i == len) { ERRMSG("incomplete 16 bit unicode escape sequence, missing 3 hex digit, end of string found"); return; }
                            hex[1] = someText[i++];
                            if(i == len) { ERRMSG("incomplete 16 bit unicode escape sequence, missing 2 hex digit, end of string found"); return; }
                            hex[2] = someText[i++];
                            if(i == len) { ERRMSG("uncomplete 16 bit unicode escape sequence, missing 1 hex digit, end of string found"); return; }
                            hex[3] = someText[i++];
                            hex[4] = '\0';
                            unsigned long long hexc = 0;
                            if(sscanf(hex, "%x", &hexc) != EOF)
                            {
                                if(hexc > 0xffff)
                                {
                                    ERRMSG("out of range 16 bit unicode escape sequence");
                                }
                                else 
                                {
                                    *wstr += (wchar_t)hexc;
                                }
                            }
                            else 
                            {
                                ERRMSG("illformed 16 bit unicode escape sequence");
                            }
                        }
                        break;

                    case 'U':
                        {
                            char hex[9];
                            if(i == len) { ERRMSG("expected hexadecimal escape sequence, end of string found"); return; }
                            hex[0] = someText[i++];
                            if(i == len) { ERRMSG("incomplete 32 bit unicode escape sequence, missing 7 hex digit, end of string found"); return; }
                            hex[1] = someText[i++];
                            if(i == len) { ERRMSG("incomplete 32 bit unicode escape sequence, missing 6 hex digit, end of string found"); return; }
                            hex[2] = someText[i++];
                            if(i == len) { ERRMSG("incomplete 32 bit unicode escape sequence, missing 5 hex digit, end of string found"); return; }
                            hex[3] = someText[i++];
                            if(i == len) { ERRMSG("uncomplete 32 bit unicode escape sequence, missing 4 hex digit, end of string found"); return; }
                            hex[4] = someText[i++];
                            if(i == len) { ERRMSG("incomplete 32 bit unicode escape sequence, missing 3 hex digit, end of string found"); return; }
                            hex[5] = someText[i++];
                            if(i == len) { ERRMSG("incomplete 32 bit unicode escape sequence, missing 2 hex digit, end of string found"); return; }
                            hex[6] = someText[i++];
                            if(i == len) { ERRMSG("uncomplete 32 bit unicode escape sequence, missing 1 hex digit, end of string found"); return; }
                            hex[7] = someText[i++];
                            hex[8] = '\0';
                            unsigned long long hexc = 0;
                            if(sscanf(hex, "%x", &hexc) != EOF)
                            {
                                if(hexc > 0xffffffff)
                                {
                                    ERRMSG("out of range 32 bit unicode escape sequence");
                                }
                                else 
                                {
                                    uint hexi = (uint)hexc;
                                    *wstr += (wchar_t)hexi&0x0000FFFF;
                                    *wstr += (wchar_t)((hexi&0xFFFF0000)>>16);
                                }
                            }
                            else 
                            {
                                ERRMSG("illformed 32 bit unicode escape sequence");
                            }
                        }
                        break;

                    default:
                        if(c >='0' AND c<='9')
                        {
                            // Octal sequence
                            char oct[4];
                            oct[0] = ec;
                            if(i == len)
                            {
                                if(ec == '0')
                                {
                                    *str += '\0';
                                }
                                else 
                                {
                                    ERRMSG("incomplete octal escape sequence, missing 2 octal digit, end of string found");
                                }
                                return;
                            }
                            oct[1] = someText[i++];
                            if(i == len) { ERRMSG("incomplete octal escape sequence, missing 1 octal digit, end of string found"); return; }
                            oct[2] = someText[i++];
                            oct[3] = '\0';
                            unsigned long long octal;
                            if(sscanf(oct, "%o", &octal) != EOF)
                            {
                                if(octal > 0xff)
                                {
                                    ERRMSG("out of range octal unicode escape sequence, must be in the range 0-255 (0-377 in octal)");
                                }
                                else 
                                {
                                    *wstr += (wchar_t)octal;
                                }
                            }
                        }
                        else *wstr += (wchar_t)ec;
                    }
                }
                else *wstr += (wchar_t)c;
            }
        }
        else 
        {
            str = new string;
            str->reserve(len);
            for(size_t i = 0; i<len; )
            {
                char c = someText[i++];
                if(c == '\\')
                {
                    char ec = someText[i++];
                    switch(ec)
                    {
                    case 'n': *str += '\n'; break;
                    case 'r': *str += '\r'; break;
                    case 'a': *str += '\a'; break;
                    case 'b': *str += '\b'; break;
                    case 'f': *str += '\f'; break;
                    case 'v': *str += '\v'; break;
                    case 't': *str += '\t'; break;
                    case '\\':*str += '\\'; break;
                    case '"': *str += '"';  break;
                    case 'x':
                        {
                            char hex[3];
                            if(i == len) { ERRMSG("expected hexadecimal escape sequence, end of string found"); return; }
                            hex[0] = someText[i++];
                            if(i == len) { ERRMSG("uncomplete hexadecimal escape sequence, missing 1 hex digit, end of string found"); return; }
                            hex[1] = someText[i++];
                            hex[2] = '\0';
                            unsigned long long hexc = 0;
                            if(sscanf(hex, "%x", &hexc) != EOF)
                            {
                                if(hexc > 0xff)
                                {
                                    ERRMSG("out of range hexadecimal escape sequence");
                                }
                                else 
                                {
                                    *str += (char)hexc;
                                }
                            }
                            else 
                            {
                                ERRMSG("illformed hexadecimal escape sequence");
                            }
                        }
                        break;

                    case 'u':
                        {
                            char hex[5];
                            if(i == len) { ERRMSG("expected hexadecimal escape sequence, end of string found"); return; }
                            hex[0] = someText[i++];
                            if(i == len) { ERRMSG("incomplete 16 bit unicode escape sequence, missing 3 hex digit, end of string found"); return; }
                            hex[1] = someText[i++];
                            if(i == len) { ERRMSG("incomplete 16 bit unicode escape sequence, missing 2 hex digit, end of string found"); return; }
                            hex[2] = someText[i++];
                            if(i == len) { ERRMSG("uncomplete 16 bit unicode escape sequence, missing 1 hex digit, end of string found"); return; }
                            hex[3] = someText[i++];
                            hex[4] = '\0';
                            unsigned long long hexc = 0;
                            if(sscanf(hex, "%x", &hexc) != EOF)
                            {
                                if(hexc > 0xffff)
                                {
                                    ERRMSG("out of range 16 bit unicode escape sequence");
                                }
                                else 
                                {
                                    ushort hexs = (ushort)hexc;
                                    *str += (char)hexs&0x00FF;
                                    *str += (char)((hexs&0xFF00)>>8);
                                }
                            }
                            else 
                            {
                                ERRMSG("illformed 16 bit unicode escape sequence");
                            }
                        }
                        break;

                    case 'U':
                        {
                            char hex[9];
                            if(i == len) { ERRMSG("expected hexadecimal escape sequence, end of string found"); return; }
                            hex[0] = someText[i++];
                            if(i == len) { ERRMSG("incomplete 32 bit unicode escape sequence, missing 7 hex digit, end of string found"); return; }
                            hex[1] = someText[i++];
                            if(i == len) { ERRMSG("incomplete 32 bit unicode escape sequence, missing 6 hex digit, end of string found"); return; }
                            hex[2] = someText[i++];
                            if(i == len) { ERRMSG("incomplete 32 bit unicode escape sequence, missing 5 hex digit, end of string found"); return; }
                            hex[3] = someText[i++];
                            if(i == len) { ERRMSG("uncomplete 32 bit unicode escape sequence, missing 4 hex digit, end of string found"); return; }
                            hex[4] = someText[i++];
                            if(i == len) { ERRMSG("incomplete 32 bit unicode escape sequence, missing 3 hex digit, end of string found"); return; }
                            hex[5] = someText[i++];
                            if(i == len) { ERRMSG("incomplete 32 bit unicode escape sequence, missing 2 hex digit, end of string found"); return; }
                            hex[6] = someText[i++];
                            if(i == len) { ERRMSG("uncomplete 32 bit unicode escape sequence, missing 1 hex digit, end of string found"); return; }
                            hex[7] = someText[i++];
                            hex[8] = '\0';
                            unsigned long long hexc = 0;
                            if(sscanf(hex, "%x", &hexc) != EOF)
                            {
                                if(hexc > 0xffffffff)
                                {
                                    ERRMSG("out of range 32 bit unicode escape sequence");
                                }
                                else 
                                {
                                    uint hexi = (uint)hexc;
                                    *str += (char)hexi&0x000000FF;
                                    *str += (char)((hexi&0x0000FF00)>>8);
                                    *str += (char)((hexi&0x00FF0000)>>16);
                                    *str += (char)((hexi&0xFF000000)>>24);
                                }
                            }
                            else 
                            {
                                ERRMSG("illformed 32 bit unicode escape sequence");
                            }
                        }
                        break;

                    default:
                        if(c >='0' AND c<='9')
                        {
                            // Octal sequence
                            char oct[4];
                            oct[0] = ec;
                            if(i == len)
                            {
                                if(ec == '0')
                                {
                                    *str += '\0';
                                }
                                else 
                                {
                                    ERRMSG("incomplete octal escape sequence, missing 2 octal digit, end of string found");
                                }
                                return;
                            }
                            oct[1] = someText[i++];
                            if(i == len) { ERRMSG("incomplete octal escape sequence, missing 1 octal digit, end of string found"); return; }
                            oct[2] = someText[i++];
                            oct[3] = '\0';
                            unsigned long long octal;
                            if(sscanf(oct, "%o", &octal) != EOF)
                            {
                                if(octal > 0xff)
                                {
                                    ERRMSG("out of range octal unicode escape sequence, must be in the range 0-255 (0-377 in octal)");
                                }
                                else 
                                {
                                    *str += (char)octal;
                                }
                            }
                        }
                        else *str += ec;
                    }
                }
                else *str += c;
            }
        }
    }

    void CxxParenthesised::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, vector<LanguageElement*>& out, modifiers_t* modifiers )
    {
        if(parameters)
        {
            for(auto it = parameters->list.begin(); it != parameters->list.end(); ++it)
            {
                LanguageElement* pElem = (*it)->precompile(a_pPrecompiler, a_pScope);
                if(pElem == nullptr)
                {
                    o_semantic_error("invalid type, parameter or argument in parenthesized expression");
                    out.push_back(a_pScope->asBlock() ? (LanguageElement*)Expression::Invalid() : Type::Invalid());
                }
                else 
                {
                    out.push_back(pElem);
                }
            }
        }
        if(modifiers)
        {
            *modifiers |= cvs ? o_const * (cvs->asIdentifier() == "const") : 0;
            if(refQualifier)
            {
                o_assert(refQualifier->size() == 1);
                if(refQualifier->words.back().id.size() == 1)
                {
                    o_assert(refQualifier->words.back().id == "&");
                    *modifiers |= o_lvalue_ref;
                }
                else 
                {
                    o_assert(refQualifier->words.back().id == "&&");
                    *modifiers |= o_rvalue_ref;
                }
            }
        }
    }

    CxxNewParenthesisExpression::CxxNewParenthesisExpression( CxxParameters *aPlace, CxxParameters *aType, CxxExpression *anInit ) : CxxNewExpression(aPlace, aType, anInit)
    {

    }


    LanguageElement* CxxCondition::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        return parameters->precompileExpression(a_pPrecompiler, a_pScope, a_pLHS);
    }

    LanguageElement* CxxDotExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        return CxxDotExpression::precompileParenthesized(a_pPrecompiler, nullptr, a_pScope, a_pLHS);
    }

    LanguageElement* CxxDotExpression::precompileParenthesized( CxxPrecompiler* a_pPrecompiler, CxxParenthesised* a_pParams, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        LanguageElement* pLeft = left->precompile(a_pPrecompiler, a_pScope, a_pLHS);
        Expression* pLeftExpression = pLeft->asExpression();
        NamedElement* pLeftUnderlyingScope = pLeftExpression ? pLeftExpression->getValueType() : pLeft->asNamedElement();
        const string& id = member->asIdentifier();
        if(id.empty())
        {
            o_semantic_error("Illformed identifier on right hand side of '.'");
            if(a_pParams)
            {
                if(pLeftExpression)
                {
                    vector<Expression*> emptyArgs;
                    emptyArgs.push_back(pLeftExpression->dereference());
                    return o_new_elem(CallExpression)(Subroutine::Invalid(), emptyArgs);
                }
                else return Subroutine::Invalid();
            }
            else
            {
                return o_new_elem(DataMemberExpression)(pLeftExpression ? pLeftExpression->dereference() : Expression::Invalid(), DataMember::Invalid());
            }
        }
        Expression* pAccessExpression = nullptr;
        if(a_pParams)
        {
            vector<LanguageElement*> argumentsOrParameters;
            modifiers_t qualifiers = 0;
            a_pParams->precompile(a_pPrecompiler, a_pScope, argumentsOrParameters, &qualifiers);
            vector<Expression*> functionArguments;
            vector<Type*> functionTypes;
            vector<Expression*>* pFunctionArguments = nullptr;
            vector<Type*>* pFunctionTypes = nullptr;
            bool bExpressions = true;
            bool bTypes = NOT(pLeftExpression); /// we don't expect signature with a left hand side being an evaluable expression
            for(auto it = argumentsOrParameters.begin(); it != argumentsOrParameters.end(); ++it)
            {
                LanguageElement* pElement = *it;
                if(pElement->asExpression() AND bExpressions)
                {
                    bTypes = false;
                    functionArguments.push_back(pElement->asExpression());
                    pFunctionArguments = &functionArguments;
                }
                else if(pElement->asType() AND bTypes)
                {
                    bExpressions = false;
                    functionTypes.push_back(pElement->asType());
                    pFunctionTypes = &functionTypes;
                }
                else 
                {
                    o_semantic_error("invalid term in parenthesized expression");
                }
            }
            LanguageElement* pElem = bExpressions 
                                        ? (LanguageElement*)a_pPrecompiler->getLanguage()->qualifiedLookup(pLeft, id, nullptr, pFunctionArguments, a_pScope, nullptr)
                                        : a_pPrecompiler->getLanguage()->solveSubroutine(pLeft, id, nullptr, *pFunctionTypes, qualifiers, a_pScope);
            if(pElem->isInvalid())
            {
                if(bExpressions)
                {
                    o_semantic_error("No member function '"<<id<<"' found '"<<pLeftUnderlyingScope->getQualifiedDecoratedName()<<"' matching given arguments");
                    vector<Expression*> emptyArgs;
                    if(pLeftExpression)
                    {
                        emptyArgs.push_back(pLeftExpression->dereference());
                    }
                    return o_new_elem(CallExpression)(Subroutine::Invalid(), emptyArgs);
                }
                else 
                {
                    o_semantic_error("No function '"<<id<<"' found in '"<<pLeftUnderlyingScope->getQualifiedDecoratedName()<<"' matching given qualifiers and parameter types");
                    return Subroutine::Invalid();
                }
            }
            return pElem;
        }
        else 
        {
            LanguageElement* pElem = a_pPrecompiler->getLanguage()->qualifiedLookup(pLeft, id, nullptr, nullptr, a_pScope, 0);
            if(pElem->isInvalid())
            {
                o_semantic_error("No member '"<<id<<"' found in '"<<pLeftUnderlyingScope->getQualifiedDecoratedName()<<"'");
                return o_new_elem(DataMemberExpression)(pLeftExpression ? pLeftExpression : Expression::Invalid(), DataMember::Invalid());
            }
            return pElem;
        }
    }


    LanguageElement* CxxDotExpression::precompileTemplateParenthesized( CxxPrecompiler* a_pPrecompiler, TemplateSignature* a_pTemplateSignature, CxxParenthesised* a_pParams, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        a_pScope->addScopedElement(a_pTemplateSignature);
        LanguageElement* pElement = precompileParenthesized(a_pPrecompiler, a_pParams, a_pTemplateSignature, a_pLHS, a_Modifiers);
        a_pScope->removeScopedElement(a_pTemplateSignature);
        return pElement;
    }
    LanguageElement* CxxArrowExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        return CxxArrowExpression::precompileParenthesized(a_pPrecompiler, nullptr, a_pScope, a_pLHS);
    }

    LanguageElement* CxxArrowExpression::precompileParenthesized( CxxPrecompiler* a_pPrecompiler, CxxParenthesised* a_pParams, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        Expression* pLeft = left->precompileExpression(a_pPrecompiler, a_pScope, a_pLHS);
        vector<Expression*> args;
        args.push_back(pLeft ? pLeft->dereference() : nullptr);
        if(pLeft->isInvalid()) 
        {
            o_semantic_error("Invalid left hand side of '->' expression");
            if(a_pParams)
                return o_new_elem(CallExpression)(Subroutine::Invalid(), args);
            else
                return o_new_elem(DataMemberExpression)(pLeft ? pLeft->dereference() : Expression::Invalid(), DataMember::Invalid());
        }
        while(pLeft->getValueType()->removeConstReference()->asDataPointerType() == nullptr) // left is not a pointer type
        {
            Expression* pArrowedExpression = a_pPrecompiler->getLanguage()->solveUnaryPostOperator("->", pLeft, a_pScope);
            if(pArrowedExpression->isInvalid()) 
            {
                o_semantic_error("no operator '->' found in type '"<<pLeft->getValueType()->getQualifiedDecoratedName()<<"'");
                if(a_pParams)
                    return o_new_elem(CallExpression)(Subroutine::Invalid(), args);
                else
                    return o_new_elem(DataMemberExpression)(pLeft, DataMember::Invalid());
            }
            pLeft = pArrowedExpression;
        }
        o_assert(pLeft->getValueType()->removeConstReference()->asDataPointerType());
        pLeft = pLeft->dereference(); // dereference pointer
        o_assert(pLeft);
        string id;
        if(member->size() > 1)
        {
             CxxName* pBack = member->takeBack();
             id = pBack->asIdentifier();
             o_assert(id.size());
             pLeft = member->precompileExpression(a_pPrecompiler, a_pScope, pLeft);
        }
        else id = member->asIdentifier();

        if(id.empty())
        {
            o_semantic_error("Illformed identifier on right hand side of '->' expression");
            if(a_pParams)
                return o_new_elem(CallExpression)(Subroutine::Invalid(), args);
            else
                return o_new_elem(DataMemberExpression)(pLeft, nullptr);
        }
        if(a_pParams)
        {
            vector<LanguageElement*> argumentsOrParameters;
            a_pParams->precompile(a_pPrecompiler, a_pScope, argumentsOrParameters);
            vector<Expression*> functionArguments;
            vector<Expression*>* pFunctionArguments = nullptr;
            bool bExpressions = true;
            bool bTypes = false; /// we don't expect signature with a left hand side being an evaluable expression
            for(auto it = argumentsOrParameters.begin(); it != argumentsOrParameters.end(); ++it)
            {
                LanguageElement* pElement = *it;
                if(pElement->asExpression() AND bExpressions)
                {
                    bTypes = false;
                    functionArguments.push_back(pElement->asExpression());
                    pFunctionArguments = &functionArguments;
                }
                else if(pElement->asType() AND bTypes)
                {
                    bExpressions = false;
                }
                else 
                {
                    o_semantic_error("invalid term in parenthesized expression");
                }
            }
            LanguageElement* pElem = a_pPrecompiler->getLanguage()->qualifiedLookup(pLeft, id, nullptr, pFunctionArguments, a_pScope, 0);
            if(pElem->isInvalid())
            {
                o_semantic_error("No member function '"<<id<<"' found in type '"<<pLeft->getValueType()->getQualifiedDecoratedName()<<"' matching the given arguments");
                return o_new_elem(CallExpression)(nullptr, args);
            }
            Expression* pAccessExpression = pElem->asExpression();
            if(pAccessExpression == nullptr)
            {
                o_semantic_error("Illformed member function call");
                return o_new_elem(CallExpression)(nullptr, args);
            }
            return pAccessExpression;
        }
        else
        {
            LanguageElement* pElem = a_pPrecompiler->getLanguage()->qualifiedLookup(pLeft, id, nullptr, nullptr, a_pScope, 0);
            Expression* pAccessExpression = pElem->asExpression();
            if(pAccessExpression == nullptr)
            {
                o_semantic_error("Illformed data member access");
                return o_new_elem(DataMemberExpression)(pLeft, DataMember::Invalid());
            }
            return pAccessExpression;
        }
    }

    LanguageElement* CxxArrowStarExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        return CxxArrowStarExpression::precompileParenthesized(a_pPrecompiler, nullptr, a_pScope, a_pLHS);
    }

    LanguageElement* CxxArrowStarExpression::precompileParenthesized( CxxPrecompiler* a_pPrecompiler, CxxParenthesised* a_pParams, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        vector<Expression*> args;
        Expression* pLeft = left->precompileExpression(a_pPrecompiler, a_pScope, a_pLHS);
        if(pLeft == nullptr OR pLeft->isInvalid()) 
        {
            o_semantic_error("Invalid left hand side of '->*' expression");
            if(a_pParams)
                return o_new_elem(MemberFunctionPointerCallExpression)(nullptr, pLeft, nullptr, args);
            else 
                return o_new_elem(DataMemberPointerExpression)(nullptr, pLeft, nullptr);
        }
        if(pLeft->getValueType()->removeConstReference()->asDataPointerType() == nullptr) // left is not a pointer type
        {
            Expression* pArrowStaredExpression = a_pPrecompiler->getLanguage()->solveBinaryOperator("->*", pLeft, member->precompileExpression(a_pPrecompiler, a_pScope), a_pScope);
            if(pArrowStaredExpression == nullptr OR pArrowStaredExpression->isInvalid()) 
            {
                o_semantic_error("no operator '->*' found for type '"<<pLeft->getValueType()->getQualifiedDecoratedName()<<"'");
                if(a_pParams)
                    return o_new_elem(MemberFunctionPointerCallExpression)(nullptr, pLeft, nullptr, args);
                else 
                    return o_new_elem(DataMemberPointerExpression)(nullptr, pLeft, nullptr);
            }
            pLeft = pArrowStaredExpression;
        }
        o_assert(pLeft->getValueType()->removeConstReference()->asDataPointerType());
        pLeft = pLeft->dereference(); // dereference pointer

        Expression* pMemberExpression = member->precompileExpression(a_pPrecompiler, a_pScope);
        if(pMemberExpression == nullptr OR pMemberExpression->isInvalid())
        {
            o_semantic_error("Invalid expression on right hand side of '->*'");
            if(a_pParams)
                return o_new_elem(MemberFunctionPointerCallExpression)(nullptr, pLeft, pMemberExpression, args);
            else 
                return o_new_elem(DataMemberPointerExpression)(nullptr, pLeft, pMemberExpression);
        }

        if(a_pParams)
        {
            MemberFunctionPointerType* pMemberFunctionPointerType = pMemberExpression->getValueType()->removeConstReference()->asMemberFunctionPointerType();
            if(pMemberFunctionPointerType == nullptr)
            {
                o_semantic_error("Expression on right hand side of '->*' is not a member function pointer type");
                return o_new_elem(MemberFunctionPointerCallExpression)(pMemberFunctionPointerType, pLeft, pMemberExpression, args);
            }

            ClassType* pClassType = pMemberFunctionPointerType->getObjectType();

            if(NOT(pLeft->getValueType()->removeConstReference()->isKindOf(pClassType)))
            {
                o_semantic_error("Incompatible member function pointer call, type '"
                    <<pLeft->getValueType()->removeConstReference()->getQualifiedDecoratedName()
                    <<"' is not a derived class of '"
                    <<pClassType->getQualifiedDecoratedName()
                    <<"'");
                return o_new_elem(MemberFunctionPointerCallExpression)(pMemberFunctionPointerType, pLeft, pMemberExpression, args);
            }

            vector<LanguageElement*> elems;
            a_pParams->precompile(a_pPrecompiler, a_pScope, elems);
            for(auto it = elems.begin(); it != elems.end(); ++it)
            {
                Expression* pArg = (*it)->asExpression();
                if(pArg == nullptr)
                {
                    o_semantic_error((*it)->translate()<<" is not an expression");
                }
                args.push_back(pArg);
            }
            conversions convs;
            pMemberFunctionPointerType->implicitConversions(cplusplus(), args, a_pScope, convs);
            for(size_t i = 0; i<args.size(); ++i)
            if(convs.hasNull())
            {
                o_semantic_error("arguments don't match member function pointer type signature");
                return o_new_elem(MemberFunctionPointerCallExpression)(pMemberFunctionPointerType, pLeft, pMemberExpression, args);
            }
            return o_new(MemberFunctionPointerCallExpression)(pMemberFunctionPointerType, pLeft, pMemberExpression, args);
        }
        else 
        {
            DataMemberPointerType* pDataMemberPointerType = pMemberExpression->getValueType()->removeConstReference()->asDataMemberPointerType();
            if(pDataMemberPointerType == nullptr)
            {
                o_semantic_error("expression on right hand side of '->*' is not a data member pointer type");
                return o_new_elem(DataMemberPointerExpression)(DataMemberPointerType::Invalid(), pLeft, pMemberExpression);
            }

            ClassType* pClassType = pDataMemberPointerType->getObjectType();

            if(NOT(pLeft->getValueType()->removeConstReference()->isKindOf(pClassType)))
            {
                o_semantic_error("incompatible data member pointer, type '"
                    <<pLeft->getValueType()->removeConstReference()->getQualifiedDecoratedName()
                    <<"' is not a derived class of '"
                    <<pClassType->getQualifiedDecoratedName()
                    <<"'");
                return o_new_elem(DataMemberPointerExpression)(pDataMemberPointerType, pLeft, pMemberExpression);
            }
            return o_new_elem(DataMemberPointerExpression)(pDataMemberPointerType, pLeft, pMemberExpression);
        }
    }

    LanguageElement* CxxDotStarExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        return CxxDotStarExpression::precompileParenthesized(a_pPrecompiler, nullptr, a_pScope, a_pLHS);
    }

    LanguageElement* CxxDotStarExpression::precompileParenthesized( CxxPrecompiler* a_pPrecompiler, CxxParenthesised* a_pParams, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        vector<Expression*> args;
        Expression* pLeft = left->precompileExpression(a_pPrecompiler, a_pScope, a_pLHS);
        if(pLeft->isInvalid()) 
        {
            o_semantic_error("invalid left hand side of '.*' expression");
            if(a_pParams)
                return o_new_elem(MemberFunctionPointerCallExpression)(MemberFunctionPointerType::Invalid(), pLeft, member->precompileExpression(a_pPrecompiler, a_pScope), args);
            else 
                return o_new_elem(DataMemberPointerExpression)(DataMemberPointerType::Invalid(), pLeft, member->precompileExpression(a_pPrecompiler, a_pScope));
        }
        if(NOT(pLeft->hasEffectiveAddress()))
        {
            o_semantic_error("invalid r-value on left hand side of '.*' expression");
            if(a_pParams)
                return o_new_elem(MemberFunctionPointerCallExpression)(MemberFunctionPointerType::Invalid(), pLeft, member->precompileExpression(a_pPrecompiler, a_pScope), args);
            else 
                return o_new_elem(DataMemberPointerExpression)(DataMemberPointerType::Invalid(), pLeft, member->precompileExpression(a_pPrecompiler, a_pScope));
        }
        Expression* pMemberExpression = member->precompileExpression(a_pPrecompiler, a_pScope);
        if(pMemberExpression->isInvalid())
        {
            o_semantic_error("invalid expression on right hand side of '.*'");
            if(a_pParams)
                return o_new_elem(MemberFunctionPointerCallExpression)(MemberFunctionPointerType::Invalid(), pLeft, pMemberExpression, args);
            else 
                return o_new_elem(DataMemberPointerExpression)(DataMemberPointerType::Invalid(), pLeft, pMemberExpression);
        }

        if(a_pParams)
        {
            vector<Expression*> args;
            MemberFunctionPointerType* pMemberFunctionPointerType = pMemberExpression->getValueType()->removeConstReference()->asMemberFunctionPointerType();
            if(pMemberFunctionPointerType->isInvalid())
            {
                o_semantic_error("expression on right hand side of '.*' is not a member function pointer type");
                return o_new_elem(MemberFunctionPointerCallExpression)(pMemberFunctionPointerType, pLeft, pMemberExpression, args);
            }

            ClassType* pClassType = pMemberFunctionPointerType->getObjectType();

            if(NOT(pLeft->getValueType()->removeConstReference()->isKindOf(pClassType)))
            {
                o_semantic_error("incompatible member function pointer call, type '"
                    <<pLeft->getValueType()->removeConstReference()->getQualifiedDecoratedName()
                    <<"' is not a derived class of '"
                    <<pClassType->getQualifiedDecoratedName()
                    <<"'");
                return o_new_elem(MemberFunctionPointerCallExpression)(pMemberFunctionPointerType, pLeft, pMemberExpression, args);
            }

            vector<LanguageElement*> elems;
            a_pParams->precompile(a_pPrecompiler, a_pScope, elems);
            for(auto it = elems.begin(); it != elems.end(); ++it)
            {
                Expression* pArg = (*it)->asExpression();
                args.push_back(pArg);
            }
            conversions convs;
            pMemberFunctionPointerType->implicitConversions(cplusplus(), args, a_pScope, convs);
            if(convs.hasNull())
            {
                o_semantic_error("arguments don't match member function pointer type signature");
            }
            return o_new(MemberFunctionPointerCallExpression)(pMemberFunctionPointerType, pLeft, pMemberExpression, args);
        }
        else 
        {
            DataMemberPointerType* pDataMemberPointerType = pMemberExpression->getValueType()->removeConstReference()->asDataMemberPointerType();
            if(pDataMemberPointerType == nullptr)
            {
                o_semantic_error("expression on right hand side of '->*' is not a data member pointer type");
                return o_new_elem(DataMemberPointerExpression)(pDataMemberPointerType, pLeft, pMemberExpression);
            }

            ClassType* pClassType = pDataMemberPointerType->getObjectType();

            if(NOT(pLeft->getValueType()->removeConstReference()->isKindOf(pClassType)))
            {
                o_semantic_error("incompatible data member pointer, type '"
                    <<pLeft->getValueType()->removeConstReference()->getQualifiedDecoratedName()
                    <<"' is not a derived class of '"
                    <<pClassType->getQualifiedDecoratedName()
                    <<"'");
            }
            return o_new_elem(DataMemberPointerExpression)(pDataMemberPointerType, pLeft, pMemberExpression);
        }
    }

    LanguageElement* CxxEnumSpecifierId::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        vector<NumericConstant*> constants;
        Type* pType = enumerators->precompile(a_pPrecompiler, a_pScope, constants);
        if(pType == nullptr OR pType->asIntegralType() == nullptr)
        {
            o_semantic_error("invalid enum declarator");
        }
        Enum* pEnum = o_new(Enum)(name->asIdentifier(), pType ? pType->asIntegralType() : nullptr, 0);
        for(auto it = constants.begin(); it != constants.end(); ++it)
        {
            pEnum->addConstant(*it);
        }
        return pEnum;
    }

    Type* CxxEnumerators::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, vector<NumericConstant*>& constants )
    {
        ulonglong startValue = 0;
        reflection::ETypeId biggestTypeId = reflection::e_uint;
        vector<string> names;
        vector<ulonglong> values;
        for(auto it = list.begin(); it != list.end(); ++it)
        {
            ConstantExpression* pConstantExpression = (*it)->precompile(a_pPrecompiler, a_pScope);
            const string& name = (*it)->name->asIdentifier();
            if(name.empty()) 
            {
                o_semantic_error("illformed enum value name");
            }
            names.push_back(name);
            if(pConstantExpression)
            {
                pConstantExpression->internalEval(&startValue);
                values.push_back(startValue);
                reflection::ETypeId typeId = pConstantExpression->getValueType()->getTypeId();
                if(typeId > biggestTypeId)
                    biggestTypeId = typeId;
            }
            else 
            {
                values.push_back(startValue);
            }
            startValue++;
        }
        switch(biggestTypeId)
        {
#define __o_enum_case(type)\
        case reflection::e_##type:\
            for(size_t i = 0; i<values.size(); ++i)\
            {\
                constants.push_back(constant<type>((type)values[i], names[i]));\
            }\
            return typeOf<type>();

            __o_enum_case(int);
            __o_enum_case(uint);
            __o_enum_case(long);
            __o_enum_case(ulong);
            __o_enum_case(longlong);
            __o_enum_case(ulonglong);

#undef __o_enum_case
        }
        return nullptr;
    }

    ConstantExpression* CxxEnumerator::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope ) const
    {
        if(expr == nullptr) return nullptr;
        Expression* pExpr = expr->precompileExpression(a_pPrecompiler, a_pScope);
        if(pExpr == nullptr)
        {
            o_semantic_error("invalid enum value expression");
            return nullptr;
        }
        ConstantExpression* pConstantExpression = pExpr->asConstantExpression();
        if(pConstantExpression == nullptr OR pConstantExpression->isInvalid())
        {
            o_semantic_error("enum only accepts constant integral values");
            return nullptr;
        }
        if(pConstantExpression->getValueType()->asIntegralType() == nullptr)
        {
            o_semantic_error("enum constant value must be an integral constant value");
            return nullptr;
        }
        return pConstantExpression;
    }


    LanguageElement* CxxAccessibilitySpecifier::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
    {
        ClassType* pScope = a_pScope->asClassType();
        if(pScope == nullptr)
        {
            o_semantic_error("access specifier outside class type scope not allowed");
        }
        const string& id = specifier->asIdentifier();
        if(id.empty()) 
        {
            o_semantic_error("invalid access specifier");
            return nullptr;
        }
        switch(id[2])
        {
        case 'o': pScope->setDefaultAccess(o_protected_access); break;
        case 'i': pScope->setDefaultAccess(o_private_access); break;
        case 'b': pScope->setDefaultAccess(o_public_access); break;
        }
        return nullptr;
    }


    LanguageElement* CxxBreakStatement::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        Block* pBlock = a_pScope->asBlock();
        if(pBlock == nullptr)
        {
            o_semantic_error("'break' outside block statement");
            BranchStatement* pBranchStatement = o_new_elem(BranchStatement)();
            pBranchStatement->setInvalid();
            return pBranchStatement;
        }
        LabelStatement* pBreakLabel = a_pPrecompiler->topBreakLabel();
        if(pBreakLabel == nullptr)
        {
            o_semantic_error("'break' outside breakable statement (while/for/do/switch)");
        }
        return o_new_elem(BranchStatement)(pBreakLabel);
    }


    LanguageElement* CxxContinueStatement::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        Block* pBlock = a_pScope->asBlock();
        if(pBlock == nullptr)
        {
            o_semantic_error("'continue' outside block statement");
            BranchStatement* pBranchStatement = o_new_elem(BranchStatement)();
            pBranchStatement->setInvalid();
            return pBranchStatement;
        }
        LabelStatement* pContinueLabel = a_pPrecompiler->topContinueLabel();
        if(pContinueLabel == nullptr)
        {
            o_semantic_error("'continue' outside continuable statement (while/for/do)");
        }
        return o_new_elem(BranchStatement)(pContinueLabel);
    }

    LanguageElement* CxxSwitchStatement::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        Block* pBlock = a_pScope->asBlock();

        o_assert(pBlock);

        Block* pSwitchStatement = o_new(Block)(pBlock, "switch");

        Expression* pTestValue = testExpr->precompileExpression(a_pPrecompiler, pSwitchStatement);
        if(pTestValue == nullptr)
        {
            pSwitchStatement->setInvalid();
            o_semantic_error("invalid switch test expression");
        }
        else
        {
            if(pTestValue->getValueType()->removeReference()->removeConst()->asIntegralType() == nullptr)
            {
                pSwitchStatement->setInvalid();
                o_semantic_error("switch expression of type '"<<pTestValue->getValueType()->getQualifiedDecoratedName()<<"' is illegal, test expression must be an integral expression");
            }
        }

        Block* pInnerBlock = o_new(Block)(pSwitchStatement);

        LabelStatement* pBreakLabel = a_pPrecompiler->pushBreakLabel();

        vector<Statement*> branchIfs;
        BranchStatement* pDefaultBranch = nullptr;
        CxxStatements* statements = statement->asStatements();
        if(statements == nullptr)
        {
            o_semantic_error("illformed switch statement");
            return nullptr;
        }
        for(auto it = statements->list.begin(); it != statements->list.end(); ++it)
        {
            CxxStatement* pStatement = *it;
            CxxCaseStatement* pCaseStatement = pStatement->asCaseStatement();
            if(pCaseStatement)
            {
                LabelStatement* pCaseLabel = o_new(LabelStatement)(pCaseStatement->expr ? "case" : "default");
                if(pCaseStatement->expr)
                {
                    Expression* pExpression = pCaseStatement->expr->precompileExpression(a_pPrecompiler, pInnerBlock);
                    if(pExpression == nullptr)
                    {
                        o_semantic_error("invalid 'case' value expression, must be an integral constant expression "<< pTestValue->getValueType()->getQualifiedDecoratedName());
                    }
                    ConstantExpression* pConstantExpression = pExpression->asConstantExpression();
                    if(pConstantExpression == nullptr)
                    {
                        o_semantic_error("invalid 'case' value expression, must be an integral constant expression "<< pTestValue->getValueType()->getQualifiedDecoratedName());
                    }
                    Expression* pTest = a_pPrecompiler->getLanguage()->solveBinaryOperator("==", pTestValue, pConstantExpression, 0);
                    if(pTest == nullptr)
                    {
                        o_semantic_error("invalid 'case' value expression, must be an integral constant expression "<< pTestValue->getValueType()->getQualifiedDecoratedName());
                    }
                    BranchIfStatement* pBranch = o_new(BranchIfStatement)(pTest);
                    pBranch->setLabelStatement(pCaseLabel);
                    branchIfs.push_back(pBranch);
                }
                else
                {
                    if(pDefaultBranch)
                    {
                        o_semantic_error("'default' label already defined");
                    }
                    else pDefaultBranch = o_new(BranchStatement);
                    pDefaultBranch->setLabelStatement(pCaseLabel);
                }
            }
            else 
            {
                pStatement->precompile(a_pPrecompiler, pInnerBlock);
            }
        }
        if(pDefaultBranch)
            branchIfs.push_back(pDefaultBranch);
        pInnerBlock->prependStatements(branchIfs);
        pInnerBlock->addStatement(pBreakLabel);
        a_pPrecompiler->popBreakLabel(pBreakLabel);
        return nullptr;
    }

    LanguageElement* CxxWhileStatement::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        Block* pBlock = a_pScope->asBlock();

        o_assert(pBlock);

        Block* pWhileStatement = o_new(Block)(pBlock, "while");

        Expression* pCondition = CxxWhileStatement::testExpr->precompileExpression(a_pPrecompiler, pWhileStatement);

        if(NOT(pCondition->isInvalid()))
        {
            pCondition = a_pPrecompiler->getLanguage()->convert(pCondition, typeOf<bool>(), reflection::e_implicit_conversion, a_pScope);
        }

        Expression* pConditionClone = pCondition->clone();

        LabelStatement* pBreakLabelStatement = a_pPrecompiler->pushBreakLabel();
        LabelStatement* pContinueLabelStatement = a_pPrecompiler->pushContinueLabel();
        LabelStatement* pCodeStartLabelStatement = o_new(LabelStatement)("while");

        BranchIfNotStatement* pBranchIfNotStatement = o_new(BranchIfNotStatement)(pCondition);
        pBranchIfNotStatement->setLabelStatement(pBreakLabelStatement);

        BranchIfStatement* pBranchIfStatement = o_new(BranchIfStatement)(pConditionClone);
        pBranchIfStatement->setLabelStatement(pCodeStartLabelStatement);

        // Branch to break if test fails
        pWhileStatement->addStatement(pBranchIfNotStatement);

        // Code start label
        pWhileStatement->addStatement(pCodeStartLabelStatement);

        // Code
        if(statement)
        {
            statement->precompile(a_pPrecompiler, pWhileStatement);
        }

        // 'continue' goes here
        pWhileStatement->addStatement(pContinueLabelStatement);

        // branch to code if test succeed
        pWhileStatement->addStatement(pBranchIfStatement);

        // 'break' goes here
        pWhileStatement->addStatement(pBreakLabelStatement);

        a_pPrecompiler->popBreakLabel(pBreakLabelStatement);

        a_pPrecompiler->popContinueLabel(pContinueLabelStatement);

        return nullptr;
    }

    LanguageElement* CxxDoWhileStatement::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        Block* pBlock = a_pScope->asBlock();
        
        o_assert(pBlock);

        Block* pDoWhileStatement = o_new(Block)(pBlock, "do");

        Expression* pCondition = testExpr->precompileExpression(a_pPrecompiler, pDoWhileStatement);

        if(NOT(pCondition->isInvalid()))
        {
            pCondition = a_pPrecompiler->getLanguage()->convert(pCondition, typeOf<bool>(), reflection::e_implicit_conversion, a_pScope);
        }

        LabelStatement*     pCodeStartLabelStatement = o_new(LabelStatement)("do");

        pDoWhileStatement->addStatement(pCodeStartLabelStatement);


        LabelStatement*     pBreakLabelStatement = a_pPrecompiler->pushBreakLabel();
        LabelStatement*     pContinueLabelStatement = a_pPrecompiler->pushContinueLabel();

        // do
        if(statement)
        {
            statement->precompile(a_pPrecompiler, pDoWhileStatement);
        }

        // 'continue' goes here
        pDoWhileStatement->addStatement(pContinueLabelStatement);

        // test condition and jump to do block if succeeds
        BranchIfStatement* pBranchIfStatement = o_new(BranchIfStatement)(pCondition);
        pBranchIfStatement->setLabelStatement(pCodeStartLabelStatement);

        // 'break' goes here
        pDoWhileStatement->addStatement(pBreakLabelStatement);

        a_pPrecompiler->popBreakLabel(pBreakLabelStatement);

        a_pPrecompiler->popContinueLabel(pContinueLabelStatement);

        return nullptr;
    }


    LanguageElement* CxxForStatement::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        Block* pBlock = a_pScope->asBlock();

        o_assert(pBlock);

        Block* pForStatement = o_new(Block)(pBlock, "for");

        LabelStatement*     pBreakLabelStatement = a_pPrecompiler->pushBreakLabel();
        LabelStatement*     pContinueLabelStatement = a_pPrecompiler->pushContinueLabel();
        LabelStatement*     pCodeStartLabelStatement = o_new(LabelStatement)("for");

        // Init
        if(init)
        {
            Expression* pInit = init->precompileExpression(a_pPrecompiler, pForStatement);
            if(pInit == nullptr)
            {
                o_semantic_error("invalid 'for' initializer");
            }
            else
            {
                pForStatement->addStatement(o_new(ExpressionStatement)(pInit));
            }
        }

        // Condition
        Expression* pCondition = nullptr;
        Expression* pConditionClone = nullptr;
        if(test)
        {
            pCondition = test->precompileExpression(a_pPrecompiler, pForStatement);
            if(pCondition == nullptr)
            {
                pForStatement->setInvalid();
                o_semantic_error("invalid 'for' condition");
                pConditionClone = nullptr;
            }
            else pConditionClone = pCondition->clone();
        }

        BranchIfNotStatement* pBranchIfNotStatement = pCondition ? o_new(BranchIfNotStatement)(pCondition) : nullptr;
        if(pBranchIfNotStatement)
        {
            pBranchIfNotStatement->setLabelStatement(pBreakLabelStatement);
        }

        BranchStatement* pBranchIfStatement = pConditionClone
            ? o_new(BranchIfStatement)(pConditionClone)
            : o_new(BranchStatement);

        pBranchIfStatement->setLabelStatement(pCodeStartLabelStatement);

        // If test exists, branch to break if test fails
        if(pBranchIfNotStatement)
        {
            pForStatement->addStatement(pBranchIfNotStatement);
        }

        // Code start label
        pForStatement->addStatement(pCodeStartLabelStatement);

        // Code
        if(content)
        {
            content->precompile(a_pPrecompiler, pForStatement);
        }

        // Updates

        // 'continue' goes here
        pForStatement->addStatement(pContinueLabelStatement);

        // updates
        
        pForStatement->addStatement(o_new(ExpressionStatement)(step->precompileExpression(a_pPrecompiler, pForStatement)));

        // branch to code if test exists and succeed, or direct branch if test doesn't exist
        pForStatement->addStatement(pBranchIfStatement);

        // 'break' goes here
        pForStatement->addStatement(pBreakLabelStatement);

        a_pPrecompiler->popBreakLabel(pBreakLabelStatement);

        a_pPrecompiler->popContinueLabel(pContinueLabelStatement);

        return nullptr;
    }

    LanguageElement* CxxGotoStatement::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        const string& id = label->asIdentifier();
        if(id.empty())
        {
            o_semantic_error("illformed label name");
            BranchStatement* pBranch = o_new(BranchStatement)(nullptr);
            pBranch->setInvalid();
            return pBranch;
        }
        Block* pBlock = a_pScope->asBlock();

        o_assert(pBlock);
        o_assert(pBlock->getSubroutine());
        LabelStatement* pLabelStatement = a_pPrecompiler->findOrCreateLabel(pBlock->getSubroutine(), id);

        pBlock->addStatement(o_new(BranchStatement)(pLabelStatement));

        return nullptr;
    }


    LanguageElement* CxxBlock::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        Block* pBlock = a_pScope->asBlock();

        o_assert(pBlock);
        Block* pNewBlock = o_new(Block)(pBlock);

        statements->precompile(a_pPrecompiler, pNewBlock);

        return nullptr;
    }


    LanguageElement* CxxIfStatement::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        Block* pBlock = a_pScope->asBlock();

        o_assert(pBlock);

        Block* pIfStatement = o_new(Block)(pBlock, "if");
        Expression* pCondition = test->precompileExpression(a_pPrecompiler, pIfStatement);
        if(pCondition == nullptr)
        {
            pIfStatement->setInvalid();
            o_semantic_error("invalid 'if' condition");
        }
        LabelStatement* pElseLabel = o_new(LabelStatement)("else");
        LabelStatement* pEndLabel = nullptr;
        BranchIfNotStatement* pBranchIfNot = o_new(BranchIfNotStatement)(pCondition);
        pBranchIfNot->setLabelStatement(pElseLabel);
        pIfStatement->addStatement(pBranchIfNot);

        thenContent->precompile(a_pPrecompiler, pIfStatement);

        if(elseContent)
        {
            // at the end of 'then' part, if 'else' exists, jump to end
            BranchStatement* pBranchToEnd = o_new(BranchStatement);
            pEndLabel = o_new(LabelStatement)("if");
            pBranchToEnd->setLabelStatement(pEndLabel);
            pIfStatement->addStatement(pBranchToEnd);
        }
        pIfStatement->addStatement(pElseLabel);
        if(pEndLabel)
        {
            elseContent->precompile(a_pPrecompiler, pIfStatement);
            pIfStatement->addStatement(pEndLabel);
        }
        return nullptr;
    }


    LanguageElement* CxxNamespaceAliasDeclaration::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        Namespace* pNamespaceScope = a_pScope->asNamespace();
        if(pNamespaceScope == nullptr)
        {
            o_semantic_error("namespace alias declaration not allowed outside namespace scope");
        }
        Namespace* pNamespace = name->precompileNamespace(a_pPrecompiler, a_pScope, a_pLHS);
        if(pNamespace == nullptr)
        {
            o_semantic_error("unknown or illformed namespace '"<<name->toString()<<"'");
        }
        string aliasId = alias->asIdentifier();
        if(aliasId.empty())
        {
            o_semantic_error("illformed alias id '"<<alias->toString()<<"'");
        }
        else 
        {
            if(pNamespaceScope)
            {
                pNamespaceScope->addNamespaceAlias(aliasId, pNamespace);
            }
        }
        return pNamespace;
    }

    string CxxTemplateArguments::toString() const
    {
        string result = "<";
        for(auto it = list.begin(); it != list.end(); ++it)
        {
            if(it != list.begin())
                result+=",";
            result+=(*it)->toString();
        }
        result+=">";
        return result;
    }

    void CxxTemplateArguments::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, vector<LanguageElement*>& out )
    {
        for(auto it = list.begin(); it != list.end(); ++it)
        {
            out.push_back((*it)->precompile(a_pPrecompiler, a_pScope));
        }
    }

    LanguageElement* CxxReturnStatement::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        Block* pBlock = a_pScope->asBlock();
        o_assert(pBlock->getSubroutine());
        ReturnStatement* pReturnStatement = o_new(ReturnStatement);
        pBlock->addStatement(pReturnStatement);
        Type* pReturnType = pReturnStatement->getSubroutine()->getReturnType();
        if(pReturnType == typeOf<void>() AND expr)
        {
            pReturnStatement->setInvalid();
            o_semantic_error("void function returning value");
        }
        else if(pReturnType != typeOf<void>() AND expr == nullptr)
        {
            pReturnStatement->setInvalid();
            o_semantic_error("non-void' function must return a value");
        }
        else if(expr)
        {
            Expression* pExpression = expr->precompileExpression(a_pPrecompiler, pBlock);
            pReturnStatement->setExpression(a_pPrecompiler->getLanguage()->convert(pExpression, pReturnType, reflection::e_implicit_conversion, pBlock));
        }
        return pReturnStatement;
    }

    LanguageElement* CxxSimpleDeclaration::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        return expr->precompile(a_pPrecompiler, a_pScope, a_pLHS);
    }

    LanguageElement* CxxSimpleDeclaration::precompileTemplate( CxxPrecompiler* a_pPrecompiler, TemplateSignature* a_pTemplateSignature, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ ) 
    {
        return expr->precompileTemplate(a_pPrecompiler, a_pTemplateSignature, a_pScope, a_pLHS);
    }

    LanguageElement* CxxTemplateDeclaration::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        TemplateSignature* pSignature = parameters->precompile(a_pPrecompiler, a_pScope, a_pLHS);
        if(pSignature == nullptr)
        {
            o_semantic_error("invalid template signature");
        }
        return declaration->precompileTemplate(a_pPrecompiler, pSignature, a_pScope, a_pLHS);
    }

    LanguageElement* CxxTryBlockStatement::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        o_assert_no_implementation();
        return nullptr;
    }

    LanguageElement* CxxUsingDeclaration::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        o_assert_no_implementation();
//         if(a_pScope->asScope() == nullptr)
//         {
//             o_semantic_error("illegal using directive");
//             return nullptr;
//         }
//         if(isTypename)
//         {
//             Type* pType = name->precompileType(a_pPrecompiler, a_pScope, a_pLHS);
//             if(pType == nullptr)
//             {
//                 o_semantic_error("unknown type '"<<name->toString()<<"'");
//             }
//             else a_pScope->asScope()->addAlias(pType, pType->getName());
//         }
//         else if(a_pScope->asNamespace())
//         {
//             LanguageElement* pLanguageElement = name->precompile(a_pPrecompiler, a_pScope, a_pLHS);
//             if(pLanguageElement == nullptr)
//             {
//                 o_semantic_error("unknown function or type '"<<name->toString()<<"'");
//             }
//             else a_pScope->asNamespace()->addUsing(pLanguageElement);
//         }
//         else if(a_pScope->asClassType())
//         {
//             LanguageElement* pLanguageElement = name->precompile(a_pPrecompiler, a_pScope, a_pLHS);
//             if(pLanguageElement == nullptr)
//             {
//                 o_semantic_error("unknown member '"<<name->toString()<<"'");
//             }
//             if(pLanguageElement->asMember() == nullptr)
//             {
//                 o_semantic_error("only member allowed in class type using declarations");
//             }
//             else a_pScope->asClassType()->addUsing(pLanguageElement);
//         }
//         else 
//         {
//             LanguageElement* pLanguageElement = name->precompile(a_pPrecompiler, a_pScope, a_pLHS);
//             if(pLanguageElement == nullptr)
//             {
//                 o_semantic_error("unknown function or type '"<<name->toString()<<"'");
//             }
//             else a_pScope->asScope()->addUsing(pLanguageElement);
//         }
        return nullptr;
    }

    LanguageElement* CxxUsingNamespaceDirective::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
//         if(a_pScope->asNamespace() == nullptr)
//         {
//             o_semantic_error("using namespace directive can only be declared in a namespace scope");
//             return nullptr;
//         }
//         else
//         {
//             Namespace* pNamespace = name->precompileNamespace(a_pPrecompiler, a_pScope, a_pLHS);
//             if(pNamespace == nullptr)
//             {
//                 o_semantic_error("unknown namespace '"<<name->toString()<<"'");
//             }
//             return a_pScope->asNamespace()->addUsing(pNamespace);
//         }
        return nullptr;
    }

    LanguageElement* CxxLabelStatement::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
    {
        Block* pBlock = a_pScope->asBlock();
        o_assert(pBlock AND pBlock->getSubroutine());
        const string& id = label->asIdentifier();
        if(id.empty())
        {
            o_semantic_error("illformed label name '"<<label->toString()<<"'");
        }
        pBlock->addStatement(a_pPrecompiler->findOrCreateLabel(pBlock->getSubroutine(), id));
        statement->precompile(a_pPrecompiler, a_pScope, a_pLHS);
        return nullptr;
    }

    LanguageElement* CxxCallExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        if(declSpecifier)
        {
            if(expr->declSpecifier == nullptr)
            {
                expr->declSpecifier = declSpecifier;
            }
            else 
            {
                declSpecifier->swallow(expr->declSpecifier);
                expr->declSpecifier = declSpecifier;
            }
            declSpecifier = nullptr;
        }
        return expr->precompileParenthesized(a_pPrecompiler, parenthesised, a_pScope, a_pLHS, a_Modifiers);
    }

    LanguageElement* CxxCallExpression::precompileTemplate( CxxPrecompiler* a_pPrecompiler, TemplateSignature* a_pTemplateSignature, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        if(declSpecifier)
        {
            if(expr->declSpecifier == nullptr)
            {
                expr->declSpecifier = declSpecifier;
            }
            else 
            {
                declSpecifier->swallow(expr->declSpecifier);
                expr->declSpecifier = declSpecifier;
            }
            declSpecifier = nullptr;
        }
        return expr->precompileTemplateParenthesized(a_pPrecompiler, a_pTemplateSignature, parenthesised, a_pScope, a_pLHS, a_Modifiers);
    }

    LanguageElement* CxxVariableDeclarationExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        Type* pType = typeExpression->precompileType(a_pPrecompiler, a_pScope, a_pLHS);
        if(pType == nullptr)
        {
            o_semantic_error("undefined variable type");
        }
        CxxName* name = nameExpression->asName();
        if(name)
        {
            Type* pTestSpecified = name->trySpecify(a_pPrecompiler, pType);
            if(pTestSpecified)
            {
                return pTestSpecified;
            }
            else
            {
                const string& id = name->asIdentifier();
                if(id.empty())
                {
                    o_semantic_error("illformed declaration name");
                }
            }
        }
        o_assert_no_implementation();
        return nullptr;
    }

    LanguageElement* CxxBinaryExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
    {
        LanguageElement* pLeft = nullptr;
        LanguageElement* pRight = nullptr;
        if(op == "*" OR op == "&")
        {
            pLeft = left->precompile(a_pPrecompiler, a_pScope);
            Type* pType = pLeft->asType();
            if(pType)
            {
                if(declSpecifier)
                    pType = declSpecifier->specify(a_pPrecompiler, pType);
                if(pType->isInvalid())
                {
                    o_semantic_error("invalid type declaration specifier");
                }
                auto* decl = new CxxDeclSpecifierId(op);
                pType = decl->specify(a_pPrecompiler, pType);
                if(pType->isInvalid())
                {
                    o_semantic_error("invalid type qualifier");
                }
                CxxName* name = right->asName();
                if(name)
                {
                    Type* pTestSpecified = name->trySpecify(a_pPrecompiler, pType);
                    if(pTestSpecified) 
                        return pTestSpecified;
                    const string& id = name->asIdentifier();
                    if(id.empty())
                    {
                        o_semantic_error("illformed parameter or variable identifier "<<name->toString());
                    }
                    if(a_pPrecompiler->hasFlag(CxxPrecompiler::e_Flag_ExpressionMode))
                    {
                        /// if in expression mode we do not provide local variables or parameters, which will not be usable, but only the corresponding type
                        return pType;
                    }
                    if(a_pScope->asStatement())
                    {
                        // we are inside a statement, we expect a local variable definition
                        return o_new_elem(LocalVariable)(pType, id);
                    }
                    else 
                    {
                        return o_new_elem(Parameter)(pType, id);
                    }
                }
                else 
                {
                    o_semantic_error("illformed parameter or variable identifier "<<name->toString());
                }
            }
        }
        Expression* pLeftExpression = nullptr;
        if(pLeft)
        {
            pLeftExpression = pLeft->asExpression();
            if(pLeftExpression == nullptr) pLeftExpression = Expression::Invalid();
        }
        else 
        {
            pLeftExpression = left->precompileExpression(a_pPrecompiler, a_pScope);
        }
        Expression* pRightExpression = right->precompileExpression(a_pPrecompiler, a_pScope);
        
        return a_pPrecompiler->getLanguage()->solveBinaryOperator(op, pLeftExpression, pRightExpression, a_pScope);
    }

    LanguageElement* CxxArrayAccessExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        LanguageElement* pElement = expression->precompile(a_pPrecompiler, a_pScope, a_pLHS);
        o_assert(pElement);
        Expression* pIndex = index->precompileExpression(a_pPrecompiler, a_pScope);
        Expression* pExpression = pElement->asExpression();
        if(pElement->asType())
        {
            ConstantExpression* pConstantIndex = pIndex->asConstantExpression();
            size_t size = 0;
            pIndex = a_pPrecompiler->getLanguage()->convert(pIndex, typeOf<size_t>(), reflection::e_implicit_conversion, a_pScope);
            if(pIndex->isInvalid()) 
                return Type::Invalid();
            pIndex->load(&size);
            if(size == 0)
            {
                o_semantic_error("illegal array type with '0' size");
                return Type::Invalid();
            }
            return pElement->asType()->arrayType(size);
        }
        else if(pExpression)
        {
            return a_pPrecompiler->getLanguage()->solveBinaryOperator("[]", pExpression, pIndex, a_pScope);
        }
        else 
        {
            return a_pPrecompiler->getLanguage()->solveBinaryOperator("[]", Expression::Invalid(), pIndex, a_pScope);
        }
    }

    LanguageElement* CxxAbstractFunctionExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        vector<LanguageElement*> elements;
        vector<Expression*> expressions;
        parenthesised->precompile(a_pPrecompiler, a_pScope, elements, nullptr);
        if(elements.size() == 1)
            return elements.back();
        int state = 0;
        for(auto it = elements.begin(); it != elements.end(); ++it)
        {
            Expression* pExpression = (*it)->asExpression();
            if(pExpression != nullptr)
            {
                if(state == 2)
                {
                    o_semantic_error("illformed parenthesized expression");
                    return nullptr;
                }
                expressions.push_back(pExpression);
                state = 1;
            }
            else 
            {
                if(state == 1)
                {
                    o_semantic_error("illformed parenthesized expression");
                    return nullptr;
                }
                state = 2;
            }
        }
        if(state == 1)
        {
            Expression* pPrev = nullptr;
            // ((a, b), c), d
            for(auto it = expressions.begin(); it != expressions.end(); ++it)
            {
                Expression* pExpr = (*it);
                if(pPrev)
                {
                    pPrev = pPrev ? a_pPrecompiler->getLanguage()->solveBinaryOperator(",", pPrev, pExpr, a_pScope) : nullptr;
                }
                else 
                {
                    pPrev = pExpr;
                }
            }
            return pPrev;
        }
        return nullptr;
    }


    LanguageElement* CxxStringLiteralExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        if(stringLiteral->wide)
        {
            return o_new_elem(WStringLiteralExpression)(stringLiteral->literal, *stringLiteral->wstr);
        }
        else 
        {
            return o_new_elem(StringLiteralExpression)(stringLiteral->literal, *stringLiteral->str);
        }
    }

    LanguageElement* CxxParameter::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
    {
        LanguageElement* pElement = expr->precompile(a_pPrecompiler, a_pScope, a_pLHS);
        if(pElement == nullptr) return nullptr;
        Type* pType = pElement->asType();
        if(pType == nullptr)
        {
            LocalVariable* pLocalVariable = pElement->asLocalVariable();
            if(pLocalVariable)
            {
                if(init) 
                {
                    Expression* pExpression = init->precompileExpression(a_pPrecompiler, a_pScope);
                    pLocalVariable->setInitializationExpression(pExpression);
                }
                return pLocalVariable;
            }
            else 
            {
                if(init)
                {
                    o_assert_no_implementation();
                    return nullptr;
                }
                return pElement;
            }
        }
        return pType;
    }

    void CxxAccessSpecifier::precompile( CxxPrecompiler* a_pPrecompiler, modifiers_t& modifiers )
    {
        const string& id = asIdentifier();
        if(id.empty())
        {
            o_semantic_error("illegal access specifier");
        }
        if(id == "public") modifiers |= o_public_access;
        else if(id == "protected") modifiers |= o_protected_access;
        else if(id == "private") modifiers |= o_private_access;
        else { o_assert_no_implementation(); }
    }


    Class* CxxBaseSpecifier::precompile( CxxPrecompiler* a_pPrecompiler, Class* a_pDerivedClass, modifiers_t& modifiers )
    {
        accessSpecifier->precompile(a_pPrecompiler, modifiers);
        modifiers |= (isVirtual * o_virtual);
        LanguageElement* pElement = name->precompile(a_pPrecompiler, a_pDerivedClass, nullptr);
        if(pElement->isInvalid())
        {
            o_semantic_error("undeclared base class '"<<name->toString()<<"'");
        }
        Class* pBaseClass = pElement->asClass();
        if(pBaseClass == nullptr)
        {
            o_semantic_error("referenced base '"<<name->toString()<<"' is not a class");
        }
        else 
        {
            if(pBaseClass == a_pDerivedClass)
            {
                o_semantic_error("class cannot inherits from itself");
            }
            if(pBaseClass->isKindOf(a_pDerivedClass))
            {
                o_semantic_error("illegal cyclic inheritance, given base class derives itself from the current class");
            }
            if(a_pDerivedClass->isKindOf(pBaseClass))
            {
                o_semantic_error("base class redefinition");
            }
            if(NOT(pBaseClass->isFinalized()))
            {
                o_semantic_error("use of incomplete class '"<<pBaseClass->getQualifiedDecoratedName()<<"'");
            }
        }
        return pBaseClass;
    }

    void CxxBaseSpecifiers::precompile( CxxPrecompiler* a_pPrecompiler, Class* a_pClass )
    {
        for(auto it = list.begin(); it != list.end(); ++it)
        {
            modifiers_t modifiers = 0;
            Class* pBaseClass = (*it)->precompile(a_pPrecompiler, a_pClass, modifiers);
            a_pClass->addBaseClass(pBaseClass);
        }
    }

    ClassType* CxxClass::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, ClassType* a_pPreviousDeclaration )
    {
        const string& keyid = key->asIdentifier();
        o_assert(keyid.size());
        string nameid = name->asIdentifier();
        o_assert(a_pPreviousDeclaration == nullptr OR (a_pPreviousDeclaration->getName() == nameid AND a_pPreviousDeclaration->isPureDeclaration()));
        ClassType* pClassType = nullptr;
        Class* pClass = nullptr;
        if(nameid.empty())
        {
            if(name->size() > 1)
            {
                o_semantic_error("illegal scoped name "<<name->toString()<<" in template "<<keyid<<" declaration");
            }
            else 
            {
                if(a_pScope->asTemplateSpecialization() == nullptr)
                {
                    o_semantic_error("illegal template arguments on non-template declaration");
                }
                nameid = name->front().id;
            }
        }
        if(keyid == "class" OR keyid == "struct")
        {
            if(a_pPreviousDeclaration)
            {
                if(a_pPreviousDeclaration->asStructure())
                {
                    o_semantic_error("incoherent type declaration previously seen as structure, and now as class");
                }
                else if(a_pPreviousDeclaration->getDefaultAccess() == o_public_access AND keyid == "class")
                {
                    o_semantic_error("incoherent type declaration previously seen as struct, and now as class");
                }
                else if(a_pPreviousDeclaration->getDefaultAccess() == o_private_access AND keyid == "struct")
                {
                    o_semantic_error("incoherent type declaration previously seen as class, and now as struct");
                }
                pClassType = a_pPreviousDeclaration;
            }
            else
            {
                pClassType = pClass = o_new(Class)(nameid);
                if(keyid[0] == 's')
                    pClassType->setDefaultAccess(o_public_access);
            }
            if(baseClasses)
            {
                baseClasses->precompile(a_pPrecompiler, pClass);
            }
        }
        else if(keyid == "structure")
        {
            if(a_pPreviousDeclaration)
            {
                if(a_pPreviousDeclaration->asClass())
                {
                    o_semantic_error("incoherent type declaration previously seen as class, and now as structure");
                }
                pClassType = a_pPreviousDeclaration;
            }
            else pClassType = o_new(Structure)(nameid);
            if(baseClasses)
            {
                o_semantic_error("structure cannot have base classes");
            }
        }
        o_assert(pClassType);
        return pClassType;
    }

    LanguageElement* CxxClass::precompileTemplate( CxxPrecompiler* a_pPrecompiler, TemplateSignature* a_pTemplateSignature, LanguageElement* a_pScope )
    {
        Template* pTemplate = nullptr;
        const string& nameid = name->asIdentifier();
        CxxTemplateArguments* specialization = nullptr;
        Scope* pScope = a_pScope->asScope();
        o_assert(pScope);
        if(name->size() == 1)
        {
            specialization = name->front().templateArgs;
            if(pScope)
            {
                // Look for an existing template in current source scope
                pTemplate = pScope->getTemplate(name->front().id);
                if(pTemplate == nullptr)
                {
                    o_semantic_error("symbol '"<<name->front().id<<"' does not refer to a template name");
                }
            }
        }

        if(pTemplate == nullptr)
        {
            pTemplate = o_new(Template)(a_pTemplateSignature, nameid);
            if(pScope == a_pPrecompiler->getSource()) /// current scope is the source
            {
                a_pPrecompiler->getSource()->getPackage()->getCounterpartNamespace()->addTemplate(pTemplate);
            }
            if(specialization)
            {
                /// specialization signature => trying to specialize a non existing template
                pTemplate->setInvalid();
                o_semantic_error("no template with name '"<<nameid<<"' found in current scope");
            }
            /// add template to current scope
            pScope->addTemplate(pTemplate);
            NamedElement* pPrevBody = pTemplate->getEmptyTemplateSpecialization()->getBody();
            pTemplate->getEmptyTemplateSpecialization()->setBody(
                    CxxClass::precompile(a_pPrecompiler, pTemplate->getEmptyTemplateSpecialization(), pPrevBody ? pPrevBody->asClassType() : nullptr)
                );
            return pTemplate->getEmptyTemplateSpecialization();
        }
        /// Template already defined => must be a specialization
        else if(pTemplate AND NOT(pTemplate->getEmptyTemplateSpecialization()->isPureDeclaration()))
        {
            /// But not a specialization => redefinition of this template => error
            if(!specialization)
            {
                o_semantic_error("template with name '"<<nameid<<"' already defined in scope '"<<static_cast<NamedElement*>(a_pScope)->getQualifiedDecoratedName()<<"'");
                TemplateSpecialization* pInvalidNewEmptySpec = o_new(TemplateSpecialization)(pTemplate, a_pTemplateSignature, vector<LanguageElement*>(), CxxClass::precompile(a_pPrecompiler, pTemplate));
                pScope->addTemplateSpecialization(pInvalidNewEmptySpec);
                return pInvalidNewEmptySpec;
            }
            /// Specialization of this template
            else 
            {
                TemplateSpecialization* pSpec = nullptr;
                if(a_pTemplateSignature->getParameterCount() == 0)
                {
                    /// Empty template signature => full specialization
                    vector<LanguageElement*> arguments;
                    specialization->precompile(a_pPrecompiler, a_pScope, arguments);
                    if(NOT(pTemplate->getTemplateSignature()->acceptsArguments(arguments)))
                    {
                        o_semantic_error("template arguments does not match template signature");
                    }
                    if(pTemplate->getTemplateSpecialization(arguments))
                    {
                        o_semantic_error("template already instanciated and cannot be explicitely specialized");
                    }
                    pSpec = o_new(TemplateSpecialization)(pTemplate, a_pTemplateSignature, arguments);
                    o_assert(pSpec->getBody() == nullptr);
                    pScope->addTemplateSpecialization(pSpec);
                    pSpec->setBody(CxxClass::precompile(a_pPrecompiler, pSpec, nullptr));
                    o_assert(pSpec->isInvalid() OR pSpec->isFull());
                }
                else 
                {
                    /// partial specialization

                    /// first solve template specialization partial/full arguments
                    a_pScope->addScopedElement(a_pTemplateSignature);
                    vector<LanguageElement*> arguments;
                    specialization->precompile(a_pPrecompiler, a_pTemplateSignature, arguments);
                    a_pScope->removeScopedElement(a_pTemplateSignature);

                    if(NOT(pTemplate->getTemplateSignature()->acceptsArguments(arguments)))
                    {
                        o_semantic_error("partial template specialization arguments do not match template signature");
                    }
                    if(pTemplate->getTemplateSpecialization(arguments))
                    {
                        o_semantic_error("template specialization already defined");
                    }
                    pSpec = o_new(TemplateSpecialization)(pTemplate, a_pTemplateSignature, arguments);
                    pScope->addTemplateSpecialization(pSpec);
                    pSpec->setBody(CxxClass::precompile(a_pPrecompiler, pSpec, nullptr));
                    for(auto it = a_pTemplateSignature->beginParameters(); it != a_pTemplateSignature->endParameters(); ++it)
                    {
                        TemplateParameter* pParam = *it;
                        if(NOT(pParam->getPlaceholder() AND pParam->getPlaceholder()->asNamedElement()->getReferencingElementCount()))
                        {
                            o_semantic_error("template parameter '"<<pParam->getName()<<"' never used in template specialization arguments");
                            pSpec->setInvalid();
                        }
                    }
                }
                return pSpec;
            } 
        }
        else 
        {
            pTemplate = o_new(Template)(a_pTemplateSignature, nameid);
            a_pPrecompiler->getSource()->addTemplate(pTemplate);
            a_pPrecompiler->getSource()->addTemplateSpecialization(pTemplate->getEmptyTemplateSpecialization());
            NamedElement* pPrevBody = pTemplate->getEmptyTemplateSpecialization()->getBody();
            ClassType* pClassType = CxxClass::precompile(a_pPrecompiler, pTemplate->getEmptyTemplateSpecialization(), pPrevBody ? pPrevBody->asClassType() : nullptr);
            if(pPrevBody == nullptr)
            {
                pTemplate->getEmptyTemplateSpecialization()->setBody(pClassType);
            }
            return pTemplate->getEmptyTemplateSpecialization();
        }
    }

    LanguageElement* CxxClassMembers::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        ClassType* pClassType = class_->precompile(a_pPrecompiler, a_pScope)->asClassType();
        o_assert(a_pPrecompiler->getSource());
        if(pClassType->isDefined())
        {
            o_semantic_error(class_->key->asIdentifier()<<" already defined");
        }
        pClassType->setDefined();
        if(a_pScope == a_pPrecompiler->getSource())
        {
            a_pPrecompiler->getSource()->getPackage()->getCounterpartNamespace()->addType(pClassType);
            a_pPrecompiler->getSource()->addType(pClassType);
        }
        else 
        {
            Scope* pScope = a_pScope->asScope();
            if(pScope == nullptr)
            {
                o_semantic_error(class_->key->asIdentifier()<<" definition outside legal scope");
                pClassType->setInvalid();
            }
            else 
            {
                pScope->addType(pClassType);
            }
            if(pClassType->getOwner() == nullptr)
            {
                a_pPrecompiler->getSource()->addType(pClassType);
            }
        }
        if(a_pPrecompiler->getPass() < CxxPrecompiler::e_Pass_Members)
        {
            a_pPrecompiler->queue(CxxPrecompiler::e_Pass_Members, pClassType, nullptr, members, nullptr, nullptr, nullptr);
        }
        else 
        {
            members->precompile(a_pPrecompiler, pClassType);
        }
        return pClassType;
    }

    LanguageElement* CxxClassMembers::precompileTemplate( CxxPrecompiler* a_pPrecompiler, TemplateSignature* a_pTemplateSignature, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
    {
        TemplateSpecialization* pTemplateSpecialization = class_->precompileTemplate(a_pPrecompiler, a_pTemplateSignature, a_pScope)->asTemplateSpecialization();
        o_assert(a_pPrecompiler->getSource());
        o_assert(pTemplateSpecialization->getBody());
        if(pTemplateSpecialization->isDefined())
        {
            o_assert(pTemplateSpecialization->getBody()->isDefined());
            o_semantic_error("template "<<class_->key->asIdentifier()<<" specialization already defined");
        }
        pTemplateSpecialization->setDefined();
        o_assert(pTemplateSpecialization->getBody());
        pTemplateSpecialization->getBody()->setDefined();
        Scope* pScope = a_pScope->asScope();
        o_assert(pScope AND a_pScope->asNamespace() == nullptr, "scope must be type, source or block, nothing else");
        if(a_pPrecompiler->getPass() < CxxPrecompiler::e_Pass_Members)
        {
            a_pPrecompiler->queue(CxxPrecompiler::e_Pass_Members, pTemplateSpecialization->getBody(), nullptr, members, nullptr, nullptr, a_pTemplateSignature);
        }
        else 
        {
            members->precompileTemplate(a_pPrecompiler, a_pTemplateSignature, pTemplateSpecialization->getBody(), nullptr, 0);
        }
        return pTemplateSpecialization;
    }

    LanguageElement* CxxMemberDeclarations::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS, modifiers_t a_Modifiers )
    {
        ClassType* pClassType = a_pScope->asClassType();
        o_assert(pClassType);
        if(a_pPrecompiler->getPass() == CxxPrecompiler::e_Pass_Members)
        {
            //a_pPrecompiler->queue(CxxPrecompiler::e_Pass_Blocks, a_pScope, nullptr, this);
            for(auto it = list.begin(); it != list.end(); ++it)
            {
                (*it)->precompile(a_pPrecompiler, pClassType);
            }
        }
//         else 
//         {
//             o_assert(a_pPrecompiler->getPass() == CxxPrecompiler::e_Pass_Blocks);
//             pClassType->setFinalized();
//         }
        return nullptr;
    }

    LanguageElement* CxxMemberDeclarations::precompileTemplate( CxxPrecompiler* a_pPrecompiler, TemplateSignature* a_pTemplateSignature, LanguageElement* a_pScope, LanguageElement* a_pLHS, modifiers_t a_Modifiers )
    {
        ClassType* pClassType = a_pScope->asClassType();
        o_assert(pClassType);
        TemplateSpecialization* pSpec = pClassType->getOwner()->asTemplateSpecialization();
        o_assert(pSpec);
        if(a_pPrecompiler->getPass() == CxxPrecompiler::e_Pass_Members)
        {
            for(auto it = list.begin(); it != list.end(); ++it)
            {
                (*it)->precompile(a_pPrecompiler, pClassType);
            }
        }
        return nullptr;
    }
    LanguageElement* CxxMemberDeclaration::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
    {
        o_assert(a_pScope->asClassType());
        return declaration->precompile(a_pPrecompiler, a_pScope, a_pLHS);
    }

    LanguageElement* CxxFunctionBody::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        // If we precompile a function body, we suppose having at worst root block from Subroutine::createBlock
        Block* pBlock = a_pScope->asBlock();

        o_assert(pBlock);
        Block* pNewBlock = o_new(Block)(pBlock);

        statement->precompile(a_pPrecompiler, pNewBlock);

        return nullptr;
    }

    LanguageElement* CxxTypedExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        Type* pType = typeName->precompileType(a_pPrecompiler, a_pScope, a_pLHS);
        CxxName* name = expr->asName();
        if(name)
        {
            Type* pTestSpecified = name->trySpecify(a_pPrecompiler, pType);
            if(pTestSpecified)
                return pTestSpecified;
        }
        o_assert_no_implementation();
        return nullptr;
    }

    LanguageElement* CxxTypedExpression::precompileParenthesized( CxxPrecompiler* a_pPrecompiler, CxxParenthesised* a_pParen, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        CxxName* name = expr->asName();
        if(name)
        {
            return (new CxxTypedName(typeName, name))->precompileParenthesized(a_pPrecompiler, a_pParen, a_pScope, a_pLHS, a_Modifiers);
        }
        o_assert_no_implementation();
        return nullptr;
    }

    LanguageElement* CxxTypedName::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        const string& id = typeName->asIdentifier();
        configureDeclSpecifiers(a_pPrecompiler);
        Type* pType = nullptr;
        if(id == "unsigned")
        {
            Type* pTypeToUnsign = name->precompileType(a_pPrecompiler, a_pScope, a_pLHS);
            if(pTypeToUnsign == nullptr)
            {
                pType = typeOf<unsigned>();
            }
            else switch(pTypeToUnsign->getTypeId())
            {
            case reflection::e_char:
                return typeName->declSpecifier ? typeName->declSpecifier->specify(a_pPrecompiler, typeOf<uchar>()) : typeOf<uchar>();
            case reflection::e_short:
                return typeName->declSpecifier ? typeName->declSpecifier->specify(a_pPrecompiler, typeOf<ushort>()) : typeOf<ushort>();
            case reflection::e_int:
                return typeName->declSpecifier ? typeName->declSpecifier->specify(a_pPrecompiler, typeOf<uint>()) : typeOf<uint>();
            case reflection::e_long:
                return typeName->declSpecifier ? typeName->declSpecifier->specify(a_pPrecompiler, typeOf<ulong>()) : typeOf<ulong>();
            case reflection::e_longlong:
                return typeName->declSpecifier ? typeName->declSpecifier->specify(a_pPrecompiler, typeOf<ulonglong>()) : typeOf<ulonglong>();
            default:
                o_semantic_error("invalid fundamental type '"<<pTypeToUnsign->getName()<<"' after 'unsigned' promoter");
            }
        }
        else if(id == "long")
        {
            Type* pTypeToPromote = name->precompileType(a_pPrecompiler, a_pScope, a_pLHS);
            if(pTypeToPromote == nullptr)
            {
                pType = typeOf<long>();
            }
            else switch(pTypeToPromote->getTypeId())
            {
            case reflection::e_int:
                return typeName->declSpecifier ? typeName->declSpecifier->specify(a_pPrecompiler, typeOf<long>()) : typeOf<long>();
            case reflection::e_long:
                return typeName->declSpecifier ? typeName->declSpecifier->specify(a_pPrecompiler, typeOf<long long>()) : typeOf<long long>();
            case reflection::e_double:
                return typeName->declSpecifier ? typeName->declSpecifier->specify(a_pPrecompiler, typeOf<long double>()) : typeOf<long double>();
            default:
                o_semantic_error("invalid fundamental type '"<<pTypeToPromote->getName()<<"' after 'long' promoter");
            }
        }
        if(pType == nullptr)
            pType = typeName->precompileType(a_pPrecompiler, a_pScope, a_pLHS);
        if(pType == nullptr)
        {
            o_semantic_error("unknown type '"<<typeName->toString()+"'");
        }
        if(typeName->declSpecifier)
        {
            pType = typeName->declSpecifier->specify(a_pPrecompiler, pType);
            if(pType->isInvalid())
            {
                o_semantic_error("illegal type specifiers for type '"<<typeName->toString()+"'");
            }
        }
        Type* pTestSpecified = name->trySpecify(a_pPrecompiler, pType);
        if(pTestSpecified)
            return pTestSpecified;

        /// If in expression mode, we don't need parameters, but only types
        if(a_pPrecompiler->hasFlag(CxxPrecompiler::e_Flag_ExpressionMode))
            return pType;

        // We have a variable declaration of format "TYPE variable"
        if(a_pScope->asSignature() OR a_pScope->asSubroutine())
        {
            const string& id = name->asIdentifier();
            if(id.empty())
            {
                o_semantic_error("illformed parameter name "<<name->toString());
            }
            return o_new(Parameter)(pType, id);
        }
        else if(a_pScope->asBlock())
        {
            const string& id = name->asIdentifier();
            if(id.empty())
            {
                o_semantic_error("illformed local variable name "<<name->toString());
            }
            return o_new(LocalVariable)(pType, id);
        }
        else if(a_pScope->asNamespace())
        {
            const string& id = name->asIdentifier();
            if(id.empty())
            {
                o_semantic_error("illformed global variable name "<<name->toString());
            }
            return o_new(Variable)(pType, id, nullptr);
        }
        return nullptr;
    }

    void CxxTypedName::configureDeclSpecifiers(CxxPrecompiler* a_pPrecompiler)
    {
        if(declSpecifier)
        {
            if(typeName->declSpecifier == nullptr)
            {
                typeName->declSpecifier = declSpecifier;
            }
            else 
            {
                declSpecifier->swallow(typeName->declSpecifier);
                typeName->declSpecifier = declSpecifier;
            }
            declSpecifier = nullptr;
        }
        if(typeName->declSpecifier)
        {
            o_assert(name->declSpecifier == nullptr);
            CxxName* pStatic = typeName->declSpecifier->extract("static");
            if(pStatic)
            {
                if(pStatic->size() != 1)
                {
                    o_semantic_error("illegal duplicate of 'static' specifier");
                }
                if(typeName->declSpecifier->size() == 0)
                    typeName->declSpecifier = nullptr;
                pStatic->resize(1);
                if(name->declSpecifier)
                    pStatic->swallow(name->declSpecifier);
                name->declSpecifier = pStatic;
            }
        }
    }

    LanguageElement* CxxTypedName::precompileParenthesized( CxxPrecompiler* a_pPrecompiler, CxxParenthesised* a_pParen, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        configureDeclSpecifiers(a_pPrecompiler);
        Type* pType = typeName->precompileType(a_pPrecompiler, a_pScope, a_pLHS);
        o_assert(pType);
        Type* pTestSpecified = name->trySpecify(a_pPrecompiler, pType);
        if(pTestSpecified)
            return pTestSpecified;
        CxxName* back = name->takeBack(); // split last word to obtain LHS scope
        LanguageElement* pLHS = nullptr;
        if(name->declSpecifier)
        {
            if(back->declSpecifier)
            {
                name->declSpecifier->swallow(back->declSpecifier);
                back->declSpecifier = name->declSpecifier;
                name->declSpecifier = nullptr;
            }
            else back->declSpecifier = name->declSpecifier;
        }
        if(name->size())
        {
            pLHS = name->precompile(a_pPrecompiler, a_pScope);
            if(pLHS == nullptr)
            {
                o_semantic_error("invalid member function scope name");
            }
            else if(pLHS->asClassType() == nullptr)
            {
                o_semantic_error("undefined member function class or struct scope");
            }
            else if(pLHS->getSource() != a_pPrecompiler->getSource())
            {
                o_semantic_error("out-of-class member function definition must stay in the same source as the owner class");
            }
        }
        LanguageElement* pElement = back->precompileTypedParenthesized(a_pPrecompiler, pType, a_pParen, a_pScope, pLHS, a_Modifiers);
        if(pElement == nullptr)
        {
            o_semantic_error("invalid function declaration");
        }
        return pElement;
    }


    string CxxName::word::toString() const
    {
        string result = id;
        if(templateArgs)
        {
            result+=templateArgs->toString();
        }
        return result;
    }


    TemplateSignature* CxxTemplateParameters::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        TemplateSignature* pSignature = o_new(TemplateSignature);
        a_pScope->addScopedElement(pSignature);
        vector<TemplateParameter*> templateParameters;
        for(auto it = list.begin(); it != list.end(); ++it)
        {
            TemplateParameter* pParameter = (*it)->precompile(a_pPrecompiler, pSignature, a_pLHS);
            if(pParameter == nullptr)
            {
                o_semantic_error("invalid template parameter");
            }
            pSignature->addParameter(pParameter);
        }
        a_pScope->removeScopedElement(pSignature);
        return pSignature;
    }


    TemplateParameter* CxxTemplateParameter::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        return expr->precompileTemplateParameter(a_pPrecompiler, a_pScope, a_pLHS);
    }


    TemplateParameter* CxxClassTypeParameter::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        return o_new(TemplateParameter)(o_new(PlaceholderType)(expr ? expr->asName()->asIdentifier() : ""));
    }


    TemplateParameter* CxxTemplatedTypeParameter::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        return o_new(TemplateParameter)(o_new(PlaceholderTemplate)(expr ? expr->asName()->asIdentifier() : "", parameters->precompile(a_pPrecompiler, a_pScope, a_pLHS)));
    }


    LanguageElement* CxxFunctionDefinition::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */, modifiers_t a_Modifiers /*= 0*/ )
    {
        if(a_pPrecompiler->getPass() < CxxPrecompiler::e_Pass_Members)
        {
            TemplateSignature* pTS = a_pScope->asTemplateSignature();
            a_pPrecompiler->queue(CxxPrecompiler::e_Pass_Members, pTS ? pTS->getOwner() : a_pScope, a_pLHS, this, nullptr, nullptr, pTS);
            return nullptr;
        }
        else 
        {
            LanguageElement* pElement = header->precompile(a_pPrecompiler, a_pScope, a_pLHS, o_defined);
            o_assert(pElement AND pElement->asSubroutine());
            Subroutine* pSubroutine = pElement->asSubroutine();
            if(pSubroutine->getOwner() == nullptr) // function definition
            {
                a_pScope->asScope()->addSubroutine(pSubroutine);
            }
            Block* pBlock = pSubroutine->createBlock();
            if(a_pPrecompiler->getPass() < CxxPrecompiler::e_Pass_Blocks)
            {
                a_pPrecompiler->queue(CxxPrecompiler::e_Pass_Blocks, pBlock, nullptr, body, nullptr, nullptr, nullptr);
            }
            else 
            {
                body->precompile(a_pPrecompiler, pBlock);
            }
            return nullptr;
        }
    }

    LanguageElement* CxxFunctionDefinition::precompileTemplate( CxxPrecompiler* a_pPrecompiler, TemplateSignature* a_pTemplateSignature, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ ) 
    {
        if(a_pPrecompiler->getPass() < CxxPrecompiler::e_Pass_Members)
        {
            a_pPrecompiler->queue(CxxPrecompiler::e_Pass_Members, a_pScope, a_pLHS, this, nullptr, nullptr, a_pTemplateSignature);
            return nullptr;
        }
        else 
        {
            LanguageElement* pElement = header->precompileTemplate(a_pPrecompiler, a_pTemplateSignature, a_pScope, a_pLHS, o_defined);
            o_assert(pElement AND pElement->asSubroutine());
            Subroutine* pSubroutine = pElement->asSubroutine();
            if(pSubroutine->getOwner() == nullptr) // function definition
            {
                a_pScope->asScope()->addSubroutine(pSubroutine);
            }
            Block* pBlock = pSubroutine->createBlock();
            if(a_pPrecompiler->getPass() < CxxPrecompiler::e_Pass_Blocks)
            {
                a_pPrecompiler->queue(CxxPrecompiler::e_Pass_Blocks, pBlock, nullptr, body, nullptr, nullptr, nullptr);
            }
            else 
            {
                body->precompile(a_pPrecompiler, pBlock);
            }
            return nullptr;
        }
    }

    LanguageElement* CxxStatement::precompileTemplate( CxxPrecompiler* a_pPrecompiler, TemplateSignature* a_pTemplateSignature, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ ) 
    {
        o_assert_no_implementation();
        a_pScope->addScopedElement(a_pTemplateSignature);
        LanguageElement* pElement = precompile(a_pPrecompiler, a_pTemplateSignature, a_pLHS, a_Modifiers);
        a_pScope->removeScopedElement(a_pTemplateSignature);
        return pElement;
    }

    LanguageElement* CxxDataExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/, modifiers_t a_Modifiers /*= 0 */ )
    {
        serialization::DataBase* pDataBase = phantom::application()->getDataBase();
        if(pDataBase == nullptr)
        {
            o_semantic_error("no data base defined, cannot use the '@' operator for this module");
        }
        return o_new(DataExpression)(pDataBase, o_new_elem(ConstantExpression)(constant<o_NESTED_TYPE CxxUnderlyingFundamental<hex_t>::type>(hex->number)));
    }

    LanguageElement* CxxStatements::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
    {
        if(a_pPrecompiler->getPass() == CxxPrecompiler::e_Pass_SourceMembersLocal) // source pass
        {
            std::sort(list.begin(), list.end(), source_scope_sorter());
        }
        for(auto it = list.begin(); it != list.end(); ++it)
        {
            (*it)->precompile(a_pPrecompiler, a_pScope);
        }
        return nullptr;
    }

    LanguageElement* CxxImportDeclaration::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
    {
        int pass = a_pPrecompiler->getPass();

        bool bStatic = false;
        bool bPublic = false; 

        if(declSpecifier != nullptr)
        {
            for(auto it = declSpecifier->begin(); it != declSpecifier->end(); ++it)
            {
                if(it->id == "public") bPublic = true;
                else if(it->id == "static") bStatic = true;
            }
        }

        string qualified = qualifiedName->asIdentifier();
        o_assert(qualified.size());

        size_t pos = qualified.find_last_of(".");
        string packageName = pos != string::npos ? qualified.substr(0, pos) : ""; 
        string sourceName = pos != string::npos ? qualified.substr(pos+1) : qualified;     

        Package* pPackage = nullptr;
        if(packageName.empty())
        {
            pPackage = a_pPrecompiler->getSource()->getPackage();
        }
        else 
        {
            string currentPackageName = a_pPrecompiler->getSource()->getPackage()->getName();
            pPackage = phantom::package(currentPackageName.size() ? (currentPackageName+'.'+packageName) : packageName);
        }
        Source* pSource = Source::Invalid();
        if(pPackage == nullptr)
        {
            o_semantic_error("package '"<<packageName<<"' not found");
            pSource = Source::Invalid();
            pPackage = Package::Invalid();
        }
        else
        {
            pSource = pPackage->getSource(sourceName);
            if(pSource == nullptr)
            {
                o_semantic_error("source '"<<sourceName<<"' not found in package '"<<packageName<<"'");
                pSource = Source::Invalid();
            }
            if(pSource == a_pPrecompiler->getSource())
            {
                o_semantic_error("source '"<<sourceName<<"' cannot import itself");
                pSource = Source::Invalid();
            }
        }

        if(bStatic)
        {
            Alias* pStaticImport = o_new(Alias)(bPublic ? 0 : o_private_visibility);
            a_pScope->asScope()->addAlias(pStaticImport);
            /// STATIC IMPORT
            if(symbols AND symbols->list.size())
            {
                o_semantic_error("static imports cannot be used with selective symbol imports");
            }
            vector<string> importWords;
            split( importWords, qualified, boost::is_any_of("."), boost::token_compress_on ); // SplitVec == { "hello abc","ABC","aBc goodbye" }
            importWords.erase( std::remove_if( importWords.begin(), importWords.end(), 
                boost::bind( &string::empty, _1 ) ), importWords.end() );

            auto it = importWords.begin();

            NamedElement* pElement = a_pScope->getUniqueElement(*it);
            Alias* pImportAlias = nullptr;
            if(pElement)
            {
                Alias* pAlias = pElement->asAlias();
                if(pAlias)
                {
                    if(pAlias->getAliasedElement() == nullptr)
                    {
                        pImportAlias = pAlias;
                    }
                    else 
                    {
                        o_semantic_error("static import package '"<<*it<<"' conflicts with alias '"<<pAlias->getName()<<"'");
                    }
                }
                else 
                {
                    o_semantic_error("static import package '"<<*it<<"' conflicts with symbol '"<<pElement->getQualifiedDecoratedName()<<"'");
                }
            }
            if(pImportAlias == nullptr)
            {
                pImportAlias = o_new(Alias)(*it);
                pStaticImport->addAlias(pImportAlias);
            }

            for(; it != importWords.end(); ++it)
            {
                Alias* pChildAlias = pImportAlias->getAlias(*it);
                if(pChildAlias == nullptr)
                {
                    pChildAlias = o_new(Alias)(*it);
                    pImportAlias->addAlias(pChildAlias);
                }
                pImportAlias = pChildAlias;
            }
            pImportAlias->addAlias(o_new(Alias)(pSource));
        }
        else 
        {
            if(symbols AND symbols->list.size())
            {
                /// SELECTIVE IMPORTS
                for(auto it = symbols->list.begin(); it != symbols->list.end(); ++it)
                {
                    CxxImportSymbolDeclaration* importedSymbol = (*it);
                    const string& symbolName = importedSymbol->symbol->asIdentifier();
                    const string& alias = importedSymbol->alias ? importedSymbol->alias->asIdentifier() : symbolName;
                    a_pScope->asSource()->addAlias(o_new(Alias)(o_new(Import)(pSource, symbolName), alias));
                }
            }
            else 
            {
                /// STANDARD IMPORT
                a_pScope->asScope()->addAlias(o_new(Alias)(pSource));
            }
        }
        return nullptr;
    }


    LanguageElement* CxxPreUnaryExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
    {
        Expression* pExpr = expr->precompileExpression(a_pPrecompiler, a_pScope);
        return a_pPrecompiler->getLanguage()->solveUnaryPreOperator(op, pExpr, a_pScope);
    }

    LanguageElement* CxxPostUnaryExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
    {
        Expression* pExpr = expr->precompileExpression(a_pPrecompiler, a_pScope);
        return a_pPrecompiler->getLanguage()->solveUnaryPostOperator(op, pExpr, a_pScope);
    }

    LanguageElement* CxxThisExpression::precompile( CxxPrecompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/, modifiers_t a_Modifiers /*= 0*/ )
    {
        Block* pBlock = a_pScope->asBlock();
        if(pBlock == nullptr)
            return nullptr;
        LocalVariable* pLocalVariable = pBlock->getLocalVariableCascade("this");
        if(pLocalVariable == nullptr)
            return nullptr;
        return pLocalVariable->toExpression();
    }

}
