// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_CUSTOM_DETAIL_INFO_PARSER_CHCONV_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_CUSTOM_DETAIL_INFO_PARSER_CHCONV_HPP_INCLUDED

#include <string>

namespace boost { namespace property_tree_custom { namespace info_parser
{

    template<class Alloc, class ChDest, class ChSrc>
    std::basic_string<ChDest, std::char_traits<ChDest>, Alloc> convert_chtype(const ChSrc *text)
    {
        std::basic_string<ChDest, std::char_traits<ChDest>, Alloc> result;
        while (*text)
        {
            result += ChDest(*text);
            ++text;
        }
        return result;
    }

} } }

#endif
