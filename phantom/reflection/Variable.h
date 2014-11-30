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

#ifndef o_phantom_reflection_Variable_h__
#define o_phantom_reflection_Variable_h__



/* ****************** Includes ******************* */


/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Variable : public LanguageElement
{
public:
    Variable();
    Variable(const string& a_strName, modifiers_t a_Modifiers = 0);
    Variable(const string& a_strName, Range* a_pRange, modifiers_t a_Modifiers = 0);

    virtual void            getValue(void* a_pDest) const = 0;

    virtual void            setValue(void const* a_pSrc) const = 0;

    Range*                  getRange() const { return m_pRange; }

    virtual Variable*       asVariable() const  { return (Variable*)this; }

    virtual Variable*       clone() const = 0;

protected:
    connection::slot::list        PHANTOM_CODEGEN_m_slot_list_of_valueChanged;
    phantom::signal_t valueChanged();

protected:
    Range* m_pRange;
};

o_namespace_end(phantom, reflection)



#endif
