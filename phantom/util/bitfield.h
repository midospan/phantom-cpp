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
o_begin_phantom_namespace()

class bitfield
{
public:
    bitfield()
        :m_uiContent(0)
    {
        
    }

    bitfield(const uint& a_uint) : m_uiContent(a_uint)
    {

    }

    o_forceinline void setBit(uint a_bBitIndex, boolean a_bValue)
    {
        if (a_bValue)
            m_uiContent |= (1 << a_bBitIndex);
        else
            m_uiContent &= ~(1 << a_bBitIndex);
    }

    o_forceinline boolean isBitSet(uint a_bBitIndex) const
    {
        return (0x1 & (m_uiContent >> a_bBitIndex)) == 0x1;
    }

    o_forceinline boolean matchesMask(uint value) const
    {
        return (m_uiContent&value) == value;
    }

    o_forceinline boolean matchesOneOfMask(uint value) const
    {
        return (m_uiContent&value) != 0;
    }

    o_forceinline void setMask(uint value) 
    {
        m_uiContent |= value;
    }

    operator uint() const
    {
        return m_uiContent;
    }

protected:
    uint m_uiContent;

};

o_end_phantom_namespace()

#endif // BitField_h__