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

#ifndef o_phantom_reflection_FunctionPointerType_h__
#define o_phantom_reflection_FunctionPointerType_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export FunctionPointerType : public PointerType
{
    o_type;

    o_declare_meta_type(FunctionPointerType);

public:
    friend class Type;

protected:
    FunctionPointerType(Signature* a_pSignature, modifiers_t a_Modifiers);

public:
    o_destructor ~FunctionPointerType(void);

    virtual void*           getClosure(void* a_pPointer) const { o_assert_no_implementation(); return nullptr; }

    virtual DelegateMemento getDelegateMemento(void* a_pPointer) const { o_assert_no_implementation(); return DelegateMemento(); }

    virtual 
    FunctionPointerType*    asFunctionPointerType() const { return const_cast<FunctionPointerType*>(this); }

    virtual boolean     isConvertibleTo(Type* a_pType) const;

    virtual void        convertValueTo(Type* a_pDestType, void* a_pDestValue, void const* a_pSrcValue) const;

    virtual void        copy(void* a_pDest, void const* a_pSrc) const;
    
    virtual void        valueFromString(const string& a_str, void* dest) const;

    virtual void        valueToString(string& a_str, const void* src) const;

    virtual void        valueToLiteral(string& a_str, const void* src) const;

    virtual boolean     isImplicitlyConvertibleTo(Type* a_pType) const;

    virtual string      getDecoratedName() const { return getQualifiedDecoratedName(); }
    virtual string      getQualifiedName() const { return getQualifiedDecoratedName(); }
    virtual string      getQualifiedDecoratedName() const { return m_pSignature->getReturnType()->getQualifiedDecoratedName()+"(*)"+m_pSignature->getQualifiedDecoratedName(); }

    virtual bool        isCopyable() const { return true; }

    Signature*          getSignature() const { return m_pSignature; }

    virtual void        call( void* a_pPointer, void** a_pArgs ) const = 0;
    virtual void        call( void* a_pPointer, void** a_pArgs, void* a_pReturnAddress ) const 
    { 
        if(a_pReturnAddress) 
        {
            o_exception(exception::base_exception, "Expecting return address from a void function pointer call, use call(void*, void**) instead"); 
        }
        else call(a_pPointer, a_pArgs); 
    }

protected:
    virtual void        referencedElementRemoved(LanguageElement* a_pElement);

protected:
    Signature*   m_pSignature;
};

o_namespace_end(phantom, reflection)



#endif