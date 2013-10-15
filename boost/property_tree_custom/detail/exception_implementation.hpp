// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
// Copyright (C) 2009 Sebastian Redl
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_CUSTOM_DETAIL_EXCEPTIONS_IMPLEMENTATION_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_CUSTOM_DETAIL_EXCEPTIONS_IMPLEMENTATION_HPP_INCLUDED

namespace boost { namespace property_tree_custom
{

    namespace detail
    {

        // Helper for preparing what string in ptree_bad_path exception
        template<typename Str, class P> inline
        Str prepare_bad_path_what(const Str &what,
                                          const P &path)
        {
            return what + Str(" (") + path.dump() + Str(")");
        }

    }

    ///////////////////////////////////////////////////////////////////////////
    // ptree_error

	template<typename Str> 
	inline ptree_error<Str>::ptree_error(const Str &w): 
        std::runtime_error(w.c_str()) 
    {
    }

	template<typename Str> 
    inline ptree_error<Str>::~ptree_error() throw()
    {
    }

    ///////////////////////////////////////////////////////////////////////////
    // ptree_bad_data

    template<typename Str>
	template<class D> inline
    ptree_bad_data<Str>::ptree_bad_data(const Str &w, const D &d):
        ptree_error<Str>(w), m_data(d)
    {
    }

	template<typename Str>
    inline ptree_bad_data<Str>::~ptree_bad_data() throw()
    {
    }

    template<typename Str>
	template<class D> inline
    D ptree_bad_data<Str>::data()
    {
        return boost::any_cast<D>(m_data);
    }

    ///////////////////////////////////////////////////////////////////////////
    // ptree_bad_path

    template<typename Str>
	template<class P> inline
    ptree_bad_path<Str>::ptree_bad_path(const Str &w, const P &p):
        ptree_error<Str>(detail::prepare_bad_path_what(w, p)), m_path(p)
    {

    }

	template<typename Str>
    inline ptree_bad_path<Str>::~ptree_bad_path() throw()
    {
    }

    template<typename Str>
	template<class P> inline
    P ptree_bad_path<Str>::path()
    {
        return boost::any_cast<P>(m_path);
    }

}}

#endif
