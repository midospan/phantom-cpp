#ifndef o_CxxSearchContext_h__
#define o_CxxSearchContext_h__

#include <phantom/phantom.h>
#include <iostream>

namespace phantom
{
    class CxxDriver;
    class CxxSearchContext
    {
        friend class ios;                   // Suppress GNU error message for no public constructors.
    private:
        CxxSearchContext(CxxSearchContext *nextSearch, CxxDriver* a_pDriver)
            : _next(nextSearch), _index(0), _depth(0), _size(sizeof(_status)/sizeof(_status[0])),
            _mark(0), _enable_type1(false), _line(0), _advances(0), m_pDriver(a_pDriver) {}
        CxxSearchContext(const CxxSearchContext&);
        CxxSearchContext& operator=(const CxxSearchContext&);
        bool did_search() const { return _depth > 0 ? true : false; }
        void initialise(size_t markIndex, bool enableType1);
        CxxSearchContext *queue(CxxSearchContext *& listHead);
        void reset();
    public:
        bool advance();
        bool enable_type1() const { return _enable_type1; }
        bool is_template();
        size_t mark() const { return _mark; }

    private:
        static CxxSearchContext *_current;
        static CxxSearchContext *_free;

    public:
        static size_t actual_searches;
        static size_t advances[16];
        static size_t max_search_depth;
        static size_t nested_searches;
        static size_t releases;
        static size_t search_advances;
        static size_t unnested_searches;

    public:
        static CxxSearchContext *current() { return _current; }
        static void release();
        static void start(size_t anIndex, bool enableType1, CxxDriver* a_pDriver);

    private:
        CxxSearchContext *_next;
        CxxDriver* m_pDriver;
        size_t _index;
        size_t _depth;
        size_t _size;
        size_t _mark;
        bool _enable_type1;
        size_t _line;
        size_t _advances;
        bool _status[32];
    };

} // namespace phantom

#endif // o_CxxSearchContext_h__
