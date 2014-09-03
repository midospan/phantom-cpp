// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_CUSTOM_JSON_PARSER_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_CUSTOM_JSON_PARSER_HPP_INCLUDED

#include <boost/property_tree_custom/ptree.hpp>
#include <boost/property_tree_custom/detail/json_parser_read.hpp>
#include <boost/property_tree_custom/detail/json_parser_write.hpp>
#include <boost/property_tree_custom/detail/json_parser_error.hpp>

#include <fstream>
#include <string>
#include <locale>

namespace boost { namespace property_tree_custom { namespace json_parser
{

    /**
     * Read JSON from a the given stream and translate it to a property tree.
     * @note Clears existing contents of property tree.  In case of error the
     *       property tree unmodified.
     * @note Items of JSON arrays are translated into ptree keys with empty
     *       names. Members of objects are translated into named keys.
     * @note JSON data can be a string, a numeric value, or one of literals
     *       "null", "true" and "false". During parse, any of the above is
     *       copied verbatim into ptree data string.
     * @throw json_parser_error In case of error deserializing the property
     *                          tree.
     * @param stream Stream from which to read in the property tree.
     * @param[out] pt The property tree to populate.
     */
    template<class Ptree>
    void read_json(typename Ptree::key_basic_istream &stream,
                   Ptree &pt)
    {
        read_json_internal(stream, pt, typename Ptree::string_type());
    }

    /**
     * Read JSON from a the given file and translate it to a property tree.
     * @note Clears existing contents of property tree.  In case of error the
     *       property tree unmodified.
     * @note Items of JSON arrays are translated into ptree keys with empty
     *       names. Members of objects are translated into named keys.
     * @note JSON data can be a string, a numeric value, or one of literals
     *       "null", "true" and "false". During parse, any of the above is
     *       copied verbatim into ptree data string.
     * @throw json_parser_error In case of error deserializing the property
     *                          tree.
     * @param filename Name of file from which to read in the property tree.
     * @param[out] pt The property tree to populate.
     * @param loc The locale to use when reading in the file contents.
     */
    template<class Ptree>
    void read_json(const typename Ptree::string_type &filename,
                   Ptree &pt,
                   const std::locale &loc = std::locale())
    {
        typename Ptree::key_basic_ifstream
            stream(filename.c_str());
        if (!stream)
            BOOST_PROPERTY_TREE_CUSTOM_THROW(json_parser_error<typename Ptree::string_type>(
                "cannot open file", filename, 0));
        stream.imbue(loc);
        read_json_internal(stream, pt, filename);
    }

    /**
     * Translates the property tree to JSON and writes it the given output
     * stream.
     * @note Any property tree key containing only unnamed subkeys will be
     *       rendered as JSON arrays.
     * @pre @e pt cannot contain keys that have both subkeys and non-empty data.
     * @throw json_parser_error In case of error translating the property tree
     *                          to JSON or writing to the output stream.
     * @param stream The stream to which to write the JSON representation of the
     *               property tree.
     * @param pt The property tree to tranlsate to JSON and output.
     * @param pretty Whether to pretty-print. Defaults to true for backward
     *               compatibility.
     */
    template<class Ptree>
    void write_json(typename Ptree::for_char<typename Ptree::key_type::value_type>::basic_ostream &stream,
                    const Ptree &pt,
                    bool pretty = true)
    {
        write_json_internal(stream, pt, typename Ptree::string_type(), pretty);
    }

    /**
     * Translates the property tree to JSON and writes it the given file.
     * @note Any property tree key containing only unnamed subkeys will be
     *       rendered as JSON arrays.
     * @pre @e pt cannot contain keys that have both subkeys and non-empty data.
     * @throw json_parser_error In case of error translating the property tree
     *                          to JSON or writing to the file.
     * @param filename The name of the file to which to write the JSON
     *                 representation of the property tree.
     * @param pt The property tree to translate to JSON and output.
     * @param loc The locale to use when writing out to the output file.
     * @param pretty Whether to pretty-print. Defaults to true and last place
     *               for backward compatibility.
     */
    template<class Ptree>
    void write_json(const typename Ptree::string_type &filename,
                    const Ptree &pt,
                    const std::locale &loc = std::locale(),
                    bool pretty = true)
    {
        typename Ptree::key_basic_ofstream
            stream(filename.c_str());
        if (!stream)
            BOOST_PROPERTY_TREE_CUSTOM_THROW(json_parser_error<typename Ptree::string_type>(
                "cannot open file", filename, 0));
        stream.imbue(loc);
        write_json_internal(stream, pt, filename, pretty);
    }

} } }

namespace boost { namespace property_tree_custom
{
    using json_parser::read_json;
    using json_parser::write_json;
    using json_parser::json_parser_error;
} }

#endif
