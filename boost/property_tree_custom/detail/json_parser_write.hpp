// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_CUSTOM_DETAIL_JSON_PARSER_WRITE_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_CUSTOM_DETAIL_JSON_PARSER_WRITE_HPP_INCLUDED

#include <boost/property_tree_custom/ptree.hpp>
#include <boost/next_prior.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <string>
#include <ostream>
#include <iomanip>

namespace boost { namespace property_tree_custom { namespace json_parser
{

    // Create necessary escape sequences from illegal characters
    template<class Str>
    Str create_escapes(const Str &s)
    {
		typedef typename Str::value_type Ch;
        Str result;
        typename Str::const_iterator b = s.begin();
        typename Str::const_iterator e = s.end();
        while (b != e)
        {
            // This assumes an ASCII superset. But so does everything in PTree.
            // We escape everything outside ASCII, because this code can't
            // handle high unicode characters.
            if (*b == 0x20 || *b == 0x21 || (*b >= 0x23 && *b <= 0x2E) ||
                (*b >= 0x30 && *b <= 0x5B) || (*b >= 0x5D && *b <= 0xFF))
                result += *b;
            else if (*b == Ch('\b')) result += Ch('\\'), result += Ch('b');
            else if (*b == Ch('\f')) result += Ch('\\'), result += Ch('f');
            else if (*b == Ch('\n')) result += Ch('\\'), result += Ch('n');
            else if (*b == Ch('\r')) result += Ch('\\'), result += Ch('r');
            else if (*b == Ch('/')) result += Ch('\\'), result += Ch('/');
            else if (*b == Ch('"'))  result += Ch('\\'), result += Ch('"');
            else if (*b == Ch('\\')) result += Ch('\\'), result += Ch('\\');
            else
            {
                const char *hexdigits = "0123456789ABCDEF";
                typedef typename make_unsigned<Ch>::type UCh;
                unsigned long u = (std::min)(static_cast<unsigned long>(
                                                 static_cast<UCh>(*b)),
                                             0xFFFFul);
                int d1 = u / 4096; u -= d1 * 4096;
                int d2 = u / 256; u -= d2 * 256;
                int d3 = u / 16; u -= d3 * 16;
                int d4 = u;
                result += Ch('\\'); result += Ch('u');
                result += Ch(hexdigits[d1]); result += Ch(hexdigits[d2]);
                result += Ch(hexdigits[d3]); result += Ch(hexdigits[d4]);
            }
            ++b;
        }
        return result;
    }

    template<class Ptree>
    void write_json_helper(typename Ptree::key_basic_ostream &stream, 
                           const Ptree &pt,
                           int indent, bool pretty)
    {

        typedef typename Ptree::key_type::value_type Ch;
        typedef typename Ptree::key_basic_string Str;

        // Value or object or array
        if (indent > 0 && pt.empty())
        {
            // Write value
            Str data = create_escapes(pt.template get_value<Str>());
            stream << Ch('"') << data << Ch('"');

        }
        else if (indent > 0 && pt.count(Str()) == pt.size())
        {
            // Write array
            stream << Ch('[');
            if (pretty) stream << Ch('\n');
            typename Ptree::const_iterator it = pt.begin();
            for (; it != pt.end(); ++it)
            {
                if (pretty) stream << Str(4 * (indent + 1), Ch(' '));
                write_json_helper(stream, it->second, indent + 1, pretty);
                if (boost::next(it) != pt.end())
                    stream << Ch(',');
                if (pretty) stream << Ch('\n');
            }
            stream << Str(4 * indent, Ch(' ')) << Ch(']');

        }
        else
        {
            // Write object
            stream << Ch('{');
            if (pretty) stream << Ch('\n');
            typename Ptree::const_iterator it = pt.begin();
            for (; it != pt.end(); ++it)
            {
                if (pretty) stream << Str(4 * (indent + 1), Ch(' '));
                stream << Ch('"') << create_escapes(it->first) << Ch('"') << Ch(':');
                if (pretty) {
                    if (it->second.empty())
                        stream << Ch(' ');
                    else
                        stream << Ch('\n') << Str(4 * (indent + 1), Ch(' '));
                }
                write_json_helper(stream, it->second, indent + 1, pretty);
                if (boost::next(it) != pt.end())
                    stream << Ch(',');
                if (pretty) stream << Ch('\n');
            }
            if (pretty) stream << Str(4 * indent, Ch(' '));
            stream << Ch('}');
        }

    }

    // Verify if ptree does not contain information that cannot be written to json
    template<class Ptree>
    bool verify_json(const Ptree &pt, int depth)
    {

        typedef typename Ptree::key_type::value_type Ch;
        typedef typename Ptree::key_basic_string Str;

        // Root ptree cannot have data
        if (depth == 0 && !pt.template get_value<Str>().empty())
            return false;
        
        // Ptree cannot have both children and data
        if (!pt.template get_value<Str>().empty() && !pt.empty())
            return false;

        // Check children
        typename Ptree::const_iterator it = pt.begin();
        for (; it != pt.end(); ++it)
            if (!verify_json(it->second, depth + 1))
                return false;

        // Success
        return true;

    }
    
    // Write ptree to json stream
    template<class Ptree>
    void write_json_internal(typename Ptree::key_basic_ostream &stream, 
                             const Ptree &pt,
                             const typename Ptree::string_type &filename,
                             bool pretty)
    {
        if (!verify_json(pt, 0))
            BOOST_PROPERTY_TREE_CUSTOM_THROW(json_parser_error<typename Ptree::string_type>("ptree contains data that cannot be represented in JSON format", filename, 0));
        write_json_helper(stream, pt, 0, pretty);
        stream << std::endl;
        if (!stream.good())
            BOOST_PROPERTY_TREE_CUSTOM_THROW(json_parser_error<typename Ptree::string_type>("write error", filename, 0));
    }

} } }

#endif
