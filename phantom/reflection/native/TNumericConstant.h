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

#ifndef o_phantom_reflection_native_TNumericConstant_h__
#define o_phantom_reflection_native_TNumericConstant_h__


/* ****************** Includes ******************* */

/* *********************************************** */

o_namespace_begin(phantom, reflection, native)

template <typename t_Ty>
class TNumericConstant : public NumericConstant
{
    o_static_assert(boost::is_arithmetic<t_Ty>::value OR boost::is_enum<t_Ty>::value OR phantom::is_nullptr_t<t_Ty>::value);

    friend class PrimitiveType;

    typedef TNumericConstant<t_Ty> self_type;
    
public:
    TNumericConstant(const string& a_strName, t_Ty a_Value)
        : NumericConstant(a_strName) 
        , m_Value(a_Value)
    {
    }
    TNumericConstant(t_Ty a_Value)
     : NumericConstant(boost::lexical_cast<string>(a_Value)) m_Value(a_Value)
    {
    }

    virtual void deleteNow() 
    {
        o_dynamic_proxy_delete(phantom::reflection::NumericConstant, phantom::reflection::NumericConstant::metaType, self_type) this;   
    }

public:
    virtual void        getValue(void* dest) const 
    {
        *static_cast<t_Ty*>(dest) = m_Value;
    }

    virtual boolean        equals(LanguageElement* a_pObject) const 
    {
        Constant* pOther = a_pObject->asConstant();
        if(pOther == nullptr) return false;
        Type* pThisType = getValueType();
        if(NOT(pOther->getValueType()->isConvertibleTo(pThisType))) return false;
        char scratch_buffer[1024];
        pOther->getValue(&scratch_buffer[0]);
        pOther->getValueType()->convertValueTo(pThisType, &scratch_buffer[0], &scratch_buffer[0]);
        return pThisType->areValueEqual(&m_Value, &scratch_buffer[0]);
    }

    virtual Type*   getValueType() const { return typeOf<t_Ty>(); }

protected:
    t_Ty            m_Value;

};

o_namespace_end(phantom, reflection, native)

    /*o_traits_specialize_all_super_traitNTS(
    (phantom,reflection,native)
    , (typename)
    , (t_Ty)
    , TNumericConstant
    , (Constant)
    )*/

#endif
