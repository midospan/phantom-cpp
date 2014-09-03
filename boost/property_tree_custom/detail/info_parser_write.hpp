// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_CUSTOM_DETAIL_INFO_PARSER_WRITE_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_CUSTOM_DETAIL_INFO_PARSER_WRITE_HPP_INCLUDED

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/detail/info_parser_utils.hpp"
#include <string>

namespace boost { namespace property_tree_custom { namespace info_parser
{
    template<typename Ptree, class Ch>
    void write_info_indent(typename Ptree::BOOST_NESTED_TEMPLATE for_char<Ch>::basic_ostream &stream,
          int indent,
          const info_writer_settings<Ch> &settings
          )
    {
        stream << typename Ptree::BOOST_NESTED_TEMPLATE for_char<Ch>::basic_string(indent * settings.indent_count, settings.indent_char);
    }
    
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
            if (*b == Ch('\0')) result += Ch('\\'), result += Ch('0');
            else if (*b == Ch('\a')) result += Ch('\\'), result += Ch('a');
            else if (*b == Ch('\b')) result += Ch('\\'), result += Ch('b');
            else if (*b == Ch('\f')) result += Ch('\\'), result += Ch('f');
            else if (*b == Ch('\n')) result += Ch('\\'), result += Ch('n');
            else if (*b == Ch('\r')) result += Ch('\\'), result += Ch('r');
            else if (*b == Ch('\v')) result += Ch('\\'), result += Ch('v');
            else if (*b == Ch('"')) result += Ch('\\'), result += Ch('"');
            else if (*b == Ch('\\')) result += Ch('\\'), result += Ch('\\');
            else
                result += *b;
            ++b;
        }
        return result;
    }

    template<class Str>
    bool is_simple_key(const Str &key)
    {
		typedef typename Str::value_type Ch;
        const static Str chars = convert_chtype<typename Str::_Alloc, Ch, char>(" \t{};\n\"");
        return !key.empty() && key.find_first_of(chars) == key.npos;
    }
    
    template<class Str>
    bool is_simple_data(const Str &data)
	{
		typedef typename Str::value_type Ch;
        const static Str chars = convert_chtype<typename Str::_Alloc, Ch, char>(" \t{};\n\"");
        return !data.empty() && data.find_first_of(chars) == data.npos;
    }

    template<class Ptree>
    void write_info_helper(typename Ptree::key_basic_ostream &stream, 
                           const Ptree &pt, 
                           int indent,
                           const info_writer_settings<typename Ptree::key_type::value_type> &settings)
    {

        // Character type
        typedef typename Ptree::string_type::value_type Ch;
        
        // Write data
        if (indent >= 0)
        {
            if (!pt.data().empty())
            {
				typename Ptree::BOOST_NESTED_TEMPLATE for_char<Ch>::basic_string data = create_escapes(pt.template get_value<typename Ptree::string_type>());
                if (is_simple_data(data))
                    stream << Ch(' ') << data << Ch('\n');
                else
                    stream << Ch(' ') << Ch('\"') << data << Ch('\"') << Ch('\n');
            }
            else if (pt.empty())
                stream << Ch(' ') << Ch('\"') << Ch('\"') << Ch('\n');
            else
                stream << Ch('\n');
        }
        
        // Write keys
        if (!pt.empty())
        {
            
            // Open brace
            if (indent >= 0)
            {
                write_info_indent<Ptree>( stream, indent, settings);
                stream << Ch('{') << Ch('\n');
            }
            
            // Write keys
            typename Ptree::const_iterator it = pt.begin();
            for (; it != pt.end(); ++it)
            {

                // Output key
                typename Ptree::BOOST_NESTED_TEMPLATE for_char<Ch>::basic_string key = create_escapes(it->first);
                write_info_indent<Ptree>( stream, indent+1, settings);
                if (is_simple_key(key))
                    stream << key;
                else
                    stream << Ch('\"') << key << Ch('\"');

                // Output data and children  
                write_info_helper(stream, it->second, indent + 1, settings);

            }
            
            // Close brace
            if (indent >= 0)
            {
                write_info_indent<Ptree>( stream, indent, settings);
                stream << Ch('}') << Ch('\n');
            }

        }
    }

    // Write ptree to info stream
    template<class Ptree>
	void write_info_internal(typename Ptree::key_basic_ostream &stream, 
                             const Ptree &pt,
                             const typename Ptree::string_type &filename,
                             const info_writer_settings<typename Ptree::key_type::value_type> &settings)
    {
        write_info_helper(stream, pt, -1, settings);
        if (!stream.good())
            BOOST_PROPERTY_TREE_CUSTOM_THROW(info_parser_error<typename Ptree::string_type>("write error", filename, 0));
    }

} } }

#endif
