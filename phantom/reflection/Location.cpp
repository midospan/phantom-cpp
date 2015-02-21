#include "phantom/phantom.h"
#include "Location.h"
#include "Location.hxx"

o_registerN((phantom, reflection), CodeLocation);
o_registerN((phantom, reflection), CodePosition);

o_namespace_begin(phantom, reflection)

bool CodeLocation::containsCodePosition( const CodePosition& pos ) const
{
    if(m_Start.source != m_End.source)
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
    if(m_Start.source != m_End.source)
    {
        return a_iLine >= m_Start.line || a_iLine <= m_End.line;
    }
    else 
    {
        return a_iLine >= m_Start.line AND a_iLine <= m_End.line;
    }
}

CodeLocation::CodeLocation( Source* a_pSourceFile ) : m_Start(a_pSourceFile)
    , m_End(a_pSourceFile)
{
    o_assert(m_Start.source == m_End.source);
}

CodeLocation::CodeLocation( const CodePosition& a_bip, const CodePosition& a_eip ) : m_Start(a_bip)
    , m_End(a_eip)
{
    o_assert(m_Start.source == m_End.source);
}

bool CodePosition::operator<( const CodePosition& other ) const
{
    return (source AND other.source AND (source < other.source))
        OR ( ( source AND other.source AND (source == other.source)) 
        AND ((line < other.line) 
        OR ((line == other.line)
        AND column < other.column)
        )
        );
}

o_namespace_end(phantom, reflection)

