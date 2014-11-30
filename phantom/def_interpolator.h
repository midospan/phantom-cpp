/*
    This file is part of PHANTOM
         P reprocessed 
         H igh-level 
         A llocator 
         N ested state-machines and 
         T emplate 
         O riented 
         M eta-programming

    For the latest infos and sources, see http://code.google.com/p/phantom-cpp

    Copyright (C) 2008-2011 by Vivien MILLET

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE
*/

#ifndef o_def_interpolator_h__
#define o_def_interpolator_h__

o_namespace_begin(phantom)


// Interpolator

template<typename t_Ty>
struct default_interpolator;

enum default_interpolator_id
{
    default_interpolator_arithmetic,
    default_interpolator_compound,
    default_interpolator_not_available,
};

namespace detail
{
    template<typename t_Ty, int t_id>
    struct default_interpolator_helper;

    template<typename t_Ty>
    struct default_interpolator_helper <t_Ty, default_interpolator_arithmetic>
    {
        static void interpolate(t_Ty* a_src_start, t_Ty* a_src_end, real a_fPercent, t_Ty* a_dest, uint mode)
        {
            *a_dest = *a_src_start +
                static_cast<t_Ty>(
                static_cast<real>(
                *a_src_end - static_cast<real>(*a_src_start)
                )*a_fPercent
                );
        }
    };

    template<typename t_Ty>
    struct default_interpolator_helper <t_Ty, default_interpolator_not_available>
    {
        static void interpolate(t_Ty* a_src_start, t_Ty* a_src_end, real a_fPercent, t_Ty* a_dest, uint mode)
        {
            o_exception(exception::unsupported_member_function_exception, __FUNCTION__);
        }
    };

    template<typename t_Ty>
    struct default_interpolator_helper <t_Ty, default_interpolator_compound>
    {
        static void interpolate(t_Ty* a_src_start, t_Ty* a_src_end, real a_fPercent, t_Ty* a_dest, uint mode)
        {
            o_unused(a_src_start);
            o_unused(a_src_end);
            o_unused(a_fPercent);
            o_unused(a_dest);
            o_unused(mode);
            o_error(false, "not implemented");
        }
    };
}

template<typename t_Ty>
struct default_interpolator : public detail::default_interpolator_helper<t_Ty,
    boost::is_arithmetic<t_Ty>::value AND NOT(boost::is_same<bool,t_Ty>::value)
    ? default_interpolator_arithmetic
    : (boost::is_class<t_Ty>::value AND has_reflection_cascade<t_Ty>::value)
    ? default_interpolator_compound
    : default_interpolator_not_available
>
{
    o_rebind(default_interpolator)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct interpolator
///
/// \brief  interpolator.
/// 		Provides interpolation from a start value to and end value
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct interpolator : public default_interpolator<t_Ty>
{
};

o_namespace_end(phantom)

#endif // o_def_interpolator_h__