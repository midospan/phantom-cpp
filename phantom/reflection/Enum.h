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

#ifndef o_phantom_reflection_Enum_h__
#define o_phantom_reflection_Enum_h__



/* ****************** Includes ******************* */


/* **************** Declarations ***************** */

/* *********************************************** */
o_namespace_begin(phantom, reflection)

class o_export Enum : public PrimitiveType
{
    o_declare_meta_type(Enum);

public:
    Enum(); // anonymous enum;
    Enum(const string& a_strName, PrimitiveType* a_pIntType, bitfield a_Modifiers = 0);
    o_destructor ~Enum();

    inline NumericConstant* getConstant(size_t i) const  { return m_Constants[i]; }
    inline size_t           getConstantCount() const     { return m_Constants.size(); }

    NumericConstant*        getConstant(const string& a_strKey) const;

    void                addConstant(NumericConstant* a_pConstant);
    void                removeConstant(NumericConstant* a_pConstant);

    virtual LanguageElement* solveElement(
        const string& a_strName
        , const vector<TemplateElement*>* ts
        , const vector<LanguageElement*>* fs
        , bitfield a_Modifiers = 0) const;

    virtual Enum*           asEnum() const { return const_cast<Enum*>(this); }
    virtual PrimitiveType*  asIntegralType() const { return const_cast<Enum*>(this); }

    virtual boolean         isConvertibleTo(Type* a_pType) const;
    virtual boolean         isImplicitlyConvertibleTo(Type* a_pType) const;
    virtual void            convertValueTo(Type* a_pDestType, void* a_pDestValue, void const* a_pSrcValue) const;

    virtual void            valueFromString(const string& a_strIn, void* a_pDest) const;
    virtual void            valueToString(string& a_strOut, const void* a_pSrc) const;

    virtual bool            isCopyable() const { return true; }

    virtual void*           allocate(size_t n) const { return m_pIntType->allocate(n); }
    virtual void*           allocate(void) const { return m_pIntType->allocate(); }
    virtual void            deallocate(void * a_pInstance,size_t n) const { m_pIntType->deallocate(a_pInstance, n); }
    virtual void            deallocate(void * a_pInstance) const { m_pIntType->deallocate(a_pInstance); }
    virtual void            construct(void * a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize) const { m_pIntType->construct(a_pInstance, a_uiCount, a_uiChunkSectionSize); }
    virtual void            construct(void * a_pInstance) const { m_pIntType->construct(a_pInstance); }
    virtual void            destroy(void * a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize) const { m_pIntType->destroy(a_pInstance, a_uiCount, a_uiChunkSectionSize); }
    virtual void            destroy(void * a_pInstance) const { m_pIntType->destroy(a_pInstance); }
    virtual void            serialize(void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntType->serialize(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntType->serialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            serialize(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntType->serialize(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntType->serialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserialize(void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntType->deserialize(a_pInstance, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntType->deserialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserialize(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntType->deserialize(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase); }
    virtual void            deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const { m_pIntType->deserialize(a_pInstance, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase); }

    virtual void            remember(void const* a_pInstance, byte*& a_pBuffer) const { m_pIntType->remember(a_pInstance, a_pBuffer); }
    virtual void            remember(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer) const { m_pIntType->remember(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pBuffer); }
    virtual void            reset(void* a_pInstance, byte const*& a_pBuffer) const { m_pIntType->reset(a_pInstance, a_pBuffer); }
    virtual void            reset(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer) const { m_pIntType->reset(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pBuffer); }
    virtual void            interpolate(void* a_src_start, void* a_src_end, real a_fPercent, void* a_pDest, uint mode = 0) const
    {
        m_pIntType->interpolate(a_src_start, a_src_end, a_fPercent, a_pDest, mode );
    }
    virtual void copy(void* a_pDest, void const* a_pSrc) const 
    { 
        m_pIntType->copy(a_pDest, a_pSrc); 
    }

protected:
    virtual void elementAdded(LanguageElement* a_pElement);
    virtual void elementRemoved(LanguageElement* a_pElement);
    Enum(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_Modifiers = 0);
    Enum(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, uint a_uiGuid, bitfield a_Modifiers = 0);

protected:
    typedef phantom::vector<NumericConstant*>   value_vector;
    value_vector                                m_Constants;
    reflection::Type*                           m_pIntType;
};

o_namespace_end(phantom, reflection)

o_namespace_begin(phantom)

template<typename t_Ty>
struct string_converter_helper<t_Ty, false, true>
{
    static void toLiteral(const reflection::Enum* a_pEnum, string& a_strOut, const t_Ty* a_pSrc)
    {
        a_pEnum->reflection::Enum::valueToLiteral(a_strOut, a_pSrc);
    }
    static void to(const reflection::Enum* a_pEnum, string& a_strOut, const t_Ty* a_pSrc)
    {
        a_pEnum->reflection::Enum::valueToString(a_strOut, a_pSrc);
    }
    static void from(const reflection::Enum* a_pEnum, const string& a_strIn, t_Ty* a_pDest)
    {
        a_pEnum->reflection::Enum::valueFromString(a_strIn, a_pDest);
    }
};

o_namespace_end(phantom)


#endif
