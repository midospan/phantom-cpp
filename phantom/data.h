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

#ifndef o_data_h__
#define o_data_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */
o_declareN(class, (phantom), data)
/* *********************************************** */
o_namespace_begin(phantom)
/**
 * \brief data stores a memory address with the reflection Type associated
 */
class data
{
public:
    data() : m_address(0), m_type(0) {}
    data(void* a_pAddress, reflection::Type* a_pType)
        : m_address(a_pAddress)
        , m_type(a_pType)
    {

    }
    inline bool isNull() const { return m_address == NULL; }
    template<typename t_Ty>
    inline data(t_Ty* const a_address);

    template<typename t_Ty>
    inline data const& operator=(t_Ty* const a_address);

    template<typename t_Ty>
    inline t_Ty* as() const;

    phantom::data       cast(reflection::Type* a_pTargetType) const;
    void*               address() const { return m_address; }
    reflection::Type*   type() const { return m_type; }
    boolean             operator==(const phantom::data& a_Other) const
    {
        return a_Other.m_address == m_address AND a_Other.m_type == m_type;
    }
    boolean             operator!=(const phantom::data& a_Other) const
    {
        return a_Other.m_address != m_address OR a_Other.m_type != m_type;
    }
    boolean             operator<(const phantom::data& a_Other) const
    {
        return m_address == a_Other.m_address ? m_type < a_Other.m_type : m_address < a_Other.m_address;
    }
    inline void        destroy() ;

protected:
    void*              m_address;
    reflection::Type*  m_type;
};

o_namespace_end(phantom)

#endif // o_data_h__