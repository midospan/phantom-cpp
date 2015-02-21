/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Precompiler.h"
#include "Precompiler.hxx"
/* *********************************************** */
o_registerN((phantom, reflection), Precompiler);


o_namespace_begin(phantom, reflection) 

Precompiler::Precompiler( int passCount, Source* a_pSource ) 
    : m_pSource(a_pSource)
    , m_iPass(-1)
    , m_iPassCount(passCount)
    , m_pLanguage(a_pSource ? a_pSource->getLanguage() : application()->getDefaultLanguage())
{
    o_assert(passCount > 0);
}

Precompiler::~Precompiler()
{
}


void Precompiler::precompileSource( int untilPass )
{
    o_assert(untilPass>=0);
    if(m_iPass == untilPass)
        runPass(m_iPass);
    else while(m_iPass < untilPass)
    {
        runPass(++m_iPass);
    }
    o_assert(m_iPass >= untilPass);
}


o_namespace_end(phantom, reflection)