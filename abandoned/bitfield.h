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

#ifndef BitField_h__
#define BitField_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */
o_namespace_begin(phantom)

//#if o__bool__enable_bitfield_type
class bitfield
{
public:
    bitfield()
        :m_iContent(0)
    {
        
    }

    bitfield(const int& a_int) : m_iContent(a_int)
    {

    }

    o_forceinline void setBit(int a_bBitIndex, boolean a_bValue)
    {
        if (a_bValue)
            m_iContent |= (1 << a_bBitIndex);
        else
            m_iContent &= ~(1 << a_bBitIndex);
    }

    o_forceinline bool isBitSet(int a_bBitIndex) const
    {
        return (0x1 & (m_iContent >> a_bBitIndex)) == 0x1;
    }

    o_forceinline bool matchesMask(int value) const
    {
        return (m_iContent&value) == value;
    }

    o_forceinline bool matchesOneOfMask(int value) const
    {
        return (m_iContent&value) != 0;
    }

    o_forceinline void setMask(int value) 
    {
        m_iContent |= value;
    }

    bitfield operator&(const int& value) const 
    {
        return bitfield(m_iContent & value);
    }

    bitfield operator&&(const int& value) const 
    {
        return bitfield(m_iContent && value);
    }

    bitfield operator|(const int& value) const 
    {
        return bitfield(m_iContent | value);
    }

    bitfield operator||(const int& value) const 
    {
        return bitfield(m_iContent || value);
    }

    bitfield operator~() const 
    {
        return bitfield(~m_iContent);
    }

    bitfield operator!() const 
    {
        return bitfield(!m_iContent);
    }

    bitfield operator-() const 
    {
        return bitfield(-m_iContent);
    }

    bitfield operator^(const int& value) const
    {
        return bitfield(m_iContent ^ value);
    }

    bitfield operator*(const int& value) const
    {
        return bitfield(m_iContent * value);
    }

    int operator*() const
    {
        return m_iContent;
    }

    bitfield& operator--()
    {
        --m_iContent;
        return *this;
    }

    bitfield& operator++()
    {
        ++m_iContent;
        return *this;
    }

    bitfield operator--(int i)
    {
        return m_iContent--;
    }

    bitfield operator++(int i)
    {
        return m_iContent++;
    }

    bitfield operator*(const bitfield& value) const
    {
        return bitfield(m_iContent * value.m_iContent);
    }

    bitfield operator+(const int& value) const
    {
        return bitfield(m_iContent + value);
    }

    bitfield operator-(const int& value) const
    {
        return bitfield(m_iContent - value);
    }

    bitfield operator%(const int& value) const
    {
        return bitfield(m_iContent % value);
    }

    bitfield operator/(const int& value) const
    {
        return bitfield(m_iContent / value);
    }

    bitfield& operator|=(const int& value)  
    {
        m_iContent |= value;
        return *this;
    }

    bitfield& operator&=(const int& value)  
    {
        m_iContent &= value;
        return *this;
    }

    bitfield& operator^=(const int& value)  
    {
        m_iContent ^= value;
        return *this;
    }

    bitfield& operator*=(const int& value)  
    {
        m_iContent *= value;
        return *this;
    }

    bitfield& operator/=(const int& value)  
    {
        m_iContent /= value;
        return *this;
    }

    bitfield& operator-=(const int& value)  
    {
        m_iContent -= value;
        return *this;
    }

    bitfield& operator+=(const int& value)  
    {
        m_iContent += value;
        return *this;
    }

    bitfield& operator%=(const int& value)
    {
        m_iContent %= value;
        return *this;
    }

    bool operator==(const int& value) const
    {
        return m_iContent == value;
    }

    bool operator==(const bitfield& value) const
    {
        return m_iContent == value.m_iContent;
    }

    bool operator!=(const int& value) const
    {
        return m_iContent != value;
    }

    bool operator<(const bitfield& value) const
    {
        return m_iContent < value.m_iContent;
    }

    bool operator>(const bitfield& value) const
    {
        return m_iContent > value.m_iContent;
    }

    bool operator<=(const bitfield& value) const
    {
        return m_iContent <= value.m_iContent;
    }

    bool operator>=(const bitfield& value) const
    {
        return m_iContent >= value.m_iContent;
    }

    bitfield operator<<(const int& value) const
    {
        return bitfield(m_iContent << value);
    }

    bitfield operator>>(const int& value) const
    {
        return bitfield(m_iContent >> value);
    }

    bitfield& operator<<=(const int& value) 
    {
        m_iContent <<= value;
        return *this;
    }

    bitfield& operator>>=(const int& value) 
    {
        m_iContent >>= value;
        return *this;
    }

    template<typename t_Ty>
    operator t_Ty() const { return m_iContent; }

protected:
    int m_iContent;

};
/*
#else 
    typedef int bitfield;
#endif*/

o_namespace_end(phantom)

template<typename t_Int>
inline phantom::bitfield operator|(t_Int l, phantom::bitfield r)
{
    return r|l;
}

template<typename t_Int>
inline phantom::bitfield operator&(t_Int l, phantom::bitfield r)
{
    return r&l;
}

#endif // BitField_h__