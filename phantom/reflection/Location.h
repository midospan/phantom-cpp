

#ifndef o_reflection_CodeLocation_h__
#define o_reflection_CodeLocation_h__


/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
o_declareN(struct, (phantom, reflection), CodePosition);
o_declareN(class, (phantom, reflection), CodeLocation);
/* *********************************************** */


o_namespace_begin(phantom, reflection)

class Source;

struct o_export CodePosition
{
    CodePosition() : source(nullptr), line(0), column(0) {}
    CodePosition(int l, int c) : source(0), line(l), column(c) {}
    CodePosition(Source* a_pSourceFile) : source(a_pSourceFile), line(0), column(0) {}
    CodePosition(Source* a_pSourceFile, int l, int c) : source(a_pSourceFile), line(l), column(c) {}
    
    bool operator==(const CodePosition& other) const 
    {
        return line == other.line AND column == other.column;
    }

    bool operator!=(const CodePosition& other) const 
    {
        return !operator==(other);
    }

    bool operator<(const CodePosition& other) const;

    Source* source;
    int         line;
    int         column;
  
};

class o_export CodeLocation
{
public:
	CodeLocation()
	{

    }
    CodeLocation(Source* a_pSourceFile);
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
    Source* getSource() const { return m_Start.source == m_End.source ? m_Start.source : nullptr; }

    inline CodeLocation operator|(const CodeLocation& other) const // union 
    {
        CodeLocation union_ = *this;
        if(other.m_Start < m_Start)
            union_.m_Start = other.m_Start;
        if(m_End < other.m_End )
            union_.m_End = other.m_End;
        return union_;
    }

protected:
	CodePosition		m_Start;
	CodePosition		m_End;
};

// 
// 
// struct CodeLocationMap
// {
//     CodeLocationMap(const CodeLocation& location)
//         : root(location) {}
//     CodeLocationNode root;
// 
//     CodeLocationNode* insert(const CodeLocation& location)
//     {
//         root.location.containsCodePosition(location.begin);
//     }
// };
// 
// struct CodeLocationNode
// {
//     CodeLocationNode(const CodeLocation& loc) 
//         : location(loc), element(nullptr), message(nullptr), userdata(nullptr), parent(nullptr) {}
//     CodeLocation location;
//     LanguageElement* element;
//     Message* message;
//     void* userdata;
//     CodeLocationNode* parent;
//     list<CodeLocationNode*> children;
// };

o_namespace_end(phantom, reflection)


#endif