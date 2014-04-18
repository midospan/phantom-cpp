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

#ifndef o_util_flags_h__
#define o_util_flags_h__

// Inpired from Qt::Flags


namespace phantom 
{

class flag
{
    int i;
public:
    inline flag(int i);
    inline operator int() const { return i; }
};

inline flag::flag(int ai) : i(ai) {}

class incompatible_flag
{
    int i;
public:
    inline explicit incompatible_flag(int i);
    inline operator int() const { return i; }
};

inline incompatible_flag::incompatible_flag(int ai) : i(ai) {}

template<typename Enum>
class flags
{
    typedef void **Zero;
    int i;
public:
    typedef Enum enum_type;
    inline flags(const flags &f) : i(f.i) {}
    inline flags(Enum f) : i(f) {}
    inline flags(Zero = 0) : i(0) {}
    inline flags(flag f) : i(f) {}

    inline flags &operator=(const flags &f) { i = f.i; return *this; }
    inline flags &operator&=(int mask) { i &= mask; return *this; }
    inline flags &operator&=(unsigned int mask) { i &= mask; return *this; }
    inline flags &operator|=(flags f) { i |= f.i; return *this; }
    inline flags &operator|=(Enum f) { i |= f; return *this; }
    inline flags &operator^=(flags f) { i ^= f.i; return *this; }
    inline flags &operator^=(Enum f) { i ^= f; return *this; }

    inline operator int() const { return i; }

    inline flags operator|(flags f) const { return flags(Enum(i | f.i)); }
    inline flags operator|(Enum f) const { return flags(Enum(i | f)); }
    inline flags operator^(flags f) const { return flags(Enum(i ^ f.i)); }
    inline flags operator^(Enum f) const { return flags(Enum(i ^ f)); }
    inline flags operator&(int mask) const { return flags(Enum(i & mask)); }
    inline flags operator&(unsigned int mask) const { return flags(Enum(i & mask)); }
    inline flags operator&(Enum f) const { return flags(Enum(i & f)); }
    inline flags operator~() const { return flags(Enum(~i)); }

    inline bool operator!() const { return !i; }

    inline bool testFlag(Enum f) const { return (i & f) == f && (f != 0 || i == int(f) ); }
};

}


#define o_declare_flags(FlagsName, Enum)\
    typedef phantom::flags<Enum> FlagsName;

#define o_declare_incompatible_flags(flags) \
    inline incompatible_flag operator|(flags::enum_type f1, int f2) \
{ return incompatible_flag(int(f1) | f2); }

#define o_declare_operators_for_flags(flags) \
    inline flags<flags::enum_type> operator|(flags::enum_type f1, flags::enum_type f2) \
{ return flags<flags::enum_type>(f1) | f2; } \
    inline flags<flags::enum_type> operator|(flags::enum_type f1, flags<flags::enum_type> f2) \
{ return f2 | f1; } o_declare_incompatible_flags(flags)

#endif // Flags_h__
