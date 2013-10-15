

#ifndef o_reflection_CodeLocation_h__
#define o_reflection_CodeLocation_h__


/* ****************** Includes ******************* */
/* **************** Declarations ***************** */

/* *********************************************** */


o_namespace_begin(phantom, reflection)

class SourceFile;

struct o_export CodePosition
{
    CodePosition() : line(0), column(0) {}
    CodePosition(SourceFile* a_pSourceFile) : sourceFile(a_pSourceFile), line(0), column(0) {}
    CodePosition(SourceFile* a_pSourceFile, int l, int c) : sourceFile(a_pSourceFile), line(l), column(c) {}
    
    bool operator==(const CodePosition& other) const 
    {
        return line == other.line AND column == other.column;
    }

    bool operator!=(const CodePosition& other) const 
    {
        return !operator==(other);
    }

    bool operator<(const CodePosition& other) const;

    SourceFile* sourceFile;
    int         line;
    int         column;
  
};

class o_export CodeLocation
{
public:
	CodeLocation()
	{

    }
    CodeLocation(SourceFile* a_pSourceFile);
	CodeLocation(const CodePosition& a_bip, const CodePosition& a_eip);
	~CodeLocation(void) 	{}

    bool operator==(const CodeLocation& other) const 
    {
        return m_Start == other.m_Start AND m_End == other.m_End;
    }

    bool operator!=(const CodeLocation& other) const 
    {
        return !operator==(other);
    }

    bool operator<(const CodeLocation& other) const
    {
        return m_Start < other.m_Start;
    }

	bool		containsLine(int a_iLine) const;
    bool		containsCodePosition(const CodePosition& pos) const;

    void setStart(const CodePosition& a_Start) { m_Start = a_Start; }
    void setEnd(const CodePosition& a_End) { m_End = a_End; }
    const CodePosition& getStart() const { return m_Start; }
    const CodePosition& getEnd() const { return m_End; }
    SourceFile* getSourceFile() const { return m_Start.sourceFile == m_End.sourceFile ? m_Start.sourceFile : nullptr; }

protected:
	CodePosition		m_Start;
	CodePosition		m_End;
};

o_namespace_end(phantom, reflection)


#endif