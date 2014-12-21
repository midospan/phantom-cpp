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
#if o_COMPILER != o_COMPILER_VISUAL_STUDIO
#include <inttypes.h>
#else
#define SCNu64 "llu"
#endif

#include "CxxPrecompiler.hxx"

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

    LanguageElement* CxxExpression::precompileParenthesized( Precompiler* a_pPrecompiler, CxxParenthesised* a_pParen, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/ )
    {
        Expression* pExpression = precompileExpression(a_pPrecompiler, a_pScope, a_pLHS);
        if(pExpression == nullptr)
        {
            o_semantic_error("invalid expression on left hand side of () operator");
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
        return pExpression->precompileOperator(a_pPrecompiler, "()", exprs);
    }

    LanguageElement* CxxScopedPointerExpression::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        o_warning(false, __FUNCTION__ "not implemented");
        return nullptr;
    }

    LanguageElement* CxxCStyleCastExpression::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        Type* pCastType = type->precompileType(a_pPrecompiler, a_pScope);
        if(pCastType == nullptr) return nullptr;
        Expression* pExpr = expr->precompileExpression(a_pPrecompiler, a_pScope);
        if(pExpr == nullptr) return nullptr;
        return pExpr->cast(pCastType);
    }

    LanguageElement* CxxName::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        if(words.empty())
        {
            o_semantic_error("rmpty name");
            return nullptr;
        }
        if(!isTemplate)
        {
            LanguageElement* pScope = a_pScope;
            bool cascadeSearch = true;
            if(a_pLHS)
            {
                pScope = a_pLHS;
                cascadeSearch = false;
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
                    LanguageElement* pChildScope = nullptr;
                    if(it->templateArgs != nullptr)
                    {
                        vector<LanguageElement*> templateElements;
                        it->templateArgs->precompile(a_pPrecompiler, a_pScope, templateElements);
                        pChildScope = cascadeSearch // if we don't have a left-hand side, we look recursively through all scope hierarchy
                                        ? pScope->precompileScopeCascade(a_pPrecompiler, it->id, &templateElements, nullptr, 0) 
                                        : pScope->precompileScope(a_pPrecompiler, it->id, &templateElements, nullptr, 0);
                    }
                    else 
                    {
                        pChildScope = cascadeSearch // if we don't have a left-hand side, we look recursively through all scope hierarchy
                                        ? pScope->precompileScopeCascade(a_pPrecompiler, it->id, nullptr, nullptr, 0)
                                        : pScope->precompileScope(a_pPrecompiler, it->id, nullptr, nullptr, 0);
                    }
                    if(pChildScope == nullptr)
                    {
                        o_semantic_error("undefined symbol '"<<it->id<<"' in scope '"<<pScope->getQualifiedDecoratedName()<<"'");
                        return nullptr;
                    }
                    pScope = pChildScope;
                }
            }
            Type* pType = pScope->asType();
            if(pType)
            {
                if(declSpecifier)
                    return declSpecifier->specify(pType);
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

    LanguageElement* CxxName::precompileParenthesized( Precompiler* a_pPrecompiler, CxxParenthesised* aParenthesised, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        if(words.empty())
        {
            o_semantic_error("empty name");
            return nullptr;
        }
        if(!isTemplate)
        {
            LanguageElement* pScope = a_pScope;
            bool cascadeSearch = true;
            if(a_pLHS)
            {
                pScope = a_pLHS;
                cascadeSearch = false;
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
                    LanguageElement* pChildScope = nullptr;
                    if(it->templateArgs != nullptr)
                    {
                        vector<LanguageElement*> templateElements;
                        it->templateArgs->precompile(a_pPrecompiler, a_pScope, templateElements);
                        pChildScope = cascadeSearch // if we don't have a left-hand side, we look recursively through all scope hierarchy
                            ? pScope->precompileScopeCascade(a_pPrecompiler, it->id, &templateElements, nullptr, 0) 
                            : pScope->precompileScope(a_pPrecompiler, it->id, &templateElements, nullptr, 0);
                    }
                    else 
                    {
                        pChildScope = cascadeSearch // if we don't have a left-hand side, we look recursively through all scope hierarchy
                            ? pScope->precompileScopeCascade(a_pPrecompiler, it->id, nullptr, nullptr, 0)
                            : pScope->precompileScope(a_pPrecompiler, it->id, nullptr, nullptr, 0);
                    }
                    if(pChildScope == nullptr)
                    {
                        o_semantic_error("undefined symbol '"<<it->id<<"' in scope '"<<pScope->getQualifiedDecoratedName()<<"'");
                        return nullptr;
                    }
                    pScope = pChildScope;
                }
                cascadeSearch = false;
            }
            vector<LanguageElement*> argumentsOrParameters;
            modifiers_t modifiers = 0;
            aParenthesised->precompile(a_pPrecompiler, pScope, argumentsOrParameters, &modifiers);
            LanguageElement* pPrecompiled = nullptr;
            if(last->templateArgs)
            {
                vector<LanguageElement*> templateElements;
                last->templateArgs->precompile(a_pPrecompiler, a_pScope, templateElements);

                pPrecompiled = cascadeSearch // if we don't have a left-hand side, we look recursively through all scope hierarchy
                                    ? pScope->precompileScopeCascade(a_pPrecompiler, last->id, &templateElements, &argumentsOrParameters, modifiers)
                                    : pScope->precompileScope(a_pPrecompiler, last->id, &templateElements, &argumentsOrParameters, modifiers);
                                    ;
            }
            else 
            {
                pPrecompiled = cascadeSearch // if we don't have a left-hand side, we look recursively through all scope hierarchy
                                    ? pScope->precompileScopeCascade(a_pPrecompiler, last->id, nullptr, &argumentsOrParameters, modifiers)
                                    : pScope->precompileScope(a_pPrecompiler, last->id, nullptr, &argumentsOrParameters, modifiers);
            }
            return pPrecompiled;
        }
        else 
        {
            o_assert(false, "template instanciation not supported by compilation yet");
            return nullptr;
        }
    }

    LanguageElement* CxxName::precompileTypedParenthesized( Precompiler* a_pPrecompiler, Type* a_pType, CxxParenthesised* a_pParen, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/ )
    {
        const string& id = asIdentifier();
        if(id.empty())
        {
            o_semantic_error("illformed function identifier");
        }
        modifiers_t modifiers = 0;
        declSpecifier->specify(a_pType, &modifiers);
        Signature* pSignature = o_new(Signature)(pType, parameters, (modifiers&o_const) ? o_const : 0);

        bool isMemberFunctionInternalDefinition = a_pScope->asClassType();
        bool isMemberFunctionExternalDefinition = (a_pScope->asNamespace() AND a_pLHS AND a_pLHS->asClassType());
        if(isMemberFunctionInternalDefinition OR isMemberFunctionExternalDefinition) // member function
        {
            // Member function
            vector<LanguageElement*> argumentsOrParameters;
            vector<Parameter*> parameters;
            aParenthesised->precompile(a_pPrecompiler, a_pScope, argumentsOrParameters, &modifiers);

            MemberFunction* pMemberFunction = nullptr;

            if(isMemberFunctionExternalDefinition)
            {
                if(modifiers & ~o_const)
                {
                    o_semantic_error("illegal specifiers on member function outscoped definition");
                }
                // if external definition we must already have created the member function
                CxxTemplateArguments* pLastTemplateArgs = getLastTemplateArguments();
                vector<LanguageElement*> templateArgs;
                pLastTemplateArgs->precompile(a_pPrecompiler, a_pScope, templateArgs);
                LanguageElement* pDeclaredElement = a_pLHS->precompileScope(id, templateArgs, &argumentsOrParameters, (modifiers&o_const) ? o_const : o_noconst);
                MemberFunction* pMemberFunction = nullptr;
                if(pDeclaredElement == nullptr OR (pMemberFunction = pDeclaredElement->asMemberFunction()))
                {
                    o_semantic_error("member function declaration not found for the current definition");
                }
            }
            for(auto it = argumentsOrParameters.begin(); it != argumentsOrParameters.end(); ++it)
            {
                LanguageElement* pElem = *it;
                if(pElem->asParameter())
                {
                    parameters.push_back(pElem->asParameter());
                    if(isMemberFunctionExternalDefinition AND pElem->asParameter()->getInitializationExpression())
                    {
                        o_semantic_error("redefining default parameter value");
                    }
                }
                else if(pElem->asType())
                {
                    parameters.push_back(o_new(Parameter)(pElem->asType()));
                }
                else 
                {
                    parameters.push_back(nullptr);
                    o_semantic_error("unexpected expression in signature, expecting type or parameter declaration");
                }
            }
            if(pMemberFunction AND NOT(pSignature->matches(pMemberFunction->asSubroutine()->getSignature())))
            {
                o_semantic_error("member function definition only differs by return type from its declaration");
                pMemberFunction->asSubroutine()->setInvalid();
            }
            if(isMemberFunctionInternalDefinition)
            {
                if(modifiers & o_static)
                {
                    pMemberFunction = o_new(StaticMemberFunction)(id, pSignature, modifiers);
                    if(modifiers & o_virtual)
                    {
                        o_semantic_error("incompatible 'static' and 'virtual' specifiers");
                        pMemberFunction->asSubroutine()->setInvalid();
                    }
                    if(modifiers & o_const)
                    {
                        o_semantic_error("incompatible 'static' and 'const' specifiers");
                        pMemberFunction->asSubroutine()->setInvalid();
                    }
                }
                else 
                {
                    pMemberFunction = o_new(InstanceMemberFunction)(id, pSignature, modifiers);
                }
            }
            return pMemberFunction->asLanguageElement();
        }
        else 
        {
            if(modifiers & o_const)
            {
                o_semantic_error("illegal 'const' specifier on function declaration, only member functions can be const");
                // if external definition we must already have created the member function
                CxxTemplateArguments* pLastTemplateArgs = getLastTemplateArguments();
                vector<LanguageElement*> templateArgs;
                pLastTemplateArgs->precompile(a_pPrecompiler, a_pScope, templateArgs);
                LanguageElement* pDeclaredElement = a_pLHS->precompileScope(id, templateArgs, &argumentsOrParameters, (modifiers&o_const) ? o_const : o_noconst);
                MemberFunction* pMemberFunction = nullptr;
                if(pDeclaredElement == nullptr OR (pMemberFunction = pDeclaredElement->asMemberFunction()))
                {
                    o_semantic_error("member function declaration not found for the current definition");
                }
                return o_new(Function)(id, pSignature, modifiers);
            }
        }
    }

    Type* CxxName::specify( Type* a_pType, modifiers_t* modifiers )
    {
        if(words.empty()) return nullptr;
        bool typeStarted = false;
        for(auto it = words.begin(); it != words.end(); ++it)
        {
            if(*it == "volatile")
            {
                typeStarted = true;
                o_assert_no_implementation(); // add volatile
                a_pType = a_pType; // a_pType->constType();
            }
            else if(*it == "const")
            {
                typeStarted = true;
                a_pType = a_pType->constType();
            }
            else if(*it == "*")
            {
                typeStarted = true;
                a_pType = a_pType->pointerType();
            }
            else if(*it == "&")
            {
                typeStarted = true;
                a_pType = a_pType->referenceType();
            }
            else if(modifiers)
            {
                if(typeStarted)
                {
                    o_semantic_error("illegal type specifier '"<<*it<<"'");
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
        }
        return a_pType;
    }
    string CxxName::toNamespaceQualifiedName() const
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
            result += it->id;
            if(it->templateArgs)
            {
                result+=it->templateArgs->toString();
            }
        }
        return result;
    }

    LanguageElement* CxxReinterpretCastExpression::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        Type* pType = type->precompileType(a_pPrecompiler, a_pScope);
        Expression* pExpr = expr->precompileExpression(a_pPrecompiler, a_pScope);
        if(pExpr)
        {
            return pExpr->cast(pType);
        }
        return nullptr;
    }


    LanguageElement* CxxStaticCastExpression::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        Type* pType = type->precompileType(a_pPrecompiler, a_pScope);
        Expression* pExpr = expr->precompileExpression(a_pPrecompiler, a_pScope);
        if(pExpr)
        {
            return pExpr->cast(pType);
        }
        return nullptr;
    }


    LanguageElement* CxxConstCastExpression::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        Type* pType = type->precompileType(a_pPrecompiler, a_pScope);
        Expression* pExpr = expr->precompileExpression(a_pPrecompiler, a_pScope);
        if(pExpr)
        {
            return pExpr->cast(pType);
        }
        return nullptr;
    }

    LanguageElement* CxxExpressions::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        LocalVariable* pLocalVariable = a_pScope->asLocalVariable();
        if(pLocalVariable AND pLocalVariable->getName() == "this")
        {
            Block* pBlock = pLocalVariable->getBlock();
            vector<Expression*> explicitInitializations;
            // scope is the 'this' variable => precompile as member initializer list
            for(auto it = list.begin(); it != list.end(); ++it)
            {
                explicitInitializations.push_back((*it)->precompileExpression(a_pPrecompiler, a_pScope));
            }
            // Check initializations validity and fetch initialized members
            vector<InstanceDataMember*> instanceDataMembers;
            for(auto it = explicitInitializations.begin(); it != explicitInitializations.end(); ++it)
            {
                PlacementConstructionExpression* pPlacementConstructionExpression = (*it)->asPlacementConstructionExpression();
                if(pPlacementConstructionExpression)
                {
                    Expression* pPlaceExpression = pPlacementConstructionExpression->getPlaceExpression();
                    if(pPlaceExpression == nullptr)
                    {
                        o_semantic_error("invalid constructor member initialization list (1)");
                        return nullptr;
                    }
                    AddressExpression* pAddressExpression = pPlaceExpression->asAddressExpression();
                    if(pAddressExpression == nullptr)
                    {
                        o_semantic_error("invalid constructor member initialization list (2)");
                        return nullptr;
                    }
                    Expression* pAddressedExpression = pAddressExpression->getAddressedExpression();
                    if(pAddressedExpression == nullptr)
                    {
                        o_semantic_error("invalid constructor member initialization list (3)");
                        return nullptr;
                    }
                    InstanceDataMemberExpression* pInstanceDataMemberExpression = pAddressedExpression->asInstanceDataMemberExpression();
                    if(pInstanceDataMemberExpression == nullptr)
                    {
                        o_semantic_error("invalid constructor member initialization list (4)");
                        return nullptr;
                    }
                    InstanceDataMember* pInstanceDataMember = pInstanceDataMemberExpression->getInstanceDataMember();
                    if(pInstanceDataMember == nullptr)
                    {
                        o_semantic_error("invalid constructor member initialization list (5)");
                        return nullptr;
                    }
                    instanceDataMembers.push_back(pInstanceDataMember);
                }
                else 
                {
                    AssignmentExpression* pAssignmentExpression = (*it)->asAssignmentExpression();
                    if(pAssignmentExpression)
                    {
                        if(pAssignmentExpression->getLeftExpression() == nullptr)
                        {
                            o_semantic_error("invalid constructor member initialization list (6)");
                            return nullptr;
                        }
                        InstanceDataMemberExpression* pInstanceDataMemberExpression = pAssignmentExpression->getLeftExpression()->asInstanceDataMemberExpression();
                        if(pInstanceDataMemberExpression == nullptr)
                        {
                            o_semantic_error("invalid constructor member initialization list (7)");
                            return nullptr;
                        }
                        InstanceDataMember* pInstanceDataMember = pInstanceDataMemberExpression->getInstanceDataMember();
                        if(pInstanceDataMember == nullptr)
                        {
                            o_semantic_error("invalid constructor member initialization list (8)");
                            return nullptr;
                        }
                        instanceDataMembers.push_back(pInstanceDataMember);
                    }
                    else 
                    {
                        CallExpression* pCallExpression = (*it)->asCallExpression();
                        if(pCallExpression)
                        {
                            if(pCallExpression->getArgumentCount() == 0)
                            {
                                o_semantic_error("invalid constructor member initialization list (9)");
                                return nullptr;
                            }
                            Expression* pArgument = pCallExpression->getArgument(0);
                            if(pArgument == nullptr)
                            {
                                o_semantic_error("invalid constructor member initialization list (10)");
                                return nullptr;
                            }
                            InstanceDataMemberExpression* pInstanceDataMemberExpression = pArgument->asInstanceDataMemberExpression();
                            if(pInstanceDataMemberExpression == nullptr)
                            {
                                o_semantic_error("invalid constructor member initialization list (7)");
                                return nullptr;
                            }
                            InstanceDataMember* pInstanceDataMember = pInstanceDataMemberExpression->getInstanceDataMember();
                            if(pInstanceDataMember == nullptr)
                            {
                                o_semantic_error("invalid constructor member initialization list (8)");
                                return nullptr;
                            }
                            instanceDataMembers.push_back(pInstanceDataMember);
                        }
                    }
                }
            }
            o_assert(explicitInitializations.size() == instanceDataMembers.size());
            vector<Expression*> initializations;
            // One initializations gathered, we need to sort them in the member declaration order
            ClassType* pClassType = pBlock->getSubroutine()->getOwner()->asClassType();
            for(auto it = pClassType->beginInstanceDataMembers(); it != pClassType->endInstanceDataMembers(); ++it)
            {
                bool initialized = false;
                for(size_t i = 0; i<explicitInitializations.size(); ++i)
                {
                    if(instanceDataMembers[i] == *it)
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
                        pBlock->addStatement(nullptr);
                        o_semantic_error((*it)->getName()<<" : reference members must be explicitely initialized");
                    }
                    else if((*it)->getValueType()->asClassType())
                    {
                        if(NOT((*it)->getValueType()->asClassType()->isDefaultConstructible()))
                        {
                            pBlock->addStatement(nullptr);
                            o_semantic_error("class type '"<< (*it)->getValueType()->getQualifiedDecoratedName() << "' does not have default constructor");
                        }
                        else if((*it)->getValueType()->asClassType()->isAbstract())
                        {
                            pBlock->addStatement(nullptr);
                            o_semantic_error("class type '"<< (*it)->getValueType()->getQualifiedDecoratedName() << "' is abstract and cannot be used as member");
                        }
                        else 
                        {
                            Expression* pMemberExpr = (*it)->createExpression(pLocalVariable->createExpression()->dereference()); // (*this).member
                            pBlock->addExpressionStatement(o_new_elem(PlacementConstructionExpression)((*it)->getValueType()->asClassType()->getDefaultConstructor(), pMemberExpr->address(), pMemberExpr));
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
                    pPrev = pPrev ? pPrev->precompileBinaryOperator(a_pPrecompiler, ",", pExpr) : nullptr;
                }
                else 
                {
                    pPrev = pExpr;
                }
            }
            return pPrev;
        }
    }

    LanguageElement* CxxBitfieldExpression::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
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

    void CxxParenthesised::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, vector<LanguageElement*>& out, modifiers_t* modifiers )
    {
        if(parameters)
        {
            for(auto it = parameters->list.begin(); it != parameters->list.end(); ++it)
            {
                LanguageElement* pElem = (*it)->precompile(a_pPrecompiler, a_pScope);
                out.push_back(pElem);
                if(pElem == nullptr)
                {
                    o_semantic_error("invalid type, parameter or argument in parenthesized expression");
                }
            }
        }
        if(modifiers)
        {
            *modifiers = cvs ? o_const * (cvs->asIdentifier() == "const") : 0;
        }
    }

    CxxNewParenthesisExpression::CxxNewParenthesisExpression( CxxParameters *aPlace, CxxParameters *aType, CxxExpression *anInit ) : CxxNewExpression(aPlace, aType, anInit)
    {

    }


    LanguageElement* CxxCondition::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        return parameters->precompileExpression(a_pPrecompiler, a_pScope, a_pLHS);
    }


    LanguageElement* CxxDotExpression::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        return CxxDotExpression::precompileParenthesized(a_pPrecompiler, nullptr, a_pScope, a_pLHS);
    }

    LanguageElement* CxxDotExpression::precompileParenthesized( Precompiler* a_pPrecompiler, CxxParenthesised* a_pParams, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        Expression* pLeft = left->precompileExpression(a_pPrecompiler, a_pScope, a_pLHS);
        vector<Expression*> args;
        args.push_back(pLeft ? pLeft->dereference() : nullptr);
        if(pLeft == nullptr OR pLeft->isInvalid()) 
        {
            o_semantic_error("Invalid left hand side of '.' expression");
            if(a_pParams)
                return o_new_elem(CallExpression)(nullptr, args);
            else
                return o_new_elem(InstanceDataMemberExpression)(pLeft ? pLeft->dereference() : nullptr, nullptr);
        }
        const string& id = member->asIdentifier();
        if(id.empty())
        {
            o_semantic_error("Illformed identifier on right hand side of '.' expression");
            if(a_pParams)
                return o_new_elem(CallExpression)(nullptr, args);
            else
                return o_new_elem(InstanceDataMemberExpression)(pLeft ? pLeft->dereference() : nullptr, nullptr);
        }
        Expression* pAccessExpression = nullptr;
        if(a_pParams)
        {
            vector<LanguageElement*> params;
            a_pParams->precompile(a_pPrecompiler, a_pScope, params);
            LanguageElement* pElem = pLeft->precompileScope(a_pPrecompiler, id, nullptr, &params, 0);
            if(pElem == nullptr)
            {
                vector<Expression*> emptyArgs;
                emptyArgs.push_back(pLeft->dereference());
                o_semantic_error("No member function '"<<id<<"' found in type '"<<pLeft->getValueType()->getQualifiedDecoratedName()<<"' matching given arguments");
                return o_new_elem(CallExpression)(nullptr, emptyArgs);
            }
            if(pElem->asExpression() == nullptr)
            {
                o_semantic_error("Illformed call expression");
                vector<Expression*> emptyArgs;
                emptyArgs.push_back(pLeft->dereference());
                return o_new_elem(CallExpression)(nullptr, emptyArgs);
            }
            return pElem->asExpression();
        }
        else 
        {
            LanguageElement* pElem = pLeft->precompileScope(a_pPrecompiler, id, nullptr, nullptr, 0);
            if(pElem == nullptr)
            {
                o_semantic_error("No data member '"<<id<<"' found in type '"<<pLeft->getValueType()->getQualifiedDecoratedName()<<"'");
                return o_new_elem(InstanceDataMemberExpression)(pLeft, nullptr);
            }
            if(pElem->asExpression() == nullptr)
            {
                o_semantic_error("Illformed call expression");
                return o_new_elem(InstanceDataMemberExpression)(pLeft, nullptr);
            }
            return pElem->asExpression();
        }
    }

    LanguageElement* CxxArrowExpression::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        return CxxArrowExpression::precompileParenthesized(a_pPrecompiler, nullptr, a_pScope, a_pLHS);
    }

    LanguageElement* CxxArrowExpression::precompileParenthesized( Precompiler* a_pPrecompiler, CxxParenthesised* a_pParams, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        Expression* pLeft = left->precompileExpression(a_pPrecompiler, a_pScope, a_pLHS);
        vector<Expression*> args;
        args.push_back(pLeft ? pLeft->dereference() : nullptr);
        if(pLeft == nullptr OR pLeft->isInvalid()) 
        {
            o_semantic_error("Invalid left hand side of '->' expression");
            if(a_pParams)
                return o_new_elem(CallExpression)(nullptr, args);
            else
                return o_new_elem(InstanceDataMemberExpression)(pLeft ? pLeft->dereference() : nullptr, nullptr);
        }
        while(pLeft->getValueType()->removeConstReference()->asDataPointerType() == nullptr) // left is not a pointer type
        {
            Expression* pArrowedExpression = pLeft->precompileUnaryOperator(a_pPrecompiler, "->");
            if(pArrowedExpression == nullptr OR pArrowedExpression->isInvalid()) 
            {
                o_semantic_error("no operator '->' found for type '"<<pLeft->getValueType()->getQualifiedDecoratedName()<<"'");
                if(a_pParams)
                    return o_new_elem(CallExpression)(nullptr, args);
                else
                    return o_new_elem(InstanceDataMemberExpression)(pLeft, nullptr);
            }
            pLeft = pArrowedExpression;
        }
        o_assert(pLeft->getValueType()->removeConstReference()->asDataPointerType());
        pLeft = pLeft->dereference(); // dereference pointer

        const string& id = member->asIdentifier();
        if(id.empty())
        {
            o_semantic_error("Illformed identifier on right hand side of '->' expression");
            if(a_pParams)
                return o_new_elem(CallExpression)(nullptr, args);
            else
                return o_new_elem(InstanceDataMemberExpression)(pLeft, nullptr);
        }
        if(a_pParams)
        {
            vector<LanguageElement*> params;
            a_pParams->precompile(a_pPrecompiler, a_pScope, params);
            LanguageElement* pElem = pLeft->precompileScope(a_pPrecompiler, id, nullptr, &params, 0);
            if(pElem == nullptr)
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
            LanguageElement* pElem = pLeft->precompileScope(a_pPrecompiler, id, nullptr, nullptr, 0);
            if(pElem == nullptr)
            {
                o_semantic_error("No data member '"<<id<<"' found in type '"<<pLeft->getValueType()->getQualifiedDecoratedName()<<"'");
                return o_new_elem(InstanceDataMemberExpression)(pLeft, nullptr);
            }
            Expression* pAccessExpression = pElem->asExpression();
            if(pAccessExpression == nullptr OR pAccessExpression->isInvalid())
            {
                o_semantic_error("Illformed data member access");
                return pAccessExpression ? pAccessExpression : o_new_elem(InstanceDataMemberExpression)(pLeft, nullptr);
            }
            return pAccessExpression;
        }
    }

    LanguageElement* CxxArrowStarExpression::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        return CxxArrowStarExpression::precompileParenthesized(a_pPrecompiler, nullptr, a_pScope, a_pLHS);
    }

    LanguageElement* CxxArrowStarExpression::precompileParenthesized( Precompiler* a_pPrecompiler, CxxParenthesised* a_pParams, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
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
            Expression* pArrowStaredExpression = pLeft->precompileBinaryOperator(a_pPrecompiler, "->*", member->precompileExpression(a_pPrecompiler, a_pScope));
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
                    o_semantic_error((*it)->getQualifiedDecoratedName()<<" is not an expression");
                }
                args.push_back(pArg);
            }
            vector<size_t> partialMatchIndexes;
            if(NOT(pMemberFunctionPointerType->matches(args, &partialMatchIndexes)))
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
                return o_new_elem(DataMemberPointerExpression)(pDataMemberPointerType, pLeft, pMemberExpression);
            }
            return o_new_elem(DataMemberPointerExpression)(pDataMemberPointerType, pLeft, pMemberExpression);
        }
    }

    LanguageElement* CxxDotStarExpression::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        return CxxDotStarExpression::precompileParenthesized(a_pPrecompiler, nullptr, a_pScope, a_pLHS);
    }

    LanguageElement* CxxDotStarExpression::precompileParenthesized( Precompiler* a_pPrecompiler, CxxParenthesised* a_pParams, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        vector<Expression*> args;
        Expression* pLeft = left->precompileExpression(a_pPrecompiler, a_pScope, a_pLHS);
        if(pLeft == nullptr OR pLeft->isInvalid()) 
        {
            o_semantic_error("invalid left hand side of '.*' expression");
            if(a_pParams)
                return o_new_elem(MemberFunctionPointerCallExpression)(nullptr, pLeft, nullptr, args);
            else 
                return o_new_elem(DataMemberPointerExpression)(nullptr, pLeft, nullptr);
        }
        if(NOT(pLeft->hasEffectiveAddress()))
        {
            o_semantic_error("invalid r-value on left hand side of '.*' expression");
            if(a_pParams)
                return o_new_elem(MemberFunctionPointerCallExpression)(nullptr, pLeft, nullptr, args);
            else 
                return o_new_elem(DataMemberPointerExpression)(nullptr, pLeft, nullptr);
        }
        Expression* pMemberExpression = member->precompileExpression(a_pPrecompiler, a_pScope);
        if(pMemberExpression == nullptr OR pMemberExpression->isInvalid())
        {
            o_semantic_error("invalid expression on right hand side of '.*'");
            if(a_pParams)
                return o_new_elem(MemberFunctionPointerCallExpression)(nullptr, pLeft, pMemberExpression, args);
            else 
                return o_new_elem(DataMemberPointerExpression)(nullptr, pLeft, pMemberExpression);
        }

        if(a_pParams)
        {
            vector<Expression*> args;
            MemberFunctionPointerType* pMemberFunctionPointerType = pMemberExpression->getValueType()->removeConstReference()->asMemberFunctionPointerType();
            if(pMemberFunctionPointerType == nullptr)
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
                if(pArg == nullptr)
                {
                    o_semantic_error((*it)->getQualifiedDecoratedName()<<" is not an expression");
                }
                args.push_back(pArg);
            }
            vector<size_t> partialMatchIndexes;
            if(NOT(pMemberFunctionPointerType->matches(args, &partialMatchIndexes)))
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
                return o_new_elem(DataMemberPointerExpression)(pDataMemberPointerType, pLeft, pMemberExpression);
            }
            return o_new_elem(DataMemberPointerExpression)(pDataMemberPointerType, pLeft, pMemberExpression);
        }
    }

    LanguageElement* CxxEnumSpecifierId::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS )
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

    Type* CxxEnumerators::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, vector<NumericConstant*>& constants )
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

    ConstantExpression* CxxEnumerator::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope ) const
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


    LanguageElement* CxxAccessibilitySpecifier::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/ )
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


    LanguageElement* CxxBreakStatement::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        Block* pBlock = a_pScope->asBlock();
        if(pBlock == nullptr)
        {
            o_semantic_error("'break' outside block statement");
            BranchStatement* pBranchStatement = o_new_elem(BranchStatement)();
            pBranchStatement->setInvalid();
            return pBranchStatement;
        }
        LabelStatement* pBreakLabel = CxxPrecompiler::topBreakLabel();
        if(pBreakLabel == nullptr)
        {
            o_semantic_error("'break' outside breakable statement (while/for/do/switch)");
        }
        return o_new_elem(BranchStatement)(pBreakLabel);
    }


    LanguageElement* CxxContinueStatement::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        Block* pBlock = a_pScope->asBlock();
        if(pBlock == nullptr)
        {
            o_semantic_error("'continue' outside block statement");
            BranchStatement* pBranchStatement = o_new_elem(BranchStatement)();
            pBranchStatement->setInvalid();
            return pBranchStatement;
        }
        LabelStatement* pContinueLabel = CxxPrecompiler::topContinueLabel();
        if(pContinueLabel == nullptr)
        {
            o_semantic_error("'continue' outside continuable statement (while/for/do)");
        }
        return o_new_elem(BranchStatement)(pContinueLabel);
    }

    LanguageElement* CxxSwitchStatement::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
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

        LabelStatement* pBreakLabel = CxxPrecompiler::pushBreakLabel();

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
                    Expression* pTest = pTestValue->precompileBinaryOperator(a_pPrecompiler, "==", pConstantExpression, 0);
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
        CxxPrecompiler::popBreakLabel(pBreakLabel);
        return nullptr;
    }

    LanguageElement* CxxWhileStatement::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        Block* pBlock = a_pScope->asBlock();

        o_assert(pBlock);

        Block* pWhileStatement = o_new(Block)(pBlock, "while");

        Expression* pCondition = CxxWhileStatement::testExpr->precompileExpression(a_pPrecompiler, pWhileStatement);

        if(pCondition)
        {
            if(NOT(pCondition->getValueType()->isConvertibleTo(typeOf<bool>())))
            {
                pWhileStatement->setInvalid();
                o_semantic_error("cannot convert from '"<<pCondition->getValueType()->getQualifiedDecoratedName()<<"' to 'bool' in while condition");
            }
        }
        else
        {
            pWhileStatement->setInvalid();
            o_semantic_error("invalid while condition");
        }

        Expression* pConditionClone = pCondition->clone();

        LabelStatement* pBreakLabelStatement = CxxPrecompiler::pushBreakLabel();
        LabelStatement* pContinueLabelStatement = CxxPrecompiler::pushContinueLabel();
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

        CxxPrecompiler::popBreakLabel(pBreakLabelStatement);

        CxxPrecompiler::popContinueLabel(pContinueLabelStatement);

        return nullptr;
    }

    LanguageElement* CxxDoWhileStatement::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        Block* pBlock = a_pScope->asBlock();
        
        o_assert(pBlock);

        Block* pDoWhileStatement = o_new(Block)(pBlock, "do");

        Expression* pCondition = testExpr->precompileExpression(a_pPrecompiler, pDoWhileStatement);

        if(pCondition)
        {
            if(NOT(pCondition->getValueType()->isConvertibleTo(typeOf<bool>())))
            {
                pDoWhileStatement->setInvalid();
                o_semantic_error("cannot convert from '"<<pCondition->getValueType()->getQualifiedDecoratedName()<<"' to 'bool' in do while condition");
            }
        }
        else
        {
            pDoWhileStatement->setInvalid();
            o_semantic_error("invalid do while condition");
        }

        LabelStatement*     pCodeStartLabelStatement = o_new(LabelStatement)("do");

        pDoWhileStatement->addStatement(pCodeStartLabelStatement);


        LabelStatement*     pBreakLabelStatement = CxxPrecompiler::pushBreakLabel();
        LabelStatement*     pContinueLabelStatement = CxxPrecompiler::pushContinueLabel();

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

        CxxPrecompiler::popBreakLabel(pBreakLabelStatement);

        CxxPrecompiler::popContinueLabel(pContinueLabelStatement);

        return nullptr;
    }


    LanguageElement* CxxForStatement::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        Block* pBlock = a_pScope->asBlock();

        o_assert(pBlock);

        Block* pForStatement = o_new(Block)(pBlock, "for");

        LabelStatement*     pBreakLabelStatement = CxxPrecompiler::pushBreakLabel();
        LabelStatement*     pContinueLabelStatement = CxxPrecompiler::pushContinueLabel();
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

        CxxPrecompiler::popBreakLabel(pBreakLabelStatement);

        CxxPrecompiler::popContinueLabel(pContinueLabelStatement);

        return nullptr;
    }

    LanguageElement* CxxGotoStatement::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
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
        LabelStatement* pLabelStatement = CxxPrecompiler::findOrCreateLabel(pBlock->getSubroutine(), id);

        pBlock->addStatement(o_new(BranchStatement)(pLabelStatement));

        return nullptr;
    }


    LanguageElement* CxxBlock::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        Block* pBlock = a_pScope->asBlock();

        o_assert(pBlock);
        Block* pNewBlock = o_new(Block)(pBlock);

        statements->precompile(a_pPrecompiler, pNewBlock);

        return nullptr;
    }


    LanguageElement* CxxIfStatement::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
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


    LanguageElement* CxxNamespaceAliasDeclaration::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
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

    LanguageElement* CxxReturnStatement::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
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
            if(pExpression == nullptr)
            {
                pReturnStatement->setInvalid();
                o_semantic_error("invalid return value");
            }
            else if(NOT(pExpression->getValueType()->isImplicitlyConvertibleTo(pReturnType)))
            {
                pReturnStatement->setInvalid();
                o_semantic_error("cannot convert return value from '"<<pExpression->getValueType()->getQualifiedDecoratedName()<<"' to '"<<pReturnType->getQualifiedDecoratedName()<<"'");
            }
            pReturnStatement->setExpression(pExpression);
        }
        return pReturnStatement;
    }

    LanguageElement* CxxSimpleDeclaration::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        return expr->precompile(a_pPrecompiler, a_pScope, a_pLHS);
    }

    LanguageElement* CxxTemplateDeclaration::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        o_assert_no_implementation();
        return nullptr;
    }

    LanguageElement* CxxTryBlockStatement::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        o_assert_no_implementation();
        return nullptr;
    }

    LanguageElement* CxxUsingDeclaration::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        if(isTypename)
        {
            Type* pType = name->precompileType(a_pPrecompiler, a_pScope, a_pLHS);
            if(pType == nullptr)
            {
                o_semantic_error("unknown type '"<<name->toString()<<"'");
            }
            else a_pScope->addUsing(pType);
        }
        else if(a_pScope->asNamespace())
        {
            LanguageElement* pLanguageElement = name->precompile(a_pPrecompiler, a_pScope, a_pLHS);
            if(pLanguageElement == nullptr)
            {
                o_semantic_error("unknown function or type '"<<name->toString()<<"'");
            }
            else a_pScope->addUsing(pLanguageElement);
        }
        else if(a_pScope->asType())
        {
            LanguageElement* pLanguageElement = name->precompile(a_pPrecompiler, a_pScope, a_pLHS);
            if(pLanguageElement == nullptr)
            {
                o_semantic_error("unknown member '"<<name->toString()<<"'");
            }
            if(pLanguageElement->asMember() == nullptr)
            {
                o_semantic_error("only member allowed in class type using declarations");
            }
            else a_pScope->addUsing(pLanguageElement);
        }
        else 
        {
            LanguageElement* pLanguageElement = name->precompile(a_pPrecompiler, a_pScope, a_pLHS);
            if(pLanguageElement == nullptr)
            {
                o_semantic_error("unknown function or type '"<<name->toString()<<"'");
            }
            else a_pScope->addUsing(pLanguageElement);
        }
        return nullptr;
    }

    LanguageElement* CxxUsingNamespaceDirective::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        Namespace* pNamespace = name->precompileNamespace(a_pPrecompiler, a_pScope, a_pLHS);
        if(pNamespace == nullptr)
        {
            o_semantic_error("unknown namespace '"<<name->toString()<<"'");
        }
        else a_pScope->addUsing(pNamespace);
        return nullptr;
    }


    LanguageElement* CxxLabelStatement::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/ )
    {
        Block* pBlock = a_pScope->asBlock();
        o_assert(pBlock AND pBlock->getSubroutine());
        const string& id = label->asIdentifier();
        if(id.empty())
        {
            o_semantic_error("illformed label name '"<<label->toString()<<"'");
        }
        pBlock->addStatement(CxxPrecompiler::findOrCreateLabel(pBlock->getSubroutine(), id));
        statement->precompile(a_pPrecompiler, a_pScope, a_pLHS);
        return nullptr;
    }

    LanguageElement* CxxCallExpression::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        return expr->precompileParenthesized(a_pPrecompiler, parenthesised, a_pScope, a_pLHS);
    }

    LanguageElement* CxxVariableDeclarationExpression::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        Type* pType = typeExpression->precompileType(a_pPrecompiler, a_pScope, a_pLHS);
        pType = declarator->name->declSpecifier->specify(pType);
        o_assert(pType);
        CxxName* name = nameExpression->asName();
        if(name)
        {
            Type* pTestSpecified = name->specify(pType);
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

    LanguageElement* CxxBinaryExpression::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/ )
    {
        LanguageElement* pLeft = nullptr;
        LanguageElement* pRight = nullptr;
        if(op == "*" OR op == "&")
        {
            pLeft = left->precompile(a_pPrecompiler, a_pScope);
            if(pLeft == nullptr)
            {
                o_semantic_error("invalid operand or type on left-hand side of "<<op);
                return o_new(BinaryOperationExpression)(nullptr, op, nullptr, right->precompileExpression(a_pPrecompiler, a_pScope));
            }
            Type* pType = pLeft->asType();
            if(pType)
            {
                if(declSpecifier)
                    pType = declSpecifier->specify(pType);
                if(pType == nullptr)
                {
                    o_semantic_error("invalid type declaration specifier");
                }
                auto* decl = new CxxDeclSpecifierId(op);
                pType = decl->specify(pType);
                if(pType == nullptr)
                {
                    o_semantic_error("invalid type declaration specifier");
                }
                CxxName* name = right->asName();
                if(name)
                {
                    Type* pTestSpecified = name->specify(pType);
                    if(pTestSpecified) 
                        return pTestSpecified;
                    const string& id = name->asIdentifier();
                    if(id.empty())
                    {
                        o_semantic_error("illformed parameter or variable identifier "<<name->toString());
                    }
                    if(CxxPrecompiler::Top()->hasFlag(CxxPrecompiler::e_Flag_ExpressionMode))
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
        }
        else 
        {
            pLeftExpression = precompileExpression(a_pPrecompiler, a_pScope);
        }
        if(pLeftExpression == nullptr)
        {
            o_semantic_error("invalid operand or type on left-hand side of "<<op);
            return o_new(BinaryOperationExpression)(nullptr, op, nullptr, right->precompileExpression(a_pPrecompiler, a_pScope));
        }
        Expression* pRightExpression = right->precompileExpression(a_pPrecompiler, a_pScope);
        if(pRightExpression == nullptr)
        {
            o_semantic_error("invalid operand or type on right-hand side of "<<op);
            return o_new(BinaryOperationExpression)(nullptr, op, pLeftExpression, nullptr);
        }
        return pLeftExpression->precompileBinaryOperator(a_pPrecompiler, op, pRightExpression);
    }

    LanguageElement* CxxArrayAccessExpression::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS )
    {
        LanguageElement* pElement = expression->precompile(a_pPrecompiler, a_pScope, a_pLHS);
        Expression* pIndex = index->precompileExpression(a_pPrecompiler, a_pScope);
        if(pIndex == nullptr)
        {
            o_semantic_error("invalid array index expression");
            return o_new(ArrayExpression)(nullptr, nullptr);
        }
        if(pElement == nullptr OR pElement->isInvalid())
        {
            o_semantic_error("invalid array expression");
            return o_new(ArrayExpression)(pElement ? pElement->asExpression() : nullptr, pIndex);
        }
        if(pElement->asExpression())
        {
            Expression* pExpression = pElement->asExpression();
            if(pExpression->getValueType()->removeConstReference()->asArrayType())
            {
                return o_new_elem(ArrayExpression)(pElement->asExpression(), pIndex);
            }
            else 
            {
                return pExpression->precompileBinaryOperator(a_pPrecompiler, "[]", pIndex);
            }
        }
        else if(pElement->asType())
        {
            ConstantExpression* pConstantIndex = pIndex->asConstantExpression();
            if(pConstantIndex == nullptr OR pConstantIndex->isInvalid())
            {
                o_semantic_error("array size specifier must be an integral constant");
                return o_new_elem(ArrayExpression)(nullptr, pIndex);
            }
            if(pConstantIndex->getValueType()->asIntegralType() == nullptr)
            {
                o_semantic_error("array size specifier must be an integral constant");
                return o_new_elem(ArrayExpression)(nullptr, pIndex);
            }
            size_t size = 0;
            pIndex = pIndex->implicitCast(typeOf<size_t>());
            o_assert(pIndex);
            pIndex->load(&size);
            if(size == 0)
            {
                o_semantic_error("illegal array with '0' size");
                return o_new_elem(ArrayExpression)(nullptr, pIndex);
            }
            return pElement->asType()->arrayType(size);
        }
        else 
        {
            o_semantic_error("illformed array expression");
            return o_new_elem(ArrayExpression)(nullptr, nullptr);
        }
    }


    LanguageElement* CxxAbstractFunctionExpression::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
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
                    pPrev = pPrev ? pPrev->precompileBinaryOperator(a_pPrecompiler, ",", pExpr) : nullptr;
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


    LanguageElement* CxxStringLiteralExpression::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
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


    LanguageElement* CxxParameter::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/ )
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
                    if(pExpression == nullptr)
                    {
                        o_semantic_error("illformed parameter default value expression");
                    }
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


    void CxxAccessSpecifier::precompile( modifiers_t& modifiers )
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


    Class* CxxBaseSpecifier::precompile( Precompiler* a_pPrecompiler, Class* a_pDerivedClass, modifiers_t& modifiers )
    {
        accessSpecifier->precompile(modifiers);
        modifiers |= (isVirtual * o_virtual);
        LanguageElement* pElement = name->precompile(a_pPrecompiler, a_pDerivedClass, nullptr);
        if(pElement == nullptr)
        {
            o_semantic_error("unknown symbol as base class '"<<name->toString()<<"'");
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
                o_semantic_error("a class cannot inherit from itself");
            }
            if(pBaseClass->isKindOf(a_pDerivedClass))
            {
                o_semantic_error("illegal given base class derives itself from the current class");
            }
            if(a_pDerivedClass->isKindOf(pBaseClass))
            {
                o_semantic_error("class already derives from the given base class");
            }
        }
        return pBaseClass;
    }


    void CxxBaseSpecifiers::precompile( Precompiler* a_pPrecompiler, Class* a_pClass )
    {
        for(auto it = list.begin(); it != list.end(); ++it)
        {
            modifiers_t modifiers = 0;
            Class* pBaseClass = (*it)->precompile(a_pPrecompiler, a_pClass, modifiers);
            a_pClass->addBaseClass(pBaseClass);
        }
    }

    ClassType* CxxClass::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope )
    {
        const string& keyid = key->asIdentifier();
        o_assert(keyid.size());
        const string& nameid = name->asIdentifier();
        if(nameid.empty())
        {
            o_semantic_error("illformed "<<keyid<<" name '"<<nameid<<"'");
        }
        ClassType* pClassType = nullptr;
        Class* pClass = nullptr;
        if(keyid == "class" OR keyid == "struct")
        {
            pClassType = pClass = o_new(Class)(nameid);
            if(keyid[0] == 's')
                pClassType->setDefaultAccess(o_public_access);
            if(baseClasses)
            {
                baseClasses->precompile(a_pPrecompiler, pClass);
            }
        }
        else if(keyid == "structure")
        {
            if(baseClasses)
            {
                o_semantic_error("structure cannot have base classes");
            }
            pClassType = o_new(Structure)(nameid);
        }
        o_assert(pClassType);
        CxxDriver::Instance()->getCompilationModule()->addLanguageElement(pClassType);
        return pClassType;
    }

    LanguageElement* CxxClassMembers::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        ClassType* pClassType = class_->precompile(a_pPrecompiler, a_pScope)->asClassType();
        o_assert(CxxDriver::Instance()->getCompilationModule());
        members->precompile(a_pPrecompiler, pClassType);
        return pClassType;
    }


    void CxxMemberDeclarations::precompile( Precompiler* a_pPrecompiler, ClassType* a_pClassType )
    {
        for(auto it = list.begin(); it != list.end(); ++it)
        {
            (*it)->precompile(a_pPrecompiler, a_pClassType);
        }
    }


    LanguageElement* CxxMemberDeclaration::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /*= nullptr*/ )
    {
        o_assert(a_pScope->asClassType());
        o_assert_no_implementation();
        return nullptr;
        //return declaration->precompile(a_pPrecompiler, a_pScope, a_pLHS);
    }


    LanguageElement* CxxFunctionBody::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        // If we precompile a function body, we suppose having at worst root block from Subroutine::createBlock
        Block* pBlock = a_pScope->asBlock();

        o_assert(pBlock);
        Block* pNewBlock = o_new(Block)(pBlock);

        statement->precompile(a_pPrecompiler, pNewBlock);

        return nullptr;
    }


    LanguageElement* CxxTypedExpression::precompile( Precompiler* a_pPrecompiler, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        Type* pType = name->precompileType(a_pPrecompiler, a_pScope, a_pLHS);
        CxxName* name = expr->asName();
        if(name)
        {
            Type* pTestSpecified = name->specify(pType);
            if(pTestSpecified)
                return pTestSpecified;
        }
        o_assert_no_implementation();
        return nullptr;
    }

    LanguageElement* CxxTypedExpression::precompileParenthesized( Precompiler* a_pPrecompiler, CxxParenthesised* a_pParen, LanguageElement* a_pScope, LanguageElement* a_pLHS /* = nullptr */ )
    {
        Type* pType = name->precompileType(a_pPrecompiler, a_pScope, a_pLHS);
        CxxName* name = expr->asName();
        if(name)
        {
            Type* pTestSpecified = name->specify(pType);
            if(pTestSpecified)
                return pTestSpecified;
            // scoped name (probably function definition)
            CxxName* back = name->takeBack(); // split last word to obtain LHS scope
            LanguageElement* pLHS = nullptr;
            if(name->size())
            {
                if(a_pScope->asNamespace() == nullptr)
                {
                    o_semantic_error("member function must be defined in a namespace");
                }
                pLHS = name->precompile(a_pPrecompiler, a_pScope);
                if(pLHS == nullptr)
                {
                    o_semantic_error("invalid member function scope name");
                }
                if(pLHS->asType()==nullptr OR pLHS->asNamespace()==nullptr)
                {
                    o_semantic_error("member function scope must be a class/union/struct or namespace");
                }
            }
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
            LanguageElement* pElement = back->precompileTypedParenthesized(a_pPrecompiler, pType, a_pParen, a_pScope, pLHS);
            if(pElement == nullptr)
            {
                o_semantic_error("invalid function declaration");
            }
            name->swallow(back); // restore initial name 
        }
    }

}
