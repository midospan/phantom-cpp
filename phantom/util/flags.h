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

#ifndef Flags_h__
#define Flags_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_begin_phantom_namespace()

template<typename E, typename _Type = uint>
class flags
{
public:
    flags() : content(0)
    {

    }
    inline void clear() { content = 0; }
    inline void set(E a_eValue)
    {
        content |= (1 << a_eValue);
    }
    inline boolean isSet(E a_eValue) const
    {
        return content >> a_eValue & 0x1;
    }
    inline void unset(E a_eValue)
    {
        content &= ~(1<<a_eValue);
    }
    inline void setValue(E a_eValue, boolean a_bValue = true)
    {
        if(a_bValue)
        {
            set(a_eValue);
        }
        else
        {
            unset(a_eValue);
        }
    }

    _Type content;

};

o_end_phantom_namespace()

#endif // Flags_h__
