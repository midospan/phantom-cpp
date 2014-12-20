//
//	  Title:			C++ Grammar Lexer support compilation unit.
//
//	  File Name:		CxxLexer.cpp
//
//	  Author:			E.D.Willink
//END
//
#include <phantom/phantom.h>
#include "CxxSearchContext.h"
#include "CxxToken.h"
#include "CxxDriver.h"
#include "CxxLexer.h"

namespace phantom 
{

CxxSearchContext *CxxSearchContext::_current = 0;
CxxSearchContext *CxxSearchContext::_free = 0;
size_t CxxSearchContext::actual_searches = 0;
size_t CxxSearchContext::advances[16] = { 0 };
size_t CxxSearchContext::max_search_depth = 0;
size_t CxxSearchContext::nested_searches = 0;
size_t CxxSearchContext::releases = 0;
size_t CxxSearchContext::search_advances;
size_t CxxSearchContext::unnested_searches;

//
//	Implements a binary search counter, performing the increment at the
//	_index of othe failed search.
//
bool CxxSearchContext::advance()
{
    _advances++;
    size_t i = _depth;
    if (i <= 0)
        return false;
    while (--i > _index)
        _status[i] = false;
    while (true)
    {
        if (!_status[i])
        {
            _status[i] = true;
            _index = 0;
            return true;
        }
        if (i <= 0)
            return false;
        _status[i--] = false;
    }
}

void CxxSearchContext::initialise(size_t markIndex, bool enableType1)
{
    _index = 0;
    _depth = 0;
    _mark = markIndex;
    _enable_type1 = enableType1;
    _line = line_number;
    _advances = 0;
}

bool CxxSearchContext::is_template()
{
    if (_index >= _depth)
    {
        if (_depth >= _size)
        {
            ERRMSG("Binary search depth exceeded.");
            return false;
        }
        _status[_depth++] = false;
        if (_depth > max_search_depth)
            max_search_depth = _depth;
    }
    return _status[_index++] ? false : true;
}

//
//	Put this element onto listHead, returning element under this one.
//
CxxSearchContext *CxxSearchContext::queue(CxxSearchContext *& listHead)
{
    CxxSearchContext *oldNext = _next;
    _next = listHead;
    listHead = this;
    return oldNext;
}

//
//	Release the current search buffer.
//
void CxxSearchContext::release()
{
    if (_current)
    {
        releases++;
        _current->reset();
        _current = _current->queue(_free);
    }
}

void CxxSearchContext::reset()
{
    if (did_search())
    {
        _advances++;
        actual_searches++;
    }
    if (_advances >= sizeof(advances)/sizeof(advances[0]))
        advances[sizeof(advances)/sizeof(advances[0])-1]++;
    else
        advances[_advances]++;
}

void CxxSearchContext::start(size_t anIndex, bool enableType1, CxxDriver* a_pDriver)
{
    if (!_current)
        unnested_searches++;
    else
        nested_searches++;
    if (!_free)
        _current = new CxxSearchContext(_current, a_pDriver);
    else
        _free = _free->queue(_current);
    _current->initialise(anIndex, enableType1);
}


}