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

#ifndef o_phantom_TArray_h__
#define o_phantom_TArray_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
#include <phantom/util/Array.h>
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "TArray.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_h_begin

template <typename t_Ty>
class o_export TArray : public Array
{
public:
    typedef vector<t_Ty>                            container;
    typedef typename container::iterator        iterator;
    typedef typename container::const_iterator    const_iterator;
    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

public: 

    boolean    isEmpty() const { return m_Content.empty(); }

    virtual reflection::Type* getContentType() const
    {
        return phantom::typeOf<t_Ty>();
    }

    virtual void    getValue(size_t i, void* a_pDest) const 
    {
        *reinterpret_cast<t_Ty*>(a_pDest) = m_Content[i];
    }
    virtual void    setValue(size_t i, void* a_pSrc) 
    {
        m_Content[i] = *reinterpret_cast<t_Ty*>(a_pSrc);
    }

    o_forceinline void    clear() { m_Content.clear(); }

    o_forceinline void    replace(const t_Ty& a_pOld, const t_Ty& a_pNew)
    {
        std::replace(m_Content.begin(),m_Content.end(),a_pOld,a_pNew);
    }

    o_forceinline void     reserve(size_t a_uiLength) { m_Content.reserve(a_uiLength); }

    o_forceinline boolean     removeFirst(const t_Ty& a_Value)
    {
        iterator found = std::find(m_Content.begin(), m_Content.end(), a_Value);
        if(m_Content.end() == found) return false;
        m_Content.erase(found);
        return true;
    }
    o_forceinline void        removeAll( const t_Ty& a_Value ) { while(removeFirst(a_Value)); }

    o_forceinline void    popFront()
    {
        m_Content.erase(m_Content.begin());
    }

    o_forceinline void    popBack()
    {
        m_Content.pop_back();
    }

    o_forceinline t_Ty& front() 
    {
        m_Content.front();
    }

    o_forceinline const t_Ty& front()  const 
    {
        m_Content.front();
    }

    const t_Ty&        back() const
    {
        return m_Content.back();
    }

    t_Ty&            back()
    {
        return m_Content.back();
    }
    
    o_forceinline void        append(const t_Ty& a_Value) 
    { 
        m_Content.push_back(a_Value); 
    }

    o_forceinline void        addFront(const t_Ty& a_Value)
    {
        m_Content.insert(m_Content.begin(), a_Value);
    }

    o_forceinline void        addBack(const t_Ty& a_Value) 
    { 
        m_Content.push_back(a_Value); 
    }

    
    t_Ty&    get(size_t i)
    {
        return m_Content[i];
    }

    virtual size_t    getSize() const { return m_Content.size(); }

    size_t            getLength() const { return m_Content.size(); }

    boolean        contains(const t_Ty& a_Value) const 
    {
        o_foreach(const t_Ty& pO, m_Content)
        {
            if(pO == a_Value) return true;
        }
        return false;
    }
    
    template<typename _Pred>
    o_forceinline void        sort(_Pred p)
    {
        std::sort(m_Content.begin(),m_Content.end(),p);
    }

    void        set(size_t i, const t_Ty& a_pValue) 
    { 
        m_Content[i] = a_pValue; 
    }

    o_forceinline    const_iterator    begin() const { return m_Content.begin(); }
    o_forceinline    iterator    begin() { return m_Content.begin(); }
    o_forceinline    const_iterator    end() const { return m_Content.end(); }
    o_forceinline    iterator    end() { return m_Content.end(); }

    o_forceinline    const container&    content() const { return m_Content; }


protected:
    vector<t_Ty>        m_Content;
    
};

o_h_end

#else // o_phantom_TArray_h__
#include "TArray.classdef.h"
#endif