#include <phantom/phantom.h>
#include "CxxDriver.h"
#include "CxxParser.h"
#include "CxxLexer.h"

namespace phantom 
{
    CxxDriver::CxxDriver(const string& a_strExpressionToParse) 
        : m_pLexer(nullptr)
        , m_pParser(nullptr)
        , m_pFileName(0)
        , m_eParseType(e_ParseType_Expression)
        , m_bExpressionParsingStarted(false)
        , m_tokens(nullptr)
        , m_pSource(nullptr)
        , m_uiInputStreamIndex(0)
    {
        m_Result.e = nullptr;
        m_pLexer = new CxxLexer(m_pInputStream = new istringstream("$"+a_strExpressionToParse+"$"));
        m_pParser = new CxxParser(this);
//         m_pLexer->set_debug(true);
        m_pParser->set_debug_level(0);
        sm_pInstance = this;
    }

    CxxDriver::CxxDriver(reflection::Source* a_pSource) 
        : m_pLexer(nullptr)
        , m_pParser(nullptr)
        , m_pFileName(0)
        , m_eParseType(e_ParseType_TranslationUnit)
        , m_bExpressionParsingStarted(false)
        , m_tokens(nullptr)
        , m_pSource(a_pSource)
    {
        o_assert(a_pSource);
        m_Result.e = nullptr;
        m_pLexer = new CxxLexer(m_pInputStream = a_pSource->getInputStream());
        m_pParser = new CxxParser(this);
        //         m_pLexer->set_debug(true);
        m_pParser->set_debug_level(0);
        sm_pInstance = this;
    }

    CxxDriver::~CxxDriver()
    {
        o_assert(sm_pInstance);
        sm_pInstance = nullptr;
        delete m_pLexer;
        delete m_pParser;
        if(m_eParseType == e_ParseType_Expression)
        {
            delete m_pInputStream;
        }
    }

    void CxxDriver::incrementErrorCount()
    {
        m_pLexer->incrementErrorCount();
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

    int CxxDriver::handleEndOfFile()
    {
        if(m_pSource == nullptr) 
            return 1;
        m_uiInputStreamIndex++;
        if(m_uiInputStreamIndex < m_pSource->getInputStreamCount())
        {
            m_pInputStream = m_pSource->getInputStream(m_uiInputStreamIndex);
            m_pLexer->changeInput(m_pInputStream);
            return 0;
        }
        return 1;
    }

    CxxDriver* CxxDriver::sm_pInstance = 0;

}