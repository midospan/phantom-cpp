#ifndef o_reflection_eval_cpp_error_handler_h__
#define o_reflection_eval_cpp_error_handler_h__

#include <iostream>
#include <string>
#include <vector>

o_namespace_begin(phantom, reflection, cpp)

///////////////////////////////////////////////////////////////////////////////
//  The error handler
///////////////////////////////////////////////////////////////////////////////

template <typename t_BaseIterator, typename t_Iterator>
struct error_handler
{
    template <typename, typename, typename>
    struct result { typedef void type; };

    error_handler(t_BaseIterator first, t_BaseIterator last)
        : first(first), last(last) {}

    template <typename t_Message, typename t_What>
    void operator()(
        t_Message const& message,
        t_What const& what,
        t_Iterator err_pos) const
    {
        // retrieve underlying iterator from current token
        t_BaseIterator err_pos_base = err_pos->matched().begin();

        int line;
        t_BaseIterator line_start = get_pos(err_pos_base, line);
        if (err_pos_base != last)
        {
            std::cout << message << what << " line " << line << ':' << std::endl;
            std::cout << get_line(line_start) << std::endl;
            for (; line_start != err_pos_base; ++line_start)
                std::cout << ' ';
            std::cout << '^' << std::endl;
        }
        else
        {
            std::cout << "Unexpected end of file. ";
            std::cout << message << what << " line " << line << std::endl;
        }
    }

    t_BaseIterator get_pos(t_BaseIterator err_pos, int& line) const
    {
        line = 1;
        t_BaseIterator i = first;
        t_BaseIterator line_start = first;
        while (i != err_pos)
        {
            bool eol = false;
            if (i != err_pos && *i == '\r') // CR
            {
                eol = true;
                line_start = ++i;
            }
            if (i != err_pos && *i == '\n') // LF
            {
                eol = true;
                line_start = ++i;
            }
            if (eol)
                ++line;
            else
                ++i;
        }
        return line_start;
    }

    std::string get_line(t_BaseIterator err_pos) const
    {
        t_BaseIterator i = err_pos;
        // position i to the next EOL
        while (i != last && (*i != '\r' && *i != '\n'))
            ++i;
        return std::string(err_pos, i);
    }

    t_BaseIterator first;
    t_BaseIterator last;
    std::vector<t_Iterator> iters;
};

o_namespace_end(phantom, reflection, cpp)

#endif // error_handler_h__