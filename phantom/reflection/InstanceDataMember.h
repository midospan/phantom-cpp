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

#ifndef o_phantom_reflection_InstanceDataMember_h__
#define o_phantom_reflection_InstanceDataMember_h__


/* ****************** Includes ******************* */

/* ************* Class Declarations ************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)


class o_export InstanceDataMember : public ValueMember, public DataMember
{
    friend class Class;
public:
    static Class* const metaType;

public:
    InstanceDataMember(const string& a_strName, Type* a_pValueType, size_t  a_uiOffset, Range* a_pRange, uint a_uiSerializationMask, bitfield a_uiModifiers = 0);
    o_destructor ~InstanceDataMember()
    {

    }

    Range*                  getRange() const { return ValueMember::getRange(); }
    inline size_t           getOffset() const { return m_uiOffset; }
    virtual void*           getAddress( void const* a_pObject ) const { return (byte*)a_pObject + m_uiOffset; }

    // fast content type access
    Type*                   getValueType() const { return ValueMember::getValueType(); }

    // overloadings
    virtual    void         getValue(void const* a_pObject, void* dest) const = 0;
    virtual    void         setValue(void* a_pObject, void const* src) const = 0;

    virtual LanguageElement*    asLanguageElement() const  { return const_cast<InstanceDataMember*>(this); }
    virtual InstanceDataMember* asInstanceDataMember() const { return const_cast<InstanceDataMember*>(this); }
    virtual StaticDataMember*   asStaticDataMember() const  { return nullptr; }
    virtual DataMember*         asDataMember() const { return const_cast<InstanceDataMember*>(this); }

    virtual Expression*       createAccessExpression(Expression* a_pLeftExpression) const;

    virtual bool            referencesData(const void* a_pInstance, const phantom::data& a_Data) const;
    
    virtual void            fetchReferencedData( const void* a_pInstance, vector<phantom::data>& out, uint a_uiSerializationMask ) const;

protected:
    virtual void referencedElementRemoved(LanguageElement* a_pElement);

protected:
    size_t  m_uiOffset;

};
o_namespace_end(phantom, reflection)



#endif
