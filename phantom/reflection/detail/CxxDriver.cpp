#include <phantom/phantom.h>
#include "CxxDriver.h"
#include "CxxParser.h"
#include "CxxLexer.h"

namespace phantom 
{
    CxxDriver::CxxDriver(const string& a_strName) 
        : m_pLexer(nullptr)
        , m_pParser(nullptr)
        , m_pFileName(0)
        , m_eParseType(e_ParseType_Expression)
        , m_bExpressionParsingStarted(false)
        , m_tokens(nullptr)
        , m_pCompilationModule(nullptr)
    {
        m_Result.e = nullptr;
        m_pLexer = new CxxLexer(new istringstream("$"+a_strName+"$"));
        m_pParser = new CxxParser(this);
//         m_pLexer->set_debug(true);
        m_pParser->set_debug_level(0);
        sm_pInstance = this;
    }
    CxxDriver::CxxDriver(const string& a_strName, Module* a_pCompilationModule) 
        : m_pLexer(nullptr)
        , m_pParser(nullptr)
        , m_pFileName(0)
        , m_eParseType(e_ParseType_TranslationUnit)
        , m_bExpressionParsingStarted(false)
        , m_tokens(nullptr)
        , m_pCompilationModule(a_pCompilationModule)
    {
        o_assert(a_pCompilationModule);
        m_Result.e = nullptr;
        m_pLexer = new CxxLexer(new istringstream(a_strName));
        m_pParser = new CxxParser(this);
        //         m_pLexer->set_debug(true);
        m_pParser->set_debug_level(0);
        sm_pInstance = this;
    }

    CxxDriver::~CxxDriver()
    {
        o_assert(sm_pInstance);
        sm_pInstance = nullptr;
    }

    void CxxDriver::increment_error_count()
    {
        m_pLexer->increment_error_count();
    }

    void CxxDriver::setExpressionParsingStarted()
    {
        o_assert(!m_bExpressionParsingStarted AND m_eParseType == e_ParseType_Expression); 
        m_bExpressionParsingStarted = true;
    }

    int CxxDriver::parse(vector<CxxToken*>& tokenproduction)
    {
        m_tokens = &tokenproduction;
        int result = m_pParser->parse();
        m_tokens = 0;
        return result;
    }

    void CxxDriver::setParserDebugLevel( int level )
    {
        m_pParser->set_debug_level(level);
    }

    CxxDriver* CxxDriver::sm_pInstance = 0;

}