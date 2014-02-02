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

#ifndef o_object_h__
#define o_object_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */
o_declareN(class, (phantom), object)
/* *********************************************** */
o_namespace_begin(phantom)

/**
  * \brief object stores a memory address with the reflection ClassType associated
  */
class object
{
public:
    object() : m_address(0), m_class_type(0) {}
    object(void* a_pAddress, reflection::ClassType* a_pClassType)
        : m_address(a_pAddress)
        , m_class_type(a_pClassType)
    {

    }
    template<typename t_Ty>
    inline object(t_Ty* const a_address);

    template<typename t_Ty>
    inline object& operator=(t_Ty* const a_address);

    template<typename t_Ty>
    inline t_Ty* as  ();

    boolean isNull() const { return m_address == nullptr; }
    void destroy();

    operator data  ()
    {
        return data(m_address,(reflection::Type*)m_class_type);
    }

    boolean             operator==(const phantom::object& a_Other) const
    {
        return a_Other.m_address == m_address AND a_Other.m_class_type == m_class_type;
    }

    boolean             operator!=(const phantom::object& a_Other) const
    {
        return a_Other.m_address != m_address OR a_Other.m_class_type != m_class_type;
    }

    void*                   address() const { return m_address; }
    reflection::ClassType*  classType() const { return m_class_type; }

protected:
    void*                   m_address;
    reflection::ClassType*  m_class_type;
};


o_namespace_end(phantom)

#endif // o_object_h__