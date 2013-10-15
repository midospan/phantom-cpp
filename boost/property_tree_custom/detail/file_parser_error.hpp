// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_CUSTOM_DETAIL_FILE_PARSER_ERROR_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_CUSTOM_DETAIL_FILE_PARSER_ERROR_HPP_INCLUDED

#include <boost/property_tree_custom/ptree.hpp>
#include <string>

namespace boost { namespace property_tree_custom
{

    //! File parse error
	template<typename Str>
    class file_parser_error: public ptree_error<Str>
    {

    public:

        ///////////////////////////////////////////////////////////////////////
        // Construction & destruction

        // Construct error
        file_parser_error(const Str &msg,
                          const Str &file,
                          unsigned long l) :
            ptree_error<Str>(format_what(msg, file, l)),
            m_message(msg), m_filename(file), m_line(l)
        {
        }

        ~file_parser_error() throw()
            // gcc 3.4.2 complains about lack of throw specifier on compiler
            // generated dtor
        {
        }

        ///////////////////////////////////////////////////////////////////////
        // Data access

        // Get error message (without line and file - use what() to get
        // full message)
        Str message() const
        {
            return m_message;
        }

        // Get error filename
        Str filename() const
        {
            return m_filename;
        }

        // Get error line number
        unsigned long line() const
        {
            return m_line;
        }

    private:

        Str m_message;
        Str m_filename;
        unsigned long m_line;

        // Format error message to be returned by std::runtime_error::what()
        static Str format_what(const Str &msg,
                                       const Str &file,
                                       unsigned long l)
        {
            std::basic_stringstream<typename Str::value_type, std::char_traits<typename Str::value_type>, typename Str::allocator_type>
				stream;
            stream << (file.empty() ? "<unspecified file>" : file.c_str());
            if (l > 0)
                stream << '(' << l << ')';
            stream << ": " << msg;
            return stream.str();
        }

    };

} }

#endif
