#include "phantom/phantom.h"
#include "Location.h"
#include "Location.hxx"

o_registerN((phantom, reflection), CodeLocation);
o_registerN((phantom, reflection), CodePosition);

o_namespace_begin(phantom, reflection)

bool CodeLocation::containsCodePosition( const CodePosition& pos ) const
{
    if(m_Start.sourceFile != m_End.sourceFile)
    {
        if(pos.line >= m_Start.line || pos.line <= m_End.line)
        {
            if(pos.line == m_Start.line) return pos.column > m_Start.column;
            else if(pos.line == m_End.line ) return pos.column < m_End.column;
            return true;
        }
    }
    else if(pos.line >= m_Start.line AND pos.line <= m_End.line)
    {
        return ((pos.line != m_Start.line) OR (pos.column >= m_Start.column))
            AND ((pos.line != m_End.line) OR (pos.column < m_End.column));
    }
    return false;
}

bool CodeLocation::containsLine( int a_iLine ) const
{
    if(m_Start.sourceFile != m_End.sourceFile)
    {
        return a_iLine >= m_Start.line || a_iLine <= m_End.line;
    }
    else 
    {
        return a_iLine >= m_Start.line AND a_iLine <= m_End.line;
    }
}

CodeLocation::CodeLocation( SourceFile* a_pSourceFile ) : m_Start(a_pSourceFile)
    , m_End(a_pSourceFile)
{
    o_assert(m_Start.sourceFile == m_End.sourceFile);
}

CodeLocation::CodeLocation( const CodePosition& a_bip, const CodePosition& a_eip ) : m_Start(a_bip)
    , m_End(a_eip)
{
    o_assert(m_Start.sourceFile == m_End.sourceFile);
}

bool CodePosition::operator<( const CodePosition& other ) const
{
    return (sourceFile->getAbsoluteName() < other.sourceFile->getAbsoluteName())
        OR ((sourceFile->getAbsoluteName() == other.sourceFile->getAbsoluteName()) 
        AND ((line < other.line) 
        OR ((line == other.line)
        AND column < other.column)
        )
        );
}

o_namespace_end(phantom, reflection)

