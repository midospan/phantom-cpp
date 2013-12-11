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

#ifndef o_phantom_reflection_TRange_h__
#define o_phantom_reflection_TRange_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include <phantom/reflection/Range.h>
/* *********************************************** */
/* **************** Declarations ***************** */
o_declare(class, phantom, reflection, DataMember)
o_declare(class, phantom, reflection, Constructor)
/* *********************************************** */

o_namespace_begin(phantom, reflection, native)

struct null_range {};

template<typename t_Ty>
class TRange : public Range
{
public:
    TRange(t_Ty a_Min, t_Ty a_Default, t_Ty a_Max) 
        : Range(typeOf<t_Ty>()) 
        , m_Min(a_Min)
        , m_Default(a_Default)
        , m_Max(a_Max)
    {

    }

    virtual void getMin(void* a_pDest) const 
    {
        *((t_Ty*)a_pDest) = m_Min;
    }

    virtual void getMax(void* a_pDest) const
    {
        *((t_Ty*)a_pDest) = m_Max;
    }

    virtual void getDefault(void* a_pDest) const
    {
        *((t_Ty*)a_pDest) = m_Default;
    }

    virtual void setMin(const void* a_pSrc)
    {
        m_Min = *((const t_Ty*)a_pSrc);
    }

    virtual void setMax(const void* a_pSrc)
    {
        m_Max = *((const t_Ty*)a_pSrc);
    }

    virtual void setDefault(const void* a_pSrc)
    {
        m_Default = *((const t_Ty*)a_pSrc);
    }

protected:
    t_Ty m_Min;
    t_Ty m_Max;
    t_Ty m_Default;
};

template<typename t_Ty>
class TRange<const t_Ty&> : public TRange<t_Ty>
{
    TRange(const t_Ty& a_Min, const t_Ty& a_Default, const t_Ty& a_Max) : TRange<t_Ty>(a_Min, a_Default, a_Max) {}
};


template<typename t_Ty>
inline TRange<t_Ty>* CreateRange(t_Ty a_Default)
{
    return o_new(TRange<t_Ty>)(std::numeric_limits<t_Ty>::min(), a_Default, std::numeric_limits<t_Ty>::max());
}

template<>
inline TRange<null_range>* CreateRange<null_range>(null_range )
{
    return nullptr;
}

template<typename t_Ty>
inline TRange<t_Ty>* CreateRange(t_Ty a_Min, t_Ty a_Default, t_Ty a_Max)
{
    typedef boost::remove_cv<boost::remove_reference<t_Ty>::type>::type type;
    o_static_assert(boost::has_less<type>::value && boost::has_equal_to<type>::value);
    return o_new(TRange<t_Ty>)(a_Min, a_Default, a_Max);
}

template<typename t_Ty>
TRange<t_Ty>* CreateRange(t_Ty a_Min, t_Ty a_Max)
{
    return o_new(TRange<t_Ty>)(a_Min, t_Ty(), a_Max);
}

o_namespace_end(phantom, reflection, native)

    o_traits_specialize_all_super_traitNTTS(
    (phantom,reflection,native)
    , (typename)
    , (t_Ty)
    , TRange
    , (Range)
    )



#endif
